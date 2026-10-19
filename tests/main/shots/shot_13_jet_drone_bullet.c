#include "test_runtime.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"
void jet_drone_bullet_fly(struct ShotObj*);
extern union AnimationStep* jet_drone_animations[];
extern u8 jet_drone_bullet_hit_box[4];
static const struct {
    u8 stage, substage, checkpoint, contact;
    s16 player_x;
} scenes[] = {
    { 3, 0, 0, 0, 0x7B7 },
    { 3, 0, 0, 1, 0x7B6 },
    { 4, 0, 0, 1, 0x7B7 },
    { 3, 1, 0, 1, 0x7B7 },
    { 3, 0, 1, 1, 0x7B7 },
};
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 intro_guard(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 scene = row % COUNT(scenes), hit = row / COUNT(scenes) % 2, facing = row / COUNT(scenes) / 2, i;
    s32 velocity = facing ? 0x20000 : -0x20000;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.stage = scenes[scene].stage;
    engine_obj.substage = scenes[scene].substage;
    engine_obj.checkpoint = scenes[scene].checkpoint;
    engine_obj.cur_character = 1;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.val = (scenes[scene].player_x - 160) * 65536;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    g_Player.active = 0x41;
    g_Player.unk2 = 1;
    g_Player.hp = 24;
    g_Player.boss_flags = 0x40;
    g_Player.x_pos.val = scenes[scene].player_x * 65536 + 0x1234;
    g_Player.y_pos.val = 120 * 65536 + 0x5678;
    g_Player.unk15 = facing ? 0x40 : 0;
    g_Player.unk54 = (const u32*)jet_drone_bullet_hit_box;
    g_Player.stun_timer = 5;
    g_Player.hurt_type = 4;
    g_Player.hit_facing = 0x40;
    player_expected = g_Player;
    obj.active = 0x41;
    obj.id = 13;
    obj.state = 1;
    obj.on_screen = 7;
    obj.bg_offset = 0;
    obj.unk15 = g_Player.unk15;
    obj.unk42 = 0x9234;
    obj.x_pos.val = g_Player.x_pos.val - velocity;
    obj.y_pos = g_Player.y_pos;
    obj.x_vel.val = velocity;
    obj.unk50.data = obj.unk54 = jet_drone_bullet_hit_box;
    obj.unk58.collision_data = D_80106070;
    obj.unk5C = 1;
    obj.unk60 = 3;
    obj.animation_table = (u32**)jet_drone_animations;
    set_animation(&obj, 3);
    assert(obj.animation_step.packed == 0x11010002);
    if (hit) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = 24;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].x_pos = g_Player.x_pos;
        weapon_objects[0].y_pos = g_Player.y_pos;
        weapon_objects[0].unk50 = jet_drone_bullet_hit_box;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.x_pos = g_Player.x_pos;
    expected.animation_step.fields.duration = 1;
    expected.on_screen = 1;
    if (scenes[scene].contact) {
        player_expected.hp = (s8)0x95;
        player_expected.hurt_type = 1;
        player_expected.stun_timer = 0;
        player_expected.hit_facing = 0;
    }
    if (hit) {
        expected.unk5C = 0;
        expected.state = 2;
        ((s16*)&weapons_expected[0].unk80)[0] = scenes[scene].player_x + (facing ? 1 : -1);
        ((s16*)&weapons_expected[0].unk80)[1] = 120;
    } else
        expected.unk42 = 0x1234;
    D_8013E198[1] = -1;
    cur_random = 0x1234;
    jet_drone_bullet_fly(&obj);
    SAME(obj, expected);
    SAME(g_Player, player_expected);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    assert(cur_random == (hit ? 0x366A : 0x1234));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "intro_damage_guard_and_real_weapon_clear", NULL, NULL, COUNT(scenes) * 4, intro_guard } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(scenes) * 4;
