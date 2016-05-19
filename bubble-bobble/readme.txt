BUBBLED version 2
_____________________________________
- Written by Ted Robb, © 2001-2002  -
- http://www.tedrobb.com/bubbled	-
- tedrobb@tedrobb.com			-
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

There are 3 editor modes, level editing, enemy editing and item editing. You can switch editor modes with the E key.

Level Editing
-------------
Select the type of tile you wish to use from the tool box on the left of the screen.
Then use the left mouse button to "paint" the tile on your level.
Here is the selection of tiles, and a description (how they act in the game).

|  Type   | Description											|
+-----------------------------------------------------------------------------------+
|  EMPTY  | Blank space which doesn't modify the movement of the bubble (moves up)  |
|  SOLID  | Regular solid block									|
|  FAKE 1 | Fake block, character falls through it. Doesn't allow bubbles through.  |
|  FAKE 2 | Fake block, character falls through it. Allows bubbles to go through.   |
|  DOWN   | Bubble mover, moves bubbles down							|
|  RIGHT  | Bubble mover, moves bubbles right							|
|  LEFT   | Bubble mover, moves bubbles left							|
|  ITEM   | When you get a bottle, a treasure will appear here.				|
+-----------------------------------------------------------------------------------+

On the right of the editor screen, you will see PALETTE, MISC DATA, and SPECIAL BUBBLES.

PALETTE
These are the 3 colors used for the selected level, you can modify them by clicking on the left/right
arrows next to the color.

MISC DATA
In this version there are two MISC options, Bubble speed and Enemy bubble pop.
Use the left/right arrows next to the value to modify it. NOTE: Enemy bubble pop is how long it will take for
a bubbled enemy to burst out. With the value 14, they will pop almost instantly. Earlier levels use the 0 setting.

SPECIAL BUBBLES
There are 3 kinds of special bubbles, lightning, fire, and blue bubbles. Also included here is the option 
to open the top of the level.

Level Editing Key List
----------------------
Here is a list of the keys used while in level editing mode.
NOTE: The arrow keys and spacebar are used for fine editing, using the mouse is much easier.

| Key   | Function                              |
+-----------------------------------------------+
| LEFT  | Move the tile one space to the left.	|
| RIGHT | Move the tile one space to the right.	|
| UP    | Move the tile one space up.		|
| DOWN  | Move the tile one space down.		|
| SPACE | Place the tile in the selected space.	|
| C     | Clear the entire level.			|
+-----------------------------------------------+


Enemy Editing
-------------
Use the mouse to select the enemy who you wish to modify. Use the left/right arrows next to the enemy's
picture to change it's type. 

Enemy Editing Key List
----------------------
Here is a list of keys used while in enemy editing mode.

| Key   | Function					|
+-----------------------------------------------+
| UP    | Move enemy 8 pixels upwards.		|
| DOWN  | Move enemy 8 pixels downwards.		|
| LEFT  | Move enemy 8 pixels to the left.	|
| RIGHT | Move enemy 8 pixels to the right.	|
| NUM 8 | Move enemy 1 pixel upwards.		|
| NUM 2 | Move enemy 1 pixel downwards.		|
| NUM 4 | Move enemy 1 pixel to the left.		|
| NUM 6 | Move enemy 1 pixel to the right.	|
| NUM 5 | Change enemy facing direction.		|
| INS/A | Insert a new enemy.				|
| DEL/D | Remove the currently selected enemy.	|
+-----------------------------------------------+


Item Editing
------------
As of version 2, you can edit the positions of the common and rare items in your levels.
Just select the item on your level, and use the arrow keys to position it however you like.

I don't think you need a table.. do you? :)

Editor Key List
---------------
Here is a list of keys that are used in both editor modes.

| Key       | Function													|
+-----------------------------------------------------------------------------------------------+
| ESC or Q  | Quit the editor (If level has been modified, you will be asked to save).		|
| +/-       | Change levels (If level has been modified, you will be asked to save).		|
| PRINTSCR  | Take a screenshot of the editor screen (saves as screenshot.pcx)			|
| ALT+ENTER | Switch between fullscreen and windowed modes.							|
| S         | Saves any modifications you have made to the selected level.				|
| E         | Switch editor modes (If level has been modified, you will be asked to save).	|
+-----------------------------------------------------------------------------------------------+

Bubbled.conf
------------
Configuration file for Bubbled. The only option is the filename of the Bubble Bobble romfile.

IPS Patches
-----------
The IPS patcher/creater UIPS is included, see uips.txt for instructions. NOTE: This program was not
written by me.

Thanks
------
Thanks to megadog for his info about palettes, sprites and other stuff.
Thanks to BigEd94@aol.com for his info about enemy IDs.

---------------
Please contact me with bug reports, comments/questions, or suggestions for future improvement of Bubbled.

klone (aka Ted Robb)
http://www.tedrobb.com/bubbled
tedrobb@tedrobb.com

