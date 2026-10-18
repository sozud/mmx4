#include "test_runtime.h"
#include "main/effects/effect_12_enemy_spawner.h"
#include "main/195B4.h"

static s32 frames[8] = { 16, 20, 24, 28, 1, 2, 3, 4 };
static u32 metadata[4] = { 0x400, 0x480, 0x500, 0x580 };
static u32 spawner_case(u32 mode)
{
    struct EffectObj obj, expected;
    struct MainObj inactive_child, inactive_before, pool_expected[48];
    struct EngineObj engine_expected;
    struct PlayerObj player_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 i, slot = mode == 4 ? 3 : mode == 7 ? 0
                                            : 1;
    memset(&obj, 0, sizeof(obj));
    memset(&inactive_child, 0, sizeof(inactive_child));
    memset(main_objects, 0, sizeof(main_objects));
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    for (i = 0; i < 48; i++) {
        main_objects[i].active = i == 47 && (mode == 4 || mode == 6 || mode == 7) ? 0 : 1;
        main_objects[i].id = 39;
        main_objects[i].state = 40;
        main_objects[i].unk2 = 9;
        main_objects[i].unk5 = 3;
        main_objects[i].unk6 = 4;
        main_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        main_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    inactive_child.id = 28;
    inactive_child.state = 3;
    inactive_child.unk2 = 4;
    inactive_before = inactive_child;
    obj.active = 1;
    obj.id = 12;
    obj.state = 1;
    obj.unk6 = 7;
    obj.x_pos.val = (mode == 0 ? 700 : 100) * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.unk5 = mode <= 2 || mode == 13 ? 0 : mode <= 7 ? 1
        : mode <= 9                                    ? 2
        : mode <= 11                                   ? 3
                                                       : 4;
    obj.ext.effect_12.child_count = mode == 3 || mode == 15 ? 0 : mode == 7 ? 1
                                                                            : 4;
    obj.ext.effect_12.child_id = 0x86;
    obj.ext.effect_12.child_subtype = 7;
    obj.ext.effect_12.cooldown = mode == 4 ? 2 : 0;
    obj.ext.effect_12.timer = mode == 10 ? 1 : 2;
    obj.ext.effect_12.spawned = mode >= 8 ? 4 : 0;
    if (mode != 3 && mode != 7 && mode != 15)
        obj.ext.effect_12.children[0] = &main_objects[0];
    if (mode == 4 || mode == 6 || mode == 12)
        obj.ext.effect_12.children[1] = &inactive_child;
    if (mode == 9)
        obj.ext.effect_12.children[3] = &main_objects[1];
    g_Player.x_pos.val = (mode == 2 ? -100 : mode == 13 ? 300
                                                        : 150)
            * 65536
        + 0xBEEF;
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)frames;
    if (mode == 14)
        obj.unk5 = -128;
    if (mode == 15)
        obj.unk5 = 2;
    expected = obj;
    player_expected = g_Player;
    engine_expected = engine_obj;
    memcpy(pool_expected, main_objects, sizeof(pool_expected));
    if (mode == 0)
        expected.state = 2;
    else {
        if (mode == 4 || mode == 6 || mode == 12)
            expected.ext.effect_12.children[1] = NULL;
        if (mode == 1)
            expected.unk5 = 1;
        if (mode == 4 || mode == 6 || mode == 7) {
            expected.ext.effect_12.children[slot] = &main_objects[47];
            expected.ext.effect_12.spawned = 1;
            expected.ext.effect_12.cooldown = mode == 6 ? 30 : 32;
            if (mode == 7)
                expected.unk5 = 2;
            pool_expected[47].active = 0x41;
            pool_expected[47].id = 0x86;
            pool_expected[47].unk2 = 7;
            pool_expected[47].x_pos.val = obj.x_pos.val;
            pool_expected[47].y_pos.val = obj.y_pos.val;
            pool_expected[47].unk40 = 9;
            pool_expected[47].unk42 = 0x784C;
            pool_expected[47].sprite_frames = (u8*)frames + 20;
        }
        if (mode == 8 || mode == 15) {
            expected.unk5 = 3;
            expected.ext.effect_12.spawned = 0;
            expected.ext.effect_12.cooldown = 0;
            expected.ext.effect_12.timer = 0x60;
        }
        if (mode == 10 || mode == 11) {
            expected.ext.effect_12.timer--;
            if (mode == 10)
                expected.unk5 = 0;
        }
    }
    assert(s_StageMainIds[11][1][1] == 0x86 && (u8)func_8002938C(0x86) == 1);
    func_800B8114(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)main_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(inactive_child) / 4; i++)
        assert(((u32*)&inactive_child)[i] == ((u32*)&inactive_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_expected) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_expected)[i]);
    for (i = 0; i < 4; i++) {
        assert(frames[i] == 16 + i * 4 && frames[i + 4] == i + 1);
        assert(metadata[i] == 0x400 + i * 0x80);
    }
    assert(D_801406A8 == metadata && SP_MENU_FRAMES == frames);
    i = obj.unk5 | ((u32)obj.ext.effect_12.cooldown << 8) | ((u32)obj.ext.effect_12.spawned << 24);
    return i;
}
#define CASE(m)                  \
    static u32 spawner_##m(void) \
    {                            \
        return spawner_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
CASE(10)
CASE(11)
CASE(12)
CASE(13)
CASE(14)
CASE(15)
#define ENTRY(m) spawner_##m,
static const CTestCase enemy_spawner_child_graph_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) ENTRY(10) ENTRY(11) ENTRY(12) ENTRY(13) ENTRY(14) ENTRY(15) };
static const u32 enemy_spawner_child_graph_cases_expected[] = { 0x0u, 0x1u, 0x0u, 0x1u, 0x1002001u, 0x1u, 0x1001E01u, 0x1002002u, 0x3u, 0x4000002u, 0x4000000u, 0x4000003u, 0x4000004u, 0x4000000u, 0xFFFFFF80u, 0x3u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "enemy_spawner_child_graph", enemy_spawner_child_graph_cases, enemy_spawner_child_graph_cases_expected, COUNT(enemy_spawner_child_graph_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(enemy_spawner_child_graph_cases);
