#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NESutils.h"

#define kAppVersion "0.61"

// this needs to be #ifdef'd based on OS, but I dunno if this is how it works... =(
// ':' for MacOS
// '/' for *nix, OSX, Be
// '\\' for win32/ dos, etc
#ifdef _WIN32
#define kPathSeparator '\\'
#else
#define kPathSeparator '/'
#endif

#pragma mark -
#pragma mark *** Commands

//command types
//extract cmd
#define kCmdExtractSprites 			"-xs"
#define kCmdExtractPRG				"-xp"
#define kCmdExtractCHR				"-xc"
#define kCmdExtractSpritesPRG		"-xsp"

//injection cmd
#define kCmdInjectPRG				"-ip"
#define kCmdInjectCHR				"-ic"
#define kCmdInjectSprites			"-is"

//titles
#define kCmdSetTitle				"-st"
#define kCmdRemoveTitle				"-rt"
#define kCmdPrintTitle				"-pt"

//drawing sprites
#define kCmdDrawSprites				"-ds"

//misc cmd
#define kCmdSetSourceFile			"-f"
#define kCmdInfo					"-i"
#define kCmdVerify					"-v"
#define kCmdGetPrgCount				"-pc"
#define kCmdGetChrCount				"-cc"
#define kCmdVerbose					"-V"

#pragma mark -
#pragma mark *** Options

#define kOptAll						"+a"
#define kOptRange					"+r"
#define kOptMono					"+m"
#define kOptFile					"+f"
#define kOptHtml					"+html"
#define kOptStrip					"+s"
#define kOptCompound				"+c"
#define kOptVMode					"+v"
#define kOptHMode					"+h"

//prototypes
#pragma mark -
#pragma mark *** Prototypes

void doCommand(char *cmd, int argc, char *argv[]);
void argumentError(const char *arg);

char *appendPathComponent(char *source, char *append);
char *lastPathComponent(char *source);

void printUsage();
void cleanUp(char *msg, int errCode);
void bail_srcFileError();

void printSpriteData(char *spriteData, int dataSize, int columns, int mono);
void spriteToHtml(char *spriteData);
int printROM_info(FILE *ifile);

#pragma mark -
#pragma mark *** Globals

FILE *srcFile;
char *srcFilename;

int verbose;

#pragma mark -
#pragma mark *** Functions

int main (int argc, char **argv) {
	char *lastCommand = NULL;
	char *params[15];
	int paramCount = 0;
	
	if (argc == 1) {
		printUsage();
		exit(0);
	}
	
	//my super-cool argument parser
	while(*argv++) {
		if (*argv && *argv[0] == '-' || !*argv) {
			if (lastCommand || !*argv) {
				//printf("Params for %s:\n", lastCommand);
				//int i = 0;
				//for (i = 0; i < paramCount; i++) {
				//	printf("\t%d: %s\n", i, params[i]);
				//}
				doCommand(lastCommand, paramCount, params);
				paramCount = 0;
			}
			lastCommand = *argv;
		} else if (*argv) {
			//printf("adding param %s...\n", *argv);
			params[paramCount++] = *argv;
		}
	}
}

#pragma mark -

void doCommand(char *cmd, int argc, char *argv[]) {

	//error checking
	if (!cmd) {
		printUsage();
		cleanUp(NULL, 1);
	}

// MISC STUFFS:
	if (strcmp(cmd, kCmdSetSourceFile) == 0) {						//set the srcFile
		#pragma mark SET SOURCE FILE
		// usage:
		// -f <filename>	set srcFile to <filename>
		
		if (argc < 1) {
			cleanUp("No filename specified for source file!", 1);
		}
		
		if (srcFile) {
			fclose(srcFile);
		}
		
		if (!argv[0] || !(srcFile = fopen(argv[0], "r+"))) {
			cleanUp("Error opening source file.", 1);
		}
		
		srcFilename = lastPathComponent(argv[0]);
		
		if (verbose)
			printf("Sourcefile set to:\t%s (%s)\n", argv[0], srcFilename);
	} else if (strcmp(cmd, kCmdVerbose) == 0) {
		verbose = !verbose;
		if (verbose) 
			printf("Verbose output is:\tON\n");
	} else if (strcmp(cmd, kCmdInfo) == 0) {						//get info!
		#pragma mark GET INFO
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		printROM_info(srcFile);
	} else if (strcmp(cmd, kCmdVerify) == 0) {						//verify!
		#pragma mark VERIFY
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		printf("Checking ROM:\t");
		if(NESVerifyROM(srcFile)) {
			printf("OK\n");
		} else {
			printf("NO GOOD\n");
			cleanUp(NULL, 1);
		}
	} else if (strcmp(cmd, kCmdGetPrgCount) == 0) {					//get the PRGCount
		#pragma mark PRG COUNT
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (verbose) {
			printf("PRG Banks:\t");
		}
		printf("%d\n", NESGetPrgBankCount(srcFile));
		//cleanUp(NULL, 0);
	} else if (strcmp(cmd, kCmdGetChrCount) == 0) {					//get the CHRCount
		#pragma mark CHR COUNT
		
		if (!srcFile)
			bail_srcFileError();
			
		if (verbose) {
			printf("CHR Banks:\t");
		}
		printf("%d\n", NESGetChrBankCount(srcFile));
		
		//cleanUp(NULL, 0);
// EXTRACTION:
	} else if (strcmp(cmd, kCmdExtractPRG) == 0) {					//extract PRG Bank(s)
		#pragma mark EXTRACT PRG
		// usage:
		// -xp +a <directory> 						Extract all PRG Banks to <directory>
		// -xp +r <fromIndex> <toIndex> <directory>	Extract <fromIndex> to <toIndex> into <directory>
		// -xp <prgIndex> <filename>				Extract <prgIndex> to <filename>
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (argc < 2) { //kCmdExtractPRG requires 2 arguments
			cleanUp("Not enough arguments for PRG Extraction", 1);
		}
		
		if (strcmp(argv[0], kOptAll) == 0) { //extract all PRGs
			#pragma mark -all
			char destPath[512];
			int i = 0;
			
			for (i = 1; i <= (int)NESGetPrgBankCount(srcFile); i++) {
				char filename[256];
				
				sprintf(filename, "%s.%d.prg", srcFilename, i);
				strcpy(destPath, argv[1]);
				appendPathComponent(destPath, filename);
				
				if (verbose) {
					printf("Extracting PRG bank:\t%d\tto:\t%s\n", i, destPath);
				}
				
				FILE *ofile;
				
				if (!(ofile = fopen(destPath, "w"))) {
					cleanUp("Could not open destination file.", 1);
				}
				
				if (NESExtractPrgBank(srcFile, ofile, i) == nesErr) {
					fclose(ofile);
					cleanUp("Could not extract PRG Bank.", 1);
				}
				
				fclose(ofile);
			}
		} else if (strcmp(argv[0], kOptRange) == 0) { //extract a range
			#pragma mark -range
			if (argc < 4) {
				cleanUp("Extracting ranges of PRG banks requires at least 4 arguments", 1);
			}
			
			int startIndex = atoi(argv[1]);
			int endIndex = atoi(argv[2]);
			
			char destPath[512];
			int i = 0;
			
			if (verbose) {
				printf("Extracting PRG range...\n");
				printf("\tStart:\t%d\n", startIndex);
				printf("\tEnd:\t%d\n", endIndex);
			}
			
			if (startIndex < 1 || endIndex > (int)NESGetPrgBankCount(srcFile)) {
				cleanUp("Invalid index for extracting PRG data.", 1);
			}
			
			for (i = startIndex; i <= endIndex; i++) {
				char filename[256];
				
				sprintf(filename, "%s.%d.prg", srcFilename, i);
				strcpy(destPath, argv[1]);
				appendPathComponent(destPath, filename);
				
				if (verbose) {
					printf("\tExtracting:\t%s\t\n", destPath);
				}
				
				FILE *ofile;
				
				if (!(ofile = fopen(destPath, "w"))) {
					cleanUp("Could not open destination file.", 1);
				}
				
				if (NESExtractPrgBank(srcFile, ofile, i) == nesErr) {
					fclose(ofile);
					cleanUp("Could not extract PRG Bank.", 1);
				}
				
				fclose(ofile);
				
				if (verbose) {
					printf("done.\n");
				}
			}
			
		} else {	//extract only a single PRG Bank.
			#pragma mark -single
			int prgIndex = atoi(argv[0]);
			char *filename = argv[1];
			
			FILE *ofile;
			
			if (verbose) {
				printf("Extracting bank %d to:\t%s\t", prgIndex, filename);
			}
			
			if (!(ofile = fopen(filename, "w"))) {
				cleanUp("Error opening file for writing.", 1);
			}
			
			if (NESExtractPrgBank(srcFile, ofile, prgIndex) == nesErr) {
				fclose(ofile);
				cleanUp("Error extracting PRG bank.", 1);
			}
			
			fclose(ofile);
			
			if (verbose) {
				printf("done.\n");
			}
		}
	} else if (strcmp(cmd, kCmdExtractCHR) == 0) {					//extract CHR bank(s)
		#pragma mark EXTRACT CHR
		// usage:
		// -xc +a <directory>							extract all CHR to <directory>
		// -xc +r <fromIndex> <toIndex> <directory>		extract from <fromIndex> to <toIndex> into <directory>
		// -xc <chrIndex> <filename>					extract <chrIndex> to <filename>
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (argc < 2) {
			cleanUp("Extraction of CHR requires at least 2 arguments", 1);
		}
		
		if (strcmp(argv[0], kOptAll) == 0) { //all
			#pragma mark -all
			char destPath[512];
			int i = 0;
			
			if (verbose) {
				printf("Extracting all CHR banks...\n");
			}
			
			for (i = 1; i <= (int)NESGetChrBankCount(srcFile); i++) {
				char filename[256];
				
				sprintf(filename, "%s.%d.chr", srcFilename, i);
				strcpy(destPath, argv[1]);
				appendPathComponent(destPath, filename);
				
				if (verbose) {
					printf("\tExtracting to:\t%s\t", destPath);
				}
				
				FILE *ofile;
				
				if (!(ofile = fopen(destPath, "w"))) {
					cleanUp("Could not open destination file.", 1);
				}
				
				if (NESExtractChrBank(srcFile, ofile, i) == nesErr) {
					fclose(ofile);
					cleanUp("Could not extract CHR Bank.", 1);
				}
				
				fclose(ofile);
				
				if (verbose) {
					printf("done\n");
				}
			}
		
		} else if (strcmp(argv[0], kOptRange) == 0) { //range
			#pragma mark -range
			if (argc < 4) {
				cleanUp("Extracting ranges of CHR banks requires at least 4 arguments", 1);
			}
			
			char destPath[512];
			int startIndex = atoi(argv[1]);
			int endIndex = atoi(argv[2]);
			
			if (verbose) {
				printf("Extracting range of CHR...\n");
				printf("\tStart:\t%d\n", startIndex);
				printf("\tEnd:\t%d\n", endIndex);
			}
			
			int i = 0;
			
			if (startIndex < 1 || endIndex > (int)NESGetChrBankCount(srcFile)) {
				cleanUp("Invalid index for extracting CHR data.", 1);
			}
			
			for (i = startIndex; i <= endIndex; i++) {
				char filename[256];
				
				sprintf(filename, "%s.%d.chr", srcFilename, i);
				strcpy(destPath, argv[3]);
				appendPathComponent(destPath, filename);
				
				if (verbose) {
					printf("Extracting %d to:\t%s\t", i, destPath);
				}
				
				FILE *ofile;
				
				if (!(ofile = fopen(destPath, "w"))) {
					cleanUp("Could not open destination file.", 1);
				}
				
				if (NESExtractChrBank(srcFile, ofile, i) == nesErr) {
					fclose(ofile);
					cleanUp("Could not extract CHR Bank.", 1);
				}
				
				fclose(ofile);
				if (verbose) {
					printf("done.\n");
				}
			}
		} else { //single
			#pragma mark -single
			if (argc < 2) {
				cleanUp("Not enough arguments to extract a CHR bank.", 1);
			}
			
			int chrIndex = atoi(argv[0]);
			char *filename = argv[1];
			
			if (verbose) {
				printf("Extracting CHR bank %d to:\t%s\t", chrIndex, filename);
			}
			
			if (chrIndex < 1 || chrIndex < (int)NESGetChrBankCount(srcFile)) {
				cleanUp("Invalid CHR index.", 1);
			}
			
			FILE *ofile;
			
			
			if (!(ofile = fopen(filename, "w"))) {
				cleanUp("An error occured when opening file for writing.", 1);
			}
			
			if (NESExtractChrBank(srcFile, ofile, chrIndex) == nesErr) {
				cleanUp("An error occured while extracting the CHR bank.", 1);
				fclose(ofile);
			}
			
			fclose(ofile);
			
			if (verbose) {
				printf("done.\n");
			}
		}
	} else if (strcmp(cmd, "-compound") == 0) {
		printf("SUPER DEBUG TEST FUNCTION! AHHHHH!\n");
	
		FILE *ofile, *stripFile;
		
		if (!(ofile = fopen("bigsprite.raw", "w"))) {
			printf("error opening file");
			exit(1);
		}
		
		if (!(stripFile = fopen("strip.raw", "w"))) {
			printf("error opening strip");
			exit(1);
		}
		
		char *spriteStrip = NESGetSpriteDataRangeFromChrBank(NESGetChrBank(srcFile, 1), 33, 40);
		char *compoundSprite = NESMakeCompoundSprite(spriteStrip, 8 * NES_rawSpriteSize, 2, nesHMode);
		
		fwrite(compoundSprite, 1, 8 * NES_rawSpriteSize, ofile);
		fwrite(spriteStrip, 1, 8 * NES_rawSpriteSize, stripFile);
		
		
		fclose(ofile);
		fclose(stripFile);
		
		printf("sprite range test worked!\n");
	} else if (strcmp(cmd, kCmdExtractSprites) == 0) {				//extract sprite(s)
		#pragma mark EXTRACT SPRITES
		// usage:
		// -xs +a <chrIndex> <directory>												Extract all sprites from <chrIndex> into <directory>
		// -xs +a +a <directory>														Extract all sprites from all CHR banks into <directory>
		// -xs +r <chrIndex> <fromIndex> <toIndex> <directory>							Extract a range of sprites from <chrIndex>
		// -xs <chrIndex> <index> <filename>											Extract a sprite from <chrIndex> to <filename>
		// -xs +r +s <chrIndex> <fromIndex> <toIndex> <filename>						Extract a sprite strip from <chrIndex> from <fromIndex> to <toIndex> to <filename>
		// -xs +r +c <mode> <columnCount> <chrIndex> <fromIndex> <toIndex> <filename>	Extract a compound sprite that is <columnCount> columns from <chrIndex> from <fromIndex> to <toIndex> to <filename>
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (argc < 3) {
			cleanUp("Extracting sprites requires at least 3 arguments.", 1);
		}
		
		if (strcmp(argv[0], kOptAll) == 0) {	//all
			if (strcmp(argv[1], kOptAll) == 0) { //all
				#pragma mark -all chr, all sprites
				if (argc < 3) {
					cleanUp("Must have at least 3 arguments to extract all sprites", 1);
				}
				int i = 0;
				int j = 0;
				
				char destPath[512];
				char *directory = argv[2];
				
				if (verbose) {
					printf("Extracting ALL sprites from ALL CHR banks...\n");
					printf("\tDirectory:\t%s\n", directory);
				}
				
				for (i = 1; i <= (int)NESGetChrBankCount(srcFile); i++) { //the chr loop
					for (j = 1; j <= NES_spritesPerChr; j++) { //the sprite loop
						char filename[256];
						
						sprintf(filename, "%s.%d-%d.raw", srcFilename, i, j);
						strcpy(destPath, directory);
						appendPathComponent(destPath, filename);
						
						if (verbose) {
							printf("Extracting:\t%s\t", filename);
						}
						
						FILE *ofile;
						
						if (!(ofile = fopen(destPath, "w"))) {
							cleanUp("Cannot open file for writing!", 1);
						}
						
						if (NESExtractSprite(srcFile, ofile, i, j) == nesErr) {
							fclose(ofile);
							cleanUp("Could not extract sprite.", 1);
						}
						
						fclose(ofile);
						
						if (verbose) {
							printf("done.\n");
						}
					}
				}
			} else {	//specific CHR, all sprites
			#pragma mark -specific chr, all sprites
				if (argc < 3) {
					cleanUp("Extracting all sprites from a CHR requires at least 3 arguments.", 1);
				}
				
				int chrIndex = atoi(argv[1]);
				char destPath[512];
				
				if (verbose) {
					printf("Extracting ALL sprites from CHR bank %d to %s.\n", chrIndex, destPath);
				}
				
				int i = 0;
				
				for (i = 1; i <= NES_spritesPerChr; i++) {
					char filename[256];
					
					sprintf(filename, "%s.%d-%d.raw", srcFilename, chrIndex, i);
					strcpy(destPath, argv[3]);
					appendPathComponent(destPath, filename);
					
					if (verbose) {
						printf("Extracting to:\t%s\t", destPath);
					}
					
					FILE *ofile;
					
					if (!(ofile = fopen(destPath, "w"))) {
						cleanUp("Could not open destination file.", 1);
					}
					
					if (NESExtractSprite(srcFile, ofile, chrIndex, i) == nesErr) {
						fclose(ofile);
						cleanUp("Could not extract sprite.", 1);
					}
					
					fclose(ofile);
					
					if (verbose) {
						printf("done.\n");
					}
				}
			}
		} else if (strcmp(argv[0], kOptRange) == 0) { //range of sprites
			#pragma mark - RANGE
			
			if (strcmp(argv[1], kOptStrip) == 0) {
				#pragma mark --strip
				
				if (argc < 6) {
					cleanUp("Need at least 6 arguments to extract a sprite strip!", 1);
				}
				
				int chrIndex = atoi(argv[2]);
				int fromIndex = atoi(argv[3]);
				int toIndex = atoi(argv[4]);
				
				char *filename = argv[5];
				
				if (verbose) {
					printf("Extracting a strip of sprites.\n");
					printf("\tchrIndex:\t%d\n", chrIndex);
					printf("\tfromIndex:\t%d\n", fromIndex);
					printf("\ttoIndex:\t%d\n", toIndex);
					printf("\tfile:\t%s...\t", filename);
				}
				
				FILE *ofile;
				
				if (!(ofile = fopen(filename, "w"))) {
					cleanUp("Can't open file for writing sprite strip!", 1);
				}
				
				if (NESExtractSpriteRange(srcFile, ofile, chrIndex, fromIndex, toIndex) == nesErr) {
					cleanUp("Could not extract a sprite strip!", 1);
				}
				
				fclose(ofile);
				
				if (verbose) {
					printf("done.\n");
				}
				
			} else if (strcmp(argv[1], kOptCompound) == 0) {
				#pragma mark --compound sprite
				
				if (argc < 8) {
					cleanUp("Need at least 8 arguments to extract a compound sprite!", 1);
				}
				
				NESSpriteMode mode;
				
				if (strcmp(argv[2], kOptVMode) == 0) {
					mode = nesVMode;
				} else if (strcmp(argv[2], kOptHMode) == 0) {
					mode = nesHMode;
				} else {
					cleanUp("Invalid mode!", 1);
				}
				
				int columnCount = atoi(argv[3]);
				int chrIndex = atoi(argv[4]);
				int fromIndex = atoi(argv[5]);
				int toIndex = atoi(argv[6]);
				
				char *filename = argv[7];
				
				if (verbose) {
					printf("Extracting compound sprite.\n");
					printf("\tcolumnCount:\t%d\n", columnCount);
					printf("\tchrIndex:\t%d\n", chrIndex);
					printf("\tfromIndex:\t%d\n", fromIndex);
					printf("\ttoIndex:\t%d\n", toIndex);
					printf("\tfile:\t%s\t", filename);
				}
				
				int dataSize = (toIndex - fromIndex + 1) * NES_rawSpriteSize;
				
				FILE *ofile;
				
				if (!(ofile = fopen(filename, "w"))) {
					cleanUp("Can't open file for writing compound sprite!", 1);
				}
				
				char *chrBank = NESGetChrBank(srcFile, chrIndex);
				
				if (!chrBank) {
					cleanUp("Can't retrieve CHR bank from ROM!", 1);
				}
				
				char *spriteData = NESGetSpriteDataRangeFromChrBank(chrBank, fromIndex, toIndex);
				free(chrBank);
				
				if (!spriteData) {
					cleanUp("Can't retrieve sprite data from CHR!", 1);
				}
				
				char *cSprite = NESMakeCompoundSprite(spriteData, dataSize, columnCount, mode);
				free(spriteData);
				
				if (!cSprite) {
					cleanUp("Can't create compound sprite!", 1);
				}
				
				if (fwrite(cSprite, 1, dataSize, ofile) != (unsigned int)dataSize) {
					free(cSprite);
					fclose(ofile);
					cleanUp("error writing compound sprite to file!", 1);
				}
				
				free(cSprite);
				fclose(ofile);
				
				if (verbose) {
					printf("done.\n");
				}
			} else {
				#pragma mark --standard range
				
				if (argc < 5) {
					cleanUp("Not enough arguments to extract a range of sprites.", 1);
				}
				
				char destPath[512];
				int chrIndex = atoi(argv[1]);
				int startIndex = atoi(argv[2]);
				int endIndex = atoi(argv[3]);
				
				if (verbose) {
					printf("Extracting a range of sprites...\n");
					printf("\tchrIndex:\t%d\n", chrIndex);
					printf("\tstartIndex:\t%d\n", startIndex);
					printf("\tendIndex:\t%d\n", endIndex);
				}
				
				int i = 0;
				
				if (chrIndex < 1 || chrIndex > (int)NESGetChrBankCount(srcFile)) {
					cleanUp("Invalid CHR index.", 1);
				}
				
				if (startIndex < 1 || endIndex > NES_spritesPerChr) {
					cleanUp("Invalid index for extracting a range sprite data.", 1);
				}
				
				for (i = startIndex; i <= endIndex; i++) {
					char filename[256];
					
					sprintf(filename, "%s.%d-%d.raw", srcFilename, chrIndex, i);
					strcpy(destPath, argv[4]);
					appendPathComponent(destPath, filename);
					
					if (verbose) {
						printf("\tExtracting: %s\t", destPath);
					}
					
					FILE *ofile;
					
					if (!(ofile = fopen(destPath, "w"))) {
						cleanUp("Could not open destination file.", 1);
					}
					
					if (NESExtractSprite(srcFile, ofile, chrIndex, i) == nesErr) {
						fclose(ofile);
						cleanUp("Could not extract sprite.", 1);
					}
					
					fclose(ofile);
					
					if (verbose) {
						printf("done.\n");
					}
				}
			}
		} else { //single
			#pragma mark -specific chr, specific sprite
			if (argc < 3) {
				cleanUp("Extracting a sprite requires at least 3 arguments", 1);
			}
			
			int chrIndex = atoi(argv[0]);
			int spriteIndex = atoi(argv[1]);
			char *filename = argv[2];
			
			if (verbose) {
				printf("Extracting single sprite...\n");
				printf("\tchrIndex:\t%d\n", chrIndex);
				printf("\tspriteIndex\t%d\n", spriteIndex);
				printf("\tfile:\t%s\t", filename);
			}
			
			if (chrIndex < 1 || chrIndex < (int)NESGetChrBankCount(srcFile)) {
				cleanUp("Invalid CHR bank index.", 1);
			}
			
			FILE *ofile;
			
			if (!(ofile = fopen(filename, "w"))) {
				cleanUp("Could not open file for writing...", 1);
			}
			
			if (NESExtractSprite(srcFile, ofile, chrIndex, spriteIndex) == nesErr) {
				cleanUp("Could not extract sprite.", 1);
				fclose(ofile);
			}
			
			fclose(ofile);
			
			if (verbose) {
				printf("done.\n");
			}
		}
	} else if (strcmp(cmd, kCmdExtractSpritesPRG) == 0) {			//extract sprite(s) from PRG!
		#pragma mark EXTRACT SPRITES FROM PRG
		//USAGE:
		// -xsp +r +c ( +h | +v ) <columnCount> <prgIndex> <fromIndex> <toIndex> <filename>
		
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		NESSpriteMode mode;
				
		if (strcmp(argv[2], kOptVMode) == 0) {
			mode = nesVMode;
		} else if (strcmp(argv[2], kOptHMode) == 0) {
			mode = nesHMode;
		} else {
			cleanUp("Invalid mode!", 1);
		}
		
		int columnCount = atoi(argv[3]);
		int prgIndex = atoi(argv[4]);
		int fromIndex = atoi(argv[5]);
		int toIndex = atoi(argv[6]);
		
		char *filename = argv[7];
		
		if (verbose) {
			printf("Extracting prg sprite (BEWARE!!!!! RAHHH!\n");
		}
								
		int dataSize = (toIndex - fromIndex + 1) * NES_rawSpriteSize;
		
		FILE *ofile;
		
		if (!(ofile = fopen(filename, "w"))) {
			cleanUp("Can't open file for writing compound sprite!", 1);
		}
		
		char *prgData = NESGetPrgBank(srcFile, prgIndex);
		
		printf("getting %d\n", prgIndex);
		
		if (!prgData) {
			cleanUp("Can't retrieve PRG bank from ROM!", 1);
		}
		
		char *spriteData = NESGetSpriteDataRangeFromChrBank(prgData, fromIndex, toIndex);
		free(prgData);
		
		if (!spriteData) {
			cleanUp("Can't retreive sprite data from PRG!", 1);
		}
		
		char *cSprite = NESMakeCompoundSprite(spriteData, dataSize, columnCount, mode);
		free(spriteData);
		
		if (!cSprite) {
			cleanUp("Can't create compound sprite!", 1);
		}
		
		if (fwrite(cSprite, 1, dataSize, ofile) != (unsigned int)dataSize) {
			free(cSprite);
			fclose(ofile);
			cleanUp("error writing compound sprite to file!", 1);
		}
		
		free(cSprite);
		fclose(ofile);
	} else if (strcmp(cmd, kCmdInjectPRG) == 0) {
		#pragma mark INJECT PRG
		// usage:
		// -ip <filename> <prgIndex>
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (argc < 2) {
			cleanUp("Injecting PRG banks requires at least 2 arguments", 1);
		}
		
		char *filename = argv[0];
		int prgIndex = atoi(argv[1]);
		
		if (verbose) {
			printf("Injecting PRG to %d from %s\n", prgIndex, filename);
		}
		
		if (prgIndex < 1 || prgIndex > (int)NESGetPrgBankCount(srcFile)) {
			cleanUp("Invalid prgIndex for injection!", 1);
		}
		
		FILE *ifile;
		
		if (!(ifile = fopen(filename, "r"))) {
			cleanUp("Can't open source file!", 1);
		}
		
		if (NESInjectPrgBank(srcFile, ifile, prgIndex) == nesErr) {
			fclose(ifile);
			cleanUp("Can't inject PRG bank!", 1);
		}
		
		fclose(ifile);
		
		if (verbose) {
			printf("done\n");
		}
	
	} else if (strcmp(cmd, kCmdInjectCHR) == 0) {
		#pragma mark INJECT CHR
		// usage:
		// -ic <filename> <chrIndex>
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (argc < 2) {
			cleanUp("Injecting CHR banks requires at least 2 arguments!", 1);
		}
		
		char *filename = argv[0];
		int chrIndex = atoi(argv[1]);
		
		if (verbose) {
			printf("Injecting CHR...\n");
			printf("\tchrIndex:\t%d\n", chrIndex);
			printf("\tfile:\t%s\t", filename);
		}
		
		if (chrIndex < 1 || chrIndex > (int)NESGetChrBankCount(srcFile)) {
			cleanUp("Invalid chrIndex bank for injection!", 1);
		}
		
		FILE *ifile;
		
		if (!(ifile = fopen(filename, "r"))) {
			cleanUp("Can't open CHR bank file!", 1);
		}
		
		if (NESInjectChrBank(srcFile, ifile, chrIndex) == nesErr) {
			fclose(ifile);
			cleanUp("Can't inject CHR bank!", 1);
		}
		
		fclose(ifile);
		
		if (verbose) {
			printf("done\n");
		}
		
	} else if (strcmp(cmd, kCmdInjectSprites) == 0) {
		#pragma mark INJECT SPRITES
		// usage:
		// -is <filename> <chrIndex> <spriteIndex>
		// -is +r <chrIndex> <fromIndex> <toIndex> [Files...]?
		// -is +r +s <chrIndex> <fromIndex> <filename>
		// -is +r +c [+h | +v] <columns> <chrIndex> <fromIndex> <filename>
		
		if (strcmp(argv[0], kOptRange) == 0) {
			#pragma mark -RANGE
			
			if (strcmp(argv[1], kOptStrip) == 0) {
				#pragma mark --strip of sprites
				
				int chrIndex = atoi(argv[2]);
				int fromIndex = atoi(argv[3]);
				char *filename = argv[4];
				
				if (verbose) {
					printf("Injecting a sprite strip\n");
					printf("\tchrIndex:\t%d\n", chrIndex);
					printf("\tfromIndex:\t%d\n", fromIndex);
					printf("\tfile:\t%s\t", filename);
				}
				
				FILE *ifile;
				
				if (!(ifile = fopen(filename, "r"))) {
					cleanUp("Can't open sprite strip file!", 1);
				}
				
				if (NESInjectSpriteStripFile(srcFile, ifile, chrIndex, fromIndex) == nesErr) {
					cleanUp("Can't inject sprite!", 1);
				}
				
				fclose(ifile);
				
				if (verbose) {
					printf("done.\n");
				}
			} else if (strcmp(argv[1], kOptCompound) == 0) {
				#pragma mark --compound sprite
				
				NESSpriteMode mode;
				
				if (strcmp(argv[2], kOptHMode) == 0) {
					mode = nesHMode;
				} else if (strcmp(argv[2], kOptVMode) == 0) {
					mode = nesVMode;
				} else {
					cleanUp("Invalid sprite mode!", 1);
				}
				
				int columns = atoi(argv[3]);
				int chrIndex = atoi(argv[4]);
				int fromIndex = atoi(argv[5]);
				char *filename = argv[6];

				if (verbose) {
					printf("Injecting compound sprite.\n");
					printf("\tcolumns:\t%d\n", columns);
					printf("\tchrIndex:\t%d\n", chrIndex);
					printf("\tfromIndex:\t%d\n", fromIndex);
					printf("\tfile:\t%s\t", filename);
				}
				
				
				FILE *ifile;
				
				if (!(ifile = fopen(filename, "r"))) {
					cleanUp("Can't open sprite file!", 1);
				}
				
				if (NESInjectCompoundSpriteFile(srcFile, ifile, columns, mode, chrIndex, fromIndex) == nesErr) {
					cleanUp("Can't inject sprite! ahhhh!", 1);
				}
				
				fclose(ifile);
				
				if (verbose) {
					printf("done.\n");
				}
				
			} else {
				#pragma mark --just a range...
				
				cleanUp("Injecting a range of sprites is not yet supported", 1);
			}
		} else {																		//specific sprite
			#pragma mark -specific sprite
			if (argc < 3) {
				cleanUp("Injecting sprites requires at least 3 arguments!", 1);
			}
			
			char *filename = argv[0];
			int chrIndex = atoi(argv[1]);
			int spriteIndex = atoi(argv[2]);
			
			if (verbose) {
				printf("Injecting sprite...\n");
				printf("\tchIndex:\t%d\n", chrIndex);
				printf("\tspriteIndex:\t%d\n", spriteIndex);
				printf("\tfromFile:\t%s\t", filename);
			}
			
			if (chrIndex < 1 || chrIndex > (int)NESGetChrBankCount(srcFile)) {
				cleanUp("Invalid chrIndex for injection of sprites!", 1);
			}
			
			if (spriteIndex < 1 || spriteIndex > NES_spritesPerChr) {
				cleanUp("Invalid spriteIndex!", 1);
			}
			
			FILE *ifile;
			
			if (!(ifile = fopen(filename, "r"))) {
				cleanUp("Can't open sprite file!", 1);
			}
			
			if (NESInjectSpriteFile(srcFile, ifile, chrIndex, spriteIndex) == nesErr) {
				fclose(ifile);
				cleanUp("Can't inject sprite!", 1);
			}
			
			fclose(ifile);
			
			if (verbose) {
				printf("done.\n");
			}
		}
	} else if (strcmp(cmd, kCmdDrawSprites) == 0) {
		#pragma mark DRAW SPRITES
		// usage:
		// -ds [+m] +a													display ALL sprites from ALL CHR banks
		// -ds [+m] <chrindex> +a										display ALL sprites from CHR bank <chrindex>
		// -ds [+m] <chrindex> <spriteindex>							display sprite <spriteindex> from CHR bank <chrindex>
		// -ds [+m] +r <chrIndex> <fromIndex> <toIndex> 				display a range of sprites from <chrIndex>
		// -ds [+m] +r +c [mode] <columns> <chrIndex> <fromIndex> <toIndex>	display compound sprite with <columns> 
		// -ds [+m] +r +s <chrIndex> <fromIndex> <toIndex>
		
		int mono = 0;
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (strcmp(argv[0], kOptMono) == 0) {
			mono = 1;
		}
		
		if (strcmp(argv[0 + mono], kOptAll) == 0) { 	//all CHR, all sprites
			#pragma mark -all chr, all sprites
			
			if ((argc - mono) < 1) {
				cleanUp("Displaying all sprites requires at least one argument.", 1);
			}
			
			if (verbose) {
				printf("Displaying ALL sprites in ALL CHR banks...\n");
			}
			
			int chrCount = NESGetChrBankCount(srcFile);
			int i = 0;
			int j = 0;
			
			for (i = 1; i <= chrCount; i++) {
				char *chrData = NESGetChrBank(srcFile, i);
				
				if (!chrData) {
					cleanUp("Can't get chrData!!!", 1);
				}
				
				for (j = 1; j < NES_spritesPerChr; j++) {
					char *spriteData = NESGetSpriteDataFromChrBank(chrData, j);
					
					if (!spriteData) {
						free(chrData);
						cleanUp("Can't get spriteData!", 1);
					}
					
					if (verbose) {
						printf("CHR:\t%d\n", i);
						printf("Sprite:\t%d\n", j);
					}
					
					printSpriteData(spriteData, 1, NES_rawSpriteSize, mono);
					
					printf("\n");
					
					free(spriteData);
				}
				
				free(chrData);
				
				if (verbose) {
					printf("Done.\n");
				}
			}
			
		} else if (strcmp(argv[0 + mono], kOptRange) == 0) {	//specific chr, range of sprites
				#pragma mark -RANGE
				
			if (strcmp(argv[1 + mono], kOptCompound) == 0) {
				#pragma mark --compound sprite
				
				if ((argc - mono) < 7) {
					cleanUp("Displaying a compound sprite requires at least 7 arguments.", 1);
				}
				
				NESSpriteMode mode;
				
				if (strcmp(argv[2 + mono], kOptVMode) == 0) {
					mode = nesVMode;
				} else if (strcmp(argv[2 + mono], kOptHMode) == 0){
					mode = nesHMode;
				} else {
					cleanUp("Illeagal mode type!", 1);
				}
				
				int columns = atoi(argv[3 + mono]);
				int chrIndex = atoi(argv[4 + mono]);
				int fromIndex = atoi(argv[5 + mono]);
				int toIndex = atoi(argv[6 + mono]);
				
				if (verbose) {
					printf("Displaying compound sprite...\n");
					printf("\tmode:\t%s\n", (mode == nesVMode) ? "Vertical" : "Horizontal");
					printf("\tcolumns:\t%d\n", columns);
					printf("\tchrIndex:\t%d\n", chrIndex);
					printf("\tfromIndex:\t%d\n", fromIndex);
					printf("\ttoIndex:\t%d\n", toIndex);
				}
				
				char *chrData = NESGetChrBank(srcFile, chrIndex);
				
				if (!chrData) {
					cleanUp("Can't get CHR bank!", 1);
				}
				
				char *spriteData = NESGetSpriteDataRangeFromChrBank(chrData, fromIndex, toIndex);
				free(chrData);
				
				if (!spriteData) {
					cleanUp("Can't get sprite data!", 1);
				}
				
				char *compSprite = NESMakeCompoundSprite(spriteData, (toIndex - fromIndex + 1) * NES_rawSpriteSize, columns, mode);
				free(spriteData);
				
				if (!compSprite) {
					cleanUp("Can't make compound sprite!", 1);
				}
				
				printSpriteData(compSprite, (toIndex - fromIndex + 1) * NES_rawSpriteSize, columns, mono);
				
			} else if (strcmp(argv[1 + mono], kOptStrip) == 0) {
				#pragma mark --strip of sprites
				
				if ((argc - mono) < 5) {
					cleanUp("Displaying a strip of sprites requires at least 5 arguments!", 1);
				}
				
				int chrIndex = atoi(argv[2 + mono]);
				int fromIndex = atoi(argv[3 + mono]);
				int toIndex = atoi(argv[4 + mono]);
				
				if (verbose) {
					printf("Displaying sprite strip...\n");
					printf("\tchrIndex:\t%d\n", chrIndex);
					printf("\tfromIndex:\t%d\n", fromIndex);
					printf("\ttoIndex:\t%d\n", toIndex);
				}
				
				char *chrData = NESGetChrBank(srcFile, chrIndex);
				
				if (!chrData) {
					cleanUp("Can't get CHR bank!", 1);
				}
				
				char *spriteData = NESGetSpriteDataRangeFromChrBank(chrData, fromIndex, toIndex);
				free(chrData);
				
				if (!spriteData) {
					cleanUp("Can't get sprite data!", 1);
				}
				
				char *compSprite = NESMakeCompoundSprite(spriteData, (toIndex - fromIndex + 1) * NES_rawSpriteSize, 1, nesHMode);
				free(spriteData);
				
				if (!compSprite) {
					cleanUp("Can't make compound sprite!", 1);
				}
				
				printSpriteData(compSprite, (toIndex - fromIndex + 1) * NES_rawSpriteSize, 1, mono);
				
			} else {
				#pragma mark -specific chr, range of sprites
				
				if ((argc - mono) < 4) {
					cleanUp("Displaying a range of sprites requires at least four arguments.", 1);
				}
				
				int chrIndex = atoi(argv[1 + mono]);
				int fromIndex = atoi(argv[2 + mono]);
				int toIndex = atoi(argv[3 + mono]);
				
				if (verbose) {
					printf("Displaying range of sprites...\n");
					printf("\tchrIndex:\t%d\n", chrIndex);
					printf("\tfromIndex:\t%d\n", fromIndex);
					printf("\ttoIndex:\t%d\n", toIndex);
				}
				
				int i = 0;
				
				char *chrData = NESGetChrBank(srcFile, chrIndex);
				
				if (!chrData) {
					cleanUp("Can't extract CHR bank!", 1);
				}
				
				for (i = fromIndex; i <= toIndex; i++) {
					char *spriteData = NESGetSpriteDataFromChrBank(chrData, i);
					
					if (!spriteData) {
						free(chrData);
						cleanUp("Can't get sprite data!", 1);
					}
					
					if (verbose) {
						printf("CHR:\t%d\n", chrIndex);
						printf("Sprite:\t%d\n", i);
					}
					
					printSpriteData(spriteData, NES_rawSpriteSize, 1, mono);
					
					printf("\n");
					
					free(spriteData);
				}
				
				free(chrData);
			}
		} else if (strcmp(argv[1 + mono], kOptAll) == 0) {		//specific chr, all sprites
			#pragma mark -specific chr, all sprites
			
			if ((argc - mono) < 2) {
				cleanUp("Displaying all sprites from a CHR bank requires at least two arguments.", 1);
			}
			
			int chrIndex = atoi(argv[0 + mono]);
			
			if (verbose) {
				printf("Displaying ALL sprites from CHR bank %d...", chrIndex);
			}
			
			int i = 0;
			
			char *chrData = NESGetChrBank(srcFile, chrIndex);
			
			for (i = 1; i <= NES_spritesPerChr; i++) {
				char *spriteData = NESGetSpriteDataFromChrBank(chrData, i);
				
				if (!spriteData) {
					free(chrData);
					cleanUp("Can't get sprite data!", 1);
				}
				
				//printf("CHR:\t%d\n", chrIndex);
				if (verbose) {
					printf("Sprite:\t%d\n", i);
				}
				
				printSpriteData(spriteData, NES_rawSpriteSize, 1, mono);
				
				printf("\n");
				
				free(spriteData);
			}
			
			free(chrData);
		} else {
			#pragma mark -specific chr, specific sprite
			
			if ((argc - mono) < 2) {
				cleanUp("Displaying a sprite requires at least two arguments.", 1);
			}
			
			int chrIndex = atoi(argv[0 + mono]);
			int spriteIndex = atoi(argv[1 + mono]);
			
			if (verbose) {
				printf("Displaying sprite...\n");
			}
			
			char *chrData = NESGetChrBank(srcFile, chrIndex);
			
			if (!chrData) {
				cleanUp("Can't get CHR bank!!!", 1);
			}
			
			char *spriteData = NESGetSpriteDataFromChrBank(chrData, spriteIndex);
			
			if (!spriteData) {
				free(chrData);
				cleanUp("Can't get spriteData!", 1);
			}
			
			if (verbose) {
				printf("CHR:\t%d\n", chrIndex);
				printf("Sprite:\t%d\n", spriteIndex);
			}
			
			printSpriteData(spriteData, NES_rawSpriteSize, 1, mono);
				
			printf("\n");
				
			free(spriteData);
			free(chrData);
		}
		#pragma mark TITLES
	} else if (strcmp(cmd, kCmdSetTitle) == 0) {					//set title
		#pragma mark -set
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (argc < 1) {
			cleanUp("Setting the title requires at least 1 argument!", 1);
		}
		
		char *newTitle = argv[0];
		
		if (verbose) {
			printf("Setting title to \"%s\"\n", newTitle);
		}
		
		if (NESSetTitle(srcFile, newTitle) == nesErr) {
			cleanUp("There was an error setting the title!!", 1);
		}
		
		if (verbose) {
			printf("Done.\n");
		}
	} else if (strcmp(cmd, kCmdPrintTitle) == 0) {					//print title
		#pragma mark -print
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (verbose) {
			printf("Title:\t");
		}
		
		printf("%s\n", NESHasTitle(srcFile) ? NESGetTitle(srcFile, true) : "NO TITLE!");
	} else if (strcmp(cmd, kCmdRemoveTitle) == 0) {					//remove title from file
		#pragma mark -remove
		
		//this command requires a sourcefile
		if (!srcFile) {
			bail_srcFileError();
		}
		
		if (verbose) {
			printf("Removing title...\t");
		}
		
		if (NESRemoveTitle(srcFile) == nesErr) {
			cleanUp("Cannot remove title from ROM!", 1);
		}
		
		if (verbose) {
			printf("Done.\n");
		}
	} else { 														//unknown command
		cleanUp("Unknown command.", 1);
	}
}

void printUsage() {
	printf("NESRomTool %s- The greatest tool on earth for editing NES ROM files (.nes).\n\n", kAppVersion);
	printf("  Written by spike (spike@sadistech.com)\n");
	printf("  < http://nesromtool.sourceforge.net >\n\n");
	
	printf("Usage:\n");
	printf("  NESRomTool [ options ]\n\n");
	
	printf("MISC OPTIONS:\n");
	printf("\t%s <filename>\n\t\tSets the working file. All extractions and injections will be performed on this file.\n", kCmdSetSourceFile);
	printf("\t%s\n\t\tPrint information about the working file.\n", kCmdInfo);
	printf("\t%s\n\t\tVerify that the ROM is ok. No output. Application returns 0 if ROM is ok.\n", kCmdVerify);
	printf("\t%s\n\t\tPrints the PrgCount of the ROM.\n", kCmdGetPrgCount);
	printf("\t%s\n\t\tPrints the ChrCount of the ROM.\n", kCmdGetChrCount);
	
	printf("\n");
	printf("EXTRACTION:\n");
	printf("\t%s %s <directory>\n\t\tExtract all PRG banks from file to <directory>\n", kCmdExtractPRG, kOptAll);
	printf("\t%s %s <fromIndex> <toIndex> <directory>\n\t\tExtract PRG <fromIndex> to PRG <toIndex> into <directory>\n", kCmdExtractPRG, kOptRange);
	printf("\t%s <prgIndex> <filename>\n\t\tExtract PRG <prgIndex> to file <filename>\n", kCmdExtractPRG);
	printf("\t%s %s <directory>\n\t\tExtract all CHR banks from file to <directory>\n", kCmdExtractCHR, kOptAll);
	printf("\t%s %s <fromIndex> <toIndex> <directory>\n\t\tExtract CHR <fromIndex> to CHR <toIndex> into <directory>\n", kCmdExtractCHR, kOptRange);
	printf("\t%s <prgIndex> <filename>\n\t\tExtract CHR <prgIndex> to file <filename>\n", kCmdExtractCHR);
	printf("\t%s %s <chrIndex> <directory>\n\t\tExtract all sprites from CHR <chrIndex> into <directory>\n", kCmdExtractSprites, kOptAll);
	printf("\t%s %s %s <directory>\n\t\tExtract all sprites from all CHR banks into <directory>\n", kCmdExtractSprites, kOptAll, kOptAll);
	printf("\t%s %s <chrIndex> <fromIndex> <toIndex> <directory>\n\t\tExtract sprites <fromIndex> to <toIndex> from CHR bank <chrIndex> into <directory>\n", kCmdExtractSprites, kOptRange);
	printf("\t%s <chrIndex> <spriteIndex> <filename>\n\t\tExtract sprite <spriteIndex> from CHR bank <chrIndex> to <filename>\n", kCmdExtractSprites);
	printf("\t%s %s %s <chrIndex> <fromIndex> <toIndex> <filename>\n\t\tExtract a range of sprites into a single file, 1 sprite wide.\n", kCmdExtractSprites, kOptRange, kOptStrip);
	printf("\t%s %s %s ( %s | %s ) <columnCount> <chrIndex> <fromIndex> <toIndex> <filename>\n\t\tExtract a range of sprites into a single file that is <columnCount> columns wide. %s or %s determines the order that the sprites are drawn into the file.\n", kCmdExtractSprites, kOptRange, kOptCompound, kOptVMode, kOptHMode, kOptVMode, kOptHMode);
	
	printf("\n");
	printf("INJECTION:\n");
	printf("\t%s <filename> <prgIndex>\n\t\tInject <filename> into PRG bank <prgIndex>\n", kCmdInjectPRG);
	printf("\t%s <filename> <chrIndex>\n\t\tInject <filename> into CHR bank <chrIndex>\n", kCmdInjectCHR);
	printf("\t%s <filename> <chrIndex> <spriteIndex>\n\t\tInject sprite <filename> into CHR bank <chrIndex> at <spriteIndex>\n", kCmdInjectSprites);
	
	printf("\n");
	printf("TITLES:\n");
	printf("\t%s\n\t\tPrints the title of the ROM if it has one set.\n", kCmdPrintTitle);
	printf("\t%s <title>\n\t\tSet the title of the ROM to <title>.\n", kCmdSetTitle);
	printf("\t%s\n\t\tRemoves the title from the ROM.\n", kCmdRemoveTitle);
	
	printf("\n");
	printf("PREVIEWING:\n");
	printf("By specifying the %s option, nesromtool will output the indexed color values of the sprite as text (for monochrome terminals (non colour))\n", kOptMono);
	printf("\t%s [%s] %s\n\t\tDisplay All sprites in the terminal window.\n", kCmdDrawSprites, kOptMono, kOptAll);
	printf("\t%s [%s] <chrIndex> %s\n\t\tDisplay all sprites from CHR bank <chrIndex>\n", kCmdDrawSprites, kOptMono, kOptAll);
	printf("\t%s [%s] <chrIndex> <spriteIndex>\n\t\tDisplay sprite <spriteIndex> from CHR bank <chrIndex>\n", kCmdDrawSprites, kOptMono);
	printf("\t%s [%s] %s <chrIndex> <fromIndex> <toIndex>\n\t\tDisplay sprites <fromIndex> to <toIndex> from CHR bank <chrIndex>\n", kCmdDrawSprites, kOptMono, kOptRange);
	printf("\t%s [%s] %s %s ( %s | %s ) <columnCount> <chrIndex> <fromIndex> <toIndex>\n\t\tDisplay a compound sprite.\n", kCmdDrawSprites, kOptMono, kOptRange, kOptCompound, kOptHMode, kOptVMode);
	printf("\t%s [%s] %s %s <chrIndex> <fromIndex> <toIndex>\n\t\tDisplay a sprite strip.\n", kCmdDrawSprites, kOptMono, kOptRange, kOptStrip);
}

void cleanUp(char *msg, int errCode) {
	if (srcFile) {
		fclose(srcFile);
	}
	
	if (msg && errCode) {
		printf("An error occurred: %s\n", msg);
	} else if (msg && !errCode) {
		printf("%s\n", msg);
	}
	
	exit(errCode);
}

void bail_srcFileError() {
	cleanUp("Source file not set!", 1);
}

void argumentError(const char *arg) {
	printf("There was an argument error...\n");
	printf("Parameter for %s is missing...\n", arg);
	exit(1);
}

void printSpriteData(char *spriteData, int dataSize, int columns, int mono) {
	//mono specifies that the terminal is monochrome, so print characters
	//to differentiate between the colors; 1 = print color numbers
	
	int i = 0;

	for (i = 0; i < dataSize; i++) {
		//printf("%d (%d) ", spriteData[i], i);
		switch (spriteData[i]) {
			case 0:
				printf("\033[40m");
				break;
			case 1:
				printf("\033[41m");
				break;
			case 2:	
				printf("\033[43m");
				break;
			case 3:
				printf("\033[46m");
				break;
			default:
				printf("\033[40m");
		}
		if (mono)
			printf("%d ", spriteData[i]);
		else
			printf("  ");
		
		printf("\033[m");
		
		if ((i + 1) % (columns * NES_spriteWidth) == 0) {
			printf("\n");
		}
	}	
	
	//printf("\n");
}

void spriteToHtml(char *spriteData) {
	int i = 0;
	
	//printf("<html><head><title>sprite!!!</title></head><body><center>");
	printf("<td><table width=32 height=32 cellspacing=0 cellpadding=0><tr>");
	
	for (i = 0; i < 64; i++) {
		//printf("%d (%d) ", spriteData[i], i);
		switch (spriteData[i]) {
			case 0:
				printf("<td bgcolor=black>&nbsp;</td>");
				break;
			case 1:
				printf("<td bgcolor=red>&nbsp;</td>");
				break;
			case 2:	
				printf("<td bgcolor=yellow>&nbsp;</td>");
				break;
			case 3:
				printf("<td bgcolor=blue>&nbsp;</td>");
				break;
			default:
				printf("<td bgcolor=black>&nbsp;</td>");
		}
		
		if ((i + 1) % 8 == 0) {
			printf("</tr>");
		}
	}
	printf("</table></td>\n\n");
}

int printROM_info(FILE *ifile) {
	if (ifile == NULL) {
		printf("can't print rom info, NULL file...");
		exit(1);
	}
	printf("Filename:\t%s\n", srcFilename);
	printf("Filesize:\t%d\n", (int)NESGetFilesize(ifile));
	
	printf("Verify: \t");
	if (NESVerifyROM(ifile)) {
		printf("OK\n");
	} else {
		printf("NO GOOD\n");
		return -1;
	}
	
	printf("PRG Banks:\t%d\n", NESGetPrgBankCount(ifile));
	printf("CHR Banks:\t%d\n", NESGetChrBankCount(ifile));
	
	char *title = NESGetTitle(ifile, 1);
	printf("Has Title:\t%s\n", title == NULL ? "NO" : title);
	
	free(title);
	
	return 0;
}

char *appendPathComponent(char *source, char *append) {
        register char *os1;

        os1=source;
        while(*source++); //get to the end of source
         
        source -= 2; //back up 2 spots
        
		//check if source already has a path separator on the end
        if (*source != kPathSeparator) {
                source++;
                *source = kPathSeparator;
        }
        source++; //move on to \0 so we overwrite it (and not the path separator)
        
        while(*source++ = *append++); //do the appending
        
        return os1;
}

char *lastPathComponent(char *source) {
	char *last = rindex(source, kPathSeparator);
	
	if (last && last != '\0') {
		*last++;
		return last;
	} else { 
		return source;
	}
}
