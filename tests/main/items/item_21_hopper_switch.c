#include "test_runtime.h"
s32 hopper_switch_hopper_touching(struct ItemObj*);

static u32 live_hopper(void)
{
    struct ItemObj obj, before;
    struct MainObj pool_before[48];
    struct Unk_unk68 box = { 0, 0, 8, 8 };
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(main_objects, 0, sizeof(main_objects));
    obj.active = 0x41;
    obj.id = 21;
    obj.x_pos.val = 100 * 65536;
    obj.y_pos.val = 200 * 65536;
    obj.unk68 = &box;
    for (i = 0; i < 48; i++) {
        main_objects[i].active = 1;
        main_objects[i].id = 0x27;
    }
    main_objects[17].active = 0x41;
    main_objects[17].id = 0x29;
    main_objects[17].x_pos = obj.x_pos;
    main_objects[17].y_pos = obj.y_pos;
    main_objects[17].terrain_box = &box;
    before = obj;
    memcpy(pool_before, main_objects, sizeof(pool_before));
    actual = hopper_switch_hopper_touching(&obj);
    assert(actual == 1);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)main_objects)[i] == ((u32*)pool_before)[i]);
    assert(box.unk0 == 0 && box.unk1 == 0 && box.unk2 == 8 && box.unk3 == 8);
    return actual;
}
static const CTestCase hopper_switch_live_pool_cases[] = { live_hopper };
static const u32 hopper_switch_live_pool_cases_expected[] = { 0x1u };

static const u32 hopper_switch_hopper_touching_expected[] = { 0u };
static u32 test_hopper_switch_hopper_touching(u32 row)
{
    u32 observed_values[1];
    struct ItemObj obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&main_objects, 0, sizeof(main_objects));
    main_objects[0].active = -1;
    main_objects[0].id = 0;
    return_value = hopper_switch_hopper_touching(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, hopper_switch_hopper_touching_expected, 1);
}

#include "support/state_cases.h"
#include "support/tile_writes.h"
#include "main/items/item_21_hopper_switch.h"
void hopper_switch_main(struct ItemObj*);
#define hs state_room.item
static struct Unk_unk68 hs_box = { 0, 0, 8, 8 };
#define HS(step, setup)                                                                                                      \
    (state_reset(step, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = 6, engine_obj.substage = 1,       \
        g_Player.unk68 = NULL, memset(main_objects, 0, sizeof(main_objects)), hs.active = 0x41, hs.id = 0x15, hs.state = 1, \
        hs.x_pos.i.hi = 0xB30, hs.y_pos.i.hi = 0x657, hs.unk68 = &hs_box, main_objects[3].active = 0x41,                    \
        main_objects[3].id = 0x29, main_objects[3].terrain_box = &hs_box, main_objects[3].x_pos.i.hi = 0xB30,                \
        main_objects[3].y_pos.i.hi = 0x600, tile_writes_begin(), setup, hopper_switch_update(&hs),                           \
        state_extra = tile_writes_end(), memset(main_objects, 0, sizeof(main_objects)), engine_obj.stage = engine_obj.substage = 0)
static void hs_hopper_away(void) { HS(0, 0); }
static void hs_hopper_on(void) { HS(0, (main_objects[3].y_pos.i.hi = 0x657, tile_writes_expect(0, 0, 0, 1))); }
static void hs_pressed_end(void) { HS(1, 0); }
static void hs_pressed(void) { HS(1, hs.animation_step.fields.relative_step = 1); }
static void (*const hopper_switch_steps_cases[])(void) = {
    hs_hopper_away,
    hs_hopper_on,
    hs_pressed_end,
    hs_pressed,
};
static const u32 hopper_switch_steps_expected[] = {
    0x1u, 0x41u, 0xB300000u, 0x6570000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x101u, 0xFF000041u, 0xB300000u, 0x6570000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x32B1402Au, 0x0u,
    0x102u, 0x41u, 0xB300000u, 0x6570000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x101u, 0x41u, 0xB300000u, 0x6570000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
};
static u32 test_hopper_switch_steps(u32 row)
{
    return object_run(hopper_switch_steps_cases[row], row, &hopper_switch_steps_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "hopper_switch_live_pool", hopper_switch_live_pool_cases, hopper_switch_live_pool_cases_expected, COUNT(hopper_switch_live_pool_cases), 0 },
    { "hopper_switch_hopper_touching", 0, 0, 1, test_hopper_switch_hopper_touching },
    { "hopper_switch_steps", 0, 0, COUNT(hopper_switch_steps_cases), test_hopper_switch_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(hopper_switch_live_pool_cases) + 1 + COUNT(hopper_switch_steps_cases);
