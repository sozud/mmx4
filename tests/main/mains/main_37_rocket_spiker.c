#include "test_runtime.h"
#include "main/mains/main_37_rocket_spiker.h"
#include "support/state_cases.h"
void rocket_spiker_resume_step(struct MainObj* arg0);
extern union AnimationStep* rocket_spiker_animations[28];
extern struct Unk_unk68 D_800FE4E4;

struct func_8005FE1C_case {
    u32 unk2, x_pos, y_pos;
    u32 expected[17];
};
static const struct func_8005FE1C_case func_8005FE1C_cases[] = {
    { -1, 6553600, 5242880, { 1u, 0u, 0u, 6u, 4u, 2u, 0u, 0x1234u, 0x640000u, 0x500000u, 0u, 0u, 0x7Cu, 0u, 0u, 0x100u, 0u } },
    { 4, 6553600, 5242880, { 1u, 0u, 0u, 6u, 4u, 2u, 0u, 0x1234u, 0x640000u, 0x500000u, 0u, 0u, 0x7Cu, 0u, 0u, 0x100u, 0u } },
    { 3, 395837440, 57606144, { 1u, 4u, 0u, 6u, 4u, 2u, PLAYER_FACING_RIGHT, 0x1236u, 0x17080000u, 0x3500000u, 0xFFFF0000u, 0u, 5u, 0x3301710u, 0x380u, 0x100u, C_TEST_STEP(0x17010003u) } },
    { 3, 395837440, 57671680, { 1u, 4u, 0u, 6u, 4u, 2u, PLAYER_FACING_RIGHT, 0x1236u, 0x17080000u, 0x3B00000u, 0xFFFF0000u, 0u, 3u, 0x3901710u, 0x40Bu, 0x100u, C_TEST_STEP(0x17010003u) } },
    { 3, 395837440, 63963136, { 1u, 4u, 0u, 6u, 4u, 2u, PLAYER_FACING_RIGHT, 0x1236u, 0x17080000u, 0x4100000u, 0xFFFF0000u, 0u, 1u, 0x3F01710u, 0x480u, 0x100u, C_TEST_STEP(0x17010003u) } },
    { 3, 395902976, 57606144, { 1u, 4u, 0u, 6u, 4u, 2u, 0u, 0x1236u, 0x18180000u, 0x3500000u, 0x10000u, 0u, 4u, 0x33017E0u, 0x380u, 0x100u, C_TEST_STEP(0x17010003u) } },
    { 3, 395902976, 57671680, { 1u, 4u, 0u, 6u, 4u, 2u, 0u, 0x1236u, 0x18180000u, 0x3B00000u, 0x10000u, 0u, 2u, 0x39017E0u, 0x40Bu, 0x100u, C_TEST_STEP(0x17010003u) } },
    { 3, 395902976, 63963136, { 1u, 4u, 0u, 6u, 4u, 2u, 0u, 0x1236u, 0x18180000u, 0x4100000u, 0x10000u, 0u, 0u, 0x3F017E0u, 0x480u, 0x100u, C_TEST_STEP(0x17010003u) } },
};
static u32 test_func_8005FE1C(u32 row)
{
    const struct func_8005FE1C_case* c = &func_8005FE1C_cases[row];
    u32 observed_values[17];
    struct MainObj obj;
    struct PlayerObj player_before;
    struct BackgroundObj backgrounds_before[3];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 37;
    obj.unk2 = c->unk2;
    obj.x_pos.val = c->x_pos;
    obj.y_pos.val = c->y_pos;
    obj.unk42 = 0x1234;
    obj.ext.main_37.unk80.word = 0;
    ((u8*)&obj.ext.main_37)[0] = 0x7D;
    ((u8*)&obj.ext.main_37)[1] = 0x7C;
    ((u8*)&obj.ext.main_37)[2] = 0x7B;
    ((u8*)&obj.ext.main_37)[3] = 0x7A;
    player_before = g_Player;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    func_8005FE1C(&obj);
    assert(obj.animation_table == (const u8* const*)rocket_spiker_animations);
    assert(obj.terrain_box == &D_800FE4E4);
    assert(obj.unk18.val == obj.x_pos.val && obj.unk1C.val == obj.y_pos.val);
    assert(obj.x_accel == 0 && obj.gravity == 0);
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(background_objects));
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.contact_damage;
    observed_values[5] = (u32)obj.unk62;
    observed_values[6] = (u32)obj.unk15;
    observed_values[7] = (u32)obj.unk42;
    observed_values[8] = (u32)obj.x_pos.val;
    observed_values[9] = (u32)obj.y_pos.val;
    observed_values[10] = (u32)obj.x_speed;
    observed_values[11] = (u32)obj.y_speed;
    observed_values[12] = (u32)((u8*)&obj.ext.main_37)[1];
    observed_values[13] = (u16)obj.ext.main_37.unk84.i.lo | (u32)(u16)obj.ext.main_37.unk84.i.hi << 16;
    observed_values[14] = (u16)obj.ext.main_37.unk88.i.lo | (u32)(u16)obj.ext.main_37.unk88.i.hi << 16;
    observed_values[15] = obj.ext.main_37.unk8C.bytes[0] | (u32)obj.ext.main_37.unk8C.bytes[1] << 8 | (u32)obj.ext.main_37.unk8C.bytes[2] << 16 | (u32)obj.ext.main_37.unk8C.bytes[3] << 24;
    observed_values[16] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 17);
}

static void rs_resume(void)
{
    state_reset(1, 0, 0);
    so.ext.main_37.saved_unk5 = 3;
    rocket_spiker_resume_step(&so);
}

void rocket_spiker_main(struct MainObj*);
void rocket_spiker_drop(struct MainObj*);
void rocket_spiker_drop_land(struct MainObj*);
void rocket_spiker_crawl(struct MainObj*);
void rocket_spiker_crawl_fall(struct MainObj*);
void rocket_spiker_crawl_turn(struct MainObj*);
void rocket_spiker_boost(struct MainObj*);
void func_800606D8(struct MainObj*);
void rocket_spiker_boost_launch(struct MainObj*);
void rocket_spiker_boost_pause(struct MainObj*);
void rocket_spiker_boost_brake(struct MainObj*);
void rocket_spiker_boost_rest(struct MainObj*);
#define RS(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, memset(weapon_objects, 0, sizeof(weapon_objects)), SPIKE_IMMUNE_SET(g_Player, 1))
#define RSX() (state_extra = so.ext.main_37.unk8C.bytes[0] | so.ext.main_37.unk8C.bytes[1] << 8 | (u8)so.ext.main_37.saved_unk5 << 16 | (u32)so.state << 24)
static void rs_update_crawl(void)
{
    RS(3, 0), so.state = 1, so.collision_flags = 8, rocket_spiker_update(&so), RSX();
}
static void rs_update_boost(void) { RS(4, 4), so.state = 1, so.unk2 = 3, so.unk7C = 5, rocket_spiker_update(&so), RSX(); }
static void rs_main_off_screen(void) { RS(3, 0), so.state = 1, so.collision_flags = 8, so.x_pos.i.hi = 0x200, rocket_spiker_main(&so), RSX(); }
static void rs_main_defeated(void) { RS(3, 0), so.state = 1, so.collision_flags = 8, so.hp = 1, state_hit(&so, 0, 0, 1), cur_random = 1, rocket_spiker_main(&so), RSX(); }
static void rs_despawn(void) { RS(3, 0), so.state = 2, so.active = 0x41, so.ext.main_37.saved_unk5 = 3, so.ext.main_37.unk8C.bytes[0] = 5, rocket_spiker_update(&so), RSX(); }
#define DROP(flags, px, vy) (RS(2, 0), so.collision_flags = flags, g_Player.x_pos.i.hi = px, so.y_speed = vy, rocket_spiker_drop(&so), RSX())
static void rs_drop_land_ahead(void)
{
    DROP(8, 0, 0);
}
static void rs_drop_land_turn(void) { DROP(8, 0x100, 0); }
static void rs_drop_falling(void) { DROP(0, 0, -0x18000); }
static void rs_drop_settle(void) { RS(2, 1), so.animation_step.fields.event = 1, rocket_spiker_drop_land(&so), RSX(); }
static void rs_drop_settling(void) { RS(2, 1), rocket_spiker_drop_land(&so), RSX(); }
#define CRAWL(face, flags, vx) (RS(3, 0), so.unk15 = face, so.collision_flags = flags, so.x_speed = vx, rocket_spiker_crawl(&so), RSX())
static void rs_crawl_left_wall(void)
{
    CRAWL(0, 10, -0x18000);
}
static void rs_crawl_right_wall(void) { CRAWL(PLAYER_FACING_RIGHT, 9, 0x18000); }
static void rs_crawl_ledge(void) { CRAWL(0, 0, -0x18000); }
static void rs_crawl_right(void) { CRAWL(PLAYER_FACING_RIGHT, 8, 0x18000); }
static void rs_crawl_fall_done(void) { RS(3, 1), so.animation_step.fields.event = 1, rocket_spiker_crawl_fall(&so), RSX(); }
static void rs_crawl_fall(void) { RS(3, 1), rocket_spiker_crawl_fall(&so), RSX(); }
static void rs_crawl_turn_done(void) { RS(3, 2), so.animation_step.fields.event = 1, rocket_spiker_crawl_turn(&so), RSX(); }
static void rs_crawl_turn(void) { RS(3, 2), rocket_spiker_crawl_turn(&so), RSX(); }
#define BOOST(sub, face, tick, smoke, puff, py, run) (RS(4, sub), so.unk15 = face, so.unk7C = 5, so.unk7E = tick, so.ext.main_37.unk8C.bytes[0] = smoke, so.ext.main_37.unk8C.bytes[1] = puff, so.ext.main_37.unk88.i.lo = 0x100, g_Player.y_pos.i.hi = py, run(&so), RSX())
static void rs_boost_wait_spotted(void)
{
    BOOST(0, 0, 0, 9, 1, 0, rocket_spiker_boost);
}
static void rs_boost_wait_sparks(void) { BOOST(0, 0, 7, 0, 5, 0x200, rocket_spiker_boost); }
static void rs_boost_wait_smoke_right(void) { BOOST(0, PLAYER_FACING_RIGHT, 4, 0, 5, 0x200, rocket_spiker_boost); }
static void rs_boost_aim_smoke(void) { BOOST(1, 0, 0, 9, 1, 0x200, func_800606D8); }
static void rs_boost_aim_sparks(void) { BOOST(1, 0, 7, 0, 5, 0x200, func_800606D8); }
static void rs_boost_aim_smoke_right(void) { BOOST(1, PLAYER_FACING_RIGHT, 4, 0, 5, 0x200, func_800606D8); }
static void rs_boost_launch_done(void) { RS(4, 2), so.unk7C = 1, so.x_speed = 0x10000, rocket_spiker_boost_launch(&so), RSX(); }
static void rs_boost_launch(void) { RS(4, 2), so.unk7C = 5, so.x_speed = 0x10000, rocket_spiker_boost_launch(&so), RSX(); }
#define FLY(face, x) (RS(4, 3), so.unk15 = face, so.x_pos.i.hi = x, func_800608CC(&so), RSX())
static void rs_boost_fly_left_end(void)
{
    FLY(0, 0x1790);
}
static void rs_boost_fly_left(void) { FLY(0, 0x17B0); }
static void rs_boost_fly_right_end(void) { FLY(PLAYER_FACING_RIGHT, 0x1790); }
static void rs_boost_fly_right(void) { FLY(PLAYER_FACING_RIGHT, 0x1770); }
static void rs_boost_pause_done(void) { RS(4, 4), so.unk7C = 1, rocket_spiker_boost_pause(&so), RSX(); }
static void rs_boost_brake_stop(void) { RS(4, 5), so.x_speed = 0x2000, so.x_accel = 0x2000, rocket_spiker_boost_brake(&so), RSX(); }
static void rs_boost_brake(void) { RS(4, 5), so.x_speed = 0x10000, so.x_accel = 0x2000, rocket_spiker_boost_brake(&so), RSX(); }
static void rs_boost_rest_done(void) { RS(4, 6), so.unk7C = 1, rocket_spiker_boost_rest(&so), RSX(); }
static void rs_boost_rest(void) { RS(4, 6), so.unk7C = 5, rocket_spiker_boost_rest(&so), RSX(); }
static void rs_init(u8 kind) { RS(0, 0), so.unk2 = kind, g_Player.x_pos.i.hi = 0x100, func_8005FE1C(&so), RSX(); }
static void rs_init_drop(void) { rs_init(0); }
static void rs_init_crawl_left(void) { rs_init(1); }
static void rs_init_crawl_right(void) { rs_init(2); }
static void (*const rocket_spiker_misc_cases[])(void) = {
    rs_resume,
    rs_update_crawl,
    rs_update_boost,
    rs_main_off_screen,
    rs_main_defeated,
    rs_despawn,
    rs_drop_land_ahead,
    rs_drop_land_turn,
    rs_drop_falling,
    rs_drop_settle,
    rs_drop_settling,
    rs_crawl_left_wall,
    rs_crawl_right_wall,
    rs_crawl_ledge,
    rs_crawl_right,
    rs_crawl_fall_done,
    rs_crawl_fall,
    rs_crawl_turn_done,
    rs_crawl_turn,
    rs_boost_wait_spotted,
    rs_boost_wait_sparks,
    rs_boost_wait_smoke_right,
    rs_boost_aim_smoke,
    rs_boost_aim_sparks,
    rs_boost_aim_smoke_right,
    rs_boost_launch_done,
    rs_boost_launch,
    rs_boost_fly_left_end,
    rs_boost_fly_left,
    rs_boost_fly_right_end,
    rs_boost_fly_right,
    rs_boost_pause_done,
    rs_boost_brake_stop,
    rs_boost_brake,
    rs_boost_rest_done,
    rs_boost_rest,
    rs_init_drop,
    rs_init_crawl_left,
    rs_init_crawl_right,
};
static const u32 rocket_spiker_misc_expected[] = {
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
    3u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x1030000u,
    0u,
    0x404u,
    4u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x1040000u,
    0u,
    3u,
    0u,
    0x2000000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x2030000u,
    0u,
    3u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0x80000000u,
    1u,
    0x2030000u,
    0x2100u,
    0u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x102u,
    0u,
    0x800000u,
    0xFFFE8000u,
    0u,
    0u,
    3u,
    0u,
    0u,
    0u,
    0x203u,
    0u,
    0x800000u,
    0x18000u,
    0u,
    0u,
    0x4002u,
    0u,
    0u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0xFFFE8000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    3u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x102u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x203u,
    0u,
    0x7E8000u,
    0x18000u,
    0u,
    0u,
    0x4002u,
    0u,
    0u,
    0u,
    0x203u,
    0u,
    0x818000u,
    0xFFFE8000u,
    0u,
    0u,
    2u,
    0u,
    0u,
    0u,
    0x103u,
    0u,
    0x7E8000u,
    0u,
    0xFFFE8000u,
    0u,
    3u,
    0u,
    0u,
    0u,
    3u,
    0u,
    0x818000u,
    0x18000u,
    0u,
    0u,
    0x4000u,
    0u,
    0u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    1u,
    0u,
    0u,
    0u,
    0x103u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    3u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x203u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x104u,
    0x10026u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x1E00u,
    0u,
    4u,
    0x80005u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x400u,
    0x2100u,
    4u,
    0x50005u,
    0x800000u,
    0u,
    0u,
    0u,
    0x4000u,
    0u,
    0x401u,
    0u,
    0x104u,
    0x10004u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x1E00u,
    0u,
    0x104u,
    0x80004u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x400u,
    0x2100u,
    0x104u,
    0x50004u,
    0x800000u,
    0u,
    0u,
    0u,
    0x4000u,
    0u,
    0x401u,
    0u,
    0x304u,
    0u,
    0x810000u,
    0u,
    0u,
    0x2000u,
    0u,
    0u,
    0u,
    0u,
    0x204u,
    4u,
    0x810000u,
    0x10000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x404u,
    0x28u,
    0x17A00000u,
    0x58000u,
    0u,
    0x2000u,
    0u,
    0u,
    0u,
    0u,
    0x304u,
    0u,
    0x17B00000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x404u,
    0x28u,
    0x17800000u,
    0xFFFA8000u,
    0u,
    0x2000u,
    0x4000u,
    0u,
    0u,
    0u,
    0x304u,
    0u,
    0x17700000u,
    0u,
    0u,
    0u,
    0x4000u,
    0u,
    0u,
    0u,
    0x504u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x604u,
    0x28u,
    0x802000u,
    0u,
    0u,
    0x2000u,
    0u,
    0u,
    0u,
    0u,
    0x504u,
    0u,
    0x810000u,
    0xE000u,
    0u,
    0x2000u,
    0u,
    0u,
    0u,
    0u,
    0x304u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x604u,
    4u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0xFFFE8000u,
    0u,
    0x4001u,
    0x60003u,
    0x1000100u,
    0u,
    3u,
    0u,
    0x800000u,
    0xFFFE8000u,
    0u,
    0u,
    0u,
    0x60003u,
    0x1000100u,
    0u,
    3u,
    0u,
    0x800000u,
    0x18000u,
    0u,
    0u,
    0x4000u,
    0x60003u,
    0x1000100u,
    0u,
};

static u32 test_rocket_spiker_misc(u32 row)
{
    return state_run(rocket_spiker_misc_cases[row], row, &rocket_spiker_misc_expected[row * 10]);
}

#include "support/tile_writes.h"
static void rs_boost_aim_blast(void)
{
    RS(4, 1), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 3, tile_writes_begin();
    so.unk7C = 1, so.ext.main_37.unk8C.bytes[1] = 5, so.ext.main_37.unk84.i.lo = 0x1708, so.ext.main_37.unk84.i.hi = 0x400;
    tile_writes_expect(5, 0x1708, 0x400, 1), func_800606D8(&so), RSX(), state_extra ^= tile_writes_end(), engine_obj.stage = 0;
}
static void (*const rocket_spiker_tiles_cases[])(void) = {
    rs_boost_aim_blast,
};
static const u32 rocket_spiker_tiles_expected[] = {
    0x204u,
    0x10020u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0xB86D83DBu,
    0x2100u,
};
static u32 test_rocket_spiker_tiles(u32 row)
{
    return state_run(rocket_spiker_tiles_cases[row], row, &rocket_spiker_tiles_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "rocket_spiker_misc", 0, 0, COUNT(rocket_spiker_misc_cases), test_rocket_spiker_misc },
    { "func_8005FE1C", 0, 0, 8, test_func_8005FE1C },
    { "rocket_spiker_tiles", 0, 0, COUNT(rocket_spiker_tiles_cases), test_rocket_spiker_tiles },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(rocket_spiker_misc_cases) + 8 + COUNT(rocket_spiker_tiles_cases);
