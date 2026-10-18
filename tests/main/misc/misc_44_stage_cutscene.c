#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_44_stage_cutscene.h"
#include "main/55C4.h"

static u32 cut_pages[0x100];
static s32 cut_frames[0x100];
static u8 cut_record[8];
#define sm state_room.misc
#define SCENE(st, step) (state_reset(step, 0, 0), sm.state = st, sm.backref = (void*)cut_record, sm.x_pos.i.hi = 0x100, g_Player.bg_offset = 0, g_Player.x_pos.i.hi = 0x80)
#define SCENE_SEEN() (sm.unk42 = 0, state_extra = sm.ext.misc_8.timer | (u32)(u8)g_Player.script_state << 8 | (u32)(u16)background_objects[0].unk26 << 16)
static void sc_init_x(void)
{
    SCENE(0, 0);
    sm.active = 1;
    engine_obj.cur_character = 0;
    stage_cutscene_update(&sm);
}
static void sc_init_seen(void)
{
    SCENE(0, 0);
    sm.active = 1;
    engine_obj.cur_character = 1;
    engine_obj.character_state.bytes[8] = 1;
    stage_cutscene_update(&sm);
}
static void sc_init_zero(void)
{
    SCENE(0, 0);
    engine_obj.cur_character = 1;
    engine_obj.character_state.bytes[8] = 0;
    D_801406A8 = cut_pages;
    TEST_MENU_FRAMES = (u8*)cut_frames;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_wait_player(void)
{
    SCENE(1, 0);
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_player_arrives(void)
{
    SCENE(1, 0);
    g_Player.x_pos.i.hi = 0xFE0;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_wait_scroll(void)
{
    SCENE(1, 1);
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_scrolled(void)
{
    SCENE(1, 1);
    background_objects[0].x_pos.i.hi = 0xFD0;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_look_turn(void)
{
    SCENE(1, 6);
    g_Player.x_pos.i.hi = 0x200;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_look_follow(void)
{
    SCENE(1, 6);
    sm.ext.misc_8.timer = 1;
    sm.animation_step.fields.event = 1;
    g_Player.x_pos.i.hi = 0x200;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_look_back(void)
{
    SCENE(1, 6);
    sm.ext.misc_8.timer = 1;
    sm.animation_step.fields.event = 1;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_look_hold(void)
{
    SCENE(1, 6);
    sm.ext.misc_8.timer = 1;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_look_return(void)
{
    SCENE(1, 6);
    sm.ext.misc_8.timer = 2;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_look_stay(void)
{
    SCENE(1, 6);
    sm.ext.misc_8.timer = 2;
    g_Player.x_pos.i.hi = 0x200;
    stage_cutscene_update(&sm);
    SCENE_SEEN();
}
static void sc_despawn(void)
{
    SCENE(2, 0);
    sm.active = 1;
    stage_cutscene_update(&sm);
}

static void (*const stage_cutscene_states_cases[])(void) = {
    sc_init_x,
    sc_init_seen,
    sc_init_zero,
    sc_wait_player,
    sc_player_arrives,
    sc_wait_scroll,
    sc_scrolled,
    sc_look_turn,
    sc_look_follow,
    sc_look_back,
    sc_look_hold,
    sc_look_return,
    sc_look_stay,
    sc_despawn,
};
static const u32 stage_cutscene_states_expected[] = { 0u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000000u, 0x1000000u, 0u, 0u, 0xA0000u, 0x200000u, 0x480000u, 0u, 0u, 1u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x101u, 0xFF000000u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 0xFD00101u, 0u, 0x101u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x201u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x40000u, 0x100u, 0u, 0x601u, 0xFF000000u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x601u, 0xFF000000u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0x601u, 0xFF000000u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x601u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 0x601u, 0xFF000000u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x601u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x40000u, 2u, 0u, 0u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_stage_cutscene_states(u32 row)
{
    return object_run(stage_cutscene_states_cases[row], row, &stage_cutscene_states_expected[row * 10]);
}

extern union AnimationStep* stage_cutscene_animations[3];
static const s8 delays[] = { 1, 2, 60 };
static const u8 dialogue_status[] = { 0x80, 1, 0 };
static const u16 script[] = { 0x0800, 0xFFFF };
static struct MiscObj pool_before[64];
static u32 dialogue_handoff(u32 row)
{
    struct MiscObj obj, expected;
    struct AbcObj dialogue_expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    struct BackgroundObj backgrounds_expected[3];
    struct MainBssState main_before = main_bss_state;
    u32 phase = row % 4, edge = row / 4 % 3, layer = row / 12, i;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.stage = 4;
    engine_obj.cur_character = 1;
    engine_obj.gameplay_locked = 1;
    g_Player.bg_offset = layer;
    g_Player.x_pos.i.hi = 100;
    g_Player.script_state = 1;
    g_Player.script_action = 0x15;
    g_Player.spike_immune = 1;
    for (i = 0; i < 3; i++) {
        background_objects[i].unk24 = 0x250 + i;
        background_objects[i].unk26 = 0x350 + i;
    }
    abc_object.unk0 = (u16*)script;
    abc_object.unk4 = script[0];
    abc_object.unkC = phase & 1 ? dialogue_status[edge] : 0x80;
    abc_object.unkA = 39;
    abc_object.unkD = 4;
    abc_object.unk10 = 0x1234;
    obj.active = 0x41;
    obj.id = 44;
    obj.state = 1;
    obj.unk5 = phase + 2;
    obj.bg_offset = layer;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.animation_table = (u32**)stage_cutscene_animations;
    set_animation(&obj, 0);
    assert(obj.animation_step.packed == 0x00010048);
    UNK_OBJECT(&obj)->ext.timer = delays[edge];
    expected = obj;
    dialogue_expected = abc_object;
    player_expected = g_Player;
    engine_expected = engine_obj;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    c_test_copy_words((u32*)pool_before, (u32*)misc_objects, sizeof(pool_before) / 4);
    expected.animation_step.fields.duration = 71;
    expected.on_screen = 1;
    if (!(phase & 1)) {
        UNK_OBJECT(&expected)->ext.timer--;
        if (edge == 0) {
            expected.unk5++;
            dialogue_expected.unk10 = phase == 0 ? 0x8029 : 0x802A;
        }
    } else if (edge == 2) {
        expected.unk5++;
        if (phase == 1)
            UNK_OBJECT(&expected)->ext.timer = 60;
        else {
            backgrounds_expected[layer].unk24 = 0x11B0;
            player_expected.script_state = 0;
            player_expected.spike_immune = 0;
            engine_expected.gameplay_locked = 0;
            engine_expected.character_state.bytes[8] = 1;
        }
    }
    stage_cutscene_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&abc_object, &dialogue_expected, sizeof(abc_object));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(misc_objects, pool_before, sizeof(pool_before));
    assert(script[0] == 0x0800 && script[1] == 0xFFFF);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "stage_cutscene_states", 0, 0, COUNT(stage_cutscene_states_cases), test_stage_cutscene_states },
    { "stage_dialogue_handoff", NULL, NULL, 36, dialogue_handoff },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stage_cutscene_states_cases) + 36;
