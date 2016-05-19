/*******************************************\
*                                           *
*  Batch NES ROM CRC32 Validation v1.0.1    *
*  By: Richard Willson                      *
*                                           *
*  THIS PROGRAM IS PUBLIC-DOMAIN SOFTWARE.  *
*                                           *
*  The CRC-32 calculation functions were    *
*  copied from Craig Bruce's program.       *
*  I have included his original source      *
*  code, so that he may not be blamed for   *
*  the modifications I have made to it.     *
*                                           *
\*******************************************/

/*
	History:
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
			Search for match in hash file (for this version, I'm just checking for presence)
			Any MISSING roms are Renamed or Moved, based on command-line options
*/

#define VERSION "v1.0.1"
#define BUFFER_SIZE  8192

#ifdef _WIN32
#define DIR_SEP_STR "\\"
#define DIR_SEP_CHR '\\'
#include <conio.h>		// getch
#include <direct.h>		// _chdir, _getdir
#include <dirent.h>		// closedir, opendir, readdir, readdir_r, rewinddir, seekdir, telldir
#include <sys/types.h>	// ino_t (for dirent.h)
#else
#define DIR_SEP_STR "/"
#define DIR_SEP_CHR '/'
#include <termios.h>
#include <unistd.h>
#endif
#include <ctype.h>		// tolower
#include <stdint.h>		// uint32_t (was unsigned long)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(const char * Message);
void printhelp();
void pressanykey();
#ifndef _WIN32
int mygetch();
#endif
int validate(uint32_t CRC32);
uint32_t craig_bruce(const char * argv);
void Crc32_ComputeFile( FILE *file, uint32_t *outCrc32 );
static uint32_t Crc32_ComputeBuf( uint32_t inCrc32, const void *buf, size_t bufLen );

FILE * LogFile = NULL;				// file stream for log file
FILE * File = NULL;					// defines a file stream
DIR * DirectoryListing = NULL;		// defines a directory stream
char * MemBuffer = NULL;			// allocated memory buffer

int main(int argc, char * argv[])
{
	int i = 0, j = 0, k = 0, l = 0;
	const char LogName[13] = "NESCRC32.LOG";
/*
	command line options:
		-w Working Directory for roms
		-m Move-To Directory for bad roms
		-r Rename Mask
		-f File containing Valid CRC-32 hashes of known good roms
*/
	int w = 0, m = 0, r = 0, f = 0;
	char Option[3] = {0, 0, 0};
	char cwd[_MAX_PATH] = "";
	char WorkingDirectory[_MAX_PATH] = "";
	char MoveDirectory[_MAX_PATH] = "";
	char RenameMask[_MAX_PATH] = "";
	char RenameName[_MAX_PATH] = "";			// New name for MISSING .NES file, based on Rename Mask
	char FileName[_MAX_PATH] = "";				// OK, so I'm not creative, but File_containing_Valid_CRC-32_hashes seemed a little long.
	char FileDirectory[_MAX_PATH] = "";			// Parse directory from FileName, to help resolve a relative directory (is this needed?)
	char FileFull[_MAX_PATH] = "";				// Used for merging FileDirectory and FileName
	char MoveFull[_MAX_PATH] = "";				// Used for move and rename
	char * Pos1 = NULL;							// Sub-String 1 start position
	char * Pos2 = NULL;							// Sub-String 2 start position
	char * Pos3 = NULL;							// Sub-String 3 start position
	struct dirent *DirectoryEntry;				// dirent structure that defines a directory entry
	int Current = 0, Total = 0;					// Current and Total number of *.nes files used for progress
	uint32_t CRC32 = 0;							// Receive 32-bit CRC-32 from Craig Bruce's function
	long FileSize = 0;							// Size of File
	size_t FileRead = 0;						// Used with fread for error checking

	// Read Command Line Parameters
	for (i = 1; i < argc; i++)
	{
		Option[0] = argv[i][0];
		Option[1] = argv[i][1];

		if (strcmp("-?", Option) == 0)
		{
			printhelp();
			pressanykey();
			exit(0);
		}
		else if ((strcmp("-w", Option) == 0) && w == 0)
		{
			if (argv[i][2] != '\0')
			{
				w++;
				strcpy(WorkingDirectory, &argv[i][2]);
			}
		}
		else if ((strcmp("-m", Option) == 0) && m == 0)
		{
			if (argv[i][2] != '\0')
			{
				m++;
				strcpy(MoveDirectory, &argv[i][2]);
			}
		}
		else if ((strcmp("-r", Option) == 0) && r == 0)
		{
			if (argv[i][2] != '\0')
			{
				r++;
				strcpy(RenameMask, &argv[i][2]);
			}
		}
		else if ((strcmp("-f", Option) == 0) && f == 0)
		{
			if (argv[i][2] != '\0')
			{
				f++;
				strcpy(FileName, &argv[i][2]);
			}
		}
	}

	// Open Log File for append
	if ((LogFile = fopen(LogName, "a")) == NULL)
	{
		error("Could not open the log file.");
	}

	if (fprintf(LogFile, "Start of a new NES ROM CRC-32 validation check.\n") < 0)
	{
		error("Could not write to log file.");
	}

	// Ensure variables are filled, and that directories exist, before moving on.
#ifdef _WIN32
	_getcwd(cwd, _MAX_PATH);
#else
#endif
	if (strcmp(cwd, "") == 0)
	{
		error("Could not get the current working directory.");
	}

	if (w == 0)
	{
		strcpy(WorkingDirectory, ".");
	}

#ifdef _WIN32
	if (_chdir(WorkingDirectory) == -1)
#else
#endif
	{
		error("Could not change to the working directory.");
	}

#ifdef _WIN32
	_getcwd(WorkingDirectory, _MAX_PATH);
#else
#endif
	if (strcmp(WorkingDirectory, "") == 0)
	{
		error("Could not get the working directory.");
	}

	strcat(WorkingDirectory, DIR_SEP_STR);

	if (m != 0)
	{
#ifdef _WIN32
		_mkdir(MoveDirectory);
		if (_chdir(MoveDirectory) == -1)
#else
#endif
		{
			error("Could not create the move-to directory.");
		}

#ifdef _WIN32
		_getcwd(MoveDirectory, _MAX_PATH);
#else
#endif
		if (strcmp(MoveDirectory, "") == 0)
		{
			error("Could not get the move-to directory.");
		}

		strcat(MoveDirectory, DIR_SEP_STR);
	}

	if (f == 0)
	{
		// find first instance of *.xml
		strcpy(FileName, "*.xml");
		strcpy(FileDirectory, cwd);
		strcat(FileDirectory, DIR_SEP_STR);

		DirectoryListing = opendir(FileDirectory);
		if (DirectoryListing != NULL)
		{
			while ((DirectoryEntry = readdir(DirectoryListing)) != NULL)
			{
				if ((Pos1 = strrchr(DirectoryEntry->d_name, '.')) != NULL)
				{
					if (strstr((Pos1+1), "xml") != NULL)
					{
						strcpy(FileName, DirectoryEntry->d_name);
						break;
					}
				}
			}
			if (closedir(DirectoryListing) != 0)
			{
				error("Could not close the hash directory.");
			}
			DirectoryListing = NULL;
		}
	}
	else
	{
		// check if FileName contains a path, and resolve that
		Pos1 = strrchr(FileName, DIR_SEP_CHR);
		if (Pos1 != NULL)
		{
			strncpy(FileDirectory, FileName, (Pos1-FileName+1));
			strcpy(FileName, (Pos1+1));

#ifdef _WIN32
			if (_chdir(FileDirectory) == -1)
#else
#endif
			{
				error("Could not find the hash file directory.");
			}
		}
		else
		{
			strcpy(FileDirectory, cwd);
			strcat(FileDirectory, DIR_SEP_STR);
		}
	}

	// Open CRC-32 File
	strcpy(FileFull, FileDirectory);
	strcat(FileFull, FileName);
	if ((File = fopen(FileFull, "r")) == NULL)
	{
		error("Could not open the hash file.");
	}

	// Find Size of File by seeking to the End of File, and reading the position
	fseek(File, 0, SEEK_END);
	FileSize = ftell(File);

	// Allocate enough memory to hold the entire file in memory
	MemBuffer = (char *) malloc(sizeof(char) * FileSize);
	if (MemBuffer == NULL)
	{
		error("Could not allocate enough memory to load the hash file.");
	}

	// Load the CRC-32 File into memory, and close File.
	fseek(File, 0, SEEK_SET);
	FileRead = fread(MemBuffer, (sizeof(char) * FileSize), 1, File);
	if (FileRead == 0)
	{
		if (ferror(File))
		{
			error("Could not read the hash file.");
		}
		else
		{
			error("Empty hash file.");
		}
	}

	// Close CRC-32 File
	if (fclose(File) == EOF)
	{
		error("Could not close the hash file.");
	}
	File = NULL;

	// Main Loop
	DirectoryListing = opendir(WorkingDirectory);
	if (DirectoryListing != NULL)
	{
		// Count matches for "*.nes"
		while ((DirectoryEntry = readdir(DirectoryListing)) != NULL)
		{
			if ((Pos1 = strrchr(DirectoryEntry->d_name, '.')) != NULL)
			{
				if ((strcmp(DirectoryEntry->d_name, ".") != 0) && (strcmp(DirectoryEntry->d_name, "..") != 0))
				{
					if ((tolower(Pos1[1]) == 'n') && (tolower(Pos1[2]) == 'e') && (tolower(Pos1[3]) == 's'))	// crappy tolower "NES"
					{
						Total++;
					}
				}
			}
		}

		// Loop through directory, passing to the CRC-32 routine, search through FileName, and handling -r and -m
		if (Total > 0)
		{
			rewinddir(DirectoryListing);
			while ((DirectoryEntry = readdir(DirectoryListing)) != NULL)
			{
				if ((Pos1 = strrchr(DirectoryEntry->d_name, '.')) != NULL)
				{
					if ((strcmp(DirectoryEntry->d_name, ".") != 0) && (strcmp(DirectoryEntry->d_name, "..") != 0))	
					{
						if ((tolower(Pos1[1]) == 'n') && (tolower(Pos1[2]) == 'e') && (tolower(Pos1[3]) == 's'))	// crappy tolower "NES"
						{
							Current++;
							strcpy(FileFull, WorkingDirectory);
							strcat(FileFull, DirectoryEntry->d_name);
							CRC32 = craig_bruce(FileFull);
							printf("%5d / %5d (%3d%%) - ", Current, Total, (Current * 100 / Total));
							if (fprintf(LogFile, "%5d / %5d (%3d%%) - ", Current, Total, (Current * 100 / Total)) < 0)
							{
								printf("%s\n", DirectoryEntry->d_name);
								error("Could not write to log file.");
							}
							if (validate(CRC32))
							{
								printf("FOUND\t");
								if (fprintf(LogFile, "FOUND\t") < 0)
								{
									printf("%s\n", DirectoryEntry->d_name);
									error("Could not write to log file.");
								}
							}
							else
							{
								printf("MISSING\t");
								if (fprintf(LogFile, "MISSING\t") < 0)
								{
									printf("%s\n", DirectoryEntry->d_name);
									error("Could not write to log file.");
								}

								// Process rename first, so WorkingDirectory doesn't have to change, like it would if it were done after a move.
								if (r != 0)
								{
									// Parse RenameMask
									if ((Pos2 = strrchr(RenameMask, '.')) == NULL)
									{
										Pos2 = (RenameMask + strlen(RenameMask) - 1);	// If there is no extension, set Pos2 to the NULL
									}

									i = 0;	// index into RenameName
									j = 0;	// index into RenameMask
									k = 0;	// index into d_name
									l = 0;	// counter
									if ((Pos1 = strchr(RenameMask, '*')) != NULL)
									{
										if (Pos1 > Pos2)
										{
											printf("%s\n", DirectoryEntry->d_name);
											if (fprintf(LogFile, "%s\n", DirectoryEntry->d_name) < 0)
											{
												error("Could not write to log file.");
											}
											error("The Rename Mask must have exactly one * before the file extension.");
										}
										else
										{
											for (l = 0; l < (Pos1 - RenameMask); l++)
											{
												RenameName[i] = RenameMask[j];
												i++;
												j++;
											}
											j++;	// Get past *
											while ((DirectoryEntry->d_name[k] != '.') && (DirectoryEntry->d_name[k] != '\0'))
											{
												RenameName[i] = DirectoryEntry->d_name[k];
												i++;
												k++;
											}
											while ((RenameMask[j] != '.') && (RenameMask[j] != '\0'))
											{
												RenameName[i] = RenameMask[j];
												i++;
												j++;
											}
										}
									}
									else
									{
										printf("%s\n", DirectoryEntry->d_name);
										if (fprintf(LogFile, "%s\n", DirectoryEntry->d_name) < 0)
										{
											error("Could not write to log file.");
										}
										error("The Rename Mask must have exactly one * before the file extension.");
									}

									Pos1 = strrchr(RenameMask, '*');
//									Pos2 = strrchr(RenameMask, '.');
									Pos3 = (RenameMask + strlen(RenameMask) - 1);
									if ((Pos1 >= Pos2) && (Pos1 <= Pos3) && (Pos2 != Pos3))
									{
										for (l = 0; l < (Pos1 - Pos2); l++)
										{
											RenameName[i] = RenameMask[j];
											i++;
											j++;
										}
										j++;	// Get past *
										k++;	// Get past .
										while (DirectoryEntry->d_name[k] != '\0')
										{
											RenameName[i] = DirectoryEntry->d_name[k];
											i++;
											k++;
										}
									}
									while (RenameMask[j] != '\0')
									{
										RenameName[i] = RenameMask[j];
										i++;
										j++;
									}
									RenameName[i] = '\0';
									strcpy(MoveFull, WorkingDirectory);
									strcat(MoveFull, RenameName);
									if(rename(FileFull, MoveFull) != 0)
									{
										printf("%s\n", DirectoryEntry->d_name);
										if (fprintf(LogFile, "%s\n", DirectoryEntry->d_name) < 0)
										{
											error("Could not write to log file.");
										}
										error("Could not move MISSING .NES file.");
									}
								}

								if (m != 0)
								{
									if (r != 0)
									{
										strcpy(FileFull, MoveFull);
										strcpy(MoveFull, MoveDirectory);
										strcat(MoveFull, RenameName);
									}
									else
									{
										strcpy(MoveFull, MoveDirectory);
										strcat(MoveFull, DirectoryEntry->d_name);
									}

									if(rename(FileFull, MoveFull) != 0)
									{
										printf("%s\n", DirectoryEntry->d_name);
										if (fprintf(LogFile, "%s\n", DirectoryEntry->d_name) < 0)
										{
											error("Could not write to log file.");
										}
										error("Could not move MISSING .NES file.");
									}
								}
							}
							printf("0x%08lX %s\n", CRC32, DirectoryEntry->d_name);
							if (fprintf(LogFile, "0x%08lX %s\n", CRC32, DirectoryEntry->d_name) < 0)
							{
								error("Could not write to log file.");
							}
						}
					}
				}
			}
			printf("\n");
			if (fprintf(LogFile, "\n") < 0)
			{
				error("Could not write to log file.");
			}
		}
		else
		{
			error("There are no .NES files in the working directory.");
		}

		// Close Directory Listing
		if (closedir(DirectoryListing) != 0)
		{
			error("Could not close the working directory.");
		}
		DirectoryListing = NULL;
	}
	else
	{
		error("Could not open the working directory.");
	}

	// I like to have some space between validations.
	if (fprintf(LogFile, "\n\n") < 0)
	{
		error("Could not write to log file.");
	}

	// Close Log File
	if (fclose(LogFile) == EOF)
	{
		error("Could not close the log file.");
	}
	LogFile = NULL;

	// Free memory allocation for hash file
	free(MemBuffer);
	MemBuffer = NULL;

	pressanykey();

	return 0;
}

void error(const char * Message)
{
	printf("Error: %s\n\n", Message);

	if (LogFile != NULL)
	{
		fprintf(LogFile, "Error: %s\n\n", Message);
		fclose(LogFile);
		LogFile = NULL;
	}

	if (File != NULL)
	{
		fclose(File);
		File = NULL;
	}

	if (DirectoryListing != NULL)
	{
		closedir(DirectoryListing);
		DirectoryListing = NULL;
	}

	if (MemBuffer != NULL)
	{
		free(MemBuffer);
		MemBuffer = NULL;
	}

	pressanykey();
	exit(1);
}

void printhelp()
{
	printf("\nNESCRC32 ");
	printf(VERSION);
	printf("\n\n");
	printf("Usage:  nescrc32 [-?] | [-w<dir>] [-m<dir>] [-r<mask>] [-f<name>]\n\n");
	printf("    -?          show this help\n");
	printf("    -w<dir>     working directory (default: current working directory)\n");
	printf("    -m<dir>     move MISSING roms to a different directory (optional)\n");
	printf("    -r<mask>    rename MISSING roms (eg: *_bad.* | *.bad)  (optional)\n");
	printf("    -f<name>    file containing valid CRC-32 hashes of known good roms\n");
	printf("                (default: the first file that matches *.xml)\n");
	printf("\n\n");

	return;
}

void pressanykey()
{
	printf("Press any key to continue...");

#ifdef _WIN32
	getch();
#else
	mygetch();
#endif

	fflush(stdin);
	printf("\n\n");

	return;
}

#ifndef _WIN32
int mygetch()
{
	// I didn't write this function, and I have no idea how it works.
	// It isn't tested, either.
	// I also realize it isn't necessary in Linux, with the current design of this program.
	// I added the "Press any key..." to prevent the command box in Windows, from closing automatically.
	// I added this, so my program might act the same way on Linux, if it is one day ported, instead of "Press ENTER..."

	// "This code sets the terminal into non-canonical mode, thus disabling line buffering, reads a character from stdin and then restores the old terminal status."
	// Thanks to kermi3 of http://cboard.cprogramming.com

	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}
#endif

int validate(uint32_t CRC32)
{
    unsigned char buf[BUFFER_SIZE];
    size_t bufLen;
	char strCRC32[9] = "00000000";
	int i, Temp;

	for (i = 0; i < 8; i++)
	{
		Temp = (int)(CRC32 % 16u);
		CRC32 /= 16u;
		if (Temp >= 10)
		{
			Temp += 7;
		}
		Temp += 48;
		strCRC32[7-i] = Temp;
	}

	if (strstr(MemBuffer, strCRC32) != NULL)
	{
		return 1;	// FOUND
	}
	else
	{
		return 0;	// MISSING
	}
}

/*----------------------------------------------------------------------------*\
 *  CRC-32 version 2.0.0 by Craig Bruce, 2006-04-29.
 *
 *  This program generates the CRC-32 values for the files named in the
 *  command-line arguments.  These are the same CRC-32 values used by GZIP,
 *  PKZIP, and ZMODEM.  The Crc32_ComputeBuf() can also be detached and
 *  used independently.
 *
 *  THIS PROGRAM IS PUBLIC-DOMAIN SOFTWARE.
 *
 *  Based on the byte-oriented implementation "File Verification Using CRC"
 *  by Mark R. Nelson in Dr. Dobb's Journal, May 1992, pp. 64-67.
 *
\*----------------------------------------------------------------------------*/

uint32_t craig_bruce(const char * argv)
{
	const char *filename;
	uint32_t crc32;

	filename = argv;
	File = fopen( filename, "rb" );
	if (File == NULL)
	{
		error("Could not open the .NES file.");
	}

	Crc32_ComputeFile( File, &crc32 );

	if (fclose( File ) == EOF)
	{
		error("Could not close the .NES file.");
	}
	File = NULL;

	return crc32;
}

void Crc32_ComputeFile( FILE *file, uint32_t *outCrc32 )
{
    unsigned char buf[BUFFER_SIZE];
    size_t bufLen;

	// Strip off the 16 byte iNES header
	bufLen = fread( buf, 1, 16, file );
	if (bufLen == 0)
	{
		error("Could not strip off the iNES header.");
	}

    /** accumulate crc32 from file **/
    *outCrc32 = 0;
    while (1)
	{
        bufLen = fread( buf, 1, BUFFER_SIZE, file );
        if (bufLen == 0)
		{
            if (ferror(file))
			{
                error("Could not read the .NES file.");
            }
			else
			{
	            break;
			}
        }
        *outCrc32 = Crc32_ComputeBuf( *outCrc32, buf, bufLen );
    }
    return;
}

static uint32_t Crc32_ComputeBuf( uint32_t inCrc32, const void *buf,
                                       size_t bufLen )
{
    static const uint32_t crcTable[256] = {
   0x00000000,0x77073096,0xEE0E612C,0x990951BA,0x076DC419,0x706AF48F,0xE963A535,
   0x9E6495A3,0x0EDB8832,0x79DCB8A4,0xE0D5E91E,0x97D2D988,0x09B64C2B,0x7EB17CBD,
   0xE7B82D07,0x90BF1D91,0x1DB71064,0x6AB020F2,0xF3B97148,0x84BE41DE,0x1ADAD47D,
   0x6DDDE4EB,0xF4D4B551,0x83D385C7,0x136C9856,0x646BA8C0,0xFD62F97A,0x8A65C9EC,
   0x14015C4F,0x63066CD9,0xFA0F3D63,0x8D080DF5,0x3B6E20C8,0x4C69105E,0xD56041E4,
   0xA2677172,0x3C03E4D1,0x4B04D447,0xD20D85FD,0xA50AB56B,0x35B5A8FA,0x42B2986C,
   0xDBBBC9D6,0xACBCF940,0x32D86CE3,0x45DF5C75,0xDCD60DCF,0xABD13D59,0x26D930AC,
   0x51DE003A,0xC8D75180,0xBFD06116,0x21B4F4B5,0x56B3C423,0xCFBA9599,0xB8BDA50F,
   0x2802B89E,0x5F058808,0xC60CD9B2,0xB10BE924,0x2F6F7C87,0x58684C11,0xC1611DAB,
   0xB6662D3D,0x76DC4190,0x01DB7106,0x98D220BC,0xEFD5102A,0x71B18589,0x06B6B51F,
   0x9FBFE4A5,0xE8B8D433,0x7807C9A2,0x0F00F934,0x9609A88E,0xE10E9818,0x7F6A0DBB,
   0x086D3D2D,0x91646C97,0xE6635C01,0x6B6B51F4,0x1C6C6162,0x856530D8,0xF262004E,
   0x6C0695ED,0x1B01A57B,0x8208F4C1,0xF50FC457,0x65B0D9C6,0x12B7E950,0x8BBEB8EA,
   0xFCB9887C,0x62DD1DDF,0x15DA2D49,0x8CD37CF3,0xFBD44C65,0x4DB26158,0x3AB551CE,
   0xA3BC0074,0xD4BB30E2,0x4ADFA541,0x3DD895D7,0xA4D1C46D,0xD3D6F4FB,0x4369E96A,
   0x346ED9FC,0xAD678846,0xDA60B8D0,0x44042D73,0x33031DE5,0xAA0A4C5F,0xDD0D7CC9,
   0x5005713C,0x270241AA,0xBE0B1010,0xC90C2086,0x5768B525,0x206F85B3,0xB966D409,
   0xCE61E49F,0x5EDEF90E,0x29D9C998,0xB0D09822,0xC7D7A8B4,0x59B33D17,0x2EB40D81,
   0xB7BD5C3B,0xC0BA6CAD,0xEDB88320,0x9ABFB3B6,0x03B6E20C,0x74B1D29A,0xEAD54739,
   0x9DD277AF,0x04DB2615,0x73DC1683,0xE3630B12,0x94643B84,0x0D6D6A3E,0x7A6A5AA8,
   0xE40ECF0B,0x9309FF9D,0x0A00AE27,0x7D079EB1,0xF00F9344,0x8708A3D2,0x1E01F268,
   0x6906C2FE,0xF762575D,0x806567CB,0x196C3671,0x6E6B06E7,0xFED41B76,0x89D32BE0,
   0x10DA7A5A,0x67DD4ACC,0xF9B9DF6F,0x8EBEEFF9,0x17B7BE43,0x60B08ED5,0xD6D6A3E8,
   0xA1D1937E,0x38D8C2C4,0x4FDFF252,0xD1BB67F1,0xA6BC5767,0x3FB506DD,0x48B2364B,
   0xD80D2BDA,0xAF0A1B4C,0x36034AF6,0x41047A60,0xDF60EFC3,0xA867DF55,0x316E8EEF,
   0x4669BE79,0xCB61B38C,0xBC66831A,0x256FD2A0,0x5268E236,0xCC0C7795,0xBB0B4703,
   0x220216B9,0x5505262F,0xC5BA3BBE,0xB2BD0B28,0x2BB45A92,0x5CB36A04,0xC2D7FFA7,
   0xB5D0CF31,0x2CD99E8B,0x5BDEAE1D,0x9B64C2B0,0xEC63F226,0x756AA39C,0x026D930A,
   0x9C0906A9,0xEB0E363F,0x72076785,0x05005713,0x95BF4A82,0xE2B87A14,0x7BB12BAE,
   0x0CB61B38,0x92D28E9B,0xE5D5BE0D,0x7CDCEFB7,0x0BDBDF21,0x86D3D2D4,0xF1D4E242,
   0x68DDB3F8,0x1FDA836E,0x81BE16CD,0xF6B9265B,0x6FB077E1,0x18B74777,0x88085AE6,
   0xFF0F6A70,0x66063BCA,0x11010B5C,0x8F659EFF,0xF862AE69,0x616BFFD3,0x166CCF45,
   0xA00AE278,0xD70DD2EE,0x4E048354,0x3903B3C2,0xA7672661,0xD06016F7,0x4969474D,
   0x3E6E77DB,0xAED16A4A,0xD9D65ADC,0x40DF0B66,0x37D83BF0,0xA9BCAE53,0xDEBB9EC5,
   0x47B2CF7F,0x30B5FFE9,0xBDBDF21C,0xCABAC28A,0x53B39330,0x24B4A3A6,0xBAD03605,
   0xCDD70693,0x54DE5729,0x23D967BF,0xB3667A2E,0xC4614AB8,0x5D681B02,0x2A6F2B94,
   0xB40BBE37,0xC30C8EA1,0x5A05DF1B,0x2D02EF8D };
    uint32_t crc32;
    unsigned char *byteBuf;
    size_t i;

    /** accumulate crc32 for buffer **/
    crc32 = inCrc32 ^ 0xFFFFFFFF;
    byteBuf = (unsigned char*) buf;
    for (i=0; i < bufLen; i++) {
        crc32 = (crc32 >> 8) ^ crcTable[ (crc32 ^ byteBuf[i]) & 0xFF ];
    }
    return( crc32 ^ 0xFFFFFFFF );
}
