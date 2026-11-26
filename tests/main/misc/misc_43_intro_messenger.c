#include "test_runtime.h"
#include "main/misc/misc_43_intro_messenger.h"
#include "main/55C4.h"

static u32 messenger_case(u32 delay, u32 zero, u32 observation)
{
    struct MiscObj obj, before;
    struct AbcObj dialogue_before;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    u32 i, message;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 43;
    obj.state = 1;
    obj.unk5 = delay ? 6 : 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.unk.unk54 = 1;
    obj.animation_table = (u32**)intro_messenger_animations;
    set_animation_frame(&obj, 1, 3);
    abc_object.unkC = 0x80;
    abc_object.unkD = 7;
    abc_object.unkA = 0x25;
    abc_object.unk10 = 0x1234;
    engine_obj.cur_character = zero ? 1 : 0;
    engine_obj.stage = 2;
    engine_obj.enable_boss = 1;
    engine_obj.unk1F = 0x27;
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    before = obj;
    dialogue_before = abc_object;
    engine_before = engine_obj;
    player_before = g_Player;
    if (delay) {
        intro_messenger_delay(&obj);
        before.ext.unk.unk54 = 0;
        before.unk5 = 7;
        message = zero ? 0x28 : 0x2F;
    } else {
        intro_messenger_land(&obj);
        before.unk5 = 3;
        message = zero ? 0x27 : 0x2E;
    }
    dialogue_before.unk10 = message | 0x8000;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&abc_object, &dialogue_before, sizeof(abc_object));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(D_801397BC == NULL && D_801397C0 == NULL && D_801397C4 == NULL && D_801397C8 == NULL);
    assert(D_801397CC == NULL && D_801397D0 == NULL && D_801397D4 == NULL);
    return observation == 0 ? (u16)abc_object.unk10 | ((u32)(u8)obj.unk5 << 16) : C_TEST_STEP(obj.animation_step.packed);
}
static const u32 intro_messenger_dialogue_context_cases_expected[] = { 0x3802Eu, 0x1000101u, 0x38027u, 0x1000101u, 0x7802Fu, 0x1000101u, 0x78028u, 0x1000101u };
static u32 intro_messenger_dialogue_context_cases_row(u32 row)
{
    return messenger_case(row / 4, row / 2 % 2, row % 2);
}


#include "support/state_cases.h"
#include "main/player_common.h"
#define sm state_room.misc
#define MSG(step, setup) (state_reset(step, 0, 0), memset(&abc_object, 0, sizeof(abc_object)), memset(&engine_obj, 0, sizeof(engine_obj)), memset(&g_Player, 0, sizeof(g_Player)), abc_object.unkC = 0x80, background_objects[0].x_pos.i.hi = 0x12F0, background_objects[0].y_pos.i.hi = 0x100, sm.active = 1, sm.state = 1, sm.x_pos.i.hi = 0x1360, sm.y_pos.i.hi = 0x140, sm.y_vel.val = 0x10000, sm.unk2C = 0x2000, sm.ext.unk.unk54 = 5, setup, intro_messenger_update(&sm), state_extra = sm.unk17 | (u32)(u8)g_Player.script_action << 8 | (u32)(u8)engine_obj.unkF << 16 | (u32)(u8)sm.ext.unk.unk54 << 24)
static void im_scroll_arrived(void) { MSG(0, 0); }
static void im_scroll_moving(void) { MSG(0, background_objects[0].x_pos.i.hi = 0x12EF); }
static void im_script_done(void) { MSG(1, g_Player.script_state = -1); }
static void im_script_running(void) { MSG(1, g_Player.script_state = 1); }
static void im_landing(void) { MSG(2, 0); }
static void im_dialogue_done(void) { MSG(3, abc_object.unkC = 0); }
static void im_dialogue_open(void) { MSG(3, 0); }
static void im_lift_off(void) { MSG(4, sm.animation_step.fields.event = 1); }
static void im_crouch(void) { MSG(4, 0); }
static void im_flown_off(void) { MSG(5, sm.y_pos.i.hi = 0xD0); }
static void im_climbing(void) { MSG(5, 0); }
static void im_delay(void) { MSG(6, 0); }
static void im_finish(void) { MSG(7, abc_object.unkC = 0); }
static void im_finish_wait(void) { MSG(7, 0); }
static void (*const im_cases[])(void) = {
    im_scroll_arrived,
    im_scroll_moving,
    im_script_done,
    im_script_running,
    im_landing,
    im_dialogue_done,
    im_dialogue_open,
    im_lift_off,
    im_crouch,
    im_flown_off,
    im_climbing,
    im_delay,
    im_finish,
    im_finish_wait,
};
static const u32 im_expected[] = {
    0x101u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x5001500u, 0u,
    0x1u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x5000000u, 0u,
    0x201u, 0xFF000001u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x5000001u, 0u,
    0x101u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x5000000u, 0u,
    0x201u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x40000u, 0x5000000u, 0u,
    0x401u, 0xFF000001u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x5000002u, 0u,
    0x301u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x5000000u, 0u,
    0x501u, 0x1u, 0x13600000u, 0x13F0000u, 0u, 0x10000u, 0x200000u, 0x40000u, 0x5000000u, 0u,
    0x401u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x40000u, 0x5000000u, 0u,
    0x601u, 0x1u, 0x13600000u, 0xCF0000u, 0u, 0xE000u, 0x200000u, 0x50000u, 0x3C000000u, 0u,
    0x501u, 0x1u, 0x13600000u, 0x13F0000u, 0u, 0xE000u, 0x200000u, 0x50000u, 0x5000000u, 0u,
    0x601u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x4000000u, 0u,
    0x702u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x5010000u, 0u,
    0x701u, 0x1u, 0x13600000u, 0x1400000u, 0u, 0x10000u, 0x200000u, 0x50000u, 0x5000000u, 0u,
};
static u32 test_im(u32 row)
{
    return object_run(im_cases[row], row, &im_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "intro_messenger_steps", 0, 0, COUNT(im_cases), test_im },
    { "intro_messenger_dialogue_context", NULL, intro_messenger_dialogue_context_cases_expected, COUNT(intro_messenger_dialogue_context_cases_expected), intro_messenger_dialogue_context_cases_row },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(intro_messenger_dialogue_context_cases_expected) + COUNT(im_cases);
