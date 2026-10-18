#ifndef MAIN_MEMCARD_H
#define MAIN_MEMCARD_H

#ifdef MMX4_PC
extern void InitMemcards (void);
#endif

s32 func_8001CB24(u8* buffer, s32 device_num, s32 size);
s32 func_8001C8F4(u8* buffer, s32 device_num, s32 size);

void func_8001CC5C(s32 device_num, struct MemcardFileList* list, const char* pattern);
s32 func_8001CD70(s32 arg0);
int func_8001CDE4(int arg0);
s32 func_8001CE84(s32 device_num);

#endif
