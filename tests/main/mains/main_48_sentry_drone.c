#include "test_runtime.h"
extern union AnimationStep* sentry_drone_animations[13];
extern u8 D_800FFAD0[4];
extern u8 D_800FFAD4[];
extern u8 D_800FFACC[];
extern u32 D_801076F8[];

enum { INIT_GROUND,
    INIT_AIR,
    INIT_GUARD,
    INIT_AIR_GUARD,
    RESUME,
    DRIFT_LEFT,
    DRIFT_RIGHT,
    DASH_LEFT,
    DASH_RIGHT,
    DASH_STILL,
    TURN_WAIT,
    TURN_0,
    TURN_2,
    TURN_8,
    TURN_10,
    TURN_16,
    TURN_18,
    TURN_24,
    TURN_26,
    TURN_NONE,
    TURN_NEGATIVE,
    DIRECTIONS };
static const u8 turn_results[] = { 0, 0, 2, 8, 10, 16, 18, 24, 26, 0x40, 0x9F };
static u32 steps[2];
static u32* table[8];
static u32 palette[64];
static s32 frames[64];
static struct MainObj drone, expected, owner;

static void step(u32 index, s8 duration)
{
    union AnimationStep value;
    value.fields.duration = duration;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 5;
    steps[index] = value.packed;
}

static void animation(u32 index, u32* cursor)
{
    expected.animation_cursor = cursor;
    expected.unk17 = index;
    expected.previous_animation_index = 0xFF;
    expected.animation_step.packed = *cursor;
}

static void direction(u32 result, u8* low, u8* high)
{
    switch (result & 0xFE) {
    case 0:
        *low = 0x1E;
        *high = 2;
        break;
    case 2:
    case 4:
    case 6:
        *low = 0;
        *high = 8;
        break;
    case 8:
        *low = 6;
        *high = 0xA;
        break;
    case 10:
    case 12:
    case 14:
        *low = 8;
        *high = 0x10;
        break;
    case 16:
        *low = 0xE;
        *high = 0x12;
        break;
    case 18:
    case 20:
    case 22:
        *low = 0x10;
        *high = 0x18;
        break;
    case 24:
        *low = 0x16;
        *high = 0x1A;
        break;
    default:
        *low = 0x18;
        *high = 0;
        break;
    }
}

static u32 sentry_drone_steps_run(u32 mode)
{
    u32 i, result = 0, difference = 0;
    cur_random = 0x2468;
    engine_obj.stage = 6;
    engine_obj.substage = 0;
    for (i = 0; i < COUNT(palette); i++) {
        palette[i] = 0x12345 + i * 0x1111;
        frames[i] = 0x100 + i * 8;
    }
    D_801406A8 = palette;
    TEST_MENU_FRAMES = (u8*)frames;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.bg_offset = 1;
    for (i = 0; i < COUNT(table); i++)
        table[i] = &steps[1];
    step(0, 3);
    step(1, 7);
    memset(&owner, 0, sizeof(owner));
    memset(&drone, 0, sizeof(drone));
    drone.active = 0x41;
    drone.id = 0x30;
    drone.state = 1;
    drone.unk5 = 3;
    drone.unk6 = 2;
    drone.unk2 = mode == INIT_AIR ? 0x80 : mode == INIT_GUARD ? 1
        : mode == INIT_AIR_GUARD                              ? 0x81
        : mode == DASH_STILL                                  ? 2
                                                              : 0;
    drone.unk15 = mode == DRIFT_RIGHT || mode == DASH_RIGHT || mode == INIT_GROUND ? 0x40 : 0;
    drone.x_speed = 0x1111;
    drone.y_speed = 0x2222;
    drone.x_accel = 0x3333;
    drone.gravity = 0x4444;
    drone.animation_table = table;
    drone.animation_cursor = &steps[0];
    drone.animation_step.packed = steps[0];
    owner.ext.main_48.saved_unk5 = 7;
    owner.ext.main_48.unk80 = mode == TURN_WAIT ? 2 : 1;
    if (mode >= TURN_0 && mode <= TURN_NEGATIVE)
        owner.ext.main_48.collision_result = turn_results[mode - TURN_WAIT];
    SP_CUR_MAIN_OBJ = &owner;
    expected = drone;

    if (mode <= INIT_AIR_GUARD) {
        u32 resource = func_8002938C(0x30);
        func_8006738C(&drone);
        expected.bg_offset = 1;
        expected.x_speed = expected.y_speed = expected.x_accel = expected.gravity = 0;
        expected.unk40 = palette[resource] >> 7;
        expected.sprite_frames = (u8*)frames + frames[resource];
        expected.unk42 = ((resource * 4 + 0x18) % 16) | (((resource + 6) / 4 + 0x1E0) << 6);
        expected.animation_table = (u32**)sentry_drone_animations;
        expected.unk16 = 4;
        expected.terrain_box = (struct Unk_unk68*)D_800FFAD0;
        expected.attack_box = D_800FFAD4;
        expected.hurt_box = D_800FFACC;
        expected.collision_data = D_801076F8;
        expected.invincibility_timer = 0;
        expected.hp = 5;
        expected.contact_damage = 3;
        expected.state = mode == INIT_GUARD || mode == INIT_AIR_GUARD ? 3 : 1;
        expected.unk6 = 0;
        animation(0, (u32*)sentry_drone_animations[0]);
        if (mode == INIT_AIR || mode == INIT_AIR_GUARD) {
            expected.unk5 = 2;
            expected.air_state = 1;
        } else {
            expected.unk15 = 0;
            expected.unk5 = 3;
            expected.air_state = 0;
        }
        assert(owner.ext.main_48.unk81 < 4);
        result = resource | ((u32)owner.ext.main_48.unk81 << 8) | ((u32)(u8)expected.state << 16);
        owner.ext.main_48.unk81 = 0;
    } else if (mode == RESUME) {
        sentry_drone_resume_step(&drone);
        expected.unk5 = 7;
    } else if (mode <= DRIFT_RIGHT) {
        sentry_drone_drift_start(&drone);
        expected.air_state = 1;
        expected.unk6 = 3;
        expected.x_speed = mode == DRIFT_RIGHT ? FIXED(0.5) : -FIXED(0.5);
        expected.x_accel = expected.y_speed = expected.gravity = 0;
        animation(0, table[0]);
        assert(owner.ext.main_48.unk80 == 0x30);
        owner.ext.main_48.unk80 = 1;
    } else if (mode <= DASH_STILL) {
        sentry_drone_dash_start(&drone);
        expected.unk6 = 3;
        expected.air_state = 0;
        expected.x_speed = mode == DASH_STILL ? 0 : mode == DASH_RIGHT ? FIXED(4)
                                                                       : -FIXED(4);
        expected.x_accel = expected.y_speed = expected.gravity = 0;
        animation(0, table[0]);
        assert(owner.ext.main_48.unk80 == 0x3C);
        owner.ext.main_48.unk80 = 1;
    } else if (mode <= TURN_NEGATIVE) {
        u32 r = owner.ext.main_48.collision_result;
        func_80067DAC(&drone);
        if (mode == TURN_WAIT) {
            assert(owner.ext.main_48.unk80 == 1);
        } else {
            assert(owner.ext.main_48.unk80 == 0);
            owner.ext.main_48.unk80 = 1;
            expected.unk6 = 3;
            if (r <= 30) {
                if (r == 0 || (r >= 2 && r <= 6))
                    expected.unk15 = 0x40;
                if (r == 16 || (r >= 10 && r <= 14) || (r >= 18 && r <= 22))
                    expected.unk15 = 0;
                if (r >= 26)
                    expected.unk15 = 0x40;
                animation(r == 8 ? 2 : r == 24 ? 3
                        : r == 0 || r == 16    ? 1
                        : r <= 14              ? 4
                                               : 5,
                    table[0]);
            }
        }
    } else {
        for (i = 0; i < 32; i++) {
            u8 low, high;
            owner.ext.main_48.collision_result = i;
            func_800681C4(&drone);
            direction(i, &low, &high);
            difference |= (owner.ext.main_48.unk86 ^ low) | (owner.ext.main_48.unk87 ^ high) | (owner.ext.main_48.unk88 ^ (i & 0xFE));
            result = result * 33 + owner.ext.main_48.unk86 + (owner.ext.main_48.unk87 << 8);
        }
        assert(difference == 0);
        owner.ext.main_48.collision_result = 0;
        owner.ext.main_48.unk86 = owner.ext.main_48.unk87 = owner.ext.main_48.unk88 = 0;
    }
    for (i = 0; i < sizeof(drone) / 4; i++)
        difference |= ((u32*)&drone)[i] ^ ((u32*)&expected)[i];
    assert(difference == 0);
    assert(owner.ext.main_48.saved_unk5 == 7 && owner.ext.main_48.unk80 == 1);
    if (mode != DIRECTIONS)
        result ^= (u8)drone.unk5 | ((u32)(u8)drone.unk6 << 8) | ((u32)(u8)drone.unk15 << 16) | ((u32)drone.unk17 << 24);
    result ^= (u32)drone.x_speed;
    return result;
}

#define CASE(name)                                    \
    static u32 sentry_drone_steps_##name##_case(void) \
    {                                                 \
        return sentry_drone_steps_run(name);          \
    }
CASE(INIT_GROUND)
CASE(INIT_AIR)
CASE(INIT_GUARD)
CASE(INIT_AIR_GUARD)
CASE(RESUME)
CASE(DRIFT_LEFT)
CASE(DRIFT_RIGHT)
CASE(DASH_LEFT)
CASE(DASH_RIGHT)
CASE(DASH_STILL)
CASE(TURN_WAIT)
CASE(TURN_0)
CASE(TURN_2)
CASE(TURN_8)
CASE(TURN_10)
CASE(TURN_16)
CASE(TURN_18)
CASE(TURN_24)
CASE(TURN_26)
CASE(TURN_NONE)
CASE(TURN_NEGATIVE)
CASE(DIRECTIONS)
#define ENTRY(name) sentry_drone_steps_##name##_case,
static const CTestCase sentry_drone_steps_cases[]
    = {
          ENTRY(INIT_GROUND) ENTRY(INIT_AIR) ENTRY(INIT_GUARD) ENTRY(INIT_AIR_GUARD) ENTRY(RESUME) ENTRY(DRIFT_LEFT) ENTRY(DRIFT_RIGHT)
              ENTRY(DASH_LEFT) ENTRY(DASH_RIGHT) ENTRY(DASH_STILL) ENTRY(TURN_WAIT) ENTRY(TURN_0) ENTRY(TURN_2) ENTRY(TURN_8) ENTRY(TURN_10)
                  ENTRY(TURN_16) ENTRY(TURN_18) ENTRY(TURN_24) ENTRY(TURN_26) ENTRY(TURN_NONE) ENTRY(TURN_NEGATIVE) ENTRY(DIRECTIONS)
      };
static const u32 sentry_drone_steps_cases_expected[] = { 0x10104u, 0x10105u, 0x30104u, 0x30105u, 0x1316u, 0xFFFF8303u, 0x408303u, 0xFFFC0303u, 0x440303u, 0x303u, 0x1312u, 0x1401212u, 0x4401212u, 0x2001212u, 0x4001212u, 0x1001212u, 0x5001212u, 0x3001212u, 0x5401212u, 0x1212u, 0x1212u, 0x18C699A1u };
#undef CASE
#undef ENTRY

static const u32 func_800681C4_expected[] = { 0u, 0u, 0x20u };
static u32 test_func_800681C4(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    child_0.ext.main_48.collision_result = 32;
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    func_800681C4(&obj);
    observed_values[0] = (u32)child_0.ext.main_48.unk86;
    observed_values[1] = (u32)child_0.ext.main_48.unk87;
    observed_values[2] = (u32)child_0.ext.main_48.unk88;
    return c_test_observe(0, row, observed_values, func_800681C4_expected, 3);
}

static const u32 func_80068340_expected[] = { 0u };
static u32 test_func_80068340(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    func_80068340(&obj);
    observed_values[0] = (u32)child_0.ext.main_48.collision_result;
    return c_test_observe(0, row, observed_values, func_80068340_expected, 1);
}

static const u32 sentry_drone_burst_fire_expected[] = { 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u };
static u32 test_sentry_drone_burst_fire(u32 row)
{
    u32 observed_values[14];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    u8 pool_1_full;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_1_full = 255;
    child_0_present = 0;
    pool_0_full = 255;
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_1_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    sentry_drone_burst_fire(&obj);
    observed_values[0] = (u32)child_0.ext.main_48.unk80;
    observed_values[1] = (u32)child_0.ext.main_48.unk82;
    observed_values[2] = (u32)misc_objects[0].active;
    observed_values[3] = (u32)misc_objects[0].id;
    observed_values[4] = (u32)misc_objects[0].unk2;
    observed_values[5] = (u32)misc_objects[0].x_pos.val;
    observed_values[6] = (u32)misc_objects[0].y_pos.val;
    observed_values[7] = (u32)obj.unk6;
    observed_values[8] = (u32)shot_objects[0].active;
    observed_values[9] = (u32)shot_objects[0].id;
    observed_values[10] = (u32)shot_objects[0].unk2;
    observed_values[11] = (u32)shot_objects[0].unk84.value;
    observed_values[12] = (u32)shot_objects[0].x_pos.val;
    observed_values[13] = (u32)shot_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, sentry_drone_burst_fire_expected, 14);
}

static const u32 inputs_0[2][9] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { -1, 255, 0, 0, 0, 0, 0, 0, 255 },
};
struct sentry_drone_spread_fire_case {
    u32 expected[14];
};
static const struct sentry_drone_spread_fire_case sentry_drone_spread_fire_cases[] = {
    { { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_sentry_drone_spread_fire(u32 row)
{
    const struct sentry_drone_spread_fire_case* c = &sentry_drone_spread_fire_cases[row];
    u32 observed_values[14];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    u8 pool_1_full;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&shot_objects, 0, sizeof(shot_objects));
    obj.animation_step.fields.event = inputs_0[row][0];
    pool_1_full = inputs_0[row][1];
    obj.x_pos.val = inputs_0[row][2];
    obj.y_pos.val = inputs_0[row][3];
    child_0_present = inputs_0[row][4];
    child_0.ext.main_48.collision_result = inputs_0[row][5];
    obj.unk6 = inputs_0[row][6];
    child_0.ext.main_48.unk82 = inputs_0[row][7];
    pool_0_full = inputs_0[row][8];
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_1_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    sentry_drone_spread_fire(&obj);
    observed_values[0] = (u32)child_0.ext.main_48.unk80;
    observed_values[1] = (u32)child_0.ext.main_48.unk82;
    observed_values[2] = (u32)misc_objects[0].active;
    observed_values[3] = (u32)misc_objects[0].id;
    observed_values[4] = (u32)misc_objects[0].unk2;
    observed_values[5] = (u32)misc_objects[0].x_pos.val;
    observed_values[6] = (u32)misc_objects[0].y_pos.val;
    observed_values[7] = (u32)obj.unk6;
    observed_values[8] = (u32)shot_objects[0].active;
    observed_values[9] = (u32)shot_objects[0].id;
    observed_values[10] = (u32)shot_objects[0].unk2;
    observed_values[11] = (u32)shot_objects[0].unk84.value;
    observed_values[12] = (u32)shot_objects[0].x_pos.val;
    observed_values[13] = (u32)shot_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 14);
}

const struct CTestGroup c_test_groups[] = {
    { "sentry_drone_steps", sentry_drone_steps_cases, sentry_drone_steps_cases_expected, COUNT(sentry_drone_steps_cases), 0 },
    { "func_800681C4", 0, 0, 1, test_func_800681C4 },
    { "func_80068340", 0, 0, 1, test_func_80068340 },
    { "sentry_drone_burst_fire", 0, 0, 1, test_sentry_drone_burst_fire },
    { "sentry_drone_spread_fire", 0, 0, 2, test_sentry_drone_spread_fire },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sentry_drone_steps_cases) + 1 + 1 + 1 + 2;
