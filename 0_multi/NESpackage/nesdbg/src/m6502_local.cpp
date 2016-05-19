#include <dbg.hpp>

#include "deb_nes.hpp"

//--------------------------------------------------------------------------
//
//      DEBUGGER REGISTER AND INSTRUCTIONS INFORMATIONS
//
//--------------------------------------------------------------------------

char* register_classes[] =
{
  "General registers",
  NULL
};


char* P[] =
{
  "C",
  "Z",
  "I",
  "D",
  "B",
  NULL,
  "V",
  "N",
};


register_info_t registers[] =
{
  // general registers
  { "A",    REGISTER_ADDRESS,             RC_GENERAL,  dt_byte, NULL,   0 },
  { "X",    REGISTER_ADDRESS,             RC_GENERAL,  dt_byte, NULL,   0 },
  { "Y",    REGISTER_ADDRESS,             RC_GENERAL,  dt_byte, NULL,   0 },
  { "SP",   REGISTER_ADDRESS|REGISTER_SP, RC_GENERAL,  dt_byte, NULL,   0 },
  { "PC",   REGISTER_ADDRESS|REGISTER_IP, RC_GENERAL,  dt_word, NULL,   0 },
  { "P",    0,                            RC_GENERAL,  dt_byte, P, 0x1|0x2|0x4|0x8|0x10|0x20|0x40|0x80 },
};

static bool inited;
static bool is_dll;

//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
int idaapi thread_read_registers(thread_id_t thread_id, regval_t *values, int count)
{
  int code = r_thread_read_registers(thread_id, values, count);

  return code;
}

//--------------------------------------------------------------------------
int idaapi thread_write_register(thread_id_t thread_id, int reg_idx, const regval_t *value)
{
  regval_t rv = *value;
  // FPU related registers

  return r_thread_write_register(thread_id, reg_idx, &rv);
}

//--------------------------------------------------------------------------
int is_valid_bpt(bpttype_t type, ea_t ea, int len)
{
  if ( type != BPT_SOFT )
  {
    if ( type != BPT_RDWR         // type is good?
      && type != BPT_WRITE
      && type != BPT_EXEC)
        return BPT_BAD_TYPE;

    if ( len != 1                 // length is good?
      && (type == BPT_EXEC        // remark: instruction hardware breakpoint only accepts the len of one byte
        || (len != 2 && len != 4)))
          return BPT_BAD_LEN;

    if ( (ea & (len-1)) != 0 )    // alignment is good?
      return BPT_BAD_ALIGN;
  }
  return BPT_OK;
}

