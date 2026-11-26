#include "test_runtime.h"
#include "main/mains/main_70_drone_pod.h"
#include "main/55C4.h"
#include "main/player_animations.h"
#include "main/player_common.h"
#include "weapon_resources.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static const u32 drone_pod_random_explosion_expected[] = { 1u };
static u32 test_drone_pod_random_explosion(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&visual_objects, 0, sizeof(visual_objects));
    main_bss_state.frame_counter = -1048575;
    drone_pod_random_explosion(&obj);
    observed_values[0] = (u32)obj.ext.main_70.unk85;
    return c_test_observe(0, row, observed_values, drone_pod_random_explosion_expected, 1);
}
#undef main_bss_state

void drone_pod_intro_fill_health(struct MainObj*);
void drone_pod_intro_open(struct MainObj*);
void drone_pod_intro_wait_player(struct MainObj*);
void drone_pod_launch_fire(struct MainObj*);
void drone_pod_launch_prepare(struct MainObj*);
void func_80088C40(struct MainObj*);
extern union AnimationStep* D_80104974[14];
static struct MainObj expected_mains[48];
static u32 launch(u32 row)
{
    struct MainObj* self = &main_objects[0];
    struct EngineObj engine;
    struct PlayerObj player;
    struct BackgroundObj backgrounds[3];
    u32 i;
    u16 rng = cur_random;
    s8 bank = D_8013E198[0];
    (void)row;
    engine_obj.state = 6;
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.max_hp = 32;
    engine_obj.stage = 7;
    engine_obj.substage = 1;
    engine_obj.checkpoint = 0;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = 2400;
    g_Player.y_pos.i.hi = 880;
    g_Player.animation_table = (u32**)D_80119DF0;
    set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    background_objects[0].x_pos.i.hi = 2384;
    background_objects[0].y_pos.i.hi = 768;
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    self->id = 70;
    self->x_pos.i.hi = 2544;
    self->y_pos.i.hi = 880;
    func_80088C40(self);
    drone_pod_intro_wait_player(self);
    for (i = 0; i < 64 && self->unk5 == 2; i++)
        drone_pod_intro_open(self);
    assert(self->unk5 == 3);
    D_8013E198[0] = -1;
    for (i = 0; i < 48; i++)
        drone_pod_intro_fill_health(self);
    assert(self->hp == 48 && self->state == 1 && self->unk5 == 3 && self->unk6 == 0);
    D_8013E198[0] = bank;
    engine = engine_obj;
    player = g_Player;
    self->on_screen = 1;
    drone_pod_launch_prepare(self);
    assert(self->unk6 == 1 && self->unk7C == 39);
    for (i = 0; i < 38; i++)
        drone_pod_launch_fire(self);
    assert(self->unk7C == 1 && self->ext.main_70.unk84 == 0);
    memcpy(expected_mains, main_objects, sizeof(expected_mains));
    expected_mains[0].unk7C = 24;
    expected_mains[0].unk6 = 2;
    expected_mains[0].unk17 = 13;
    expected_mains[0].previous_animation_index = 0xFF;
    expected_mains[0].animation_cursor = (const u8*)D_80104974[13];
    expected_mains[0].animation_step = D_80104974[13][0];
    expected_mains[0].ext.main_70.unk84 = 2;
    drone_pod_launch_fire(self);
    assert(c_test_word_difference((u32*)main_objects, (u32*)expected_mains, sizeof(expected_mains) / 4) == 0);
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    assert(cur_random == rng);
    return 1;
}

void func_80089588(struct MainObj* self);
static const struct {
    u8 start;
    u32 expected[5];
} pair_cases[] = {
    { 0, { 0x413A0001u, 0x02E009C8u, 0x413A0002u, 0x03700A30u, 2u } },
    { 14, { 0x413A0101u, 0x02E008F0u, 0x413A0101u, 0x040008F0u, 0u } },
    { 2, { 0x413A0002u, 0x03700A30u, 0x413A0001u, 0x040009C8u, 4u } },
    { 4, { 0x413A0101u, 0x02E008F0u, 0x413A0102u, 0x037008A0u, 6u } },
};
static u32 pair_metadata[8];
static s32 pair_frames[8];
static u32 pair(u32 row)
{
    static struct MainObj pod;
    u8* old_frames = TEST_MENU_FRAMES;
    u32* old_metadata = D_801406A8;
    u32 observed[5], i;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)&pod, sizeof(pod) / 4);
    for (i = 0; i < COUNT(pair_metadata); i++) {
        pair_metadata[i] = (i + 1) * 128;
        pair_frames[i] = (i + 1) * 64;
    }
    D_801406A8 = pair_metadata;
#ifdef MMX4_SATURN
    saturn_stage_graphics_offsets_pointer = pair_metadata;
#endif
    TEST_MENU_FRAMES = (u8*)pair_frames;
    engine_obj.stage = 7;
    engine_obj.substage = 1;
    pod.active = 0x41;
    pod.id = 70;
    pod.bg_offset = 0;
    pod.ext.main_70.unk84 = pair_cases[row].start;
    func_80089588(&pod);
    for (i = 0; i < 2; i++) {
        struct MainObj* drone = &main_objects[i];
        assert(drone->unk40 == (u16)OBJECT_STAGE_TEXTURE(func_8002938C(0x3A)) && drone->unk42 == (u16)OBJECT_STAGE_CLUT(0x3A));
        assert(drone->sprite_frames == (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x3A)));
        assert(drone->unk16 == VISUAL_SATURN_LAYER(5) && drone->bg_offset == 0);
        observed[i * 2] = (u8)drone->unk2 | (u32)(drone->unk15 == PLAYER_FACING_RIGHT) << 8 | (u32)(u8)drone->id << 16 | (u32)(u8)drone->active << 24;
        observed[i * 2 + 1] = (u16)drone->x_pos.i.hi | (u32)(u16)drone->y_pos.i.hi << 16;
    }
    assert(main_objects[2].active == 0);
    observed[4] = pod.ext.main_70.unk84;
    D_801406A8 = old_metadata;
    TEST_MENU_FRAMES = old_frames;
    return c_test_observe(0, row, observed, pair_cases[row].expected, 5);
}

#include "support/state_cases.h"
void drone_pod_alarm_flash(struct MainObj*);
void drone_pod_rest_open(struct MainObj*);
void drone_pod_launch(struct MainObj*);
#define DP(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, memset(weapon_objects, 0, sizeof(weapon_objects)), SPIKE_IMMUNE_SET(g_Player, 1))
#define DPX() (state_extra = (u8)so.ext.main_70.saved_unk5 | (u32)so.state << 8)
#define ALARM() (state_extra = (u8)so.ext.main_70.alarm_timer | (u8)so.ext.main_70.flash_timer << 8 | (u32)so.ext.main_70.alarm_color << 16 | (u32)so.ext.main_70.alarm_flashing << 24)
static void dp_init_after_checkpoint(void)
{
    DP(0, 0), so.active = 0x41, engine_obj.checkpoint = 2, drone_pod_update(&so), DPX();
}
static void dp_wait_player(void) { DP(1, 0), drone_pod_update(&so), DPX(); }
#define RUN(step, setup) (DP(step, 0), so.state = 1, so.unk7C = 5, setup, func_80088EA4(&so), DPX())
static void dp_run_hit_hard(void)
{
    RUN(2, (so.hp = 0x30, state_hit(&so, 0, 0, 5)));
}
static void dp_run_defeated(void) { RUN(2, (so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void dp_run_resume_hit_reaction(void) { RUN(1, 0); }
#define DEATH(step, timer, tick, frame, seed) (DP(step, 0), so.state = 2, so.unk7C = timer, so.unk7E = tick, WEAPON_FRAME_COUNTER = frame, cur_random = seed, drone_pod_update(&so))
static void dp_death_start(void)
{
    DP(0, 0), so.state = 2, so.unk42 = 0x8001, WEAPON_FRAME_COUNTER = 1, drone_pod_update(&so), ALARM();
}
static void dp_death_explode_done(void) { DEATH(1, 1, 5, 1, 4), ALARM(); }
static void dp_death_explode_burst(void) { DEATH(1, 5, 1, 1, 4), ALARM(); }
static void dp_death_explode(void) { DEATH(1, 5, 3, 1, 4), ALARM(); }
static void dp_death_alarm_burst(void) { DP(2, 0), so.state = 2, so.unk7C = 5, so.ext.main_70.alarm_timer = 5, WEAPON_FRAME_COUNTER = 4, cur_random = 4, drone_pod_update(&so), ALARM(); }
static void dp_death_alarm_end(void) { DEATH(2, 1, 3, 1, 4), ALARM(); }
static void dp_death_debris_done(void) { DEATH(4, 1, 5, 1, 4), state_extra = (u16)so.y_pos.i.hi; }
static void dp_death_debris_burst(void) { DEATH(4, 5, 1, 8, 4), state_extra = (u16)so.y_pos.i.hi; }
static void dp_death_debris(void) { DEATH(4, 5, 3, 1, 4), state_extra = (u16)so.y_pos.i.hi; }
static void dp_death_finish(void) { DEATH(5, 0, 0, 1, 4), DPX(); }
#define FLASH(timer, flash, color, flashing) (DP(2, 0), so.ext.main_70.alarm_timer = timer, so.ext.main_70.flash_timer = flash, so.ext.main_70.alarm_color = color, so.ext.main_70.alarm_flashing = flashing, drone_pod_alarm_flash(&so), ALARM())
static void dp_alarm_start(void)
{
    FLASH(1, 4, 0, 0);
}
static void dp_alarm_red(void) { FLASH(9, 2, 0, 1); }
static void dp_alarm_red_end(void) { FLASH(9, 1, 0, 1); }
static void dp_alarm_white(void) { FLASH(9, 2, 1, 1); }
static void dp_alarm_white_end(void) { FLASH(9, 1, 1, 1); }
static void dp_blast(u16 seed) { DP(2, 0), WEAPON_FRAME_COUNTER = 1, cur_random = seed, drone_pod_random_explosion(&so), state_extra = so.ext.main_70.unk85; }
static void dp_blast_bottom_left(void) { dp_blast(2); }
static void dp_blast_bottom_right(void) { dp_blast(3); }
static void dp_rest_close(void) { DP(2, 0), so.state = 1, so.unk7C = 1, func_80088EA4(&so), DPX(); }
static void dp_rest_open_done(void) { DP(2, 1), so.unk7C = 1, drone_pod_rest_open(&so), DPX(); }
static void dp_rest_open(void) { DP(2, 1), so.unk7C = 5, drone_pod_rest_open(&so), DPX(); }
static void dp_launch_close_done(void) { DP(3, 2), so.unk7C = 1, drone_pod_launch(&so), DPX(); }
static void dp_launch_close(void) { DP(3, 2), so.unk7C = 5, drone_pod_launch(&so), DPX(); }

static void (*const drone_pod_states_cases[])(void) = {
    dp_init_after_checkpoint,
    dp_wait_player,
    dp_run_hit_hard,
    dp_run_defeated,
    dp_run_resume_hit_reaction,
    dp_death_start,
    dp_death_explode_done,
    dp_death_explode_burst,
    dp_death_explode,
    dp_death_alarm_burst,
    dp_death_alarm_end,
    dp_death_debris_done,
    dp_death_debris_burst,
    dp_death_debris,
    dp_death_finish,
    dp_alarm_start,
    dp_alarm_red,
    dp_alarm_red_end,
    dp_alarm_white,
    dp_alarm_white_end,
    dp_blast_bottom_left,
    dp_blast_bottom_right,
    dp_rest_close,
    dp_rest_open_done,
    dp_rest_open,
    dp_launch_close_done,
    dp_launch_close,
};
static const u32 drone_pod_states_expected[] = {
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
    1u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    4u,
    0x800000u,
    0u,
    0u,
    0u,
    0x80000000u,
    0x2B0001u,
    0x102u,
    0x2100u,
    0u,
    4u,
    0x800000u,
    0u,
    0u,
    0u,
    0x80000003u,
    1u,
    0x202u,
    0x2100u,
    0u,
    5u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x100u,
    0u,
    1u,
    0x50028u,
    0x800000u,
    0u,
    0u,
    0u,
    0x10000u,
    0u,
    0x428u,
    0u,
    2u,
    0x500A0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    1u,
    0x50004u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x2100u,
    1u,
    0x20004u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    4u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    4u,
    0x2100u,
    3u,
    0x20000u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    5u,
    0x50000u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x60u,
    0u,
    4u,
    0x50004u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x364u,
    0x2100u,
    4u,
    0x20004u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x60u,
    0u,
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
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x1000400u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x1000109u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x1045Au,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x1010109u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x428u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    0x2100u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    3u,
    0x2100u,
    0x102u,
    0x18u,
    0x800000u,
    0u,
    0u,
    0u,
    1u,
    0u,
    0x102u,
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
    0x5Au,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x203u,
    4u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
};
static u32 test_drone_pod_states(u32 row)
{
    return state_run(drone_pod_states_cases[row], row, &drone_pod_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "drone_pod_states", 0, 0, COUNT(drone_pod_states_cases), test_drone_pod_states },
    { "drone_pod_random_explosion", 0, 0, 1, test_drone_pod_random_explosion },
    { "actual_stage7_pod_first_two_drone_launch_full_Main_pool", NULL, NULL, 1, launch },
    { "drone_pair_launch_slots_into_an_empty_pool", NULL, NULL, COUNT(pair_cases), pair },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(drone_pod_states_cases) + 1 + 1 + COUNT(pair_cases);
