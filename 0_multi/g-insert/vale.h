/* Vale Header v.4.0
by Griffin Knodle, a.k.a. Jair, 10/15/98
E-mail: gknodle@trinity.edu
http://fly.to/vale

CONTENTS

long int hexInput()
   - Function used in Relative Searcher, Graphics Extractor, etc. to allow decimal
     or hexadecimal input.

void getString(int stringLength, char* stringToWriteTo)
   - Will only accept a given number of characters.

int openFile(char* nameOfFileToOpen, char openingMode)
   - Opens a file. Returns the handle for the int.
   - values for openingMode:
      - 'w' will create the file if it doesn't exist
      - 'r' won't create it and will return -1
      - 't' acts like 'w'and erases the file's previous contents if it already exists

void changeExt(char* stringToModify, char* extensionToAdd)
   - Takes a string and changes its .extension to .extensionToAdd.

void addExt(char* stringToModify, char* extensionToAdd)
   - Takes a string and adds .extensionToAdd if it doesn't have an extension yet.


TERMS OF USE

This program is distributed with its source code. You may use,
distribute, and modify it freely. Only two restrictions: These terms of use 
must stay the same, and you must always include the source code with the
program. Oh, and I'd appreciate it if you credit me as the original
author.*/

#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>

long int hexInput(){
  long int value=0;
  char hexFlag=0;
  char negFlag=0;
  char input[10];
  int charsRead=0;
  int x;

  for(charsRead=0; charsRead < 10; charsRead++){

  input[charsRead]=getch();

  if(input[charsRead]==13 && charsRead > 0){
    printf("\n");
    break; // enter
    }

  if(input[charsRead]==8){ //backspace
    charsRead--;
    if(charsRead==-1 && negFlag==1){
      negFlag=0;
      printf("%c",8);
      }
    if(charsRead==-1) continue; //not if nothing to erase
    if(hexFlag==1) hexFlag=0; // erase H
    else{ // or erase last digit
      charsRead--;
      }
    printf("%c",8);
    continue;
    }
     
  if(hexFlag==1){ // after typing H, only backspace or enter
    charsRead--;
    continue;
    }

  if(input[charsRead]=='h' || input[charsRead]=='H'){  // set H
    charsRead--;
    if(charsRead==-1) continue; // not if no value yet
    hexFlag=1;
    printf("h");
    continue;
    }
  if(input[charsRead]=='-'){ // set neg
    charsRead--;
    if(charsRead > -1) continue; // only at start
    if(negFlag==1) continue; // once is enough
    negFlag=1;
    printf("-");
    continue;
    }
  if(input[charsRead] > 96 && input[charsRead] < 103)
    input[charsRead] -= 32; // a-f -> A-F
  if(input[charsRead] > 64 && input[charsRead] < 71){
    printf("%c",input[charsRead]);
    continue;
    }
  if(input[charsRead] > 47 && input[charsRead] < 58){
    printf("%c",input[charsRead]);
    continue;
    }
  charsRead--;
  }

  if(hexFlag==0){
    for(x=0; x<charsRead; x++){
      if(input[x] > 64 && input[x] < 71){
	hexFlag=1;
	break;
	}
      }
    }

  for(x=0; x < charsRead; x++){ 
    if(hexFlag==1) value *= 16;
    else value *= 10;
    if(input[x] > 47 && input[x] < 58){// digit 0-9
      value += (input[x] - 48);
      }
    if(input[x] > 64 && input[x] < 71){ // hex digit A-F
      value += (input[x] - 55);
      }
    }

  if(negFlag==1) value = (-value);

  //printf("\n%li",value);
  return value;
  }

void getString(int length, char* target){
  int counter;
  char input;
  // Note: your string must be one char longer than "length", to leave room for
  // the '\0' end-of-string marker.

  for(counter=0; ; counter++){
    input=getch();
    if(input==13){ // enter
      printf("\n");
      break; // Note: no protection against 0-length entries
      }
    if(input==8){ //backspace
      if(counter==0){ // no input yet
	counter--;
	continue;
        }
      printf("%c",8);
      counter -= 2;
      continue;
      }
    if(counter==length){ // at max length
      counter--;
      continue;
      }
    target[counter]=input;
    printf("%c",input);
    }
  target[counter]=0;
  }

int openFile(char* fileName, char mode){
  int filePtr;
  FILE* temp;

  if(mode == 't') filePtr = open(fileName, O_RDWR | O_TRUNC);
  else filePtr = open(fileName, O_RDWR);

  if(filePtr== -1){ // unsuccessful
    if(mode=='r'){
      return -1;
      }

    temp=fopen(fileName, "w");
    fclose(temp);
    filePtr=open(fileName, O_RDWR);
    }
  return filePtr;
  }

void changeExt(char* target, char* ext){
  int c = 0, d = 0, end;

  while(target[c] != 0)
    c++;
  end = c;

  while(target[c] != '.'){
    c--;
    if(c == -1) break;
    }
  if(c == -1){
    c = end;
    target[c] = '.';
    }

  while(ext[d] != 0){
    c++;
    target[c] = ext[d];
    d++;
    }
  target[c + 1] = 0;
  }

void addExt(char* target, char* ext){
  int c = 0, d = 0, end;

  while(target[c] != 0)
    c++;
  end = c;

  while(target[c] != '.'){
    c--;
    if(c == -1) break;
    }
  if(c > -1)
    return;

  c = end;
  target[c] = '.';

  while(ext[d] != 0){
    c++;
    target[c] = ext[d];
    d++;
    }
  target[c + 1] = 0;
  }