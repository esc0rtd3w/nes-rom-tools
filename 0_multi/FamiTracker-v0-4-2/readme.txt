FamiTracker Readme
------------------

FamiTracker is an application designed to create music for the NES/Famicom systems, it is
distributed under the GNU GPL license. Windows XP or later and a DirectX compatible sound 
card is required to run this software. More information can be found in the help files or 
on the web page.

For a compendium of frequently asked questions, see:
http://www.famitracker.com/wiki/index.php?title=Frequently_Asked_Questions

To uninstall, run "famitracker.exe /unregister". This will remove the file association.

Web:  http://www.famitracker.com
Mail: jsr@famitracker.com


Changelog (v0.4.2)
------------------
 New stuff:
  - Added selection + drag & drop capability to the frame editor
  - NSF exporter will optimize N163 waves
  - Added initial delta counter setting to the DPCM instrument editor
  - Added a text exporter / importer (by rainwarrior)
  - Added a shortcut item for the duplicate patterns command
  - Added a volume mask option to pattern editor (edit menu)
  - Added module comments dialog
  - Adjusted filtering of FDS audio emulation
  
 Fixed bugs:
  - Fixed extra effect columns not being copied on shift+drag
  - Fixed a problem with shift+mouse wheel
  - Fixed a few other FTM file import problems
  - Fixed a problem with FDS wave previewing
  - Fixed a bankswitching bug when exporting multisong NSFs
  - Fixed VRC6 and MMC5 not being silenced by the Cxx command
  - Fixed some problems with the Dxx command
