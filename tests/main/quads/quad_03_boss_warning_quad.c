#include "test_runtime.h"
#include "main/quads/quad_03_boss_warning_quad.h"
extern struct QuadMotionData boss_warning_quad_motions[22];
extern u8 boss_warning_quad_blink_levels[16];
static const struct QuadMotionData motions[22] = {
    { { 32, 48, 44, 48 }, { 2, 12, 2, 12 } },
    { { 48, 96, 52, 96 }, { 2, -12, 2, -12 } },
    { { 56, 48, 68, 48 }, { 2, 12, 2, 12 } },
    { { 72, 96, 76, 96 }, { 2, -12, 2, -12 } },
    { { 84, 96, 80, 96 }, { 5, -12, 5, -12 } },
    { { 100, 48, 112, 48 }, { 0, 12, 0, 12 } },
    { { 128, 96, 116, 96 }, { 0, -12, 0, -12 } },
    { { 118, 48, 118, 52 }, { 7, 0, 7, 0 } },
    { { 130, 48, 146, 48 }, { 2, 5, 4, 9 } },
    { { 132, 80, 144, 72 }, { 3, 6, 2, 4 } },
    { { 164, 96, 160, 96 }, { 0, -12, 0, -12 } },
    { { 164, 48, 160, 64 }, { 8, 8, 8, 8 } },
    { { 196, 96, 192, 96 }, { 0, -12, 0, -12 } },
    { { 200, 48, 212, 48 }, { 0, 12, 0, 12 } },
    { { 220, 96, 216, 96 }, { 0, -12, 0, -12 } },
    { { 220, 48, 216, 64 }, { 8, 8, 8, 8 } },
    { { 252, 96, 248, 96 }, { 0, -12, 0, -12 } },
    { { 296, 48, 296, 52 }, { -8, 0, -8, 0 } },
    { { 264, 48, 280, 48 }, { -2, 6, -2, 6 } },
    { { 256, 72, 272, 72 }, { 2, 6, 2, 6 } },
    { { 296, 96, 280, 96 }, { 1, -7, 0, -7 } },
    { { 164, 100, 164, 104 }, { -9, 0, 9, 0 } },
};
static const u8 levels[16] = { 4, 6, 7, 8, 9, 10, 11, 12, 11, 10, 9, 8, 7, 6, 0, 0 };
struct Scenario {
    u8 mode, timer, fraction, enabled, frame;
};
static const struct Scenario scenarios[] = {
    { 0, 2, 0, 0, 0 },
    { 0, 15, 13, 1, 0 },
    { 1, 1, 0, 0, 0 },
    { 1, 2, 13, 1, 0 },
    { 1, 0, 0, 0, 0 },
    { 1, 0, 13, 1, 0 },
    { 1, 0, 7, 1, 1 },
    { 1, 0, 7, 1, 2 },
    { 2, 0, 0, 0, 0 },
    { 2, 1, 0, 1, 0 },
    { 2, 2, 13, 1, 0 },
    { 2, 15, 7, 1, 1 },
    { 2, 1, 7, 1, 2 },
    { 3, 1, 0, 0, 0 },
    { 3, 2, 13, 1, 0 },
    { 3, 0, 0, 1, 0 },
    { 3, 0, 13, 1, 0 },
    { 4, 0, 0, 0, 0 },
    { 4, 15, 13, 1, 0 },
};

static u32 warning_transition(u32 row)
{
    const struct Scenario* c = &scenarios[row / 2];
    u32 type = row % 2 ? 21 : 0, i, j, flag = c->enabled;
    struct {
        u32 before;
        struct QuadObj value;
        u32 after;
    } got, want;
    struct QuadObj* obj = &got.value;
    struct QuadObj* expected = &want.value;
    struct PlayerObj player_before = g_Player, entity_before = g_Entity;
    struct EngineObj engine_before = engine_obj;
    struct MainBssState main_before;
    static struct QuadObj pool_before[32];
    u16 random_before = cur_random;
    memset(&got, 0xA5, sizeof(got));
    got.before = 0x12345678;
    got.after = 0x87654321;
    obj->active = (s8)0x93;
    obj->id = 3;
    obj->state = c->mode == 0 ? 0 : c->mode == 4 ? 2
                                                 : 1;
    obj->unk5 = c->mode > 0 && c->mode < 4 ? c->mode - 1 : 0;
    obj->unk2 = type;
    obj->ext.quad_2.x_scale.bytes.integer = c->timer;
    obj->ext.quad_2.x_scale.bytes.fraction = c->fraction;
    for (i = 0; i < 4; i++) {
        obj->vertices[i].x.val = (100 + i) * 65536 + 0xFEDC;
        obj->vertices[i].y.val = (200 + i) * 65536 + 0x1234;
    }
    D_8013B960 = c->enabled;
    main_bss_state.frame_counter = c->frame;
    main_before = main_bss_state;
    c_test_copy_words((u32*)pool_before, (const u32*)g_QuadObjects, sizeof(pool_before) / 4);
    want = got;
    if (c->mode == 0) {
        expected->bg_offset = -1;
        expected->unk34 = 4;
        expected->unk36 = 16;
        expected->on_screen = 1;
        expected->x_pos.val = expected->y_pos.val = 0;
        expected->state = 1;
        expected->ext.quad_2.x_scale.bytes.fraction = 0;
        expected->ext.quad_2.x_scale.bytes.integer = type == 21 ? 15 : 2;
        expected->ext.quad_2.y_scale.bytes.fraction = 0;
        for (i = 0; i < 4; i++) {
            j = i == 0 || i == 3 ? 0 : 2;
            expected->vertices[i].x.val = motions[type].vertex[j] * 65536;
            expected->vertices[i].y.val = motions[type].vertex[j + 1] * 65536;
        }
        if (type == 0)
            flag = 0;
    } else if (c->mode == 4) {
        expected->active = expected->id = expected->unk2 = expected->on_screen = 0;
        expected->state = expected->unk5 = expected->unk6 = expected->unk7 = 0;
    } else {
        if (c->mode == 2)
            expected->ext.quad_2.x_scale.bytes.integer = type == 21 ? 15 : 2;
        else if (c->timer == 0) {
            if (c->mode == 1)
                expected->unk5 = 1;
            else
                expected->state = 2;
            if (type == 21)
                flag = c->mode == 1;
        } else {
            expected->ext.quad_2.x_scale.bytes.integer--;
            if (type == 21) {
                for (i = 0; i < 4; i++) {
                    j = (i < 2) == (c->mode == 1) ? 0 : 2;
                    expected->vertices[i].x.val += motions[type].speed[j] * 65536;
                }
            } else {
                u32 first = c->mode == 1 ? 2 : 1, second = c->mode == 1 ? 3 : 0;
                expected->vertices[first].x.i.hi += motions[type].speed[0] * 2;
                expected->vertices[first].y.i.hi += motions[type].speed[1] * 2;
                expected->vertices[second].x.i.hi += motions[type].speed[2] * 2;
                expected->vertices[second].y.i.hi += motions[type].speed[3] * 2;
            }
        }
        if (expected->unk5 && flag && c->frame == 0) {
            expected->unk34 = levels[c->fraction];
            expected->ext.quad_2.x_scale.bytes.fraction = c->fraction == 13 ? 0 : c->fraction + 1;
        }
    }
    boss_warning_quad_update(obj);
    c_test_same_words(&got, &want, sizeof(want));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&g_Entity, &entity_before, sizeof(g_Entity));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(g_QuadObjects, pool_before, sizeof(pool_before));
    c_test_same_words(boss_warning_quad_motions, motions, sizeof(motions));
    for (i = 0; i < 16; i++)
        assert(boss_warning_quad_blink_levels[i] == levels[i]);
    assert(D_8013B960 == flag && cur_random == random_before);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "warning_transitions", 0, 0, COUNT(scenarios) * 2, warning_transition },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(scenarios) * 2;
