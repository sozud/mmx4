#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_02_gunner_shot.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"
#include "weapon_resources.h"

#ifndef VERSION_DEMO
static struct WeaponObj gunner_owner;
extern u8 gunner_shot_hit_box[4];
#define ss state_room.shot
#define GS(kind, facing, setup) (state_reset(0, 0, 0), memset(&gunner_owner, 0, sizeof(gunner_owner)), gunner_owner.unk15 = facing, ss.active = 1, ss.state = 1, ss.unk2 = kind, ss.unk7C = &gunner_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x400, setup, func_8009A10C(&ss))
static void gs_spread_left(void)
{
    GS(1, 0, 0);
}
static void gs_spread_right(void) { GS(3, 0x40, 0); }
static void gs_straight(void) { GS(0, 0, ss.x_vel.val = 0x20000); }
static void gs_grounded(void) { GS(0, 0, ss.unk70 = 8); }
static struct PlayerObj gunner_player;
static void gs_hit_player(void)
{
    gunner_player = g_Player;
    GS(0, 0, (g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x60, g_Player.unk68 = &state_hit_box, ss.unk68 = &state_hit_box));
    g_Player = gunner_player;
}
static void gs_away(void) { GS(0, 0, ss.x_pos.i.hi = 0x1000); }
#else
extern u8 gunner_shot_hit_box[4];
#define ss state_room.shot
#endif

extern u8 eregion_fireball_hit_box[4], eregion_wing_slash_hit_box[4];
extern u8 mech_boulder_shockwave_boxes[4];
static struct MainObj go_owner;
static u32 go_collision_state;
#define SH(st, kind, face) (state_reset(0, 0, 0), memset(&go_owner, 0, sizeof(go_owner)), go_owner.animation_table = (void*)state_table, memset(weapon_objects, 0, sizeof(weapon_objects)), ss.active = 1, ss.state = st, ss.unk2 = kind, ss.unk15 = face, ss.unk7C = (struct WeaponObj*)&go_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x400, g_Player.y_pos.i.hi = 0x60, SPIKE_IMMUNE_SET(g_Player, 1), go_collision_state = 0x8000, ss.unk84.collision_state = &go_collision_state)
#define PLAYER_HERE() (g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x60, ((struct MainObj*)&g_Player)->hurt_box = &state_hit_box, g_Player.hp = 0x10)
#define OWNER(x, y, face) (go_owner.x_pos.i.hi = x, go_owner.y_pos.i.hi = y, go_owner.unk15 = face)
static void go_gunner_init(void) { SH(0, 1, 0), ss.x_vel.val = 0x10000, ss.y_vel.val = 0x8000, gunner_shot_update(&ss); }
static void go_gunner_hits_player(void) { SH(1, 0, 0), ss.unk50.data = gunner_shot_hit_box, PLAYER_HERE(), gunner_shot_fly(&ss); }
static void go_gunner_destroyed(void) { SH(1, 0, 0), ((struct MainObj*)&ss)->hp = 1, state_hit((struct MainObj*)&ss, 0, 0, 1), gunner_shot_fly(&ss); }
static void go_gunner_off_screen(void) { SH(1, 0, 0), ss.x_pos.i.hi = 0x200, gunner_shot_fly(&ss); }
static void go_gunner_despawn(void) { SH(2, 0, 0), gunner_shot_update(&ss); }
static void go_gunner_unused(void) { SH(1, 0, 0), gunner_shot_unused(&ss); }
#define FIREBALL(kind, face) (SH(0, kind, 0), OWNER(0x100, 0x80, face), go_owner.unk42 = 0x8123, g_Player.x_pos.i.hi = 0x200, g_Player.y_pos.i.hi = 0x80, eregion_fireball_update(&ss))
static void go_fireball_aimed(void) { FIREBALL(0, PLAYER_FACING_RIGHT); }
static void go_fireball_spread_left(void) { FIREBALL(2, 0); }
static void go_fireball_spread_right(void) { FIREBALL(1, PLAYER_FACING_RIGHT); }
#ifndef VERSION_DEMO
static void go_fireball_hits_player(void) { SH(1, 0, 0), ss.unk50.data = eregion_fireball_hit_box, PLAYER_HERE(), func_8009A10C(&ss); }
static void go_fireball_burst(void) { SH(3, 0, 0), eregion_fireball_explode(&ss); }
static void go_fireball_burst_done(void) { SH(3, 0, 0), ss.unk5 = 1, ss.animation_step.fields.relative_step = -1, eregion_fireball_explode(&ss); }
static void go_fireball_burst_off_screen(void) { SH(3, 0, 0), ss.unk5 = 1, ss.x_pos.i.hi = 0x200, eregion_fireball_explode(&ss); }
#endif
static void go_fireball_despawn(void) { SH(2, 0, 0), eregion_fireball_update(&ss); }
#define SLASH(st, face, owner_state, owner_step, ev) (SH(st, 0, 0), OWNER(face ? 0x35 : 0xCB, 0x5E, face), go_owner.state = owner_state, go_owner.unk5 = owner_step, ss.animation_step.fields.event = ev, eregion_wing_slash_update(&ss), state_extra = go_owner.ext.main_8.queued_sound)
static void go_slash_init(void) { SH(0, 0, 0), OWNER(0x100, 0x80, 0), go_owner.unk42 = 0x8123, eregion_wing_slash_update(&ss); }
static void go_slash_hits_player(void)
{
    SH(1, 0, 0);
    OWNER(0x35, 0x5E, PLAYER_FACING_RIGHT);
    go_owner.state = 1;
    go_owner.unk5 = 5;
    ss.animation_step.fields.event = -1;
    ss.unk50.data = eregion_wing_slash_hit_box;
    ss.unk60 = 5;
    PLAYER_HERE();
    SPIKE_IMMUNE_SET(g_Player, 0);
    eregion_wing_slash_update(&ss);
    state_extra = go_owner.ext.main_8.queued_sound | (u8)g_Player.hp << 8;
}
static void go_slash_owner_gone(void) { SLASH(1, 0, 2, 5, -1); }
static void go_slash_swing_end(void) { SLASH(1, 0, 1, 5, 1); }
static void go_slash_owner_moved_on(void) { SLASH(1, 0, 1, 3, 0); }
static void go_slash_despawn(void) { SLASH(2, 0, 1, 5, 0); }
static void go_boulder_init_left(void) { SH(0, 0, 0), mech_boulder_update(&ss); }
static void go_boulder_init_right(void) { SH(0, 0, PLAYER_FACING_RIGHT), mech_boulder_update(&ss); }
#define BOULDER(flag, setup) (SH(1, 0, 0), ss.unk50.data = mech_boulder_shockwave_boxes, ss.unk60 = 6, go_collision_state = flag, setup, mech_boulder_fall(&ss), state_extra = go_collision_state)
static void go_boulder_hits_player(void) { BOULDER(0x8000, (PLAYER_HERE(), SPIKE_IMMUNE_SET(g_Player, 0))); }
static void go_boulder_hits_player_again(void) { BOULDER(0x7000, (PLAYER_HERE(), SPIKE_IMMUNE_SET(g_Player, 0))); }
static void go_boulder_destroyed(void) { BOULDER(0x8000, (((struct MainObj*)&ss)->hp = 1, state_hit((struct MainObj*)&ss, 0, 0, 1))); }
static void go_boulder_off_screen(void) { BOULDER(0x8000, ss.x_pos.i.hi = 0x200); }
static void go_shockwave_start_left(void) { SH(3, 0, 0), mech_boulder_update(&ss), state_extra = go_collision_state; }
static void go_shockwave_start_right(void) { SH(3, 0, PLAYER_FACING_RIGHT), mech_boulder_update(&ss), state_extra = go_collision_state; }
#define SHOCK(flag, setup) (SH(4, 0, 0), ss.animation_step.fields.frame_index = 20, ss.unk60 = 2, go_collision_state = flag, setup, mech_boulder_shockwave(&ss), state_extra = go_collision_state)
static void go_shockwave_hits_player(void) { SHOCK(0x8000, (PLAYER_HERE(), SPIKE_IMMUNE_SET(g_Player, 0))); }
static void go_shockwave_hits_player_again(void) { SHOCK(0x7000, (PLAYER_HERE(), SPIKE_IMMUNE_SET(g_Player, 0))); }
static void go_shockwave_end(void) { SHOCK(0x8000, ss.animation_step.fields.event = 1); }
static void go_shockwave_off_screen(void) { SHOCK(0x8000, ss.x_pos.i.hi = 0x200); }
static void go_boulder_despawn(void) { SH(2, 0, 0), mech_boulder_update(&ss); }
static void go_shockwave_despawn(void) { SH(5, 0, 0), mech_boulder_update(&ss); }
static void (*const gunner_shot_fly_cases[])(void) = {
#ifndef VERSION_DEMO
    gs_spread_left,
    gs_spread_right,
    gs_straight,
    gs_grounded,
    gs_hit_player,
    gs_away,
#endif
    go_gunner_init,
    go_gunner_hits_player,
    go_gunner_destroyed,
    go_gunner_off_screen,
    go_gunner_despawn,
    go_gunner_unused,
    go_fireball_aimed,
    go_fireball_spread_left,
    go_fireball_spread_right,
#ifndef VERSION_DEMO
    go_fireball_hits_player,
    go_fireball_burst,
    go_fireball_burst_done,
    go_fireball_burst_off_screen,
#endif
    go_fireball_despawn,
    go_slash_init,
    go_slash_hits_player,
    go_slash_owner_gone,
    go_slash_swing_end,
    go_slash_owner_moved_on,
    go_slash_despawn,
    go_boulder_init_left,
    go_boulder_init_right,
    go_boulder_hits_player,
    go_boulder_hits_player_again,
    go_boulder_destroyed,
    go_boulder_off_screen,
    go_shockwave_start_left,
    go_shockwave_start_right,
    go_shockwave_hits_player,
    go_shockwave_hits_player_again,
    go_shockwave_end,
    go_shockwave_off_screen,
    go_boulder_despawn,
    go_shockwave_despawn,
};
static const u32 gunner_shot_fly_expected[] = {
#ifndef VERSION_DEMO
    1u, 0x101u, 0x800000u, 0x680000u, 0u, 0xFFF80000u, 0u, 0x40000u, 0u, 0u, 1u, 0x301u, 0x800000u, 0x680000u, 0u, 0xFFF80000u, 0u, 0x40000u, 0u, 0u, 1u, 1u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 0u, 0u, 3u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 1u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 1u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u,
#endif
    1u, 0xFF000101u, 0x920000u, 0x5E0000u, 0x30000u, 0x18000u, 0u, 0x50000u, 0u, 0u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x2100u,
    2u, 1u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u,
    0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    1u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    1u, 0xFF400001u, 0x1530000u, 0x800000u, 0x40000u, 0u, 0u, 0x50123u, 0u, 0u,
    1u, 0xFF000201u, 0xAD0000u, 0x800000u, 0u, 0xFFF80000u, 0u, 0x50123u, 0u, 0u,
    1u, 0xFF400101u, 0x1530000u, 0x800000u, 0u, 0xFFF80000u, 0u, 0x50123u, 0u, 0u,
#ifndef VERSION_DEMO
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    0x103u, 0xFF000001u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0x41000000u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u,
    0x102u, 1u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u,
#endif
    0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    1u, 0xFF000001u, 0xB50000u, 0x820000u, 0u, 0u, 0u, 0x58123u, 0u, 0u,
    1u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x8B00u | SATURN_SOUND(0x1C, 0x07), 0u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    1u, 0xFF000001u, 0x600000u, 0x780000u, 0xFFFD4000u, 0x70000u, 0x420000u, 0x50000u, 0u, 0u,
    1u, 0xFF400001u, 0xA00000u, 0x780000u, 0x2C000u, 0x70000u, 0x420000u, 0x50000u, 0u, 0u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x8001u, 0x41000000u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x7000u, 0x41000000u,
    2u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0x8000u, 0x41002100u,
    2u, 1u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x8000u, 0u,
    4u, 0xFF000001u, 0x670000u, 0x810000u, 0u, 0u, 0u, 0x50000u, 0x8000u, 0u,
    4u, 0xFF400001u, 0x990000u, 0x810000u, 0u, 0u, 0u, 0x50000u, 0x8000u, 0u,
    4u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x8001u, 0u,
    4u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x7000u, 0u,
    5u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x8000u, 0u,
    5u, 1u, 0x2000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x8000u, 0u,
    0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
};

static u32 test_gunner_shot_fly(u32 row)
{
    return object_run(gunner_shot_fly_cases[row], row, &gunner_shot_fly_expected[row * 10]);
}

extern union AnimationStep* dash_gunner_animations[];
extern u8 gunner_shot_hit_box[4];
static const struct {
    u8 stage, substage;
    s16 x;
    u8 clear;
} scenes[] = {
    { 0, 1, 0xF41, 1 },
    { 0, 1, 0xF40, 0 },
    { 0, 1, 0xF3F, 0 },
    { 0, 0, 0xF41, 0 },
    { 1, 1, 0xF41, 0 },
};
static struct WeaponObj weapons_before[16];
static u32 opening_guard(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 scene = row % COUNT(scenes), facing = row / COUNT(scenes) % 2, layer = row / COUNT(scenes) / 2;
    s32 velocity = facing ? 3 * 65536 : -3 * 65536;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_before = g_Player;
    engine_obj.stage = scenes[scene].stage;
    engine_obj.substage = scenes[scene].substage;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[layer].x_pos.val = (scenes[scene].x - 160) * 65536;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 2;
    obj.state = 1;
    obj.on_screen = 7;
    obj.unk5 = 3;
    obj.unk6 = 4;
    obj.unk7 = 5;
    obj.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
    obj.bg_offset = layer;
    obj.unk42 = 0x9234;
    obj.x_pos.val = scenes[scene].x * 65536 + 0x1234 - velocity;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = velocity;
    obj.unk50.data = obj.unk54 = gunner_shot_hit_box;
    obj.unk58.animation_steps = D_80105FF0;
    obj.unk5C = 1;
    obj.unk60 = 2;
    obj.animation_table = (u32**)dash_gunner_animations;
    set_animation(&obj, 8);
    assert(obj.animation_step.packed == C_TEST_STEP(0x38000101));
    expected = obj;
    expected.x_pos.val += velocity;
    if (scenes[scene].clear) {
        expected.active = expected.id = expected.unk2 = expected.on_screen = 0;
        expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
    } else {
        expected.on_screen = 1;
        expected.unk42 = 0x1234;
    }
    gunner_shot_fly(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "gunner_shot_fly", 0, 0, COUNT(gunner_shot_fly_cases), test_gunner_shot_fly },
    { "opening_cleanup_boundary_and_other_scenes", NULL, NULL, COUNT(scenes) * 6, opening_guard },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(gunner_shot_fly_cases) + COUNT(scenes) * 6;
