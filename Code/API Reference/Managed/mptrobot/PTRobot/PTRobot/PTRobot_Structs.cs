using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace PrimeraTechnology
{

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class PrinterSettings
    {
        public PrintQuality PrintQuality;
        public UInt32 InnerDiam;
        public UInt32 OuterMargin;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class PrinterSettings2
    {
        // Get: value of 0xffff means not supported
        // Set: value of 0xffff means to use current driver setting
        public PrintQuality PrintQuality;       //
        public UInt32 InnerDiam;                // units in .1mm increments (150 - 500)
        public UInt32 OuterMargin;              // units in .1mm increments (0 - 20)
        public CartridgeType CartridgeToUse;    // 1=Black, 2=Color, 3=Color+Black
        public ColorType ColorType;             // 0=Best for Graphics, 1=Best for Photos
        public ColorTable ColorTable;           // Tables 1-6
        public UInt32 Saturation;               // Ink Saturation.  0-100 where 100 is full saturation
        public bool fPrintBidi;                 // 1 = print bi-directional,  0 = print Uni-directional
        public bool fRotate180;                 // 1 = Rotate image 180 degrees, 0 = do not rotate
        public bool fKioskPrintOnly;            // 1 = Kiosk mode (print-only job), 0 = not kiosk mode
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 9)]
        public UInt32[] Reserved;    
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class DriveInfo
    {
        public UInt32 DriveID = 0;			 	 //Drive Handle.
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 132)]
        public String DriveName = null;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 40)]
        public String FirmwareVer = null;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 40)]
        public String SerialNum = null;
        public UInt32 RobotID = 0;
        public UInt32 DriveColumn = 0;  //Drive Column (0 based - 0 is leftmost column)
        public UInt32 DriveRow = 0;     //Drive Row (0 based - 0 is the top row)
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class ManufactureInfo
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        public String SerialNum = null;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public String ManufactureDate = null;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public int[] FillerArray;
    }


    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class RobotInfo
    {
        public UInt32 Robot = 0;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public String RobotDesc = null;
        public RobotType RobotType;			//See "Robot Type" section above
        public UInt32 NumDrives = 0;			//Number of Recorders on this robot
        public UInt32 NumPrinters = 0;		//Number of Printers on this robot (0 or 1)
        public UInt32 NumBins = 0;			//Number of Bins on this robot
        public UInt32 DriveColumns = 0;		//Number of Drive Columns
        public UInt32 DriveRows = 0;			//Number of Drive Rows
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public String RobotFirmware = null;
        public UInt32 SupportedOptions = 0;	//See "Robot Options" section above
        public UInt32 SupportedActions = 0;	//See "Robot Actions" section above
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public UInt32[] DriveIDs;
        public BusType DriveBusType = 0;		//BusType of the Drives
    }


    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class RobotInfo2
    {
        public UInt32 NumCartridges;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public CartridgeType[] CartridgeType;
        public UInt32 Firmware2Code;
        public UInt32 PGA;
        public UInt32 Model;
        public UInt32 USBSerialNum;
        public UInt32 MaxDiscsPerBin;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 9)]
        public UInt32[] Reserved;

    }


    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class RobotStatus
    {
        public SystemState SystemState;
        public SystemError SystemError = 0;
        public UInt32 CurrentColorSpits = 0;
        public UInt32 CurrentBlackSpits = 0;
        public UInt32 FullColorSpits = 0;
        public UInt32 FullBlackSpits = 0;
    }


    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class RobotStatus2
    {
        public UInt32 CartridgeTypes = 0;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
        public UInt32[] NumDiscsInBins;
        public UInt32 TotalPrints = 0;
        public UInt32 TotalPicks = 0;
        public Int32 VerticalOffset = 0;
        public Int32 HorizontalOffset = 0;
        public UInt32 PrinterTrayStatus = 0;
        public UInt32 nDiscPickSwitchStatus = 0;
        public UInt32 CoverBeenOpenedFlag = 0;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public UInt32[] CartridgeInstalled;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public UInt32[] CartridgeNeedsAlign;
        public UInt32 SystemStateHardware = 0;
        public Int32 lYellowInkRemaining;		    // Yellow % remaining (in ten thousandths of a percent).  e.g. 891723 = 89.1723%
        public Int32 lMagentaInkRemaining;		// Magenta % remaining (in ten thousandths of a percent).  e.g. 891723 = 89.1723%
        public Int32 lCyanInkRemaining;			// Cyan % remaining (in ten thousandths of a percent).  e.g. 891723 = 89.1723%
        public Int32 lBlackInkRemaining;			// Black % remaining (in ten thousandths of a percent).  e.g. 891723 = 89.1723%
            // -BELOW VALUES ONLY VALID FOR DISC PUBLISHER 4100-
        public Byte bCartridgeStatusYellow;	    // See CartridgeInfoType enum for valid values 
        public Byte bCartridgeStatusMagenta;	// See CartridgeInfoType enum for valid values 
        public Byte bCartridgeStatusCyan;		// See CartridgeInfoType enum for valid values 
        public Byte bCartridgeStatusBlack;	    // See CartridgeInfoType enum for valid values 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
        public UInt32[] Reserved;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class MediaInfo
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public String MediaID = null;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public String MediaType = null;
    }
}
