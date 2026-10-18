#include "test_runtime.h"
#include "main/mains/main_36_latcher.h"
#include "main/195B4.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
extern struct Unk_unk68 latcher_hurt_box;
extern struct Unk_unk68 D_801073F4[];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 release_case(u32 linked)
{
    struct MainObj obj, before;
    struct MiscObj companion, companion_before;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&companion, 0, sizeof(companion));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 36;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk62 = 7;
    obj.ext.main_36.unk8A = 1;
    obj.ext.main_36.unk8C = linked;
    obj.ext.main_36.unk84 = linked ? &companion : NULL;
    obj.hurt_box = obj.attack_box = (const u8*)&latcher_hurt_box;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)latcher_animations;
    set_animation(&obj, 4);
    companion.active = 0x41;
    companion.id = 11;
    companion.ext.misc_11.active = 0;
    companion.animation_table = (u32**)latcher_animations;
    set_animation(&companion, 5);
    g_Player.stun_timer = 0x25;
    g_Player.hp = 0x26;
    before = obj;
    companion_before = companion;
    player_before = g_Player;
    SP_CUR_MAIN_OBJ = &obj;
    latcher_grab_drain(&obj);
    before.ext.main_36.unk8A = 0;
    before.unk62 = 0;
    before.attack_box = before.hurt_box = NULL;
    before.unk6 = 3;
    before.unk17 = 6;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)latcher_animations[6];
    before.animation_step = *latcher_animations[6];
    player_before.stun_timer = 0;
    if (linked)
        companion_before.ext.misc_11.active = 1;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(companion) / 4; i++)
        assert(((u32*)&companion)[i] == ((u32*)&companion_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(SP_CUR_MAIN_OBJ == &obj);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)companion.ext.misc_11.active << 16);
}
static const u32 latcher_drain_release_animation_cases_expected[] = { 0x603u, 0x10603u };

static u32 hit_case(u32 mode)
{
    struct MainObj obj, expected, context, context_before;
    struct WeaponObj weapons_before[16];
    struct VisualObj visuals_before[32];
    struct PlayerObj player_before;
    u32 i, animation = mode == 1 ? 3 : mode == 3 ? 1
        : mode == 5                              ? 2
                                                 : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&context, 0, sizeof(context));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
    }
    D_8013E198[0] = -1;
    SP_CUR_MAIN_OBJ = &context;
    obj.active = 0x41;
    obj.id = 36;
    obj.state = 1;
    obj.unk5 = mode == 2 ? 3 : 1;
    obj.hp = mode == 1 ? 1 : 10;
    obj.unk42 = 0x9234;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.hurt_box = obj.attack_box = (const u8*)&latcher_hurt_box;
    obj.collision_data = (const u16*)D_80105FF0;
    obj.x_speed = mode == 4 ? 0x4800 : mode == 6 ? -0x4800
                                                 : 0;
    obj.animation_table = (const u8* const*)latcher_animations;
    set_animation(&obj, 0);
    g_Player.spike_immune = 1;
    g_Player.x_pos.i.hi = mode >= 5 ? 110 : 90;
    if (mode != 0) {
        weapon_objects[0].active = 1;
        weapon_objects[0].id = 0;
        weapon_objects[0].unk50 = (const u8*)&latcher_hurt_box;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
    }
    expected = obj;
    context_before = context;
    player_before = g_Player;
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    expected.unk42 = mode == 0 ? 0x1234 : 0x9234;
    if (mode != 0) {
        weapons_before[0].unk98 = 1;
        weapons_before[0].unk80.word = 100 | (200u << 16);
        if (mode == 1) {
            expected.hp = 0;
            expected.unk5 = 3;
            expected.unk6 = 1;
            expected.hurt_box = expected.attack_box = NULL;
            context_before.ext.main_36.unk8A = 1;
        } else {
            expected.hp = 16;
            if (mode != 2)
                expected.x_speed = mode == 3 ? 0x4800 : mode == 4 ? 0x9000
                    : mode == 5                                   ? -0x4800
                                                                  : -0x9000;
        }
        if (animation) {
            expected.unk17 = animation;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = (const u8*)latcher_animations[animation];
            expected.animation_step = *latcher_animations[animation];
        }
    }
    latcher_check_hit(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(context) / 4; i++)
        assert(((u32*)&context)[i] == ((u32*)&context_before)[i]);
    for (i = 0; i < sizeof(weapons_before) / 4; i++)
        assert(((u32*)weapon_objects)[i] == ((u32*)weapons_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(visuals_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals_before)[i]);
    assert(SP_CUR_MAIN_OBJ == &context && D_8013E198[0] == -1);
    return (u8)obj.hp | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk6 << 16) | ((u32)obj.unk17 << 24);
}
static const u32 latcher_weapon_responses_cases_expected[] = { 0x10Au, 0x3010300u, 0x310u, 0x1000110u, 0x110u, 0x2000110u, 0x110u };

struct func_8005F558_case {
    u32 unk2;
};
static const struct func_8005F558_case func_8005F558_cases[] = {
    { 0 },
    { 1 },
    { 2 },
    { -1 },
    { 3 },
};
static u32 test_func_8005F558(u32 row)
{
    const struct func_8005F558_case* c = &func_8005F558_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    s32 frames[32], frames_before[32];
    u32 metadata[16], metadata_before[16];
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 36;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.hp = 16;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = (const u8* const*)latcher_animations;
    set_animation(&obj, 2);
    obj.state = 0;
    obj.unk2 = c->unk2;
    obj.unk62 = 7;
    obj.unk15 = 0x20;
    obj.contact_damage = 5;
    obj.hp = 7;
    obj.x_speed = 0x24000;
    obj.y_speed = -0x23000;
    obj.x_accel = 0x1000;
    obj.gravity = 0x2000;
    obj.air_state = 1;
    obj.invincibility_timer = 3;
    obj.terrain_box = &latcher_hurt_box;
    obj.ext.main_36.unk80[0] = 0x31;
    obj.ext.main_36.unk80[1] = 0x32;
    obj.ext.main_36.unk80[2] = 0x33;
    obj.ext.main_36.unk80[3] = 0x34;
    obj.ext.main_36.unk84 = &misc_objects[63];
    obj.ext.main_36.saved_unk5 = 0x23;
    obj.ext.main_36.unk8A = 7;
    obj.ext.main_36.unk8C = 3;
    obj.ext.main_36.unk8D = 5;
    memset(&frames, 0, sizeof(frames));
    memset(&metadata, 0, sizeof(metadata));
    frames[1] = 64;
    metadata[1] = 0x1680;
    TEST_MENU_FRAMES = (u8*)frames;
    D_801406A8 = metadata;
    engine_obj.stage = 6;
    engine_obj.substage = 0;
    g_Player.bg_offset = 1;
    SP_CUR_MAIN_OBJ = &obj;
    assert(s_StageMainIds[6][0][1] == 0x24);
    assert((u8)func_8002938C(0x24) == 1);
    expected = obj;
    expected.unk40 = 0x2D;
    expected.unk42 = 0x784C;
    expected.sprite_frames = (u8*)frames + 64;
    expected.attack_box = &latcher_hurt_box;
    expected.hurt_box = &latcher_hurt_box;
    expected.unk16 = 6;
    expected.unk62 = 3;
    expected.collision_data = D_801073F4;
    expected.hp = 16;
    expected.x_speed = 0;
    expected.y_speed = 0;
    expected.x_accel = 0;
    expected.gravity = 0;
    expected.air_state = 0;
    expected.unk15 = 0;
    expected.contact_damage = 0;
    expected.terrain_box = NULL;
    expected.invincibility_timer = 0;
    expected.bg_offset = 1;
    if (obj.unk2 == 0) {
        set_animation(&expected, 0);
    }
    if (obj.unk2 == 0) {
        expected.ext.main_36.unk80[0] = 0;
    }
    if (obj.unk2 == 0) {
        expected.ext.main_36.unk80[1] = 0;
    }
    if (obj.unk2 == 0) {
        expected.ext.main_36.unk80[2] = 0;
    }
    if (obj.unk2 == 0) {
        expected.ext.main_36.unk80[3] = 0;
    }
    if (obj.unk2 == 1) {
        set_animation(&expected, 1);
    }
    if (obj.unk2 == 1) {
        expected.x_speed = 0x18000;
    }
    if (obj.unk2 == 2) {
        set_animation(&expected, 1);
    }
    if (obj.unk2 == 2) {
        expected.unk15 = 0x40;
    }
    if (obj.unk2 == 2) {
        expected.x_speed = -0x18000;
    }
    expected.ext.main_36.unk8A = 0x80;
    expected.ext.main_36.unk8C = 0;
    expected.ext.main_36.unk8D = 0;
    expected.state = 1;
    expected.unk5 = 2;
    player_expected = g_Player;
    engine_before = engine_obj;
    memcpy(frames_before, frames, sizeof(frames_before));
    memcpy(metadata_before, metadata, sizeof(metadata_before));
    func_8005F558(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(frames, frames_before, sizeof(frames));
    c_test_same_words(metadata, metadata_before, sizeof(metadata));
    assert(SP_MENU_FRAMES == frames && D_801406A8 == metadata);
    return 1;
}

struct latcher_drift_case {
    u32 stun_timer, pool_0_full;
    u32 expected[13];
};
static const struct latcher_drift_case latcher_drift_cases[] = {
    { 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { -1, 255, { 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_latcher_drift(u32 row)
{
    const struct latcher_drift_case* c = &latcher_drift_cases[row];
    u32 observed_values[13];
    struct MainObj obj;
    struct MainObj child_0;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&misc_objects, 0, sizeof(misc_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0.ext.main_36.unk8D = 1;
    g_Player.stun_timer = c->stun_timer;
    pool_0_full = c->pool_0_full;
    SP_CUR_MAIN_OBJ = &child_0;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    latcher_drift(&obj);
    observed_values[0] = (u32)child_0.ext.main_36.unk8C;
    observed_values[1] = (u32)misc_objects[0].active;
    observed_values[2] = (u32)misc_objects[0].bg_offset;
    observed_values[3] = (u32)misc_objects[0].ext.misc_11.active;
    observed_values[4] = (u32)misc_objects[0].id;
    observed_values[5] = (u32)misc_objects[0].unk15;
    observed_values[6] = (u32)misc_objects[0].unk16;
    observed_values[7] = (u32)misc_objects[0].unk40;
    observed_values[8] = (u32)misc_objects[0].unk42;
    observed_values[9] = (u32)misc_objects[0].x_pos.val;
    observed_values[10] = (u32)misc_objects[0].y_pos.val;
    observed_values[11] = (u32)obj.unk5;
    observed_values[12] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 13);
}

static const u32 latcher_grab_clamp_expected[] = { 1u };
static u32 test_latcher_grab_clamp(u32 row)
{
    u32 observed_values[1];
    struct MainObj obj;
    struct MainObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    obj.animation_step.fields.event = -1;
    SP_CUR_MAIN_OBJ = &child_0;
    latcher_grab_clamp(&obj);
    observed_values[0] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, latcher_grab_clamp_expected, 1);
}

static const u32 latcher_grab_drain_expected[] = { 0xFFFFu, 0u, 0u, 0u, 0u };
static u32 test_latcher_grab_drain(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    struct MainObj child_0;
    struct MiscObj child_1;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    SP_CUR_MAIN_OBJ = &child_0;
    child_0.ext.main_36.unk84 = NULL;
    latcher_grab_drain(&obj);
    observed_values[0] = (u32)child_0.ext.main_36.unk8A;
    observed_values[1] = (u32)child_1.ext.misc_11.active;
    observed_values[2] = (u32)g_Player.stun_timer;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk62;
    return c_test_observe(0, row, observed_values, latcher_grab_drain_expected, 5);
}

struct latcher_grab_home_case {
    u32 y_pos, close, y_speed, unk89;
};
static const struct latcher_grab_home_case latcher_grab_home_cases[] = {
    { 7886456, 0, -65536, 24 },
    { 6772344, 0, -65536, 24 },
    { 6706808, 1, -65536, 24 },
    { 6444664, 1, 65536, 8 },
};
static u32 test_latcher_grab_home(u32 row)
{
    const struct latcher_grab_home_case* c = &latcher_grab_home_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct MiscObj misc_expected[64];
    s32 y_speed;
    u8 close;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 36;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.hp = 16;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = (const u8* const*)latcher_animations;
    set_animation(&obj, 2);
    obj.unk5 = 3;
    obj.unk6 = 0;
    obj.ext.main_36.unk84 = &misc_objects[63];
    obj.ext.main_36.unk8C = 1;
    set_animation(&obj, 0);
    memset(&misc_objects[63], 0, sizeof(misc_objects[63]));
    misc_objects[63].active = 0x41;
    misc_objects[63].id = 11;
    misc_objects[63].state = 1;
    misc_objects[63].unk16 = 1;
    misc_objects[63].unk40 = obj.unk40;
    misc_objects[63].unk42 = obj.unk42;
    misc_objects[63].unk3C = obj.sprite_frames;
    misc_objects[63].animation_table = (u32**)latcher_animations;
    misc_objects[63].x_pos = obj.x_pos;
    misc_objects[63].y_pos = obj.y_pos;
    set_animation(&misc_objects[63], 0);
    SP_CUR_MAIN_OBJ = &obj;
    g_Player.x_pos = obj.x_pos;
    g_Player.y_pos.val = c->y_pos;
    close = c->close;
    y_speed = c->y_speed;
    expected = obj;
    expected.ext.main_36.unk89 = c->unk89;
    expected.x_speed = 0;
    expected.y_speed = y_speed;
    expected.y_pos.val = obj.y_pos.val - y_speed;
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    misc_expected[63].x_vel.val = 0;
    misc_expected[63].y_vel.val = y_speed;
    misc_expected[63].y_pos.val = misc_objects[63].y_pos.val - y_speed;
    if (close) {
        set_animation(&expected, 3);
    }
    if (close) {
        set_animation(&misc_expected[63], 3);
    }
    if (close) {
        expected.unk6 = 1;
    }
    player_expected = g_Player;
    engine_before = engine_obj;
    latcher_grab_home(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    return 1;
}

struct latcher_main_case {
    u32 unk62, immune;
    u32 expected[5];
};
static const struct latcher_main_case latcher_main_cases[] = {
    { 0, 0, { 0u, 0xFFFFFF90u, 1u, 0u, 0x10001u } },
    { 3, 0, { 1u, 0xFFFFFF90u, 3u, 1u, 0x10001u } },
    { 3, 1, { 0u, 0x10u, 0u, 0u, 0x10001u } },
};
static u32 test_latcher_main(u32 row)
{
    const struct latcher_main_case* c = &latcher_main_cases[row];
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    struct WeaponObj weapons_before[16];
    u8 immune;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 36;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.hp = 16;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.animation_table = (const u8* const*)latcher_animations;
    set_animation(&obj, 2);
    set_animation(&obj, 0);
    obj.unk5 = 1;
    obj.ext.main_36.saved_unk5 = 2;
    obj.ext.main_36.unk8D = 0;
    obj.unk62 = c->unk62;
    obj.contact_damage = 0;
    obj.attack_box = &latcher_hurt_box;
    obj.hurt_box = &latcher_hurt_box;
    obj.collision_data = D_801073F4;
    SP_CUR_MAIN_OBJ = &obj;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 16;
    g_Player.x_pos = obj.x_pos;
    g_Player.y_pos = obj.y_pos;
    g_Player.unk54 = (const u32*)&latcher_hurt_box;
    immune = c->immune;
    g_Player.spike_immune = immune;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    FILL_ACTIVE(weapon_objects, 16, 0);
    expected = obj;
    expected.unk5 = 2;
    expected.animation_step.fields.duration = 1;
    player_expected = g_Player;
    if (!immune) {
        player_expected.hp = -112;
    }
    if (!immune) {
        player_expected.hurt_type = obj.unk62 ? 3 : 1;
    }
    if (!immune) {
        player_expected.stun_timer = obj.unk62 ? 1 : 0;
    }
    if (!immune && obj.unk62 == 3) {
        expected.ext.main_36.unk8D = 1;
    }
    engine_before = engine_obj;
    background_before = background_objects[0];
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    latcher_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    observed_values[0] = (u32)g_Player.stun_timer;
    observed_values[1] = (u32)g_Player.hp;
    observed_values[2] = (u32)g_Player.hurt_type;
    observed_values[3] = (u32)obj.ext.main_36.unk8D;
    observed_values[4] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

const struct CTestGroup c_test_groups[] = {
    { "latcher_drain_release_animation", NULL, latcher_drain_release_animation_cases_expected, COUNT(latcher_drain_release_animation_cases_expected), release_case },
    { "latcher_weapon_responses", NULL, latcher_weapon_responses_cases_expected, COUNT(latcher_weapon_responses_cases_expected), hit_case },
    { "func_8005F558", 0, 0, 5, test_func_8005F558 },
    { "latcher_drift", 0, 0, 2, test_latcher_drift },
    { "latcher_grab_clamp", 0, 0, 1, test_latcher_grab_clamp },
    { "latcher_grab_drain", 0, 0, 1, test_latcher_grab_drain },
    { "latcher_grab_home", 0, 0, 4, test_latcher_grab_home },
    { "latcher_main", 0, 0, 3, test_latcher_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(latcher_drain_release_animation_cases_expected) + COUNT(latcher_weapon_responses_cases_expected) + 5 + 2 + 1 + 1 + 4 + 3;
