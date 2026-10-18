#include "test_runtime.h"
#include "main/mains/main_49_train_soldier.h"
#include "main/55C4.h"
extern union AnimationStep* highway_trooper_animations[27];
extern u8 D_800FFB5C[4];
extern u32 D_801076F8[];
extern u8 train_soldier_guard_hurt_box[];
extern u8 train_soldier_guard_attack_box[];

static u32 aim_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i, animation;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 49;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.main_49.unk82 = mode < 4 ? 0x80 | mode : 0;
    obj.animation_table = (const u8* const*)highway_trooper_animations;
    set_animation(&obj, 11);
    if (mode < 5) {
        obj.animation_cursor = (const u8*)(highway_trooper_animations[11] + 1);
        obj.animation_step = highway_trooper_animations[11][1];
        assert(obj.animation_step.packed == 0x1F000006);
    }
    expected = obj;
    if (mode < 5) {
        expected.unk6 = 3;
        if (mode == 3)
            expected.animation_step.fields.duration = 5;
        else {
            animation = mode == 0 ? 13 : mode == 1 ? 12
                : mode == 2                        ? 14
                                                   : 26;
            expected.unk17 = animation;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = (const u8*)highway_trooper_animations[animation];
            expected.animation_step = highway_trooper_animations[animation][0];
        }
    } else
        expected.animation_step.fields.duration = 9;
    SP_CUR_MAIN_OBJ = &obj;
    train_soldier_shoot_aim(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(SP_CUR_MAIN_OBJ == &obj);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)obj.animation_step.fields.duration << 16);
}
#define CASE(m)                                      \
    static u32 train_soldier_aim_flags_aim_##m(void) \
    {                                                \
        return aim_case(m);                          \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) train_soldier_aim_flags_aim_##m,
static const CTestCase train_soldier_aim_flags_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 train_soldier_aim_flags_cases_expected[] = { 0x140D03u, 0x140C03u, 0x140E03u, 0x50B03u, 0x81A03u, 0x90B02u };
#undef CASE
#undef ENTRY

static struct JumpInput {
    s8 air;
    u8 floor, pit, wall, facing, patrol, guard, fast;
};
enum { AIRBORNE,
    FALL,
    GUARD,
    GROUND_AHEAD,
    TURN,
    WALL,
    JUMP_FAST_LEFT,
    JUMP_SLOW_RIGHT };
static const struct JumpInput inputs[] = {
    { 1, 1, 5, 0, 0, 1, 0, 0 },
    { 0, 0, 5, 0, 0, 1, 0, 0 },
    { 0, 1, 5, 0, 0, 1, 2, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 5, 0, 0, 0, 0, 0 },
    { 0, 1, 5, 1, 0, 1, 0, 1 },
    { 0, 1, 5, 0, 0, 1, 0, 1 },
    { 0, 1, 7, 0, 0x40, 1, 0, 0 },
};
static u8 tilemap[256];
static u16 tiles[2][16][16];
static u32 attributes[2] = { 0, 0x39 };
static u32 train_soldier_check_jump_steps[2];
static u32* train_soldier_check_jump_table[0x20];
static struct MainObj train_soldier_check_jump_soldier, train_soldier_check_jump_expected, train_soldier_check_jump_owner;

static void terrain(const struct JumpInput* input)
{
    u32 row, column;
    memset(tilemap, 0, sizeof(tilemap));
    memset(tiles, 0, sizeof(tiles));
    tilemap[0] = 1;
    for (row = 8; row < 16 && input->floor; row++)
        for (column = 0; column < 16; column++)
            tiles[1][row][column] = column != input->pit || input->pit == 0;
    for (row = 5; row < 8 && input->wall; row++)
        tiles[1][row][input->pit] = 1;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
}

static u32 check(u32 mode, u32 observation)
{
    const struct JumpInput* input = &inputs[mode];
    union AnimationStep value;
    u32 i;
    terrain(input);
    memset(&train_soldier_check_jump_soldier, 0, sizeof(train_soldier_check_jump_soldier));
    memset(&train_soldier_check_jump_owner, 0, sizeof(train_soldier_check_jump_owner));
    value.fields.duration = 4;
    value.fields.event = 0;
    value.fields.relative_step = 0;
    value.fields.frame_index = 9;
    train_soldier_check_jump_steps[0] = train_soldier_check_jump_steps[1] = value.packed;
    for (i = 0; i < COUNT(train_soldier_check_jump_table); i++)
        train_soldier_check_jump_table[i] = &train_soldier_check_jump_steps[1];
    train_soldier_check_jump_soldier.active = 0x41;
    train_soldier_check_jump_soldier.id = 0x31;
    train_soldier_check_jump_soldier.state = 1;
    train_soldier_check_jump_soldier.unk2 = input->patrol;
    train_soldier_check_jump_soldier.unk5 = 2;
    train_soldier_check_jump_soldier.unk6 = 1;
    train_soldier_check_jump_soldier.unk15 = input->facing;
    train_soldier_check_jump_soldier.air_state = input->air;
    train_soldier_check_jump_soldier.x_pos.val = 104 << 16;
    train_soldier_check_jump_soldier.y_pos.val = 107 << 16;
    train_soldier_check_jump_soldier.unk18.val = train_soldier_check_jump_soldier.x_pos.val;
    train_soldier_check_jump_soldier.unk1C.val = train_soldier_check_jump_soldier.y_pos.val;
    train_soldier_check_jump_soldier.x_speed = 0x8000;
    train_soldier_check_jump_soldier.terrain_box = (struct Unk_unk68*)D_800FFB5C;
    train_soldier_check_jump_soldier.animation_table = train_soldier_check_jump_table;
    train_soldier_check_jump_soldier.animation_cursor = &train_soldier_check_jump_steps[0];
    train_soldier_check_jump_soldier.animation_step.packed = train_soldier_check_jump_steps[0];
    train_soldier_check_jump_owner.ext.main_49.unk85 = input->guard;
    train_soldier_check_jump_owner.ext.main_49.unk86 = input->fast;
    SP_CUR_MAIN_OBJ = &train_soldier_check_jump_owner;
    train_soldier_check_jump_expected = train_soldier_check_jump_soldier;
    func_80068D6C(&train_soldier_check_jump_soldier);

    if (!input->air) {
        train_soldier_check_jump_expected.x_pos = train_soldier_check_jump_soldier.x_pos;
        train_soldier_check_jump_expected.y_pos = train_soldier_check_jump_soldier.y_pos;
        train_soldier_check_jump_expected.collision_flags = train_soldier_check_jump_soldier.collision_flags;
        train_soldier_check_jump_expected.unk6C = train_soldier_check_jump_soldier.unk6C;
        train_soldier_check_jump_expected.unk6E = train_soldier_check_jump_soldier.unk6E;
        ((u8*)&train_soldier_check_jump_expected)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = ((u8*)&train_soldier_check_jump_soldier)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)];
        ((u8*)&train_soldier_check_jump_expected)[MMX4_OFFSET_OF(struct PlayerObj, wall_climbable)] = ((u8*)&train_soldier_check_jump_soldier)[MMX4_OFFSET_OF(struct PlayerObj, wall_climbable)];
    }
    if (mode == FALL || mode == JUMP_FAST_LEFT || mode == JUMP_SLOW_RIGHT) {
        train_soldier_check_jump_expected.animation_cursor = &train_soldier_check_jump_steps[1];
        train_soldier_check_jump_expected.animation_step.packed = train_soldier_check_jump_steps[1];
        train_soldier_check_jump_expected.unk17 = mode == FALL ? 0xF : 0x19;
        train_soldier_check_jump_expected.previous_animation_index = 0xFF;
        train_soldier_check_jump_expected.unk6 = 0;
    }
    if (mode == FALL) {
        train_soldier_check_jump_expected.unk5 = 3;
        train_soldier_check_jump_expected.gravity = FIXED(0.2578125);
        train_soldier_check_jump_expected.y_speed = 0;
        train_soldier_check_jump_expected.x_accel = 0;
        train_soldier_check_jump_expected.air_state = -1;
        assert(train_soldier_check_jump_owner.ext.main_49.unk80 == 5);
    } else if (mode == TURN) {
        train_soldier_check_jump_expected.unk15 = 0x40;
        train_soldier_check_jump_expected.x_speed = -0x8000;
    } else if (mode == JUMP_FAST_LEFT) {
        train_soldier_check_jump_expected.unk5 = 4;
        train_soldier_check_jump_expected.y_speed = FIXED(4.5);
        train_soldier_check_jump_expected.gravity = FIXED(0.3203125);
        train_soldier_check_jump_expected.x_speed = FIXED(-2);
        train_soldier_check_jump_expected.air_state = 1;
    } else if (mode == JUMP_SLOW_RIGHT) {
        train_soldier_check_jump_expected.unk5 = 4;
        train_soldier_check_jump_expected.y_speed = FIXED(3.5);
        train_soldier_check_jump_expected.gravity = FIXED(0.2578125);
        train_soldier_check_jump_expected.x_speed = FIXED(1);
        train_soldier_check_jump_expected.air_state = 1;
    }
    if (mode != FALL)
        assert(train_soldier_check_jump_owner.ext.main_49.unk80 == 0);
    for (i = 0; i < sizeof(train_soldier_check_jump_soldier) / 4; i++)
        assert(((u32*)&train_soldier_check_jump_soldier)[i] == ((u32*)&train_soldier_check_jump_expected)[i]);
    assert(tilemap[0] == 1 && attributes[0] == 0 && attributes[1] == 0x39 && layout_width == 16 && layout_size == 256);

    if (observation == 0)
        return train_soldier_check_jump_soldier.collision_flags | ((u32)(u8)train_soldier_check_jump_soldier.unk5 << 8) | ((u32)(u8)train_soldier_check_jump_soldier.air_state << 16)
            | ((u32)(u8)train_soldier_check_jump_soldier.unk15 << 24);
    return (u16)train_soldier_check_jump_soldier.y_pos.i.hi | ((u32)(u8)train_soldier_check_jump_soldier.unk6C << 16) | ((u32)(u8)train_soldier_check_jump_soldier.unk6E << 24);
}

#define OBSERVE(name, field)                                   \
    static u32 train_soldier_check_jump_##name##_##field(void) \
    {                                                          \
        return check(name, field);                             \
    }
#define CASE(name) OBSERVE(name, 0) OBSERVE(name, 1)
CASE(AIRBORNE)
CASE(FALL)
CASE(GUARD)
CASE(GROUND_AHEAD)
CASE(TURN)
CASE(WALL)
CASE(JUMP_FAST_LEFT)
CASE(JUMP_SLOW_RIGHT)
#define ENTRY(name) train_soldier_check_jump_##name##_0, train_soldier_check_jump_##name##_1,
static const CTestCase train_soldier_check_jump_cases[]
    = {
          ENTRY(AIRBORNE) ENTRY(FALL) ENTRY(GUARD) ENTRY(GROUND_AHEAD) ENTRY(TURN) ENTRY(WALL) ENTRY(JUMP_FAST_LEFT) ENTRY(JUMP_SLOW_RIGHT)
      };
static const u32 train_soldier_check_jump_cases_expected[] = { 0x10200u, 0x6Bu, 0xFF0300u, 0x8006Bu, 0x208u, 0x8006Bu, 0x208u, 0x8006Bu, 0x40000208u, 0x8006Bu, 0x20Eu, 0x8006Bu, 0x10408u, 0x8006Bu, 0x40010408u, 0x8006Bu };
#undef OBSERVE
#undef CASE
#undef ENTRY

static u32 train_soldier_states_steps[2];
static u32* train_soldier_states_table[0x20];
static struct MainObj train_soldier_states_soldier, train_soldier_states_expected, train_soldier_states_owner;

static void step(u32 index, s8 duration, s8 event, s8 relative, u8 frame)
{
    union AnimationStep value;
    value.fields.duration = duration;
    value.fields.event = event;
    value.fields.relative_step = relative;
    value.fields.frame_index = frame;
    train_soldier_states_steps[index] = value.packed;
}

static void prepare(s8 duration, s8 event)
{
    u32 i;
    memset(&train_soldier_states_soldier, 0, sizeof(train_soldier_states_soldier));
    memset(&train_soldier_states_owner, 0, sizeof(train_soldier_states_owner));
    for (i = 0; i < COUNT(train_soldier_states_table); i++)
        train_soldier_states_table[i] = &train_soldier_states_steps[1];
    step(0, duration, 0, 1, 3);
    step(1, 5, event, 0, 7);
    train_soldier_states_soldier.active = 0x41;
    train_soldier_states_soldier.id = 0x31;
    train_soldier_states_soldier.state = 1;
    train_soldier_states_soldier.unk5 = 4;
    train_soldier_states_soldier.unk6 = 2;
    train_soldier_states_soldier.bg_offset = 1;
    train_soldier_states_soldier.x_pos.val = 0x01234567;
    train_soldier_states_soldier.y_pos.val = 0x00456789;
    train_soldier_states_soldier.x_speed = 0x11111;
    train_soldier_states_soldier.x_accel = 0x2222;
    train_soldier_states_soldier.y_speed = 0x3333;
    train_soldier_states_soldier.gravity = 0x4444;
    train_soldier_states_soldier.unk40 = 0x1234;
    train_soldier_states_soldier.unk42 = 0x8765;
    train_soldier_states_soldier.sprite_frames = (const u8*)&train_soldier_states_steps[0];
    train_soldier_states_soldier.animation_table = train_soldier_states_table;
    train_soldier_states_soldier.animation_cursor = &train_soldier_states_steps[0];
    train_soldier_states_soldier.animation_step.packed = train_soldier_states_steps[0];
    SP_CUR_MAIN_OBJ = &train_soldier_states_owner;
}

static void same_object(void)
{
    u32 i;
    for (i = 0; i < sizeof(train_soldier_states_soldier) / 4; i++)
        assert(((u32*)&train_soldier_states_soldier)[i] == ((u32*)&train_soldier_states_expected)[i]);
}

static u32 walk_start(u32 fast, u32 facing)
{
    prepare(9, 0);
    train_soldier_states_owner.ext.main_49.unk86 = fast;
    train_soldier_states_soldier.unk15 = facing ? 0x40 : 0;
    train_soldier_states_expected = train_soldier_states_soldier;
    func_80068B80(&train_soldier_states_soldier);
    train_soldier_states_expected.collision_data = D_801076F8;
    train_soldier_states_expected.hurt_box = train_soldier_guard_hurt_box;
    train_soldier_states_expected.attack_box = train_soldier_guard_attack_box;
    train_soldier_states_expected.unk6 = 3;
    train_soldier_states_expected.x_speed = fast ? (facing ? FIXED(3) : -FIXED(3)) : (facing ? FIXED(1.75) : -FIXED(1.75));
    train_soldier_states_expected.x_accel = train_soldier_states_expected.y_speed = train_soldier_states_expected.gravity = 0;
    train_soldier_states_expected.animation_cursor = train_soldier_states_table[1];
    train_soldier_states_expected.unk17 = 1;
    train_soldier_states_expected.previous_animation_index = 0xFF;
    train_soldier_states_expected.animation_step.packed = train_soldier_states_steps[1];
    same_object();
    assert(train_soldier_states_owner.ext.main_49.unk86 == fast);
    return (u32)train_soldier_states_soldier.x_speed;
}

static u32 idle(void)
{
    prepare(1, 6);
    train_soldier_states_expected = train_soldier_states_soldier;
    train_soldier_idle(&train_soldier_states_soldier);
    same_object();
    return (u8)train_soldier_states_soldier.unk6 | ((u32)(u8)train_soldier_states_soldier.animation_step.fields.duration << 8);
}

static u32 crouch(s8 duration, s8 event)
{
    prepare(duration, event);
    train_soldier_states_expected = train_soldier_states_soldier;
    train_soldier_jump_crouch(&train_soldier_states_soldier);
    if (duration == 1) {
        train_soldier_states_expected.animation_cursor = &train_soldier_states_steps[1];
        train_soldier_states_expected.animation_step.packed = train_soldier_states_steps[1];
        if (event != 0)
            train_soldier_states_expected.unk6 = 3;
    } else {
        train_soldier_states_expected.animation_step.fields.duration = duration - 1;
    }
    same_object();
    return (u8)train_soldier_states_soldier.unk6 | ((u32)(u8)train_soldier_states_soldier.animation_step.fields.event << 8)
        | ((u32)(u8)train_soldier_states_soldier.animation_step.fields.duration << 16);
}

static u32 fire(s8 event, u32 free_slot)
{
    struct ShotObj before[0x20];
    u32 i, j, spawned = 0xFF;
    prepare(1, event);
    train_soldier_states_soldier.unk15 = 0x40;
    train_soldier_states_owner.ext.main_49.unk82 = 0x93;
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i != free_slot;
    memcpy(before, shot_objects, sizeof(before));
    D_8013E198[2] = -1;
    train_soldier_states_expected = train_soldier_states_soldier;
    train_soldier_shoot_fire(&train_soldier_states_soldier);
    assert(D_8013E198[2] == -1);
    train_soldier_states_expected.animation_cursor = &train_soldier_states_steps[1];
    train_soldier_states_expected.animation_step.packed = train_soldier_states_steps[1];
    if (event != 0)
        train_soldier_states_expected.unk6 = 3;
    same_object();
    for (i = 0; i < COUNT(shot_objects); i++) {
        struct ShotObj want = before[i];
        if (event != 0 && i == free_slot) {
            want.active = 0x41;
            want.id = 0x19;
            want.unk2 = 0x93;
            want.x_pos.val = train_soldier_states_soldier.x_pos.val;
            want.y_pos.val = train_soldier_states_soldier.y_pos.val;
            want.unk3C = (void*)train_soldier_states_soldier.sprite_frames;
            want.unk40 = train_soldier_states_soldier.unk40;
            want.unk42 = train_soldier_states_soldier.unk42 & 0x7FFF;
            want.bg_offset = train_soldier_states_soldier.bg_offset;
            want.animation_table = train_soldier_states_soldier.animation_table;
            want.unk15 = train_soldier_states_soldier.unk15;
            spawned = i;
        }
        for (j = 0; j < sizeof(want); j++)
            assert(((u8*)&shot_objects[i])[j] == ((u8*)&want)[j]);
    }
    return (u8)train_soldier_states_soldier.unk6 | (spawned << 8) | ((u32)(u8)shot_objects[free_slot < 0x20 ? free_slot : 0].unk2 << 16);
}

#define CASE(name, call)  \
    static u32 name(void) \
    {                     \
        return call;      \
    }
CASE(WALK_SLOW_LEFT, walk_start(0, 0))
CASE(WALK_SLOW_RIGHT, walk_start(0, 1))
CASE(WALK_FAST_LEFT, walk_start(1, 0))
CASE(WALK_FAST_RIGHT, walk_start(1, 1))
CASE(IDLE, idle())
CASE(CROUCH_WAIT, crouch(3, 2))
CASE(CROUCH_NO_EVENT, crouch(1, 0))
CASE(CROUCH_EVENT, crouch(1, 2))
CASE(FIRE_NO_EVENT, fire(0, 4))
CASE(FIRE_SOUND_SHOT, fire(3, 4))
CASE(FIRE_SHOT, fire(1, 0))
CASE(FIRE_POOL_FULL, fire(1, 0x20))
#define ENTRY(name) name,
static const CTestCase train_soldier_states_cases[] = {
    ENTRY(WALK_SLOW_LEFT) ENTRY(WALK_SLOW_RIGHT) ENTRY(WALK_FAST_LEFT) ENTRY(WALK_FAST_RIGHT)
        ENTRY(IDLE) ENTRY(CROUCH_WAIT) ENTRY(CROUCH_NO_EVENT) ENTRY(CROUCH_EVENT)
            ENTRY(FIRE_NO_EVENT) ENTRY(FIRE_SOUND_SHOT) ENTRY(FIRE_SHOT) ENTRY(FIRE_POOL_FULL)
};
static const u32 train_soldier_states_cases_expected[] = { 0xFFFE4000u, 0x1C000u, 0xFFFD0000u, 0x30000u, 0x102u, 0x20002u, 0x50002u, 0x50203u, 0xFF02u, 0x930403u, 0x930003u, 0xFF03u };
#undef CASE
#undef ENTRY

static const u32 train_soldier_shoot_aim_expected[] = { 1u };
static u32 test_train_soldier_shoot_aim(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0_present = 255;
    child_0.ext.main_49.unk82 = 131;
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    train_soldier_shoot_aim(&obj);
    observed_values[0] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, train_soldier_shoot_aim_expected, 1);
}

#define SOLDIER_CASE(name, player_x, object_x)  \
    static u32 name(void)                       \
    {                                           \
        struct MainObj obj;                     \
        u32 actual;                             \
        memset(&obj, 0, sizeof(obj));           \
        memset(&g_Player, 0, sizeof(g_Player)); \
        obj.unk6 = 1;                           \
        obj.unk7A = 9;                          \
        obj.x_pos.val = object_x;               \
        g_Player.x_pos.val = player_x;          \
        SP_CUR_MAIN_OBJ = &obj;                 \
        ((u8*)&obj)[0x81] = 0;                  \
        train_soldier_wait_for_player(&obj);    \
        assert(obj.state == 1);                 \
        assert(obj.unk5 == 2);                  \
        assert(obj.unk6 == 0);                  \
        assert(obj.unk7A == 0);                 \
        actual = (u32)obj.unk15;                \
        SP_CUR_MAIN_OBJ = NULL;                 \
        return actual;                          \
    }
SOLDIER_CASE(soldier_player_left, 0, 65536)
SOLDIER_CASE(soldier_player_right, 65536, 0)
#undef SOLDIER_CASE
static const CTestCase train_soldier_wait_facing_cases[] = {
    soldier_player_left,
    soldier_player_right,
};

static const u32 train_soldier_wait_facing_cases_expected[] = { 0x0u, 0x40u };
const struct CTestGroup c_test_groups[] = {
    { "train_soldier_aim_flags", train_soldier_aim_flags_cases, train_soldier_aim_flags_cases_expected, COUNT(train_soldier_aim_flags_cases), 0 },
    { "train_soldier_check_jump", train_soldier_check_jump_cases, train_soldier_check_jump_cases_expected, COUNT(train_soldier_check_jump_cases), 0 },
    { "train_soldier_states", train_soldier_states_cases, train_soldier_states_cases_expected, COUNT(train_soldier_states_cases), 0 },
    { "train_soldier_shoot_aim", 0, 0, 1, test_train_soldier_shoot_aim },
    { "train_soldier_wait_facing", train_soldier_wait_facing_cases, train_soldier_wait_facing_cases_expected, COUNT(train_soldier_wait_facing_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_soldier_aim_flags_cases) + COUNT(train_soldier_check_jump_cases) + COUNT(train_soldier_states_cases) + 1 + COUNT(train_soldier_wait_facing_cases);
