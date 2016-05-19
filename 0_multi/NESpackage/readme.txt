  NES package
  -----------

  Copyright 2006, Dennis Elser


  This is a collection of IDA Pro extensions for NES ROM image
  analysis. It consists of:

  - nesldr: a loader module for NES ROM images in iNES file format
    (this is required for all other modules). This module instructs
    IDA Pro how to load and disassemble iNES ROM images.
  
  - bankswitch: a plugin module which simulates the NES' various
    mappers by allowing the user to load any PRG-ROM page into
    the ROM banks at 0x8000 or 0xC000.
    
  - MadNES: a plugin module to export IDA names, comments, xrefs etc.
    to FCEUXD SP symbol format to allow symbolic debugging.
    
  - nesdbg: a debugger plugin module to allow debugging the NES'
    M6502 code directly from IDA Pro.


  Please note that all binaries are delivered as debug build.

   Copyright 2006, Dennis Elser (dennis@backtrace.de)