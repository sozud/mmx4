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

void func_8002328C(struct AbcObj* arg0);

void func_80023624(struct EngineObj* arg0);

void func_80023684(struct EngineObj* arg0);

void func_80023698(struct EngineObj* arg0);

void func_800237E4(struct EngineObj* arg0);

void func_80023870(struct EngineObj* arg0);

void func_800238F0(struct EngineObj* arg0);

void func_80023970(struct EngineObj* arg0);

void func_800239E0(struct EngineObj* arg0);

void func_80023A54(struct EngineObj* arg0);

void func_80023B98(struct MiscObj* arg0);

void func_80023C0C(struct MiscObj* arg0);

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
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/144A4", init_objects);
#else
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
#endif
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
