If the program complains about missing DLLs, all you should need is provided on the website:

http://bck.sourceforge.net/

If not, then perhaps you don't have DirectX installed. (is that even possible any more?) If the DLLs don't fix it, let me know and I'll see what I can find out.

If the program complains about a missing ROM, then go into bck.cfg and change the second line to whatever your ROM is named. The first line lets you set the size of the window, but be aware that setting it too small can cause the program to crash, as it really doesn't do any bounds checking on the screen.

If the program complains about any other missing or corrupt files, try re-extracting the zip. If that doesn't fix it, I don't know.

The "Save/Load" commands produce feedback on the console in the Linux version, or with dialog boxes in the Windows version. If you switch to another Level without saving your current one, your work IS stored in memory, but NOT on disk until you go back and save.

The "Test Rom" command uses the third line of bck.cfg for the command to run. The ROM filename is appended. I use FCEUltra, so my command is "fceu". Replace it with whatever command would be neccessary to run your emulator. Unfortunately no spaces are allowed. Example:
--
Blaster Edit.nes
fceu
--
Would run the command 'fceu "Blaster Edit.nes"' when "Test Rom" is invoked. Control is returned to BCK after the program terminates.

Using the Mouse

For Block/Map editing, clicking on something either selects it, or changes it if it's already selected. Left click decreases, right click increases. You can also use the mouse wheel. Holding Shift increases the amount it changes. You can swap Scroll Bits or USB Attribute Bits by clicking them. Click the edges/corners of the Map in Map editing mode to scroll.

For Thing/Gateway/Start Point editing, you may hit the "M" key to "lock" the mouse. The mouse pointer will disappear, and moving the mouse will move the currently selected object around. Left and Right click will change the value, if applicable. Selecting different objects can be accomplished by a mouse wheel, if you have one. Hit "M" again to unlock the mouse.

For RLE viewing, left/right clicking and the wheel select different screens.

Keystrokes

ESC always goes back to the previous menu

Alt+Enter Swaps Fullscreen Mode

RLE Viewing
Left/Right Arrow/Bracket = Prev/Next Screen

(US/S)Block editing

Left/Right/Up/Down Arrow = Browse Blocks
Left/Right Bracket = Pick which subvalue to change
Plus/Minus = Add/Subtract 1 from chosen subvalue
Shift + Plus/Minus = Jump 16 (0x10) at a time instead of 1
Shift + Left/Right (Block Editing Only) = Prev/Next Page
1-8 keys (USB editing only) = Toggle USB attribute bits (Experiment to see what sort of effects you get, I'm not entirely sure I've coded all the possibilities, and if you discover something not listed, by all means tell me!)

	Tank
	Bit 0&1 (0x00-0x03) = Which Sub-palette to use
	Bit 2 (0x04) = Unknown
	Bit 3 (0x08) = Gateway
	Bit 2&3 (0x0C) = Tunnel (From Tank to Overhead)
	Bit 4 (0x10) = Damaging
	Bit 5 (0x20) = Ladder (One you will fall through)
	Bit 6 (0x40) = Water
	Bit 7 (0x80) = Solid
	Bit 4&6 (0x50) = Lava (Damaging and slows you like water)
	Bit 5&7 (0xA0) = Solid Ladder (One you can stand on)
	Bit 6&7 (0xC0) = Destroyable (w/Crusher)
	Bit 3&7 (0x88) = Doorway (the kind that seperates Rooms)
	Bit 5&6 (0X60) = Water Ladder (One you can climb or swim)

	In Level 6 Tank section, any solid/crushable block NOT using Sub-palette 1 is considered "ice".

        Overhead
	Bit 0&1 (0x00-0x03) = As above
	Bit 2 (0x04) = "Walk Behind"/Overhang
	Bit 3 (0x08) = Tunnel
	Bit 4 (0x10) = Damaging
	Bit 2&4 (0x14) = Instant Death (Sploosh!) or Ice (Level 6 Only)
	Bit 5 (0x20) = Unknown
	Bit 6 (0x40) = Unknown
	Bit 7 (0x80) = Solid
	Bit 3&7 (0x88) = Doorway (True for all directions, but any direction but Up has Bit 2 set for cosmetic reasons)
	Bit 6&7 (0xC0) = Destroyable 

Ice in the Level 6 Tank sections seems to be a hardcoded thing, as the bitmasks don't look any different than non-ice blocks.

Map Editing

Arrow Keys = Choose Block
Shift + Arrow Keys = Choose Room
Plus/Minus (+ Shift) = As above
1-4 = Toggle scroll bits
T = Toggle Thing (Sprite/Enemy/Item) Display
G = Toggle Gateway Display
M = Toggle Start/Boss Point Display

Things are displayed in the map as two hex values. The top value is the Thing #, and the bottom is the Thing type. To the right of the map are the "proper" names for the things.

Gateways are displayed in the map as four hex values. The yellow numbers are for the Gateway on screen, the cyan numbers for the Gateway's other side. Top numbers are the Gateway IDs and the bottom numbers are the levels they are contained in. (00-07 = Overhead Sections 1-8, 08-0F Tank Sections 1-8) To the right of the map is similar info, plus X and Y positions for the Gateway and its sibling.

Start/Boss points are where your tank shows up after you have to continue, or where Jason shows up after you beat a boss, respectively. Tank sections have Start points, Overhead sections have Boss points. Start points are displayed as a single red "S", and Boss points are displayed as a single red "B".

Note: Making non-rectangular scroll borders is risky. If the player hits them at the wrong angle it can garble the graphics unless they hit pause afterwards. If they don't, they still look strange because they make the screen jerk suddenly. If you do this, make sure to test it to see what it does.

Important: Editing the garbled portions of the overhead maps is risky due to data overlap. Because of the way the program writes the ROM back out, editing *shouldn't* have any effect on it. Best to just leave it alone in the first place. I'll add bounds checking in a later version, for now just leave it alone. The error messages it spits out on the console when you view this data is NORMAL. If you don't like it, don't look at that part of the map! ;)

Thing (Sprite/Enemy/Item) Editing

Arrow Keys = Move Current Thing
Left/Right Bracket = Change Current Thing
Plus/Minus = Change Thing Type
Shift + Plus/Minus/Left/Right = As above
R = Reset Current Thing (sets position to 0,0 and type to 1F, which is ignored by the game)

You can place any normal Thing in any level, but it may not display correctly if the sprite data is loaded in the wrong place. That means no Caterpillars in Level 1. You COULD however display Red Fliers in Level 1, as they're just palette swaps of Gray Fliers. Experiment and see which enemies work in which levels. Another thing to note is that the Gate Guard can only be killed once. If you place multiple Gate Guards, they'll all die when the first one dies. I've not tested if he can be placed outside of Level 1 at all. I believe the same "only one" rule is true of the two Keyholes in Level 4, but I've not tested.Placing anything marked as "UNKNOWN" or any variant can do nasty things when they come on screen, ranging from freezing your game to doing... well, REALLY bizarre things. I believe some of them are used internally by the game and aren't meant to be placed on the maps themselves.

Global Data Editing

"Save Changes to Memory" means to write all your modifications (besides Gateways) into memory. They are not stored on disk until you also "Save Level" in the previous menu, but it does not matter which level is selected when you do so. If you leave this menu without saving to memory, all your non-Gateway changes will be lost.

Gateway/Tunnel Editing

Arrow Keys = Move Current Gateway
Left/Right Bracket = Change Current Gateway
Shift = As Above
Plus/Minus = Change Gateway Level

Note that while you can edit any gateway in the game, you will only be able to see what you're doing if the current gateway is in the currently loaded Level. It is possible to have more than one gateway on the same screen, but the editor does NOT handle this situation entirely gracefully, as the ROM never did this. It won't crash or anything like that, but some of the info will be overwritten on screen. It is possible to have a one-way gate by having the other side placed over a non-gate block, but you lose the use of a gate, so be careful how much you use it, as there are only so many Gate pairs available.

The info on the side is arranged like this:
G  L  X  Y
<Gateway ID> <Gateway Level> <Gateway X Pos> <Gateway Y Pos>
And repeated for the gate it leads to. Gates always lead to their opposite:
#0 <==> #1
#2 <==> #3
Etc etc.

Start/Boss Point Editing

Identical to Gateway editing, except that you can only edit the Start/Boss point in the current level, and the only thing you can change is its position, as that's the only attribute it has.

Boss Pattern Editing

Arrow Keys = Choose value to edit
Plus/Minus = Change Value
Shift = As Above, but for Boss 3 "P" parameter only

Boss 3 has two patterns: Spawn Pattern and Attack Pattern.

The Spawn Pattern is the first two columns, and designates where the various boxes will attempt to spawn. See blastermaster.txt for more details. Coords can range from 0x03-0x0D, but it is recommended you keep them odd to keep anything unexpected from happening.

The attack pattern is the second two columns easier to follow. The "P" parameter for any of the movement attacks designates how many "box lengths" to attempt to slide. For some reason "01" means not to slide at all, and "02" means slide one box length, etc. If a box can't slide in the designated direction, it tries the next direction clockwise until it can. If it can't slide in any direction, it gives up and shuts off immediately. For the shooting attack, it designates how long to flash before opening fire. Shift only effects editing the "P" parameter.

Boss 4 and 7 each only have one pattern, and it should be fairly self explanatory.

Misc Data Editing

Up/Down Arrow Keys = Choose Value to edit
Plus/Minus = Change Value
Shift = As Above

Most of these values should be fairly self explanatory. All are in hex. Bosses 4 and 7 and Bosses 2 and 6 share some values.

Overhead/Tank ice sections designate which level uses the "ice" code when neccessary. Remember that 0x00 is the first overhead section, and 0x08 is the first tank section. Setting the Overhead value to a Tank value or vice versa means that none of those sections are slippery.

For any of the speed values, remember that the values are SIGNED bytes, in other words 0x00-0x7F are positive, 0x80-0xFF is negative. Also remember that for negative numbers, the LOWER it is, the further into the negatives it is. ie 0x80 = -128, 0xFF = -1. The first two speed values for the Level 1 Boss are the "initial" direction, and the others are used to determine how fast to move when chasing you around. Setting the speed values on the Level 1 Boss too high can cause it to "skip" over Jason. Experiment and see just how much of a tolerance for that behavior you have.

GateA/B Editing
Up/Down = Change Subpalette (Display Only, has no effect on the ROM)
Left/Right = Change Character
Plus/Minus = Edit Character
Shift = As Above

These two data structures determine what the game paints back onto the screen when the Gate Thing types close. The game uses the pre-existing subpalette from the block that's already there, but it repaints the characters from these structures. Gate A is Thing 2A, and Gate B is Things 2B and 2C. Make sure to have the correct level loaded when you're editing these, so they show up properly. This is in here so that the gates won't look wonky if you put them in a level other than their original location.

If you have any problems with or comments about this program, go to the Sourceforge site at http://sourceforge.net/projects/bck/ and submit a bug report, tech support request, or whatever. I'll look into it as soon as I can. BE AS DESCRIPTIVE AS POSSIBLE. If the program corrupts your rom, do NOT attach the corrupted rom file, Sourceforge frowns on that due to legal issues. If I need to look at your rom, I'll ask you to send it directly to my e-mail.

Enemy Stat Editing

First column is the enemies HP. Jason's gun does 1 point, tank gun does 4/6/8 (standard/hyper/crusher). Remember that the values are in hex, ie 8 * 2 = 10, not 16. Second column is how much damage you sustain when you contact the enemy. 20 is one "block". The value is doubled when you're out of the tank, ie Jason takes twice as much damage. The third value is what sprite to spawn when the enemy is killed. It doesn't match up with the Thing table, so a different lookup table is used. The fourth column is unknown. The fifth and sixth columns are purely for reference, to tell you which thing type you're editing, as well as what it'll drop.

Palette Editing

Left, Right, Plus, Minus. All you need. Simple enough.

Level Select

This toggle changes some code in the rom to either enable or disable the debug mode. It's disabled by default. All it allows you to do is select a starting level, either at the beginning of the level (01-08), or in front of the boss (09-10). Note that at this point it does NOT give you any end of boss powerups, so you may have difficulty testing certain levels. I'll see what I can do about this, but don't hold your breath, since I'm not the person who managed to hack the routine in the first place.
