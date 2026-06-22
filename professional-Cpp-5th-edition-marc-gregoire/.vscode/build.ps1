param(
    [Parameter(Mandatory)][string]$ActiveFile,
    [switch]$Run
)

$ErrorActionPreference = 'Stop'

if (-not (Test-Path -LiteralPath $ActiveFile)) {
    throw "Active file not found: $ActiveFile"
}
if ([IO.Path]::GetExtension($ActiveFile).ToLowerInvariant() -ne '.cpp') {
    throw "Active file must be a .cpp file: $ActiveFile"
}

$active = (Resolve-Path -LiteralPath $ActiveFile).Path
$dir    = Split-Path $active -Parent
$base   = [IO.Path]::GetFileNameWithoutExtension($active)
$exe    = "$base.exe"

$mainPattern = '\bint\s+main\s*\('

function Test-HasUncommentedMain {
    param([Parameter(Mandatory)][string]$Path)
    $text = Get-Content -Raw -LiteralPath $Path
    if ([string]::IsNullOrEmpty($text)) { return $false }
    $stripped = [regex]::Replace($text, '/\*[\s\S]*?\*/', '')
    $stripped = [regex]::Replace($stripped, '//[^\r\n]*', '')
    return [bool]([regex]::IsMatch($stripped, $mainPattern))
}

if (-not (Test-HasUncommentedMain -Path $active)) {
    throw "Active file does not contain an uncommented main() - this sample may need its main() uncommented before it can be built."
}

if (-not $env:VSINSTALLDIR) {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
    if (-not (Test-Path $vswhere)) {
        throw "vswhere.exe not found. Install Visual Studio with the 'Desktop development with C++' workload."
    }
    $vsPath = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if (-not $vsPath) {
        throw "No Visual Studio install with VC tools found. Install the 'Desktop development with C++' workload."
    }
    $vcvars = Join-Path $vsPath 'VC\Auxiliary\Build\vcvars64.bat'
    if (-not (Test-Path $vcvars)) {
        throw "vcvars64.bat not found at $vcvars"
    }

    Write-Host "Initializing MSVC environment from $vsPath ..."
    $envDump = cmd /c "`"$vcvars`" >nul && set"
    foreach ($line in $envDump) {
        if ($line -match '^(?<k>[^=]+)=(?<v>.*)$') {
            Set-Item -Path "env:$($Matches.k)" -Value $Matches.v
        }
    }
}

$siblings = @()
Get-ChildItem -LiteralPath $dir -Filter *.cpp | ForEach-Object {
    if ($_.FullName -ieq $active) { return }
    if (-not (Test-HasUncommentedMain -Path $_.FullName)) { $siblings += $_.Name }
}

Push-Location $dir
try {
    $inputs = @([IO.Path]::GetFileName($active)) + $siblings
    Write-Host ("Compiling -> {0}" -f $exe)
    Write-Host ("Sources : {0}" -f ($inputs -join ', '))
    & cl /nologo /std:c++latest /EHsc /W4 /utf-8 /MD /Zi /Fe:$exe $inputs
    $clExit = $LASTEXITCODE
    if ($clExit -ne 0) {
        Write-Host ("Build failed with exit code {0}." -f $clExit) -ForegroundColor Red
        exit $clExit
    }
    Write-Host ("Built: {0}\{1}" -f $dir, $exe) -ForegroundColor Green

    if ($Run) {
        Write-Host ("Running {0}..." -f $exe) -ForegroundColor Cyan
        & ".\$exe"
        Write-Host ("`nProgram exited with code {0}." -f $LASTEXITCODE)
    }
} finally {
    Pop-Location
}
