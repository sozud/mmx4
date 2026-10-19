#include "test_runtime.h"
#include "main/2824.h"
#include "main/game_info.h"
void func_80012600(void);

#ifdef MMX4_PC
#include <psyz/cd.h>
#include <psyz/spu.h>
#include <psyz/video.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void func_8001213C(void);
void clear_vram_rect_ptrs(void);
void load_vram_rect_ptrs(void);
void load_palette(void);
void func_80014780(void);
void func_800168D8(void);
s32 func_800169D8(void);
extern s32 mmx4_pc_sfx_group, mmx4_pc_canonical_load;
extern u32 mmx4_pc_sfx_index, mmx4_pc_sfx_frames;
extern const char* mmx4_pc_sfx_raw;
extern u8 D_80110064[];

static const char* direct_names[] = {
    "MMX4_DIRECT_STAGE",
    "MMX4_DIRECT_SUBSTAGE",
    "MMX4_DIRECT_CHECKPOINT",
    "MMX4_DIRECT_CHARACTER",
    "MMX4_DIRECT_LOADOUT",
    "MMX4_DIRECT_STORY",
};

static void environment_clear(void)
{
    u32 i;
    assert(unsetenv("MMX4_ORACLE_SCENE") == 0);
    for (i = 0; i < COUNT(direct_names); i++)
        assert(unsetenv(direct_names[i]) == 0);
    mmx4_pc_sfx_group = -1;
    mmx4_pc_sfx_raw = NULL;
    mmx4_pc_canonical_load = 0;
}

static void disc_path(char* cue)
{
    char* suffix;
    strcpy(cue, __FILE__);
    suffix = strstr(cue, "/tests/integration/boot.c");
    assert(suffix != NULL);
    strcpy(suffix, "/disks/mmx4.us.cue");
    if (access(cue, R_OK) != 0)
        c_test_skip();
}

static void prepare(void)
{
    char cue[sizeof(__FILE__) + 32];
    disc_path(cue);
    assert(setenv("SDL_AUDIODRIVER", "dummy", 1) == 0);
    assert(Psyz_CdSetDiskPath(cue) == 0);
    Psyz_SpuInit();
    assert(Psyz_VideoSetVsyncMode(PSYZ_VSYNC_LIMITLESS) == 0);
    func_8001213C();
    memset(&game_info, 0x25, sizeof(game_info));
    memset(&engine_obj, 0, sizeof(engine_obj));
}

static void check_threads(s32 fade)
{
    struct GameThread expected[4];
    u32 i;
    memset(expected, 0, sizeof(expected));
    expected[0].state = 2;
    expected[2].state = fade ? 2 : 0;
    assert(D_801F8300 == mmx4_pc_thread_slot(0));
    for (i = 0; i < 4; i++)
        c_test_same_words(mmx4_pc_thread_slot(i), &expected[i], sizeof(expected[i]));
}

static void check_game_info(void)
{
    struct GameInfo expected;
    memset(&expected, 0, sizeof(expected));
    c_test_same_words(&game_info, &expected, sizeof(expected));
    assert(D_8013BD44 == 1);
}

static u32 test_default(u32 row)
{
    static const char* scenes[] = { NULL, "", "unknown-scene" };
    struct EngineObj expected;
    environment_clear();
    if (scenes[row])
        assert(setenv("MMX4_ORACLE_SCENE", scenes[row], 1) == 0);
    prepare();
    mmx4_pc_thread_run(0);
    check_game_info();
    check_threads(0);
    memset(&expected, 0, sizeof(expected));
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    mmx4_pc_thread_run(0);
    assert(game_info.unk0 == 0 && game_info.mode == 1 && game_info.unkD == 1);
    assert(main_bss_state.character_mode == 1);
    assert(mmx4_pc_thread_slot(0)->state == 1 && mmx4_pc_thread_slot(0)->timer == 1);
    mmx4_pc_thread_run(0);
    assert(game_info.unk0 == 1 && game_info.mode == 0 && game_info.unkD == 1);
    return 1;
}

static u32 test_character_select(u32 row)
{
    struct EngineObj expected;
    u32 i;
    environment_clear();
    assert(setenv("MMX4_ORACLE_SCENE", "character-select", 1) == 0);
    if (row)
        for (i = 0; i < COUNT(direct_names); i++)
            assert(setenv(direct_names[i], "1", 1) == 0);
    prepare();
    mmx4_pc_thread_run(0);
    check_game_info();
    check_threads(1);
    memset(&expected, 0, sizeof(expected));
    expected.state = 1;
    expected.unk1 = 1;
    expected.stage = 14;
    expected.substage = 1;
    expected.unkA = 3;
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    assert(background_objects[0].unk3 == 0 && background_objects[1].unk3 == 0);
    assert(background_objects[2].unk3 == 1);
    assert(main_bss_state.transition.active == 1 && main_bss_state.transition.fade_amount == 8);
    assert(SP_BG_TILE_PIXELS != NULL && SP_BG_TILE_ATTRS != NULL && SP_PALETTE != NULL);
    return 1;
}

static void set_value(const char* name, u32 value)
{
    char text[16];
    snprintf(text, sizeof(text), "%u", value);
    assert(setenv(name, text, 1) == 0);
}

static u32 test_briefing(u32 row)
{
    struct EngineObj expected;
    u32 character = row % 2, loadout = row / 2 % 3, story = row / 6;
    environment_clear();
    assert(setenv("MMX4_ORACLE_SCENE", "mission-briefing", 1) == 0);
    if (row) {
        set_value("MMX4_DIRECT_STAGE", 8);
        set_value("MMX4_DIRECT_CHARACTER", character);
        set_value("MMX4_DIRECT_LOADOUT", loadout);
        set_value("MMX4_DIRECT_STORY", story);
    }
    prepare();
    mmx4_pc_thread_run(0);
    check_game_info();
    check_threads(0);
    memset(&expected, 0, sizeof(expected));
    expected.state = 3;
    expected.stage = 13;
    expected.cur_character = character;
    expected.unk5F = story;
    expected.unk1 = 8;
    expected.unkE = story ? 2 : character;
    if (loadout) {
        expected.player_lives = 4;
        expected.checkpoint_hp = expected.max_hp = 0x30;
        expected.collected_upgrades = 0xF0FF;
        expected.palette_flags = loadout == 2 ? 0 : 0xFF;
        expected.sub_tanks[0] = expected.sub_tanks[1] = 0xA0;
        expected.sub_tanks[2] = 0x20;
        if (character == 0) {
            expected.armor_parts = 15;
            expected.arm_type = 2;
        }
    }
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    assert(SP_BG_TILE_PIXELS != NULL && SP_BG_TILE_ATTRS != NULL && SP_PALETTE != NULL);
    return 1;
}

static u32 test_initial_stage(u32 row)
{
    static const u8 stages[] = { 0, 1, 8, 9 };
    struct EngineObj expected;
    u32 character = row % 2, loadout = row / 2 % 3, stage = stages[row / 6];
    u32 substage = row % 2, checkpoint = row % 4, story = row % 11;
    environment_clear();
    assert(setenv("MMX4_ORACLE_SCENE", "initial-stage", 1) == 0);
    if (row) {
        set_value("MMX4_DIRECT_STAGE", stage);
        set_value("MMX4_DIRECT_SUBSTAGE", substage);
        set_value("MMX4_DIRECT_CHECKPOINT", checkpoint);
        set_value("MMX4_DIRECT_CHARACTER", character);
        set_value("MMX4_DIRECT_LOADOUT", loadout);
        set_value("MMX4_DIRECT_STORY", story);
    }
    prepare();
    mmx4_pc_thread_run(0);
    check_game_info();
    check_threads(0);
    memset(&expected, 0, sizeof(expected));
    expected.state = 5;
    expected.stage = stage;
    expected.substage = substage;
    expected.checkpoint = checkpoint;
    expected.cur_character = character;
    expected.player_lives = 2;
    expected.max_hp = 0x20;
    expected.unk5F = story;
    if (loadout) {
        expected.player_lives = 4;
        expected.checkpoint_hp = expected.max_hp = 0x30;
        expected.collected_upgrades = 0xF0FF;
        expected.palette_flags = loadout == 2 && stage >= 1 && stage <= 8
            ? (u8) ~(1 << (stage - 1))
            : 0xFF;
        expected.sub_tanks[0] = expected.sub_tanks[1] = 0xA0;
        expected.sub_tanks[2] = 0x20;
        if (character == 0) {
            expected.armor_parts = 15;
            expected.arm_type = 2;
        }
    }
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    assert(layout_width == D_80110064[stage * 4 + substage * 2]);
    assert(layout_height == D_80110064[stage * 4 + substage * 2 + 1]);
    assert(layout_size == layout_width * layout_height);
    assert(D_80171EA8 == 0);
    assert(SP_BG_TILE_PIXELS != NULL && SP_BG_TILE_ATTRS != NULL && SP_PALETTE != NULL);
    return 1;
}

static u32 test_sfx_return(u32 row)
{
    struct EngineObj expected;
    struct GameInfo info;
    environment_clear();
    mmx4_pc_sfx_group = row ? 5 : 0;
    mmx4_pc_sfx_index = row ? 0 : 12;
    prepare();
    info = game_info;
    func_8001D064();
    memset(&expected, 0, sizeof(expected));
    expected.stage = 14;
    expected.substage = 1;
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    c_test_same_words(&game_info, &info, sizeof(info));
    assert(D_8013E198[mmx4_pc_sfx_group] >= 0);
    assert(SP_BG_TILE_PIXELS != NULL && SP_BG_TILE_ATTRS != NULL);
    assert(mmx4_pc_thread_slot(0)->state == 2);
    return 1;
}

static u32 test_sfx_file(u32 row)
{
    char directory[] = "/tmp/mmx4-boot-sfx-XXXXXX";
    char raw[sizeof(directory) + 16], log[sizeof(directory) + 16], text[4096];
    const char* output;
    FILE* stream;
    struct stat status;
    pid_t child;
    s16 samples[735 * 2 * 3];
    u32 i, nonzero = 0;
    int wait_status, result;
    char cue[sizeof(__FILE__) + 32];
    disc_path(cue);
    assert(mkdtemp(directory) != NULL);
    snprintf(raw, sizeof(raw), "%s/audio.pcm", directory);
    snprintf(log, sizeof(log), "%s/run.log", directory);
    output = row == 2 ? directory : row == 3 ? "/dev/full"
                                             : raw;
    fflush(NULL);
    child = fork();
    assert(child >= 0);
    if (child == 0) {
        assert(freopen(log, "w", stderr) != NULL);
        environment_clear();
        mmx4_pc_sfx_group = row == 1 ? 5 : 0;
        mmx4_pc_sfx_index = row == 1 ? 0 : 12;
        mmx4_pc_sfx_raw = output;
        mmx4_pc_sfx_frames = 3;
        prepare();
        func_8001D064();
        _exit(99);
    }
    assert(waitpid(child, &wait_status, 0) == child && WIFEXITED(wait_status));
    assert(WEXITSTATUS(wait_status) == (row >= 2 ? EXIT_FAILURE : EXIT_SUCCESS));
    stream = fopen(log, "r");
    assert(stream != NULL);
    i = fread(text, 1, sizeof(text) - 1, stream);
    assert(!ferror(stream) && fclose(stream) == 0);
    text[i] = 0;
    {
        char* trigger = strstr(text, "MMX4 SFX fixture: group=");
        assert(trigger != NULL);
        trigger = strstr(trigger, "result=");
        assert(trigger != NULL);
        result = strtol(trigger + 7, NULL, 10);
        assert(result >= 0);
    }
    if (row >= 2) {
        assert(strstr(text, row == 2 ? "cannot open" : "write failed") != NULL);
        assert(access(raw, F_OK) == -1);
    } else {
        assert(strstr(text, "rendered 3 frames") != NULL);
        assert(stat(raw, &status) == 0 && status.st_size == sizeof(samples));
        stream = fopen(raw, "rb");
        assert(stream != NULL);
        assert(fread(samples, sizeof(samples), 1, stream) == 1);
        assert(fgetc(stream) == EOF && !ferror(stream) && fclose(stream) == 0);
        for (i = 0; i < COUNT(samples); i++)
            nonzero += samples[i] != 0;
        assert(nonzero > 0);
        assert(unlink(raw) == 0);
    }
    assert(unlink(log) == 0 && rmdir(directory) == 0);
    return 1;
}

static void tick(u16 pressed)
{
    VSync(0);
    SP_DRAW_BUFFER ^= 1;
    cur_draw_info = &draw_infos[SP_DRAW_BUFFER];
    ClearOTagR(&cur_draw_info->ordering_table.start, 12);
    func_800168D8();
    func_800169D8();
    clear_vram_rect_ptrs();
    main_bss_state.frame_counter++;
    controller_input.held = controller_input.pressed = pressed;
    controller_input.previous = 0;
    func_80012600();
    func_80014780();
    DrawSync(0);
    load_vram_rect_ptrs();
    load_palette();
    DrawSync(0);
}

static u32 test_title_input(u32 row)
{
    static const u16 inputs[] = { 0, PAD_CONFIRM, PADstart };
    u32 frame;
    struct GameInfo expected;
    environment_clear();
    prepare();
    for (frame = 0; frame < 2000; frame++) {
        tick(0);
        if (game_info.unk0 == 1 && game_info.mode == 13
            && game_info.unkD == 0 && main_bss_state.transition.active == 0)
            break;
    }
    assert(frame < 2000);
    expected = game_info;
    expected.unk4--;
    if (row == 2) {
        expected.unk0 = 5;
        expected.mode = expected.unk2 = expected.unk3 = 0;
        expected.unkD = 1;
        expected.unkE = 1;
    }
    tick(inputs[row]);
    c_test_same_words(&game_info, &expected, sizeof(expected));
    assert(main_bss_state.transition.active == (row == 2 ? -1 : 0));
    assert(mmx4_pc_thread_slot(0)->state == 1 && mmx4_pc_thread_slot(0)->timer == 1);
    return 1;
}

static u32 test_attract_input(u32 row)
{
    struct GameInfo expected;
    u32 frame;
    environment_clear();
    prepare();
    for (frame = 0; frame < 8000; frame++) {
        tick(0);
        if (game_info.unk0 == 2 && game_info.mode == 2
            && main_bss_state.transition.active == 0) {
            if (row != 2 || game_info.unk4 == 1 || g_Player.active == 0 || g_Player.state == 3)
                break;
        }
    }
    assert(frame < 8000);
    expected = game_info;
    expected.unk4--;
    if (row) {
        expected.unk0 = 5;
        expected.mode = expected.unk2 = expected.unk3 = 0;
        expected.unkD = 1;
        expected.unkE = 2;
    } else {
        expected.unkD = 0;
    }
    tick(row ? PAD_CONFIRM : 0);
    c_test_same_words(&game_info, &expected, sizeof(expected));
    assert(main_bss_state.transition.active == (row ? -1 : 0));
    assert(mmx4_pc_thread_slot(0)->state == 1 && mmx4_pc_thread_slot(0)->timer == 1);
    return 1;
}

static u32 test_fade_boundaries(u32 row)
{
    static const s8 amounts[] = { 1, 2, 3, 8, 16, 17, 31, 127 };
    u32 amount = amounts[row / 4], buffer = row % 2;
    s32 positive = (row / 2) % 2;
    s32 value = positive ? 255 : 0;
    u32 step, steps = positive ? (255 + amount - 1) / amount : (256 + amount - 1) / amount;
    environment_clear();
    prepare();
    SP_DRAW_BUFFER = buffer;
    cur_draw_info = &draw_infos[buffer];
    if (positive)
        func_800129A4(amount);
    else
        func_800129F0(amount);
    mmx4_pc_thread_run(2);
    assert(D_8016DEA0.unk0 == 0 && D_8016DEA0.unk4 == value);
    for (step = 0; step < steps; step++) {
        ClearOTagR(&cur_draw_info->ordering_table.start, 12);
        mmx4_pc_thread_run(2);
        assert(D_80169D78[buffer].r0 == value);
        assert(D_80169D78[buffer].g0 == value && D_80169D78[buffer].b0 == value);
        value += positive ? -(s32)amount : (s32)amount;
        if (step == steps - 1)
            value = positive ? 0 : 255;
        assert(D_8016DEA0.unk4 == value);
        assert(D_8016DEA0.unk0 == (step == steps - 1));
        assert(main_bss_state.transition.active == (positive ? 1 : -1));
        assert(main_bss_state.transition.fade_amount == (step == steps - 1 ? 2 : amount));
    }
    for (step = 0; step < 3; step++) {
        ClearOTagR(&cur_draw_info->ordering_table.start, 12);
        mmx4_pc_thread_run(2);
        assert(D_8016DEA0.unk4 == value);
        assert(main_bss_state.transition.fade_amount == (step < 2 ? 1 - step : 0));
        assert(main_bss_state.transition.active == (step < 2 ? (positive ? 1 : -1) : 0));
    }
    assert(mmx4_pc_thread_slot(2)->state == 0);
    assert(mmx4_pc_thread_slot(0)->state == 2);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "default_boot_route", 0, 0, 3, test_default },
    { "character_select_boot_route", 0, 0, 2, test_character_select },
    { "briefing_boot_route", 0, 0, 12, test_briefing },
    { "initial_stage_boot_route", 0, 0, 24, test_initial_stage },
    { "sfx_boot_return", 0, 0, 2, test_sfx_return },
    { "sfx_boot_file", 0, 0, 4, test_sfx_file },
    { "title_input_from_boot", 0, 0, 3, test_title_input },
    { "attract_input_from_boot", 0, 0, 3, test_attract_input },
    { "fade_thread_boundaries", 0, 0, 32, test_fade_boundaries },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 3 + 2 + 12 + 24 + 2 + 4 + 3 + 3 + 32;
#else
const struct CTestGroup c_test_groups[] = { { 0 } };
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
