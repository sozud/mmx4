#include "test_runtime.h"
#include "main/55C4.h"
#include "main/player_animations.h"
#include "main/weapons/weapon_20_plasma_shot.h"
#include "main/player_common.h"
void plasma_shot_main(struct WeaponObj*);
void func_8002DF7C(struct WeaponObj*, s32);
static struct WeaponObj expected_weapons[16];
static struct VisualObj expected_visuals[32];
static u32 frames[32];
static u32 hit(u32 row)
{
    struct WeaponObj* self = &weapon_objects[0];
    struct EngineObj engine;
    struct PlayerObj player;
    struct MainBssState main = main_bss_state;
    s8 bank = D_8013E198[1];
    u16 rng = cur_random;
    u32 i;
    (void)row;
    engine_obj.state = 6;
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.armor_parts = 4;
    engine_obj.arm_type = 2;
    engine = engine_obj;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.state = 1;
    g_Player.x_pos.i.hi = 128;
    g_Player.y_pos.i.hi = 120;
    g_Player.animation_table = (u32**)D_80119DF0;
    set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    g_Player.arm_type = 2;
    g_Player.shot_count = 1;
    player = g_Player;
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < 16; i++)
        weapon_objects[i].active = 1;
    for (i = 0; i < 32; i++)
        visual_objects[i].active = 1;
    memcpy(expected_visuals, visual_objects, sizeof(expected_visuals));
    memset(frames, 0, sizeof(frames));
    frames[12] = 96;
    TEST_SPRITE_FRAMES = (u8*)frames;
    background_objects[0].x_pos.val = background_objects[0].y_pos.val = 0;
    self->active = 0x21;
    self->id = 20;
    self->owner = &g_Player;
    self->unk15 = 0x40;
    self->x_pos.i.hi = 160;
    self->y_pos.i.hi = 120;
    func_800929DC(self);
    assert(self->state == 1 && self->animation_step.packed == 0x0F010003 && self->unk98 == 0 && self->x_vel.val == 0xB0000);
    D_8013E198[1] = -1;
    func_8002DF7C(self, 0);
    assert(self->unk98 == 1);
    memcpy(expected_weapons, weapon_objects, sizeof(expected_weapons));
    expected_weapons[0].unk98 = 0;
    expected_weapons[0].x_pos.i.hi = 171;
    expected_weapons[0].animation_step.fields.duration = 2;
    plasma_shot_main(self);
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)expected_weapons, sizeof(expected_weapons) / 4) == 0);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)expected_visuals, sizeof(expected_visuals) / 4) == 0);
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(cur_random == rng && D_8013E198[1] == -1 && TEST_SPRITE_FRAMES == (u8*)frames);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i == 12 ? 96u : 0));
    D_8013E198[1] = bank;
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "real_plasma_nonlethal_hit_feedback_orb_full_weapon_pool", NULL, NULL, 1, hit } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
