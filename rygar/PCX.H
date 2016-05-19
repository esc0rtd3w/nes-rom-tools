#include <dos.h>

struct pcx_header
   {
   char manufacturer;             // Always set to 0
   char version;                  // Always 5 for 256-color files
   char encoding;                 // Always set to 1
   char bits_per_pixel;           // Should be 8 for 256-color files
   int  xmin,ymin;                // Coordinates for top left corner
   int  xmax,ymax;                // Width and hieght of image
   int  hres;                     // Horizontal resolution of image
   int  vres;                     // Vertical resolution of image
   char palette16[48];            // EGA palette; not used for 8-bit
   char reserved;                 // Reserved for future use
   char color_planes;             // Color planes
   int  bytes_per_line;           // Number of bytes in 1 line
   int  palette_type;             // Should be 2 for color palette
   char filler[58];               // Nothing but junk
   };

void showpcx(char* file)
{
FILE *fp=fopen(file,"rb");
long count;
unsigned char byte,run_length;
fseek(fp,sizeof(pcx_header),SEEK_SET);
for(count=0;count<64000;count++)
   {
   byte=getc(fp);
   if(byte<192) pokeb(0xa000, count, byte); //*(buffer+count)=byte;
   else
      {
      run_length=byte-192;
      byte=getc(fp);
      _fmemset((void far *)MK_FP(0xa000, count),byte,run_length);
      count+=(run_length-1);
      }
   }
fclose(fp);
}

char *readpcx(char* file)
{
long count;
unsigned char byte,run_length;
FILE *fp=fopen(file,"rb");
char *array=new char[64000];
if(!array)return NULL;
fseek(fp,sizeof(pcx_header),SEEK_SET);
for(count=0;count<64000;count++)
   {
   byte=getc(fp);
   if(byte<192)array[count]=byte;
   else
      {
      run_length=byte-192;
      byte=getc(fp);
      memset(array+count,byte,run_length);
      count+=(run_length-1);
      }
   }
fclose(fp);
return array;
}

char *readpcx2(int h, int w, char* file)
{
long count;
unsigned char byte,run_length;
FILE *fp=fopen(file,"rb");
char *array=new char[h*w];
if(!array)return NULL;
fseek(fp,sizeof(pcx_header),SEEK_SET);
for(count=0;count<h*w;count++)
   {
   byte=getc(fp);
   if(byte<192)array[count]=byte;
   else
      {
      run_length=byte-192;
      byte=getc(fp);
      memset(array+count,byte,run_length);
      count+=(run_length-1);
      }
   }
fclose(fp);
return array;
}

void pcxpalette(char *file)
{
int i;
unsigned char pal[3];
FILE *fp=fopen(file,"rb");
fseek(fp,-(256*3),SEEK_END);
for(i=0;i<256;i++)
	{
	fread(pal,1,3,fp);
	outportb(0x3c8,i);
	outportb(0x3c9,pal[0]>>2);
	outportb(0x3c9,pal[1]>>2);
	outportb(0x3c9,pal[2]>>2);
	}
fclose(fp);
}

char *readpartpcx(char* file,int x1,int y1,int x2,int y2)
{
int height=y2-y1,length=x2-x1,x,y,i;
long count,ncount=0;
unsigned char byte,run_length;
char *array=new char[height*length];
if(!array)return NULL;
FILE *fp=fopen(file,"rb");
fseek(fp,sizeof(pcx_header),SEEK_SET);
for(count=0;count<64000;count++)
   {
   byte=getc(fp);
   if(byte<192)
	{
	y=count/320;
	x=count%320;
	if(y>=y1&&y<=y2&&x>=x1&&x<=x2)
		{
		array[ncount]=byte;
		ncount++;
		}
	}
   else
      {
      run_length=byte-192;
      byte=getc(fp);
      for(i=0;i<run_length;i++)
	{
	y=(count+i)/320;
	x=(count+i)%320;
	if(y>=y1&&y<=y2&&x>=x1&&x<=x2)
		{
		array[ncount]=byte;
		ncount++;
		}
	}
      count+=(run_length-1);
      if(ncount>height*length)break;
      }
   }
fclose(fp);
return array;
}

void showarray(char* array,int x,int y,int height,int length)
{                         //shows array...trims black edges
for(int i=0;i<height;i++)
  {
  for(int b=0;b<length;b++)
    {
    if(array[(i*length)+b])
      movedata(FP_SEG(array), FP_OFF(array) + (i * length) + b,
      0xa000, (y + i) * 320 + b + x, 1);
    }
  }
}
