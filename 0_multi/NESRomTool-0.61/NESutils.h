/*
 *  NESutils.h
 *  NESRomTool
 *
 *  Created by spike on Sat May 24 2003.
 *  Copyright (c) 2003 Sadistech. All rights reserved.
 *
 */

#ifndef _NES_UTIL_H_
#define _NES_UTIL_H_

#include <stdio.h>
//#include "NESSprite.h"

#ifdef __cplusplus
extern "C" {
#endif

//header stuff
#define NES_headerPrefix "NES\x01a"
#define NES_headerPrefixOffset 0
#define NES_headerSize 16

#define NES_prgCountOffset 4
#define NES_chrCountOffset 5

//datasize from ROM file (.nes) - 16 bytes
#define NES_romSpriteSize 16

//half of the romSpriteSize (NES_romSpriteSize / 2) = 8 bytes
#define NES_romSpriteChannelSize 8

//datasize from RAW file (.raw) - 8 x 8 bytes
#define NES_rawSpriteSize 64

#define NES_spriteWidth 8
#define NES_spriteHeight 8

//the number of sprites stored in each CHR
#define NES_spritesPerChr 512
//the max number of sprites in each PRG (usually not completely filled)
#define NES_spritesPerPrg 1024

//PRG_bankSize is 16K	(program data (somtimes graphic))
//CHR_bankSize is 8K	(graphic data)
#define NES_prgBankSize 16384
#define NES_chrBankSize 8192

//for titling ROMs:
#define NES_romTitleBlockSize 128

//return values for functions
typedef enum {
	nesErr = -1,
	nesNoErr = 0,
} NESErrorCode;

typedef enum {
	nesHMode = 0,
	nesVMode = 1,
} NESSpriteMode;

#define bool int

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

//for converting between ROM sprite data and RAW sprite data
char NESCombineBits(int a, int b, int n);
char *NESBreakBits(char c);

//returns the number of PRG and CHR banks respectively
unsigned int NESGetPrgBankCount(FILE *ifile);
unsigned int NESGetChrBankCount(FILE *ifile);

//extracts the PRG and CHR banks to a file
NESErrorCode NESExtractPrgBank(FILE *fromFile, FILE *toFile, int n);
NESErrorCode NESExtractChrBank(FILE *fromFile, FILE *toFile, int n);

//returns the PRG and CHR banks from a file
char *NESGetPrgBank(FILE *ifile, int n);
char *NESGetChrBank(FILE *ifile, int n);

//takes a PRG or CHR bank (full file) from ifile and puts it into the nth bank in ofile
NESErrorCode NESInjectPrgBankData(FILE *ofile, char *prgData, int n);
NESErrorCode NESInjectChrBankData(FILE *ofile, char *chrData, int n);

NESErrorCode NESInjectPrgBank(FILE *ofile, FILE *ifile, int n);
NESErrorCode NESInjectChrBank(FILE *ofile, FILE *ifile, int n);

//sprite conversion stuff
//char *NESConvertSpriteDataToRaw(char *spriteData, int size);
//char *NESConvertRawToSpriteData(char *rawData, int size);

//sprite extraction stuff
char *NESGetSpriteDataFromChrBank(char *chrData, int n);
char *NESGetSpriteDataRangeFromChrBank(char *chrData, int startIndex, int endIndex);

NESErrorCode NESExtractSprite(FILE *ifile, FILE *ofile, int chrIndex, int n);
NESErrorCode NESExtractSpriteRange(FILE *ifile, FILE *ofile, int chrIndex, int startIndex, int endIndex);

//sprite injection stuff
NESErrorCode NESInjectSpriteFile(FILE *ofile, FILE *spriteFile, int chrIndex, int spriteIndex);
NESErrorCode NESInjectSpriteData(FILE *ofile, char *spriteData, int chrIndex, int spriteIndex);

NESErrorCode NESInjectSpriteStripFile(FILE *ofile, FILE *ifile, int chrIndex, int startIndex);
NESErrorCode NESInjectSpriteStrip(FILE *ofile, char *spriteData, int size, int chrIndex, int startIndex);

NESErrorCode NESInjectCompoundSpriteFile(FILE *ofile, FILE *ifile, int columns, NESSpriteMode mode, int chrIndex, int startIndex);
NESErrorCode NESInjectCompoundSprite(FILE *ofile, char *spriteData, int size, int columns, NESSpriteMode mode, int chrIndex, int startIndex);

//sprite assembling stuff
char *NESMakeCompoundSprite(char *spriteData, int size, int columns, NESSpriteMode mode);

//title functions
bool NESHasTitle(FILE *ifile);
char *NESGetTitle(FILE *ifile, int strip);
NESErrorCode NESSetTitle(FILE *ofile, char *title);
NESErrorCode NESRemoveTitle(FILE *ofile);

//some utility functions
long NESGetFilesize(FILE *ifile);
bool NESVerifyROM(FILE *ifile);

int NESGetOffset(int x, int y, int width);

#ifdef __cplusplus
};
#endif

#endif /* _NES_UTIL_H_ */