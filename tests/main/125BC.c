#include "test_runtime.h"

void func_80021E74(void);
void func_80022074(void);

static union {
    u32 words[0x800];
    u8 bytes[0x2000];
} expected_replay;
static struct EngineObj expected_engine;
static struct MainObj expected_mains[48];
static struct PlayerObj expected_player;
static s32 expected_clock;
static u16 expected_random;

static void put16(u8* target, u32 value)
{
    target[0] = value;
    target[1] = value >> 8;
}

static void put32(u8* target, u32 value)
{
    put16(target, value);
    put16(target + 2, value >> 16);
}

static u16 get16(const u8* source)
{
    return source[0] | ((u16)source[1] << 8);
}

static void make_image(u8* image, u32 pattern, s32 boss)
{
    u32 i;
    for (i = 0; i < 0x64; i++)
        image[i] = pattern == 0 ? 0 : pattern == 1 ? 0xFF
                                                   : (i * 73 + 0x35);
    put32(image + 0x20, boss < 0 ? 0 : 0x8013BED0u + boss * 0x9C);
    put32(image + 0x38, 0);
    put32(image + 0x3C, 0);
}

static void engine_from_image(struct EngineObj* target, const u8* image, s32 boss)
{
    u32 i;
    c_test_zero_words((u32*)target, sizeof(*target) / 4);
    target->state = image[0x00];
    target->unk1 = image[0x01];
    target->unk2 = image[0x02];
    target->unk3 = image[0x03];
    target->unk6 = image[0x06];
    target->unk7 = image[0x07];
    target->stage = image[0x0C];
    target->substage = image[0x0D];
    target->unkE = image[0x0E];
    target->unkF = image[0x0F];
    target->unk10 = image[0x10];
    target->unk11 = image[0x11];
    target->unk12 = image[0x12];
    target->unk13 = image[0x13];
    target->unk14 = image[0x14];
    target->unk15 = image[0x15];
    target->unk16 = image[0x16];
    target->unk17 = image[0x17];
    target->unk18 = image[0x18];
    target->unk19 = image[0x19];
    target->unk1A = image[0x1A];
    target->unk1B = image[0x1B];
    target->gameplay_locked = image[0x1C];
    target->checkpoint = image[0x1D];
    target->unk1E = image[0x1E];
    target->unk1F = image[0x1F];
    target->enable_boss = image[0x24];
    target->unk25 = image[0x25];
    target->unk36.value = image[0x36];
    target->unk37 = image[0x37];
    target->unk40 = image[0x40];
    target->unk41 = image[0x41];
    target->unk42 = image[0x42];
    target->cur_character = image[0x43];
    target->player_lives = image[0x44];
    target->checkpoint_hp = image[0x45];
    target->max_hp = image[0x46];
    target->armor_parts = image[0x47];
    target->arm_type = image[0x48];
    target->palette_flags = image[0x59];
    target->unk5F = image[0x5F];
    target->unk60 = image[0x60];
    target->unk4 = get16(image + 0x04);
    target->unk8 = get16(image + 0x08);
    target->unkA = get16(image + 0x0A);
    target->collected_upgrades = get16(image + 0x5A);
    target->boss_ptr = boss < 0 ? NULL : &main_objects[boss];
    for (i = 0; i < 16; i++) {
        target->character_state.bytes[i] = image[0x26 + i];
        target->player_initial_data[i] = image[0x49 + i];
    }
    for (i = 0; i < 3; i++) {
        target->sub_tanks[i] = image[0x5C + i];
        target->pad61[i] = image[0x61 + i];
    }
}

static void check(void)
{
    assert(c_test_word_difference((const u32*)REPLAY_DATA, expected_replay.words, COUNT(expected_replay.words)) == 0);
    assert(c_test_word_difference((const u32*)main_objects, (const u32*)expected_mains, sizeof(expected_mains) / 4) == 0);
    c_test_same_words(&engine_obj, &expected_engine, sizeof(engine_obj));
    c_test_same_words(&g_Player, &expected_player, sizeof(g_Player));
    assert(main_bss_state.frame_counter == expected_clock && cur_random == expected_random);
}

static const s32 clocks[] = { 0, 0x7FFFFFFF, (s32)0x80000000 };
static const u16 randoms[] = { 0, 0xFFFF, 0x9234 };
#ifdef MMX4_PC
static const u32 bad_addresses[] = {
    0x8013BECF,
    1,
    0x8013BED1,
    0x8013BF6B,
    0x8013DC10,
    0x8013DC11,
    0x8013DCAC,
    0xFFFFFFFF,
};
#endif

static u32 playback(u32 row, u32 native)
{
    struct EngineObj saved_engine;
    u8 initial_image[0x64], saved_image[0x64], next_image[0x64];
    u32 i, mode = row % 2, pattern = (row / 2) % 3;
    s32 boss = native ? -1 : (s32)(row / 6) - 1;
    s32 saved_boss = boss < 0 ? 47 : 47 - boss;
    for (i = 0; i < COUNT(expected_replay.words); i += 4) {
        expected_replay.words[i] = 0xA55A0000u ^ i;
        expected_replay.words[i + 1] = 0x5AA50000u ^ i;
        expected_replay.words[i + 2] = ~expected_replay.words[i];
        expected_replay.words[i + 3] = ~expected_replay.words[i + 1];
    }
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    for (i = 0; i < COUNT(main_objects); i++) {
        main_objects[i].id = i;
        main_objects[i].x_pos.val = 0x12340000u + i * 65539;
    }
    c_test_copy_words((u32*)expected_mains, (const u32*)main_objects, sizeof(expected_mains) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    g_Player.input.history = 0xCAFE1234;
    g_Player.pressed_input = 0x8001;
    expected_player = g_Player;
    make_image(initial_image, pattern, boss);
    make_image(saved_image, (pattern + 1) % 3, saved_boss);
    engine_from_image(&engine_obj, saved_image, saved_boss);
#ifdef MMX4_PC
    if (native) {
        put32(initial_image + 0x20, bad_addresses[row / 6]);
        put32(initial_image + 0x38, 0x81234568);
        put32(initial_image + 0x3C, 0x89ABCDEF);
        engine_obj.controlled_player = &g_Player;
        engine_obj.unk3C = (struct BaseObj*)&main_objects[7];
    }
#endif
    saved_engine = engine_obj;
    put32(expected_replay.bytes, 0xDEADBEEF);
    put32(expected_replay.bytes + 4, clocks[pattern]);
    put16(expected_replay.bytes + 8, randoms[pattern]);
    memcpy(expected_replay.bytes + 0xC, initial_image, 0x64);
    c_test_copy_words((u32*)REPLAY_DATA, expected_replay.words, COUNT(expected_replay.words));
    main_bss_state.frame_counter = 1234567;
    cur_random = 0x4321;
    put32(expected_replay.bytes, 0);
#ifndef MMX4_PC
    memcpy(expected_replay.bytes + 0x70, saved_image, 0x64);
#endif
    engine_from_image(&expected_engine, initial_image, boss);
    expected_clock = clocks[pattern];
    expected_random = randoms[pattern];
    func_80021E74();
    check();

    if (mode) {
        engine_obj.player_lives = 9;
        engine_obj.unk36.value = 0x37;
        expected_engine.player_lives = 9;
        expected_engine.unk36.value = 0x37;
        saved_engine = expected_engine;
        initial_image[0x44] = 9;
        initial_image[0x36] = 0x37;
#ifndef MMX4_PC
        memcpy(expected_replay.bytes + 0x70, initial_image, 0x64);
#endif
        make_image(next_image, (pattern + 2) % 3, saved_boss);
        memcpy(expected_replay.bytes + 0xC, next_image, 0x64);
        memcpy(REPLAY_DATA + 0xC, next_image, 0x64);
        put32(expected_replay.bytes + 4, clocks[(pattern + 1) % 3]);
        put16(expected_replay.bytes + 8, randoms[(pattern + 1) % 3]);
        put32(REPLAY_DATA + 4, clocks[(pattern + 1) % 3]);
        put16(REPLAY_DATA + 8, randoms[(pattern + 1) % 3]);
        put32(expected_replay.bytes, 0);
        engine_from_image(&expected_engine, next_image, saved_boss);
        expected_clock = clocks[(pattern + 1) % 3];
        expected_random = randoms[(pattern + 1) % 3];
        func_80021E74();
        check();
    }

    engine_obj.state = 5;
    engine_obj.player_lives = 2;
    engine_obj.boss_ptr = &main_objects[3];
    main_bss_state.frame_counter = expected_clock = -7654321;
    cur_random = expected_random = 0xA1B2;
    expected_engine = saved_engine;
    func_80022074();
    check();
    if (!mode) {
        engine_obj.player_lives = 1;
        func_80022074();
        check();
    }
    return (native ? 0xB900 : 0xA900) + row;
}

static u32 shared(u32 row)
{
    u32 value = playback(row, 0);
    assert(value == 0xA900 + row);
    return value;
}

#ifdef MMX4_PC
static u32 native(u32 row)
{
    u32 value = playback(row, 1);
    assert(value == 0xB900 + row);
    return value;
}
#endif

const struct CTestGroup c_test_groups[] = {
    { "replay_playback_lifecycle", NULL, NULL, 12, shared },
#ifdef MMX4_PC
    { "replay_native_address_validation", NULL, NULL, 48, native },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12
#ifdef MMX4_PC
    + 48
#endif
    ;
