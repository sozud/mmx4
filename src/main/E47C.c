// 8001DC7C..8001F118
#include "common.h"

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
extern union TitleScratch D_80169498;
void func_80016F0C();
extern u8 D_80171EA9;
void func_800153D4(u8 arg0);

#ifdef VERSION_JP
u8 D_800F21F8[8] = { 0x00, 0x01, 0x04, 0x07, 0x09, 0x08, 0x00, 0x00 };

s16 D_800F2204[36] = {
    -176,
    -220,
    308,
    -220,
    374,
    -220,
    792,
    -220,
    -77,
    -143,
    176,
    -154,
    407,
    -176,
    -550,
    693,
    -143,
    627,
    -110,
    693,
    110,
    605,
    363,
    583,
    -22,
    693,
    484,
    693,
    11,
    187,
    220,
    0,
    275,
    242,
    66,
    429,
};

s16 D_800F224C[36] = {
    181,
    27,
    225,
    27,
    231,
    27,
    269,
    27,
    190,
    34,
    213,
    33,
    234,
    31,
    147,
    110,
    184,
    104,
    187,
    110,
    207,
    102,
    230,
    100,
    195,
    110,
    241,
    110,
    198,
    64,
    217,
    47,
    222,
    69,
    203,
    86,
};

extern void func_8001DF24_jp(struct GameInfo*);
extern void func_8001E194_jp(struct GameInfo*);

void (*D_800F2294[15])(struct GameInfo*) = {
    func_8001DCCC,
    func_8001E690,
    func_8001DDB0,
    func_8001DE20,
    func_8001DF24_jp,
    func_8001DE54,
    func_8001DF48,
    func_8001DF7C,
    func_8001E194_jp,
    func_8001E000,
    func_8001E130,
    func_8001E3FC,
    func_8001E54C,
    func_8001E638,
    func_8001E6BC,
};

#else
s16 D_800F21DC[14] = {
    0x8442,
    0x8C84,
    0x94C6,
    0x9908,
    0xA16B,
    0xA9AD,
    0xADEF,
    0xB631,
    0xBE73,
    0xC6D6,
    0xCB18,
    0xD35A,
    0xDB9C,
    0xE3FF,
};

#ifdef MMX4_WIN32
u8 D_800F21F8[] = { 0x12, 0x13, 0x00, 0x0b, 0x0c, 0x04, 0x06, 0x09 };
#else
u8 D_800F21F8[] = {
    0x12, 0x13, 0x00, 0x0b, 0x0c, 0x04, 0x07, 0x09, 0x11, 0, 0, 0
};
#endif

s16 D_800F2204[36] = {
    -154,
    -297,
    319,
    -297,
    429,
    -297,
    869,
    -297,
    -77,
    -187,
    176,
    -220,
    473,
    -242,
    -605,
    649,
    -220,
    605,
    -154,
    649,
    132,
    572,
    396,
    572,
    -11,
    649,
    473,
    649,
    11,
    154,
    231,
    -33,
    275,
    154,
    77,
    308,
};

s16 D_800F224C[36] = {
    169,
    26,
    212,
    26,
    222,
    26,
    262,
    26,
    176,
    36,
    199,
    33,
    229,
    31,
    128,
    112,
    163,
    108,
    169,
    112,
    195,
    105,
    219,
    105,
    182,
    112,
    226,
    112,
    184,
    67,
    204,
    50,
    208,
    67,
    190,
    81,
};

void (*D_800F2294[15])(struct GameInfo*) = {
    func_8001DCCC,
    func_8001E690,
    func_8001DDB0,
    func_8001DE20,
    func_8001DE54,
    func_8001DF48,
    func_8001DF7C,
    func_8001E000,
    func_8001E130,
    func_8001E3FC,
    func_8001E458,
    func_8001E4F0,
    func_8001E54C,
    func_8001E638,
    func_8001E6BC,
};

#endif

extern u8 D_800F22D0[16];
extern u8 D_800F22E0[16];
extern u8 D_800F22F0[16];
extern u8 D_800F2300[16];
extern u8 D_800F2310[12];
extern u8 D_800F231C[12];
extern u8 D_800F2328[16];
extern struct GameInfoAuxData D_800F2338;
extern RECT D_800F2388;
extern void (*D_800F2390[3])(struct GameInfo*);
extern void (*D_800F239C[5])(struct GameInfo*);
#ifdef VERSION_JP
extern u8 D_800F2474_jp[4];
#endif

#ifdef MMX4_PC
u8 direct_u8(const char* name);

static void apply_direct_progress(u8 stage, u8 character, u8 loadout, u8 story)
{
    engine_obj.unk5F = story;
    if (loadout != 1 && loadout != 2)
        return;
    engine_obj.unk44 = 4;
    engine_obj.unk45 = 0x30;
    engine_obj.unk46 = 0x30;
    engine_obj.palette_flags = 0xFF;
    if (loadout == 2 && stage >= 1 && stage <= 8)
        engine_obj.palette_flags &= (u8) ~(1 << (stage - 1));
    engine_obj.unk5A = 0xF0FF;
    engine_obj.unk5C[0] = 0xA0;
    engine_obj.unk5C[1] = 0xA0;
    engine_obj.unk5C[2] = 0x20;
    if (character == CHARACTER_X) {
        engine_obj.unk47 = 0x0F;
        engine_obj.unk48 = 2;
    }
}
#endif

void func_8001D064(void);

void func_8001D104(void);

void PlayCapcomLogo(void);

void func_8001D134(void);

void func_8001D178(struct GameInfo* arg0);

void func_8001D1A4(struct GameInfo* arg0);

void func_8001D1F0(struct GameInfo* arg0);

void func_8001D230(struct GameInfo* arg0);

void func_8001D284(struct GameInfo* arg0);

void func_8001D294(struct GameInfo* arg0);

void func_8001D2D0(struct GameInfo* arg0);

void func_8001D364(struct GameInfo* arg0);

void func_8001D460(struct GameInfo* arg0);

void func_8001D514(struct GameInfo* arg0);

void func_8001D57C(struct GameInfo* arg0);

void func_8001D5C8(struct GameInfo* arg0);

void func_8001D64C(struct GameInfo* arg0);

void func_8001D698(struct GameInfo* arg0);

void func_8001D6DC(struct GameInfo* arg0);

void func_8001D77C(struct GameInfo* arg0);

void func_8001D7D0(struct GameInfo* /* D_80173C70 */ arg0);

void func_8001D8DC(struct GameInfo* arg0);

void func_8001D9D0(struct GameInfo* arg0);

// never called?
void func_8001DA70(void);

// never called?
void func_8001DAA0(void);

void func_8001DAD0(struct GameInfo* arg0);

void func_8001DAF8(void);

void func_8001DC30(void);

struct QuadObj* func_8001DC7C(s8 arg0, s8 arg1)
{
    struct QuadObj* quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = arg0;
        quad->unk2 = arg1;
        return quad;
    }
    return NULL;
}

void func_8001DCCC(struct GameInfo* arg0)
{
    arg0->unkD = 2;
    arg0->unkA = 0;
    func_8001D134();
    reset_game_engine();
    engine_obj.stage = 0xE;
    engine_obj.substage = 0;
    func_80013014();
    func_800160AC();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    need_palette_load |= 1;
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 1;
    background_objects[2].unk3 = 0;
#ifdef VERSION_JP
    func_8001DC7C(0xB, 0);
    func_8001DC7C(0xB, 1);
    func_8001DC7C(0xB, 5);
    func_8001DC7C(0xB, 9);
#else
    D_80139690 = OBJECT_HEADER(func_8001DC7C(0xB, 0xA));
#endif
    func_800129A4(8);
    arg0->unk4 = 0;
    arg0->mode++;
}

void func_8001DDB0(struct GameInfo* arg0)
{
    if (arg0->unk4 == 0) {
        func_8001663C(MUSIC_TITLE, 0x7F);
        arg0->unk4 = 1;
    }
    if (D_80173C84 == 2) {
        arg0->unkD = 1;
#ifdef VERSION_JP
        D_80139690 = OBJECT_HEADER(func_8001DC7C(0xB, 2));
        func_8001DC7C(0xB, 3);
        func_8001DC7C(0xB, 4);
        arg0->unk4 = 0x3C;
#else
        arg0->unk4 = 0xA;
#endif
        arg0->mode++;
    }
}

void func_8001DE20(struct GameInfo* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
#ifdef VERSION_JP
        arg0->unkA = 1;
        arg0->unk4 = 0x46;
#else
        arg0->unkA = 2;
#endif
        arg0->mode++;
    }
}

extern s16 D_800F2204[];

#ifdef VERSION_JP
void func_8001DF24_jp(struct GameInfo* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
        arg0->unkA = 2;
        arg0->mode++;
    }
    if (background_objects[1].x_pos.i.hi >= 10) {
        background_objects[1].x_pos.i.hi -= 9;
    }
}
#endif
void func_8001DE54(struct GameInfo* arg0)
{
    s16 var_a2;
    s16* var_a1;
    s32* var_a0;
    struct MiscObj* temp_v0;
#ifdef VERSION_JP
    struct MiscObj* first;
#else
    s32 saved_reg_s2;
#endif

    background_objects[1].x_pos.i.hi = 0x400;
    background_objects[1].unk4C = 1;
    if (D_80139690->state == 2) {
#ifdef VERSION_JP
        first = find_free_misc_obj();
        if (first != NULL) {
            first->id = 0x13;
            first->active = 1;
            first->unk2 = 0xA;
        }
#endif
        temp_v0 = find_free_misc_obj();
        if (temp_v0 != 0) {
            temp_v0->active = 1;
            temp_v0->id = 0x1D;
            temp_v0->unk2 = 0x20;
#ifdef VERSION_JP
            temp_v0->ext.unk.unk50 = (struct MiscUnk50_2*)first;
#else
            temp_v0->ext.unk.unk50 = (struct MiscUnk50_2*)saved_reg_s2;
#endif
            D_80139690 = OBJECT_HEADER(temp_v0);
        }
        var_a1 = D_800F2204;
        var_a0 = D_80169498.sector;
        var_a2 = 0;
        do {
            *var_a0 = (*var_a1) << 0x10;
            var_a0++;
            var_a1 += 1;
            var_a2 += 1;
        } while (var_a2 < 0x24);
        D_80169498.title.settled = 1;
        background_objects[0].unk3 = 1;
        arg0->mode++;
    }
}

void func_8001DF48(struct GameInfo* arg0)
{
    if (D_80139690->id == 0x13) {
#ifdef VERSION_JP
        ZeroObjectState(OBJECT_HEADER(((struct MiscObj*)D_80139690)->ext.pointer.unk50));
#endif
#ifdef VERSION_EU
        arg0->unk4 = 0x14;
#else
        arg0->unk4 = 0x32;
#endif
        arg0->mode++;
    }
}

void func_8001DF7C(struct GameInfo* arg0)
{
    struct EffectObj* obj;

    if (--arg0->unk4 == 0) {
        obj = find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 2;
            obj->unk2 = 0xC;
            D_80139690 = OBJECT_HEADER(obj);
        }
#ifdef VERSION_EU
        arg0->unk4 = 0;
#else
        arg0->unk4 = 0xA;
#endif
        arg0->mode++;
    }
#ifdef VERSION_JP
    background_objects[0].x_pos.i.hi += 6;
#endif
}
#ifdef VERSION_JP
void func_8001E194_jp(struct GameInfo* arg0)
{
    if (--arg0->unk4 == 0) {
        arg0->mode++;
    }
}
#endif
void func_8001E000(struct GameInfo* arg0)
{
#ifndef VERSION_JP
    if (arg0->unk4 != 0) {
        arg0->unk4--;
        return;
    }
#endif
    if (D_80139690->active == 0) {
        g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0;
        D_8013E188[0] = 0;
        D_8013E188[1] = 0;
        D_8013E188[2] = 0;
        D_8013E188[3] = 0;
        need_palette_load |= 1;
        func_8001DC7C(0xC, 0);
        func_8001DC7C(0xC, 1);
        func_8001DC7C(0xC, 2);
        func_8001DC7C(0xC, 3);
        func_8001DC7C(0xC, 4);
        func_8001DC7C(0xC, 5);
        func_8001DC7C(0xC, 6);
        func_8001DC7C(0xC, 7);
        func_8001DC7C(0xC, 8);
        arg0->unk6 = 0x3C;
        background_objects[0].unk3 = 0;
        arg0->unkA = 0;
        arg0->mode++;
    }
#ifdef VERSION_JP
    background_objects[0].x_pos.i.hi += 11;
#endif
}

INCLUDE_ASM("main/nonmatchings/E47C", func_8001E130);
void func_8001E3FC(struct GameInfo* arg0)
{
    if (D_80139690->active == 0) {
#ifdef VERSION_JP
        arg0->unk4 = 6;
#else
        arg0->unk4 = 0x10;
        arg0->unk6 = 0;
#endif
        arg0->mode++;
#ifndef VERSION_JP
        SP_PALETTE[0x306 / 2] = 0x8000;
        need_palette_load |= 1;
#endif
    }
}
#ifndef VERSION_JP
void func_8001E458(struct GameInfo* arg0)
{
    s16 temp_a1;

    if (--arg0->unk4 == 0) {
        temp_a1 = arg0->unk6;
        if (temp_a1 != 0xE) {
            arg0->unk6++;
            SP_PALETTE[0x106 / 2] = D_800F21DC[temp_a1];
            arg0->unk4 = 6;
            need_palette_load |= 1;
            return;
        }
        arg0->unk4 = 1;
        arg0->mode++;
    }
}
#endif
#ifndef VERSION_JP
void func_8001E4F0(struct GameInfo* arg0)
{
    if (--arg0->unk4 == 0) {
        reset_objects();
        arg0->unk4 = 1;
        arg0->mode++;
    }
}
#endif
void func_8001E54C(struct GameInfo* /* D_80173C70 */ arg0)
{
    u32 var_s0;
    struct BaseObj* obj;

    if (--arg0->unk4 == 0) {
        obj = (struct BaseObj*)find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 2;
            obj->unk2 = 0xD;
        }
        for (var_s0 = 0;
#ifdef VERSION_JP
             var_s0 < 5;
#elif defined(MMX4_WIN32)
             var_s0 < 8;
#else
             var_s0 < 9;
#endif
             var_s0++) {
            obj = (struct BaseObj*)find_free_misc_obj();
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 0x13;
                obj->unk2 = D_800F21F8[var_s0];
            }
        }
#ifdef VERSION_EU
        arg0->unk4 = 0x5DC;
#else
        arg0->unk4 = 0x258;
#endif
        arg0->mode++;
        background_objects[2].unk3 = 1;
        arg0->unkD = 0;
    }
}

void func_8001E638(struct GameInfo* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
        func_800129F0(8);
        arg0->mode++;
    }
}

void func_8001E690(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active == 0) {
        arg0->mode++;
    }
}

void func_8001E6BC(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active == 0) {
        arg0->unkD = 1;
        func_8001D134();
        arg0->mode = 0;
        arg0->unk0++;
    }
}

void func_8001E708(struct GameInfo* arg0)
{
    D_800F2294[arg0->mode](arg0);
    if (controller_input.pressed & PADstart && arg0->unkD == 1) {
        func_80016F0C();
        func_8001540C(0, 0x22, 0);
        arg0->mode = 0xC;
        g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0;
        D_8013E188[0] = 0;
        D_8013E188[1] = 0;
        D_8013E188[2] = 0;
        D_8013E188[3] = 0;
        background_objects[0].unk3 = 0;
        background_objects[1].unk3 = 1;
        background_objects[2].unk3 = 0;
        need_palette_load |= 1;
        reset_objects();
        background_objects[1].x_pos.i.hi = 0x400;
        background_objects[1].unk4C = 1;
        arg0->unk4 = 1;
    }
    update_effect_objects();
    update_misc_objects();
    update_quad_objects();
    func_8002A484();
    func_80023D68();
}

u8 func_8001E850(u8* arg0, u8 arg1)
{
    s8 counter = 0;
    struct MiscObj* misc;

    if (arg0[0] != 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 1;
            misc->id = 0x20;
            misc->ext.pointer.unk50 = arg0;
            misc->x_pos.i.hi = arg0[0];
            arg0++;
            misc->ext.title_logo.palette_shift_value = arg1;
        }
    } else {
        arg0++;
    }

    while (arg0[0] != 0xFF) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 1;
            misc->id = 0x1F;
            misc->unk2 = arg0[0];
            arg0++;
            misc->unk7 = counter++;
#ifdef VERSION_JP
            misc->y_pos.i.hi = arg0[0];
#else
            misc->y_pos.i.hi = arg0[0] & 0xF0;
#endif
            misc->ext.title_logo.palette_shift_value = arg1;
            arg0++;
        }
    }
    return arg0[1];
}

void func_8001E954(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active == 0) {
        arg0->mode++;
    }
}

void func_8001E980(u8 arg0)
{
    if (arg0 == 0) {
        LoadImage(&D_800F2388,
            (u_long*)(WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[1]));
    } else {
        need_palette_load |= 1;
    }
}

void func_8001E9E0(struct GameInfo* arg0)
{
    struct MiscObj* obj;

    reset_objects();
    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 1;
        obj->id = 0x1F;
        obj->unk2 = 0x56;
        obj->y_pos.i.hi = 0x80;
    }
    main_bss_state.transition.selection = 0;
    arg0->unk8 = func_8001E850(D_800F22F0, 0) & 0xFF;
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 0;
    background_objects[2].unk3 = 0;
    func_8001E980(0);
    func_800129A4(8);
    arg0->mode++;
}

void func_8001EA90(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active == 0) {
        if (controller_input.pressed & (PADstart | PAD_SELECTION_ALT)) {
            func_800129F0(8);
            main_bss_state.transition.selection = 2;
            arg0->mode++;
            return;
        }
        if ((controller_input.pressed & PAD_CONFIRM) && main_bss_state.transition.selection != 1) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->mode++;
            return;
        }
        func_800204CC((s8*)&main_bss_state.transition.selection, arg0->unk8);
        if ((controller_input.pressed & (PADLleft | PADLright | PAD_CONFIRM)) && main_bss_state.transition.selection == 1) {
            func_8001540C(0, 0xC, 0);
            D_80171EA9 ^= 1;
            func_800153D4(D_80171EA9);
        }
    }
}

void func_8001EBA0(struct GameInfo* info)
{
    if (main_bss_state.transition.active != 0) {
        return;
    }
    if (main_bss_state.transition.selection == 0) {
        info->unk0 = 0xA;
        info->mode = 0;
        info->unk2 = 0;
        info->unk3 = 0;
        return;
    }

    func_8001E980(1);
    background_objects[0].unk4C = 1;
    background_objects[1].unk4C = 1;
    background_objects[2].unk4C = 1;
    background_objects[1].unk3 = 1;
    background_objects[2].unk3 = 1;
    background_objects[2].x_pos.i.hi = 0;
    info->unk0 = 6;
    info->mode = 0;
    info->unk2 = 0;
    info->unk3 = 0;
}
void func_8001EC34(struct GameInfo* arg0)
{
    D_800F2390[arg0->mode](arg0);
    update_misc_objects();
    func_8002A484();
    func_80016124();
    func_80023D68();
}

void func_8001EC90(struct GameInfo* arg0)
{
    reset_objects();
    main_bss_state.transition.selection = 0;
    if (D_800F1D90.save.character != 0xFF) {
        arg0->unk8 = func_8001E850(D_800F22D0, 0) & 0xFF;
        arg0->mode = arg0->mode + 1;
    } else {
        arg0->unk8 = func_8001E850(D_800F22E0, 0) & 0xFF;
        arg0->mode = arg0->mode + 3;
    }
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 0;
    background_objects[2].unk3 = 0;
    func_8001E980(0);
    func_800129A4(8);
}

void func_8001ED44(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active == 0) {
        if (controller_input.pressed & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            if (main_bss_state.transition.selection != 1) {
                func_800129F0(8);
            }
            arg0->mode = (u8)arg0->mode + 1;
        } else if (controller_input.pressed & PAD_SELECTION_ALT) {
            func_800129F0(8);
            main_bss_state.transition.selection = 2;
            arg0->mode = (u8)arg0->mode + 1;
        } else {
            func_800204CC((s8*)&main_bss_state.transition.selection, arg0->unk8);
        }
    }
}

void func_8001EE08(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active == 0) {
        if (main_bss_state.transition.selection != 1) {
            func_8001E980(1);
        }
        {
            s32 state = main_bss_state.transition.selection;

            if (state != 1) {
                if (state < 2) {
                    if (state == 0) {
                        func_8001C30C(&D_800F1D90.save);
                        engine_obj.state = 1;
                        engine_obj.unk1 = 6;
                        engine_obj.unk2 = 0;
                        engine_obj.unk3 = 0;
                        func_80012740(1, &func_8001FB50);
                        func_800127FC();
                        return;
                    }
                }
            } else {
                arg0->unk0 = 9;
                engine_obj.unk1 = 0;
                engine_obj.unk2 = 0;
                engine_obj.unk3 = 0;
                return;
            }
            background_objects[2].x_pos.i.hi = 0;
            background_objects[0].unk4C = 1;
            background_objects[1].unk4C = 1;
            background_objects[2].unk4C = 1;
            background_objects[1].unk3 = 1;
            background_objects[2].unk3 = 1;
            arg0->unk0 = 6;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        }
    }
}

void func_8001EF48(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active != 0) {
        return;
    }

    if (controller_input.pressed & PAD_CONFIRM) {
        func_8001540C(0, 0x22, 0);
        if (main_bss_state.transition.selection != 0) {
            func_800129F0(8);
        }
    } else if (controller_input.pressed & PAD_SELECTION_ALT) {
        func_800129F0(8);
        main_bss_state.transition.selection = 2;
    } else {
        return;
    }

    arg0->mode++;
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/E47C", func_8001EFF0);
#else
void func_8001EFF0(struct GameInfo* arg0)
{
    struct TransitionState* transition;

    transition = &main_bss_state.transition;
    if (main_bss_state.transition.active == 0) {
        if ((transition->selection == 0) || (func_8001E980(1), main_bss_state.transition.selection == 0)) {
            arg0->unk0 = 9;
            engine_obj.unk1 = 0;
            engine_obj.unk2 = 0;
            engine_obj.unk3 = 0;
        } else {
            background_objects[2].x_pos.i.hi = 0;
            background_objects[0].unk4C = 1;
            background_objects[1].unk4C = 1;
            background_objects[2].unk4C = 1;
            background_objects[1].unk3 = 1;
            background_objects[2].unk3 = 1;
            arg0->unk0 = 6;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        }
    }
}
#endif

void func_8001F0BC(struct GameInfo* arg0)
{
    D_800F239C[arg0->mode](arg0);
    update_misc_objects();
    func_8002A484();
    func_80016124();
    func_80023D68();
}
