#include "test_runtime.h"
#include "main/items/item_08_boss_door.h"

#ifndef VERSION_DEMO
static const u32 boss_door_block_player_expected[] = { 0u };
static u32 test_boss_door_block_player(u32 row)
{
    u32 observed_values[1];
    struct ItemObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk72 = 12;
    boss_door_block_player(&obj);
    observed_values[0] = (u32)g_Player.unk71;
    return c_test_observe(0, row, observed_values, boss_door_block_player_expected, 1);
}
#endif

static const u32 func_800C1E7C_expected[] = { 0u };
static u32 test_func_800C1E7C(u32 row)
{
    u32 observed_values[1];
    struct ItemObj obj;
    struct Unk_unk68 child_0;
    struct Unk_unk68 child_1;
    s8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.unk2 = -1;
    obj.x_pos.i.hi = 32766;
    g_Player.x_pos.i.hi = 1;
    child_0.unk0 = 106;
    child_1.unk0 = 47;
    obj.unk68 = &child_0;
    g_Player.unk68 = &child_1;
    return_value = func_800C1E7C(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, func_800C1E7C_expected, 1);
}

static const struct {
    u8 immune;
    s16 y;
    u32 expected;
} touch_cases[] = {
    { 1, 100, 0 },
    { 0, 112, 0 },
};
static u32 touch(u32 row)
{
    static struct Unk_unk68 door_box = { 0, 0, 16, 16 }, player_box = { 0, 0, 8, 8 };
    struct ItemObj obj;
    u32 observed;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.unk68 = &door_box;
    SPIKE_IMMUNE_SET(g_Player, touch_cases[row].immune);
    g_Player.x_pos.i.hi = 100;
    g_Player.y_pos.i.hi = touch_cases[row].y;
    g_Player.unk68 = &player_box;
    observed = (u32)func_800C1E7C(&obj);
    return c_test_observe(0, row, &observed, &touch_cases[row].expected, 1);
}

#include "support/state_cases.h"
void boss_door_update(struct ItemObj*);
void boss_door_open(struct ItemObj*, struct EngineObj*, struct PlayerObj*);
void func_800C1C88(struct ItemObj*, struct EngineObj*, struct PlayerObj*);
void boss_door_locked(struct ItemObj*);
extern struct Unk_unk68 boss_door_terrain_box;
#define bd state_room.item
static struct Unk_unk68 bd_door_box = { 0, 0, 16, 16 }, bd_player_box = { 0, 0, 8, 8 };
static u32 bd_resources[0x100];
static s32 bd_frames[0x100];
#define BD2(step) (state_reset(0, 0, 0), memset(&g_Player, 0, sizeof(g_Player)), memset(&engine_obj, 0, sizeof(engine_obj)), bd.active = 0x49, bd.state = 1, bd.unk5 = step, bd.x_pos.i.hi = 100, bd.y_pos.i.hi = 100, bd.unk68 = &bd_door_box, g_Player.x_pos.i.hi = 100, g_Player.y_pos.i.hi = 100, g_Player.unk68 = &bd_player_box)
#define BD2X() (state_extra = bd.unk5 | engine_obj.unk10 << 8 | (u32)(u16)background_objects[0].unk24 << 16)
static void bd2_init_locked(void)
{
    BD2(0), bd.state = 0, bd.unk2 = 0x40, D_801406A8 = bd_resources, TEST_MENU_FRAMES = (u8*)bd_frames, boss_door_update(&bd), assert(bd.unk42 == VISUAL_STAGE_PALETTE(func_8002938C(0x80))), bd.unk42 = 0, BD2X(), state_extra ^= (bd.unk68 == NULL) << 4 | bd.ext.packed << 4;
}
static void bd2_init(void) { BD2(0), bd.state = 0, bd.unk2 = 0x11, D_801406A8 = bd_resources, TEST_MENU_FRAMES = (u8*)bd_frames, boss_door_update(&bd), assert(bd.unk42 == VISUAL_STAGE_PALETTE(func_8002938C(0x80))), bd.unk42 = 0, BD2X(), state_extra ^= (bd.unk68 == &boss_door_terrain_box) << 4 | bd.unk7C.timer << 4; }
static void bd2_open(void) { BD2(1), g_Player.capsule_state = -1, boss_door_open(&bd, &engine_obj, &g_Player), BD2X(), state_extra ^= (g_Player.unk68 == NULL) << 4; }
static void bd2_open_wait(void) { BD2(1), boss_door_open(&bd, &engine_obj, &g_Player), BD2X(); }
static void bd2_opening_sound(void) { BD2(2), bd.animation_step.fields.event = 1, func_800C1C88(&bd, &engine_obj, &g_Player), BD2X(); }
static void bd2_opening(void) { BD2(2), func_800C1C88(&bd, &engine_obj, &g_Player), BD2X(); }
#define OPENED(kind) (BD2(2), bd.unk2 = kind, bd.animation_step.fields.event = 2, engine_obj.unk10 = 1, func_800C1C88(&bd, &engine_obj, &g_Player), BD2X(), state_extra ^= (u32)background_objects[0].unk26 << 4)
static void bd2_opened_0(void)
{
    OPENED(0);
}
static void bd2_opened_1(void) { OPENED(1); }
static void bd2_opened_2(void) { OPENED(2); }
static void bd2_opened_4(void) { OPENED(4); }
static void bd2_opened_5(void) { OPENED(5); }
static void bd2_opened_6(void) { OPENED(6); }
#define TOUCH(setup) (BD2(0), setup, state_extra = (u8)func_800C1E7C(&bd))
static void bd2_touch_hurt(void)
{
    TOUCH(g_Player.hurt_phase = 1);
}
static void bd2_touch_step_3(void) { TOUCH(g_Player.unk5 = 3); }
static void bd2_touch_step_11(void) { TOUCH(g_Player.unk5 = 0xB); }
static void bd2_touch_attacking(void) { TOUCH((g_Player.unk2 = 1, g_Player.attacking = 1)); }
static void bd2_touch_past(void) { TOUCH(g_Player.x_pos.i.hi = 101); }
static void bd2_touch(void) { TOUCH(0); }
static void bd2_touch_above(void) { TOUCH(g_Player.y_pos.i.hi = 60); }
#ifndef VERSION_DEMO
#define LOCKED(packed_, active_) (BD2(0), bd.state = 2, bd.unk68 = NULL, bd.ext.packed = packed_, engine_obj.character_state.fields.active = active_, boss_door_locked(&bd), BD2X(), state_extra ^= bd.state << 4 | (bd.unk68 != NULL) << 8)
static void bd2_locked_plain(void)
{
    LOCKED(0, 1);
}
static void bd2_locked_wait(void) { LOCKED(0x40, 0); }
static void bd2_unlocked(void) { LOCKED(0x40, 1); }
#endif
static void (*const bd2_cases[])(void) = {
    bd2_init_locked,
    bd2_init,
    bd2_open,
    bd2_open_wait,
    bd2_opening_sound,
    bd2_opening,
    bd2_opened_0,
    bd2_opened_1,
    bd2_opened_2,
    bd2_opened_4,
    bd2_opened_5,
    bd2_opened_6,
    bd2_touch_hurt,
    bd2_touch_step_3,
    bd2_touch_step_11,
    bd2_touch_attacking,
    bd2_touch_past,
    bd2_touch,
    bd2_touch_above,
#ifndef VERSION_DEMO
    bd2_locked_plain,
    bd2_locked_wait,
    bd2_unlocked,
#endif
};
static const u32 bd2_expected[] = {
    0x2u,
    0xFF000049u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x10000u,
    0x410u,
    0x0u,
    0x1u,
    0xFF000149u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x10000u,
    0x110u,
    0x0u,
    0x201u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x112u,
    0x0u,
    0x101u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
    0x201u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x2u,
    0x0u,
    0x201u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x2u,
    0x0u,
    0x301u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x640643u,
    0x0u,
    0x301u,
    0x149u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x940643u,
    0x0u,
    0x301u,
    0x249u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1040643u,
    0x0u,
    0x301u,
    0x449u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0xB40643u,
    0x0u,
    0x301u,
    0x549u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1140643u,
    0x0u,
    0x301u,
    0x649u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x6040643u,
    0x0u,
    0x1u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
    0x1u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x1u,
    0x0u,
    0x1u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x0u,
    0x0u,
#ifndef VERSION_DEMO
    0x2u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20u,
    0x0u,
    0x2u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x20u,
    0x0u,
    0x1u,
    0x49u,
    0x640000u,
    0x640000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x110u,
    0x0u,
#endif
};
static u32 bd2_run(u32 row)
{
    return object_run(bd2_cases[row], row, &bd2_expected[row * 10]);
}

#ifndef VERSION_DEMO
void boss_door_wait_player(struct ItemObj*, struct EngineObj*, struct PlayerObj*);
void boss_door_walk_through(struct ItemObj*, struct EngineObj*, struct PlayerObj*);
void boss_door_close(struct ItemObj*, struct EngineObj*, struct PlayerObj*);
extern struct Item08AnimationStep* boss_door_animations[2];
static u32 door_step(u32 row)
{
    static u32 animation[2] = { 0, 0 };
    BD2(row < 3 ? 0 : row < 5 ? 3
                              : 4);
    memset(main_objects, 0, sizeof(main_objects));
    memset(background_objects, 0, sizeof(background_objects));
    main_objects[0].active = 1;
    background_objects[0].unk3E.half = 0x1234;
    if (row < 3) {
        bd.unk7C.timer = row == 1;
        g_Player.x_pos.i.hi = row == 2 ? 200 : 100 - 24;
        boss_door_wait_player(&bd, &engine_obj, &g_Player);
        assert(bd.unk5 == (row < 2));
        assert(g_Player.capsule_state == (row < 2));
        assert(background_objects[0].unk3E.half == (row < 2 ? 0x4 : 0x1234));
        assert(main_objects[0].active == (row != 0));
        return bd.unk5;
    }
    if (row < 5) {
        bd.animation_table = (const u8* const*)boss_door_animations;
        g_Player.capsule_state = 1;
        g_Player.x_pos.val = 0x640000;
        background_objects[0].x_pos.i.hi = 0x300;
        background_objects[0].unk26 = row == 3 ? 0x300 : 0x310;
        boss_door_walk_through(&bd, &engine_obj, &g_Player);
        assert(g_Player.x_pos.val == 0x640000 + 0xA400);
        assert(bd.unk5 == (row == 3 ? 4 : 3));
        assert(g_Player.capsule_state == (row == 3 ? 0 : 1));
        if (row == 3)
            assert(bd.unk17 == 1 && bd.animation_cursor == (const u8*)boss_door_animations[1]);
        return bd.unk5;
    }
    bd.animation_cursor = (const u8*)animation;
    bd.animation_step.packed = 0;
    bd.animation_step.fields.duration = 2;
    bd.animation_step.fields.event = row == 5 ? 1 : row == 6 ? 0
                                                             : 2;
    boss_door_close(&bd, &engine_obj, &g_Player);
    assert(bd.state == (row == 7 ? 2 : 1) && bd.unk5 == (row == 7 ? 0 : 4));
    assert(bd.animation_step.fields.event == (row == 7 ? 2 : 0));
    assert(bd.animation_step.fields.duration == (row == 7 ? 2 : 1));
    return bd.state;
}
#define DOOR_STEP_COUNT 8
#else
#define DOOR_STEP_COUNT 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "boss_door_branch_steps", 0, 0, COUNT(bd2_cases), bd2_run },
#ifndef VERSION_DEMO
    { "boss_door_block_player", 0, 0, 1, test_boss_door_block_player },
    { "door_steps", NULL, NULL, DOOR_STEP_COUNT, door_step },
#endif
    { "func_800C1E7C", 0, 0, 1, test_func_800C1E7C },
    { "player_touching_door", NULL, NULL, COUNT(touch_cases), touch },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(bd2_cases) + 1 + COUNT(touch_cases) + DOOR_STEP_COUNT
#ifndef VERSION_DEMO
    + 1
#endif
    ;
