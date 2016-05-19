Readme file that comes with Jade.

Contents:
1 - Introduction
2 - Version history
3 - What's new
4 - Misc info
5 - Unsupported FF2 ROMS
6 - Contact info
7 - Credits

/=============================================================================================\
| 1 - Introduction									      |
\=============================================================================================/

	Ever since FF Origins was released, I suddenly had an urge to want to make an FF2 hack.
The difficulty was the big issue I wanted to address. It was either far too difficult or too
easy, depending on the approach. But there are a few other things I also wanted to change. The
biggest annoyance of ROM hacking is taking the time to change all the offsets. Seeing as though
changing the offsets by hand wouldn't be feasible, I decided to take up C++. Doing so would kill
two birds with one stone. Learn how to read hexadecimal and learn C++.

/=============================================================================================\
| 2 - Version history									      |
\=============================================================================================/

10-15-04 Jade v.09d

Character Editor: I've expanded the items in the two belts slots. ANY item can be saved there.
But if your game crashes (like if you put Phin/Fin or a key item other than the Hiryuu in a
slot, etc) don't yell at me.

o_O When I optimized the code a couple verions back, I must have accidently deleted the line
to save magic defense experience. Oopsie, it's fixed.

Text Editor: Length detection is in only for the character names. And, also fixed that nagging
error that would decapitate the stats of any named changed character.

For now, editing the Epilogue has been left out. There is a conflict between the Prototype and
Demi's translations. I'll get this figured out. (There's actually a couple conflicts, but this
was the only crash bug producing conflict.)

The advise of not editing dialogue still applies, as I've now been deciphering the variables.
They still do not display at this time. Don't click the Save button with Epilogue highlited, or
else be drown in your own stupidity.

Formation Editor: *NEW* Now you can finally change the insane battle formation data. Errr,
well, most of it. Hehehehe... For now, I choose to be evil and not let you change what two
palettes are used. Rest assured, all of the data will be editable soon enough.

Spoils Editor: *NEW* I ran out of room in the Monster Editor, so this was made as a result.
There are 60 sets of things that can be dropped. The "random" amounts of Gil that can be
dropped was a good idea actually, and I'm kind of surprised it was used again in the later
games of the series. (FF4 on up.)

----------------------------------------------------------------------------------------------

9-21-04: Jade v.09

Jade: Added two more tables, a DTE for the standard, and a DTE for the prototype. The two
normal tables have been adjusted as a result.

Font Editor: *NEW* Guess what, this doesn't really do anything except show the font. =p It
also displays a pretty small picture.

Shop Editor: *NEW* With the exception of the empty slot, you can put anything you want in a
shop. Just know that some items aren't really meant to be used... Right now, you can edit the
contents of the shops, just not shop locations (for that, I would need town/dungeon map data).
Thanks to Dragonsbrethren of the TEK boards for identifying a shop location, the Tropical
Island shop.

Text Editor: *NEW* Right now, you can edit any text that the editor already sees. You CAN
edit dialogue, however, I highly recommend against it. Not everything is displayed with
dialogue, and saving would overwrite what isn't displayed. In short, bad. Also, there's no
length detection and nothing to prevent you from overwriting existing data. Just be mindful
of what you are editing and what comes next in terms of text, and you'll be fine.

Character Editor: Removed the safeguard about learning spells in order. The idea was nice in
principle, but was ultimately pointless. Also, see the next section for further details.

Really did fix the dominant hand and row position saving errors.

Monster Editor: Minor cosmetic tweak, made the 'Added effect' area a bit smaller, and stretched
out the 'Elemental Weakness' and 'Elemental Absorb.' This way, it should be easier to distinguish
which set is which. (Better be, anyway. It can't get more obvious than the current setup.) =\

I came to my senses with stats. You can now edit Index 0 of HP, strength, number of hits, and
accuracy.

----------------------------------------------------------------------------------------------

7-17-04: Jade v.06

Jade: The Prototype table has been updated, many thanks to Dragonsbrethren of the TEK boards
for providing this.

You no longer need to name Prototype.tbl to StandardTable.tbl for the Prototype table to load.
It now loads on its own, as is.

Added support for the FF1+FF2 combo cart. I will only say this once, and the "check version"
button will remind you from here on out. Jade will only edit the FF2 portion of the FF1+FF2
combo!

Misc.: Parasyte has submitted an IPS patch that will fix the flickering title screen for v1.03.
That IPS is included.

Character Editor: Thanks to Dragonsbrethren, fixed a bug. Maria would always and for no reason
save as left handed, and as Firion/Frionel's graphic index.

Spells Editor: Figured out some of the obvious unknowns, some still remain, however.

There is an error I'm aware of, but it is cosmetic. Say you loaded the Prototype, then edited
some spells. Now you switch (without exiting Jade) to say Demi's v.93, the AI pack will have
the Prototype spell names instead. This also applies to the Weapon Editor and Monster Editor,
since AI is displayed the same way between all three. I'm not really sure if I'm going to do
anything about it, but we'll see what happens.

Monster Editor: Added Effect now implemented, some extensive testing went into this, so
this shouldn't have a problem.

Weapon Editor: Added Effect is the same with weapons as well as monsters, so it is in here too.

!!NOTE!! Added effects cannot be mixed, which is a shame really. Also, the Ripper dagger
effect does NOT work. This will be addressed later, so do not fret.

----------------------------------------------------------------------------------------------

5-18-04: Jade v.05

Jade: Added a new IPS, an update from the prototype cart. Also added a new table file so
everything is displyable. However, you must rename Prototype.tbl to StandardTable.tbl for it
to work, mostly because I'm lazy. :) This will not change either, so live with it.

Added the option to lock your hack, so the noobs and cheater's can't get into it. Far less
hidden than FuSoYa's way of locking your hack, that's for sure. :)

Character Editor: Implemented a new safegaurd, this one prevents you from putting spells
"out of order." You must have a spell in slot 2 before you can put a spell in slot 3, etc.
I'm not sure how long this one will stick around, so bear with me.

Monster Editor: Well, you may as well just call me an idiot. Morale shares a table with
strength and defense, not monster race. This information was gracefully pointed out to me by
awj. :) My credibility has been shot down to nothing at this point. My deepest apologies to
everyone. As a result of this, I've re-added the edit field to Morale. The only thing I did
get right about Morale is that the higher it is, the more likely a monster is to run.

Artificial intelligence is now enabled, edit to your hearts' content. It's a lot better now
than the update from 2-24-04 isn't it? :D Added effect is NOT in yet, getting it to display
correctly hasn't gone smooth yet, so I've put it on hold until the next update.

Spells Editor: Formerly known as the Magic Editor. Added the AI list.

Also expanded the spell list, the entire list of spells in the game is editable, at least to
my knowledge. =\ Guess that isn't much reasurrance, sorry. Palette and animation are all
that remain!

Weapon Editor: Because Monster AI is enabled, weapons that cast spells is also enabled. Both
use the same list of spells.

----------------------------------------------------------------------------------------------

4-07-04: Jade v.04d
About box: Oops, forgot to change that to v.04 when v.04 came out. =\

Monster Editor: Added Monster Race to the list. And, as it turns out, Morale and Monster Race
use the same table... Yeah I know, insert your own durogatory comments. Took away the edit
field to Morale, live with it. =p The edit field for added effect will remain until the next
update.

Weapon Editor: Minor tweak to the code that determines when it should say "Elemental attack"
and "Elemental defense." It's based on weapon type now, and not what it highlighted. =p

Magic Editor: It no longer shows the 2nd status ailment for temporary ailments.

Figured out the unknown for direct damage and healing type, it's spell power. =\

Misc.: Added two more IPS files, updates from v.93 (which I should've added a long time ago),
and now from v1.0. There is a reasoning for this maddness, as it is now explained in the next
section.

----------------------------------------------------------------------------------------------

4-01-04: Jade v.04
Weapon Editor: For now, I added the ability to change the added effect and spell cast from item
in hex. For cast spell, FF means no spell is cast. For added effect, 0 means no added effect.

Added Magic Editor!

Magic Editor: I REALLY wanted to use radio buttons for spell types, but I couldn't get them to
work. I tried check boxes, that would've been way too much work. So another list box is used
instead. =p For the same reason as the rest, you cannot edit the graphics, but you can save
the hex values they use. I know I said I wouldn't allow it, but I decided to at the last
moment. That big glob of space is where palette and animation info will go when it's deciphered.
Also, be careful about some spells that are used out of battle. (Cure, Life, etc) THAT info
hasn't been found yet, so try to refrain from making drastic changes. :)

3-30-04: Jade v.03e
Monster Editor: Morale works now. Call me a bad coder if you wish. This error should not have
happened. As a result, Elemental absorb is likely messed up for any monster you saved. See the
FF2 Monster Bytes text file, (it's still in hex, as I haven't quite figured out the table
behind the elemental properties for monsters yet.)

Weapons Editor: Fixed the "added damage to monster types." As a result of this error, it's
likely that other stats are messed up. See the FF2 Gear Bytes text file.

Misc.: Instead of linking the text various text files, all of them will now be included.

----------------------------------------------------------------------------------------------

3-17-04: Jade v.03d
Monster Editor: I think I rushed Morale a little bit. You can now save changes made to Morale,
and when the index is changed, the information is updated. Sorry about that. =\ 

Weapon Editor: 
Added "more damage to monster types," that leaves "attack with" and "when used as an item."

----------------------------------------------------------------------------------------------

3-16-04: Jade v.03
Monster Editor: Morale has been added. I forsee a problem in the future. When the elemental
properties and attack types are deciphered, I will run out of room before I can get everything
meshed in there.

Armor Editor: Now there aren't ANY unknowns! Ha ha! There was an issue with v0.02/d. I was off
on the starting byte for each piece. You see, I was GUESSING before I knew where it was. If you
made any extreme changes, then head to http://www.geocities.com/abgh21/ff2gearbytes.txt and
compare the game's list to your list.

Weapon Editor: This is new... The update originally scheduled for 3-13-04 was delayed. The cause
of the delay was pretty much ALL of the equipment data was handed to me about 5 minutes before
the update was uploaded. =\ The original update only had attack power deciphered too. Aren't you
happy you can change it all now? ^_^ Great deal of thanks to awj (first contributor) and Vagabond
(second contributor) for this information. Every aspect of weapons cannot be edited yet, I
decided to go ahead with the update as is right now.

----------------------------------------------------------------------------------------------

3-07-04: Jade v.02d

Character Editor: Fixed shield exp. When saving, it grabbed the info in the fist exp field. Don't
 know how long that went unnoticed... Oh well. =p

----------------------------------------------------------------------------------------------

3-1-04: Jade v0.2

Jade: Gave it an icon.
Main dialog: Oh crap, it's the Emperor!
About dialog: Oh no, Astaroth killed the party!
Monster editor: No progress on the "attack with," course it helps if I try to decipher it. =p
Armor editor: Hey, this is new! Right now the only value I know is defense. Rest are in as hex
 values.
Misc: Changed Update.ips to mention that it's for Demi's incomplete translation. Added an .ips
 for the Original Japanese version.

----------------------------------------------------------------------------------------------

2-27-04: Jade v.01d

Monster Editor: Spoke too soon about the saving stats. Turns out Strength, Accuracy, and # of
hits were saving the value -1 of the index you selected. I guarantee it works now.

Made sure that Strength, Accuracy, and # of hits were at least one when saving. (They did before,
but the order of saving nullified that safeguard.)

Added "attack with" index. The table it points too hasn't been deciphered yet, so the values are
displayed in hex. I suspect that you can mesh anything together from 0 to FF, so feel free to
try some values out. Here's what I do know, though:
04: Drain a LOT of HP.  Used by Skull, Revenant, Wraith, Specter, Ghost, VmpGirl, VmpLady,
    DthRider, Astaroth, and the Emperor (final battle). 3-12-04: UPDATE! This drains 1/16 of MAX
    HP per hit, plus normal damage calculations.
08: Drain MP. Used by Sucker. (This succeeds even if target evades attack.)
05: Envenom (2nd level poison, sticks with you after battle)
0A: Poison (randomly fades during battle, fades after battle)

If there is a system behind this, as I suspect there is, then it'll take some time to crack.

I think I know the lower bit of the Magic Evade byte. It's likely race, however, it probably
points to a table. Also, with gear data not found, testing it is almost impossible.

Also, Elemental Weakness, Resistance, and Absorb are probably also pointers, yet I haven't gotten
to testing them yet. I've been doing a million things at once.

----------------------------------------------------------------------------------------------

2-24-04: Jade v.01
Character Editor:
Implemented a safeguard that prevents you from setting the four starting characters in the back
row. Did the same for the first three plus any character that takes up the fourth slot. Do you
really want your game to freeze up in battle? ^_^

I gave the whole editor a cosmetic change, hope you like it. :)

Monster Editor:
Figured out why AI wasn't displaying properly, so now it's in. The spells in each pack have not
yet been found, so you can't edit those YET.

FIXED the saving function. Somehow, without me realizing it, I managed to confuse high bit and
low bit so stats were saving backwords. No problems exist with monsters now, which is great news.

----------------------------------------------------------------------------------------------

1-27-04: Second beta released. Changed character editor to load the spell text, gear, and
character names from the rom itself. Fixed crash bug that would crash the program if the table
file couldn't be loaded. Added a version checker in the main dialog if you are not sure about
which version of the ROM you have.

----------------------------------------------------------------------------------------------

12-20-03: First beta released. Character editor and monster editor up and running. Can edit
monster stats, character stats, character magic, character's gear, character's position,
character's dominant hand, and character's weapon proficiencies.

/=============================================================================================\
| 3 - What's new									      |
\=============================================================================================/

10-30-04 Jade v.10

Yay, tenths digit for version number. *fanfare*

Misc.: Apparently the palette file wasn't entirely accurate. So it has been updated. *shrug*
The old one was FFHackster's palette file, in case anyone is curious.

Character Editor: Minor cosmetic tweak.

Formation Editor: Figured out how palettes are displayed (in battle) and are now editable. Note
that the monsters that are a whole pattern table will use both palettes regardless. You can also
change the palettes themselves.

Currently, changing a color of a palette will be pseudo permanent. If you wish to revert back
to the old color, avoid saving, exit and re-open Jade. (Or just change it back, whichever works
for you.)

Spells Editor: That little issue with palette's has been solved, animation's are all that remain
now. :)

Text Editor: As of now, just about everything displays for dialogue. I've also discovered that
the Prototype translation has massive conflicts with Demi's translation. However, since there's
an issue with keywords in dialogue, and character name's are yet to be displayed, I still
recommend against saving any dialogue changes.

Weapon Editor: Figured out what weapons use what palettes, and some weapons don't have palettes.
("Unarmed" and every shield.) NOW, I just need to enable editing the in-battle graphic of each
weapon. :)

/=============================================================================================\
| 4 - Misc. info									      |
\=============================================================================================/

Basic rule of ROM hacking, always make a backup of your ROM. (That's pretty much common
knowledge by now, but it's helpful for those that don't know.)

You should keep a few things in mind while editing...
1. Frionel's stats, spells, and gear are copied to Lionheart for the opening battle.
2. Some monster stats like Strength and Defense share the same offsets. I grouped up stats that
   share offsets so it'll be easy for you the user to change values. Just make sure you keep
   other monsters in mind when you change a value.
3. Monsters need MP to cast spells, so if they don't have enough MP to cast a spell, they'll
   attack instead.
4. The Intelligence and Soul penalties... They appear to be an "in battle" effect only. I don't
   know if it's high bit/low bit, or if that number is subtracted from both, or if it even works
   period. But most gear has insane penalties (all shields have a default 70 penalty) so I have
   no idea. This may explain why magic sucks so badly on FF2. =\
5. The IPS files are for when you decide to make a hack for FF2. There are many versions of the
   rom out there now (6 by my count, likely more). Making an IPS file based on different
   versions will mean that they don't work for many people. So, this is the plan, and it is
   policy. When you make an IPS to release your hack, you must base it off of v1.03 of the rom,
   which is what every IPS included updates your rom to. After some consideration, you must base
   if with the title screen fix.
6. About the AI, the first unused spell is a dummy item that was never used. The second unused
   is the item Cottage, which is equippable. Just keep that in mind.
7. I think I had better cover this now, there are only three item shops, but every town uses
   those three item shops. Mysidia uses all of the spell shops you've seen previously up to that
   point, plus their own shop. Also, you can assign any price to any item, it will not affect
   the selling price. Selling has its own section of data, one for every item. Obvoiusly, you
   cannot sell key items (and oh, how I wish you could.....) Perhaps that will happen in the
   not to distant future.
   Note: awj contacted me sometime after I wrote this, and he suggested that the unused prices
   may actually be treasure chest finds. It would make sense after all. It remains unknown at
   this moment in time.
8. Ahh, the Text Editor. Two things, "Pointer:" is the location of the pointer. It's at that
   address, plus the next byte. Little endian! Fun! "Location:" is the where the highlited
   text starts. Anyone experienced enough with pointers really doesn't need this window, but
   I put it in anyway. For kicks, I added "Value:" which means the value of the pointer. This
   isn't needed for the experienced hackers, but should be handy for the less experienced.
9. In the Character Editor, if you set a spell slot to have a level other than one, the first
   spell in that slot will have the correct level. Once you move it and put another spell in
   that slot (a new spell for instance), it will be back down to one. This does not affect
   spells a character already knows.
10.Text Editor, if you want to use DTE (Dual Tile Encoding) then you must have "Prefer DTE"
   checked. If it's not checked, DTE will not be used for saving.

As for what's next, dunno. Here's the ultimate plan:
- Enable map editing, overworld and other maps
- Enable graphics editing, of any kind.
- Enable a font editor that actually does something.
- Enable a music editor.

Other ideas go here.

/=============================================================================================\
| 5 - Unsupported FF2 ROMS								      |
\=============================================================================================/

Currently Demi's incomplete translation and the original Japanese version are the only ones not
supported by Jade. If you have Demi's incomplete translation, use an IPS patcher and update
your rom with the .IPS file included. If you are unsure about which version you have, open your
rom and click the "check version" button. If you have the Original Japanese version, you can do
the same.

/=============================================================================================\
| 6 - Contact info									      |
\=============================================================================================/

Comments, bug reports, contributions, whatever; it can all be sent to me at lenophis@yahoo.com

/=============================================================================================\
| 7 - Credits										      |
\=============================================================================================/

Big thanks go out to the following people:

Y Dienyddiwr Da: For finding and posting the the character info. That's what started the project.
Disch: Inspiration from FF Hackster, help with deciphering some data, and code supporter. Now for
 hosting Jade at Slick Productions.
Hypher: Inspiration to start working on the program, and code supporter.
Gavin: For hosting the program at Dragon Eye Studios.
SpaceTiger: For hosting the program at Zophar's Domain.
Grond: For contributing a lot of palette info, as well as some other miscellaneous data.
awj & Vagabond: For contributions of weapons, armor, spells, items, and monster AI.
Vagla: For finding the shop data, thanks a ton.
tornado4734: For finding and submitting the formation data.