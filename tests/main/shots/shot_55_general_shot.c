#include "test_runtime.h"
#include "main/shots/shot_55_general_shot.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "support/state_cases.h"
extern void* general_animations[46];
extern s8 general_shot_attack_boxes[][4];
extern s8 general_shot_boxes[4];
extern s8 general_shot_attack_box[4];
extern s8 general_shot_guard_box[4];
extern u8 D_8013B8DC[4];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 general_dust_animation_start_dust_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    u32 i, animation = mode == 0 ? 0x19 : 0x1C;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk2 = mode == 0 ? 6 : 7;
    obj.unk5 = 0;
    obj.timer = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (u32**)general_animations;
    set_animation(&obj, 0);
    obj.animation_step.fields.duration = 2;
    obj.animation_step.fields.relative_step = 0;
    before = obj;
    general_dust_start(&obj);
    before.unk5 = 1;
    before.timer = 0x19;
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = general_animations[animation];
    before.animation_step = *(union AnimationStep*)general_animations[animation];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u16)obj.timer << 8) | ((u32)obj.unk17 << 24) : obj.animation_step.packed;
}
static const u32 general_dust_animation_start_cases_expected[] = { 0x19001901u, C_TEST_STEP(0x47010001u), 0x1C001901u, C_TEST_STEP(0x51010001u) };
static u32 general_dust_animation_start_cases_row(u32 row)
{
    return general_dust_animation_start_dust_case(row / 2, row % 2);
}

static u32 general_dust_event_expiry_dust_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk2 = mode == 2 ? 7 : 6;
    obj.timer = mode == 0 ? 2 : 1;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, 25);
    if (mode != 3) {
        obj.animation_cursor = (void*)((u8*)general_animations[25] + 4);
        obj.animation_step = *(const union AnimationStep*)obj.animation_cursor;
        assert(obj.animation_step.packed == C_TEST_STEP(0x48010001));
    }
    expected = obj;
    expected.animation_cursor = (void*)((u8*)obj.animation_cursor + 4);
    expected.animation_step = *(const union AnimationStep*)expected.animation_cursor;
    if (mode != 3) {
        assert(expected.animation_step.packed == C_TEST_STEP(0x49FE0101));
        expected.animation_step.fields.event = 0;
        expected.unk50.data = (u8*)&general_shot_attack_boxes[2];
        expected.timer--;
        if (mode == 1 || mode == 2) {
            u32 end = mode == 1 ? 26 : 29;
            expected.unk50.data = NULL;
            expected.unk5 = 2;
            expected.unk17 = end;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = general_animations[end];
            expected.animation_step = *(union AnimationStep*)general_animations[end];
        }
    }
    general_dust_burst(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u16)obj.timer | ((u32)(u8)obj.unk5 << 16) | ((u32)obj.unk17 << 24);
}
static const u32 general_dust_event_expiry_cases_expected[] = { 0x19010001u, 0x1A020000u, 0x1D020000u, 0x19010001u };

static u32 wait_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    struct WeaponObj owner, owner_before;
    struct PlayerObj player_before;
    u32 i, orb = mode & 1;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk2 = orb ? 4 : 3;
    obj.unk5 = 3;
    obj.unk90.u.lo = 0x7777;
    obj.unk8A = mode == 3 ? 1 : 2;
    obj.unk15 = mode == 3 ? PLAYER_FACING_RIGHT : 0;
    D_8013E198[2] = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -32768;
    owner.x_pos.i.hi = mode == 2 ? 50 : 300;
    owner.active = 0x41;
    obj.unk7C = &owner;
    obj.animation_table = (u32**)general_animations;
    set_animation(&obj, 0);
    before = obj;
    owner_before = owner;
    player_before = g_Player;
    if (orb) {
        general_orb_aim(&obj);
        before.unk8A = mode == 3 ? 0 : 1;
        if (mode == 3) {
            before.unk5 = 4;
            before.x_vel.val = 5 * 65536;
            before.y_vel.val = 0;
        }
    } else {
        general_fist_approach(&obj);
        before.x_pos.val += 65536;
        before.y_pos.val += 32768;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_8013E198[2] == -1);
    return observation == 0 ? (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16) : (u8)obj.unk5 | ((u32)(u16)obj.unk8A << 8);
}
static const u32 general_projectile_wait_context_cases_expected[] = { 0xC80065u, 0x203u, 0xC80064u, 0x103u, 0xC80065u, 0x203u, 0xC80064u, 0x4u };
static u32 general_projectile_wait_context_cases_row(u32 row)
{
    return wait_case(row / 2, row % 2);
}

static const s8 subtypes[] = { 2, 9, 10, 11 };
static u32 thruster_case(u32 mode, u32 observation)
{
    struct ShotObj obj, before;
    struct MainObj parent, parent_before;
    u8 flags_before[4];
    u32 i, actual, animation;
    memset(&obj, 0, sizeof(obj));
    memset(&parent, 0, sizeof(parent));
    memset(D_8013B8DC, 0x27, sizeof(D_8013B8DC));
    parent.active = 0x41;
    parent.id = 75;
    parent.state = 1;
    parent.unk15 = mode == 0 ? PLAYER_FACING_RIGHT : 0;
    parent.unk40 = 0x1A00;
    parent.unk42 = 0xD234;
    parent.bg_offset = -1;
    parent.unk16 = VISUAL_SATURN_LAYER(5);
    parent.x_pos.val = 100 * 65536 + 0x1234;
    parent.y_pos.val = 200 * 65536 + 0x5678;
    parent.animation_table = (u32**)general_animations;
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk2 = subtypes[mode];
    obj.unk7C = (struct WeaponObj*)&parent;
    obj.timer = mode == 3 ? 5 : 0;
    obj.unk84.shot_55.x = 3;
    obj.unk84.shot_55.y = -4;
    before = obj;
    parent_before = parent;
    memcpy(flags_before, D_8013B8DC, sizeof(flags_before));
    func_800AC8C4(&obj);
    animation = mode == 0 ? 0xD : mode == 1 ? 0x1E
                                            : 0x1F;
    before.state = obj.state;
    before.unk40 = parent.unk40;
    before.unk42 = parent.unk42;
    before.bg_offset = parent.bg_offset;
    before.unk15 = parent.unk15;
    before.animation_table = (u32**)general_animations;
    before.unk3C = (void*)parent.sprite_frames;
    before.unk16 = obj.unk16;
    before.unk60 = obj.unk60;
    before.unk75 = obj.unk75;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.unk18 = obj.unk18;
    before.unk1C = obj.unk1C;
    before.x_vel = obj.x_vel;
    before.y_vel = obj.y_vel;
    before.timer = obj.timer;
    before.unk8A = obj.unk8A;
    before.unk84 = obj.unk84;
    before.animation_step = obj.animation_step;
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = general_animations[animation];
    before.unk50.data = mode == 0 ? (u8*)general_shot_attack_box : NULL;
    before.unk54 = mode == 0 ? (u8*)general_shot_guard_box : NULL;
    before.unk58.collision_bounds = mode == 0 ? D_801060F0 : NULL;
    before.unk68 = NULL;
    if (mode == 1)
        flags_before[0] = 0;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(parent) / 4; i++)
        assert(((u32*)&parent)[i] == ((u32*)&parent_before)[i]);
    for (i = 0; i < sizeof(flags_before); i++)
        assert(D_8013B8DC[i] == flags_before[i]);
    switch (observation) {
    case 0:
        actual = (u8)obj.state | ((u32)(u8)obj.unk16 << 8) | ((u32)(u8)obj.unk60 << 16) | ((u32)obj.unk75 << 24);
        break;
    case 1:
        actual = obj.x_pos.val;
        break;
    case 2:
        actual = obj.y_pos.val;
        break;
    case 3:
        actual = obj.x_vel.val;
        break;
    case 4:
        actual = obj.y_vel.val;
        break;
    case 5:
        actual = (u16)obj.timer | ((u32)(u16)obj.unk8A << 16);
        break;
    case 6:
        actual = C_TEST_STEP(obj.animation_step.packed);
        break;
    case 7:
        actual = obj.unk18.val;
        break;
    case 8:
        actual = obj.unk1C.val;
        break;
    default:
        actual = (u16)obj.unk84.shot_55.x | (u32)(u16)obj.unk84.shot_55.y << 16;
        break;
    }
    return actual;
}
#define LAYER_5 ((u32)(u8)VISUAL_SATURN_LAYER(5) << 8)
static const u32 general_thruster_init_cases_expected[] = { 0x1060002u | LAYER_5, 0xB41234u, 0xA05678u, 0x0u, 0x0u, 0x0u, 0x21000001u, 0x641234u, 0xC85678u, 0xA000B4u, 0x30002u | LAYER_5, 0x491234u, 0xAE5678u, 0x0u, 0x0u, 0x0u, 0x52010001u, 0x641234u, 0xC85678u, 0xFFFC0003u, 0x30002u | LAYER_5, 0x671234u, 0xC45678u, 0xFFFF0000u, 0x18000u, 0x1E0000u, 0x55010001u, 0x641234u, 0xC85678u, 0xFFFC0003u, 0x30002u | LAYER_5, 0x671234u, 0xC45678u, 0xFFFF0000u, 0xFFFE8000u, 0xF0005u, 0x55010001u, 0x641234u, 0xC85678u, 0xFFFC0003u };
static u32 general_thruster_init_cases_row(u32 row)
{
    return thruster_case(row / 10, row % 10);
}

static const u32 func_800AC8C4_expected[] = { 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_800AC8C4(u32 row)
{
    u32 observed_values[22];
    struct ShotObj obj;
    struct MainObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_8013B8DC, 0, sizeof(D_8013B8DC));
    obj.unk2 = -1;
    obj.unk7C = &child_0;
    func_800AC8C4(&obj);
    observed_values[0] = (u32)D_8013B8DC[0];
    observed_values[1] = (u32)obj.bg_offset;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.timer;
    observed_values[4] = (u32)obj.unk15;
    observed_values[5] = (u32)obj.unk16;
    observed_values[6] = (u32)obj.unk18.val;
    observed_values[7] = (u32)obj.unk1C.val;
    observed_values[8] = (u32)obj.unk40;
    observed_values[9] = (u32)obj.unk42;
    observed_values[10] = (u32)obj.unk60;
    observed_values[11] = (u32)obj.unk75;
    observed_values[12] = (u32)obj.unk84.shot_55.x;
    observed_values[13] = (u32)obj.unk84.shot_55.y;
    observed_values[14] = (u32)obj.unk84.value;
    observed_values[15] = (u32)obj.unk8A;
    observed_values[16] = (u32)obj.x_pos.i.hi;
    observed_values[17] = (u32)obj.x_pos.val;
    observed_values[18] = (u32)obj.x_vel.val;
    observed_values[19] = (u32)obj.y_pos.i.hi;
    observed_values[20] = (u32)obj.y_pos.val;
    observed_values[21] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, func_800AC8C4_expected, 22);
}

static const u32 inputs_0[2][2] = {
    { -1, 0 },
    { 0, 0 },
};
struct general_dust_end_case {
    u32 expected[1];
};
static const struct general_dust_end_case general_dust_end_cases[] = {
    { { 0u } },
    { { 1u } },
};
static u32 test_general_dust_end(u32 row)
{
    const struct general_dust_end_case* c = &general_dust_end_cases[row];
    u32 observed_values[1];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.animation_step.fields.relative_step = inputs_0[row][0];
    obj.state = inputs_0[row][1];
    general_dust_end(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, c->expected, 1);
}

static const u32 general_dust_start_expected[] = { 0u, 0u };
static u32 test_general_dust_start(u32 row)
{
    u32 observed_values[2];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.animation_step.fields.relative_step = -1;
    general_dust_start(&obj);
    observed_values[0] = (u32)obj.timer;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, general_dust_start_expected, 2);
}

static const u32 general_fist_approach_expected[] = { 1u, 0x3Cu, 0u };
static u32 test_general_fist_approach(u32 row)
{
    u32 observed_values[3];
    struct ShotObj obj;
    struct WeaponObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    obj.unk7C = &child_0;
    general_fist_approach(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk90.u.lo;
    observed_values[2] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, general_fist_approach_expected, 3);
}

static const u32 general_orb_aim_expected[] = { 1u, 0u, 0xFFFB0000u, 0u };
static u32 test_general_orb_aim(u32 row)
{
    u32 observed_values[4];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk8A = 1;
    general_orb_aim(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk8A;
    observed_values[2] = (u32)obj.x_vel.val;
    observed_values[3] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, general_orb_aim_expected, 4);
}

static const u32 general_orb_fly_expected[] = { 0u };
static u32 test_general_orb_fly(u32 row)
{
    u32 observed_values[1];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    general_orb_fly(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, general_orb_fly_expected, 1);
}

extern void* general_animations[46];
static u32 resource[4];
static u32 dust(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 face = row % 2, layer = row / 2, i;
    for (i = 0; i < 4; i++)
        resource[i] = 0x12340000 + i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 75;
    owner.state = 1;
    owner.animation_table = (const u8* const*)general_animations;
    owner.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    owner.bg_offset = layer;
    owner.unk16 = VISUAL_SATURN_LAYER(6);
    owner.unk40 = 9;
    owner.unk42 = 0x9234;
    owner.sprite_frames = (u8*)resource;
    owner.x_pos.val = 160 * 65536 + 0x1234;
    owner.y_pos.val = 120 * 65536 + 0x5678;
    owner_before = owner;
    obj.active = 0x41;
    obj.id = 55;
    obj.unk2 = 6;
    obj.unk7C = WEAPON_OBJECT(&owner);
    expected = obj;
    expected.state = 1;
    expected.unk40 = owner.unk40;
    expected.unk42 = owner.unk42;
    expected.animation_table = (u32**)general_animations;
    expected.unk3C = (u8*)resource;
    expected.unk15 = owner.unk15;
    expected.bg_offset = layer;
    expected.unk16 = VISUAL_SATURN_LAYER(5);
    expected.unk60 = 9;
    expected.x_pos = expected.unk18 = owner.x_pos;
    expected.y_pos = expected.unk1C = owner.y_pos;
    expected.unk17 = 24;
    expected.previous_animation_index = 255;
    expected.animation_cursor = general_animations[24];
    expected.animation_step.packed = C_TEST_STEP(0x3F010002);
    func_800AC8C4(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    for (i = 0; i < 4; i++)
        assert(resource[i] == 0x12340000 + i);
    return 1;
}

void general_orb_spread(struct ShotObj*);
void general_shot_orb_launcher(struct ShotObj*);
extern void* general_animations[46];
extern s8 general_shot_attack_boxes[][4];
static struct ShotObj expected_pool[32];
static u32 orbs(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 kind = row % 3, available = row / 3 % 3, face = row / 9, spawned = kind ? available != 0 : available, i;
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    D_8013E198[2] = -1;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i >= 32 - available ? 0 : 1;
    memcpy(expected_pool, shot_objects, sizeof(expected_pool));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 75;
    owner.state = 1;
    owner.hp = 48;
    owner.x_pos.i.hi = 160;
    owner.y_pos.i.hi = 120;
    owner.unk15 = face ? PLAYER_FACING_RIGHT : 0;
    owner.animation_table = (const u8* const*)general_animations;
    owner_before = owner;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 55;
    obj.state = 1;
    obj.unk2 = kind ? 10 : 9;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.x_pos.i.hi = face ? 187 : 133;
    obj.y_pos.i.hi = 94;
    obj.unk15 = owner.unk15;
    obj.timer = kind == 2;
    obj.animation_table = (u32**)general_animations;
    set_animation_frame(&obj, kind ? 31 : 30, kind ? 0 : 23);
    assert(obj.animation_step.packed == (kind ? C_TEST_STEP(0x55010001) : C_TEST_STEP(0x54000001)));
    expected = obj;
    expected.unk5 = 1;
    if (kind) {
        expected.unk17 = 32;
        expected.animation_cursor = general_animations[32];
        expected.animation_step.packed = C_TEST_STEP(0x58010001);
        expected.unk50.data = (u8*)general_shot_attack_boxes;
    } else
        expected.on_screen = 1;
    for (i = 0; i < spawned; i++) {
        struct ShotObj* s = &expected_pool[32 - available + i];
        s->active = 0x41;
        s->id = 55;
        s->unk2 = kind ? 10 : i + 10;
        s->timer = kind ? obj.timer + 1 : 0;
        s->unk7C = obj.unk7C;
        s->unk84.halves[0] = face ? 27 : -27;
        s->unk84.halves[1] = -26;
    }
    if (kind)
        general_orb_spread(&obj);
    else
        general_shot_orb_launcher(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(D_8013E198[2] == -1);
    return 1;
}

void general_shot_intro_prop(struct ShotObj*);
void general_shot_thruster(struct ShotObj*);
void general_fist_wait_launch(struct ShotObj*);
void general_fist_fly_to_row(struct ShotObj*);
void func_800ACF60(struct ShotObj*);
void general_fist_hold(struct ShotObj*);
void general_fist_turn(struct ShotObj*);
void general_fist_pause(struct ShotObj*);
void general_fist_sweep_turn(struct ShotObj*);
void general_fist_docked(struct ShotObj*);
void general_fist_follower_wait_launch(struct ShotObj*);
void general_fist_follower_launch(struct ShotObj*);
void general_fist_follower_fly_to_row(struct ShotObj*);
void general_shot_fist(struct ShotObj*);
void general_shot_ring(struct ShotObj*);
void general_shot_hit_flash(struct ShotObj*);
void general_shot_orb_launcher(struct ShotObj*);
void general_orb_spread(struct ShotObj*);
void general_orb_wait(struct ShotObj*);
void general_shot_orb(struct ShotObj*);
void general_shot_dust(struct ShotObj*);
#define ss state_room.shot
static struct MainObj gs_owner;
static struct ShotObj gs_leader;
#define GX(kind, step) (state_reset(step, 0, 0), memset(&gs_owner, 0, sizeof(gs_owner)), memset(weapon_objects, 0, sizeof(weapon_objects)), ss.active = 0x41, ss.state = 1, ss.unk2 = kind, ss.unk7C = (struct WeaponObj*)&gs_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60, gs_owner.x_pos.i.hi = 0x80, gs_owner.y_pos.i.hi = 0x60, SPIKE_IMMUNE_SET(g_Player, 1))
#define GT() (state_extra = (u8)ss.timer | (u8)ss.unk8A << 8 | (u8)ss.unk90.i.lo << 16 | (u32)ss.unk17 << 24)
static void gs_init(u32 kind, u8 facing, s16 timer)
{
    GX(kind, 0);
    ss.state = 0;
    ss.timer = timer;
    ss.unk84.shot_55.x = 4;
    ss.unk84.shot_55.y = -2;
    gs_owner.x_pos.i.hi = 0x100;
    gs_owner.y_pos.i.hi = 0x80;
    gs_owner.unk42 = 0x9234;
    gs_owner.unk15 = facing;
    gs_owner.animation_table = (void*)state_table;
    func_800AC8C4(&ss);
    state_extra = ss.unk60 | ss.unk75 << 4 | ss.unk17 << 8 | (u8)ss.timer << 16 | (u32)(u8)ss.unk8A << 24;
}
static void gs_init_fist_follower(void) { gs_init(3, 0, 0); }
static void gs_init_ring_left(void) { gs_init(4, 0, 0); }
static void gs_init_ring_right(void) { gs_init(5, 0, 0); }
static void gs_init_dust_right(void) { gs_init(7, 0, 0); }
static void gs_init_hit_flash(void) { gs_init(8, 0, 0); }
static void gs_init_fist_leader_left(void) { gs_init(2, 0, 0); }
static void gs_init_orb_launcher_right(void) { gs_init(9, PLAYER_FACING_RIGHT, 0); }
static void gs_init_orb_low_follow_up(void) { gs_init(10, PLAYER_FACING_RIGHT, 5); }
static void gs_init_orb_high_first(void) { gs_init(11, PLAYER_FACING_RIGHT, 0); }
static void gs_prop_wait(void) { GX(1, 0), general_shot_intro_prop(&ss), GT(); }
static void gs_prop_break(void) { GX(1, 1), general_shot_intro_prop(&ss), GT(); }
static void gs_thruster(u8 facing, s16 timer)
{
    GX(0, 0);
    gs_owner.x_pos.i.hi = 0x100;
    gs_owner.y_pos.i.hi = 0x80;
    gs_owner.unk15 = facing;
    ss.unk84.halves[0] = 4;
    ss.unk84.halves[1] = -2;
    ss.timer = timer;
    general_shot_thruster(&ss);
    GT();
}
static void gs_thruster_firing(void) { gs_thruster(0, 1); }
static void gs_fist_launch_signal(void) { GX(3, 0), gs_owner.unk6 = 3, general_shot_fist(&ss), GT(); }
static void gs_fist_wait(void) { GX(3, 0), general_fist_wait_launch(&ss), GT(); }
#define LAUNCH(rel, facing, py) (GX(3, 1), ss.animation_step.fields.relative_step = rel, ss.unk15 = facing, ss.timer = 9, g_Player.y_pos.i.hi = py, func_800ACDE4(&ss), GT())
static void gs_fist_launch_windup(void)
{
    LAUNCH(1, 0, 0x200);
}
static void gs_fist_launch_row_0(void) { LAUNCH(0, PLAYER_FACING_RIGHT, 0x200); }
static void gs_fist_launch_row_1(void) { LAUNCH(0, 0, 0x220); }
static void gs_fist_launch_row_2(void) { LAUNCH(0, PLAYER_FACING_RIGHT, 0x250); }
static void gs_fist_launch_row_3(void) { LAUNCH(0, PLAYER_FACING_RIGHT, 0x280); }
#define ROW(kind, step, x, y, facing) (GX(kind, step), ss.x_pos.i.hi = x, ss.y_pos.i.hi = y, ss.unk15 = facing, gs_leader.timer = 0, ss.unk8C.object = (struct ObjectHeader*)&gs_leader)
static void gs_fist_row_reached_right(void)
{
    ROW(3, 2, 0xE20, 0x208, PLAYER_FACING_RIGHT), general_fist_fly_to_row(&ss), GT();
}
static void gs_fist_row_reached_left(void) { ROW(3, 2, 0xE20, 0x208, 0), general_fist_fly_to_row(&ss), GT(); }
static void gs_fist_row_flying(void) { ROW(3, 2, 0xD00, 0x208, 0), general_fist_fly_to_row(&ss), GT(); }
static void gs_fist_sweep_wall(void) { GX(3, 3), ss.unk15 = PLAYER_FACING_RIGHT, state_terrain(0x38), func_800ACF60(&ss), GT(); }
static void gs_fist_sweep_open(void) { GX(3, 3), ss.x_vel.val = -0x18000, state_terrain(0), func_800ACF60(&ss), GT(); }
#define TIMED(kind, step, count, run) (GX(kind, step), ss.unk90.i.lo = count, run(&ss), GT())
static void gs_fist_hold(void)
{
    TIMED(3, 4, 2, general_fist_hold);
}
static void gs_fist_hold_done_follower(void) { TIMED(3, 4, 1, general_fist_hold); }
static void gs_fist_hold_done_leader(void) { TIMED(2, 4, 1, general_fist_hold); }
#define TURN(kind, step, ev, rs, face, count, run) (GX(kind, step), ss.animation_step.fields.event = ev, ss.animation_step.fields.relative_step = rs, ss.unk15 = face, ss.unk8A = count, run(&ss), GT())
static void gs_fist_turn_flip(void)
{
    TURN(3, 5, 1, 0, 0, 0, general_fist_turn);
}
static void gs_fist_turn_flip_back(void) { TURN(3, 5, 1, 1, PLAYER_FACING_RIGHT, 0, general_fist_turn); }
static void gs_fist_turn_done_leader(void) { TURN(2, 5, 0, 0, 0, 0, general_fist_turn); }
static void gs_fist_pause(void) { TIMED(3, 7, 2, general_fist_pause); }
static void gs_fist_pause_done_follower(void) { TIMED(3, 7, 1, general_fist_pause); }
static void gs_fist_pause_done_leader(void) { TIMED(2, 7, 1, general_fist_pause); }
static void gs_fist_sweep_turn_flip(void) { TURN(3, 8, 1, 1, 0, 0, general_fist_sweep_turn); }
static void gs_fist_sweep_turn_dock_follower(void) { TURN(3, 8, 0, 0, 0, 1, general_fist_sweep_turn), state_extra |= gs_owner.unk6 << 16; }
static void gs_fist_sweep_turn_dock_leader(void) { TURN(2, 8, 1, 0, PLAYER_FACING_RIGHT, 1, general_fist_sweep_turn); }
static void gs_fist_sweep_turn_again_follower(void) { TURN(3, 8, 0, 0, 0, 0, general_fist_sweep_turn); }
static void gs_fist_sweep_turn_again_leader(void) { TURN(2, 8, 0, 0, 0, 0, general_fist_sweep_turn); }
#define RETURN(kind, px) (GX(kind, 9), ss.x_pos.i.hi = px, ss.y_pos.i.hi = 0x80, ss.unk84.shot_55.x = 0x100, ss.unk84.shot_55.y = 0x80, func_800AD338(&ss), GT())
static void gs_fist_return_follower(void)
{
    RETURN(3, 0x102);
}
static void gs_fist_return_leader(void) { RETURN(2, 0x102); }
static void gs_fist_returning(void) { RETURN(3, 0x120); }
static void gs_fist_docked(void) { GX(3, 10), general_fist_docked(&ss), GT(); }
static void gs_fist_docking(void) { GX(3, 10), ss.animation_step.fields.relative_step = 1, general_fist_docked(&ss), GT(); }
static void gs_follower_launch_signal(void) { ROW(2, 0, 0x80, 0x60, 0), gs_leader.unk5 = 3, general_shot_fist(&ss), GT(); }
static void gs_follower_wait(void) { ROW(2, 0, 0x80, 0x60, 0), gs_leader.unk5 = 0, general_fist_follower_wait_launch(&ss), GT(); }
static void gs_follower_launch(void) { GX(2, 1), general_fist_follower_launch(&ss), GT(); }
static void gs_follower_launch_windup(void) { GX(2, 1), ss.animation_step.fields.relative_step = 1, general_fist_follower_launch(&ss), GT(); }
static void gs_follower_row_reached_right(void) { ROW(2, 2, 0xE20, 0x268, PLAYER_FACING_RIGHT), general_fist_follower_fly_to_row(&ss), GT(); }
static void gs_follower_row_reached_left(void) { ROW(2, 2, 0xE20, 0x268, 0), general_fist_follower_fly_to_row(&ss), GT(); }
static void gs_follower_row_flying(void) { ROW(2, 2, 0xE20, 0x300, 0), general_fist_follower_fly_to_row(&ss), GT(); }
#define RING(kind, facing, count, px, py) (GX(kind, 0), gs_owner.unk42 = 0x8005, ss.unk15 = facing, ss.timer = count, ss.x_pos.i.hi = 0x100, ss.y_pos.i.hi = 0x100, g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, general_shot_ring(&ss), GT())
static void gs_ring_charge(void)
{
    RING(4, 0, 2, 0, 0);
}
static void gs_ring_throw_left_hand(void) { RING(4, PLAYER_FACING_RIGHT, 1, 0x200, 0xD8); }
static void gs_ring_throw_right_hand(void) { RING(5, 0, 1, 0x10D, 0x200); }
static void gs_ring_fly(void) { GX(4, 1), general_shot_ring(&ss), GT(); }
static void gs_ring_gone(void) { GX(4, 1), ss.x_pos.i.hi = 0x200, general_shot_ring(&ss), GT(); }
static void gs_hit_flash(u8 active)
{
    GX(8, 0);
    gs_owner.x_pos.val = 0x1000000;
    gs_owner.y_pos.val = 0x800000;
    gs_owner.ext.main_75.hit_active = active;
    general_shot_hit_flash(&ss);
    GT();
}
static void gs_hit_flash_follow(void) { gs_hit_flash(1); }
static void gs_hit_flash_end(void) { gs_hit_flash(0); }
static void gs_orb_launcher_done(void) { GX(9, 1), general_shot_orb_launcher(&ss), GT(); }
static void gs_orb_launcher_opening(void) { GX(9, 0), ss.animation_step.fields.relative_step = 1, general_shot_orb_launcher(&ss), GT(); }
static void gs_orb_spreading(void) { GX(10, 0), ss.unk8A = 3, ss.x_vel.val = 0x10000, general_orb_spread(&ss), GT(); }
static void gs_orb_spread_last(void) { GX(10, 0), ss.timer = 2, general_orb_spread(&ss), GT(), state_extra |= gs_owner.ext.main_75.orbs_ready << 16; }
static void gs_orb_wait_ready(void) { GX(10, 1), gs_owner.ext.main_75.orbs_ready = 1, general_shot_orb(&ss), GT(); }
static void gs_orb_wait(void) { GX(10, 1), general_orb_wait(&ss), GT(); }
static void gs_orb_fly_gone(void) { GX(10, 3), ss.x_pos.i.hi = 0x200, general_orb_fly(&ss), GT(); }
static void gs_run_owner_gone(void) { GX(0, 0), gs_owner.state = 2, general_shot_update(&ss), GT(); }
static void gs_run(void) { GX(0, 0), gs_owner.state = 1, general_shot_update(&ss), GT(); }
static void gs_despawn(void) { GX(0, 0), ss.state = 2, general_shot_update(&ss), GT(); }
static void gs_dust_settled(void) { GX(6, 2), general_shot_dust(&ss), GT(); }

static void (*const general_shot_states_cases[])(void) = {
    gs_init_fist_follower,
    gs_init_ring_left,
    gs_init_ring_right,
    gs_init_dust_right,
    gs_init_hit_flash,
    gs_init_fist_leader_left,
    gs_init_orb_launcher_right,
    gs_init_orb_low_follow_up,
    gs_init_orb_high_first,
    gs_prop_wait,
    gs_prop_break,
    gs_thruster_firing,
    gs_fist_launch_signal,
    gs_fist_wait,
    gs_fist_launch_windup,
    gs_fist_launch_row_0,
    gs_fist_launch_row_1,
    gs_fist_launch_row_2,
    gs_fist_launch_row_3,
    gs_fist_row_reached_right,
    gs_fist_row_reached_left,
    gs_fist_row_flying,
    gs_fist_sweep_wall,
    gs_fist_sweep_open,
    gs_fist_hold,
    gs_fist_hold_done_follower,
    gs_fist_hold_done_leader,
    gs_fist_turn_flip,
    gs_fist_turn_flip_back,
    gs_fist_turn_done_leader,
    gs_fist_pause,
    gs_fist_pause_done_follower,
    gs_fist_pause_done_leader,
    gs_fist_sweep_turn_flip,
    gs_fist_sweep_turn_dock_follower,
    gs_fist_sweep_turn_dock_leader,
    gs_fist_sweep_turn_again_follower,
    gs_fist_sweep_turn_again_leader,
    gs_fist_return_follower,
    gs_fist_return_leader,
    gs_fist_returning,
    gs_fist_docked,
    gs_fist_docking,
    gs_follower_launch_signal,
    gs_follower_wait,
    gs_follower_launch,
    gs_follower_launch_windup,
    gs_follower_row_reached_right,
    gs_follower_row_reached_left,
    gs_follower_row_flying,
    gs_ring_charge,
    gs_ring_throw_left_hand,
    gs_ring_throw_right_hand,
    gs_ring_fly,
    gs_ring_gone,
    gs_hit_flash_follow,
    gs_hit_flash_end,
    gs_orb_launcher_done,
    gs_orb_launcher_opening,
    gs_orb_spreading,
    gs_orb_spread_last,
    gs_orb_wait_ready,
    gs_orb_wait,
    gs_orb_fly_gone,
    gs_run_owner_gone,
    gs_run,
    gs_despawn,
    gs_dust_settled,
};
static const u32 general_shot_states_expected[] = {
    1u,
    0xFF000341u,
    0x1000000u,
    0x580000u,
    0u,
    0u,
    0u,
    0x59234u,
    0x1216u,
    0u,
    1u,
    0xFF000441u,
    0x1000000u,
    0x800000u,
    0u,
    0u,
    0u,
    0x59234u,
    0x202106u,
    0u,
    1u,
    0xFF000541u,
    0x1000000u,
    0x800000u,
    0u,
    0u,
    0u,
    0x59234u,
    0x202206u,
    0u,
    1u,
    0xFF000741u,
    0x1000000u,
    0x800000u,
    0u,
    0u,
    0u,
    0x59234u,
    0x1B03u,
    0u,
    1u,
    0xFF000841u,
    0x1000000u,
    0x800000u,
    0u,
    0u,
    0u,
    0x51234u,
    0x2603u,
    0u,
    1u,
    0xFF000241u,
    0xB00000u,
    0x580000u,
    0u,
    0u,
    0u,
    0x59234u,
    0xD16u,
    0u,
    1u,
    0xFF400941u,
    0x11B0000u,
    0x660000u,
    0u,
    0u,
    0u,
    0x59234u,
    0x1E03u,
    0u,
    1u,
    0xFF400A41u,
    0x1040000u,
    0x7E0000u,
    0x10000u,
    0x18000u,
    0u,
    0x59234u,
    0x0F051F03u,
    0u,
    1u,
    0xFF400B41u,
    0x1040000u,
    0x7E0000u,
    0x10000u,
    0xFFFE8000u,
    0u,
    0x59234u,
    0x1E001F03u,
    0u,
    1u,
    0x141u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x102u,
    0x141u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0x41000000u,
    1u,
    0x41u,
    0x1040000u,
    0x7E0000u,
    0u,
    0u,
    0u,
    0x40000u,
    1u,
    0u,
    0x101u,
    0xFF000341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x13000000u,
    0u,
    1u,
    0x341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x101u,
    0x341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    9u,
    0u,
    0x201u,
    0xFF400341u,
    0x800000u,
    0x600000u,
    0x40000u,
    0u,
    0u,
    0x50000u,
    0x14000000u,
    0u,
    0x201u,
    0xFF000341u,
    0x800000u,
    0x600000u,
    0xFFFC0000u,
    0u,
    0u,
    0x50000u,
    0x14000001u,
    0u,
    0x201u,
    0xFF400341u,
    0x800000u,
    0x600000u,
    0x40000u,
    0u,
    0u,
    0x50000u,
    0x14000002u,
    0u,
    0x201u,
    0xFF400341u,
    0x800000u,
    0x600000u,
    0x40000u,
    0u,
    0u,
    0x50000u,
    0x14000003u,
    0u,
    0x301u,
    0x400341u,
    0xE218000u,
    0x2080000u,
    0x18000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x301u,
    0x341u,
    0xE1E8000u,
    0x2080000u,
    0xFFFE8000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x201u,
    0x341u,
    0xD040000u,
    0x2080000u,
    0x40000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x401u,
    0x400341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x3C0000u,
    0u,
    0x301u,
    0x341u,
    0x7E8000u,
    0x600000u,
    0xFFFE8000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x401u,
    0x341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x10000u,
    0u,
    0x501u,
    0xFF000341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x16000000u,
    0u,
    0x501u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x11000000u,
    0u,
    0x601u,
    0xFF400341u,
    0x800000u,
    0x600000u,
    0x18000u,
    0u,
    0u,
    0x50000u,
    0x0F000000u,
    0u,
    0x501u,
    0x341u,
    0x800000u,
    0x600000u,
    0xFFFE8000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x601u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x14000000u,
    0u,
    0x701u,
    0x341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x10000u,
    0u,
    0x801u,
    0xFF000341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x11000000u,
    0u,
    0x801u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x16000000u,
    0u,
    0x801u,
    0x400341u,
    0x800000u,
    0x600000u,
    0x18000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x901u,
    0xFF000341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x15010200u,
    0u,
    0x901u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0xFFFE8000u,
    0u,
    0u,
    0x50000u,
    0x10000200u,
    0u,
    0x301u,
    0xFF000341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x14000100u,
    0u,
    0x301u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x0F000100u,
    0u,
    0xA01u,
    0xFF000341u,
    0xFE0000u,
    0x800000u,
    0xFFFC0000u,
    0u,
    0u,
    0x50000u,
    0x13000000u,
    0u,
    0xA01u,
    0xFF000241u,
    0xFE0000u,
    0x800000u,
    0xFFFC0000u,
    0u,
    0u,
    0x50000u,
    0x0E000000u,
    0u,
    0x901u,
    0x341u,
    0x11C0000u,
    0x800000u,
    0xFFFC0000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0xA01u,
    0x341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x80u,
    0u,
    0xA01u,
    0x341u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x101u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x0E000000u,
    0u,
    1u,
    0x241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x201u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x0F000000u,
    0u,
    0x101u,
    0x241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x301u,
    0x400241u,
    0xE218000u,
    0x2680000u,
    0x18000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x301u,
    0x241u,
    0xE1E8000u,
    0x2680000u,
    0xFFFE8000u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x201u,
    0x241u,
    0xE200000u,
    0x2FC0000u,
    0u,
    0x40000u,
    0u,
    0x40000u,
    0u,
    0u,
    1u,
    0x441u,
    0x1000000u,
    0x1000000u,
    0u,
    0u,
    0u,
    0x48005u,
    1u,
    0u,
    0x101u,
    0xFF400441u,
    0x13F0000u,
    0xD80000u,
    0x30000u,
    0u,
    0u,
    0x50005u,
    0x23000000u,
    0u,
    0x101u,
    0xFF000541u,
    0x10D0000u,
    0xD80000u,
    0u,
    0xFFFD0000u,
    0u,
    0x50005u,
    0x23000000u,
    0u,
    0x101u,
    0x441u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x102u,
    0x441u,
    0x2000000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    1u,
    0x841u,
    0x1000000u,
    0x800000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    2u,
    0x841u,
    0x1000000u,
    0x800000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x102u,
    0x941u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    1u,
    0x941u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    1u,
    0xA41u,
    0x810000u,
    0x600000u,
    0x10000u,
    0u,
    0u,
    0x40000u,
    0x200u,
    0u,
    0x101u,
    0xFF000A41u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x20010002u,
    0u,
    0x201u,
    0xA41u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0x1400u,
    0u,
    0x101u,
    0xA41u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0x302u,
    0xA41u,
    0x2000000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    2u,
    0x41u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    1u,
    0x41u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0u,
    0u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x202u,
    0x641u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
};
static u32 test_general_shot_states(u32 row)
{
    return object_run(general_shot_states_cases[row], row, &general_shot_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "general_shot_states", 0, 0, COUNT(general_shot_states_cases), test_general_shot_states },
    { "general_dust_animation_start", NULL, general_dust_animation_start_cases_expected, COUNT(general_dust_animation_start_cases_expected), general_dust_animation_start_cases_row },
    { "general_dust_event_expiry", NULL, general_dust_event_expiry_cases_expected, COUNT(general_dust_event_expiry_cases_expected), general_dust_event_expiry_dust_case },
    { "general_projectile_wait_context", NULL, general_projectile_wait_context_cases_expected, COUNT(general_projectile_wait_context_cases_expected), general_projectile_wait_context_cases_row },
    { "general_thruster_init", NULL, general_thruster_init_cases_expected, COUNT(general_thruster_init_cases_expected), general_thruster_init_cases_row },
    { "func_800AC8C4", 0, 0, 1, test_func_800AC8C4 },
    { "general_dust_end", 0, 0, 2, test_general_dust_end },
    { "general_dust_start", 0, 0, 1, test_general_dust_start },
    { "general_fist_approach", 0, 0, 1, test_general_fist_approach },
    { "general_orb_aim", 0, 0, 1, test_general_orb_aim },
    { "general_orb_fly", 0, 0, 1, test_general_orb_fly },
    { "actual_slam_dust_mode_inherits_general_resources", NULL, NULL, 6, dust },
    { "General_own_launcher_terminal_and_orb_chain_full_partial_shot_slots", NULL, NULL, 18, orbs },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(general_shot_states_cases) + COUNT(general_dust_animation_start_cases_expected) + COUNT(general_dust_event_expiry_cases_expected) + COUNT(general_projectile_wait_context_cases_expected) + COUNT(general_thruster_init_cases_expected) + 1 + 2 + 1 + 1 + 1 + 1 + 6 + 18;
