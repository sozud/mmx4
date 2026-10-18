#ifndef MAIN_1CF60_H
#define MAIN_1CF60_H

void func_8002C808(struct PlayerObj* arg0);

#ifdef MMX4_PC
extern u8 func_8002D8B8 (struct PlayerObj *arg0);
extern u8 func_8002D94C (struct PlayerObj *arg0);

extern void func_8002C760 (struct PlayerObj *arg0);

extern void func_8002C954 (struct PlayerObj *arg0);

extern void func_8002CDD4 (struct PlayerObj *arg0);
#endif

s32 func_8002D180(struct PlayerObj*, s16, s16, s32);

s32 func_8002CF98(struct PlayerObj*, u8, s16, s16);
s32 func_8002D32C(struct PlayerObj*, s16, s32);
s32 func_8002D5E4(struct PlayerObj*, s16);
u8 func_8002D724(struct PlayerObj*, s16, s16);

u8 func_8002D900(struct PlayerObj*);
u8 func_8002D994(struct PlayerObj*);

s32 func_8002D25C(struct PlayerObj* arg0);
s32 func_8002D490(struct PlayerObj* arg0);

#endif
