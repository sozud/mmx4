// 80021DBC..8002771C
#include "common.h"
#include "main/125BC.h"
#include "main/55C4.h"
#include "main/13A8C.h"

struct FixedMatrix2 {
    s16 m00, m01;
    s16 m10, m11;
};

extern struct FixedMatrix2 D_800F2ADC[16];

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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
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
#include "pc_replay.h"

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
    restored.gameplay_locked = source->gameplay_locked;
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
    restored.player_lives = source->player_lives;
    restored.checkpoint_hp = source->checkpoint_hp;
    restored.max_hp = source->max_hp;
    restored.armor_parts = source->armor_parts;
    restored.arm_type = source->arm_type;
    for (i = 0; i < COUNT(restored.player_initial_data); i++) {
        restored.player_initial_data[i] = source->player_initial_data[i];
    }
    restored.palette_flags = source->palette_flags;
    restored.collected_upgrades = source->collected_upgrades;
    restored.sub_tanks[0] = source->sub_tanks[0];
    restored.sub_tanks[1] = source->sub_tanks[1];
    restored.sub_tanks[2] = source->sub_tanks[2];
    restored.unk5F = source->unk5F;
    restored.unk60 = source->unk60;
    restored.pad61[0] = source->pad61[0];
    restored.pad61[1] = source->pad61[1];
    restored.pad61[2] = source->pad61[2];
    engine_obj = restored;
}

void save_replay_engine(struct SerializedEngineObj* target)
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
    target->gameplay_locked = engine_obj.gameplay_locked;
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
    target->player_lives = engine_obj.player_lives;
    target->checkpoint_hp = engine_obj.checkpoint_hp;
    target->max_hp = engine_obj.max_hp;
    target->armor_parts = engine_obj.armor_parts;
    target->arm_type = engine_obj.arm_type;
    for (i = 0; i < COUNT(engine_obj.player_initial_data); i++) {
        target->player_initial_data[i] = engine_obj.player_initial_data[i];
    }
    target->palette_flags = engine_obj.palette_flags;
    target->collected_upgrades = engine_obj.collected_upgrades;
    target->sub_tanks[0] = engine_obj.sub_tanks[0];
    target->sub_tanks[1] = engine_obj.sub_tanks[1];
    target->sub_tanks[2] = engine_obj.sub_tanks[2];
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

#ifdef MMX4_SATURN
#define REPLAY_FRAMES 0xE10

void func_80021C14(void);
void player_update(void);
void update_weapon_objects(void);
void update_main_objects(void);
void update_shot_objects(void);
void update_visual_objects(void);
void update_effect_objects(void);
void update_item_objects(void);
void update_misc_objects(void);
void update_quad_objects(void);
void update_layer_objects(void);
void func_80028E24(void);
void func_80027850(void);
void func_80027D40(void);
void func_800281E8(void);
void func_8002A484(void);
void func_80021D84(void);
void func_80021CC8(void);
void CollisionRelated(struct PlayerObj*);
void saturn_gameplay_prepare(void);
void saturn_update_object_texture(void*);

void func_80021F34(void)
{
    struct ReplayData* replay = (struct ReplayData*)REPLAY_DATA;
    u16 held;

    saturn_gameplay_prepare();
    g_Player.input.buttons.previous = g_Player.input.buttons.held;
    if (replay->frame != REPLAY_FRAMES) {
        g_Player.input.buttons.held = replay->inputs[replay->frame];
        replay->frame++;
    } else {
        g_Player.input.buttons.held = 0;
    }
    held = g_Player.input.buttons.held;
    g_Player.pressed_input = (g_Player.input.buttons.previous ^ held) & held;
    func_80021C14();
    player_update();
    update_weapon_objects();
    update_main_objects();
    update_shot_objects();
    update_visual_objects();
    update_effect_objects();
    update_item_objects();
    update_misc_objects();
    update_quad_objects();
    func_80028E24();
    CollisionRelated(&g_Player);
    func_80027850();
    func_80027D40();
    func_800281E8();
    update_layer_objects();
    func_8002A484();
    func_80021D84();
    func_80021CC8();
    saturn_update_object_texture(GRAPHICS_OBJECT(&g_Player));
}
#else
INCLUDE_ASM("main/nonmatchings/125BC", func_80021F34);
#endif

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
