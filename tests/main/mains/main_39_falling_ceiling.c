#include "test_runtime.h"
#include "support/platform_fixture.h"
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
    obj.unk15 = mode & 1 ? PLAYER_FACING_RIGHT : 0;
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
    assert(falling_ceiling_animations[0][0].packed == C_TEST_STEP(0x00010001));
    assert(falling_ceiling_animations[0][1].packed == C_TEST_STEP(0x01010001));
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
    observed_values[9] = C_TEST_PSX_FACING(obj.unk15);
    observed_values[10] = TEST_PSX_LAYER(obj.unk16);
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
    observed_values[6] = C_TEST_STEP(obj.animation_step.packed);
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
#include "support/tile_writes.h"
void func_80061918(struct MainObj*);
void falling_ceiling_drop_start(struct MainObj*);
void falling_ceiling_drop_land(struct MainObj*);
#define FCX() (state_extra = so.ext.main_39.unk80.h.unk82 | (u32)so.ext.main_39.unk84.h.unk84 << 16)
#define FCINIT(kind) (state_reset(0, 0, 0), so.unk2 = kind, func_800615CC(&so), FCX(), state_extra ^= so.ext.main_39.unk80.h.unk80 << 4 ^ so.ext.main_39.unk84.h.unk86 << 8)
static void fcl_init_1(void)
{
    FCINIT(1);
}
static void fcl_init_2(void) { FCINIT(2); }
static void fcl_init_3(void) { FCINIT(3); }
static void fcl_init_4(void) { FCINIT(4); }
static void fcl_init_5(void) { FCINIT(5); }
static void fcl_init_6(void) { FCINIT(6); }
static void fcl_init_7(void) { FCINIT(7); }
static void fcl_init_8(void) { FCINIT(8); }
static void fcl_init_9(void) { FCINIT(9); }
static void fcl_init_10(void) { FCINIT(10); }
static void fcl_init_11(void) { FCINIT(11); }
#define WAITC(setup) (state_reset(0, 0, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.gravity = 0x2000, so.ext.main_39.unk88 = 1, so.ext.main_39.unk8C = 0x1200000, g_Player.x_pos.i.hi = 0x90, g_Player.y_pos.i.hi = 0x100, setup, func_80061918(&so), FCX(), state_extra ^= so.ext.main_39.unk8C)
static void fcl_wait_flip_trigger(void)
{
    WAITC((so.ext.main_39.unk88 = 0, so.y_speed = 0x12000, so.ext.main_39.unk84.h.unk84 = 0x80));
}
static void fcl_wait_below(void) { WAITC(g_Player.y_pos.i.hi = 0x200); }
static void fcl_wait_above(void) { WAITC(g_Player.y_pos.i.hi = 0x40); }
static void fcl_wait_odd_far(void) { WAITC((so.unk2 = 1, g_Player.x_pos.i.hi = 0x40)); }
static void fcl_drop_floor(void) { state_reset(1, 0, 0), so.y_pos.i.hi = 0x120, so.y_speed = -0x10000, so.animation_step.fields.event = 1, falling_ceiling_drop_start(&so); }
static void fcl_drop_air(void) { state_reset(1, 0, 0), so.y_pos.i.hi = 0x100, so.y_speed = -0x10000, so.gravity = 0x8000, falling_ceiling_drop_start(&so); }
#define FALLC(setup) (state_reset(1, 1, 0), memset(item_objects, 0, sizeof(item_objects)), so.y_pos.i.hi = 0x100, so.ext.main_39.unk94 = 5, so.unk7E = 1, so.unk7C = 1, so.ext.main_39.unk80.h.unk80 = 0x300, so.ext.main_39.unk84.h.unk86 = 0x188, setup, func_80061B58(&so), state_extra = so.ext.main_39.unk94 | (u32)so.unk7E << 8 | (u32)item_objects[1].unk2 << 16 | (u32)item_objects[1].id << 24)
static void fcl_fall_shake(void)
{
    FALLC((so.ext.main_39.unk94 = 1, so.unk7E = 0xF, so.unk7C = 5));
}
static void fcl_fall_odd_end(void) { FALLC((so.unk7E = 7, so.unk2 = 1, background_objects[0].unk34 = 0x10, ((u8*)&background_objects[0].unk3E)[0] = 4)); }
static void fcl_fall_items(void) { FALLC((so.unk7E = 7, background_objects[0].unk34 = 0x10, ((u8*)&background_objects[0].unk3E)[0] = 1)); }
static void fcl_fall_items_late(void) { FALLC(so.unk2 = 8); }
#define FCLAND(kind) (state_reset(1, 2, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 8, background_objects[0].x_pos.i.hi = 0xB00, background_objects[0].y_pos.i.hi = 0x100, tile_writes_begin(), so.unk2 = kind, so.ext.main_39.unk80.h.unk82 = 0xB20)
static void fcl_land_odd(void)
{
    FCLAND(1), falling_ceiling_drop_land(&so), state_extra = tile_writes_end();
}
static void fcl_land_even(void) { FCLAND(2), tile_writes_expect(1, 0xB20, 0x120, 1), falling_ceiling_drop_land(&so), state_extra = tile_writes_end(); }

static void (*const falling_ceiling_states_cases[])(void) = {
    fcl_sink,
    fcl_sink_away,
    fcl_despawn,
    fcl_hover_flip,
    fcl_init_1,
    fcl_init_2,
    fcl_init_3,
    fcl_init_4,
    fcl_init_5,
    fcl_init_6,
    fcl_init_7,
    fcl_init_8,
    fcl_init_9,
    fcl_init_10,
    fcl_init_11,
    fcl_wait_flip_trigger,
    fcl_wait_below,
    fcl_wait_above,
    fcl_wait_odd_far,
    fcl_drop_floor,
    fcl_drop_air,
    fcl_fall_shake,
    fcl_fall_odd_end,
    fcl_fall_items,
    fcl_fall_items_late,
    fcl_land_odd,
    fcl_land_even,
};
static const u32 falling_ceiling_states_expected[] = {
    2u,
    0u,
    0x800000u,
    0u,
    0x10000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x80u,
    0u,
    0u,
    0u,
    0x800000u,
    0u,
    0xE000u,
    0x100000u,
    0u,
    0u,
    0u,
    0u,
    0x0u,
    0x0u,
    0xB900000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xB700B20u,
    0x0u,
    0x0u,
    0x0u,
    0xC300000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xBF14220u,
    0x0u,
    0x0u,
    0x0u,
    0xC900000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xBF00C20u,
    0x0u,
    0x0u,
    0x0u,
    0xD300000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xCE15320u,
    0x0u,
    0x0u,
    0x0u,
    0xD900000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xCE00D20u,
    0x0u,
    0x0u,
    0x0u,
    0xE300000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xDD16020u,
    0x0u,
    0x0u,
    0x0u,
    0xE900000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xDD00E20u,
    0x0u,
    0x0u,
    0x0u,
    0xEB00000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xE5160A0u,
    0x0u,
    0x0u,
    0x0u,
    0xF100000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xE500EA0u,
    0x0u,
    0x0u,
    0x0u,
    0xF300000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xEB17920u,
    0x0u,
    0x0u,
    0x0u,
    0xF900000u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x60003u,
    0xEB00F20u,
    0x0u,
    0x1u,
    0x0u,
    0x800000u,
    0x0u,
    0x10000u,
    0x200000u,
    0x1u,
    0x0u,
    0x1A00000u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0xFFFFE000u,
    0x200000u,
    0x0u,
    0x0u,
    0x1200000u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0xFFFFE000u,
    0x200000u,
    0x0u,
    0x0u,
    0x1200000u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0xFFFFE000u,
    0x200000u,
    0x0u,
    0x0u,
    0x1200000u,
    0x0u,
    0x101u,
    0x3Cu,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0xFFFE8000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x101u,
    0x100004u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x101Eu,
    0x2100u,
    0x201u,
    0x80000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x804u,
    0x0u,
    0x201u,
    0x80000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0xF010804u,
    0x0u,
    0x201u,
    0x20000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0xF030204u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x200000u,
    0x0u,
    0x0u,
    0x22B3A8C8u,
    0x0u,
};

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
