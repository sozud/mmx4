#include "test_runtime.h"
void armored_walker_pick_step(struct MainObj* arg0);
void iris_death_finish(struct MainObj*);
void iris_despawn(struct MainObj*);
void unused_ride_armor_set_walk_speed(struct MainObj*);
static const s16 positions[5][2] = { { 160, 120 }, { -96, 120 }, { 416, 120 }, { 160, -96 }, { 160, 336 } };
static const s8 air_states[] = { 0, 1, -1 };
static const s16 timers[] = { 0, 1, 2 };
static u32 actor_transition(u32 row)
{
    struct MainObj obj, expected;
    struct EngineObj engine_expected = engine_obj;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 kind = row % 4, edge = row / 4 % 5, phase = row / 20 % 3, facing = row / 60;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = kind == 0 ? 1 : kind == 1 ? 72
                                       : 66;
    obj.state = kind == 3 ? 3 : 1;
    obj.unk5 = kind == 3 ? phase != 0 : 4;
    obj.unk6 = 9;
    obj.unk7 = 10;
    obj.unk2 = 1;
    obj.on_screen = 7;
    obj.bg_offset = -1;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_pos.val = positions[edge][0] * 65536 + 0x1234;
    obj.y_pos.val = positions[edge][1] * 65536 + 0x5678;
    obj.x_speed = 0x13579;
    obj.y_speed = -0x2468;
    obj.air_state = air_states[phase];
    obj.unk7C = timers[phase];
    expected = obj;
    if (kind == 0) {
        expected.unk5 = phase ? 6 : 2;
        armored_walker_pick_step(&obj);
    } else if (kind == 1) {
        expected.x_speed = facing ? 0x16000 : -0x16000;
        unused_ride_armor_set_walk_speed(&obj);
    } else if (kind == 2) {
        expected.unk7C--;
        if (phase == 1)
            engine_expected.unkF = 0x40;
        expected.on_screen = edge == 0 || edge == 1 || edge == 3;
        iris_death_finish(&obj);
    } else {
        if (phase)
            memset(&expected, 0, 8);
        else
            expected.on_screen = edge == 0 || edge == 1 || edge == 3;
        iris_despawn(&obj);
    }
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "actor_cleanup_and_speed", NULL, NULL, 64, actor_transition },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 64;
