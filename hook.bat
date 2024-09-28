@echo off
start "" "C:\Program Files (x86)\Steam\steamapps\common\Brawlhalla\Brawlhalla.exe" -provider Steam
start /b powershell -command "Start-Process 'C:\Users\Desktop-PC\Documents\Development\BrawhallaLock\brawlhalla-lock.exe'" -windowstyle hidden
exit
