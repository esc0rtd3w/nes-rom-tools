#define MEMORY_PAGE_SIZE 0x200
#define BPT_CODE         { 0xCC }
#define FPU_REGS_COUNT 0        // number of FPU registers
#define MAX_BPT 9               // maximal number of hardware breakpoints

enum register_class_m6502_t
{
  RC_GENERAL          = 0x01,
};

enum register_m6502_t
{
  R_A,
  R_X,
  R_Y,
  R_SP,
  R_PC,
  R_P,
};


