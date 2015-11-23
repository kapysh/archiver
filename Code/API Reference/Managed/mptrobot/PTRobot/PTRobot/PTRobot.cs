using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace PrimeraTechnology
{
    public delegate UInt32 OpenCloseCallBack(uint nDriveID, uint nAction);

    public class PTRobot
    {


        /* 
         * *** PTRobot DLL Function Prototypes ***
         * 
        DWORD WINAPI PTRobot_SetRobotOptions(HANDLE hRobot, DWORD dwRobotOptions);
        DWORD WINAPI PTRobot_GetRobotOptions(HANDLE hRobot, DWORD *pdwRobotOptions);
        DWORD WINAPI PTRobot_GetRobotInfo2(HANDLE hRobot, PTRobotInfo2 *pRobotInfo2);
        DWORD WINAPI PTRobot_GetRobotStatus(HANDLE hRobot, PTRobotStatus *pRobotStatus);
        DWORD WINAPI PTRobot_GetRobotStatus2(HANDLE hRobot, PTRobotStatus2 *pRobotStatus2);
        DWORD WINAPI PTRobot_PrintFileWithMerge(HANDLE hRobot, 
                                                    TCHAR * tszFile, 
                                                    DWORD dwNumMergeStrings,
                                                    ...);
        DWORD WINAPI PTRobot_SetPrinterSettings(HANDLE hRobot, PTPrinterSettings *pPrinterSettings);
        DWORD WINAPI PTRobot_GetPrinterSettings(HANDLE hRobot, PTPrinterSettings *pPrinterSettings);
        DWORD WINAPI PTRobot_KillSystemError(HANDLE hRobot, DWORD dwResetPrinter);
        DWORD WINAPI PTRobot_SystemAction(HANDLE hRobot, DWORD dwAction);
        DWORD WINAPI PTRobot_GetErrorString(HANDLE hRobot, 
                                            DWORD dwErrorNum, 
                                            WCHAR * pwszErrorString,  
                                            DWORD dwMaxLength, 
                                            DWORD dwLanguage);
        DWORD WINAPI PTRobot_GetMediaInfo(HANDLE hDrive, PTMediaInfo * pDiscInfo );
        */



        //////////////////////////////////////////////////////////////
        //
        // DLL IMPORTS 
        //
        //////////////////////////////////////////////////////////////
        //PTRobot_Init()
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_Initialize();

        //PTRobot_Destroy()
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_Destroy();

        // PTRobot_SetupDebugging
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetupDebugging(
            [MarshalAs(UnmanagedType.LPWStr)] string szDbgFile,
            UInt32 dwDebugLvl,
            [MarshalAs(UnmanagedType.LPWStr)] string szTraceFile);

        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetErrorString(
            UInt32 nRobotID,
            UInt32 nErrorNum,
            [MarshalAs(UnmanagedType.LPWStr)] string szErrorString,
            UInt32 nMaxLength,
            UInt32 nLanguage);


        // PTRobot_EnumRobots
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_EnumRobots(
            ref UInt32 nRobots, ref UInt32 pnNumRobots);

        // PTRobot_EnumDrives
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_EnumDrives(
            UInt32 nRobotID, ref UInt32 nDriveIDs, ref UInt32 nNumDrives);

        // PTRobot_EnumDrives
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_EnumDrivesWithList(
            UInt32 nRobotID, ref UInt32 nDriveIDs, ref UInt32 nNumDrives, ref UInt32 nRobotDriveIDs, ref UInt32 nNumRobotDrives);

        // PTRobot_GetRobotInfo
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetRobotInfo(
            UInt32 nRobotID, [In, Out] RobotInfo myRobotInfo);

        // PTRobot_GetRobotOptions
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetRobotOptions(
            UInt32 nRobotID, ref UInt32 myRobotOptions);

        // PTRobot_GetRobotOptions
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetRobotOptions(
            UInt32 nRobotID, UInt32 myRobotOptions);

        // PTRobot_GetRobotInfo
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetRobotInfo2(
            uint nRobotID, [In, Out] RobotInfo2 myRobotInfo2);

        // PTRobot_GetDriveInfo
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetDriveInfo(
            UInt32 nDriveID, [In, Out] DriveInfo myDriveInfo);

        // PTRobot_GetRobotStatus
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetRobotStatus(
            UInt32 nRobotID, [In, Out] RobotStatus myRobotStatus);

        // PTRobot_GetRobotStatus2
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetRobotStatus2(
            uint nRobotID, [In, Out] RobotStatus2 myRobotStatus2);

        // PTRobot_LoadDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_LoadDrive(
            UInt32 nRobotID, UInt32 nDriveID, UInt32 nFromLocation, UInt32 nClearDrive);

        // PTRobot_LoadPrinter
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_LoadPrinter(
                                    UInt32 nRobotID, UInt32 nFromLocation);

        // PTRobot_LoadPrinterFromDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_LoadPrinterFromDrive(
                                    UInt32 nRobotID, UInt32 nDriveID);

        // PTRobot_UnLoadDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_UnLoadDrive(
                                    UInt32 nRobotID, UInt32 nDriveID, UInt32 nToLocation);

        // PTRobot_UnLoadPrinter
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_UnLoadPrinter(
                                            UInt32 nRobotID, UInt32 nToLocation);

        // PTRobot_MoveDiscBetweenLocations
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_MoveDiscBetweenLocations(
                                            UInt32 nRobotID, UInt32 nFromLocation, UInt32 nToLocation);

        // PTRobot_SetRoboticDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetRoboticDrive(
            UInt32 nRobotID, UInt32 nDriveID, UInt32 nColumnIndex, UInt32 nRowIndex);

        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetRoboticDriveWithoutEnum(
            UInt32 nRobotID, UInt32 nDriveID, [MarshalAs(UnmanagedType.LPWStr)] string szDriveSerial, UInt32 nColumnIndex, UInt32 nRowIndex, int fProgramFlash);

        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetDriveSerialFromFlash(UInt32 hRobot, UInt32 dwColIndex,
                                UInt32 dwRowIndex, [MarshalAs(UnmanagedType.LPWStr)] string tszDriveSerial);


        // PTRobot_SetOpenCloseFunction
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetOpenCloseFunction(
                                        OpenCloseCallBack x);

        // PTRobot_GetMediaInfo
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetMediaInfo(
            UInt32 nDriveID, [In, Out] MediaInfo myMediaInfo);


        // PTRobot_GetManufactureInfo
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetManufactureInfo(
            UInt32 nRobotID, [In, Out] ManufactureInfo myManufactureInfo);

        // PTRobot_GetSureThingPreview
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetSureThingPreview(
                    [MarshalAs(UnmanagedType.LPWStr)] string sSureThingFile,
                    [MarshalAs(UnmanagedType.LPWStr)] string sOutputFile,
                   UInt32 nResolution);

        // PTRobot_PrintFile
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_PrintFileWithMerge2(
                    UInt32 nRobotID,
                    [MarshalAs(UnmanagedType.LPWStr)] string sFile,
                    bool fClearMergeList);

        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_PrintFileWithMergeFile(
                    UInt32 nRobotID,
                    [MarshalAs(UnmanagedType.LPWStr)] string sFile,
                    [MarshalAs(UnmanagedType.LPWStr)] string sMergeFile);

        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_AddMergeFields(
                    UInt32 nRobotID,
                    [MarshalAs(UnmanagedType.LPWStr)] string sField);

        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_ClearMergeList(
                    UInt32 nRobotID);

        // PTRobot_PrintFile
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_PrintFile(
                    UInt32 nRobotID,
                    [MarshalAs(UnmanagedType.LPWStr)] string sFile,
                   UInt32 nPrintIndex);

        // PTRobot_SetPrinterSettings
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetPrinterSettings(
                    UInt32 nRobotID,
                    [In, Out] PrinterSettings printerSettings);

        // PTRobot_GetPrinterSettings
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetPrinterSettings(
                    UInt32 nRobotID,
                    [In, Out] PrinterSettings printerSettings);

        // PTRobot_SetPrinterSettings2
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetPrinterSettings2(
                    UInt32 nRobotID,
                    [In, Out] PrinterSettings2 printerSettings2);

        // PTRobot_GetPrinterSettings2
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_GetPrinterSettings2(
                    UInt32 nRobotID,
                    [In, Out] PrinterSettings2 printerSettings2);

        // PTRobot_OpenCloseDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_OpenCloseDrive(
                    UInt32 nDriveID,
                    UInt32 nAction);

        // PTRobot_KillSystemError
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_KillSystemError(
                    UInt32 nRobotID,
                    UInt32 nResetPrinter);

        // PTRobot_SystemAction
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SystemAction(
                    UInt32 nRobotID,
                    UInt32 nAction);

        // PTRobot_SetApplicationID
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetApplicationID(
                    UInt32 nAppID);

        // PTRobot_SetPrintCopies
        [DllImport("PTRobot.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PTRobot_SetPrintCopies(
                    UInt32 nRobotID,
                    UInt32 dwCopies);

        
        ////////////////////////////////////////////////////////////////////////
        /// <summary>
        //  Constructor
        /// </summary>
        public PTRobot()
        {
            
        }



        ////////////////////////////////////////////////////////////////////////
        //
        // DLL CALL WRAPPERS
        //
        ////////////////////////////////////////////////////////////////////////
        public static PTRobotReturn Initialize()
        {
            uint nValue = 0;

            PTRobotReturn ret = PTRobotReturn.Ok;
            
            try
            {
                nValue = PTRobot_Initialize();
                ret = (PTRobotReturn)nValue;

            }
            catch (Exception)
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn Destroy()
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_Destroy();
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn SetupDebugging(string debugFile, UInt32 level, string traceFile)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_SetupDebugging(debugFile, level, traceFile);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn GetDriveSerialFromFlash(UInt32 robotID, UInt32 dwColIndex, UInt32 dwRowIndex, string serial )
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetDriveSerialFromFlash(robotID, dwColIndex, dwRowIndex, serial);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }


            return ret;
        }

        public static PTRobotReturn GetErrorString(UInt32 robotID, UInt32 errorNum, string errorString, UInt32 maxLength, UInt32 language)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetErrorString(robotID, errorNum, errorString, maxLength, language);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn EnumRobots(ref UInt32 robotArray, ref UInt32 numRobots)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_EnumRobots(ref robotArray, ref numRobots);
                ret = (PTRobotReturn)nValue;
            }
            catch (Exception)
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn EnumDrives(UInt32 robotID, ref UInt32 driveArray, ref UInt32 numDrives)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_EnumDrives(robotID, ref driveArray, ref numDrives);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }



        public static PTRobotReturn GetRobotInfo(UInt32 robotID, ref RobotInfo robotInfo)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetRobotInfo(robotID, robotInfo);
                ret = (PTRobotReturn)nValue;
            }
            catch (Exception)
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn SetRoboticDriveWithoutEnum(UInt32 robotID, UInt32 nDriveID, string sDriveSerial,  UInt32 col, UInt32 row, int fProgramFlash)
        {
            PTRobotReturn ret = PTRobotReturn.Ok;
            uint nValue = 0;
            try
            {
                nValue = PTRobot_SetRoboticDriveWithoutEnum(robotID, nDriveID, sDriveSerial, col, row, fProgramFlash);
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn GetRobotInfo2(UInt32 robotID, ref RobotInfo2 robotInfo2)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetRobotInfo2(robotID, robotInfo2);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn GetDriveInfo(UInt32 driveID, ref DriveInfo driveInfo)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetDriveInfo(driveID, driveInfo);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn GetMediaInfo(UInt32 driveID, ref MediaInfo mediaInfo)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetMediaInfo(driveID, mediaInfo);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn GetRobotStatus(UInt32 robotID, ref RobotStatus robotStatus)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetRobotStatus(robotID, robotStatus);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn GetRobotStatus2(UInt32 robotID, ref RobotStatus2 robotStatus2)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetRobotStatus2(robotID, robotStatus2);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn GetRobotOptions(UInt32 robotID, ref UInt32 robotOptions)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetRobotOptions(robotID, ref robotOptions);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }
        public static PTRobotReturn SetRobotOptions(UInt32 robotID, UInt32 robotOptoins)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_SetRobotOptions(robotID, robotOptoins);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn SetRoboticDrive(UInt32 robotID, UInt32 driveID,
                                        UInt32 columnIndex, UInt32 rowIndex)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_SetRoboticDrive(robotID, driveID,
                                                columnIndex, rowIndex);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;

        }


        public static PTRobotReturn LoadDrive(UInt32 robotID, UInt32 driveID,
                                DiscLocation fromLocation, ClearDrive clearDrive)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_LoadDrive(robotID, driveID,
                                            Convert.ToUInt32(fromLocation), Convert.ToUInt32(clearDrive));
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;

        }


        public static PTRobotReturn LoadPrinter(UInt32 robotID, DiscLocation fromLocation)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_LoadPrinter(robotID, Convert.ToUInt32(fromLocation));
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;

        }

        public static PTRobotReturn LoadPrinterFromDrive(UInt32 robotID, UInt32 driveID)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_LoadPrinterFromDrive(robotID, driveID);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;

        }

        public static PTRobotReturn UnLoadDrive(UInt32 robotID, UInt32 driveID, DiscLocation toLocation)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_UnLoadDrive(robotID, driveID, Convert.ToUInt32(toLocation));
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn UnLoadPrinter(UInt32 robotID, DiscLocation toLocation)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_UnLoadPrinter(robotID, Convert.ToUInt32(toLocation));
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn MoveDiscBetweenLocations(UInt32 robotID, DiscLocation fromLocation, DiscLocation toLocation)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_MoveDiscBetweenLocations(robotID, Convert.ToUInt32(fromLocation), Convert.ToUInt32(toLocation));
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn SetOpenCloseCallback(OpenCloseCallBack myOpenCloseCallback)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;

            try
            {
                nValue = PTRobot_SetOpenCloseFunction(myOpenCloseCallback);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;

        }


        public static PTRobotReturn GetManufactureInfo(UInt32 robotID, ref ManufactureInfo manufactureInfo)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetManufactureInfo(robotID, manufactureInfo);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn GetPrinterSettings(UInt32 robotID, ref PrinterSettings printerSettings)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetPrinterSettings(robotID, printerSettings);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn SetPrinterSettings(UInt32 robotID, ref PrinterSettings printerSettings)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_SetPrinterSettings(robotID, printerSettings);
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn GetPrinterSettings2(UInt32 robotID, ref PrinterSettings2 printerSettings2)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetPrinterSettings2(robotID, printerSettings2);
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn SetPrinterSettings2(UInt32 robotID, ref PrinterSettings2 printerSettings2)
        {
            uint nValue = 0;

            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_SetPrinterSettings2(robotID, printerSettings2);
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn GetSureThingPreview(string sureThingFile, string outputFile, uint DPI)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_GetSureThingPreview(sureThingFile, outputFile, DPI);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn PrintFile(uint robotID, string file, uint printIndex)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_PrintFile(robotID, file, printIndex);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn PrintFileWithMerge2(uint robotID, string file, bool fClearList)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_PrintFileWithMerge2(robotID, file, fClearList);
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn AddMergeFields(uint robotID, string sField)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_AddMergeFields(robotID, sField);
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn PrintFileWithMergeFile(uint robotID, string file, string mergeFile)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_PrintFileWithMergeFile(robotID, file, mergeFile);
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }
        

        public static PTRobotReturn OpenCloseDrive(uint driveID, DriveAction action)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_OpenCloseDrive(driveID, Convert.ToUInt32(action));
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn KillSystemError(UInt32 robotID, UInt32 resetPrinter)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_KillSystemError(robotID, resetPrinter);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        public static PTRobotReturn SystemAction(UInt32 robotID, SystemActions action)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_SystemAction(robotID, Convert.ToUInt32(action));
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }


        public static PTRobotReturn SetPrintCopies(UInt32 robotID, UInt32 dwCopies)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_SetPrintCopies(robotID, dwCopies);
                ret = (PTRobotReturn)nValue;
            }
            catch
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }



        public static PTRobotReturn SetApplicationID(UInt32 nAppID)
        {
            uint nValue = 0;
            PTRobotReturn ret = PTRobotReturn.Ok;
            try
            {
                nValue = PTRobot_SetApplicationID( nAppID);
                ret = (PTRobotReturn)nValue;
            }
            catch 
            {
                ret = PTRobotReturn.Internal;
            }

            return ret;
        }

        
        ////////////////////////////////////////////////////////////////////////
        //
        // end of DLL CALL WRAPPERS
        //
        ////////////////////////////////////////////////////////////////////////
    }
}
