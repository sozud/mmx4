#include "test_runtime.h"
extern u8 D_800FD5C8[32];
extern struct Unk_unk68* D_800FD5B0[2];
extern struct Unk_unk68* D_800FD5B8[2];
extern struct Unk_unk68* D_800FD5C0[2];
extern struct FixedPointPosition D_800FD618[4];
extern struct FixedPointPosition D_800FD638[4];

static void expect_animation(struct MainObj* obj, u32 index)
{
    obj->unk17 = index;
    obj->previous_animation_index = 0xFF;
    obj->animation_cursor = (const u8*)spawner_pod_animations[index];
    obj->animation_step = spawner_pod_animations[index][0];
}
static u32 pod_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj pool_expected[32];
    struct PlayerObj player_before = g_Player;
    s32 frames[4] = { 16, 16, 16, 16 };
    u32 i;
    s32 kind = mode < 16 ? mode / 4 : mode == 19 || mode == 24 ? 2
        : mode == 28                                           ? 1
        : mode == 31                                           ? -1
        : mode == 32                                           ? 4
                                                               : 0;
    u32 facing = mode < 16 ? (mode / 2) & 1 : mode == 27;
    s32 speed = kind & 1 ? (facing ? 0x500000 : 0x10000) : (facing ? -0x10000 : -0x500000);
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = mode == 22 && i == 31 ? 0 : 1;
        shot_objects[i].id = 39;
        shot_objects[i].state = 40;
        shot_objects[i].unk2 = 9;
        shot_objects[i].unk5 = 3;
        shot_objects[i].unk6 = 4;
        shot_objects[i].unk7 = 5;
        shot_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        shot_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    obj.active = 0x41;
    obj.id = 28;
    obj.state = 1;
    obj.unk2 = kind;
    obj.unk5 = 2;
    obj.unk6 = mode == 29 ? 5 : mode == 30 ? 3
        : mode >= 27                       ? 0
        : mode < 17                        ? 0
        : mode < 20                        ? 1
        : mode < 23                        ? 2
        : mode < 25                        ? 3
                                           : 4;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk16 = 5;
    obj.unk40 = 7;
    obj.unk42 = 0x8123;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 32768;
    obj.y_speed = 16384;
    obj.x_accel = 128;
    obj.gravity = 256;
    obj.unk7E = mode == 16 ? 1 : 3;
    obj.unk7C = mode == 23 || mode == 25 ? 1 : 0;
    obj.ext.main_28.unk84 = 0;
    obj.ext.main_28.unk85 = mode == 18 ? 4 : 3;
    obj.sprite_frames = (const u8*)frames;
    obj.animation_table = (const u8* const*)spawner_pod_animations;
    set_animation(&obj, 1);
    if (mode < 16) {
        if (!(mode & 1))
            speed += kind & 1 ? (facing ? -1 : 1) : (facing ? -1 : 1);
        if (kind < 2)
            obj.x_speed = speed;
        else
            obj.y_speed = speed;
    }
    if (mode == 27)
        obj.x_speed = -0x500000;
    if (mode == 28)
        obj.x_speed = 0x500000;
    if (mode == 21 || mode == 22) {
        obj.unk17 = 3;
        obj.animation_cursor = (const u8*)&spawner_pod_animations[3][15];
        obj.animation_step = spawner_pod_animations[3][15];
        assert(obj.animation_step.packed == 0x09000002);
    }
    expected = obj;
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    cur_random = 119;
    expected.unk7E--;
    if (mode < 17 || mode == 27 || mode == 28 || mode >= 31) {
        if (mode == 16 || (mode < 16 && (mode & 1))) {
            expected.ext.main_28.unk85++;
            expected.unk6 = 1;
            expected.unk7C = 60;
        } else {
            expected.x_speed += expected.x_accel;
            expected.y_speed += expected.gravity;
            expected.animation_step.fields.duration--;
        }
    } else if (mode < 20) {
        if (mode == 18) {
            expected.ext.main_28.unk85 = 0;
            expected.unk6 = 2;
            expect_animation(&expected, 2);
        } else {
            expected.unk15 ^= 0x40;
            if (kind >= 2) {
                expected.ext.main_28.unk84 = 8;
                expect_animation(&expected, 9);
            }
            expected.unk7C = 32;
            expected.unk6 = 4;
            expected.x_accel = -128;
            expected.gravity = -256;
            expected.unk7E = 0;
        }
    } else if (mode < 23) {
        expected.animation_step.fields.duration--;
        if (mode != 20) {
            expected.unk7C = 16;
            expected.unk6 = 3;
        }
        if (mode == 22) {
            struct ShotObj* child = &pool_expected[31];
            child->active = 0x41;
            child->id = 18;
            child->x_pos.val = obj.x_pos.val + obj.x_speed;
            child->y_pos.val = obj.y_pos.val + obj.y_speed;
            child->animation_table = (u32**)spawner_pod_animations;
            child->unk40 = 7;
            child->unk3C = frames;
            child->unk42 = 0x123;
            child->unk7C = WEAPON_OBJECT(&obj);
            child->unk16 = 5;
            child->unk15 = obj.unk15;
        }
    } else if (mode == 23 || mode == 25)
        expected.unk7C = 0;
    else if (mode != 29) {
        expected.unk7C = 0;
        expected.unk6 = 0;
        expected.unk7E = 50;
        if (mode == 24 || mode == 30) {
            expected.unk15 ^= 0x40;
            expected.ext.main_28.unk84 = mode == 24 ? 8 : 0;
            expected.x_accel = -128;
            expected.gravity = -256;
            expect_animation(&expected, mode == 24 ? 9 : 1);
        }
    }
    expected.x_pos.val += expected.x_speed;
    expected.y_pos.val += expected.y_speed;
    func_80059F60(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 4; i++)
        assert(frames[i] == 16);
    for (i = 0; i < 32; i++)
        assert(D_800FD5C8[i] == 10 * (i % 5 + 1));
    assert(cur_random == (mode == 24 || mode == 26 || mode == 30 ? 376 : 119));
    i = (u8)obj.unk6 | ((u32)(u8)obj.unk7E << 8) | ((u32)(u8)obj.unk15 << 16) | ((u32)(u8)obj.ext.main_28.unk85 << 24);
    return i;
}
#define CASE(m)                                               \
    static u32 spawner_pod_turn_and_shot_states_pod_##m(void) \
    {                                                         \
        return pod_case(m);                                   \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
CASE(10)
CASE(11)
CASE(12)
CASE(13)
CASE(14)
CASE(15)
CASE(16)
CASE(17)
CASE(18)
CASE(19)
CASE(20)
CASE(21)
CASE(22)
CASE(23)
CASE(24)
CASE(25)
CASE(26)
CASE(27)
CASE(28)
CASE(29)
CASE(30)
CASE(31)
CASE(32)
#define ENTRY(m) spawner_pod_turn_and_shot_states_pod_##m,
static const CTestCase spawner_pod_turn_and_shot_states_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) ENTRY(10) ENTRY(11) ENTRY(12) ENTRY(13) ENTRY(14) ENTRY(15) ENTRY(16) ENTRY(17) ENTRY(18) ENTRY(19) ENTRY(20) ENTRY(21) ENTRY(22) ENTRY(23) ENTRY(24) ENTRY(25) ENTRY(26) ENTRY(27) ENTRY(28) ENTRY(29) ENTRY(30) ENTRY(31) ENTRY(32) };
static const u32 spawner_pod_turn_and_shot_states_cases_expected[] = { 0x3000200u, 0x4000201u, 0x3400200u, 0x4400201u, 0x3000200u, 0x4000201u, 0x3400200u, 0x4400201u, 0x3000200u, 0x4000201u, 0x3400200u, 0x4400201u, 0x3000200u, 0x4000201u, 0x3400200u, 0x4400201u, 0x4000001u, 0x3400004u, 0x202u, 0x3400004u, 0x3000202u, 0x3000203u, 0x3000203u, 0x3000203u, 0x3403200u, 0x3000204u, 0x3003200u, 0x3400200u, 0x3000200u, 0x3000205u, 0x3403200u, 0x3000200u, 0x3000200u };
#undef CASE
#undef ENTRY

struct func_80059E40_case {
    u32 unk2;
    u32 expected[11];
};
static const struct func_80059E40_case func_80059E40_cases[] = {
    { 0, { 3u, 0xFFFF0000u, 0u, 0u, 0x28u, 0u, 6u, 0x10010002u, 8u, 0u, 0u } },
    { 1, { 3u, 0x10000u, 0u, 0u, 0x28u, 0u, 6u, 0x10010002u, 8u, 0u, 0u } },
    { 2, { 3u, 0u, 0xFFFF0000u, 0u, 0x28u, 0u, 2u, 0x4010002u, 8u, 0u, 0u } },
    { 3, { 3u, 0u, 0x10000u, 0u, 0x28u, 0u, 0xAu, 0x23010002u, 8u, 0u, 0u } },
};
static u32 test_func_80059E40(u32 row)
{
    const struct func_80059E40_case* c = &func_80059E40_cases[row];
    u32 observed_values[11];
    struct MainObj obj, context, context_before, before;
    struct FixedPointPosition fast_before[4], slow_before[4];
    memset(&obj, 0, sizeof(obj));
    memset(&context, 0, sizeof(context));
    obj.active = 0x41;
    obj.id = 28;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    obj.unk2 = c->unk2;
    spawner_pod_init(&obj);
    obj.ext.main_28.context = &context;
    context.unk7C = 85;
    context_before = context;
    context_before.unk7C = 0;
    set_animation_frame(&obj, obj.ext.main_28.unk84, 4);
    cur_random = 8;
    memcpy(fast_before, D_800FD618, sizeof(fast_before));
    memcpy(slow_before, D_800FD638, sizeof(slow_before));
    func_80059E40(&obj);
    assert(obj.terrain_box == D_800FD5B0[0]);
    assert(obj.hurt_box == D_800FD5B8[0]);
    assert(obj.attack_box == D_800FD5C0[0]);
    c_test_same_words(&context, &context_before, sizeof(context));
    c_test_same_words(D_800FD618, fast_before, sizeof(fast_before));
    c_test_same_words(D_800FD638, slow_before, sizeof(slow_before));
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.x_accel;
    observed_values[2] = (u32)obj.gravity;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.unk7E;
    observed_values[5] = (u32)context.unk7C;
    observed_values[6] = (u32)(u8)obj.unk17;
    observed_values[7] = obj.animation_step.packed;
    observed_values[8] = (u32)cur_random;
    observed_values[9] = (u32)obj.x_speed;
    observed_values[10] = (u32)obj.y_speed;
    before = obj;
    spawner_pod_idle(&obj);
    spawner_pod_step_4(&obj);
    c_test_same_words(&obj, &before, sizeof(obj));
    spawner_pod_remove(&obj);
    before.active = 0;
    before.id = 0;
    before.unk2 = 0;
    before.on_screen = 0;
    before.state = 0;
    before.unk5 = 0;
    before.unk6 = 0;
    before.unk7 = 0;
    c_test_same_words(&obj, &before, sizeof(obj));
    return c_test_observe(0, row, observed_values, c->expected, 11);
}

struct spawner_pod_detach_case {
    u32 active;
    u32 expected[1];
};
static const struct spawner_pod_detach_case spawner_pod_detach_cases[] = {
    { 0, { 0u } },
    { 1, { 0u } },
};
static u32 test_spawner_pod_detach(u32 row)
{
    const struct spawner_pod_detach_case* c = &spawner_pod_detach_cases[row];
    u32 observed_values[1];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    child_0.active = c->active;
    obj.ext.main_28.context = child_0_present ? &child_0 : NULL;
    spawner_pod_detach(&obj);
    observed_values[0] = (u32)child_0.ext.main_29.unk94;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "spawner_pod_turn_and_shot_states", spawner_pod_turn_and_shot_states_cases, spawner_pod_turn_and_shot_states_cases_expected, COUNT(spawner_pod_turn_and_shot_states_cases), 0 },
    { "func_80059E40", 0, 0, 4, test_func_80059E40 },
    { "spawner_pod_detach", 0, 0, 2, test_spawner_pod_detach },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(spawner_pod_turn_and_shot_states_cases) + 4 + 2;
