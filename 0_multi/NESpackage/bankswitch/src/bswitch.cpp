/*

	Nintendo Entertainment System (NES) bank switcher
	------------------------------------------------------
	Copyright 2006, Dennis Elser (dennis@backtrace.de)


	IDA Pro plugin module for Nintendo Enternainment System
    (NES) ROM images in iNES file format.


	license:
	--------

	- freeware, copyright messages have to stay intact.



	Copy compiled plugin to idadir%/plugins/bankswitch.plw


    Please send me an e-mail if you find any bugs!

	(c) 2006, Dennis Elser (dennis@backtrace.de)

*/

#include <ida.hpp>
#include <idp.hpp>
#include <expr.hpp>
#include <bytes.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <netnode.hpp>
#include <auto.hpp>
#include "nes.h"
#include "mappers.h"

extern plugin_t PLUGIN;


static ines_hdr hdr;


//----------------------------------------------------------------------
//
//      load iNES header into global ines_hdr structure
//
static bool load_ines_hdr(void)
{
    netnode node(INES_HDR_NODE);
    ines_hdr *temphdr = NULL;
    
    if(!netnode_exist(node))
        return false;
    temphdr = (ines_hdr *)node.getblob(NULL, NULL, 0, 'I');
    if(temphdr == NULL)
        return false;
    memcpy(&hdr, temphdr, INES_HDR_SIZE);
    qfree(temphdr);
    return true;
}

//----------------------------------------------------------------------
//
//      return number of PRG ROM pages contained in ROM image
//
static uchar get_prg_rom_page_count()
{
    return hdr.prg_page_count_16k;
}


//----------------------------------------------------------------------
//
//      calculates original file offset of "page"
//
//      this function is needed to load_prg_rom_page_from_blob()
//
static long calc_prg_rom_file_offset( uchar page )
{
    return INES_HDR_SIZE
        + (INES_MASK_TRAINER( hdr.rom_control_byte_0) ? TRAINER_SIZE : 0)
        + page * PRG_ROM_BANK_SIZE;
}


//----------------------------------------------------------------------
//
//      load PRG ROM page from blob
//
static bool load_prg_rom_page_from_blob( uchar page, ea_t loading_address )
{
	netnode node;
    char prg_node_name[MAXNAMESIZE];
    uchar *buffer;

    qsnprintf( prg_node_name, sizeof(prg_node_name), "$ PRG-ROM page %d", --page );
    if( node.create( prg_node_name ) ) return false;
    buffer = (uchar *)node.getblob(NULL, NULL, 0, 'I');
    if(buffer == 0)
        return false;
    show_wait_box("Loading page..");
    mem2base((uchar *)buffer, loading_address, loading_address + PRG_ROM_BANK_SIZE, calc_prg_rom_file_offset( page ));
    qfree(buffer);
    do_unknown_range(loading_address, PRG_ROM_BANK_SIZE, true);
    analyze_area(inf.minEA, inf.maxEA);
    autoWait();
    hide_wait_box();

	return true;
}

//----------------------------------------------------------------------
//
//      checks for 8k PRG ROM page mappers, which are not supported yet
//
static bool is_8k_prg_mapper(void)
{
    uchar mapper;
    bool badmapper = false;

    mapper = INES_MASK_MAPPER_VERSION(hdr.rom_control_byte_0, hdr.rom_control_byte_1);
    switch( mapper )
    {
    case MAPPER_MMC2:
    case MAPPER_TENGEN_RAMBO_1:
        badmapper = true;
        break;
    }
    return badmapper;
}


//----------------------------------------------------------------------
//
//      check loader name
//
int idaapi init(void)
{
    char loadername[MAXSTR];

    get_loader_name(loadername, sizeof(loadername));
    if(strcmp("nes",loadername) != 0)
        return PLUGIN_SKIP;
    return PLUGIN_OK;
}


void idaapi term(void)
{
    
}


//----------------------------------------------------------------------
//
//      all the action is happening here
//
void idaapi run(int arg)
{
    int res;
    sval_t maxpage;
    sval_t page;
    
    if(!load_ines_hdr())
    {
        warning("iNES header could not be loaded from database!\nThe database is damaged!");
        return;
    }
    
    if(is_8k_prg_mapper())
    {
        warning("The mapper used in this ROM image allows swapping of 8k PRG pages.\n"
                "This is not supported by the loader, yet!");
        return;
    }

    page = maxpage = get_prg_rom_page_count();

    if(page<=1)
    {
        warning("PRG-ROMs can't be switched for this file!\n");
        return;
    }

    warning("Warning! Previous banks are not saved automatically!\n"
            "It is advised that you save the database under a\n"
            "different filename after banks have been switched.\n"
            "Otherwise you will lose all previous results!\n");
    
    do
    {
        res = asklong(&page, "This file contains %d 16k-PRG-ROM pages.\n"
            "Which page do you want to load at 0x%X ?\n\n",
            maxpage,
            (get_screen_ea() < PRG_ROM_BANK_C000) ? PRG_ROM_BANK_8000 : PRG_ROM_BANK_C000);
        if(res != 1)
            return;
    } while(page<=0 || page>maxpage);

    msg("Loading page %d..\n",page);
    bool ok = load_prg_rom_page_from_blob( page, (get_screen_ea() < PRG_ROM_BANK_C000) ? PRG_ROM_BANK_8000 : PRG_ROM_BANK_C000);
    msg("%s loading page %d\n", ok ? "Done" : "Failed", page);

}

//--------------------------------------------------------------------------
char comment[] = "Bankswitch";

char help[] =
        "This plugin loads PRG-ROM pages into the database.\n"
        "\n"
        "It requires the NES loader module.\n";


//--------------------------------------------------------------------------
// This is the preferred name of the plugin module in the menu system
// The preferred name may be overriden in plugins.cfg file

char wanted_name[] = "Bankswitch";


// This is the preferred hotkey for the plugin module
// The preferred hotkey may be overriden in plugins.cfg file
// Note: IDA won't tell you if the hotkey is not correct
//       It will just disable the hotkey.

char wanted_hotkey[] = "Ctrl-Space";


//--------------------------------------------------------------------------
//
//      PLUGIN DESCRIPTION BLOCK
//
//--------------------------------------------------------------------------
plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  PLUGIN_UNL,           // plugin flags
  init,                 // initialize

  term,                 // terminate. this pointer may be NULL.

  run,                  // invoke plugin

  comment,              // long comment about the plugin
                        // it could appear in the status line
                        // or as a hint

  help,                 // multiline help about the plugin

  wanted_name,          // the preferred short name of the plugin
  wanted_hotkey         // the preferred hotkey to run the plugin
};
