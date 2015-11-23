using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace PTRobotUserControl
{
    public delegate UInt32 OpenCloseCallBack(uint nDriveID, uint nAction);


    class PTRobot_DLL
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
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_Initialize();

        //PTRobot_Destroy()
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_Destroy();

        // PTRobot_SetupDebugging
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_SetupDebugging(
            [MarshalAs(UnmanagedType.LPStr)] string szDbgFile,
            UInt32 dwDebugLvl,
            [MarshalAs(UnmanagedType.LPStr)] string szTraceFile);

        // PTRobot_EnumRobots
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_EnumRobots(
            ref uint nRobots, ref uint pnNumRobots );

        // PTRobot_EnumDrives
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_EnumDrives(
            uint nRobotID, ref uint nDriveIDs, ref uint nNumDrives);

        // PTRobot_GetRobotInfo
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_GetRobotInfo(
            uint nRobotID, [In, Out] RobotInfo myRobotInfo);

        // PTRobot_GetDriveInfo
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_GetDriveInfo(
            uint nRobotID, [In, Out] DriveInfo myDriveInfo);

        // PTRobot_GetRobotStatus
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_GetRobotStatus(
            uint nRobotID, [In, Out] RobotStatus myRobotStatus);

        // PTRobot_GetRobotStatus2
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_GetRobotStatus2(
            uint nRobotID, [In, Out] RobotStatus2 myRobotStatus2);

        // PTRobot_LoadDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_LoadDrive(
            uint nRobotID, uint nDriveID, uint nFromLocation, uint nClearDrive);

        // PTRobot_LoadPrinter
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_LoadPrinter(
                                    uint nRobotID, uint nFromLocation);

        // PTRobot_LoadPrinterFromDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_LoadPrinterFromDrive(
                                    uint nRobotID, uint nDriveID);

        // PTRobot_UnLoadDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_UnLoadDrive(
                                    uint nRobotID, uint nDriveID, uint nToLocation);

        // PTRobot_UnLoadPrinter
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_UnLoadPrinter(
                                            uint nRobotID, uint nToLocation);

        // PTRobot_MoveDiscBetweenLocations
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_MoveDiscBetweenLocations(
                                            uint nRobotID, uint nFromLocation, uint nToLocation);

        // PTRobot_SetRoboticDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_SetRoboticDrive(
            uint nRobotID, uint nDriveID, uint nColumnIndex, uint nRowIndex);

        // PTRobot_SetOpenCloseFunction
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_SetOpenCloseFunction(
                                        OpenCloseCallBack x);

        // PTRobot_GetManufactureInfo
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_GetManufactureInfo(
            uint nRobotID, [In, Out] ManufactureInfo myManufactureInfo);

        // PTRobot_GetSureThingPreview
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_GetSureThingPreview(
                    [MarshalAs(UnmanagedType.LPStr)] string sSureThingFile,         
                    [MarshalAs(UnmanagedType.LPStr)] string sOutputFile,         
                    uint nResolution);

        // PTRobot_PrintFile
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_PrintFile(
                    uint nRobotID,         
                    [MarshalAs(UnmanagedType.LPStr)] string sFile,         
                    uint nPrintIndex);

        // PTRobot_OpenCloseDrive
        [DllImport("PTRobot.dll", CharSet = CharSet.Ansi)]
        private static extern UInt32 PTRobot_OpenCloseDrive(
                    uint nDriveID,         
                    uint nAction);


        ////////////////////////////////////////////////////////////////////////
        /// <summary>
        //  Constructor
        /// </summary>
        public PTRobot_DLL()
        {
            m_OpenCloseCallBack = new OpenCloseCallBack(cbOpenCloseDrive); 
        }


        
        ////////////////////////////////////////////////////////////////////////
        //
        // DLL CALL WRAPPERS
        //
        ////////////////////////////////////////////////////////////////////////
        public uint Initialize()
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_Initialize();
                
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_Initialize() failed:\n" + e.Message);
            }
            
            return nValue;
        }

        public uint Destroy()
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_Destroy();
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_Destroy() failed:\n" + e.Message);
            }

            return nValue;
        }

        public uint SetupDebugging(string sDebugFile, uint nLevel, string sTraceFile )
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_SetupDebugging(sDebugFile, nLevel, sTraceFile);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_SetupDebugging() failed:\n" + e.Message);
            }
            
            return nValue;
        }


        public uint EnumRobots(ref uint nRobotArray, ref uint nNumRobots)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_EnumRobots(ref nRobotArray, ref nNumRobots);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_EnumRobots() failed:\n" + e.Message);
            }

            return nValue;
        }


        public uint EnumDrives(uint nRobotID, ref uint nDriveArray, ref uint nNumDrives)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_EnumDrives(nRobotID, ref nDriveArray, ref nNumDrives);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_EnumDrives() failed:\n" + e.Message);
            }

            return nValue;
        }



        public uint GetRobotInfo(uint nRobotID, ref RobotInfo myRobotInfo)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_GetRobotInfo( nRobotID, myRobotInfo);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_GetRobotInfo() failed:\n" + e.Message);
            }

            return nValue;
        }


        public uint GetDriveInfo(uint nRobotID, ref DriveInfo myDriveInfo)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_GetDriveInfo(nRobotID, myDriveInfo);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_GetDriveInfo() failed:\n" + e.Message);
            }

            return nValue;
        }

        public uint GetRobotStatus(uint nRobotID, ref RobotStatus myRobotStatus)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_GetRobotStatus(nRobotID, myRobotStatus);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_GetRobotStatus() failed:\n" + e.Message);
            }

            return nValue;
        }

        public uint GetRobotStatus2(uint nRobotID, ref RobotStatus2 myRobotStatus2)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_GetRobotStatus2(nRobotID, myRobotStatus2);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_GetRobotStatus2() failed:\n" + e.Message);
            }

            return nValue;
        }


        public uint SetRoboticDrive(uint nRobotID, uint nDriveID, 
                                        uint nColumnIndex, uint nRowIndex)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_SetRoboticDrive(nRobotID, nDriveID,
                                                nColumnIndex, nRowIndex);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_SetRoboticDrive() failed:\n" + e.Message);
            }

            return nValue;

        }


        public uint LoadDrive(uint nRobotID, uint nDriveID,
                                uint nFromLocation, uint nClearDrive)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_LoadDrive(nRobotID, nDriveID,
                                            nFromLocation, nClearDrive);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_LoadDrive() failed:\n" + e.Message);
            }

            return nValue;

        }


        public uint LoadPrinter(uint nRobotID, uint nFromLocation)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_LoadPrinter(nRobotID, nFromLocation);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_LoadPrinter() failed:\n" + e.Message);
            }

            return nValue;

        }

        public uint LoadPrinterFromDrive(uint nRobotID, uint nDriveID)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_LoadPrinterFromDrive(nRobotID, nDriveID);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_LoadPrinterFromDrive() failed:\n" + e.Message);
            }

            return nValue;

        }

        public uint UnLoadDrive(uint nRobotID, uint nDriveID, uint nToLocation)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_UnLoadDrive(nRobotID, nDriveID, nToLocation);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_UnLoadDrive() failed:\n" + e.Message);
            }

            return nValue;
        }

        public uint UnLoadPrinter(uint nRobotID, uint nToLocation)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_UnLoadPrinter(nRobotID, nToLocation);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_UnLoadPrinter() failed:\n" + e.Message);
            }

            return nValue;
        }

        public uint MoveDiscBetweenLocations(uint nRobotID, uint nFromLocation, uint nToLocation)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_MoveDiscBetweenLocations(nRobotID, nFromLocation, nToLocation);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_MoveDiscBetweenLocations() failed:\n" + e.Message);
            }

            return nValue;
        }


        public uint SetOpenCloseCallback(OpenCloseCallBack myOpenCloseCallback)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_SetOpenCloseFunction(myOpenCloseCallback);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_SetRoboticDrive() failed:\n" + e.Message);
            }

            return nValue;

        }


        public uint GetManufactureInfo(uint nRobotID, ref ManufactureInfo myManufactureInfo)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_GetManufactureInfo( nRobotID, myManufactureInfo);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_GetManufactureInfo() failed:\n" + e.Message);
            }

            return nValue;
        }


        
        public uint GetSureThingPreview(string sSureThingFile, string sOutputFile, uint nDPI)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_GetSureThingPreview(sSureThingFile, sOutputFile, nDPI);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_GetSureThingPreview() failed:\n" + e.Message);
            }

            return nValue;
        }


        public uint PrintFile(uint nRobotID, string sFile, uint nPrintIndex)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_PrintFile(nRobotID, sFile, nPrintIndex);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_GetSureThingPreview() failed:\n" + e.Message);
            }

            return nValue;
        }

        public uint OpenCloseDrive(uint nDriveID, uint nAction)
        {
            uint nValue = 0;
            try
            {
                nValue = PTRobot_OpenCloseDrive(nDriveID, nAction);
            }
            catch (Exception e)
            {
                MessageBox.Show("PTRobot_OpenCloseDrive() failed:\n" + e.Message);
            }

            return nValue;
        }
        ////////////////////////////////////////////////////////////////////////
        //
        // end of DLL CALL WRAPPERS
        //
        ////////////////////////////////////////////////////////////////////////




        ////////////////////////////////////////////////////////////////////////
        //
        // OpenClose CallBack from PTRobot DLL
        //   ie. PTRobot DLL calls back into here IF we have given it 
        //       this callback function.
        //
        ////////////////////////////////////////////////////////////////////////
        private static UInt32 cbOpenCloseDrive(uint nDriveID, uint nAction)
        {
            // NOTE: we will just show a dialog for user to open/close the drive
            // Normally, this function would call into the user's burn engine
            // to open/close the drive
            
            // TODO: WE NEED TO SEND A NOTIFICATION TO CALLER

            string myText;
            if (nAction == 0)
                myText = "Callback to OPEN driveID: " + nDriveID.ToString();
            else
                myText = "Callback to CLOSE driveID: " + nDriveID.ToString();

            MessageBox.Show(myText);

            return 0;
        }


        private OpenCloseCallBack m_OpenCloseCallBack;
    }
}
