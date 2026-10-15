#include "test_runtime.h"
extern union AnimationStep* ice_block_animations[9];
extern void* sigma_final_animations[39];
extern s8* sigma_spit_boxes[8];

#include "func_tables.h"

struct sigma_spit_hit_case {
    u32 obj_unk6, obj_unk61, unk5, expected_unk6, expected_unk61, unk42;
    u32 expected[3];
};
static const struct sigma_spit_hit_case sigma_spit_hit_cases[] = {
    { 0, 0, 0, 1, 39, 37428, { 0u, 0x27u, 0x9234u } },
    { 1, 1, 1, 0, 0, 4660, { 1u, 0u, 0x1234u } },
};
static u32 test_sigma_spit_hit(u32 row)
{
    const struct sigma_spit_hit_case* c = &sigma_spit_hit_cases[row];
    u32 observed_values[3];
    struct ShotObj obj, expected;
    struct MainObj owner, owner_expected;
    struct PlayerObj player_expected;
    void (*reaction)(struct ShotObj*);
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 74;
    owner.animation_table = (const u8* const*)sigma_final_animations;
    owner.x_pos.val = 0x1AA00000;
    owner.y_pos.val = 0x00800000;
    owner_expected = owner;
    obj.active = 0x41;
    obj.id = 56;
    obj.unk2 = 0;
    obj.state = 1;
    obj.unk5 = 0;
    obj.unk6 = c->obj_unk6;
    obj.unk63 = 1;
    obj.unk61 = c->obj_unk61;
    obj.unk42 = 0x9234;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.x_pos.val = 0x1AA81234;
    obj.y_pos.val = 0x00845678;
    obj.unk16 = 0x20;
    obj.unk5C = 3;
    obj.unk60 = 6;
    obj.animation_table = (u32**)owner.animation_table;
    obj.unk58.animation_steps = D_80105FF0;
    obj.unk54 = (const u8*)sigma_spit_boxes[0];
    obj.unk50.data = (const u8*)sigma_spit_boxes[1];
    set_animation_frame(ANIMATED_OBJECT(&obj), 0x15, 0);
    player_expected = g_Player;

    expected = obj;
    expected.unk5 = c->unk5;
    expected.unk6 = c->expected_unk6;
    expected.unk61 = c->expected_unk61;
    expected.unk42 = c->unk42;
    reaction = sigma_spit_hit;
    reaction(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk61;
    observed_values[2] = (u32)obj.unk42;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_spit_hit", 0, 0, 2, test_sigma_spit_hit },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2;
