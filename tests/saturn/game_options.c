#include "test_runtime.h"
#include "main/1A5BC.h"
#include "main/objects.h"

void func_80029DBC(void);
void func_80029E1C(struct GameInfo* arg0);
void func_8002A098(struct GameInfo* arg0);
void func_8002A394(struct GameInfo* arg0);
extern u16 saturn_button_masks[];

static struct GameInfo info;

static void reset(u8 character_mode, u8 character, u8 selection, u16 pressed)
{
    c_test_zero_words((u32*)&info, sizeof(info) / 4);
    c_test_zero_words((u32*)unk_objects, sizeof(unk_objects) / 4);
    main_bss_state.transition.active = 0;
    main_bss_state.transition.selection = selection;
    main_bss_state.character_mode = character_mode;
    engine_obj.cur_character = character;
    saturn_pad_pressed = pressed;
    D_8013B7D0 = 1;
}

static void open_x(void) { reset(0, 0, 3, 0); func_80029E1C(&info); }

static void input_confirm_exit(void) { reset(0, 0, 7, 0x0200); func_8002A098(&info); }
static void input_confirm_row(void) { reset(0, 0, 0, 0x0600); func_8002A098(&info); }
static void input_up_zero(void) { reset(0, 1, 7, 0x1000); func_8002A098(&info); }
static void input_down_zero(void) { reset(0, 1, 4, 0x2000); func_8002A098(&info); }
static void input_remap(void) { reset(0, 0, 0, 0x0100); func_8002A098(&info); }

static void exit_title(void) { reset(0, 0, 0, 0); func_8002A394(&info); }
static void exit_mode(void) { reset(1, 0, 0, 0); func_8002A394(&info); }

static void (*const option_cases[])(void) = {
    open_x,
    input_confirm_exit, input_confirm_row,
    input_up_zero, input_down_zero, input_remap,
    exit_title, exit_mode,
};

#define WORDS 5
static const u32 option_expected[][WORDS] = {
#include "game_options_expected.inc"
};

static u32 option_run(u32 row)
{
    u32 observed[WORDS], active = 0, masks = 0, i;
    option_cases[row]();
    for (i = 0; i < COUNT(unk_objects); i++)
        active += unk_objects[i].active != 0;
    for (i = 0; saturn_button_masks[i] != 0; i++)
        masks += saturn_button_masks[i] * (i + 1);
    observed[0] = (u8)info.unk0 | (u32)(u8)info.mode << 8 | (u32)(u8)info.unk2 << 16 | (u32)(u8)info.unk3 << 24;
    observed[1] = (u8)info.unk6 | (u32)main_bss_state.transition.selection << 8 | (u32)D_8013B7D0 << 16;
    observed[2] = active | (u32)(u8)unk_objects[2].unk2 << 8 | (u32)(u8)unk_objects[2].y_pos.i.hi << 16 | (u32)unk_objects[2].unk7 << 24;
    observed[3] = saturn_button_masks[4] | (u32)saturn_button_masks[5] << 16;
    observed[4] = masks;
    return c_test_observe(0, row, observed, option_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_options", 0, 0, COUNT(option_cases), option_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(option_cases);
