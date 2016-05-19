'$STATIC
OPTION BASE 0
'Declare all subs and functions
DEFINT A-Z
DECLARE SUB EditMusic ()
DECLARE SUB EditContents ()
DECLARE SUB MoveSpecial ()
DECLARE SUB SetRomSpecials ()
DECLARE SUB SpecRefresh ()
DECLARE SUB SpecRedraw ()
DECLARE SUB EditSpecials ()
DECLARE FUNCTION Strim$ (t%)
DECLARE SUB EdRedraw ()
DECLARE SUB EdRefresh ()
DECLARE SUB GetRomSpecials ()
DECLARE SUB ovLDivert (y%)
DECLARE SUB ovdivert ()
DECLARE SUB ovsmovecursor (xc%, yc%)
DECLARE SUB ovSRefresh ()
DECLARE SUB ovdrawmap ()
DECLARE SUB ovdrawtile (x%, y%)
DECLARE SUB ovlKonvert (y%)
DECLARE SUB ovkonvert (y1%, y2%)
DECLARE SUB ovSuperEdit ()
DECLARE SUB ovSpecial (x AS INTEGER, y AS INTEGER, text$)
DECLARE SUB ovrefresh ()
DECLARE SUB ovGetO ()
DECLARE SUB ovedit ()
DECLARE SUB ovGetX ()
DECLARE SUB ovLConvert (row%)
DECLARE SUB ovconvert (y1%, y2%)
DECLARE SUB drawspecial (x AS INTEGER, y AS INTEGER)
DECLARE SUB RemapTile (t AS INTEGER)
DECLARE SUB changepage (funct%)
DECLARE SUB Warp ()
DECLARE SUB SecurityCheck ()
DECLARE SUB specials (t%)
DECLARE SUB TownFinder ()
DECLARE SUB GetSpecials ()
DECLARE SUB SaveFile ()
DECLARE SUB Editor ()
DECLARE SUB LoadTileSet ()
DECLARE SUB LoadFile ()
DECLARE SUB divert (x1%, y1%)
DECLARE SUB SetTown (t%)
DECLARE SUB gettown (t%)
DECLARE SUB SetPalette ()
DECLARE SUB drawtile (x%, y%)
DECLARE SUB drawmap (x1%, y1%)
DECLARE SUB pause ()
DECLARE SUB convert (x1%, y1%)
DECLARE FUNCTION getmass% (y%)
DECLARE FUNCTION Trim$ (t$)
DECLARE FUNCTION TrimStr$ (t%)
DECLARE FUNCTION YesOrNo% ()
DECLARE FUNCTION prompt$ (pmt AS STRING, ext AS STRING, dft AS STRING)

palet: 'Palette Data
DATA 00,00,00
DATA 50,08,00
DATA 00,32,00
DATA 63,36,13
DATA 46,62,06
DATA 31,31,32
DATA 00,18,63
DATA 63,56,42
DATA 47,47,50
DATA 63,63,63

'Define from ROM specials
DIM SHARED treasure(30, 3) AS INTEGER, stairs(1 TO 2, 50, 2) AS INTEGER

'Define Map data Storage
DIM SHARED ovstring  AS STRING * 2320
DIM SHARED mapstring  AS STRING * 4738 '4708
DIM SHARED map(119, 119)  AS INTEGER
'Define Overworld Editor Varables
DIM SHARED offset(-1 TO 120) AS INTEGER
DIM SHARED orow AS INTEGER
DIM SHARED xbyte AS INTEGER
DIM SHARED obyte AS INTEGER
DIM SHARED oterrain AS INTEGER
DIM SHARED otype AS INTEGER
DIM SHARED olen AS INTEGER
DIM SHARED arow AS INTEGER
DIM SHARED acol AS INTEGER

'Define Misc Things
DIM SHARED chirp$, teleport$
DIM SHARED twemp AS INTEGER, filename AS STRING

DIM SHARED maptile(1470) AS INTEGER

DIM SHARED edge(2) AS INTEGER
DIM SHARED special(119, 119) AS INTEGER
DIM SHARED buffer AS INTEGER, tile AS INTEGER
DIM SHARED rooftile AS INTEGER, roof(29, 29) AS INTEGER
DIM SHARED page AS INTEGER, flags AS INTEGER, temp AS INTEGER, ffile AS INTEGER
DIM SHARED csrx AS INTEGER, csry AS INTEGER
DIM SHARED cmd$
DIM SHARED dq AS INTEGER
DIM SHARED cx, cy
DIM SHARED drawmode AS INTEGER

'More Vars
DIM SHARED pag AS INTEGER
DIM SHARED editmode AS INTEGER
DIM SHARED cur AS INTEGER
DIM SHARED ctres AS INTEGER
DIM SHARED cstar AS INTEGER
DIM SHARED content AS INTEGER

CLEAR , , 200   'Low stack for finding bugs!

'NOTE! If you get an "Advanced feature unavailable" Error, add a comment (')
'to the beginning of the next line.
cmd$ = COMMAND$

'Comment (') the following lines to disable sound
chirp$ = "MBMLt255l64o3eo3c"
teleport$ = "t255mlMBl64o1"
teleport$ = teleport$ + "cc+dd+eff+gg+aa+b>"
teleport$ = teleport$ + "cc+dd+eff+gg+aa+b>"
teleport$ = teleport$ + "ccc<gedc<gedc<gc"


'Display Version Number and generate blank space
PRINT
twemp = CSRLIN
LOCATE twemp, 1
PRINT SPACE$(80);
LOCATE twemp, 1
PRINT "DW/DQ Town Editor, Version 3.1, 10/19/1999"

LoadFile        'Load the file

SCREEN 12       'Set VGA Video Mode  640x480x16

LoadTileSet     'Load Graphics

SetPalette      'Get Palette4

GetRomSpecials  'Obtain Stairs locations and chest locations

page = 5        'Default page is throne room
Editor          'Start the editor

SYSTEM          'Exit QBASIC if /RUN param is used

SUB changepage (funct)  'Since the maps are not in logical order,
                        'this sub arranges them with page up/down
IF funct = 1 THEN       'Page down
  SELECT CASE page
    CASE 0: page = 1
    CASE 1: page = 5
    CASE 5: page = 4
    CASE 4: page = 8
    CASE 8: page = 9
    CASE 9: page = 7
    CASE 7: page = 11
    CASE 11: page = 3
    CASE 3: page = 10
    CASE 10: page = 2
    CASE 2: page = 15
    CASE 15: page = 16
    CASE 16: page = 17
    CASE 17: page = 18
    CASE 18: page = 19
    CASE 19: page = 20
    CASE 20: page = 6
    CASE 6: page = 12
    CASE 12: page = 13
    CASE 13: page = 14
    CASE 14: page = 21
    CASE 21: page = 22
    CASE 22: page = 23
    CASE 23: page = 24
    CASE 24: page = 25
    CASE 25: page = 26
    CASE 26: page = 27
    CASE 27: page = 28
    CASE 28: page = 29
    CASE 29: page = 1
  END SELECT

ELSEIF funct = 0 THEN   'Page up

  SELECT CASE page
    CASE 0: page = 29
    CASE 1: page = 29
    CASE 5: page = 1
    CASE 4: page = 5
    CASE 8: page = 4
    CASE 9: page = 8
    CASE 7: page = 9
    CASE 11: page = 7
    CASE 3: page = 11
    CASE 10: page = 3
    CASE 2: page = 10
    CASE 15: page = 2
    CASE 16: page = 15
    CASE 17: page = 16
    CASE 18: page = 17
    CASE 19: page = 18
    CASE 20: page = 19
    CASE 6: page = 20
    CASE 12: page = 6
    CASE 13: page = 12
    CASE 14: page = 13
    CASE 21: page = 14
    CASE 22: page = 21
    CASE 23: page = 22
    CASE 24: page = 23
    CASE 25: page = 24
    CASE 26: page = 25
    CASE 27: page = 26
    CASE 28: page = 27
    CASE 29: page = 28
  END SELECT

END IF

END SUB

'This subprogram writes tile numbers into the array "map"
SUB convert (x1, y1)

'The Following code generates a bunch of temporary variables.
DIM x AS INTEGER
DIM y AS INTEGER
DIM w1 AS INTEGER
DIM w2 AS INTEGER
DIM take2 AS INTEGER

'The next piece of code writes to the array.
FOR y = 0 TO y1
FOR x = 1 TO x1 STEP 2

take2 = ASC(MID$(mapstring, tile, 1))
w1 = take2 \ 16
w2 = take2 MOD 16

map(x - 1, y) = w1
map(x, y) = w2
tile = tile + 1

NEXT
NEXT

IF flags = 4 THEN


FOR y = 0 TO y1
  FOR x = 1 TO x1 STEP 2

    take2 = ASC(MID$(mapstring, rooftile, 1))
    w1 = take2 \ 16
    w2 = take2 MOD 16

    roof(x - 1, y) = w1
    roof(x, y) = w2
    rooftile = rooftile + 1

  NEXT
NEXT

END IF

END SUB

SUB divert (x1, y1)
'This sub takes the map array and places it back into the Mapstring

DIM x AS INTEGER, y AS INTEGER     'Declare Temporary Varables
DIM w1 AS INTEGER, w2 AS INTEGER

FOR y = 0 TO y1
FOR x = 1 TO x1 STEP 2

w1 = map(x - 1, y)
w2 = map(x, y)

MID$(mapstring, tile, 1) = CHR$(w1 * 16 + w2)
tile = tile + 1

NEXT
NEXT

IF flags = 4 THEN

FOR y = 0 TO y1
FOR x = 1 TO x1 STEP 2

w1 = roof(x - 1, y)
w2 = roof(x, y)

MID$(mapstring, rooftile, 1) = CHR$(w1 * 16 + w2)
rooftile = rooftile + 1

NEXT

NEXT
END IF
END SUB

SUB drawmap (x1, y1)

LINE (483, 0)-(483, 479), 15

FOR y = 0 TO y1
FOR x = 0 TO x1

  drawtile x, y

NEXT
NEXT

END SUB

SUB drawspecial (x AS INTEGER, y AS INTEGER)
DIM x1, y1, x2, y2  'Coordinates of box
DIM c, z            'c= Color, z=Special

IF flags = 5 THEN   'If on overworld
  x1 = x * 4        'Calculate Coordinates
  y1 = y * 4        '...
  x2 = x1 + 3       '..
  y2 = y1 + 3       '.
  z = special(x, y) 'Get Special
  c = z             'Set color from special
  IF z > 15 THEN c = 5 'If stairs, then green
  LINE (x1, y1)-(x2, y2), c, B   'draw box...
  EXIT SUB                       'And leave
END IF

x1 = x * 16    'Calculate Coords....
y1 = y * 16    '...
x2 = x1 + 15   '..
y2 = y1 + 15   '.

z = special(x, y)   'Get Special

IF z < 16 THEN
  c = z
  l = 0
END IF

IF z > 64 AND z < 128 THEN
c = 5
IF z > 90 THEN z = z + 6
l = 1
END IF

IF z > 128 AND z < 255 THEN
c = 5
z = z - 64
IF z > 90 THEN z = z + 6
l = 2
END IF

LINE (x1, y1)-(x2, y2), c, B
LINE (x1 + 1, y1 + 1)-(x2 - 1, y2 - 1), c, B

IF l > 0 THEN

LOCATE y + 1, x * 2 + l: PRINT CHR$(z);

LINE (x1, y1)-(x2, y1), c, B
LINE (x1, y1 + 1)-(x2, y1 + 1), c, B

LINE (x1, y2)-(x2, y2), c, B
LINE (x1, y2 - 1)-(x2, y2 - 1), c, B

END IF

END SUB

SUB drawtile (x, y)

IF flags = 5 THEN  'If "overworld" mode, then use another sub.
  ovdrawtile x, y
  EXIT SUB
END IF

DIM t AS INTEGER, g AS INTEGER

IF x = -1 THEN   'If drawing Current Tile, then use this small code.
  t = buffer
  IF flags > 0 AND flags < 4 THEN RemapTile t
  PUT (624, 304), maptile(t * 67 + 1), PSET
  EXIT SUB
END IF

DIM x1 AS INTEGER, y1 AS INTEGER
DIM x2 AS INTEGER, y2 AS INTEGER
DIM c AS INTEGER, z AS INTEGER

t = map(x, y)       'Get Tile from map
IF flags > 0 AND flags < 4 THEN RemapTile t  'Change tilesets sets if necessary

g = t * 67
g = g + 1

x1 = x * 16
y1 = y * 16
x2 = x1 + 15
y2 = y1 + 15

SELECT CASE t
  CASE 0 TO 17: PUT (x1, y1), maptile(g), PSET
  CASE 19: LINE (x1, y1)-(x1 + 15, y1 + 15), 0, BF
  CASE 18: PUT (x1, y1), maptile(g), OR
END SELECT

IF flags = 4 THEN                 'Draw Black Checkered box
  IF (roof(x, y) \ 8 = 1) THEN
    FOR y2 = y1 + 1 TO y1 + 15 STEP 2
      FOR x2 = x1 TO x1 + 15 STEP 2
        PSET (x2, y2), 0
        PSET (x2 + 1, y2 - 1), 0
      NEXT
    NEXT
    PUT (x1, y1), maptile(18 * 67 + 1), OR
  END IF
END IF

z = special(x, y)

IF z > 0 THEN drawspecial x, y
END SUB

SUB EditContents

LINE (488, 48)-(639, 479), 0, BF

LOCATE 4, 62: PRINT ": Change Contents"
LOCATE 5, 62: PRINT "Enter: Finished"
LOCATE 6, 62: PRINT "ESC: Cancel"

DO

  SpecRefresh

a$ = ""
WHILE a$ = ""
a$ = INKEY$
WEND

SELECT CASE UCASE$(a$)
  CASE CHR$(0) + "H"
    content = content - 1
    IF content = -1 THEN content = &H17

  CASE CHR$(0) + "P"
    content = content + 1
    IF content > &H17 THEN content = 0
  
  CASE CHR$(27)
    content = cx
    SpecRefresh
    EXIT SUB

  CASE CHR$(13)
    EXIT SUB

END SELECT

LOOP

END SUB

SUB EditMusic
DIM f AS INTEGER
DIM mus AS INTEGER
DIM getbyte AS STRING * 1
DIM musi$

f = FREEFILE

OPEN filename FOR BINARY AS #f
  IF dq = 0 THEN GET f, &H31BF + page, getbyte
  IF dq = 1 THEN GET f, &H33C2 + page, getbyte
CLOSE

mus = ASC(getbyte)

LINE (488, 48)-(639, 479), 0, BF

LOCATE 4, 62: PRINT ": Change Song"
LOCATE 5, 62: PRINT "Pg : Inc/Dec 10"
LOCATE 6, 62: PRINT "Enter: Finished"
LOCATE 7, 62: PRINT "ESC: Cancel"
LOCATE 13, 62: PRINT "Music Editor"

DO

  LOCATE 14, 62: PRINT "Song "; Strim$(mus); "/255  "
  LOCATE 15, 62: PRINT HEX$(mus); "-"; "                "
  LOCATE 15, 65
  SELECT CASE mus
    CASE 0: PRINT "No music"
    CASE 1: PRINT "Title Fanfare"
    CASE 2: PRINT "Throne Room"
    CASE 3: PRINT "Castle Theme"
    CASE 4: PRINT "Town Theme"
    CASE 5: PRINT "Overworld Tune"
    CASE 6: PRINT "Cave 1"
    CASE 7: PRINT "Cave 2"
    CASE 8: PRINT "Cave 3"
    CASE 9: PRINT "Cave 4"
    CASE 10: PRINT "Cave 5"
    CASE 11: PRINT "Cave 6"
    CASE 12: PRINT "Cave 7"
    CASE 13: PRINT "Cave 8"
    CASE 14: PRINT "Battle Music"
    CASE 15: PRINT "Dragonlord"
    CASE 16: PRINT "Ending Song"
    CASE 17: PRINT "Silver Harp"
    CASE 18: PRINT "Fary Flut"
    CASE 19: PRINT "Rainbow Drop"
    CASE 20: PRINT "Thou art dead"
    CASE 21: PRINT "Inn"
    CASE 22: PRINT "Princess Gwaelin"
    CASE 23: PRINT "Curse"
    CASE 24: PRINT "Battle w/o intro"
    CASE 25: PRINT "Win Battle"
    CASE 26: PRINT "Level Up"
    CASE ELSE: PRINT "Sound Effect"
  END SELECT

a$ = ""
WHILE a$ = ""
a$ = INKEY$
WEND

SELECT CASE UCASE$(a$)
  CASE CHR$(0) + "H"
    mus = mus - 1
    IF mus < 0 THEN mus = 255

  CASE CHR$(0) + "P"
    mus = mus + 1
    IF mus > 255 THEN mus = 0
 
  CASE CHR$(0) + "I"
    mus = mus - 16
    IF mus < 0 THEN mus = mus + 256

  CASE CHR$(0) + "Q"
    mus = mus + 16
    IF mus > 255 THEN mus = mus - 256
 
  CASE CHR$(27)
    LINE (488, 48)-(639, 479), 0, BF
    EXIT SUB

  CASE CHR$(13)
    EXIT DO

END SELECT

LOOP

LOCATE 24, 62: PRINT "Music="; HEX$(mus)
getbyte = CHR$(mus)
OPEN filename FOR BINARY AS #f
  IF dq = 0 THEN PUT f, &H31BF + page, getbyte
  IF dq = 1 THEN PUT f, &H33C2 + page, getbyte
CLOSE

LINE (488, 48)-(639, 479), 0, BF

END SUB

SUB Editor

csrx = 0
csry = 0
gettown page
buffer = 0

Redraw:

EdRedraw

DO
a$ = ""
WHILE a$ = ""
a$ = INKEY$
WEND

a$ = UCASE$(a$)
SELECT CASE a$
  CASE CHR$(9)
    drawmode = NOT drawmode
    IF drawmode THEN
    map(csrx, csry) = buffer
    drawtile csrx, csry
    END IF
    IF drawmode = 0 THEN
      drawtile csrx, csry
      LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 15, B
    END IF
  CASE "C"
    IF flags = 4 THEN
      roof(csrx, csry) = (roof(csrx, csry) + 8) MOD 16
      drawtile csrx, csry
    ELSE
      PLAY chirp$
    END IF
  CASE "N": SetTown page
    SaveFile
    SHELL "NESticle " + filename$
    SCREEN 0: SCREEN 12
    LoadTileSet
    SetPalette
    gettown page
    EdRedraw
  CASE "S": SetTown page
    SaveFile
  CASE "R": gettown page
  CASE "W": Warp: EdRedraw
  CASE CHR$(0) + "I"
    changepage (0)
    IF page < 1 THEN page = 32
    CLS : gettown page
    IF csrx > edge(0) THEN csrx = edge(0)
    IF csry > edge(1) THEN csry = edge(1)
    IF flags = 1 OR flags = 2 THEN
      IF map(csrx, csry) > 7 AND buffer < 8 THEN buffer = buffer + 8
      IF map(csrx, csry) < 8 AND buffer > 7 THEN buffer = buffer - 8
    END IF
    IF flags = 3 THEN buffer = (map(csrx, csry) + 8) MOD 16
    EdRedraw
  CASE CHR$(0) + "Q"
    changepage (1)
    IF page > 32 THEN page = 1
    CLS : gettown page
    IF csrx > edge(0) THEN csrx = edge(0)
    IF csry > edge(1) THEN csry = edge(1)
    IF flags = 1 OR flags = 2 THEN
      IF map(csrx, csry) > 7 AND buffer < 8 THEN buffer = buffer + 8
      IF map(csrx, csry) < 8 AND buffer > 7 THEN buffer = buffer - 8
    END IF
    IF flags = 3 THEN buffer = (map(csrx, csry) + 8) MOD 16
    EdRedraw
  CASE CHR$(0) + "H"
    drawtile csrx, csry
    csry = csry - 1
    IF csry < 0 THEN csry = edge(1)
    IF flags = 1 OR flags = 2 THEN
      IF map(csrx, csry) > 7 AND buffer < 8 THEN buffer = buffer + 8
      IF map(csrx, csry) < 8 AND buffer > 7 THEN buffer = buffer - 8
    END IF
    IF drawmode THEN
    map(csrx, csry) = buffer
    drawtile csrx, csry
    END IF
'    IF flags = 3 THEN buffer = (map(csrx, csry) + 8) MOD 16
    
  CASE CHR$(0) + "P"
    drawtile csrx, csry
    csry = csry + 1
    IF csry > edge(1) THEN csry = 0
    IF flags = 1 OR flags = 2 THEN
      IF map(csrx, csry) > 7 AND buffer < 8 THEN buffer = buffer + 8
      IF map(csrx, csry) < 8 AND buffer > 7 THEN buffer = buffer - 8
    END IF
    IF drawmode THEN
    map(csrx, csry) = buffer
    drawtile csrx, csry
    END IF
'    IF flags = 3 THEN buffer = (map(csrx, csry) + 8) MOD 16
    
  CASE CHR$(0) + "K"
    drawtile csrx, csry
    csrx = csrx - 1
    IF csrx < 0 THEN csrx = edge(0)
    IF flags = 1 OR flags = 2 THEN
      IF map(csrx, csry) > 7 AND buffer < 8 THEN buffer = buffer + 8
      IF map(csrx, csry) < 8 AND buffer > 7 THEN buffer = buffer - 8
    END IF
    IF drawmode THEN
    map(csrx, csry) = buffer
    drawtile csrx, csry
    END IF
    'IF flags = 3 THEN buffer = (map(csrx, csry) + 8) MOD 16
    
  CASE CHR$(0) + "M"
    drawtile csrx, csry
    csrx = csrx + 1
    IF csrx > edge(0) THEN csrx = 0
    IF flags = 1 OR flags = 2 THEN
      IF map(csrx, csry) > 7 AND buffer < 8 THEN buffer = buffer + 8
      IF map(csrx, csry) < 8 AND buffer > 7 THEN buffer = buffer - 8
    END IF
    IF drawmode THEN
    map(csrx, csry) = buffer
    drawtile csrx, csry
    END IF
    'IF flags = 3 THEN buffer = (map(csrx, csry) + 8) MOD 16
    
  CASE "+", "="
    buffer = buffer + 1
    IF flags = 1 OR flags = 2 THEN
      IF buffer = 8 THEN buffer = 0
      IF buffer = 16 THEN buffer = 8
    ELSEIF flags = 3 THEN buffer = buffer - 1
    ELSE
      IF buffer = 16 THEN buffer = 0
    END IF
    drawtile -1, -1
    IF drawmode THEN
    map(csrx, csry) = buffer
    drawtile csrx, csry
    END IF
    
  CASE "-"
    buffer = buffer - 1
    IF flags = 1 OR flags = 2 THEN
      IF buffer = 7 THEN buffer = 15
      IF buffer = -1 THEN buffer = 7
    ELSEIF flags = 3 THEN buffer = buffer + 1
    ELSE
      IF buffer < 0 THEN buffer = 15
    END IF
    drawtile -1, -1
    IF drawmode THEN
    map(csrx, csry) = buffer
    drawtile csrx, csry
    END IF
    
  CASE CHR$(13)
    IF flags <> 3 THEN buffer = map(csrx, csry)
    drawtile -1, -1
    
  CASE " "
    map(csrx, csry) = buffer
    drawtile csrx, csry
    IF flags = 3 THEN buffer = (map(csrx, csry) + 8) MOD 16
  CASE "L"
    CLS
    LoadFile
    CLS
    gettown page
    EdRedraw
  CASE "D"
    SCREEN 0: SLEEP 1: SCREEN 12
    LoadTileSet
    SetPalette
    gettown page
    EdRedraw
  CASE "O"
    CLS
    flags = 5
    specials 1
    ovedit
    CLS
    gettown page
    EdRedraw
  CASE "P"
    oldpage = page
    CLS : INPUT "Page"; page
    IF page < 0 OR page > 28 THEN
      IF page = 0 THEN
        PRINT "Page 0 is all grass!"
        pause
        page = 0
        gettown page
        EdRedraw
      ELSE
        PRINT "Invalid Page!"
      END IF
      page = oldpage
      z$ = INPUT$(1)
    END IF
    CLS : gettown page
    IF csrx > edge(0) THEN csrx = edge(0)
    IF csry > edge(1) THEN csry = edge(1)
    IF flags = 1 OR flags = 2 THEN
      IF map(csrx, csry) > 7 AND buffer < 8 THEN buffer = buffer + 8
      IF map(csrx, csry) < 8 AND buffer > 7 THEN buffer = buffer - 8
    END IF
    EdRedraw
  CASE "T"
    oldpage = page
    EditSpecials
    GetRomSpecials
    gettown page
    EdRedraw
  CASE "M"
    EditMusic
    EdRedraw
END SELECT

EdRefresh
IF flags = 5 THEN
  ovSuperEdit
  IF page = 1 THEN page = 5
  gettown page

  IF csrx > edge(0) THEN csrx = edge(0)
  IF csry > edge(1) THEN csry = edge(1)

  GOTO Redraw
END IF

LOOP UNTIL a$ = CHR$(27)

EXIT SUB


ov:



END SUB

SUB EditSpecials

CLS

IF editmode = 0 THEN
  pag = treasure(ctres, 0)
  page = pag
  CLS
  gettown page
  csrx = treasure(ctres, 1)
  csry = treasure(ctres, 2)
  content = treasure(ctres, 3)
END IF
IF editmode > 0 THEN
  pag = stairs(editmode, cstar, 0)
  page = pag
  CLS
  gettown page
  csrx = stairs(editmode, cstar, 1)
  csry = stairs(editmode, cstar, 2)
END IF
SpecRedraw
  IF flags <> 5 THEN
    LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
    LINE (csrx * 16 + 1, csry * 16 + 1)-(csrx * 16 + 14, csry * 16 + 14), 2, B
  ELSE
    LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 2, B
  END IF


DO
  a$ = "": DO: a$ = INKEY$: LOOP WHILE a$ = ""
  SELECT CASE UCASE$(a$)
    CASE CHR$(0) + "H"
      drawtile csrx, csry
      IF editmode = 0 THEN
        ctres = ctres - 1
        IF ctres < 0 THEN ctres = 30
        pag = treasure(ctres, 0)
        IF pag <> page THEN
          page = pag
          CLS
          gettown page
        END IF
        csrx = treasure(ctres, 1)
        csry = treasure(ctres, 2)
        content = treasure(ctres, 3)
        SpecRedraw
      END IF
      IF editmode > 0 THEN
        cstar = cstar - 1
        IF cstar < 0 THEN cstar = 50
        pag = stairs(editmode, cstar, 0)
        IF pag <> page THEN
          page = pag
          CLS
          gettown page
        END IF
        csrx = stairs(editmode, cstar, 1)
        csry = stairs(editmode, cstar, 2)
        SpecRedraw
      END IF
      IF flags <> 5 THEN
        LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
        LINE (csrx * 16 + 1, csry * 16 + 1)-(csrx * 16 + 14, csry * 16 + 14), 2, B
      ELSE
        LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 2, B
      END IF

    CASE CHR$(0) + "P"
      drawtile csrx, csry
      IF editmode = 0 THEN
        ctres = ctres + 1
        IF ctres > 30 THEN ctres = 0
        pag = treasure(ctres, 0)
        IF pag <> page THEN
          page = pag
          CLS
          gettown page
        END IF
        csrx = treasure(ctres, 1)
        csry = treasure(ctres, 2)
        content = treasure(ctres, 3)
        SpecRedraw
      END IF
      IF editmode > 0 THEN
        cstar = cstar + 1
        IF cstar > 50 THEN cstar = 0
        pag = stairs(editmode, cstar, 0)
        IF pag <> page THEN
          page = pag
          CLS
          gettown page
        END IF
        csrx = stairs(editmode, cstar, 1)
        csry = stairs(editmode, cstar, 2)
        SpecRedraw
      END IF
      IF flags <> 5 THEN
        LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
        LINE (csrx * 16 + 1, csry * 16 + 1)-(csrx * 16 + 14, csry * 16 + 14), 2, B
      ELSE
        LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 2, B
      END IF
    CASE CHR$(0) + "K"
      editmode = editmode - 1
      IF editmode = -1 THEN editmode = 2
      IF editmode = 0 THEN
        pag = treasure(ctres, 0)
        page = pag
        CLS
        gettown page
        csrx = treasure(ctres, 1)
        csry = treasure(ctres, 2)
        content = treasure(ctres, 3)
        SpecRedraw
      END IF
      IF editmode > 0 THEN
        pag = stairs(editmode, cstar, 0)
        page = pag
        CLS
        gettown page
        csrx = stairs(editmode, cstar, 1)
        csry = stairs(editmode, cstar, 2)
        SpecRedraw
      END IF
        IF flags <> 5 THEN
          LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
          LINE (csrx * 16 + 1, csry * 16 + 1)-(csrx * 16 + 14, csry * 16 + 14), 2, B
        ELSE
          LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 2, B
        END IF
    CASE CHR$(0) + "M"
      editmode = editmode + 1
      IF editmode = 3 THEN editmode = 0
      IF editmode = 0 THEN
        pag = treasure(ctres, 0)
        page = pag
        CLS
        gettown page
        csrx = treasure(ctres, 1)
        csry = treasure(ctres, 2)
        content = treasure(ctres, 3)
        SpecRedraw
      END IF
      IF editmode > 0 THEN
        pag = stairs(editmode, cstar, 0)
        page = pag
        CLS
        gettown page
        csrx = stairs(editmode, cstar, 1)
        csry = stairs(editmode, cstar, 2)
        SpecRedraw
      END IF
        IF flags <> 5 THEN
          LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
          LINE (csrx * 16 + 1, csry * 16 + 1)-(csrx * 16 + 14, csry * 16 + 14), 2, B
        ELSE
          LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 2, B
        END IF
    CASE "S"
      SetRomSpecials
    CASE CHR$(0) + "I"
      changepage (0)
      IF editmode = 0 THEN treasure(ctres, 0) = page
      IF editmode > 0 THEN stairs(editmode, cstar, 0) = page
      CLS : gettown page
        SpecRedraw
        IF flags <> 5 THEN
          LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
          LINE (csrx * 16 + 1, csry * 16 + 1)-(csrx * 16 + 14, csry * 16 + 14), 2, B
        ELSE
          LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 2, B
        END IF
    CASE CHR$(0) + "Q"
      changepage (1)
      IF editmode = 0 THEN treasure(ctres, 0) = page
      IF editmode > 0 THEN stairs(editmode, cstar, 0) = page
      CLS : gettown page
        SpecRedraw
        IF flags <> 5 THEN
          LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
          LINE (csrx * 16 + 1, csry * 16 + 1)-(csrx * 16 + 14, csry * 16 + 14), 2, B
        ELSE
          LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 2, B
        END IF
    CASE CHR$(13)
      cx = csrx
      cy = csry
      MoveSpecial
        IF editmode = 0 THEN
          treasure(ctres, 1) = csrx
          treasure(ctres, 2) = csry
        END IF
        IF editmode > 0 THEN
          stairs(editmode, cstar, 1) = csrx
          stairs(editmode, cstar, 2) = csry
        END IF
      CLS : gettown page
        SpecRedraw
        IF flags <> 5 THEN
          LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
          LINE (csrx * 16 + 1, csry * 16 + 1)-(csrx * 16 + 14, csry * 16 + 14), 2, B
        ELSE
          LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 2, B
        END IF
    CASE "Z"
      IF editmode > 0 THEN
        PLAY chirp$
      ELSE
        cx = content
        EditContents
        LINE (488, 43)-(639, 479), 0, BF
        SpecRedraw
        treasure(ctres, 3) = content
      END IF
  END SELECT


LOOP UNTIL a$ = CHR$(27)

LINE (488, 0)-(639, 479), 0, BF
LOCATE 1, 62: PRINT "Save First?"
LOCATE 2, 62: PRINT "Y/N"
IF YesOrNo = 1 THEN SetRomSpecials

GetRomSpecials








CLS
END SUB

SUB EdRedraw
LOCATE 3, 62: PRINT "Keys:              ";
LOCATE 4, 62: PRINT "Pgup/dn: Change Map";
LOCATE 5, 62: PRINT CHR$(27) + "" + "" + CHR$(26) + ": Move Box    ";
LOCATE 6, 62: PRINT "+/-: Change Tile   ";
LOCATE 7, 62: PRINT "S: Save Data       ";
LOCATE 8, 62: PRINT "R: Revert          ";
LOCATE 9, 62: PRINT "L: Load new file   ";
LOCATE 10, 62: PRINT "ESC: Quit Program  ";
LOCATE 11, 62: PRINT "Enter: Get Tile    "
LOCATE 12, 62: PRINT "SPACE: Draw        ";
LOCATE 13, 62: PRINT "N: Run Nesticle";
LOCATE 14, 62: PRINT "W: Warp";
LOCATE 15, 62: PRINT "C: Toggle Roof";
LOCATE 16, 62: PRINT "TAB: ToggleDrawMode";
LOCATE 17, 62: PRINT "O: Edit Overworld";
LOCATE 18, 62: PRINT "T: Edit Specials"

LOCATE 23, 62: PRINT "P: Change Page"
LOCATE 24, 62: PRINT "M: Change Music"

LOCATE 26, 62: PRINT "Specials:";
LOCATE 27, 62: PRINT "Orange=Treasure   4"; '4
LOCATE 28, 62: PRINT "Blue=Entity       7"; '7
LOCATE 29, 62: PRINT "Gray=Searchable   9"; '9
LOCATE 30, 62: PRINT "Green=Stairs      5"; '5

EdRefresh
END SUB

SUB EdRefresh
  IF flags <> 5 THEN
    LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 15, B
    IF drawmode THEN LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 2, B
  ELSE
    LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 15, B
  END IF
  LOCATE 20, 62: PRINT "Paint With:"
  LOCATE 20, 76: PRINT Strim$(buffer); " "
  drawtile -1, -1
  LOCATE 21, 62: PRINT "Page="; Strim$(page)
  LOCATE 21, 70: PRINT "X,Y="; Strim$(csrx); ","; Strim$(csry); "  "
END SUB

FUNCTION getmass (y)

IF y > 119 THEN EXIT FUNCTION
buffa = -1
DO
IF map(x, y) = buffa THEN rep = rep + 1
IF rep = 16 OR map(x, y) <> buffa THEN
  buffa = map(x, y)
  masses = masses + 1
  rep = 0
END IF
x = x + 1
LOOP UNTIL x = 120

getmass = masses

END FUNCTION

SUB GetRomSpecials

DIM getblock AS STRING
DIM start AS LONG

ffile = FREEFILE
 
  getblock = SPACE$(124)
  OPEN filename FOR BINARY AS #ffile
 
  start = 24029
  IF dq = 1 THEN start = 61598
 
  GET #ffile, start + 1, getblock
  CLOSE
  FOR t = 0 TO 30
    treasure(t, 0) = ASC(MID$(getblock, t * 4 + 1, 1))
    treasure(t, 1) = ASC(MID$(getblock, t * 4 + 2, 1))
    treasure(t, 2) = ASC(MID$(getblock, t * 4 + 3, 1))
    treasure(t, 3) = ASC(MID$(getblock, t * 4 + 4, 1))
  NEXT
 
  getblock = SPACE$(153)
  OPEN filename FOR BINARY AS #ffile
 
  start = 62424
  IF dq = 1 THEN start = 61722
 
  GET #ffile, start + 1, getblock
  CLOSE
  FOR t = 0 TO 50
    stairs(1, t, 0) = ASC(MID$(getblock, t * 3 + 1, 1))
    stairs(1, t, 1) = ASC(MID$(getblock, t * 3 + 2, 1))
    stairs(1, t, 2) = ASC(MID$(getblock, t * 3 + 3, 1))
  NEXT
  OPEN filename FOR BINARY AS #ffile
 
  start = 62577
  IF dq = 1 THEN start = 61875
 
  GET #ffile, start + 1, getblock
  CLOSE
  FOR t = 0 TO 50
    stairs(2, t, 0) = ASC(MID$(getblock, t * 3 + 1, 1))
    stairs(2, t, 1) = ASC(MID$(getblock, t * 3 + 2, 1))
    stairs(2, t, 2) = ASC(MID$(getblock, t * 3 + 3, 1))
  NEXT





END SUB

SUB gettown (t)

LOCATE 1, 62
SELECT CASE t
  CASE 0
    PRINT "Null Map!";
    edge(0) = 3: edge(1) = 3
    tile = &HB74
    flags = 0
  CASE 1
    flags = 5
    edge(0) = 119: edge(1) = 119
    f = FREEFILE
    OPEN "offset.dw" FOR BINARY AS #f
    IF LOF(f) = 0 THEN
      PRINT "The file, `offset.dw', is required for overworld editing."
      pause
      CLOSE
      page = 5
      gettown page
      EXIT SUB
    END IF
    offsett$ = SPACE$(120)
    GET #f, 1, offsett$
    CLOSE
    FOR g = 1 TO 120
    offset(g) = offset(g - 1) + ASC(MID$(offsett$, g, 1))
    NEXT
    OPEN filename$ FOR BINARY AS #f
    IF dq = 1 THEN GET #f, &HB4B, ovstring
    IF dq = 0 THEN GET #f, &H1D6E, ovstring
    CLOSE
    specials 1

    cx = csrx
    cy = csry

    CLS

LINE (488, 0)-(639, 479), 0, BF
 LOCATE 1, 62: PRINT "Alefgard  h1D6E";
 LOCATE 2, 62: PRINT "120x120, RLE";
   
    ovkonvert 0, 119
    ovdrawmap

    EXIT SUB
  CASE 2
    PRINT "Charlock Castle";
    edge(0) = 19: edge(1) = 19
    tile = &HC1
    flags = 0
  CASE 3
    PRINT "Ruins of Hauksness";
    tile = &H189
    edge(0) = 19: edge(1) = 19
    flags = 0
  CASE 4
    PRINT "Tantegel Castle";
    tile = &H251
    edge(0) = 29: edge(1) = 29
    flags = 0
  CASE 5
    PRINT "Throne Room";
    tile = &H413
    edge(0) = 9: edge(1) = 9
    flags = 0
  CASE 6
    PRINT "Dragonlord's Lair";
    tile = &H445
    edge(0) = 29: edge(1) = 29
    flags = 0
  CASE 7
    PRINT "Village of Kol";
    tile = &H607
    edge(0) = 23: edge(1) = 23
    flags = 0
  CASE 8
    PRINT "Town of Breconary";
    tile = &H727
    edge(1) = 29: edge(0) = 29
    rooftile = &HD35
    flags = 4
  CASE 9
    PRINT "Town of Garinham";
    tile = &HAAB
    edge(0) = 19: edge(1) = 19
    rooftile = &HEF7
    flags = 4
  CASE 10
    PRINT "Cantlin Castle town";
    tile = &H8E9
    edge(0) = 29: edge(1) = 29
    rooftile = &HFBF
    flags = 4
  CASE 11
    PRINT "City of Rimuldar";
    tile = &HB73
    edge(0) = 29: edge(1) = 29
    rooftile = &H1181
    flags = 4
  CASE 12
    PRINT "Shrine of Sunlight";
    tile = &HD35
    edge(0) = 9: edge(1) = 9
    flags = 1
  CASE 13
    PRINT "Shrine of Rain";
    tile = &HD67
    edge(0) = 9: edge(1) = 9
    flags = 1
  CASE 14
    PRINT "Shrine of Rainbow";
    tile = &HD99
    edge(0) = 9: edge(1) = 9
    flags = 1
  CASE 15
    PRINT "Dragonlords Cave B1";
    tile = &HDCB
    edge(0) = 19: edge(1) = 19
    flags = 2
  CASE 16
    PRINT "Dragonlords Cave B2";
    tile = &HE93
    edge(0) = 9: edge(1) = 9
    flags = 2
  CASE 17
    PRINT "Dragonlords Cave B3";
    tile = &HEC5
    edge(0) = 9: edge(1) = 9
    flags = 2
  CASE 18
    PRINT "Dragonlords Cave B4";
    tile = &HEF7
    edge(0) = 9: edge(1) = 9
    flags = 2
  CASE 19
    PRINT "Dragonlords Cave B5";
    tile = &HF29
    edge(0) = 9: edge(1) = 9
    flags = 2
  CASE 20
    PRINT "Dragonlords Cave B6";
    tile = &HF5B
    edge(0) = 9: edge(1) = 9
    flags = 2
  CASE 21
    PRINT "Passage to Rimuldar";
    tile = &HF8D
    edge(0) = 5: edge(1) = 29
    flags = 2
  CASE 22
    PRINT "Cave W of Tntgel B1";
    tile = &HFE7
    edge(0) = 13: edge(1) = 13
    flags = 2
  CASE 23
    PRINT "Cave W of Tntgel B2";
    tile = &H1049
    edge(0) = 13: edge(1) = 13
    flags = 2
  CASE 24
    PRINT "Garin's Grave B1";
    tile = &H10AB
    edge(0) = 19: edge(1) = 19
    flags = 2
  CASE 25
    PRINT "Garin's Grave B2";
    tile = &H126D
    edge(0) = 13: edge(1) = 11
    flags = 2
  CASE 26
    PRINT "Garin's Grave B3";
    tile = &H1173
    edge(0) = 19: edge(1) = 19
    flags = 2
  CASE 27
    PRINT "Garin's Grave B4";
    tile = &H123B
    edge(0) = 9: edge(1) = 9
    flags = 2
  CASE 28
    PRINT "Erdrick's Cave B1";
    tile = &H12C1
    edge(0) = 9: edge(1) = 9
    flags = 2
  CASE 29
    PRINT "Erdrick's Cave B2";
    tile = &H12F3
    edge(0) = 9: edge(1) = 9
    flags = 2
END SELECT
tile = tile - &HC0

IF rooftile > 0 THEN rooftile = rooftile - &HC0

LOCATE 2, 62
PRINT "h"; HEX$(tile + &HC0); "-h"; HEX$(tile + &HC0 + ((edge(0) + 1) * (edge(1) + 1)) / 2 - 1); ", "; Strim$(edge(0) + 1); "x"; Strim$(edge(1) + 1)
IF r <> 1 THEN
convert edge(0), edge(1)
END IF
specials t

drawmap edge(0), edge(1)
tile = tile - (edge(0) + 1) * (edge(1) + 1) / 2
rooftile = rooftile - (edge(0) + 1) * (edge(1) + 1) / 2
END SUB

SUB LoadFile

temp = CSRLIN

IF cmd$ = "" THEN
  filename = prompt$("File Name:", "NES", "DragonW1.NES")
ELSE
  filename = UCASE$(cmd$)
  IF RIGHT$(filename, 4) <> ".NES" THEN filename = filename + ".NES"
END IF

cmd$ = ""

ffile = FREEFILE

OPEN filename FOR BINARY AS #ffile

IF LOF(ffile) = 0 THEN
 
  CLOSE
 
  PRINT : PRINT : PRINT
 
  PRINT "The file, "; filename; " was not found.  Do you want to create it?"
 
  SELECT CASE YesOrNo
 
  CASE 1: KILL filename
   
    newfilename$ = filename
   
    DO
      filename = prompt$("Enter EXISTING DW file:", "NES", "DragonW1.NES")
      OPEN filename FOR BINARY AS #ffile
      IF LOF(ffile) = 0 THEN
        CLOSE : KILL filename
        PRINT : PRINT : PRINT : PRINT "That file doesn't exist."
      ELSE
        SecurityCheck
        SHELL "COPY " + filename + " " + newfilename$ + " /V /B"
        filename = newfilename$
        twemp = 1
      GET #ffile, &HC1, mapstring
      END IF
    LOOP UNTIL twemp = 1
  CASE 0: KILL filename
    LoadFile
  END SELECT
ELSE
SecurityCheck
IF dq = 0 THEN GET #ffile, &HC1, mapstring
IF dq = 1 THEN GET #ffile, &HC1 + &H1506, mapstring
  CLOSE
END IF

twemp = 0
END SUB

SUB LoadTileSet
DEF SEG = VARSEG(maptile(1))
BLOAD "dw1tiles.dw", VARPTR(maptile(1))
DEF SEG
END SUB

SUB MoveSpecial

LINE (488, 43)-(639, 479), 0, BF

LOCATE 4, 62: PRINT "Enter: Place Object"
LOCATE 5, 62: PRINT "ESC: Cancel"

DO

  IF flags <> 5 THEN
    LINE (csrx * 16, csry * 16)-(csrx * 16 + 15, csry * 16 + 15), 15, B
  ELSE
    LINE (csrx * 4, csry * 4)-(csrx * 4 + 3, csry * 4 + 3), 15, B
  END IF

  SpecRefresh

a$ = ""
WHILE a$ = ""
a$ = INKEY$
WEND

SELECT CASE UCASE$(a$)
  CASE CHR$(0) + "H"
    drawtile csrx, csry
    csry = csry - 1
    IF csry < 0 THEN csry = edge(1)
 
  CASE CHR$(0) + "P"
    drawtile csrx, csry
    csry = csry + 1
    IF csry > edge(1) THEN csry = 0
   
  CASE CHR$(0) + "K"
    drawtile csrx, csry
    csrx = csrx - 1
    IF csrx < 0 THEN csrx = edge(0)
   
  CASE CHR$(0) + "M"
    drawtile csrx, csry
    csrx = csrx + 1
    IF csrx > edge(0) THEN csrx = 0

  CASE CHR$(27)
    csrx = cx
    csry = cy
    EXIT SUB

  CASE CHR$(13)
    EXIT SUB

END SELECT

LOOP

END SUB

SUB ovconvert (y1, y2)

FOR g = y1 TO y2
ovLConvert g
NEXT

END SUB

SUB ovdivert

FOR g = 0 TO 119
ovLDivert g
NEXT

END SUB

SUB ovdrawmap

LINE (483, 0)-(483, 479), 15

FOR y = 0 TO 119
FOR x = 0 TO 119

  ovdrawtile x, y

NEXT
NEXT

END SUB

SUB ovdrawtile (x, y)
 
  IF x > -1 THEN
    t = map(x, y)
    ELSE
    t = buffer
    x = 142
    y = 49 + 4 * 2
    g = t * 10 + 1300
    PUT (x * 4, y * 4), maptile(g), PSET
    EXIT SUB
  END IF
    g = t * 10 + 1300
    PUT (x * 4, y * 4), maptile(g), PSET

z = special(x, y)
IF z > 0 THEN drawspecial x, y

END SUB

SUB ovedit

specials 1
cx = 0
cy = 0

x = 0

tile = 0
offset(-1) = tile
offset(0) = offset(-1)

f = FREEFILE

OPEN "offset.dw" FOR BINARY AS #f
IF LOF(f) = 0 THEN
  PRINT "The file, `offset.dw', is required for overworld editing."
  z$ = INPUT$(1)
  CLOSE
  EXIT SUB
END IF

offsett$ = SPACE$(120)
GET #f, 1, offsett$

CLOSE

FOR g = 1 TO 120
offset(g) = offset(g - 1) + ASC(MID$(offsett$, g, 1))
NEXT

f = FREEFILE

OPEN filename$ FOR BINARY AS #f
IF dq = 1 THEN GET #f, &HB4B, ovstring
IF dq = 0 THEN GET #f, &H1D6E, ovstring
CLOSE

ovconvert 0, 119
obyte = 0

LINE (483, 0)-(483, 479), 10
 LOCATE 1, 62: PRINT "Alefgard  h1D6E";
 LOCATE 2, 62: PRINT "120x120, 2294 Bytes";
 LOCATE 3, 62: PRINT "Keys:"
 LOCATE 4, 62: PRINT "Arrows: Move Around"
 LOCATE 5, 62: PRINT "ESC: QUIT"
 LOCATE 6, 62: PRINT "+- Change Length"
 LOCATE 7, 62: PRINT "[] Change Terrain"
 LOCATE 8, 62: PRINT "S: Save"
 LOCATE 9, 62: PRINT "P: Show Specials"
LOCATE 10, 62: PRINT "B: Byteswap"
LOCATE 11, 62: PRINT "E: Super Editor"
ovrefresh

DO
a$ = UCASE$(INKEY$)
SELECT CASE a$
CASE CHR$(27): EXIT DO

CASE CHR$(0) + "H"

ovLConvert orow
orow = orow - 1
IF orow = -1 THEN orow = 119
ovGetO

ovrefresh

CASE CHR$(0) + "P"
ovLConvert orow
orow = orow + 1
IF orow = 120 THEN orow = 0
ovGetO

ovrefresh

CASE CHR$(0) + "K"

ovLConvert orow

IF obyte <> offset(orow) THEN
obyte = obyte - 1
ovGetX
END IF

ovrefresh

CASE CHR$(0) + "M"

ovLConvert orow

IF obyte <> offset(orow + 1) - 1 THEN
obyte = obyte + 1
ovGetX
END IF

ovrefresh

CASE "-"

bits = ASC(MID$(ovstring, obyte + 1, 1))
tern = bits \ 16
olen = bits MOD 16
olen = olen - 1
IF olen = -1 THEN olen = 0
bits = tern * 16 + olen
MID$(ovstring, obyte + 1, 1) = CHR$(bits)
ovLConvert orow
ovrefresh

CASE "+"

bits = ASC(MID$(ovstring, obyte + 1, 1))
tern = bits \ 16
olen = bits MOD 16
olen = olen + 1
IF olen = 16 THEN olen = 15
bits = tern * 16 + olen
MID$(ovstring, obyte + 1, 1) = CHR$(bits)
ovLConvert orow
ovrefresh

CASE "["

bits = ASC(MID$(ovstring, obyte + 1, 1))
tern = bits \ 16
olen = bits MOD 16
tern = tern - 1
IF tern = -1 THEN tern = 0
bits = tern * 16 + olen
MID$(ovstring, obyte + 1, 1) = CHR$(bits)
ovLConvert orow

CASE "]"

bits = ASC(MID$(ovstring, obyte + 1, 1))
tern = bits \ 16
olen = bits MOD 16
tern = tern + 1
IF tern = 16 THEN tern = 15
bits = tern * 16 + olen
MID$(ovstring, obyte + 1, 1) = CHR$(bits)
ovLConvert orow

CASE "S"
f = FREEFILE
OPEN filename$ FOR BINARY AS #f
IF dq = 1 THEN PUT #f, &HB4B, ovstring
IF dq = 0 THEN PUT #f, &H1D6E, ovstring
CLOSE

CASE "P"

ovSpecial 81, 1, "Rain Shrine"
ovSpecial 2, 2, "Garinham"
ovSpecial 104, 10, "Kol"
ovSpecial 28, 12, "Erd's Cave"
ovSpecial 48, 41, "Breconray"
ovSpecial 43, 43, "Tantegel"
ovSpecial 104, 44, "Pass1"
ovSpecial 104, 49, "Pass2"
ovSpecial 48, 48, "Charlock"
ovSpecial 29, 57, "Cave"
ovSpecial 102, 72, "Rimuldar"
ovSpecial 25, 89, "Hauksness"
ovSpecial 73, 102, "Cantlin"
ovSpecial 108, 109, "Rbow"
z$ = INPUT$(1)

ovconvert 0, 119
ovrefresh

CASE "B"

t1$ = MID$(ovstring, obyte + 1, 1)
t2$ = MID$(ovstring, obyte + 2, 1)
MID$(ovstring, obyte + 1, 1) = t2$
MID$(ovstring, obyte + 2, 1) = t1$
ovLConvert orow
ovrefresh

CASE "E"

CLS

ovkonvert 0, 119
ovdrawmap

buffer = 0
 LOCATE 1, 62: PRINT "Alefgard  h1D6E";
 LOCATE 2, 62: PRINT "120x120, RLE";
 LOCATE 3, 62: PRINT "Keys:"
 LOCATE 4, 62: PRINT "Arrows: Move Around"

specials 1
ovSuperEdit

IF flags <> 5 THEN EXIT SUB
'CLS
LINE (483, 0)-(483, 479), 10
 LOCATE 1, 62: PRINT "Alefgard  h1D6E";
 LOCATE 2, 62: PRINT "120x120, 2294 Bytes";
 LOCATE 3, 62: PRINT "Keys:"
 LOCATE 4, 62: PRINT "Arrows: Move Around"
 LOCATE 5, 62: PRINT "ESC: QUIT"
 LOCATE 6, 62: PRINT "+- Change Length"
 LOCATE 7, 62: PRINT "[] Change Terrain"
 LOCATE 8, 62: PRINT "S: Save"
 LOCATE 9, 62: PRINT "P: Show Specials"
LOCATE 10, 62: PRINT "B: Byteswap"
LOCATE 11, 62: PRINT "E: Super Editor"

ovconvert 0, 119

ovrefresh

END SELECT

LOOP

LINE (488, 0)-(639, 479), 0, BF
LOCATE 1, 62: PRINT "Save First?"
LOCATE 2, 62: PRINT "Y/N"
IF YesOrNo = 1 THEN
  f = FREEFILE
  OPEN filename$ FOR BINARY AS #f
  IF dq = 1 THEN PUT #f, &HB4B, ovstring
  IF dq = 0 THEN PUT #f, &H1D6E, ovstring
  CLOSE
END IF

END SUB

SUB ovGetO
tile = offset(orow)
x = 0
x1 = 0
DO
  d = 0
  B = ASC(MID$(ovstring, tile + 1, 1))
  rep = B MOD 16
  FOR t = 0 TO rep
    x = x + 1
    d = d + 1
  NEXT
  tile = tile + 1
  IF x > xbyte + d / 2 THEN EXIT DO
  x1 = x
LOOP
obyte = tile - 1

xbyte = x1

IF obyte >= offset(orow + 1) THEN
  WHILE obyte >= offset(orow + 1)
  obyte = obyte - 1
  WEND
  ovGetX
END IF

END SUB

SUB ovGetX

tile = offset(orow)
xbyte = 0
DO
  IF tile = obyte THEN EXIT SUB
  rep = ASC(MID$(ovstring, tile + 1, 1)) MOD 16
  FOR x = 0 TO rep
    xbyte = xbyte + 1
  NEXT
  tile = tile + 1
LOOP

END SUB

SUB ovkonvert (y1, y2)

FOR g = y1 TO y2
ovlKonvert g
NEXT

END SUB

SUB ovLConvert (row)

col = 0
t = 0
rep = 0
tile = offset(row)

DO
  tmp = ASC(MID$(ovstring, tile + 1, 1))
  t = tmp \ 16
  rep = (tmp MOD 16)
  FOR x = 0 TO rep
    g = t * 10 + 1300
    PUT (col * 4, row * 4), maptile(g), PSET
  col = col + 1
    IF col = 120 THEN
      EXIT SUB
    END IF
  NEXT
  tile = tile + 1
LOOP

END SUB

SUB ovLDivert (y)

tile = offset(y)
x = 0
B = map(0, y)

DO
  IF tile = offset(y + 1) THEN EXIT SUB
  x = x + 1
  IF x = 120 THEN
    MID$(ovstring, tile + 1, 1) = CHR$(B * 16 + ln)
    EXIT SUB
  END IF
 
  buffa = map(x, y)
  IF B = buffa THEN ln = ln + 1
  IF ln = 16 THEN
    ln = 0
    MID$(ovstring, tile + 1, 1) = CHR$(B * 16 + 15)
    tile = tile + 1
  END IF
  IF B <> buffa THEN
    MID$(ovstring, tile + 1, 1) = CHR$(B * 16 + ln)
    ln = 0
    B = buffa
    tile = tile + 1
  END IF
LOOP








END SUB

SUB ovlKonvert (y)

x = 0
t = 0
rep = 0
tile = offset(y)

DO
  tmp = ASC(MID$(ovstring, tile + 1, 1))
  t = tmp \ 16
  rep = (tmp MOD 16)
  FOR temp = 0 TO rep
    map(x, y) = t
      x = x + 1
      IF x = 120 THEN
      EXIT SUB
    END IF
  NEXT
  tile = tile + 1
LOOP

END SUB

SUB ovrefresh

olen = ASC(MID$(ovstring, obyte + 1, 1)) MOD 16
x1 = xbyte * 4: y1 = orow * 4
x2 = x1 + olen * 4 + 3: y2 = y1 + 3
IF x2 > 479 THEN x2 = 480
LINE (x1, y1)-(x2, y2), 11, B
LINE (480, 0)-(480, 479), 0
LOCATE 13, 62: PRINT "Csr X,Y=" + Strim$(xbyte) + "," + Strim$(orow) + "   "

END SUB

SUB ovsmovecursor (xc, yc)
cx = cx + xc
cy = cy + yc
IF cx < 0 THEN cx = 119
IF cx > 119 THEN cx = 0
IF cy < 0 THEN cy = 119
IF cy > 119 THEN cy = 0

END SUB

SUB ovSpecial (x AS INTEGER, y AS INTEGER, text$)

x1 = x * 4
x2 = x1 + 3

y1 = y * 4
y2 = y1 + 3

row = ((y + 1) \ 4) + 1
col = INT((x + 1) / 2 + 2)

LINE (x1, y1)-(x2, y2), 4, B
LOCATE row, col: PRINT text$

END SUB

SUB ovSRefresh

LOCATE 14, 62: PRINT "Cursor X,Y=        ";
LOCATE 14, 62: PRINT "Cursor X,Y=" + Trim(STR$(cx)) + ", " + Trim(STR$(cy))
LOCATE 15, 62: PRINT "Draw with: "; buffer
LOCATE 16, 62: PRINT "Masses: ";
IF getmass(cy) > offset(cy + 1) - offset(cy) + 1 THEN COLOR 12
PRINT Strim$(getmass(cy));
COLOR 15: PRINT ; "/"; Strim$(offset(cy + 1) - offset(cy)) + "   "
ovdrawtile -1, -1

END SUB

SUB ovSuperEdit
DIM TemPage

restart:

LINE (488, 0)-(639, 479), 0, BF
 LOCATE 1, 62: PRINT "Alefgard  h1D6E";
 LOCATE 2, 62: PRINT "120x120, RLE";
 LOCATE 3, 62: PRINT "Keys:"
 LOCATE 4, 62: PRINT "Arrows: Move Around"

IF page > 1 THEN
  LOCATE 5, 62: PRINT "ESC: Return without"
  LOCATE 6, 62: PRINT "     Saving!"
  LOCATE 7, 62: PRINT "Enter: Get Tile"
  LOCATE 8, 62: PRINT "Space: Paste Tile"
  LOCATE 9, 62: PRINT "+/- Change Tile"
 LOCATE 10, 62: PRINT "S: Keep Changes"
 LOCATE 11, 62: PRINT "P: Show Specials"
 LOCATE 12, 62: PRINT "TAB: ToggleDrawMode"
 LOCATE 18, 62: PRINT "M: Change Music"


END IF
IF page = 1 THEN
  LOCATE 5, 62: PRINT "ESC: Throne Room"
  LOCATE 6, 62: PRINT "W: Warp"
  LOCATE 7, 62: PRINT "M: Change Music"
  LOCATE 9, 62: PRINT "Just browsing..."
 LOCATE 10, 62: PRINT "(not editing!)"
END IF

LOCATE 14, 62: PRINT "Cursor X,Y="
LOCATE 15, 62: PRINT "Draw with:"
LOCATE 16, 62: PRINT "Masses: 0/0"
ovdrawtile -1, -1

x1 = cx * 4: y1 = cy * 4
LINE (x1, y1)-(x1 + 3, y1 + 3), 15, B

IF drawmode THEN LINE (x1, y1)-(x1 + 3, y1 + 3), 2, B

ovSRefresh
top:
DO
a$ = ""

IF page = 1 THEN
  buffer = map(cx, cy)
  ovdrawtile -1, -1
  ovSRefresh
END IF

DO
a$ = UCASE$(INKEY$)
LOOP WHILE a$ = ""



SELECT CASE a$
 
  CASE "M"
    TemPage = page
    page = 1
    EditMusic
    page = TemPage
    GOTO restart

  CASE CHR$(0) + "H"
  
    ovdrawtile cx, cy
    ovsmovecursor 0, -1
    IF drawmode THEN
      map(cx, cy) = buffer
      ovdrawtile csrx, csry
    END IF

    ovSRefresh

  CASE CHR$(0) + "P"
 
    ovdrawtile cx, cy
    ovsmovecursor 0, 1
    IF drawmode THEN
      map(cx, cy) = buffer
      ovdrawtile csrx, csry
    END IF

    ovSRefresh

  CASE CHR$(0) + "K"
 
    ovdrawtile cx, cy
    ovsmovecursor -1, 0
    IF drawmode THEN
      map(cx, cy) = buffer
      ovdrawtile csrx, csry
    END IF

    ovSRefresh

  CASE CHR$(0) + "M"
 
    ovdrawtile cx, cy
    ovsmovecursor 1, 0
    IF drawmode THEN
      map(cx, cy) = buffer
      ovdrawtile csrx, csry
    END IF

    ovSRefresh

  CASE "+", "="
  
    buffer = buffer + 1
    IF buffer = 16 THEN buffer = 0
    ovdrawtile -1, -1
    IF drawmode THEN
      map(cx, cy) = buffer
      ovdrawtile cx, cy
    END IF
  
    ovSRefresh

  CASE "-"
 
    buffer = buffer - 1
    IF buffer = -1 THEN buffer = 15
    ovdrawtile -1, -1
    IF drawmode THEN
      map(cx, cy) = buffer
      ovdrawtile cx, cy
    END IF

    ovSRefresh

  CASE CHR$(13)

    buffer = map(cx, cy)
    ovdrawtile -1, -1
   
    ovSRefresh
END SELECT

IF page > 1 THEN
SELECT CASE a$
  CASE CHR$(9)
   
    drawmode = NOT drawmode
    IF drawmode THEN
      map(cx, cy) = buffer
      ovdrawtile cx, cy
    ELSE
      ovdrawtile cx, cy
      x1 = cx * 4: y1 = cy * 4
      LINE (x1, y1)-(x1 + 3, y1 + 3), 15, B
    END IF
   
    ovSRefresh
 
  CASE "S"
    ovdrawtile cx, cy
    FOR cy = 0 TO 119
      IF getmass(cy) > offset(cy + 1) - offset(cy) + 1 THEN
        x1 = cx * 4: y1 = cy * 4
        LINE (x1, y1)-(x1 + 3, y1 + 3), 15, B
        ovSRefresh
        PLAY chirp$
        GOTO top
      END IF
    NEXT
    cy = 0
    ovdivert
    CLS
    EXIT DO
 
  CASE " "
   
    map(cx, cy) = buffer
    ovdrawtile cx, cy
 
    ovSRefresh

END SELECT
END IF
IF page = 1 THEN
SELECT CASE a$

  CASE "W"
    csrx = cx
    csry = cy
    Warp
    IF page <> 1 THEN EXIT SUB
  CASE CHR$(0) + "I"
    changepage (0)
    CLS : gettown page
    EXIT SUB
  CASE CHR$(0) + "Q"
    changepage (1)
    CLS : gettown page
    EXIT SUB


END SELECT
END IF

x1 = cx * 4: y1 = cy * 4
LINE (x1, y1)-(x1 + 3, y1 + 3), 15, B

IF drawmode THEN LINE (x1, y1)-(x1 + 3, y1 + 3), 2, B

LOOP UNTIL a$ = CHR$(27)

CLS



END SUB

SUB pause
LOCATE 28, 62
PRINT "Press any key";
LOCATE 29, 62
PRINT "to continue";
z$ = INPUT$(1)
LOCATE 28, 62
PRINT "             ";
LOCATE 29, 62
PRINT "           ";
END SUB

FUNCTION prompt$ (pmt AS STRING, ext AS STRING, dft AS STRING)

DIM a$

lin = CSRLIN
LOCATE lin, 1

PRINT SPACE$(LEN(pmt) + 16)

PRINT "     (" + CHR$(34) + dft + CHR$(34) + " if no file specified)";
lin = CSRLIN - 1

LOCATE lin, 1

PRINT pmt + "________."; ext;
LOCATE lin, LEN(pmt) + 1, 1, 14, 16

DIM pstring$

fini = 0
DO

DO: a$ = INKEY$: LOOP WHILE a$ = ""

SELECT CASE ASC(a$)
  CASE 27
    LOCATE , LEN(pmt) + 15, 0
    PRINT "Abort program?"
    IF YesOrNo = 1 THEN
      PRINT
      SYSTEM
    END IF

    LOCATE lin, LEN(pmt + pstring$) + 1, 1
  CASE 7: BEEP
  CASE 8
    IF LEN(pstring$) > 0 THEN
      pstring$ = LEFT$(pstring$, LEN(pstring$) - 1)
      LOCATE CSRLIN, POS(0) - 1
      PRINT "_";
      LOCATE CSRLIN, POS(0) - 1
  END IF
 
  CASE 13
    fini = 1
 
  CASE IS < 33
  CASE ELSE
    IF LEN(pstring$) < 8 THEN
      PRINT a$;
      pstring$ = pstring$ + a$
  END IF

END SELECT

a$ = ""
LOOP UNTIL fini = 1
LOCATE , , 0

FOR twemp = 1 TO LEN(pstring$)
  IF MID$(pstring$, twemp, 1) = "." THEN
    pstring$ = LEFT$(pstring$, twemp - 1)
  END IF
NEXT



prompt$ = pstring$ + "." + ext
IF pstring$ = "" THEN prompt$ = dft

END FUNCTION

SUB RemapTile (t AS INTEGER)

IF flags = 5 THEN EXIT SUB

IF flags = 1 OR flags = 2 THEN t = t MOD 8


IF flags = 2 THEN
  SELECT CASE t
    CASE 0: t = 4
    CASE 1: t = 5
    CASE 2: t = 6
    CASE 3: t = 7
    CASE 4: t = 3
    CASE 5: t = 11
    CASE 6: t = 16
    CASE 7: t = 19
  END SELECT
END IF
IF flags = 3 THEN
  t = t \ 8
  IF t = 1 THEN t = 17
  IF t = 0 THEN t = 19
END IF

END SUB

SUB SaveFile
ffile = FREEFILE
OPEN filename FOR BINARY AS #ffile
IF dq = 0 THEN PUT #ffile, &HC1, mapstring
IF dq = 1 THEN PUT #ffile, &HC1 + &H1506, mapstring
CLOSE
END SUB

SUB SecurityCheck
DIM n AS INTEGER
DIM ck AS STRING
DIM infile AS STRING * 15
GET #ffile, 17, infile

dq = 0
passed = 0

ck = CHR$(&H0) + CHR$(&H0) + CHR$(&H7E) + CHR$(&HAA) + CHR$(&HBD)
ck = ck + CHR$(&HBA) + CHR$(&H47) + CHR$(&H99) + CHR$(&HDA) + CHR$(&HB6)
ck = ck + CHR$(&HA2) + CHR$(&HA7) + CHR$(&H62) + CHR$(&HAA) + CHR$(&H3D)
IF ck = infile THEN passed = 1

IF passed = 0 THEN
  ck = CHR$(&HA) + CHR$(&H0) + CHR$(&H3C) + CHR$(&H0) + CHR$(&HB4)
  ck = ck + CHR$(&H0) + CHR$(&H30) + CHR$(&H2) + CHR$(&HDC) + CHR$(&H5)
  ck = ck + CHR$(&H48) + CHR$(&H26) + CHR$(&H2) + CHR$(&H0) + CHR$(&H14)
  IF ck = infile THEN
    passed = 1
    dq = 1
  END IF
END IF

IF passed = 0 THEN
  BEEP
  PRINT : PRINT : PRINT
  PRINT "First 15 bytes of ROM are:"
  FOR x = 1 TO 16
  LOCATE CSRLIN, x * 3
  PRINT HEX$(ASC(MID$(infile, x)));
  NEXT
  PRINT : PRINT : PRINT "The bytes should be:"
  PRINT "  0  0  7E AA BD BA 47 99 DA B6 A2 A7 62 AA 3D  for Dragon Warrior and"
  PRINT "  A  0  3C 0  B4 0  30 2  DC 5  48 26 2  0  14  for Dragon Quest."
  PRINT "The loaded ROM might not be Dragon Warrior/Quest.  Continue?"
  IF YesOrNo = 0 THEN SYSTEM
END IF

n = 0
END SUB

SUB SetPalette
RESTORE palet:
FOR x = 1 TO 10
  READ r%, g%, B&: g% = g% * 256: B& = B& * 65536
  PALETTE x, r% + g% + B&
NEXT x
END SUB

SUB SetRomSpecials

DIM setblock AS STRING
DIM start AS LONG

ffile = FREEFILE
IF dq = 0 THEN
  setblock = SPACE$(124)
  FOR t = 0 TO 30
    MID$(setblock, t * 4 + 1, 1) = CHR$(treasure(t, 0))
    MID$(setblock, t * 4 + 2, 1) = CHR$(treasure(t, 1))
    MID$(setblock, t * 4 + 3, 1) = CHR$(treasure(t, 2))
    MID$(setblock, t * 4 + 4, 1) = CHR$(treasure(t, 3))
  NEXT
 
  OPEN filename FOR BINARY AS #ffile
 
  start = 24029
  IF dq = 1 THEN start = 61598
 
  PUT #ffile, start + 1, setblock
  CLOSE

  setblock = SPACE$(153)
  FOR t = 0 TO 50
    MID$(setblock, t * 3 + 1, 1) = CHR$(stairs(1, t, 0))
    MID$(setblock, t * 3 + 2, 1) = CHR$(stairs(1, t, 1))
    MID$(setblock, t * 3 + 3, 1) = CHR$(stairs(1, t, 2))
  NEXT
 
  OPEN filename FOR BINARY AS #ffile
 
  start = 62424
  IF dq = 1 THEN start = 61722
 
  PUT #ffile, start + 1, setblock
  CLOSE
 
  FOR t = 0 TO 50
    MID$(setblock, t * 3 + 1, 1) = CHR$(stairs(2, t, 0))
    MID$(setblock, t * 3 + 2, 1) = CHR$(stairs(2, t, 1))
    MID$(setblock, t * 3 + 3, 1) = CHR$(stairs(2, t, 2))
  NEXT
 
  OPEN filename FOR BINARY AS #ffile
 
  start = 62577
  IF dq = 1 THEN start = 61875

  PUT #ffile, start + 1, setblock
  CLOSE

END IF


END SUB

SUB SetTown (t)

SELECT CASE t
  CASE IS <= 1: PLAY chirp$: EXIT SUB
  CASE 2: tile = &HC1: edge(0) = 19: edge(1) = 19
  CASE 3: tile = &H189: edge(0) = 19: edge(1) = 19
  CASE 4: tile = &H251: edge(0) = 29: edge(1) = 29
  CASE 5: tile = &H413: edge(0) = 9: edge(1) = 9
  CASE 6: tile = &H445: edge(0) = 29: edge(1) = 29
  CASE 7: tile = &H607: edge(0) = 23: edge(1) = 23
  CASE 8: tile = &H727: edge(1) = 29: edge(0) = 29: rooftile = &HD35
  CASE 10: tile = &H8E9: edge(0) = 29: edge(1) = 29: rooftile = &HFBF
  CASE 9: tile = &HAAB: edge(0) = 19: edge(1) = 19: rooftile = &HEF7
  CASE 11: tile = &HB73: edge(0) = 29: edge(1) = 29: rooftile = &H1181
  CASE 12: tile = &HD35: edge(0) = 9: edge(1) = 9
  CASE 13: tile = &HD67: edge(0) = 9: edge(1) = 9
  CASE 14: tile = &HD99: edge(0) = 9: edge(1) = 9
  CASE 15: tile = &HDCB: edge(0) = 19: edge(1) = 19
  CASE 16: tile = &HE93: edge(0) = 9: edge(1) = 9
  CASE 17: tile = &HEC5: edge(0) = 9: edge(1) = 9
  CASE 18: tile = &HEF7: edge(0) = 9: edge(1) = 9
  CASE 19: tile = &HF29: edge(0) = 9: edge(1) = 9
  CASE 20: tile = &HF5B: edge(0) = 9: edge(1) = 9
  CASE 21: tile = &HF8D: edge(0) = 5: edge(1) = 29
  CASE 22: tile = &HFE7: edge(0) = 13: edge(1) = 13
  CASE 23: tile = &H1049: edge(0) = 13: edge(1) = 13
 
  CASE 24: tile = &H10AB: edge(0) = 19: edge(1) = 19
  CASE 25: tile = &H126D: edge(0) = 13: edge(1) = 11
  CASE 26: tile = &H1173: edge(0) = 19: edge(1) = 19
  CASE 27: tile = &H123B: edge(0) = 9: edge(1) = 9
 
  CASE 28: tile = &H12C1: edge(0) = 9: edge(1) = 9
  CASE 29: tile = &H12F3: edge(0) = 9: edge(1) = 9
END SELECT

tile = tile - &HC0
rooftile = rooftile - &HC0

divert edge(0), edge(1)
'   rooftile = &HD35
'   rooftile = &HFBF
'   rooftile = &HEF7
'   rooftile = &H1181
END SUB

SUB specials (t)
FOR x = 0 TO edge(0): FOR y = 0 TO edge(1): special(x, y) = 0: NEXT: NEXT

FOR tres = 0 TO 30
  IF treasure(tres, 0) = t THEN
    special(treasure(tres, 1), treasure(tres, 2)) = 4
  END IF
NEXT

FOR star = 50 TO 0 STEP -1
  IF stairs(1, star, 0) = t THEN
    special(stairs(1, star, 1), stairs(1, star, 2)) = star + 65
  END IF
NEXT

FOR star = 50 TO 0 STEP -1
  IF stairs(2, star, 0) = t THEN
    special(stairs(2, star, 1), stairs(2, star, 2)) = star + 129
  END IF
NEXT



SELECT CASE t
  CASE 2
     special(10, 3) = 9
  CASE 3
    special(18, 12) = 9
  CASE 4
    special(24, 1) = 7
    special(19, 2) = 7
    special(27, 5) = 7
    special(8, 6) = 7
    special(2, 8) = 7
    special(8, 8) = 7
    special(11, 11) = 7
    special(17, 11) = 7
    special(25, 11) = 7
    special(2, 12) = 7
    special(8, 13) = 7
    special(26, 15) = 7
    special(18, 18) = 7
    special(15, 20) = 7
    special(4, 21) = 7
    special(24, 21) = 7
    special(6, 25) = 7
    special(20, 26) = 7
    special(9, 27) = 7
    special(12, 27) = 7
  CASE 5
    special(3, 3) = 7
    special(6, 3) = 7
    special(3, 6) = 7
    special(5, 6) = 7
    special(7, 5) = 7
  CASE 6
    special(16, 24) = 7
  CASE 7
    special(1, 1) = 7
    special(12, 1) = 7
    special(19, 4) = 7
    special(6, 7) = 7
    special(20, 8) = 7
    special(12, 10) = 7
    special(5, 12) = 7
    special(2, 12) = 7
    special(22, 12) = 7
    special(20, 13) = 7
    special(11, 14) = 7
    special(14, 13) = 7
    special(7, 19) = 7
    special(20, 19) = 7
    special(14, 21) = 7
    special(1, 23) = 7
    special(9, 6) = 9
  CASE 8
    special(1, 13) = 7
    special(3, 26) = 7
    special(4, 7) = 7
    special(5, 4) = 7
    special(9, 4) = 7
    special(10, 14) = 7
    special(10, 21) = 7
    special(10, 26) = 7
    special(12, 19) = 7
    special(15, 9) = 7
    special(15, 24) = 7
    special(19, 18) = 7
    special(20, 10) = 7
    special(20, 23) = 7
    special(24, 4) = 7
    special(24, 10) = 7
    special(25, 22) = 7
    special(25, 25) = 7
    special(26, 15) = 7
    special(28, 1) = 7
  CASE 10
    special(8, 3) = 7
    special(2, 7) = 7
    special(5, 6) = 7
    special(15, 6) = 7
    special(22, 5) = 7
    special(27, 6) = 7
    special(22, 9) = 7
    special(2, 12) = 7
    special(7, 12) = 7
    special(24, 12) = 7
    special(22, 13) = 7
    special(4, 14) = 7
    special(9, 16) = 7
    special(15, 16) = 7
    special(20, 15) = 7
    special(25, 17) = 7
    special(22, 22) = 7
    special(27, 26) = 7
    special(3, 26) = 7
    special(14, 28) = 7
  CASE 9
    special(2, 10) = 7
    special(2, 17) = 7
    special(3, 5) = 7
    special(5, 5) = 7
    special(5, 11) = 7
    special(14, 1) = 7
    special(12, 4) = 7
    special(7, 17) = 7
    special(9, 6) = 7
    special(11, 7) = 7
    special(12, 8) = 7
    special(10, 18) = 7
    special(12, 12) = 7
    special(18, 12) = 7
    special(17, 15) = 7
  CASE 11
    special(2, 4) = 7
    special(4, 7) = 7
    special(11, 8) = 7
    special(15, 8) = 7
    special(27, 0) = 7
    special(23, 7) = 7
    special(6, 13) = 7
    special(14, 11) = 7
    special(23, 11) = 7
    special(22, 14) = 7
    special(8, 16) = 7
    special(16, 18) = 7
    special(24, 19) = 7
    special(20, 23) = 7
    special(3, 23) = 7
    special(6, 21) = 7
    special(6, 23) = 7
    special(5, 25) = 7
    special(0, 26) = 7
    special(16, 26) = 7
  CASE 12
    special(4, 6) = 7
  CASE 13
    special(4, 4) = 7
  CASE 14
    special(4, 5) = 7
  CASE 21
    special(4, 14) = 5
END SELECT

END SUB

SUB SpecRedraw

 LOCATE 3, 62: PRINT "Keys:              ";
 LOCATE 4, 62: PRINT "Pgup/dn:Move Object";
 LOCATE 5, 62: PRINT "    to another page";
 LOCATE 6, 62: PRINT ": Change Active  ";
 LOCATE 7, 62: PRINT CHR$(27); CHR$(26); ": Change Tool   "
 LOCATE 8, 62: PRINT "S: Save Changes    ";
 LOCATE 9, 62: PRINT "Enter: Move Object ";
 LOCATE 10, 62
 IF editmode = 0 THEN PRINT "Z: Change Contents ";
 IF editmode = 1 THEN PRINT CHR$(26) + ": Warp            "
 IF editmode = 2 THEN PRINT CHR$(27) + ": Warp            "
 LOCATE 11, 62: PRINT "ESC: Exit w/nosave "
LINE (483, 0)-(483, 479), 15


SpecRefresh
END SUB

SUB SpecRefresh

LOCATE 16, 62: PRINT "Pg="; Strim$(page)
LOCATE 16, 68: PRINT "X,Y="; Strim$(csrx); ","; Strim$(csry); "  "

IF editmode = 0 THEN
 
  LOCATE 13, 62: PRINT "Treasure Editor"
  LOCATE 14, 62: PRINT "Chest "; Strim$(ctres + 1); "/31"
  LOCATE 18, 62: PRINT "Inside Chest:"
  LOCATE 19, 62: PRINT HEX$(content); "-"; "                "
  LOCATE 19, 65
  SELECT CASE content
    CASE 0: PRINT "Axe Ghost *"
    CASE 1: PRINT "Bamboo Pole *"
    CASE 2: PRINT "Herb"
    CASE 3: PRINT "Magic Key"
    CASE 4: PRINT "Torch"
    CASE 5: PRINT "Fairy Water"
    CASE 6: PRINT "Wings"
    CASE 7: PRINT "Dragon's Scale"
    CASE 8: PRINT "Fairy Flute"
    CASE 9: PRINT "Fighter's Ring"
    CASE 10: PRINT "Erdrick's Token"
    CASE 11: PRINT "Gwaelin's Love"
    CASE 12: PRINT "Cursed Belt"
    CASE 13: PRINT "Silver Harp"
    CASE 14: PRINT "GP: 100-130"
    CASE 15: PRINT "Sunlight Stones"
    CASE 16: PRINT "Staff of Rain"
    CASE 17: PRINT "Erdrick's Sword"
    CASE 18: PRINT "GP: 5-21"
    CASE 19: PRINT "GP: 7-13"
    CASE 20: PRINT "GP: 10-18"
    CASE 21: PRINT "GP: 512-784"
    CASE 22: PRINT "GP: 120"
    CASE ELSE: PRINT "Tablet"
  END SELECT
END IF

IF editmode > 0 THEN
  LOCATE 13, 62
  PRINT "Stairs ";
  IF editmode = 1 THEN PRINT "Down";
  IF editmode = 2 THEN PRINT "Up";
  PRINT " Editor"
  LOCATE 14, 62
  PRINT "Staircase "; Strim$(cstar + 1); "/51"
  LOCATE 18, 62: PRINT "Other Stairs:"
  IF editmode = 1 THEN
    LOCATE 20, 62: PRINT "Pg=" + Strim$(stairs(2, cstar, 0)) + "              "
    LOCATE 20, 68: PRINT "X,Y="; Strim$(stairs(2, cstar, 1)); ","; Strim$(stairs(2, cstar, 2))
  END IF
  IF editmode = 2 THEN
    LOCATE 20, 62: PRINT "Pg=" + Strim$(stairs(1, cstar, 0)) + "              "
    LOCATE 20, 68: PRINT "X,Y="; Strim$(stairs(1, cstar, 1)); ","; Strim$(stairs(1, cstar, 2))
  END IF

END IF


END SUB

FUNCTION Strim$ (t)
Strim$ = Trim$(STR$(t))
END FUNCTION

FUNCTION Trim$ (t$)
Trim$ = LTRIM$(RTRIM$(t$))
END FUNCTION

SUB Warp

FOR star = 0 TO 50
  IF stairs(1, star, 0) = page AND stairs(1, star, 1) = csrx AND stairs(1, star, 2) = csry THEN
    page = stairs(2, star, 0)
    csrx = stairs(2, star, 1)
    csry = stairs(2, star, 2)
    PLAY teleport$
    CLS
    gettown page
    EXIT SUB
  END IF
  IF stairs(2, star, 0) = page AND stairs(2, star, 1) = csrx AND stairs(2, star, 2) = csry THEN
    page = stairs(1, star, 0)
    csrx = stairs(1, star, 1)
    csry = stairs(1, star, 2)
    PLAY teleport$
    CLS
    gettown page
    EXIT SUB
  END IF
NEXT

PLAY chirp$
END SUB

FUNCTION YesOrNo
yn = -1
DO
a$ = INKEY$
SELECT CASE UCASE$(a$)
CASE "Y": yn = 1
CASE "N": yn = 0
END SELECT
LOOP WHILE yn = -1
YesOrNo = yn
END FUNCTION

