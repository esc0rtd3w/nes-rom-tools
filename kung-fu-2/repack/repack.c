#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int outsize=2,debug = 0; //debug output

FILE *fin;
FILE *fout;
FILE *fdbg;

unsigned char *dataout(unsigned char data, int size) {
	static unsigned char chr=0;
	static int j=8;
	int i;

	if (size == 0) {
		chr |= 0xFF>>(8-j);
		return &chr;
	}

	for (i = (size-1); i >= 0; i--) {
		if (j == 0) {
			outsize++;
			fputc(chr,fout);
			if (debug) fputc(chr,fdbg);
			chr=0;
			j=8;
		}
		j--;
		chr |= (((data>>i)&1)<<j);
	}
}

int checkopts(char *opt, int argc, char **argv) {
	int i;

	for (i = 4; i < argc; i++)
		if (strcmp(argv[i],opt) == 0) return 1;

	return 0;
}

int main(int argc, char **argv) {
	int dst=0,len,i=0,j,k=0,l;
	unsigned short cachebuf[256] = { 0 };
	unsigned char chr,cache=0;
	unsigned char tmp=0,tmp1=0;
	unsigned char *output,buffer[0x40] = { 0 };
	char str[100] = { 0 };

	printf("\nSpartan X 2 Bitstring Repacker v1.0, by Parasyte\n\n");

	if ((argc < 4) || (argc > 6)) {
		for (i = strlen(argv[0]); i > 0; i--) if (argv[0][i] == '\\') break; //filter directories
		strcpy(str,argv[0]+i+1);
		printf("Usage: %s <infile> <outfile> <dest> [-0] [-debug]\n\n",str);
		printf("  infile:   Filename of input binary\n");
		printf("  outfile:  Filename of ROM for output\n");
		printf("  dest:     Desination address (hex) for bitstring\n");
		printf("  -0:       Allow using 0x00 as a cache value [optional]\n");
		printf("            (May result in larger bitstring)\n\n");
		printf("  -debug:   Enable debug output [optional]\n");
		return 1;
	}

	fin = fopen(argv[1],"rb");
	if (fin == NULL) {
		printf("Error loading input file\n");
		return 1;
	}
	fseek(fin,0,SEEK_END);
	len = ftell(fin);
	output = (unsigned char*)malloc(len);
	if (output == NULL) {
		printf("Unable to allocate memory\n");
		return 1;
	}

	fout = fopen(argv[2],"r+b");
	if (fout == NULL) {
		printf("Error loading output file\n");
		return 1;
	}
	fseek(fout,0,SEEK_END);
	if (ftell(fout) != 0x40010) {
		printf("Output file size error\n");
		return 1;
	}

	sscanf(argv[3], "%x", &dst);

	if (checkopts("-debug",argc,argv)) {
		debug = 1;
		fdbg = fopen("debug.bin","wb");
		if (fdbg == NULL) {
			printf("Error loading debug file\n");
			return 1;
		}
	}

	printf("Starting repack\\encrypt process...\n Destination: 0x%04X\n",dst);

	fseek(fin,0,SEEK_SET);
	fseek(fout,dst,SEEK_SET);

	while (i < len) {
		tmp = fgetc(fin);
		chr=tmp-tmp1;
		tmp1=tmp;
		output[i++] = chr;
		cachebuf[chr]++;
	}
	chr=0;
	tmp=1;
	if (checkopts("-0",argc,argv)) tmp=0;
	for (i = tmp; i < 256; i++) { //only check 0x00 if specified
		if (cachebuf[i] > chr) {
			chr = cachebuf[i];
			cache = i;
		}
	}
	printf(" Best possible cache value: 0x%02X (%d entries)\n\n",cache,cachebuf[cache]);

	fputc(cache,fout);
	if (debug) fputc(cache,fdbg);
	i=0;
	while (i < len) {
		tmp1=0;
		for (k = 0x3F; k >= 0; k--) { //control bit 2, LZ-copy
			j=0;
			l=0;
			while (j < 0x41) {
				if ((i+j) > len) break;
				if ((((j+k) & 0x3F) == ((i+l) & 0x3F)) && (j != 0) && (output[i+j] != cachebuf[l++])) break; //messy code which took me too long write! o_O
				if ((output[i+j] == buffer[(j+k) & 0x3F]) || (l>0)) cachebuf[j++] = output[i+j];           //basically, all of this just makes sure the LZ-copy is as efficient as possible
				else break;
			}
			if ((j >= 2) && (j > tmp1)) {
				tmp = k;
				tmp1 = j;
			}
		}
		j=0;
		for (k = 0; k < tmp1; k++) if (cachebuf[k] == cache) j++;
		if ((tmp1 >= 2) && ((j+((tmp1-j)*10)) >= 14)) { //ensure LZ-copy is actually useful. in many cases, cache compresses better than LZ-copy
			dataout(1,2);
			dataout(tmp,6); //LZ source
			dataout(tmp1-2,6); //LZ length

			while (tmp1 > 0) {
				buffer[i++ & 0x3F] = buffer[tmp++ & 0x3F];
				tmp1--;
			}
			continue;
		}

		chr = output[i];
		if (chr == cache) { //control bit 1, cache byte
			buffer[i++ & 0x3F] = chr;
			dataout(1,1);
			continue;
		}

		//8-bit data
		buffer[i++ & 0x3F] = chr;
		dataout(0,2);
		dataout(chr,8);
	}
	fputc(*dataout(0,0),fout);

	free(output);
	fclose(fin);
	fclose(fout);
	if (debug) {
		fputc(*dataout(0,0),fdbg);
		fclose(fdbg);
	}

	printf(" Repacked data size: 0x%04X bytes\n\nDone!\n",outsize);

	return 0;
}
