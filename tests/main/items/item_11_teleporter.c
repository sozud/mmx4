#include "test_runtime.h"

#include "support/state_cases.h"
void teleporter_despawn(struct ItemObj*);
void teleporter_main(struct ItemObj*);

static u8 teleporter_record;
#define si state_room.item
#define TP(x) (state_reset(0, 0, 0), si.active = 1, si.state = 1, si.x_pos.i.hi = x, si.y_pos.i.hi = 0x60, teleporter_main(&si))
static void tp_idle(void)
{
    TP(0x80);
}
static void tp_away(void) { TP(0x1000); }
static void tp_despawn(void)
{
    state_reset(0, 0, 0);
    teleporter_record = 0;
    si.active = 1;
    si.backref = (void*)&teleporter_record;
    teleporter_despawn(&si);
    state_extra = teleporter_record;
    si.backref = NULL;
}

static void (*const teleporter_states_cases[])(void) = {
    tp_idle,
    tp_away,
    tp_despawn,
};
static const u32 teleporter_states_expected[] = { 1u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_teleporter_states(u32 row)
{
    return object_run(teleporter_states_cases[row], row, &teleporter_states_expected[row * 10]);
}

void teleporter_spawn_beam(struct ItemObj*);
void teleporter_spawn_glow(struct ItemObj*);
struct Item11AnimationStep;
extern struct Item11AnimationStep* teleporter_animations[5];
static struct MiscObj pool_expected[64];
static const u32 frames[4] = { 8, 12, 0x11223344, 0x55667788 };
static u32 spawn(u32 row)
{
    struct ItemObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    u32 glow = row % 2, free_slot = row / 2 % 2, wait = row / 4 % 2, layer = row / 8, i;
    memset(&obj, 0, sizeof(obj));
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i == 63 && free_slot ? 0 : 1;
        misc_objects[i].id = 63;
        misc_objects[i].state = 5;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 2;
    }
    c_test_copy_words((u32*)pool_expected, (u32*)misc_objects, sizeof(pool_expected) / 4);
    g_Player.bg_offset = layer;
    player_before = g_Player;
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = glow ? 1 : 0;
    obj.sprite_frames = (const u8*)frames;
    obj.tail_ext.unk1.unk84.timer = wait ? 94 : 95;
    obj.unk15 = 0x40;
    obj.unk40 = 0x1234;
    obj.unk42 = 0x4567;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    expected = obj;
    expected.tail_ext.unk1.unk84.timer++;
    if (!wait && free_slot) {
        struct MiscObj* m = &pool_expected[63];
        m->active = 0x41;
        m->id = 11;
        m->unk2 = glow ? 2 : 1;
        m->bg_offset = layer;
        m->unk16 = glow ? 16 : 1;
        m->unk15 = obj.unk15;
        m->unk40 = obj.unk40;
        m->unk42 = obj.unk42;
        m->unk3C = (void*)obj.sprite_frames;
        m->animation_table = (u32**)teleporter_animations;
        m->x_pos = obj.x_pos;
        m->y_pos = obj.y_pos;
        m->ext.misc_11.active = 0;
        if (glow)
            expected.ext.owner = (struct MainObj*)&misc_objects[63];
        else
            expected.unk7C.misc = &misc_objects[63];
        expected.tail_ext.unk1.unk84.timer = 0;
        expected.unk6++;
    }
    if (glow)
        teleporter_spawn_glow(&obj);
    else
        teleporter_spawn_beam(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(c_test_word_difference((u32*)misc_objects, (u32*)pool_expected, sizeof(pool_expected) / 4) == 0);
    assert(frames[0] == 8 && frames[1] == 12 && frames[2] == 0x11223344 && frames[3] == 0x55667788);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "teleporter_states", 0, 0, COUNT(teleporter_states_cases), test_teleporter_states },
    { "beam_and_glow_timing_independent_full_pool_and_last_free_slot_all_layers", NULL, NULL, 24, spawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(teleporter_states_cases) + 24;
