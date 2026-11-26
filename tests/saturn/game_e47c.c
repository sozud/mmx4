#include "test_runtime.h"
#include "saturn/menu.h"
#include "main/E47C.h"
#include "main/menu.h"

void func_8001EBA0(struct GameInfo* info);
void func_8001EE08(struct GameInfo* arg0);
void func_8001EFF0(struct GameInfo* arg0);
void func_8001DDB0(struct GameInfo* arg0);

static struct GameInfo info;

static void reset_info(void)
{
    c_test_zero_words((u32*)&info, sizeof(info) / 4);
    saturn_pad_pressed = 0;
    saturn_title_skip = 0;
    main_bss_state.transition.active = 0;
    main_bss_state.transition.selection = 0;
    saturn_color_ram[0] = 0x1111;
    saturn_title_palette[0] = 0x2222;
    saturn_title_palette_backup[0] = 0x3333;
    need_palette_load = 0;
}

static void intro_skip(void)
{
    info.mode = 3;
    info.unk4 = 5;
    info.unkD = 1;
    saturn_title_skip = 1;
    func_8001E708(&info);
}

static void options_open(void)
{
    func_8001E9E0(&info);
}

static void continue_open_saved(void)
{
    D_800F1D90.save.character = 0;
    func_8001EC90(&info);
}
static void continue_open_empty(void)
{
    D_800F1D90.save.character = 0xFF;
    func_8001EC90(&info);
}

extern u8* saturn_stage_screens;
extern u8* saturn_stage_screen_tiles;
extern u32* saturn_stage_tile_cells;
extern u8 saturn_stage_layout_width;
extern s16 saturn_stage_layout_size;
static u8 blank_screens[4];
static u16 blank_tiles[0x100];
static u32 blank_cells[4];

static void blank_stage(void)
{
    memset(background_objects, 0, sizeof(background_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    saturn_stage_screens = blank_screens;
    saturn_stage_screen_tiles = (u8*)blank_tiles;
    saturn_stage_tile_cells = blank_cells;
    saturn_stage_layout_width = 1;
    saturn_stage_layout_size = 1;
}
static void options_exit_title(void)
{
    blank_stage();
    main_bss_state.transition.selection = 1;
    func_8001EBA0(&info);
}
static void continue_exit_back(void)
{
    blank_stage();
    main_bss_state.transition.selection = 2;
    func_8001EE08(&info);
}
static void new_game_exit_back(void)
{
    blank_stage();
    main_bss_state.transition.selection = 2;
    func_8001EFF0(&info);
}

static void title_intro_first(void)
{
    info.mode = 1;
    func_8001DDB0(&info);
}
static void title_intro_skipped(void)
{
    info.mode = 1;
    saturn_title_skip = 1;
    func_8001DDB0(&info);
}
static void title_intro_end(void)
{
    info.mode = 1;
    info.unk4 = 27;
    func_8001DDB0(&info);
}
static void new_game_start(void)
{
    blank_stage();
    func_8001EFF0(&info);
}

static void (*const e47c_cases[])(void) = {
    intro_skip,
    options_open,
    continue_open_saved,
    continue_open_empty,
    options_exit_title,
    continue_exit_back,
    new_game_exit_back,
    title_intro_first,
    title_intro_skipped,
    title_intro_end,
    new_game_start,
};

#define WORDS 5
static const u32 e47c_expected[][WORDS] = {
#include "game_e47c_expected.inc"
};

static u32 e47c_run(u32 row)
{
    u32 observed[WORDS];
    reset_info();
    e47c_cases[row]();
    observed[0] = (u8)info.unk0 | (u8)info.mode << 8 | (u8)info.unk2 << 16 | (u8)info.unk3 << 24;
    observed[1] = (u16)info.unk4 | (u32)(u8)info.unkD << 16 | (u32)main_bss_state.transition.selection << 24;
    observed[2] = saturn_sound_output | (u32)need_palette_load << 8;
    observed[3] = saturn_color_ram[0] | (u32)saturn_title_palette_backup[0] << 16;
    observed[4] = saturn_display_mode | (u32)saturn_title_skip << 8;
    return c_test_observe(0, row, observed, row < COUNT(e47c_expected) ? e47c_expected[row] : e47c_expected[0], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_e47c_menu", 0, 0, COUNT(e47c_cases), e47c_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(e47c_cases);
