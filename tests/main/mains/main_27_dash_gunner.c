#include "test_runtime.h"
extern union AnimationStep* dash_gunner_animations[12];
extern struct StageObjectRecord stage_object_records_10_0[62];
extern struct StageObjectRecord stage_object_records_3_1[71];
extern struct StageObjectRecord stage_object_records_3_0[58];
extern struct Unk_unk68 dash_gunner_boxes[10];
extern struct Unk_unk68* D_8013B828;
extern struct Unk_unk68* D_8013B82C;
extern struct Unk_unk68* D_8013B830;
extern struct Unk_unk68* D_8013B834;

static u8 stop_entries[82 * 4];
static void expected_animation(struct MainObj* obj, u32 index)
{
    obj->unk17 = index;
    obj->previous_animation_index = 0xFF;
    ANIMATED_OBJECT(obj)->animation_cursor = dash_gunner_animations[index];
    obj->animation_step = *dash_gunner_animations[index];
}
static u32 dash_gunner_animation_transitions_dash_case(u32 mode)
{
    static const s16 player_x[8] = { 90, 110, 102, 98, 90, 110, 110, 100 };
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct BackgroundObj backgrounds_before[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(stop_entries, 0, sizeof(stop_entries));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    D_80141F50[2] = stop_entries;
    cur_random = 119;
    obj.active = 0x41;
    obj.id = 27;
    obj.state = 1;
    obj.unk5 = 6;
    obj.unk6 = 3;
    obj.unk15 = mode == 1 || mode == 3 || mode == 5 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_speed = 12345;
    obj.y_speed = 2 * 65536;
    obj.x_accel = 777;
    obj.ext.main_27.unk8C = mode >= 4 && mode <= 6 ? 1 : 9;
    obj.ext.main_27.unk82 = mode == 7 ? 1 : 9;
    obj.ext.main_27.unk89 = 6;
    obj.ext.main_27.unk88 = mode == 2 || mode == 3;
    obj.ext.main_27.unk84 = 100 * 65536;
    obj.animation_table = (const u8* const*)dash_gunner_animations;
    set_animation(&obj, 0);
    g_Player.x_pos.val = player_x[mode] * 65536;
    g_Player.y_pos.val = 100 * 65536;
    expected = obj;
    player_expected = g_Player;
    expected.ext.main_27.unk8C--;
    if (mode == 4 || mode == 5) {
        expected_animation(&expected, 3);
        expected.x_speed = 0;
        expected.unk5 = 5;
        expected.unk6 = 0;
    } else {
        expected.ext.main_27.unk82--;
        if (mode == 7) {
            expected.ext.main_27.unk82 = 30;
            expected.unk7C = 10;
            expected.x_speed = 0;
            expected.unk5 = 7;
            expected.unk6 = 0;
        } else {
            expected.ext.main_27.unk89--;
            assert(expected.animation_step.fields.duration == 3);
            expected.animation_step.fields.duration--;
            if (mode <= 1) {
                expected.ext.main_27.unk88 = 1;
                expected_animation(&expected, 7);
            }
            if (mode == 2 || mode == 3) {
                expected.ext.main_27.unk88 = 0;
                expected_animation(&expected, 1);
            }
            expected.x_speed = mode <= 1 ? (obj.unk15 ? 4 : -4) * 65536 : (obj.unk15 ? 2 : -2) * 65536;
            expected.x_pos.val += expected.x_speed;
            expected.y_pos.val -= expected.y_speed;
        }
    }
    func_80059640(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < sizeof(stop_entries); i++)
        assert(stop_entries[i] == 0);
    assert(D_80141F50[2] == stop_entries && cur_random == (mode == 7 ? 376 : 119));
    i = (u8)obj.unk5 | ((u32)obj.unk17 << 8) | ((u32)obj.ext.main_27.unk88 << 16) | ((u32)obj.ext.main_27.unk82 << 24);
    return i;
}
#define CASE(m)                                                 \
    static u32 dash_gunner_animation_transitions_dash_##m(void) \
    {                                                           \
        return dash_gunner_animation_transitions_dash_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) dash_gunner_animation_transitions_dash_##m,
static const CTestCase dash_gunner_animation_transitions_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 dash_gunner_animation_transitions_cases_expected[] = { 0x8010706u, 0x8010706u, 0x8000106u, 0x8000106u, 0x9000305u, 0x9000305u, 0x8000006u, 0x1E000007u };
#undef CASE
#undef ENTRY

static u32 dash_gunner_facing_start_dash_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    u32 i, facing = mode >= 2 && mode < 4, turn = mode == 1 || mode == 2;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 27;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk7C = mode == 4 ? 2 : 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.x_speed = 0x5678;
    g_Player.x_pos.i.hi = mode == 1 || mode == 3 ? 110 : 90;
    obj.animation_table = (const u8* const*)dash_gunner_animations;
    set_animation(&obj, 0);
    expected = obj;
    player_before = g_Player;
    expected.animation_step.fields.duration--;
    expected.unk7C--;
    if (mode != 4) {
        expected.ext.main_27.unk8A = 1;
        expected.unk6 = 1;
        if (turn) {
            expected.unk5 = 4;
            expected.unk7C = 1;
            expected.unk17 = 2;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = (const u8*)dash_gunner_animations[2];
            expected.animation_step = *dash_gunner_animations[2];
        } else {
            expected.unk7C = 20;
            expected.x_speed = facing ? 4 * 65536 : -4 * 65536;
        }
    }
    dash_gunner_dash_start(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u16)obj.unk7C | ((u32)(u8)obj.unk5 << 16) | ((u32)obj.unk17 << 24);
}
#define CASE(m)                                        \
    static u32 dash_gunner_facing_start_dash_##m(void) \
    {                                                  \
        return dash_gunner_facing_start_dash_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) dash_gunner_facing_start_dash_##m,
static const CTestCase dash_gunner_facing_start_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 dash_gunner_facing_start_cases_expected[] = { 0x30014u, 0x2040001u, 0x2040001u, 0x30014u, 0x30001u };
#undef CASE
#undef ENTRY

static struct GunnerInput {
    u8 shoot, facing, direction, full;
    s16 timer;
    s32 counter;
    s16 player_x;
};
enum { DASH_TICK,
    DASH_HELD,
    DASH_TURN_RIGHT,
    DASH_TURN_LEFT,
    DASH_STOP,
    SHOOT_BLOCKED_RIGHT,
    SHOOT_BLOCKED_LEFT,
    SHOOT_FULL,
    SHOOT_SPAWN,
    SHOOT_EDGE,
    SHOOT_BURST };
static const struct GunnerInput inputs[] = {
    { 0, 0, 0, 0, 3, 5, 0x40 },
    { 0, 0, 0, 0, 3, 1, 0x40 },
    { 0, 0x40, 0, 0, 1, 5, 0x40 },
    { 0, 0, 0, 0, 1, 5, 0x100 },
    { 0, 0, 0, 0, 1, 5, 0x40 },
    { 1, 0x40, 16, 0, 5, 0, 0 },
    { 1, 0, 2, 0, 5, 0, 0 },
    { 1, 0, 16, 1, 5, 0, 0 },
    { 1, 0, 16, 0, 1, 0, 0 },
    { 1, 0x40, 8, 0, 5, 0, 0 },
    { 1, 0, 20, 0, 4, 0, 0 },
};
#define SHOT_SLOT 4
static u32 steps[2];
static u32* table[8];
static struct MainObj gunner, expected;
static struct ShotObj want_shots[0x20];

static void zero(void* target, u32 size)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)target)[i] = 0;
}

static u32 dash_gunner_steps_run(u32 mode)
{
    const struct GunnerInput* input = &inputs[mode];
    union AnimationStep value;
    u32 i, difference = 0, spawned = 0;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = input->player_x;
    zero(shot_objects, sizeof(shot_objects));
    for (i = 0; i < 0x20; i++)
        shot_objects[i].active = input->full || i != SHOT_SLOT;
    memcpy(want_shots, shot_objects, sizeof(want_shots));
    value.fields.duration = 4;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 2;
    steps[0] = value.packed;
    value.fields.duration = 6;
    steps[1] = value.packed;
    for (i = 0; i < COUNT(table); i++)
        table[i] = &steps[1];
    memset(&gunner, 0, sizeof(gunner));
    gunner.active = 0x41;
    gunner.id = 0x1B;
    gunner.unk2 = 3;
    gunner.state = 1;
    gunner.unk5 = input->shoot ? 5 : 3;
    gunner.unk6 = 2;
    gunner.unk15 = input->facing;
    gunner.unk40 = 0x0321;
    gunner.unk42 = 0x0654;
    gunner.x_pos.val = 0x00801111;
    gunner.y_pos.val = 0x00602222;
    gunner.x_accel = 0x1000;
    gunner.y_speed = 0x2000;
    gunner.unk7C = input->timer;
    gunner.sprite_frames = (const u8*)&steps[0];
    gunner.animation_table = table;
    gunner.animation_cursor = &steps[0];
    gunner.animation_step.packed = steps[0];
    gunner.ext.main_27.collision_direction = input->direction;
    gunner.ext.main_27.unk89 = 7;
    gunner.ext.main_27.unk8A = 8;
    gunner.ext.main_27.unk8C = input->counter;
    expected = gunner;

    if (!input->shoot) {
        dash_gunner_dash_end(&gunner);
        if (input->counter != 1)
            expected.ext.main_27.unk8C--;
        expected.animation_step.fields.duration--;
        expected.unk7C--;
        if (expected.unk7C == 0) {
            expected.ext.main_27.unk89 = 0;
            expected.ext.main_27.unk8A = 0;
            if ((input->facing == 0 && input->player_x > 0x80) || (input->facing != 0 && input->player_x < 0x80)) {
                expected.unk7C = 0x14;
                expected.x_accel = 0;
                expected.y_speed = 0;
                expected.unk5 = 4;
            } else {
                expected.unk5 = 6;
            }
            expected.unk6 = 0;
        }
    } else {
        u32 blocked = (input->direction > 8 && input->direction < 24) ? input->facing != 0
                                                                      : (input->direction < 8 || input->direction > 24) && input->facing == 0;
        dash_gunner_shoot_fire(&gunner);
        expected.animation_step.fields.duration--;
        if (blocked) {
            expected.unk7C = 0xA;
            expected.unk6 = 3;
        } else {
            expected.unk17 = 4;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = &steps[1];
            expected.animation_step.packed = steps[1];
            if (!input->full) {
                struct ShotObj* shot = &want_shots[SHOT_SLOT];
                shot->active = 0x41;
                shot->id = 0xE;
                shot->unk2 = gunner.unk2;
                shot->unk40 = gunner.unk40;
                shot->unk42 = gunner.unk42;
                shot->animation_table = (u32**)gunner.animation_table;
                shot->unk3C = (void*)gunner.sprite_frames;
                shot->unk15 = gunner.unk15;
                shot->bg_offset = gunner.bg_offset;
                shot->x_pos.val = gunner.x_pos.val;
                shot->y_pos.val = gunner.y_pos.val;
                shot->state = 0;
                shot->x_vel = shot_objects[SHOT_SLOT].x_vel;
                shot->y_vel = shot_objects[SHOT_SLOT].y_vel;
                assert(shot->x_vel.val % 3 == 0 && shot->y_vel.val % 3 == 0);
                spawned = 1;
            }
            if (--expected.unk7C == 0) {
                expected.unk7C = 0xA;
                expected.unk6 = 3;
            } else {
                expected.unk7E = 0x14;
                expected.unk6 = 1;
            }
        }
    }
    for (i = 0; i < sizeof(gunner) / 4; i++)
        difference |= ((u32*)&gunner)[i] ^ ((u32*)&expected)[i];
    for (i = 0; i < sizeof(want_shots) / 4; i++)
        difference |= ((u32*)shot_objects)[i] ^ ((u32*)want_shots)[i];
    assert(difference == 0);
    i = (u8)gunner.unk5 | ((u32)(u8)gunner.unk6 << 8) | ((u32)(u16)gunner.unk7C << 16) | (spawned << 31);
    i ^= (u32)shot_objects[SHOT_SLOT].x_vel.val ^ ((u32)shot_objects[SHOT_SLOT].y_vel.val << 3);
    return i;
}

#define CASE(name)                                   \
    static u32 dash_gunner_steps_##name##_case(void) \
    {                                                \
        return dash_gunner_steps_run(name);          \
    }
CASE(DASH_TICK)
CASE(DASH_HELD)
CASE(DASH_TURN_RIGHT)
CASE(DASH_TURN_LEFT)
CASE(DASH_STOP)
CASE(SHOOT_BLOCKED_RIGHT)
CASE(SHOOT_BLOCKED_LEFT)
CASE(SHOOT_FULL)
CASE(SHOOT_SPAWN)
CASE(SHOOT_EDGE)
CASE(SHOOT_BURST)
#define ENTRY(name) dash_gunner_steps_##name##_case,
static const CTestCase dash_gunner_steps_cases[]
    = {
          ENTRY(DASH_TICK) ENTRY(DASH_HELD) ENTRY(DASH_TURN_RIGHT) ENTRY(DASH_TURN_LEFT) ENTRY(DASH_STOP) ENTRY(SHOOT_BLOCKED_RIGHT)
              ENTRY(SHOOT_BLOCKED_LEFT) ENTRY(SHOOT_FULL) ENTRY(SHOOT_SPAWN) ENTRY(SHOOT_EDGE) ENTRY(SHOOT_BURST)
      };
static const u32 dash_gunner_steps_cases_expected[] = { 0x20203u, 0x20203u, 0x140004u, 0x140004u, 0x6u, 0xA0305u, 0xA0305u, 0x40105u, 0x7FF70305u, 0x801C0105u, 0x8011E67Cu };
#undef SHOT_SLOT
#undef CASE
#undef ENTRY

static u32 turn_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    u32 i, animation = mode == 0 ? 1 : 7;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 27;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.unk15 = mode == 2 ? 0x40 : 0;
    obj.ext.main_27.unk8A = mode == 0 ? 0 : 1;
    obj.x_speed = 65536;
    obj.y_speed = -65536;
    obj.unk7C = 0x7777;
    obj.hp = 0x27;
    obj.animation_table = (const u8* const*)dash_gunner_animations;
    set_animation_frame(&obj, 2, 6);
    before = obj;
    dash_gunner_turn_flip(&obj);
    before.unk15 ^= 0x40;
    before.unk7C = 0x14;
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)dash_gunner_animations[animation];
    before.animation_step = *dash_gunner_animations[animation];
    if (mode == 0)
        before.unk6 = 2;
    else {
        before.unk5 = 7;
        before.unk6 = 1;
        before.x_speed = mode == 2 ? -4 * 65536 : 4 * 65536;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    return observation == 0 ? obj.animation_step.packed : (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u8)obj.unk15 << 16);
}
#define CASE(m, n)                                             \
    static u32 dash_gunner_turn_animation_turn_##m##_##n(void) \
    {                                                          \
        return turn_case(m, n);                                \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(m, n) dash_gunner_turn_animation_turn_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase dash_gunner_turn_animation_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 dash_gunner_turn_animation_cases_expected[] = { 0x4010003u, 0x400203u, 0x26010002u, 0x400107u, 0x26010002u, 0x107u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

#include "support/enemy_world.h"

static struct MainObj* dg_spawn(u32 stage, u32 substage, u32 kind, struct StageObjectRecord* record)
{
    return world_spawn(27, stage, substage, kind, record);
}

static void dg_check_boxes(u32 first)
{
    assert(D_8013B828 == &dash_gunner_boxes[first]);
    assert(D_8013B82C == &dash_gunner_boxes[first + 1]);
    assert(D_8013B830 == &dash_gunner_boxes[first + 3]);
    assert(D_8013B834 == &dash_gunner_boxes[first + 2]);
}
static const u32 dash_gunner_dash_move_expected[] = { 1u };
static u32 test_dash_gunner_dash_move(u32 row)
{
    struct MainObj* obj = dg_spawn(3, 0, 2, &stage_object_records_3_0[25]);
    u32 observed, i;
    func_80058740(obj);
    obj->x_pos.val = 0x00CC0000;
    obj->y_pos.val = 0x00C80000;
    obj->x_speed = 0xFFFE0000;
    obj->y_speed = 0;
    obj->x_accel = 0;
    obj->gravity = 0;
    obj->unk5 = 6;
    obj->unk6 = 0;
    obj->unk7C = 0;
    obj->unk7E = 0;
    obj->unk15 = 0;
    obj->unk17 = 1;
    obj->ext.main_27.unk82 = 12;
    obj->ext.main_27.unk84 = 0;
    obj->ext.main_27.unk88 = 0;
    obj->ext.main_27.unk89 = 0;
    obj->ext.main_27.unk8A = 0;
    obj->ext.main_27.unk8B = 0;
    obj->ext.main_27.unk8C = 150;
    obj->ext.main_27.collision_direction = 0;
    obj->animation_step.packed = 0x06010003;
    obj->previous_animation_index = 0xFF;
    obj->animation_cursor = (const u8*)(dash_gunner_animations[1] + 2);
    cur_random = 5;
    for (i = 0; i < 132; ++i) {
        if (i == 131)
            cur_random = 0;
        g_Player.x_pos.i.hi = obj->x_pos.i.hi - 100;
        g_Player.y_pos.i.hi = obj->y_pos.i.hi;
        func_80059640(obj);
    }
    assert(obj->unk5 == 7 && obj->unk6 == 0 && obj->ext.main_27.unk8C == 18);
    g_Player.x_pos.i.hi = obj->x_pos.i.hi - 100;
    for (i = 0; i < 10; ++i)
        dash_gunner_dash_start(obj);
    for (i = 0; i < 17; ++i)
        dash_gunner_dash_move(obj);
    assert(obj->unk5 == 7 && obj->unk6 == 1 && obj->ext.main_27.unk8C == 1 && obj->unk7C == 3);
    world_snapshot();
    animate_object(ANIMATED_OBJECT(world_expected));
    move_object(MOVING_OBJECT(world_expected));
    --world_expected->unk7C;
    dash_gunner_dash_move(obj);
    world_check();
    observed = obj->ext.main_27.unk8C;
    return c_test_observe(0, row, &observed, dash_gunner_dash_move_expected, 1);
}

static const u32 dash_gunner_run_move_expected[] = { 4u };
static u32 test_dash_gunner_run_move(u32 row)
{
    struct MainObj* obj = dg_spawn(10, 0, 8, &stage_object_records_10_0[28]);
    u32 observed, i;
    func_80058740(obj);
    assert(obj->unk5 == 2 && obj->unk6 == 0);
    for (i = 0; i < 47; ++i)
        dash_gunner_run_move(obj);
    assert(obj->unk5 == 2 && obj->unk6 == 0);
    assert(obj->ext.main_27.unk91 == 1 && obj->ext.main_27.unk90 == 1);
    world_snapshot();
    move_object(MOVING_OBJECT(world_expected));
    animate_object(ANIMATED_OBJECT(world_expected));
    --world_expected->ext.main_27.unk8C;
    world_expected->ext.main_27.unk91 = 96;
    world_expected->unk7C = 20;
    world_expected->y_speed = 0;
    world_expected->unk5 = 4;
    world_expected->unk6 = 0;
    dash_gunner_run_move(obj);
    dg_check_boxes(0);
    world_check();
    observed = obj->unk5;
    return c_test_observe(0, row, &observed, dash_gunner_run_move_expected, 1);
}

static const u32 func_80058740_0_expected[] = { 2u };
static u32 test_func_80058740_0(u32 row)
{
    struct MainObj* obj = dg_spawn(10, 0, 8, &stage_object_records_10_0[28]);
    u32 observed;
    world_snapshot();
    world_expected->hp = 6;
    world_expected->animation_table = (const u8* const*)dash_gunner_animations;
    world_expected->unk16 = 6;
    world_expected->unk18 = world_expected->x_pos;
    world_expected->unk1C = world_expected->y_pos;
    world_expected->state = 1;
    world_expected->x_speed = -0x18000;
    world_expected->ext.main_27.unk90 = 1;
    world_expected->ext.main_27.unk91 = 48;
    world_expected->unk5 = 2;
    world_expected->contact_damage = 6;
    world_expected->terrain_box = &dash_gunner_boxes[4];
    set_animation(world_expected, 1);
    func_80058740(obj);
    dg_check_boxes(0);
    world_check();
    observed = obj->unk5;
    return c_test_observe(0, row, &observed, func_80058740_0_expected, 1);
}

static const u32 func_80058740_1_expected[] = { 3u };
static u32 test_func_80058740_1(u32 row)
{
    struct MainObj* obj = dg_spawn(3, 1, 7, &stage_object_records_3_1[18]);
    u32 observed;
    world_snapshot();
    world_expected->hp = 6;
    world_expected->animation_table = (const u8* const*)dash_gunner_animations;
    world_expected->unk16 = 6;
    world_expected->unk18 = world_expected->x_pos;
    world_expected->unk1C = world_expected->y_pos;
    world_expected->state = 1;
    world_expected->unk15 = 64;
    world_expected->ext.main_27.unk82 = 30;
    world_expected->ext.main_27.unk8C = 300;
    world_expected->ext.main_27.unk89 = 20;
    world_expected->ext.main_27.unk80 = 1;
    world_expected->ext.main_27.unk88 = 1;
    world_expected->unk7A = 1;
    world_expected->unk5 = 3;
    world_expected->contact_damage = 7;
    world_expected->terrain_box = &dash_gunner_boxes[9];
    set_animation(world_expected, 1);
    func_80058740(obj);
    dg_check_boxes(5);
    world_check();
    observed = obj->unk5;
    return c_test_observe(0, row, &observed, func_80058740_1_expected, 1);
}

struct func_80058AC8_0_case {
    u32 x, player_x, clamped_x;
    u32 expected[1];
};
static const struct func_80058AC8_0_case func_80058AC8_0_cases[] = {
    { 31, 31, 32, { 3u } },
    { 2433, 2433, 2432, { 3u } },
};
static u32 test_func_80058AC8_0(u32 row)
{
    const struct func_80058AC8_0_case* c = &func_80058AC8_0_cases[row];
    struct MainObj* obj = dg_spawn(3, 1, 7, &stage_object_records_3_1[18]);
    u32 observed;
    func_80058740(obj);
    obj->x_pos.i.hi = c->x;
    g_Player.x_pos.i.hi = c->player_x;
    assert(obj->unk5 == 3 && obj->unk6 == 0);
    world_snapshot();
    world_expected->unk18 = world_expected->x_pos;
    world_expected->unk1C = world_expected->y_pos;
    world_expected->x_pos.i.hi = c->clamped_x;
    func_80058AC8(obj);
    dg_check_boxes(5);
    world_check();
    observed = obj->unk5;
    return c_test_observe(0, row, &observed, c->expected, 1);
}

static const u32 func_80058AC8_1_expected[] = { 2u };
static u32 test_func_80058AC8_1(u32 row)
{
    struct MainObj* obj = dg_spawn(3, 0, 0, &stage_object_records_3_0[22]);
    u32 observed;
    func_80058740(obj);
    obj->x_pos.i.hi = 1923;
    g_Player.x_pos.i.hi = 1800;
    background_objects[0].x_pos.i.hi = 1840;
    background_objects[0].y_pos.i.hi = 100;
    assert(obj->unk5 == 2 && obj->unk6 == 0);
    world_snapshot();
    world_expected->unk18 = world_expected->x_pos;
    world_expected->unk1C = world_expected->y_pos;
    move_object(MOVING_OBJECT(world_expected));
    animate_object(ANIMATED_OBJECT(world_expected));
    --world_expected->ext.main_27.unk8C;
    world_expected->x_pos.i.hi = 1920;
    world_expected->ext.main_27.saved_unk5 = 2;
    world_expected->ext.main_27.unk84 = g_Player.x_pos.val;
    world_expected->attack_box = (const u8*)&dash_gunner_boxes[2];
    world_expected->collision_data = (const u16*)D_801060F0;
    world_expected->hurt_box = (const u8*)&dash_gunner_boxes[0];
    world_expected->on_screen = 1;
    func_80058AC8(obj);
    world_check();
    observed = obj->unk5;
    return c_test_observe(0, row, &observed, func_80058AC8_1_expected, 1);
}

struct func_80059640_case {
    u32 unk8C, unk15, x_pos_hi, unk82, unk89, unk88, g_Player_y_pos_hi, obj_y_pos_hi, unk84, x_pos;
    u32 collision_flags;
    u32 expected[10];
};
static const struct func_80059640_case func_80059640_cases[] = {
    { 0, 255, 0, 0, 255, 255, 0, 0, 295388, 948736, 0, { 0xFFu, 0xFFu, 0xFEu, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0x40000u, 0u } },
    { 0, 0, -2, 0, 0, 255, 0, 0, 524353, 64, 0, { 0xFFu, 0xFFu, 0u, 0xFFFFFFFFu, 4u, 0u, 0x14u, 0xFFFFE000u, 0u, 0u } },
    { 1, 255, 0, 1, 0, 0, 0, 0, 0, 0, 0, { 0x1Eu, 0u, 0u, 0u, 7u, 0u, 0xAu, 0u, 0u, 0u } },
    { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, { 0x1Eu, 0u, 0u, 0u, 7u, 0u, 0xAu, 0u, 0u, 0u } },
    { 0, 255, 0, 0, 255, 255, 0, 0, 295388, 948736, 1, { 0xFFu, 0xFFu, 0xFEu, 0xFFFFFFFFu, 4u, 0u, 0x14u, 0u, 0u, 0u } },
    { 0, 0, 0, 0, 255, 255, 0, 0, 295388, 948736, 2, { 0xFFu, 0xFFu, 0xFEu, 0xFFFFFFFFu, 4u, 0u, 0x14u, 0u, 0u, 0u } },
    { 0, 0, 15, 0, 0, 255, 0, 0, -981883, -565921, 0, { 0xFFu, 0xFFu, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0xFFFC0000u, 0u } },
    { 0, 0, 0, 0, 255, 0, 3912, 4096, 0, 0, 0, { 0xFFu, 0u, 0xFEu, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0xFFFE0000u, 0u } },
};
static u32 test_func_80059640(u32 row)
{
    const struct func_80059640_case* c = &func_80059640_cases[row];
    u32 observed_values[10];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&cur_random, 0, sizeof(cur_random));
    obj.ext.main_27.unk8C = c->unk8C;
    obj.unk15 = c->unk15;
    obj.x_pos.i.hi = c->x_pos_hi;
    obj.ext.main_27.unk82 = c->unk82;
    obj.ext.main_27.unk89 = c->unk89;
    obj.ext.main_27.unk88 = c->unk88;
    g_Player.y_pos.i.hi = c->g_Player_y_pos_hi;
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    obj.ext.main_27.unk84 = c->unk84;
    g_Player.x_pos.val = c->x_pos;
    obj.collision_flags = c->collision_flags;
    func_80059640(&obj);
    observed_values[0] = (u32)obj.ext.main_27.unk82;
    observed_values[1] = (u32)obj.ext.main_27.unk88;
    observed_values[2] = (u32)obj.ext.main_27.unk89;
    observed_values[3] = (u32)obj.ext.main_27.unk8C;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.unk6;
    observed_values[6] = (u32)obj.unk7C;
    observed_values[7] = (u32)obj.x_accel;
    observed_values[8] = (u32)obj.x_speed;
    observed_values[9] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 10);
}

const struct CTestGroup c_test_groups[] = {
    { "dash_gunner_animation_transitions", dash_gunner_animation_transitions_cases, dash_gunner_animation_transitions_cases_expected, COUNT(dash_gunner_animation_transitions_cases), 0 },
    { "dash_gunner_facing_start", dash_gunner_facing_start_cases, dash_gunner_facing_start_cases_expected, COUNT(dash_gunner_facing_start_cases), 0 },
    { "dash_gunner_steps", dash_gunner_steps_cases, dash_gunner_steps_cases_expected, COUNT(dash_gunner_steps_cases), 0 },
    { "dash_gunner_turn_animation", dash_gunner_turn_animation_cases, dash_gunner_turn_animation_cases_expected, COUNT(dash_gunner_turn_animation_cases), 0 },
    { "dash_gunner_dash_move", 0, 0, 1, test_dash_gunner_dash_move },
    { "dash_gunner_run_move", 0, 0, 1, test_dash_gunner_run_move },
    { "func_80058740_0", 0, 0, 1, test_func_80058740_0 },
    { "func_80058740_1", 0, 0, 1, test_func_80058740_1 },
    { "func_80058AC8_0", 0, 0, 2, test_func_80058AC8_0 },
    { "func_80058AC8_1", 0, 0, 1, test_func_80058AC8_1 },
    { "func_80059640", 0, 0, 8, test_func_80059640 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dash_gunner_animation_transitions_cases) + COUNT(dash_gunner_facing_start_cases) + COUNT(dash_gunner_steps_cases) + COUNT(dash_gunner_turn_animation_cases) + 1 + 1 + 1 + 1 + 2 + 1 + 8;
