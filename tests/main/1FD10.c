#include "test_runtime.h"
#include "main/1FD10.h"
#include "main/55C4.h"
#include "main/2824.h"
#include "main/1AC84.h"
#include "main/3D88.h"

static u32 transition_case(u32 mode)
{
    struct EngineObj obj, expected;
    struct AbcObj abc_before;
    struct PlayerObj player_before = g_Player;
    struct MiscObj expected_pool[64];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    obj.unk1 = 3;
    obj.unk2 = 4;
    obj.unk3 = mode == 4 ? 6 : 7;
    obj.unk5F = 9;
    obj.stage = 5;
    obj.substage = 2;
    abc_object.unkC = mode == 3 ? 1 : 0;
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 39;
        misc_objects[i].unk2 = 9;
        misc_objects[i].state = 40;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].unk7 = 5;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        misc_objects[i].unk42 = 0x7777;
    }
    if (mode >= 1)
        misc_objects[61].active = 0;
    if (mode >= 2)
        misc_objects[63].active = 0;
    expected = obj;
    abc_before = abc_object;
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    if (mode != 3) {
        if (mode == 4) {
            expected.unk3 = 7;
            expected.unk2 = 1;
        } else {
            expected.unk5F = 3;
            expected.unk1 = 4;
            expected.unk2 = 0;
            expected.unk3 = 0;
            if (mode >= 1) {
                expected_pool[61].active = 0x41;
                expected_pool[61].id = 15;
                expected_pool[61].unk2 = 0;
            }
            if (mode == 2) {
                expected_pool[63].active = 0x41;
                expected_pool[63].id = 15;
                expected_pool[63].unk2 = 1;
            }
        }
    }
    func_8002F5E8(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(expected_pool) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)expected_pool)[i]);
    for (i = 0; i < sizeof(abc_object) / 4; i++)
        assert(((u32*)&abc_object)[i] == ((u32*)&abc_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    actual = (u8)obj.unk1 | ((u32)(u8)obj.unk3 << 8) | ((u32)misc_objects[61].active << 16) | ((u32)misc_objects[63].active << 24);
    return actual;
}
static const u32 engine_transition_two_misc_pool_cases_expected[] = { 0x1010004u, 0x1410004u, 0x41410004u, 0x703u, 0x703u };

extern struct Unk5 D_800F0E18[];
void func_8002FB54(struct EngineObj*);
void func_8002F510(struct EngineObj*);
void func_8002F524(struct EngineObj*);
void func_8002F584(struct EngineObj*);
void func_8002F7A8(struct EngineObj*);
void func_8002F828(struct EngineObj*);
void func_8002F8F8(struct EngineObj*);
void func_8002F92C(struct EngineObj*);
void func_8002F9EC(struct EngineObj*);
void func_8002FAB0(struct EngineObj*);
void func_8002FAE4(struct EngineObj*);
void func_8002FBDC(struct EngineObj* arg0);
#ifdef MMX4_PC
#include <stdlib.h>
#endif
extern s32 D_80139538, D_80139540, D_80139544;
extern s16 D_80139560;

struct SceneContext {
    struct EngineObj engine;
    struct PlayerObj player;
};
static struct QuadObj expected_quads[32];
static struct EffectObj expected_effects[32];
static struct MiscObj expected_misc[64];

static void scene_engine(struct EngineObj* obj, u8 phase, struct SceneContext* context)
{
    memset(obj, 0, sizeof(*obj));
    obj->state = 3;
    obj->unk1 = 11;
    obj->unk2 = phase;
    obj->unk4 = 9;
    obj->stage = 3;
    obj->substage = 1;
    obj->cur_character = CHARACTER_ZERO;
    context->engine = engine_obj;
    context->player = g_Player;
}

static void scene_check(const struct EngineObj* obj, const struct EngineObj* expected,
    const struct SceneContext* context)
{
    c_test_same_words(obj, expected, sizeof(*obj));
    c_test_same_words(&engine_obj, &context->engine, sizeof(engine_obj));
    c_test_same_words(&g_Player, &context->player, sizeof(g_Player));
}

static u32 test_card_start(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    scene_engine(&obj, 0, &context);
    obj.unk3 = 7;
    expected = obj;
    expected.unk2 = 1;
    expected.unk3 = 0;
    func_8002F510(&obj);
    scene_check(&obj, &expected, &context);
    return 1;
}

static u32 test_card_allocation(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    struct QuadObj previous;
    u32 i, availability = row % 3, slot = availability == 1 ? 0 : 31;
    scene_engine(&obj, 1, &context);
    memset(g_QuadObjects, 0x5A, sizeof(g_QuadObjects));
    memset(&previous, 0, sizeof(previous));
    obj.unk3 = row / 3;
    obj.unk3C = BASE_OBJECT(&previous);
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = 1;
    if (availability)
        g_QuadObjects[slot].active = 0;
    expected = obj;
    memcpy(expected_quads, g_QuadObjects, sizeof(expected_quads));
    if (availability) {
        expected_quads[slot].active = -0x7F;
        expected_quads[slot].id = 1;
        expected_quads[slot].unk2 = obj.unk3 + 16;
        expected.unk2 = 2;
        expected.unk3C = BASE_OBJECT(&g_QuadObjects[slot]);
    }
    func_8002F524(&obj);
    scene_check(&obj, &expected, &context);
    c_test_same_words(g_QuadObjects, expected_quads, sizeof(expected_quads));
    assert(previous.active == 0 && previous.state == 0);
    return 1;
}

static u32 test_card_completion(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    struct QuadObj linked, linked_before;
    struct AbcObj dialogue_expected;
    u32 state = row % 3;
    scene_engine(&obj, 2, &context);
    memset(&linked, 0, sizeof(linked));
    memset(&abc_object, 0, sizeof(abc_object));
    linked.active = -0x7F;
    linked.id = 1;
    linked.state = state;
    linked.x_pos.val = 100 * 65536 + 0x1234;
    obj.unk3 = row / 3;
    obj.unk3C = BASE_OBJECT(&linked);
    abc_object.unkC = 0x80;
    abc_object.unk10 = 9;
    abc_object.unkA = 0x27;
    abc_object.unkD = 4;
    dialogue_expected = abc_object;
    linked_before = linked;
    expected = obj;
    if (state == 2) {
        expected.unk2 = 3;
        dialogue_expected.unk10 = obj.unk3 | 0x8000;
    }
    func_8002F584(&obj);
    scene_check(&obj, &expected, &context);
    c_test_same_words(&linked, &linked_before, sizeof(linked));
    c_test_same_words(&abc_object, &dialogue_expected, sizeof(abc_object));
    return 1;
}

static const struct {
    u16 seed, next;
    u8 spawns;
} particle_random[] = {
    { 0, 0, 0 },
    { 1, 1, 0 },
    { 2, 2, 1 },
    { 0xFF, 0x201, 0 },
    { 0x1234, 0x366A, 1 },
    { 0xFFFF, 0xFFFE, 1 },
};

static u32 test_countdown_particles(u32 row)
{
    static const s16 timers[3] = { 150, 2, 1 };
    struct EngineObj obj, expected;
    struct SceneContext context;
    u32 i, index = row / 6, timer = row / 2 % 3, available = row % 2;
    u32 slot = index % 2 ? 0 : 31;
    scene_engine(&obj, 5, &context);
    obj.unk4 = timers[timer];
    memset(g_QuadObjects, 0x5A, sizeof(g_QuadObjects));
    memset(effect_objects, 0x5A, sizeof(effect_objects));
    for (i = 0; i < 32; i++) {
        g_QuadObjects[i].active = 1;
        effect_objects[i].active = 1;
        g_QuadObjects[i].x_pos.val = 100 * 65536 + 0x1234;
        g_QuadObjects[i].y_pos.val = 200 * 65536 + 0x5678;
    }
    if (available) {
        g_QuadObjects[slot].active = 0;
        effect_objects[slot].active = 0;
    }
    cur_random = particle_random[index].seed;
    expected = obj;
    expected.unk4 = timers[timer] - 1;
    memcpy(expected_quads, g_QuadObjects, sizeof(expected_quads));
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    if (timer == 2) {
        expected.unk2 = 6;
        if (available) {
            expected_effects[slot].active = 1;
            expected_effects[slot].id = 2;
            expected_effects[slot].unk2 = 12;
        }
    } else if (available && particle_random[index].spawns) {
        expected_quads[slot].active = 1;
        expected_quads[slot].id = 6;
        expected_quads[slot].x_pos.i.hi = 0x9C0;
        expected_quads[slot].y_pos.i.hi = 0x70;
    }
    func_8002F92C(&obj);
    scene_check(&obj, &expected, &context);
    c_test_same_words(g_QuadObjects, expected_quads, sizeof(expected_quads));
    c_test_same_words(effect_objects, expected_effects, sizeof(expected_effects));
    assert(cur_random == (timer == 2 ? particle_random[index].seed : particle_random[index].next));
    return 1;
}

static const struct {
    s32 upper, lower, next_upper, next_lower;
    u8 complete;
} curtain_positions[] = {
    { 0x82000, 0x12345, 0x1000, 0x93345, 0 },
    { 0x81000, 0x12345, 0, 0x93345, 0 },
    { 0x80FFF, 0x12345, 0, 0x1000000, 1 },
    { 0x1000, 0x12345, 0, 0x1000000, 1 },
    { 0, 0x12345, 0, 0x1000000, 1 },
    { 0x1000000, 0x12345, 0xF7F000, 0x93345, 0 },
};

static u32 test_curtain_motion(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    struct BackgroundObj backgrounds_expected[3];
    u32 i, index = row / 3, ready = row % 3;
    scene_engine(&obj, 3, &context);
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = (100 + i) * 65536 + 0x1234;
        background_objects[i].y_pos.val = (200 + i) * 65536 + 0x5678;
        background_objects[i].unk14.val = 0x13572468;
        background_objects[i].unk18.val = 0x24681357;
    }
    background_objects[1].y_pos.val = curtain_positions[index].upper;
    background_objects[2].y_pos.val = curtain_positions[index].lower;
    D_80173C84 = ready;
    expected = obj;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    backgrounds_expected[0].unk14 = backgrounds_expected[0].x_pos;
    backgrounds_expected[0].unk18 = backgrounds_expected[0].y_pos;
    if (ready == 2) {
        backgrounds_expected[1].y_pos.val = curtain_positions[index].next_upper;
        backgrounds_expected[2].y_pos.val = curtain_positions[index].next_lower;
        if (curtain_positions[index].complete) {
            expected.unk2 = 4;
            expected.unk4 = 30;
        }
    }
    func_8002FBDC(&obj);
    scene_check(&obj, &expected, &context);
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    assert(D_80173C84 == ready);
    return 1;
}

static u32 test_fixed_countdowns(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    u32 second = row / 2;
    scene_engine(&obj, second ? 7 : 4, &context);
    obj.unk4 = row % 2 ? 2 : 1;
    expected = obj;
    if (row % 2)
        expected.unk4 = 1;
    else {
        expected.unk2++;
        expected.unk4 = second ? 300 : 150;
    }
    if (second)
        func_8002FAB0(&obj);
    else
        func_8002F8F8(&obj);
    scene_check(&obj, &expected, &context);
    return 1;
}

static u32 test_flash_completion(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    u32 i, complete = row / 3, availability = row % 3, slot = availability == 1 ? 0 : 63;
    scene_engine(&obj, 6, &context);
    memset(misc_objects, 0x5A, sizeof(misc_objects));
    memset(effect_objects, 0x5A, sizeof(effect_objects));
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    if (availability)
        misc_objects[slot].active = 0;
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = i % 4 == 3 ? 0 : 1;
        effect_objects[i].id = i % 4 == 2 ? 3 : 2;
        effect_objects[i].unk2 = i % 4 == 1 ? 11 : 12;
    }
    g_FilterAmountR = complete ? 31 : 30;
    g_FilterAmountG = 7;
    g_FilterAmountB = 9;
    g_FilterModeR = 1;
    g_FilterModeG = 2;
    g_FilterModeB = 3;
    need_palette_load = 0x80;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 9;
    expected = obj;
    memcpy(expected_misc, misc_objects, sizeof(expected_misc));
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    if (complete) {
        expected.unk2 = 7;
        expected.unk4 = 120;
        for (i = 0; i < 32; i++)
            if (i % 4 == 0)
                memset(&expected_effects[i], 0, 8);
        if (availability) {
            expected_misc[slot].active = 0x41;
            expected_misc[slot].id = 50;
            expected_misc[slot].unk2 = 0;
        }
    }
    func_8002F9EC(&obj);
    scene_check(&obj, &expected, &context);
    c_test_same_words(misc_objects, expected_misc, sizeof(expected_misc));
    c_test_same_words(effect_objects, expected_effects, sizeof(expected_effects));
    assert(g_FilterAmountR == (complete ? 0 : 30));
    assert(g_FilterAmountG == (complete ? 0 : 7));
    assert(g_FilterAmountB == (complete ? 0 : 9));
    assert(g_FilterModeR == 1 && g_FilterModeG == 2 && g_FilterModeB == 3);
    assert(need_palette_load == (complete ? 0x81 : 0x80));
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == (complete ? 0 : 9));
    return 1;
}

static void scene_threads_init(void)
{
#ifdef MMX4_PC
    mmx4_pc_threads_init();
#endif
}

static void check_scene_fade_thread(void)
{
#ifdef MMX4_PC
    struct GameThread expected[4];
    u32 i;
    memset(expected, 0, sizeof(expected));
    expected[2].state = 2;
    for (i = 0; i < 4; i++)
        c_test_same_words(mmx4_pc_thread_slot(i), &expected[i], sizeof(expected[i]));
#endif
}

static u32 test_boss_intro_banner(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    struct MainBssState main_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 i, availability = row % 3, slot = availability == 1 ? 0 : 63;
    scene_engine(&obj, 1, &context);
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(background_objects, 0, sizeof(background_objects));
    memset(misc_objects, 0x5A, sizeof(misc_objects));
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    if (availability)
        misc_objects[slot].active = 0;
    D_8013B810 = row / 3 + 1;
    scene_threads_init();
    expected = obj;
    expected.unk2 = 2;
    main_expected = main_bss_state;
    main_expected.transition.active = 1;
    main_expected.transition.fade_amount = 8;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    backgrounds_expected[2].unk4C = 1;
    memcpy(expected_misc, misc_objects, sizeof(expected_misc));
    if (availability) {
        expected_misc[slot].active = 0x41;
        expected_misc[slot].id = 50;
        expected_misc[slot].unk2 = row / 3 + 1;
        expected_misc[slot].x_pos.i.hi = 256;
        expected_misc[slot].y_pos.i.hi = 112;
    }
    func_8002F7A8(&obj);
    scene_check(&obj, &expected, &context);
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(misc_objects, expected_misc, sizeof(expected_misc));
    assert(D_8013B810 == row / 3 + 1);
    check_scene_fade_thread();
    return 1;
}

static u32 test_intro_fade_out(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    struct MainBssState main_expected;
    struct BackgroundObj backgrounds_expected[3];
    scene_engine(&obj, 8, &context);
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.val = 100 * 65536 + 0x1234;
    obj.unk4 = row % 2 ? 2 : 1;
    scene_threads_init();
    if (row >= 2)
        func_800129F0(3);
    expected = obj;
    expected.unk4--;
    main_expected = main_bss_state;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    backgrounds_expected[0].x_pos.val = 94 * 65536 + 0x1234;
    if (row % 2 == 0) {
        expected.unk2 = 9;
        if (row < 2) {
            main_expected.transition.active = -1;
            main_expected.transition.fade_amount = 8;
        }
    }
    func_8002FAE4(&obj);
    scene_check(&obj, &expected, &context);
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    if (row != 1)
        check_scene_fade_thread();
    return 1;
}

static u16 scene_cd_enabled(void)
{
#ifdef MMX4_PC
    return Psyz_SpuRead(0x1AA) & 1;
#else
    return *(volatile u16*)0x1F801DAA & 1;
#endif
}

static u32 test_intro_music_start(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    struct MainBssState main_before;
    struct Unk5 archive_before = D_800F0E18[XA_ARCHIVE_BOSS_INTRO];
    CdlLOC expected_location;
    u32 i, waiting = row % 2, boss = row / 2;
    s32 start = archive_before.unk0 + boss;
#ifdef MMX4_PC
    Psyz_SpuInit();
#endif
    scene_engine(&obj, 2, &context);
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    main_bss_state.transition.active = waiting;
    main_bss_state.transition.fade_amount = 8;
    D_8013B810 = boss + 1;
    D_80171EA9 = 1;
    D_80139538 = 123;
    D_80137CC0 = 3;
    D_80139540 = 44;
    D_80139544 = 99;
    D_80139560 = XA_ARCHIVE_BGM1;
    D_80139568 = 0;
    D_80139530 = 0;
    D_80141BD4 = 0;
    D_80173C84 = 0;
    D_80175EE8[0] = 0x35353535;
    D_80139514 = 0x27272727;
    func_80016420(7);
    SsSetSerialAttr(0, 0, 0);
    main_before = main_bss_state;
    expected = obj;
    memset(&expected_location, 0x27, sizeof(expected_location));
    if (!waiting) {
        expected.unk2 = 3;
        expected.unk4 = 16;
        CdIntToPos(start, &expected_location);
    }
    func_8002F828(&obj);
    scene_check(&obj, &expected, &context);
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(&D_800F0E18[XA_ARCHIVE_BOSS_INTRO], &archive_before, sizeof(archive_before));
    for (i = 0; i < sizeof(expected_location); i++)
        assert(((u8*)&D_80139514)[i] == ((u8*)&expected_location)[i]);
    assert(D_80139538 == (waiting ? 123 : archive_before.unk4));
    assert(D_80137CC0 == (waiting ? 3 : archive_before.unk8));
    assert(D_80139540 == (waiting ? 44 : start));
    assert(D_80139544 == (waiting ? 99 : start + 273 * 8));
    assert(D_80139560 == (waiting ? XA_ARCHIVE_BGM1 : XA_ARCHIVE_BOSS_INTRO));
    assert(D_80139568 == !waiting);
    assert(D_80139530 == (waiting ? 0 : 7));
    assert(D_80141BD4 == (waiting ? 0 : 2));
    assert(D_80173C84 == !waiting);
    assert((u32)D_80175EE8[0] == (waiting ? 0x35353535u : 0x35350001u | boss << 8));
    assert(D_80139524 == (waiting ? 7 : 127) && D_80139528 == D_80139524);
    assert(D_80139520.val0 == D_80139524 && D_80139520.val2 == D_80139524);
    assert(D_80139520.val1 == 0 && D_80139520.val3 == 0);
    assert(D_80171EA9 == 1 && D_8013B810 == boss + 1);
    assert(scene_cd_enabled() == !waiting);
    return 1;
}

#ifdef MMX4_PC
static void intro_fill_pools(u8 value)
{
#define FILL(pool) memset(&(pool), value, sizeof(pool))
    FILL(g_Player);
    FILL(g_Entity);
    FILL(foo_objects);
    FILL(baz_objects);
    FILL(weapon_objects);
    FILL(main_objects);
    FILL(shot_objects);
    FILL(visual_objects);
    FILL(effect_objects);
    FILL(item_objects);
    FILL(misc_objects);
    FILL(unk_objects);
    FILL(layer_objects);
    FILL(g_QuadObjects);
    FILL(qux_object);
    FILL(bar_object);
    FILL(abc_object);
#undef FILL
}

static void intro_check_bytes(const void* memory, u32 size, u8 value)
{
    const u8* bytes = memory;
    u32 i;
    for (i = 0; i < size; i++)
        assert(bytes[i] == value);
}

static void intro_check_pools(u8 value)
{
#define CHECK(pool) intro_check_bytes(pool, sizeof(pool), value)
    intro_check_bytes(&g_Player, sizeof(g_Player), value);
    intro_check_bytes(&g_Entity, sizeof(g_Entity), value);
    CHECK(foo_objects);
    CHECK(baz_objects);
    CHECK(weapon_objects);
    CHECK(main_objects);
    CHECK(shot_objects);
    CHECK(visual_objects);
    CHECK(effect_objects);
    CHECK(item_objects);
    CHECK(misc_objects);
    CHECK(unk_objects);
    CHECK(layer_objects);
    CHECK(g_QuadObjects);
    intro_check_bytes(&qux_object, sizeof(qux_object), value);
    intro_check_bytes(&bar_object, sizeof(bar_object), value);
    intro_check_bytes(&abc_object, sizeof(abc_object), value);
#undef CHECK
}

static u32 test_intro_restore(u32 row)
{
    struct EngineObj obj, expected;
    struct SceneContext context;
    struct MainBssState main_before;
    struct BackgroundObj backgrounds_expected[3];
    u32 i, waiting = row % 2, substage = row / 2 % 2, stage = row / 4 + 1;
    s16 left, right;
    int configured = setenv("SDL_AUDIODRIVER", "dummy", 1);
    assert(configured == 0);
    Psyz_SpuInit();
    func_80014DC4();
    scene_engine(&obj, 9, &context);
    obj.stage = 13;
    obj.substage = 1;
    obj.unk3 = 7;
    D_8013B810 = stage;
    D_8013B814 = substage;
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    main_bss_state.transition.active = waiting ? -1 : 0;
    main_bss_state.transition.fade_amount = 8;
    memset(background_objects, 0x25, sizeof(background_objects));
    background_objects[0].x_pos.val = 100 * 65536 + 0x1234;
    intro_fill_pools(0x25);
    context.player = g_Player;
    for (i = 0; i < 4; i++) {
        D_80173C6C[i] = 9;
        D_8013E188[i] = 9;
    }
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 5;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 1;
    D_80141BD4 = 2;
    D_80139564 = 0;
    D_80139568 = 1;
    D_80139530 = 7;
    D_80173C84 = 2;
    D_80171EA9 = 1;
    func_80016420(42);
    SsSetSerialAttr(0, 0, 1);
    for (i = 0; i < 24; i++)
        assert(SsUtSetVVol(i, 127, 64) == 0);
    SsSeqCalledTbyT();
    for (i = 0; i < 24; i++) {
        assert(SsUtGetVVol(i, &left, &right) == 0);
        assert(left > 0 && right > 0);
    }
    expected = obj;
    main_before = main_bss_state;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    if (waiting) {
        backgrounds_expected[0].x_pos.val = 94 * 65536 + 0x1234;
    } else {
        expected.state = 4;
        expected.unk1 = expected.unk2 = expected.unk3 = 0;
        expected.stage = stage;
        expected.substage = substage;
        memset(&context.player, 0, sizeof(context.player));
        memset(backgrounds_expected, 0, sizeof(backgrounds_expected));
        for (i = 0; i < 3; i++)
            backgrounds_expected[i].unk2 = i;
    }
    func_8002FB54(&obj);
    SsSeqCalledTbyT();
    scene_check(&obj, &expected, &context);
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    intro_check_pools(waiting ? 0x25 : 0);
    for (i = 0; i < 4; i++) {
        assert(D_80173C6C[i] == (waiting ? 9 : i + 3));
        assert(D_8013E188[i] == (waiting ? 9 : 0));
    }
    assert(g_FilterAmountR == (waiting ? 5 : 0));
    assert(g_FilterAmountG == (waiting ? 5 : 0));
    assert(g_FilterAmountB == (waiting ? 5 : 0));
    assert(g_FilterModeR == (waiting ? 1 : 0));
    assert(g_FilterModeG == (waiting ? 1 : 0));
    assert(g_FilterModeB == (waiting ? 1 : 0));
    assert(D_80139568 == waiting && D_80139530 == (waiting ? 7 : 0));
    assert(D_80173C84 == (waiting ? 2 : 0));
    assert(D_80139524 == (waiting ? 42 : 0));
    assert(D_80139528 == D_80139524);
    assert(D_80139564 == 0 && D_80141BD4 == 2);
    assert(scene_cd_enabled() == waiting);
    assert(D_8013B810 == stage && D_8013B814 == substage);
    for (i = 0; i < 24; i++) {
        assert(SsUtGetVVol(i, &left, &right) == 0);
        assert(waiting ? left > 0 && right > 0 : left == 0 && right == 0);
    }
    return 1;
}
#define INTRO_RESTORE_CASE_COUNT 32
#else
#define INTRO_RESTORE_CASE_COUNT 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "engine_transition_two_misc_pool", NULL, engine_transition_two_misc_pool_cases_expected, COUNT(engine_transition_two_misc_pool_cases_expected), transition_case },
    { "card_start", 0, 0, 1, test_card_start },
    { "card_allocation", 0, 0, 3, test_card_allocation },
    { "card_completion", 0, 0, 3, test_card_completion },
    { "countdown_particles", 0, 0, 14, test_countdown_particles },
    { "curtain_motion", 0, 0, 9, test_curtain_motion },
    { "fixed_countdowns", 0, 0, 4, test_fixed_countdowns },
    { "flash_completion", 0, 0, 6, test_flash_completion },
    { "boss_intro_banner", 0, 0, 3, test_boss_intro_banner },
    { "intro_fade_out", 0, 0, 4, test_intro_fade_out },
    { "intro_music_start", 0, 0, 4, test_intro_music_start },
#ifdef MMX4_PC
    { "intro_restore", 0, 0, INTRO_RESTORE_CASE_COUNT, test_intro_restore },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(engine_transition_two_misc_pool_cases_expected) + 1 + 3 + 3 + 14 + 9 + 4 + 6 + 3 + 4 + 4
#ifdef MMX4_PC
    + INTRO_RESTORE_CASE_COUNT
#endif
    ;
