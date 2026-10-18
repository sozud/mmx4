#include "test_runtime.h"
#include "main/shots/shot_23_web_thread.h"
#include "main/55C4.h"
#include "main/mains/main_43_web_spider.h"

static u32 pulse_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct VisualObj pool_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
        visual_objects[i].state = 0x28;
    }
    if (mode == 1)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 23;
    obj.state = 1;
    obj.unk2 = 2;
    obj.unk5 = 1;
    obj.unk6 = mode >= 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk16 = 2;
    obj.unk15 = 0x40;
    obj.unk40 = 0x540;
    obj.unk42 = 0x9234;
    obj.animation_table = (const u8* const*)web_spider_animations;
    set_animation(&obj, 18);
    if (mode == 2) {
        obj.animation_cursor = (void*)(web_spider_animations[18] + 15);
        obj.animation_step = *(union AnimationStep*)obj.animation_cursor;
        assert(obj.animation_step.packed == 0x63000001);
    }
    expected = obj;
    memcpy(pool_before, visual_objects, sizeof(pool_before));
    if (mode < 2) {
        expected.unk6 = 1;
        if (mode == 1) {
            struct VisualObj* v = &pool_before[31];
            v->active = 0x41;
            v->id = 20;
            v->unk2 = 0;
            v->x_pos = obj.x_pos;
            v->y_pos = obj.y_pos;
            v->animation_table = obj.animation_table;
            v->unk40 = obj.unk40;
            v->unk3C = obj.unk3C;
            v->unk42 = 0x1234;
            v->unk16 = 2;
            v->unk15 = 0x40;
            v->unk50 = PLAYER_OBJECT(&obj);
        }
    } else if (mode == 2) {
        expected.unk5 = expected.unk6 = expected.unk2 = 0;
        expected.unk17 = 19;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (void*)(web_spider_animations[19] + 1);
        expected.animation_step = web_spider_animations[19][1];
    } else {
        expected.animation_cursor = (void*)(web_spider_animations[18] + 1);
        expected.animation_step = web_spider_animations[18][1];
    }
    web_thread_pulse(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.unk17 << 16) | ((u32)visual_objects[31].active << 24);
}
static const u32 web_thread_pulse_visual_pool_cases_expected[] = { 0x1120101u, 0x41120101u, 0x1130000u, 0x1120101u };

static const u32 inputs_0[2][2] = {
    { -1, 0 },
    { 0, 255 },
};
struct web_thread_snap_case {
    u32 expected[3];
};
static const struct web_thread_snap_case web_thread_snap_cases[] = {
    { { 0u, 0u, 0u } },
    { { 0u, 2u, 0u } },
};
static u32 test_web_thread_snap(u32 row)
{
    const struct web_thread_snap_case* c = &web_thread_snap_cases[row];
    u32 observed_values[3];
    struct ShotObj obj;
    struct WeaponObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    obj.animation_step.fields.relative_step = inputs_0[row][0];
    child_0_present = inputs_0[row][1];
    obj.unk7C = child_0_present ? &child_0 : NULL;
    web_thread_snap(&obj);
    observed_values[0] = (u32)child_0.unk80.word;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

void web_thread_main(struct ShotObj*);
extern u8 web_thread_hit_box[4], web_thread_collision[32][4];
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
static u32 owner_handoffs(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 gate = row % 4, dead = row / 4 % 2, flash = row / 8 % 2, hit = row / 16 % 2, facing = row / 32, i;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_before = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 43;
    owner.state = dead ? 2 : 1;
    owner.unk5 = 6;
    owner.unk6 = 4;
    owner.x_pos.val = 160 * 65536 + 0x1234;
    owner.y_pos.val = 170 * 65536 + 0x5678;
    owner.ext.main_43.flash_timer = flash;
    owner.ext.main_43.hurt_collision = gate & 1;
    owner.ext.main_43.big_web_done = gate >> 1;
    owner_expected = owner;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 23;
    obj.state = 1;
    obj.on_screen = 7;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk42 = 0x1234;
    obj.unk5C = 3;
    obj.unk60 = 3;
    obj.timer = -50;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.unk84.value = 16 * 65536;
    obj.x_pos.val = 0x12345;
    obj.y_pos.val = 0x23456;
    obj.unk50.data = obj.unk54 = web_thread_hit_box;
    obj.unk58.data = web_thread_collision[0];
    obj.animation_table = (u32**)web_spider_animations;
    set_animation(&obj, 19);
    assert(obj.animation_step.packed == 0x64010001);
    if (hit) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = 8;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].x_pos.val = owner.x_pos.val + 16 * 65536;
        weapon_objects[0].y_pos.val = owner.y_pos.val - 50 * 65536;
        weapon_objects[0].unk50 = web_thread_hit_box;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.x_pos.val = owner.x_pos.val + 16 * 65536;
    expected.y_pos.val = owner.y_pos.val - 50 * 65536;
    if (dead) {
        expected.active = expected.id = expected.unk2 = expected.on_screen = expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
        expected.unk61 = flash;
    } else {
        expected.animation_cursor = (u32*)web_spider_animations[19] + 1;
        expected.animation_step.packed = 0x65010001;
        expected.on_screen = 1;
        if (!gate && hit && !flash) {
            expected.unk42 |= 0x8000;
            weapons_expected[0].unk98 = 1;
            ((s16*)&weapons_expected[0].unk80)[0] = facing ? 177 : 175;
            ((s16*)&weapons_expected[0].unk80)[1] = 71;
            if (!flash) {
                expected.unk5 = 1;
                expected.unk61 = 30;
                expected.unk17 = 20;
                expected.previous_animation_index = 0xFF;
                expected.animation_cursor = (u32*)web_spider_animations[20];
                expected.animation_step.packed = 0x66010001;
                owner_expected.unk5 = 1;
                owner_expected.unk6 = 0;
            }
        }
    }
    D_8013E198[5] = -1;
    cur_random = 0x1234;
    web_thread_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(weapon_objects, weapons_expected, sizeof(weapons_expected));
    c_test_same_words(visual_objects, visuals_before, sizeof(visuals_before));
    assert(cur_random == 0x1234);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "web_thread_pulse_visual_pool", NULL, web_thread_pulse_visual_pool_cases_expected, COUNT(web_thread_pulse_visual_pool_cases_expected), pulse_case },
    { "web_thread_snap", 0, 0, 2, test_web_thread_snap },
    { "owner_death_web_gates_and_real_weapon_snap", NULL, NULL, 64, owner_handoffs },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(web_thread_pulse_visual_pool_cases_expected) + 2 + 64;
