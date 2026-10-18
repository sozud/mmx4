#include "test_runtime.h"
#include "main/55C4.h"
#include "main/player_animations.h"
#include "main/player_common.h"
void func_800257BC(struct PlayerObj*);
static u32 frames[247], frames_before[247];
static POLY_FT4 primitives[3], primitives_expected[3];
static DR_TPAGE modes[3], modes_expected[3];
static P_TAG sentinel, sentinel_expected;
static P_TAG* tails_before[2][4][8];
static struct BackgroundObj backgrounds_before[3];
static u32 render(u32 row)
{
    struct PlayerObj player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.armor_parts = 4;
    engine_obj.arm_type = 1;
    g_Player.active = 1;
    g_Player.on_screen = 1;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.armor_parts = 4;
    g_Player.arm_type = 1;
    g_Player.unk40 = 0x500;
    g_Player.unk42 = 0x7800;
    g_Player.unk16 = 2;
    g_Player.x_pos.i.hi = 160;
    g_Player.y_pos.i.hi = 120;
    g_Player.animation_table = (u32**)D_80119DF0;
    set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    background_objects[0].x_pos.val = background_objects[0].y_pos.val = 0;
    memset(frames, 0, sizeof(frames));
    frames[7] = 32;
    frames[8] = 0x00ED0002;
    frames[245] = 0xFBED0B00;
    frames[246] = 0xF9000C00;
    TEST_SPRITE_FRAMES = (u8*)frames;
    memset(primitives, 0xA5, sizeof(primitives));
    memset(modes, 0x5A, sizeof(modes));
    memset(&sentinel, 0, sizeof(sentinel));
    memcpy(primitives_expected, primitives, sizeof(primitives));
    memcpy(modes_expected, modes, sizeof(modes));
    sentinel_expected = sentinel;
    setaddr(&sentinel_expected, &modes[0]);
    for (i = 0; i < 2; i++) {
        POLY_FT4* p = &primitives_expected[i];
        setlen(p, 3);
        setcode(p, 0x7D);
        p->clut = 0x7843;
        p->x0 = i ? 160 : 141;
        p->y0 = i ? 113 : 115;
        p->u0 = i ? 0xC0 : 0xB0;
        p->v0 = 0;
        setaddr(p, &modes[i + 1]);
        setlen(&modes_expected[i], 1);
        modes_expected[i].code[0] = 0xE1000025;
        setaddr(&modes_expected[i], &primitives[i]);
    }
    memcpy(tails_before, D_8013BC40, sizeof(tails_before));
    D_8013BC40[0][0][2] = &sentinel;
    tails_before[0][0][2] = (P_TAG*)&primitives[1];
    SP_DRAW_BUFFER = 0;
    SP_PRIM_CURSOR = primitives;
    SP_DRAW_MODE_CURSOR = modes;
    player = g_Player;
    engine = engine_obj;
    memcpy(frames_before, frames, sizeof(frames));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    cur_random = 0x1234;
    func_800257BC(&g_Player);
    c_test_same_words(primitives, primitives_expected, sizeof(primitives));
    c_test_same_words(modes, modes_expected, sizeof(modes));
    c_test_same_words(&sentinel, &sentinel_expected, sizeof(sentinel));
    assert(c_test_word_difference((u32*)D_8013BC40, (u32*)tails_before, sizeof(tails_before) / 4) == 0);
    assert(c_test_word_difference(frames, frames_before, COUNT(frames)) == 0);
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(SP_DRAW_BUFFER == 0 && SP_PRIM_CURSOR == &primitives[2] && SP_DRAW_MODE_CURSOR == &modes[2] && TEST_SPRITE_FRAMES == (u8*)frames && cur_random == 0x1234);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "actual_X_stock_buster_arm_upgrade_own_idle_two_original_US_armor_sprites", NULL, NULL, 1, render } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
