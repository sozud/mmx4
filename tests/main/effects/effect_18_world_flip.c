#include "test_runtime.h"
void world_flip_objects(void);

#define INIT_POOL(pool)                                        \
    for (i = 0; i < COUNT(pool); i++) {                        \
        pool[i].active = (i == COUNT(pool) - 1 || i % 2 == 0); \
        pool[i].y_pos.val = pool[i].active ? 12345 : -34567;   \
    }

static void prepare_pools(void)
{
    u32 i;
    INIT_POOL(main_objects)
    INIT_POOL(misc_objects)
    INIT_POOL(weapon_objects)
    INIT_POOL(shot_objects)
    INIT_POOL(visual_objects)
}

#define FLIP_CASE(name, pool, active_lane, expected)        \
    static u32 name(void)                                   \
    {                                                       \
        u32 i;                                              \
        prepare_pools();                                    \
        world_flip_objects();                               \
        for (i = 0; i < COUNT(pool); i++) {                 \
            if (!!pool[i].active == active_lane) {          \
                assert((u32)pool[i].y_pos.val == expected); \
            }                                               \
        }                                                   \
        return (u32)pool[active_lane ? 0 : 1].y_pos.val;    \
    }
FLIP_CASE(main_active, main_objects, 1, 0x7FFCFC7u)
FLIP_CASE(main_inactive, main_objects, 0, 0xFFFF78F9u)
FLIP_CASE(misc_active, misc_objects, 1, 0x7FFCFC7u)
FLIP_CASE(misc_inactive, misc_objects, 0, 0xFFFF78F9u)
FLIP_CASE(weapon_active, weapon_objects, 1, 0x7FFCFC7u)
FLIP_CASE(weapon_inactive, weapon_objects, 0, 0xFFFF78F9u)
FLIP_CASE(shot_active, shot_objects, 1, 0x7FFCFC7u)
FLIP_CASE(shot_inactive, shot_objects, 0, 0xFFFF78F9u)
FLIP_CASE(visual_active, visual_objects, 1, 0x7FFCFC7u)
FLIP_CASE(visual_inactive, visual_objects, 0, 0xFFFF78F9u)

static const CTestCase world_flip_cases[] = {
    main_active,
    main_inactive,
    misc_active,
    misc_inactive,
    weapon_active,
    weapon_inactive,
    shot_active,
    shot_inactive,
    visual_active,
    visual_inactive,
};
static const u32 world_flip_cases_expected[] = { 0x7FFCFC7u, 0xFFFF78F9u, 0x7FFCFC7u, 0xFFFF78F9u, 0x7FFCFC7u, 0xFFFF78F9u, 0x7FFCFC7u, 0xFFFF78F9u, 0x7FFCFC7u, 0xFFFF78F9u };
#undef INIT_POOL
#undef FLIP_CASE

#define PREPARE(pool)                                \
    for (i = 0; i < COUNT(pool); i++) {              \
        pool[i].active = i == 0;                     \
        pool[i].y_pos.val = i == 0 ? 0x00120034 : 0; \
    }
#define CHECK_POOL(pool)                                              \
    assert(pool[0].active == 1);                                      \
    assert(pool[0].y_pos.val == (pressed ? 0x07EDFFCC : 0x00120034)); \
    for (i = 1; i < COUNT(pool); i++)                                 \
        assert(pool[i].active == 0 && pool[i].y_pos.val == 0);

static u32 trigger_case(u8 pressed)
{
    struct EffectObj obj;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    PREPARE(main_objects)
    PREPARE(misc_objects)
    PREPARE(weapon_objects)
    PREPARE(shot_objects)
    PREPARE(visual_objects)
    engine_obj.character_state.bytes[0]
        = 1;
    g_Player.input.buttons.held = pressed ? 0 : 0x20;
    g_Player.pressed_input = pressed ? 0x20 : 0;
    g_Player.y_pos.val = 0x01000003;
    background_objects[0].y_pos.val = 0x02000001;
    background_objects[0].unk18.val = 0x03000007;
    background_objects[1].y_pos.val = 0x04000005;
    background_objects[1].unk18.val = 0x05000009;
    background_objects[2].y_pos.val = 0x0600000B;
    background_objects[2].unk18.val = 0x0700000D;
    func_800B96E0(&obj);
    assert(g_Player.y_pos.val == (pressed ? 0x06FFFFFD : 0x01000003));
    assert(background_objects[0].y_pos.val == (pressed ? 0x04FFFFFF : 0x02000001));
    assert(background_objects[0].unk18.val == (pressed ? 0x03FFFFF9 : 0x03000007));
    assert(background_objects[1].y_pos.val == (pressed ? 0x013FFFFF : 0x04000005));
    assert(background_objects[2].y_pos.val == (pressed ? 0x013FFFFF : 0x0600000B));
    assert(background_objects[1].unk18.val == (pressed ? 0x00FFFFFE : 0x05000009));
    assert(background_objects[2].unk18.val == (pressed ? 0x00FFFFFE : 0x0700000D));
    CHECK_POOL(main_objects)
    CHECK_POOL(misc_objects)
    CHECK_POOL(weapon_objects)
    CHECK_POOL(shot_objects)
    CHECK_POOL(visual_objects)
    actual
        = engine_obj.character_state.bytes[0] | ((u32)background_objects[0].unk4C << 8) | ((u32)background_objects[1].unk4C << 16) | ((u32)background_objects[2].unk4C << 24);
    return actual;
}
static u32 flip_off(void)
{
    return trigger_case(0);
}
static u32 flip_on(void)
{
    return trigger_case(1);
}
static const CTestCase world_flip_trigger_cases[] = {
    flip_off,
    flip_on,
};
static const u32 world_flip_trigger_cases_expected[] = { 0x1u, 0x1010100u };
#undef PREPARE
#undef CHECK_POOL

const struct CTestGroup c_test_groups[] = {
    { "world_flip", world_flip_cases, world_flip_cases_expected, COUNT(world_flip_cases), 0 },
    { "world_flip_trigger", world_flip_trigger_cases, world_flip_trigger_cases_expected, COUNT(world_flip_trigger_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(world_flip_cases) + COUNT(world_flip_trigger_cases);
