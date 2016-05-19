/* Graphics Inserter v.1.1
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

void convert(int,char*);
void readData(int,char*,int,int);
int countTiles(int);
int countRows(int);

void main(){
  char tile[64];
  int input;
  int output;
  long int offset;
  int rowCount;
  int bytesRead;
  int tileCount;
  int readCount;
  char fileName[35]; 
  char outputName[35];

  srcin:
  printf("Name of bitmap to read:");
  getString(30, fileName);
  addExt(fileName, "bmp");
  input = openFile(fileName, 'r');
  if(input == -1){
    printf("Unable to open %s!\n\n", fileName);
    goto srcin;
    }
  destin:
  printf("File to output to:");
  getString(30, outputName);
  addExt(outputName, "nes");
  output = openFile(outputName, 'w');
  if(output == -1){
    printf("Unable to open %s!\n\n", outputName);
    goto destin;
    }

  printf("\nEnter starting address:");
  offset=hexInput();

  lseek(output,offset,0);

  rowCount= countRows(input);
  tileCount=countTiles(input);
  printf("\nCounted %li tile(s).",(long)(rowCount - 1) * 32 + tileCount);

  while(rowCount > 1){
    if(rowCount % 32==0)
      printf("\n%li tiles left to write....",(long) rowCount * 32);

    for(readCount=0;readCount < 32; readCount++){
      readData(input, tile, rowCount, readCount);
      convert(output, tile);
      }

    rowCount--;
    }

  for(readCount=0;readCount < tileCount; readCount++){
    readData(input, tile, 1, readCount);
    convert(output, tile);
    }

  printf("\nDone!");

  close(input);
  close(output);
  }

void convert(int output, char* tile){
  int row;
  char outputByte[16];
  int value;
  int col;

  for(row=0; row<16; row++) outputByte[row]=0;

  for(row=0; row<8; row++){
    value=128;  // bitmask
    for(col=0; col<8; col++){
      if(tile[row*8 + col] > 1){ // color 2 on
	outputByte[row + 8] += value;
	}
      if(tile[row*8 + col] % 2 == 1){ // color 1 on
	outputByte[row] += value;
	}
      value /= 2;
      }
    }

  _write(output,outputByte,16);
  }

void readData(int input,char* tile, int tileRow, int tileColumn){
  char buffer[24];
  long int offset;
  int rowLength;
  int row;
  int col;
  int color;

  if(countRows(input)==1){
    rowLength= countTiles(input) * 24;
    //printf("\nrowLength:%i",rowLength);
    }
  else rowLength= 768;

  for(row=7; row > -1; row--){
    offset= (long) ( ((long) tileRow - 1) * (long) 6144); //seek to tile row
    offset+= (long) ( (long) row * (long) rowLength); // seek to pixel row
    offset+= (long) ( (long) tileColumn * (long) 24); // seek to tile
    offset+= (long) 54; // account for BMP header
    //printf("offset:%li\n",offset);
    lseek(input, offset, 0);
    _read(input, buffer, 24);
    //printf("\n");
    for(col=0; col<8; col++){
      if(buffer[col * 3]==-1){  // Blue or white
        if(buffer[col * 3 + 1] == -1)
          color=3; //white
        else
          color=1; //blue
        }
      else{ // Red or black
	if(buffer[col * 3 + 2] == -1)
	  color=2; //red
        else
          color=0; //black
	}
      //printf("%i",color);
      tile[(7 - row) * 8 + col] = color;
      }
    }
  }

int countTiles(int input){
  int tileCount;
  int bytesRead;
  char buffer[192];

  for(tileCount=0; tileCount < 32; tileCount++){
    lseek(input,54 + tileCount * 192, 0);
    bytesRead= _read(input,buffer,192);

    if(bytesRead==0) break;

    if (bytesRead != 192 && bytesRead != 0){
      printf("Error reading BMP: bad data length.");
      exit(1);
      }
    }

  if(tileCount==32){
    for(tileCount=0; tileCount < 32; tileCount++){
      lseek(input, 54 + tileCount * 24, 0);
      _read(input, buffer, 24);
      if(buffer[0]==-0x80) break;
      }
    }

  return tileCount;
  }

int countRows(int input){
  int row;
  int check=1;
  char temp;

  for(row=0; check==1;){
    row++;
    lseek(input,(long) row * 6144 + 54, 0);
    check=_read(input, &temp, 1);
    if(row==100) break;
    }
  //printf("\n%i",row);
  return row;
  }
