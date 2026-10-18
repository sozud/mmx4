#include "test_runtime.h"
#include "main/128C4.h"
#include "main/55C4.h"
extern union MainPaletteData D_800F1660;

static u32 dialogue_case(u32 mode, u32 observation)
{
    struct MiscObj parts[6], before[6], pool_expected;
    struct MiscObj** slots[] = { &D_801397C0, &D_801397C4, &D_801397CC, &D_801397C8, &D_801397D4, &D_801397D0 };
    struct AbcObj dialogue_before;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    struct Func80022730Config config = { 1, 2, 3, 4, 5, 6 };
    u16 palette[1024], messages[] = { 2, 0x800 };
    const u16* dialogue_colors = (const u16*)&D_800F1660.raw[0xA0];
    u32 i, j, active_mask = 0, actual;
    memset(parts, 0, sizeof(parts));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(&pool_expected, 0, sizeof(pool_expected));
    pool_expected.active = 1;
    pool_expected.id = 0x17;
    for (i = 0; i < 64; i++)
        misc_objects[i] = pool_expected;
    for (i = 0; i < 1024; i++)
        palette[i] = 0x1400 + i;
    TEST_PALETTE = (u8*)palette;
    TEST_ARC_48 = (u8*)messages;
    engine_obj.stage = 2;
    engine_obj.cur_character = 1;
    engine_obj.enable_boss = 1;
    engine_obj.unk1F = 7;
    abc_object.unk0 = &messages[1];
    abc_object.unk4 = 0x27;
    abc_object.unkA = 0x15;
    abc_object.unkC = mode == 2 ? 0 : 1;
    abc_object.unkD = 2;
    abc_object.unkE = 3;
    abc_object.unkF = 7;
    for (i = 0; i < 6; i++) {
        parts[i].active = 1;
        parts[i].id = mode == 3 || (mode == 1 && (i == 2 || i == 4)) ? 0x16 : 0x17;
        parts[i].on_screen = 1;
        parts[i].state = 3;
        parts[i].unk6 = 0x27 + i;
        *slots[i] = mode == 4 || (mode == 0 && i == 0) ? NULL : &parts[i];
    }
    D_801397BC = &parts[5];
    D_801397D8 = 0x27;
    D_801397DC = &config;
    D_801397E0 = 0x25;
    D_80139824 = 0x49;
    D_80139828 = 0x42;
    need_palette_load = 0x20;
    for (i = 0; i < 32; i++)
        D_801397E4[i] = 0x4242;
    memcpy(before, parts, sizeof(before));
    dialogue_before = abc_object;
    engine_before = engine_obj;
    player_before = g_Player;
    func_8002217C(mode == 2 ? 0 : 0x1234, 0x80, 0);
    dialogue_before.unkC = 0x80;
    dialogue_before.unkA = 0x27;
    if (mode == 2) {
        dialogue_before.unk0 = &messages[1];
        dialogue_before.unk4 = 0x800;
        dialogue_before.unk6 = -0x78;
        dialogue_before.unk8 = 0x1D;
        dialogue_before.unkD = 0;
        dialogue_before.unkE = 0;
        dialogue_before.unkF = 1;
        dialogue_before.unk10 = 0;
        engine_before.enable_boss = 0;
        engine_before.unk1F = 0;
        assert(D_801397BC == NULL && D_801397D8 == 0x80 && D_801397E0 == 0);
        assert(D_80139824 == 7 && D_80139828 == 1 && need_palette_load == 0x21);
    } else {
        dialogue_before.unkD = 4;
        dialogue_before.unk10 = (s16)0x9234;
        if (mode == 1) {
            before[2].active = before[2].on_screen = 0;
            before[4].active = before[4].on_screen = 0;
        }
        if (mode == 3)
            for (i = 0; i < COUNT(before); i++)
                before[i].active = before[i].on_screen = 0;
        assert(D_801397BC == &parts[5] && D_801397D8 == 0x27 && D_801397E0 == 0x25);
        assert(D_80139824 == 0x49 && D_80139828 == 0x42 && need_palette_load == 0x20);
    }
    assert(D_801397DC == &config && messages[0] == 2 && messages[1] == 0x800);
    for (i = 0; i < 6; i++) {
        assert(*slots[i] == (mode == 2 || mode == 4 || (mode == 0 && i == 0) ? NULL : &parts[i]));
        if (parts[i].active)
            active_mask |= 1 << i;
    }
    for (i = 0; i < sizeof(parts) / 4; i++)
        assert(((u32*)parts)[i] == ((u32*)before)[i]);
    for (i = 0; i < sizeof(abc_object) / 4; i++)
        assert(((u32*)&abc_object)[i] == ((u32*)&dialogue_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 64; i++)
        for (j = 0; j < sizeof(pool_expected) / 4; j++)
            assert(((u32*)&misc_objects[i])[j] == ((u32*)&pool_expected)[j]);
    for (i = 0; i < 1024; i++)
        assert(palette[i] == (mode == 2 && i >= 0x150 && i < 0x170 ? dialogue_colors[i - 0x150] : 0x1400 + i));
    for (i = 0; i < 32; i++)
        assert(D_801397E4[i] == (mode == 2 ? 0x1550 + i : 0x4242));
    actual = observation == 0 ? abc_object.unkC | ((u32)abc_object.unkD << 8) | ((u32)abc_object.unkA << 16) : (u16)abc_object.unk10 | (active_mask << 16);
    return actual;
}
static const u32 dialogue_interrupt_pool_full_cases_expected[] = { 0x270480u, 0x3F9234u, 0x270480u, 0x2B9234u, 0x270080u, 0x3F0000u, 0x270480u, 0x9234u, 0x270480u, 0x3F9234u };
static u32 dialogue_interrupt_pool_full_cases_row(u32 row)
{
    return dialogue_case(row / 2, row % 2);
}

static struct Func80022730Config talk_config;
static u32 talk_pages[0x40];
static s32 talk_frames[0x200];
static u16 talk_palette[0x400];

static void talk_reset(u8 step, u16 timer, u8 portrait)
{
    memset(&abc_object, 0, sizeof(abc_object));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(&talk_config, 0, sizeof(talk_config));
    abc_object.unkD = step;
    abc_object.unkA = timer;
    D_801397D8 = portrait;
    D_801397DC = &talk_config;
    D_801406A8 = talk_pages;
    TEST_MENU_FRAMES = (u8*)talk_frames;
    TEST_PALETTE = (u8*)talk_palette;
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    engine_obj.cur_character = 0;
    engine_obj.armor_parts = 0;
    engine_obj.stage = 0;
    controller_input.pressed = 0;
    need_palette_load = 0;
}

static u32 talk_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[5], active = 0, i;
    run();
    for (i = 0; i < COUNT(misc_objects); i++)
        active += misc_objects[i].active != 0;
    seen[0] = abc_object.unkA | (u32)abc_object.unkC << 16 | (u32)abc_object.unkD << 24;
    seen[1] = abc_object.unkE | abc_object.unkF << 8 | (u32)(u16)abc_object.unk6 << 16;
    seen[2] = active | (D_801397C8 != NULL) << 8 | (D_801397D0 != NULL) << 9 | (D_801397CC != NULL) << 10 | (D_801397D4 != NULL) << 11;
    seen[3] = misc_objects[0].unk2 | misc_objects[0].ext.title_logo.palette_shift_speed << 8 | (u32)(u16)misc_objects[0].x_pos.i.hi << 16;
    seen[4] = need_palette_load | engine_obj.enable_boss << 8 | talk_palette[0x150] << 16;
    return c_test_observe(0, row, seen, expected, 5);
}

static void t_open_wait(void)
{
    talk_reset(0, 2, 0);
    func_80022730(&abc_object);
}
static void t_open_narration(void)
{
    talk_reset(0, 1, 0x80);
    func_80022730(&abc_object);
}
static void t_open_pair(void)
{
    talk_reset(0, 1, 0);
    talk_config.unk2 = 0x92;
    func_80022730(&abc_object);
}
static void t_open_pair_bright(void)
{
    talk_reset(0, 1, 0);
    talk_config.unk4 = 1;
    talk_config.unk2 = 0x91;
    engine_obj.armor_parts = 3;
    func_80022730(&abc_object);
}
static void t_open_alone_head(void)
{
    talk_reset(0, 1, 0);
    talk_config.unk5 = 1;
    engine_obj.armor_parts = 1;
    func_80022730(&abc_object);
}
static void t_open_alone_arms(void)
{
    talk_reset(0, 1, 0);
    talk_config.unk5 = 1;
    talk_config.unk4 = 1;
    engine_obj.armor_parts = 2;
    func_80022730(&abc_object);
}
static void t_open_zero(void)
{
    talk_reset(0, 1, 0);
    talk_config.unk5 = 1;
    engine_obj.cur_character = 1;
    func_80022730(&abc_object);
}
static void t_pause_skip(void)
{
    talk_reset(2, 3, 0);
    abc_object.unkF = 1;
    controller_input.pressed = 1;
    func_80022730(&abc_object);
}
static void t_pause_done(void)
{
    talk_reset(2, 1, 0);
    func_80022730(&abc_object);
}
static void t_wait_page(void)
{
    talk_reset(3, 0, 0);
    func_80022730(&abc_object);
}
static void t_wait_close(void)
{
    talk_reset(3, 0, 0);
    abc_object.unk4 = 0x8000;
    controller_input.pressed = 1;
    D_801397C4 = &misc_objects[1];
    misc_objects[1].id = 0x16;
    misc_objects[1].active = 1;
    D_801397D0 = &misc_objects[2];
    misc_objects[2].id = 0x16;
    misc_objects[2].active = 1;
    func_80022730(&abc_object);
}
static void t_close_wait(void)
{
    talk_reset(4, 2, 0);
    func_80022730(&abc_object);
}
static void t_close(void)
{
    talk_reset(4, 1, 0);
    D_80139828 = 1;
    D_801397E4[0] = 0x1234;
    D_801397BC = &misc_objects[3];
    misc_objects[3].id = 0x16;
    misc_objects[3].active = 1;
    func_80022730(&abc_object);
}
static void t_close_sigma(void)
{
    talk_reset(4, 1, 0);
    engine_obj.stage = 0xD;
    D_801397E4[0] = 0x4321;
    func_80022730(&abc_object);
}
static void t_finish_wait(void)
{
    talk_reset(6, 2, 0);
    abc_object.unkC = 1;
    func_80022730(&abc_object);
}
static void t_finish(void)
{
    talk_reset(6, 1, 0);
    abc_object.unkC = 1;
    func_80022730(&abc_object);
}
static void t_idle(void)
{
    talk_reset(7, 1, 0);
    func_80022730(&abc_object);
}

static void (*const talk_cases[])(void) = {
    t_open_wait,
    t_open_narration,
    t_open_pair,
    t_open_pair_bright,
    t_open_alone_head,
    t_open_alone_arms,
    t_open_zero,
    t_pause_skip,
    t_pause_done,
    t_wait_page,
    t_wait_close,
    t_close_wait,
    t_close,
    t_close_sigma,
    t_finish_wait,
    t_finish,
    t_idle,
};
static const u32 talk_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x1010000u, 0u, 0u, 0u, 0u, 0x1010000u, 0u, 0xF04u, 0x500005u, 0u, 0x1010000u, 0u, 0xF04u, 0x500605u, 0u, 0x1010000u, 0u, 0x302u, 0xA00205u, 0u, 0x1010000u, 0u, 0x302u, 0xA00405u, 0u, 0x1010000u, 0u, 0x302u, 0xA00005u, 0u, 0x2000002u, 0u, 0u, 0u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x3000000u, 0u, 0u, 0u, 0u, 0x4800027u, 0u, 0x200u, 0u, 0u, 0x4000001u, 0u, 0u, 0u, 0u, 0x5000000u, 0u, 0u, 0u, 0x12340101u, 0x5000000u, 0u, 0u, 0u, 1u, 0x6010001u, 0u, 0u, 0u, 0u, 0x6000000u, 0u, 0u, 0u, 0u, 0x7000001u, 0u, 0u, 0u, 0u };

static u32 test_dialogue_states(u32 row)
{
    return talk_run(talk_cases[row], row, &talk_expected[row * 5]);
}

#include "support/state_cases.h"

static void talk_portraits(u8 id)
{
    struct MiscObj** slots[7] = { &D_801397BC, &D_801397C0, &D_801397C4, &D_801397C8, &D_801397CC, &D_801397D0, &D_801397D4 };
    u32 i;
    for (i = 0; i < 7; i++) {
        *slots[i] = &misc_objects[i + 1];
        misc_objects[i + 1].id = id;
        misc_objects[i + 1].active = 1;
    }
}
static void t_wait_close_all(void)
{
    talk_reset(3, 0, 0);
    abc_object.unk4 = 0x8000;
    controller_input.pressed = 1;
    talk_portraits(0x16);
    func_80022730(&abc_object);
}
static void t_wait_close_reused(void)
{
    talk_reset(3, 0, 0);
    abc_object.unk4 = 0x8000;
    controller_input.pressed = 1;
    talk_portraits(0x17);
    func_80022730(&abc_object);
}
static void t_close_all(void)
{
    talk_reset(4, 1, 0);
    talk_portraits(0x16);
    func_80022730(&abc_object);
}
static void t_close_reused(void)
{
    talk_reset(4, 1, 0);
    talk_portraits(0x17);
    func_80022730(&abc_object);
}

static void (*const dialogue_portraits_cases[])(void) = {
    t_wait_close_all,
    t_wait_close_reused,
    t_close_all,
    t_close_reused,
};
static const u32 dialogue_portraits_expected[] = { 0x4800027u, 0u, 0xF01u, 0u, 0u, 0x4800027u, 0u, 0xF07u, 0u, 0u, 0x5000000u, 0u, 0xF00u, 0u, 1u, 0x5000000u, 0u, 0xF07u, 0u, 1u };

static u32 test_dialogue_portraits(u32 row)
{
    return talk_run(dialogue_portraits_cases[row], row, &dialogue_portraits_expected[row * 5]);
}

static const struct {
    u8 character, portrait;
    u16 text_flags;
    s16 expected_y;
} new_dialogues[] = {
    { 0, 0xFF, 0x800, 0xB4 },
    { 1, 0, 0x800, 0xAC },
    { 1, 0, 0, 0x3C },
    { 0, 0x80, 0, 0x74 },
};

static u32 test_dialogue_window(u32 row)
{
    u16 messages[] = { 2, new_dialogues[row].text_flags };
    struct MiscObj* window;
    u32 i;
    talk_reset(0, 0, new_dialogues[row].portrait);
    engine_obj.cur_character = new_dialogues[row].character;
    engine_obj.stage = 2;
    engine_obj.enable_boss = 1;
    engine_obj.unk1F = 7;
    TEST_ARC_48 = (u8*)messages;
    for (i = 0; i < COUNT(talk_palette); i++)
        talk_palette[i] = 0x1234;

    func_8002217C(0, new_dialogues[row].portrait, 0);

    window = D_801397BC;
    assert(window == &misc_objects[0]);
    assert(window->active == 1 && window->id == 0x16 && window->unk2 == 2);
    assert(window->x_pos.i.hi == 0xA0 && window->y_pos.i.hi == new_dialogues[row].expected_y);
    assert(window->bg_offset == -1 && window->unk42 == 0x7846);
    assert(window->unk40 == 0x1E00 && window->unk16 == 0x11);
    assert(abc_object.unk0 == &messages[1] && abc_object.unk4 == messages[1]);
    assert(abc_object.unkC == 0x80 && abc_object.unkD == 0 && abc_object.unkA == 0x27);
    assert(abc_object.unk6 == -0x78 && abc_object.unk8 == 0x1D && abc_object.unkF == 1);
    assert(D_801397D8 == new_dialogues[row].portrait);
    assert(engine_obj.enable_boss == 0 && engine_obj.unk1F == 0);
    assert(D_80139828 == 1 && D_80139824 == 7);
    for (i = 0; i < COUNT(D_801397E4); i++)
        assert(D_801397E4[i] == 0x1234);
    return (u16)window->y_pos.i.hi;
}

void func_800220C4(void);
void func_80022138(void);

static union {
    u32 words[0x800];
    u8 bytes[0x2000];
} expected;
static struct EngineObj engine_before;
static struct PlayerObj player_before;
static s32 clock_before;
static u16 random_before;

static void put16(u8* dest, u32 value)
{
    dest[0] = value;
    dest[1] = value >> 8;
}

static void put32(u8* dest, u32 value)
{
    put16(dest, value);
    put16(dest + 2, value >> 16);
}

static u16 get16(const u8* source)
{
    return source[0] | ((u16)source[1] << 8);
}

static void prepare(u32 salt)
{
    u32 i;
    for (i = 0; i < COUNT(expected.words); i += 4) {
        expected.words[i] = 0xA55A0000u ^ (salt * 0x1020304u) ^ i;
        expected.words[i + 1] = 0x5AA50000u ^ (salt * 0x4030201u) ^ i;
        expected.words[i + 2] = ~expected.words[i];
        expected.words[i + 3] = ~expected.words[i + 1];
    }
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    main_bss_state.frame_counter = salt ? (s32)0xFEDCBA98 : 0;
    cur_random = salt ? 0xFEDC : 0;
}

static void seal(void)
{
    c_test_copy_words((u32*)REPLAY_DATA, expected.words, COUNT(expected.words));
    engine_before = engine_obj;
    player_before = g_Player;
    clock_before = main_bss_state.frame_counter;
    random_before = cur_random;
}

static void check(void)
{
    assert(c_test_word_difference((const u32*)REPLAY_DATA, expected.words, COUNT(expected.words)) == 0);
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(main_bss_state.frame_counter == clock_before && cur_random == random_before);
}

static u32 snapshot(u32 row)
{
    u8 image[0x64];
    u32 pattern = row / 3, boss = row % 3, i;
    prepare(row);
    for (i = 0; i < sizeof(image); i++)
        image[i] = pattern == 0 ? 0 : pattern == 1 ? 0xFF
                                                   : (i * 73 + 0x35);
    put32(image + 0x20, boss == 0 ? 0 : 0x8013BED0u + (boss == 1 ? 0 : 47 * 0x9C));
    put32(image + 0x38, 0);
    put32(image + 0x3C, 0);
    engine_obj.state = image[0x00];
    engine_obj.unk1 = image[0x01];
    engine_obj.unk2 = image[0x02];
    engine_obj.unk3 = image[0x03];
    engine_obj.unk6 = image[0x06];
    engine_obj.unk7 = image[0x07];
    engine_obj.stage = image[0x0C];
    engine_obj.substage = image[0x0D];
    engine_obj.unkE = image[0x0E];
    engine_obj.unkF = image[0x0F];
    engine_obj.unk10 = image[0x10];
    engine_obj.unk11 = image[0x11];
    engine_obj.unk12 = image[0x12];
    engine_obj.unk13 = image[0x13];
    engine_obj.unk14 = image[0x14];
    engine_obj.unk15 = image[0x15];
    engine_obj.unk16 = image[0x16];
    engine_obj.unk17 = image[0x17];
    engine_obj.unk18 = image[0x18];
    engine_obj.unk19 = image[0x19];
    engine_obj.unk1A = image[0x1A];
    engine_obj.unk1B = image[0x1B];
    engine_obj.gameplay_locked = image[0x1C];
    engine_obj.checkpoint = image[0x1D];
    engine_obj.unk1E = image[0x1E];
    engine_obj.unk1F = image[0x1F];
    engine_obj.enable_boss = image[0x24];
    engine_obj.unk25 = image[0x25];
    engine_obj.unk36.value = image[0x36];
    engine_obj.unk37 = image[0x37];
    engine_obj.unk40 = image[0x40];
    engine_obj.unk41 = image[0x41];
    engine_obj.unk42 = image[0x42];
    engine_obj.cur_character = image[0x43];
    engine_obj.player_lives = image[0x44];
    engine_obj.checkpoint_hp = image[0x45];
    engine_obj.max_hp = image[0x46];
    engine_obj.armor_parts = image[0x47];
    engine_obj.arm_type = image[0x48];
    engine_obj.palette_flags = image[0x59];
    engine_obj.unk5F = image[0x5F];
    engine_obj.unk60 = image[0x60];
    engine_obj.unk4 = get16(image + 0x04);
    engine_obj.unk8 = get16(image + 0x08);
    engine_obj.unkA = get16(image + 0x0A);
    engine_obj.collected_upgrades = get16(image + 0x5A);
    engine_obj.boss_ptr = boss == 0 ? NULL : &main_objects[boss == 1 ? 0 : 47];
#ifdef MMX4_PC
    if (row == 9)
        engine_obj.boss_ptr = &main_objects[COUNT(main_objects)];
    if (row == 10) {
        engine_obj.controlled_player = &g_Player;
        engine_obj.unk3C = (struct BaseObj*)&main_objects[0];
        put32(image + 0x38, 0x81234568);
        put32(image + 0x3C, 0x89ABCDEF);
    }
#endif
    for (i = 0; i < 16; i++) {
        engine_obj.character_state.bytes[i] = image[0x26 + i];
        engine_obj.player_initial_data[i] = image[0x49 + i];
    }
    for (i = 0; i < 3; i++) {
        engine_obj.sub_tanks[i] = image[0x5C + i];
        engine_obj.pad61[i] = image[0x61 + i];
    }
    memcpy(expected.bytes + 0xC + 0x38, image + 0x38, 8);
    seal();
    put32(expected.bytes, 0);
    put32(expected.bytes + 4, clock_before);
    put16(expected.bytes + 8, random_before);
    memcpy(expected.bytes + 0xC, image, sizeof(image));
    func_800220C4();
    check();
    return 0x6400 + row;
}

static const u16 positions[] = { 0, 1, 1799, 3599, 3600 };
static u32 append(u32 row)
{
    u32 position = positions[row / 18], bit = row % 18;
    u16 held = bit == 0 ? 0 : bit == 17 ? 0xFFFF
                                        : 1u << (bit - 1);
    prepare(row + 1);
    put32(expected.bytes, position);
    g_Player.input.buttons.held = held;
    g_Player.input.buttons.previous = ~held;
    g_Player.pressed_input = 0x5AA5;
    seal();
    if (position < 3600) {
        put16(expected.bytes + 0xD4 + position * 2, held);
        put32(expected.bytes, position + 1);
    }
    func_80022138();
    check();
    return 0xD400 + row;
}

static u32 final_inputs(void)
{
    static const u16 inputs[] = { 0x8001, 0x1248, 0xFFFF, 0, 0x5AA5 };
    u32 i;
    prepare(7);
    put32(expected.bytes, 3597);
    seal();
    for (i = 0; i < COUNT(inputs); i++) {
        g_Player.input.buttons.held = inputs[i];
        player_before.input.buttons.held = inputs[i];
        if (i < 3) {
            put16(expected.bytes + 0xD4 + (3597 + i) * 2, inputs[i]);
            put32(expected.bytes, 3598 + i);
        }
        func_80022138();
        check();
    }
    return 3600;
}

static const CTestCase final_cases[] = { final_inputs };
static const u32 final_expected[] = { 3600 };
#ifdef MMX4_PC
static u32 native_snapshot(u32 row)
{
    return snapshot(row + 9);
}
#endif

const struct CTestGroup c_test_groups[] = {
    { "dialogue_window", 0, 0, COUNT(new_dialogues), test_dialogue_window },
    { "dialogue_portraits", 0, 0, COUNT(dialogue_portraits_cases), test_dialogue_portraits },
    { "dialogue_states", 0, 0, COUNT(talk_cases), test_dialogue_states },
    { "dialogue_interrupt_pool_full", NULL, dialogue_interrupt_pool_full_cases_expected, COUNT(dialogue_interrupt_pool_full_cases_expected), dialogue_interrupt_pool_full_cases_row },
    { "replay_snapshot", NULL, NULL, 9, snapshot },
    { "replay_append", NULL, NULL, 90, append },
    { "replay_full_buffer", final_cases, final_expected, COUNT(final_cases), 0 },
#ifdef MMX4_PC
    { "replay_native_snapshot", NULL, NULL, 2, native_snapshot },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(new_dialogues) + COUNT(dialogue_portraits_cases) + COUNT(talk_cases) + COUNT(dialogue_interrupt_pool_full_cases_expected) + 9 + 90 + COUNT(final_cases)
#ifdef MMX4_PC
    + 2
#endif
    ;
