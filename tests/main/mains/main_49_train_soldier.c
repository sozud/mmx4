#include "test_runtime.h"
#include "main/mains/main_49_train_soldier.h"
#include "main/55C4.h"
#include "main/195B4.h"
#include "weapon_resources.h"
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
        assert(obj.animation_step.packed == C_TEST_STEP(0x1F000006));
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
static const u32 train_soldier_aim_flags_cases_expected[] = { 0x140D03u, 0x140C03u, 0x140E03u, 0x50B03u, 0x81A03u, 0x90B02u };

static struct JumpInput {
    s8 air;
    u8 floor, pit, wall, facing, patrol, guard, fast, step;
};
enum { AIRBORNE,
    FALL,
    GUARD,
    GROUND_AHEAD,
    TURN,
    WALL,
    JUMP_FAST_LEFT,
    JUMP_SLOW_RIGHT,
    TURN_BACK,
    SHOOTING,
    JUMP_SLOW_LEFT,
    JUMP_FAST_RIGHT };
static const struct JumpInput inputs[] = {
    { 1, 1, 5, 0, 0, 1, 0, 0 },
    { 0, 0, 5, 0, 0, 1, 0, 0 },
    { 0, 1, 5, 0, 0, 1, 2, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 1, 5, 0, 0, 0, 0, 0 },
    { 0, 1, 5, 1, 0, 1, 0, 1 },
    { 0, 1, 5, 0, 0, 1, 0, 1 },
    { 0, 1, 7, 0, 0x40, 1, 0, 0 },
    { 0, 1, 7, 0, PLAYER_FACING_RIGHT, 0, 0, 0 },
    { 0, 1, 5, 0, 0, 1, 0, 0, 6 },
    { 0, 1, 5, 0, 0, 1, 0, 0 },
    { 0, 1, 7, 0, PLAYER_FACING_RIGHT, 1, 0, 1 },
};
static u8 tilemap[256];
static u16 tiles[2][16][16];
static u32 attributes[2] = { 0, C_TEST_PSX_WORD(0x39) };
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
    train_soldier_check_jump_soldier.unk5 = input->step ? input->step : 2;
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
    if (mode == FALL || mode == JUMP_FAST_LEFT || mode == JUMP_SLOW_RIGHT || mode == JUMP_SLOW_LEFT || mode == JUMP_FAST_RIGHT) {
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
        train_soldier_check_jump_expected.unk15 = PLAYER_FACING_RIGHT;
        train_soldier_check_jump_expected.x_speed = -0x8000;
    } else if (mode == TURN_BACK) {
        train_soldier_check_jump_expected.unk15 = 0;
        train_soldier_check_jump_expected.x_speed = -0x8000;
    } else if (mode == JUMP_FAST_LEFT || mode == JUMP_FAST_RIGHT) {
        train_soldier_check_jump_expected.unk5 = 4;
        train_soldier_check_jump_expected.y_speed = FIXED(4.5);
        train_soldier_check_jump_expected.gravity = FIXED(0.3203125);
        train_soldier_check_jump_expected.x_speed = mode == JUMP_FAST_RIGHT ? FIXED(2) : FIXED(-2);
        train_soldier_check_jump_expected.air_state = 1;
    } else if (mode == JUMP_SLOW_RIGHT || mode == JUMP_SLOW_LEFT) {
        train_soldier_check_jump_expected.unk5 = 4;
        train_soldier_check_jump_expected.y_speed = FIXED(3.5);
        train_soldier_check_jump_expected.gravity = FIXED(0.2578125);
        train_soldier_check_jump_expected.x_speed = mode == JUMP_SLOW_LEFT ? FIXED(-1) : FIXED(1);
        train_soldier_check_jump_expected.air_state = 1;
    }
    if (mode != FALL)
        assert(train_soldier_check_jump_owner.ext.main_49.unk80 == 0);
    for (i = 0; i < sizeof(train_soldier_check_jump_soldier) / 4; i++)
        assert(((u32*)&train_soldier_check_jump_soldier)[i] == ((u32*)&train_soldier_check_jump_expected)[i]);
    assert(tilemap[0] == 1 && attributes[0] == 0 && attributes[1] == C_TEST_PSX_WORD(0x39) && layout_width == 16 && layout_size == 256);

    if (observation == 0)
        return train_soldier_check_jump_soldier.collision_flags | ((u32)(u8)train_soldier_check_jump_soldier.unk5 << 8) | ((u32)(u8)train_soldier_check_jump_soldier.air_state << 16)
            | ((u32)C_TEST_PSX_FACING(train_soldier_check_jump_soldier.unk15) << 24);
    return (u16)train_soldier_check_jump_soldier.y_pos.i.hi | ((u32)(u8)train_soldier_check_jump_soldier.unk6C << 16) | ((u32)(u8)train_soldier_check_jump_soldier.unk6E << 24);
}

static const u32 train_soldier_check_jump_cases_expected[] = { 0x10200u, 0x6Bu, 0xFF0300u, 0x8006Bu, 0x208u, 0x8006Bu, 0x208u, 0x8006Bu, 0x40000208u, 0x8006Bu, 0x20Eu, 0x8006Bu, 0x10408u, 0x8006Bu, 0x40010408u, 0x8006Bu, 0x208u, 0x608u, 0x10408u, 0x40010408u };
static u32 train_soldier_check_jump_cases_row(u32 row)
{
    return row < 2 * TURN_BACK ? check(row / 2, row % 2) : check(row - TURN_BACK, 0);
}

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
    train_soldier_states_soldier.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
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
    train_soldier_states_soldier.unk15 = PLAYER_FACING_RIGHT;
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
        obj.ext.main_49.index = 0;              \
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

static const u32 train_soldier_wait_facing_cases_expected[] = { 0x0u, PLAYER_FACING_RIGHT };

void train_soldier_despawn(struct MainObj* arg0);
extern union AnimationStep* highway_trooper_animations[27];
extern u8 D_800FFB5C[4], train_soldier_guard_hurt_box[], train_soldier_guard_attack_box[];
extern u32 D_801076F8[];
static u32 metadata[8], archive[16];
static u32 initialize(u32 row)
{
    struct MainObj obj, expected, *current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 type = row % 10, side = row / 10 % 3, layer = row / 30 % 3, substage = row / 90, resource = substage ? 4 : 3, i;
    for (i = 0; i < 8; i++) {
        metadata[i] = (i + 1) * 128;
        archive[i] = 32 + i * 4;
        archive[8 + i] = 0x13570000 + i;
    }
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)archive;
    engine_obj.stage = 8;
    engine_obj.substage = substage;
    engine_before = engine_obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    obj.active = 0x41;
    obj.id = 49;
    obj.unk2 = type;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x10000;
    obj.y_speed = -0x20000;
    obj.x_accel = 0x3456;
    obj.gravity = 0x4567;
    obj.unk15 = PLAYER_FACING_RIGHT;
    g_Player.x_pos.val = obj.x_pos.val + ((s32)side - 1) * 65536;
    g_Player.bg_offset = layer;
    player_before = g_Player;
    expected = obj;
    expected.ext.main_49.unk85 = type < 6 ? type / 2 : type;
    expected.ext.main_49.unk86 = type >= 6;
    expected.unk2 = type < 6 ? type % 2 : type;
    expected.unk7A = type >= 6 && type != 9;
    expected.unk42 = VISUAL_STAGE_PALETTE(resource) + (type == 2 || type == 3 || type == 5 ? 2 : 0);
    expected.unk40 = OBJECT_STAGE_TEXTURE(resource);
    expected.sprite_frames = (u8*)archive + 32 + resource * 4;
    expected.x_speed = expected.y_speed = expected.x_accel = expected.gravity = 0;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.animation_table = (const u8* const*)highway_trooper_animations;
    expected.terrain_box = (struct Unk_unk68*)D_800FFB5C;
    expected.attack_box = train_soldier_guard_attack_box;
    expected.hurt_box = train_soldier_guard_hurt_box;
    expected.collision_data = D_801076F8;
    expected.bg_offset = layer;
    expected.unk16 = VISUAL_SATURN_LAYER(6);
    expected.hp = 6;
    expected.contact_damage = 3;
    expected.unk17 = 1;
    expected.previous_animation_index = 255;
    expected.animation_cursor = (const u8*)highway_trooper_animations[1];
    expected.animation_step.packed = C_TEST_STEP(0x01010004);
    expected.state = type >= 6 && type != 9 ? 3 : 1;
    expected.unk5 = type >= 6 && type != 9 ? 0 : type == 4 || type == 5 ? 7
                                                                        : 2;
    expected.unk15 = type < 6 || !side ? 0 : PLAYER_FACING_RIGHT;
    assert(s_StageMainIds[8][substage][resource] == 0x22 && (u8)func_8002938C(0x22) == resource);
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &obj;
    func_80068548(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < 8; i++)
        assert(metadata[i] == (i + 1) * 128 && archive[i] == 32 + i * 4 && archive[8 + i] == 0x13570000 + i);
    assert(cur_random == 0x1234 && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive);
    return 1;
}
static u32 despawn(u32 row)
{
    struct MainObj obj, expected, *current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 type = row % 10, wanted;
    u8 record = row / 10 ? 0x8F : 0xDF;
    wanted = type >= 6 && type != 9 ? 0x80 : record & 0x70;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 49;
    obj.state = 2;
    obj.unk2 = type < 6 ? type % 2 : type;
    obj.on_screen = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk7 = 1;
    obj.backref = (u8*)&record;
    obj.ext.main_49.unk86 = type >= 6;
    expected = obj;
    memset(&expected, 0, 8);
    SP_CUR_MAIN_OBJ = &obj;
    train_soldier_despawn(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(record == wanted);
    return 1;
}

#include "support/state_cases.h"
void train_soldier_main(struct MainObj*);
void train_soldier_walk(struct MainObj*);
void train_soldier_walk_move(struct MainObj*);
void train_soldier_guard(struct MainObj*);
void train_soldier_check_guard(struct MainObj*);
void train_soldier_check_shoot(struct MainObj*);
void train_soldier_fall(struct MainObj*);
void train_soldier_fall_land(struct MainObj*);
void train_soldier_jump(struct MainObj*);
void train_soldier_rest(struct MainObj*);
void train_soldier_shoot(struct MainObj*);
void train_soldier_shoot_end(struct MainObj*);
#define TS(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.terrain_box = (struct Unk_unk68*)D_800FFB5C, SP_CUR_MAIN_OBJ = &so, memset(weapon_objects, 0, sizeof(weapon_objects)), SPIKE_IMMUNE_SET(g_Player, 1))
#define TX() (state_extra = so.ext.main_49.index | so.ext.main_49.unk80 << 8 | so.ext.main_49.unk82 << 16 | (u32)so.ext.main_49.unk83 << 24)
#define MAIN(kind, special, x) (TS(1, 0), so.state = 1, so.air_state = 1, so.ext.main_49.unk85 = kind, so.ext.main_49.unk86 = special, so.x_pos.i.hi = x, train_soldier_main(&so), state_extra = so.state)
static void tsx_main_shielded_off_screen(void)
{
    MAIN(2, 0, 0x200);
}
static void tsx_main_special_on_screen(void) { MAIN(6, 1, 0x80); }
static void tsx_main_special_off_screen(void) { MAIN(6, 1, 0x200); }
static void tsx_main_defeated(void) { TS(1, 0), so.state = 1, so.hp = 1, state_hit(&so, 0, 0, 1), cur_random = 1, train_soldier_main(&so), state_extra = so.state; }
static void tsx_update(void) { TS(1, 0), so.state = 1, so.air_state = 1, state_terrain(0), train_soldier_update(&so), state_extra = so.state; }
#define WAIT(sub, px, count) (TS(0, sub), so.state = 3, so.unk2 = 7, g_Player.x_pos.i.hi = px, so.ext.main_49.index = count, train_soldier_wait_for_player(&so), state_extra = so.ext.main_49.index)
static void tsx_wait_spotted(void)
{
    WAIT(0, 0x110, 0);
}
static void tsx_wait_far(void) { WAIT(0, 0x90, 0); }
static void tsx_wait_count(void) { WAIT(1, 0, 3); }
#define WALK(face, flags, vx) (TS(2, 1), so.unk15 = face, so.collision_flags = flags, so.x_speed = vx, train_soldier_walk(&so), TX())
static void tsx_walk_right_wall(void)
{
    WALK(PLAYER_FACING_RIGHT, 1, 0x1C000);
}
static void tsx_walk_right(void) { WALK(PLAYER_FACING_RIGHT, 0, 0x1C000); }
static void tsx_walk_left_wall(void) { WALK(0, 2, -0x1C000); }
static void tsx_walk_left(void) { WALK(0, 0, -0x1C000); }
static void tsx_guard_start(void) { TS(7, 0), so.x_speed = 0x10000, train_soldier_guard(&so), TX(); }
static void tsx_guard_hold(void) { TS(7, 1), train_soldier_guard(&so), TX(); }
static void tsx_check_guard_ready(void) { TS(2, 1), so.ext.main_49.index = 0x59, so.x_speed = 0x10000, train_soldier_check_guard(&so), TX(); }
static void tsx_check_guard_count(void) { TS(2, 1), train_soldier_check_guard(&so), TX(); }
#define SHOOT(step, air, cool, kind, sub, px, py) (TS(step, 0), so.air_state = air, so.ext.main_49.unk83 = cool, so.ext.main_49.unk85 = kind, so.unk2 = sub, g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, train_soldier_check_shoot(&so), TX())
static void tsx_shoot_busy(void)
{
    SHOOT(6, 0, 0, 0, 0, 0x80, 0x60);
}
static void tsx_shoot_cooling(void) { SHOOT(2, 0, 3, 0, 0, 0x80, 0x60); }
static void tsx_shoot_far(void) { SHOOT(2, 0, 0, 0, 0, 0x200, 0x60); }
static void tsx_shoot_kind1_left(void) { SHOOT(2, 0, 0, 1, 0, 0x40, 0x60); }
static void tsx_shoot_kind2_right(void) { SHOOT(2, 0, 0, 2, 1, 0xC0, 0x60); }
static void tsx_shoot_high(void) { SHOOT(2, 0, 0, 2, 0, 0x80, 0x20); }
static void tsx_shoot_low(void) { SHOOT(2, 0, 0, 0, 0, 0x80, 0x80); }
static void tsx_shoot_level(void) { SHOOT(2, 0, 0, 0, 0, 0x80, 0x60); }
#define DROP(flags, kind) (TS(3, 0), so.collision_flags = flags, so.ext.main_49.unk80 = kind, so.y_speed = 0x10000, so.gravity = 0x4200, train_soldier_fall(&so), TX())
static void tsx_drop_land_jump(void)
{
    DROP(8, 4);
}
static void tsx_drop_land_fall(void) { DROP(8, 5); }
static void tsx_drop_falling(void) { DROP(0, 5); }
#define LAND(kind, rel) (TS(3, 1), so.air_state = -1, so.ext.main_49.unk85 = kind, so.animation_step.fields.relative_step = rel, train_soldier_fall_land(&so), TX())
static void tsx_land_walk(void)
{
    LAND(0, 0);
}
static void tsx_land_guard(void) { LAND(2, 0); }
static void tsx_land_wait(void) { LAND(0, 1); }
static void tsx_jump_apex(void) { TS(4, 1), so.y_speed = 0x1000, so.gravity = 0x4200, train_soldier_jump(&so), TX(); }
static void tsx_jump_rising(void) { TS(4, 1), so.y_speed = 0x10000, so.gravity = 0x4200, train_soldier_jump(&so), TX(); }
static void tsx_rest_done(void) { TS(5, 0), so.ext.main_49.index = 0x3B, train_soldier_rest(&so), TX(); }
static void tsx_rest(void) { TS(5, 0), train_soldier_rest(&so), TX(); }
static void tsx_recoil_done(void) { TS(6, 2), train_soldier_shoot(&so), TX(); }
static void tsx_recoil(void) { TS(6, 2), so.animation_step.fields.relative_step = 1, train_soldier_shoot(&so), TX(); }
#define END(kind, rel) (TS(6, 3), so.ext.main_49.unk85 = kind, so.ext.main_49.index = 9, so.x_speed = 0x10000, so.animation_step.fields.relative_step = rel, train_soldier_shoot_end(&so), TX())
static void tsx_end_rest(void)
{
    END(0, 0);
}
static void tsx_end_guard(void) { END(2, 0); }
static void tsx_end_wait(void) { END(0, 1); }

static void (*const train_soldier_step_states_cases[])(void) = {
    tsx_main_shielded_off_screen,
    tsx_main_special_on_screen,
    tsx_main_special_off_screen,
    tsx_main_defeated,
    tsx_update,
    tsx_wait_spotted,
    tsx_wait_far,
    tsx_wait_count,
    tsx_walk_right_wall,
    tsx_walk_right,
    tsx_walk_left_wall,
    tsx_walk_left,
    tsx_guard_start,
    tsx_guard_hold,
    tsx_check_guard_ready,
    tsx_check_guard_count,
    tsx_shoot_busy,
    tsx_shoot_cooling,
    tsx_shoot_far,
    tsx_shoot_kind1_left,
    tsx_shoot_kind2_right,
    tsx_shoot_high,
    tsx_shoot_low,
    tsx_shoot_level,
    tsx_drop_land_jump,
    tsx_drop_land_fall,
    tsx_drop_falling,
    tsx_land_walk,
    tsx_land_guard,
    tsx_land_wait,
    tsx_jump_apex,
    tsx_jump_rising,
    tsx_rest_done,
    tsx_rest,
    tsx_recoil_done,
    tsx_recoil,
    tsx_end_rest,
    tsx_end_guard,
    tsx_end_wait,
};
static const u32 train_soldier_step_states_expected[] = {
    0x1000001u,
    0u,
    0x2000000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    0u,
    0x1000001u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    1u,
    0u,
    0x1000001u,
    0u,
    0x2000000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    0u,
    1u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0x80000000u,
    1u,
    2u,
    0x2100u,
    0x1000001u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    1u,
    0u,
    0x100u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x10u,
    0u,
    0u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x100u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    0u,
    0x102u,
    0u,
    0x81C000u,
    0xFFFE4000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x102u,
    0u,
    0x81C000u,
    0x1C000u,
    0u,
    0u,
    0x4000u,
    0u,
    0u,
    0u,
    0x102u,
    0u,
    0x7E4000u,
    0x1C000u,
    0u,
    0u,
    0x4000u,
    0u,
    0u,
    0u,
    0x102u,
    0u,
    0x7E4000u,
    0xFFFE4000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x107u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    8u,
    3u,
    0u,
    0u,
    0x107u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    5u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    7u,
    0u,
    0u,
    0u,
    0x102u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    1u,
    0u,
    6u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x2000000u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    6u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0xAu,
    0u,
    0x400000u,
    0u,
    6u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0x400Au,
    0u,
    0x400000u,
    0u,
    6u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0x400Au,
    0u,
    0x800000u,
    0u,
    6u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0x400Au,
    0u,
    0x820000u,
    0u,
    6u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0x400Au,
    0u,
    0x810000u,
    0u,
    0x103u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0x17u,
    0u,
    0x400u,
    0u,
    0x103u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0x18u,
    0u,
    0x500u,
    0u,
    3u,
    0u,
    0x800000u,
    0u,
    0xBE00u,
    0x420000u,
    0u,
    0u,
    0x500u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    7u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0xFF000103u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0xFF000003u,
    0u,
    0x800000u,
    0u,
    0u,
    0x420000u,
    9u,
    0u,
    0x400u,
    0u,
    0x104u,
    0u,
    0x800000u,
    0u,
    0xBE00u,
    0x420000u,
    0u,
    0u,
    0u,
    0u,
    2u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    1u,
    0u,
    0x3Cu,
    0u,
    5u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    1u,
    0u,
    0x306u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0xBu,
    0u,
    0u,
    0u,
    0x206u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    5u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    7u,
    0u,
    0xB4000000u,
    0u,
    7u,
    0u,
    0x800000u,
    0u,
    0u,
    0u,
    7u,
    0u,
    0x5A000000u,
    0u,
    0x306u,
    0u,
    0x800000u,
    0x10000u,
    0u,
    0u,
    0u,
    0u,
    9u,
    0u,
};
static u32 test_train_soldier_step_states(u32 row)
{
    return state_run(train_soldier_step_states_cases[row], row, &train_soldier_step_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "train_soldier_step_states", 0, 0, COUNT(train_soldier_step_states_cases), test_train_soldier_step_states },
    { "train_soldier_aim_flags", NULL, train_soldier_aim_flags_cases_expected, COUNT(train_soldier_aim_flags_cases_expected), aim_case },
    { "train_soldier_check_jump", NULL, train_soldier_check_jump_cases_expected, COUNT(train_soldier_check_jump_cases_expected), train_soldier_check_jump_cases_row },
    { "train_soldier_states", train_soldier_states_cases, train_soldier_states_cases_expected, COUNT(train_soldier_states_cases), 0 },
    { "train_soldier_wait_facing", train_soldier_wait_facing_cases, train_soldier_wait_facing_cases_expected, COUNT(train_soldier_wait_facing_cases), 0 },
    { "all_shipped_modes_resource_variants_layers_and_player_sides", NULL, NULL, 30, initialize },
    { "temporary_and_permanent_backref_rules_including_mode9", NULL, NULL, 10, despawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_soldier_step_states_cases) + COUNT(train_soldier_aim_flags_cases_expected) + COUNT(train_soldier_check_jump_cases_expected) + COUNT(train_soldier_states_cases) + COUNT(train_soldier_wait_facing_cases) + 30 + 10;
