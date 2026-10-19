#include "test_runtime.h"
#include "main/102FC.h"
#include "main/game_info.h"
void func_80012328(void);
struct ControllerButtons {
    u16 current, previous, pressed;
};
#ifdef MMX4_PC
extern struct ControllerButtons D_80166D50;
#else
extern u16 D_80166D52;
#define D_80166D50 (*(struct ControllerButtons*)((u8*)&D_80166D52 - 2))
#endif
static u8 primary[34], secondary[34];
static u32 packets(u32 row)
{
    struct EngineObj engine = engine_obj;
    struct PlayerObj player = g_Player;
    struct MainBssState main = main_bss_state;
    u32 i, frame, wire, expected, previous = 0x100;
    (void)row;
    StopPAD();
    for (i = 0; i < 34; i++)
        primary[i] = secondary[i] = 0xA5;
    primary[0] = 0;
    primary[1] = 0x41;
    primary[2] = primary[3] = 0xFF;
    controller_input.held = 0x100;
    controller_input.previous = 0x200;
    controller_input.pressed = 0x400;
    D_80166D50.current = 0x100;
    D_80166D50.previous = 0x200;
    D_80166D50.pressed = 0x400;
    for (frame = 0; frame < 5; frame++) {
        wire = frame == 1 ? 0xA040 : 0x5020;
        expected = (frame == 0 || frame == 4) ? 0 : frame == 1 ? 0x40
                                                               : 0x20;
        secondary[0] = frame == 0 ? 0xFF : 0;
        secondary[1] = frame == 4 ? 0x73 : 0x41;
        secondary[2] = (u8)(~wire >> 8);
        secondary[3] = (u8)~wire;
        for (i = 0; i < 34; i++) {
            pad_port1_packet[i] = primary[i];
            D_8012F46C[i] = secondary[i];
        }
        func_80012328();
        assert(controller_input.held == 0 && controller_input.previous == (frame == 0 ? 0x100 : 0) && controller_input.pressed == 0);
        assert(D_80166D50.current == expected && D_80166D50.previous == previous && D_80166D50.pressed == (expected & (expected ^ previous)));
        previous = expected;
        for (i = 0; i < 34; i++)
            assert(pad_port1_packet[i] == primary[i] && D_8012F46C[i] == secondary[i]);
        c_test_same_words(&engine_obj, &engine, sizeof(engine));
        c_test_same_words(&g_Player, &player, sizeof(player));
        c_test_same_words(&main_bss_state, &main, sizeof(main));
    }
    assert(StartPAD() == 1);
    return 1;
}

void func_80012600(void);
void func_80012740(s32, void*);
void func_800127FC(void);
void func_80012854(s32);
void func_800128EC(s32);
void func_80012910(s32);
static volatile u32 entered, returned;
static struct GameThread saved[4], expected[4];
static u32 worker_stack[256];
static void menu_worker(void)
{
    entered = 1;
    func_8001D9D0(&game_info);
    returned = 1;
    func_800127FC();
}
static u32 handoff(u32 row)
{
    struct GameThread* slots[4];
    struct GameThread* current;
    struct EngineObj engine;
    struct GameInfo game;
    struct PlayerObj player = g_Player;
    struct MainBssState main;
    struct ControllerInput input = controller_input;
    u32 i;
    u16 rng = cur_random;
    (void)row;
#ifdef MMX4_PC
    mmx4_pc_threads_init();
    for (i = 0; i < 4; i++)
        slots[i] = mmx4_pc_thread_slot(i);
#else
    for (i = 0; i < 4; i++)
        slots[i] = &GAME_THREADS[i];
#endif
    current = D_801F8300;
    for (i = 0; i < 4; i++)
        saved[i] = *slots[i];
    assert(slots[3]->state == 0);
    for (i = 0; i < 3; i++)
        func_800128EC(i);
    for (i = 0; i < COUNT(worker_stack); i++)
        worker_stack[i] = 0x13579BDF;
    slots[3]->stack = (u32)(unsigned long)&worker_stack[240];
    memset(&game_info, 0, sizeof(game_info));
    game_info.unk0 = 6;
    game_info.mode = 2;
    game_info.unk2 = 0;
    main_bss_state.transition.active = 0;
    game = game_info;
    main = main_bss_state;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine = engine_obj;
    engine.state = 0;
    entered = returned = 0;
    func_80012740(3, menu_worker);
    for (i = 0; i < 4; i++)
        expected[i] = *slots[i];
    func_80012600();
    assert(entered == 1 && returned == 0 && slots[1]->state == 2 && slots[1]->handle != (u32)-1 && slots[3]->state == 0);
    expected[1].state = 2;
    expected[1].handle = slots[1]->handle;
    expected[3].state = 0;
    for (i = 0; i < 4; i++)
        c_test_same_words(slots[i], &expected[i], sizeof(expected[i]));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&game_info, &game, sizeof(game));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(cur_random == rng);
    func_80012854(1);
    *slots[1] = saved[1];
    for (i = 0; i < 3; i++)
        if (!(saved[i].state & 0x40))
            func_80012910(i);
    *slots[3] = saved[3];
    D_801F8300 = current;
    for (i = 0; i < 4; i++)
        c_test_same_words(slots[i], &saved[i], sizeof(saved[i]));
    for (i = 0; i < 16; i++)
        assert(worker_stack[i] == 0x13579BDF && worker_stack[240 + i] == 0x13579BDF);
    return 1;
}

void func_80012454(void);
static u32 hold(u32 row)
{
    struct EngineObj engine;
    struct PlayerObj player = g_Player;
    struct MainBssState main;
    struct ControllerInput input;
    u32 i;
    (void)row;
    engine_obj.state = 6;
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    engine_obj.unk5F = 3;
    engine = engine_obj;
    main_bss_state.transition.active = 0;
    main = main_bss_state;
    memset(&controller_input, 0, sizeof(controller_input));
    controller_input.held = PADstart | PADselect;
    input = controller_input;
    D_8013BD44 = 1;
    D_80141BD2 = 120;
    cur_random = 0x1234;
    for (i = 0; i < 119; i++) {
        func_80012454();
        assert(D_80141BD2 == 119 - i);
    }
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(D_8013BD44 == 1 && cur_random == 0x1234);
    controller_input.held = 0;
    input.held = 0;
    func_80012454();
    assert(D_80141BD2 == 120);
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(D_8013BD44 == 1 && cur_random == 0x1234);
    return 1;
}

void func_80012600(void);
void func_80012740(s32, void*);
void func_800127C8(s32);
void func_800127FC(void);
void func_800128EC(s32);
void func_80012910(s32);
static volatile u32 progress;
static struct GameThread saved_thread_two_frame_wait[4], expected_thread_two_frame_wait[4];
static u32 worker_stack_thread_two_frame_wait[256];
static void worker(void)
{
    progress = 1;
    func_800127C8(2);
    progress = 2;
    func_800127FC();
}
static u32 wait_two(u32 row)
{
    struct GameThread* slots[4];
    struct GameThread* current;
    struct EngineObj engine = engine_obj;
    struct PlayerObj player = g_Player;
    u32 i;
    (void)row;
#ifdef MMX4_PC
    mmx4_pc_threads_init();
    for (i = 0; i < 4; i++)
        slots[i] = mmx4_pc_thread_slot(i);
#else
    for (i = 0; i < 4; i++)
        slots[i] = &GAME_THREADS[i];
#endif
    current = D_801F8300;
    for (i = 0; i < 4; i++)
        saved_thread_two_frame_wait[i] = *slots[i];
    assert(slots[3]->state == 0);
    for (i = 0; i < COUNT(worker_stack_thread_two_frame_wait); i++)
        worker_stack_thread_two_frame_wait[i] = 0x13579BDF;
    for (i = 0; i < 3; i++)
        func_800128EC(i);
    slots[3]->timer = 0;
    slots[3]->stack = (u32)(unsigned long)&worker_stack_thread_two_frame_wait[240];
    progress = 0;
    func_80012740(3, worker);
    assert(slots[3]->state == 2 && slots[3]->handle != (u32)-1);
    for (i = 0; i < 4; i++)
        expected_thread_two_frame_wait[i] = *slots[i];
    func_80012600();
    assert(progress == 1 && slots[3]->state == 1 && slots[3]->timer == 2);
    expected_thread_two_frame_wait[3].state = 1;
    expected_thread_two_frame_wait[3].timer = 2;
    for (i = 0; i < 4; i++)
        c_test_same_words(slots[i], &expected_thread_two_frame_wait[i], sizeof(expected_thread_two_frame_wait[i]));
    func_80012600();
    assert(progress == 1 && slots[3]->state == 1 && slots[3]->timer == 1);
    expected_thread_two_frame_wait[3].timer = 1;
    for (i = 0; i < 4; i++)
        c_test_same_words(slots[i], &expected_thread_two_frame_wait[i], sizeof(expected_thread_two_frame_wait[i]));
    func_80012600();
    assert(progress == 2 && slots[3]->state == 0 && slots[3]->timer == 0);
    expected_thread_two_frame_wait[3].state = 0;
    expected_thread_two_frame_wait[3].timer = 0;
    for (i = 0; i < 4; i++)
        c_test_same_words(slots[i], &expected_thread_two_frame_wait[i], sizeof(expected_thread_two_frame_wait[i]));
#ifndef MMX4_PC
    EnterCriticalSection();
    assert(CloseTh(slots[3]->handle) != 0);
    ExitCriticalSection();
#endif
    for (i = 0; i < 3; i++)
        if (!(saved_thread_two_frame_wait[i].state & 0x40))
            func_80012910(i);
    *slots[3] = saved_thread_two_frame_wait[3];
    D_801F8300 = current;
    for (i = 0; i < 4; i++)
        c_test_same_words(slots[i], &saved_thread_two_frame_wait[i], sizeof(saved_thread_two_frame_wait[i]));
    for (i = 0; i < 16; i++)
        assert(worker_stack_thread_two_frame_wait[i] == 0x13579BDF && worker_stack_thread_two_frame_wait[240 + i] == 0x13579BDF);
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "real_input_decoder_secondary_disconnect_digital_opposite_axes_and_pressed_edges", NULL, NULL, 1, packets },
    { "real_new_game_menu_worker_starts_engine_slot1_then_exits", NULL, NULL, 1, handoff },
    { "actual_game_loop_start_select_119_frame_hold_then_release_resets_countdown", NULL, NULL, 1, hold },
    { "real_slot3_worker_waits_two_scheduler_frames_then_resumes_and_closes", NULL, NULL, 1, wait_two },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 1 + 1 + 1;
