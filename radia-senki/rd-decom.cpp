/*Radia Decompressor
by Griffin Knodle, a.k.a. Jair, 8/6/98
E-mail:gknodle@trinity.edu
http://www.resnet.trinity.edu/users/gknodle/

TERMS OF USE

This program is distributed with its source code. You may use,
distribute, and modify it freely. Only two restrictions: These terms of use 
must stay the same, and you must always include the source code with the
program. Oh, and I'd appreciate it if you credit me as the original
author.*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<io.h>

void outputChar(FILE*,unsigned char);

void main(){

  int point;
  long int filePos=0x107b7;
  long int success;
  FILE* output;
  long int count;
  int word=0x05;
  char junk[24];
            
  point=open("radia.nes",O_RDONLY);

  output=fopen("radiacom.tbl","w");
  
  success=lseek(point,filePos,0);
  printf("Offset:%lX\n",success);

  readWord:

  _read(point,junk,24);

  /*for(count=0;count<24;count++)
    printf("%02X",junk[count]);
  printf("\n");*/

  fprintf(output,"B3%02X=",word);

  for(count=0;count<24;count++){
    //printf("Read %c (%X)\n",junk[count],junk[count]);
    if(junk[count]==-75)
      break;
    outputChar(output,junk[count]);
    }

  word++;
  filePos=filePos+count+1;
  fprintf(output,"\n");

  lseek(point,filePos,0);

  if(word<0x100) goto readWord;

  fclose(output);

  //SEEK_CUR
  }

void outputChar(FILE* output,unsigned char val){
  if(val==0x00) fprintf(output," ");
  if(val==0x04) fprintf(output,"a");
  if(val==0x05) fprintf(output,"i");
  if(val==0x06) fprintf(output,"u");
  if(val==0x07) fprintf(output,"e");
  if(val==0x08) fprintf(output,"o");
  if(val==0x09) fprintf(output,"ka");
  if(val==0x0A) fprintf(output,"ki");
  if(val==0x0B) fprintf(output,"ku");
  if(val==0x0C) fprintf(output,"ke");
  if(val==0x0D) fprintf(output,"ko");
  if(val==0x0E) fprintf(output,"sa");
  if(val==0x0F) fprintf(output,"shi");
  if(val==0x10) fprintf(output,"su");
  if(val==0x11) fprintf(output,"se");
  if(val==0x12) fprintf(output,"so");
  if(val==0x13) fprintf(output,"ta");
  if(val==0x14) fprintf(output,"chi");
  if(val==0x15) fprintf(output,"tsu");
  if(val==0x16) fprintf(output,"te");
  if(val==0x17) fprintf(output,"to");
  if(val==0x18) fprintf(output,"na");
  if(val==0x19) fprintf(output,"ni");
  if(val==0x1A) fprintf(output,"nu");
  if(val==0x1B) fprintf(output,"ne");
  if(val==0x1C) fprintf(output,"no");
  if(val==0x1D) fprintf(output,"ha");
  if(val==0x1E) fprintf(output,"hi");
  if(val==0x1F) fprintf(output,"fu");
  if(val==0x20) fprintf(output,"he");
  if(val==0x21) fprintf(output,"ho");
  if(val==0x22) fprintf(output,"ma");
  if(val==0x23) fprintf(output,"mi");
  if(val==0x24) fprintf(output,"mu");
  if(val==0x25) fprintf(output,"me");
  if(val==0x26) fprintf(output,"mo");
  if(val==0x27) fprintf(output,"ya");
  if(val==0x28) fprintf(output,"yu");
  if(val==0x29) fprintf(output,"yo");
  if(val==0x2A) fprintf(output,"ra");
  if(val==0x2B) fprintf(output,"ri");
  if(val==0x2C) fprintf(output,"ru");
  if(val==0x2D) fprintf(output,"re");
  if(val==0x2E) fprintf(output,"ro");
  if(val==0x2f) fprintf(output,"wa");
  if(val==0x30) fprintf(output,"0");
  if(val==0x31) fprintf(output,"1");
  if(val==0x32) fprintf(output,"2");
  if(val==0x33) fprintf(output,"3");
  if(val==0x34) fprintf(output,"4");
  if(val==0x35) fprintf(output,"5");
  if(val==0x36) fprintf(output,"6");
  if(val==0x37) fprintf(output,"7");
  if(val==0x38) fprintf(output,"8");
  if(val==0x39) fprintf(output,"9");
  if(val==0x3a) fprintf(output,"A");
  if(val==0x3b) fprintf(output,"B");
  if(val==0x3c) fprintf(output,"C");
  if(val==0x3d) fprintf(output,"D");
  if(val==0x3e) fprintf(output,"E");
  if(val==0x3f) fprintf(output,"F");
  if(val==0x40) fprintf(output,"o");
  if(val==0x41) fprintf(output,"n");
  if(val==0x42) fprintf(output,"ba");
  if(val==0x43) fprintf(output,"gi");
  if(val==0x44) fprintf(output,"A");
  if(val==0x45) fprintf(output,"I");
  if(val==0x46) fprintf(output,"U");
  if(val==0x47) fprintf(output,"E");
  if(val==0x48) fprintf(output,"O");
  if(val==0x49) fprintf(output,"KA");
  if(val==0x4A) fprintf(output,"KI");
  if(val==0x4B) fprintf(output,"KU");
  if(val==0x4C) fprintf(output,"KE");
  if(val==0x4D) fprintf(output,"KO");
  if(val==0x4E) fprintf(output,"SA");
  if(val==0x4F) fprintf(output,"SHI");
  if(val==0x50) fprintf(output,"SU");
  if(val==0x51) fprintf(output,"SE");
  if(val==0x52) fprintf(output,"SO");
  if(val==0x53) fprintf(output,"TA");
  if(val==0x54) fprintf(output,"CHI");
  if(val==0x55) fprintf(output,"TSU");
  if(val==0x56) fprintf(output,"TE");
  if(val==0x57) fprintf(output,"TO");
  if(val==0x58) fprintf(output,"NA");
  if(val==0x59) fprintf(output,"NI");
  if(val==0x5A) fprintf(output,"NU");
  if(val==0x5B) fprintf(output,"NE");
  if(val==0x5C) fprintf(output,"NO");
  if(val==0x5D) fprintf(output,"HA");
  if(val==0x5E) fprintf(output,"HI");
  if(val==0x5F) fprintf(output,"FU");
  if(val==0x60) fprintf(output,"HE");
  if(val==0x61) fprintf(output,"HO");
  if(val==0x62) fprintf(output,"MA");
  if(val==0x63) fprintf(output,"MI");
  if(val==0x64) fprintf(output,"MU");
  if(val==0x65) fprintf(output,"ME");
  if(val==0x66) fprintf(output,"MO");
  if(val==0x67) fprintf(output,"YA");
  if(val==0x68) fprintf(output,"RU");
  if(val==0x69) fprintf(output,"RE");
  if(val==0x6A) fprintf(output,"RO");
  if(val==0x6b) fprintf(output,"WA");
  if(val==0x6C) fprintf(output,"'A");
  if(val==0x6D) fprintf(output,"'I");
  if(val==0x6E) fprintf(output,"'YU");
  if(val==0x6F) fprintf(output,"'YO");
  if(val==0x70) fprintf(output,"O");
  if(val==0x71) fprintf(output,"N");
  if(val==0x73) fprintf(output,"ge");
  if(val==0x74) fprintf(output,"YU");
  if(val==0x75) fprintf(output,"YO");
  if(val==0x76) fprintf(output,"RA");
  if(val==0x77) fprintf(output,"RI");
  if(val==0x78) fprintf(output,"'U");
  if(val==0x79) fprintf(output,"'E");
  if(val==0x7a) fprintf(output,"'");
  if(val==0x7b) fprintf(output,",");
  if(val==0x7C) fprintf(output,"'O");
  if(val==0x7d) fprintf(output,"'YA");
  if(val==0x7f) fprintf(output,"..");
  if(val==0x7e) fprintf(output,"?");
  if(val==0x80) fprintf(output,"G");
  if(val==0x81) fprintf(output,"H");
  if(val==0x82) fprintf(output,"I");
  if(val==0x83) fprintf(output,"J");
  if(val==0x84) fprintf(output,"K");
  if(val==0x85) fprintf(output,"L");
  if(val==0x86) fprintf(output,"N");
  if(val==0x87) fprintf(output,"M");
  if(val==0x88) fprintf(output,"O");
  if(val==0x89) fprintf(output,"P");
  if(val==0x8A) fprintf(output,"Q");
  if(val==0x8B) fprintf(output,"R");
  if(val==0x8C) fprintf(output,"S");
  if(val==0x8D) fprintf(output,"T");
  if(val==0x8E) fprintf(output,"U");
  if(val==0x8F) fprintf(output,"V");
  if(val==0x90) fprintf(output,"W");
  if(val==0x91) fprintf(output,"X");
  if(val==0x92) fprintf(output,"Y");
  if(val==0x93) fprintf(output,"Z");
  if(val==0x94) fprintf(output,"'a");
  if(val==0x95) fprintf(output,"'i");
  if(val==0x96) fprintf(output,"'u");
  if(val==0x97) fprintf(output,"'e");
  if(val==0x98) fprintf(output,"'o");
  if(val==0x99) fprintf(output,"'ya");
  if(val==0x9a) fprintf(output,"'yu");
  if(val==0x9b) fprintf(output,"'yo");
  if(val==0x9c) fprintf(output,"'");
  if(val==0x9d) fprintf(output,"~");
  if(val==0xa4) fprintf(output,".");
  if(val==0xa5) fprintf(output,"!");
  if(val==0xa6) fprintf(output,"-");
  if(val==0xa8) fprintf(output,"\"");
  if(val==0xa9) fprintf(output,"\"");
  if(val==0xAA) fprintf(output,"\"");
  if(val==0xab) fprintf(output,"\"");
  if(val==0xac) fprintf(output,"(");
  if(val==0xad) fprintf(output,")");
  if(val==0xaf) fprintf(output,"ze");
  if(val==0xc0) fprintf(output,"ga");
  if(val==0xc1) fprintf(output,"gi");
  if(val==0xc2) fprintf(output,"gu");
  if(val==0xc3) fprintf(output,"ge");
  if(val==0xc4) fprintf(output,"go");
  if(val==0xc5) fprintf(output,"za");
  if(val==0xc6) fprintf(output,"ji");
  if(val==0xc7) fprintf(output,"zu");
  if(val==0xc8) fprintf(output,"ze");
  if(val==0xc9) fprintf(output,"zo");
  if(val==0xca) fprintf(output,"da");
  if(val==0xcb) fprintf(output,"ji");
  if(val==0xcc) fprintf(output,"zu");
  if(val==0xcd) fprintf(output,"de");
  if(val==0xce) fprintf(output,"do");
  if(val==0xcf) fprintf(output,"ba");
  if(val==0xd0) fprintf(output,"bi");
  if(val==0xd1) fprintf(output,"bu");
  if(val==0xd2) fprintf(output,"be");
  if(val==0xd3) fprintf(output,"bo");
  if(val==0xd4) fprintf(output,"GA");
  if(val==0xd5) fprintf(output,"GI");
  if(val==0xd6) fprintf(output,"GU");
  if(val==0xd7) fprintf(output,"GE");
  if(val==0xd8) fprintf(output,"GO");
  if(val==0xD9) fprintf(output,"ZA");
  if(val==0xDA) fprintf(output,"JI");
  if(val==0xdb) fprintf(output,"ZU");
  if(val==0xdC) fprintf(output,"ZE");
  if(val==0xdD) fprintf(output,"ZO");
  if(val==0xDE) fprintf(output,"DA");
  if(val==0xDF) fprintf(output,"VU");
  if(val==0xE0) fprintf(output,"ZU");
  if(val==0xE1) fprintf(output,"DE");
  if(val==0xE2) fprintf(output,"DO");
  if(val==0xE3) fprintf(output,"BA");
  if(val==0xE4) fprintf(output,"BI");
  if(val==0xE5) fprintf(output,"BU");
  if(val==0xE6) fprintf(output,"BE");
  if(val==0xE7) fprintf(output,"BO");
  if(val==0xE8) fprintf(output,"pa");
  if(val==0xe9) fprintf(output,"pi");
  if(val==0xea) fprintf(output,"pu");
  if(val==0xeb) fprintf(output,"pe");
  if(val==0xec) fprintf(output,"po");
  if(val==0xED) fprintf(output,"PA");
  if(val==0xEE) fprintf(output,"PI");
  if(val==0xEF) fprintf(output,"PU");
  if(val==0xF0) fprintf(output,"PE");
  if(val==0xF1) fprintf(output,"PO");
  }