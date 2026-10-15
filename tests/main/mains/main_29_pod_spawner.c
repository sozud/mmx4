#include "test_runtime.h"
extern union AnimationStep* pod_spawner_animations[16];
u8 pod_spawner_player_quadrant(struct MainObj*);
extern s16 D_800FD86C[12], D_800FD884[12];

static const s8 phases[] = { 0, -1, 3 };
static u32 pod_case(u32 mode, u32 observation)
{
    struct MainObj obj, source, children[4], before, source_before, children_before[4];
    struct PlayerObj player_before;
    struct BackgroundObj bg_before[3];
    u32 i, j, nulls = 0;
    memset(&obj, 0, sizeof(obj));
    memset(&source, 0, sizeof(source));
    memset(children, 0, sizeof(children));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 29;
    obj.state = 3;
    obj.unk5 = phases[mode];
    obj.unk6 = 0x27;
    obj.unk42 = 0xFFFF;
    source.x_pos.val = 100 * 65536 + 0x1234;
    source.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.main_29.source = &source;
    obj.ext.main_29.unk94 = 0x2718;
    for (i = 0; i < COUNT(children); i++) {
        children[i].active = i == 1 ? 0 : 0x41;
        children[i].id = i == 2 ? 27 : 28;
        children[i].state = 2;
        obj.ext.main_29.slots.children[i] = i ? &children[i] : NULL;
    }
    obj.animation_table = (const u8* const*)pod_spawner_animations;
    set_animation(&obj, 0);
    before = obj;
    source_before = source;
    player_before = g_Player;
    memcpy(children_before, children, sizeof(children_before));
    memcpy(bg_before, background_objects, sizeof(bg_before));
    func_8005B2C8(&obj);
    before.x_pos = source.x_pos;
    before.y_pos = source.y_pos;
    if (mode == 0) {
        before.unk5 = 1;
        before.unk42 = 0x7FFF;
        before.on_screen = obj.on_screen;
        before.ext.main_29.unk94 = 0;
        for (i = 0; i < COUNT(children); i++)
            before.ext.main_29.slots.children[i] = NULL;
        children_before[3].state = 3;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(source) / 4; i++)
        assert(((u32*)&source)[i] == ((u32*)&source_before)[i]);
    for (i = 0; i < COUNT(children); i++) {
        if (obj.ext.main_29.slots.children[i] == NULL)
            nulls |= 1U << i;
        for (j = 0; j < sizeof(children[0]) / 4; j++)
            assert(((u32*)&children[i])[j] == ((u32*)&children_before[i])[j]);
    }
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    switch (observation) {
    case 0:
        return (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)obj.on_screen << 16);
    case 1:
        return obj.unk42 | ((u32)obj.ext.main_29.unk94 << 16);
    case 2:
        return obj.x_pos.val;
    case 3:
        return obj.y_pos.val;
    case 4:
        return children[0].state | ((u32)children[1].state << 8)
            | ((u32)children[2].state << 16) | ((u32)children[3].state << 24);
    case 5:
        return nulls;
    default:
        return obj.animation_step.packed;
    }
}
#define CASE(m, n)                                              \
    static u32 pod_spawner_children_context_pod_##m##_##n(void) \
    {                                                           \
        return pod_case(m, n);                                  \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2) CASE(m, 3) CASE(m, 4) CASE(m, 5) CASE(m, 6)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(m, n) pod_spawner_children_context_pod_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2) ENTRY(m, 3) ENTRY(m, 4) ENTRY(m, 5) ENTRY(m, 6)
static const CTestCase pod_spawner_children_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 pod_spawner_children_context_cases_expected[] = { 0x10103u, 0x7FFFu, 0x641234u, 0xC85678u, 0x3020202u, 0xFu, 0x1u, 0xFF03u, 0x2718FFFFu, 0x641234u, 0xC85678u, 0x2020202u, 0x1u, 0x1u, 0x303u, 0x2718FFFFu, 0x641234u, 0xC85678u, 0x2020202u, 0x1u, 0x1u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 cleanup_case(u32 mode)
{
    struct MainObj obj, expected, children[4], children_expected[4];
    struct PlayerObj player_before = g_Player;
    u32 i, result = 0;
    memset(&obj, 0, sizeof(obj));
    memset(children, 0, sizeof(children));
    obj.active = 0x41;
    obj.id = 29;
    obj.unk2 = 2;
    obj.on_screen = 1;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 4;
    obj.unk7 = 5;
    obj.ext.main_29.unk94 = 9;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    for (i = 0; i < 4; i++) {
        children[i].active = mode == 4 || (mode == 1 && i == 1) ? 0 : 0x41;
        children[i].id = mode == 1 && i == 2 ? 27 : 28;
        children[i].state = 1;
        children[i].unk5 = 4;
        children[i].unk6 = 5;
        children[i].unk7 = 6;
        children[i].x_pos.val = (50 + i) * 65536 + 0xBEEF;
        children[i].y_pos.val = (60 + i) * 65536 + 0xCAFE;
        obj.ext.main_29.slots.children[i] = mode == 0 || (mode == 1 && i == 3) ? NULL : &children[mode == 3 ? 0 : i];
    }
    expected = obj;
    memcpy(children_expected, children, sizeof(children));
    memset(&expected, 0, 8);
    expected.ext.main_29.unk94 = 0;
    for (i = 0; i < 4; i++) {
        if (obj.ext.main_29.slots.children[i] && obj.ext.main_29.slots.children[i]->active && obj.ext.main_29.slots.children[i]->id == 28)
            children_expected[mode == 3 ? 0 : i].state = 3;
        expected.ext.main_29.slots.children[i] = NULL;
    }
    func_8005B24C(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(children) / 4; i++)
        assert(((u32*)children)[i] == ((u32*)children_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 4; i++)
        result |= (u32)(u8)children[i].state << (i * 8);
    return result;
}
#define CASE(m)                                             \
    static u32 pod_spawner_linked_cleanup_cleanup_##m(void) \
    {                                                       \
        return cleanup_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) pod_spawner_linked_cleanup_cleanup_##m,
static const CTestCase pod_spawner_linked_cleanup_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 pod_spawner_linked_cleanup_cases_expected[] = { 0x1010101u, 0x1010103u, 0x3030303u, 0x1010103u, 0x1010101u };
#undef CASE
#undef ENTRY

static u32 pod_spawner_quadrant_context_quadrant_case(u32 mode)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 29;
    obj.state = 1;
    obj.x_pos.val = 100 * 65536;
    obj.y_pos.val = 100 * 65536;
    g_Player.x_pos.val = (mode == 0 ? 200 : mode == 1 ? 0
                                                      : 100)
        * 65536;
    g_Player.y_pos.val = (mode == 2 ? 200 : mode == 3 ? 0
                                                      : 100)
        * 65536;
    g_Player.hp = 0x27;
    before = obj;
    player_before = g_Player;
    actual = pod_spawner_player_quadrant(&obj);
    assert(actual <= 3);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return actual;
}
#define CASE(m)                                                \
    static u32 pod_spawner_quadrant_context_quadrant_##m(void) \
    {                                                          \
        return pod_spawner_quadrant_context_quadrant_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
#define ENTRY(m) pod_spawner_quadrant_context_quadrant_##m,
static const CTestCase pod_spawner_quadrant_context_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) };
static const u32 pod_spawner_quadrant_context_cases_expected[] = { 0x1u, 0x0u, 0x3u, 0x2u };
#undef CASE
#undef ENTRY

enum { POOL_FULL,
    COOLDOWN,
    HANDOFF };
static u32 steps[2];
static struct MainObj spawner, source, expected, expected_source;
static struct MainObj pool_before[0x30];

static u32 pod_spawner_spawn_run(u32 mode)
{
    union AnimationStep value;
    u32 i, j;
    memcpy(pool_before, main_objects, sizeof(pool_before));
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    memset(&spawner, 0, sizeof(spawner));
    memset(&source, 0, sizeof(source));
    value.fields.duration = 3;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 2;
    steps[0] = steps[1] = value.packed;
    source.active = 0x41;
    source.id = 0x1D;
    source.unk6 = 2;
    source.x_pos.val = 0x00801234;
    source.y_pos.val = 0x00405678;
    source.unk42 = 0x4321;
    spawner.active = 0x41;
    spawner.id = 0x1C;
    spawner.unk6 = mode == HANDOFF ? 2 : 1;
    spawner.unk7C = mode == COOLDOWN;
    spawner.animation_cursor = &steps[0];
    spawner.animation_step.packed = steps[0];
    spawner.ext.main_29.source = &source;
    spawner.ext.main_29.unk96 = 2;
    expected = spawner;
    expected_source = source;
    func_8005AF5C(&spawner);

    expected.x_pos = source.x_pos;
    expected.y_pos = source.y_pos;
    expected.unk42 = source.unk42;
    expected.animation_step.fields.duration = 2;
    expected.on_screen = 1;
    if (mode == HANDOFF) {
        expected.unk6 = 3;
        expected_source.unk6 = 4;
        expected_source.unk7C = 0x1E;
    }
    for (i = 0; i < sizeof(spawner) / 4; i++)
        assert(((u32*)&spawner)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(source) / 4; i++)
        assert(((u32*)&source)[i] == ((u32*)&expected_source)[i]);
    for (i = 0; i < COUNT(main_objects); i++) {
        struct MainObj want = pool_before[i];
        want.active = 1;
        for (j = 0; j < sizeof(want) / 4; j++)
            assert(((u32*)&main_objects[i])[j] == ((u32*)&want)[j]);
    }
    assert(background_objects[0].x_pos.val == 0 && background_objects[0].y_pos.val == 0);
    return (u8)spawner.unk6 | ((u32)(u8)spawner.on_screen << 28) | ((u32)spawner.ext.main_29.unk94 << 8) | ((u32)(u8)source.unk6 << 24)
        | ((u32)(spawner.ext.main_29.slots.children[0] != NULL) << 16) | ((u32)(spawner.ext.main_29.slots.children[1] != NULL) << 17);
}

#define CASE(name)                                   \
    static u32 pod_spawner_spawn_##name##_case(void) \
    {                                                \
        return pod_spawner_spawn_run(name);          \
    }
CASE(POOL_FULL)
CASE(COOLDOWN)
CASE(HANDOFF)
#define ENTRY(name) pod_spawner_spawn_##name##_case,
static const CTestCase pod_spawner_spawn_cases[]
    = { ENTRY(POOL_FULL) ENTRY(COOLDOWN) ENTRY(HANDOFF) };
static const u32 pod_spawner_spawn_cases_expected[] = { 0x12000001u, 0x12000001u, 0x14000003u };
#undef CASE
#undef ENTRY

static s32 frames[4] = { 8, 12, 0x11223344, 0x55667788 };
static u32 pod_spawner_subtype_quadrants_quadrant_case(u32 mode)
{
    static const s16 delta[8][2] = { { 32, 0 }, { 32, -32 }, { 0, -32 }, { -32, -32 }, { -32, 0 }, { -32, 32 }, { 0, 32 }, { 32, 32 } };
    static const u8 direction[3][8] = { { 1, 2, 2, 0, 0, 3, 3, 1 }, { 2, 2, 2, 2, 3, 3, 3, 3 }, { 1, 1, 0, 0, 0, 0, 1, 1 } };
    static const s16 motion_x[12] = { 1, 2, 3, 3, 2, 1, -1, -2, -3, -3, -2, -1 };
    static const s16 motion_y[12] = { -3, -2, -1, 1, 2, 3, 3, 2, 1, -1, -2, -3 };
    struct MainObj obj, expected, controller, controller_expected;
    struct ShotObj pool_expected[32];
    struct PlayerObj player_expected;
    struct MainBssState bss_expected;
    u32 i, index = mode < 24 ? mode % 8 : 0;
    u32 subtype = mode < 24 ? mode / 8 : mode == 24 ? 255
        : mode == 25                                ? 3
                                                    : 0;
    u32 shoot = mode < 24 || mode >= 26 && mode <= 28;
    u8* context;
    memset(&obj, 0, sizeof(obj));
    memset(&controller, 0, sizeof(controller));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = i == 31 && mode != 34 ? 0 : 1;
        shot_objects[i].id = 39;
        shot_objects[i].state = 40;
        shot_objects[i].unk2 = 9;
        shot_objects[i].unk5 = 3;
        shot_objects[i].unk6 = 4;
        shot_objects[i].unk42 = 0x7777;
        shot_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        shot_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    obj.active = 0x41;
    obj.id = 29;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 3;
    obj.unk2 = subtype;
    obj.unk16 = 7;
    obj.unk40 = 0x456;
    obj.unk42 = 0x8123;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)pod_spawner_animations;
    obj.sprite_frames = (u8*)frames;
    set_animation(&obj, 1);
    controller.active = 0x41;
    controller.id = 29;
    controller.state = 1;
    controller.unk5 = 8;
    context = (u8*)&controller.ext;
    context[0] = mode == 27 ? 11 : 0;
    context[1] = mode == 29 ? 1 : 0;
    ((s16*)context)[1] = 100;
    ((s16*)context)[2] = 200;
    ((s16*)context)[3] = 9;
    ((s16*)context)[4] = 10;
    SP_CUR_MAIN_OBJ = &controller;
    main_bss_state.frame_counter = mode == 26 || mode == 27 ? 0 : mode == 28 ? 2
                                                                             : 1;
    expected = obj;
    controller_expected = controller;
    if (mode == 26 || mode == 27) {
        u8* expected_context = (u8*)&controller_expected.ext;
        u32 next_index = mode == 26 ? 1 : 0;
        expected_context[0] = next_index;
        ((s16*)expected_context)[3] = motion_x[next_index];
        ((s16*)expected_context)[4] = motion_y[next_index];
        expected.x_pos.i.hi = 100 + motion_x[next_index];
        expected.y_pos.i.hi = 200 + motion_y[next_index];
    }
    g_Player.x_pos.val = (expected.x_pos.i.hi + delta[index][0]) * 65536 + 0x1234;
    g_Player.y_pos.val = (expected.y_pos.i.hi + delta[index][1]) * 65536 + 0x5678;
    if (mode == 30)
        g_Player.x_pos.i.hi = expected.x_pos.i.hi + 129;
    if (mode == 31)
        g_Player.y_pos.i.hi = expected.y_pos.i.hi + 65;
    if (mode == 32)
        g_Player.x_pos.i.hi = expected.x_pos.i.hi - 129;
    if (mode == 33)
        g_Player.y_pos.i.hi = expected.y_pos.i.hi - 65;
    player_expected = g_Player;
    bss_expected = main_bss_state;
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    assert(expected.animation_step.fields.duration == 2);
    expected.animation_step.fields.duration--;
    if (shoot) {
        struct ShotObj* child = &pool_expected[31];
        expected.unk5 = 3;
        controller_expected.ext.main_29_controller.unk81 = 1;
        controller_expected.ext.main_29.slots.controller.record = (struct Main29Record*)&shot_objects[31];
        child->active = obj.active;
        child->id = 0x10;
        child->unk2 = direction[subtype][index];
        child->x_pos = expected.x_pos;
        child->y_pos = expected.y_pos;
        child->animation_table = (u32**)obj.animation_table;
        child->unk38 = NULL;
        child->unk3C = obj.sprite_frames;
        child->unk40 = obj.unk40;
        child->unk42 = obj.unk42 & 0x7FFF;
        child->unk16 = obj.unk16;
        child->unk7C = WEAPON_OBJECT(&obj);
    }
    func_8005A758(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(controller) / 4; i++)
        assert(((u32*)&controller)[i] == ((u32*)&controller_expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(main_bss_state) / 4; i++)
        assert(((u32*)&main_bss_state)[i] == ((u32*)&bss_expected)[i]);
    for (i = 0; i < 12; i++)
        assert(D_800FD86C[i] == motion_x[i] && D_800FD884[i] == motion_y[i]);
    assert(SP_CUR_MAIN_OBJ == &controller);
    assert(frames[0] == 8 && frames[1] == 12 && frames[2] == 0x11223344 && frames[3] == 0x55667788);
    i = (u8)obj.unk5 | ((u32)(u8)shot_objects[31].unk2 << 8) | ((u32)context[0] << 16) | ((u32)context[1] << 24);
    return i;
}
#define CASE(m)                                                 \
    static u32 pod_spawner_subtype_quadrants_quadrant_##m(void) \
    {                                                           \
        return pod_spawner_subtype_quadrants_quadrant_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
CASE(10)
CASE(11)
CASE(12)
CASE(13)
CASE(14)
CASE(15)
CASE(16)
CASE(17)
CASE(18)
CASE(19)
CASE(20)
CASE(21)
CASE(22)
CASE(23)
CASE(24)
CASE(25)
CASE(26)
CASE(27)
CASE(28)
CASE(29)
CASE(30)
CASE(31)
CASE(32)
CASE(33)
CASE(34)
#define ENTRY(m) pod_spawner_subtype_quadrants_quadrant_##m,
static const CTestCase pod_spawner_subtype_quadrants_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) ENTRY(10) ENTRY(11) ENTRY(12) ENTRY(13) ENTRY(14) ENTRY(15) ENTRY(16) ENTRY(17) ENTRY(18) ENTRY(19) ENTRY(20) ENTRY(21) ENTRY(22) ENTRY(23) ENTRY(24) ENTRY(25) ENTRY(26) ENTRY(27) ENTRY(28) ENTRY(29) ENTRY(30) ENTRY(31) ENTRY(32) ENTRY(33) ENTRY(34) };
static const u32 pod_spawner_subtype_quadrants_cases_expected[] = { 0x1000103u, 0x1000203u, 0x1000203u, 0x1000003u, 0x1000003u, 0x1000303u, 0x1000303u, 0x1000103u, 0x1000203u, 0x1000203u, 0x1000203u, 0x1000203u, 0x1000303u, 0x1000303u, 0x1000303u, 0x1000303u, 0x1000103u, 0x1000103u, 0x1000003u, 0x1000003u, 0x1000003u, 0x1000003u, 0x1000103u, 0x1000103u, 0x902u, 0x902u, 0x1010103u, 0x1000103u, 0x1000103u, 0x1000902u, 0x902u, 0x902u, 0x902u, 0x902u, 0x902u };
#undef CASE
#undef ENTRY

static const u32 func_8005A538_expected[] = { 0u, 0u, 1u, 0u, 0u, 0u, 3u, 0u, 8u, 0u, 1u, 1u, 7u, 2u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8005A538(u32 row)
{
    u32 observed_values[19];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&main_objects, 0, sizeof(main_objects));
    child_0_present = 255;
    pool_0_full = 255;
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 48; ++slot)
            main_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8005A538(&obj);
    observed_values[0] = (u32)((u8*)&child_0.ext)[0];
    observed_values[1] = (u32)((u8*)&child_0.ext)[1];
    observed_values[2] = (u32)main_objects[0].active;
    observed_values[3] = (u32)main_objects[0].id;
    observed_values[4] = (u32)main_objects[0].unk2;
    observed_values[5] = (u32)obj.air_state;
    observed_values[6] = (u32)obj.contact_damage;
    observed_values[7] = (u32)obj.gravity;
    observed_values[8] = (u32)obj.hp;
    observed_values[9] = (u32)obj.invincibility_timer;
    observed_values[10] = (u32)obj.on_screen;
    observed_values[11] = (u32)obj.state;
    observed_values[12] = (u32)obj.unk16;
    observed_values[13] = (u32)obj.unk5;
    observed_values[14] = (u32)obj.unk6;
    observed_values[15] = (u32)obj.unk7C;
    observed_values[16] = (u32)obj.x_accel;
    observed_values[17] = (u32)obj.x_speed;
    observed_values[18] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, func_8005A538_expected, 19);
}

static const u32 inputs_0[2][5] = {
    { 255, 255, 255, 0, 0 },
    { 255, 255, 255, 1, 0 },
};
struct pod_spawner_despawn_case {
    u32 expected[2];
};
static const struct pod_spawner_despawn_case pod_spawner_despawn_cases[] = {
    { { 2u, 0u } },
    { { 2u, 0u } },
};
static u32 test_pod_spawner_despawn(u32 row)
{
    const struct pod_spawner_despawn_case* c = &pod_spawner_despawn_cases[row];
    u32 observed_values[2];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    struct Main29Record child_1;
    u8 child_1_present;
    struct Main29Record child_2;
    u8 child_2_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&child_2, 0, sizeof(child_2));
    child_0_present = inputs_0[row][0];
    child_1_present = inputs_0[row][1];
    child_2_present = inputs_0[row][2];
    child_2.unk0 = inputs_0[row][3];
    child_2.unk1 = inputs_0[row][4];
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    child_0.ext.main_29.slots.controller.target = child_1_present ? &child_1 : NULL;
    child_0.ext.main_29.slots.controller.record = child_2_present ? &child_2 : NULL;
    pod_spawner_despawn(&obj);
    observed_values[0] = (u32)child_1.unk4;
    observed_values[1] = (u32)child_2.unk4;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "pod_spawner_children_context", pod_spawner_children_context_cases, pod_spawner_children_context_cases_expected, COUNT(pod_spawner_children_context_cases), 0 },
    { "pod_spawner_linked_cleanup", pod_spawner_linked_cleanup_cases, pod_spawner_linked_cleanup_cases_expected, COUNT(pod_spawner_linked_cleanup_cases), 0 },
    { "pod_spawner_quadrant_context", pod_spawner_quadrant_context_cases, pod_spawner_quadrant_context_cases_expected, COUNT(pod_spawner_quadrant_context_cases), 0 },
    { "pod_spawner_spawn", pod_spawner_spawn_cases, pod_spawner_spawn_cases_expected, COUNT(pod_spawner_spawn_cases), 0 },
    { "pod_spawner_subtype_quadrants", pod_spawner_subtype_quadrants_cases, pod_spawner_subtype_quadrants_cases_expected, COUNT(pod_spawner_subtype_quadrants_cases), 0 },
    { "func_8005A538", 0, 0, 1, test_func_8005A538 },
    { "pod_spawner_despawn", 0, 0, 2, test_pod_spawner_despawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pod_spawner_children_context_cases) + COUNT(pod_spawner_linked_cleanup_cases) + COUNT(pod_spawner_quadrant_context_cases) + COUNT(pod_spawner_spawn_cases) + COUNT(pod_spawner_subtype_quadrants_cases) + 1 + 2;
