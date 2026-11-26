#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/effects/effect_44_stage_dialogue_trigger.h"
#include "main/55C4.h"

static struct PlayerObj talk_player;
static struct EngineObj talk_engine;
#define te state_room.effect
#define TALK(st, setup) (talk_player = g_Player, talk_engine = engine_obj, state_reset(0, 0, 0), memset(&engine_obj, 0, sizeof(engine_obj)), memset(&abc_object, 0, sizeof(abc_object)), te.active = 1, te.state = st, te.ext.unk_effect.unk14 = 5, setup, stage_dialogue_trigger_update(&te), te.x_pos.val = abc_object.unk10, state_extra = (u8)te.ext.unk_effect.unk14 | (u32)(u8)engine_obj.character_state.bytes[9] << 8 | (u32)(u8)g_Player.script_state << 16 | (u32)(u8)g_Player.script_action << 24, g_Player = talk_player, engine_obj = talk_engine)
static void talk_already_done(void) { TALK(0, engine_obj.character_state.bytes[9] = 1); }
static void talk_locked(void) { TALK(0, engine_obj.gameplay_locked = 1); }
static void talk_starts(void) { TALK(0, 0); }
static void talk_waits(void) { TALK(1, 0); }
static void talk_x(void) { TALK(1, (te.ext.unk_effect.unk14 = 1, abc_object.unkC = 0x80, engine_obj.cur_character = CHARACTER_X)); }
static void talk_zero(void) { TALK(1, (te.ext.unk_effect.unk14 = 1, abc_object.unkC = 0x80, engine_obj.cur_character = CHARACTER_X + 1)); }
static void talk_box_open(void) { TALK(2, abc_object.unkC = 1); }
static void talk_box_closed(void) { TALK(2, 0); }
static void (*const talk_cases[])(void) = {
    talk_already_done,
    talk_locked,
    talk_starts,
    talk_waits,
    talk_x,
    talk_zero,
    talk_box_open,
    talk_box_closed,
};
static const u32 talk_expected[] = {
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x105u, 0x0u,
    0x0u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x5u, 0x0u,
    0x1u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x14010030u, 0x0u,
    0x1u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x4u, 0x0u,
    0x2u, 0x1u, 0xFFFF8034u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x100u, 0x0u,
    0x2u, 0x1u, 0xFFFF802Fu, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x100u, 0x0u,
    0x2u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x5u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x5u, 0x0u,
};
static u32 test_talk(u32 row)
{
    return object_run(talk_cases[row], row, &talk_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "stage_dialogue_trigger_states", 0, 0, COUNT(talk_cases), test_talk },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(talk_cases);
