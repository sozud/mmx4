#include "test_runtime.h"
#include "main/items/item_13_trap_floor.h"
#include "support/state_cases.h"
#include "support/tile_writes.h"
void trap_floor_main(struct ItemObj*);
void trap_floor_opened(struct ItemObj*);
extern u8 trap_floor_terrain_box[4];

#define tf state_room.item
static struct Unk_unk68 tf_player_box = { -8, -16, 16, 16 };
#define TF(step, py, setup) (state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), tf.active = 0x49, tf.id = 0xD, tf.state = 1, tf.unk5 = step, tf.x_pos.i.hi = 0x80, tf.y_pos.i.hi = 0x60, tf.unk68 = (struct Unk_unk68*)trap_floor_terrain_box, g_Player.unk68 = &tf_player_box, g_Player.y_pos.i.hi = 0x60 - (py), setup, trap_floor_main(&tf), state_extra = engine_obj.unk10 | (u32)engine_obj.unk14 << 8)
static void tf_wait_below(void)
{
    TF(0, -0x10, 0);
}
static void tf_wait_close(void) { TF(0, 4, 0); }
static void tf_wait_stand(void) { TF(0, 0x40, 0); }
static void tf_wait_stand_locked(void) { TF(0, 0x40, engine_obj.unk10 = 1); }
static void tf_open_end(void) { TF(1, 0, (engine_obj.unk10 = engine_obj.unk14 = 1, tf.animation_step.fields.event = 1)); }
static void tf_opened(void)
{
    state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.stage = 2, g_Player.unk68 = NULL;
    tf.active = 0x49, tf.id = 0xD, tf.state = 2, tf.x_pos.i.hi = 0x1498, tf.y_pos.i.hi = 0x330;
    background_objects[0].x_pos.i.hi = 0x1400, background_objects[0].y_pos.i.hi = 0x280;
    tile_writes_begin();
    tile_writes_expect(7, 0x1488, 0x330, 1);
    trap_floor_opened(&tf);
    state_extra = tile_writes_end();
    engine_obj.stage = 0;
}

static void (*const trap_floor_states_cases[])(void) = {
    tf_wait_below,
    tf_wait_close,
    tf_wait_stand,
    tf_wait_stand_locked,
    tf_open_end,
    tf_opened,
};
static const u32 trap_floor_states_expected[] = {
    0x1u,
    0x49u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x49u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x101u,
    0xFF000049u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x101u,
    0x0u,
    0x101u,
    0xFF000049u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
    0x2u,
    0x49u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x2u,
    0x49u,
    0x14980000u,
    0x3300000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x7692DEBCu,
    0x0u,
};
static u32 test_trap_floor_states(u32 row)
{
    return object_run(trap_floor_states_cases[row], row, &trap_floor_states_expected[row * 10]);
}

void trap_floor_open(struct ItemObj* arg0, struct EngineObj* arg1, struct PlayerObj* arg2);
static u32 open_paths(u32 row)
{
    u8 duration;
    state_reset(0, 0, 0);
    memset(&engine_obj, 0, sizeof(engine_obj));
    tf.active = 0x49;
    tf.id = 0xD;
    tf.state = 1;
    tf.unk5 = 1;
    tf.animation_step.fields.event = row;
    engine_obj.unk11 = engine_obj.unk14 = 7;
    duration = tf.animation_step.fields.duration;
    trap_floor_open(&tf, &engine_obj, &g_Player);
    assert(tf.state == (row ? 2 : 1) && tf.unk5 == (row ? 0 : 1));
    assert(row || tf.animation_step.fields.duration != duration);
    assert(engine_obj.unk10 == 0 && engine_obj.unk11 == 7 && engine_obj.unk14 == 7);
    return tf.state;
}

const struct CTestGroup c_test_groups[] = {
    { "trap_floor_states", 0, 0, COUNT(trap_floor_states_cases), test_trap_floor_states },
    { "open_paths", 0, 0, 2, open_paths },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(trap_floor_states_cases) + 2;
