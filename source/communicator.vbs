Set objShell = WScript.CreateObject("WScript.Shell")

dim quote
dim answer
quote = chr(34)
dim strArgument
dim path
dim arg

path = "C:\ArchiveMH\Source\move_disc.exe"
arg = " 1"

strArgument = "cmd /c " & quote & path & quote & quote & arg & quote

objShell.Run strArgument, 1, true

'msgBox "First one done"

arg = " 2"

objShell.Run strArgument, 1, true

'msgBox "Second one done"
'WScript.Sleep 250

'Set fso = CreateObject("Scripting.FileSystemObject")
'Set file = fso.OpenTextFile("C:\temptest.txt",1)
'text = file.ReadAll
'file.Close
'Shell.AppActivate "RemoteControlShell"
'WScript.Sleep 250

'answer = Shell.SendKeys quote & "C:\Google Drive\Projects\CD Loader\ptrobot\testCompile\vs\move_disc\Debug\move_disc.exe 2" & quote & "{ENTER}"
'WScript.Sleep 250

'msgBox text