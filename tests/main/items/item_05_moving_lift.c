#include "test_runtime.h"
#include "main/items/item_05_moving_lift.h"
#include "support/state_cases.h"
void moving_lift_despawn(struct ItemObj*);

static const u32 moving_lift_spawn_effect_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_moving_lift_spawn_effect(u32 row)
{
    u32 observed_values[11];
    struct ItemObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    FILL_ACTIVE(visual_objects, 32, 255 ? 1 : 0);
    moving_lift_spawn_effect(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].state;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].unk5;
    observed_values[8] = (u32)visual_objects[0].unk6;
    observed_values[9] = (u32)visual_objects[0].x_pos.val;
    observed_values[10] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, moving_lift_spawn_effect_expected, 11);
}

#include "support/pool_full.h"
static u32 pool_full_moving_lift_spawn_all(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    moving_lift_spawn_all();
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_moving_lift_spawn_all,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
static u8 lift_record;
static void ml_despawn(void)
{
    state_reset(0, 0, 0);
    lift_record = 0;
    state_room.item.active = 1;
    state_room.item.backref = (void*)&lift_record;
    moving_lift_despawn(&state_room.item);
    state_extra = lift_record;
    state_room.item.backref = NULL;
}

void func_800C0EBC(struct ItemObj*);
void func_800C1050(struct ItemObj*);
extern u8 moving_lift_boxes[9][4];
#define ml state_room.item
static s32 ml_frames[64];
static u32 ml_meta[64];
static struct Unk_unk68 ml_player_box = { -8, -16, 16, 32 };
#define ML(setup) (state_reset(0, 0, 0), memset(item_objects, 0, sizeof(item_objects)), D_801406A8 = ml_meta, TEST_MENU_FRAMES = (u8*)ml_frames, g_Player.unk68 = NULL, ml.active = 0x41, ml.id = 5, setup)
#define MLX() (state_extra = ml.unk76 | (u32)(u8)g_Player.unk71 << 8 | (u32)visual_objects[0].unk2 << 16 | (u32)item_objects[7].unk2 << 24)
#define MLM(sub, setup) ML((ml.unk2 = sub, ml.state = 1, ml.x_pos.i.hi = 0x10A0, ml.y_pos.i.hi = 0x500, ml.unk68 = (struct Unk_unk68*)moving_lift_boxes[sub], setup)), func_800C1050(&ml), MLX(), state_extra ^= (u32)g_Player.y_pos.val
static void ml_init_first(void) { ML(0), func_800C0EBC(&ml), assert(ml.unk42 == OBJECT_CLUT(0x788C)), ml.unk42 = 0, MLX(); }
static void ml_init_turning(void) { ML(ml.unk2 = 3), func_800C0EBC(&ml), assert(ml.unk42 == OBJECT_CLUT(0x788C)), ml.unk42 = 0, MLX(); }
static void ml_move_ridden_turning(void) { MLM(3, ml.unk76 = 1); }
static void ml_move_ridden(void) { MLM(0, ml.unk76 = 1); }
static void ml_move_wrap(void) { MLM(0, ml.y_pos.i.hi = 0x630); }
static void ml_move_carry(void) { MLM(0, (g_Player.unk68 = &ml_player_box, g_Player.x_pos.i.hi = 0x10B0, g_Player.y_pos.i.hi = 0x4F6, g_Player.unk71 = 0)); }
static void ml_move_side(void) { MLM(0, (ml.unk1C.val = ml.y_pos.val, g_Player.unk68 = &ml_player_box, g_Player.x_pos.i.hi = 0x10D8, g_Player.y_pos.i.hi = 0x500, g_Player.unk71 = 0)); }
static void ml_move_side_slip(void) { MLM(0, (ml.unk1C.val = ml.y_pos.val, g_Player.unk68 = &ml_player_box, g_Player.x_pos.i.hi = 0x10D8, g_Player.y_pos.val = 0x53EC000, g_Player.unk71 = 0)); }
static void (*const moving_lift_misc_cases[])(void) = {
    ml_despawn,
    ml_init_first,
    ml_init_turning,
    ml_move_ridden_turning,
    ml_move_ridden,
    ml_move_wrap,
    ml_move_carry,
    ml_move_side,
    ml_move_side_slip,
};
static const u32 moving_lift_misc_expected[] = {
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u,
    0x1u, 0xFF000041u, 0x10A00000u, 0x4E00000u, 0x0u, 0xFFFF0000u, 0x10000u, 0x30000u, 0x8010000u, 0x4100u,
    0x1u, 0xFF000341u, 0x11D80000u, 0x4800000u, 0x0u, 0xFFFF0000u, 0x10000u, 0x40000u, 0x30000u, 0x4100u,
    0x1u, 0x341u, 0x10A00000u, 0x501A000u, 0x0u, 0xFFFE6000u, 0x0u, 0x50000u, 0x5010000u, 0x0u,
    0x1u, 0x41u, 0x10A00000u, 0x5000000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x5000000u, 0x0u,
    0x1u, 0x41u, 0x10A00000u, 0x4E00000u, 0x0u, 0xFFFF0000u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x1u, 0x41u, 0x10A00000u, 0x5010000u, 0x0u, 0xFFFF0000u, 0x0u, 0x40000u, 0x4EB0801u, 0x0u,
    0x1u, 0x41u, 0x10A00000u, 0x5010000u, 0x0u, 0xFFFF0000u, 0x0u, 0x40000u, 0x5014201u, 0x0u,
    0x1u, 0x41u, 0x10A00000u, 0x5010000u, 0x0u, 0xFFFF0000u, 0x0u, 0x40000u, 0x5430200u, 0x0u,
};

static u32 test_moving_lift_misc(u32 row)
{
    return object_run(moving_lift_misc_cases[row], row, &moving_lift_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "moving_lift_misc", 0, 0, COUNT(moving_lift_misc_cases), test_moving_lift_misc },
    { "moving_lift_spawn_effect", 0, 0, 1, test_moving_lift_spawn_effect },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(moving_lift_misc_cases) + 1 + COUNT(pool_full_cases);
