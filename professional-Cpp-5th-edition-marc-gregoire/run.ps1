<#
.SYNOPSIS
    Interactive build-and-run launcher for the Professional C++ (5th ed.) samples.

.DESCRIPTION
    Pick a chapter, then a sample, and this script compiles it with MSVC
    (C++23 / /std:c++latest) and runs it. Each sample is one folder; the file
    that contains main() is compiled together with any sibling .cpp files that
    do NOT contain their own main() (helper translation units). Build output
    goes to a gitignored .build\ folder so the source tree stays clean.

    Requires Visual Studio with the "Desktop development with C++" workload.
    The MSVC environment is bootstrapped automatically via vswhere + vcvars64.

.EXAMPLE
    .\run.ps1                       # fully interactive menu
    .\run.ps1 -Chapter 13           # jump straight to chapter 13's sample menu
    .\run.ps1 -Chapter 13 -Sample 2 # build+run sample 2 of chapter 13
    .\run.ps1 -List                 # list all chapters and exit
    .\run.ps1 -NoRun -Chapter 13 -Sample 2   # build only, do not run
#>
[CmdletBinding()]
param(
    [int]$Chapter,
    [int]$Sample,
    [int]$File,
    [switch]$List,
    [switch]$NoRun,
    [switch]$Verify
)

$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path

# Chapter number -> human-readable topic (from the book's table of contents).
$ChapterTitles = @{
    0  = 'Getting Started (setup sample: AirlineTicket)'
    1  = 'A Crash Course in C++ and the Standard Library'
    2  = 'Working with Strings and String Views'
    3  = 'Coding with Style'
    4  = 'Designing Professional C++ Programs'
    5  = 'Designing with Objects'
    6  = 'Designing for Reuse'
    7  = 'Memory Management'
    8  = 'Gaining Proficiency with Classes and Objects'
    9  = 'Mastering Classes and Objects'
    10 = 'Discovering Inheritance Techniques'
    11 = 'Odds and Ends (Modules, Namespaces, Attributes...)'
    12 = 'Writing Generic Code with Templates'
    13 = 'Demystifying C++ I/O'
    14 = 'Handling Errors'
    15 = 'Overloading C++ Operators'
    16 = 'Overview of the C++ Standard Library'
    17 = 'Understanding Iterators and the Ranges Library'
    18 = 'Standard Library Containers'
    19 = 'Function Pointers, Function Objects, and Lambda Expressions'
    20 = 'Mastering Standard Library Algorithms'
    21 = 'String Localization and Regular Expressions'
    22 = 'Date and Time Utilities'
    23 = 'Random Number Facilities'
    24 = 'Additional Library Utilities'
    25 = 'Customizing and Extending the Standard Library'
    26 = 'Advanced Templates'
    27 = 'Multithreaded Programming with C++'
    28 = 'Maximizing Software Engineering Methods'
    29 = 'Writing Efficient C++'
    30 = 'Becoming Adept at Testing'
    31 = 'Conquering Debugging'
    32 = 'Incorporating Design Techniques and Frameworks'
    33 = 'Applying Design Patterns'
    34 = 'Developing Cross-Platform and Cross-Language Applications'
}

$mainPattern = '\bint\s+main\s*\('

function Test-HasMain {
    param([Parameter(Mandatory)][string]$Path)
    $text = Get-Content -Raw -LiteralPath $Path
    if ([string]::IsNullOrEmpty($text)) { return $false }
    $stripped = [regex]::Replace($text, '/\*[\s\S]*?\*/', '')
    $stripped = [regex]::Replace($stripped, '//[^\r\n]*', '')
    return [bool]([regex]::IsMatch($stripped, $mainPattern))
}

function Initialize-Msvc {
    if ($env:VSINSTALLDIR) { return }
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
    if (-not (Test-Path $vswhere)) {
        throw "vswhere.exe not found. Install Visual Studio with the 'Desktop development with C++' workload."
    }
    $vsPath = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if (-not $vsPath) { throw "No Visual Studio install with VC tools found." }
    $vcvars = Join-Path $vsPath 'VC\Auxiliary\Build\vcvars64.bat'
    if (-not (Test-Path $vcvars)) { throw "vcvars64.bat not found at $vcvars" }
    Write-Host "Initializing MSVC environment..." -ForegroundColor DarkGray
    $envDump = cmd /c "`"$vcvars`" >nul 2>nul && set"
    foreach ($line in $envDump) {
        if ($line -match '^(?<k>[^=]+)=(?<v>.*)$') {
            Set-Item -Path "env:$($Matches.k)" -Value $Matches.v
        }
    }
}

# Return the chapter directories (Ch00, Ch01, ...) sorted by number.
function Get-Chapters {
    Get-ChildItem -LiteralPath $root -Directory -Filter 'Ch*' |
        Where-Object { $_.Name -match '^Ch(\d+)$' } |
        Sort-Object { [int]($_.Name -replace '^Ch','') }
}

function Get-ChapterNumber { param($Dir) [int]($Dir.Name -replace '^Ch','') }

# A "sample" is any leaf directory under a chapter that contains at least one .cpp file.
function Get-Samples {
    param([Parameter(Mandatory)][string]$ChapterPath)
    Get-ChildItem -LiteralPath $ChapterPath -Recurse -File -Filter '*.cpp' |
        ForEach-Object { Split-Path $_.FullName -Parent } |
        Select-Object -Unique |
        Sort-Object
}

function Show-Chapters {
    Write-Host ""
    Write-Host "Professional C++ (5th ed.) - Samples" -ForegroundColor Cyan
    Write-Host "=====================================" -ForegroundColor Cyan
    foreach ($c in Get-Chapters) {
        $n = Get-ChapterNumber $c
        $title = $ChapterTitles[$n]
        if (-not $title) { $title = '' }
        Write-Host ("  [{0,2}] {1}" -f $n, $title)
    }
    Write-Host ""
}

# Compile $MainFile + sibling non-main .cpp into .build. Returns $true on success.
function Invoke-Build {
    param(
        [Parameter(Mandatory)][string]$MainFile,
        [switch]$Quiet
    )
    Initialize-Msvc
    $main = (Resolve-Path -LiteralPath $MainFile).Path
    $dir  = Split-Path $main -Parent
    $base = [IO.Path]::GetFileNameWithoutExtension($main)

    # Sibling helper TUs (no main of their own).
    $siblings = @()
    Get-ChildItem -LiteralPath $dir -Filter *.cpp | ForEach-Object {
        if ($_.FullName -ieq $main) { return }
        if (-not (Test-HasMain -Path $_.FullName)) { $siblings += $_.FullName }
    }

    # Mirror the sample's relative path under .build so outputs stay isolated.
    $rel = $dir.Substring($root.Length).TrimStart('\','/')
    $outDir = Join-Path (Join-Path $root '.build') (Join-Path $rel $base)
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null
    $exe = Join-Path $outDir "$base.exe"

    $inputs = @($main) + $siblings
    if (-not $Quiet) {
        Write-Host ("Compiling {0}" -f (Split-Path $main -Leaf)) -ForegroundColor Cyan
        Write-Host ("  sources: {0}" -f (($inputs | ForEach-Object { Split-Path $_ -Leaf }) -join ', ')) -ForegroundColor DarkGray
    }

    Push-Location $outDir
    try {
        if ($Quiet) {
            & cl /nologo /std:c++latest /EHsc /W4 /utf-8 /MD /Zi /Fe:$exe $inputs *> $null
        } else {
            & cl /nologo /std:c++latest /EHsc /W4 /utf-8 /MD /Zi /Fe:$exe $inputs
        }
        $ok = ($LASTEXITCODE -eq 0)
    } finally { Pop-Location }
    return $ok
}

# Build one sample's main file, then run it (unless suppressed).
function Build-And-Run {
    param(
        [Parameter(Mandatory)][string]$MainFile,
        [switch]$Run
    )
    $main = (Resolve-Path -LiteralPath $MainFile).Path
    $dir  = Split-Path $main -Parent
    $base = [IO.Path]::GetFileNameWithoutExtension($main)
    $exe  = Join-Path (Join-Path (Join-Path $root '.build') ($dir.Substring($root.Length).TrimStart('\','/'))) (Join-Path $base "$base.exe")

    if (-not (Invoke-Build -MainFile $main)) {
        Write-Host "Build failed." -ForegroundColor Red
        return
    }
    Write-Host ("Built: {0}" -f $exe) -ForegroundColor Green
    if ($Run) {
        # Run inside the sample's source dir so relative data files resolve.
        Push-Location $dir
        try {
            Write-Host ("Running {0}...`n" -f $base) -ForegroundColor Cyan
            & $exe
            Write-Host ("`nProgram exited with code {0}." -f $LASTEXITCODE) -ForegroundColor DarkGray
        } finally { Pop-Location }
    }
}

function Read-Choice {
    param([string]$Prompt, [int]$Min, [int]$Max)
    while ($true) {
        $raw = Read-Host $Prompt
        if ($raw -match '^[Qq]$') { return $null }
        $val = 0
        if ([int]::TryParse($raw, [ref]$val) -and $val -ge $Min -and $val -le $Max) { return $val }
        Write-Host "Enter a number between $Min and $Max (or q to quit)." -ForegroundColor Yellow
    }
}

# Compile every runnable file in a chapter (no run). Returns $true if all pass.
function Verify-Chapter {
    param([Parameter(Mandatory)]$ChapterDir)
    $n = Get-ChapterNumber $ChapterDir
    Write-Host ("`nVerifying Ch{0:00} - {1}" -f $n, $ChapterTitles[$n]) -ForegroundColor Cyan
    $pass = 0; $fail = 0; $failed = @()
    foreach ($s in (Get-Samples -ChapterPath $ChapterDir.FullName)) {
        $mains = @(Get-ChildItem -LiteralPath $s -Filter *.cpp | Where-Object { Test-HasMain -Path $_.FullName })
        foreach ($m in $mains) {
            $relName = $m.FullName.Substring($ChapterDir.FullName.Length).TrimStart('\','/')
            if (Invoke-Build -MainFile $m.FullName -Quiet) {
                Write-Host ("  PASS  {0}" -f $relName) -ForegroundColor Green
                $pass++
            } else {
                Write-Host ("  FAIL  {0}" -f $relName) -ForegroundColor Red
                $fail++; $failed += $relName
            }
        }
    }
    Write-Host ("Ch{0:00}: {1} passed, {2} failed" -f $n, $pass, $fail) -ForegroundColor ($(if ($fail) { 'Yellow' } else { 'Green' }))
    if ($fail) { $failed | ForEach-Object { Write-Host "    - $_" -ForegroundColor Yellow } }
    return ($fail -eq 0)
}

# ------------------------------------------------------------------ main flow
if ($List) { Show-Chapters; return }

if ($Verify) {
    $targets = if ($PSBoundParameters.ContainsKey('Chapter')) {
        @(Get-Chapters | Where-Object { (Get-ChapterNumber $_) -eq $Chapter })
    } else { @(Get-Chapters) }
    if ($targets.Count -eq 0) { throw "Chapter $Chapter not found." }
    $allOk = $true
    foreach ($t in $targets) { if (-not (Verify-Chapter -ChapterDir $t)) { $allOk = $false } }
    if (-not $allOk) { exit 1 }
    return
}

# Resolve chapter directory.
$chapterDir = $null
if ($PSBoundParameters.ContainsKey('Chapter')) {
    $chapterDir = Get-Chapters | Where-Object { (Get-ChapterNumber $_) -eq $Chapter }
    if (-not $chapterDir) { throw "Chapter $Chapter not found." }
} else {
    Show-Chapters
    $sel = Read-Choice -Prompt 'Pick a chapter number (q to quit)' -Min 0 -Max 99
    if ($null -eq $sel) { return }
    $chapterDir = Get-Chapters | Where-Object { (Get-ChapterNumber $_) -eq $sel }
    if (-not $chapterDir) { Write-Host "No such chapter." -ForegroundColor Yellow; return }
}

$n = Get-ChapterNumber $chapterDir
Write-Host ""
Write-Host ("Ch{0:00} - {1}" -f $n, $ChapterTitles[$n]) -ForegroundColor Cyan

$samples = @(Get-Samples -ChapterPath $chapterDir.FullName)
if ($samples.Count -eq 0) { Write-Host "No .cpp samples in this chapter." -ForegroundColor Yellow; return }

for ($i = 0; $i -lt $samples.Count; $i++) {
    $relName = $samples[$i].Substring($chapterDir.FullName.Length).TrimStart('\','/')
    Write-Host ("  [{0,2}] {1}" -f ($i + 1), $relName)
}
Write-Host ""

# Resolve sample selection.
$sampleIndex = $null
if ($PSBoundParameters.ContainsKey('Sample')) {
    if ($Sample -lt 1 -or $Sample -gt $samples.Count) { throw "Sample $Sample out of range (1..$($samples.Count))." }
    $sampleIndex = $Sample - 1
} else {
    $sel = Read-Choice -Prompt 'Pick a sample number (q to quit)' -Min 1 -Max $samples.Count
    if ($null -eq $sel) { return }
    $sampleIndex = $sel - 1
}

$sampleDir = $samples[$sampleIndex]

# Find the file(s) with main() in the chosen sample dir.
$mains = @(Get-ChildItem -LiteralPath $sampleDir -Filter *.cpp | Where-Object { Test-HasMain -Path $_.FullName })
if ($mains.Count -eq 0) {
    Write-Host "No file with an (uncommented) main() in this sample - it may be a header-only or fragment sample." -ForegroundColor Yellow
    return
}

$mainFile = $null
if ($mains.Count -eq 1) {
    $mainFile = $mains[0].FullName
} else {
    Write-Host "This sample has several runnable files:" -ForegroundColor Cyan
    for ($i = 0; $i -lt $mains.Count; $i++) {
        Write-Host ("  [{0,2}] {1}" -f ($i + 1), $mains[$i].Name)
    }
    if ($PSBoundParameters.ContainsKey('File')) {
        if ($File -lt 1 -or $File -gt $mains.Count) { throw "File $File out of range (1..$($mains.Count))." }
        $mainFile = $mains[$File - 1].FullName
    } else {
        $sel = Read-Choice -Prompt 'Pick a file number (q to quit)' -Min 1 -Max $mains.Count
        if ($null -eq $sel) { return }
        $mainFile = $mains[$sel - 1].FullName
    }
}

Build-And-Run -MainFile $mainFile -Run:(-not $NoRun)
