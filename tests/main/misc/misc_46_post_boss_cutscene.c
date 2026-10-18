#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_46_post_boss_cutscene.h"
void post_boss_cutscene_init(struct MiscObj*);

static s32 cutscene_frames[0x50];
static u32 cutscene_pages[3];
#define sm state_room.misc
#define CUT(step, wait) (state_reset(step, 0, 0), sm.state = 1, state_room.unk.ext.timer = wait)
#define CUT_TIMER() (state_extra = (u16)state_room.unk.ext.timer | (u32)(u8)engine_obj.unkF << 16 | (u32)(u8)state_room.unk.unk4B << 24)
static void pc_init(void)
{
    state_reset(0, 0, 0);
    TEST_MENU_FRAMES = (u8*)cutscene_frames;
    D_801406A8 = cutscene_pages;
    g_Player.x_pos.i.hi = 0x100;
    post_boss_cutscene_init(&sm);
    sm.unk42 = 0;
    state_extra = visual_objects[0].active | visual_objects[1].active << 8 | visual_objects[2].active << 16;
}
static void pc_wait_scroll(void)
{
    CUT(0, 0);
    g_Player.x_pos.i.hi = 0x30;
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_wait_scroll_moving(void)
{
    CUT(0, 0);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_arrive(void)
{
    CUT(1, 1);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_arrive_wait(void)
{
    CUT(1, 2);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_fly_in(void)
{
    CUT(2, 0);
    sm.x_pos.i.hi = 0x100;
    post_boss_cutscene_update(&sm);
}
static void pc_fly_in_far(void)
{
    CUT(2, 0);
    sm.x_pos.i.hi = 0x200;
    sm.x_vel.val = -0x40000;
    post_boss_cutscene_update(&sm);
}
static void pc_stop(void)
{
    CUT(3, 0);
    sm.x_vel.val = 0x10000;
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_brake(void)
{
    CUT(3, 0);
    sm.x_vel.val = -0x20000;
    sm.unk28 = 0x3000;
    post_boss_cutscene_update(&sm);
}
static void pc_first_line_x(void)
{
    CUT(4, 1);
    abc_object.unkC = 0x80;
    post_boss_cutscene_update(&sm);
}
static void pc_first_line_zero(void)
{
    CUT(4, 1);
    abc_object.unkC = 0x80;
    engine_obj.cur_character = 1;
    post_boss_cutscene_update(&sm);
}
static void pc_first_line_wait(void)
{
    CUT(4, 2);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_wait_first(void)
{
    CUT(5, 0);
    abc_object.unkC = 0;
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_wait_first_talking(void)
{
    CUT(5, 0);
    abc_object.unkC = 0x80;
    post_boss_cutscene_update(&sm);
}
static void pc_shake_start(void)
{
    CUT(6, 1);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_shake_start_wait(void)
{
    CUT(6, 2);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_shake_odd(void)
{
    CUT(7, 2);
    sm.unk28 = 0x10000;
    post_boss_cutscene_update(&sm);
}
static void pc_shake_even(void)
{
    CUT(7, 3);
    sm.unk28 = 0x10000;
    post_boss_cutscene_update(&sm);
}
static void pc_shake_done(void)
{
    CUT(7, 1);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_second_line_x(void)
{
    CUT(8, 1);
    abc_object.unkC = 0x80;
    post_boss_cutscene_update(&sm);
}
static void pc_second_line_zero(void)
{
    CUT(8, 1);
    abc_object.unkC = 0x80;
    engine_obj.cur_character = 1;
    post_boss_cutscene_update(&sm);
}
static void pc_second_line_wait(void)
{
    CUT(8, 2);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_wait_second(void)
{
    CUT(9, 0);
    abc_object.unkC = 0;
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_wait_second_talking(void)
{
    CUT(9, 0);
    abc_object.unkC = 0x80;
    post_boss_cutscene_update(&sm);
}
static void pc_finish(void)
{
    CUT(10, 1);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_finish_wait(void)
{
    CUT(10, 2);
    post_boss_cutscene_update(&sm);
    CUT_TIMER();
}
static void pc_despawn(void)
{
    state_reset(0, 0, 0);
    sm.state = 2;
    sm.active = 1;
    post_boss_cutscene_update(&sm);
}

static void (*const post_boss_cutscene_states_cases[])(void) = {
    pc_wait_scroll,
    pc_wait_scroll_moving,
    pc_arrive,
    pc_arrive_wait,
    pc_fly_in,
    pc_fly_in_far,
    pc_stop,
    pc_brake,
    pc_first_line_x,
    pc_first_line_zero,
    pc_first_line_wait,
    pc_wait_first,
    pc_wait_first_talking,
    pc_shake_start,
    pc_shake_start_wait,
    pc_shake_odd,
    pc_shake_even,
    pc_shake_done,
    pc_second_line_x,
    pc_second_line_zero,
    pc_second_line_wait,
    pc_wait_second,
    pc_wait_second_talking,
    pc_finish,
    pc_finish_wait,
    pc_despawn,
    pc_init,
};
static const u32 post_boss_cutscene_states_expected[] = { 0x101u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x3Cu, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x201u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x1000000u, 0u, 0x101u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x301u, 0u, 0x1000000u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x201u, 0u, 0x1FC0000u, 0u, 0xFFFC0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x401u, 0xFF000000u, 0x10000u, 0u, 0x10000u, 0u, 0u, 0x50000u, 0xFF00001Eu, 0u, 0x301u, 0u, 0xFFFE0000u, 0u, 0xFFFDD000u, 0u, 0x3000u, 0x50000u, 0u, 0u, 0x501u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x501u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x401u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x601u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x1Eu, 0u, 0x501u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x701u, 0xFF000000u, 0u, 0u, 0u, 0u, 0x10000u, 0x50000u, 0x20u, 0u, 0x601u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0x701u, 0u, 0x10000u, 0u, 0x10000u, 0u, 0x10000u, 0x50000u, 0u, 0u, 0x701u, 0u, 0xFFFF0000u, 0u, 0x10000u, 0u, 0x10000u, 0x50000u, 0u, 0u, 0x801u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x3Cu, 0u, 0x901u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x901u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x801u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0xA01u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x3Cu, 0u, 0x901u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xA02u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x10000u, 0u, 0xA01u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF000000u, 0x2700000u, 0xFFF80000u, 0xFFFBE000u, 0u, 0xFFFFD000u, 0x10000u, 0u, 0u };

static u32 test_post_boss_cutscene_states(u32 row)
{
    return object_run(post_boss_cutscene_states_cases[row], row, &post_boss_cutscene_states_expected[row * 10]);
}

extern union AnimationStep* D_8010F19C[2];
static const u32 frames[4] = { 8, 12, 0x12345678, 0x23456789 };
static struct VisualObj pool_expected[32];
static u32 images(u32 row)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 slots = row % 4, layer = row / 4, i;
    engine_obj.stage = 0;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    g_Player.bg_offset = layer;
    player_before = g_Player;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i >= 32 - slots ? 0 : 1;
    memcpy(pool_expected, visual_objects, sizeof(pool_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 46;
    obj.state = 1;
    obj.bg_offset = layer;
    obj.unk16 = 6;
    obj.unk40 = 0xB3;
    obj.unk42 = 0x780A;
    obj.unk3C = (u8*)frames;
    obj.animation_table = (u32**)D_8010F19C;
    obj.x_pos.val = 528 * 65536 + 0x1234;
    obj.y_pos.val = 112 * 65536 + 0x5678;
    expected = obj;
    for (i = 0; i < slots; i++) {
        struct VisualObj* v = &pool_expected[31 - i];
        v->active = 0x41;
        v->id = 5;
        v->unk2 = i;
        v->bg_offset = layer;
        v->unk40 = obj.unk40;
        v->unk3C = obj.unk3C;
        v->animation_table = obj.animation_table;
        v->unk42 = obj.unk42;
        v->unk16 = 6;
        v->unk5C.owner = PLAYER_OBJECT(&obj);
        v->unk50 = i ? PLAYER_OBJECT(&visual_objects[32 - i]) : PLAYER_OBJECT(&obj);
    }
    post_boss_cutscene_spawn_afterimages(UNK_OBJECT(&obj));
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(visual_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(frames[0] == 8 && frames[1] == 12 && frames[2] == 0x12345678 && frames[3] == 0x23456789);
    return 1;
}

void post_boss_cutscene_update(struct MiscObj*);
void object_afterimage_update(struct VisualObj*);
static u32 metadata[8], menu[64];
static struct VisualObj expected[32];
union OwnerStorage {
    struct MiscObj misc;
    struct PlayerObj player;
};
static u32 partial_lifetime(u32 row)
{
    union OwnerStorage owner_storage, owner_before;
    struct EngineObj engine_before;
    struct PlayerObj player_before, entity_before;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    u16 rng;
    u32 i;
    (void)row;
    c_test_zero_words((u32*)&owner_storage, sizeof(owner_storage) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = (i + 1) * 128;
    for (i = 0; i < COUNT(menu); i++)
        menu[i] = i < 8 ? 64 : 0;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)menu;
    engine_obj.stage = 0;
    engine_obj.substage = 1;
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = 160;
    g_Player.y_pos.i.hi = 120;
    background_objects[0].x_pos.i.hi = 112;
    for (i = 0; i < 31; i++)
        visual_objects[i].active = 1;
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    owner_storage.misc.active = 0x41;
    owner_storage.misc.id = 46;
    post_boss_cutscene_update(&owner_storage.misc);
    assert(owner_storage.misc.state == 1 && owner_storage.misc.unk5 == 0 && visual_objects[31].active == 0x41 && visual_objects[31].id == 5 && visual_objects[31].unk2 == 0 && visual_objects[31].unk5C.owner == PLAYER_OBJECT(&owner_storage.misc));
    post_boss_cutscene_update(&owner_storage.misc);
    assert(owner_storage.misc.unk5 == 1);
    for (i = 0; i < 60; i++) {
        post_boss_cutscene_update(&owner_storage.misc);
        object_afterimage_update(&visual_objects[31]);
    }
    assert(owner_storage.misc.unk5 == 2 && owner_storage.player.pad4B[0] == 1 && visual_objects[31].state == 1);
    for (i = 0; i < 100 && !(visual_objects[31].unk5 == 2 && visual_objects[31].unk58 == 0); i++) {
        post_boss_cutscene_update(&owner_storage.misc);
        object_afterimage_update(&visual_objects[31]);
    }
    assert(i < 100 && owner_storage.misc.unk5 == 4 && owner_storage.player.pad4B[0] == -1 && visual_objects[31].state == 1);
    post_boss_cutscene_update(&owner_storage.misc);
    assert(owner_storage.misc.unk5 == 4);
    c_test_copy_words((u32*)expected, (u32*)visual_objects, sizeof(expected) / 4);
    owner_before = owner_storage;
    engine_before = engine_obj;
    player_before = g_Player;
    entity_before = g_Entity;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    expected[31].animation_step.fields.frame_index = owner_storage.misc.animation_step.fields.frame_index;
    expected[31].unk15 = owner_storage.misc.unk15;
    expected[31].unk18 = expected[31].x_pos;
    expected[31].unk1C = expected[31].y_pos;
    expected[31].on_screen = 0;
    expected[31].state = 0;
    object_afterimage_update(&visual_objects[31]);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)expected, sizeof(expected) / 4) == 0 && c_test_word_difference((u32*)&owner_storage, (u32*)&owner_before, sizeof(owner_storage) / 4) == 0);
    assert(c_test_word_difference((u32*)&engine_obj, (u32*)&engine_before, sizeof(engine_before) / 4) == 0 && c_test_word_difference((u32*)&g_Player, (u32*)&player_before, sizeof(player_before) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity_before, sizeof(entity_before) / 4) == 0);
    assert(c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && D_8013E198[2] == -1 && D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)menu);
    for (i = 0; i < COUNT(metadata); i++)
        assert(metadata[i] == (i + 1) * 128);
    for (i = 0; i < COUNT(menu); i++)
        assert(menu[i] == (i < 8 ? 64u : 0));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "post_boss_cutscene_states", 0, 0, COUNT(post_boss_cutscene_states_cases), test_post_boss_cutscene_states },
    { "real_cutscene_reverse_allocator_zero_through_three_afterimages_and_links", NULL, NULL, 12, images },
    { "actual_post_boss_single_afterimage_reaches_nonfinal_catch_up", NULL, NULL, 1, partial_lifetime },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(post_boss_cutscene_states_cases) + 12 + 1;
