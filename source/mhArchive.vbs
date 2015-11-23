'$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
'								MH Project Archive
'
'working on Acrobat X Pro 
'	Version 10.1.5
'Microsoft Excel
'	2007
'$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$						
Dim strFilePath
Dim strOutFile
Dim strDefectPath
Dim intLeftBin
Dim intRightBin
Dim moveDiscPath
Dim quote
Dim projectNumber
Dim strFile

Set objShell = WScript.CreateObject("WScript.Shell")

'Initializing
strFile = "C:\ArchiveMH\source\mh_contracts.xls"
quote = chr(34)
moveDiscPath = "C:\ArchiveMH\Source\move_disc\move_disc.exe"
strFilePath = "C:\ArchiveMH"
strFile = "C:\ArchiveMH\0.jpg"
strDefectPath = "C:\ArchiveMH\Defect"
strDefectFile = "C:\ArchiveMH\Defect\0.jpg"
intLeftBin = inputBox("How many discs in LEFT bin?")
intRightBin = inputBox("how about the RIGHT bin?")

For i = 1 to intLeftBin
	objShell.Run "cmd /c " & quote & moveDiscPath & quote & quote & " load left" & quote, 1, true
	'Window_Onload
	'sub_Take_Picture
	'downloadOne(0)
	'sub_OCR
	sub_RipDisc
Next

For i = 1 to intRightBin
	objShell.Run "cmd /c " & quote & moveDiscPath & quote & quote & " load right" & quote, 1, true
	'Window_Onload
	'sub_Take_Picture
	'downloadOne(0)
	'sub_OCR
	sub_RipDisc
Next

'********************************************************************************************************
'Acrobat OCR
'********************************************************************************************************
sub sub_OCR
	Dim App
	Dim AVDoc
	Dim PDDoc
	Dim JSO
	Dim pdfPage
	Dim PageHL
	Dim PageHLRes
	Dim PageSel
	Dim startTime
	Dim endTime

	Dim fileSys
	Set fileSys = CreateObject("Scripting.FileSystemObject")

	Set App = CreateObject("AcroExch.App")
	Set AVDoc = CreateObject("AcroExch.AVDoc")
	App.Hide

													
	if not fileSys.FileExists(strFile) then
		startTime = Timer 								'File hasn't showed up from camera - starting timer
		Do while (Timer - startTime = 10) 				'Doing for 10 seconds
			if fileSys.FileExists(strFile) then 		'if file is here, quit loop
				exit do 
			end if
		Loop 								
		if not fileSys.FileExists(strFile) then   		'checking for file one more time
			msgBox "Line 46: " & strFile & " has not shown up yet for some reason" 	'erroring out if necessary
		end if 
	end if

	AVDoc.Open strFile, "NewTitle"
	'AVDoc.BringToFront()
	Set AVDoc = App.GetActiveDoc()
	Set PDDoc = AVDoc.GetPDDoc()														  'Get's COM object
	Set JSO = PDDoc.GetJSObject												'Accessing Javascript interface

	JSO.app.execMenuItem("ADBE:BasicPluginMenu")

	Set PdfPage = PDDoc.AcquirePage(0) 															'page number
	Set PageHL = CreateObject("AcroExch.HiliteList")
	PageHLRes = PageHL.Add(0,9000) 																'start, end
	Set PageSel = PdfPage.CreatePageHilite(PageHL)

	if PageSel is Nothing then 													'pdf hilite string was empty
		msgbox "from sub_OCR: OCR didn't find any words in picture"		 		
		if fileSys.FileExists(strDefectFile) then 			 					'if something in defect		
			fileSys.DeleteFile strDefectFile 									'delete defect
		end if 
		JSO.saveAs(strDefectFile) 					   'save in defect to avoid saving prompt when closing pdf
		JSO.closeDoc 															'closing pdf
		JSO.app.execMenuItem("Close") 											'closing pdf
		fileSys.DeleteFile strDefectFile 										'delete defect file
		fileSys.MoveFile strFile, strDefectPath 								'saving strFile in defect
	end if

	for i = 0 to PageSel.Getnumtext - 1
		pdfData = PDFData & PageSel.GetText(i)
	Next

	Call sub_Query_Database(pdfData)															'Calling Query
	JSO.saveAs(strOutFile)																		'saving pdf

	JSO.closeDoc
	JSO.app.execMenuItem("Close")

	if fileSys.FileExists(strFile) then
		fileSys.DeleteFile strFile
	else
		msgbox "Line 62: " & strFile & " Could not delete for some reason"
	end if

end sub

'********************************************************************************************************
'Querying Database
'********************************************************************************************************
sub sub_Query_Database(sPdfData)
	Dim strComputer
	Dim strExcel
	Dim objExcel
	Dim objWB
	Dim objSheet
	Dim iCol
	Dim iRow
	Dim iLastRow
	Dim objRegExpr
	Dim aCounter
	Dim extraZero
	Dim sProjectName

	strComputer = "."
	strExcel = UCase(strFile)
	Set objExcel = CreateObject("Excel.Application")
	
	'refresh database
	objExcel.Visible = False
	objExcel.Application.DisplayAlerts = false
	Set objWB = objExcel.Workbooks.Open(strExcel)
	Set objSheet = objWB.Sheets(1)

	iCol = "F"																	'To hold starting column
    iRow = 10																		'To hold starting row
   	iLastRow = objSheet.UsedRange.Rows.Count

   	'ReDim Preserve arrayOfProjects(iLastRow)
	Set objRegExpr = New RegExp
	objRegExpr.Multiline = True

    Do
    	if len(objExcel.Cells(iRow, iCol).Value) > 3 then		'Checking to see if current cell is populated
    		aCounter = 0
    		arrayOfSplit = split(objExcel.Cells(iRow, iCol).Value,".")					'splitting cell at '.'
    		
    		for each x in arrayOfSplit
    			aCounter = aCounter + 1
    		next

    		if aCounter > 1 then
    			if Left(arrayOfSplit(0), 1) = 0 then 								'if there is an extra zero
    				extraZero = Right(arrayOfSplit(0), len(arrayOfSplit(0))-1) 		'strip the extra zero
					objRegExpr.Pattern = extraZero & "\." & arrayOfSplit(1)			'setting regexp pattern
					sProjectName = extraZero & "." & arrayOfSplit(1)				'saving the proj number
				else
					objRegExpr.Pattern = arrayOfSplit(0) & "\." & arrayOfSplit(1)	'set regexp pattern
					sProjectName = arrayOfSplit(0) & "." & arrayOfSplit(1)			'saving the proj number
				end if
			end if
    	End If
    	iRow = iRow + 1 															'Incrementing row anyways
    Loop Until (objRegExpr.Test(sPdfData)) Or (iRow = iLastRow)						'Looping until last row
    																				'Or passes test

	if objRegExpr.Test(sPdfData) then
		msgBox "Test completely passed " & sProjectName
		projectNumber = sProjectName
		Call sub_Create_Folder_Structure(sProjectName)
	else
		msgBox "Not found... " & sProjectName
	end if

	objWB.Close True
	objExcel.Quit

end sub	

'********************************************************************************************************
'Creating Folder Structure
'********************************************************************************************************
sub sub_Create_Folder_Structure(sProjectName)
	Dim fileSys
	Dim newFolder
	Dim newFolderPath

	newFolderPath = "C:\ArchiveMH\Archive\" & sProjectName
	set fileSys = CreateObject("Scripting.FileSystemObject")
	If Not fileSys.FolderExists(newFolderPath) then
		Set newFolder = fileSys.CreateFolder(newFolderPath)
	End If

	strOutFile = newFolderPath & "\cover.pdf"
end sub

'********************************************************************************************************
'Window OnLoad
'********************************************************************************************************
'global defs for camera

Const wiaCommandTakePicture = "{AF933CAC-ACAD-11D2-A093-00C04F72DC3C}"
Const wiaCommandSynchronize = "{9B26B7B2-ACAD-11D2-A093-00C04F72DC3C}"
Const wiaCameraDeviceType = 2
Const tickSize = 500

Const HKEY_LOCAL_MACHINE = &H80000002
Const HKEY_CURRENT_USER  = &H80000001
const REG_SZ = 1
const REG_EXPAND_SZ = 2
const REG_BINARY = 3
const REG_DWORD = 4
const REG_MULTI_SZ = 7

Dim outputfolder
Dim DevMan
Dim dlg
Dim dev 'As WIA.Device
dim okB ' as integer
dim ynB ' as integer
dim devInited '
Dim ContinuousTether
dim WshShell , fso
dim afile
dim colEnvVars 
Dim tempfolder, foldername
Dim DevicesConnectedCount

Dim timerID

Dim imgFormat

Dim highestDownloadedItemNumber

Dim tickno, Pushtick	
dim TimelapseActive 
dim nextTimeLapseShot
Dim TimeLapseShots
Dim mostRecentJPGFileName

Dim FullScreenPreviewWindow
Dim FullScreenPreviewVisible
Dim FullScreenPreviewDIV


'Dim cbDownloadImmediatelySaved

Dim dicShutterTable
Dim dicWBTable

Dim arExpCompTable(31) ' no idea the maximum but 5 stops each direction in thirds seems reasonable
Dim arShutterTable(106) ' max is 53 on the D40 so I'm going for double to be safe

Dim BlockTether

' Camera Capabilities
Dim ExposureModeAdjustable
Dim ExposureTimeSubtypesValues
Dim ExposureISOSubtypeValues

Dim currentPreview

'Subs start here

Sub Window_Onload

	Dim elm
	Dim Cameras 
	Dim LatestCameraID
	Dim fldstr
	Dim objreg
	Dim savedpreviewsize, savedpushexternalviewer

	FullScreenPreviewVisible = False

    devInited = 0
    Cameras = 0 
	LatestCameraID = ""
	imgFormat = "jpg"
	ContinuousTether = 0
	highestDownloadedItemNumber = 0 
	tickno = 1
	Pushtick = -10
	BlockTether = False
	currentPreview = ""
	
	' read from the registry the previous raw/jpg setting and defalut to jpg if there is no setting saved
	imgformat = RegistryGetSetting("imgformat")
	if imgformat ="" Then
		imgFormat = "jpg"
		registrysavesetting "imgformat", imgformat
	end If
	If devInited = 1 Then
		if imgformat = "jpg" then
			setjpg
		end if
		if imgformat = "raw" then
			setraw
		end If
	End If

	StopTimeLapse
		
	Set dicShutterTable = CreateObject("Scripting.Dictionary") 
	dicShutterTable.add 1,"6400"
	dicShutterTable.add 2,"4000"
	dicShutterTable.add 3,"3200"
	dicShutterTable.add 4,"2500"
	dicShutterTable.add 5,"2000"
	dicShutterTable.add 6,"1600"
	dicShutterTable.add 8,"1250"
	dicShutterTable.add 10,"1000"
	dicShutterTable.add 12,"800"
	dicShutterTable.add 15,"640"
	dicShutterTable.add 20,"500"
	dicShutterTable.add 25,"400"
	dicShutterTable.add 31,"320"
	dicShutterTable.add 40,"250"
	dicShutterTable.add 50,"200"
	dicShutterTable.add 62,"160"
	dicShutterTable.add 80,"125"
	dicShutterTable.add 100,"100"
	dicShutterTable.add 125,"80"
	dicShutterTable.add 166,"60"
	dicShutterTable.add 200,"50"
	dicShutterTable.add 250,"40"
	dicShutterTable.add 333,"30"
	dicShutterTable.add 400,"25"
	dicShutterTable.add 500,"20"
	dicShutterTable.add 666,"15"
	dicShutterTable.add 769,"13"
	dicShutterTable.add 1000,"10"
	dicShutterTable.add 1250,"8"
	dicShutterTable.add 1666,"6"
	dicShutterTable.add 2000,"5"
	dicShutterTable.add 2500,"4"
	dicShutterTable.add 3333,"3"
	dicShutterTable.add 4000,"2.5"
	dicShutterTable.add 5000,"2"
	dicShutterTable.add 6250,"1.6"
	dicShutterTable.add 7692,"1.3"
	dicShutterTable.add 10000,"1s"
	dicShutterTable.add 13000,"1.3s"
	dicShutterTable.add 16000,"1.6s"
	dicShutterTable.add 20000,"2s"
	dicShutterTable.add 25000,"2.5s"
	dicShutterTable.add 30000,"3s"
	dicShutterTable.add 40000,"4s"
	dicShutterTable.add 50000,"5s"
	dicShutterTable.add 60000,"6s"
	dicShutterTable.add 80000,"8s"
	dicShutterTable.add 100000,"10s"
	dicShutterTable.add 130000,"13s"
	dicShutterTable.add 150000,"15s"
	dicShutterTable.add 200000,"20s"
	dicShutterTable.add 250000,"25s"
	dicShutterTable.add 300000,"30s"	

	
	Set dicWBTable = CreateObject("Scripting.Dictionary") 
	dicWBTable.Add 2, "Auto"
	dicWBTable.Add 4, "Daylight"
	dicWBTable.Add 5, "Fluorescent "
	dicWBTable.Add 6, "Incandescent"
	dicWBTable.Add 7, "Flash"
	dicWBTable.Add 32784, "Cloudy"
	dicWBTable.Add 32785, "Shade"
	dicWBTable.Add 32786, "Kelvin"
	dicWBTable.Add 32787, "Custom"
	
    Set DevMan = CreateObject("WIA.DeviceManager")

    DevicesConnectedCount = DevMan.deviceinfos.count
    For Each elm In DevMan.deviceinfos 
    	If elm.type = wiaCameraDeviceType Then
    		Cameras = Cameras + 1
    		LatestCameraID = elm.DeviceID
    	End If
    Next
    'MsgBox cameras
    If Cameras = 1 Then
	    For Each elm In DevMan.deviceinfos 
	    	If elm.DeviceID = LatestCameraID Then
				Set dev = elm.connect
				DeviceSelected
	    	End If
	    Next    
    
    End If 
    
    Set dlg  = CreateObject("WIA.CommonDialog")
    
 	Set WshShell = CreateObject("WScript.Shell")
	Set colEnvVars = WshShell.Environment("User")
	tempfolder = WshShell.ExpandEnvironmentStrings("%TEMP%")
	
	Set fso= CreateObject("Scripting.FileSystemObject")   


	'outputfolder = RegistryGetSetting("outputfolder")
	outputfolder = strFilePath
	If outputfolder = "" Then
		Set objReg = GetObject("winmgmts:\\localhost\root\default:StdRegProv")
		objReg.GetStringValue &H80000001, "Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders", "My Pictures", outputfolder
		
		outputfolder  = outputfolder + "\"
	
		foldername = Left(outputfolder,Len(outputfolder)-1)
		foldername = Mid(foldername, 1+InStrRev(foldername,"\")) 
		
		If not fso.FolderExists(outputfolder) Then
		   fso.CreateFolder(outputfolder )
		End If

		RegistrySaveSetting "outputfolder", outputfolder 
	End If

	' this value is used for the push external viewer to identify which window to send keystrokes to
	foldername = Left(outputfolder,Len(outputfolder)-1)
	foldername = Mid(foldername, 1+InStrRev(foldername,"\")) 

	savedpreviewsize = RegistryGetSetting("previewsize")
	If savedpreviewsize = "" Then
		' MsgBox "No value for preview size, setting 10%"
		savedpreviewsize = "10%"	
		
	End If

	savedpushexternalviewer = RegistryGetSetting("pushexternalviewer")
	If savedpushexternalviewer = "" Then
		savedpushexternalviewer = "off"
	End If

	registrySaveSetting "pushexternalviewer", savedpushexternalviewer

	If RegistryGetSetting("tethering") = "on" Then
		StartContinuousTether		
		If devInited = 0 Then 
			'btStartContinuousTether.disabled = True
			'btStopContinuousTether.disabled = False
		End If
	Else		
		StopContinuousTether
	End If

	'timerID = window.setInterval("tickProcess", tickSize)
	
End Sub

'********************************************************************************************************
'Registry Save Setting
'********************************************************************************************************

Sub registrySaveSetting(SettingName,SettingValue)
Dim objReg
Dim OurKeyExists
Dim arrSubKeys
Dim objSubKey
 
	'MsgBox "Save " + SettingName + SettingValue
	Set objReg=GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\default:StdRegProv")
	objReg.EnumKey HKEY_CURRENT_USER, "Software", arrSubKeys
	OurKeyExists = False
	
	For Each objSubKey In arrSubKeys
	   If objSubKey = "DIYPhotobits.com" Then
	      OurKeyExists = True
	      Exit For	   
	   End If
	Next
	
	If Not OurKeyExists Then
		objReg.CreateKey HKEY_CURRENT_USER, "Software\DIYPhotobits.com"
	End If	
    
	objReg.SetStringValue HKEY_CURRENT_USER,"Software\DIYPhotobits.com",SettingName,SettingValue 

	
End sub

'********************************************************************************************************
'Registry Get Setting
'********************************************************************************************************

Function RegistryGetSetting(SettingName)
Dim objReg
Dim OurKeyExists
Dim ourValue
Dim arrSubKeys
Dim objSubKey
Dim arrValues
Dim objValue
Dim OurValueExists

	Set objReg=GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\default:StdRegProv")
	objReg.EnumKey HKEY_CURRENT_USER, "Software", arrSubKeys
	OurKeyExists = False
	
	For Each objSubKey In arrSubKeys
	   If objSubKey = "DIYPhotobits.com" Then
	      OurKeyExists = True
	      Exit For	   
	   End If
	Next
	
	If  OurKeyExists Then

		objReg.EnumValues HKEY_CURRENT_USER, "Software\DIYPhotobits.com", arrValues

		OurValueExists = False
		For each objValue In arrValues
			If objValue = SettingName Then
				OurValueExists = True
				Exit For
			End If
		Next	
		
		If OurValueExists Then
			objReg.GetStringValue HKEY_CURRENT_USER,"Software\DIYPhotobits.com",SettingName,ourValue 
			RegistryGetSetting = ourValue		
		Else
			RegistryGetSetting = ""			
		End If		
		
	Else 
		RegistryGetSetting = ""
	End If	

End function

'********************************************************************************************************
'Select Device
'********************************************************************************************************

sub fnSelectDevice
	if devInited = 1 Then
		devInited = 0
	 	Set dev = Nothing
	End If
	On Error Resume Next
	Err.Clear
	Set dev = dlg.ShowSelectDevice( wiaCameraDeviceType)
	If Err.Number = 0 Then
		DeviceSelected
	End If
	On Error Goto 0 
End sub

'********************************************************************************************************
'Device Selected
'********************************************************************************************************

Sub DeviceSelected
	Dim originalMode
	Dim originalDevice
	Dim elm
	Dim i

	devInited = 1
	highestDownloadedItemNumber = dev.Items.Count
	If Not testCollection(dev.Commands, "Take a new picture") Then
	End If

	if imgformat = "jpg" then'
		setjpg
	end if
	if imgformat = "raw" then
		setraw
	end If

	ExposureModeAdjustable = Not dev.properties("Exposure Mode").IsReadOnly
	
	fnRawJpgChange	' not really changed but it forces a push of the required value to the camera depending on the gui state at the moment
	
End Sub

'********************************************************************************************************
'Take Picture
'********************************************************************************************************

Sub sub_Take_Picture
	Dim itemCount
	Dim downloadedfilename
	Dim convertedpath
	Dim WaitTimeout
	Dim ShotsToTake
	Dim CurrentExpoCompOffset
	Dim CurrentExpoComp
	Dim CurrentExposureTimeOffset, CurrentExposureTime
	Dim i

	if devInited = 1 Then

		BlockTether = true
    	
		itemCount = dev.Items.Count

		ShotsToTake = 1

		Err.Clear		
		On Error Resume Next
		Do While ShotsToTake > 0
			dev.ExecuteCommand (wiaCommandTakePicture)
			ShotsToTake = ShotsToTake  - 1
		Loop 
		BlockTether = false
       	
    End if
End Sub

'********************************************************************************************************
'Stop Time Lapse
'********************************************************************************************************

sub StopTimeLapse
	TimelapseActive = false
end sub

'********************************************************************************************************
'Set JPG
'********************************************************************************************************

Sub setJpg
	if devInited = 1 Then
		If testCollection(dev.Properties, "Format") Then
			on error resume next
			on error goto 0
			imgFormat = "jpg"
			registrysavesetting "imgformat", imgformat	
		Else
			MsgBox "This device does not support image formats", vbExclamation  
		End If			
	End If

end sub

'********************************************************************************************************
'FN Raw JPG Change
'********************************************************************************************************

Sub fnRawJpgChange
  	setJpg
End Sub

'********************************************************************************************************
'Test Collection
'********************************************************************************************************

Function testCollection( obj, name)
	Dim elm
	testCollection = False
	For Each elm In obj
		If elm.name =name Then
			testCollection = True
		End If
	Next

End Function

'********************************************************************************************************
'Start Continuous Tether
'********************************************************************************************************

Sub StartContinuousTether
	if devInited = 1 Then
		ContinuousTether = 1
		highestDownloadedItemNumber = dev.Items.Count
	End If 
	registrySaveSetting "tethering", "on"
End Sub

'********************************************************************************************************
'Stop Continuous Tether
'********************************************************************************************************

Sub StopContinuousTether
	ContinuousTether = 0
	registrySaveSetting "tethering", "off"
End Sub

'********************************************************************************************************
'Download One
'********************************************************************************************************

Function downloadOne(itemnumber)
	Dim objOption
	Dim img
	Dim fn, fnext, tempfn, originalfn
	Dim RunReturnCode
	
	fn = ""
	If dev.items.count >= itemnumber Then
		Set img = dlg.ShowTransfer(dev.Items(dev.items.count))
		tempfn = outputfolder & "0" & ".jpg"
		img.SaveFile "C:\ArchiveMH\0.jpg" 
	    img = null
		highestDownloadedItemNumber = itemnumber 			'i'm keeping track of this as I hope to be able to 
															   		  'reconnect if the cable is dropped later
	End If

	downloadOne = fn
End Function

'********************************************************************************************************
'TickProcess
'********************************************************************************************************

Sub tickProcess
	Dim downloadedfilename
	Dim i 
	Dim ret
	
	tickno = tickno + 1
	If DevMan.deviceinfos.count <> DevicesConnectedCount then
		DevicesConnectedCount = DevMan.deviceinfos.count
	End If
	If devInited = 1 Then
		If ContinuousTether = 1 Then
			If Not BlockTether Then 
				While 	highestDownloadedItemNumber < dev.Items.Count
					downloadedfilename = downloadOne(highestDownloadedItemNumber + 1)
				Wend	
			End If
		End If	
	
		If tickno = Pushtick Then
			ret = WshShell.AppActivate( foldername, 1000 )
			If ret = False then
				' no such window or window is busy so don't try to send keys
				Pushtick = 0
			End If
		End If
		If tickno = Pushtick+1 Then
			'MsgBox "right"
			WshShell.SendKeys "{RIGHT}"	
		End If
		If tickno = Pushtick+2 Then
			'MsgBox "end"
			WshShell.SendKeys "{END}"
			Pushtick = -1
		End If
	End If ' devInited = 1 
		
End Sub

'********************************************************************************************************
'Rip CD
'********************************************************************************************************
'sub sub_RipDisc

'	Dim jrqMaster
'	Dim jrqPool
'	Dim fileSys
'
'	jrqMaster = "C:\Archive\JRQ\jrqmaster.jrq"
'	jrqPool = "C:\Archive\JRQ\Pool"
'		
'	Set fileSys = CreateObject("Scripting.FileSystemObject")
'
'	fileSys.CopyFile jrqMaster, jrqPool 	
'
'	if not fileSys.FileExists(jrqPool & "\done.jrq") then
'		startTime = Timer 								'File hasn't showed 'up from camera - starting timer
'		Do while (Timer - startTime = 200) 				'Doing for 200 seconds
'			if fileSys.FileExists(jrqPool & "\done.jrq") then 		'if file is here, quit loop
'				exit do 
'			end if
'		Loop 								
'		if not fileSys.FileExists(jrqPool & "\done.jrq") then   		'checking for file one more 'time
'			msgBox "Error: " & jrqPool & "\done.jrq" & 
'			" the CD data ripping is taking forever?" 	'erroring out if necessary
'		end if 
'	end if
'
'end sub

sub sub_RipDisc
	Set objShell = WScript.CreateObject("WScript.Shell")
	dim projectNumber
	projectNumber = 00102.03

	dim path
	path = "C:\ArchiveMH\Source\move_disc.exe"
	arg = " rip" & " C:\ArchiveMH\Archive\" & projectNumber & "\0"

	strArgument = "cmd /c " & quote & moveDiscPath & quote & quote & arg & quote
	'objShell.Run "cmd /c " & quote & moveDiscPath & quote & quote & " " & quote, 1, true
	objShell.Run strArgument, 1, true
end sub

'********************************************************************************************************
'Exiting Program Unexpectedly
'********************************************************************************************************


'Dunno what this does but it works too, if 'theScript' is set
'Set AForm = CreateObject("AFormAut.App")
'AForm.Fields.ExecuteThisJavaScript theScript
	