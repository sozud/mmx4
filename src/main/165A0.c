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

void func_80024260(void);

void func_80024E70(void);

void func_80024F5C(struct PlayerObj* arg0);

void func_8002509C(struct PlayerObj* arg0);

void func_80025588(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4);

void func_800257BC(struct PlayerObj* arg0);

void func_80025CDC(void);

/* EU always uses the getTPage layout; US/JP pick it from GetGraphType(). */
#ifdef VERSION_EU
#define BG_TPAGE(tp, abr, x, y) getTPage(tp, abr, x, y)
#else
#define BG_TPAGE(tp, abr, x, y)                                                            \
    ((GetGraphType() == 1 || GetGraphType() == 2)                                          \
            ? (((tp)&3) << 9) | (((abr)&3) << 7) | (((y)&0x300) >> 3) | (((x)&0x3FF) >> 6) \
            : getTPage(tp, abr, x, y))
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

void func_80026118(void)
{
    u32 var_a1;
    u8 temp_v0;
    u8* var_a0;
    u8* var_a2;

    var_a0 = D_8010FFDC[engine_obj.stage][engine_obj.substage];
    var_a2 = SP_BG_TILEMAP;
    for (var_a1 = 0; var_a1 < (u32)(layout_size * 3); var_a1++) {
        temp_v0 = *var_a0;
        var_a0 += 1;
        *var_a2 = temp_v0;
        var_a2 += 1;
    }
    func_800261B4(-1);
}
void func_800261B4(s32 arg0)
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

INCLUDE_ASM("main/nonmatchings/165A0", func_800262B8);
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

    SP_BG_SPRITE_COUNT = 0;
    var_s0 = 0;
    do {
        if (background_objects[var_s0].unk4C != 0) {
            func_800262B8(var_s0 & 0xFF);
        }
        var_s0 += 1;
    } while (var_s0 < 3);
    func_8002728C();
    func_80026720();
    bg_obj = background_objects;
    SP_BG_PRIM_CURSOR = &D_8015D9D0[SP_DRAW_BUFFER];
    bg_num = 0;
    do {
        if (bg_obj->unk3 != 0) {
            func_800267D4(bg_num);
            func_80026AA0(bg_num);
            func_80026894(bg_num);
        }
        bg_obj += 1;
        bg_num += 1;
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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/165A0", func_800267D4);
#else
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
#endif

INCLUDE_ASM("main/nonmatchings/165A0", func_80026894);

INCLUDE_ASM("main/nonmatchings/165A0", func_80026AA0);

INCLUDE_ASM("main/nonmatchings/165A0", func_80026CEC);

INCLUDE_ASM("main/nonmatchings/165A0", func_800270F8);
void func_8002728C(void)
{
    s32 temp_s1;
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

INCLUDE_ASM("main/nonmatchings/165A0", func_80027344);

INCLUDE_ASM("main/nonmatchings/165A0", func_800275DC);
