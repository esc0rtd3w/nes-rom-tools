Quarry v0.8
Written by: Dan
12/04/2003
Homepage: http://www.dragoneyestudios.net

______________________________________________________________________________________

Contents 
______________________________________________________________________________________

1.  Introduction
2.  What's New
3.  Using Quarry
4.  FAQ
5.  Bugs/Suggestions
6.  Whats to come...
7.  Special Thanks 

______________________________________________________________________________________

1.  Introduction 
______________________________________________________________________________________

Quarry is a Boulder Dash level editor written in Delphi. It supports the NES 
version of the game only. This version of Quarry is essentially a Delphi rewrite 
of the unreleased Visual Basic of Quarry, which was a rewrite of the unreleased
Visual Basic version of Quarry. :) Essentially, there have been three rewrites
of Quarry. (Hey, I'm a perfectionist!). The Visual Basic .NET version was killed
off because of slow graphics drawing time, the Visual Basic version was killed 
off because of its hideous interface, and the Delphi version was killed off ...
no wait it wasn't killed off was it ;) Anyways, currently supported features 
in Quarry are as follows: 

- Each level in the game editable. Plus there is animation :)
- Scroll data for each level is editable.
- All passwords editable.
- TSA data editor.
- World Map Editor
- Title Logo Editor
- Rockford Palette Editor
- Palette and block colour attribute editor.
- Level Importer/Exporter. Compatible with all versions of the Quarry level
  export format (For those of you who have the unreleased beta versions)

This program is downloadware. You need to download it before you can use it. :) 

______________________________________________________________________________________

2.  What's New 
______________________________________________________________________________________

Version 0.8 ~ (The tidy release)
- Added title logo editor, and world map editor. Both are unoptimized and may lag
  a bit on older machines (Hell, it lags a bit on my 1.54 ghz PC)
- Added a rockford palette editor. Edits rockford's choice of colours.
- Moved the gridlines and animation checkboxes into the toolbar.
- Made the tile selector 8x2, instead of 4x4.
- Fixed the stupid thing I did in the previous version, where the encrypted datafile
  was written to the disk, in an unencrypted format. :S
- Rewrote the code, so I would not be ashamed of it if I released the source.
- Rewrote the code so it has a bit of error checking now
- Fixed a shit load of potential memory leaks. Quarry now tidies up behind itself :)
- Added a label on the palette dialog that tells you which colour you are on in the
  colour selector.
- Fixed the Exit button. It actually works now :)
- Altered the Erase Level code so that instead of flood filling the level with empty
  spaces, it fills it with diggable earth.
- There are now Tooltips on the Palette dialog for each of the eight palettes.
- Fixed a bug with scroll editor's preview pane.
- Fixed a lazy (on my part) memory leak.
- Added animation to the level editor. May be slower to navigate the levels, so
  I added an option to disable it. It's disabled by default (or you can set the
  default). You can also set the time between each frame redraw.
- Fixed a TSA bug that was caused by my inaccurate picturebox size :P

Version 0.7 (Delphi)
- Rewritten in Delphi.
- Totally scrapped the old interface and redid it.
- Moved the data into encrypted ini files.

Version 0.7 (Visual Basic)
- Redesigned the palette dialogs to be smaller.
- Accurate.pal is used by default.
- Scroll data is now dumped in the BDD file that is exported.
- Fixed a few grammar errors in Import/Export dialog.
- Quarry now remembers the last rom that was loaded, and the directory of the ROM.
- Very basic scroll editor built-in, with templates.
- Speed boost for the TSA editor, quite quick now.
- The dragoneye studios link in the about box is now clickable (although it does 
  take over an instance of your browser if you have any)
- Speed boost for the entire program. Because of this, to save the changes made 
  to your ROM, click the 'Save ROM' menu item in the file menu.
- Help file is now in HTML.
- Gridlines flickering, and start block flickering is now eliminated :)
- TSA Editor's block display is now smaller.
- TSA editor's block selector is now images of the 44 blocks in the game.
- Time and crystals for each level are now moved into the scroll dialog, and the 
  dialog is now a level properties dialog instead. 

Version 0.6 (02/01/2003) 

- Includes the accurate NES palette in the ZIP. Just change the palette you want 
  to use in the options, to 'accurate.pal'.
- TSA editor has a new palette switching thingie.
- World map editor can view the world map. Editing not yet coded yet, the palette
  is (totally) wrong, and the Temple and Mountains that aren't part of the map 
  cannot be viewed yet.
- Palette editor is now available. May not be 100% correct though.
- TSA editor now tells you which block you are at.
- Level can draw gridlines now. Two new options related to this are in the options 
  dialog.
- Gridline Colour (which allows you to set the colour of the Gridline), and View 
  Gridlines on level edit by default (in case you can't be arsed constantly 
  flicking the gridlines off at every level) Gridlines cause a bit of flicker 
  though, which has to be resolved (API :))
- Added the Dragoneye Studios url on the About box. How dumbass of me to forget :P
- Fixed the options 'cancel' button, so it actually cancels now, instead of doing 
  squat all.
- Added import/export level options. Need to find the data that tells the game how 
  many blocks to scroll to be truly useful though. 

Version 0.5.1 (01/01/2003) 

- First easter-egg style feature, only an easter egg because I'm not happy with it 
  yet. But it does work. If you can find it :D
- Fixed the TSA editor, which didn't update the Tile Selector when you selected 
  a new palette.
- Added the password editor. Quick to add too!
- Added the scrolling code, which highlighted a few bugs in Quarry.
- The horizontal scrollbar now scrolls one tile instead of two. Fixes the bugs that   
  existed with the start position viewing.
- Forgot to credit one of the most important people who provided source, The Fake 
  God. Now credited in both the About box and the readme. Always give other people 
  credit for their work. 

Version 0.5.0 

- Converted mostly to VB. 

______________________________________________________________________________________

3.  Using Quarry
______________________________________________________________________________________

I have made Quarry so it is incredibly easy to use. If you find any trouble with
it, post on the CG boards, or pm me, or email me.
______________________________________________________________________________________

4.  FAQ
______________________________________________________________________________________

These are just questions that I have decided to put together. They aren't really
questions that have been asked, but I forsee them being asked.

Q. What took so long to make this?

A. If you look at the introduction it explains this. It actually took less than
   a month to fully code this Delphi version, though.

Q. You are aware that you can open any ROM in this?

A. Yes, I am fully aware of this. I may put in some kind of protection to stop
   people from opening anything but an iNES rom, but if someone manages to code
   an emulator that can run the UNIF rom, then this would be pointless. The iNES
   format isn't designed to give explicit information about games. All it gives
   is information on mapper numbers, mirroring, etc. Anyways, if you want to be
   a twat and try and break Quarry, then be my guest. It won't get you any
   respect. * NEW * iNES Mapper Checking code has been implemented in v0.8. This 
   checks the iNES header of your ROM, and makes sure it matches the specified 
   mapper settings. This is also configurable, so you can ignore it if you want to.

Q. How do I add palette files to the list?

A. Later versions of Quarry will have palette list management built-in. Currently,
   the only way to add them is by using notepad. Ask me if you cannot figure it 
   out. :)

Q. Arghhhhhh! The scroll editor crashes all the time! Fix it!

A. Actually, I don't honestly know if crashes at all. This is just incase it does.
   Essentially to use the Scroll Editor properly, you need to follow these 
   guidelines:

   The Start X position requires a hexadecimal value between $0 and $200 and the 
   Start Y position requires a value between $0 and $90. Select the first 
   direction that you want to scroll to, but make sure that it is logical to do so, 
   (don't try to go up when you are already in the top-right), and type the value 
   that you want to scroll to.

   If you follow that, you should no problems whatsoever. If you mess it up and
   complain hard enough I may put a feature in that can repair the scroll data. Or
   I may restore the templates-based system that was in the Visual Basic betas.

Q. I open a ROM, and it appears with strange graphics and colours! What's 
   happening? Am I tripping again?

A. Well, you are probably not tripping. What has happened is you have loaded a ROM
   that is not supported by the current datafile that you have selected. Download
   the GoodNES tool (found at http://www.zophar.net, in the GoodXXX page), and scan
   the ROM. This should tell you what version of the ROM you have. Quarry supports
   three versions of the ROM:
   
   - Boulder Dash (U)
   - Boulder Dash (E)(!)
   - Boulder Dash (J)

   So, if your scanned ROM is not one of the above, chances are it won't work.
   But come on, I found all of those ROMs in about five minutes on Google. It's
   not hard. And no, no links or ROMs from me.

Q. I look in the datafiles, and all I see is garbage! What's the meaning of this?

A. Well, the data files are encrypted. That's all really. I don't mind people 
   seeing my data, but not right away. When I'm totally finished with Quarry,
   I may release my source, and the method I used to encrypt the data. Until then,
   you probably may not be to decrypt it. It's not a simple encryption.

Q. How do I use the TSA editor?

A. It's quite simple actually :) Essentially all you have to do is bring up the TSA
   editor dialog, and select the block you want. Then you right click on the tile
   selector on the main window, where you want the tile to be. Quite easy, I reckon.

Q. Hmm, the enemies are a bit fucked up. What's going on?

A. Personally, I don't really know. I do know what enemies that some enemies work on
   some stages, whereas others don't. It's pretty simple that way. Just use the ones
   which are already used in the levels and you should have no problems. Also, don't
   use the very last (the spider) as an enemy. From what I can tell, it just sits 
   there doing squat all. There are some levels where the amoebas turn into diamonds,
   or do nothing too. Unfortunately, I cannot do anything to fix this. (yet)

Q. When I make a level which involves you collecting all the diamonds from the bottom
   right, an exit block appears in the bottom right. What's going on?

A. Again, no idea. From what I can tell, the Boulder Dash ROM was created VERY
   sloppily. It could be a weird bug, but I'm not sure. Hopefully in the future, I
   can get an ASM master to look into it, but I wouldn't hold your breath 
   unfortunately.

______________________________________________________________________________________

5.  Bugs/Suggestions 
______________________________________________________________________________________

If you find any bugs, or have any suggestions (not ones like make it faster, 
as unless you provide code which you know is faster than mine, you'll be 
getting the middle finger son) pm me. Or e-mail me. You can also contact me 
at the Challenge Games board, if you just want to give suggestions and stuff. 

______________________________________________________________________________________

6.  Whats to come... 
______________________________________________________________________________________

- The random level generator will be rule based.
- Sprite Editor.
- World Map Editor
- Title Screen Logo Editor
- Rockford Palette Editor
- Code tidied up and released as open source.
- Better readme, with actual tutorials.
- Quite possibly a demo patch that demonstrates Quarry in action.

______________________________________________________________________________________

7.  Special Thanks: 
______________________________________________________________________________________

- Parasyte
- Vagla
- Dr Jay Phd
- The Fake God
- DahrkDaiz
- Skiffles
- Gil-Galad
- The creators of the palette files that I included with this ZIP. 
- Anyone who uses this to make a hack.