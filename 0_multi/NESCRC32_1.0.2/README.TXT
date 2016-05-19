NESCRC32 v1.0.1
Batch NES ROM CRC-32 Validation
By: Richard Willson

THIS PROGRAM IS PUBLIC-DOMAIN SOFTWARE.

Permission to use, copy, modify, distribute and sell this software and its documentation for
any purpose is hereby granted without fee, provided that credit is given to Richard Willson.
I make no representations about the suitability of this software for any purpose.
It is provided "as is" without express or implied warranty. 

The CRC-32 calculation functions were copied from Craig Bruce's CRC-32 calculator program.
I have included his original source code, crc32.c, so that he
is credited for his work, and not blamed for the modifications I have made to it.

----------

This is a command-line program, that can be used to validate your rom collection. 

It goes through a directory of .nes rom files, and for each file, it: 
Strips off the 16 byte iNES header. 
Gets the CRC-32 of the rest of the rom. 
Searches in a hash file for a match. 
The roms of any hashes that could not be found, are Renamed or Moved, based on commandline options. 

I just get the hash file from http://bootgod.dyndns.org:7777/xml.php
You can add your homebrew roms to this file, since any file with the hashes in it will work;
whether they are manually created, NES Cart Database, NESHead Database, etc...


Usage:  nescrc32 [-?] | [-w<dir>] [-m<dir>] [-r<mask>] [-f<name>]

    -?          show this help
    -w<dir>     working directory (default: current working directory)
    -m<dir>     move MISSING roms to a different directory (optional)
    -r<mask>    rename MISSING roms (eg: *_bad.* | *.bad)  (optional)
    -f<name>    file containing valid CRC-32 hashes of known good roms
                (default: the first file that matches *.xml)


Note 1: The log file, NESCRC32.LOG will be created, if it doesn't exist, or appended to, if it does.
This is really useful, if you have a lot of roms, and want to see what happened.
I couldn't be bothered to add a bunch of code, to add the option to disable this, then check it all throughout my code, for every message.
It is for informational use only, so feel free to delete it.

Note 2: If a file or directory doesn't seem to work, try using quotation marks.

Note 3: When using relative directories with Rename and/or Move, and the -w option is used,
then the relative directory is based on the working directory, not the current working directory on your system.

Note 4: Relative directories don't seem to be working with the -f option.
They would otherwise be based on the current working directory on your system.
Absolute directories do work, with quotation marks when necessary.
You can't use a mask for the -f option, a file name is assumed. (eg: \hashfiles\*.xml does not work)
I don't see why hash files shouldn't just be placed in the NESCRC32 directory.


Example 1:
nescrc32 -?
Displays usage help screen

Example 2:
nescrc32
Looks in the current working directory for *.NES files
Looks in the current working directory for the first file matching the mask *.xml
Displays FOUND or MISSING to screen

Example 3:
nescrc32 -w\emu\nes\roms -m\emu\nes\roms\missing -r*.BAD -f"NesCarts (2011-02-26).xml"
Looks in the directory \emu\nes\roms\ for *.NES files
Looks in the current working directory for "NesCarts (2011-02-26).xml"; the quotes aren't required for names without spaces
Any MISSING roms are renamed based on the *.BAD mask, then moved to \emu\nes\roms\missing\  (I could have used the option "-mmissing")
Displays FOUND or MISSING to screen


I have included my source code, however it has only been tested to compile on my system:
Windows XP (32-bit), using gcc.  It will not compile, unaltered, under a non-windows system.
If anyone has updates, ports to other systems, patches, constructive criticism, etc...
feel free to e-mail me at: keyboard_smasher@hotmail.com

This package is hosted on my DropBox account.
For the latest version, visit:
http://dl.dropbox.com/u/29432448/index.html

I included an up-to-date NES Cart Database hash file, when making this package.
For updates, this file can be downloaded from here:
http://bootgod.dyndns.org:7777/xml.php

It is public domain, so feel free to do whatever you want with it.


History:
v1.0.2	Date:		May  18, 2011
	Updated README.TXT file

v1.0.1
	Date:		May  17, 2011
	Updated README.TXT file
	Corrected minor spelling mistakes
	Added some messages/errors, and Changed some messages/error
	If a file name is known, then it should be output before calling an error,
		so the user knows the name of the offending file, and not have to go by the file before it.

v1.0
	Start:		May   6, 2011
	End:		May  16, 2011
	Get any options, including the working directory, from the command-line.
	For each file:
		Strip off the 16 byte iNES header.
		Get CRC-32
		Search in *.xml (for this version, I'm just checking for presence)
		Any MISSING roms are Renamed or Moved, based on command-line options
