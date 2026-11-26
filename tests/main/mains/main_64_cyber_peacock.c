#include "test_runtime.h"
#include "support/platform_fixture.h"
#ifndef VERSION_DEMO
#include "main/mains/main_64_cyber_peacock.h"
#include "support/state_cases.h"
#include "main/55C4.h"
u8 cyber_peacock_choose_attack(struct MainObj*);

static u32 peacock_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct EffectObj child, child_before, pool_before[32];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    static u32 resources[1];
    u32 i;
    s32 archive[128];
    memset(&obj, 0, sizeof(obj));
    memset(&child, 0, sizeof(child));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(archive, 0, sizeof(archive));
    archive[4] = 64;
    resources[0] = 0x10000;
    test_stage_graphics(resources);
    TEST_MENU_FRAMES = (u8*)archive;
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 0x27;
    }
    obj.active = 0x41;
    obj.id = 64;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk7 = 0x25;
    obj.unk6 = mode == 6 ? -1 : mode == 7 ? 3
        : mode < 2                        ? 0
        : mode < 4                        ? 1
                                          : 2;
    obj.unk7C = mode == 4 ? 1 : 2;
    obj.ext.main_64.object = &child;
    child.id = 0x18;
    obj.hp = 0x27;
    obj.contact_damage = 0x26;
    obj.invincibility_timer = 0x25;
    obj.bg_offset = 0;
    obj.unk40 = 0x7777;
    obj.unk42 = 0x6666;
    obj.unk16 = VISUAL_SATURN_LAYER(0x24);
    obj.unk62 = 0x23;
    obj.unk63 = 0x22;
    g_Player.capsule_state = mode == 0 ? 1 : 0;
    g_Player.bg_offset = 2;
    g_Player.script_state = -1;
    g_Player.script_action = 0x25;
    g_Player.script_facing = 0x26;
    engine_obj.stage = mode == 3 ? 12 : 6;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 7;
    before = obj;
    child_before = child;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(pool_before, effect_objects, sizeof(pool_before));
    cyber_peacock_intro_wait_player(&obj);
    if (mode == 1) {
        before.unk6 = 1;
        before.unk7 = 0;
        player_before.script_state = 1;
        player_before.script_action = 0x14;
        player_before.script_facing = PLAYER_FACING_RIGHT;
        SPIKE_IMMUNE_SET(player_before, 1);
        engine_before.gameplay_locked = 1;
    } else if (mode == 2 || mode == 3) {
        before.unk6 = 2;
        before.bg_offset = 2;
        before.unk40 = OBJECT_STAGE_TEXTURE(0) + OBJECT_TEXTURE_OFFSET(mode == 3 ? 0x160 : 0xB0);
        if (mode == 3) {
            before.sprite_frames = (u8*)archive + 64;
            before.unk42 = OBJECT_CLUT(0x7888);
        }
        before.animation_table = (const u8* const*)cyber_peacock_animations;
        before.unk16 = VISUAL_SATURN_LAYER(4);
        before.hp = 0;
        before.contact_damage = 5;
        before.invincibility_timer = -0x80;
        before.unk62 = 0;
        before.unk63 = 2;
        before.unk7C = 0x20;
        engine_before.enable_boss = 0;
        engine_before.unk25 = 0;
        engine_before.boss_ptr = &obj;
    } else if (mode == 4 || mode == 5) {
        before.unk7C = mode == 4 ? 0 : 1;
        if (mode == 4) {
            before.unk5 = 2;
            before.unk6 = 0;
            before.unk7 = 0;
        }
    }
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&child, &child_before, sizeof(child));
    c_test_same_words(effect_objects, pool_before, sizeof(pool_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(resources[0] == 0x10000);
    for (i = 0; i < 128; i++)
        assert(archive[i] == (i == 4 ? 64 : 0));
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u16)obj.unk7C << 16) : (u16)obj.unk40 | ((u32)(u16)obj.unk42 << 16);
}
static const u32 cyber_peacock_intro_context_cases_expected[] = { 0x20001u, 0x66667777u, 0x20101u, 0x66667777u, 0x200201u, 0, 0x200201u, 0, 0x2u, 0x66667777u, 0x10201u, 0x66667777u, 0x2FF01u, 0x66667777u, 0x20301u, 0x66667777u };
static u32 cyber_peacock_intro_context_cases_row(u32 row)
{
    u32 actual = peacock_case(row / 2, row % 2), expected = cyber_peacock_intro_context_cases_expected[row];
    if (row == 5)
        expected = (u16)(OBJECT_STAGE_TEXTURE(0) + OBJECT_TEXTURE_OFFSET(0xB0)) | 0x6666u << 16;
    if (row == 7)
        expected = (u16)(OBJECT_STAGE_TEXTURE(0) + OBJECT_TEXTURE_OFFSET(0x160)) | (u32)(u16)OBJECT_CLUT(0x7888) << 16;
    assert(actual == expected);
    return actual;
}

#include "support/pool_full.h"
static u32 pool_full_cyber_peacock_spawn_laser_target(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    cyber_peacock_spawn_laser_target(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_cyber_peacock_spawn_missile(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    cyber_peacock_spawn_missile(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_cyber_peacock_death_explode(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    cyber_peacock_death_explode(&pf_self);
    pf_expected.unk5 = 2;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_cyber_peacock_spawn_laser_target,
    pool_full_cyber_peacock_spawn_missile,
    pool_full_cyber_peacock_death_explode,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x2u };
#define CP(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x480, so.y_pos.i.hi = 0x660, so.ext.main_64.arena_x = 0x410, so.ext.main_64.arena_y = 0x600)
#define LASER(t) (CP(7, 0), so.unk7C = t, so.ext.main_64.force_laser = 1, func_8007CA68(&so), state_extra = (u16)so.ext.main_64.target_x | (u32)(u16)so.ext.main_64.target_y << 16)
static void cp_dash_start(void)
{
    CP(8, 0);
    func_8007D5D0(&so);
}
static void cp_dash_even(void)
{
    CP(8, 1);
    so.animation_step.fields.relative_step = 1;
    so.x_speed = 0x10000;
    so.ext.main_64.target_x = 0x480;
    main_bss_state.frame_counter = 0;
    func_8007D5D0(&so);
}
static void cp_dash_odd(void)
{
    CP(8, 1);
    so.animation_step.fields.relative_step = 1;
    so.x_speed = 0x10000;
    so.ext.main_64.target_x = 0x480;
    main_bss_state.frame_counter = 1;
    func_8007D5D0(&so);
}
static void cp_dash_end(void)
{
    CP(8, 1);
    func_8007D5D0(&so);
}
static void cp_dash_return(void)
{
    CP(8, 2);
    func_8007D5D0(&so);
}
static void cp_aim(void)
{
    g_Player.x_pos.i.hi = 0x440;
    LASER(0x15);
}
static void cp_laser_left(void)
{
    g_Player.x_pos.i.hi = 0x440;
    LASER(1);
}
static void cp_laser_right(void)
{
    g_Player.x_pos.i.hi = 0x500;
    LASER(1);
}
static void cp_low_health(void)
{
    CP(7, 0);
    so.hp = 8;
    cur_random = 0x1234;
    so.unk2 = cyber_peacock_choose_attack(&so);
}
static void cp_setup_stage(void)
{
    u8 stage = engine_obj.stage;
    CP(0, 0);
    engine_obj.stage = 6;
    func_8007C30C(&so);
    engine_obj.stage = stage;
}
static void cp_setup(void)
{
    u8 stage = engine_obj.stage;
    CP(0, 0);
    engine_obj.stage = 0;
    func_8007C30C(&so);
    engine_obj.stage = stage;
}

static void (*const cyber_peacock_states_cases[])(void) = {
    cp_dash_start,
    cp_dash_even,
    cp_dash_odd,
    cp_dash_end,
    cp_dash_return,
    cp_aim,
    cp_laser_left,
    cp_laser_right,
    cp_low_health,
    cp_setup_stage,
    cp_setup,
};
static const u32 cyber_peacock_states_expected[] = { 0x108u, 0u, 0x4800000u, 0u, 0u, 0x10000u, 0x20u, 0u, 0u, 0u, 0x108u, 0u, 0x47F0000u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x108u, 0u, 0x4810000u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x208u, 0x3Cu, 0x4800000u, 0u, 0u, 0u, 0x22u, 0u, 0u, 0u, 0x102u, 0u, 0x4800000u, 0x160000u, 0u, 0x10000u, 0x22u, 0u, 0u, 0u, 7u, 0x14u, 0x4800000u, 0u, 0u, 0u, 0u, 0u, 0xFFE80000u, 0u, 0x107u, 0u, 0x5200000u, 0u, 0u, 0u, 8u, 0u, 0x6700520u, 0u, 0x107u, 0u, 0x5200000u, 0u, 0u, 0u, 8u, 0u, 0x6700520u, 0u, 7u, 0u, 0x4800000u, 0u, 0u, 0u, 0u, 0x80000u, 0u, 0u, 1u, 0x80u, 0x4800000u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 1u, 0x80u, 0x4800000u, 0u, 0u, 0u, 0u, 3u, 0u, 0u };

static u32 test_cyber_peacock_states(u32 row)
{
    return state_run(cyber_peacock_states_cases[row], row, &cyber_peacock_states_expected[row * 10]);
}

extern void* cyber_peacock_animations[];
extern struct Unk_unk68 D_80107CFC[];
static const struct {
    u8 weapon, damage, lethal, flag;
} hits[] = {
    { 255, 0, 0, 0 },
    { 0, 1, 0, 1 },
    { 3, 4, 0, 0 },
    { 35, 4, 0, 0 },
    { 2, 0, 0, 0 },
    { 0, 1, 1, 1 },
};
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 hit_count_reactions(u32 row)
{
    struct MainObj obj, expected;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 hit = row % COUNT(hits), flash = row / COUNT(hits) % 3, count = row / COUNT(hits) / 3 % 2, facing = row / COUNT(hits) / 6, i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_expected = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    obj.active = 0x41;
    obj.id = 64;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 4;
    obj.unk7 = 9;
    obj.unk7C = 2;
    obj.on_screen = 7;
    obj.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
    obj.unk42 = 0x9234;
    obj.hp = hits[hit].lethal ? 1 : 48;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = 0x12345;
    obj.y_speed = -0x23456;
    obj.hurt_box = &cyber_peacock_hit_box;
    obj.attack_box = &cyber_peacock_hit_box;
    obj.collision_data = D_80107CFC;
    obj.ext.main_64.hit_count = count ? 7 : 6;
    obj.ext.main_64.flash_timer = flash;
    obj.ext.main_64.saved_health = obj.hp;
    obj.animation_table = (const u8* const*)cyber_peacock_animations;
    set_animation(&obj, 34);
    assert(obj.animation_step.packed == C_TEST_STEP(0x34000004));
    if (hits[hit].weapon != 255) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = hits[hit].weapon;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
        weapon_objects[0].unk50 = (const u8*)&cyber_peacock_hit_box;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk42 = 0x1234;
    expected.on_screen = 1;
    if (count) {
        expected.ext.main_64.hit_count = 0;
        expected.ext.main_64.shot_count = 0;
        expected.unk5 = 4;
        expected.unk6 = 1;
        expected.unk7 = 0;
        expected.ext.main_64.target_x = 160;
        expected.ext.main_64.target_y = 120;
        expected.x_speed = expected.y_speed = expected.gravity = 0;
        expected.x_accel = 65536;
        expected.hurt_box = expected.attack_box = NULL;
        expected.unk17 = 32;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)cyber_peacock_animations[32];
        expected.animation_step.packed = C_TEST_STEP(0x87010002);
    } else {
        expected.unk7C = 1;
        expected.animation_step.fields.duration = 3;
        if (hits[hit].weapon != 255) {
            expected.unk63 = hits[hit].weapon == 2 ? -1 : 0;
            ((s16*)&weapons_expected[0].unk80)[0] = facing ? 158 : 162;
            ((s16*)&weapons_expected[0].unk80)[1] = 125;
            weapons_expected[0].unk98 = hits[hit].flag;
            if (hits[hit].weapon == 35)
                player_expected.update_delay_request = 1;
            if (hits[hit].weapon != 2) {
                expected.hp = hits[hit].lethal ? 0 : 48 - hits[hit].damage;
                expected.unk42 |= 0x8000;
                if (!flash) {
                    if (hits[hit].lethal) {
                        expected.state = 2;
                        expected.unk5 = expected.unk6 = 0;
                        expected.unk42 &= 0x7FFF;
                        SPIKE_IMMUNE_SET(player_expected, 1);
                    } else {
                        expected.ext.main_64.flash_timer = 64;
                        expected.ext.main_64.saved_health = expected.hp;
                        if (hits[hit].weapon == 3 || hits[hit].weapon == 35) {
                            expected.unk5 = 5;
                            expected.unk6 = expected.unk7 = 0;
                        } else
                            expected.ext.main_64.hit_count++;
                    }
                }
            }
        }
    }
    if (flash) {
        expected.ext.main_64.flash_timer--;
        expected.hp = expected.ext.main_64.saved_health;
        if (flash == 2)
            expected.unk42 |= 0x8000;
        else
            expected.unk42 &= 0x7FFF;
    }
    D_8013E198[0] = D_8013E198[1] = D_8013E198[2] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &obj;
    func_8007D838(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = current;
    SAME(obj, expected);
    SAME(g_Player, player_expected);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    assert(cur_random == 0x1234);
    return 1;
}

void cyber_peacock_intro(struct MainObj*);
extern struct Unk_unk68 cyber_peacock_hit_box;

static struct MainObj po;
#define PO_IS(a, b) ((const void*)(a) == (const void*)(b))
static void po_reset(u8 unk5, u8 unk6)
{
    memset(&po, 0, sizeof(po));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(item_objects, 0, sizeof(item_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    D_80141F50[2] = state_sound_rows;
    engine_obj.stage = 6;
    cur_random = 0;
    po.active = 0x41;
    po.id = 64;
    po.state = 1;
    po.unk5 = unk5;
    po.unk6 = unk6;
    po.hp = 0x30;
    po.x_pos.i.hi = 0x480;
    po.y_pos.i.hi = 0x660;
    po.ext.main_64.arena_x = 0x410;
    po.ext.main_64.arena_y = 0x600;
    po.animation_table = (const u8* const*)cyber_peacock_animations;
    set_animation(&po, 1);
}
static void po_step(s8 event, s8 relative)
{
    po.animation_step.fields.duration = 5;
    po.animation_step.fields.event = event;
    po.animation_step.fields.relative_step = relative;
}

static void pcx_death(void)
{
    struct EngineObj engine = engine_obj;
    po_reset(0, 0);
    po.state = 2;
    po.unk42 = 0x8123;
    cyber_peacock_update(&po);
    assert(po.unk5 == 1 && po.unk7C == 0x7F && po.unk7E == 0x19 && po.ext.main_64.flash_timer == 0x19 && po.unk42 == 0x123 && po.unk17 == 0x20 && g_Player.script_action == 0x14);
    po.unk7C = 1;
    po.unk7E = 0;
    cyber_peacock_update(&po);
    assert(po.unk5 == 2 && effect_objects[0].id == 0x1A && po.ext.main_64.object == &effect_objects[0] && po.ext.main_64.flash_timer == 0x14 && po.unk7E == 0x14 && po.unk42 == 0x8123);
    po.unk5 = 1;
    po.unk7C = 5;
    po.unk7E = 0;
    po.ext.main_64.flash_timer = 3;
    cyber_peacock_update(&po);
    assert(po.unk5 == 1 && po.ext.main_64.flash_timer == 0 && po.unk7E == 5);
    po.unk5 = 2;
    effect_objects[0].unk7 = 1;
    po.unk7E = 0;
    cyber_peacock_update(&po);
    assert(po.unk7E == 0 && po.unk42 == 0x123);
    effect_objects[0].unk7 = 0;
    cyber_peacock_update(&po);
    assert(po.unk7E == 5 && po.unk42 == 0x8123);
    cyber_peacock_update(&po);
    assert(po.unk7E == 4);
    effect_objects[0].active = 0;
    engine_obj.unkF = 0;
    cyber_peacock_update(&po);
    assert(po.active == 0 && engine_obj.unkF == 0x10);
    po_reset(2, 0);
    po.state = 2;
    po.ext.main_64.object = &effect_objects[0];
    engine_obj.stage = 0xC;
    engine_obj.checkpoint = 0;
    engine_obj.character_state.bytes[6] = 0;
    cyber_peacock_update(&po);
    assert(po.active == 0 && (u8)engine_obj.unkF == 0x80 && engine_obj.character_state.bytes[6] == 1 && engine_obj.checkpoint == 9);
    engine_obj = engine;
}
static void pcx_intro(void)
{
    struct EngineObj engine = engine_obj;
    po_reset(1, 0);
    po.state = 0;
    cyber_peacock_intro(&po);
    assert(po.unk6 == 1 && effect_objects[0].id == 0x18 && po.ext.main_64.object == &effect_objects[0] && g_Player.script_action == 0x14);
    cyber_peacock_intro(&po);
    assert(po.unk6 == 1);
    po.unk5 = 2;
    po.unk6 = 0;
    cyber_peacock_intro(&po);
    assert(po.unk6 == 1 && po.unk17 == 0);
    po_step(1, 1);
    cyber_peacock_intro(&po);
    assert(po.unk6 == 1 && po.animation_step.fields.event == 0);
    cyber_peacock_intro(&po);
    assert(po.unk6 == 1);
    engine_obj.character_state.bytes[8] = 1;
    abc_object.unkC = 0;
    po_step(0, 0);
    cyber_peacock_intro(&po);
    assert(po.unk6 == 2 && po.unk7C == 2 && abc_object.unkC == 0x80 && abc_object.unkA == 0x3C);
    engine_obj.stage = 0xC;
    abc_object.unkC = 0;
    po.unk6 = 1;
    cyber_peacock_intro(&po);
    assert(po.unk6 == 2 && abc_object.unkC == 0);
    abc_object.unkC = 0x80;
    cyber_peacock_intro(&po);
    assert(po.unk6 == 2);
    abc_object.unkC = 0;
    engine_obj.enable_boss = 0;
    engine_obj.unk36.value = 0;
    cyber_peacock_intro(&po);
    assert(po.unk6 == 3 && po.unk17 == 1 && engine_obj.enable_boss == 1 && engine_obj.unk36.value == 0x3C);
    po.hp = 0x10;
    D_80173C84 = 0;
    engine_obj.unk36.timer = 2;
    cyber_peacock_intro(&po);
    assert(po.hp == 0x10 && engine_obj.unk36.timer == 1);
    engine_obj.unk36.timer = 0;
    po_step(1, 1);
    cyber_peacock_intro(&po);
    assert(po.hp == 0x10 && po.animation_step.fields.event == 0);
    cyber_peacock_intro(&po);
    assert(po.hp == 0x10);
    po_step(0, 0);
    po.unk7C = 2;
    cyber_peacock_intro(&po);
    assert(po.hp == 0x11 && po.unk7C == 1);
    cyber_peacock_intro(&po);
    assert(po.hp == 0x12 && po.unk7C == 2);
    po.hp = 0x30;
    g_Player.script_state = 1;
    cyber_peacock_intro(&po);
    assert(po.state == 1 && po.unk5 == 2 && po.unk6 == 0 && po.ext.main_64.saved_health == 0x30 && g_Player.script_state == 0);
    engine_obj = engine;
}
static void pcx_teleport(void)
{
    static const struct {
        u8 skip, laser, random;
        s16 player_x;
        u8 step, animation, unk2, facing;
        s16 x, y;
    } picks[] = {
        { 1, 0, 0, 0x500, 2, 3, 0, 1, 0x480, 0x660 },
        { 0, 0, 2, 0x440, 3, 0x23, 0, 0, 0x480, 0x6B3 },
        { 0, 0, 16, 0x440, 3, 3, 1, 1, 0x4A0, 0x6B3 },
        { 0, 0, 16, 0x500, 3, 3, 1, 0, 0x4F0, 0x6B3 },
        { 0, 1, 0, 0x500, 3, 8, 2, 1, 0x460, 0x670 },
    };
    u32 i;
    po_reset(2, 0);
    po.ext.main_64.skip_attack = 1;
    cyber_peacock_teleport(&po);
    assert(po.unk6 == 1 && po.unk17 == 2 && po.ext.main_64.skip_attack == 0 && po.ext.main_64.target_x == 0x480 && po.x_accel == FIXED(1) && po.hurt_box == NULL);
    po_step(0, 1);
    WEAPON_FRAME_COUNTER = 1;
    cyber_peacock_teleport(&po);
    assert(po.x_speed == FIXED(1) && po.x_pos.i.hi == 0x481);
    WEAPON_FRAME_COUNTER = 0;
    cyber_peacock_teleport(&po);
    assert(po.x_speed == FIXED(2) && po.x_pos.i.hi == 0x47E);
    po_step(0, 0);
    cyber_peacock_teleport(&po);
    assert(po.unk6 == 2 && po.unk7C == 0x50 && po.unk17 == 0x22);
    po.unk7C = 5;
    cyber_peacock_teleport(&po);
    assert(po.unk6 == 2 && po.unk7C == 4);
    for (i = 0; i < COUNT(picks); i++) {
        po_reset(2, 2);
        po.unk7C = 1;
        po.ext.main_64.target_x = 0x480;
        po.ext.main_64.target_y = 0x660;
        po.ext.main_64.skip_attack = picks[i].skip;
        po.ext.main_64.force_laser = picks[i].laser;
        cur_random = picks[i].random;
        g_Player.x_pos.i.hi = picks[i].player_x;
        cyber_peacock_teleport(&po);
        assert(po.unk6 == 3 && po.ext.main_64.next_step == picks[i].step && po.unk17 == picks[i].animation && po.unk2 == picks[i].unk2);
        assert(po.x_pos.i.hi == picks[i].x && po.y_pos.i.hi == picks[i].y && po.ext.main_64.target_y == picks[i].y && po.unk15 == (picks[i].facing ? PLAYER_FACING_RIGHT : 0));
    }
    po.x_accel = FIXED(1);
    po.x_speed = FIXED(2);
    po_step(0, 1);
    WEAPON_FRAME_COUNTER = 1;
    cyber_peacock_teleport(&po);
    assert(po.x_speed == FIXED(1) && po.x_pos.i.hi == 0x461);
    WEAPON_FRAME_COUNTER = 0;
    cyber_peacock_teleport(&po);
    assert(po.x_speed == 0 && po.x_pos.i.hi == 0x460);
    po_step(0, 0);
    cyber_peacock_teleport(&po);
    assert(po.unk6 == 4 && po.unk7C == 0x14 && PO_IS(po.hurt_box, &cyber_peacock_hit_box) && po.contact_damage == 5);
    po.unk7C = 2;
    cyber_peacock_teleport(&po);
    assert(po.unk6 == 4 && po.unk7C == 1);
    po.ext.main_64.hit_count = 3;
    cyber_peacock_teleport(&po);
    assert(po.unk5 == 3 && po.unk6 == 0 && po.ext.main_64.hit_count == 0);
}
static void pcx_kick(void)
{
    po_reset(3, 0);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 1 && po.unk17 == 4 && po.contact_damage == 6);
    po_step(0, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 1);
    po_step(1, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 2 && po.air_state == 1 && po.y_speed == FIXED(8) && po.gravity == FIXED(0.34375));
    cyber_peacock_attack(&po);
    assert(po.unk6 == 2 && po.y_speed == FIXED(8) - FIXED(0.34375) && po.y_pos.i.hi == 0x658);
    po.y_speed = -1;
    cyber_peacock_attack(&po);
    assert(po.unk6 == 3 && po.unk17 == 5);
    po_step(0, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 3);
    po_step(0, 0);
    cyber_peacock_attack(&po);
    assert(po.unk5 == 2 && po.unk6 == 1 && po.x_speed == FIXED(22) && po.air_state == 0 && po.unk17 == 0x22 && po.contact_damage == 5);
}
static void pcx_slash(void)
{
    po_reset(3, 0);
    po.unk2 = 1;
    cyber_peacock_attack(&po);
    assert(po.unk6 == 1 && po.unk7C == 0 && po.unk17 == 6 && po.contact_damage == 9);
    po_step(1, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 1 && po.animation_step.fields.event == 0 && !PO_IS(po.hurt_box, NULL));
    cyber_peacock_attack(&po);
    assert(po.unk6 == 1);
    po.unk7C = 2;
    po_step(0, -1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 1 && po.unk7C == 3);
    po.unk7C = 3;
    po_step(0, -1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 2 && po.unk17 == 7);
    po_step(0, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 2);
    po_step(0, 0);
    cyber_peacock_attack(&po);
    assert(po.unk5 == 2 && po.unk6 == 1 && po.x_speed == FIXED(22) && po.unk17 == 0x22 && po.contact_damage == 5);
}
static void pcx_laser(void)
{
    po_reset(3, 0);
    po.unk2 = 2;
    po.ext.main_64.shot_count = 5;
    cyber_peacock_attack(&po);
    assert(po.unk6 == 1 && po.ext.main_64.shot_count == 0 && po.unk17 == 0x25);
    po_step(0, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 1);
    po_step(0, 0);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 2 && po.unk7C == 0x1E && po.unk17 == 9);
    po_step(0, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 2 && item_objects[0].active == 0);
    po_step(0, 0);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 3 && po.unk17 == 0x24 && item_objects[0].active == 0x41 && item_objects[0].id == 0x17 && po.ext.main_64.object == &item_objects[0]);
    po.unk7C = 2;
    cyber_peacock_attack(&po);
    assert(po.unk6 == 3 && po.unk7C == 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 4 && po.unk17 == 0xC);
    po_step(0, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 4 && shot_objects[0].active == 0);
    po_step(0, 0);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 5 && shot_objects[0].active == 0x41 && shot_objects[0].id == 0x2A && shot_objects[0].unk7C == (void*)&item_objects[0]);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 3 && po.unk7C == 0x5A && po.ext.main_64.shot_count == 1 && po.unk17 == 9);
    po.unk6 = 5;
    po.ext.main_64.shot_count = 7;
    cyber_peacock_attack(&po);
    assert(po.unk6 == 6 && po.unk7C == 0x3C && po.ext.main_64.shot_count == 8 && po.unk17 == 2);
    po_step(0, 1);
    cyber_peacock_attack(&po);
    assert(po.unk6 == 6);
    po_step(0, 0);
    cyber_peacock_attack(&po);
    assert(po.unk5 == 2 && po.unk6 == 1 && po.unk2 == 0 && po.ext.main_64.shot_count == 0 && po.x_speed == FIXED(22));
}
static void pcx_guard(void)
{
    po_reset(5, 0);
    po.unk7C = 5;
    po.ext.main_64.shot_count = 2;
    po.hurt_box = &cyber_peacock_hit_box;
    func_8007D710(&po);
    assert(po.unk6 == 1 && po.unk7C == 0 && po.ext.main_64.shot_count == 0 && po.unk17 == 0x21 && po.hurt_box == NULL && po.attack_box == NULL);
    po_step(0, 1);
    func_8007D710(&po);
    assert(po.unk6 == 1 && po.unk7C == 0);
    po_step(0, -1);
    func_8007D710(&po);
    assert(po.unk6 == 1 && po.unk7C == 1);
    po.unk7C = 3;
    func_8007D710(&po);
    assert(po.unk6 == 2 && po.unk7C == 0x3C && po.unk17 == 0x22);
    po.ext.main_64.flash_timer = 9;
    func_8007D710(&po);
    assert(po.unk5 == 2 && po.unk6 == 1 && po.x_speed == 0x160000 && po.ext.main_64.flash_timer == 0);
}
static void (*const pcx_cases[])(void) = {
    pcx_death,
    pcx_intro,
    pcx_teleport,
    pcx_kick,
    pcx_slash,
    pcx_laser,
    pcx_guard,
};
static u32 pcx_run(u32 row)
{
    pcx_cases[row]();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "cyber_peacock_states", 0, 0, COUNT(cyber_peacock_states_cases), test_cyber_peacock_states },
    { "cyber_peacock_intro_context", NULL, NULL, COUNT(cyber_peacock_intro_context_cases_expected), cyber_peacock_intro_context_cases_row },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "hit_count_reset_both_weaknesses_parry_and_flash", NULL, NULL, COUNT(hits) * 12, hit_count_reactions },
    { "cyber_peacock_state_steps", NULL, NULL, COUNT(pcx_cases), pcx_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(cyber_peacock_states_cases) + COUNT(cyber_peacock_intro_context_cases_expected) + COUNT(pool_full_cases) + COUNT(hits) * 12 + COUNT(pcx_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
