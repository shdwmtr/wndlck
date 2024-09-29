# Set the path to the Steam game executable, this example is for Brawlhalla
$gamePath = "C:\Program Files (x86)\Steam\steamapps\common\Brawlhalla\Brawlhalla.exe"
$gamePathParent = $gamePath | Split-Path -Parent

Set-Location $gamePathParent
Start-Process $gamePath -ArgumentList "-provider Steam"
# Get absolute path of the current script
$startScriptLocation = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent

# Start wndlck in the same directory as the script
Set-Location $startScriptLocation
Start-Process "$startScriptLocation/wndlck.exe" -NoNewWindow