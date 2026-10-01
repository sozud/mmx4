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

void func_80023CA4(struct MiscObj* arg0);

void func_80023CE0();

void func_80023D30(void);

void func_80023D68(void);

void func_80023D90(void);

// some kind of init?
void init_objects(void);

void func_800241E8(void);

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
#ifdef MMX4_WIN32
u8 x_ready_text_flags[] = { 0, 0, 0, 0 };
u8 x_ready_text_flags_4[] = { 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 };
u8 x_ready_text_flags_28[] = { 0, 0, 0, 0 };
u8 x_ready_text_flags_32[] = { 1, 1, 0, 0 };
u8 x_ready_text_flags_36[] = { 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 };
u8 x_ready_text_flags_48[] = { 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0 };
u8 x_ready_text_flags_64[] = { 0, 1, 1, 0, 1, 1, 1, 0 };
u8 x_ready_text_flags_72[] = { 1, 0, 1, 1, 1, 0, 1, 0 };
u8 x_ready_text_flags_80[] = { 0, 1, 1, 0, 1, 1, 1, 0 };
u8 x_ready_text_flags_88[] = { 0, 0, 0, 0 };

static u8* x_ready_text[] = {
    x_ready_text_flags,
    x_ready_text_flags_4,
    x_ready_text_flags_28,
    x_ready_text_flags_32,
    x_ready_text_flags_36,
    x_ready_text_flags_48,
    x_ready_text_flags_64,
    x_ready_text_flags_72,
    x_ready_text_flags_80,
    x_ready_text_flags_88,
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

#if defined(VERSION_JP) || defined(MMX4_WIN32)
const u32* D_800F2FD4[1] = { D_800F2F60 };
#else
const u32* D_800F2FD4[2] = { D_800F2F60, NULL };
#endif

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

INCLUDE_ASM("main/nonmatchings/14A60", func_80024334);

INCLUDE_ASM("main/nonmatchings/14A60", func_80024920);

INCLUDE_ASM("main/nonmatchings/14A60", func_80024B9C);
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

    if (arg0->weapon != 0) {
        temp_s0 = arg0->weapon_energy[arg0->weapon];
        func_80025588(0x24, 0x29, 0x4F - temp_s0, 0x4F, 0);
        temp_v0_2 = player_weapon_energy.hud.health_divisors[arg0->shot_types[0]];
        temp = temp_s0 / temp_v0_2;
        func_80025188(3, (temp / 10) + 0x3B);
        func_80025188(4, (temp % 10) + 0x3B);

        if (arg0->weapon == 3) {
            func_80025188(6, arg0->weapon + 0x4E);
        } else {
            func_80025188(5, arg0->weapon + 0x4E);
        }

        func_80025188(2, 0x4E);
    }
}
void func_8002509C(struct PlayerObj* arg0)
{
    s8 temp_s0;
    s8 temp_s1;

    if (arg0->boss_flags & 0x20) {
        temp_s0 = arg0->weapon_energy[0];
        func_80025588(0x24, 0x29, 0x4F - temp_s0, 0x4F, 0);
        temp_s1 = temp_s0 / 12;
        func_80025188(3, (temp_s1 / 10) + 0x3B);
        func_80025188(4, (temp_s1 % 10) + 0x3B);
        func_80025188(2, 0x4E);
    }
}

INCLUDE_ASM("main/nonmatchings/14A60", func_80025188);

INCLUDE_ASM("main/nonmatchings/14A60", func_800253F0);
void func_80025588(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4)
{
    u32 color;
    u32 temp_r;
    s8 temp_g;
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
        if ((engine_obj.stage != 0x2 || engine_obj.substage != 0) && g_FilterAmountR == ((u16)g_FilterAmountG >> 5) && g_FilterAmountR == ((u16)g_FilterAmountB >> 10)) {
            if (*(u8*)&g_FilterModeR != 0) {
                var_r = g_FilterAmountR <= (color & 0x1F) ? (color & 0x1F) - g_FilterAmountR : 0;
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
                var_b = temp_v1 < (u16)g_FilterAmountB ? 0 : temp_v1 - (u16)g_FilterAmountB;
            } else {
                temp_v1 += (u16)g_FilterAmountB;
                if (temp_v1 < 0x7C01U) {
                    var_b = temp_v1;
                } else {
                    var_b = 0x7C00;
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

    if (player->armor_parts & 8) {
        func_8002588C(arg0, 3, 0x7843);
    }
    if (player->armor_parts & 1) {
        func_8002588C(arg0, 0, 0x7843);
    }
    if (player->armor_parts & 4) {
        func_8002588C(arg0, 2, (player->arm_type == 2 ? 0x7844 : 0x7843));
    }
    if (player->armor_parts & 2) {
        func_8002588C(arg0, 1, 0x7843);
    }
}

INCLUDE_ASM("main/nonmatchings/14A60", func_8002588C);
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
