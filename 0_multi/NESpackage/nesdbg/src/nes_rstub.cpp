#define DEBUGGER_ID_NES_FCEUXD_SP 0x4
#define REMOTE_DEBUGGER
#define DEBUGGER_CLIENT

char wanted_name[] = "NES debugger";
#define DEBUGGER_NAME  "nesdbg"
#define PROCESSOR_NAME "m6502"
#define DEBUGGER_ID    DEBUGGER_ID_NES_FCEUXD_SP
#define DEBUGGER_FLAGS DBG_FLAG_REMOTE

#include "idarpc.cpp"
#include "m6502_local.cpp"
#include "nes_local.cpp"
#include "common_local.cpp"

