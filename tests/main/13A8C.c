#include "test_runtime.h"
#include "main/menu.h"
#include "main/165A0.h"
#include "main/2824.h"
#include "main/323C.h"
#include "main/55C4.h"
#include "main/144A4.h"
#include "main/background.h"
#include "main/stage_objects.h"
#include "main/objects.h"
#include "main/hud_origins.h"
#include "main/stage_layouts.h"
#include "main/1A5BC.h"
#include "main/3D88.h"
extern struct Unk5 D_800F0E18[];
extern struct BackgroundLayoutConfigData D_800F3188;
#ifdef MMX4_PC
#include <unistd.h>
#include <psyz/cd.h>
#include <psyz/spu.h>
#include <stdlib.h>
#endif

void func_80023624(struct EngineObj*);
void func_80023684(struct EngineObj*);
void func_80023698(struct EngineObj*);
void func_800237E4(struct EngineObj*);
void func_80023870(struct EngineObj*);
void func_800238F0(struct EngineObj*);
void func_80023970(struct EngineObj*);
void func_800239E0(struct EngineObj*);
void func_80023A54(struct EngineObj*);
void func_80023B98(struct MiscObj*);
void func_80023C0C(struct MiscObj*);
extern union AnimationStep* D_800F307C[3];

static struct EngineObj global_before;
static struct PlayerObj player_before;
static struct MainBssState main_expected;
static struct BackgroundObj backgrounds_expected[3];
static struct MiscObj misc_expected[64];
static struct ControllerInput input_before;
static u16 random_expected;
static s32 music_before;
static u8 palette_expected;
static u16 thread0_expected;

static void prepare(struct EngineObj* obj, u32 character, u32 step)
{
    u32 i;
    memset(obj, 0x25, sizeof(*obj));
    memset(&engine_obj, 0x35, sizeof(engine_obj));
    memset(&g_Player, 0x45, sizeof(g_Player));
    memset(&main_bss_state, 0x55, sizeof(main_bss_state));
    memset(background_objects, 0x65, sizeof(background_objects));
    memset(misc_objects, 0x75, sizeof(misc_objects));
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    obj->state = 11;
    obj->unk1 = step;
    obj->unk2 = 0;
    obj->stage = 15;
    obj->substage = 1;
    obj->cur_character = character;
    main_bss_state.transition.active = 0;
    main_bss_state.transition.fade_amount = 5;
    background_objects[0].unk3 = 1;
    background_objects[1].unk3 = 0;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    cur_random = 0x1234;
    D_80173C84 = 1;
    thread0_expected = 0;
#ifdef MMX4_PC
    mmx4_pc_threads_init();
#endif
}

static void capture(void)
{
    global_before = engine_obj;
    player_before = g_Player;
    main_expected = main_bss_state;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    input_before = controller_input;
    random_expected = cur_random;
    music_before = D_80173C84;
    palette_expected = need_palette_load;
}

static void check_world(void)
{
    c_test_same_words(&engine_obj, &global_before, sizeof(global_before));
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_expected));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    assert(c_test_word_difference((const u32*)misc_objects,
               (const u32*)misc_expected, sizeof(misc_expected) / 4)
        == 0);
    assert(controller_input.held == input_before.held);
    assert(controller_input.previous == input_before.previous);
    assert(controller_input.pressed == input_before.pressed);
    assert(cur_random == random_expected && D_80173C84 == music_before);
    assert(need_palette_load == palette_expected);
#ifdef MMX4_PC
    {
        struct GameThread expected[4];
        u32 i;
        memset(expected, 0, sizeof(expected));
        expected[0].state = thread0_expected;
        expected[2].state = main_expected.transition.active ? 2 : 0;
        for (i = 0; i < 4; i++)
            c_test_same_words(mmx4_pc_thread_slot(i), &expected[i], sizeof(expected[i]));
    }
#endif
}

static void start_fade(u32 fade)
{
    if (fade == 1)
        func_800129A4(5);
    else if (fade == 2)
        func_800129F0(5);
}

static u32 test_start_delay(u32 character)
{
    struct EngineObj obj, expected;
    prepare(&obj, character, 1);
    capture();
    expected = obj;
    expected.unk1 = 2;
    func_80023684(&obj);
    c_test_same_words(&obj, &expected, sizeof(expected));
    check_world();
    return 1;
}

static const struct {
    u8 phase, music, advances;
    s32 y, next_y;
} first_scroll[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0 },
    { 0, 2, 0, 0, 0 },
    { 1, 2, 0, 4303 * 65536, 4303 * 65536 + 0x7000 },
    { 1, 2, 0, 4303 * 65536 + 0x8FFF, 4303 * 65536 + 0xFFFF },
    { 1, 2, 1, 4303 * 65536 + 0x9000, 4304 * 65536 },
    { 1, 2, 1, 4303 * 65536 + 0xFFFF, 4304 * 65536 + 0x6FFF },
    { 1, 2, 0, 4302 * 65536 + 0xFFFF, 4303 * 65536 + 0x6FFF },
};

static u32 test_first_scroll(u32 row)
{
    struct EngineObj obj, expected;
    u32 index = row % COUNT(first_scroll), fade = row / COUNT(first_scroll) % 3;
    prepare(&obj, row / (3 * COUNT(first_scroll)), 3);
    obj.unk2 = first_scroll[index].phase;
    obj.unk4 = 0;
    D_80173C84 = first_scroll[index].music;
    background_objects[0].y_pos.val = first_scroll[index].y;
    start_fade(fade);
    capture();
    expected = obj;
    if (fade == 0) {
        backgrounds_expected[0].y_pos.val = first_scroll[index].next_y;
        if (index == 2)
            expected.unk2 = 1;
        if (first_scroll[index].advances) {
            expected.unk1 = 4;
            expected.unk2 = 0;
            expected.unk4 = 420;
        }
    }
    func_800237E4(&obj);
    c_test_same_words(&obj, &expected, sizeof(expected));
    check_world();
    return 1;
}

static const s16 delays[] = { 1, 2, 180, 420 };

static u32 test_final_spark(u32 row)
{
    struct EngineObj obj, expected;
    u32 availability = row % 3, timer = row / 3 % COUNT(delays);
    u32 slot = availability == 1 ? 0 : 63;
    prepare(&obj, row / (3 * COUNT(delays)), 4);
    obj.unk4 = delays[timer];
    if (availability)
        misc_objects[slot].active = 0;
    capture();
    expected = obj;
    expected.unk4--;
    if (timer == 0) {
        expected.unk1 = 5;
        expected.unk4 = 180;
        if (availability) {
            misc_expected[slot].active = 0x41;
            misc_expected[slot].id = 0x38;
            misc_expected[slot].unk2 = 2;
            misc_expected[slot].ext.title_logo.palette_shift_speed = 0;
        }
    }
    func_80023870(&obj);
    c_test_same_words(&obj, &expected, sizeof(expected));
    check_world();
    return 1;
}

static const struct {
    s32 y, next_y;
    u8 advances;
} second_scroll[] = {
    { 4304 * 65536, 4304 * 65536 + 0x8000, 0 },
    { 4479 * 65536, 4479 * 65536 + 0x8000, 0 },
    { 4479 * 65536 + 0x7FFF, 4479 * 65536 + 0xFFFF, 0 },
    { 4479 * 65536 + 0x8000, 4480 * 65536, 1 },
    { 4479 * 65536 + 0xFFFF, 4480 * 65536 + 0x7FFF, 1 },
};

static u32 test_second_scroll(u32 row)
{
    static const s16 timers[] = { 0, 1, 180 };
    struct EngineObj obj, expected;
    u32 index = row % COUNT(second_scroll), timer = row / COUNT(second_scroll) % 3;
    prepare(&obj, row / (3 * COUNT(second_scroll)), 5);
    obj.unk4 = timers[timer];
    background_objects[0].y_pos.val = second_scroll[index].y;
    capture();
    expected = obj;
    if (timer) {
        expected.unk4--;
    } else {
        backgrounds_expected[0].y_pos.val = second_scroll[index].next_y;
        if (second_scroll[index].advances) {
            expected.unk1 = 6;
            backgrounds_expected[0].unk3 = 0;
            backgrounds_expected[1].unk3 = 1;
        }
    }
    func_800238F0(&obj);
    c_test_same_words(&obj, &expected, sizeof(expected));
    check_world();
    return 1;
}

static u32 test_portrait_scroll(u32 row)
{
    static const s32 offsets[] = { -65536, -32769, -32768, -1, -65537 };
    static const s16 endpoints[] = { 768, 1536 };
    struct EngineObj obj, expected;
    u32 character = row / COUNT(offsets), index = row % COUNT(offsets);
    prepare(&obj, character, 6);
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 1;
    background_objects[1].y_pos.val = endpoints[character] * 65536 + offsets[index];
    capture();
    expected = obj;
    backgrounds_expected[1].y_pos.val += 32768;
    if (index == 2 || index == 3) {
        expected.unk1 = 7;
        main_expected.transition.active = -1;
        main_expected.transition.fade_amount = 8;
    }
    func_80023970(&obj);
    c_test_same_words(&obj, &expected, sizeof(expected));
    check_world();
    assert(D_800F2FDC[0] == 768 && D_800F2FDC[1] == 1536);
    return 1;
}

static u8 next_random(void)
{
    u32 high = ((random_expected * 3u) % 65536) / 256;
    random_expected = high * 256 + ((random_expected + high) % 256);
    return random_expected % 256;
}

static u32 test_spark_cleanup(u32 row)
{
    static const s8 timers[] = { 0, 1, 127, -128, -1 };
    static const u16 seeds[] = { 1, 0x1234, 0x5555, 0xFFFF };
    struct EngineObj obj;
    u32 availability = row % 3, timer = row / 3 % COUNT(timers);
    u32 subtype = row / (3 * COUNT(timers)) % 3;
    u32 seed = row / (9 * COUNT(timers)), slot = availability == 1 ? 0 : 63;
    struct MiscObj* spark = &misc_objects[32];
    prepare(&obj, subtype % 2, 3);
    spark->active = 0x41;
    spark->id = 0x38;
    spark->state = 2;
    spark->unk2 = subtype;
    spark->ext.misc_11.active = timers[timer];
    cur_random = seeds[seed];
    if (availability)
        misc_objects[slot].active = 0;
    capture();
    if (timer) {
        misc_expected[32].ext.misc_11.active = timers[timer] == -128 ? 127 : timers[timer] - 1;
    } else {
        if (subtype != 2 && availability) {
            misc_expected[slot].active = 0x41;
            misc_expected[slot].id = 0x38;
            misc_expected[slot].unk2 = next_random() % 2;
            misc_expected[slot].ext.misc_11.active = next_random();
        }
        memset(&misc_expected[32], 0, 8);
    }
    func_80023C0C(spark);
    check_world();
    return 1;
}

static const u32 spark_frames[3][11] = {
    { 0x0A010002, 0x0B010002, 0x0A010002, 0x0B010002, 0x0A010002,
        0x0B010002, 0x0C010003, 0x0D010003, 0x0E010003, 0x0F010003, 0x10000003 },
    { 0x11010002, 0x12010002, 0x11010002, 0x12010002, 0x11010002,
        0x12010002, 0x13010003, 0x14010003, 0x15010003, 0x16000003 },
    { 0x00010004, 0x01010004, 0x02010002, 0x03010004, 0x04010004,
        0x05010004, 0x06010004, 0x07010004, 0x08010003, 0x09000003 },
};

static u32 test_spark_animation(u32 row)
{
    static const struct {
        s16 x, y;
        u8 visible;
    } positions[] = {
        { -33, 120, 0 },
        { -32, 120, 1 },
        { 351, 120, 1 },
        { 352, 120, 0 },
        { 160, -33, 0 },
        { 160, -32, 1 },
        { 160, 271, 1 },
        { 160, 272, 0 },
    };
    struct EngineObj obj;
    u32 type, index = row / 2, expiring = row % 2, next, i;
    struct MiscObj* spark = &misc_objects[32];
    if (index < 11) {
        type = 0;
    } else if (index < 21) {
        type = 1;
        index -= 11;
    } else {
        type = 2;
        index -= 21;
    }
    prepare(&obj, type % 2, 3);
    spark->active = 0x41;
    spark->id = 0x38;
    spark->state = 1;
    spark->unk2 = type;
    spark->ext.misc_11.active = 0;
    spark->animation_table = (u32**)D_800F307C;
    spark->animation_cursor = (u32*)&D_800F307C[type][index];
    spark->animation_step.packed = spark_frames[type][index];
    if (expiring)
        spark->animation_step.fields.duration = 1;
    spark->bg_offset = -1;
    spark->x_pos.i.hi = positions[row % COUNT(positions)].x;
    spark->y_pos.i.hi = positions[row % COUNT(positions)].y;
    capture();
    if (expiring) {
        next = index == (type == 0 ? 10 : 9) ? index : index + 1;
        misc_expected[32].animation_cursor = (u32*)&D_800F307C[type][next];
        misc_expected[32].animation_step.packed = spark_frames[type][next];
    } else {
        misc_expected[32].animation_step.fields.duration--;
    }
    if ((misc_expected[32].animation_step.packed & 0xFF0000) == 0) {
        misc_expected[32].state = 2;
        misc_expected[32].ext.misc_11.active = next_random() % 32;
    }
    misc_expected[32].on_screen = positions[row % COUNT(positions)].visible;
    func_80023B98(spark);
    check_world();
    for (type = 0; type < 3; type++)
        for (i = 0; i < (type == 0 ? 11 : 10); i++)
            assert(D_800F307C[type][i].packed == spark_frames[type][i]);
    return 1;
}

static u32 test_spark_animation_delay(u32 row)
{
    static const s8 timers[] = { 1, 2, 31, 127, -128, -1 };
    struct EngineObj obj;
    u32 type = row / COUNT(timers), index = row % COUNT(timers);
    struct MiscObj* spark = &misc_objects[32];
    prepare(&obj, type % 2, 3);
    spark->active = 0x41;
    spark->id = 0x38;
    spark->state = 1;
    spark->unk2 = type;
    spark->ext.misc_11.active = timers[index];
    spark->animation_table = (u32**)D_800F307C;
    spark->animation_cursor = (u32*)D_800F307C[type];
    spark->animation_step.packed = spark_frames[type][0];
    capture();
    misc_expected[32].ext.misc_11.active = timers[index] == -128 ? 127 : timers[index] - 1;
    func_80023B98(spark);
    check_world();
    return 1;
}

static u32 test_handoff_blocked(u32 row)
{
    struct EngineObj obj, expected;
    struct GameInfo info;
    prepare(&obj, row / 2, 7);
    memset(&game_info, 0x35, sizeof(game_info));
    info = game_info;
    D_8013E1C4 = 0x25;
    D_8013BD44 = 1;
    start_fade(row % 2 + 1);
    capture();
    expected = obj;
    func_800239E0(&obj);
    c_test_same_words(&obj, &expected, sizeof(expected));
    c_test_same_words(&game_info, &info, sizeof(info));
    assert(D_8013E1C4 == 0x25 && D_8013BD44 == 1);
    check_world();
    return 1;
}

#ifdef MMX4_PC
void func_8001213C(void);
extern s32 mmx4_pc_sfx_group, mmx4_pc_canonical_load;
extern const char* mmx4_pc_sfx_raw;
extern s16 D_80139560;
extern s32 D_80139538, D_80139540, D_80139544;

static void prepare_archives(u32 character)
{
    char cue[sizeof(__FILE__) + 32];
    char* suffix;
    strcpy(cue, __FILE__);
    suffix = strstr(cue, "/tests/main/13A8C.c");
    assert(suffix != NULL);
    strcpy(suffix, "/disks/mmx4.us.cue");
    if (access(cue, R_OK) != 0)
        c_test_skip();
    assert(setenv("SDL_AUDIODRIVER", "dummy", 1) == 0);
    assert(unsetenv("MMX4_ORACLE_SCENE") == 0);
    mmx4_pc_sfx_group = -1;
    mmx4_pc_sfx_raw = NULL;
    mmx4_pc_canonical_load = 0;
    assert(Psyz_CdSetDiskPath(cue) == 0);
    Psyz_SpuInit();
    func_8001213C();
    func_80012E38();
    reset_game_engine();
    engine_obj.stage = 14;
    engine_obj.cur_character = character;
    func_80013014();
    func_800160AC();
    engine_obj.substage = 1;
    func_80013014();
    func_800160AC();
    func_80012EB8();
    assert(D_8013E198[0] >= 0 && D_8013E198[1] >= 0);
    engine_obj.stage = 15;
    engine_obj.substage = 0;
    func_80013014();
    func_800160AC();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
}

static u32 test_setup(u32 row)
{
    static const u8 free_counts[] = { 0, 1, 2, 3, 4, 5, 6, 5 };
    static const u8 styles[3][2] = { { 4, 5 }, { 7, 8 }, { 10, 10 } };
    static const u8 object_ids[] = { 9, 8, 9, 10 };
    struct EngineObj obj;
    struct GameInfo info;
    struct MenuRuntimeData runtime;
    struct BackgroundLayoutConfig config;
    u32 plan = row % COUNT(free_counts), character = row / COUNT(free_counts) % 2;
    u32 first = plan == 7 ? 59 : 0, count = free_counts[plan], i, buffer, j;
    u32 tile_bytes;
    prepare_archives(character);
    prepare(&obj, character, 2);
    engine_obj = obj;
    engine_obj.substage = 0;
    engine_obj.checkpoint = 0;
    func_8002AB20();
    memset(&g_Player, 0x35, sizeof(g_Player));
    for (i = 0; i < count; i++)
        misc_objects[first + i].active = 0;
    cur_random = row / 16 ? 0xFFFF : 0x1234;
    info = game_info;
    runtime = D_800F1D90;
    config = D_800F3188.records[31];
    capture();
    global_before.substage = 1;
    global_before.unk1 = 3;
    global_before.unk2 = 0;
    memset(global_before.character_state.bytes, 0, 16);
    player_before.x_pos.val = player_before.y_pos.val = 0;
    player_before.unk18.val = player_before.unk1C.val = 0;
    player_before.unk15 = 64;
    player_before.beam_in_delay = 0;
    for (i = 0; i < 3; i++) {
        backgrounds_expected[i].unk0 = 1;
        backgrounds_expected[i].unk3 = i != 1;
        backgrounds_expected[i].unk44 = 1;
        backgrounds_expected[i].unk4E = 1;
        backgrounds_expected[i].max_y = 18;
        backgrounds_expected[i].unk4B = styles[i][0];
        backgrounds_expected[i].unk4A = styles[i][1];
    }
    if (character)
        backgrounds_expected[1].y_pos.val = 768 * 65536;
    for (i = 0; i < count && i < 5; i++) {
        struct MiscObj* expected = &misc_expected[first + i];
        expected->active = 0x41;
        expected->id = 0x38;
        expected->unk2 = next_random() % 2;
        expected->ext.title_logo.palette_shift_speed = next_random();
    }
    main_expected.transition.active = 1;
    main_expected.transition.fade_amount = 8;
    palette_expected = 0x21;
    func_80023698(&engine_obj);
    check_world();
    c_test_same_words(&game_info, &info, sizeof(info));
    assert(memcmp(&D_800F1D90, &runtime, sizeof(runtime)) == 0);
    assert(memcmp(&D_800F3188.records[31], &config, sizeof(config)) == 0);
    assert(memcmp(D_80173C6C, object_ids, sizeof(object_ids)) == 0);
    assert(layout_width == 2 && layout_height == 19 && layout_size == 38);
    assert(SP_BG_TILEMAP == D_80141BE8);
    assert(memcmp(SP_BG_TILEMAP, D_8010FFDC[15][1], 114) == 0);
    tile_bytes = (u8*)SP_BG_TILE_ATTRS - (u8*)SP_BG_TILE_PIXELS;
    assert(tile_bytes > 0 && (tile_bytes & 1) == 0);
    assert(memcmp(SP_BG_TILE_PIXELS, D_801441B4, tile_bytes) == 0);
    for (buffer = 0; buffer < 2; buffer++)
        for (i = 0; i < 6; i++)
            for (j = 0; j < 8; j++)
                assert(D_80171EB0[buffer][i][j].code[0]
                    == (0xE1000000u | (getTPage(0, D_800F30D4[15][1], 320 + j * 64, 256) & 0x9FF)));
    assert(D_80139560 == XA_ARCHIVE_BGM1 && D_80139568 == 1);
    assert(((u8*)D_80175EE8)[0] == 1 && ((u8*)D_80175EE8)[1] == 0);
    assert(D_80139538 == D_800F0E18[XA_ARCHIVE_BGM1].unk4);
    assert(D_80139540 == D_800F0E18[XA_ARCHIVE_BGM1].unk0);
    assert(D_80139544 == D_80139540 + 0xC8A * 8);
    assert(D_80139524 == 127 && D_80141BD4 == 2 && D_80139530 == 7);
    return 1;
}

#define POOLS(action)        \
    action(&g_Player);       \
    action(&g_Entity);       \
    action(&foo_objects);    \
    action(&baz_objects);    \
    action(&weapon_objects); \
    action(&main_objects);   \
    action(&shot_objects);   \
    action(&visual_objects); \
    action(&effect_objects); \
    action(&item_objects);   \
    action(&misc_objects);   \
    action(&unk_objects);    \
    action(&layer_objects);  \
    action(&g_QuadObjects);  \
    action(&qux_object);     \
    action(&bar_object);     \
    action(&abc_object)

static void check_zero(const void* data, u32 size)
{
    const u8* bytes = data;
    u32 i;
    for (i = 0; i < size; i++)
        assert(bytes[i] == 0);
}

static u32 test_reset(u32 row)
{
    static const u8 fills[] = { 0, 0x25, 0xA5 };
    struct EngineObj obj;
    struct GameInfo info;
    struct MenuRuntimeData runtime;
    u32 character = row % 2, i;
    prepare_archives(character);
    prepare(&obj, character, 0);
    engine_obj = obj;
    engine_obj.substage = 0;
#define FILL(pool) memset(pool, fills[row / 2], sizeof(*(pool)))
    POOLS(FILL);
#undef FILL
    g_FilterAmountR = 123;
    g_FilterAmountG = 456;
    g_FilterAmountB = 789;
    g_FilterModeR = 1;
    g_FilterModeG = 2;
    g_FilterModeB = 3;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 0x123456 + i;
    info = game_info;
    runtime = D_800F1D90;
    capture();
    global_before.unk1 = 1;
    global_before.unk1F = global_before.enable_boss = 0;
    memset(&player_before, 0, sizeof(player_before));
    memset(misc_expected, 0, sizeof(misc_expected));
    memset(backgrounds_expected, 0, sizeof(backgrounds_expected));
    for (i = 0; i < 3; i++)
        backgrounds_expected[i].unk2 = i;
    func_80023624(&engine_obj);
    check_world();
#define ZERO(pool) check_zero(pool, sizeof(*(pool)))
    POOLS(ZERO);
    assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    assert(g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == 0);
    c_test_same_words(&game_info, &info, sizeof(info));
    assert(memcmp(&D_800F1D90, &runtime, sizeof(runtime)) == 0);
    func_80023A54(&engine_obj);
    global_before.unk1 = 2;
    check_world();
    POOLS(ZERO);
#undef ZERO
    return 1;
}
#undef POOLS

static u32 handoff_returned;
static void handoff_entry(void)
{
    func_800239E0(&engine_obj);
    handoff_returned = 1;
}

static u32 test_handoff(u32 row)
{
    struct EngineObj obj;
    struct GameInfo info;
    struct MenuRuntimeData runtime;
    prepare(&obj, row % 2, 7);
    engine_obj = obj;
    memset(&game_info, 0x35, sizeof(game_info));
    D_8013E1C4 = row / 2;
    D_8013BD44 = 1;
    info = game_info;
    info.unk0 = 3;
    info.mode = info.unk2 = info.unk3 = 0;
    runtime = D_800F1D90;
    capture();
    handoff_returned = 0;
    func_80012740(1, handoff_entry);
    mmx4_pc_thread_run(1);
    thread0_expected = 2;
    check_world();
    assert(handoff_returned == 0);
    assert(D_8013E1C4 == 1 && D_8013BD44 == 0);
    c_test_same_words(&game_info, &info, sizeof(info));
    assert(memcmp(&D_800F1D90, &runtime, sizeof(runtime)) == 0);
    return 1;
}
#define PC_CASES 42
#else
#define PC_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "staff_start_delay", 0, 0, 2, test_start_delay },
    { "staff_first_scroll", 0, 0, 9, test_first_scroll },
    { "staff_final_spark", 0, 0, 6, test_final_spark },
    { "staff_second_scroll", 0, 0, 6, test_second_scroll },
    { "staff_portrait_scroll", 0, 0, 10, test_portrait_scroll },
    { "staff_spark_cleanup", 0, 0, 33, test_spark_cleanup },
    { "staff_spark_animation", 0, 0, 20, test_spark_animation },
    { "staff_spark_animation_delay", 0, 0, 18, test_spark_animation_delay },
    { "staff_handoff_blocked", 0, 0, 4, test_handoff_blocked },
#ifdef MMX4_PC
    { "staff_archive_setup", 0, 0, 16, test_setup },
    { "staff_scene_reset", 0, 0, 6, test_reset },
    { "staff_thread_handoff", 0, 0, 4, test_handoff },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 9 + 6 + 6 + 10 + 33 + 20 + 18 + 4
#ifdef MMX4_PC
    + 16
    + 6
    + 4
#endif
    ;
