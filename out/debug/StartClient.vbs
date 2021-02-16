Set WshShell = CreateObject("WScript.Shell")
WScript.Sleep 4000
WshShell.Run chr(34) & "d:\My\TacticsVictoryU3D\out\debug\Client.bat"  & Chr(34), 0
Set WshShell = Nothing