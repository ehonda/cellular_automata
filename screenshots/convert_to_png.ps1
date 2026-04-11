param(
    [string]$SourceDirectory = $PSScriptRoot,
    [string]$OriginalsDirectory = (Join-Path $PSScriptRoot "originals")
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

Add-Type -AssemblyName System.Drawing

if (-not (Test-Path -LiteralPath $SourceDirectory -PathType Container)) {
    throw "Source directory '$SourceDirectory' does not exist."
}

if (-not (Test-Path -LiteralPath $OriginalsDirectory -PathType Container)) {
    New-Item -ItemType Directory -Path $OriginalsDirectory | Out-Null
}

$bmpFiles = Get-ChildItem -LiteralPath $SourceDirectory -Filter *.bmp -File | Sort-Object Name

foreach ($bmpFile in $bmpFiles) {
    $pngPath = Join-Path $SourceDirectory ($bmpFile.BaseName + ".png")
    $archivedBmpPath = Join-Path $OriginalsDirectory $bmpFile.Name

    if (Test-Path -LiteralPath $archivedBmpPath) {
        throw "Refusing to overwrite existing archived BMP '$archivedBmpPath'."
    }

    $bitmap = [System.Drawing.Bitmap]::new($bmpFile.FullName)

    try {
        $bitmap.Save($pngPath, [System.Drawing.Imaging.ImageFormat]::Png)
    }
    finally {
        $bitmap.Dispose()
    }

    Move-Item -LiteralPath $bmpFile.FullName -Destination $archivedBmpPath
}

$summary = [pscustomobject]@{
    ConvertedBmpCount = $bmpFiles.Count
    PngDirectory = $SourceDirectory
    OriginalsDirectory = $OriginalsDirectory
}

$summary | Format-List
