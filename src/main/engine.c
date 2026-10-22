// EngineObj
// 8001F118..8001FAFC
#include "common.h"
#include "main/55C4.h"
#include "main/engine.h"
#include "main/objects.h"
#include "main/128C4.h"
#include "main/144A4.h"
#include "main/1A5BC.h"
#include "main/2824.h"
#include "main/game_info.h"
#include "main/object_update.h"

#ifdef MMX4_PC
#include "main/323C.h"
#include "main/background.h"
#include "main/stage_objects.h"
#include "main/xa_sequence_data.h"
#endif

// D_800F23B0
extern void (*D_800F23B0[])(struct EngineObj*);

// D_800F23B8
extern void (*D_800F23B8[])(struct EngineObj*);

// D_800F23D4
extern void (*D_800F23D4[])(struct EngineObj*);

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

#ifdef MMX4_PC
void func_8001F198(struct EngineObj* arg0);
void func_8001F2BC(struct EngineObj* arg0);
void func_8001F488(struct EngineObj* arg0);
void func_8001F634(struct EngineObj* arg0);
void func_8001F6E8(struct EngineObj* arg0);
void func_8001FA24(struct EngineObj* arg0);
extern s32 D_801396B8;
extern s32 D_801396BC;
extern struct MiscObj* D_801396C0;
extern struct MiscObj* D_801396C4;
void func_8001F3D4(struct MainObj*);
void func_8001F5D8(struct EngineObj*);
#endif

#ifdef MMX4_PC
void func_8001F198(struct EngineObj* arg0)
{
    s32* dst;
    s32* src;
    u8 stage;
    u32 i;

    for (i = 0; i < 0x10; i++)
        arg0->character_state.bytes[i] = 0;
    stage = arg0->stage;
    arg0->character_state.bytes[2] = 0;
    arg0->character_state.bytes[1] = 0;
    arg0->stage = 0xF;
    arg0->substage = 0;
    arg0->checkpoint = 0;
    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    arg0->character_state.bytes[0] = stage;
    func_80013014();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    arg0->unkE = 0;
    arg0->unk2 = 1;
    arg0->unk3 = 0;
    D_801396B8 = 0;
    D_801396BC = 0;
    if (arg0->cur_character != 0)
        return;
    src = SP_ARC_30 + (arg0->character_state.bytes[0] - 1) * 0x30;
    dst = SP_PALETTE_WORDS + 0xAE0 / 4;
    for (i = 0; i < 0x30; i++)
        *dst++ = *src++;
    need_palette_load |= 1;
}
#else
INCLUDE_ASM("main/nonmatchings/engine", func_8001F198);
#endif

#ifdef MMX4_PC
void func_8001F2BC(struct EngineObj* arg0)
{
    u8 index;

    func_800129A4(8);
    func_8001663C(MUSIC_WEAPON_GET, 0x70);
    arg0->unk2 = 0;
    arg0->unk1++;
    if (arg0->cur_character == 0) {
        D_801396B8 = 0x100000;
        background_objects[0].x_pos.val = 0;
    } else {
        D_801396B8 = 0xFFF00000;
        background_objects[1].x_pos.val = 0x3000000;
    }
    D_801396C0 = func_8001F150(arg0, arg0->cur_character != 0 ? 9 : 0);
    index = arg0->character_state.bytes[0];
    if (arg0->cur_character != 0)
        index += 9;
    D_801396C4 = func_8001F150(arg0, index);
}
#else
INCLUDE_ASM("main/nonmatchings/engine", func_8001F2BC);
#endif

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
    background_index = ((struct EngineObj*)obj)->cur_character;
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

#ifdef MMX4_PC
void func_8001F488(struct EngineObj* arg0)
{
    struct BackgroundObj* background;

    if (controller_input.pressed & 0x8FF) {
        func_8001F3D4((struct MainObj*)arg0);
        background_objects[arg0->cur_character].unk4C = 1;
        arg0->character_state.bytes[2] = 1;
        arg0->character_state.bytes[1] = 1;
        D_801396C0->state = 1;
        D_801396C4->state = 1;
        D_801396C0->unk5 = 4;
        D_801396C4->unk5 = 4;
        return;
    }
    background = &background_objects[arg0->cur_character];
    background->x_pos.val += D_801396B8;
    if (arg0->cur_character == 0) {
        if (background->x_pos.val <= 0x2000000)
            return;
    } else if (background->x_pos.val > 0xFFFFFF) {
        return;
    }
    func_8001F3D4((struct MainObj*)arg0);
}
#else
INCLUDE_ASM("main/nonmatchings/engine", func_8001F488);
#endif

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
#ifdef MMX4_PC
void func_8001F634(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        if (arg0->character_state.bytes[2] == 0) {
            arg0->unk4 = 0x1E;
            arg0->unk3 = 0;
            arg0->character_state.bytes[1] = 1;
            arg0->unk2++;
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
#endif

#ifdef MMX4_PC
void func_8001F6E8(struct EngineObj* arg0)
{
    if (D_801396C0->unk5 != 2 || D_801396C4->unk5 != 2) {
        if (!(controller_input.pressed & 0x8FF))
            return;
        D_801396C0->state = 1;
        D_801396C4->state = 1;
        D_801396C0->unk5 = 4;
        D_801396C4->unk5 = 4;
    }
    arg0->unk3 = 0;
    arg0->unk4 = 6;
    arg0->unk2++;
}
#else
INCLUDE_ASM("main/nonmatchings/engine", func_8001F6E8);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/engine", func_8001F798);
#else
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
#endif

void func_8001F850(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        func_8002217C(arg0->character_state.bytes[0] + 0x10, 0x80, 0);
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
    if (main_bss_state.transition.active == 0) {
        func_8001D134();
        arg0->unk2++;
    }
}

#ifdef MMX4_PC
void func_8001FA24(struct EngineObj* arg0)
{
    u8 flags;
    u32 i;

    flags = arg0->palette_flags | (1 << (arg0->character_state.bytes[0] - 1));
    arg0->palette_flags = flags;
    if ((u8)g_Player.boss_flags != 0xFF && flags == 0xFF)
        arg0->unk5F = 5;
    g_Player.boss_flags |= 1 << (arg0->character_state.bytes[0] - 1);
    arg0->state = 9;
    arg0->unk1 = 0;
    arg0->unk2 = 0;
    for (i = 0; i < 0x10; i++)
        arg0->character_state.bytes[i] = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/engine", func_8001FA24);
#endif

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
