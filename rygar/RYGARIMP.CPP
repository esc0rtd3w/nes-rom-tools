/*
     The following source code can be used, but not without permission.
     You may not create your own Rygar Level Editor with this source code,
     I've already made one.  - Chris.

     Compiled with Borland C++ v4.5
                                                                            */

#include <alloc.h>
#include <conio.h>
#include <dir.h>
#include <fcntl.h>
#include <io.h>
#include <iostream.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys\stat.h>
#include <time.h>
#include <pcx.h>
#include <sublimnl.h>

char *leebo,                                   // Pointer for 'reveal codes'
     *rygar="rygar.nes",                       //
     *rygarnew="rygarnew.nes";                 //
                                               //
int b=0, x=0, y=0, ssp=0,                      // Mouse Variables
    keybe=0,                                   // Keyboard button
    set=1,                                     // Graphics Set #
    levelnum=0,                                // Level Number
    offset=0,
    snd=0;                                     // Sound Variable
                                               //
int lmb=0, lmbo=0, rmbo=0;                     // PCX viewer pointer & offset
                                               //
long level=66836;                              // Level Beginning @ Sueru Mnts
                                               //
void editor(),                                 // The GUI
     copy(char *input, char *output),          // File copying routine
     dispcodes(),                              // HEX Output / Graphic Output
     changembutton(),                          // Mouse button display
     label(),                                  // Level name output
     input(),                                  // HEX Code Input (Keyboard)
     minput(int button),                       // HEX Code Input (Mouse)
     plotpcx(int st_x, int st_y, int width, int height, char *fname);
                                               // Plot PCX
struct obj_img                                 // Struct for PCX handling
 {unsigned char *data;};                       //
                                               //
 FILE *in, *out;                               // Initialize two file handles
                                               //
 obj_img test;                                 // Init object for PCXs
//----------------------------------------------------------------------------
                      void main(int argc, char ** argv)
//----------------------------------------------------------------------------
{test.data = (char *)malloc(320 * 200);        // Allocate memory for PCX file
                                               //
 if (argc==3)                                  // If command line options
  {rygar=argv[1];                              // Copy first as input file
   rygarnew=argv[2];}                          // Copy second as output file
                                               //
 if (argc!=3)                                  // If less than 2 entries
  {cout << "Invalid, or no command line parameters.\n"
        << "Defaulting to: input as 'rygar.nes' and output as 'rygarnew.nes'\n\n"
        << "C:\\> rygarimp rygar.nes rygarnew.nes\n\n";
   sleep(2);                                   // Four second pause
  }                                            //
                                               //
 if (mouse()==-1)                              // Detect mouse
  {cout << "No Mouse Driver Installed!\n\n";   // -Output error message
   getch();}                                   // -Wait for Keypress...
 editor();                                     // Go to editor
                                               // ----------------------------
 hide();                                       // Hide Mouse Cursor
 textmode(C80);                                // Change to colour text mode
 clrscr();                                     // Clear Screen
 cout                                          // Display credits
   << "                       .xX Rygar Improvement v1.0 Xx.\n\n"
   << "   Coded by:        Chris Hickman (chris@bpwl.com)\n"
   << "   ROM Hacking by:  Jay McGavren (thespook@novia.net)\n"
   << "   Last Revision:   July 22nd, 1997\n"
   << "   Homepage:        http://www.bpwl.com/ar/utils/nes/rygarimp.htm\n\n";
   remove("RYGAR.TMP");                        // Remove work file
}                                              //
//****************************************************************************
                              void editor()
//****************************************************************************
{hide();                                       // Hide mouse cursor
 copy(rygar, "rygar.tmp");                     // Copy input file to output
 copy("rygar.tmp", rygarnew);                  // Create duplicate temp file
 smode(0x13);                                  // Switch Screen Modes
 installfont();                                // Init 'outtextxy' function
 cursor(hand);                                 // Make mouse cursor a hand
 pcxpalette("rygarimp.pcx");                   // Load palette from PCX
 showpcx("rygarimp.pcx");                      // Show the GUI PCX
 dispcodes();                                  // Display Hex Codes / Tiles
 changembutton();                              // Display Tile Browser Info
 label();                                      // Display Level Title
 show();                                       // Display Mouse cursor
//----------------------------------------------------------------------------
//---------------------- THE MAIN PROGRAM LOOP IS BELOW! ---------------------
//----------------------------------------------------------------------------
 while (b<20)                                  // Loop until 'exit'
  {getmv(&x,&y,&b);                            // Update mouse variables
   if (b==0 && ssp==1) ssp=0;                  // Unlock after button release
// ---------------------------------------------------------------------------
   if (kbhit())                                // If key is pressed:
    {keybe=getch();                            // Get key as 'keybe'
     if (keybe==75 || keybe==72)               // ----------- Up or Left Arrow
      {offset--;                               // Move level offset back
       dispcodes();                            // Display updated info
       cdelay(30);}                            // Add short delay
     if (keybe==77 || keybe==80)               // -------- Down or Right Arrow
      {offset++;                               // Move level offset back
       dispcodes();                            // Display updated info
       cdelay(30);}                            // Add short delay
     if (keybe==73)                            // ---------------------Page Up
      {offset=offset-16;                       // Move back 16 bytes
       dispcodes();}                           // Redisplay screen info
     if (keybe==81)                            // -------------------Page Down
      {offset=offset+16;                       // Move forward 16 bytes
       dispcodes();}                           // Redisplay screen info
     if (keybe==9)                             // -------------------------Tab
      {set++;                                  // Increment graphics set
       if (set>4) set=1;                       // Set to 0 if out of bounds
       hide();                                 // Hide mouse cursor
       box(17,15,203,150, 99);                 // Clear Area
       dispcodes();                            // Redisplay screen info
       changembutton();                        // Redisplay graphics browser
       show();}                                // Show mouse cursor
     if (keybe==45)                            // -------------------------- -
       {minput(59-49+3);                       // Act as if it is after 0
        dispcodes();}                          // Redisplay screen info
     if (keybe==48)                            // -------------------------- 0
       {minput(58-49+3);                       // Act as if it is after 9
        dispcodes();}                          // Redisplay screen info
     if (keybe>=49 && keybe<=57)               // ---------------------- 1 - 9
       {minput(keybe-49+3);                    // - 49 = 0, + 3 for mouse
        dispcodes();}                          // Redisplay screen info
     if (keybe==59)                            // ------------------------- F1
       lmbo=lmb;                               // Select first tile in palette
     if (keybe==60)                            // ------------------------- F2
       lmbo=lmb+1;                             // Select 2nd tile in palette
     if (keybe==61)                            // ------------------------- F3
       lmbo=lmb+2;                             // Select third tile in palette
     if (keybe==63)                            // ------------------------- F5
       if (lmb>0) lmb--, changembutton();      // Move left through palette
     if (keybe==64)                            // ------------------------- F6
       if (lmb<255-2) lmb++, changembutton();  // Move right through palette
     if (keybe==65)                            // ------------------------- F7
      {levelnum--;                             // Move up a level
       hide();                                 // Hide mouse cursor
       box(17,15,203,150, 99);                 // Clear Area
       label();                                // Change level label
       dispcodes();                            // Redisplay screen info
       changembutton();                        // Redisplay graphics browser
       show();}                                // Show mouse cursor
     if (keybe==66)                            // ------------------------- F8
      {levelnum++;                             // Move up a level
       hide();                                 // Hide mouse cursor
       box(17,15,203,150, 99);                 // Clear Area
       label();                                // Change level label
       dispcodes();                            // Redisplay screen info
       changembutton();                        // Redisplay graphics browser
       show();}                                // Show mouse cursor
     if (keybe==68)                            // -------------------------F10
       b=21;                                   // Give signal to exit
    }                                          //
// ---------------------------------------------------------------------------
   if (b==1 && ssp==0)                         // If left button is pressed:
    {                                          // ----------------Left Turtle
     if (x>=12 && x<=37 && y>=151 && y<=168 && ssp==0)
      {while (b!=0 && x>=12 && x<=37 && y>=151 && y<=168)
        {offset--;                             // Move level offset back
         dispcodes();                          // Display updated info
         cdelay(20);                           // Add short delay
         getmv(&x,&y,&b);}                     // Check mouse status
       ssp=1;}                                 // Lock after button release.
                                               // ---------------Right Turtle
     if (x>=180 && x<=205 && y>=151 && y<=168 && ssp==0)
      {while (b!=0 && x>=180 && x<=205 && y>=151 && y<=168)
        {offset++;                             // Move level offset forward
         dispcodes();                          // Display updated info
         cdelay(20);                           // Add short delay
         getmv(&x,&y,&b);}                     // Check mouse status
       ssp=1;}                                 // Lock after button release
                                               // ------------Page Up Buttton
     if (x>=216 && x<=260 && y>=17 && y<=37 && ssp==0)
      {offset=offset-16;                       // Move back 16 bytes
       dispcodes();                            // Redisplay screen info
       ssp=1;}                                 // Lock GUI
                                               // -----------Page Down Button
     if (x>=216 && x<=260 && y>=40 && y<=60 && ssp==0)
      {offset=offset+16;                       // Move forward 16 bytes
       dispcodes();                            // Redisplay screen info
       ssp=1;}                                 // Lock GUI
                                               // ------------Level Up Button
     if (x>=216 && x<=260 && y>=63 && y<=83 && ssp==0)
      {levelnum++;                             // Move up a level
       box(17,15,203,150, 99);                 // Clear Area
       label();                                // Change level label
       dispcodes();                            // Redisplay screen info
       changembutton();                        // Redisplay graphics browser
       ssp=1;}                                 // Lock GUI
                                               // ----------Level Down Button
     if (x>=216 && x<=260 && y>=86 && y<=106 && ssp==0)
      {levelnum--;                             // Move down a level
       box(17,15,203,150, 99);                 // Clear Area
       label();                                // Change level label
       dispcodes();                            // Redisplay screen info
       changembutton();                        // Redisplay graphics browser
       ssp=1;}                                 // Lock GUI
                                               // -------------PCX Set Button
     if (x>=216 && x<=260 && y>=109 && y<=129 && ssp==0)
      {set++;                                  // Increment graphics set
       if (set>4) set=1;                       // Set to 0 if out of bounds
       hide();                                 // Hide mouse cursor
       box(17,15,203,150, 99);                 // Clear Area
       dispcodes();                            // Redisplay screen info
       changembutton();                        // Redisplay graphics browser
       show();                                 // Show mouse cursor
       ssp=1;}                                 // Lock GUI
                                               // ----------------Exit Button
     if (x>=216 && x<=260 && y>=132 && y<=152 && ssp==0)
      {b=21;                                   // Give signal to exit
       ssp=1;}                                 // Lock GUI
                                               // ----------Browser <- Button
     if (x>=266 && x<=291 && y>=142 && y<=162 && ssp==0)
      {while (b!=0 && x>=266 && x<=291 && y>=142 && y<=162)
        {if (lmb > 0) lmb--;                   // If valid, move offset back
         changembutton();                      // Redisplay browser info
         cdelay(20);                           // Add short delay
         getmv(&x,&y,&b);}                     // Get mouse status
       ssp=1;}                                 // Lock after button release
                                               // -----------Browser -> Button
     if (x>=292 && x<=317 && y>=142 && y<=162 && ssp==0)
      {while (b!=0 && x>=292 && x<=317 && y>=142 && y<=162)
        {if (lmb < 253) lmb++;                 // If valid, add to offset
         changembutton();                      // Redisplay browser info
         cdelay(20);                           // Add short delay
         getmv(&x,&y,&b);}                     // Get mouse status
       ssp=1;}                                 // Lock after button release
                                               // ------------Selecting a .PCX
     if (x>=266 && x<=317 && y>=9 && y<=128 && ssp==0)
      {lmbo=lmb+(x-266)/17;                    // Determine which of the three
                                               // you clicked on and create a
                                               // new value based on offset.
       ssp=1;}                                 // Lock GUI
                                               // ---HEX Code entry (Vertical)
     if (set<3 && x>=16 && x<=16+17*11 && y>=140 && y<=150 && ssp==0)
      {input();                                // Run input routine
       dispcodes();                            // Redisplay screen info
       ssp=1;}                                 // Lock GUI
                                               // ------HEX entry (Horizontal)
     if (set>=3 && x>=174 && x<=190 && y>=23 && y<=150 && ssp==0)
      {input();                                // Run input routine
       dispcodes();                            // Redisplay screen info
       ssp=1;}                                 // Lock GUI
                                               // -----------------Mouse entry
     if (x>=16 && x<=201 && y>=17 && y<=140 && ssp==0)
      {minput(0);                              // Run minput (left button)
       dispcodes();                            // Redisplay screen info
       ssp=1;}                                 // Lock GUI
                                               // ----------------------------
     else ssp=1;}                              // If nothing, lock GUI!
//----------------------------------------------------------------------------
   if (b==2 && ssp==0)                         // If right button is pressed:
    {                                          // ------------Selecting a .PCX
     if (x>=266 && x<=317 && y>=9 && y<=128 && ssp==0)
      {rmbo=lmb+(x-266)/17;                    // Determine which of the three
                                               // you clicked on and create a
                                               // new value based on offset.
       ssp=1;}                                 // Lock GUI
     if (x>=16 && x<=16+17*11 && y>=17 && y<=138 && ssp==0)
      {minput(1);                              // Run minput (right button)
       dispcodes();                            // Redisplay screen info
       ssp=1;}                                 // Lock GUI
                                               // ----------------------------
     else ssp=1;}                              // If nothing, lock GUI!
//------------------------------------------------------------------------------
   }                                           // End of main program loop
 hide();                                       // Hide mouse cursor
}                                              // Return back to main()
//Xx.------------------------------------------------------------------------Xx.
                              void dispcodes()
//Xx.------------------------------------------------------------------------Xx.
{                                              //
if ((in = fopen(rygarnew, "rb"))==NULL)        // Open file, and check it.
  {fprintf(stderr, "Error opening output file...\n");
   getch();                                    // On fail, output error,
   exit(1);}                                   // pause and exit.
                                               //
hide();                                        // Hide mouse cursor
                                               //
unsigned char tempor[2];                       // 2 Letter hex code
unsigned char tempor2[15];                     // Filename and directory
int holder=0;                                  // Initialize variable
fseek(in, level+offset, 0);                    // Set file pointer
                                               //
if (set<3)                                     // If using vertical columns
  for (int hx=0; hx < 11; hx++)                // Load all 11 HEX Co
    {holder=fgetc(in);                         // Get ascii code (0-255)
     if (holder<16)                            // If ascii code (0-15)
       sprintf(tempor, "0%X", holder);         // Add a 0 before the the hex
     else                                      // If ascii code (15-255)
       sprintf(tempor, "%X", holder);          // Retrieve without adding a 0
     box(18+17*hx, 141, 17+17*(hx+1), 149, 99);// Erase old hex code
     outtextxy(17+17*hx+2, 142, tempor, 9);    // Output new hex code
                                               // Figure out the PCX filename
     sprintf(tempor2, "pcxs%i\\%X.pcx", set, holder);
     plotpcx(17+17*hx, 18, 16, 120, tempor2);  // Open and plot PCX
    }                                          //
                                               //
else                                           // If using horizontal columns
  for (int hx=0; hx < 8; hx++)                 // Load all 11 HEX Co
    {holder=fgetc(in);                         // Get ascii code (0-255)
     if (holder<15)                            // If ascii code (0-15)
       sprintf(tempor, "0%X", holder);         // Add a 0 before the the hex
     else                                      // If ascii code (15-255)
       sprintf(tempor, "%X", holder);          // Retrieve without adding a 0
     box(176, 21+17*hx, 199, 31+17*hx, 99);    // Erase old hex code
     outtextxy(176, 21+17*hx, tempor, 9);      // Output new hex code
                                               // Figure out the PCX filename
     sprintf(tempor2, "pcxs%i\\%X.pcx", set, holder);
     plotpcx(46, 16+17*hx, 128, 16, tempor2);  // Open and plot PCX
    }                                          //
                                               //
show();                                        // Show mouse cursor
fclose(in);                                    // Close "RYGARNEW.NES"
}                                              //
//Xx.------------------------------------------------------------------------Xx.
      void plotpcx(int st_x, int st_y, int width, int height, char *fname)
//Xx.------------------------------------------------------------------------Xx.
{                                              //
 test.data = readpcx2(height, width, fname);   // Read PCX into memory
 int count=0;                                  // Initialize counter
 for(int y = st_y; y < st_y + height; y++)     // Loop while in vert. bounds
   for(int x = st_x; x < st_x + width; x++)    // Loop while in horz. bounds
    pokeb(0xa000,320*y+x,test.data[count++]);  // Output directly to video
 free(test.data);                              // Free memory used by .PCX
}                                              //
//Xx.------------------------------------------------------------------------Xx.
      void plotpcx2(int st_x, int st_y, int width, int height, char *fname)
//Xx.------------------------------------------------------------------------Xx.
{                                              //
 test.data = readpcx2(height, width, fname);   // Read PCX into memory
 int count=0;                                  // Initialize counter
 for(int x = st_x; x < st_x + width; x++)      // Loop while in horz. bounds
  for(int y = st_y; y < st_y + height; y++)    // Loop while in vert. bounds
    pokeb(0xa000,320*y+x,test.data[count++]);  // Output directly to video
 free(test.data);                              // Free memory used by .PCX
}                                              //
//Xx.------------------------------------------------------------------------Xx.
                               void label()
//Xx.------------------------------------------------------------------------Xx.
{offset=0;                                     // Reset level offset
 box(40,155,178,163,99);                       // Erase on screen label
 if (levelnum<0)                               // If level is negative,
   levelnum=12;                                // Go to the last level
 if (levelnum>12)                              // If level exceeds bounds,
   levelnum=0;                                 // Go to first level
 if (levelnum==0)                              // If level #1
   {level=66836, set=1;                        // Level length 10514 - 105D3
    outtextxy(40,155," Sueru Mountains", 9);}  // Output label
 if (levelnum==1)                              // If level #2
   {level=67028, set=1;                        // Level length 105D4 - ?????
    outtextxy(40,155,"  Gran Mountain ", 9);}  // Output label
 if (levelnum==2)                              // If level #3
   {level=67856+5, set=1;                      // Level length 10A30 - ?????
    outtextxy(40,155," Tower of Garba ", 9);}  // Output label
 if (levelnum==3)                              // If level #4
   {level=68148, set=1;                        // Level length 10A30 - ?????
    outtextxy(40,155,"  Rolsa Valley  ", 9);}  // Output label
 if (levelnum==4)                              // If level #5
   {level=68596, set=1;                        // Level length 10A30 - ?????
    outtextxy(40,155,"   Lapis Gate   ", 9);}  // Output label
 if (levelnum==5)                              // If level #6
   {level=68708, set=1;                        // Level length 10A30 - ?????
    outtextxy(40,155,"      Lapis     ", 9);}  // Output label
 if (levelnum==6)                              // If level #7
   {level=69156, set=2;                        // Level length 10A30 - ?????
    outtextxy(40,155,"  Mt. Primeval  ", 9);}  // Output label
 if (levelnum==7)                              // If level #8
   {level=69316, set=2;                        // Level length 10A30 - ?????
    outtextxy(40,155,"  Sagila's Cave ", 9);}  // Output label
 if (levelnum==8)                              // If level #9
   {level=69952+4, set=2;                      // Level length 10A30 - ?????
    outtextxy(40,155," Eruga's Forest ", 9);}  // Output label
 if (levelnum==9)                              // If level #10
   {level=70372, set=1;                        // Level length 105D4 - ?????
    outtextxy(40,155," Misc. Areas ", 9);}     // Output label
 if (levelnum==10)                             // If level #11
   {level=70772, set=3;                        // Level length 10A30 - ?????
    outtextxy(40,155,"     Garloz     ", 9);}  // Output label
 if (levelnum==11)                             // If level #12
   {level=71492, set=4;                        // Level length 10A30 - ?????
    outtextxy(40,155," Ligar's Castle ", 9);}  // Output label
 if (levelnum==12)                             // If level #13
   {level=72392, set=4;                        // Level length 10A30 - ?????
    outtextxy(40,155," Dorago's Palace", 9);}  // Output label
}                                              //
//Xx.------------------------------------------------------------------------Xx.
                             void changembutton()
//Xx.------------------------------------------------------------------------Xx.
{                                              //
char dump[18];                                 // Initialize filename string
for (int l=0; l<3; l++)                        // Loop 3 times
 {sprintf(dump, "pcxs%i\\%X.pcx", set, lmb+l); // Copy filename to 'tempor'
  if (set<3)                                   //
    plotpcx(266+17*l, 8, 16, 120, dump);       //
  else                                         //
    plotpcx2(266+17*l, 8, 16, 128, dump);}     // Display tile
                                               //
if (set<3) box(266, 128, 316, 138, 99);        // Erase old HEX display (Vert)
else  box(266, 130, 316, 138, 99);             // Erase old HEX display (Hori)
                                               //
for (l=0; l<3; l++)                            // Loop 3 times
 {if (lmb+l>15)                                // If HEX address is 10 - FF
    sprintf(dump, "%X", lmb+l);                // Output 2 digit HEX code
  else                                         // If HEX address is 00 - 0F
    sprintf(dump, "0%X", lmb+l);               // Output a 0 then the HEX
  outtextxy(267+17*l, 131, dump, 9);}          // Output HEX string to screen
}                                              //
//Xx.------------------------------------------------------------------------Xx.
                        void copy(char *input, char *output)
//Xx.------------------------------------------------------------------------Xx.
{                                              //
 if ((in = fopen(input, "rb")) == NULL)        // Open up input file
  {fprintf(stderr,"Can't open input file.\n"); // If error, print message
   getch();                                    // Pause program
   textmode(C80);                              // Return to TEXT mode
   exit(1);}                                   // Quit
 if ((out = fopen(output, "wb")) == NULL)      // Open up output file
  {fprintf(stderr,"Can't open output file.\n");// If error, print message
   getch();                                    // Pause program
   textmode(C80);                              // Return to TEXT mode
   exit(1);}                                   // Quit
                                               //
 unsigned char bitch=fgetc(in);                // Get first character
 while (!feof(in))                             // Check to see if at EOF
   {fputc(bitch, out);                         // Copy file char. at a time
    bitch=fgetc(in);}                          // Get next character
                                               //
 fclose(in);                                   // Close input file
 fclose(out);                                  // Close ouput file
}                                              //
//Xx.----------------------------------------------------------------------Xx.
                             void minput(int button)
//Xx.----------------------------------------------------------------------Xx.
{hide();                                       // Hide mouse cursor
/*                                             //
   The following is identical to the copy routine, but the ouput file is left
   open for editing in this instance           //
                                               //                          */
 if ((in = fopen("rygar.tmp", "rb")) == NULL)  // Open up input file
  {fprintf(stderr,"Can't open input file.\n"); // If error, print message
   getch();                                    // Pause program
   textmode(C80);                              // Return to TEXT mode
   exit(1);}                                   // Quit
                                               //
 if ((out=fopen(rygarnew, "wb"))== NULL)       // Open up output file
  {fprintf(stderr,"Can't open output file.\n");// If error, print message
   getch();                                    // Pause program
   textmode(C80);                              // Return to TEXT mode
   exit(1);}                                   // Quit
                                               //
 unsigned char bitch=fgetc(in);                // Get first character
 while (!feof(in))                             // Check to see if at EOF
   {fputc(bitch, out);                         // Copy file char. at a time
    bitch=fgetc(in);}                          // Get next character
 fclose(in);                                   // Close 'rygar.tmp'
                                               //
 unsigned char bob;                            // Initialize variable (0-10)
 if (set!=3 && button<2)                       // If using vertical columns
    bob=((x-15)/17);                           // Find which column is used
 if (set==3 && button<2)                       // If using horizontal rows
    bob=((y-16)/17);                           // Find which row is used
 if (button>2)                                 // If keyboard entry
    bob=button-3;                              // (See the keyboard entry for
                                               // explanation to button(>2)
 fseek(out, level+offset+bob, 0);              // Set file pointer
                                               //
 if (button==0)                                // If left mouse button
   fputc(lmbo, out);                           // Insert 'lmbo' into file.
 if (button==1)                                // If right mouse button
   fputc(rmbo, out);                           // Insert 'rmbo' into file.
 if (button>2)                                 // If other (key) button
   fputc(lmbo, out);                           // Insert 'lmbo' into file.
                                               //
 fclose(out);                                  // Close 'rygarnew.nes'
 copy (rygarnew, "rygar.tmp");                 // Make backup for next input
 show();                                       // Show mouse cursor
}                                              //
//Xx.----------------------------------------------------------------------Xx.
                               void input()
//Xx.----------------------------------------------------------------------Xx.
/*
   The following has not been commented very well because I have no desire
   to make it look more complicated :-)

   set!=3 = Vertical PCX display
   else   = Horizontal PCX display

*/
{hide();                                       // Hide mouse cursor
 if (set!=3)                                   // If vert., erase input area
   box (17+ ((x-16)/17)*17, 141, 33+((x-16)/17)*17, 149, 99);
 else                                          // If horiz, erase input area
   box(176, 21+((y-16)/17)*17, 199, 33+((y-16)/17)*17, 99);
 unsigned char ak[3]={0,0,0};                  // Initialize string for input
 char hexcode[3]="   ";                        // Initialize string for output
 int rc=0;                                     // Initialize counter
                                               //
 while (ak[rc]!=27 && ak[rc]!=13)              // Loop until 'ENTER' or 'ESC'
  {ak[rc]=getche();                            // Get input
                                               // If 0-9, A-F, or backspace:
   if ((ak[rc]>=48 && ak[rc]<=57) || (ak[rc]>=65 && ak[rc]<=70) || ak[rc]==8)
                                               //
    {if (ak[rc]!=8 && rc<2)                    // If not backspace
                                               //
      {if (set!=3)
         box (17 + ((x-16)/17)*17, 141, 32+((x-16)/17)*17, 149, 99);
       else
         box(176, 21+((y-16)/17)*17, 199, 33+((y-16)/17)*17, 99);
       sprintf(hexcode, "%c%c", ak[0], ak[1]);
       if (set!=3)
         outtextxy(18+ ((x-16)/17)*17, 142, hexcode, 0);
       else
         outtextxy(176, 21+((y-16)/17)*17, hexcode, 0);
       rc++;}

     if (ak[rc]==8)                             // ---If input is backspace,
      {if (set!=3)
         box (17+ ((x-16)/17)*17, 141, 32+((x-16)/17)*17, 149, 99);
       else
         box(176, 21+((y-16)/17)*17, 199, 33+((y-16)/17)*17, 99);
       ak[0]=0; ak[1]=0; ak[2]=0; rc=0;}
     }
  }

 if (ak[0]==27 || ak[1]==27)
   {if ((out = fopen(rygar, "rb")) == NULL)
     {fprintf(stderr, "Cannot open input file (RYGAR.NES).\n");
      getch();
      exit(1);}

 if (set!=3)
   fseek(in, level+offset+((x-16)/17), 0);
 else
   fseek(in, level+offset+((y-16)/17), 0);

 sprintf(hexcode, "%X", fgetc(in));

 if (set!=3)
   box (17 + ((x-16)/17)*17, 141, 32+((x-16)/17)*17, 149, 99);
 else
   box(176, 23+((y-16)/17)*17, 199, 33+((y-16)/17)*17, 99);

 if (set!=3)
   outtextxy(18+ ((x-16)/17)*17, 142, hexcode, 0);
 else
   outtextxy(176, 23+((y-16)/17)*17, hexcode, 0);
 fclose(in);}

// ------------- Open up RYGAR.TMP - copy it to RYGARNEW.NES -------------------
 else
   {
    if ((in = fopen("rygar.tmp", "rb")) == NULL)
      {fprintf(stderr, "Cannot open input file.\n");
       getch();
       exit(1);}
    if ((out = fopen(rygarnew, "wb")) == NULL)
      {fprintf(stderr, "Cannot open output file.\n");
       getch();
       exit(1);}

    unsigned char bitch=fgetc(in);              // Get first character
    while (!feof(in))                           // Check to see if at EOF
     {fputc(bitch, out);                        // Copy file char. at a time
      bitch=fgetc(in);}                         // Get next character
      fclose(in);
// ------------- RYGARNEW.NES and RYGAR.TMP are now identical! -----------------

//------------------------------------------------------------------------------
// Chris's way of converting two inputted unsigned characters into one unsigned
// character to write into a file -- there probably are a billion better ways
// to do this :)
    unsigned char code=0;
    if (hexcode[0]==48) code=0;        // 0
    if (hexcode[0]==49) code=16;       // 1
    if (hexcode[0]==50) code=16*2;     // 2
    if (hexcode[0]==51) code=16*3;
    if (hexcode[0]==52) code=16*4;
    if (hexcode[0]==53) code=16*5;
    if (hexcode[0]==54) code=16*6;
    if (hexcode[0]==55) code=16*7;
    if (hexcode[0]==56) code=16*8;
    if (hexcode[0]==57) code=16*9;    // 9
    if (hexcode[0]==65) code=16*10;   // A
    if (hexcode[0]==66) code=16*11;
    if (hexcode[0]==67) code=16*12;
    if (hexcode[0]==68) code=16*13;
    if (hexcode[0]==69) code=16*14;
    if (hexcode[0]==70) code=16*15;   // F
    if (hexcode[1]==49) code=code+1;
    if (hexcode[1]==50) code=code+2;
    if (hexcode[1]==51) code=code+3;
    if (hexcode[1]==52) code=code+4;
    if (hexcode[1]==53) code=code+5;
    if (hexcode[1]==54) code=code+6;
    if (hexcode[1]==55) code=code+7;
    if (hexcode[1]==56) code=code+8;
    if (hexcode[1]==57) code=code+9;
    if (hexcode[1]==65) code=code+10;
    if (hexcode[1]==66) code=code+11;
    if (hexcode[1]==67) code=code+12;
    if (hexcode[1]==68) code=code+13;
    if (hexcode[1]==69) code=code+14;
    if (hexcode[1]==70) code=code+15;
//------------------------------------------------------------------------------
    unsigned char bob;
    if (set!=3) bob=(x-16)/17;
    else bob=(y-16)/17;
    fseek(out, level+offset+bob, 0);
    fputc(code, out);
    fclose(out);
    copy (rygarnew, "rygar.tmp");}
 show();
}
