/*

	MadNES, a symbol exported plugin for FCEUXD SP
	----------------------------------------------
	Copyright 2006, Dennis Elser (dennis@backtrace.de)


	IDA Pro plugin module for Nintendo Enternainment System
    (NES) ROM images in iNES file format.



	license:
	--------

	- freeware, copyright messages have to stay intact.



	Copy compiled plugin to idadir%/plugins/MadNES.plw


    Please send me an e-mail if you find any bugs!

	(c) 2006, Dennis Elser (dennis@backtrace.de)

*/


#include <ida.hpp>
#include <idp.hpp>
#include <expr.hpp>
#include <bytes.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <name.hpp>

extern plugin_t PLUGIN;


//----------------------------------------------------------------------
//
//      get number of newline characters
//
size_t get_newline_count(char *buf)
{
    size_t count = 0;
    for(size_t i=0;i<=strlen(buf);i++)
    {
        if(buf[i] == 0xA)
            count++;
    }
    return count;
}

//----------------------------------------------------------------------
//
//      replace invalid characters, add required ones for
//      multiline comments
//
char *validate_comment(char *cmt)
{
    size_t bufsize;
    char *buf = NULL;
    size_t j = 0;

    bufsize = get_newline_count( cmt )+1;
    if( bufsize == 0 )
        return NULL;
    bufsize += strlen(cmt);
    buf = (char *)qalloc( bufsize );
    for(size_t i=0;i<=strlen(cmt);i++)
    {
        
        switch(cmt[i])
        {
        default:
            buf[j] = cmt[i];
            break;
        case '#': // conflicting with FCEUXD SP syntax
            buf[j]='*'; // convert to '*'
            break;
        case 0xA:
            buf[j] = cmt[i]; // multiline comment
            buf[++j] = '\\';
        }
        j++;
    }
    //buf[j] = 0;
    return buf;
}


//----------------------------------------------------------------------
//
//      check loader name
//
int idaapi init(void)
{
    char buf[MAXSTR];

    get_loader_name(buf,sizeof(buf));
    if(strcmp("nes", buf) != 0) // allow NES files only
        return PLUGIN_SKIP;

    return PLUGIN_OK;
}


void idaapi term(void)
{

}

// form for dialog / MadNES options
static const char madnes_options[] = 
"STARTITEM 0\n"
"MadNES options\n\n"                                        // Title
"  <Export ~n~ames:C>\n"
"  <Export ~a~ny name:C>\n"
"  <Export ~x~refs:C>\n"
"  <Export ~c~omments:C>>\n\n"
"  <Page number         :N:4:4::>\n"
"\n";

#define OPTION_NAMES    0x1
#define OPTION_ANYNAME  0x2
#define OPTION_XREFS    0x4
#define OPTION_COMMENTS 0x8


void idaapi run(int arg)
{
    char buf[MAXSTR];
    char cmt[MAXSTR];
    char *valid_cmt = NULL;
    char ext[0x20];
    FILE *f = NULL;
    short checkboxes = OPTION_NAMES | OPTION_COMMENTS;
    sval_t bank = 1; // default
    bool first = true;
    bool hasName = false;
    flags_t flags;
    ea_t ea = 0x0;


    if( AskUsingForm_c( madnes_options, &checkboxes, &bank ) != 1 || checkboxes == 0 )
        return;

    // prepare filename for namelist (.nl) file
    get_input_file_path( buf, sizeof( buf ) );
    qsnprintf( ext, sizeof( ext ),".%X.nl",--bank );
    qstrncat( buf, ext, sizeof( buf )-strlen( buf ) );
    
    // (always) create file
    f = qfopen( buf, "w" );
    if( f == NULL )
    {
        warning( "%s could not be created!", buf );
        return;
    }
    
    msg( "Writing to file %s..", buf );
    
    while( ea <= 0xFFFF )
    {
        hasName = false;

        // get flags
        if( isCode( getFlags( ea ) ) )
            flags = getFlags( ea );
        else
            flags = getFlags( get_item_head( ea ) );

        // if user either chose to export names or anynames
        if( ( ( checkboxes & OPTION_NAMES ) && has_name( flags ) ) || ( ( checkboxes & OPTION_ANYNAME ) && has_any_name( flags ) ) )
        {
            // if current item is code or if current item is head of item
            if( isCode( flags ) || ea==get_item_head( ea ) )
            {
                // get name
                get_name( ea, ea, buf, sizeof( buf ) );
                // write to file
                qfprintf( f, "$%04X#%s#", ea, buf );
            }
            else // if not code or not head of item (must be an array)
            {
                // get name of item start
                get_name( get_item_head( ea ), get_item_head( ea ), buf, sizeof( buf ) );
                // calc displacement, write to file (example: "password+$04")
                qfprintf( f, "$%04X#%s+$%X#", ea, buf, ea-get_item_head( ea ) );
            }
            hasName = true;
        }
        
        // if user chose to export cross references
        if( checkboxes & OPTION_XREFS )
        {
            xrefblk_t xb;

            first = true;
            // cycle through all xrefs except ordinary flow xrefs
            for ( bool ok=xb.first_to( ea, XREF_FAR/*XREF_ALL*/); ok; ok=xb.next_to() )
            {
                if( first ) // if first xref
                {
                    if( !hasName ) // if this location hasn't a name yet, add symbol stub
                    {
                        qfprintf( f, "$%04X##", ea );
                        hasName = true;
                    }
                    qfprintf( f, "XREFS:\n\\"); // append XREFS
                    first = false;
                }
                qfprintf( f, "  $%04X\n\\", xb.from );
            }
        }
        
        // if user chose to export comments
        if( checkboxes & OPTION_COMMENTS )
        {
            if( has_cmt( flags ) ) // if current item has comment
            {              
                // get comment
                // workaround for get_any_indeted_cmt()
                // -> unresolved external symbol "char * __stdcall get_any_indented_cmt(unsigned long,unsigned char *)" (?get_any_indented_cmt@@YGPADKPAE@Z)
                if( get_cmt( ea, false, cmt, sizeof( cmt ) ) == -1 )
                    get_cmt( ea, true, cmt, sizeof( cmt ) );
                
                // validate comment (replace invalid chars, add room for additional chars)
                valid_cmt = validate_comment( cmt );
                
                if( valid_cmt != NULL )
                {
                    if( !hasName )
                    {
                        qfprintf( f, "$%04X##", ea ); // add symbol stub if no name yet
                        hasName = true;
                    }
                    qfprintf( f, "%s", valid_cmt ); // write comment to file
                    qfree( valid_cmt );
                }
            }            
        }        
        
        if( hasName) qfprintf( f, "\n" );
        ea++; // get name of each byte
    }
    qfclose( f );
    msg( "done.\n" );
}

//--------------------------------------------------------------------------
char comment[] = "Symbol exporter for FCEUXD SP";

char help[] = "Symbol exporter for FCEUXD SP";


//--------------------------------------------------------------------------
// This is the preferred name of the plugin module in the menu system
// The preferred name may be overriden in plugins.cfg file

char wanted_name[] = "MadNES";


// This is the preferred hotkey for the plugin module
// The preferred hotkey may be overriden in plugins.cfg file
// Note: IDA won't tell you if the hotkey is not correct
//       It will just disable the hotkey.

char wanted_hotkey[] = "Alt-Space";


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
