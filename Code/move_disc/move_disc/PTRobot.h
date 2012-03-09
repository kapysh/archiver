/////////////////////////////////////////////////////////////////////////////
//																		   //
//					PTRobot API Definition	  							   //
//																		   //
//	   PTRobot is an API to allow third parties to integrate     		   //
//	   Primera disc publishing systems into their application.			   //
//																		   //																   
//																		   //
// Copyright (C) 2005-6 Primera Technology Inc.							   //
//																		   //
/////////////////////////////////////////////////////////////////////////////


// NOTE:  See end of this file for pseudo-code example usage of the PTRobot API


///////////////////////////////////////////////////////////////////
//
//    PTRobot Definitions
//
///////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#pragma once

//////////////////////////////////////////////////
//
//	Return Values from PTRobot_xxxx API functions
//
///////////////////////////////////////////////////
#define PTROBOT_OK							0
#define PTROBOT_INTERNAL					500
#define PTROBOT_SEQUENCE					501
#define PTROBOT_INVALID_ROBOT				502
#define PTROBOT_INVALID_DRIVE				503
#define PTROBOT_INVALID_BIN					504
#define PTROBOT_NODRIVES					505
#define PTROBOT_OPENCLOSE_FAILED			506
#define PTROBOT_OVERFLOW					507
#define PTROBOT_NO_PRINTER					508
#define PTROBOT_PRINTFILE_INVALID			509
#define PTROBOT_PRINTAPP_NOT_INSTALLED	  	510
#define PTROBOT_PRINTFILE_NOT_FOUND			511
#define PTROBOT_PRN_INVALID					512
#define PTROBOT_UNSUPPORTED_OPTION			513
#define PTROBOT_DIRNOTFOUND					514
#define PTROBOT_INVALID_LOCATION			515
#define PTROBOT_MULTDRIVES					516
#define PTROBOT_INVALID_PRINTER_SETTINGS	517
#define PTROBOT_INVALID_DRIVE_POSITION		518
#define PTROBOT_INVALID_ACTION				519
#define PTROBOT_FEATURE_NOT_IMPLEMENTED		520
#define PTROBOT_PRINTAPP_OPEN				521
#define PTROBOT_MISSING_DLL					522
#define PTROBOT_DRIVE_NOT_READY				523
#define PTROBOT_INVALID_MEDIA				524
#define PTROBOT_NO_MEDIA					525
#define PTROBOT_INVALID_LANG				526
#define PTROBOT_INVALID_ERROR				527
#define PTROBOT_BUSY						528
#define PTROBOT_INVALID_EXTENSION			529

///////////////////////////
//
//	System Errors
//  (used by PTRobotStatus.dwSystemError)
//
///////////////////////////
#define SYSERR_NONE							0
#define SYSERR_PTR_TRAY						1
#define SYSERR_CART_CODE					2
#define SYSERR_INPUT_EMPTY					3
#define SYSERR_PTR_COMM						4
#define SYSERR_CLR_EMPTY					5
#define SYSERR_BLK_EMPTY					6
#define SYSERR_BOTH_EMPTY					7
#define SYSERR_PICK							8
#define SYSERR_ARM_MOVE						9
#define SYSERR_CART_MOVE					10
// 11 not used
#define SYSERR_INTERNAL_SW					12
#define SYSERR_NO_ROBODRIVES				13
#define SYSERR_OFFLINE						14
#define SYSERR_COVER_OPEN					15
#define SYSERR_PRINTER_PICK					16
#define SYSERR_MULTIPLE_PICK				17		
#define SYSERR_MULTIPLEDISCS_IN_PRINTER		18
#define SYSERR_MULTIPLEDISCS_IN_RECORDER	19
#define SYSERR_DROPPED_DISC_RECORDER		20 
#define SYSERR_DROPPED_DISC_BIN1			28 
#define SYSERR_DROPPED_DISC_BIN2			29
#define SYSERR_DROPPED_DISC_BIN3			30
#define SYSERR_DROPPED_DISC_BIN4			31
#define SYSERR_DROPPED_DISC_BIN5			32
#define SYSERR_DROPPED_DISC_PRINTER			33 
#define SYSERR_DROPPED_DISC_REJECT			34 
#define SYSERR_DROPPED_DISC_UNKNOWN			35 
#define SYSERR_ALIGNNEEDED					36
#define SYSERR_COLOR_INVALID				37
#define SYSERR_BLACK_INVALID				38
#define SYSERR_BOTH_INVALID					39
#define SYSERR_NOCARTS						40
#define SYSERR_K_IN_CMY						41
#define SYSERR_CMY_IN_K						42
#define SYSERR_SWAPPED						43
#define SYSERR_PIGONPRO						44
#define SYSERR_ALIGNFAILED					45
#define SYSERR_DROPPED_DISC_PRINTER_FATAL	46
#define SYSERR_MULTIPLEDISCS_IN_RIGHTBIN	47
#define SYSERR_MULTIPLEDISCS_IN_LEFTBIN		48
#define SYSERR_CLR_EMPTY_FINAL				49
#define SYSERR_BLK_EMPTY_FINAL				50
#define SYSERR_BOTH_EMPTY_FINAL				51
#define SYSERR_WAITING_FOR_PRINTER			52
#define SYSERR_NO_DISC_IN_PRINTER			53	
#define SYSERR_BUSY							54
#define SYSERR_PURGE						55
#define SYSERR_DOCK_SENSOR					56
#define SYSERR_ALREADY_PRINTED				57
#define SYSERR_UNKNOWN_HARDWARE				58


///////////////////////////
//
//  System State
//  (used by PTRobotStatus.dwSystemState)
//
//////////////////////////
#define SYSSTATE_IDLE		0
#define SYSSTATE_BUSY		1
#define SYSSTATE_ERROR		2 

///////////////////////////
//
//	Robot Type
//
///////////////////////////
#define ROBOT_DISCPUBLISHER				0
#define ROBOT_DISCPUBLISHERII			1
#define ROBOT_DISCPUBLISHERPRO			2
#define ROBOT_COMPOSERMAX				3
#define ROBOT_RACKMOUNT_DPII			4
#define ROBOT_DISCPUBLISHER_XRP			5
#define ROBOT_DISCPUBLISHER_SE			6
#define ROBOT_DISCPUBLISHERPRO_XI		7
#define ROBOT_DISCPUBLISHER_4100		8
#define ROBOT_DISCPUBLISHER_4100_XRP	9
#define ROBOT_DISCPUBLISHER_4051		10


///////////////////////////
//
//	Bin Auto Use
//
///////////////////////////
#define BIN_INPUT					0
#define BIN_OUTPUT					1

///////////////////////////
//
//	Robot Options
//
///////////////////////////
#define PTOPT_KIOSKMODE 		0x00000001



///////////////////////////
//
//	Robot Actions
//
///////////////////////////
#define PTACT_ALIGNPRINTER 			0x00000001	 
#define PTACT_IGNOREINKLOW			0x00000002
#define PTACT_DISABLEPWRBUTTON		0x00000004
#define PTACT_REINIT_DRIVES			0x00000008
#define PTACT_IDENTIFY				0x00000010
#define PTACT_CANCELCMD				0x00000020
#define PTACT_ENABLEPWRBUTTON		0x00000040
#define PTACT_RESETSYSTEM			0x00000080
#define PTACT_CHECKDISCS			0x00000100		// Check the number of discs in the bins
#define PTACT_CLEANCARTRIDGES		0x00000200		// Clean the cartridges
#define PTACT_CALIBRATE_ONE_DISC	0x00000400		// SE, II, Pro:  Calibrate for one disc (user must put one disc in each bin).
#define PTACT_CHANGE_CARTRIDGE		0x00000800		// SE, II, Pro:  Start the cartridge change procedure
#define PTACT_END_CARTRIDGE_CHANGE	0x00001000		// SE:			 End the cartridge change (can close lid also)
#define PTACT_SHIP_POSITION			0x00002000		// SE, II, Pro:  Move the picker to the shipping position
#define PTACT_RESET_LEFT_INK_LEVELS	0x00004000		// II:			 Clears the ink spits for the LEFT cartridge
#define PTACT_RESET_RIGHT_INK_LEVELS 0x00008000		// II:			 Clears the ink spits for the RIGHT cartridge
#define PTACT_ALLOW_NO_CARTRIDGES	0x00010000		// SE, II, Pro:	 Allows unit to operate non-printing robotics without a cartridge
#define PTACT_XI_LIGHT_OFF        	0x00020000
#define PTACT_XI_LIGHT_ON        	0x00040000
#define PTACT_XI_LIGHT_FLASH       	0x00080000
#define PTACT_UNHOOK_PICKER			0x00100000
#define	PTACT_AUTOPRINTER_MODE		0x00200000		// DP4100: can perform a faster multiple copy print-only job by calling PTRobot_SetPrintCopies()
													// prior to calling the print function (e.g. PTRobot_PrintFile()).  
#define	PTACT_FAN_ON				0x00400000		// DP4100: turn on system fan
#define	PTACT_FAN_OFF				0x00800000		// DP4100: turn off system fan


///////////////////////////
//
//	Print Quality 
//
///////////////////////////
#define PQ_LOW 		0
#define PQ_MED 		1
#define PQ_BETTER	2
#define PQ_HIGH		3
#define PQ_BEST		4

///////////////////////////
//
//	Drive Open/Close 
//
///////////////////////////
#define DRIVE_OPEN 		0
#define DRIVE_CLOSE		1


///////////////////////////
//
//	Locations 
//
///////////////////////////
#define LOCATION_AUTO		0
#define LOCATION_PRINTER	100
#define LOCATION_REJECT		200

///////////////////////////
//
//	Drive Bus Types
//
///////////////////////////
#define BUSTYPE_USB			0
#define BUSTYPE_1394		1

///////////////////////////
//
//	Clear Drive
//
///////////////////////////
#define CLEARDRIVE_NO		0
#define CLEARDRIVE_YES		1


///////////////////////////
//
//  Languages
//
///////////////////////////
#define ENGLISH			0
#define JAPANESE		1
#define	GERMAN			2
#define FRENCH			3
#define SPANISH			4
#define ITALIAN			5
#define CHINESE			6	// Simplified
#define KOREAN			7
#define POLISH			8
#define CHINESE_TRAD	9	// Traditional
#define CZECH			10
#define LAST_LANGUAGE	CZECH


//////////////////////////////
// 
// Printer Tray Status
//
//////////////////////////////
#define PRINT_TRAY_IN_WITH_DISC	'D'
#define	PRINT_TRAY_IN_NO_DISC	'I'
#define PRINT_TRAY_OUT			'O'


////////////////////////////////
//
// Disc Pick Switch Status
//
////////////////////////////////
#define DISC_PICKER_NO_DISC		'X'
#define DISC_PICKER_HAS_DISC	'O'


/////////////////////////////////
// 
// Cartridge Types
//
/////////////////////////////////
#define CARTRIDGE_NONE	0
#define CARTRIDGE_COLOR	1
#define CARTRIDGE_BLACK	2
#define CARTRIDGE_YELLOW 3
#define CARTRIDGE_CYAN 4
#define CARTRIDGE_MAGENTA 5


/////////////////////////////////
// 
// Cartridges Installed
//
/////////////////////////////////
#define CARTRIDGE_INSTALLED_NONE	0
#define CARTRIDGE_INSTALLED_COLOR	1
#define CARTRIDGE_INSTALLED_BLACK	2
#define CARTRIDGE_INSTALLED_COLOR_AND_BLACK 3
#define CARTRIDGE_INSTALLED_COLOR_AND_COLOR 4



///////////////////////////////////////////////////////////////////
//
//    PTRobot Data Structures
//
///////////////////////////////////////////////////////////////////

///////////////////////////
//
//	PTDriveInfo Structure
//
///////////////////////////
typedef struct 
{
	HANDLE hDrive;			 	 //Drive Handle.
	TCHAR tszDriveName[132]; 	 //Drive String (reported from drive)	
	TCHAR tszFirmwareVer[40];	 //Drive FW version
	TCHAR tszSerialNum[40];		 //Drive Serial Number
	HANDLE hRobot;
	DWORD dwDriveColumn;		 //Drive Column (0 based - 0 is leftmost column)
	DWORD dwDriveRow;			 //Drive Row (0 based - 0 is the top row)
}PTDriveInfo, *pPTDriveInfo;

///////////////////////////
//
//	PTRobotInfo Structure
//
///////////////////////////
#define MAX_ROBOT_DRIVES 10
typedef struct 
{
   	HANDLE hRobot;				//Robot Handle
	TCHAR tszRobotDesc[100]; 	//Robot	Description
	DWORD dwRobotType;			//See "Robot Type" section above
	DWORD dwNumDrives;			//Number of Recorders on this robot
	DWORD dwNumPrinters;		//Number of Printers on this robot (0 or 1)
	DWORD dwNumBins;			//Number of Bins on this robot
	DWORD dwDriveColumns;		//Number of Drive Columns
	DWORD dwDriveRows;			//Number of Drive Rows
	TCHAR tszRobotFirmware[20];	//String Containing the FW Version of the Robot
	DWORD dwSupportedOptions;	//See "Robot Options" section above
	DWORD dwSupportedActions;	//See "Robot Actions" section above
	HANDLE hDrives[MAX_ROBOT_DRIVES];
	DWORD dwDriveBusType;		//BusType of the Drives
}PTRobotInfo, *pPTRobotInfo;


///////////////////////////
//
//	PTRobotInfo2 Structure
//
///////////////////////////
#define MAX_CARTRIDGE_TYPES 8
typedef struct 
{
	DWORD dwNumCartridges;		//Max Number of cartridges robot can hold
	DWORD dwCartridgeType[MAX_CARTRIDGE_TYPES];	// First element is left-most cartridge and last element is right-most cartridge
												// (from the user's viewpoint)
												// see "Cartridge Types" above
	DWORD dwFirmware2Code;
	DWORD dwPGA;
	DWORD dwModel;
	DWORD dwUSBSerialNum;	
	DWORD dwMaxDiscsPerBin;		// Added Version 1.22
	DWORD dwReserved[9];		// reserved for future data												
}PTRobotInfo2, *pPTRobotInfo2;



//To determine the BinLocation 1 represents the leftmost bin on the 
//duplicator and N represents the rightmost bin (where N is the number
//of bins in the robot).  

///////////////////////////
//
//	PTRobotStatus Structure
//
///////////////////////////
typedef struct 
{
	DWORD dwSystemState;		  //See "System State" section above
	DWORD dwSystemError;		  //See "System Errors" section above
	DWORD dwCurrColorSpits;
	DWORD dwCurrBlackSpits;
	DWORD dwFullColorSpits;
	DWORD dwFullBlackSpits;
}PTRobotStatus, *pPTRobotStatus;



// Cartridge Status Information Values for bCartridgeStatus[] in PTRobotStatus2 below (for Bravo 4100)
typedef enum
{
   CARTRIDGE_INFO_STILL_READING,
   CARTRIDGE_INFO_UNUSED,
   CARTRIDGE_INFO_MISSING,
   CARTRIDGE_INFO_INVALID,
   CARTRIDGE_INFO_COMM_ERROR,
   CARTRIDGE_INFO_BAD_POSITION,
   CARTRIDGE_INFO_BAD_INSTALL,
   CARTRIDGE_INFO_INVALID2,
   CARTRIDGE_INFO_EMPTY,
   CARTRIDGE_INFO_EMPTY2,
   CARTRIDGE_INFO_EMPTY3,
   CARTRIDGE_INFO_OK					// Valid cartridge
} CartridgeInfoType;


///////////////////////////
//
//	PTRobotStatus2 Structure
//
///////////////////////////
#define MAX_BINS				5
#define UNKNOWN_NUM_DISCS		255
#define NO_CARTRIDGE_INSTALLED	0
#define VALID_CARTRIDGE			1
#define INVALID_CARTRIDGE		2
typedef struct 
{
	DWORD dwCartridgeTypes;			// See "Cartridges Installed" section above
	DWORD dwNumDiscsInBins[MAX_BINS];	// 0th element is left-most bin (values are UNKNOWN_NUM_DISCS if unknown)
	DWORD dwTotalPrints;			// Total # of prints
	DWORD dwTotalPicks;				// Total # of picks from input bin
	long  lVerticalOffset;			// Vertial print offset (300dpi units) - Ver 1.25 updated to long (can be negative)
	long lHorizontalOffset;			// Horizontal print offset (300dpi units) - Ver 1.25 updated to long (can be negative)
	DWORD dwPrinterTrayStatus;		// See "Printer Tray Status" section above
	DWORD dwDiscPickSwitchStatus;	// See "Disc Pick Switch Status" section above
	DWORD dwCoverBeenOpenedFlag;	// set to 1 if cover has been opened
	DWORD dwCartridgeInstalled[MAX_CARTRIDGE_TYPES];	// 0=not installed.  1=valid cartridge.  2=invalid cartridge (ver 1.22 added)
	DWORD dwCartridgeNeedsAlign[MAX_CARTRIDGE_TYPES];	// set to TRUE (1) if cartridge needs alignment (ver 1.22 added)
	DWORD dwSystemStateHW;			// actual system state as reported directly from the printer (may be different than dwSystemState in PTRobotStatus)
	long  lYellowInkRemaining;		// Yellow % remaining (in ten thousandths of a percent).  e.g. 891723 = 89.1723%
	long  lMagentaInkRemaining;	// Magenta % remaining (in ten thousandths of a percent).  e.g. 891723 = 89.1723%
	long  lCyanInkRemaining;		// Cyan % remaining (in ten thousandths of a percent).  e.g. 891723 = 89.1723%
	long  lBlackInkRemaining;		// Black % remaining (in ten thousandths of a percent).  e.g. 891723 = 89.1723%
								// -BELOW VALUES ONLY VALID FOR DISC PUBLISHER 4100-
	BYTE  bCartridgeStatusYellow;	// See CartridgeInfoType above for valid values 
	BYTE  bCartridgeStatusMagenta;	// See CartridgeInfoType above for valid values 
	BYTE  bCartridgeStatusCyan;		// See CartridgeInfoType above for valid values 
	BYTE  bCartridgeStatusBlack;	// See CartridgeInfoType above for valid values 
	DWORD dwReserved[6];			// reserved for future data
}PTRobotStatus2, *pPTRobotStatus2;


///////////////////////////
//
//	PTPrinterSettings Structure
//
///////////////////////////
typedef struct 
{
	DWORD dwPrintQuality;		  //See "Print Quality" section above
	DWORD dwInnerDiam;			  //units in .1mm increments (150 - 500)
	DWORD dwOuterMargin;		  //units in .1mm increments (0 - 20)
}PTPrinterSettings,  *pPTPrinterSettings;


///////////////////////////
//
//	PTPrinterSettings2 Structure
//
///////////////////////////
typedef struct 
{
	// NOTE: 0xffff is a special value depending on Get or Set--
	// Get:  0xffff means that the setting is not supported
	// Set:  0xffff means to use the current driver setting
	DWORD dwPrintQuality;		  //See "Print Quality" section above
	DWORD dwInnerDiam;			  //units in .1mm increments (150 - 500)
	DWORD dwOuterMargin;		  //units in .1mm increments (0 - 20)
	DWORD dwCartridge;			// Cartridge type to use.  1=Black  2=Color  3=Color+Black  
	DWORD dwColorMatchType;		// Color Rendering type.  0=Best for Graphics  1=Best for Photos 
	DWORD dwColorTable;			// Color Table number to use. Valid values: 1-6  
	DWORD dwSaturation;			// Amount of saturation.  0-100  where 100 is full saturation  
	DWORD dwPrintBidi;			// Print bi-directionally or not.  0=No  1=Yes 
	DWORD dwRotate180;			// Rotate the image 180 degrees or not.  0=No  1=Yes  
	DWORD dwKioskPrintOnly;		// Kiosk mode when doing print-only.  0=No  1=Yes
	DWORD dwReserved[9];
}PTPrinterSettings2,  *pPTPrinterSettings2;



///////////////////////////
//
//	PTMediaInfo Structure
//
///////////////////////////
typedef struct 
{
    TCHAR tszMediaID[20];
	TCHAR tszMediaType[20];
} PTMediaInfo, *pPTMediaInfo;


///////////////////////////
//
//	PTManufactureInfo Structure
//
///////////////////////////
typedef struct
{
	TCHAR tszSerialNum[11];
	TCHAR tszManufactureDate[12];
	DWORD dwFiller[20];
}PTManufactureInfo, *pPTManufactureInfo;



//-----------------------------------------------------------------
// PTRobot API Prototypes
//-----------------------------------------------------------------


//*****************************************************************
//
//    PTRobot Initialization Functions
//
//*****************************************************************

///////////////////////////
//
//	PTRobot_Initialize
//
//	Description:
//		Function to initialize internal data structures of
//      the PTRobot module.
//	Params:
//		None
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_INTERNAL if an internal error occurred.
//		PTROBOT_MISSING_DLL if one of the support DLLs cannot be found
//		
///////////////////////////
DWORD WINAPI PTRobot_Initialize();

///////////////////////////
//
//	PTRobot_Destroy
//
//	Description:
//		Function to destroy internal data structures of
//      the PTRobot module.
//	Params:
//		None
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//
///////////////////////////
DWORD WINAPI PTRobot_Destroy();


///////////////////////////
//
//	PTRobot_SetupDebugging
//
//	Description:
//		Function to setup logging in the PTRobot module.  We advise that your
//      application has a "back door" method of turning debugging on.  All debugging
//      is off by default.
//	Params:
//		szDbgFile		full path to a debug file
//		dwDbgLvl		debug Level (0-5)
//						   0 = off, 1 = errors, 2 = warnings
//						   3 = Info, 4 and 5 = more info
//		szTraceFile		full path to a trace file
//	Notes:
//		If szDbgFile is NULL then debugging will be turned off.  If szTraceFile is
//      NULL then function tracing will be off.  Function tracing just logs the 
//      API function calls including the parameters.
//		This function should be the very first PTRobot_xxxx function to be called.
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_INTERNAL if an internal error occurred
//
///////////////////////////
DWORD WINAPI PTRobot_SetupDebugging(TCHAR * szDbgFile, DWORD dwDbgLvl, TCHAR * szTraceFile);


///////////////////////////
//
//	PTRobot_EnumRobots
//
//	Description:
//		Function to enumerate the Robots on the system.
//	Params:
//		phRobots 	points to an array of HANDLEs to store
//                  the Robots found.
//      pdwNumRobots 	points to a DWORD containing the number of HANDLEs
//               	in the phRobots array.  This value is an input
//                  and an output.  The user should specify the size
//					(number of HANDLEs) of the phRobots array on input.
//					The value of the pdwNumRobots on output will be the
//                  number of robots found.
//
//	Notes:
//		Both params will be updated upon successful completion of this
//      command.  phRobots will contain handles to robots connected to
//      this system. pdwNumRobots will will be updated with the number of 
//      robots found.
//      Also, note that the hDrives[] array in the PTRobotInfo will not be
//		valid until PTRobot_EnumDrives is called.
//
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_INVALID_ROBOT if no robots found
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_OVERFLOW if the number of robots found is > the value in 
//                       pdwNumRobots
//
///////////////////////////
DWORD WINAPI PTRobot_EnumRobots(HANDLE * phRobots, DWORD * pdwNumRobots);

///////////////////////////
//
//	PTRobot_EnumDrives
//
//	Description:
//		Function to enumerate the drives on the system and
//      determine which drives are under the control of this
//      robot.
//	Params:
//		hRobot		Handle to the robot to enumerate the drives of.
//		phDrives 	points to an array of DWORDS to store
//                  the Drives found.
//      pdwNumDrives 	points to a DWORD containing the number of HANDLEs
//               	in the phDrives array.  This value is an input
//                  and an output.  The user should specify the size
//					(number of HANDLEs) of the phDrives array on input.
//					The value of the pdwNumDrives on output will be the
//                  number of drives found.
//
//	Notes:
//		Both params will be updated upon successful completion of this
//      command.  phDrives will contain handles to drives connected to
//      this system. pdwNumDrives will will be updated with the number of 
//      drives found.
//
//		The format of the drive handles is the following:
//
//      	The least significant byte should contain the drive letter, the 
//			other three bytes should contain the SCSI triple.
//      	The drive can be identified by either of these methods.
//
//			For Example:  0x01030044 would identify a drive with:
//						Host=1, ID = 3, LUN = 0, and a drive letter of "D"
//					   
//			To identify the same drive the client could pass 
//			down 0x01030000, 0x00000044, or 0x01030044.
//
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence or after 
//                       PTRobot_EnumDrivesWithList
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_OVERFLOW if the number of drives found is > the value in 
//                       pdwNumDrives
//		PTROBOT_MULTDRIVES if the module cannot determine which drives are 
//						   robotically controlled. The calling application 
//                         needs to use PTRobot_SetRoboticDrive to resolve
//						   this error.
//
///////////////////////////
DWORD WINAPI PTRobot_EnumDrives(HANDLE hRobot, HANDLE * phDrives, DWORD * pdwNumDrives);

///////////////////////////
//
//	PTRobot_EnumDrivesWithList
//
//	Description:
//		Function to pass down drives enumerated by the calling app for
//      PTRobot to use in determining which drives are robotically controlled.
//		This is an alternative function to PTRobot_EnumDrives.
//	Params:
//		hRobot		Handle to the robot.
//		phDrives 	points to an array of HANDLEs that contains the
//                  drive handles of the drives in the system
//      pdwNumDrives 	points to a DWORD containing the number of HANDLEs
//               		in the phDrives array.  
//		phRobotDrives 	points to an array of HANDLEs that contains the
//                  	drive handles of the drives contained in this robot.
//      pdwNumRobotDrives 	points to a DWORD containing the number of drives
//               			in the phRobotDrives array.
//
//	Notes:
//		phRobotDrives and pdwNumRobotDrives will be updated upon successful 
//      completion of this command.  phRobotDrives will contain 
//      handles to drives contained in the robot. pdwNumRobotDrives will be
//		updated with the number of drives found. 
//
//		The format of the drive handle is the following:
//
//      	The least significant byte should contain the drive letter, the 
//			other three bytes should contain the SCSI triple.  The drive can 
//			be identified by either of these methods.
//
//			For Example:  0x01030044 would identify a drive with:
//						Host=1, ID = 3, LUN = 0, and a drive letter of "D"
//					   
//			To identify the same drive the client could pass down 
//			0x01030000, 0x00000044, or 0x01030044.
//
//		This function should be called instead of PTRobot_EnumDrives if the 
//		calling application wants to enumerate the drives and have PTRobot 
//		select the Robotically controlled drives from the list the calling 
//		application provides.
//			
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence or after 
//						 PTRobot_EnumDrives
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_OVERFLOW if the number of robotic drives found is > the value 
//						 in pdwDrives
//		PTROBOT_MULTDRIVES if the module cannot determine which drives are 
//						   robotically controlled.
//
///////////////////////////
DWORD WINAPI PTRobot_EnumDrivesWithList(HANDLE hRobot, HANDLE * phDrives, 
			DWORD * pdwNumDrives, HANDLE * phRobotDrives, DWORD * pdwNumRobotDrives);


///////////////////////////
//
//	PTRobot_SetRoboticDrive
//
//	Description:
//		Function to set a drive's position within the duplicator when
//      the PTROBOT_MULTDRIVES error is returned from either of the
//      EnumDrives functions.
//	Params:
//		hRobots 	Handle to the Robot.
//      hDrive		Handle to the Drive
// 		dwColIndex	Index identifying the column that the drive is in.
//					(0 based where 0 is the left-most column)
//		dwRowIndex	Index identifying the row that the drive is in.
//					(0 based where 0 is the top row)
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_INVALID_DRIVE if the drive handle is invalid
//		PTROBOT_INVALID_DRIVE_POSITION if column/row ids are invalid.
//
///////////////////////////
DWORD WINAPI PTRobot_SetRoboticDrive(HANDLE hRobot, HANDLE hDrive, DWORD dwColIndex, 
								DWORD dwRowIndex);

///////////////////////////
//
//	PTRobot_SetOpenCloseFunction
//
//	Description:
//		Function to set a calling application provided drive open/close 
//		function.
//	Params:
//		pvOpenClose 	pointer to a function to open and close the drive.
//						(setting to NULL will cause non-callback open/close
//						 to be used).
//	Notes:
//		This function allows the calling application to provide the drive 
//		open/closing functionality through their recording engine.  If this 
//      function is not called then the drive will be opened/closed via OS 
//		calls.  The function pointed to by the pvOpenClose param should be 
//		defined as follows:
//  
//      void   OpenCloseDrive(DWORD hDrive, DWORD dwOpen);
//
//		Please see the "Drive Open/Close" definitions above for the dwOpen
//		param.
//
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//
///////////////////////////
DWORD WINAPI PTRobot_SetOpenCloseFunction(void * pvOpenClose);

///////////////////////////
//
//	PTRobot_SetRobotOptions
//
//	Description:
//		Function to set the current robot options.
//	Params:
//		hRobot			Handle to the robot
//      dwRobotOptions 	DWORD containing the options to set.
//						See "Robot Options" defines above 
//	Notes:
//		You should call PTRobot_GetRobotOptions to get the current Options
//      and then set the options you want to change prior to calling
//      this function.
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_UNSUPPORTED_OPTION if the option is unsupported on that robot
//
///////////////////////////
DWORD WINAPI PTRobot_SetRobotOptions(HANDLE hRobot, DWORD dwRobotOptions);

///////////////////////////
//
//	PTRobot_GetRobotOptions
//
//	Description:
//		Function to get the current robot options.
//	Params:
//		hRobot				Handle to the robot
//      pdwRobotOptions 	points to a DWORD.
//							See "Robot Options" defines above
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_GetRobotOptions(HANDLE hRobot, DWORD *pdwRobotOptions);





//*****************************************************************
//
//    PTRobot Info/Status Functions
//
//*****************************************************************

///////////////////////////
//
//	PTRobot_GetDriveInfo
//
//	Description:
//		Function to get the drive info for a particular
//      drive handle.
//	Params:
//		hDrive		Handle to the drive (from EnumDrives)
//      pDrvInfo 	points to a PTDriveInfo structure. 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_DRIVE if the drive handle is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_GetDriveInfo(HANDLE hDrive, PTDriveInfo* pDrvInfo);
		
///////////////////////////
//
//	PTRobot_GetRobotInfo
//
//	Description:
//		Function to get the robot info for a particular
//      robot handle.
//	Params:
//		hRobot		Handle to the robot (from EnumRobots)
//      pRobotInfo 	points to a PTRobotInfo structure. 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_GetRobotInfo(HANDLE hRobot, PTRobotInfo *pRobotInfo);

///////////////////////////
//
//	PTRobot_GetRobotInfo2
//
//	Description:
//		Function to get ADDITIONAL robot info for a particular
//      robot handle.
//	Params:
//		hRobot		Handle to the robot (from EnumRobots)
//      pRobotInfo2 	points to a PTRobotInfo structure. 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_GetRobotInfo2(HANDLE hRobot, PTRobotInfo2 *pRobotInfo2);


///////////////////////////
//
//	PTRobot_GetRobotStatus
//
//	Description:
//		Function to get the current status for a particular
//      robot.
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//      pRobotStatus 	points to a PTRobotStatus structure. 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_GetRobotStatus(HANDLE hRobot, PTRobotStatus *pRobotStatus);


///////////////////////////
//
//	PTRobot_GetRobotStatus2
//
//	Description:
//		Function to get the Additional current status for a particular
//      robot.
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//      pRobotStatus2 	points to a PTRobotStatus2 structure. 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_BUSY if no response from robot
//
///////////////////////////
DWORD WINAPI PTRobot_GetRobotStatus2(HANDLE hRobot, PTRobotStatus2 *pRobotStatus2);


///////////////////////////
//
//	PTRobot_GetManufactureInfo
//
//	Description:
//		Function to get manufacture info
//	Params:
//		hRobot				Handle to the robot (from EnumRobots)
//		pPTManufactureInfo	points to a PTManufactureInfo structure.
//	Notes:
//
//	Return:
//     	PTROBOT_OK if Successful (and fills in pPTManufactureInfo)
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if invalid robot specified
//		
///////////////////////////
DWORD WINAPI PTRobot_GetManufactureInfo( HANDLE hRobot, PTManufactureInfo * pManufactureInfo);



//*****************************************************************
//
//    PTRobot Robotic Functions
//
//*****************************************************************

///////////////////////////
//
//	PTRobot_LoadDrive
//
//	Description:
//		Function to load a drive from an input location
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//		hDrive			Handle to the drive (from EnumDrives)
//      dwFromLocation  DWORD containing the "from" location
//			0 = Auto
//			1 = Bin1 (right-most bin)
//			2 = Bin2
//			...
//			100 = Printer
//		dwClearDrive	Clear drive before loading. 
//						(See Clear Drive section)
// 
//	Notes:
//		Clear drive before loading should be done the first loading.  This will
//		cause the picker to attempt to pick discs out of the drive to determine
//      if any discs were left in the drive from a previous job. 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_INVALID_DRIVE if the drive handle is invalid
//		PTROBOT_INVALID_LOCATION if the location is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_LoadDrive(HANDLE hRobot, HANDLE hDrive, DWORD dwFromLocation, DWORD dwClearDrive);

///////////////////////////
//
//	PTRobot_LoadPrinter
//
//	Description:
//		Function to load the printer from an input bin location
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//      dwFromLocation DWORD containing the "from" location
//			0 = Auto
//			1 = Bin1 (right-most bin)
//			2 = Bin2
//			...
//
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		PTROBOT_INVALID_LOCATION if the location is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_LoadPrinter(HANDLE hRobot, DWORD dwFromLocation);

///////////////////////////
//
//	PTRobot_LoadPrinterFromDrive
//
//	Description:
//		Function to load the printer from a drive
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//		hDrive			Handle to the drive (from EnumDrives)
 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_INVALID_DRIVE if the drive handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//
///////////////////////////
DWORD WINAPI PTRobot_LoadPrinterFromDrive(HANDLE hRobot, HANDLE hDrive);

///////////////////////////
//
//	PTRobot_UnLoadDrive
//
//	Description:
//		Function to unload the drive to an output position.
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//		hDrive			Handle to the drive (from EnumDrives)
//		dwToLocation 	DWORD containing the "to" location
//			0 = Auto
//			1 = Bin1 (right-most bin)
//			2 = Bin2
//			...
//			100 = Printer
//			200 = Reject
// 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_INVALID_DRIVE if the drive handle is invalid
//		PTROBOT_INVALID_LOCATION if the location is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_UnLoadDrive(HANDLE hRobot, HANDLE hDrive, DWORD dwToLocation);

///////////////////////////
//
//	PTRobot_UnLoadPrinter
//
//	Description:
//		Function to unload the printer to an output position.
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//		dwToLocation 	DWORD containing the "to" location 
//			0 = Auto
//			1 = Bin1 (right-most bin)
//			2 = Bin2
//			...
//			200 = Reject
// 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		PTROBOT_INVALID_LOCATION if the location is invalid
//
//
///////////////////////////
DWORD WINAPI PTRobot_UnLoadPrinter(HANDLE hRobot, DWORD dwToLocation);

///////////////////////////
//
//	PTRobot_MoveDiscBetweenLocations
//
//	Description:
//		Function to move disc from one bin to another bin
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//		dwFromLocation 	DWORD containing the from location 
//			1 = Bin1 (right-most bin)
//			2 = Bin2
//			...
//		dwToLocation 	DWORD containing the "to" location 
//			1 = Bin1 (right-most bin)
//			2 = Bin2
//			...
//			100 = Printer
//			200 = Reject
// 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_INVALID_LOCATION if the location is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_MoveDiscBetweenLocations(HANDLE hRobot, DWORD dwFromLocation, DWORD dwToLocation);


///////////////////////////
//
//	PTRobot_SetPrintCopies
//
//	Description:
//		This function is used for a multiple auto-print job.
//	This function is called each time prior to calling one of the print functions
//  (e.g. PTRobot_PrintFile() ).  The number of copies is set back to 1 after printing
//  Not all robots support this feature (PTACT_AUTOPRINTER_MODE specifies support)
//	e.g. Bravo 4100 prints mulitple copies faster with this method.
//
//
//	Params:
// 
//	Notes:
//	Return:
//     	PTROBOT_OK if Successful
//		
//	
///////////////////////////
DWORD WINAPI PTRobot_SetPrintCopies(HANDLE hRobot, DWORD dwCopies );


///////////////////////////
//
//	PTRobot_PrintFile
//
//	Description:
//		Function to print a Surething image (.STD), raster image (.JPG, .BMP, .TIF, 
//		etc.), or .PRN file to the printer.
//	Params:
//		hRobot		Handle to the robot (from EnumRobots)
//		tszFile		File to print (.STD, .PRN, .JPG, .BMP)
// 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		PTROBOT_PRN_INVALID if the prn file is not valid for the printer
//		PTROBOT_PRINTFILE_INVALID if unknown print file 
//		PTROBOT_PRINTFILE_NOT_FOUND if the file doesn't exist (or if Merge file not found)
//		PTROBOT_PRINTAPP_NOT_INSTALLED if the required print application is not installed.
//
///////////////////////////
DWORD WINAPI PTRobot_PrintFile(HANDLE hRobot, TCHAR * tszFile, DWORD dwPrintIndex);



///////////////////////////
//
//	PTRobot_PrintFileWithMerge
//
//	Description:
//		Function to print a Surething .STD file that has Merge Text/Photos.
//		The Merge Text and/or Photos can be specified in a variable number of 
//		arguments passed into this function.  The Surething file should be designed 
//		with the same number of merge strings passed in here.
//
//	Params:
//		hRobot				Handle to the robot (from EnumRobots)
//		tszFile				Surething (.STD) File to print.  
//		dwNumMergeStrings	Number of merge strings to follow
//		...					Variable number of pointers to TCHAR strings
//							These are the merge strings or photo names (including 
//							path) to be printed.
//							NOTE: For the strings that follow dwMergeStrings to 
//							be used, the user must have �Set Merge File� within the .STD file
//						  	** Limit each string to 256 characters or less **
//
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		PTROBOT_PRINTFILE_NOT_FOUND if the file doesn't exist
//		PTROBOT_PRINTAPP_NOT_INSTALLED if the required print application is not 
//			installed.
//		PTROBOT_PRINTFILE_INVALID if the filename is not .STD
//		
///////////////////////////
DWORD WINAPI PTRobot_PrintFileWithMerge(HANDLE hRobot, 
											TCHAR * tszFile, 
											DWORD dwNumMergeStrings,
											...);


///////////////////////////////
//
//	PTRobot_PrintFileWithMerge2
//
//	Description:
//		Function to print a Surething .STD file that has Merge Text/Photos.
//		The Merge Text and/or Photos MUST be specified BEFORE THIS CALL, by
//		calling PTRobot_AddMergeFields().  PTRobot_AddMergeFields() must be called 
//		once for every Merge field that is designed into the SureThing file.
//		Then, this function is called to print the file with the specified Merge data.
//
//	Params:
//		hRobot				Handle to the robot (from EnumRobots)
//		tszFile				Surething (.STD) File to print. 
//		fClearMergeList		Whether or not to clear the list of merge strings (or photo names)
//							that were stored from previous calls to PTRobot_AddMergeFields().
//							If doing mutiple discs with the same merge data then set to FALSE.
//							If merge data will be changing for each disc then set to TRUE.
//							
//		NOTE: For this to work, the user must have �Set Merge File� within the .STD file
//
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		PTROBOT_PRINTFILE_NOT_FOUND if the file doesn't exist
//		PTROBOT_PRINTAPP_NOT_INSTALLED if the required print application is not 
//			installed.
//		PTROBOT_PRINTFILE_INVALID if the filename is not .STD
//		
//////////////////////////////
DWORD WINAPI PTRobot_PrintFileWithMerge2(HANDLE hRobot, 
											TCHAR * tszFile, 
											BOOL fClearMergeList);




DWORD WINAPI PTRobot_PrintFileWithMergeFile(HANDLE hRobot, 
													TCHAR * tszFile, 
													TCHAR * tszMergeFile);

///////////////////////////
//
//	PTRobot_AddMergeFields
//
//	Description:
//		This function is used in conjuction with PTRobot_PrintMergeFile2()
//		to print a SureThing file with merge/replaceable text fields (or photos).
//		DESIGN TIME:
//		User first designs a SureThing (.STD) file with replaceable Text and/or
//		photos and then sets the Merge file (using Tools/Set Merge File).
//		RUN TIME:		
//		This function is called repeatedly, passing in the text you want printed
//		(and/or the name & path of the photo you want printed).  
//		The number of times this function is called should be equal to the number of 
//		Merge Fields inserted at design time.
//		Then, call PTRobot_PrintFileWithMerge2() to print the SureThing file, using 
//		the merge fields set with this call.
//
//	Params:
//		dwAppID		Application ID specified by Primera
// 
//	Notes:
//	Return:
//     	PTROBOT_OK if Successful
//		
//	
///////////////////////////
DWORD WINAPI PTRobot_AddMergeFields(HANDLE hRobot, const TCHAR * tszField );



///////////////////////////
//
//	PTRobot_ClearMergeList
//
//	Description:
//		Function to clear the List of Merge strings (or photo names) 
//		that were stored from previous calls to PTRobot_AddMergeFields().
//		This function would be used if doing a print preview of a STD file 
//		that has merge fields (ie. using PTRobot_GetSureThingPreview() ).
//		This function is NOT needed if only printing a SureThing file with merge fields
//		because PTRobot_PrintFileWithMerge2() has a flag to clear the merge list after printing.
//		So, the use of this function would be like this:
//			PTRobot_AddMergeFields()
//			PTRobot_AddMergeFields()...
//			PTRobot_GetSureThingPreview()
//			PTRobot_ClearMergeList()
//
//		NOTE: For this to work, the user must have �Set Merge File� within the .STD file

//	Params:
//		hRobot				Handle to the robot (from EnumRobots)
//	Return:
//     	PTROBOT_OK 
//		
///////////////////////////
DWORD WINAPI PTRobot_ClearMergeList( HANDLE hRobot );



///////////////////////////
//
//	PTRobot_GetSureThingPreview
//
//	Description:
//		Function to get a preview of a SureThing file
//	Params:
//		tszSureThingFile	The SureThing file to get a preview of
//		tszOutputFile		The file name (including path) of desired output file
//							(NOTE: must have extension of .JPG, .BMP, or .PNG)
//		dwResolution		Resolution (in DPI) of output file (Valid values: 50-600)
//	Notes:
//		1)This function returns immediately, but the output file may take several seconds
//		  to generate. Caller should keep checking for the output file's existence.
//		2)The output file is NOT deleted.  Caller is responsible for deleting, if desired.
//
//	Return:
//     	PTROBOT_OK if Successful
//		PTROBOT_PRINTFILE_INVALID if fails to generate preview
//		PTROBOT_INVALID_EXTENSION if not a valid output file extension (.JPG, .BMP, .PNG)
//
//		
///////////////////////////
DWORD WINAPI PTRobot_GetSureThingPreview(TCHAR * tszSureThingFile, 
													TCHAR * tszOutputFile, 
													DWORD dwResolution);


///////////////////////////
//
//	PTRobot_SetPrinterSettings
//
//	Description:
//		Function to set some printer driver settings
//	Params:
//		hRobot				Handle to the robot (from EnumRobots)
//		pPrinterSettings	points to a PTPrinterSettings structure.
// 
//	Notes:
//		If this function is not called the default print settings will be used.	This
//      function will change the system default print settings.
//		As of Version 1.2.0 the system default print settings will restored after a print
//		is sent via PTRobot_PrintFile() or PTRobot_PrintFileWithMerge().
//
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		PTROBOT_INVALID_PRINTER_SETTINGS if the printer settings are invalid
//		
///////////////////////////
DWORD WINAPI PTRobot_SetPrinterSettings(HANDLE hRobot, PTPrinterSettings *pPrinterSettings);

///////////////////////////
//
//	PTRobot_GetPrinterSettings
//
//	Description:
//		Function to get some printer driver settings
//	Params:
//		hRobot				Handle to the robot (from EnumRobots)
//		pPrinterSettings	points to a PTPrinterSettings structure.
// 
//	Notes:
//		If this function is not called the default print settings will be used.
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		
///////////////////////////
DWORD WINAPI PTRobot_GetPrinterSettings(HANDLE hRobot, PTPrinterSettings *pPrinterSettings);


///////////////////////////
//
//	PTRobot_SetPrinterSettings2
//
//	Description:
//		Function to set additional printer driver settings
//	Params:
//		hRobot				Handle to the robot (from EnumRobots)
//		pPrinterSettings2	points to a PTPrinterSettings2 structure.
// 
//	Notes:
//		If this function is not called the default print settings will be used.	This
//      function will change the system default print settings.
//		As of Version 1.2.0 the system default print settings will restored after a print
//		is sent via PTRobot_PrintFile() or PTRobot_PrintFileWithMerge().
//
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		PTROBOT_INVALID_PRINTER_SETTINGS if the printer settings are invalid
//		
///////////////////////////
DWORD WINAPI PTRobot_SetPrinterSettings2(HANDLE hRobot, PTPrinterSettings2 *pPrinterSettings2);

///////////////////////////
//
//	PTRobot_GetPrinterSettings2
//
//	Description:
//		Function to get some additional printer driver settings
//	Params:
//		hRobot				Handle to the robot (from EnumRobots)
//		pPrinterSettings2	points to a PTPrinterSettings2 structure.
// 
//	Notes:
//		If this function is not called the default print settings will be used.
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_NO_PRINTER if the robot doesn't have a printer
//		
///////////////////////////
DWORD WINAPI PTRobot_GetPrinterSettings2(HANDLE hRobot, PTPrinterSettings2 *pPrinterSettings2);


///////////////////////////
//
//	PTRobot_KillSystemError
//
//	Description:
//		Function to kill a system error.
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//		dwResetPrinter	DWORD to notify if the printer should be reset.
//				1 = Reset the printer
//				0 = do not reset the printer
// 
//	Notes:
//		If there is no system error and dwResetPrinter is set to 1 the 
//      printer will be reset.  Otherwise if there is a system error, that error
//      will be cleared (if possible) and the printer will be reset if the 
//      dwResetPrinter is set to 1. 
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_KillSystemError(HANDLE hRobot, DWORD dwResetPrinter);


///////////////////////////
//
//	PTRobot_SystemAction
//
//	Description:
//		Function to instruct the system to perform a specifc action.
//	Params:
//		hRobot			Handle to the robot (from EnumRobots)
//		dwAction		Action to perform
// 
//	Notes:
//		This function is used to perform a specific function on a
//      robot.  The defined actions and their descriptions are detailed
//      below.
//
//		Action:
//			PTACT_ALIGNPRINTER -> Align the Printer (Disc Publisher PRO only)
//		Description:
//			This will cause an alignment print to occur on the printer and
//          this function will return when the alignment is complete.
//
//		Action:
//		    PTACT_IGNOREINKLOW -> Ignore Ink Low (Disc Publisher PRO only)
//		Description:
//			This will cause an ink low system error to be ignored.
//
//		Action:
//		    PTACT_DISABLEPWRBUTTON -> Disable Power Button 
//		Description:
//			This will disable the power button on Disc Publisher II and PRO.
//
//		Action:
//		    PTACT_REINIT_DRIVES -> Re-initialize drives
//		Description:
//			PTRobot maintains Registry values for persistent settings including drive
//          serial numbers.  This action will clear the drive serial numbers stored
//          which will force the user to re-identify the robotically controlled drives.
//		Action:
//		    PTACT_IDENTIFY -> Identify a robot
//		Description:
//			This will cause the robot to do something to visually identify itself
//          For example the Bravo units will move their printer tray.
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_ROBOT if the robot handle is invalid
//		PTROBOT_INVALID_ACTION if the robot action is invalid
//
///////////////////////////
DWORD WINAPI PTRobot_SystemAction(HANDLE hRobot, DWORD dwAction);

///////////////////////////
//
//	PTRobot_OpenCloseDrive
//
//	Description:
//		Function to open or close a drive
//	Params:
//		hDrive				Handle to the drive (from EnumDrives)
//		dwOpen				See (Drive Open/Close) section above 
//							   (DRIVE_OPEN=0  DRIVE_CLOSE=1)
// 
//	Notes:
//	Return:
//      PTROBOT_OK if Successful
//		PTROBOT_SEQUENCE if this command is called out of sequence
//		PTROBOT_INTERNAL if an internal error occurred
//		PTROBOT_INVALID_DRIVE if the drive handle is invalid
//		
///////////////////////////
DWORD WINAPI PTRobot_OpenCloseDrive(HANDLE hDrive, DWORD dwOpen );

///////////////////////////
//
//	PTRobot_GetErrorString
//
//	Description:
//		Function to get the error string for a specific system
//      	error or PTRobot API Return error.
//  
//	Params:
//      hRobot				Robot that the error is on.
//		dwErrorNum			System Error Number 
//		pwszErrorString		Error string returned 
//							(Note wide characters.  Calling application must 
//							allocate this memory).
//		dwMaxLength			Length of buffer pointed to by pwszErrorString 
//  						(number of wide characters)
//		dwLanguage			Language of string to return (See "Languages" 	
//							definitions above)
// 
//	Notes:
//		dwErrorNum can be either dwSystemError from PTRobotStatus structure (which is 
//		returned by PTRobot_GetRobotStatus()) or dwErrorNum can be an error returned
// 		from a PTRobot_xxxxx call (e.g. PTROBOT_INVALID_ROBOT).
//
//
//	Return:
//     	PTROBOT_OK if Successful
//		PTROBOT_INVALID_LANG if language is invalid
//		PTROBOT_INVALID_ERROR if error is invalid
//		PTROBOT_INTERNAL if buffer is undersized, etc.
//		
///////////////////////////
DWORD WINAPI PTRobot_GetErrorString(HANDLE hRobot, 
									DWORD dwErrorNum, 
									WCHAR * pwszErrorString,  
									DWORD dwMaxLength, 
									DWORD dwLanguage);

///////////////////////////
//
//	PTRobot_GetMediaInfo
//
//	Description:
//		This function will get information on the media that
//      is loaded in the drive.
//	Params:
//		hDrive				Handle to the drive (from EnumDrives)
//		PTMediaInfo *		Media info
// 
//	Notes:
//	Return:
//		PTROBOT_OK if successful and media is found and the media is valid.
//      PTROBOT_INVALID_MEDIA if the media is not valid 
//      PTROBOT_NO_MEDIA if no media is found
//      PTROBOT_INVALID_DRIVE if the drive is not valid
//      PTROBOT_INTERNAL some other error
//		
///////////////////////////
DWORD WINAPI PTRobot_GetMediaInfo(HANDLE hDrive, PTMediaInfo * pDiscInfo );

///////////////////////////
//
//	PTRobot_SetApplicationID
//
//	Description:
//		Function to set the Application ID.  
//		This value is assigned for each application by Primera as needed.
//		Only applications that require special functionality will require this.
//		(note most applications will not need this).
//
//	Params:
//		dwAppID		Application ID specified by Primera
// 
//	Notes:
//	Return:
//     	PTROBOT_OK if Successful
//		PTROBOT_INTERNAL if an internal error occurred
//		
///////////////////////////
DWORD WINAPI PTRobot_SetApplicationID( DWORD dwAppID );

DWORD WINAPI PTRobot_SetRoboticDriveWithoutEnum(HANDLE hRobot, HANDLE hDrive, TCHAR *tszSerial, DWORD dwColIndex, 
								DWORD dwRowIndex, BOOL fProgramFlash);

DWORD WINAPI PTRobot_GetDriveSerialFromFlash(HANDLE hRobot, DWORD dwColIndex, 
								DWORD dwRowIndex, TCHAR * tszSerial);

//-----------------------------------------------------------------
// end of PTRobot API Prototypes
//-----------------------------------------------------------------



/*****************************************************************************

PTRobot Usage:

	Below is PSUEDO-CODE for how a calling application should use PTRobot to 
	implement robotics into its application.

	PTRobot_Initialize

	PTRobot_EnumRobots
		- if the number of robots is greater than 1 then the calling application will
		  need to provide some logic/ui to determine which robot to use.  The app
		  can use PTRobot_GetRobotInfo to get details about each robot.
	PTRobot_EnumDrives or PTRobot_EnumDrivesWithList
		- This will cause PTRobot to determine which drives are robotically controlled 
		  by enumerating the drives themselves (PTRobot_EnumDrives) or based off a 
		  list of drives passed in (PTRobot_EnumDrivesWithList)
	PTRobot_GetDriveInfo for all drives returned
		- This will allow the calling app to know which drive is which
	PTRobot_LoadDrive(Robot, Drive, TRUE)
		- This will load a disc into the drive from the input bin
		  (should set parameter 3 to TRUE if first round of the job)
	PTRobot_GetRobotStatus
		- This would be called in a loop until dwSystemState is set to SYSSTATE_IDLE 
          or SYSSTATE_ERROR.
	
	..  Client application will perform operations on the disc in the drive.

	if the operations are successful
		PTRobot_LoadPrinterFromDrive(Robo, Drive)
		PTRobot_GetRobotStatus -See Above-
		PTRobot_PrintFile(szPrintFile)	or   PTRobot_PrintFileWithMerge(...)
		PTRobot_GetRobotStatus -See Above-
		PTRobot_UnloadPrinter(Robot, 0)
		PTRobot_GetRobotStatus -See Above-
	else
		PTRobot_UnloadDrive(Robot, Drive, 100)
		PTRobot_GetRobotStatus -See Above-

	PTRobot_Destroy
		

***/


#ifdef __cplusplus
}
#endif
