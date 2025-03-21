//--------------------------------------------------------------------------------
// Auto-generated by Migen (9a0be7a) & LiteX (dc4c190) on 2022-11-27 23:51:55
//--------------------------------------------------------------------------------
#ifndef __GENERATED_MEM_H
#define __GENERATED_MEM_H

#ifndef VEXRISCV_DEBUG_BASE
#define VEXRISCV_DEBUG_BASE 0xf00f0000L
#define VEXRISCV_DEBUG_SIZE 0x00000100
#endif

#ifndef SRAM_BASE
#define SRAM_BASE 0x00000000L
#define SRAM_SIZE 0x00000800
#endif

#ifndef FLASH_BASE
#define FLASH_BASE 0x10000000L
#define FLASH_SIZE 0x01000000
#endif

#ifndef MPRJ_BASE
#define MPRJ_BASE 0x30000000L
#define MPRJ_SIZE 0x10000000
#endif

#ifndef HK_BASE
#define HK_BASE 0x26000000L
#define HK_SIZE 0x00300000
#endif

#ifndef CSR_BASE
#define CSR_BASE 0xf0000000L
#define CSR_SIZE 0x00010000
#endif

#ifndef MEM_REGIONS
#define MEM_REGIONS                                                                                                    \
  "VEXRISCV_DEBUG  0xf00f0000 0x100 \nSRAM      0x00000000 0x800 \nFLASH     0x10000000 0x1000000 \nMPRJ      "        \
  "0x30000000 0x10000000 \nHK        0x26000000 0x300000 \nCSR       0xf0000000 0x10000 "
#endif
#endif
