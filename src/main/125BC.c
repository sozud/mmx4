// 80021DBC..8002771C
#include "common.h"

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
void func_80016F0C();
extern u8 D_800F2B5C[21][12];
extern u8 D_800F2C58[];
extern u8 D_800F2D18[];
extern u32 D_800F2F08[12];
extern u32 D_800F2F38[2];
extern u32 D_800F2F60[];
extern union AnimationStep D_800F3000[10];
extern union AnimationStep D_800F3028[11];
extern union AnimationStep D_800F3054[10];
extern union AnimationStep* D_800F307C[3];
extern s16 D_800F3088[16];
extern s16 D_800F30A8[16];
extern struct HudSpriteOrigin D_800F30F4[8];
extern struct PlayerGaugePosition D_800F3124[2];

void func_80021DBC(s16* arg0, s16* arg1, s32 arg2)
{
    struct FixedMatrix2* matrix;
    s16 x;
    s16 y;
    s32 product0;
    s32 product1;
    s32 product2;
    s32 product3;

    matrix = &D_800F2ADC[arg2 & 0xFF];
    x = *arg0;
    y = *arg1;
    product0 = x * matrix->m00;
    product1 = y * matrix->m01;
    product2 = x * matrix->m10;
    product3 = y * matrix->m11;
    *arg0 = (product0 >> 8) + (product1 >> 8);
    *arg1 = (product2 >> 8) + (product3 >> 8);
}

void func_80021E3C(void)
{
    engine_obj.cur_character = D_801F604F;
    engine_obj.stage = D_801F6018;
    engine_obj.substage = D_801F6019;
}

#ifdef MMX4_PC
struct SerializedEngineObj {
    s8 state, unk1, unk2, unk3;
    s16 unk4;
    s8 unk6, unk7;
    s16 unk8, unkA;
    s8 stage, substage, unkE, unkF;
    s8 unk10, unk11, unk12, unk13;
    s8 unk14, unk15, unk16, unk17;
    s8 unk18, unk19, unk1A, unk1B;
    s8 unk1C, checkpoint, unk1E, unk1F;
    u32 boss_ptr;
    s8 enable_boss, unk25;
    union EngineCharacterState character_state;
    s8 unk36, unk37;
    u32 unk38, unk3C;
    u8 unk40;
    s8 unk41;
    u8 unk42;
    s8 cur_character, unk44;
    u8 unk45;
    s8 unk46, unk47, unk48;
    s8 player_initial_data[0x10];
    s8 palette_flags;
    u16 unk5A;
    s8 pad5C[3];
    u8 unk5F, unk60;
    u8 pad61[3];
};

_Static_assert(sizeof(struct SerializedEngineObj) == 0x64,
    "replay engine state must use the PSX layout");

struct ReplayData {
    u32 frame;
    s32 flags;
    u16 random;
    u16 padA;
    struct SerializedEngineObj initial_engine;
    struct SerializedEngineObj saved_engine;
    u16 inputs[0xE10];
};

static struct EngineObj replay_saved_engine;
#define REPLAY_SAVED_ENGINE replay_saved_engine

#define PSX_MAIN_OBJECTS_ADDRESS 0x8013BED0
#define PSX_MAIN_OBJ_SIZE 0x9C

static struct MainObj* restore_replay_main_object(u32 address)
{
    u32 offset;

    if (address < PSX_MAIN_OBJECTS_ADDRESS) {
        return NULL;
    }
    offset = address - PSX_MAIN_OBJECTS_ADDRESS;
    if ((offset % PSX_MAIN_OBJ_SIZE) != 0 || (offset / PSX_MAIN_OBJ_SIZE) >= COUNT(main_objects)) {
        return NULL;
    }
    return &main_objects[offset / PSX_MAIN_OBJ_SIZE];
}

static u32 save_replay_main_object(struct MainObj* object)
{
    if (object < &main_objects[0] || object >= &main_objects[COUNT(main_objects)]) {
        return 0;
    }
    return PSX_MAIN_OBJECTS_ADDRESS + (object - &main_objects[0]) * PSX_MAIN_OBJ_SIZE;
}

static void restore_replay_engine(const struct SerializedEngineObj* source)
{
    struct EngineObj restored = { 0 };
    s32 i;

    restored.state = source->state;
    restored.unk1 = source->unk1;
    restored.unk2 = source->unk2;
    restored.unk3 = source->unk3;
    restored.unk4 = source->unk4;
    restored.unk6 = source->unk6;
    restored.unk7 = source->unk7;
    restored.unk8 = source->unk8;
    restored.unkA = source->unkA;
    restored.stage = source->stage;
    restored.substage = source->substage;
    restored.unkE = source->unkE;
    restored.unkF = source->unkF;
    restored.unk10 = source->unk10;
    restored.unk11 = source->unk11;
    restored.unk12 = source->unk12;
    restored.unk13 = source->unk13;
    restored.unk14 = source->unk14;
    restored.unk15 = source->unk15;
    restored.unk16 = source->unk16;
    restored.unk17 = source->unk17;
    restored.unk18 = source->unk18;
    restored.unk19 = source->unk19;
    restored.unk1A = source->unk1A;
    restored.unk1B = source->unk1B;
    restored.unk1C = source->unk1C;
    restored.checkpoint = source->checkpoint;
    restored.unk1E = source->unk1E;
    restored.unk1F = source->unk1F;
    restored.boss_ptr = restore_replay_main_object(source->boss_ptr);
    restored.enable_boss = source->enable_boss;
    restored.unk25 = source->unk25;
    restored.character_state = source->character_state;
    restored.unk36.value = source->unk36;
    restored.unk37 = source->unk37;
    // unk38 and 38 are baked psx pointers. these are left uninitialized.
    // they get set in engine stage 5
    restored.unk40 = source->unk40;
    restored.unk41 = source->unk41;
    restored.unk42 = source->unk42;
    restored.cur_character = source->cur_character;
    restored.unk44 = source->unk44;
    restored.unk45 = source->unk45;
    restored.unk46 = source->unk46;
    restored.unk47 = source->unk47;
    restored.unk48 = source->unk48;
    for (i = 0; i < COUNT(restored.player_initial_data); i++) {
        restored.player_initial_data[i] = source->player_initial_data[i];
    }
    restored.palette_flags = source->palette_flags;
    restored.unk5A = source->unk5A;
    restored.unk5C[0] = source->pad5C[0];
    restored.unk5C[1] = source->pad5C[1];
    restored.unk5C[2] = source->pad5C[2];
    restored.unk5F = source->unk5F;
    restored.unk60 = source->unk60;
    restored.pad61[0] = source->pad61[0];
    restored.pad61[1] = source->pad61[1];
    restored.pad61[2] = source->pad61[2];
    engine_obj = restored;
}

static void save_replay_engine(struct SerializedEngineObj* target)
{
    s32 i;

    target->state = engine_obj.state;
    target->unk1 = engine_obj.unk1;
    target->unk2 = engine_obj.unk2;
    target->unk3 = engine_obj.unk3;
    target->unk4 = engine_obj.unk4;
    target->unk6 = engine_obj.unk6;
    target->unk7 = engine_obj.unk7;
    target->unk8 = engine_obj.unk8;
    target->unkA = engine_obj.unkA;
    target->stage = engine_obj.stage;
    target->substage = engine_obj.substage;
    target->unkE = engine_obj.unkE;
    target->unkF = engine_obj.unkF;
    target->unk10 = engine_obj.unk10;
    target->unk11 = engine_obj.unk11;
    target->unk12 = engine_obj.unk12;
    target->unk13 = engine_obj.unk13;
    target->unk14 = engine_obj.unk14;
    target->unk15 = engine_obj.unk15;
    target->unk16 = engine_obj.unk16;
    target->unk17 = engine_obj.unk17;
    target->unk18 = engine_obj.unk18;
    target->unk19 = engine_obj.unk19;
    target->unk1A = engine_obj.unk1A;
    target->unk1B = engine_obj.unk1B;
    target->unk1C = engine_obj.unk1C;
    target->checkpoint = engine_obj.checkpoint;
    target->unk1E = engine_obj.unk1E;
    target->unk1F = engine_obj.unk1F;
    target->boss_ptr = save_replay_main_object(engine_obj.boss_ptr);
    target->enable_boss = engine_obj.enable_boss;
    target->unk25 = engine_obj.unk25;
    target->character_state = engine_obj.character_state;
    target->unk36 = engine_obj.unk36.value;
    target->unk37 = engine_obj.unk37;
    target->unk40 = engine_obj.unk40;
    target->unk41 = engine_obj.unk41;
    target->unk42 = engine_obj.unk42;
    target->cur_character = engine_obj.cur_character;
    target->unk44 = engine_obj.unk44;
    target->unk45 = engine_obj.unk45;
    target->unk46 = engine_obj.unk46;
    target->unk47 = engine_obj.unk47;
    target->unk48 = engine_obj.unk48;
    for (i = 0; i < COUNT(engine_obj.player_initial_data); i++) {
        target->player_initial_data[i] = engine_obj.player_initial_data[i];
    }
    target->palette_flags = engine_obj.palette_flags;
    target->unk5A = engine_obj.unk5A;
    target->pad5C[0] = engine_obj.unk5C[0];
    target->pad5C[1] = engine_obj.unk5C[1];
    target->pad5C[2] = engine_obj.unk5C[2];
    target->unk5F = engine_obj.unk5F;
    target->unk60 = engine_obj.unk60;
    target->pad61[0] = engine_obj.pad61[0];
    target->pad61[1] = engine_obj.pad61[1];
    target->pad61[2] = engine_obj.pad61[2];
}
#else
struct ReplayData {
    u32 frame;
    s32 flags;
    u16 random;
    u16 padA;
    struct EngineObj initial_engine;
    struct EngineObj saved_engine;
    u16 inputs[0xE10];
};
#define REPLAY_SAVED_ENGINE (((struct ReplayData*)REPLAY_DATA)->saved_engine)
#endif

void func_80021E74(void)
{
    struct ReplayData* replay = (struct ReplayData*)REPLAY_DATA;

    replay->frame = 0;
    D_80141BD8.unk0 = replay->flags;
    cur_random = replay->random;
    REPLAY_SAVED_ENGINE = engine_obj;
#ifdef MMX4_PC
    restore_replay_engine(&replay->initial_engine);
#else
    engine_obj = replay->initial_engine;
#endif
}

INCLUDE_ASM("main/nonmatchings/125BC", func_80021F34);

// see also func_800220C4, func_80021E74
void func_80022074(void)
{
    engine_obj = REPLAY_SAVED_ENGINE;
}

void func_800220C4(void)
{
    struct ReplayData* replay = (struct ReplayData*)REPLAY_DATA;

    replay->frame = 0;
    replay->flags = D_80141BD8.unk0;
    replay->random = cur_random;
#ifdef MMX4_PC
    save_replay_engine(&replay->initial_engine);
#else
    replay->initial_engine = engine_obj;
#endif
}

void func_80022138(void)
{
    struct ReplayData* replay = (struct ReplayData*)REPLAY_DATA;
    s32 frame;

    frame = replay->frame;
    if (frame != 0xE10) {
        replay->inputs[frame] = g_Player.input.buttons.held;
        replay->frame += 1;
    }
}

INCLUDE_ASM("main/nonmatchings/125BC", func_8002217C);

void func_8002328C(struct AbcObj*);

#define CONFIG D_801397DC

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/125BC", func_80022730);
#else
void func_80022730(struct AbcObj* arg0)
{
    s32 charOffset;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0;
    signed long temp_v1;
    s16 temp_a2;
    struct MiscObj* obj;
    u8* readyText;
    u16 value;
    u16* src;
    u16* dst;

    switch (arg0->unkD) {
    case 0:
        value = arg0->unkA - 1;
        arg0->unkA = value;

        if ((value << 0x10) == 0) {
            if (!(D_801397D8 & 0x80)) {
                readyText = D_800F2DD8[engine_obj.cur_character][D_801397D8];

                obj = find_free_misc_obj();
                if (obj != NULL) {
                    obj->active = 0x41;
                    obj->id = 0x16;
                    obj->unk2 = 5;
                    obj->unk15 = 0;
                    obj->bg_offset = -1;

                    if (CONFIG->unk5 != 0) {
                        obj->x_pos.i.hi = 0xA0;
                    } else {
                        obj->x_pos.i.hi = 0x50;
                    }

                    obj->y_pos.i.hi = 0x48;
                    obj->unk16 = 0x10;

                    obj->animation_table = D_800F2EE8[engine_obj.cur_character];

                    if (CONFIG->unk4 != 0) {
                        obj->unk40 = (D_801406A8[CONFIG->unk0 + engine_obj.cur_character + 2] >> 7) + 0xB0;
                    } else {
                        obj->unk40 = D_801406A8[CONFIG->unk0 + engine_obj.cur_character + 2] >> 7;
                    }

                    temp_v1 = CONFIG->unk3 * 4;
                    charOffset = engine_obj.cur_character + 0x1A;
                    temp_v1 += charOffset;

                    temp_v0 = temp_v1;
                    if (temp_v1 < 0) {
                        temp_v0 = temp_v1 + 0xF;
                    }

                    temp_a0 = temp_v0 >> 4;
                    temp_v0 = temp_a0 << 4;
                    temp_a1 = temp_v1 - temp_v0;

                    obj->unk42 = temp_a1 | ((temp_a0 + 0x1E0) << 6);

                    temp_v0 = func_8002938C(
                        engine_obj.cur_character + 0x91,
                        temp_a1,
                        &engine_obj.cur_character);

                    temp_v1 = (signed long)SP_MENU_FRAMES;
                    temp_v0 = ((s32*)temp_v1)[temp_v0];

                    obj->ext.pointer.unk50 = readyText;
                    obj->state = 0;
                    temp_v1 += temp_v0;
                    obj->unk3C = (void*)temp_v1;

                    if ((engine_obj.unk47 & 3) == 3) {
                        obj->ext.title_logo
                            .palette_shift_speed
                            = 6;
                    } else if (engine_obj.unk47 & 1) {
                        obj->ext.title_logo
                            .palette_shift_speed
                            = 2;
                    } else if (engine_obj.unk47 & 2) {
                        obj->ext.title_logo
                            .palette_shift_speed
                            = 4;
                    } else {
                        obj->ext.title_logo
                            .palette_shift_speed
                            = 0;
                    }

                    obj->ext.title_logo
                        .palette_shift_value
                        = 0;

                    func_80015D60(
                        obj,
                        (s32)(s8)obj->ext.title_logo
                            .palette_shift_speed);
                }

                D_801397C8 = obj;

                obj = find_free_misc_obj();
                if (obj != NULL) {
                    obj->active = 0x41;
                    obj->id = 0x16;
                    obj->unk2 = 4;
                    obj->unk15 = 0;
                    obj->bg_offset = -1;

                    if (CONFIG->unk5 != 0) {
                        obj->x_pos.i.hi = 0xA0;
                    } else {
                        obj->x_pos.i.hi = 0x50;
                    }

                    value = 0x48;
                    obj->y_pos.i.hi = value;

                    value = 0x11;
                    obj->unk16 = value;

                    obj->animation_table = D_800F2F00[0];

                    if (CONFIG->unk4 != 0) {
                        obj->unk40 = (D_801406A8[CONFIG->unk0] >> 7) + 0xB0;
                    } else {
                        obj->unk40 = D_801406A8[CONFIG->unk0] >> 7;
                    }

                    value = CONFIG->unk3;
                    temp_v0 = value * 4;

                    temp_v1 = temp_v0 + 0x18;
                    temp_a2 = temp_v1;

                    if (temp_v1 < 0) {
                        temp_a2 = temp_v0 + 0x27;
                    }

                    temp_a1 = value + 6;
                    temp_v1 -= temp_a2 & 0x7F0;

                    if (temp_a1 < 0) {
                        temp_a1 = value + 9;
                    }

                    obj->unk42 = temp_v1 | (((temp_a1 >> 2) + 0x1E0) << 6);

                    temp_v0 = func_8002938C(
                        0x97,
                        temp_a1,
                        (s8*)temp_a2);

                    temp_v1 = (signed long)SP_MENU_FRAMES;
                    temp_v0 = ((s32*)temp_v1)[temp_v0];

                    obj->state = 0;
                    temp_v1 += temp_v0;
                    obj->unk3C = (void*)temp_v1;

                    func_80015D60(obj, 0);
                }

                D_801397D0 = obj;

                if (CONFIG->unk5 == 0) {
                    obj = find_free_misc_obj();

                    if (obj != NULL) {
                        obj->active = 0x41;
                        obj->id = 0x16;
                        obj->unk2 = 3;
                        obj->bg_offset = -1;
                        obj->unk15 = 0;
                        obj->unk16 = 0x10;
                        obj->x_pos.i.hi = 0xF0;
                        obj->y_pos.i.hi = 0x48;

                        obj->animation_table = D_800F2EE8[CONFIG->unk2 - 0x91];

                        if (CONFIG->unk4 != 0) {
                            obj->unk40 = (D_801406A8[CONFIG->unk1] >> 7) + 0xB0;
                        } else {
                            obj->unk40 = D_801406A8[CONFIG->unk1] >> 7;
                        }

                        value = CONFIG->unk3;
                        temp_v0 = value * 4;

                        temp_a0 = temp_v0 + 0x19;
                        temp_a2 = temp_a0;

                        if (temp_a0 < 0) {
                            temp_a2 = temp_v0 + 0x28;
                        }

                        temp_v1 = value + 6;
                        temp_a0 -= temp_a2 & 0x7F0;

                        if (temp_v1 < 0) {
                            temp_v1 = value + 9;
                        }

                        obj->unk42 = temp_a0 | (((temp_v1 >> 2) + 0x1E0) << 6);

                        temp_v0 = func_8002938C(
                            CONFIG->unk2,
                            value,
                            (s8*)temp_a2,
                            D_801397DC);

                        temp_v1 = (signed long)SP_MENU_FRAMES;
                        temp_v0 = ((s32*)temp_v1)[temp_v0];

                        obj->state = 0;
                        obj->ext.pointer.unk50 = readyText;

                        obj->ext.title_logo
                            .palette_shift_value
                            = 0;

                        temp_v1 += temp_v0;
                        obj->unk3C = (void*)temp_v1;

                        func_80015D60(obj, 0);
                    }

                    D_801397CC = obj;

                    obj = find_free_misc_obj();

                    if (obj != NULL) {
                        obj->active = 0x41;
                        obj->id = 0x16;
                        obj->unk2 = 4;
                        obj->unk15 = 0x40;
                        obj->bg_offset = -1;

                        *(volatile s16*)&obj->x_pos.i.hi = 0xF0;

                        *(volatile s16*)&obj->y_pos.i.hi = 0x48;

                        *(volatile u8*)&obj->unk16 = 0x11;

                        obj->animation_table = D_800F2F00[0];

                        if (CONFIG->unk4 != 0) {
                            obj->unk40 = (D_801406A8[CONFIG->unk0] >> 7) + 0xB0;
                        } else {
                            obj->unk40 = D_801406A8[CONFIG->unk0] >> 7;
                        }

                        value = CONFIG->unk3;
                        temp_v0 = value * 4;

                        temp_v1 = temp_v0 + 0x18;
                        temp_a2 = temp_v1;

                        if (temp_v1 < 0) {
                            temp_a2 = temp_v0 + 0x27;
                        }

                        temp_a1 = value + 6;
                        temp_v1 -= temp_a2 & 0x7F0;

                        if (temp_a1 < 0) {
                            temp_a1 = value + 9;
                        }

                        obj->unk42 = temp_v1 | (((temp_a1 >> 2) + 0x1E0) << 6);

                        temp_v0 = func_8002938C(
                            0x97,
                            temp_a1,
                            (s8*)temp_a2);

                        temp_v1 = (signed long)SP_MENU_FRAMES;
                        temp_v0 = ((s32*)temp_v1)[temp_v0];

                        obj->state = 0;
                        temp_v1 += temp_v0;
                        obj->unk3C = (void*)temp_v1;

                        func_80015D60(obj, 0);
                    }

                    D_801397D4 = obj;
                }
            }

            arg0->unkC = 1;
            arg0->unkD = 1;
            return;
        }

    default:
        return;

    case 1:
        func_8002328C(arg0);
        return;

    case 2:
        if (*(u8*)&controller_state != 0) {
            arg0->unkF = 0;
        }

        value = arg0->unkA - 1;
        arg0->unkA = value;

        if ((value << 0x10) == 0) {
            arg0->unkD = 1;
            return;
        }
        break;

    case 3:
        if (*(u8*)&controller_state != 0) {
            if ((D_801397C4 != NULL) && (D_801397C4->id == 0x16)) {
                D_801397C4->active = 0;
                D_801397C4->on_screen = 0;
            }

            if (arg0->unk4 & 0x8000) {
                if ((D_801397C0 != NULL) && (D_801397C0->id == 0x16)) {
                    D_801397C0->active = 0;
                    D_801397C0->on_screen = 0;
                }

                if ((D_801397CC != NULL) && (D_801397CC->id == 0x16)) {
                    D_801397CC->active = 0;
                    D_801397CC->on_screen = 0;
                }

                if ((D_801397D4 != NULL) && (D_801397D4->id == 0x16)) {
                    D_801397D4->active = 0;
                    D_801397D4->on_screen = 0;
                }

                if ((D_801397C8 != NULL) && (D_801397C8->id == 0x16)) {
                    D_801397C8->active = 0;
                    D_801397C8->on_screen = 0;
                }

                if (D_801397D0 != NULL) {
                    if (D_801397D0->id == 0x16) {
                        D_801397D0->active = 0;
                        D_801397D0->on_screen = 0;
                    }
                }

                arg0->unkA = 0x27;
                arg0->unkD = 4;
                arg0->unkC = 0x80;
                return;
            }

            D_801397E0 = 0;
            arg0->unkC = 1;
            arg0->unk6 = -0x78;
            arg0->unk8 = 0x1D;
            arg0->unkE = (u8)(arg0->unkE + 1);

            func_8002328C(arg0);
            return;
        }
        break;

    case 4:
        value = arg0->unkA - 1;
        arg0->unkA = value;

        if ((value << 0x10) == 0) {
            if (engine_obj.stage != 0xD) {
                dst = SP_PALETTE + 0x150;
            } else {
                dst = SP_PALETTE + 0x3E0;
            }

            src = D_801397E4;
            temp_a0 = 0;

            do {
                *dst = *src;
                src += 1;
                temp_a0 += 1;
                dst += 1;
            } while (temp_a0 < 0x20);

            need_palette_load |= 1;

            engine_obj.enable_boss = D_80139828;
            engine_obj.unk1F = D_80139824;

            if ((D_801397BC != NULL) && (D_801397BC->id == 0x16)) {
                D_801397BC->active = 0;
                D_801397BC->on_screen = 0;
            }

            if ((D_801397C0 != NULL) && (D_801397C0->id == 0x16)) {
                D_801397C0->active = 0;
                D_801397C0->on_screen = 0;
            }

            if ((D_801397C4 != NULL) && (D_801397C4->id == 0x16)) {
                D_801397C4->active = 0;
                D_801397C4->on_screen = 0;
            }

            if ((D_801397CC != NULL) && (D_801397CC->id == 0x16)) {
                D_801397CC->active = 0;
                D_801397CC->on_screen = 0;
            }

            if ((D_801397C8 != NULL) && (D_801397C8->id == 0x16)) {
                D_801397C8->active = 0;
                D_801397C8->on_screen = 0;
            }

            if ((D_801397D4 != NULL) && (D_801397D4->id == 0x16)) {
                D_801397D4->active = 0;
                D_801397D4->on_screen = 0;
            }

            if (D_801397D0 != NULL) {
                if (D_801397D0->id == 0x16) {
                    D_801397D0->active = 0;
                    D_801397D0->on_screen = 0;
                }
            }

            arg0->unkE = 0;
            arg0->unkD = 5;
            goto block_110;
        }
        break;

    case 6:
        value = arg0->unkA - 1;
        arg0->unkA = value;

        if ((value << 0x10) != 0) {
            return;
        }

    block_110:
        arg0->unkC = 0;
        break;
    }
}
#endif

#undef CONFIG

extern u32 D_800F2F38[];

extern struct DialogueGlyphData D_801396C8;

extern struct MiscObj* D_801397C0;

extern struct MiscObj* D_801397C4;

extern u8 D_801397D8;

extern s16 D_801397E0;

void func_8002328C(struct AbcObj* arg0)
{
    s16 temp_v0_2;
    struct MiscObj* temp_v0;
    struct MiscObj* temp_v0_4;
    u16 temp_v1;
    u8 temp_v0_3;
    u8 var_v0_4;

    do {
        temp_v1 = *arg0->unk0;
        arg0->unk4 = temp_v1;
        if ((temp_v1 & 0x1FF) != 0x1FF) {
            if (D_801397E0 == 0) {
                if (D_801397C0 == NULL) {
                    temp_v0 = find_free_misc_obj();
                    if (temp_v0 != NULL) {
                        D_801397C0 = temp_v0;
                        temp_v0->active = 1;
                        temp_v0->id = 0x16;
                        temp_v0->unk16 = 0x10;
                        temp_v0->unk40 = 0x1F00;
                        temp_v0->unk2 = 0;
                        temp_v0->unk3C = &D_801396C8.count;
                        if (engine_obj.stage == 0xD) {
                            temp_v0->unk42 = 0x78CE;
                        } else {
                            temp_v0->unk42 = 0x7845;
                        }
                        temp_v0->bg_offset = -1;
                        temp_v0->x_pos.val = 0xA00000;
                        if (!(arg0->unk4 & 0x800)) {
                            if (D_801397D8 != 0x80) {
                                temp_v0->y_pos.val = 0;
                            } else {
                                temp_v0->y_pos.val = 0x380000;
                            }
                        } else {
                            if (D_801397D8 == 0xFF) {
                                temp_v0->y_pos.val = 0x780000;
                            } else {
                                temp_v0->y_pos.val = 0x700000;
                            }
                        }
                        temp_v0->animation_step.fields.frame_index = 0;
                        temp_v0->unk15 = 0;
                    }
                    D_801396C8.active = 1;
                }
            }
            D_801396C8.glyphs[D_801397E0].frame = 0;
            D_801396C8.glyphs[D_801397E0].character = (u8)arg0->unk4;
            D_801396C8.glyphs[D_801397E0].x = (u8)arg0->unk6;
            D_801396C8.glyphs[D_801397E0].y = (u8)arg0->unk8;
            temp_v0_2 = (u16)D_801397E0 + 1;
            D_801397E0 = temp_v0_2;
            D_801396C8.count = temp_v0_2;
        }
        arg0->unk0++;
        if (arg0->unk4 & 0x4000) {
            arg0->unk6 = -0x78U;
            arg0->unk8 = (u16)(arg0->unk8 + 0x12);
        } else {
            arg0->unk6 = (u16)(arg0->unk6 +
#ifdef VERSION_JP
                0x10
#else
                0xC
#endif
            );
        }
        if (arg0->unkF == 0) {
            arg0->unk4 = (u16)(arg0->unk4 & 0xEFFF);
        }
    } while (!(arg0->unk4 & 0xB000));
    func_8001540C(0, 0xE, 0);
    if ((arg0->unk4 & 0xB000) == 0x1000) {
        if (*(u8*)&controller_state != 0) {
            temp_v0_3 = arg0->unkF;
            if (temp_v0_3 != 0) {
                arg0->unkF = (u8)(temp_v0_3 - 1);
            }
        }
        arg0->unkA = 4;
        var_v0_4 = 2;
    } else {
        arg0->unkF = 2U;
        if (arg0->unk4 & 0x2000) {
            temp_v0_4 = find_free_misc_obj();
            if (temp_v0_4 != NULL) {
                D_801397C4 = temp_v0_4;
                temp_v0_4->active = 1;
                temp_v0_4->id = 0x16;
                temp_v0_4->unk16 = 0x10;
                temp_v0_4->unk40 = 0x1FFF;
                temp_v0_4->unk2 = 1;
                temp_v0_4->unk3C = D_800F2F38;
                if (engine_obj.stage == 0xD) {
                    temp_v0_4->unk42 = 0x78CE;
                } else {
                    temp_v0_4->unk42 = 0x7845;
                }
                temp_v0_4->bg_offset = -1;
                temp_v0_4->x_pos.i.hi = 0x98;
                if (!(arg0->unk4 & 0x800)) {
                    if (D_801397D8 == 0x80) {
                        temp_v0_4->y_pos.i.hi = 0x85;
                    } else {
                        temp_v0_4->y_pos.i.hi = 0x4D;
                    }
                } else {
                    if (D_801397D8 == 0xFF) {
                        temp_v0_4->y_pos.i.hi = 0xC5;
                    } else {
                        temp_v0_4->y_pos.i.hi = 0xBD;
                    }
                }
                temp_v0_4->animation_step.fields.frame_index = 0;
                temp_v0_4->unk15 = 0;
                temp_v0_4->ext.title_logo.palette_shift_speed = 0;
                temp_v0_4->ext.ready_text.stay_up_timer = 0x20;
            }
        }
        arg0->unkC = 0xFF;
        var_v0_4 = 3;
    }
    arg0->unkD = var_v0_4;
}

void func_80023624(struct EngineObj* arg0)
{
    reset_objects();
    func_8002AB20();
    arg0->unk1F = 0;
    arg0->enable_boss = 0;

    if (arg0->cur_character == CHARACTER_X) {
        func_80018000(5);
    } else {
        func_80018000(10);
    }

    arg0->unk1++;
}

void func_80023684(struct EngineObj* arg0)
{
    arg0->unk1++;
}

void func_80023698(struct EngineObj* arg0)
{
    struct MiscObj* obj;
    u8 var_v1;

    for (var_v1 = 0; var_v1 < 16; var_v1++) {
        arg0->character_state.bytes[var_v1] = 0;
    }
    arg0->stage = 0xF;
    arg0->substage = 1;

    func_80013014();
    func_800160AC();
    func_80028BF0();
    func_8002771C();

    if (arg0->cur_character != CHARACTER_X) {
        background_objects[1].y_pos.val = FIXED(768);
    }

    func_80023CE0();
    background_objects[0].unk3 = 1;
    background_objects[1].unk3 = 0;
    background_objects[2].unk3 = 1;
    need_palette_load |= 1;

    for (var_v1 = 0; var_v1 < 5; var_v1++) {
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x38;
            obj->unk2 = get_random() & 1;
            obj->ext.title_logo.palette_shift_speed = get_random();
        }
    }

    arg0->unk2 = 0;
    arg0->unk1++;

    func_8001663C(0, 0x7F);
    func_800129A4(8);
}

void func_800237E4(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->unk2 == 0) {
            if (D_80173C84 == 2) {
                arg0->unk2++;
            }
        } else {
#ifdef VERSION_JP
            background_objects[0].y_pos.val += FIXED(7.0 / 16);
            if (background_objects[0].y_pos.i.hi == 0x11FF) {
#else
            background_objects[0].y_pos.val += FIXED(7.0 / 16);
            if (background_objects[0].y_pos.i.hi == 4304) {
#endif
                arg0->unk2 = 0;
#ifdef VERSION_JP
                arg0->unk4 = 0x258;
#else
                arg0->unk4 = 0x1A4;
#endif
                arg0->unk1++;
#ifdef VERSION_JP
                func_80016F0C();
#endif
            }
        }
    }
}

void func_80023870(struct EngineObj* arg0)
{
    struct MiscObj* obj;

    if (--arg0->unk4 == 0) {
        arg0->unk1++;
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x38;
            obj->unk2 = 2;
            obj->ext.title_logo.palette_shift_speed = 0;
        }
#ifdef VERSION_JP
        arg0->unk4 = 0x12C;
#else
        arg0->unk4 = 0xB4;
#endif
    }
}

void func_800238F0(struct EngineObj* arg0)
{
    if (arg0->unk4 == 0) {
        background_objects[0].y_pos.val += FIXED(0.5);
        if (background_objects[0].y_pos.i.hi ==
#ifdef VERSION_JP
            4864
#else
            4480
#endif
        ) {
            arg0->unk1++;
            background_objects[0].unk3 = 0;
            background_objects[1].unk3 = 1;
        }
    } else {
        arg0->unk4--;
    }
}

void func_80023970(struct EngineObj* arg0)
{
    background_objects[1].y_pos.val += FIXED(0.5);
    if (background_objects[1].y_pos.i.hi == D_800F2FDC[arg0->cur_character]) {
        arg0->unk1++;
        func_800129F0(8);
    }
}

void func_800239E0(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        game_info.unk0 = 3;
        game_info.mode = 0;
        game_info.unk2 = 0;
        game_info.unk3 = 0;
        D_8013E1C4 = 1;
        D_8013BD44 = 0;
        func_80012740(0, &func_8001DAF8);
        func_800127FC();
    }
}

void func_80023A54(struct EngineObj* arg0)
{
    D_800F2FE0[arg0->unk1](arg0);
    func_8002B460();
    update_misc_objects();
    func_80023D68();
}

INCLUDE_ASM("main/nonmatchings/125BC", func_80023AA8);

void func_80023B98(struct MiscObj* arg0)
{
    s8 timer;

    timer = arg0->ext.misc_11.active;
    if (timer == 0) {
        func_80015DC8(arg0);
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->state = 2;
            arg0->ext.misc_11.active = get_random() & 0x1F;
        }
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->ext.misc_11.active = timer - 1;
}

void func_80023C0C(struct MiscObj* arg0)
{
    s8 timer;
    struct MiscObj* spawned;

    timer = arg0->ext.misc_11.active;
    if (timer == 0) {
        if (arg0->unk2 != 2) {
            spawned = find_free_misc_obj();
            if (spawned != NULL) {
                spawned->active = 0x41;
                spawned->id = 0x38;
                spawned->unk2 = get_random() & 1;
                spawned->ext.misc_11.active = get_random();
            }
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    arg0->ext.misc_11.active = timer - 1;
}

void func_80023CA4(struct MiscObj* arg0)
{
    D_800F30C8[arg0->state](arg0);
}

void func_80023CE0()
{
    func_80025DA0(0, D_800F30D4[engine_obj.stage][engine_obj.substage]);
    func_80026118();
}

void func_80023D30(void)
{
    D_80173C6C[0] = 3;
    D_80173C6C[1] = 4;
    D_80173C6C[2] = 5;
    D_80173C6C[3] = 6;
}

void func_80023D68(void)
{
    func_80026648();
    init_objects();
}

void func_80023D90(void)
{
    func_80017100();
    func_80017340();
}

// some kind of init?
void init_objects(void)
{
    struct UnkObj* var_s0;
    struct MainObj* var_s0_2;
    struct WeaponObj* var_s0_3;
    struct ShotObj* var_s0_4;
    struct VisualObj* var_s0_5;
    struct ItemObj* var_s0_6;
    struct MiscObj* var_s0_7;
    struct UnkObj* var_s0_8;
    struct QuadObj* var_s0_9;
    void* temp_v1;
    void* temp_v1_2;
    void* temp_v1_3;
    void* temp_v1_4;
    void* temp_v1_5;
    void* temp_v1_6;
    void* temp_v1_7;
    void* temp_v1_8;
    void* temp_v1_9;
    struct PlayerObj* ptr = &g_Player;
    struct BazObj* ptr2;
    struct PlayerObj* ptr3 = &g_Entity;
    struct RideArmorObj* ptr4;

    SP_SPRITE_COUNT = 0;
    SP_PRIM_CURSOR = temp1[SP_DRAW_BUFFER].data;
    SP_DRAW_MODE_CURSOR = temp2[SP_DRAW_BUFFER].data;
    SP_BG_PRIM_CURSOR = temp3[SP_DRAW_BUFFER].data;
    SP_OT_CURSOR = temp4[SP_DRAW_BUFFER].data;
    SP_AUX_CURSOR = temp5[SP_DRAW_BUFFER].data;

    func_80024E70();
    func_800241E8();

    if (g_Player.on_screen) {
        func_80024334(ptr);
        if (g_Player.unk2 == 0) {
            func_800257BC(ptr);
        }
    }
    if (g_Entity.on_screen != 0) {
        func_80024334(ptr3);
    }
    if (ptr->unk2 == 0) {
        ptr2 = &baz_objects;
        if (ptr2->on_screen != 0) {
            func_80024334(ptr2);
        }
        ptr2 += 1;
        if (ptr2->on_screen != 0) {
            func_80024334(ptr2);
        }
    }

    // this one loops backwards for some reason, doesn't seem to be a compiler optimization
    for (var_s0 = &foo_objects[2]; var_s0 >= &foo_objects[0]; var_s0--) {
        if (var_s0->on_screen != 0) {
            func_80024334(var_s0);
        }
    }

    // might be a series of macros or inlines

    for (var_s0_2 = &main_objects[0]; var_s0_2 < &main_objects[COUNT(main_objects)]; var_s0_2++) {
        if (var_s0_2->on_screen != 0) {
            func_80024334(var_s0_2);
        }
    }

    for (var_s0_3 = &weapon_objects[0]; var_s0_3 < &weapon_objects[COUNT(weapon_objects)]; var_s0_3++) {
        if (var_s0_3->on_screen != 0) {
            func_80024334(var_s0_3);
        }
    }

    for (var_s0_4 = &shot_objects[0]; var_s0_4 < &shot_objects[COUNT(shot_objects)]; var_s0_4++) {
        if (var_s0_4->on_screen != 0) {
            func_80024334(var_s0_4);
        }
    }

    for (var_s0_5 = &visual_objects[0]; var_s0_5 < &visual_objects[COUNT(visual_objects)]; var_s0_5++) {
        if (var_s0_5->on_screen != 0) {
            func_80024334(var_s0_5);
        }
    }

    for (var_s0_6 = &item_objects[0]; var_s0_6 < &item_objects[COUNT(item_objects)]; var_s0_6++) {
        if (var_s0_6->on_screen != 0) {
            func_80024334(var_s0_6);
        }
    }

    for (var_s0_7 = &misc_objects[0]; var_s0_7 < &misc_objects[COUNT(misc_objects)]; var_s0_7++) {
        if (var_s0_7->on_screen != 0) {
            func_80024334(var_s0_7);
        }
    }

    for (var_s0_8 = &unk_objects[0]; var_s0_8 < &unk_objects[COUNT(unk_objects)]; var_s0_8++) {
        if (var_s0_8->on_screen != 0) {
            func_80024334(var_s0_8);
        }
    }

    ptr4 = &qux_object;
    if (ptr4->on_screen != 0) {
        func_80024334(&qux_object);
    }

    for (var_s0_9 = &g_QuadObjects[0]; var_s0_9 < &g_QuadObjects[COUNT(g_QuadObjects)]; var_s0_9++) {
        if (var_s0_9->on_screen != 0) {
            if (var_s0_9->active & 2) {
                func_80024B9C(var_s0_9);
            } else {
                func_80024920(var_s0_9);
            }
        }
    }

    func_80024260();
}

void func_800241E8(void)
{
    u32 buffer;
    u32 i;
    u32 j;

    buffer = SP_DRAW_BUFFER;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            D_8013E1E8[buffer][i][j] = NULL;
            D_8013BC40[buffer][i][j] = (P_TAG*)&D_8013E1E8[buffer][i][j];
        }
    }
}

void func_80024260(void)
{
    u32 buffer;
    u32 i;
    u32 j;
    OT_TYPE* otag;

    buffer = SP_DRAW_BUFFER;

    for (i = 0; i < 4; i++) {
        otag = &cur_draw_info->ordering_table.start + D_80173C6C[i];

        for (j = 0; j < 8; j++) {
            if (D_8013E1E8[buffer][i][j] != NULL) {
                setaddr(D_8013BC40[buffer][i][j], getaddr(otag));
                setaddr(otag, D_8013E1E8[buffer][i][j]);
            }
        }
    }

#ifdef MMX4_PC
    mmx4_pc_render_log_dump();
#endif
}

INCLUDE_ASM("main/nonmatchings/125BC", func_80024334);

INCLUDE_ASM("main/nonmatchings/125BC", func_80024920);

INCLUDE_ASM("main/nonmatchings/125BC", func_80024B9C);

void func_80024E70(void)
{
    struct PlayerObj* player = &g_Player;
    struct EngineObj* ptr = &engine_obj;

    if (engine_obj.unk1F != 0) {
        func_800253F0(MAIN_OBJECT(player), 0);
        func_80025188(1, engine_obj.unk44 + 0x3B);
        func_80025188(0, (engine_obj.unk46 - 0x20) / 2 + 0x45);
        if (player->unk2 == 0) {
            func_80024F5C(player);
        } else {
            func_8002509C(player);
        }
        if (ptr->enable_boss) {
            func_800253F0(ptr->boss_ptr, 1);
            func_80025188(7, ptr->unk25 + 0x57);
        }
    }
}

void func_80024F5C(struct PlayerObj* arg0)
{
    s8 temp_v0_2;
    s8 temp_s0;
    s8 temp;

    if (arg0->unk93 != 0) {
        temp_s0 = arg0->charge_levels[arg0->unk93];
        func_80025588(0x24, 0x29, 0x4F - temp_s0, 0x4F, 0);
        temp_v0_2 = D_800F8BE0.hud.health_divisors[arg0->unk94[0]];
        temp = temp_s0 / temp_v0_2;
        func_80025188(3, (temp / 10) + 0x3B);
        func_80025188(4, (temp % 10) + 0x3B);

        if (arg0->unk93 == 3) {
            func_80025188(6, arg0->unk93 + 0x4E);
        } else {
            func_80025188(5, arg0->unk93 + 0x4E);
        }

        func_80025188(2, 0x4E);
    }
}

void func_8002509C(struct PlayerObj* arg0)
{
    s8 temp_s0;
    s8 temp_s1;

    if (arg0->unkB9 & 0x20) {
        temp_s0 = arg0->charge_levels[0];
        func_80025588(0x24, 0x29, 0x4F - temp_s0, 0x4F, 0);
        temp_s1 = temp_s0 / 12;
        func_80025188(3, (temp_s1 / 10) + 0x3B);
        func_80025188(4, (temp_s1 % 10) + 0x3B);
        func_80025188(2, 0x4E);
    }
}

INCLUDE_ASM("main/nonmatchings/125BC", func_80025188);

INCLUDE_ASM("main/nonmatchings/125BC", func_800253F0);

void func_80025588(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4)
{
    u32 color;
    u32 temp_r;
    u32 temp_g;
    u32 temp_b;
    u32 temp_v1;
    u32 var_r;
    u32 var_g;
    u32 var_b;
    POLY_F4* prim;

    prim = SP_AUX_POLY_F4_CURSOR;
    setPolyF4(prim);
    prim->x0 = prim->x2 = arg0;
    prim->x1 = prim->x3 = arg1;
    color = arg2;
    prim->y0 = prim->y1 = color;
    prim->y2 = prim->y3 = arg3;
    color = D_800F312C[arg4];

    if (((u16)g_FilterAmountB | (g_FilterAmountR | (u16)g_FilterAmountG)) != 0) {
        if (ENGINE_STAGE_ID != 2 && g_FilterAmountR == ((u16)g_FilterAmountG >> 5) && g_FilterAmountR == ((u16)g_FilterAmountB >> 10)) {
            if (*(u8*)&g_FilterModeR != 0) {
                var_r = 0;
                if ((color & 0x1F) >= g_FilterAmountR) {
                    var_r = (color & 0x1F) - g_FilterAmountR;
                }
            } else {
                temp_v1 = (color & 0x1F) + g_FilterAmountR;
                var_r = 0x1F;
                if (temp_v1 < 0x20U) {
                    var_r = temp_v1;
                }
            }

            temp_v1 = color & 0x3E0;
            if (*(u8*)&g_FilterModeG != 0) {
                var_g = 0;
                if (temp_v1 >= (u16)g_FilterAmountG) {
                    var_g = temp_v1 - (u16)g_FilterAmountG;
                }
            } else {
                temp_v1 += (u16)g_FilterAmountG;
                var_g = 0x3E0;
                if (temp_v1 < 0x3E1U) {
                    var_g = temp_v1;
                }
            }

            temp_v1 = color & 0x7C00;
            if (*(u8*)&g_FilterModeB != 0) {
                var_b = 0;
                if (temp_v1 >= (u16)g_FilterAmountB) {
                    var_b = temp_v1 - (u16)g_FilterAmountB;
                }
            } else {
                temp_v1 += (u16)g_FilterAmountB;
                var_b = 0x7C00;
                if (temp_v1 < 0x7C01U) {
                    var_b = temp_v1;
                }
            }

            color = var_r | var_g | var_b | (color & 0x8000);
        }
    }

    temp_r = color & 0x1F;
    temp_g = (color >> 5) & 0x1F;
    temp_b = color >> 10;
    prim->r0 = temp_r * 8 + ((temp_r & 0xFF) >> 2);
    prim->g0 = temp_g * 8 + ((temp_g & 0xFF) >> 2);
    prim->b0 = temp_b * 8 + ((temp_b & 0xFF) >> 2);

    addPrim(&cur_draw_info->ordering_table.unk3, prim);
    SP_AUX_CURSOR = SP_AUX_POLY_F4_CURSOR + 1;
}

void func_800257BC(struct PlayerObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s16 var_a2;

    if (player->unkA7 & 8) {
        func_8002588C(arg0, 3, 0x7843);
    }
    if (player->unkA7 & 1) {
        func_8002588C(arg0, 0, 0x7843);
    }
    if (player->unkA7 & 4) {
        if (player->unkB8 == 2) {
            var_a2 = 0x7844;
        } else {
            var_a2 = 0x7843;
        }
        func_8002588C(arg0, 2, var_a2);
    }
    if (player->unkA7 & 2) {
        func_8002588C(arg0, 1, 0x7843);
    }
}

INCLUDE_ASM("main/nonmatchings/125BC", func_8002588C);

void func_80025CDC(void)
{
    struct UnkObj* var_s0;

    SP_SPRITE_COUNT = 0;
    SP_PRIM_CURSOR = temp1[SP_DRAW_BUFFER].data;
    SP_DRAW_MODE_CURSOR = temp2[SP_DRAW_BUFFER].data;
    func_800241E8();
    for (var_s0 = &unk_objects[0]; var_s0 < &unk_objects[COUNT(unk_objects)]; var_s0++) {
        if (var_s0->on_screen != 0) {
            func_80024334(var_s0);
        }
    }
    func_80024260();
}

#define BG_TPAGE(tp, abr, x, y)                                                            \
    ((GetGraphType() == 1 || GetGraphType() == 2)                                          \
            ? (((tp)&3) << 9) | (((abr)&3) << 7) | (((y)&0x300) >> 3) | (((x)&0x3FF) >> 6) \
            : getTPage(tp, abr, x, y))

#define BG_DRAW_TPAGE(p, tpage) \
    (setlen(p, 1), ((u_long*)(p))[sizeof(OT_TYPE) / sizeof(u_long)] = 0xE1000000 | ((GetGraphType() == 1 || GetGraphType() == 2) ? (tpage) : ((tpage)&0x9FF)))

void func_80025DA0(s32 texture_depth, s32 blend_mode)
{
    u32 buffer, i, j;
    s16 x;
    DR_TPAGE* page;
    for (buffer = 0; buffer < 2; buffer++) {
        setTile(&D_8013B7B0[buffer]);
        for (i = 0; i < 0x400; i++) {
            setSprt16(&D_8015D9D0[buffer].sprites[i]);
            setShadeTex(&D_8015D9D0[buffer].sprites[i], 1);
        }
        for (i = 0; i < 6; i++) {
            x = 320;
            j = 0;
            page = D_80171EB0[buffer][i];
            for (; j < 8; j++, x += 64) {
                BG_DRAW_TPAGE(page, BG_TPAGE(texture_depth, blend_mode, x, 256));
                page++;
            }
        }
        setPolyFT4(&D_80139F20[buffer]);
        setShadeTex(&D_80139F20[buffer], 1);
        setPolyF4(&D_80139F70[buffer]);
        setSemiTrans(&D_80139F70[buffer], 1);
        BG_DRAW_TPAGE(&D_80139FA0[buffer], BG_TPAGE(0, 0, 960, 256));
        for (i = 0; i < 128; i++) {
            setPolyF4(&D_80139FB0[buffer][i]);
            setSemiTrans(&D_80139FB0[buffer][i], 1);
        }
    }
    SP_BG_TILEMAP = D_80141BE8;
}

#undef BG_TPAGE

#undef BG_DRAW_TPAGE

void func_80026118(void)
{
    u32 var_a1;
    u8 temp_v0;
    u8* var_a0;
    u8* var_a2;
    u32 var_s0;

    (void)&var_s0;
    var_a2 = SP_BG_TILEMAP;
    var_a0 = D_8010FFDC[engine_obj.stage][engine_obj.substage];
    var_a1 = 0;
    if ((layout_size * 3) != 0) {
        do {
            temp_v0 = *var_a0;
            var_a0 += 1;
            var_a1 += 1;
            *var_a2 = temp_v0;
            var_a2 += 1;
        } while (var_a1 < (u32)(layout_size * 3));
    }
    func_800261B4(-1, var_a1, var_a2);
}

void func_800261B4(s32 arg0, u32 arg1, u8* arg2)
{
    s32 var_v0;
    s32 var_s0;
    s32 var_s2;
    u32 var_s5;
    u32 var_s6;
    u32 var_k;
    u32 var_j;
    u32 var_i;

    for (var_i = 0, var_s5 = 0; var_i < 3; var_i++, var_s5 += 0x54) {
        var_v0 = background_objects[var_i].y_pos.i.hi;
        if (var_v0 < 0) {
            var_v0 += 0xF;
        }
        var_s2 = (var_v0 >> 4) + arg0;
        var_j = 0;
        var_s6 = var_s5;
        for (; var_j < 0x20; var_j++) {
            if (var_s2 >= 0) {
                var_v0 = background_objects[var_i].x_pos.i.hi;
                if (var_v0 < 0) {
                    var_v0 += 0xF;
                }
                var_s0 = (var_v0 >> 4) + arg0;
                for (var_k = 0; var_k < 0x20; var_k++) {
                    if (var_s0 >= 0) {
                        func_800264D0(var_i, var_s0, var_s2);
                    }
                    var_s0 += 1;
                }
            }
            var_s2 += 1;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/125BC", func_800262B8);

void func_800264D0(s32 layer, s32 x, s32 y)
{
    s32 block_x = x / 16;
    s32 block_y = y / 16;
    s32 tile_x = x % 32;
    s32 tile_y = y % 32;

    s32 inner_x = tile_x & 15;
    s32 inner_y = tile_y & 15;
    u8 block = (SP_BG_TILEMAP + layer * layout_size + layout_width * block_y)[block_x];

    D_801441C8[layer][tile_y][tile_x] = (inner_y * 16 + (SP_BG_TILE_PIXELS + block * 256))[inner_x];
}

void func_800265B4(void)
{
    struct BackgroundObj* obj = background_objects;
    u32 i;

    SP_BG_PRIM_CURSOR = &D_8015D9D0[SP_DRAW_BUFFER];
    for (i = 0; i < 3; i++) {
        if (obj->unk3 != 0) {
            SP_CUR_BG_INDEX = i;
            func_800267D4(i);
            func_80026CEC(i);
            func_80026894(i);
        }
        obj++;
    }
}

void func_80026648(void)
{
    struct BackgroundObj* bg_obj;
    u32 var_s0;
    u32 bg_num;

    var_s0 = 0;
    SP_BG_SPRITE_COUNT = 0;
    do {
        if (background_objects[var_s0].unk4C != 0) {
            func_800262B8(var_s0 & 0xFF);
        }
        var_s0 += 1;
    } while (var_s0 < 3);
    bg_num = 0;
    func_8002728C();
    func_80026720();
    bg_obj = background_objects;
    SP_BG_PRIM_CURSOR = &D_8015D9D0[SP_DRAW_BUFFER];
    do {
        if (bg_obj->unk3 != 0) {
            func_800267D4(bg_num);
            func_80026AA0(bg_num);
            func_80026894(bg_num);
        }
        bg_num += 1;
        bg_obj += 1;
    } while (bg_num < 3);
}

void func_80026720(void)
{
    TILE* sprt;

    if (engine_obj.stage == 0) {
        if (engine_obj.substage == 0) {
            sprt = &D_8013B7B0[SP_DRAW_BUFFER];
            setRGB0(sprt, 8, 0x18, 0x31);
            setXY0(sprt, 0, 0);
            setWH(sprt, 0x140, 0x60);
            addPrim(&cur_draw_info->ordering_table.end, sprt);
        }
    }
}

extern s32* D_8013BD50[][8];

extern s32 D_8013E2F0[][8];

void func_800267D4(s32 input)
{
    u32 i;
    s32 input3;

    for (i = 0, input3 = input + 3; i < 8; i++) {
        D_8013E2F0[input][i] = 0;
        D_8013E2F0[input + 6][i] = 0;
        D_8013BD50[input][i] = &D_8013E2F0[input][i];
        D_8013BD50[input + 6][i] = &D_8013E2F0[input + 6][i];
        D_8013E2F0[input3][i] = 0;
        D_8013E2F0[input3 + 6][i] = 0;
        D_8013BD50[input3][i] = &D_8013E2F0[input3][i];
        D_8013BD50[input3 + 6][i] = &D_8013E2F0[input3 + 6][i];
    }
}

INCLUDE_ASM("main/nonmatchings/125BC", func_80026894);

INCLUDE_ASM("main/nonmatchings/125BC", func_80026AA0);

INCLUDE_ASM("main/nonmatchings/125BC", func_80026CEC);

INCLUDE_ASM("main/nonmatchings/125BC", func_800270F8);

void func_8002728C(void)
{
    s16 temp_s1;
    s16 temp_s2;
    u32 var_i;
    for (var_i = 0; var_i < 3; var_i++) {
        temp_s1 = background_objects[var_i].x_pos.i.hi;
        temp_s2 = background_objects[var_i].y_pos.i.hi;
        func_80027344(var_i, temp_s1 - 0x10, temp_s2 - 0x10);
        func_80027344(var_i, temp_s1 + 0x150, temp_s2 - 0x10);
        func_800275DC(var_i, temp_s1, temp_s2 - 0x10);
        func_800275DC(var_i, temp_s1, temp_s2 + 0x100);
    }
}

INCLUDE_ASM("main/nonmatchings/125BC", func_80027344);

INCLUDE_ASM("main/nonmatchings/125BC", func_800275DC);

struct FixedMatrix2 D_800F2ADC[16] = {
    { 256, 0, 0, 256 },
    { 236, 97, -97, 236 },
    { 180, 180, -180, 180 },
    { 97, 236, -236, 97 },
    { 0, 256, -256, 0 },
    { -97, 236, -236, -97 },
    { -180, 180, -180, -180 },
    { -236, 97, -97, -236 },
    { -256, 0, 0, -256 },
    { -236, -97, 97, -236 },
    { -180, -180, 180, -180 },
    { -97, -236, 236, -97 },
    { 0, -256, 256, 0 },
    { 97, -236, 236, 97 },
    { 180, -180, 180, 180 },
    { 236, -97, 97, 236 },
};

u8 D_800F2B5C[21][12] = {
    { 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0xc6, 0x00, 0x00, 0xc6 },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x21, 0x21, 0xe7, 0x21, 0x21, 0xe7 },
    { 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 },
    { 0xff, 0xff, 0xff, 0xc6, 0xc6, 0xff, 0xc6, 0xc6, 0xff, 0xff, 0xff, 0xff },
    { 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00 },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff },
    { 0xde, 0x00, 0x00, 0xde, 0x00, 0x00, 0xde, 0x00, 0x00, 0xde, 0x00, 0x00 },
    { 0xbd, 0x00, 0x00, 0xbd, 0x00, 0x00, 0xbd, 0x00, 0x00, 0xbd, 0x00, 0x00 },
    { 0x9c, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x9c, 0x00, 0x00 },
    { 0x7b, 0x00, 0x00, 0x7b, 0x00, 0x00, 0x7b, 0x00, 0x00, 0x7b, 0x00, 0x00 },
    { 0x5a, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x5a, 0x00, 0x00 },
    { 0x39, 0x00, 0x00, 0x39, 0x00, 0x00, 0x39, 0x00, 0x00, 0x39, 0x00, 0x00 },
    { 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00 },
    { 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x84, 0x00, 0x00, 0xff, 0x00 },
    { 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x84, 0x00, 0x00, 0xff, 0x00, 0x00 },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x84, 0x84, 0x00, 0xff, 0xff, 0x00 },
    { 0x42, 0xff, 0x84, 0x42, 0xff, 0x84, 0xff, 0x42, 0x84, 0xff, 0x42, 0x84 },
    { 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00 },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00 },
    { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff },
};

u8 D_800F2C58[] = {
    0x0A,
    0x0B,
    0xFF,
    0x09,
    0x00,
    0x01,
    0x03,
    0x04,
    0x93,
    0x09,
    0x01,
    0x00,
    0x03,
    0x03,
    0xFF,
    0x09,
    0x01,
    0x01,
    0x01,
    0x02,
    0x93,
    0x01,
    0x01,
    0x00,
    0x01,
    0x02,
    0x93,
    0x06,
    0x01,
    0x00,
    0x06,
    0x07,
    0x94,
    0x06,
    0x00,
    0x00,
    0x02,
    0x03,
    0x95,
    0x09,
    0x01,
    0x00,
    0x02,
    0x06,
    0x96,
    0x08,
    0x01,
    0x00,
    0x02,
    0x03,
    0x95,
    0x07,
    0x01,
    0x00,
    0x09,
    0x0A,
    0xFF,
    0x08,
    0x00,
    0x01,
};

#ifdef VERSION_JP
u8 x_ready_text_flags[] = {
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    1,
    1,
    0,
    1,
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    1,
    1,
    0,
    0,
    0,
    0,
    1,
    0,
    1,
    1,
    0,
    0,
    0,
    1,
    0,
    1,
    1,
    0,
    1,
    0,
    0,
    0,
    1,
    0,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static u8* x_ready_text[] = {
    x_ready_text_flags + 0,
    x_ready_text_flags + 4,
    x_ready_text_flags + 20,
    x_ready_text_flags + 24,
    x_ready_text_flags + 28,
    x_ready_text_flags + 36,
    x_ready_text_flags + 48,
    x_ready_text_flags + 56,
    x_ready_text_flags + 64,
    x_ready_text_flags + 72,
};
#else
u8 x_ready_text_flags[] = {
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    0,
    0,
    1,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    0,
    1,
    1,
    1,
    1,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    1,
    1,
    0,
    1,
    1,
    1,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    1,
    0,
    0,
    1,
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
};

static u8* x_ready_text[] = {
    x_ready_text_flags + 0,
    x_ready_text_flags + 4,
    x_ready_text_flags + 28,
    x_ready_text_flags + 32,
    x_ready_text_flags + 36,
    x_ready_text_flags + 48,
    x_ready_text_flags + 64,
    x_ready_text_flags + 72,
    x_ready_text_flags + 80,
    x_ready_text_flags + 88,
};
#endif

u8 D_800F2D18[] = {
    0x0A,
    0x0B,
    0xFF,
    0x09,
    0x00,
    0x01,
    0x09,
    0x0A,
    0x98,
    0x08,
    0x00,
    0x00,
    0x09,
    0x0A,
    0xFF,
    0x08,
    0x00,
    0x01,
    0x03,
    0x04,
    0x93,
    0x09,
    0x01,
    0x00,
    0x03,
    0x04,
    0xFF,
    0x09,
    0x01,
    0x01,
    0x01,
    0x02,
    0x93,
    0x06,
    0x01,
    0x00,
    0x02,
    0x03,
    0x95,
    0x09,
    0x01,
    0x00,
    0x02,
    0x06,
    0x96,
    0x08,
    0x01,
    0x00,
    0x02,
    0x03,
    0x95,
    0x07,
    0x01,
    0x00,
    0x09,
    0x0A,
    0xFF,
    0x08,
    0x00,
    0x01,
};

static u8 zero_ready_text_flags[] = {
    0,
    0,
    0,
    0,
};

static u8 zero_ready_text_flags_1[] = { 0, 0, 1, 0, 1, 0, 0, 0 };

static u8 zero_ready_text_flags_2[] = { 0, 0, 0, 0 };

static u8 zero_ready_text_flags_3[] = {
    1,
    0,
    1,
    1,
    0,
    1,
    0,
    0,
    1,
    1,
    1,
    0,
    1,
    0,
    1,
    1,
#ifdef VERSION_JP
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
#else
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
#endif
};

static u8 zero_ready_text_flags_4[] = { 0, 0, 0, 0 };

static u8 zero_ready_text_flags_5[] = {
    1,
    0,
    1,
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
};

static u8 zero_ready_text_flags_6[] = { 0, 1, 0, 1, 0, 0, 0, 0 };

static u8 zero_ready_text_flags_7[] = { 1, 0, 1, 1, 0, 1, 0, 0 };

static u8 zero_ready_text_flags_8[] = { 0, 1, 1, 0, 1, 0, 1, 0 };

static u8 zero_ready_text_flags_9[] = { 0, 0, 0, 0 };

static u8* zero_ready_text[] = {
    &zero_ready_text_flags[0],
    &zero_ready_text_flags_1[0],
    &zero_ready_text_flags_2[0],
    &zero_ready_text_flags_3[0],
    &zero_ready_text_flags_4[0],
    &zero_ready_text_flags_5[0],
    &zero_ready_text_flags_6[0],
    &zero_ready_text_flags_7[0],
    &zero_ready_text_flags_8[0],
    &zero_ready_text_flags_9[0],
};

const u8* D_800F2DD0[] = { D_800F2C58, D_800F2D18 };

u8* const* D_800F2DD8[] = {
    x_ready_text,
    zero_ready_text,
};

static u32 anim_91_0[] = { 0x00000101 };

static u32 anim_91_1[] = { 0x00010007, 0x04010006, 0x04000101 };

static u32 anim_91_2[] = { 0x01000101 };

static u32 anim_91_3[] = { 0x01010007, 0x05010006, 0x05000101 };

static u32 anim_91_4[] = { 0x02000101 };

static u32 anim_91_5[] = { 0x02010007, 0x06010006, 0x06000101 };

static u32 anim_91_6[] = { 0x03000101 };

static u32 anim_91_7[] = { 0x03010007, 0x07010006, 0x07000101 };

static const u32* animation_91[] = {
    anim_91_0,
    anim_91_1,
    anim_91_2,
    anim_91_3,
    anim_91_4,
    anim_91_5,
    anim_91_6,
    anim_91_7,
};

static u32 anim_92_0[] = { 0x00000101 };

static u32 anim_92_1[] = { 0x01010007, 0x02010006, 0x02000101 };

static const u32* animation_92[] = { anim_92_0, anim_92_1 };

static u32 anim_93_0[] = { 0x00000101 };

static u32 anim_93_1[] = { 0x01010007, 0x02010006, 0x02000101 };

static const u32* animation_93[] = { anim_93_0, anim_93_1 };

static u32 anim_94_0[] = { 0x00000101 };

static u32 anim_94_1[] = { 0x00010007, 0x01010006, 0x01000101 };

static const u32* animation_94[] = { anim_94_0, anim_94_1 };

static u32 anim_95_0[] = { 0x00000101 };

static u32 anim_95_1[] = { 0x00010007, 0x01010006, 0x01000101 };

static const u32* animation_95[] = { anim_95_0, anim_95_1 };

static u32 anim_96_0[] = { 0x00000101 };

static u32 anim_96_1[] = { 0x00010007, 0x01010006, 0x01000101 };

static const u32* animation_96[] = { anim_96_0, anim_96_1 };

static u32 anim_97_0[] = {
    0x00010003,
    0x01010003,
    0x02010003,
    0x03010003,
    0x04FC0003,
};

static const u32* animation_97[] = { anim_97_0 };

static u32 anim_98_0[] = { 0x00000101 };

static u32 anim_98_1[] = { 0x00010007, 0x01010006, 0x01000101 };

static const u32* animation_98[] = { anim_98_0, anim_98_1 };

const u32* const* D_800F2EE8[] = {
    animation_91,
    animation_92,
    animation_93,
    animation_94,
    animation_95,
    animation_96,
};

const u32* const* D_800F2F00[] = { animation_97, animation_98 };

u32 D_800F2F08[12] = {
    0xFEFE19FE,
    0xFEFEFEFF,
    0xFE19FEFE,
    0xFFFF181A,
    0xFEFEFEFE,
    0xFEFE19FE,
    0xFEFE19FE,
    0xFEFEFEFE,
    0x18181AFE,
    0xFEFEFFFF,
    0xFEFEFEFE,
    0x00FE19FE,
};

u32 D_800F2F38[2] = { 0x00010001, 0 };

u16 D_800F2F40[16] = {
    0x0000,
    0xEDE1,
    0xCC40,
    0x8C41,
    0xD35F,
    0xF6C9,
    0xD543,
    0xFFB3,
    0xB639,
    0xFFFF,
    0x904F,
    0x807D,
    0xB56B,
    0xCE32,
    0xC2BB,
    0x8E40,
};

u32 D_800F2F60[] = {
    0x28010004,
    0x27010003,
    0x26010002,
    0x25010002,
    0x24010002,
    0x23010002,
    0x22010002,
    0x21010002,
    0x20010002,
    0x1F010002,
    0x1E010002,
    0x1D010002,
    0x1C010002,
    0x1B010002,
    0x1A010010,
    0x1B010002,
    0x1C010002,
    0x1D010002,
    0x1E010002,
    0x1F010002,
    0x20010002,
    0x21010002,
    0x22010002,
    0x23010002,
    0x24010002,
    0x25010002,
    0x26010002,
    0x27010003,
    0x28000104,
};

#ifdef VERSION_JP
const u32* D_800F2FD4[1] = { D_800F2F60 };
#else
const u32* D_800F2FD4[2] = { D_800F2F60, NULL };
#endif

s16 D_800F2FDC[2] = { 0x0300, 0x0600 };

void (*D_800F2FE0[8])(struct EngineObj*) = {
    func_80023624,
    func_80023684,
    func_80023698,
    func_800237E4,
    func_80023870,
    func_800238F0,
    func_80023970,
    func_800239E0,
};

union AnimationStep D_800F3000[10] = {
    { .packed = 0x00010004 },
    { .packed = 0x01010004 },
    { .packed = 0x02010002 },
    { .packed = 0x03010004 },
    { .packed = 0x04010004 },
    { .packed = 0x05010004 },
    { .packed = 0x06010004 },
    { .packed = 0x07010004 },
    { .packed = 0x08010003 },
    { .packed = 0x09000003 },
};

union AnimationStep D_800F3028[11] = {
    { .packed = 0x0A010002 },
    { .packed = 0x0B010002 },
    { .packed = 0x0A010002 },
    { .packed = 0x0B010002 },
    { .packed = 0x0A010002 },
    { .packed = 0x0B010002 },
    { .packed = 0x0C010003 },
    { .packed = 0x0D010003 },
    { .packed = 0x0E010003 },
    { .packed = 0x0F010003 },
    { .packed = 0x10000003 },
};

union AnimationStep D_800F3054[10] = {
    { .packed = 0x11010002 },
    { .packed = 0x12010002 },
    { .packed = 0x11010002 },
    { .packed = 0x12010002 },
    { .packed = 0x11010002 },
    { .packed = 0x12010002 },
    { .packed = 0x13010003 },
    { .packed = 0x14010003 },
    { .packed = 0x15010003 },
    { .packed = 0x16000003 },
};

union AnimationStep* D_800F307C[3] = { D_800F3028, D_800F3054, D_800F3000 };

s16 D_800F3088[16] = { -30, -26, -21, -18, -14, -10, -7, -3, 3, 7, 10, 14, 18, 21, 26, 30 };

s16 D_800F30A8[16] = { -22, -19, -17, -13, -10, -7, -4, -2, 2, 4, 7, 10, 13, 17, 19, 22 };

void (*D_800F30C8[])(struct MiscObj*) = {
    func_80023AA8,
    func_80023B98,
    func_80023C0C,
};

u8 D_800F30D4[16][2] = {
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 0, 0 },
    { 1, 1 },
    { 1, 0 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
};

struct HudSpriteOrigin D_800F30F4[8] = {
    { 0x20, 0x38, 0x7841 },
    { 0x27, 0x58, 0x7841 },
    { 0x20, 0x38, 0x7841 },
    { 0x15, 0x16, 0x7841 },
    { 0x1A, 0x16, 0x7841 },
    { 0x25, 0x14, 0x7801 },
    { 0x25, 0x14, 0x7841 },
    { 0x125, 0x41, 0x7841 },
};

struct PlayerGaugePosition D_800F3124[2] = {
    { 0x16, 0x4F },
    { 0x122, 0x4F },
};

u16 D_800F312C[4] = { 0x2341, 0x33BF, 0x0898, 0 };
