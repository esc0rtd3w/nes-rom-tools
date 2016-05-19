ISD SMB Util (Insectduel's SMB Utility)
A level editor for Super Mario Bros. 1 for NES
©1999-2002 M.K.S
©2008 Insectduel

=============================================================================
Contents
=============================================================================

1] Introduction
2] Why did I design this?
3] Reversion history
4] Insectduel's Domain License Agreement
5] What comes with it other than ISD SMB Util?
6] What's added in ISD SMB Util?
7] What is ISD SMB Util used for?
8] What is SMB2 Japanese Items?
9] What are SMB2 Japanese Items in hex?
10] What are SMB2 Japanese enemies in hex?
11] Hacking SMB2 Japanese
12] KEYS for SMB Utility by default
13] SMB Utility FAQ
14] Bugs & Suggestions
15] Contact
16] Credits

=============================================================================
Introduction
=============================================================================

"ISD SMB Util" is based on "SMB Utilty English Beta 3" by M.K.S as well as the Item SMB2 Japanese which is the Japanese version of SMB Utility Version 1.04. It is added with a few corrections that is miscorrected. It is also added many item SMB2 Japanese Item names inside ISD SMB Util. M.K.S only knows these things; He do not know my own details. So you cannot, I repeat, CANNOT ask M.K.S about "ISD SMB Util".

Please note that I have no knowledge in programming. Someone else only taught me to do it.

=============================================================================
Why did I design this?
=============================================================================

I didn't design it. I modified it. It can motivate ROM-Hackers to hack SMB1 with SMB2 Japanese Items. The tool called Item SMB2 Japanese is created by SMB Software based on SMB Utility Version 1.04 which is the Japanese version. You can find Item SMB2J on my website or SMB Software's webpage or grab SMB Utility Version 1.04 on my website as well. So I motivate myself to do the English version of Item SMB2J called ISD SMB Util based on SMB Utility Version 1.00 English BETA 3. That's because too many fellow Americans cannot understand the native Japanese langauge. And of course I took my own name in my own level editor for it.

=============================================================================
Reversion history
=============================================================================

April 3, 2002 English Beta 3 of SMB Utility Public Release

April 17, 2008 Started

April 20, 2008 1:40 PM Finished

April 21, 2008 Public Release 

=============================================================================
Insectduel's Domain License Agreement
=============================================================================

This is a free software, meaning no commercial ways. It has absolutely no warranties, so you use it at your own risk. Any ROM images can not be packaged or distributed with this level editor. I can not be responsible for your actions. However, feel free to distribute it whenever you want, by respecting the agreement lines you just read. My website is always at http://insectduel.googlepages.com, and you can even use my forums to contact me.
 
Failure to follow these rules and this tool will be deleted off my website. PERMANENTLY.

Cool, you are 1% of people that actually read software docs.

=============================================================================
What comes with it other than ISD SMB Util?
=============================================================================

This package comes with SMB Mapper 1 as well as the batch file called Mapper. You can follow instructions in SMB Mapper1.txt It also has Lunar IPS (Patcher), Translhextion (Hex Editor), a few IPS Patches, SMB1 Fix, SMB2 Japanese levels and SMB2 Japanese documents.

=============================================================================
What's added in ISD SMB Util?
=============================================================================

ADDED:
Name all items to SMB2 Japanese based
About file (But believe me, I do not claim SMB Utility as my own)

CORRECTED:
Unedited Japanese Text in Sort Areas to Room of Area when choosing an area.
Brick (Tree of beans) replaced with Brick (Vine).
A few Captializations.
Brick: Surface which has pitholes and celing has been changed to Brick: Celing.
The word Cancle has been corrected to Cancel when exiting SMB Utility.
In the text editor dialogue. Mario (Unknows blah, blah, blah) is changed to Mario (Unknown)
The 2nd Night and Snow is changed to Castle Palette.
Reflesh world data changed to Refresh world data.
Righht corrected to Right in the Keyboard configuation.

Stuff still existed that cannot be fixed:
Enable Pilania Plants from 1-1 text dialogue cannot be found.
Custum that should have be Custom which cannot be found as well.

=============================================================================
What is ISD SMB Util used for?
=============================================================================

That's for all ROM-Hackers who hack SMB1 to hack SMB1 with SMB2 Japanese Items. It also have the benefit to hack the FDS SMB2 Japanese version of the game. Please look in SMB2 (J) Levels folder. Keep in mind that the SMB2 Japanese game for the FDS isn't compatable with SMB Utility or ISD SMB Util. For every hack you do with ISD SMB Util, give-me credit for the SMB2 Japanese names.

=============================================================================
What is SMB2 Japanese Items?
=============================================================================

For those who never played SMB2 Japanese for FDS. Here's a list of items in the game.

? Poison Mushroom
Invisible Posion Mushroom
Brick Posion Mushroom
Invisible Mushroom
Upside down Pipes
Red Piranha Plants
Green Jumping Boards

=============================================================================
What are SMB2 Japanese Items in hex?
=============================================================================

ROWS 0-B

00 ? Mushroom

01 Poison ? Mushroom

02 ? Coin

03 Invisible coin

04 Invisible 1-UP Mushroom

05 Invisible Poison Mushroom

06 Invisible Mushroom

07 Brick with Mushroom

08 Brick with Poison Mushroom

09 Brich with Vine

0A Brick with Star

0B Brick with 10 coins

0C Brick with 1-UP Mushroom

0D Sideways Pipe

0E Used Block

0F Jump stand (Changes programs with different worlds)

Super Spring levels require in SMB2J

World 2

World 3

World 7

World C 

1L Island (Cannon)

2L Horizontal brick (Seaplant)

3L Horizontal block

4L Horizontal coins

5L Vertical brick (Seaplant)

6L Vertical block

70-77 Pipe (CAN’T GO DOWN)

78-7F Pipe (CAN GO DOWN)

80-FF Flagged object

ROW C

0L Hole

1L Balance Horizontal Rope

2L Bridge (Vertical 7)

3L Bridge (Vertical 8)

4L Bridge (Vertical 10)

5L Hole filled with water

6L Horizontal ? Coin (Vertical 3)

7L Horizontal ? Coin (Vertical 7)

80-FF Flagged object

ROW D

00-3F Page Skip (Page flag does not acquire)

40 Reverse L Pipe

41 Pole

42 Axe (May move on another World if touched)

43 Rope

44 Castle Bridge 

45 Scroll Stop (Warp Zone)

46 Scroll Stop

47 Scroll Stop 

48 Infinite flying cheep cheeps

49 Infinite Shooters 

(Bullet bills in Overworld, Castle and Underground)

(Cheep Cheeps in Sea)

4A Stops infinite enemies

4B Loop Command (Requires Castle loop editing)

4C Wind on

4D Wind off

4E WARNING: Crashes game

4F WARNING: Crashes game

80-CF Flagged Object

ROW E

Digit left objects for Brick scenery

0 Nothing

1 Clouds

2 Mountain

3 Fence

Digit Right for Brick Scenery Objects

0 None

1 Surface

2 Surface and Ceiling

3 Surface and Ceiling 3

4 Surface and Ceiling 4

5 Surface and Ceiling 8

6 Surface 4 and Ceiling

7 Surface 4 and Ceiling 3

8 Surface 4 and Ceiling 4

9 Surface 5 and Ceiling

A Holes with ceiling

B Surface 5 and Ceiling 4

C Surface 8 and Ceiling

D Surface and Ceiling and Middle 5

E Surface and Ceiling and Middle 4

F All

Season change

40 Overworld

41 In Water

42 Castle Walls

43 Overwater

44 Night

45 Snow

46 Night and Snow

47 Night and Snow (Castle Palette)

80-C7 Flagged objects

ROW F

0L Rope of lift 

1L Vertical rope of balance lift

2L Castle (B-F will Freeze)

30-37 Width X and Height X steps

38 Width 9 and Height 8 Steps (Will cause a nasty bug if increases)

4L Long reverse L pipe

5L Vertical balls (Used for climbing)

*60 - 67 Upside down pipe (Vertical 0)

*68 - 6F Upside down pipe (Vertical 3)

*70 - 78 Upside down pipe (Vertical 1)

*78 - 7f Upside down pipe (Vertical 5)


* I am tempt to change M.H.S's version of the Upside down pipe to the ACTUAL SMB2 Japanese Pipes because they are NOT accurate as the original. And for some reason, both of the Upside down pipes in the SMB2 J are the EXACT SAME as the other. 

=============================================================================
What are SMB2 Japanese enemies in hex?
=============================================================================

00 Koopa Troopa Green

01 Koopa Troopa Red

02 Buzzy Beetle

03 Koopa Troopa Red (Walks both ways)

*04 Green Koopa Troopa (Stopped)

05 Hammer Brothers

06 Little Goomba

07 Blobber

08 Bullet Bill

09 Green Koopa Paratroopa (Stopped)

0A Green Cheep Cheep

0B Red Cheep Cheep

0C Podoboo

OD Piranha Plant

0E Leaping Green Parakoopa

0F Vertical Red Parakoopa

10 Horizontal Green Parakoopa

11 Lakitu

12 Spiny

*13 Red Hanging down Piranha Plant

14 Infinite Cheep Cheeps

15 Bowser’s fire

16 Fireworks Generator

17 Infinite Shooters

18 Nothing?

19 Nothing?

1A Nothing?

1B Fire bar (Right)

1C Fire bar (Right, fast)

1D Fire bar (Left)

1E Fire bar (Left, fast)

1F Long fire bar

20 Stray Fire bar 

21 Stray Fire bar 

22 Stray Fire bar 

23 Nothing?

24 Lift (Balance)

25 Lift (Up and down)

26 Lift (Moves up)

27 Lift (Moves down)

28 Lift (Right and left)

29 Lift (Fall if touched)

2A Lift (Moves right if touched)

2B Short lift (Moves up)

2C Short lift (Moves down)

2D Bowser, the king of koopa

2E Stray Mushroom

2F Nothing?

30 Nothing?

31 Nothing?

32 Jump Stand (Does not act like it)

33 Nothing?

34 Warp Zone

35 Mushroom Retrainers

36 WARNING: Crashes Game

37 2 little Goombas (Vertical 10)

38 3 little Goombas (Vertical 10)

39 2 little Goombas (Vertical 6)

3A 3 little Goombas (Vertical 6)

3B 2 Koopas (Vertical 10)

3C 3 Koopas (Vertical 10)

3D 2 Koopas (Vertical 6)

3E 3 Koopas (Vertical 6)

3F WARNING: Crashes Game

40-7F Enemies that were in hard mode

80-BF Flagged Enemies

C0-FF Flagged Enemies that were in hard mode

* These enemies are NOT the true version of SMB2 Japanese. They were coded by M.H.S as well. The ACTUAL Sprite numbers in SMB2 Japanese is Sprite 04 which is the Red Hanging down Piranha Plant and Sprite 13 which is the Weird enemy.

=============================================================================
Hacking SMB2 Japanese
=============================================================================

There's some stuff in the Smb2 (J) levels and Smb2 (J) docs folder which allows to hack the ACTUAL version of SMB2 Japanese for FDS than SMB1. These 5 patches in the Smb2 (J) levels folder will allow to view every Smb2 (J) level in your SMB1 ROM will allow to edit and paste them in your FDS ROM. You will need the hex editor to dump and insert levels from your SMB1 NES ROM into your SMB2J FDS ROM. Please read all tutorials by all means. 

If you don't want to hack the SMB2 Japanese game. Then hack SMB1 with SMB2 Japanese items. It's quite useful.

=============================================================================
KEYS for SMB Utility by default
=============================================================================  
KEYBOARD ACCELATOR

KEY_PLUS_PAD - Object value +1
KEY_MINUS_PAD - Object value -1
KEY_NUMPAD_* - Object value +16
KEY_NUMPAD_/ - Object value -16
KEY_NUMPAD_8 - Object position to up
KEY_NUMPAD_2 - Object position to down
KEY_NUMPAD_4 - Object position to left
KEY_NUMPAD_6 - Object position to right
KEY_NUMPAD_9 - Next Page
KEY_NUMPAD_3 - Previous Page
KEY_NUMPAD_7 - Next Object
KEY_NUMPAD_1 - Previous Object
KEY_S+Ctrl - Overwrite save
KEY_Z+Ctrl - Undo
KEY_F2 - Open Room
KEY_F3 - Sprite Mode
KEY_F4 - Object Mode
KEY_F9 - Emulator Test Play
KEY_F10 - Emulator Page test Play
KEY_F11 - Emulator Midpoint Test Play
KEY_F12 - Emulator Stop test Play
KEY_F5 - Emulator Save State
KEY_F7 - Emulator Load State
KEY_F8 - Emulator Test Play option
KEY_TAB - Next Window
KEY_TAB+Shift - Previous Window

EMULATOR KEYBOARD ACCELATOR

KEY_N - NES A Button
KEY_B - NES B Button
KEY_Backspace - NES SELECT Button
KEY_Enter - NES START Button
KEY_Up - NES UP Button
KEY_Down - NES DOWN Button
KEY_Left - NES LEFT Button
KEY_Right - NES RIGHT Button

MOUSE ACCELATOR
- LEFT CLICK is used toggle objects and sprites.
- RIGHT CLICK is used to toggle the next and previous page.  
  When using an object or sprite, it allows to "Edit" or "Send".

=============================================================================
SMB Utility FAQ
=============================================================================

Q: What is SMB Utility?

A: SMB Utility is a SMB1 level editor that has many features, including a built-in emulator for testing.

Q: What is ISD SMB Util?

A: ISD SMB Util is a SMB1 level editor that include SMB2 Japanese item names along with corrections. ISD SMB Util stands for Insectduel's SMB Utility.

Q: How do you use the emulator?

A: One of the features include a built-in emulator.  You can go to Emulator and click on "Title Screen" to start at the title screen, "Start of level" to go to the start of the level currently opened, "Current Page" to start at the current page of the block/sprite you are editing, "Halfway Area" to start at the halfway page if the area has one, or "End" to stop.  Press F5 to save in the emulator, or F7 to load the savestate.  

Q: What are the other features?

A: Listed in "Tools" include "Edit Text", "Edit Looping Castle Loop", "World Data Update", "Sort Areas", "Record Into Demo", "General Setting", "Edit Some Game Stuff", "Options", and "Configuration".

Q: What's "Edit Text"?  How do you use it?

A: "Edit Text" can edit text, hence the name.  The text it can edit includes the Status Bar, the "Thank You" messages, "Game Over", "Welcome to Warp Zone!", the copyright at the title screen, and the 1P/2P Menu.

Q: What's "Edit Looping Castle Loop"?

A: "Edit Looping Castle Loop" edits how the Loop Commands work.  All of the values (which are in hexadecimal) are in "non-straight" columns.  The world row has the values of the worlds each command works in.  Add 1 to these values for the real world number.  The page row are the values that are the page numbers the loop commands are located.  The V pos row are the values of the locations that Mario has to be at in order to pass the commands.  The values are set up as y pos/x pos.  The Offset of map page skip data row has values of the header of each (one) page skip behind a loop command.  To find these headers, double click on the page skip block.  The value with a "H" next to it (i.e., 3FH, 43H, etc.) in the description is the header of the page skip.  I'm not sure what "World 7's loop" is.  I'm guessing that World 7's looping is special.  The two values next to it tells the world number (hex) of this "special loop".  The values should be the same.  However, I don't know what's the World's 7 loop thing.

However, SMB2 Japanese looping is SOMEHOW different, so you better use SMB2 Japanese level map to edit the loops.

Q: What's "World Data Update"?

A: "World Data Update" updates the world order to the one adjusted in the level order in the Level Select window.  I believe it's useful if you have a number of levels in a world that's not 4.  I believe that from that kind of world, if you have a warp zone to the world after that, it would go to a different level not what you wanted.  If that happens, I suggest you use this.

Q: What's "Sort Areas"?

A: "Sort Areas" allows you to switch places of levels and change the room number of the levels.

Q: What's "Record Into Demo"?

A: "Record Into Demo" allows you to record your own demo.  In the demo, you use the emulator to control Mario.  This feature roughly records this.  However, it is not very accurate, and may turn out very different from what you intended.  I believe that this may be due to the fact that what you wanted was too complex, or there wasn't enough space.

However, there's NO way that I find that data in SMB2 Japanese.

Q: What's "General Setting"?

A:  "General Setting" changes how long the game is by worlds.  This doesn't clear any other level data, however.

Q: What's "Edit Some Game Stuff"?

A: "Edit Some Game Stuff" edits other things.  At the "warpzone" tab, you can edit warp zones.  At the "1UP mushroom" tab, you can edit the amount of coins needed on each x-3 level to get a hidden 1UP on the next level.  At the "Bowser" tab, you can edit which world does Bowser start to throw hammers and what Bowser turns into when killed for each world.  At the "world" tab, you can edit which level do the levels start to get harder (shorter lifts, "after 5-3" enemies) and which world has water levels with castle blocks.  At the "other" tab, you can change how many lives you start with, whether Piranha Plants appear on 1-1 or not, TSA (graphic tiles) for the vertical balls that you can climb on, and time limits (400, 300, 200).

However in SMB2 Japanese, the warp zones is somehow seperate. By hex listing order including 0B 0C and 0D.

Q: What's "Options"?

A: "Options" has options for the emulator and editor.  At the emulator tab, you can Enable MMX (not sure what this means) and Disable Pad.  At the editor tab, you can enable a "room protect system", but I don't know what that is.

Q: What's "Configuration"?

A: With "Configuration", you can edit the keyboard commands for the editor.

Q: Any other features?

A: Yes.  You can send objects to another level, edit level headers, and insert GFX from another ROM!

Q: How do I send objects to another level?

A: Right click an object and select Send... or double-click it.  Make sure the object you are sending isn't page-flagged and there are object "entries" in the page Also, if you are sending sprites, make sure the page you send it at doesn't have a page change.

Q: How do I edit level headers?

A: Go to Edit and select Edit Header.  You can change time (if you changed time limits with Edit Some Game Stuff, 400=1st time limit, 300=2nd time limit, 200=3rd time limit), position (V:1=top, area: X= top, but slightly lower than V:1, V:10=on ground, V:4=in the middle, walking=with autowalk), Back, or starting background (first Night and snow is night and snow palette, second Night and snow is the castle palette), palette/island type (Green and tree uses a green palette with green trees, Orange and mushroom uses an orange palette with mushroom islands, Guns uses a green palette with cannons instead of trees/islands, Clouds replaces the ground, block patterns, and horizontal bricks with the clouds in the cloud bonuses), Seanery, or scenery (not a typo, spelt like that in the window), Basic brick (starting block pattern), Attribute, and Halfway page.

Q: How do I insert GFX from another ROM?

A: Go to File and select Load GFX from another ROM.  This doesn't load TSA (tile arrangements of blocks and sprites) from another ROM, however.

Q: Any other features?

A: Besides editing levels and other features listed here, you can edit the hex values of objects.  With this, you can change enemies or page changes into pointers, or vice verca.  However, I don't recommend doing this, especially the former.  This may cause sprites from other levels to be loaded in the level.  I would recommend sending objects from levels instead.

Q: How do I change objects into other objects?

A: With non-sprite/pointer blocks, you can move the block to V pos <12 for some regular objects, 12 for holes, question blocks, pulleys, and bridges, 13 for page skips (which don't work if they are page flagged) , poles, Reverse L pipe, axes, ropes, castle bridges, continuations, stopping continuations, scroll stops including the warp zone scroll stop, and loop commands, 14 for block patterns or background, and 15 for castles, long Reverse L pipes with no pipe opening on top, staircases, ropes, Upside down pipes, and vertical balls.  For enemies, you can change them into page changes by checking Skip Page and type in the number of pages to skip.  For page changes, you can change them into enemies by unchecking Skip Page and selecting an enemy type.

Q: What's YY-ME?

A: It's another level editor before SMB Utility was released.  The differences between the two that instead of sending objects in SMB Utility, you "add" or "remove" objects (but this is actually taking away or giving away objects to the next room/area (not really level).  Also, YY-ME can also load any SMB ROM, while SMB Utility can only open regular 40,976 byte ROMs or trained 41,488 byte ROMs.

Q: Are there other level editors available?

A: Yes, there's one called SMB MapEditor by ZANTETSU, which is available at YY's Japanese site.  However, I think YY-ME and SMB Utility are better.  There's also another one, which some people may have used or heard of, called Mario Improvement, available at YY's Japanese site and Zophar's Domain.  However, it can't edit enemies.  Both work with trained ROMs.  I believe that YY-ME and SMB Utility are very superior compared to these.

Q: Ahh!!  When I finish a level, the next level's number is a weird tile!  Why!?

A: From my experience, the most common reason is that the staircase (width 9; height 8)'s length is not zero.  These staircases' length should always be 0. If it's not zero, this will happen.
 
Q: Is that all?

A: Pretty much. But the Troubleshooting FAQ in the SMB2 (J) docs folder covers glitches and bugs during gameplay.

=============================================================================
Bugs & Suggestions
=============================================================================

I cannot guarantee that ISD SMB Util has bug effects. If you find one, please contact me for it. I will make version 1.01 for it. Please USE THE ISD SMB Util AT YOUR OWN RISK. Insectduel cannot, I repeat CANNOT BE RESPONISBLE that ISD SMB Util causes your computer to create viruses, make your computer crash, killed your pet animal, etc.

=============================================================================
Contact
=============================================================================

Insectduel's Board - http://insectduel.proboards82.com You can register to the forum WITH YOUR E-MAIL ADDRESS to post whatever question in the forum you have trouble with.

My E-mail address is the following below

insectduel@yahoo.com
Insectdueljapan.excite.co.jp (Japanese users only)
insectduelILOVEJAPANESEGIRLZ@gmail.com (Remove the obilivous to contact me with Gmail)

And forum PM Contacts are UNACCEPTABLE. Once I recieved a forum PM asking me about anything including ISD SMB Util will have your sent message ignored and deleted. That's because I'm most likely on INactivity in forums except Insectduel's Board.

Also note that ROM Requests will be ignored and forwarded to piracy@nintendo.com !!!! So please do not ask me for the ROM!!! It's rude!

However, English is my native language.

=============================================================================
Credits
=============================================================================

(in no particular order)

YY for SMB1 Fix
FuSoYa for Lunar IPS
Brian Bennewitz for Translhextion
Sakugarne for testing and taught me programming knowledge that I can't do.
SMB Software for designing Item SMB2J and includes SMB Mapper 1.exe and Mapper.bat
M.H.S for the red plants and pipes (Although I don't like them)

And finally

M.K.S for designing SMB Utility. Without M.K.S SMB Utility would not exist. Along with International contributors Cheezman1 and YY. We always love M.K.S

Insectduel is in no way in affiliation with Nintendo and Super Mario Bros. is copyrighted by Nintendo ©1985 Nintendo. Super Mario Bros. 2 for super players is copyrighted by Nintendo ©1986 Nintendo.

My website is located at http://insectduel.googlepages.com

END OF FILE