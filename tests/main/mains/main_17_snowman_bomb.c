#include "test_runtime.h"
#include "main/mains/main_17_snowman_bomb.h"
#include "support/state_cases.h"
void snowman_bomb_resume_step(struct MainObj* arg0);
extern struct Unk_unk68 item_carrier_hitboxes;
extern struct Unk_unk68 item_carrier_capsule_hurtbox;

static const u32 snowman_bomb_main_expected[] = { 2u, 6u, 1u, 6u, 0x640000u, 0x500000u, 6u, 0u };
static u32 test_snowman_bomb_main(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    struct VisualObj visual_before[32];
    struct MiscObj misc_before[64];
    u32 map_words[64], pixels_words[256], attributes[1];
    u32 map_before[64], pixels_before[256], attributes_before[1];
    u8 pool_full;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    SPIKE_IMMUNE_SET(g_Player, 1);
    obj.active = 0x41;
    obj.id = 17;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    snowman_bomb_init(&obj);
    memset(&map_words, 0, sizeof(map_words));
    memset(&pixels_words, 0, sizeof(pixels_words));
    memset(&attributes, 0, sizeof(attributes));
    SP_BG_TILEMAP = (u8*)map_words;
    TEST_BG_TILE_PIXELS = (void*)pixels_words;
    TEST_BG_TILE_ATTRS = (void*)attributes;
    layout_width = 16;
    layout_size = 256;
    map_words[0] = 0x01010101;
    attributes[0] = C_TEST_PSX_WORD(0x3E);
    memcpy(map_before, map_words, sizeof(map_before));
    memcpy(pixels_before, pixels_words, sizeof(pixels_before));
    memcpy(attributes_before, attributes, sizeof(attributes_before));
    pool_full = 1;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_full ? 1 : 0;
    }
    memcpy(visual_before, visual_objects, sizeof(visual_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    obj.unk5 = 6;
    obj.unk7C = 2;
    obj.air_state = 1;
    snowman_bomb_main(&obj);
    assert(obj.terrain_box == &snowman_bomb_terrain_box);
    c_test_same_words(map_words, map_before, sizeof(map_words));
    c_test_same_words(pixels_words, pixels_before, sizeof(pixels_words));
    c_test_same_words(attributes, attributes_before, sizeof(attributes));
    c_test_same_words(visual_objects, visual_before, sizeof(visual_objects));
    c_test_same_words(misc_objects, misc_before, sizeof(misc_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk7C;
    observed_values[3] = (u32)(u8)obj.hp;
    observed_values[4] = (u32)obj.x_pos.val;
    observed_values[5] = (u32)obj.y_pos.val;
    observed_values[6] = (u32)obj.ext.main_17.unk90;
    observed_values[7] = (u32)obj.collision_flags;
    return c_test_observe(0, row, observed_values, snowman_bomb_main_expected, 8);
}

static void sb_resume(void)
{
    state_reset(1, 0, 0);
    so.ext.raw[4] = 3;
    snowman_bomb_resume_step(&so);
}

void func_80050278(struct MainObj* arg0);
void snowman_bomb_turn(struct MainObj* arg0);
void snowman_bomb_detonate(struct MainObj* arg0);
void snowman_bomb_fall(struct MainObj* arg0);
extern struct Unk_unk68 snowman_bomb_blast_terrain_box;
#define SB(step) (state_reset(step, 0, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.collision_flags = 8)
#define SBX() (state_extra = (u8)so.ext.main_17.unk80 | (u8)so.ext.main_17.unk84 << 8 | (u8)so.ext.main_17.unk88 << 16 | (u32)(u8)so.ext.main_17.unk8C << 24)
#define HOP(timer, setup) (SB(2), so.ext.main_17.unk80 = timer, so.ext.main_17.unk84 = 3, so.ext.main_17.unk88 = 5, setup, func_80050278(&so), SBX())
static void sb_hop_bounce(void)
{
    HOP(2, (so.collision_flags = 1));
}
static void sb_hop_left(void) { HOP(2, (so.collision_flags = 0)); }
static void sb_hop_near(void) { HOP(1, (g_Player.x_pos.i.hi = 0x40, g_Player.y_pos.i.hi = 0x60)); }
static void sb_hop_patience(void) { HOP(1, (so.unk15 = PLAYER_FACING_RIGHT, so.ext.main_17.unk88 = 1, g_Player.x_pos.i.hi = 0x200)); }
static void sb_hop_turn(void) { HOP(1, (so.ext.main_17.unk84 = 1, g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x40)); }
static void sb_hop_pause(void) { HOP(1, (g_Player.x_pos.i.hi = 0x200)); }
static void sb_turn_end(void) { SB(3), so.animation_step.fields.event = 1, g_Player.x_pos.i.hi = 0x100, snowman_bomb_turn(&so), SBX(); }
static void sb_turn(void) { SB(3), snowman_bomb_turn(&so), SBX(); }
static void sb_detonate_arm(void) { SB(4), so.x_speed = 0x30000, so.animation_step.fields.event = 2, snowman_bomb_detonate(&so), state_extra = so.terrain_box == &snowman_bomb_blast_terrain_box; }
static void sb_detonate_blast(void) { SB(4), so.animation_step.fields.event = 1, snowman_bomb_detonate(&so), state_extra = so.state; }
#define FALL(setup) (SB(5), so.air_state = 1, so.ext.main_17.saved_unk5 = 0x600000, setup, snowman_bomb_fall(&so), SBX())
static void sb_fall_rolling(void)
{
    FALL(so.ext.main_17.unk8C = 1);
}
static void sb_fall_far(void) { FALL(so.ext.main_17.saved_unk5 = 0x500000); }
static void sb_fall_near(void) { FALL(so.ext.main_17.saved_unk5 = 0x660000); }
static void sb_fall_air_moving(void) { FALL((so.collision_flags = 0, so.x_speed = 0x10000, so.x_accel = 0x100, so.gravity = 0x4200)); }
#define SBMAIN(step, setup) (SB(step), so.state = 1, so.terrain_box = &snowman_bomb_terrain_box, state_terrain(0), SPIKE_IMMUNE_SET(g_Player, 1), setup, snowman_bomb_update(&so), state_extra = so.state)
static void sb_main_wait_end(void)
{
    SBMAIN(6, so.unk7C = 1);
}
static void sb_main_drop(void) { SBMAIN(6, (so.unk7C = 5, so.collision_flags = 0)); }
static void sb_main_defeat(void) { SBMAIN(6, (so.unk7C = 5, so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void sb_main_off_screen(void) { SBMAIN(6, (so.unk7C = 5, so.x_pos.i.hi = 0x400)); }

static void (*const snowman_bomb_misc_cases[])(void) = {
    sb_resume,
    sb_hop_bounce,
    sb_hop_left,
    sb_hop_near,
    sb_hop_patience,
    sb_hop_turn,
    sb_hop_pause,
    sb_turn_end,
    sb_turn,
    sb_detonate_arm,
    sb_detonate_blast,
    sb_fall_rolling,
    sb_fall_far,
    sb_fall_near,
    sb_fall_air_moving,
    sb_main_wait_end,
    sb_main_drop,
    sb_main_defeat,
    sb_main_off_screen,
};
static const u32 snowman_bomb_misc_expected[] = {
    3u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x2u,
    0x0u,
    0x810000u,
    0x10000u,
    0x80000u,
    0x0u,
    0x4000u,
    0x0u,
    0x50301u,
    0x0u,
    0x2u,
    0x0u,
    0x7F0000u,
    0xFFFF0000u,
    0x80000u,
    0x0u,
    0x0u,
    0x0u,
    0x50301u,
    0x0u,
    0x4u,
    0x0u,
    0x800000u,
    0xFFFD0000u,
    0x0u,
    0xFFFFF000u,
    0x2u,
    0x0u,
    0x1050300u,
    0x0u,
    0x4u,
    0x0u,
    0x800000u,
    0x30000u,
    0x0u,
    0xFFFFF000u,
    0x4002u,
    0x0u,
    0x1000300u,
    0x0u,
    0x3u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x0u,
    0x40000u,
    0x0u,
    0x6u,
    0x14u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x40200u,
    0x0u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4000u,
    0x0u,
    0x304u,
    0x0u,
    0x3u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x4u,
    0x0u,
    0x830000u,
    0x30000u,
    0x0u,
    0x0u,
    0x0u,
    0x3u,
    0x1u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x2100u,
    0x4u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1000000u,
    0x0u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0xC0304u,
    0x0u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1000005u,
    0x0u,
    0x810000u,
    0xFF00u,
    0xFFFFBE00u,
    0x420100u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x1u,
    0x0u,
    0x1000005u,
    0x5u,
    0x800000u,
    0x0u,
    0xFFFFBE00u,
    0x420000u,
    0x0u,
    0x0u,
    0x1u,
    0x0u,
    0x6u,
    0x4u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x80000000u,
    0x1u,
    0x2u,
    0x2100u,
    0x6u,
    0x4u,
    0x4000000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
};

static u32 test_snowman_bomb_misc(u32 row)
{
    return state_run(snowman_bomb_misc_cases[row], row, &snowman_bomb_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "snowman_bomb_misc", 0, 0, COUNT(snowman_bomb_misc_cases), test_snowman_bomb_misc },
    { "snowman_bomb_main", 0, 0, 1, test_snowman_bomb_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(snowman_bomb_misc_cases) + 1;
