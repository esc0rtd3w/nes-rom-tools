/* Graphics Extractor v.1.1
by Griffin Knodle, a.k.a. Jair, 10/15/98
E-mail: gknodle@trinity.edu
http://fly.to/vale

TERMS OF USE

This program is distributed with its source code. You may use,
distribute, and modify it freely. Only two restrictions: These terms of use 
must stay the same, and you must always include the source code with the
program. Oh, and I'd appreciate it if you credit me as the original
author.*/

#include<stdio.h>
#include<stdlib.h>
#include "vale.h"

void convert(char*,int,int,int);
void prepBMP(int,int);

void main(){   
  int input;
  int output;
  long int offset;
  char buffer[512];
  long int tileCount;
  int row;
  int bytesRead;
  char fileName[35]; 
  char outputName[35];

  srcin:
  printf("File to extract from:");
  getString(30, fileName);
  addExt(fileName, "nes");
  input = openFile(fileName, 'r');
  if(input == -1){
    printf("Couldn't open %s!\n\n", fileName);
    goto srcin;
    }

  destin:
  printf("Bitmap to output to:");
  getString(30, outputName);
  changeExt(outputName, "bmp");
  output = openFile(outputName, 't');
  if(output == -1){
    printf("Couldn't open %s!\n\n", outputName);
    goto destin;
    }

  printf("\nEnter starting address:");
  offset=hexInput();

  printf("\nExtract how many tiles?");
  tileCount=hexInput();
  prepBMP(output,tileCount);
  row = (tileCount - 1) / 32 + 1;

  lseek(input,offset + (long) (row-1) * 512, 0);
  bytesRead= _read(input,buffer,512);

  if (bytesRead / 16 < ((tileCount%32==0)? 32 : tileCount%32)){
    printf("File not long enough!");
    exit(1);
    }

  convert(buffer,output,(tileCount%32==0) ? 32 : tileCount%32,row);

  row--;
  while(row > 0){

  if(row%32==0)
    printf("\n%li tiles left to extract....",(long) row*32);

  lseek(input,offset + (long) (row-1) * 512, 0);
  bytesRead= _read(input,buffer,512);

  convert(buffer,output,32,row);

  row--;
  }

  close(input);
  close(output);
  printf("\nDone!");
  }

void convert(char* buffer,int output,int tileCount,int rowCount){
  int tile;
  int row;
  int col;
  int bitMask;
  char pixelOut;
  char black[3],blue[3],red[3],white[3],gray[3];

  // Init. colors
  for(row=0;row<3;row++){
    black[row]=0;
    white[row]=0xFF;
    blue[row]=0;
    red[row]=0;
    gray[row]=0x80;
    }
  blue[0]=0xFF;
  red[2]=0xFF;

  for(row=7;row>-1;row--){
    for(tile=0; tile < tileCount; tile++){
      bitMask=128;
      for(col=0;col<8;col++){
        pixelOut=0;
        if( (int) buffer[row + tile * 16] & bitMask)
	  pixelOut++;
        if( (int) buffer[row + tile * 16 + 8] & bitMask)
	  pixelOut+=2;
        switch(pixelOut){
	  case 0:_write(output,black,3);break;
	  case 1:_write(output,blue,3);break;
	  case 2:_write(output,red,3);break;
          case 3:_write(output,white,3);break;
      	  }
        bitMask /= 2;
        }
      }
      if(tileCount < 32 && rowCount > 1)
	for(col=tileCount * 8; col < 256; col++)
	  _write(output,gray,3);
    }
  }

void prepBMP(int output,int tileCount){
  int x;
  long int yDim;
  char prepString[54];

  for(x=0;x<54;x++)
    prepString[x]=0;

  prepString[0]='B';
  prepString[1]='M';
  // File size (2-9) can be left out
  prepString[10]=0x36; // ???
  prepString[14]=0x28; // ???
  // x-dim
  if(tileCount > 31) prepString[19]=1;
  else prepString[18]= tileCount * 8;
  // y-dim
  yDim = (((tileCount - 1) / 32) + 1) * 8;
  if(yDim >= 16777216){
    prepString[25]= yDim / 16777216;
    yDim = yDim % 16777216;
    }
  if(yDim >= 65536){
    prepString[24]= yDim / 65536;
    yDim = yDim % 65536;
    }
  if(yDim >= 256){
    prepString[23]= yDim / 256;
    yDim = yDim % 256;
    }
  prepString[22] = yDim;
  prepString[26]=0x01; // ???
  prepString[28]=0x18; // ???
  // pixel count (34) can be left out

  _write(output,prepString,54);
  }
