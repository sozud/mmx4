// saturn-capability: vblank
// saturn-step-budget: 2000000000
#include "test_runtime.h"
#include "support/saturn_disc.h"
#include "saturn/player_resources.h"
#include "saturn/menu.h"
#include "main/player_special.h"

void func_8001FC20(struct EngineObj* arg0);
void engine_state_6(struct EngineObj* arg0);
s32 saturn_archive_load_blocking(const char* path);

static const struct {
    u16 frames, pad;
} play_script[] = {
    { 500, 0 },
    { 40, SATURN_PAD_RIGHT },
    { 30, 0 },
    { 12, SATURN_PAD_B },
    { 90, 0 },
};
static u8 actions_seen[0x40];
static s32 play_start_x;
static u8 play_started;
static void load_thread(void)
{
    saturn_archive_load_blocking("ASCII.ARC");
    saturn_archive_load_blocking("PL01.ARC");
    engine_state_4(&engine_obj);
}
static void play_thread(void)
{
    u32 step, frame;
    func_8001FC20(&engine_obj);
    play_started = engine_obj.state == 6 && engine_obj.gameplay_locked == 1 && g_Player.unk5 == PLAYER_BEAM_IN;
    play_start_x = g_Player.x_pos.i.hi;
    for (step = 0; step < COUNT(play_script); step++) {
        for (frame = 0; frame < play_script[step].frames; frame++) {
            saturn_pad_previous = saturn_pad_held;
            saturn_pad_held = play_script[step].pad;
            saturn_pad_pressed = saturn_pad_held & ~saturn_pad_previous;
            engine_state_6(&engine_obj);
            actions_seen[g_Player.unk5 & 0x3F] = 1;
            saturn_thread_sleep(1);
        }
    }
}
static u32 stage_play_body(u32 row)
{
    test_vblank_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 4;
    engine_obj.stage = 3;
    engine_obj.cur_character = 1;
    engine_obj.player_lives = 2;
    engine_obj.max_hp = 0x20;
    test_vblank_run_thread(load_thread, NULL, 1);
    assert(engine_obj.state == 5);
    engine_obj.unk42 = 1;
    memset(actions_seen, 0, sizeof(actions_seen));
    saturn_pad_held = 0;
    test_vblank_run_thread(play_thread, NULL, 0);
    saturn_pad_held = saturn_pad_pressed = saturn_pad_previous = 0;
    assert(play_started && g_Player.unk2 == 1);
    assert(engine_obj.gameplay_locked == 0);
    assert(actions_seen[PLAYER_BEAM_IN] && actions_seen[PLAYER_IDLE]);
    assert(actions_seen[PLAYER_WALK_START] && actions_seen[PLAYER_WALK] && actions_seen[PLAYER_SETTLE]);
    assert(actions_seen[PLAYER_JUMP] && actions_seen[PLAYER_FALL] && actions_seen[PLAYER_LAND]);
    assert(g_Player.x_pos.i.hi > play_start_x);
    return g_Player.x_pos.i.hi - play_start_x;
}
static u32 stage_play(u32 row) { return test_disc_on_fixture_stack(stage_play_body, row); }

const struct CTestGroup c_test_groups[] = {
    { "saturn_stage_play", 0, 0, 1, stage_play },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
