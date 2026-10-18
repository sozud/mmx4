#include "test_runtime.h"
#include "main/visuals/visual_19_double_cyclone_charged_fan.h"
#include "main/55C4.h"
extern u32* D_8011C0F0[5];

static s32 gfx[128], sprites[128];

static u32 fan_case(u32 mode)
{
    struct VisualObj obj, expected;
    struct PlayerObj player_before;
    struct BackgroundObj backgrounds_before[3];
    s32 gfx_before[128], sprites_before[128];
    u32 i, result;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    for (i = 0; i < 128; i++) {
        gfx[i] = 0x12340000 + i;
        sprites[i] = 0x56780000 + i;
    }
    gfx[8] = 64;
    sprites[16] = 80;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)sprites;
    memcpy(gfx_before, gfx, sizeof(gfx));
    memcpy(sprites_before, sprites, sizeof(sprites));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    g_Player.hp = 30;
    g_Player.weapon = 7;
    g_Player.unk15 = mode == 8 ? 0x40 : 0;
    g_Player.x_pos.val = 100 * 65536 + 0xABCD;
    g_Player.y_pos.val = 100 * 65536 + 0xDCBA;
    if (mode == 0)
        g_Player.input_locked = 1;
    if (mode == 1)
        g_Player.capsule_state = 1;
    if (mode == 2)
        g_Player.weapon = 6;
    if (mode == 3)
        g_Player.actions_reset = 1;
    if (mode == 4)
        g_Player.hp = 0;
    obj.active = 0x41;
    obj.id = 19;
    obj.unk2 = 1;
    obj.state = mode < 7 ? 1 : 0;
    obj.on_screen = 1;
    obj.unk5 = 9;
    obj.unk6 = 10;
    obj.unk7 = 11;
    obj.bg_offset = -1;
    obj.unk15 = 0x20;
    obj.unk16 = 3;
    obj.unk49 = 0x55;
    obj.unk5C.value = mode == 6 ? 0 : 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_vel.val = -12345;
    obj.y_vel.val = 54321;
    obj.unk38 = (u8*)gfx + 96;
    obj.unk3C = (u8*)sprites + 112;
    obj.animation_table = D_8011C0F0;
    set_animation(&obj, 3);
    assert(obj.animation_step.packed == 0x14010001);
    expected = obj;
    player_before = g_Player;
    if (mode < 5 || mode == 6)
        memset(&expected, 0, 8);
    else if (mode == 5) {
        expected.unk5C.value = 0;
        expected.animation_cursor = D_8011C0F0[3] + 1;
        expected.animation_step = *(union AnimationStep*)(D_8011C0F0[3] + 1);
        assert(expected.animation_step.packed == 0x18010001);
    } else {
        expected.unk38 = (u8*)gfx + 64;
        expected.unk3C = (u8*)sprites + 80;
        expected.unk40 = 0x520;
        expected.unk42 = 0x7801;
        expected.unk16 = 0;
        expected.unk15 = mode == 8 ? 0 : 0x40;
        expected.x_pos.i.hi = mode == 8 ? 69 : 131;
        expected.y_pos.i.hi = 93;
        expected.unk5C.value = 16;
        expected.unk49 = 0;
        expected.state = 1;
    }
    func_800B2698(&obj);
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
    result = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)(u16)obj.unk5C.value << 16);
    return result;
}
static const u32 double_cyclone_fan_player_gates_cases_expected[] = { 0x10000u, 0x10000u, 0x10000u, 0x10000u, 0x10000u, 0x141u, 0x0u, 0x100141u, 0x100141u };

const struct CTestGroup c_test_groups[] = {
    { "double_cyclone_fan_player_gates", NULL, double_cyclone_fan_player_gates_cases_expected, COUNT(double_cyclone_fan_player_gates_cases_expected), fan_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_cyclone_fan_player_gates_cases_expected);
