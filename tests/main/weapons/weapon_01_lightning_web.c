#include "test_runtime.h"
#include "main/shots/shot_41_magma_fire.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/weapons/weapon_07_double_cyclone.h"
#include "main/55C4.h"
#include "main/sprite_animations.h"
#include "support/state_cases.h"
#include "support/player_cases.h"
void lightning_web_charged_init(struct WeaponObj*);
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
static const u32 lightning_web_part_animation_reset_cases_expected[] = { 0x77804u, 0x70103u };

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
#define sw state_room.weapon
#define WEB(kind, facing) (player_reset(1, 0, 0), memset(&state_room, 0, sizeof(state_room)), memset(&shot_objects[0], 0, sizeof(shot_objects[0])), memset(&effect_objects[0], 0, sizeof(effect_objects[0])), pl.unk15 = facing, sw.active = 1, sw.id = 1, sw.unk2 = kind, lightning_web_charged_init(&sw), state_extra = sw.ext.weapon_10.timer | sw.unk49 << 8)
static void lwc_init_left(void)
{
    WEB(2, 0);
}
static void lwc_init_right(void) { WEB(2, 0x40); }
static void lwc_init_part(void) { WEB(3, 0); }

static void (*const lightning_web_charged_init_states_cases[])(void) = {
    lwc_init_left,
    lwc_init_right,
    lwc_init_part,
};
static const u32 lightning_web_charged_init_states_expected[] = { 1u, 0xFF000201u, 0x640000u, 0xC80000u, 0xFFF80000u, 0u, 0u, 0x27801u, 0x110u, 0u, 1u, 0xFF400201u, 0x640000u, 0xC80000u, 0x80000u, 0u, 0u, 0x27801u, 0x110u, 0u, 1u, 0xFF000301u, 0x640000u, 0xC80000u, 0xFFF80000u, 0u, 0u, 0x27801u, 0x110u, 0u };

static u32 test_lightning_web_charged_init_states(u32 row)
{
    return object_run(lightning_web_charged_init_states_cases[row], row, &lightning_web_charged_init_states_expected[row * 10]);
}

extern struct Unk_unk68 lightning_web_charged_net_box[];
void lightning_web_charged_fade(struct WeaponObj*);
void lightning_web_charged_fly(struct WeaponObj*);
void lightning_web_charged_hold(struct WeaponObj*);
void lightning_web_charged_part_drift(struct WeaponObj*);
void lightning_web_charged_spread(struct WeaponObj*);

static const u32 web_words[4][11] = {
    { 0x00010002, 0x04010002, 0x02010002, 0x08010002, 0x01010002, 0x04010002, 0x03010002, 0x08F90002 },
    { 0x07010001, 0x1E010001, 0x0A010001, 0x1F010001, 0x07010001, 0x1F010001, 0x0A010001, 0x20010001, 0x05010001, 0x20010001, 0x20000001 },
    { 0x06010001, 0x21010001, 0x09010001, 0x22010001, 0x06010001, 0x21010001, 0x09010001, 0x23F90001 },
    { 0x20010001, 0x05010001, 0x20010001, 0x0A010001, 0x1F010001, 0x07010001, 0x1F010001, 0x0A010001, 0x1E010001, 0x07010001, 0x07000060 },
};
static const u8 web_animations[] = { 0, 6, 7, 8 };
static const u8 web_lengths[] = { 8, 11, 8, 11 };
static const u8 web_timers[] = { 0, 1, 60 };
static struct WeaponObj pool_before[16];
static struct BackgroundObj backgrounds_before[3];

static void expect_animation(struct WeaponObj* obj, u32 bank, u32 frame)
{
    obj->unk17 = web_animations[bank];
    obj->previous_animation_index = 0xFF;
    obj->animation_cursor = D_8011C070[web_animations[bank]] + frame;
    obj->animation_step.packed = web_words[bank][frame];
}

static u32 charged_web_step(u32 row)
{
    struct WeaponObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct MainBssState main_before = main_bss_state;
    u32 phase = row % 5, edge = row / 5 % 3, facing = row / 15 % 2, buzz = row / 30;
    u32 bank = phase == 0 ? 0 : phase == 1 ? 1
                                           : 2,
        frame = edge == 0 ? 0 : edge == 1 ? web_lengths[bank] - 2
                                          : web_lengths[bank] - 1;
    u32 i, j;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memcpy(pool_before, weapon_objects, sizeof(pool_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 4; i++)
        for (j = 0; j < web_lengths[i]; j++)
            assert(D_8011C070[web_animations[i]][j].packed == web_words[i][j]);
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 10;
    obj.unk2 = phase == 4 ? 1 : 0;
    obj.state = phase == 4 ? 2 : 1;
    obj.unk5 = phase == 4 ? 2 : phase;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk64 = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = facing ? 0x18000 : -0x18000;
    obj.y_vel.val = 0x23456;
    obj.unk50 = (const u8*)lightning_web_charged_part_box;
    obj.animation_table = D_8011C070;
    expect_animation(&obj, bank, frame);
    obj.previous_animation_index = 0x35;
    obj.ext.weapon_10.timer = web_timers[edge];
    obj.ext.weapon_10.unk8F = 0;
    obj.ext.weapon_10.unk90 = 9;
    ((u8*)&obj.ext.weapon_10.timer)[4] = buzz ? 1 : 0;
    expected = obj;
    if (!(phase == 0 || phase == 3) || obj.ext.weapon_10.timer != 0) {
        if (bank == 0)
            expected.animation_step.fields.duration = 1;
        else {
            i = frame + (s8)(web_words[bank][frame] >> 16);
            assert(i < web_lengths[bank]);
            expected.animation_cursor = D_8011C070[web_animations[bank]] + i;
            expected.animation_step.packed = web_words[bank][i];
        }
    }
    if (phase == 0) {
        if (edge == 0) {
            expect_animation(&expected, 1, 0);
            expected.unk15 = 0;
            expected.unk5++;
        } else {
            expected.x_pos.val += obj.x_vel.val;
            expected.y_pos.val -= obj.y_vel.val;
            expected.ext.weapon_10.timer--;
        }
        lightning_web_charged_fly(&obj);
    } else if (phase == 1) {
        if (edge != 0) {
            expect_animation(&expected, 2, 0);
            expected.unk50 = (const u8*)lightning_web_charged_net_box;
            expected.unk64 = 2;
            expected.ext.weapon_10.timer = 60;
            expected.ext.weapon_10.unk90 = 0;
            expected.unk5++;
        }
        lightning_web_charged_spread(&obj);
    } else if (phase == 2) {
        ((u8*)&expected.ext.weapon_10.timer)[4] = buzz ? 0 : 10;
        if (edge == 0) {
            expected.ext.weapon_10.timer = 152;
            expected.ext.weapon_10.unk8F = 1;
            expected.unk5++;
        } else
            expected.ext.weapon_10.timer--;
        lightning_web_charged_hold(&obj);
    } else if (phase == 3) {
        if (edge == 0) {
            expect_animation(&expected, 3, 0);
            expected.unk50 = NULL;
            expected.state = 4;
        } else {
            expected.ext.weapon_10.timer--;
            ((u8*)&expected.ext.weapon_10.timer)[4] = buzz ? 0 : 10;
        }
        lightning_web_charged_fade(&obj);
    } else {
        if (edge == 0) {
            expect_animation(&expected, 3, 0);
            expected.unk50 = NULL;
            expected.state = 4;
        } else {
            expected.ext.weapon_10.timer--;
            expected.x_pos.val += obj.x_vel.val;
            expected.y_pos.val -= obj.y_vel.val;
        }
        lightning_web_charged_part_drift(&obj);
    }
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(weapon_objects, pool_before, sizeof(pool_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

void lightning_web_charged_update(struct WeaponObj*);

static u32 gfx[16], frames[16];
static struct WeaponObj part;

static u32 init(u32 index)
{
    u32 hash, i;

    c_test_zero_words((u32*)&part, sizeof(part) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    for (i = 0; i < 16; i++)
        gfx[i] = frames[i] = 0x40 + i * 4;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    g_Player.weapon = 1;
    part.active = 1;
    part.id = 10;
    part.unk2 = index;
    part.unk15 = 0x40;
    part.x_pos.val = 0x01234567;
    part.y_pos.val = 0x00ABCDEF;
    lightning_web_charged_update(&part);
    assert(part.state == 1 && part.unk15 == 0 && part.unk16 == 1 && part.unk49 == 2);
    assert(part.unk40 == 0x540 && part.unk42 == 0x7801 && part.animation_table == (void*)D_8011C070);
    assert(part.unk38 == (u8*)gfx + 0x48 && part.unk3C == (u8*)frames + 0x68);
    assert(part.x_pos.val == 0x01234567 && part.y_pos.val == 0x00ABCDEF);
    hash = part.x_vel.val;
    hash = hash * 31 + part.y_vel.val;
    hash = hash * 31 + part.animation_step.packed;
    return hash * 31 + (u32)((u8*)part.animation_cursor - (u8*)D_8011C070[6]);
}

static u32 run(u32 row)
{
    static const u8 indexes[] = { 1, 2, 3, 4, 5, 6, 7, 8, 0x41, 0x48 };
    static const u32 expected[COUNT(indexes)] = {
        2862284831u,
        753066655u,
        3894607903u,
        2593610695u,
        128122911u,
        2237341087u,
        3390767135u,
        396797047u,
        2862284831u,
        396797047u,
    };
    u32 hash = init(indexes[row]);
    return c_test_observe(0, row, &hash, &expected[row], 1);
}

const struct CTestGroup c_test_groups[] = {
    { "lightning_web_charged_init_states", 0, 0, COUNT(lightning_web_charged_init_states_cases), test_lightning_web_charged_init_states },
    { "lightning_web_part_animation_reset", NULL, lightning_web_part_animation_reset_cases_expected, COUNT(lightning_web_part_animation_reset_cases_expected), part_case },
    { "lightning_web_charged_part_fly", 0, 0, 2, test_lightning_web_charged_part_fly },
    { "lightning_web_charged_part_hold", 0, 0, 2, test_lightning_web_charged_part_hold },
    { "lightning_web_charged_vanish", 0, 0, 2, test_lightning_web_charged_vanish },
    { "lightning_web_update", 0, 0, 2, test_lightning_web_update },
    { "lightning_web_charged_dispatch", lightning_web_charged_dispatch_cases, lightning_web_charged_dispatch_cases_expected, COUNT(lightning_web_charged_dispatch_cases), 0 },
    { "charged_vanish_ending", charged_vanish_ending_cases, charged_vanish_ending_cases_expected, COUNT(charged_vanish_ending_cases), 0 },
    { "charged_web_steps", NULL, NULL, 60, charged_web_step },
    { "charged_part_entry_angles", NULL, NULL, 10, run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(lightning_web_charged_init_states_cases) + COUNT(lightning_web_part_animation_reset_cases_expected) + 2 + 2 + 2 + 2 + COUNT(lightning_web_charged_dispatch_cases) + COUNT(charged_vanish_ending_cases) + 60 + 10;
