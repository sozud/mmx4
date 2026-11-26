#include "test_runtime.h"
#include "main/shots/shot_20_cannon_blast.h"

struct func_8009D048_case {
    u32 value, unk2, v_0_x_pos_hi, child_0_x_pos_hi;
    u32 expected[3];
};
static const struct func_8009D048_case func_8009D048_cases[] = {
    { 1, -1, 0, 32940, { 1u, 0u, 0x181u } },
    { 70, 0, -8192, 1024, { 1u, 0x45u, 0xFFFFE129u } },
};
static u32 test_func_8009D048(u32 row)
{
    const struct func_8009D048_case* c = &func_8009D048_cases[row];
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
    child_0.x_pos.u.hi = c->child_0_x_pos_hi;
    obj.unk7C = &child_0;
    func_8009D048(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk84.value;
    observed_values[2] = (u32)obj.x_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

#include "support/state_cases.h"
static struct WeaponObj blast_owner;
#define ss state_room.shot
#define BLAST(st, kind, timer, setup) (state_reset(0, 0, 0), memset(&blast_owner, 0, sizeof(blast_owner)), blast_owner.active = 1, blast_owner.state = 1, blast_owner.x_pos.i.hi = 0x200, blast_owner.y_pos.i.hi = 0x80, background_objects[0].x_pos.i.hi = 0x180, ss.active = 1, ss.state = st, ss.unk2 = kind, ss.unk7C = &blast_owner, ss.unk84.value = timer, ss.x_pos.i.hi = 0x123, setup, cannon_blast_update(&ss), state_extra = ss.unk84.value | (u32)ss.unk17 << 8 | (u32)(ss.unk50.data == NULL ? 0xFF : ss.unk50.data[0]) << 16)
static void cb_init_short(void)
{
    BLAST(0, 0, 0, 0);
}
static void cb_init_long(void) { BLAST(0, 1, 0, 0); }
static void cb_charging(void) { BLAST(1, 0, 0x6E, 0); }
static void cb_widen_long(void) { BLAST(1, 1, 0x46, 0); }
static void cb_fade_short(void) { BLAST(1, 0, 0x19, 0); }
static void cb_fade_long(void) { BLAST(1, 1, 0x19, 0); }
static void cb_owner_leaving(void) { BLAST(1, 0, 0x30, blast_owner.state = 2); }

static void (*const cb_cases[])(void) = {
    cb_init_short,
    cb_init_long,
    cb_charging,
    cb_widen_long,
    cb_fade_short,
    cb_fade_long,
    cb_owner_leaving,
};
static const u32 cb_expected[] = {
    0x1u,
    0xFF000001u,
    0x1890000u,
    0x800000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x80036Eu,
    0u,
    0x1u,
    0xFF000101u,
    0x890000u,
    0x800000u,
    0u,
    0u,
    0u,
    0x50000u,
    0x80046Eu,
    0u,
    0x1u,
    0x1u,
    0x1230000u,
    0u,
    0u,
    0u,
    0u,
    0x40000u,
    0xFF006Du,
    0u,
    0x1u,
    0x101u,
    0x1230000u,
    0u,
    0u,
    0u,
    0u,
    0x40000u,
    0x800045u,
    0u,
    0x1u,
    0xFF000001u,
    0x1230000u,
    0u,
    0u,
    0u,
    0u,
    0x50000u,
    0xFF0B18u,
    0u,
    0x1u,
    0xFF000101u,
    0x1230000u,
    0u,
    0u,
    0u,
    0u,
    0x50000u,
    0xFF0C18u,
    0u,
    0x2u,
    0x1u,
    0x1230000u,
    0u,
    0u,
    0u,
    0u,
    0x40000u,
    0xFF002Fu,
    0u,
};
static u32 test_cb(u32 row)
{
    return object_run(cb_cases[row], row, &cb_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "cannon_blast_states", 0, 0, COUNT(cb_cases), test_cb },
    { "func_8009D048", 0, 0, 2, test_func_8009D048 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + COUNT(cb_cases);
