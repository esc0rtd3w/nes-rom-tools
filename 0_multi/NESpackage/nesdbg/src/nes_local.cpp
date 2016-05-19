#include <loader.hpp>

//--------------------------------------------------------------------------
void idaapi rebase_if_required_to(ea_t new_base)
{

}

//--------------------------------------------------------------------------
// Initialize NES debugger plugin
static bool init_plugin(void)
{
  char buf[MAXSTR];
  get_loader_name(buf, sizeof(buf));
  if ( strcmp( buf, "nes" ) != 0 )
    return false; // only NES files

  return true;
}

//--------------------------------------------------------------------------
char comment[] = "NES debugger plugin.";

char help[] =
        "A NES debugger plugin\n"
        "\n"
        "This module shows you how to create debugger plugins.\n";

