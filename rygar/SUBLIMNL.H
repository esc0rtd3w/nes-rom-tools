// The OFFICIAL Subliminal Creations 8 C++/ASM HEADER File!  Ver 3.1 4/9/96
//                       v1.0 created on Nov 3rd 1995.
//
#define STEREO                // Define this for SBPro CT-1330 or later card.
#define OPL3                  // Also define this for SBPro CT-1600 or later.
#ifdef OPL3
  #define LEFT   0x10
  #define RIGHT	 0x20
#endif

#include <alloc.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fontseg, fontofs;                           // Font Driver Variables.
                                                // -----------------------------
unsigned IOport;                                // Sound Blaster port address
int base10(char **str, unsigned *val),          // Sound Blaster thing
    base16(char **str, unsigned *val),          // Sound Blaster thing
    getpx(int x, int y),                        // Get Pixel Routine
    mouse();                                    // Initialize Mouse
                                                // -----------------------------
                                                // Mouse Routines:
                                                // -----------------------------
void cls(unsigned char Col,unsigned char *Where),
     curse(int asc,int end),                    // Change Cursor in Text Mode
     cursor(int *Mask),                         // Change Cursor in MCGA Mode
     getmt(int*, int*, int*),                   // Get Position in Text Mode
     getmv(int*, int*, int*),                   // Get Position in MCGA Modeee
     hide(),                                    // Hide Mouse Cursor
     mousecents(int x, int y, int Threshold),   // Define Mouse Threshold (?)
     reset(),                                   // Reset Mouse Driver
     show(),                                    // Show Mouse Cursor
                                                // -----------------------------
                                                // MCGA Routines:
                                                // -----------------------------
     box(int bxx, int bxy, int bxxx, int bxxy, unsigned char bxc),
                                                // Draw an enclosed perimeter.
     bw(unsigned char pall),                    // Change MCGA Pal. to Grey Scale
     fadein(unsigned char pall),                // Fade in either palette
     fadeout(unsigned char pall),               // Fade either palette to black
     frame(int frx, int fry, int frrx, int frry, unsigned char frcc),
                                                // Draw 2 sets of parallels.
     frainpal(int rainoff),                     // Change palette to 'Rainbow'
     initvirt(int toggle),                      // Initialize Virtual Screen
     initvirt2(int toggle),                     // Initialize Virtual Screen #2
     installfont(),                             // Install Font Driver
     outtextxy(int tx, int ty, char *cs, unsigned char colr),
                                                // Text Plotting Routine
     pal(unsigned char cnum,                    //
         unsigned char rgbr, unsigned char rgbg, unsigned char rgbb),
                                                // Manually change a color
     pset(int ppx,int ppy,unsigned char ppc),   // Plot a pixel in MCGA mode
     sline(unsigned x1,unsigned y1,unsigned x2, // Draw a line between two
          unsigned y2, unsigned char colour),   // points in space.
     smode(int mode),                           // Change screen modes
     spal(int s8off),                           // Change palette to Subliminal
     whiteout(unsigned char pall),              // Fade MCGA screen out to white
     vpset(int x, int y, unsigned char Col, unsigned char *Where),
                                                // -----------------------------
                                                // Other Routines:
                                                // -----------------------------
     cdelay(long msec),                         // Delay for x/1000s of a second
     mydelay(unsigned long clocks),             // Alternate delay routine.
     wait(),                                    // Wait until screen refresh
                                                // -----------------------------
                                                // Sound Routines:
                                                // -----------------------------
     fm(int reg, int val),                      // Sound routine for ProFM2 Cards
     FMoutput(unsigned port, int reg, int val), // FM Sound player =)
     Profm1(int reg, int val),                  // Sound routine 4 ProFM1 Cards
     Profm2(int reg, int val),                  // Sound routine 4 ProFM2 Cards
     shutup();                                  // Stop SB FM Sound
struct SREGS segregs;                           // Initialize Registers
union REGS iReg, oReg;                          // Initialize Registers
unsigned ReadBlasterEnv                         // Get SB Environment
            (unsigned *port, unsigned *irq, unsigned *dma8,unsigned *dma16);
unsigned char *vaddr=NULL, *vaddr2=NULL,
              *vga=(unsigned char *) MK_FP(0xA000, 0);
/*

  Notes

  Page Flipping (Virtual Screen 1 to Screen): _fmemcpy(vga,vaddr,64000);
*/
//------------------------------------------------------------------------------
                                   int arrow[] =
//------------------------------------------------------------------------------
// String containing mouse mask for graphical cursor changing routines.
{0x9FFF, 0x8FFF, 0x87FF, 0x83FF, 0x81FF, 0x80FF, 0x807F, 0x803F,
 0x801F, 0x800F, 0x80FF, 0x887F, 0x987F, 0xFC3F, 0xFC3F, 0xFE3F,
 0x0000, 0x2000, 0x3000, 0x3800, 0x3C00, 0x3E00, 0x3F00, 0x3F80,
 0x3FC0, 0x3E00, 0x3600, 0x2300, 0x0300, 0x0180, 0x0180, 0x0000};
//------------------------------------------------------------------------------
                                    int cbit[] =
//------------------------------------------------------------------------------
// String containing mouse mask for graphical cursor changing routines.
{0xBFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
//------------------------------------------------------------------------------
                                    int hand[] =
//------------------------------------------------------------------------------
// String containing mouse mask for graphical cursor changing routines.
{0xE1FF, 0xE1FF, 0xE1FF, 0xE1FF, 0xE1FF, 0xE000, 0xE000, 0xE000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x1E00, 0x1200, 0x1200, 0x1200, 0x1200, 0x13FF, 0x1249, 0x1249,
 0xF249, 0x9001, 0x9001, 0x9001, 0x8001, 0x8001, 0x8001, 0xFFFF};
//------------------------------------------------------------------------------
                              unsigned char frainp[256*3] =
//------------------------------------------------------------------------------
// String containing palette values for palette manipulation routines.
{
60,0,0,   60,4,0,   60,8,0,   60,12,0,  60,16,0,  60,20,0,  60,24,0,  60,28,0,
60,32,0,  60,36,0,  60,40,0,  60,44,0,  60,48,0,  60,52,0,  60,56,0,  60,60,0,
56,60,0,  52,60,0,  48,60,0,  44,60,0,  40,60,0,  36,60,0,  32,60,0,  28,60,0,
24,60,0,  20,60,0,  16,60,0,  12,60,0,  8,60,0,   4,60,0,   0,60,0,   0,60,4,
0,60,8,   0,60,12,  0,60,16,  0,60,20,  0,60,24,  0,60,28,  0,60,32,  0,60,36,
0,60,40,  0,60,44,  0,60,48,  0,60,52,  0,60,56,  0,60,60,  0,56,60,  0,52,60,
0,48,60,  0,44,60,  0,40,60,  0,36,60,  0,32,60,  0,28,60,  0,24,60,  0,20,60,
0,16,60,  0,12,60,  0,8,60,   0,4,60,   0,0,60,   4,0,60,   8,0,60,   12,0,60,
16,0,60,  20,0,60,  24,0,60,  28,0,60,  32,0,60,  36,0,60,  40,0,60,  44,0,60,
48,0,60,  52,0,60,  56,0,60,  60,0,60,  60,0,56,  60,0,52,  60,0,48,  60,0,44,
60,0,40,  60,0,36,  60,0,32,  60,0,28,  60,0,24,  60,0,20,  60,0,16,  60,0,12,
60,0,8,   60,0,0,   60,4,0,   60,8,0,   60,12,0,  60,16,0,  60,20,0,  60,24,0,
60,28,0,  60,32,0,  60,36,0,  60,40,0,  60,44,0,  60,48,0,  60,52,0,  60,56,0,
60,60,0,  56,60,0,  52,60,0,  48,60,0,  44,60,0,  40,60,0,  36,60,0,  32,60,0,
28,60,0,  24,60,0,  20,60,0,  16,60,0,  12,60,0,  8,60,0,   4,60,0,   0,60,0,
0,60,4,   0,60,8,   0,60,12,  0,60,16,  0,60,20,  0,60,24,  0,60,28,  0,60,32,
0,60,36,  0,60,40,  0,60,44,  0,60,48,  0,60,52,  0,60,56,  0,60,60,  0,56,60,
0,52,60,  0,48,60,  0,44,60,  0,40,60,  0,36,60,  0,32,60,  0,28,60,  0,24,60,
0,20,60,  0,16,60,  0,12,60,  0,8,60,   0,4,60,   0,0,60,   4,0,60,   8,0,60,
12,0,60,  16,0,60,  20,0,60,  24,0,60,  28,0,60,  32,0,60,  36,0,60,  40,0,60,
44,0,60,  48,0,60,  52,0,60,  56,0,60,  60,0,60,  60,0,56,  60,0,52,  60,0,48,
60,0,44,  60,0,40,  60,0,36,  60,0,32,  60,0,28,  60,0,24,  60,0,20,  60,0,16,
60,0,12,  60,0,8,   60,0,0,   60,4,0,   60,8,0,   60,12,0,  60,16,0,  60,20,0,
60,24,0,  60,28,0,  60,32,0,  60,36,0,  60,40,0,  60,44,0,  60,48,0,  60,52,0,
60,56,0,  60,60,0,  56,60,0,  52,60,0,  48,60,0,  44,60,0,  40,60,0,  36,60,0,
32,60,0,  28,60,0,  24,60,0,  20,60,0,  16,60,0,  12,60,0,  8,60,0,   4,60,0,
0,60,0,   0,60,4,   0,60,8,   0,60,12,  0,60,16,  0,60,20,  0,60,24,  0,60,28,
0,60,32,  0,60,36,  0,60,40,  0,60,44,  0,60,48,  0,60,52,  0,60,56,  0,60,60,
0,56,60,  0,52,60,  0,48,60,  0,44,60,  0,40,60,  0,36,60,  0,32,60,  0,28,60,
0,24,60,  0,20,60,  0,16,60,  0,12,60,  0,8,60,   0,4,60,   0,0,60,   4,0,60,
8,0,60,   12,0,60,  16,0,60,  20,0,60,  24,0,60,  28,0,60,  32,0,60,  36,0,60,
40,0,60,  44,0,60,  48,0,60,  52,0,60,  56,0,60,  60,0,45,  60,0,30,  60,0,15};
//------------------------------------------------------------------------------
                          unsigned char spalette[256*3] =
//------------------------------------------------------------------------------
// String containing palette values for palette manipulation routines.
{0, 0, 0,                                       // 000 Black
 63, 0, 0,   61, 0, 0,                          // 001-002 Bright Reds
 58, 0, 0,   56, 0, 0,   53, 0, 0,   51, 0, 0,  // 003-006
 48, 0, 0,   46, 0, 0,   43, 0, 0,   41, 0, 0,  // 007-010
 38, 0, 0,   36, 0, 0,   33, 0, 0,   31, 0, 0,  // 011-014
 28, 0, 0,   26, 0, 0,   23, 0, 0,   21, 0, 0,  // 015-018
 18, 0, 0,   16, 0, 0,   13, 0, 0,   11, 0, 0,  // 019-022
  8, 0, 0,    6, 0, 0,    3, 0, 0,    1, 0, 0,  // 023-026 Dark Red
//---------------------------------------------///------------------------------
  0,63, 0,    0,61, 0,                          // 027-028 Bright Greens
  0,58, 0,    0,56, 0,    0,53, 0,    0,51, 0,  // 029-032
  0,48, 0,    0,46, 0,    0,43, 0,    0,41, 0,  // 033-036
  0,38, 0,    0,36, 0,    0,33, 0,    0,31, 0,  // 037-040
  0,28, 0,    0,26, 0,    0,23, 0,    0,21, 0,  // 041-044
  0,18, 0,    0,16, 0,    0,13, 0,    0,11, 0,  // 045-048
  0, 8, 0,    0, 6, 0,    0, 3, 0,    0, 1, 0,  // 049-052 Dark Green
//---------------------------------------------///------------------------------
  0, 0,63,    0, 0,61,                          // 053-054 Bright Blue
  0, 0,58,    0, 0,56,    0, 0,53,    0, 0,51,  // 055-058
  0, 0,48,    0, 0,46,    0, 0,43,    0, 0,41,  // 059-062
  0, 0,38,    0, 0,36,    0, 0,33,    0, 0,31,  // 063-066
  0, 0,28,    0, 0,26,    0, 0,23,    0, 0,21,  // 067-070
  0, 0,18,    0, 0,16,    0, 0,13,    0, 0,11,  // 071-074
  0, 0, 8,    0, 0, 6,    0, 0, 3,    0, 0, 1,  // 075-078 Dark Blue
//---------------------------------------------///------------------------------
 63,53, 0,   61,51, 0,                          // 079-080 Bright Yellow
 58,48, 0,   56,46, 0,   53,43, 0,   51,41, 0,  // 081-084
 48,38, 0,   46,36, 0,   43,33, 0,   41,31, 0,  // 085-088
 38,28, 0,   36,26, 0,   33,23, 0,   31,21, 0,  // 089-092
 28,18, 0,   26,16, 0,   23,13, 0,   21,11, 0,  // 093-096
 18, 8, 0,   16, 6, 0,   13, 3, 0,   11, 1, 0,  // 097-100
  8, 0, 0,    6, 0, 0,    3, 0, 0,    1, 0, 0,  // 101-104 Bright Brown (Hrmm)
//---------------------------------------------///------------------------------
 63, 0,63,   61, 0,61,                          // 105-106 Bright Purple
 58, 0,58,   56, 0,56,   53, 0,53,   51, 0,51,  // 107-110
 48, 0,48,   46, 0,46,   43, 0,43,   41, 0,41,  // 111-114
 38, 0,38,   36, 0,36,   33, 0,33,   31, 0,31,  // 115-118
 28, 0,28,   26, 0,26,   23, 0,23,   20, 0,21,  // 119-122
 18, 0,18,   16, 0,16,   13, 0,13,   11, 0,11,  // 123-126
  8, 0, 8,    6, 0, 6,    3, 0, 3,    1, 0, 1,  // 127-130 Dark Purple
//---------------------------------------------///------------------------------
  0,63,63,    0,61,61,                          //
  0,58,58,    0,56,56,    0,53,53,    0,51,51,  //
  0,48,48,    0,46,46,    0,43,43,    0,41,41,  //
  0,38,38,    0,36,36,    0,33,33,    0,31,31,  //
  0,28,28,    0,26,26,    0,23,23,    0,21,21,  //
  0,18,18,    0,16,16,    0,13,13,    0,11,11,  //
  0, 8, 8,    0, 6, 6,    0, 3, 3,    0, 1, 1,  // 131-156 Turquoise
//---------------------------------------------///------------------------------
 63,63,63,   61,61,61,                          //
 58,58,58,   56,56,56,   53,53,53,   51,51,51,  //
 48,48,48,   46,46,46,   43,43,43,   41,41,41,  //
 38,38,38,   36,36,36,   33,33,33,   31,30,31,  //
 28,28,28,   26,26,26,   23,23,23,   20,21,21,  //
 18,18,18,   16,16,16,   13,13,13,   11,11,11,  //
  8, 8, 8,    6, 6, 6,    3, 3, 3,    1, 1, 1,  // 157-182 Grey Scale
//---------------------------------------------///------------------------------
 63, 3, 3,   63, 7, 7,   63,11,11,   63,15,15,  //
 63,19,19,   63,23,23,   63,27,27,   63,31,31,  //
 63,35,35,   63,39,39,   63,43,43,   63,47,47,  //
 63,51,51,   63,55,55,   63,59,59,              // 183-197 Peachy
//---------------------------------------------///------------------------------
 59,63,59,   55,63,55,   51,63,51,   47,63,47,  //
 43,63,43,   39,63,39,   35,63,35,   31,63,31,  //
 27,63,27,   23,63,23,   19,63,19,   15,63,15,  //
 11,63,11,    5,63, 5,    1,63, 1,              // 198-212 Minty
//---------------------------------------------///------------------------------
  3, 3,63,    7, 7,63,   11,11,63,   15,15,63,  //
 19,19,63,   23,23,63,   27,27,63,   31,31,63,  //
 35,35,63,   39,39,63,   43,43,63,   47,47,63,  //
 51,51,63,   55,55,63,   59,59,63,              // 213-227 Sea
//---------------------------------------------///------------------------------
 63,54,36,   63,50,32,   63,46,28,   63,42,24,  //
 63,38,20,   63,34,16,   63,30,12,   63,26, 8,  //
 63,22, 4,   63,18, 0,   63,14, 0,   63,10, 0,  //
 63, 6, 0,   63, 2, 0,   63, 0, 0,              // 228-242 Orange
//---------------------------------------------///------------------------------
};                                              //243-255 Reserved
//------------------------------------------------------------------------------
                        int base16(char **str, unsigned *val)
//------------------------------------------------------------------------------
// Sound Card Stuff                          //
{char c;                                     //
 int digit;                                  //
 *val=0;                                     //
 while (**str != ' ')                        //
   {c=toupper(**str);                        //
     if (c>='0' && c<='9')                   //
       digit=c-'0';                          //
     else                                    //
       if (c>='A' && c<='F')                 //
         digit=c-'A'+10;                     //
    *val=*val * 16+digit;                    //
    (*str)++;                                //
   }                                         //
 return 0;                                   //
}                                            //
//------------------------------------------------------------------------------
                      int base10(char **str, unsigned *val)
//------------------------------------------------------------------------------
// Sound Card Stuff                          //
{char c;                                     //
 int digit;                                  //
 *val=0;                                     //
 while (**str != ' ')                        //
   {c=toupper(**str);                        //
    if (c>='0' && c<='9')                    //
      digit=c-'0';                           //
    *val=*val*10+digit;                      //
    (*str)++;                                //
   }                                         //
 return 0;                                   //
}                                            //
//------------------------------------------------------------------------------
       void box(int bxx, int bxy, int bxxx, int bxxy, unsigned char bxc)
//------------------------------------------------------------------------------
// Routine to draw a filled in perimeter.    //
{int ty=bxy;                                 // Initialize Verticle Tracer
 for (int tx=bxx; ty<bxxy+1; tx++)           //
  {pset(tx,ty,bxc);                          // -Plot pixel on tracers
        if (tx==bxxx)                        // -If Horizontal Tracer is out of
                {tx=bxx-1;                   // --bounds, reset Horiz. Tracer
                 ty++;}}}                    // --and increase Vertical Tracer.
//------------------------------------------------------------------------------
                       void bw(unsigned char pall)
//------------------------------------------------------------------------------
// Routine to average all onscreen colors (turn to black and white)
{unsigned char rr=0,                         // Set red value at black
               bb=0,                         // Set blue value at black
               gg=0,                         // Set green value at black
               avg=0;                        // Set average color at black
 for (short b=0; b<256; b++)                 // Loop until all colors are avg.
  {if (pall==0)                              // -If using Subliminal Palette
    {rr=spalette[b*3],                       // --Find red value of color tb
     gg=spalette[b*3+1],                     // --Find green value of color tb
     bb=spalette[b*3+2];}                    // --Find blue value of color tb
   if (pall==1)                              // -If using Rainbow Palette
    {rr=frainp[b*3],                         // --Find red value of color tb
     gg=frainp[b*3+1],                       // --Find green value of color tb
     bb=frainp[b*3+2];}                      // --Find blue value of color tb
   avg=(rr+bb+gg)/3;                         // -Find Average Value of Color
   while (rr!=avg || bb!=avg || gg!=avg)     // -Loop until all colors are avg'd
    {if (rr>avg)                             // --If red value is brighter then
       rr--;                                 // ---average color, decrease it by 1
     if (rr<avg)                             // --If red value is darker then
       rr++;                                 // ---average color, increase it by 1
     if (bb>avg)                             // --If blue value is brighter then
       bb--;                                 // ---average color, decrease it by 1
     if (bb<avg)                             // --If blue value is darker then
       bb++;                                 // ---average color, increase it by 1
     if (gg>avg)                             // --If green value is brighter then
       gg--;                                 // ---average color, decrease it by 1
     if (gg<avg)                             // --If green value is darken then
       gg++;                                 // ---average color, increase it by 1
     pal(b,rr,gg,bb);}                       // --Update onscreen palette to match
   }                                         //
 }                                           //
//------------------------------------------------------------------------------
                             void cdelay(long msec)
//------------------------------------------------------------------------------
// Simple pause routine in milliseconds
{register long goal=msec+clock();            // Find desired time of unpause
 while(clock()<goal);}                       // Wait til desired time is reached
//------------------------------------------------------------------------------
                  void cls(unsigned char Col,unsigned char *Where)
//------------------------------------------------------------------------------
{_fmemset(Where, Col, 64000);}
//------------------------------------------------------------------------------
                          void curse(int asc,int end)
//------------------------------------------------------------------------------
// Simple routine to change the text base mouse cursor to any ascii character
{asm {mov ax,10;                             // Call 10th register
      mov bx,asc;                            // Input desired ascii character
      mov cx,0;                              // Input undetermined factor
      mov dx,end;                            // Input undetermined factor
      int 33h}}                              // Call 33rd interrupt
//------------------------------------------------------------------------------
                             void cursor(int *Mask)
//------------------------------------------------------------------------------
// Simple routine to change the graphical mouse cursor
{int x,                                      // Initialize Horizontal Clickpoint
     y;                                      // Initialize Vertical Clickpoint
 if (Mask==hand)                             // If you want the hand cursor
  {x=3,                                      // -Set horizontal clickpoint as 3
   y=0;}                                     // -Keep vertical clickpoint as top
 if (Mask==arrow || cbit)                    // If you want the arrow cursor
  {x=1,                                      // -Set horizontal clickpoint as 1
   y=0;}                                     // -Keep vertical clickpoint as top
 asm {mov ax,9                               // Call the 9th register
      mov bx,x                               // Input horiz. clickpoint offset
      mov cx,y                               // Input vertical clickpoint offset
      les dx,Mask                            // Input cursor design from string
      int 33h}}                              // Call 33rd interrupt.
//------------------------------------------------------------------------------
                     void fadein(unsigned char pall)
//------------------------------------------------------------------------------
// Routine to smoothly a blackened screen into either of the two palettes.
{unsigned char tar=0,                        // Start counter at black
 trr=0,                                      // Set red value at black
 tbb=0,                                      // Set blue value at black
 tgg=0;                                      // Set green value at black
 for (int tb=0; tar!=64; tb++)               // The main loop!
  {if (tb>255)                               // -If all colors are synced to fade
    {tb=0;                                   // --Start back at color 0,
     tar++;                                  // --Increase fade color by 1,
     wait();}                                // --and wait for screen retrace.
   if (pall==0)                              // -If using Subliminal Palette
    {trr=spalette[tb*3],                     // --Find red value of color tb
     tgg=spalette[tb*3+1],                   // --Find green value of color tb
     tbb=spalette[tb*3+2];}                  // --Find blue value of color tb
   if (pall==1)                              // -If using Rainbow Palette
    {trr=frainp[tb*3],                       // --Find red value of color tb
     tgg=frainp[tb*3+1],                     // --Find green value of color tb
     tbb=frainp[tb*3+2];}                    // --Find blue value of color tb
   if (trr>=tar)                             // -If real red value should be
     trr=tar;                                // --brighter, sync to fadein color.
   if (tgg>=tar)                             // -If real green value should be
     tgg=tar;                                // --brighter, sync to fadein color.
   if (tbb>=tar)                             // -If real blue value should be
     tbb=tar;                                // --brighter, sync to fadein color.
   pal(tb,trr,tgg,tbb);}                     // -Update onscreen colors to match.
 }                                           //
//------------------------------------------------------------------------------
                           void fadeout(unsigned char pall)
//------------------------------------------------------------------------------
// Routine to smoothly fade all onscreen colors to black using either the
// Subliminal or Rainbow palette.
{unsigned char star=62,                      // Start counter at white
               rr=62,                        // Start red value at max
               bb=62,                        // Start blue value at max
               gg=62;                        // Start green value at max
 for(int b=0; star>0; b++)                   // Draw bottom line
  {if (b>255)                                // -If all colors synced to fade
    {b=0;                                    // --reset color variable,
     star--;                                 // --darken fade value,
     wait();}                                // --and wait for vertical retrace.
   if (pall==0)                              // -If using Subliminal palette
    {rr=spalette[b*3],                       // --Find red value of color b
     gg=spalette[b*3+1],                     // --Find green value of color b
     bb=spalette[b*3+2];}                    // --Find blue value of color b
   if (pall==1)                              // -If using Rainbow palette
    {rr=frainp[b*3],                         // --Find red value of color b
     gg=frainp[b*3+1],                       // --Find green value of color b
     bb=frainp[b*3+2];}                      // --Find blue value of color b
   if (rr>=star)                             // -If red value is brighter than
     rr=star;                                // --fade color, make equal.
   if (gg>=star)                             // -If green value is brighter than
     gg=star;                                // --fade color, make equal.
   if (bb>=star)                             // -If blue value is brighter than
     bb=star;                                // --fade color, make equal.
   pal(b,rr,gg,bb);}                         // -Update onscreen colors to match
 }
//------------------------------------------------------------------------------
                            void frainpal(int rainoff)
//------------------------------------------------------------------------------
// Simple routine to change the palette to the Rainbow Palette
{asm {mov ax, SEG frainp                     // Get the Palette String 256*3
      mov es, ax                             //
      mov dx, OFFSET frainp                  // Get offset of palette
      mov bx, rainoff                        // Start with color 0
      mov cx, 256                            // Copy String with 256 Characters
      mov ax, 0x1012                         // Copy memory location
      int 0x10}}                             // Call 10th interrupt
//------------------------------------------------------------------------------
         void frame(int frx,int fry,int frrx,int frry,unsigned char frcc)
//------------------------------------------------------------------------------
// Simple box outline algorithm.  Draw two sets of parallels to create a frame.
{for(int tx=frx; tx!=frrx+1; tx++)           // Draw top line
   pset(tx,fry,frcc);                        //
 for(tx=frx; tx!=frrx+1; tx++)               // Draw bottom line
   pset(tx,frry,frcc);                       //
 for(tx=fry; tx!=frry+1; tx++)               // Draw left line
   pset(frx,tx,frcc);                        //
 for(tx=fry; tx!=frry+1; tx++)               // Draw bottom line
   pset(frrx,tx,frcc);}                      //
//------------------------------------------------------------------------------
                              void fm(int reg, int val)
//------------------------------------------------------------------------------
// Access sound card through a FM Based Card
{FMoutput(IOport+8, reg, val);}              //
//------------------------------------------------------------------------------
                  void FMoutput(unsigned port, int reg, int val)
//------------------------------------------------------------------------------
{outp(port, reg);                            //
 mydelay(8);                                 //
 outp(port+1, val);                          //
 mydelay(55);}                               //
//------------------------------------------------------------------------------
                              void installfont(void)
//------------------------------------------------------------------------------
{asm {mov ax,1130h
      mov bh,03h
      int 10h
      mov fontseg,es
      mov fontofs,bp}}
//------------------------------------------------------------------------------
                    void getmt(int *smx, int *smy, int *smb)
//------------------------------------------------------------------------------
// Simple routine to find mouse cursor position and button status in a standard
// 80x25 text mode.  Call routine as follows:  getmt(&x,&y,&b);  Regs will be
// stored into the three variables.
{iReg.x.ax=3;                                // Call 3rd register
 int86(0x33,&iReg,&oReg);                    // Call 33rd interrupt and find
                                             //  absolute mouse position.
 *smx=oReg.x.cx/8;                           // Divide ABS Pos by pixels/char(8)
 *smy=oReg.x.dx/8;                           // Divide ABS Pos by pixels/char(8)
 *smb=oReg.x.bx;}                            // Store Button Status
//------------------------------------------------------------------------------
                    void getmv(int *smx, int *smy, int *smb)
//------------------------------------------------------------------------------
// Simple routine to find mouse cursor position and button status MCGA mode.
// Call routine as follows: getmt(&x,&y,&b);  Values will be stored into the
// three designated variables.
{iReg.x.ax=3;                                // Call 3rd register
 int86(0x33,&iReg,&oReg);                    // Call 33rd interrupt and find
                                             //  absolute mouse position.
 *smx=oReg.x.cx/2;                           // Divide ABS Horizontal position
                                             //  in half to rationalize for 320
 *smy=oReg.x.dx;                             // Store verticle value (Coincides)
 *smb=oReg.x.bx;}                            // Store Button Status
//------------------------------------------------------------------------------
                            int getpx(int x, int y)
//------------------------------------------------------------------------------
// Simple assembly routine to return color value as specified in location (x,y)
{unsigned char temp;
 asm {mov ax, y                              //
      mov bx, ax                             //
      shl ax, 8                              //
      shl bx, 6                              //
      add bx, ax                             //
      add bx, x                              //
      mov ax, 0A000h                         //
      mov es, ax                             //
      mov al, es:[bx]                        //
      mov temp,al}                           //
return(temp);}                               //
//------------------------------------------------------------------------------
                               void hide(void)
//------------------------------------------------------------------------------
// Simple interrupt call to hide the mouse cursor as defined by the driver.
{asm {mov ax,2;                              // Call 2nd register.
      int 33h}}                              // Call 33rd interrupt.
//------------------------------------------------------------------------------
                                 void initvirt(int toggle)
//------------------------------------------------------------------------------
{if (toggle==1)
   {vaddr=(unsigned char *)calloc(64000,1);
    if (vaddr == NULL)
      {smode(0x03);
       cout << "Not enough memory available, exiting program...";
       exit(1);}}
 if (toggle!=1)
   free(vaddr);}
//------------------------------------------------------------------------------
                                void initvirt2(int toggle)
//------------------------------------------------------------------------------
{if (toggle==1)
   {vaddr2=(unsigned char *)calloc(64000,1);
    if (vaddr2 == NULL)
      {smode(0x03);
       cout << "Not enough memory available, exiting program...";
       exit(1);}}
 if (toggle!=1)
   free(vaddr2);}
//------------------------------------------------------------------------------
                                    int mouse()
//------------------------------------------------------------------------------
// Simple mouse initialization routine.
{int x;                                      // Initiate Mouse Checker
 asm {xor ax,ax                              // Check all mouse registers.
      int 33h                                // Call 33rd interrupt.
      or ax, ax                              // Recheck all mouse registers.
      jne found                              // Jump to found if found.
      mov x,1                                // Return error code if not found
 found:                                      // Jump to this location if found
      xor al,al}                             // Exit with a code of 0
 return(x);}                                 // Return Status of mouse
//------------------------------------------------------------------------------
                   void mousethr(int x, int y, int Threshold)
//------------------------------------------------------------------------------
// Input a custom mouse threshold
{asm {mov ax,26                              // Call 26th register.
      mov bx,x                               //
      mov cx,y                               //
      mov dx,Threshold                       // Input desired threshold
      int 33h}}                              // Call 33rd interrupt.
//------------------------------------------------------------------------------
                            void movem(int x,int y)
//------------------------------------------------------------------------------
// Simple move mouse cursor routine
{asm {mov ax,4                               // Call 4th register
      mov cx,x                               // Input X Value
      mov dx,y                               // Input Y Value
      int 33h}}                              // Call 33rd interrupt.
//------------------------------------------------------------------------------
        void outtextxy(int tx, int ty, char *cs, unsigned char colr)
//------------------------------------------------------------------------------
// Outputs text to MCGA Screen (Not made yet)
{
unsigned char txtidx,x,y,ch;
    for(txtidx=0;txtidx<(strlen(cs));txtidx++)
     {ch=((unsigned char)cs[txtidx]);
	for(y=0;y<8;y++)
	  for(x=0;x<8;x++)
          if(((peek(fontseg,fontofs+(ch<<3)+y)>>x)&1)!=0)
            pset(tx+(7-x)+8*(txtidx),ty+y,colr);}}
//------------------------------------------------------------------------------
                     void mydelay(unsigned long clocks)
//------------------------------------------------------------------------------
{unsigned long elapsed=0;                    //
 unsigned int last,                          //
              next,                          //
              ncopy;                         //
 outp(0x43,0);                               //
 last=inp(0x40);                             //
 last=~((inp(0x40)<< 8) + last);             //
 do                                          //
  {outp(0x43,0);                             //
   next=inp(0x40);                           //
   ncopy=next=~((inp(0x40)<< 8) + next);     //
   next-=last;                               //
   elapsed += next;                          //
   last=ncopy;}                              //
 while (elapsed<clocks);}                    //
/*-------------------------------*/ void pal /*-------------------------------*/
(unsigned char cnum, unsigned char rgbr, unsigned char rgbg, unsigned char rgbb)
//------------------------------------------------------------------------------
// Assembly routine to alter a specified color's RGB values.
{asm {mov dx,3c8h                            // Call Video Card Palette Location
      mov al,cnum                            // Input Color to change values
      out dx,al                              //
      inc dx                                 //
      mov al,rgbr                            // Input Red Value
      out dx,al                              //
      mov al,rgbg                            // Input Green Value
      out dx,al                              //
      mov al,rgbb                            // Input Blue Value
      out dx,al}}                            //
//------------------------------------------------------------------------------
                           void Profm1(int reg, int val)
//------------------------------------------------------------------------------
// Access sound card through a ProFM         //
{FMoutput(IOport+0, reg, val);}              //
//------------------------------------------------------------------------------
                           void Profm2(int reg, int val)
//------------------------------------------------------------------------------
// Access sound card through a ProFM2        //
{FMoutput(IOport+2, reg, val);}              //
//------------------------------------------------------------------------------
                  void pset(int ppx,int ppy, unsigned char ppc)
//------------------------------------------------------------------------------
// Simple ASM routine for direct video writing.
{asm {mov ax, ppy                            //
      mov bx, ax                             //
      shl ax, 8                              //
      shl bx, 6                              //
      add bx, ax                             //
      add bx, ppx                            //
      mov ax, 0A000h                         //
      mov es, ax                             //
      mov al, ppc                            //
      mov es:[bx], al}}                      //
/*-------------------------*/ unsigned ReadBlasterEnv /*------------------------
/*-----*/(unsigned *port, unsigned *irq, unsigned *dma8,unsigned *dma16)/*----*/
//------------------------------------------------------------------------------
{char *env;                                  //
 env=getenv("BLASTER");                      //
 while (*env)                                //
  {switch(toupper(*(env++)))                 //
    {case 'A':                               //
       if (base16(&env, port))               //
         return 1;                           //
       break;                                //
     case 'I':                               //
       if (base10(&env,irq))                 //
         return 2;                           //
       break;                                //
     case 'D':                               //
       if (base10(&env, dma8))               //
         return 3;                           //
       break;                                //
     case 'H':                               //
       if (base10(&env, dma16))              //
         return 4;                           //
       break;                                //
     default:                                //
       break;}}                              //
 return 0;}                                  //
//------------------------------------------------------------------------------
                                 void reset()
//------------------------------------------------------------------------------
// Simple routine to reset mouse driver.
{asm {mov ax,33                              // Call 33rd register
      int 33h}}                              // Call 33rd interrupt
//------------------------------------------------------------------------------
                                void show(void)
//------------------------------------------------------------------------------
// Simple routine to show mouse cursor.
{asm {mov ax,1                               // Call 1st register
 int 33h}}                                   // Call 33rd interrupt
//------------------------------------------------------------------------------
                                 void shutup()
//------------------------------------------------------------------------------
{fm(0xB0,((577 >> 8) & 0x3) + (4 << 2));}    // -Small routine =)
//------------------------------------------------------------------------------
/*-------------------------------*/ void sline /*-----------------------------*/
 (unsigned x1, unsigned y1, unsigned x2, unsigned y2, unsigned char colour)
//------------------------------------------------------------------------------
// Line algorythm                            //
{if (x1>x2)                                  //
  {unsigned temp=x2;                         //
   x2=x1;                                    //
   x1=temp;}                                 //
 if (y1>y2)                                  //
  {unsigned temp=y2;                         //
   y2=y1;                                    //
   y1=temp;}                                 //
 int dx=x2-x1,                               //
     dy=y2-y1,                               //
     yy=y1,                                  //
     eps=0;                                  //
 for (int xx=x1; xx<=x2; xx++)               //
  {pset(xx,yy,colour);                       //
   eps += dy;                                //
   if ((eps<<1)>=dx)                         //
    {yy++;                                   //
     eps -= dx;}}                            //
 if (x1==x2)                                 //
   for (int yy=y1; yy<=y2; yy++)             //
     pset(x1,yy,colour);}                    //
//------------------------------------------------------------------------------
                              void smode(int mode)
//------------------------------------------------------------------------------
// Simple routine to directly change screen modes.
{union REGS inregs, outregs;                 // Open registers
 inregs.h.ah=0;                              // Set Null Return
 inregs.h.al=(unsigned char)mode;            // Define Register
 int86(0x10, &inregs, &outregs);}            // Call 10th interrupt with regs.
//------------------------------------------------------------------------------
                               void spal(int s8off)
//------------------------------------------------------------------------------
// Simple routine to change the palette to the Subliminal Palette
{asm {mov  ax, SEG spalette                   // Gets the Palette[90][3]
      mov  es, ax                             //
      mov  dx, OFFSET spalette                // Get offset of palette
      mov  bx, s8off                          // Input palette offset
      mov  cx, 256                            // go 256 times (0-255)
      mov  ax, 0x1012                         // Copy Memory Location
      int  10h}}                              // Call 10th interrupt
//------------------------------------------------------------------------------
            void vpset(int x, int y, unsigned char Col, unsigned char *Where)
//------------------------------------------------------------------------------
{memset(Where+(x+(y*320)),Col,1);}            // Plot Pixel
//------------------------------------------------------------------------------
                                   void wait()
//------------------------------------------------------------------------------
// Complex routine to eliminate monitor fuzz by pausing until the screen retrace
// is over.
{_DX = 0x03DA;
  l1: asm {in  al,dx;
           and al,0x08;
           jnz l1;}
  l2: asm {in  al,dx;
           and al,0x08;
           jz  l2;}}
//------------------------------------------------------------------------------
                       void whiteout(unsigned char pall)
//------------------------------------------------------------------------------
// Routine harnessing the 'pal' routine to fade all 256 colors to white using
// either the Subliminal or Rainbow palette.
{unsigned char star=0,                       // Initialize Loop Counter
               rr=0,                         // Initialize Red Value Variable
               bb=0,                         // Initialize Blue Value Variable
               gg=0;                         // Initialize Green Value Variable
 for (int b=0; star!=64; b++)                // Start loop!
  {if (b>255)                                // -If all colors have been checked
    {b=0;                                    // --begin again with first color
     star++;                                 // --and fade value being 1 higher.
     wait();}                                // --Wait till screen retraces.
   if (pall==0)                              // -If using Subliminal Palette
    {rr=spalette[b*3],                       // --Find Red value of color b
     gg=spalette[b*3+1],                     // --Find Green value of color b
     bb=spalette[b*3+2];}                    // --Find Blue value of color b
   if (pall==1)                              // If using Rainbow Palette
    {rr=frainp[b*3],                         // --Find Red value of color b
     gg=frainp[b*3+1],                       // --Find Green value of color b
     bb=frainp[b*3+2];}                      // --Find blue value of color b
   if (rr<=star)                             // If red value is less than fade
     rr=star;                                // -color, make red equal to fade.
   if (gg<=star)                             // If green value is less than fade
     gg=star;                                // -color, make green equal to fade.
   if (bb<=star)                             // If blue value is less than fade
     bb=star;                                // -color, make blue equal to fade.
   pal(b,rr,gg,bb);}}                        // Update on screen palette
