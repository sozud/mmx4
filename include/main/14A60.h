#ifndef MAIN_14A60_H
#define MAIN_14A60_H

#ifdef MMX4_PC
extern void func_80024E70 (void);

extern void func_800257BC (struct PlayerObj *arg0);
#endif

extern u8* const* D_800F2DD8[];
extern const u8* D_800F2DD0[];
extern u16 D_800F2F40[16];
extern const union AnimationStep* const* D_800F2EE8[];

void func_80025188(s32, u8);
void func_800253F0(struct MainObj*, s32);
void func_80025588(s16, s16, s16, s16, s32);

void func_80025CDC(void);

#endif
