#include "test_runtime.h"
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
    obj.unk15 = 0x40;
    obj.bg_offset = -1;
    obj.unk16 = 3;
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
        assert(obj.animation_step.packed == 0x12000060);
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
        expected.unk40 = 0x520;
        expected.unk42 = 0x7801;
        expected.unk16 = 1;
        expected.state = 1;
    }
    func_80097DD8(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < 128; i++) {
        assert(gfx[i] == gfx_before[i]);
        assert(sprites[i] == sprites_before[i]);
    }
    assert(SP_PLAYER_GFX == gfx && SP_SPRITE_FRAMES == sprites);
    result = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)obj.animation_step.fields.duration << 16) | ((u32)obj.unk17 << 24);
    return result;
}
#define CASE(m)                                                 \
    static u32 twin_slasher_trail_archive_gates_trail_##m(void) \
    {                                                           \
        return trail_case(m);                                   \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
#define ENTRY(m) twin_slasher_trail_archive_gates_trail_##m,
static const CTestCase twin_slasher_trail_archive_gates_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) };
static const u32 twin_slasher_trail_archive_gates_cases_expected[] = { 0x6020000u, 0x6020000u, 0x6020000u, 0x6010101u, 0x65F0000u, 0x6020101u, 0x7020101u, 0x8020101u, 0x9020101u };
#undef CASE
#undef ENTRY

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

const struct CTestGroup c_test_groups[] = {
    { "twin_slasher_trail_archive_gates", twin_slasher_trail_archive_gates_cases, twin_slasher_trail_archive_gates_cases_expected, COUNT(twin_slasher_trail_archive_gates_cases), 0 },
    { "twin_slasher_charged_update", 0, 0, 1, test_twin_slasher_charged_update },
    { "twin_slasher_update", 0, 0, 1, test_twin_slasher_update },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(twin_slasher_trail_archive_gates_cases) + 1 + 1;
