#include "test_runtime.h"
#include "main/weapons/weapon_08_twin_slasher.h"
#include "main/55C4.h"
extern u32* D_8011C104[10];

static s32 gfx[128], sprites[128];
static u32 trail_case(u32 mode)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before;
    struct BackgroundObj backgrounds_before[3];
    s32 gfx_before[128], sprites_before[128];
    u32 i, result, animation = mode >= 5 ? mode + 1 : 6;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    for (i = 0; i < 128; i++) {
        gfx[i] = 0x12340000 + i;
        sprites[i] = 0x56780000 + i;
    }
    gfx[9] = 64;
    sprites[17] = 80;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    memcpy(gfx_before, gfx, sizeof(gfx));
    memcpy(sprites_before, sprites, sizeof(sprites));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    g_Player.hp = 30;
    g_Player.weapon = mode == 2 ? 7 : 8;
    g_Player.input_locked = mode == 0;
    g_Player.capsule_state = mode == 1;
    obj.active = 1;
    obj.id = 41;
    obj.unk2 = mode >= 5 ? mode - 5 : 0;
    obj.state = mode < 5 ? 1 : 0;
    obj.on_screen = 1;
    obj.unk5 = 9;
    obj.unk6 = 10;
    obj.unk7 = 11;
    obj.unk15 = PLAYER_FACING_RIGHT;
    obj.bg_offset = -1;
    obj.unk16 = VISUAL_SATURN_LAYER(3);
    obj.unk40 = 0x3333;
    obj.unk42 = 0x5555;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_vel.val = -12345;
    obj.y_vel.val = 54321;
    obj.unk38 = (u8*)gfx + 96;
    obj.unk3C = (u8*)sprites + 112;
    obj.animation_table = D_8011C104;
    set_animation(&obj, animation);
    if (mode == 4) {
        obj.animation_cursor = D_8011C104[6] + 5;
        obj.animation_step = *(union AnimationStep*)obj.animation_cursor;
        assert(obj.animation_step.packed == C_TEST_STEP(0x12000060));
    }
    expected = obj;
    player_before = g_Player;
    if (mode < 3 || mode == 4) {
        memset(&expected, 0, 8);
        if (mode == 4)
            expected.animation_step.fields.duration = 95;
    } else if (mode == 3)
        expected.animation_step.fields.duration = 1;
    else {
        expected.unk38 = (u8*)gfx + 64;
        expected.unk3C = (u8*)sprites + 80;
        expected.unk40 = WEAPON_TEXTURE_SPECIAL_0;
        expected.unk42 = OBJECT_CLUT(0x7801);
        expected.unk16 = VISUAL_SATURN_LAYER(1);
        expected.state = 1;
    }
    func_80097DD8(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < 128; i++) {
        assert(gfx[i] == gfx_before[i]);
        assert(sprites[i] == sprites_before[i]);
    }
    assert(SP_PLAYER_GFX == gfx && SP_SPRITE_FRAMES == sprites);
    result = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)obj.animation_step.fields.duration << 16) | ((u32)obj.unk17 << 24);
    return result;
}
static const u32 twin_slasher_trail_archive_gates_cases_expected[] = { 0x6020000u, 0x6020000u, 0x6020000u, 0x6010101u, 0x65F0000u, 0x6020101u, 0x7020101u, 0x8020101u, 0x9020101u };

static const u32 twin_slasher_charged_update_expected[] = { 0x10200u };
static u32 test_twin_slasher_charged_update(u32 row)
{
    u32 observed_values[1];
    struct WeaponObj obj, before;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&misc_objects, 0, sizeof(misc_objects));

    g_Player.input_locked = 0;
    g_Player.capsule_state = -1;
    g_Player.weapon = 0;
    obj.state = 0;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    obj.active = 0x41;
    obj.id = 17;
    obj.unk2 = 1;
    obj.on_screen = 1;
    obj.unk5 = 5;
    obj.unk6 = 6;
    obj.unk7 = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.unk50 = &obj;
    before = obj;
    player_before = g_Player;
    twin_slasher_charged_update(&obj);
    before.active = before.id = before.unk2 = before.on_screen = 0;
    before.state = before.unk5 = before.unk6 = before.unk7 = 0;
    before.unk50 = NULL;
    --player_before.shot_count;
    --player_before.special_shot_count;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u8)obj.state | ((u32)(u8)g_Player.shot_count << 8) | ((u32)(u8)g_Player.special_shot_count << 16) | ((u32)(u8)obj.active << 24);
    return c_test_observe(0, row, observed_values, twin_slasher_charged_update_expected, 1);
}

static const u32 twin_slasher_update_expected[] = { 0x10200u };
static u32 test_twin_slasher_update(u32 row)
{
    u32 observed_values[1];
    struct WeaponObj obj, before;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&background_objects, 0, sizeof(background_objects));

    g_Player.input_locked = 0;
    g_Player.capsule_state = -1;
    g_Player.weapon = 0;
    obj.state = 0;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    obj.active = 0x41;
    obj.id = 8;
    obj.unk2 = 1;
    obj.on_screen = 1;
    obj.unk5 = 5;
    obj.unk6 = 6;
    obj.unk7 = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.unk50 = &obj;
    before = obj;
    player_before = g_Player;
    twin_slasher_update(&obj);
    before.active = before.id = before.unk2 = before.on_screen = 0;
    before.state = before.unk5 = before.unk6 = before.unk7 = 0;
    before.unk50 = NULL;
    --player_before.shot_count;
    --player_before.special_shot_count;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u8)obj.state | ((u32)(u8)g_Player.shot_count << 8) | ((u32)(u8)g_Player.special_shot_count << 16);
    return c_test_observe(0, row, observed_values, twin_slasher_update_expected, 1);
}

void twin_slasher_charged_update(struct WeaponObj*);
static struct WeaponObj ts;
static u32 slash_step = C_TEST_STEP(5);
static u32 slasher(void (*update)(struct WeaponObj*), u8 state, s16 x, u8 stop, u8 timer)
{
    u32 i;
    memset(&ts, 0, sizeof(ts));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < COUNT(gfx); i++)
        gfx[i] = sprites[i] = 0x40;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    g_Player.weapon = 8;
    g_Player.x_pos.i.hi = 0x100;
    g_Player.y_pos.i.hi = 0x80;
    ts.active = 1;
    ts.id = 8;
    ts.state = state;
    ts.on_screen = 1;
    ts.unk50 = (const u8*)&ts;
    ts.animation_cursor = (const u8*)&slash_step;
    ts.animation_step.packed = slash_step;
    ts.x_pos.i.hi = x;
    ts.y_pos.i.hi = 0x60;
    ts.unk98 = stop;
    ts.ext.weapon_8.timer = timer;
    update(&ts);
    return ts.state | (u32)ts.on_screen << 8 | (u32)(ts.unk50 != NULL) << 16 | (u32)ts.ext.weapon_8.timer << 24;
}
static u32 tsl_start_left(void)
{
    u32 seen = slasher(twin_slasher_update, 0, 0, 0, 0);
    assert(ts.x_vel.val < 0 && ts.unk15 == 0);
    return seen;
}
static u32 tsl_far(void) { return slasher(twin_slasher_update, 1, 0x1000, 0, 5); }
static u32 tsl_stopped(void) { return slasher(twin_slasher_update, 1, 0x80, 1, 5); }
static u32 tsl_timed_out(void) { return slasher(twin_slasher_update, 1, 0x80, 0, 0); }
static u32 tsl_charged_far(void) { return slasher(twin_slasher_charged_update, 1, 0x1000, 0, 5); }
static const CTestCase twin_slasher_paths_cases[] = {
    tsl_start_left,
    tsl_far,
    tsl_stopped,
    tsl_timed_out,
    tsl_charged_far,
};
static const u32 twin_slasher_paths_cases_expected[] = { 0x18010101u, 0x05000003u, 0x05000003u, 0x00000003u, 0x05000003u };

const struct CTestGroup c_test_groups[] = {
    { "twin_slasher_trail_archive_gates", NULL, twin_slasher_trail_archive_gates_cases_expected, COUNT(twin_slasher_trail_archive_gates_cases_expected), trail_case },
    { "twin_slasher_charged_update", 0, 0, 1, test_twin_slasher_charged_update },
    { "twin_slasher_update", 0, 0, 1, test_twin_slasher_update },
    { "twin_slasher_paths", twin_slasher_paths_cases, twin_slasher_paths_cases_expected, COUNT(twin_slasher_paths_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(twin_slasher_trail_archive_gates_cases_expected) + 1 + 1 + COUNT(twin_slasher_paths_cases);
