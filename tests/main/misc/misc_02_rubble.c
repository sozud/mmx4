#include "test_runtime.h"
#include "main/mains/main_30_regen_turret.h"
#include "main/misc/misc_02_rubble.h"
extern void* regen_turret_animations[11];

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
        child->unk15 = random_bytes[i * 3] & 0x40;
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
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(expected) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 8; i++)
        assert(regen_turret_debris[i] == (i < 5 ? i + 5 : 0));
    for (i = 0; i < 4; i++)
        assert(frames[i] == 16);
    assert(cur_random == final_random[spawned]);
    i = cur_random | ((u32)(u8)misc_objects[63].id << 16) | ((u32)(u8)misc_objects[63].unk15 << 24);
    return i;
}
static const u32 owner_debris_allocation_prefixes_cases_expected[] = { 0x270077u, 0x270077u, 0x40030D89u, 0x36E99u, 0x4003AB72u, 0x270077u };

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
static const CTestCase pool_full_cases[] = {
    pool_full_spawn_debris_offset_one,
    pool_full_spawn_debris_offset_none,
    pool_full_rubble_spawn_one,
    pool_full_rubble_spawn_none,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u, 0x50000u };

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

const struct CTestGroup c_test_groups[] = {
    { "owner_debris_allocation_prefixes", NULL, owner_debris_allocation_prefixes_cases_expected, COUNT(owner_debris_allocation_prefixes_cases_expected), debris_case },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "zero_count_debris_API_preserves_source_pools_and_random_state", NULL, NULL, 8, empty },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(owner_debris_allocation_prefixes_cases_expected) + COUNT(pool_full_cases) + 8;
