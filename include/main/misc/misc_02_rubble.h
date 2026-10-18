#ifndef MAIN_MISC_MISC_02_RUBBLE_H
#define MAIN_MISC_MISC_02_RUBBLE_H

void rubble_update(struct MiscObj* arg0);
void func_800C7F1C(struct MiscObj*);

void spawn_owner_debris(s32 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4, s32 arg5);
void spawn_debris_offset(u8 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4);

void spawn_rubble(arg_u8, u8*, void*, s32);

void func_800C842C(s32, u8*, void*, s32, void*);

#endif
