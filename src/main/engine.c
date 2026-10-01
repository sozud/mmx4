// EngineObj
// 8001F118..8001FAFC
#include "common.h"

void func_80016F0C();

void func_8001F118(void)
{
    update_misc_objects();
    func_80021D20();
    func_8002A484();
    func_80023D68();
}

struct MiscObj* func_8001F150(struct EngineObj* arg0, u8 arg1)
{
    struct MiscObj* obj = find_free_misc_obj();

    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x2D;
        obj->unk2 = arg1;
    }
    return obj;
}

INCLUDE_ASM("main/nonmatchings/engine", func_8001F198);

INCLUDE_ASM("main/nonmatchings/engine", func_8001F2BC);

void func_8001F398(struct EngineObj* arg0)
{
    D_800F23B0[arg0->unk2](arg0);
}

void func_8001F3D4(struct MainObj* obj)
{
    s32 background_index;
    u32 i;

    *(s16*)&obj->state = 6;
    obj->on_screen = 0;
    obj->unk2++;
    background_index = ((s8*)&obj->unk42)[1];
    if (background_index == 0) {
        background_objects[0].x_pos.val = FIXED(512);
    } else {
        background_objects[background_index].x_pos.val = FIXED(256);
    }

    for (i = 0; i < 4; i++) {
        D_8013E188[i] = -1;
    }
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
}

INCLUDE_ASM("main/nonmatchings/engine", func_8001F488);

void func_8001F5D8(struct EngineObj* arg0)
{
    if (!(arg0->unk4 & 1)) {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    } else {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
    }
}

#ifdef MMX4_WIN32
void func_8001F634(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        if (arg0->character_state.bytes[2] == 0) {
            arg0->unk3 = 0;
            arg0->unk4 = 0x1E;
            arg0->unk2++;
            arg0->character_state.bytes[1] = 1;
        } else {
            arg0->unk2 = 4;
            arg0->unk3 = 0;
            arg0->unk4 = 0x78;
        }
    } else {
        func_8001F5D8(arg0);
    }
    need_palette_load |= 1;
}
#else
INCLUDE_ASM("main/nonmatchings/engine", func_8001F634);
#endif

INCLUDE_ASM("main/nonmatchings/engine", func_8001F6E8);

void func_8001F798(struct EngineObj* arg0)
{
    u8 a1;

    if (--arg0->unk4 == 0) {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->unk3 = 0;
        arg0->unk2++;

        if (arg0->cur_character != 0) {
            *(s16*)&arg0->unk6 = 0x46;
            a1 = 0;
        } else {
            *(s16*)&arg0->unk6 = 0x3C;
            a1 = 0;
        }

        arg0->unk4 = 0xF0;
        func_8001540C(5, a1, 0);
    } else {
        func_8001F5D8(arg0);
    }
    need_palette_load |= 1;
}

void func_8001F850(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        ((void (*)(arg_u16, u8, u8))func_8002217C)(arg0->character_state.bytes[0] + 0x10, 0x80, 0);
        arg0->unk2++;
    } else if (arg0->unk4 == 0xF0 - *(s16*)&arg0->unk6) {
        func_8001540C(5, (u8)arg0->character_state.bytes[0], 0);
    }
}

void func_8001F8DC(void)
{
    func_80016FB4(3);
}

s32 func_8001F8FC(struct GameInfo* arg0)
{
    if (--arg0->unk6 == 0) {
        func_80016F0C();
        return 0;
    }
    return 1;
}

void func_8001F93C(struct EngineObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk4 = 0x3C;
        arg0->unk2 = (u8)arg0->unk2 + 1;
    }
}

void func_8001F968(struct EngineObj* arg0)
{
    func_800129F0(8);
    arg0->unk1 = 2;
    arg0->unk2 = 0;
}

void func_8001F9A0(struct EngineObj* arg0)
{
    D_800F23B8[arg0->unk2](arg0);
}

void func_8001F9DC(struct EngineObj* arg0)
{
    if (*D_80141BDC == 0) {
        func_8001D134();
        arg0->unk2++;
    }
}

INCLUDE_ASM("main/nonmatchings/engine", func_8001FA24);

void func_8001FAC0(struct EngineObj* arg0)
{
    D_800F23D4[arg0->unk2](arg0);
}

extern void func_800164D8(void);

void (*D_800F23B0[2])(struct EngineObj*) = {
    func_8001F198,
    func_8001F2BC,
};

void (*D_800F23B8[7])(struct EngineObj*) = {
    func_8001F488,
    func_8001F634,
    func_8001F6E8,
    func_8001F798,
    func_8001F850,
    func_8001F93C,
    func_8001F968,
};

void (*D_800F23D4[2])(struct EngineObj*) = {
    func_8001F9DC,
    func_8001FA24,
};
