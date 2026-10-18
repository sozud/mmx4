#include "test_runtime.h"
#include "main/55C4.h"
extern void* sigma_animations[];
void func_800B4E34(struct VisualObj*);
static const u8 cloak_animations[] = { 13, 12, 13, 11 };
static const u32 cloak_words[] = { 0x36010001, 0x32010002, 0x36010001, 0x2E010002 };
static const u16 seeds[] = { 0x1234, 0x7FFF }, final_seeds[] = { 0xBDB3, 0x75ED };
static const s32 y_offsets[] = { 22, -8 }, y_velocities[] = { -0xC000, -0x10000 }, x_velocities[] = { 0x28000, -0x43000 };
static u32 facing(u32 row)
{
    struct VisualObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 type = row < 16 ? 1 : row < 18 ? 3
                                       : 4,
        face = row % 2, piece = row / 2 % 4, seed = row / 8 % 2;
    u32 animation = type == 1 ? cloak_animations[piece] : type == 3 ? 34
                                                                    : 36;
    u32 word = type == 1 ? cloak_words[piece] : type == 3 ? 0x6C010002
                                                          : 0x77010002;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 68;
    owner.state = 1;
    owner.unk15 = face ? 0x40 : 0;
    owner.unk16 = 3;
    owner.unk40 = 9;
    owner.unk42 = 0x8123;
    owner.x_pos.val = 160 * 65536 + 0x1234;
    owner.y_pos.val = 120 * 65536 + 0x5678;
    owner.animation_table = (const u8* const*)sigma_animations;
    obj.active = 0x41;
    obj.id = 32;
    obj.unk2 = type;
    obj.unk50 = PLAYER_OBJECT(&owner);
    obj.unk54 = piece;
    obj.unk56 = 7;
    expected = obj;
    owner_before = owner;
    cur_random = seeds[seed];
    expected.state = 1;
    expected.unk40 = 9;
    expected.unk42 = 0x8123;
    expected.unk15 = owner.unk15;
    expected.unk16 = 3;
    expected.animation_table = (u32**)owner.animation_table;
    expected.x_pos.val = owner.x_pos.val;
    expected.y_pos.val = owner.y_pos.val;
    if (type == 1) {
        expected.x_pos.i.hi += face ? -22 : 22;
        expected.y_pos.i.hi += y_offsets[seed];
        expected.x_vel.val = x_velocities[seed];
        expected.y_vel.val = y_velocities[seed];
        expected.unk54 = 20;
    } else if (type == 3) {
        expected.x_pos.val += face ? 0x90000 : -0x90000;
        expected.y_pos.val -= 0x160000;
    } else {
        expected.x_pos.val += face ? -0x160000 : 0x160000;
        expected.y_pos.val += 0x40000;
    }
    assert(((const union AnimationStep*)sigma_animations[animation])->packed == word);
    expected.unk17 = animation;
    expected.previous_animation_index = 255;
    expected.animation_cursor = sigma_animations[animation];
    expected.animation_step.packed = word;
    func_800B4E34(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(cur_random == (type == 1 ? final_seeds[seed] : seeds[seed]));
    return 1;
}

void sigma_fx_electric(struct VisualObj*);
extern void* sigma_animations[44];
static struct ShotObj pool_expected[32];
static u32 electric(u32 row)
{
    struct VisualObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 free_slot = row % 2, dead = row / 2 % 2, face = row / 4, i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++) {
        shot_objects[i].active = i == 31 && free_slot ? 0 : 1;
        shot_objects[i].id = 63;
        shot_objects[i].state = 5;
        shot_objects[i].unk2 = 9;
    }
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    owner.active = 0x41;
    owner.id = 68;
    owner.state = dead ? 2 : 1;
    owner_before = owner;
    obj.active = 1;
    obj.id = 32;
    obj.state = 1;
    obj.unk2 = 4;
    obj.unk50 = PLAYER_OBJECT(&owner);
    obj.unk15 = face ? 0x40 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (u32**)sigma_animations;
    set_animation_frame(ANIMATED_OBJECT(&obj), 36, 6);
    assert(obj.animation_step.packed == 0x7D000002);
    expected = obj;
    expected.animation_step.fields.duration = 1;
    expected.unk5 = 1;
    expected.unk56 = 5;
    expected.on_screen = 1;
    if (dead)
        expected.state = 2;
    if (free_slot) {
        struct ShotObj* s = &pool_expected[31];
        s->active = 0x41;
        s->id = 46;
        s->unk2 = 5;
        s->unk7C = WEAPON_OBJECT(&obj);
        s->timer = 0;
    }
    sigma_fx_electric(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((u32*)shot_objects, (u32*)pool_expected, sizeof(pool_expected) / 4) == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_cloak_and_electric_effects_inherit_facing", NULL, NULL, 20, facing },
    { "real_electric_terminal_animation_full_pool_last_slot_and_owner_defeat", NULL, NULL, 8, electric },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 20 + 8;
