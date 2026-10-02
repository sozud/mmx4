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

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/125BC", func_80021E3C);
#else
void func_80021E3C(void)
{
#ifdef MMX4_PC
    engine_obj.cur_character = REPLAY_DATA[0x4F];
    engine_obj.stage = REPLAY_DATA[0x18];
    engine_obj.substage = REPLAY_DATA[0x19];
#else
    engine_obj.cur_character = D_801F604F;
    engine_obj.stage = D_801F6018;
    engine_obj.substage = D_801F6019;
#endif
}
#endif

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
    main_bss_state.frame_counter = replay->flags;
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

// start_dialogue

void func_8002328C(struct AbcObj*);

#undef CONFIG

extern struct DialogueGlyphData D_801396C8;

extern struct MiscObj* D_801397C0;

extern struct MiscObj* D_801397C4;

extern u8 D_801397D8;

extern s16 D_801397E0;

extern s32* D_8013BD50[][8];

extern s32 D_8013E2F0[][8];

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
