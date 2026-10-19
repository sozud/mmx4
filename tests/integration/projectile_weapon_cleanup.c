#include "test_runtime.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"
void dash_gunner_shot_fly(struct ShotObj*);
void jump_shooter_shot_fly(struct ShotObj*);
void trident_shot_fly(struct ShotObj*);
extern union AnimationStep *trident_mech_animations[], *dash_gunner_animations[], *jump_shooter_animations[];
extern u8 trident_shot_hit_box[], dash_gunner_shot_hit_box[], jump_shooter_shot_hit_box[];
static const struct {
    void (*run)(struct ShotObj*);
    union AnimationStep** animations;
    u8* box;
    u8 id, animation, state, dead_state;
    u32 next;
} kinds[] = {
    { trident_shot_fly, trident_mech_animations, trident_shot_hit_box, 9, 8, 4, 5, 0x17FF0101 },
    { dash_gunner_shot_fly, dash_gunner_animations, dash_gunner_shot_hit_box, 14, 5, 1, 2, 0x1F010002 },
    { jump_shooter_shot_fly, jump_shooter_animations, jump_shooter_shot_hit_box, 27, 12, 1, 2, 0x20010001 },
};
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 cleanup(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 type = row % 3, hit = row / 3 % 2, contact = row / 6 % 2, facing = row / 12 % 2, scene = row / 24, i;
    s32 x = scene == 0 ? 160 : scene == 1 ? 0x7B7
        : scene == 2                      ? 0x9B6
                                          : 0x9B7,
        velocity = facing ? 0x20000 : -0x20000;
    u32 damage = hit && !(type == 2 && contact), guard = type == 1 && scene == 3;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&obj, 0, sizeof(obj));
    g_Player.active = 0x41;
    g_Player.unk2 = 1;
    g_Player.hp = 24;
    g_Player.boss_flags = 0x40;
    g_Player.x_pos.val = (contact ? x : x + 128) * 65536 + 0x1234;
    g_Player.y_pos.val = 120 * 65536 + 0x5678;
    g_Player.unk54 = (const u32*)kinds[type].box;
    g_Player.unk15 = facing ? 0x40 : 0;
    player_expected = g_Player;
    engine_obj.stage = scene ? 3 : 4;
    engine_obj.cur_character = 1;
    engine_obj.character_state.bytes[0] = scene == 2;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.val = (x - 160) * 65536;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    obj.active = 0x41;
    obj.id = kinds[type].id;
    obj.state = kinds[type].state;
    obj.unk2 = type == 1 ? 4 : 0;
    obj.on_screen = 7;
    obj.unk15 = g_Player.unk15;
    obj.unk42 = 0x1234;
    obj.x_pos.val = x * 65536 + 0x1234 - velocity;
    obj.y_pos.val = g_Player.y_pos.val;
    obj.x_vel.val = velocity;
    obj.unk50.data = obj.unk54 = kinds[type].box;
    obj.unk58.collision_data = D_80106070;
    obj.unk5C = 1;
    obj.unk60 = 3;
    obj.animation_table = (u32**)kinds[type].animations;
    set_animation(&obj, kinds[type].animation);
    if (hit) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = 24;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].x_pos.val = x * 65536 + 0x1234;
        weapon_objects[0].y_pos = obj.y_pos;
        weapon_objects[0].unk50 = kinds[type].box;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.x_pos.val += velocity;
    expected.on_screen = 1;
    expected.animation_step.packed = kinds[type].next;
    if (type != 1)
        expected.animation_cursor = (u32*)kinds[type].animations[kinds[type].animation] + 1;
    if (contact && !guard) {
        player_expected.hp = (s8)0x95;
        player_expected.hurt_type = 1;
    }
    if (damage) {
        expected.unk5C = 0;
        expected.unk42 |= 0x8000;
        expected.state = kinds[type].dead_state;
        ((s16*)&weapons_expected[0].unk80)[0] = x + (type == 0 ? facing ? -1 : 1 : facing ? 1
                                                                                          : -1);
        ((s16*)&weapons_expected[0].unk80)[1] = type == 1 ? 120 : 119;
    }
    if (type == 0 && (contact || scene == 2))
        expected.state = 5;
    if (type == 2 && contact) {
        expected.state = 2;
        expected.on_screen = 7;
    }
    D_8013E198[1] = -1;
    cur_random = 0x1234;
    kinds[type].run(&obj);
    SAME(obj, expected);
    SAME(g_Player, player_expected);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    assert(cur_random == (damage ? 0x366A : 0x1234));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "real_weapon_clear_contact_priority_and_stage_guards", NULL, NULL, 96, cleanup } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 96;
