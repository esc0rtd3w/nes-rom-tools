Erosion v.3 by Syizm
	Syizm@yahoo.com
	http://www.geocities.com/syizm/

-If you experience any problems, bugs, or anything that you may find abnormal, please send me an e-mail discribing the situation.

[Source Code:]

The source code for version 1 can be downloaded at www.zophar.net under the Utilities>General section.

[Discription:]

Erosion v.3 is a program that will corrupt certain parts of a file.  The results can be interesting, especially if you use the right kind of file.  It's mainly intended to find the ranges of data within a file that contain the specific data you're seeking.  For example, it can be used to find level layouts in a ROM Dump, character information in a save state, etc.

Here are the features:
-Choose between single byte and integer corruption.
-Choose a starting and ending offset for more controlled corrupting.
-Choose a replacement value, either set, random, slopes, set values, increasing or decreasing values.
-Ability to do specific replacements.  For example, as you corrupt the file, if you only want bytes with the value "35" corrupted, then it will only corrupt the bytes containing the value 35.  This is very useful for savestate hacking.
-Ability to replace bytes within a range - for example, 30 to 50.  All bytes with that value will be replaced.
-Ability to jump by "powers".  You can set this value to 1000 and it will only corrupt every 1000 bytes (1 KB), set to 10 and it corrupts every 10 bytes.
-Added option to backup the file.
-Ability to restore the original file.
-Option to log the data that has been corrupted and save that information to a text file.

Thanks,
Syizm [aka S. T.]