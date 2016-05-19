JNesG v0.3a, by Matt Greer
matthew-greer@uiowa.edu
http://www.cs.uiowa.edu/~mgreer/nes/

About
====----
JNesG is a simple NES graphics editor written in Java. It's in the early stages 
right now, but is quite usable. It's released under the Gnu General Public License
(GPL), a copy is included in the zip file.


Requires
====----
JNesG requires a Java 2 environment. It will definitely work in Java 1.4, and very likely
work in Java 1.3. 1.2 is pushing it and 1.1 and below won't work. Future versions of JNesG
will require at least Java 1.4.

http://java.sun.com/


To run
====----
In Windows or Solaris just double click the jar (JNesG_0.3a.jar). It will start right up.
For other operating systems, you need to enter this on the command line

java -jar JNesG_0.3a.jar

in the same directory as JNesG. 


Documentation
====----
Documentation is provided in docs.html, in the zip file. It's pretty easy to figure out
though I think.

Important note
===----
Just to stress, when you decide to export your graphics into an existing iNES rom,
JNesG always makes a copy of the rom. The original won't get touched, so export away.

Bugs
====----
There's surely bugs at this point. I've tested it out pretty well, but can't
possibly have found everything. If you find something please let me know.

Unimplemented stuff
====----
Some things have a button or whatever in the program but don't actually do 
anthing yet. Mostly minor stuff. I just need to take a little break from
this program for a bit but want to get some feedback on it, so it's going out
like this.

Mirror across all palettes --- doesn't do anything, when implemented will
tie the mirror value in the current palette to all palettes.

Reset (button on main toolbar and in main menu) -- when implemented will 
drop everything down to just one and clear it out, as if you had just opened
the program.

ascii exporting -- in the exporter, is an option to export to ascii. What this
will do is allow you to export your palette into a text file as say 

--------
; palette0 exported from JNesG
.byte $0A, $02, $10 ; etc
--------

Not all that important, but I'll get it in there eventually. Exporting to
binary works just fine.


Future features
====----
Features planned for future versions of JNesG

-all the unimplemented stuff above

-importing from images. JNesG will take an image file and create a nametable and tiles
and palettes from it as best it can. For low color images this should work quite well.

-Attribute table support

-automatic generation of font/text tiles from fonts installed on the system.

-other stuff...








