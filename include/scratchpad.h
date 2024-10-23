#ifndef SCRATCHPAD_H
#define SCRATCHPAD_H

struct Scratchpad1C {
    s8 unk0[1];
    s8 pad[0xf];
    s32 unk10;
    s8 pad14[0x24 - 0x14];
    s32 unk24;
};

#define SP_DRAW_INFO_POS (*(s32*)0x1F800000)
#define SP_1C (*(struct Scratchpad1C**)0x1F80001C)
#define SP_PALETTE_ADDR 0x1F800028
#define SP_PALETTE (*(volatile u32**)SP_PALETTE_ADDR)

#endif