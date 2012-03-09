![](https://github.com/admwazo/archiver/blob/master/photo.JPG?raw=true)

MH Disc Archiver v1.3
=====================

This is a project to automate the archival of MH Project Discs. The program logic is broken down to five stages:

1. move one disc onto staging area
2. take a picture of disc cover
3. OCR disc cover
4. build directory structures based on that output
5. archive disc data

Unabridged Process
==================

	human loads 25 frontfaced discs onto right, left, or both spindles
	human executes mh_archive.vbs and follows the prompts to enter the number of discs in the left and right trays
	vbs controls camera with WIA to snap pic of disc cover
	vbs uses ImageMagick to translate jpg into lossless tiff
	vbs kicks on acrobat to execute basicplugin which runs ocr
	vbs runs javascript on acrobat to search for project number
	if project number not found,
		image1 is rotated CW 15*, ocr'd, and searched again
		if project number not found 
			image1 is rotated CCW 15*, ocr'd, and searched again
			if project number not found
				disc number (3 for instance) is recorded as a failure
	if project number is found
		vbs moves disc cover image into corresponding (and existing) project folder
		vbs calls move_disc.exe with a rip command
		move_disc.exe rips data off of disc and stores files in corresponding (and existing) project folder
		move_disc.exe drops processed disc into front tray
		when all 50 cd's are processed, human checks failure folder, finds corresponding cd's, processes them manually, reloads 50 cd's

Requirements
============

	required software:
		acrobat x pro v10.1.5
		c++ libraries
		PTRobot.dll
		mhArchive.vbs
		move_disc.exe
		microsoft excel 2007

	required hardware:
		computer
		bravo pro disc duplicator
		nikon d70

	required files:
		excel spreadsheet of project files

