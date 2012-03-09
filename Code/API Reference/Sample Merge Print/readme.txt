Surething Merge sample readme --

This is an example of a Surething print file using four Merge Text fields and a background bitmap.
This can be used with the PTRobot API call PTRobot_PrintFileWithMerge( ).


Basic points When using the sample PTRobotPrint.std with PTRobot_PrintFileWithMerge():
---------------------------------------------------------------------------------------
1. The file PTRobotMerge.txt is not needed for use with PTRobot_PrintFileWithMerge().
PTRobot_PrintFileWithMerge() will create the .txt file on-the-fly based on the strings
you pass into the function.  It is included here only for reference.

2. The file Background.jpg is included here for reference.  You can change it to anything you want,
but you should keep the dimensions square (e.g. 1417x1417 pixels).  You must specify the absolute path 
for this background image (.BMP, .JPG) when calling into PTRobot_PrintFileWithMerge().  You can name it
anything you want also; you must pass the correct name including path into PTRobot_PrintFileWithMerge().


Example:

dwRet = PTRobot_PrintFileWithMerge( hRobot, "c:\MyImages\PTRobotPrint.std", 5, 
					"Text #1", "Text #2", "Text #3", "Text #4", "c:\MyImages\Background.jpg" );


Also, you can leave off any of these fields if you want nothing printed in that location.
For example, if you wanted no background bitmap and no text on top you would write:

dwRet = PTRobot_PrintFileWithMerge( hRobot, "c:\MyImages\PTRobotPrint.std", 5, 
					"", "Text #2", "Text #3", "Text #4", "" );




NOTE--
If you want to Preview how the PTRobotPrint.std file will print you must do the following:
A. Put the files PTRobotPrint.std and PTRobotMerge.txt into the same directory as each other.
B. Modify the four text fields within PTRobotMerge.txt file to contain the text you want.
C. Copy the Background.jpg to a directory of your choice.  
   Modify PTRobotMerge.txt to specify that directory (if it is not C:\images\).
D. Open PTRobotPrint.std and click Preview in upper-right corner of Surething.

