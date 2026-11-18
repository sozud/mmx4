#ifndef MAIN_MISC_MISC_03_DEBRIS_H
#define MAIN_MISC_MISC_03_DEBRIS_H

void debris_update(struct MiscObj* arg0);

void spawn_owner_debris(s32 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4, s32 arg5);
void spawn_debris_offset(u8 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4);
void func_800C842C(u8, u8*, void*, s32, void*);

#endif
