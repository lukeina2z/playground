[CmdletBinding()]
param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]] $ComposeArgs
)

$ErrorActionPreference = 'Stop'

if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
    Write-Error "'docker' was not found on PATH. Install Docker Desktop and ensure 'docker' is available in PowerShell."
    exit 127
}

$scriptDir = $PSScriptRoot
$composeFile = Join-Path $scriptDir 'docker-compose-jaeger.yml'

if (-not (Test-Path -LiteralPath $composeFile)) {
    Write-Error "Compose file not found: $composeFile"
    exit 2
}

Push-Location -LiteralPath $scriptDir
try {
    # Equivalent to: docker compose -f ./docker-compose-jaeger.yml up --remove-orphans
    & docker compose -f $composeFile up --remove-orphans @ComposeArgs
    exit $LASTEXITCODE
}
finally {
    Pop-Location
}

docker compose -f 

