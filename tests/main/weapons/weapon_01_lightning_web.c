#include "test_runtime.h"
#include "main/shots/shot_41_magma_fire.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/weapons/weapon_07_double_cyclone.h"
#include "main/55C4.h"
#include "main/sprite_animations.h"
extern s32 player_gfx_buf_0[1024];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 part_case(u32 mode)
{
    struct WeaponObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 1;
    obj.state = 2;
    obj.unk5 = 3;
    obj.ext.weapon_10.timer = mode ? 2 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = 2 * 65536;
    obj.animation_table = D_8011C070;
    set_animation(&obj, 6);
    obj.animation_cursor = D_8011C070[6] + 10;
    obj.animation_step = *(union AnimationStep*)obj.animation_cursor;
    assert(obj.animation_step.packed == 0x20000001);
    expected = obj;
    expected.unk17 = 7;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = D_8011C070[7];
    expected.animation_step = *(union AnimationStep*)D_8011C070[7];
    if (mode) {
        expected.ext.weapon_10.timer = 1;
        expected.x_pos.val += 65536;
        expected.y_pos.val -= 2 * 65536;
    } else {
        expected.unk50 = (const u8*)lightning_web_charged_part_box;
        expected.unk64 = 1;
        expected.ext.weapon_10.timer = 120;
        expected.unk5 = 4;
    }
    lightning_web_charged_part_fly(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)obj.ext.weapon_10.timer << 8) | ((u32)obj.unk17 << 16);
}
#define CASE(m)                                                  \
    static u32 lightning_web_part_animation_reset_part_##m(void) \
    {                                                            \
        return part_case(m);                                     \
    }
CASE(0)
CASE(1)
static const CTestCase lightning_web_part_animation_reset_cases[] = { lightning_web_part_animation_reset_part_0, lightning_web_part_animation_reset_part_1 };
static const u32 lightning_web_part_animation_reset_cases_expected[] = { 0x77804u, 0x70103u };
#undef CASE

struct lightning_web_charged_part_fly_case {
    u32 timer;
    u32 expected[2];
};
static const struct lightning_web_charged_part_fly_case lightning_web_charged_part_fly_cases[] = {
    { 0, { 1u, 1u } },
    { 255, { 0u, 0u } },
};
static u32 test_lightning_web_charged_part_fly(u32 row)
{
    const struct lightning_web_charged_part_fly_case* c = &lightning_web_charged_part_fly_cases[row];
    u32 observed_values[2];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.weapon_10.timer = c->timer;
    obj.animation_step.fields.relative_step = -1;
    lightning_web_charged_part_fly(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk64;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

struct lightning_web_charged_part_hold_case {
    u32 timer;
    u32 expected[3];
};
static const struct lightning_web_charged_part_hold_case lightning_web_charged_part_hold_cases[] = {
    { 255, { 0xFEu, 0u, 0u } },
    { 0, { 0x10u, 1u, 2u } },
};
static u32 test_lightning_web_charged_part_hold(u32 row)
{
    const struct lightning_web_charged_part_hold_case* c = &lightning_web_charged_part_hold_cases[row];
    u32 observed_values[3];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.weapon_10.timer = c->timer;
    lightning_web_charged_part_hold(&obj);
    observed_values[0] = (u32)obj.ext.weapon_10.timer;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk64;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

struct lightning_web_charged_vanish_case {
    u32 relative_step;
    u32 expected[2];
};
static const struct lightning_web_charged_vanish_case lightning_web_charged_vanish_cases[] = {
    { 0, { 0u, 3u } },
    { -1, { 1u, 0u } },
};
static u32 test_lightning_web_charged_vanish(u32 row)
{
    const struct lightning_web_charged_vanish_case* c = &lightning_web_charged_vanish_cases[row];
    u32 observed_values[2];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&player_gfx_buf_0, 0, sizeof(player_gfx_buf_0));
    memset(&player_gfx_buf_1, 0, sizeof(player_gfx_buf_1));
    memset(&vram_rect_ptr, 0, sizeof(vram_rect_ptr));
    obj.animation_step.fields.relative_step = c->relative_step;
    lightning_web_charged_vanish(&obj);
    observed_values[0] = (u32)obj.on_screen;
    observed_values[1] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

struct lightning_web_update_case {
    u32 capsule_state, weapon, state, unk75, unk72;
    u32 expected[4];
};
static const struct lightning_web_update_case lightning_web_update_cases[] = {
    { -1, 0, 0, 0, 0, { 0u, 0u, 0u, 0u } },
    { 0, 1, 4, -1, 8, { 0u, 3u, 0u, 0u } },
};
static u32 test_lightning_web_update(u32 row)
{
    const struct lightning_web_update_case* c = &lightning_web_update_cases[row];
    u32 observed_values[4];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Entity, 0, sizeof(g_Entity));

    memset(&player_gfx_buf_0, 0, sizeof(player_gfx_buf_0));
    memset(&player_gfx_buf_1, 0, sizeof(player_gfx_buf_1));
    memset(&qux_object, 0, sizeof(qux_object));
    memset(&vram_rect_ptr, 0, sizeof(vram_rect_ptr));
    obj.x_pos.val = 0;
    obj.y_pos.val = 0;
    g_Player.input_locked = 0;
    g_Player.capsule_state = c->capsule_state;
    g_Player.weapon = c->weapon;
    obj.state = c->state;
    obj.unk75 = c->unk75;
    obj.unk72 = c->unk72;
    g_Player.unk71 = 0;
    lightning_web_update(&obj);
    observed_values[0] = (u32)g_Player.unk71;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk18.val;
    observed_values[3] = (u32)obj.unk1C.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#include "support/charged_dispatch.h"
CHARGED_BASIC(0)
CHARGED_CASE(0, 6)
static const CTestCase lightning_web_charged_dispatch_cases[] = { CHARGED_BASIC_ENTRIES(0) CHARGED_ENTRIES(0, 6) };
static const u32 lightning_web_charged_dispatch_cases_expected[] = { 0x1020191u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x504u };

#include "support/animation_endings.h"
ENDING_CASE(0)
ENDING_CASE(1)
ENDING_CASE(2)
static const CTestCase charged_vanish_ending_cases[] = { ENDING_ENTRY(0) ENDING_ENTRY(1) ENDING_ENTRY(2) };

static const u32 charged_vanish_ending_cases_expected[] = { 0x5F0003u, 0x10101u, 0x10001u };
const struct CTestGroup c_test_groups[] = {
    { "lightning_web_part_animation_reset", lightning_web_part_animation_reset_cases, lightning_web_part_animation_reset_cases_expected, COUNT(lightning_web_part_animation_reset_cases), 0 },
    { "lightning_web_charged_part_fly", 0, 0, 2, test_lightning_web_charged_part_fly },
    { "lightning_web_charged_part_hold", 0, 0, 2, test_lightning_web_charged_part_hold },
    { "lightning_web_charged_vanish", 0, 0, 2, test_lightning_web_charged_vanish },
    { "lightning_web_update", 0, 0, 2, test_lightning_web_update },
    { "lightning_web_charged_dispatch", lightning_web_charged_dispatch_cases, lightning_web_charged_dispatch_cases_expected, COUNT(lightning_web_charged_dispatch_cases), 0 },
    { "charged_vanish_ending", charged_vanish_ending_cases, charged_vanish_ending_cases_expected, COUNT(charged_vanish_ending_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(lightning_web_part_animation_reset_cases) + 2 + 2 + 2 + 2 + COUNT(lightning_web_charged_dispatch_cases) + COUNT(charged_vanish_ending_cases);
