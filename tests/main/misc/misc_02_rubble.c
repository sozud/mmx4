#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mains/main_30_regen_turret.h"
#include "main/misc/misc_02_rubble.h"
#include "main/misc/misc_03_debris.h"
#include "weapon_resources.h"
extern void* regen_turret_animations[11];

#ifndef VERSION_DEMO
static u32 debris_case(u32 mode)
{
    static const u8 random_bytes[9] = { 120, 124, 137, 177, 43, 153, 228, 199, 114 };
    static const u16 final_random[4] = { 119, 3465, 28313, 43890 };
    struct MainObj owner, owner_before;
    struct MiscObj expected[64];
    struct PlayerObj player_before = g_Player;
    s32 frames[4] = { 16, 16, 16, 16 };
    u32 i, available = mode == 0 || mode == 5 ? 3 : mode - 1;
    u32 spawned = mode == 0 || mode == 5 ? 0 : available;
    s32 count = mode == 0 ? 0 : mode == 5 ? 0x100
                                          : 3;
    memset(&owner, 0, sizeof(owner));
    memset(misc_objects, 0, sizeof(misc_objects));
    owner.active = 0x41;
    owner.id = 30;
    owner.state = 1;
    owner.unk5 = 2;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 200 * 65536 + 0x5678;
    owner.unk40 = 0x456;
    owner.sprite_frames = (u8*)frames;
    owner.animation_table = (const u8* const*)regen_turret_animations;
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i >= 64 - available ? 0 : 1;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].unk7 = 5;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    owner_before = owner;
    memcpy(expected, misc_objects, sizeof(expected));
    cur_random = 119;
    for (i = 0; i < spawned; i++) {
        struct MiscObj* child = &expected[64 - available + i];
        child->active = 0x41;
        child->id = 3;
        child->unk2 = 1;
        child->unk15 = random_bytes[i * 3] & PLAYER_FACING_RIGHT;
        child->state = 0;
        child->unk5 = 0;
        child->unk6 = 0;
        child->x_pos.val = owner.x_pos.val + (random_bytes[i * 3 + 1] & 3) - 5;
        child->y_pos.val = owner.y_pos.val + (random_bytes[i * 3 + 2] & 3) + 7;
        child->ext.misc_2.unk58 = 5 + i;
        child->ext.misc_2.owner = &owner;
        child->unk42 = 0x8123;
        child->unk3C = frames;
        child->animation_table = (u32**)regen_turret_animations;
        child->unk40 = owner.unk40;
    }
    spawn_owner_debris(count, regen_turret_debris, &owner, 0x18123, -5, 7);
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(misc_objects, expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    for (i = 0; i < 5; i++)
        assert(regen_turret_debris[i] == i + 5);
    for (i = 0; i < 4; i++)
        assert(frames[i] == 16);
    assert(cur_random == final_random[spawned]);
    i = cur_random | ((u32)(u8)misc_objects[63].id << 16);
    return i;
}
static const u32 owner_debris_allocation_prefixes_cases_expected[] = { 0x270077u, 0x270077u, 0x30D89u, 0x36E99u, 0x3AB72u, 0x270077u };
#define OWNER_DEBRIS_CASES COUNT(owner_debris_allocation_prefixes_cases_expected)
#else
#define OWNER_DEBRIS_CASES 0
#endif

#include "support/pool_full.h"
static u32 pool_full_spawn_debris_offset_one(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spawn_debris_offset(1, pf_variants, &pf_self, 0, 0);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_spawn_debris_offset_none(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spawn_debris_offset(0, pf_variants, &pf_self, 0, 0);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_rubble_spawn_one(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    func_800C842C(1, pf_variants, &pf_self, 0x22, pf_table);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_rubble_spawn_none(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    func_800C842C(0, pf_variants, &pf_self, 0x22, pf_table);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_spawn_rubble_one(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    spawn_rubble(1, pf_variants, &pf_self, 0);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_spawn_debris_offset_one,
    pool_full_spawn_debris_offset_none,
    pool_full_rubble_spawn_one,
    pool_full_rubble_spawn_none,
    pool_full_spawn_rubble_one,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u, 0x50000u, 0x50000u };

extern u8 hatch_blast_break_debris[16];
static struct MiscObj pool_before[64];
static u32 empty(u32 row)
{
    struct ShotObj obj, before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 rubble = row % 2, full = row / 2 % 2, seed = row / 4, i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 40;
    obj.state = 1;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 422 * 65536 + 0x5678;
    before = obj;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = full;
    memcpy(pool_before, misc_objects, sizeof(pool_before));
    cur_random = seed ? 0x1000 : 0x1234;
    if (rubble)
        spawn_rubble(0, hatch_blast_break_debris, &obj, -1);
    else
        spawn_debris(0, hatch_blast_break_debris, &obj);
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(misc_objects, pool_before, sizeof(pool_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(cur_random == (seed ? 0x1000 : 0x1234));
    return 1;
}


#include "support/state_cases.h"
#define sm state_room.misc
static u32 rubble_frames[0x40], rubble_meta[0x40];
#define RUBBLE(st, stg, kind, setup) (state_reset(0, 0, 0), engine_obj.stage = stg, engine_obj.substage = 0, memset(rubble_frames, 0, sizeof(rubble_frames)), TEST_MENU_FRAMES = (u8*)rubble_frames, test_stage_graphics(rubble_meta), sm.active = 0x41, sm.state = st, sm.unk2 = kind, sm.ext.unk.unk54 = 7, sm.x_pos.i.hi = 0x80, sm.y_pos.i.hi = 0x60, sm.y_vel.val = 0x10000, sm.unk2C = 0x5000, cur_random = 0x1234, setup, rubble_update(&sm), state_extra = (u16)sm.unk42 | (u32)sm.animation_step.fields.frame_index << 16 | (u32)(u8)sm.on_screen << 24)
static void rb_start_stage_3(void) { RUBBLE(0, 3, 0, 0); }
static void rb_start_thrown(void) { RUBBLE(0, 2, 0, 0); }
static void rb_start_dropped(void) { RUBBLE(0, 2, 1, 0); }
static void rb_fall_shown(void) { RUBBLE(1, 2, 0, sm.on_screen = 0); }
static void rb_fall_hidden(void) { RUBBLE(1, 2, 0, sm.on_screen = 1); }
static void rb_fall_gone(void) { RUBBLE(1, 2, 0, sm.x_pos.i.hi = 0x1000); }

static void (*const rb_cases[])(void) = {
    rb_start_stage_3,
    rb_start_thrown,
    rb_start_dropped,
    rb_fall_shown,
    rb_fall_hidden,
    rb_fall_gone,
};
static const u32 rb_expected[] = {
    0x1u, 0x41u, 0x800000u, 0x600000u, 0x18000u, 0x50000u, 0x500000u, 0x50000u | OBJECT_CLUT(0x7987), 0x1070000u | OBJECT_CLUT(0x7987), 0u,
    0x1u, 0x41u, 0x800000u, 0x600000u, 0x18000u, 0x50000u, 0x500000u, 0x50000u | OBJECT_CLUT(0x7983), 0x1070000u | OBJECT_CLUT(0x7983), 0u,
    0x1u, 0x141u, 0x800000u, 0x600000u, 0x18000u, 0x50000u, 0x500000u, 0x50000u | VISUAL_STAGE_PALETTE(8), 0x1070000u | VISUAL_STAGE_PALETTE(8), 0u,
    0x1u, 0x41u, 0x800000u, 0x5F0000u, 0u, 0xB000u, 0x500000u, 0x50000u, 0x1000000u, 0u,
    0x1u, 0x41u, 0x800000u, 0x5F0000u, 0u, 0xB000u, 0x500000u, 0x50000u, 0u, 0u,
    0u, 0u, 0x10000000u, 0x600000u, 0u, 0x10000u, 0x500000u, 0x50000u, 0u, 0u,
};
static u32 test_rb(u32 row)
{
    return object_run(rb_cases[row], row, &rb_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "rubble_steps", 0, 0, COUNT(rb_cases), test_rb },
#ifndef VERSION_DEMO
    { "owner_debris_allocation_prefixes", NULL, owner_debris_allocation_prefixes_cases_expected, COUNT(owner_debris_allocation_prefixes_cases_expected), debris_case },
#endif
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "zero_count_debris_API_preserves_source_pools_and_random_state", NULL, NULL, 8, empty },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = OWNER_DEBRIS_CASES + COUNT(pool_full_cases) + 8 + COUNT(rb_cases);
