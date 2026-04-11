param(
    [string]$ScreenshotsDirectory = (Join-Path $PSScriptRoot "..\screenshots"),
    [string]$OutputFile = (Join-Path $PSScriptRoot "screenshots.json")
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Convert-ToDisplayText {
    param([string]$Value)

    if ([string]::IsNullOrWhiteSpace($Value)) {
        return "Untitled"
    }

    $parts = @($Value -split "[_-]+" | Where-Object { $_ })
    if ($parts.Count -eq 0) {
        return "Untitled"
    }

    $formatted = foreach ($part in $parts) {
        if ($part -cmatch "^[a-z]+$") {
            (Get-Culture).TextInfo.ToTitleCase($part)
        }
        else {
            $part
        }
    }

    return ($formatted -join " ")
}

function Convert-ToGalleryItem {
    param([System.IO.FileInfo]$File)

    $baseName = $File.BaseName
    $title = Convert-ToDisplayText -Value $baseName
    $caption = "Standalone pattern"
    $capturedAtIso = $null
    $capturedAtDisplay = $null
    $sortTimestamp = -1
    $ruleLabel = $null
    $family = "Pattern"
    $tags = [System.Collections.Generic.List[string]]::new()

    $match = [regex]::Match(
        $baseName,
        "^screenshot_(?<day>\d{1,2})_(?<month>\d{1,2})_(?<year>\d{4})__(?<hour>\d{1,2})_(?<minute>\d{1,2})_(?<second>\d{1,2})__(?<label>.+)$"
    )

    if ($match.Success) {
        $timestamp = Get-Date `
            -Year ([int]$match.Groups["year"].Value) `
            -Month ([int]$match.Groups["month"].Value) `
            -Day ([int]$match.Groups["day"].Value) `
            -Hour ([int]$match.Groups["hour"].Value) `
            -Minute ([int]$match.Groups["minute"].Value) `
            -Second ([int]$match.Groups["second"].Value)

        $capturedAtIso = $timestamp.ToString("s")
        $capturedAtDisplay = $timestamp.ToString("yyyy-MM-dd HH:mm:ss")
        $sortTimestamp = ([System.DateTimeOffset]$timestamp).ToUnixTimeSeconds()

        $label = $match.Groups["label"].Value
        $ruleLabel = $label
        $title = if ($label.StartsWith("rule_")) {
            "Rule " + (Convert-ToDisplayText -Value $label.Substring(5))
        }
        else {
            Convert-ToDisplayText -Value $label
        }

        $family = if ($label -match "_k_(\d+)") {
            "k=$($matches[1])"
        }
        elseif ($label.StartsWith("rule_")) {
            "Rule Study"
        }
        else {
            "Screenshot"
        }

        $caption = if ($capturedAtDisplay) {
            "Captured $capturedAtDisplay"
        }
        else {
            "Captured screenshot"
        }

        [void]$tags.Add("PNG")

        if ($label -match "_s_(\d+)") {
            [void]$tags.Add("s=$($matches[1])")
        }

        if ($label -match "_k_(\d+)") {
            [void]$tags.Add("k=$($matches[1])")
        }

        if ($label.StartsWith("rule_i_")) {
            [void]$tags.Add("Indexed Rule")
        }
        elseif ($label.StartsWith("rule_")) {
            [void]$tags.Add("Rule")
        }
    }
    else {
        [void]$tags.Add("PNG")
    }

    $searchTerms = @(
        $File.Name,
        $baseName,
        $title,
        $caption,
        $capturedAtDisplay,
        $capturedAtIso,
        $ruleLabel,
        $family,
        ($tags -join " ")
    ) | Where-Object { -not [string]::IsNullOrWhiteSpace($_) }

    return [ordered]@{
        file = $File.Name
        title = $title
        caption = $caption
        capturedAtIso = $capturedAtIso
        capturedAtDisplay = $capturedAtDisplay
        sortTimestamp = $sortTimestamp
        ruleLabel = $ruleLabel
        family = $family
        tags = $tags
        searchText = ($searchTerms -join " ")
    }
}

$resolvedScreenshotsDirectory = (Resolve-Path -LiteralPath $ScreenshotsDirectory).Path
$resolvedOutputFile = $ExecutionContext.SessionState.Path.GetUnresolvedProviderPathFromPSPath($OutputFile)
$outputDirectory = Split-Path -Parent $resolvedOutputFile

if (-not (Test-Path -LiteralPath $outputDirectory -PathType Container)) {
    New-Item -ItemType Directory -Path $outputDirectory | Out-Null
}

$items = Get-ChildItem -LiteralPath $resolvedScreenshotsDirectory -Filter *.png -File |
    Sort-Object Name |
    ForEach-Object { Convert-ToGalleryItem -File $_ }

$manifest = [ordered]@{
    generatedAt = (Get-Date).ToUniversalTime().ToString("o")
    itemCount = $items.Count
    items = $items
}

$manifest |
    ConvertTo-Json -Depth 6 |
    Set-Content -LiteralPath $resolvedOutputFile -Encoding UTF8

[pscustomobject]@{
    OutputFile = $resolvedOutputFile
    ItemCount = $items.Count
} | Format-List
