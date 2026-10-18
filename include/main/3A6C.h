#ifndef MAIN_3A6C_H
#define MAIN_3A6C_H

struct Prim {
    u16 x;
    u16 y;
    s8 uv;
    u8 w;
    u8 h;
    s8 clut;
}; // size 0x8

#ifdef MMX4_PC
extern void func_8001326C (u8 arg0);
extern void func_80013404 (u8 arg0);
#endif

extern struct Prim D_800EE504[];

void func_80013530(void);

#endif
