#include <stdio.h>
#include <string.h>

FILE *fin;
FILE *fout;
FILE *fdbg;

void bitstring(unsigned short *chr, int *i) {
	static int j=0;

	if (j == 0) {
		*i+=1; //*i++;
		j=8;
		*chr = fgetc(fin);
	}
	*chr <<= 1;
	j--;
}

void dataout(unsigned char *buffer, unsigned char data) {
	static unsigned char sum=0,index=0;

	buffer[index++ & 0x3F] = data;
	sum+=data;
	fputc(sum,fout);
}

int checkopts(char *opt, int argc, char **argv) {
	int i;

	for (i = 4; i < argc; i++)
		if (strcmp(argv[i],opt) == 0) return 1;

	return 0;
}

int main(int argc, char **argv) {
	int debug = 0; //debug output
	int src,len,i=0,j=0,k=0;
	unsigned short chr;
	unsigned char tmp=0,tmp1=0,tmp2=0;
	unsigned char cache,buffer[0x40] = { 0 };
	char str[100] = { 0 };

	printf("\nSpartan X 2 Bitstring Unpacker v1.0, by Parasyte\n\n");

	if ((argc < 5) || (argc > 6)) {
		for (i = strlen(argv[0]); i > 0; i--) if (argv[0][i] == '\\') break; //filter directories
		strcpy(str,argv[0]+i+1);
		printf("Usage: %s <infile> <outfile> <source> <length> -debug\n\n",str);
		printf("  infile:   Filename of ROM for input\n");
		printf("  outfile:  Filename of output binary\n");
		printf("  source:   Source address (hex) of bitstring\n");
		printf("  length:   Data length (hex) of bitstring\n\n");
		printf("  -debug:   Enable debug output [optional]\n");
		return 1;
	}

	fin = fopen(argv[1],"rb");
	if (fin == NULL) {
		printf("Error loading input file\n");
		return 1;
	}
	fseek(fin,0,SEEK_END);
	#ifndef DEBUG
	if (ftell(fin) != 0x40010) {
		printf("Input file size error\n");
		return 1;
	}
	#endif

	fout = fopen(argv[2],"wb");
	if (fout == NULL) {
		printf("Error loading output file\n");
		return 1;
	}

	sscanf(argv[3], "%x", &src);
	if (src >= 0x40010) {
		printf("Source address error\n");
		return 1;
	}
	sscanf(argv[4], "%x", &len);
	if (len > 0x2000) {
		printf("Max. data length is 0x2000; setting length to max.\n");
		len = 0x2000;
	}
	if (src+len >= 0x40010) {
		printf("Data length error\n");
		return 1;
	}

	if (checkopts("-debug",argc,argv)) {
		debug = 1;
		fdbg = fopen("debug.txt","wt");
		if (fdbg == NULL) {
			printf("Error loading debug file\n");
			return 1;
		}
	}

	printf("Starting unpack\\decrypt process...\n Source: 0x%04X\n Length: 0x%04X\n\n",src,len);

	fseek(fin, src, SEEK_SET);
	cache = fgetc(fin);

	while (i < (len-1)) {
		bitstring(&chr,&i);
		if (chr & 0x0100) { //control bit 1, cache byte

			if (debug) {
				fprintf(fdbg,"$%04X - 0x%02X (cache)\n",j,cache);
				j++;
			}

			dataout(buffer,cache);
			continue;
		}
		bitstring(&chr,&i);
		if (chr & 0x0100) { //control bit 2, LZ copy

			for (k = 3; k <= 8; k++) { //6-bit data, LZ source
				bitstring(&chr,&i);
				tmp |= ((chr & 0x0100) >> k);
			}
			for (k = 3; k <= 8; k++) { //6-bit data, LZ length - 2
				bitstring(&chr,&i);
				tmp1 |= ((chr & 0x0100) >> k);
			}
			tmp1+=2;

			if (debug) {
				fprintf(fdbg,"$%04X - (LZ Copy) Source: 0x%02X, Length: 0x%02X, Data:  ",j,tmp,tmp1);
				j+=tmp1;
			}

			for (k = 0; k < tmp1; k++) {
				tmp2 = buffer[tmp++ & 0x3F];
				dataout(buffer,tmp2);

				if (debug) fprintf(fdbg,"%02X ",tmp2);
			}

			if (debug) fprintf(fdbg,"\n",tmp2);

			tmp=0;
			tmp1=0;
			continue;
		}
		for (k = 1; k <= 8; k++) { //8-bit data
			bitstring(&chr,&i);
			tmp |= ((chr & 0x0100) >> k);
		}

		if (debug) {
			fprintf(fdbg,"$%04X - 0x%02X\n",j,tmp);
			j++;
		}

		dataout(buffer,tmp);
		tmp=0;
	}

	fclose(fin);
	fclose(fout);
	if (debug) fclose(fdbg);

	printf("Done!\n");

	return 0;
}
