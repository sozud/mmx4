#ifndef MAIN_MENU_H
#define MAIN_MENU_H

struct MenuRuntimeData {
    struct MemcardSaveSlot save;
#ifdef MMX4_WIN32
    u8 pad2A[6];
#else
    u8 pad2A[2];
#endif
    u8 button_lookup[24];
    u16 low_button_masks[8];
    u16 high_button_masks[3];
    u16 sign_bit_mask;
};

void func_8001961C(struct EngineObj* arg0);

void func_8001A498(struct EngineObj* arg0);
void func_8001A710(struct EngineObj* arg0);
void func_8001A7D4(struct EngineObj* arg0);

#ifdef MMX4_PC
extern void func_800193D8 (struct EngineObj *arg0);
#endif

extern struct MenuRuntimeData D_800F1D90;

void func_8001B644(u8*);

void func_8001C4B4(struct MemcardMenuState*);
void func_8001C5A8(u8**);

void func_8001B718(s16, u8, u8);
void func_8001B7C0(s16 x, s16 y, u8 arg2);
void func_8001B8B0(s16 x, s16 y, u8 arg2);
void func_8001BCAC(s16 x, s16 y, u8 arg2);
void func_8001BE10(s16 x, s16 y, u8 arg2);

void func_8001C30C(struct MemcardSaveSlot*);
void func_8001C008(s32, s32);
void func_8001C07C(void);

void func_8001C3E8(void);

#endif
