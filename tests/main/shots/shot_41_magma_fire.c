#include "test_runtime.h"
#include "main/shots/shot_41_magma_fire.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/sprite_animations.h"
void magma_fire_pillar(struct ShotObj*);
extern void* magma_dragoon_animations[38];
extern u8 magma_fire_wave_hit_box[4], magma_fire_pillar_hit_boxes[1][4];
extern u8 magma_fire_ember_hit_box[4], magma_fire_ember_terrain_box[4];
extern u8 magma_fire_burst_hit_box[4], magma_fire_burst_terrain_box[4];
extern s16 magma_fire_wave_offsets[8];

static s32 sprites[4] = { 8, 12, 0x11223344, 0x55667788 };
static u32 fire_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_expected;
    struct BackgroundObj backgrounds_before[3];
    u32 i, kind = mode < 2 ? 0 : mode < 6 ? 1
        : mode == 6                       ? 2
        : mode == 7                       ? 3
                                          : 4;
    u32 animation = kind == 0 ? 28 : kind == 1 ? 29
        : kind == 2                            ? 31
                                               : 27;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    owner.active = 0x41;
    owner.id = 65;
    owner.state = 1;
    owner.unk5 = 7;
    owner.unk40 = 0x2345;
    owner.unk42 = 0x8123;
    owner.bg_offset = -1;
    owner.unk15 = mode & 1 ? 0x40 : 0;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 100 * 65536 + 0x5678;
    owner.animation_table = (const u8* const*)magma_dragoon_animations;
    owner.sprite_frames = (const u8*)sprites;
    obj.active = 0x41;
    obj.id = 41;
    obj.state = 1;
    obj.unk2 = kind;
    obj.unk7 = mode == 2 ? 1 : mode == 3 ? 7
        : mode == 4                      ? 2
        : mode == 5                      ? 3
                                         : 0;
    obj.unk15 = 0x20;
    obj.unk16 = 3;
    obj.unk5C = 9;
    obj.unk60 = 11;
    obj.unk28 = 0x123456;
    obj.unk2C = 0x654321;
    obj.x_pos.val = 50 * 65536 + 0xABCD;
    obj.y_pos.val = 60 * 65536 + 0xFEDC;
    obj.x_vel.val = 123;
    obj.y_vel.val = 456;
    obj.timer = 17;
    obj.unk7C = &owner;
    expected = obj;
    owner_expected = owner;
    expected.unk40 = owner.unk40;
    expected.animation_table = (u32**)magma_dragoon_animations;
    expected.unk3C = (void*)sprites;
    expected.unk5C = 0;
    expected.unk16 = 1;
    expected.unk42 = 0x123;
    expected.bg_offset = -1;
    if (kind < 4) {
        expected.unk54 = NULL;
        expected.unk58.data = (u8*)(kind == 1 ? D_80105FF0 : D_801060F0);
        expected.unk60 = kind == 0 ? 9 : kind == 3 ? 6
                                                   : 4;
        expected.state = 2;
        expected.unk5 = kind + 2;
        expected.unk15 = kind == 1 ? 0 : owner.unk15;
        if (kind == 0) {
            expected.unk50.data = magma_fire_wave_hit_box;
            expected.unk68 = NULL;
            expected.x_pos.val = owner.x_pos.val + (owner.unk15 ? 24 * 65536 : -24 * 65536);
            expected.y_pos.val = owner.y_pos.val + 16 * 65536;
            expected.x_vel.val = owner.unk15 ? 6 * 65536 : -6 * 65536;
            expected.y_vel.val = 2 * 65536;
            expected.timer = 7;
        } else if (kind == 1) {
            expected.unk50.data = (u8*)magma_fire_pillar_hit_boxes;
            expected.unk68 = NULL;
            expected.x_pos.val = owner.x_pos.val + (owner.unk15 ? -16 * 65536 : 16 * 65536);
            expected.y_pos.val = owner.y_pos.val - 32 * 65536;
            expected.x_vel.val = magma_fire_wave_offsets[obj.unk7] * 4096;
            expected.y_vel.val = 5 * 65536;
        } else if (kind == 2) {
            expected.unk50.data = magma_fire_ember_hit_box;
            expected.unk68 = (struct Unk_unk68*)magma_fire_ember_terrain_box;
            expected.x_pos.val = owner.x_pos.val;
            expected.y_pos.val = owner.y_pos.val - 64 * 65536;
            expected.x_vel.val = owner.unk15 ? 4 * 65536 : -4 * 65536;
            expected.y_vel.val = 0x1C000;
            expected.unk28 = 0;
            expected.unk2C = 0x1300;
        } else {
            expected.unk50.data = magma_fire_burst_hit_box;
            expected.unk68 = (struct Unk_unk68*)magma_fire_burst_terrain_box;
            expected.timer = 3;
        }
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        ANIMATED_OBJECT(&expected)->animation_cursor = magma_dragoon_animations[animation];
        expected.animation_step.packed = *(u32*)magma_dragoon_animations[animation];
    }
    expected.on_screen = 1;
    func_800A56E4(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    assert(sprites[0] == 8 && sprites[1] == 12 && sprites[2] == 0x11223344 && sprites[3] == 0x55667788);
    return (u8)obj.unk5 | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_vel.i.hi << 16);
}
static const u32 magma_fire_owner_animation_start_cases_expected[] = { 0xFFFA1C02u, 0x61C02u, 0x1D03u, 0x1D03u, 0xFFFF1D03u, 0xFFFF1D03u, 0xFFFC1F04u, 0x1B05u, 0x0u };

#include "support/animation_endings.h"
ENDING_CASE(3)
ENDING_CASE(4)
ENDING_CASE(5)
ENDING_CASE(6)
static const CTestCase pillar_repeat_ending_cases[] = { ENDING_ENTRY(3) ENDING_ENTRY(4) ENDING_ENTRY(5) ENDING_ENTRY(6) };

static const u32 pillar_repeat_ending_cases_expected[] = { 0x20401u, 0x20401u, 0x201u, 0x10002u };
#include "support/state_cases.h"

static struct MainObj magma_owner;
#define ss state_room.shot
#define PILLAR(phase) (state_reset(3, phase, 0), memset(&magma_owner, 0, sizeof(magma_owner)), magma_owner.state = 1, ss.unk7C = (struct WeaponObj*)&magma_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define PILLAR_SEEN() (state_extra = (u16)ss.timer | (u32)(u8)ss.unk8A << 16)
static void mf_spawn(void)
{
    PILLAR(0);
    ss.unk7 = 2;
    cur_random = 1;
    magma_fire_pillar(&ss);
    PILLAR_SEEN();
}
static void mf_spawn_visible(void)
{
    PILLAR(0);
    ss.on_screen = 1;
    ss.x_pos.i.hi = 0x1000;
    magma_fire_pillar(&ss);
}
static void mf_spawn_owner_gone(void)
{
    PILLAR(0);
    magma_owner.state = 2;
    ss.x_pos.i.hi = 0x1000;
    magma_fire_pillar(&ss);
}
static void mf_wait(void)
{
    PILLAR(1);
    ss.timer = 3;
    magma_fire_pillar(&ss);
    PILLAR_SEEN();
}
static void mf_shake(void)
{
    PILLAR(1);
    ss.timer = 1;
    ss.y_vel.val = 0x10000;
    magma_fire_pillar(&ss);
    PILLAR_SEEN();
}
static void mf_rise_volcano(void)
{
    PILLAR(1);
    ss.y_pos.i.hi = 0x2C0;
    magma_fire_pillar(&ss);
}
static void mf_rise_rematch(void)
{
    PILLAR(1);
    engine_obj.stage = 0xC;
    ss.y_pos.i.hi = 0x700;
    magma_fire_pillar(&ss);
}
static void mf_rise_below(void)
{
    PILLAR(1);
    engine_obj.stage = 0xC;
    ss.y_pos.i.hi = 0x600;
    magma_fire_pillar(&ss);
}
static void mf_column_wait(void)
{
    PILLAR(0);
    ss.animation_step.fields.relative_step = 1;
    func_800A5E60(&ss);
}
static void mf_column_volcano_left(void)
{
    PILLAR(0);
    engine_obj.stage = 3;
    func_800A5E60(&ss);
}
static void mf_column_volcano_right(void)
{
    PILLAR(0);
    engine_obj.stage = 3;
    ss.unk15 = 0x40;
    func_800A5E60(&ss);
}
static void mf_column_rematch(void)
{
    PILLAR(0);
    engine_obj.stage = 0xC;
    ss.unk15 = 0x40;
    func_800A5E60(&ss);
}

static void (*const magma_fire_pillar_states_cases[])(void) = {
    mf_spawn,
    mf_spawn_visible,
    mf_spawn_owner_gone,
    mf_wait,
    mf_shake,
    mf_rise_volcano,
    mf_rise_rematch,
    mf_rise_below,
    mf_column_wait,
    mf_column_volcano_left,
    mf_column_volcano_right,
    mf_column_rematch,
};
static const u32 magma_fire_pillar_states_expected[] = { 0x2010300u, 0xFF000000u, 0x1510000u, 0xFFE00000u, 0xFFFA0000u, 0xFFFA0000u, 0u, 0x50000u, 0x40074u, 0u, 0x300u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10300u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0x10300u, 0u, 0x800000u, 0x5F0000u, 0u, 0x10000u, 0u, 0x40000u, 0u, 0u, 0x20300u, 0xFF000000u, 0x800000u, 0x2B80000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20300u, 0xFF000000u, 0x800000u, 0x6C80000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10300u, 0u, 0x800000u, 0x6000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x300u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10300u, 0xFF000000u, 0x14180000u, 0x18C0000u, 0u, 0x40000u, 0u, 0x50000u, 0u, 0u, 0x10300u, 0xFF400000u, 0x15A80000u, 0x18C0000u, 0u, 0x40000u, 0u, 0x50000u, 0u, 0u, 0x10300u, 0xFF400000u, 0x2C80000u, 0x18C0000u, 0u, 0x40000u, 0u, 0x50000u, 0u, 0u };

static u32 test_magma_fire_pillar_states(u32 row)
{
    return object_run(magma_fire_pillar_states_cases[row], row, &magma_fire_pillar_states_expected[row * 10]);
}

void magma_fire_burst(struct ShotObj*);
extern void* magma_dragoon_animations[38];
static const u32 burst_words[2][5] = {
    { 0xC6010001, 0xC7010001, 0xC8010001, 0xC9010001, 0xCA000001 },
    { 0xAB010002, 0x76010001, 0xAB010001, 0xAC010001, 0xADFE0001 },
};
static const s16 positions[][2] = { { 160, 120 }, { -49, 120 }, { 368, 120 }, { 160, -49 }, { 160, 288 } };
static u32 burst(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 step = row % 5, edge = row / 5 % 5, facing = row / 25 % 2, variant = row / 50, animation = variant ? 31 : 34;
    const union AnimationStep* commands = (const union AnimationStep*)magma_dragoon_animations[animation];
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 41;
    obj.state = 1;
    obj.unk5 = 6;
    obj.unk6 = 3;
    obj.bg_offset = 0;
    obj.on_screen = 7;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_pos.val = positions[edge][0] * 65536 + 0x1234;
    obj.y_pos.val = positions[edge][1] * 65536 + 0x5678;
    obj.x_vel.val = facing ? 0x18000 : -0x18000;
    obj.y_vel.val = -0x8000;
    obj.animation_table = (u32**)magma_dragoon_animations;
    set_animation(&obj, animation);
    assert(commands[step].packed == burst_words[variant][step]);
    obj.animation_cursor = (u32*)&commands[step];
    obj.animation_step.packed = burst_words[variant][step];
    expected = obj;
    expected.x_pos.val += obj.x_vel.val;
    expected.y_pos.val -= obj.y_vel.val;
    if (variant && step == 0)
        expected.animation_step.fields.duration = 1;
    else if (step < 4) {
        expected.animation_cursor = (u32*)&commands[step + 1];
        expected.animation_step.packed = burst_words[variant][step + 1];
    } else if (variant) {
        expected.animation_cursor = (u32*)&commands[2];
        expected.animation_step.packed = burst_words[1][2];
    }
    if (variant && step == 3) {
        expected.state = 2;
        expected.unk5 = expected.unk6 = 0;
    }
    expected.on_screen = expected.x_pos.i.hi >= -48 && expected.x_pos.i.hi < 368 && expected.y_pos.i.hi >= -48 && expected.y_pos.i.hi < 288;
    magma_fire_burst(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

extern void* magma_dragoon_animations[38];
static struct ShotObj pool_expected[32];
static u32 spread(u32 row)
{
    struct MainObj owner, owner_before;
    struct ShotObj* obj = &shot_objects[0];
    struct ShotObj* expected = &pool_expected[0];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    u32 free = row % 2, face = row / 2 % 2, low = row / 4 % 2, layer = row / 8, i;
    engine_obj.stage = 4;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    g_Player.spike_immune = 1;
    player_before = g_Player;
    background_objects[layer].x_pos.val = 5333 << 16;
    background_objects[layer].y_pos.val = 526 << 16;
    background_before = background_objects[layer];
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 65;
    owner.state = 1;
    owner.hp = 48;
    owner.unk5 = low ? 11 : 10;
    owner.unk6 = 1;
    owner.unk15 = face ? 0x40 : 0;
    owner.bg_offset = layer;
    owner.x_pos.i.hi = 5493;
    owner.y_pos.i.hi = 646;
    owner.animation_table = (const u8* const*)magma_dragoon_animations;
    owner_before = owner;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i == 31 && free ? 0 : 1;
    obj->active = 0x41;
    obj->id = 41;
    obj->unk2 = 3;
    obj->unk7C = WEAPON_OBJECT(&owner);
    obj->x_pos.i.hi = owner.x_pos.i.hi + (face ? 23 : -23);
    obj->y_pos.i.hi = owner.y_pos.i.hi + (low ? 40 : 0);
    func_800A56E4(obj);
    assert(obj->state == 1 && obj->unk5 == 5 && obj->timer == 3 && obj->animation_step.packed == 0x84010002);
    func_800A60D0(obj);
    func_800A60D0(obj);
    assert(obj->timer == 1 && obj->animation_step.packed == 0x85010002);
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    expected->timer = 0;
    expected->animation_step.packed = 0x85010001;
    if (free) {
        struct ShotObj* s = &pool_expected[31];
        s->active = 0x41;
        s->id = 41;
        s->unk2 = 3;
        s->unk7C = WEAPON_OBJECT(obj);
        s->x_pos.i.hi = obj->x_pos.i.hi + (face ? 24 : -24);
        s->y_pos.i.hi = obj->y_pos.i.hi;
        s->timer = 3;
    }
    func_800A60D0(obj);
    c_test_same_words(shot_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[layer], &background_before, sizeof(background_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "magma_fire_pillar_states", 0, 0, COUNT(magma_fire_pillar_states_cases), test_magma_fire_pillar_states },
    { "magma_fire_owner_animation_start", NULL, magma_fire_owner_animation_start_cases_expected, COUNT(magma_fire_owner_animation_start_cases_expected), fire_case },
    { "pillar_repeat_ending", pillar_repeat_ending_cases, pillar_repeat_ending_cases_expected, COUNT(pillar_repeat_ending_cases), 0 },
    { "burst_configured_shipped_animations", NULL, NULL, 55, burst },
    { "own_Magma_high_low_fire_factory_spread_after_two_ticks_full_shot_pool", NULL, NULL, 24, spread },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(magma_fire_pillar_states_cases) + COUNT(magma_fire_owner_animation_start_cases_expected) + COUNT(pillar_repeat_ending_cases) + 55 + 24;
