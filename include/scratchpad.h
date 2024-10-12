#ifndef SCRATCHPAD_H
#define SCRATCHPAD_H

#define SP_DRAW_INFO_POS (*(s32*)0x1F800000)

#define SP_PALETTE_ADDR 0x1F800028
#define SP_PALETTE (*(volatile u32**)SP_PALETTE_ADDR)

#endif