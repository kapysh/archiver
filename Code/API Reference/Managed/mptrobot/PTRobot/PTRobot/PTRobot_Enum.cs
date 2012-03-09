namespace PrimeraTechnology
{
    public enum SystemState
    {
        Idle = 0,
        Busy = 1,
        Error = 2
    }

    public enum PTRobotReturn
    {
        Ok = 0,
        Internal =500,
        Sequence =501,
        InvalidRobot=502,
        InvalidDrive=503,
        InvalidBin=504,
        NoDrives=505,
        OpenCloseFailed=506,
        Overflow=507,
        NoPrinter=508,
        PrintFileInvalid=509,
        PrintApplicationNotInstalled=510,
        PrintFileNotFound=511,
        PRNInvalid=512,
        UnsupportedOption=513,
        DirectoryNotFound=514,
        InvalidLocation=515,
        MultDrives=516,
        InvalidPrinterSettings=517,
        InvalidDrivePosition=518,
        InvalidAction=519,
        FeatureNotImplemented=520,
        PrintApplicationOpen=521,
        MissingDLL=522,
        DriveNotReady=523,
        InvalidMedia=524,
        NoMedia=525,
        InvalidLanguage=526,
        InvalidError=527,
        Busy = 528,
        InvalidExtension = 529

    }
    public enum SystemError
    {
        None                =0,
        PrinterTray	        =1,
        CartCode			=2,
        InputEmpty			=3,
        PrinterComm			=4,
        ColorCartEmpty		=5,
        BlackCartEmpty		=6,
        BothCartsEmpty		=7,
        Pick				=8,
        ArmMove				=9,
        CartMove			=10,
        InternalSoftware	=12,
        NoRoboticDrives		=13,
        Offline				=14,
        CoverOpen			=15,
        PrinterPick			=16,
        MultipleDiscsPicked	=17,	
        MultipleDiscsPrinter			=18,
        MultipleDiscsRecorder			=19,
        DroppedDiscRecorder			    =20 ,
        DroppedDiscBin1				    =28 ,
        DroppedDiscBin2				    =29,
        DroppedDiscPrinter				=33 ,
        DroppedDiscReject				=34 ,
        DroppedDiscUnknown				=35 ,
        AlignNeeded					    =36,
        ColorCartInvalid				=37,
        BlackCartInvalid				=38,
        BothCartInvalid					=39,
        NoCarts						    =40,
        BlackInColorCart				=41,
        ColorInBlackCart				=42,
        CartsSwapped					=43,
        PigmentCartridge				=44,
        AlignFailed					    =45,
        DroppedDiscPrinterFatal			=46,
        MultipleDiscsRightBin			=47,
        MultipleDiscsLeftBin			=48,
        ColorCartEmptyFinal				=49,
        BlackCartEmptyFinal				=50,
        BothCartEmptyFinal				=51,
        WaitingForPrinter				=52,
        NoDiscInPrinter				    =53	,
        Busy						    =54,
        Purge                           =55,
        DockSensor                      =56,
        AlreadyPrinted                  =57,
        UnknownHardware                 =58
    }

    public enum DriveAction
    {
        Open = 0,
        Close = 1
    }
    public enum DiscLocation
    {
        Auto = 0,
        Right_Bin = 1,
        Left_Bin = 2,
        Printer = 100,
        Reject = 200
    }
    public enum RobotType
    {
        DiscPublisher = 0,
        DiscPublisherII = 1,
        DiscPublisherPRO = 2,
        ComposerMAX =3,
        DiscPublisherXR = 4,
        DiscPublisherXRP = 5,
        DiscPublisherSE = 6,
        DiscPublisherPROXI = 7,
        DiscPublisher4100 = 8,
        DiscPublisher4100_XRP = 9,
        DiscPublisher4051 = 10

    }

    public enum RobotOptions
    {
        KioskMode = 0x01
    }
    public enum SystemActions
    {
        AlignPrinter = 0x1,
        IgnoreInkLow = 0x2,
        DisablePwrButton = 0x4,
        ReinitDrives = 0x8,
        Identify = 0x10,
        CancelCmd = 0x20,
        EnablePwrButton = 0x40,
        ResetSystem = 0x80,
        CheckDiscs = 0x100,
        CleanCartridges = 0x200,
        CalibrateOneDisc = 0x400,
        ChangeCartridge = 0x800,
        EndCartridgeChange = 0x1000,
        ShipPosition = 0x2000,
        ResetLeftInkLevels = 0x4000,
        ResetRightInkLevels = 0x8000,
        AllowNoCartridgeOperation = 0x10000,
        XiLightOff = 0x20000,
        XiLightOn =  0x40000,
        XiLightFlash = 0x80000,
        UnhookPicker = 0x00100000,
        AutoPrinterMode = 0x00200000,
		FanOn = 0x00400000,	
        FanOff = 0x00800000
    }

    public enum PrintQuality
    {
        Low=0,
        Medium,
        Better,
        High,
        Best
    }

    public enum BusType
    {
        USB = 0,
        FireWire = 1
    }

    public enum ClearDrive
    {
        No =0,
        Yes =1
    }

    public enum Languages
    {
        English = 0,
        Japanese,
        German,
        French,
        Spanish,
        Italian,
        ChineseSimplified,
        Korean,
        Polish,
        ChineseTraditional,
        Czech
    }
    public enum PrinterTrayStatus
    {
        TrayInWithDisc = 'D',
        TrayInNoDisc = 'I',
        TrayOut = 'O'
    }
    public enum DiscPickSwitchStatus
    {
        NoDisc = 'X',
        HasDisc = 'O'
    }
    public enum CartridgeType
    {
        None = 0,
        Color,
        Black,
        Both
    }

    public enum ColorType
    {
        Graphics = 0,
        Photos,
        NotSupported = 0xffff
    }
    
    public enum ColorTable
    {
        Table1 = 1,
        Table2,
        Table3,
        Table4,
        Table5,
        Table6,
        NotSupported = 0xffff
    }

    public enum CartridgeInfoType
    {
       CARTRIDGE_INFO_STILL_READING=0,
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
    }

}