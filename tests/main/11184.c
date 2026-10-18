#include "test_runtime.h"
#include "main/2824.h"
#include "main/323C.h"
#include "main/55C4.h"
#include "main/11184.h"
#include "main/objects.h"
#include "main/menu.h"
#include "main/1A5BC.h"
extern void func_80020DEC(u8* arg0, s16 arg1);
void func_80020ED4(struct EngineObj*);
void func_80020F24(struct EngineObj*);
void func_800210B8(struct EngineObj*);
#ifdef MMX4_PC
#include <unistd.h>
#include <psyz/cd.h>
#include <psyz/spu.h>
#include <stdlib.h>
#endif

extern u8 D_800F2468[], D_800F247C[], D_800F2490[];
extern u16 D_800EE430[16];

static struct UnkObj expected_unknown[UNK_OBJECT_COUNT];

static void check_bytes(const void* actual, const void* expected, u32 size)
{
    const u8* a = actual;
    const u8* b = expected;
    u32 i;
    for (i = 0; i < size; i++)
        assert(a[i] == b[i]);
}

static void expect_labels(u32 confirmation)
{
    static const u8 labels[2][5] = {
        { 0x59, 0x2D, 0x5B, 0x5C, 0x72 },
        { 0x59, 0x5A, 0x51, 0x52, 0x72 },
    };
    static const u8 y[] = { 0x10, 0x40, 0x70, 0x90, 0xD0 };
    static const u8 category[] = { 0x80, 0x80, 0, 1, 0x80 };
    u32 i;
    memset(expected_unknown, 0, sizeof(expected_unknown));
    for (i = 0; i < 5; i++) {
        expected_unknown[i].active = 1;
        expected_unknown[i].id = 1;
        expected_unknown[i].unk2 = labels[confirmation][i];
        expected_unknown[i].y_pos.i.hi = y[i];
        expected_unknown[i].unk7 = category[i];
    }
    expected_unknown[5].active = 1;
    expected_unknown[5].unk2 = -1;
    expected_unknown[5].link.data = D_800F2490;
    expected_unknown[5].x_pos.i.hi = confirmation ? 0x78 : 0x40;
}

static void prepare_menu(struct EngineObj* obj, u32 phase, u32 cursor, u16 input, s8 fade)
{
    memset(obj, 0x25, sizeof(*obj));
    memset(&engine_obj, 0x37, sizeof(engine_obj));
    memset(&g_Player, 0x47, sizeof(g_Player));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(unk_objects, 0x27, sizeof(unk_objects));
    memset(&controller_input, 0, sizeof(controller_input));
    obj->state = 6;
    obj->unk6 = 2;
    obj->unk7 = 1;
    obj->character_state.fields.menu_state = phase;
    controller_input.held = controller_input.pressed = input;
    main_bss_state.frame_counter = 0x13572468;
    main_bss_state.transition.suspended = 1;
    main_bss_state.transition.selection = cursor;
    main_bss_state.transition.fade_amount = 5;
    D_8013E198[0] = -1;
    need_palette_load = 0x20;
#ifdef MMX4_PC
    mmx4_pc_threads_init();
    ResetGraph(0);
    memset(WINDOW_ARCHIVE_DATA, 0, 0x3000);
    ((u32*)WINDOW_ARCHIVE_DATA)[1] = 0x20;
#endif
    if (fade > 0)
        func_800129A4(5);
    else if (fade < 0)
        func_800129F0(5);
    memcpy(expected_unknown, unk_objects, sizeof(expected_unknown));
}

static void check_menu(const struct EngineObj* obj, const struct EngineObj* expected,
    const struct EngineObj* global, const struct PlayerObj* player,
    const struct MainBssState* main, u16 input)
{
    c_test_same_words(obj, expected, sizeof(*obj));
    c_test_same_words(&engine_obj, global, sizeof(*global));
    c_test_same_words(&g_Player, player, sizeof(*player));
    c_test_same_words(&main_bss_state, main, sizeof(*main));
    assert(c_test_word_difference((const u32*)unk_objects,
               (const u32*)expected_unknown, sizeof(expected_unknown) / 4)
        == 0);
    assert(controller_input.held == input && controller_input.pressed == input);
    assert(controller_input.previous == 0 && need_palette_load == 0x20);
#ifdef MMX4_PC
    {
        struct GameThread threads[4];
        u32 i;
        memset(threads, 0, sizeof(threads));
        threads[2].state = main->transition.active ? 2 : 0;
        for (i = 0; i < 4; i++)
            c_test_same_words(mmx4_pc_thread_slot(i), &threads[i], sizeof(threads[i]));
    }
#endif
}

static u32 test_entry(u32 row)
{
    static const u8 fill[] = { 0, 0x25, 0xA5 };
    struct EngineObj obj, expected, global;
    struct PlayerObj player;
    struct MainBssState main;
    prepare_menu(&obj, 1, 1, 0, 0);
    memset(unk_objects, fill[row], sizeof(unk_objects));
    expected = obj;
    expected.unk7 = 1;
    expected.character_state.fields.menu_state = 0;
    global = engine_obj;
    player = g_Player;
    main = main_bss_state;
    main.transition.selection = 0;
    main.transition.active = 1;
    main.transition.fade_amount = 8;
    expect_labels(0);
    func_80020ED4(&obj);
    check_menu(&obj, &expected, &global, &player, &main, 0);
    return 1;
}

enum { KEEP,
    RESUME,
    ASK_QUIT,
    CANCEL_QUIT };
static const struct {
    u8 phase, cursor;
    u16 pressed;
    u8 next_cursor, outcome;
} inputs[] = {
    { 0, 0, 0, 0, KEEP },
    { 0, 1, 0, 1, KEEP },
    { 0, 0, PADLup, 1, KEEP },
    { 0, 1, PADLup, 0, KEEP },
    { 0, 0, PADLdown, 1, KEEP },
    { 0, 1, PADLdown, 0, KEEP },
    { 0, 0, PADLup | PADLdown, 0, KEEP },
    { 0, 1, PADLup | PADLdown, 1, KEEP },
    { 0, 0, PADstart, 0, KEEP },
    { 0, 1, PAD_CANCEL, 1, KEEP },
    { 0, 0, PAD_CONFIRM, 0, RESUME },
    { 0, 1, PAD_CONFIRM, 0, ASK_QUIT },
    { 0, 0, PADLup | PAD_CONFIRM, 0, ASK_QUIT },
    { 0, 1, PADLdown | PAD_CONFIRM, 0, RESUME },
    { 0, 0, PADLup | PADLdown | PAD_CONFIRM, 0, RESUME },
    { 0, 1, PADLup | PADLdown | PAD_CONFIRM, 0, ASK_QUIT },
    { 1, 0, 0, 0, KEEP },
    { 1, 1, 0, 1, KEEP },
    { 1, 0, PADLup, 1, KEEP },
    { 1, 1, PADLup, 0, KEEP },
    { 1, 0, PADLdown, 1, KEEP },
    { 1, 1, PADLdown, 0, KEEP },
    { 1, 0, PADLup | PADLdown, 0, KEEP },
    { 1, 1, PADLup | PADLdown, 1, KEEP },
    { 1, 1, PADstart, 1, KEEP },
    { 1, 0, PAD_CANCEL, 0, KEEP },
    { 1, 0, PAD_CONFIRM, 0, CANCEL_QUIT },
    { 1, 1, PADLup | PAD_CONFIRM, 0, CANCEL_QUIT },
    { 1, 1, PADLdown | PAD_CONFIRM, 0, CANCEL_QUIT },
    { 1, 0, PADLup | PADLdown | PAD_CONFIRM, 0, CANCEL_QUIT },
};

static u32 test_input(u32 row)
{
    struct EngineObj obj, expected, global;
    struct PlayerObj player;
    struct MainBssState main;
    u32 outcome = inputs[row].outcome;
    prepare_menu(&obj, inputs[row].phase, inputs[row].cursor, inputs[row].pressed, 0);
    expected = obj;
    global = engine_obj;
    player = g_Player;
    main = main_bss_state;
    main.transition.selection = inputs[row].next_cursor;
    if (outcome == RESUME) {
        expected.unk7 = 2;
        main.transition.active = -1;
        main.transition.fade_amount = 8;
    } else if (outcome == ASK_QUIT) {
        expected.character_state.fields.menu_state = 1;
        expect_labels(1);
    } else if (outcome == CANCEL_QUIT) {
        expected.character_state.fields.menu_state = 0;
        expected.unk7 = 1;
        expect_labels(0);
    }
    func_80020F24(&obj);
    check_menu(&obj, &expected, &global, &player, &main, inputs[row].pressed);
    return 1;
}

static u32 test_blocked_input(u32 row)
{
    static const u16 buttons[] = { 0, PAD_CONFIRM, PADLup | PADLdown | PAD_CONFIRM };
    struct EngineObj obj, expected, global;
    struct PlayerObj player;
    struct MainBssState main;
    u16 input = buttons[row % 3];
    prepare_menu(&obj, row / 12, row / 6 % 2, input, row / 3 % 2 ? -1 : 1);
    expected = obj;
    global = engine_obj;
    player = g_Player;
    main = main_bss_state;
    func_80020F24(&obj);
    check_menu(&obj, &expected, &global, &player, &main, input);
    return 1;
}

static u32 test_resume_completion(u32 row)
{
    struct EngineObj obj, expected, global;
    struct PlayerObj player;
    struct MainBssState main;
    s8 fade = row / 2 == 0 ? 0 : row / 2 == 1 ? 1
                                              : -1;
    prepare_menu(&obj, 1, 1, 0, fade);
    obj.unk6 = row % 2 ? 127 : 2;
    obj.unk7 = 2;
    expected = obj;
    global = engine_obj;
    player = g_Player;
    main = main_bss_state;
    if (!fade) {
        expected.unk6 = row % 2 ? -128 : 3;
        expected.unk7 = 0;
        expected.character_state.fields.menu_state = 0;
        memset(expected_unknown, 0, sizeof(expected_unknown));
    }
    func_800210B8(&obj);
    check_menu(&obj, &expected, &global, &player, &main, 0);
    return 1;
}

static u32 test_retry_without_reload(u32 row)
{
    struct EngineObj obj, expected, global;
    struct PlayerObj player;
    struct MainBssState main;
    u32 bonus = row % 2, selection = row < 2 ? 0 : (row - 2) / 2 % 2;
    s8 fade = row < 2 ? 0 : (row - 2) / 4 ? -1
                                          : 1;
    prepare_menu(&obj, 0, selection, 0, fade);
    obj.state = 8;
    obj.unk1 = 6;
    obj.unk2 = 4;
    obj.unk3 = 3;
    obj.player_lives = 9;
    obj.checkpoint = 2;
    obj.unk1E = 1;
    obj.collected_upgrades = bonus ? 0 : 0x8000;
    engine_obj.collected_upgrades = bonus ? 0x8000 : 0;
    D_80171EA8 = 0;
    expected = obj;
    if (!fade) {
        expected.state = 5;
        expected.player_lives = bonus ? 4 : 2;
        expected.checkpoint = expected.unk1E = 0;
        expected.unk1 = expected.unk2 = expected.unk3 = 0;
    }
    global = engine_obj;
    player = g_Player;
    main = main_bss_state;
    func_80020A08(&obj);
    check_menu(&obj, &expected, &global, &player, &main, 0);
    assert(D_80171EA8 == 0);
    return 1;
}

static u32 test_label_allocation(u32 row)
{
    static const u8 available[] = { 0, 1, 1, 4, 5, 6, 6, 7 };
    struct EngineObj obj, expected_obj, global;
    struct PlayerObj player;
    struct MainBssState main;
    struct UnkObj labels[6];
    u8 program[20];
    u32 i, variant = row / 8, mode = row % 8, count = available[mode];
    u32 first = mode == 2 || mode == 6 ? COUNT(unk_objects) - count : 0;
    u8* source = variant ? D_800F247C : D_800F2468;
    prepare_menu(&obj, 0, 0, 0, 0);
    expected_obj = obj;
    global = engine_obj;
    player = g_Player;
    main = main_bss_state;
    memcpy(program, source, sizeof(program));
    expect_labels(variant);
    memcpy(labels, expected_unknown, sizeof(labels));
    for (i = 0; i < count; i++)
        unk_objects[first + i].active = 0;
    memcpy(expected_unknown, unk_objects, sizeof(expected_unknown));
    for (i = 0; i < count && i < 6; i++) {
        struct UnkObj* expected = &expected_unknown[first + i];
        expected->active = 1;
        expected->id = labels[i].id;
        expected->unk2 = labels[i].unk2;
        if (i < 5) {
            expected->y_pos.i.hi = labels[i].y_pos.i.hi;
            expected->unk7 = labels[i].unk7;
        } else {
            expected->link.data = labels[i].link.data;
            expected->x_pos.i.hi = labels[i].x_pos.i.hi;
        }
    }
    func_80020DEC(source, variant ? 0x78 : 0x40);
    check_menu(&obj, &expected_obj, &global, &player, &main, 0);
    check_bytes(source, program, sizeof(program));
    return 1;
}

static u32 test_menu_navigation(u32 row)
{
    static void (*const handlers[])(struct EngineObj*) = {
        func_80020984,
        func_80020B8C,
        func_80020CB8,
    };
    static const struct {
        u16 pressed;
        s8 fade;
        u8 cursor, limit, next_cursor, confirm;
    } cases[] = {
        { 0, 0, 0, 1, 0, 0 },
        { PAD_CONFIRM, 0, 0, 1, 0, 1 },
        { PAD_CONFIRM, 0, 1, 1, 1, 1 },
        { PADLup, 0, 0, 1, 1, 0 },
        { PADLdown, 0, 1, 1, 0, 0 },
        { PADLup | PAD_CONFIRM, 0, 0, 1, 1, 1 },
        { PADLdown | PAD_CONFIRM, 0, 1, 1, 0, 1 },
        { PADLup | PADLdown | PAD_CONFIRM, 0, 1, 1, 1, 1 },
        { PAD_CONFIRM, 1, 0, 1, 0, 0 },
        { PAD_CONFIRM, -1, 1, 1, 1, 0 },
        { PADLdown | PAD_CONFIRM, 0, 2, 2, 0, 1 },
        { PADLup, 0, 0, 2, 2, 0 },
    };
    struct EngineObj obj, expected, global;
    struct PlayerObj player;
    struct MainBssState main;
    u32 handler = row / COUNT(cases), index = row % COUNT(cases);
    prepare_menu(&obj, 0, cases[index].cursor, cases[index].pressed, cases[index].fade);
    obj.unk1 = 1;
    obj.unk8 = cases[index].limit;
    expected = obj;
    global = engine_obj;
    player = g_Player;
    main = main_bss_state;
    main.transition.selection = cases[index].next_cursor;
    if (cases[index].confirm) {
        expected.unk1++;
        if (handler != 1 || cases[index].next_cursor != 0) {
            main.transition.active = -1;
            main.transition.fade_amount = 8;
        }
    }
    handlers[handler](&obj);
    check_menu(&obj, &expected, &global, &player, &main, cases[index].pressed);
    return 1;
}

static u32 test_menu_route(u32 row)
{
    struct EngineObj obj, expected, global;
    struct PlayerObj player;
    struct MainBssState main;
    u32 handler = row >= 8, index = handler ? row - 8 : row;
    u32 cursor = handler ? (index ? (index - 1) % 2 : 0) : (index < 2 ? index : (index - 2) % 3);
    s8 fade = handler ? (index == 0 ? 0 : index <= 2 ? 1
                                                     : -1)
                      : (index < 2 ? 0 : index <= 4 ? 1
                                                    : -1);
    prepare_menu(&obj, 0, cursor, 0, fade);
    obj.state = 9;
    obj.unk1 = 6;
    obj.unk2 = 3;
    obj.unk3 = 4;
    expected = obj;
    global = engine_obj;
    player = g_Player;
    main = main_bss_state;
    if (!fade) {
        expected.state = !handler && cursor == 0 ? 12 : 3;
        if (!handler && cursor == 0)
            expected.unk4 = obj.state;
        expected.unk1 = expected.unk2 = expected.unk3 = 0;
    }
    if (handler)
        func_80020D3C(&obj);
    else
        func_80020C24(&obj);
    check_menu(&obj, &expected, &global, &player, &main, 0);
    return 1;
}

#ifdef MMX4_PC
void func_8001213C(void);
extern s32 mmx4_pc_sfx_group, mmx4_pc_canonical_load;
extern const char* mmx4_pc_sfx_raw;
static u32 quit_returned;

static void quit_entry(void)
{
    func_80020F24(&engine_obj);
    quit_returned = 1;
}

static void memory_value(const void* data, u32 size, u8 expected)
{
    const u8* bytes = data;
    u32 i;
    for (i = 0; i < size; i++)
        assert(bytes[i] == expected);
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

static void prepare_assets(u32 character)
{
    char cue[sizeof(__FILE__) + 32];
    char* suffix;
    strcpy(cue, __FILE__);
    suffix = strstr(cue, "/tests/main/11184.c");
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
}

static u32 test_quit(u32 row)
{
    static const u8 stages[] = { 0, 0, 1, 8 };
    static const u8 stories[] = { 2, 3, 2, 3 };
    struct EngineObj expected_engine;
    struct GameInfo expected_info;
    struct MenuRuntimeData expected_runtime;
    struct MainBssState expected_main;
    struct BackgroundObj backgrounds[3];
    struct GameThread threads[4];
    u32 i, character = row % 2, index = row / 2;
    s16 left, right;
    prepare_assets(character);
    for (i = 0; i < 24; i++)
        assert(SsUtSetVVol(i, 127, 64) == 0);
    SsSeqCalledTbyT();
    for (i = 0; i < 24; i++) {
        assert(SsUtGetVVol(i, &left, &right) == 0);
        assert(left > 0 && right > 0);
    }
#define FILL(pool) memset(pool, 0x25, sizeof(*(pool)))
    POOLS(FILL);
#undef FILL
    memset(background_objects, 0x27, sizeof(background_objects));
    memset(&game_info, 0x25, sizeof(game_info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&D_800F1D90.save, 0x37, sizeof(D_800F1D90.save));
    main_bss_state.transition.selection = 1;
    main_bss_state.frame_counter = 0x13572468;
    main_bss_state.transition.suspended = 1;
    controller_input.held = controller_input.pressed = PAD_CONFIRM;
    engine_obj.state = 6;
    engine_obj.unk6 = 2;
    engine_obj.unk7 = 1;
    engine_obj.character_state.fields.menu_state = 1;
    engine_obj.stage = stages[index];
    engine_obj.unk5F = stories[index];
    engine_obj.max_hp = 0x30;
    engine_obj.arm_type = 2;
    engine_obj.armor_parts = 15;
    engine_obj.palette_flags = 0x5A;
    engine_obj.collected_upgrades = 0xA55A;
    engine_obj.unk37 = 1;
    D_80171EA9 = character;
    for (i = 0; i < 16; i++)
        D_800EE430[i] = 0x100 + i;
    expected_runtime = D_800F1D90;
    if (stages[index] && stories[index] >= 3) {
        expected_runtime.save.character = character;
        expected_runtime.save.unk1 = 0x30;
        expected_runtime.save.unk2 = 2;
        expected_runtime.save.unk3 = 15;
        expected_runtime.save.unk4 = 0x5A;
        expected_runtime.save.unk5 = stories[index];
        expected_runtime.save.unk6 = 0xA55A;
        expected_runtime.save.unk28 = character;
        expected_runtime.save.unk29 = 1;
        for (i = 0; i < 16; i++)
            expected_runtime.save.unk8[i] = 0x100 + i;
    }
    expected_info = game_info;
    expected_info.unk0 = 1;
    expected_info.mode = expected_info.unk2 = expected_info.unk3 = 0;
    expected_main = main_bss_state;
    memset(&expected_engine, 0, sizeof(expected_engine));
    memset(backgrounds, 0, sizeof(backgrounds));
    for (i = 0; i < 3; i++)
        backgrounds[i].unk2 = i;
    for (i = 0; i < 4; i++)
        D_80173C6C[i] = D_8013E188[i] = 9;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 5;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 1;
    quit_returned = 0;
    func_80012740(1, quit_entry);
    mmx4_pc_thread_run(1);
    assert(quit_returned == 0);
    c_test_same_words(&engine_obj, &expected_engine, sizeof(expected_engine));
    c_test_same_words(&game_info, &expected_info, sizeof(expected_info));
    c_test_same_words(&main_bss_state, &expected_main, sizeof(expected_main));
    assert(memcmp(&D_800F1D90, &expected_runtime, sizeof(expected_runtime)) == 0);
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
#define ZERO(pool) memory_value(pool, sizeof(*(pool)), 0)
    POOLS(ZERO);
#undef ZERO
    memset(threads, 0, sizeof(threads));
    threads[0].state = 2;
    for (i = 0; i < 4; i++) {
        c_test_same_words(mmx4_pc_thread_slot(i), &threads[i], sizeof(threads[i]));
        assert(D_80173C6C[i] == i + 3 && D_8013E188[i] == 0);
        assert(D_8013924C[i] == 0xFF && D_8013E1C8[i] == -1);
    }
    assert(D_801F8300 == mmx4_pc_thread_slot(1));
    assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    assert(g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0);
    assert(controller_input.held == PAD_CONFIRM && controller_input.pressed == PAD_CONFIRM);
    assert(controller_input.previous == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    SsSeqCalledTbyT();
    for (i = 0; i < 24; i++) {
        assert(D_80139234[i] == -1);
        assert(SsUtGetVVol(i, &left, &right) == 0 && left == 0 && right == 0);
    }
    return 1;
}

extern u8 D_80110064[64];
static u32 retry_returned;

static void retry_entry(void)
{
    func_80020A08(&engine_obj);
    retry_returned = 1;
}

static u32 title_handler;
static void title_entry(void)
{
    if (title_handler == 0)
        func_80020A08(&engine_obj);
    else if (title_handler == 1)
        func_80020C24(&engine_obj);
    else
        func_80020D3C(&engine_obj);
    retry_returned = 1;
}

static u32 test_retry_reload(u32 row)
{
    struct EngineObj before, expected;
    struct GameInfo info;
    struct GameThread threads[4];
    struct MenuRuntimeData runtime;
    u32 i, character = row % 2, substage = row / 2 % 2, bonus = row / 4 % 2;
    u32 stage = row / 8 ? 8 : 1;
    prepare_assets(character);
    engine_obj.state = 8;
    engine_obj.unk1 = 6;
    engine_obj.unk2 = 4;
    engine_obj.unk3 = 3;
    engine_obj.stage = stage;
    engine_obj.substage = substage;
    engine_obj.cur_character = character;
    engine_obj.player_lives = 9;
    engine_obj.checkpoint = 2;
    engine_obj.unk1E = 1;
    engine_obj.collected_upgrades = bonus ? 0x8000 : 0;
    main_bss_state.transition.active = 0;
    main_bss_state.transition.selection = 0;
    D_80171EA8 = 1;
    before = expected = engine_obj;
    expected.state = 5;
    expected.player_lives = bonus ? 4 : 2;
    expected.checkpoint = expected.unk1E = 0;
    expected.unk1 = expected.unk2 = expected.unk3 = 0;
    info = game_info;
    runtime = D_800F1D90;
    retry_returned = 0;
    func_80012740(1, retry_entry);
    mmx4_pc_thread_run(1);
    assert(retry_returned == 0 && D_80171EA8 == 1);
    c_test_same_words(&engine_obj, &before, sizeof(before));
    assert(mmx4_pc_thread_slot(1)->state == 1 && mmx4_pc_thread_slot(1)->timer == 1);
    mmx4_pc_thread_run(1);
    assert(retry_returned == 1 && D_80171EA8 == 0);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    c_test_same_words(&game_info, &info, sizeof(info));
    assert(memcmp(&D_800F1D90, &runtime, sizeof(runtime)) == 0);
    memset(threads, 0, sizeof(threads));
    threads[0].state = 2;
    threads[1].timer = 1;
    for (i = 0; i < 4; i++)
        c_test_same_words(mmx4_pc_thread_slot(i), &threads[i], sizeof(threads[i]));
    assert(layout_width == D_80110064[stage * 4 + substage * 2]);
    assert(layout_height == D_80110064[stage * 4 + substage * 2 + 1]);
    assert(layout_size == layout_width * layout_height);
    assert(SP_BG_TILE_PIXELS != NULL && SP_BG_TILE_ATTRS != NULL && SP_PALETTE != NULL);
    return 1;
}

static u32 test_retry_title(u32 row)
{
    struct EngineObj before;
    struct GameInfo info;
    struct GameThread threads[4];
    struct MenuRuntimeData runtime;
    s8 banks[6];
    u32 i, variant = row % 8;
    title_handler = row / 8;
    prepare_assets(row % 2);
    engine_obj.state = title_handler == 0 ? 8 : 9;
    engine_obj.unk1 = 6;
    engine_obj.unk2 = 4;
    engine_obj.unk3 = 3;
    engine_obj.collected_upgrades = variant / 2 % 2 ? 0x8000 : 0;
    main_bss_state.transition.active = 0;
    main_bss_state.transition.selection = title_handler == 1 ? 2 : 1;
    D_80171EA8 = variant / 4;
    before = engine_obj;
    info = game_info;
    info.unk0 = 1;
    info.mode = info.unk2 = info.unk3 = 0;
    runtime = D_800F1D90;
    memcpy(banks, D_8013E198, sizeof(banks));
    retry_returned = 0;
    func_80012740(1, title_entry);
    mmx4_pc_thread_run(1);
    assert(retry_returned == 0 && D_80171EA8 == variant / 4);
    c_test_same_words(&engine_obj, &before, sizeof(before));
    c_test_same_words(&game_info, &info, sizeof(info));
    assert(memcmp(&D_800F1D90, &runtime, sizeof(runtime)) == 0);
    assert(memcmp(D_8013E198, banks, sizeof(banks)) == 0);
    memset(threads, 0, sizeof(threads));
    threads[0].state = 2;
    for (i = 0; i < 4; i++)
        c_test_same_words(mmx4_pc_thread_slot(i), &threads[i], sizeof(threads[i]));
    return 1;
}
#undef POOLS
#define PC_THREAD_CASES 48
#else
#define PC_THREAD_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "pause_transition_entry", 0, 0, 3, test_entry },
    { "pause_transition_input", 0, 0, COUNT(inputs), test_input },
    { "pause_transition_blocked", 0, 0, 3, test_blocked_input },
    { "pause_transition_resume", 0, 0, 6, test_resume_completion },
    { "retry_without_reload", 0, 0, 10, test_retry_without_reload },
    { "menu_label_allocation", 0, 0, 8, test_label_allocation },
    { "menu_navigation", 0, 0, 36, test_menu_navigation },
    { "menu_route", 0, 0, 13, test_menu_route },
#ifdef MMX4_PC
    { "pause_transition_quit", 0, 0, 8, test_quit },
    { "retry_checkpoint_reload", 0, 0, 2, test_retry_reload },
    { "menu_return_to_title", 0, 0, 24, test_retry_title },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3 + COUNT(inputs) + 3 + 6 + 10 + 8 + 36 + 13
#ifdef MMX4_PC
    + 8
    + 2
    + 24
#endif
    ;
