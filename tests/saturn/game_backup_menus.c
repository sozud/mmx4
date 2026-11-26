// saturn-capability: sh2_dma
#include "test_runtime.h"
#include "saturn/platform.h"
#include "saturn/menu.h"
#include "main/10CA4.h"
#include "main/menu.h"

static u8 sound_queue[0x800] __attribute__((aligned(4)));

static void reset(u8 stage)
{
    saturn_sound_driver_area = NULL;
    saturn_sound_command_queue = sound_queue;
    saturn_sound_command_slot = sound_queue;
    saturn_sound_request_read = saturn_sound_request_write = 0;
    saturn_sound_effect_request_read = saturn_sound_effect_request_write = 0;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.stage = stage;
    engine_obj.unk1 = 1;
    engine_obj.unk1F = 3;
    engine_obj.enable_boss = 1;
    main_bss_state.transition.selection = 2;
    saturn_color_ram[0] = 0x1111;
    saturn_title_palette[0] = 0x2222;
    need_palette_load = 0;
    D_800F1D90.save.character = 0x55;
}

typedef struct {
    u32 state;
    u32 sleep_timer;
    u32 context_argument;
    u32 entry;
    u32 saved_stack_pointer;
    u32 initial_stack_pointer;
} SaturnThread;
extern volatile SaturnThread saturn_threads[6];
void saturn_threads_init(void);
void saturn_threads_run(void);

static void (*menu_open)(struct EngineObj*);
static u32 frames;

static void menu_thread(void)
{
    menu_open(&engine_obj);
    saturn_thread_exit();
}

static void run_in_thread(void (*open)(struct EngineObj*))
{
    menu_open = open;
    saturn_threads_init();
    saturn_thread_create(1, (u32)menu_thread);
    for (frames = 0; frames < 10 && saturn_threads[1].state != 0; frames++)
        saturn_threads_run();
}

static void game_over_intro(void)
{
    reset(0);
    run_in_thread(func_80020580);
}

static void (*const menu_cases[])(void) = {
    game_over_intro,
};

#define WORDS 4
static const u32 menu_expected[][WORDS] = {
#include "game_backup_menus_expected.inc"
};

static u32 menu_run(u32 row)
{
    u32 observed[WORDS];
    menu_cases[row]();
    observed[0] = (u8)engine_obj.unk1 | (u32)(u8)engine_obj.unk1F << 8 | (u32)(u8)engine_obj.enable_boss << 16
        | (u32)main_bss_state.transition.selection << 24;
    observed[1] = (u16)engine_obj.unk4 | (u32)(u16)engine_obj.unk8 << 16;
    observed[2] = saturn_color_ram[0] | (u32)need_palette_load << 16 | (u32)saturn_display_mode << 24;
    observed[3] = D_800F1D90.save.character | (u32)main_bss_state.transition.active << 8 | frames << 16;
    return c_test_observe(0, row, observed, menu_expected[row], WORDS);
}

static u32 game_over_stage(u32 row)
{
    reset(3);
    engine_obj.cur_character = 1;
    saturn_backup_cart_status = row == 0 ? 0 : SATURN_BACKUP_UNAVAILABLE;
    run_in_thread(func_80020580);
    saturn_backup_cart_status = 0;
    assert(saturn_threads[1].state == 0);
    assert(D_800F1D90.save.character == 1);
    assert(engine_obj.unk1 == (row == 0 ? 2 : 4) && engine_obj.unk4 == 0x78);
    assert(engine_obj.unk1F == 0 && engine_obj.enable_boss == 0 && main_bss_state.transition.selection == 0);
    return engine_obj.unk1;
}

static u32 stage_select_menu(u32 row)
{
    reset(3);
    engine_obj.cur_character = 1;
    saturn_backup_cart_status = row == 0 ? 0 : SATURN_BACKUP_UNAVAILABLE;
    run_in_thread(func_80020B1C);
    saturn_backup_cart_status = 0;
    assert(saturn_threads[1].state == 0);
    assert(D_800F1D90.save.character == 1);
    assert(engine_obj.unk1 == (row == 0 ? 2 : 4));
    return engine_obj.unk1;
}

void func_800239E0(struct EngineObj*);
void func_80020A08(struct EngineObj*);
void func_80020C24(struct EngineObj*);
void func_80020D3C(struct EngineObj*);
void func_8001DAF8(void);
static const struct {
    void (*leave)(struct EngineObj*);
    u8 selection;
} quits[] = {
    { func_800206D0, 3 },
    { func_8002088C, 2 },
    { func_80020A08, 1 },
    { func_80020C24, 2 },
    { func_80020D3C, 1 },
    { func_800239E0, 0 },
};
static u32 menu_quit(u32 row)
{
    reset(3);
    main_bss_state.transition.active = 0;
    saturn_soft_reset_mode = 1;
    saturn_controller_refresh = 0;
    saturn_demo_return = 0;
    main_bss_state.transition.selection = quits[row].selection;
    run_in_thread(quits[row].leave);
    assert(saturn_threads[1].state == 0);
    assert(saturn_threads[0].state == 1 && saturn_threads[0].entry == (u32)func_8001DAF8);
    assert(saturn_soft_reset_mode == 0 && saturn_controller_refresh == 1);
    assert(engine_obj.state == 0 && engine_obj.unk1 == 1);
    assert(saturn_demo_return == (quits[row].leave == func_800239E0));
    saturn_threads[0].state = 0;
    return quits[row].selection;
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_backup_menus", 0, 0, COUNT(menu_cases), menu_run },
    { "saturn_game_over_stage", 0, 0, 2, game_over_stage },
    { "saturn_stage_select_menu", 0, 0, 2, stage_select_menu },
    { "saturn_menu_quit", 0, 0, COUNT(quits), menu_quit },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(menu_cases) + 2 + 2 + COUNT(quits);
