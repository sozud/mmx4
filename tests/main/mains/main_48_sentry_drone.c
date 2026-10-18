#include "test_runtime.h"
#include "main/mains/main_48_sentry_drone.h"
#include "support/state_cases.h"
#include "support/drone_burst_data.h"
void sentry_drone_wait_for_player(struct MainObj*);
extern union AnimationStep* sentry_drone_animations[13];
extern u8 D_800FFAD0[4];
extern u8 D_800FFAD4[];
extern s8 D_800FFACC[4];
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

static const u32 sentry_drone_steps_cases_expected[] = { 0x10104u, 0x10105u, 0x30104u, 0x30105u, 0x1316u, 0xFFFF8303u, 0x408303u, 0xFFFC0303u, 0x440303u, 0x303u, 0x1312u, 0x1401212u, 0x4401212u, 0x2001212u, 0x4001212u, 0x1001212u, 0x5001212u, 0x3001212u, 0x5401212u, 0x1212u, 0x1212u, 0x18C699A1u };

static const u32 func_800681C4_expected[] = { 0u, 0u, 0x20u };
static u32 test_func_800681C4(u32 row)
{
    u32 observed_values[3];
    struct MainObj obj;
    struct MainObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    child_0.ext.main_48.collision_result = 32;
    SP_CUR_MAIN_OBJ = &child_0;
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
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    SP_CUR_MAIN_OBJ = &child_0;
    func_80068340(&obj);
    observed_values[0] = (u32)child_0.ext.main_48.collision_result;
    return c_test_observe(0, row, observed_values, func_80068340_expected, 1);
}

static void sd_wait(void)
{
    state_reset(0, 0, 0);
    so.x_pos.i.hi = 0x80;
    g_Player.x_pos.i.hi = 0x100;
    sentry_drone_wait_for_player(&so);
}
static void sd_wake(void)
{
    state_reset(0, 0, 0);
    so.x_pos.i.hi = 0x80;
    g_Player.x_pos.i.hi = 0x140;
    sentry_drone_wait_for_player(&so);
}

static void (*const sentry_drone_misc_cases[])(void) = {
    sd_wait,
    sd_wake,
};
static const u32 sentry_drone_misc_expected[] = { 0u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u };

static u32 test_sentry_drone_misc(u32 row)
{
    return state_run(sentry_drone_misc_cases[row], row, &sentry_drone_misc_expected[row * 10]);
}

extern union AnimationStep* sentry_drone_animations[13];
extern s8 D_800FFACC[4];
extern u8 D_800FFAD0[4], D_800FFAD4[4];
extern u32 D_801076F8[];
void sentry_drone_burst(struct MainObj*);
void sentry_drone_spread(struct MainObj*);
void sentry_drone_drift(struct MainObj*);
void sentry_drone_dash(struct MainObj*);
void sentry_drone_drop(struct MainObj*);
void sentry_drone_check_player_near(struct MainObj*);

static struct {
    u32 before;
    struct MainObj value;
    u32 after;
} guarded;
#define obj guarded.value
static struct MainObj expected_sentry_drone_burst;
static struct ShotObj shots_expected[32];
static struct MiscObj misc_expected[64];
static struct PlayerObj player_before, entity_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static u32 backref, backref_expected;
static const s16 cameras[3][2] = { { 0, 0 }, { 1024, 512 }, { -320, -240 } };
static const s8 first_shot[5] = { -1, 0, 0, 15, 31 };
static const s8 first_misc[5] = { -1, 0, 0, 31, 63 };

static void install_animation(u32 animation, u32 frame)
{
    obj.unk17 = animation;
    obj.animation_cursor = (const u8*)sentry_drone_animations[animation] + frame * 4;
    obj.animation_step.packed = sentry_drone_animations[animation][frame].packed;
}

static void expect_animation(u32 animation, u32 frame)
{
    expected_sentry_drone_burst.unk17 = animation;
    expected_sentry_drone_burst.previous_animation_index = 0xFF;
    expected_sentry_drone_burst.animation_cursor = (const u8*)sentry_drone_animations[animation] + frame * 4;
    expected_sentry_drone_burst.animation_step.packed = sentry_drone_animations[animation][frame].packed;
}

static void expect_tick(void)
{
    u32 animation = expected_sentry_drone_burst.unk17;
    u32 frame = ((const u8*)expected_sentry_drone_burst.animation_cursor - (const u8*)sentry_drone_animations[animation]) / 4;
    assert(animation < 6 && frame < 2);
    expected_sentry_drone_burst.animation_cursor = (const u8*)sentry_drone_animations[animation] + (1 - frame) * 4;
    expected_sentry_drone_burst.animation_step.packed = sentry_drone_animations[animation][1 - frame].packed;
}

static void prepare(u32 direction, u32 facing, u32 layer, u32 shot_mode, u32 misc_mode)
{
    u32 i;
    c_test_zero_words((u32*)&guarded, sizeof(guarded) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    guarded.before = 0x12345678;
    guarded.after = 0x87654321;
    obj.active = 0x41;
    obj.id = 48;
    obj.state = 1;
    obj.unk5 = 4;
    obj.bg_offset = layer;
    obj.unk15 = facing * 0x40;
    obj.x_pos.val = (cameras[layer][0] + 200) * 65536 + 0x1234;
    obj.y_pos.val = (cameras[layer][1] + 120) * 65536 + 0x5678;
    obj.x_speed = -0x23456;
    obj.y_speed = 0x34567;
    obj.x_accel = 0x456;
    obj.gravity = -0x567;
    obj.animation_table = (const u8* const*)sentry_drone_animations;
    obj.previous_animation_index = 0;
    install_animation(1, 0);
    obj.terrain_box = (struct Unk_unk68*)D_800FFAD0;
    obj.hurt_box = (u8*)D_800FFACC;
    obj.attack_box = D_800FFAD4;
    obj.collision_data = D_801076F8;
    obj.hp = 5;
    obj.contact_damage = 3;
    obj.unk40 = 0x4567;
    obj.unk42 = 0x9234;
    backref = 0xABCDEFF1;
    obj.backref = &backref;
    memset(&obj.ext, 0xA5, sizeof(obj.ext));
    obj.ext.main_48.unk80 = 2;
    obj.ext.main_48.unk81 = 3;
    obj.ext.main_48.unk82 = 2;
    obj.ext.main_48.unk83 = 1;
    obj.ext.main_48.saved_unk5 = 3;
    obj.ext.main_48.collision_result = direction;
    obj.ext.main_48.unk86 = directions[direction].low;
    obj.ext.main_48.unk87 = directions[direction].high;
    obj.ext.main_48.unk88 = direction & 0xFE;
    for (i = 0; i < 32; i++) {
        struct ShotObj* s = &shot_objects[i];
        s->active = shot_mode == 1 || (s32)i == first_shot[shot_mode] ? 0 : 1;
        if (s->active) {
            s->id = 7;
            s->state = 1;
            s->unk5 = 2;
        }
        s->x_pos.val = (50 + i) * 65536 + 0xBEEF;
        s->y_pos.val = (60 + i) * 65536 + 0xCAFE;
        s->x_vel.val = -0x76543;
        s->y_vel.val = 0x65432;
        s->unk50.data = D_800FFAD4;
        s->unk54 = (u8*)D_800FFACC;
        s->unk68 = (struct Unk_unk68*)D_800FFAD0;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 1;
        s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = 1;
        s->unk78 = s->unk62 = s->unk63 = s->unk7A = s->unk75 = 1;
        s->unk60 = 0x12;
        s->unk67 = 0x23;
        s->unk70 = 0x34;
        s->unk7C = (struct WeaponObj*)&g_Entity;
        s->unk84.value = 0x12345678;
        s->timer = 77;
    }
    for (i = 0; i < 64; i++) {
        struct MiscObj* m = &misc_objects[i];
        m->active = misc_mode == 1 || (s32)i == first_misc[misc_mode] ? 0 : 1;
        if (m->active) {
            m->id = 39;
            m->state = 1;
            m->unk5 = 2;
        }
        m->x_pos.val = (70 + i) * 65536 + 0xBEEF;
        m->y_pos.val = (80 + i) * 65536 + 0xCAFE;
        m->ext.pointer.unk50 = &g_Entity;
        m->unk40 = 0x2345;
        m->unk42 = 0x3456;
    }
    g_Player.x_pos.val = obj.x_pos.val - directions[direction].dx;
    g_Player.y_pos.val = obj.y_pos.val - directions[direction].dy;
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = cameras[i][0] * 65536;
        background_objects[i].y_pos.val = cameras[i][1] * 65536;
    }
    SP_CUR_MAIN_OBJ = &obj;
    cur_random = 0x1234;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
}

static void capture(void)
{
    expected_sentry_drone_burst = obj;
    backref_expected = backref;
    player_before = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)shots_expected, (const u32*)shot_objects, sizeof(shots_expected) / 4);
    c_test_copy_words((u32*)misc_expected, (const u32*)misc_objects, sizeof(misc_expected) / 4);
}
#define SAME(a, b) assert(c_test_word_difference((const u32*)(a), (const u32*)(b), sizeof(*(b)) / 4) == 0)
static void check_object(void)
{
    SAME(&obj, &expected_sentry_drone_burst);
    assert(guarded.before == 0x12345678 && guarded.after == 0x87654321);
    assert(backref == backref_expected && SP_CUR_MAIN_OBJ == &obj);
    assert(cur_random == 0x1234);
}
static void check(void)
{
    check_object();
    SAME(&g_Player, &player_before);
    SAME(&g_Entity, &entity_before);
    SAME(&engine_obj, &engine_before);
    SAME(&main_bss_state, &main_before);
    SAME(&background_objects, &backgrounds_before);
    SAME(&shot_objects, &shots_expected);
    SAME(&misc_objects, &misc_expected);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(need_palette_load == 0x20);
}

static void invoke(u32 family)
{
    expect_tick();
    if (family)
        sentry_drone_spread(&obj);
    else
        sentry_drone_burst(&obj);
}
static void expect_start(u32 family, u32 direction, u32 facing)
{
    expected_sentry_drone_burst.unk6 = 1;
    expected_sentry_drone_burst.x_speed = expected_sentry_drone_burst.x_accel = expected_sentry_drone_burst.y_speed = expected_sentry_drone_burst.gravity = 0;
    expected_sentry_drone_burst.ext.main_48.unk80 = 20;
    expect_animation(1, 0);
    if (family) {
        expected_sentry_drone_burst.ext.main_48.unk82 = 0;
        expected_sentry_drone_burst.unk15 = directions[direction].start_face[facing];
        expected_sentry_drone_burst.ext.main_48.collision_result = direction;
        expected_sentry_drone_burst.ext.main_48.unk86 = directions[direction].low;
        expected_sentry_drone_burst.ext.main_48.unk87 = directions[direction].high;
        expected_sentry_drone_burst.ext.main_48.unk88 = direction & 0xFE;
    }
}
static void expect_aim(u32 family, u32 direction, u32 facing)
{
    expected_sentry_drone_burst.ext.main_48.unk80 = 0;
    expected_sentry_drone_burst.unk6 = 2;
    expected_sentry_drone_burst.unk15 = family ? directions[direction].spread_face[facing] : directions[direction].burst_face[facing];
    if (!family)
        expected_sentry_drone_burst.ext.main_48.collision_result = direction;
    if (family || !directions[direction].keep_burst_animation)
        expect_animation(directions[direction].animation, 0);
}
static void expect_fire(s32 shot_index, s32 misc_index, u32 direction)
{
    if (shot_index >= 0) {
        struct ShotObj* s = &shots_expected[shot_index];
        s->unk50.data = 0;
        s->unk54 = 0;
        s->unk68 = 0;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 0;
        s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = 0;
        s->unk78 = s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
        s->active = 0x41;
        s->id = 0x1A;
        s->unk2 = direction;
        s->x_pos = expected_sentry_drone_burst.x_pos;
        s->y_pos = expected_sentry_drone_burst.y_pos;
        s->unk7C = (struct WeaponObj*)&obj;
        s->unk84.value = 0;
        s->x_vel.val = velocities[direction / 2][0];
        s->y_vel.val = velocities[direction / 2][1];
        expected_sentry_drone_burst.ext.main_48.unk80 = 8;
        expected_sentry_drone_burst.ext.main_48.unk82++;
        expected_sentry_drone_burst.unk6++;
    }
    if (misc_index >= 0) {
        struct MiscObj* m = &misc_expected[misc_index];
        m->active = 0x41;
        m->id = 0x19;
        m->unk2 = direction;
        m->x_pos = expected_sentry_drone_burst.x_pos;
        m->y_pos = expected_sentry_drone_burst.y_pos;
        m->ext.pointer.unk50 = &obj;
    }
}

static u32 test_starts(u32 row)
{
    u32 family = row >= 6, direction, facing, layer;
    if (!family) {
        direction = 0;
        facing = row % 2;
        layer = row / 2;
    } else {
        row -= 6;
        direction = row % 32;
        facing = (row / 32) % 2;
        layer = row / 64;
    }
    prepare(direction, facing, layer, 0, 0);
    obj.unk5 = family ? 5 : 4;
    obj.ext.main_48.collision_result = 0x12;
    obj.ext.main_48.unk86 = obj.ext.main_48.unk87 = obj.ext.main_48.unk88 = 0x1E;
    capture();
    expect_start(family, direction, facing);
    invoke(family);
    check();
    return 1;
}
static u32 test_compass(u32 row)
{
    u32 direction = row % 32, family = row < 64 ? row / 32 : row - 64, timer = row < 64 ? 1 : 2;
    prepare(direction, 0, direction % 3, 0, 0);
    obj.unk5 = family ? 5 : 4;
    obj.unk6 = 1;
    obj.ext.main_48.unk80 = timer;
    if (!family)
        obj.ext.main_48.collision_result = direction ^ 16;
    install_animation(1, 0);
    if (family) {
        g_Player.x_pos.val = obj.x_pos.val + directions[direction].dx;
        g_Player.y_pos.val = obj.y_pos.val + directions[direction].dy;
    }
    capture();
    expected_sentry_drone_burst.ext.main_48.unk80--;
    if (timer == 1)
        expect_aim(family, direction, 0);
    invoke(family);
    check();
    return 1;
}
static u32 test_boundaries(u32 row)
{
    u32 b = row % 24, q = (row / 24) % 4, facing = b % 2, family = row / 96;
    u32 direction = boundaries[b].directions[q];
    u32 live_facing = q == 0 || q == 3 ? 1 : facing;
    s32 dx = boundaries[b].ratio * 16, dy = 16 * 65536;
    if (q == 0 || q == 3)
        dx = -dx;
    if (q >= 2)
        dy = -dy;
    prepare(direction, facing, q % 3, 0, 0);
    g_Player.x_pos.val = obj.x_pos.val - dx;
    g_Player.y_pos.val = obj.y_pos.val - dy;
    obj.unk5 = family ? 5 : 4;
    obj.unk6 = family ? 0 : 1;
    obj.ext.main_48.unk80 = 1;
    obj.ext.main_48.collision_result = direction ^ 16;
    capture();
    if (family)
        expect_start(1, direction, live_facing);
    else
        expect_aim(0, direction, live_facing);
    invoke(family);
    check();
    return 1;
}
static u32 test_wait_event(u32 row)
{
    u32 animation = row % 6, frame = (row / 6) % 2, facing = (row / 12) % 2, layer = row / 24;
    prepare(0, facing, layer, 0, 0);
    obj.unk6 = 2;
    install_animation(animation, frame);
    capture();
    if (frame && animation != 0)
        expected_sentry_drone_burst.unk6 = 3;
    invoke(0);
    check();
    return 1;
}
static u32 test_fire(u32 row)
{
    u32 direction = row % 32, sm = (row / 32) % 5, mm = (row / 160) % 5, family = row / 800;
    prepare(direction, direction & 1, direction % 3, sm, mm);
    obj.unk5 = family ? 5 : 4;
    obj.unk6 = family ? 2 : 3;
    install_animation(directions[direction].animation, 1);
    capture();
    expect_fire(first_shot[sm], first_misc[mm], direction);
    invoke(family);
    check();
    return 1;
}
static u32 test_event_gate(u32 row)
{
    u32 direction = row % 32, mode = row / 32;
    prepare(direction, direction & 1, direction % 3, mode, mode);
    obj.unk5 = 5;
    obj.unk6 = 2;
    install_animation(1, 0);
    capture();
    invoke(1);
    check_object();
    expect_fire(first_shot[mode], first_misc[mode], direction);
    invoke(1);
    check();
    return 1;
}
static u32 test_burst_repeat(u32 row)
{
    static const s8 timers[3] = { 1, 2, 8 };
    u32 count = row % 3 + 1, t = (row / 3) % 3, facing = (row / 9) % 2, layer = row / 18;
    prepare(0, facing, layer, 0, 0);
    obj.unk6 = 4;
    obj.ext.main_48.unk82 = count;
    obj.ext.main_48.unk80 = timers[t];
    capture();
    if (count == 3) {
        expected_sentry_drone_burst.unk6 = 5;
        expected_sentry_drone_burst.ext.main_48.unk82 = 0;
        expected_sentry_drone_burst.ext.main_48.unk80 = 20;
    } else {
        expected_sentry_drone_burst.ext.main_48.unk80--;
        if (t == 0)
            expected_sentry_drone_burst.unk6 = 3;
    }
    invoke(0);
    check();
    return 1;
}
static u32 test_burst_end(u32 row)
{
    static const s8 timers[3] = { 0, 1, 20 };
    u32 t = row % 3, cycle = (row / 3) % 2, facing = (row / 6) % 2, layer = row / 12;
    prepare(0, facing, layer, 0, 0);
    obj.unk6 = 5;
    obj.ext.main_48.unk80 = timers[t];
    obj.ext.main_48.unk83 = cycle;
    capture();
    if (t)
        expected_sentry_drone_burst.ext.main_48.unk80--;
    else {
        expected_sentry_drone_burst.unk5 = cycle ? 5 : 3;
        expected_sentry_drone_burst.unk6 = 0;
        expected_sentry_drone_burst.ext.main_48.unk83 = cycle ? 0 : 1;
    }
    invoke(0);
    check();
    return 1;
}
static u32 test_spread_repeat(u32 row)
{
    static const u8 which[8] = { 0, 2, 1, 2, 0, 2, 1, 2 };
    u32 direction = (row % 16) * 2, count = row + 1, facing = 0;
    u8 choices[3];
    prepare(direction, facing, direction % 3, 0, 0);
    obj.unk5 = 5;
    obj.unk6 = 3;
    obj.ext.main_48.unk82 = count;
    capture();
    choices[0] = directions[direction].low;
    choices[1] = directions[direction].high;
    choices[2] = direction;
    expected_sentry_drone_burst.unk6 = count == 9 ? 4 : 1;
    if (count < 9)
        expected_sentry_drone_burst.ext.main_48.collision_result = choices[which[count - 1]];
    invoke(1);
    check();
    return 1;
}
static u32 test_spread_tail(u32 row)
{
    u32 end = row % 2, frame = (row / 2) % 2, facing = (row / 4) % 2, layer = row / 8;
    prepare(24, facing, layer, 0, 0);
    obj.unk5 = 5;
    obj.unk6 = end ? 5 : 4;
    install_animation(3, frame);
    capture();
    if (end) {
        expected_sentry_drone_burst.air_state = -1;
        expected_sentry_drone_burst.unk5 = 6;
        expected_sentry_drone_burst.unk6 = 0;
    } else
        expected_sentry_drone_burst.unk6 = 5;
    invoke(1);
    check();
    return 1;
}
static u32 test_movement(u32 row)
{
    static const u8 types[3] = { 0, 2, 0x80 };
    u32 kind = row % 3, phase = (row / 3) % 2, type = (row / 6) % 3, facing = (row / 18) % 2;
    u32 timer = (row / 36) % 2 + 1, frame = (row / 72) % 2, layer = row / 144;
    s32 speed = kind == 0 ? (facing ? 0x8000 : -0x8000) : kind == 1 && type != 1 ? (facing ? 0x40000 : -0x40000)
                                                                                 : 0;
    prepare(0, facing, layer, 0, 0);
    obj.unk2 = types[type];
    obj.unk5 = kind == 0 ? 2 : kind == 1 ? 3
                                         : 6;
    obj.unk6 = phase;
    obj.air_state = kind == 0 ? 1 : kind == 1 ? 0
                                              : -1;
    obj.ext.main_48.unk80 = timer;
    if (phase) {
        obj.x_speed = speed;
        obj.y_speed = kind == 2 ? 0x20000 : 0;
        obj.x_accel = obj.gravity = 0;
    }
    install_animation(kind == 2 ? 1 : 0, frame);
    capture();
    if (!phase) {
        expected_sentry_drone_burst.unk6 = 1;
        expected_sentry_drone_burst.x_speed = speed;
        expected_sentry_drone_burst.y_speed = kind == 2 ? 0x20000 : 0;
        expected_sentry_drone_burst.x_accel = expected_sentry_drone_burst.gravity = 0;
        expect_animation(kind == 2 ? 1 : 0, 0);
        if (kind != 2)
            expected_sentry_drone_burst.ext.main_48.unk80 = kind == 0 ? 48 : 60;
    } else {
        expect_tick();
        expected_sentry_drone_burst.x_pos.val += speed;
        expected_sentry_drone_burst.y_pos.val -= expected_sentry_drone_burst.y_speed;
        if (kind != 2) {
            expected_sentry_drone_burst.ext.main_48.unk80--;
            if (timer == 1) {
                expected_sentry_drone_burst.unk5 = kind == 0 ? 3 : 6;
                expected_sentry_drone_burst.unk6 = 0;
                if (kind == 1)
                    expected_sentry_drone_burst.air_state = -1;
            }
        }
    }
    if (kind == 0)
        sentry_drone_drift(&obj);
    else if (kind == 1)
        sentry_drone_dash(&obj);
    else
        sentry_drone_drop(&obj);
    check();
    return 1;
}
static u32 test_player_near(u32 row)
{
    static const s8 states[5] = { 3, 4, 5, 6, 3 };
    static const u8 hits[6] = { 0, 1, 1, 1, 1, 0 };
    u32 index = row % 4, edge = (row / 4) % 6, mode = (row / 24) % 5, facing = row / 120;
    s32 limit = 0x40 + index * 0x10;
    s32 offsets[6];
    offsets[0] = -limit - 1;
    offsets[1] = -limit;
    offsets[2] = -limit + 1;
    offsets[3] = limit - 1;
    offsets[4] = limit;
    offsets[5] = limit + 1;
    prepare(0, facing, index % 3, 0, 0);
    obj.unk5 = states[mode];
    obj.unk6 = 1;
    obj.air_state = mode == 4;
    obj.ext.main_0.index = index;
    g_Player.x_pos.val = obj.x_pos.val + offsets[edge] * 65536;
    capture();
    if ((mode == 0 || mode == 3) && hits[edge]) {
        expected_sentry_drone_burst.unk5 = 4;
        expected_sentry_drone_burst.unk6 = 0;
    }
    sentry_drone_check_player_near(&obj);
    check();
    return 1;
}
static u32 test_wait_player(u32 row)
{
    static const s16 distances[6] = { -176, -1, 0, 175, 176, 177 };
    u32 d = row % 6, facing = (row / 6) % 2, layer = row / 12;
    prepare(0, facing, layer, 0, 0);
    obj.state = 3;
    obj.unk5 = 3;
    g_Player.x_pos.val = obj.x_pos.val + distances[d] * 65536;
    capture();
    if (d >= 4) {
        expected_sentry_drone_burst.unk15 = 0x40;
        expected_sentry_drone_burst.state = 1;
        expected_sentry_drone_burst.unk5 = 3;
    }
    sentry_drone_update(&obj);
    check();
    return 1;
}
static u32 test_despawn(u32 row)
{
    u32 air = row % 2, ref = (row / 2) % 2, facing = (row / 4) % 2, layer = row / 8;
    prepare(24, facing, layer, 0, 0);
    obj.unk2 = air ? (s8)0x80 : 0;
    obj.state = 2;
    obj.unk6 = 5;
    if (!ref)
        obj.backref = 0;
    capture();
    expected_sentry_drone_burst.ext.main_48.unk80 = expected_sentry_drone_burst.ext.main_48.unk81 = expected_sentry_drone_burst.ext.main_48.unk82 = expected_sentry_drone_burst.ext.main_48.unk83 = 0;
    expected_sentry_drone_burst.ext.main_48.saved_unk5 = expected_sentry_drone_burst.ext.main_48.collision_result = expected_sentry_drone_burst.ext.main_48.unk86 = expected_sentry_drone_burst.ext.main_48.unk87 = expected_sentry_drone_burst.ext.main_48.unk88 = 0;
    expected_sentry_drone_burst.active = expected_sentry_drone_burst.id = expected_sentry_drone_burst.unk2 = expected_sentry_drone_burst.on_screen = expected_sentry_drone_burst.state = expected_sentry_drone_burst.unk5 = expected_sentry_drone_burst.unk6 = expected_sentry_drone_burst.unk7 = 0;
    if (!air && ref)
        backref_expected &= 0xFFFFFF70;
    sentry_drone_update(&obj);
    check();
    return 1;
}
static u32 test_burst_sequence(u32 row)
{
    static const s8 shot_slots[3] = { 0, 15, 31 }, misc_slots[3] = { 0, 31, 63 };
    u32 direction = row % 32, facing = (row / 32) % 2, cycle = row / 64, n, tick;
    prepare(direction, facing, direction % 3, 0, 0);
    for (n = 0; n < 3; n++) {
        struct ShotObj* s = &shot_objects[shot_slots[n]];
        struct MiscObj* m = &misc_objects[misc_slots[n]];
        c_test_zero_words((u32*)s, 2);
        c_test_zero_words((u32*)m, 2);
    }
    obj.unk6 = 1;
    obj.ext.main_48.unk80 = 1;
    obj.ext.main_48.unk82 = 0;
    obj.ext.main_48.unk83 = cycle;
    obj.ext.main_48.collision_result = direction ^ 16;
    capture();
    expect_aim(0, direction, facing);
    invoke(0);
    check_object();
    expected_sentry_drone_burst.unk6 = 3;
    invoke(0);
    check_object();
    for (n = 0; n < 3; n++) {
        expect_fire(shot_slots[n], misc_slots[n], direction);
        invoke(0);
        check_object();
        if (n < 2) {
            for (tick = 0; tick < 8; tick++) {
                expected_sentry_drone_burst.ext.main_48.unk80--;
                if (tick == 7)
                    expected_sentry_drone_burst.unk6 = 3;
                invoke(0);
                check_object();
            }
        }
    }
    expected_sentry_drone_burst.unk6 = 5;
    expected_sentry_drone_burst.ext.main_48.unk82 = 0;
    expected_sentry_drone_burst.ext.main_48.unk80 = 20;
    invoke(0);
    check_object();
    for (tick = 0; tick < 20; tick++) {
        expected_sentry_drone_burst.ext.main_48.unk80--;
        invoke(0);
        check_object();
    }
    expected_sentry_drone_burst.unk5 = cycle ? 5 : 3;
    expected_sentry_drone_burst.unk6 = 0;
    expected_sentry_drone_burst.ext.main_48.unk83 = cycle ? 0 : 1;
    invoke(0);
    check();
    return 1;
}
static u32 test_pool_retry(u32 row)
{
    u32 direction = (row % 4) * 8, facing = (row / 4) % 2, layer = row / 8;
    prepare(direction, facing, layer, 0, 0);
    c_test_zero_words((u32*)&misc_objects[0], 2);
    c_test_zero_words((u32*)&misc_objects[31], 2);
    obj.unk6 = 3;
    capture();
    expect_fire(-1, 0, direction);
    invoke(0);
    check_object();
    expect_fire(-1, 31, direction);
    invoke(0);
    check_object();
    c_test_zero_words((u32*)&shot_objects[15], 2);
    c_test_zero_words((u32*)&shots_expected[15], 2);
    expect_fire(15, -1, direction);
    invoke(0);
    check();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "sentry_drone_misc", 0, 0, COUNT(sentry_drone_misc_cases), test_sentry_drone_misc },
    { "sentry_drone_steps", NULL, sentry_drone_steps_cases_expected, COUNT(sentry_drone_steps_cases_expected), sentry_drone_steps_run },
    { "func_800681C4", 0, 0, 1, test_func_800681C4 },
    { "func_80068340", 0, 0, 1, test_func_80068340 },
    { "starts", 0, 0, 2, test_starts },
    { "compass", 0, 0, 66, test_compass },
    { "angle_boundaries", 0, 0, 192, test_boundaries },
    { "wait_event", 0, 0, 6, test_wait_event },
    { "fire_pools", 0, 0, 32, test_fire },
    { "spread_event_gate", 0, 0, 64, test_event_gate },
    { "burst_repeat", 0, 0, 3, test_burst_repeat },
    { "burst_end", 0, 0, 3, test_burst_end },
    { "spread_repeat", 0, 0, 9, test_spread_repeat },
    { "spread_tail", 0, 0, 2, test_spread_tail },
    { "movement", 0, 0, 42, test_movement },
    { "player_near", 0, 0, 100, test_player_near },
    { "wait_player", 0, 0, 6, test_wait_player },
    { "despawn", 0, 0, 4, test_despawn },
    { "burst_sequence", 0, 0, 96, test_burst_sequence },
    { "pool_retry", 0, 0, 4, test_pool_retry },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sentry_drone_misc_cases) + COUNT(sentry_drone_steps_cases_expected) + 1 + 1 + 2 + 66 + 192 + 6 + 32 + 64 + 3 + 3 + 9 + 2 + 42 + 100 + 6 + 4 + 96 + 4;
