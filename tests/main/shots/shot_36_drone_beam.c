#include "test_runtime.h"
#include "main/shots/shot_36_drone_beam.h"

struct func_800A3A4C_case {
    u32 value, unk2, v_0_x_pos_hi, unk15, child_0_x_pos_hi;
    u32 expected[3];
};
static const struct func_800A3A4C_case func_800A3A4C_cases[] = {
    { 1, 0, 31421, 0, 36864, { 1u, 0u, 0xFFFFA633u } },
    { 1, 0, 512, 255, 65535, { 1u, 0u, 0x110u } },
    { 1, -1, -26624, 255, 16, { 1u, 0u, 0x6830u } },
    { 70, -1, -8192, 0, 1024, { 1u, 0x45u, 0xFFFFDFF0u } },
};
static u32 test_func_800A3A4C(u32 row)
{
    const struct func_800A3A4C_case* c = &func_800A3A4C_cases[row];
    u32 observed_values[3];
    struct ShotObj obj;
    struct WeaponObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    obj.unk84.value = c->value;
    obj.unk2 = c->unk2;
    background_objects[0].x_pos.i.hi = c->v_0_x_pos_hi;
    obj.unk15 = c->unk15;
    child_0.x_pos.u.hi = c->child_0_x_pos_hi;
    obj.unk7C = &child_0;
    func_800A3A4C(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk84.value;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}


#include "support/state_cases.h"
static struct WeaponObj beam_owner;
#define ss state_room.shot
#define BEAM(st, kind, face, timer, setup) (state_reset(0, 0, 0), memset(&beam_owner, 0, sizeof(beam_owner)), beam_owner.active = 1, beam_owner.state = 1, beam_owner.x_pos.i.hi = 0x200, beam_owner.y_pos.i.hi = 0x80, background_objects[0].x_pos.i.hi = 0x180, ss.active = 1, ss.state = st, ss.unk2 = kind, ss.unk15 = face, ss.unk7C = &beam_owner, ss.unk84.value = timer, ss.x_pos.i.hi = 0x123, setup, drone_beam_update(&ss), state_extra = ss.unk84.value | (u32)ss.unk17 << 8 | (u32)(ss.unk50.data == NULL ? 0xFF : ss.unk50.data[0]) << 16)
static void db_init_near_left(void) { BEAM(0, 0, 0, 0, 0); }
static void db_init_near_right(void) { BEAM(0, 0, PLAYER_FACING_RIGHT, 0, 0); }
static void db_init_far_left(void) { BEAM(0, 1, 0, 0, 0); }
static void db_init_far_right(void) { BEAM(0, 1, PLAYER_FACING_RIGHT, 0, 0); }
static void db_charging(void) { BEAM(1, 0, 0, 0x6E, 0); }
static void db_widen_near(void) { BEAM(1, 0, 0, 0x46, 0); }
static void db_fade_near(void) { BEAM(1, 0, 0, 0x19, 0); }
static void db_fade_far(void) { BEAM(1, 1, 0, 0x19, 0); }
static void db_owner_leaving(void) { BEAM(1, 0, 0, 0x30, beam_owner.state = 2); }
static void (*const drone_beam_states_cases[])(void) = {
    db_init_near_left,
    db_init_near_right,
    db_init_far_left,
    db_init_far_right,
    db_charging,
    db_widen_near,
    db_fade_near,
    db_fade_far,
    db_owner_leaving,
};
static const u32 drone_beam_states_expected[] = {
    0x1u, 0xFF000001u, 0x1700000u, 0x7D0000u, 0u, 0u, 0u, 0x50000u, 0x80036Eu, 0u,
    0x1u, 0xFF400001u, 0x2900000u, 0x7D0000u, 0u, 0u, 0u, 0x50000u, 0x80036Eu, 0u,
    0x1u, 0xFF000101u, 0x700000u, 0x7D0000u, 0u, 0u, 0u, 0x50000u, 0x80046Eu, 0u,
    0x1u, 0xFF400101u, 0x3900000u, 0x7D0000u, 0u, 0u, 0u, 0x50000u, 0x80046Eu, 0u,
    0x1u, 0x1u, 0x1230000u, 0u, 0u, 0u, 0u, 0x40000u, 0xFF006Du, 0u,
    0x1u, 0x1u, 0x1230000u, 0u, 0u, 0u, 0u, 0x40000u, 0x800045u, 0u,
    0x1u, 0xFF000001u, 0x1230000u, 0u, 0u, 0u, 0u, 0x50000u, 0xFF0518u, 0u,
    0x1u, 0xFF000101u, 0x1230000u, 0u, 0u, 0u, 0u, 0x50000u, 0xFF0618u, 0u,
    0x2u, 0x1u, 0x1230000u, 0u, 0u, 0u, 0u, 0x40000u, 0xFF002Fu, 0u,
};
static u32 test_drone_beam_states(u32 row)
{
    return object_run(drone_beam_states_cases[row], row, &drone_beam_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "func_800A3A4C", 0, 0, 4, test_func_800A3A4C },
    { "drone_beam_states", 0, 0, COUNT(drone_beam_states_cases), test_drone_beam_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4 + COUNT(drone_beam_states_cases);
