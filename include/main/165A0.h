#ifndef MAIN_165A0_H
#define MAIN_165A0_H

// D_800F2FE0
extern void (*D_800F2FE0[])(struct EngineObj*);

// D_800F30C8
extern void (*D_800F30C8[])(struct MiscObj*);

#ifdef MMX4_PC
extern void func_80025DA0 (s32 texture_depth, s32 blend_mode);
extern void func_80026118 (void);

extern void func_80026894 (s32 arg0);
#endif

extern s16 D_800F2FDC[2];

void func_800261B4(s32);

void func_80026648();

#endif
