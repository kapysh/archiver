#include "stdafx.h"
#include "PTRobotApp.h"
#include "PTRobotAppDlg.h"
#include "PTRobot.h"
#include <Winioctl.h>
#include <process.h>
#include "utility.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

//includes for copyRecursive
#include <stdio.h>
#include <windows.h>
#include <WinBase.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#define chunk (5*1024)

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_STRING 512

// move_disc takes 3 strings
// First: mode
//		Possible parameters:
//			"load"
//			"rip"
//			"helP"
// Second: bin
//		Possible parameters:
//			"left"
//			"right"
// Third: path
//		Format:
//			"C:\ArchiveMH\Archive\0102.03"
// Example: move_disc.exe load right
// Example: move_disc.exe rip "C:\\ArchiveMH\\Archive\\0102.03"


// checkDirStructure takes a char* type for the project number folder in archive,
// sorts the subfolders, and returns the highest subfolder# + 1 as a char*. Just
// ensures that all folders are created sequentially.
char* checkDirStructure(char* dest)
{
	WIN32_FIND_DATA info;
	HANDLE hwnd;
	char temp[1000] = "";
	int subFolders[1000];	//array to hold list of subfolders to sort
	int i = 0; //starting counter at 0
	int temp2;	//this is actually for the improved bubblesort

	strcpy(temp, dest); //copying the destination to temp
	strcat(temp, "\\*.*"); //adding the wildcard

	hwnd = FindFirstFile(temp, &info); //finding first file
	do{
		if(!strcmp(info.cFileName , ".")) continue;		//if its not cwd
		if(!strcmp(info.cFileName , "..")) continue;	//if its not parent dir
		if((info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) //if it's a directory
		{
			//converting TCHAR to char
			CT2CA pszConvertedAnsiString (info.cFileName);
			//converting char to string
			string sConverted(pszConvertedAnsiString);
			//converting string to integer and storing in int array
			subFolders[i] = atoi(sConverted.c_str());
			i++;	//incrementing counter
		}
		else;
	}
	while(FindNextFile(hwnd, &info)); //looping til no more files
	FindClose(hwnd);

	if(i > 1)	//if there are more than 1 subfolders, sort them
	{
		int k = 0;	//outer loop counter
		bool swapped = true;	//LCV to stop if sorted
		//now sorting the array of folders
		while((swapped == true) || (k < i))
		{
			for(int j = 0; j < i; j++)
				if (subFolders[j] < subFolders[j+1])
				{
					temp2 = subFolders[j+1];
					subFolders[j+1] = subFolders[j];
					subFolders[j] = temp2;
				}
				else
					swapped = false;
			k++;
		}
	}
	else;

	strcat(dest, "\\");	//adding '\' to original destination
	stringstream ss; //creating stringstream instance to convert back to string
	ss << subFolders[0]+1;	//incrementing folder to return 1 higher

	//returning dest + int->string->c_string... there is obviously a better way
	//to implement this, just quick dirty hacks so i can get back to my homework
	return strcat(dest, ss.str().c_str());
}

void copyFolder(char * src, char * dest)
{
	WIN32_FIND_DATA info;		//contains info found by FindFirstFile(), FindNextFile(), etc
	HANDLE hwnd;				
	char temp[1000] = "";
	char temp_1[1000] = "";

	char temp_src[1000];
	char temp_dest[1000];

	int in, out, i, x;
	void * buffer;

	strcpy(temp_1, src);
	strcat(temp_1, "\\*.*");

	CreateDirectory(dest, NULL);

	hwnd = FindFirstFile(temp_1, &info); //first param is input, second is WIN32_FIND_DATA dword, returns to a handle
	do{
		if(!strcmp(info.cFileName , ".")) continue;		//if its not cwd
		if(!strcmp(info.cFileName , "..")) continue;	//if its not parent dir

		strcpy(temp_src, src);		//copy src to temp_src
		strcat(temp_src, "\\");		//add on "\\" to nullify and add another level down
		strcat(temp_src, info.cFileName);	//add on Filename

		if((info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) //if it's a directory
		{
			strcpy(temp_dest, dest);	//make the destination folder the temp_dest
			strcat(temp_dest, "\\");	//add on "\\" to nullify and add another level down
			strcat(temp_dest, info.cFileName); //add on the filename - well in this case foldername
			printf("%s\n", temp_dest);
			CreateDirectory(temp_dest, NULL);
			copyFolder(temp_src, temp_dest); //copy folder temp_src to temp_dest
		}
		else
		{
			strcpy(temp, dest);
			strcat(temp, "\\");
			strcat(temp, info.cFileName);
			printf("%s\n", temp);

			buffer = malloc(chunk);
			in = (int)_open(temp_src, O_RDONLY|O_BINARY);
			out = (int)_open(temp, O_CREAT|O_WRONLY|O_BINARY|O_TRUNC);
			printf("%s %s\n", temp_src, temp);
			while (i = _read(in, buffer, chunk))
			{
				x = _write(out, buffer, i);
			}
			_close(in);
			_close(out);
			free(buffer);
		}
	}
	while(FindNextFile(hwnd, &info));
	FindClose(hwnd);
}

bool systemReady(HANDLE hRobot)
{
	PTRobotStatus2 myStatus2;
	PTRobotStatus myStatus;
	PTRobot_GetRobotStatus2(hRobot, &myStatus2);
	PTRobot_GetRobotStatus(hRobot, &myStatus);

	while ((myStatus2.dwSystemStateHW != 73)||(myStatus.dwSystemState != 0))
	{
		PTRobot_GetRobotStatus(hRobot, &myStatus);
		PTRobot_GetRobotStatus2(hRobot, &myStatus2);
		cout << "Waiting on robot..." << endl;
		Sleep(600);
	}
	return true;
}

int main(int argc, char* argv[])
{	
	DWORD dwRobots=10, dwRetVal = PTROBOT_OK, dwDrives = MAX_ROBOT_DRIVES, dwBin;
	HANDLE hRobots[10], hDrives[MAX_ROBOT_DRIVES];
	string sBin, sMode, sPath;
	char cPath[1000];

	sMode = argv[1];

	// Getting argument
	if(sMode == "load")		//if its a load sequence
	{	
		sBin = argv[2];
		if (sBin == "right")
			dwBin = 1;		// This is left-most bin
		else
			dwBin = 2;		// This is right-most bin
	}
	else if(sMode == "rip")		//else its a rip sequence, we need path and mode
	{
		strcpy(cPath, argv[2]);
	}
	else if(sMode == "help")
	{
		cout << "// move_disc takes 3 strings" << endl;
		cout << "// First: mode" << endl;
		cout << "//		Possible parameters:" << endl;
		cout << "//			load" << endl;
		cout << "//			rip" << endl;
		cout << "//			help" << endl;
		cout << "// Second: bin" << endl;
		cout << "//		Possible parameters:" << endl;
		cout << "//			left" << endl;
		cout << "//			right" << endl;
		cout << "// Third: path" << endl;
		cout << "//		Format:" << endl;
		cout << "//			C:\\\\ArchiveMH\\\\Archive\\\\0102.03" << endl;
		cout << "// Example: move_disc.exe load right" << endl;
		cout << "// Example: move_disc.exe rip C:\\\\ArchiveMH\\\\Archive\\\\0102.03" << endl;

		return 0;
	}

	
	// Initializing Robot
	PTRobot_Initialize();	// dwRetVal is the code received

	// Enumerating Robots
	PTRobot_EnumRobots(hRobots, &dwRobots);	//dwRobots is the numberof handles in the hRobots array, number of robots found
	PTRobot_EnumDrives(hRobots[0], hDrives, &dwDrives);

	//test move to load disc and then malfunction robot with destroy, so that tray doesn't close
	if (sMode == "load")
	{
		cout << "Loading drive with one disc, and then malfuntioning..." << endl;
		PTRobot_LoadDrive(hRobots[0], hDrives[0], dwBin, CLEARDRIVE_NO);
		PTRobot_SystemAction(hRobots[0], PTACT_CANCELCMD);
	}
	
	//test move to check discs
	else if (sMode == "rip")
	{
		cout << "Ripping disc...";
		char sSource[1000] = "E:\\";	//this is the drive letter of source
		PTRobot_OpenCloseDrive(hDrives[0], 1); //1 to close
		Sleep(1000);							//try to get rid of this later
		checkDirStructure(cPath);	//getting the subfolder to create
		copyFolder(sSource, cPath);	//doing the ripping
		PTRobot_UnLoadDrive(hRobots[0], hDrives[0], LOCATION_REJECT);
	}

	cout << "Exiting!" << endl;

	systemReady(hRobots[0]);
	PTRobot_Destroy();	
}