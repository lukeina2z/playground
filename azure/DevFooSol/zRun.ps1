[CmdletBinding()]
param(
    [switch]$ResetSecret
)

$projectPath = Join-Path $PSScriptRoot "FirstADWebApp\FirstADWebApp.csproj"
$storedSecrets = dotnet user-secrets list --project $projectPath
$clientSecretEntry = $storedSecrets |
    Where-Object { $_ -match '^AzureAd:ClientSecret\s*=' } |
    Select-Object -First 1
$hasClientSecret = $null -ne $clientSecretEntry -and
    -not [string]::IsNullOrWhiteSpace($clientSecretEntry.Substring($clientSecretEntry.IndexOf('=') + 1))

if ($ResetSecret -or -not $hasClientSecret) {
    do {
        $secret = Read-Host "Paste the client secret VALUE" -AsSecureString
        $plainSecret = [System.Net.NetworkCredential]::new("", $secret).Password

        if ([string]::IsNullOrWhiteSpace($plainSecret)) {
            Write-Warning "The client secret cannot be empty. Paste the secret VALUE, then press Enter."
        }
    } while ([string]::IsNullOrWhiteSpace($plainSecret))

    dotnet user-secrets set "AzureAd:ClientSecret" $plainSecret --project $projectPath

    Remove-Variable secret, plainSecret
}

dotnet run --project $projectPath --launch-profile https

