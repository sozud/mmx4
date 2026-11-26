#include "test_runtime.h"
#include "main/items/item_22_layout_gate.h"
#include "support/state_cases.h"

#include "support/pool_full.h"
void layout_gate_despawn(struct ItemObj*);
static u32 pool_full_layout_gate_spawn_alarm(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    layout_gate_spawn_alarm(&pf_item);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_layout_gate_spawn_alarm,
};
static const u32 pool_full_cases_expected[] = { 0x50000u };

#define LAYOUT_CASE(name, subtype, tile)                     \
    static u32 name(void)                                    \
    {                                                        \
        struct ItemObj obj;                                  \
        u32 actual;                                          \
        memset(&obj, 0, sizeof(obj));                        \
        obj.unk2 = subtype;                                  \
        obj.tail_ext.unk1.unk84.bytes[0] = 0xFF;             \
        layout_width = 0;                                    \
        D_80141BE8[6] = tile;                                \
        layout_gate_check_layout(&obj);                      \
        assert(obj.tail_ext.unk1.unk84.bytes[0] == subtype); \
        actual = (u32)obj.unk2;                              \
        return actual;                                       \
    }
LAYOUT_CASE(layout_0_match, 0, 0x44)
LAYOUT_CASE(layout_0_other, 0, 0)
LAYOUT_CASE(layout_1_match, 1, 0x43)
LAYOUT_CASE(layout_1_other, 1, 0)
#undef LAYOUT_CASE
static const CTestCase layout_gate_check_layout_tiles_cases[] = {
    layout_0_match,
    layout_0_other,
    layout_1_match,
    layout_1_other,
};

static const u32 layout_gate_check_layout_tiles_cases_expected[] = { 0x2u, 0x0u, 0x2u, 0x1u };
static u8 gate_record;
static void lg_despawn(void)
{
    state_reset(0, 0, 0);
    gate_record = 0;
    state_room.item.active = 1;
    state_room.item.backref = (void*)&gate_record;
    layout_gate_despawn(&state_room.item);
    state_extra = gate_record;
    state_room.item.backref = NULL;
}

void layout_gate_wait_hit(struct ItemObj*);
void func_800C580C(struct ItemObj*);
void func_800C5994(struct ItemObj*, u8);
#define lg state_room.item
#define LG(step) (state_reset(0, 0, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), lg.active = 1, lg.state = 1, lg.unk5 = step, lg.x_pos.i.hi = 0x80, lg.y_pos.i.hi = 0x60, lg.unk5C = 1, SPIKE_IMMUNE_SET(g_Player, 1))
#define LGX() (state_extra = lg.ext.item_22.collision_side | (u32)lg.unk7C.timer << 8 | (u32)lg.unk2 << 24)
static void lg_hit_left(void)
{
    LG(0), state_hit(MAIN_OBJECT(&lg), 0, 0, 1), layout_gate_wait_hit(&lg), LGX();
}
static void lg_hit_right(void) { LG(0), state_hit(MAIN_OBJECT(&lg), 0, 0, 1), weapon_objects[0].x_pos.i.hi += 0x1A0, layout_gate_wait_hit(&lg), LGX(); }
static void lg_hit_none(void) { LG(0), MAIN_OBJECT(&lg)->hurt_box = &state_hit_box, layout_gate_wait_hit(&lg), LGX(); }
static void lg_open_rebuild(void) { LG(1), lg.unk7C.timer = 0x1F, lg.unk2 = 3, WEAPON_FRAME_COUNTER = 0, cur_random = 4, layout_width = 16, func_800C580C(&lg), LGX(), state_extra ^= (u32)D_80141BE8[16 + 11] << 4; }
static void lg_open_wait(void) { LG(1), lg.unk7C.timer = 5, WEAPON_FRAME_COUNTER = 1, func_800C580C(&lg), LGX(); }
static void lg_open_done(void) { LG(1), lg.unk7C.timer = 1, lg.tail_ext.unk1.unk84.bytes[0] = 5, func_800C580C(&lg), LGX(); }
#define BLAST(seed, debris) (LG(1), cur_random = seed, func_800C5994(&lg, debris), LGX(), state_extra ^= (u32)(u16)visual_objects[0].x_pos.i.hi << 4)
static void lg_blast_1(void)
{
    BLAST(1, 0);
}
static void lg_blast_2(void) { BLAST(2, 0); }
static void lg_blast_3(void) { BLAST(3, 1); }
static void (*const layout_gate_misc_cases[])(void) = {
    lg_despawn,
    lg_hit_left,
    lg_hit_right,
    lg_hit_none,
    lg_open_rebuild,
    lg_open_wait,
    lg_open_done,
    lg_blast_1,
    lg_blast_2,
    lg_blast_3,
};
static const u32 layout_gate_misc_expected[] = {
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0x50000u,
    0u,
    0u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x58000u,
    0x1u,
    0x2101u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x58000u,
    0x2u,
    0x2101u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x101u,
    0x301u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x3001A50u,
    0x41002100u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x400u,
    0x0u,
    0x3u,
    0x501u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x5000000u,
    0x0u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x720u,
    0x2100u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x840u,
    0x2100u,
    0x101u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x41000000u,
};

static u32 test_layout_gate_misc(u32 row)
{
    return object_run(layout_gate_misc_cases[row], row, &layout_gate_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "layout_gate_misc", 0, 0, COUNT(layout_gate_misc_cases), test_layout_gate_misc },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "layout_gate_check_layout_tiles", layout_gate_check_layout_tiles_cases, layout_gate_check_layout_tiles_cases_expected, COUNT(layout_gate_check_layout_tiles_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(layout_gate_misc_cases) + COUNT(pool_full_cases) + COUNT(layout_gate_check_layout_tiles_cases);
