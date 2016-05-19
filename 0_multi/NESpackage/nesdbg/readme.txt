	
	Nintendo Entertainment System (NES) debugger module
	------------------------------------------------------
	Copyright 2006, Dennis Elser (dennis@backtrace.de)


  Please note that this debugger is the client part for a
  remote debugger. The remote debugger does not exist yet,
  because of troubles while compiling the server.


1. install IDA Pro SDK.
2. install bcc(55) and configure it to be able to compile IDA Pro plugins
   (for instructions, see IDA Pro SDK). The Microsoft compilers don't seem
   to work, at least I don't know how to compile the project - if you know,
   please tell me how :)
3. make a copy of the "debugger" project in the "plugins" subdirectory of
   the IDA Pro sdk. Name the copy of the directory "desdbg" and copy the source
   code of this package (/src) there.
4. run "makenes.bat". if everything goes well, you should have nes_stub.plw,
   that you are to copy to %idadir%\plugins\. if it didn't compile, you either
   didn't set up the IDA sdk or BCC correctly or you didn't follow these instructions
   carefully enough.
5. in conjunction with the NES loader for iNES ROM images
   (http://home.arcor.de/idapalace/nesldr) you can almost use the debugger.
   almost because it is "just" a client for a remote debugger, which is not
   developed yet. the idea is to integrate the remote debugger (which is the
   server for the IDA plugin) into an NES emulator like FCEUSP.
   
   Copyright 2006, Dennis Elser (dennis@backtrace.de)