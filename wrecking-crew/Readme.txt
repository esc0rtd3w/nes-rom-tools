Demolition v1.0
Written by: Dan
23/07/2003
Homepage: http://www.dragoneyestudios.net 

______________________________________________________________________________________

Contents 
______________________________________________________________________________________

1.  Introduction
2.  What's New
3.  Using Demolition
4.  FAQ
5.  Bugs/Suggestions
6.  Whats to come...
7.  Special Thanks 

______________________________________________________________________________________

1.  Introduction 
______________________________________________________________________________________

Demolition is a level editor for the NES game Wrecking Crew. It is written in Delphi,
and is displays a pretty much 99% (I don't want to jinx myself by saying 100%) perfect 
rendering of a Wrecking Crew level. You have no idea what I went through to actually 
implement this ;) The game itself has some pretty wacked out level designs. I actually
had to double check that my data was correct as the levels looked, um, crap.

Demolition has the following features:

 - Can view/edit all 100 levels
 - Can exports to a separate file and import them back again
 - Can export any levels that you may have created in the ingame level designer to
   allow you to import them into your ROM, permanantly.
 - Can edit the lives you start with.

______________________________________________________________________________________

2.  What's New 
______________________________________________________________________________________

Version 1.0 (First Release)
 - Ahem, everything is new.
______________________________________________________________________________________

3.  Using Demolition
______________________________________________________________________________________

Demolition is very easy to use. If you have any troubles whatsoever with it, email
me at the address at the bottom of this document. 

______________________________________________________________________________________

4.  FAQ
______________________________________________________________________________________

These are just questions that I have decided to put together. They aren't really
questions that have been asked, but I forsee them being asked.

Q. What took so long to make this?

A. Purely coding, Demolition took me about two days to allow you to edit all the 
   levels. TSA data was a total bitch though.

Q. What is Wrecking Crew?

A. Wrecking Crew is an ancient NES game, which stars Mario. Basically, you have to run
   around demolishing the scenery in the levels. Wrecking Crew received an update in
   the form of a SNES version. Unfortunately, the SNES version was a pretty crappy
   puzzler, which wasn't a patch on the original, imo. They did include the original
   NES version as well in the SNES game, so it wasn't entirely bad. This program
   does not edit the SNES version.

Q. You are aware that you can open any ROM in this?

A. Yes, I am fully aware of this. I may put in some kind of protection to stop
   people from opening anything but an iNES rom, but if someone manages to code
   an emulator that can run the UNIF rom, then this would be pointless. The iNES
   format isn't designed to give explicit information about games. All it gives
   is information on mapper numbers, mirroring, etc. Anyways, if you want to be
   a twat and try and break Demolition, then be my guest. It won't get you any
   respect.

Q. I open a ROM, and it appears with strange graphics and colours! What's 
   happening? Am I tripping again?

A. You probably opened the wrong ROM. The GoodNES rom that you want is 
   Wrecking Crew (JUE). All other versions are unsupported at this time.

Q. I look in the datafiles, and all I see is garbage! What's the meaning of this?

A. Well, the data files are encrypted basically. It also makes me look like less of
   an idiot, as I had to compensate for those bloody ladders.

Q. Why haven't you got a palette editor or TSA editor?

A. The main reason for this, is that the TSA data for this game is such a mess. Mapper
   0 games, (which Wrecking Crew), have a tendency to use severe optimisation when it
   comes to data. Plus you'd have to manually edit each frame of animation. So really
   it wouldn't be worthwhile in my opinion. Palette editor isn't available because
   I don't believe it would be worth putting it in without a TSA editor. If you really
   want to do palette hacks, the data is at $5C3E. Demolition does load the palette
   in from the ROM, though.

Q. Why have you got a save state exporter?

A. Well, in case you didn't know, Wrecking Crew came with its own level editor. 
   Funnily, it had save and load functions, even though it came with no battery back
   up. Nintendo believed that they could implement some way of saving later on. 
   Anyways, the save state exporter allows you to export the levels that you have 
   created using the in-game editor. In case you are insane enough to actually prefer
   using the in-game editor to Demolition. This currently only supports FCEU savestates.

______________________________________________________________________________________

5.  Bugs/Suggestions 
______________________________________________________________________________________

If you find any bugs, or have any suggestions (not ones like make it faster, 
as unless you provide code which you know is faster than mine, you'll be 
getting the middle finger son) pm me. Or e-mail me. You can also contact me 
at the Dragon Eye Studios board, if you just want to give suggestions and stuff. 

______________________________________________________________________________________

6.  Whats to come... 
______________________________________________________________________________________

- Erm, pretty much nothing with this editor.

______________________________________________________________________________________

7.  Special Thanks: 
______________________________________________________________________________________

- Vagla
- The Fake God
- Gil-Galad
- The creators of the palette files that I included with this ZIP. 
- Anyone who uses this to make a hack.