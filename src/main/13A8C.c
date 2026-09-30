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

void func_80021DBC(s16* arg0, s16* arg1, s32 arg2);

void func_80021E3C(void);

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


#define PSX_MAIN_OBJECTS_ADDRESS 0x8013BED0
#define PSX_MAIN_OBJ_SIZE 0x9C

struct MainObj* restore_replay_main_object(u32 address);

u32 save_replay_main_object(struct MainObj* object);

void restore_replay_engine(const struct SerializedEngineObj* source);

void save_replay_engine(struct SerializedEngineObj* target);
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

void func_80021E74(void);





void func_80022074(void);

void func_800220C4(void);

void func_80022138(void);

// start_dialogue




void func_8002328C(struct AbcObj*);

#define CONFIG D_801397DC

void func_80022730(struct AbcObj* arg0);

#undef CONFIG

extern u32 D_800F2F38[];

extern struct DialogueGlyphData D_801396C8;

extern struct MiscObj* D_801397C0;

extern struct MiscObj* D_801397C4;

extern u8 D_801397D8;

extern s16 D_801397E0;

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

    func_8001663C(MUSIC_STAFF_ROLL, 0x7F);
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

INCLUDE_ASM("main/nonmatchings/13A8C", func_80023AA8);
void func_80023B98(struct MiscObj* arg0)
{
    s8 timer;

    timer = arg0->ext.misc_11.active;
    if (timer == 0) {
        animate_object(arg0);
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
