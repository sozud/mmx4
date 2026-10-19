#include "test_runtime.h"
#include "main/mains/main_39_falling_ceiling.h"
#include "main/55C4.h"
#include "support/state_cases.h"
void falling_ceiling_despawn(struct MainObj*);
void falling_ceiling_main(struct MainObj*);
extern union AnimationStep* falling_ceiling_animations[4];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern s8 D_800FE94C[4];

static const s16 delta[8] = { -17, -16, 0, 16, 17, -16, 0, 16 };
static u32 ceiling_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&obj.ext, 0xA5, sizeof(obj.ext));
    obj.active = 0x41;
    obj.id = 39;
    obj.unk2 = mode & 1;
    obj.state = 1;
    obj.unk5 = 0;
    obj.unk6 = 7;
    obj.unk7 = 8;
    obj.x_pos.val = (500 + (mode & 1 ? 16 : -16) - delta[mode]) * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.gravity = 0x2000;
    obj.unk15 = mode & 1 ? 0x40 : 0;
    obj.ext.main_39.unk88 = 1;
    obj.ext.main_39.unk8C = mode < 5 ? 300 * 65536 : 0x2FFFFF0;
    obj.ext.main_39.unk90 = mode < 5 ? 0x2000 : 0x10000;
    obj.animation_table = (const u8* const*)falling_ceiling_animations;
    obj.animation_cursor = (const u8*)falling_ceiling_animations[0];
    obj.animation_step = *falling_ceiling_animations[0];
    obj.unk17 = 0;
    obj.previous_animation_index = 9;
    g_Player.x_pos.val = 500 * 65536 + 0xBEEF;
    g_Player.y_pos.val = 200 * 65536 + 0xCAFE;
    expected = obj;
    player_expected = g_Player;
    expected.animation_cursor += 4;
    expected.animation_step = falling_ceiling_animations[0][1];
    expected.y_speed = -0x2000;
    expected.ext.main_39.unk8C = mode < 5 ? 300 * 65536 + 0x2000 : 0x3000000;
    expected.ext.main_39.unk90 = mode < 5 ? 0x3000 : 0x10000;
    if (mode != 0 && mode != 4) {
        expected.gravity = 0x8000;
        expected.unk5 = 2;
    }
    func_80061918(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    assert(falling_ceiling_animations[0][0].packed == 0x00010001);
    assert(falling_ceiling_animations[0][1].packed == 0x01010001);
    actual = obj.unk5 | ((u32)obj.unk2 << 8) | ((u32)(obj.gravity >> 12) << 16);
    return actual;
}
static const u32 falling_ceiling_track_player_cases_expected[] = { 0x20000u, 0x80102u, 0x80002u, 0x80102u, 0x20000u, 0x80102u, 0x80002u, 0x80102u };

static const u32 func_800615CC_expected[] = { 1u, 0u, 0u, 0u, 0x14u, 0x2000u, 6u, 0u, 1u, 0u, 6u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1100000u, 0u };
static u32 test_func_800615CC(u32 row)
{
    u32 observed_values[19];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk2 = 12;
    func_800615CC(&obj);
    observed_values[0] = (u32)((u8*)&obj.ext)[20];
    observed_values[1] = (u32)((u8*)&obj.ext)[8];
    observed_values[2] = (u32)obj.air_state;
    observed_values[3] = (u32)obj.bg_offset;
    observed_values[4] = (u32)obj.contact_damage;
    observed_values[5] = (u32)obj.gravity;
    observed_values[6] = (u32)obj.hp;
    observed_values[7] = (u32)obj.invincibility_timer;
    observed_values[8] = (u32)obj.state;
    observed_values[9] = (u32)obj.unk15;
    observed_values[10] = (u32)obj.unk16;
    observed_values[11] = (u32)obj.unk5;
    observed_values[12] = (u32)obj.unk6;
    observed_values[13] = (u32)obj.unk7E;
    observed_values[14] = (u32)obj.x_accel;
    observed_values[15] = (u32)obj.x_pos.val;
    observed_values[16] = (u32)obj.x_speed;
    observed_values[17] = (u32)obj.y_pos.val;
    observed_values[18] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_800615CC_expected, 19);
}

static const u32 func_80061B58_0_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFFu, 0u, 2u, 0u, 1u, 0u };
static u32 test_func_80061B58_0(u32 row)
{
    u32 observed_values[15];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&item_objects, 0, sizeof(item_objects));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&visual_objects, 0, sizeof(visual_objects));
    obj.y_pos.i.hi = 284;
    obj.unk7C = 1;
    FILL_ACTIVE(item_objects, 32, 255 ? 1 : 0);
    func_80061B58(&obj);
    observed_values[0] = (u32)item_objects[0].active;
    observed_values[1] = (u32)item_objects[0].bg_offset;
    observed_values[2] = (u32)item_objects[0].id;
    observed_values[3] = (u32)item_objects[0].state;
    observed_values[4] = (u32)item_objects[0].unk2;
    observed_values[5] = (u32)item_objects[0].x_pos.u.hi;
    observed_values[6] = (u32)item_objects[0].x_pos.val;
    observed_values[7] = (u32)item_objects[0].y_pos.u.hi;
    observed_values[8] = (u32)item_objects[0].y_pos.val;
    observed_values[9] = (u32)obj.ext.main_39.unk94;
    observed_values[10] = (u32)obj.gravity;
    observed_values[11] = (u32)obj.unk6;
    observed_values[12] = (u32)obj.unk7C;
    observed_values[13] = (u32)obj.unk7E;
    observed_values[14] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_80061B58_0_expected, 15);
}

static const u32 func_80061B58_1_expected[] = { 1u, 1u, 2u, 0u, 1u, 1u, 0x7010002u, 0xB300000u, 0x1100000u, 0xFFFFE000u, 0x2000u, 1u };
static u32 test_func_80061B58_1(u32 row)
{
    u32 observed_values[12];
    struct MainObj obj;
    struct ItemObj items_before[32];
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 39;
    func_800615CC(&obj);
    assert(obj.terrain_box == (struct Unk_unk68*)D_800FE94C);
    set_animation(&obj, 2);
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.unk7C = 1;
    obj.unk7E = 0;
    obj.ext.main_39.unk94 = 2;
    FILL_ACTIVE(item_objects, 32, 1);
    memcpy(items_before, item_objects, sizeof(items_before));
    func_80061B58(&obj);
    c_test_same_words(item_objects, items_before, sizeof(item_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.unk7E;
    observed_values[5] = (u32)obj.ext.main_39.unk94;
    observed_values[6] = obj.animation_step.packed;
    observed_values[7] = (u32)obj.x_pos.val;
    observed_values[8] = (u32)obj.y_pos.val;
    observed_values[9] = (u32)obj.y_speed;
    observed_values[10] = (u32)obj.gravity;
    observed_values[11] = (u32)item_objects[0].active;
    return c_test_observe(0, row, observed_values, func_80061B58_1_expected, 12);
}

static u8 ceiling_record;
#define FC(step, setup) (state_reset(step, 0, 0), so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, setup, falling_ceiling_main(&so))
static void fcl_sink(void)
{
    FC(2, so.y_speed = 0x10000);
}
static void fcl_sink_away(void) { FC(2, so.y_pos.i.hi = 0x1000); }
static void fcl_despawn(void)
{
    state_reset(0, 0, 0);
    ceiling_record = 0;
    so.backref = (void*)&ceiling_record;
    so.state = 2;
    so.ext.main_39.unk80.w = 5;
    falling_ceiling_despawn(&so);
    state_extra = ceiling_record | so.ext.main_39.unk80.w << 8;
    so.backref = NULL;
}
static void fcl_hover_flip(void) { FC(0, (so.y_speed = 0xF000, so.gravity = 0x1000, so.ext.main_39.unk84.h.unk84 = 0x100)); }

static void (*const falling_ceiling_states_cases[])(void) = {
    fcl_sink,
    fcl_sink_away,
    fcl_despawn,
    fcl_hover_flip,
};
static const u32 falling_ceiling_states_expected[] = { 2u, 0u, 0x800000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x80u, 0u, 0u, 0u, 0x800000u, 0u, 0xE000u, 0x100000u, 0u, 0u, 0u, 0u };

static u32 test_falling_ceiling_states(u32 row)
{
    return state_run(falling_ceiling_states_cases[row], row, &falling_ceiling_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "falling_ceiling_states", 0, 0, COUNT(falling_ceiling_states_cases), test_falling_ceiling_states },
    { "falling_ceiling_track_player", NULL, falling_ceiling_track_player_cases_expected, COUNT(falling_ceiling_track_player_cases_expected), ceiling_case },
    { "func_800615CC", 0, 0, 1, test_func_800615CC },
    { "func_80061B58_0", 0, 0, 1, test_func_80061B58_0 },
    { "func_80061B58_1", 0, 0, 1, test_func_80061B58_1 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(falling_ceiling_states_cases) + COUNT(falling_ceiling_track_player_cases_expected) + 1 + 1 + 1;
