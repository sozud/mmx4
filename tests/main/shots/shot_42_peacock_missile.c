#include "test_runtime.h"
#include "main/shots/shot_42_peacock_missile.h"
#include "main/55C4.h"
s32 peacock_missile_hit_target(struct ShotObj*);

static u32 missile_case(u32 mode)
{
    struct ShotObj obj, before;
    struct WeaponObj target, target_before;
    struct Unk_unk68 box = { 0, 0, 8, 8 };
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&target, 0, sizeof(target));
    obj.active = 0x41;
    obj.id = 42;
    obj.unk5 = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk68 = &box;
    obj.unk7C = &target;
    target.active = 0x41;
    target.id = 0x17;
    target.unk68 = &box;
    target.x_pos.val = (mode == 0 ? 100 : 117) * 65536;
    target.y_pos.val = 200 * 65536;
    before = obj;
    target_before = target;
    actual = peacock_missile_hit_target(&obj);
    assert(actual == (mode == 0 ? 1 : 0));
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(target) / 4; i++)
        assert(((u32*)&target)[i] == ((u32*)&target_before)[i]);
    assert(box.unk0 == 0 && box.unk1 == 0 && box.unk2 == 8 && box.unk3 == 8);
    return actual;
}
static const u32 peacock_missile_collision_cases_expected[] = { 0x1u, 0x0u };

static const u32 peacock_missile_hit_target_expected[] = { 0u, 1u };
static u32 test_peacock_missile_hit_target(u32 row)
{
    u32 observed_values[2];
    struct ShotObj obj;
    struct WeaponObj child_0;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0.active = 1;
    obj.unk7C = &child_0;
    return_value = peacock_missile_hit_target(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, peacock_missile_hit_target_expected, 2);
}

void peacock_missile_explode(struct ShotObj*);
void peacock_missile_explode_start(struct ShotObj*);
extern void* cyber_peacock_animations[38];
static struct MiscObj pool_expected[64];
static u8 roll(u16* seed)
{
    u32 high = (u16)(*seed * 3) >> 8;
    *seed = ((*seed + high) & 255) | high << 8;
    return *seed;
}
static u32 explosion(u32 row)
{
    struct MainObj owner, owner_before;
    struct ShotObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 free = row % 2, face = row / 2 % 2, i, amount;
    u16 seed = row / 4 ? 0x1234 : 119;
    engine_obj.stage = 6;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 64;
    owner.state = 1;
    owner.hp = 48;
    owner.unk15 = face ? 0x40 : 0;
    owner.x_pos.i.hi = 1248;
    owner.y_pos.i.hi = 2424;
    owner.animation_table = (const u8* const*)cyber_peacock_animations;
    owner_before = owner;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = i == 63 && free ? 0 : 1;
    memcpy(pool_expected, misc_objects, sizeof(pool_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 42;
    obj.backref = &owner;
    obj.x_pos.val = owner.x_pos.val;
    obj.y_pos.val = owner.y_pos.val;
    obj.animation_table = (u32**)cyber_peacock_animations;
    func_800A63B0(&obj);
    peacock_missile_explode_start(&obj);
    set_animation_frame(ANIMATED_OBJECT(&obj), 31, 2);
    assert(obj.animation_step.packed == 0x84FE0002);
    obj.timer = 57;
    expected = obj;
    expected.timer = 56;
    expected.animation_step.packed = 0x84FE0001;
    cur_random = seed;
    if (free) {
        struct MiscObj* m = &pool_expected[63];
        m->active = 0x41;
        m->id = 49;
        m->unk2 = 4;
        m->x_pos = obj.x_pos;
        m->y_pos = obj.y_pos;
        amount = roll(&seed) & 16;
        if (roll(&seed) & 1)
            m->x_pos.i.hi += amount;
        else
            m->x_pos.i.hi -= amount;
        amount = roll(&seed) & 16;
        if (roll(&seed) & 1)
            m->y_pos.i.hi += amount;
        else
            m->y_pos.i.hi -= amount;
        m->animation_table = obj.animation_table;
        m->unk40 = obj.unk40;
        m->unk3C = obj.unk3C;
        m->unk42 = obj.unk42 & 0x7FFF;
        m->unk16 = obj.unk16;
        m->ext.misc_49.owner = &obj;
    }
    peacock_missile_explode(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(misc_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(cur_random == seed);
    return 1;
}

extern u8 peacock_missile_explosion_box[4];
void peacock_missile_explode_start(struct ShotObj*);
extern void* cyber_peacock_animations[38];
static u32 owner_death(u32 row)
{
    struct MainObj owner, owner_expected;
    struct ShotObj obj, expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    u32 subtype = row % 8, face = row / 8 % 2, dead = row / 16;
    engine_obj.stage = 6;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 64;
    owner.state = 1;
    owner.hp = 48;
    owner.unk15 = face ? 0x40 : 0;
    owner.x_pos.i.hi = 1248;
    owner.y_pos.i.hi = 2424;
    owner.animation_table = (const u8* const*)cyber_peacock_animations;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 42;
    obj.unk2 = subtype;
    obj.unk15 = 0;
    obj.backref = &owner;
    obj.x_pos.val = owner.x_pos.val;
    obj.y_pos.val = owner.y_pos.val;
    obj.animation_table = (u32**)cyber_peacock_animations;
    func_800A63B0(&obj);
    assert(obj.state == 1 && obj.timer == 10 && obj.unk90.val == 110);
    owner.state = dead ? 2 : 1;
    owner_expected = owner;
    expected = obj;
    expected.unk50.data = dead ? NULL : peacock_missile_explosion_box;
    expected.unk8C.word = 1;
    expected.unk5 = 2;
    expected.timer = 60;
    expected.unk60 = 6;
    expected.unk17 = 31;
    expected.previous_animation_index = 255;
    expected.animation_cursor = cyber_peacock_animations[31];
    expected.animation_step.packed = 0x82010001;
    peacock_missile_explode_start(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "peacock_missile_collision", NULL, peacock_missile_collision_cases_expected, COUNT(peacock_missile_collision_cases_expected), missile_case },
    { "peacock_missile_hit_target", 0, 0, 1, test_peacock_missile_hit_target },
    { "own_Peacock_explosion_fourth_tick_full_misc_pool_preserves_RNG", NULL, NULL, 8, explosion },
    { "own_Peacock_eight_missile_launches_explosion_collision_after_owner_death", NULL, NULL, 32, owner_death },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(peacock_missile_collision_cases_expected) + 1 + 8 + 32;
