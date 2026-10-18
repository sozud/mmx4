#include "test_runtime.h"
#include "main/mains/main_70_drone_pod.h"
#include "main/55C4.h"
#include "main/player_animations.h"
#include "main/player_common.h"
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

const struct CTestGroup c_test_groups[] = {
    { "drone_pod_random_explosion", 0, 0, 1, test_drone_pod_random_explosion },
    { "actual_stage7_pod_first_two_drone_launch_full_Main_pool", NULL, NULL, 1, launch },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1;
