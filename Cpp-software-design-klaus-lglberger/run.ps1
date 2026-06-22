<#
.SYNOPSIS
    Interactive build-and-run launcher for the "C++ Software Design" (Klaus
    Iglberger) guideline samples.

.DESCRIPTION
    Pick a guideline, then a sample, and this script compiles it with MSVC
    (C++23 / /std:c++latest) and runs it. Each guideline is one folder; a sample
    is a sub-folder containing a .cpp with main() (or the guideline folder
    itself). The file with main() is compiled together with any sibling .cpp
    files that do NOT contain their own main() (helper translation units). Build
    output goes to a gitignored .build\ folder so the source tree stays clean.

    Requires Visual Studio with the "Desktop development with C++" workload.
    The MSVC environment is bootstrapped automatically via vswhere + vcvars64.

.EXAMPLE
    .\run.ps1                          # fully interactive menu
    .\run.ps1 -Guideline 19            # jump to guideline 19's sample menu
    .\run.ps1 -Guideline 19 -Sample 2  # build+run sample 2 of guideline 19
    .\run.ps1 -List                    # list all guidelines and exit
    .\run.ps1 -Verify                  # compile-check every sample of every guideline
    .\run.ps1 -NoRun -Guideline 19 -Sample 2   # build only, do not run
#>
[CmdletBinding()]
param(
    [int]$Guideline,
    [int]$Sample,
    [int]$File,
    [switch]$List,
    [switch]$NoRun,
    [switch]$Verify
)

$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path

# Guideline number -> title (verbatim from the book).
$GuidelineTitles = @{
    1  = 'Understand the Importance of Software Design'
    2  = 'Design for Change'
    3  = 'Separate Interfaces to Avoid Artificial Coupling'
    4  = 'Design for Testability'
    5  = 'Design for Extension'
    6  = 'Adhere to the Expected Behavior of Abstractions'
    7  = 'Understand the Similarities Between Base Classes and Concepts'
    8  = 'Understand the Semantic Requirements of Overload Sets'
    9  = 'Pay Attention to the Ownership of Abstractions'
    10 = 'Consider Creating an Architectural Document'
    11 = 'Understand the Purpose of Design Patterns'
    12 = 'Beware of Design Pattern Misconceptions'
    13 = 'Design Patterns Are Everywhere'
    14 = 'Use a Design Pattern''s Name to Communicate Intent'
    15 = 'Design for the Addition of Types or Operations'
    16 = 'Use Visitor to Extend Operations'
    17 = 'Consider std::variant for Implementing Visitor'
    18 = 'Beware the Performance of Acyclic Visitor'
    19 = 'Use Strategy to Isolate How Things Are Done'
    20 = 'Favor Composition over Inheritance'
    21 = 'Use Command to Isolate What Things Are Done'
    22 = 'Prefer Value Semantics over Reference Semantics'
    23 = 'Prefer a Value-Based Implementation of Strategy and Command'
    24 = 'Use Adapters to Standardize Interfaces'
    25 = 'Apply Observers as an Abstract Notification Mechanism'
    26 = 'Use CRTP to Introduce Static Type Categories'
    27 = 'Use CRTP for Static Mixin Classes'
    28 = 'Build Bridges to Remove Physical Dependencies'
    29 = 'Be Aware of Bridge Performance Gains and Losses'
    30 = 'Apply Prototype for Abstract Copy Operations'
    31 = 'Use External Polymorphism for Nonintrusive Runtime Polymorphism'
    32 = 'Consider Replacing Inheritance Hierarchies with Type Erasure'
    33 = 'Be Aware of the Optimization Potential of Type Erasure'
    34 = 'Be Aware of the Setup Costs of Owning Type Erasure Wrappers'
    35 = 'Use Decorators to Add Customization Hierarchically'
    36 = 'Understand the Trade-off Between Runtime and Compile Time Abstraction'
    37 = 'Treat Singleton as an Implementation Pattern, Not a Design Pattern'
    38 = 'Design Singletons for Change and Testability'
    39 = 'Continue to Learn About Design Patterns'
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

# Return the guideline directories (Guideline01_..., Guideline02_..., ...) sorted by number.
function Get-Guidelines {
    Get-ChildItem -LiteralPath $root -Directory -Filter 'Guideline*' |
        Where-Object { $_.Name -match '^Guideline(\d+)_' } |
        Sort-Object { [int]($_.Name -replace '^Guideline(\d+)_.*','$1') }
}

function Get-GuidelineNumber { param($Dir) [int]($Dir.Name -replace '^Guideline(\d+)_.*','$1') }

# A "sample" is any leaf directory under a guideline that contains at least one .cpp file.
function Get-Samples {
    param([Parameter(Mandatory)][string]$GuidelinePath)
    Get-ChildItem -LiteralPath $GuidelinePath -Recurse -File -Filter '*.cpp' |
        ForEach-Object { Split-Path $_.FullName -Parent } |
        Select-Object -Unique |
        Sort-Object
}

function Show-Guidelines {
    Write-Host ""
    Write-Host "C++ Software Design (Klaus Iglberger) - Guidelines" -ForegroundColor Cyan
    Write-Host "==================================================" -ForegroundColor Cyan
    foreach ($g in Get-Guidelines) {
        $n = Get-GuidelineNumber $g
        $title = $GuidelineTitles[$n]
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

# Compile every runnable file in a guideline (no run). Returns $true if all pass.
function Verify-Guideline {
    param([Parameter(Mandatory)]$GuidelineDir)
    $n = Get-GuidelineNumber $GuidelineDir
    Write-Host ("`nVerifying Guideline {0:00} - {1}" -f $n, $GuidelineTitles[$n]) -ForegroundColor Cyan
    $pass = 0; $fail = 0; $failed = @()
    foreach ($s in (Get-Samples -GuidelinePath $GuidelineDir.FullName)) {
        $mains = @(Get-ChildItem -LiteralPath $s -Filter *.cpp | Where-Object { Test-HasMain -Path $_.FullName })
        foreach ($m in $mains) {
            $relName = $m.FullName.Substring($GuidelineDir.FullName.Length).TrimStart('\','/')
            if (Invoke-Build -MainFile $m.FullName -Quiet) {
                Write-Host ("  PASS  {0}" -f $relName) -ForegroundColor Green
                $pass++
            } else {
                Write-Host ("  FAIL  {0}" -f $relName) -ForegroundColor Red
                $fail++; $failed += $relName
            }
        }
    }
    Write-Host ("Guideline {0:00}: {1} passed, {2} failed" -f $n, $pass, $fail) -ForegroundColor ($(if ($fail) { 'Yellow' } else { 'Green' }))
    if ($fail) { $failed | ForEach-Object { Write-Host "    - $_" -ForegroundColor Yellow } }
    return ($fail -eq 0)
}

# ------------------------------------------------------------------ main flow
if ($List) { Show-Guidelines; return }

if ($Verify) {
    $targets = if ($PSBoundParameters.ContainsKey('Guideline')) {
        @(Get-Guidelines | Where-Object { (Get-GuidelineNumber $_) -eq $Guideline })
    } else { @(Get-Guidelines) }
    if ($targets.Count -eq 0) { throw "Guideline $Guideline not found." }
    $allOk = $true
    foreach ($t in $targets) { if (-not (Verify-Guideline -GuidelineDir $t)) { $allOk = $false } }
    if (-not $allOk) { exit 1 }
    return
}

# Resolve guideline directory.
$guidelineDir = $null
if ($PSBoundParameters.ContainsKey('Guideline')) {
    $guidelineDir = Get-Guidelines | Where-Object { (Get-GuidelineNumber $_) -eq $Guideline }
    if (-not $guidelineDir) { throw "Guideline $Guideline not found." }
} else {
    Show-Guidelines
    $sel = Read-Choice -Prompt 'Pick a guideline number (q to quit)' -Min 1 -Max 39
    if ($null -eq $sel) { return }
    $guidelineDir = Get-Guidelines | Where-Object { (Get-GuidelineNumber $_) -eq $sel }
    if (-not $guidelineDir) { Write-Host "No such guideline." -ForegroundColor Yellow; return }
}

$n = Get-GuidelineNumber $guidelineDir
Write-Host ""
Write-Host ("Guideline {0:00} - {1}" -f $n, $GuidelineTitles[$n]) -ForegroundColor Cyan

$samples = @(Get-Samples -GuidelinePath $guidelineDir.FullName)
if ($samples.Count -eq 0) { Write-Host "No .cpp samples in this guideline (it may be a README-only conceptual guideline)." -ForegroundColor Yellow; return }

for ($i = 0; $i -lt $samples.Count; $i++) {
    $relName = $samples[$i].Substring($guidelineDir.FullName.Length).TrimStart('\','/')
    if ([string]::IsNullOrEmpty($relName)) { $relName = '(this guideline folder)' }
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
