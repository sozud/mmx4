#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/shots/shot_43_gunship_shot.h"
#include "main/collision_bounds.h"
#include "main/mains/main_67_gunship.h"
#include "main/55C4.h"

static struct MainObj gunship_owner;
#define ss state_room.shot
#define GUN(st) (state_reset(0, 0, 0), memset(&gunship_owner, 0, sizeof(gunship_owner)), gunship_owner.x_pos.i.hi = 0x100, gunship_owner.y_pos.i.hi = 0x80, ss.state = st, ss.unk7C = (struct WeaponObj*)&gunship_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define HOMING() (state_extra = ss.unk90.bytes[0] | ss.unk90.bytes[1] << 8 | (u32)(u16)ss.unk8C.word << 16)
static void gs_init(u8 kind, u8 facing)
{
    GUN(0);
    ss.unk2 = kind;
    ss.unk15 = facing;
    gunship_shot_update(&ss);
    HOMING();
}
static void gs_bullet_top(void) { gs_init(0, 0); }
static void gs_bullet_low_right(void) { gs_init(1, 0x40); }
static void gs_missile_a(void) { gs_init(2, 0); }
static void gs_missile_b(void) { gs_init(3, 0); }
static void gs_missile_c(void) { gs_init(4, 0); }
static void gs_missile_d(void) { gs_init(5, 0); }
static void gs_fly_smoke(void)
{
    GUN(2);
    cur_random = 1;
    gunship_shot_update(&ss);
    HOMING();
}
static void gs_fly(void)
{
    GUN(2);
    ss.unk7 = 2;
    ss.x_vel.val = -0x28000;
    gunship_shot_update(&ss);
}
static void gs_fly_away(void)
{
    GUN(2);
    ss.unk7 = 2;
    ss.x_pos.i.hi = 0x1000;
    gunship_shot_update(&ss);
}
static void gs_fly_shot(void)
{
    GUN(2);
    ss.unk7 = 2;
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    gunship_shot_update(&ss);
}
static void gs_home_wait(void)
{
    GUN(2);
    ss.unk7 = 2;
    ss.unk8C.word = 3;
    ss.unk90.bytes[1] = 2;
    gunship_shot_update(&ss);
    HOMING();
}
static void gs_home(u8 heading, s16 px, s16 py)
{
    GUN(2);
    ss.unk7 = 2;
    ss.unk8C.word = 3;
    ss.unk90.bytes[0] = heading;
    g_Player.x_pos.i.hi = px;
    g_Player.y_pos.i.hi = py;
    gunship_shot_update(&ss);
    HOMING();
}
static void gs_home_ahead(void) { gs_home(0x0C, 0x80, 0x60 + 0x40); }
static void gs_home_cw(void) { gs_home(0x02, 0x80 - 0x40, 0x60 + 0x40); }
static void gs_home_ccw(void) { gs_home(0x1C, 0x80 + 0x40, 0x60); }
static void gs_home_wrap(void) { gs_home(0x01, 0x80 - 0x40, 0x60 - 0x40); }
static void gs_home_back(void) { gs_home(0x14, 0x80 + 0x40, 0x60 + 0x40); }
static void gs_home_back_wrap(void) { gs_home(0x1E, 0x80 + 0x40, 0x60 - 0x08); }

static void (*const gunship_shot_states_cases[])(void) = {
    gs_bullet_top,
    gs_bullet_low_right,
    gs_missile_a,
    gs_missile_b,
    gs_missile_c,
    gs_missile_d,
    gs_fly_smoke,
    gs_fly,
    gs_fly_away,
    gs_fly_shot,
    gs_home_wait,
    gs_home_ahead,
    gs_home_cw,
    gs_home_ccw,
    gs_home_wrap,
    gs_home_back,
    gs_home_back_wrap,
};
static const u32 gunship_shot_states_expected[] = { 1u, 0xFF000000u, 0xBB0000u, 0x660000u, 0xFFFC0000u, 0u, 0u, 0x50000u, 0u, 0u, 1u, 0xFF400100u, 0x1450000u, 0x770000u, 0x40000u, 0u, 0u, 0x50000u, 0u, 0u, 0x2000002u, 0xFF000200u, 0x1140000u, 0x590000u, 0xFFFD8000u, 0x28000u, 0u, 0x50000u, 0x5A140Cu, 0u, 0x2000002u, 0xFF000300u, 0x1080000u, 0x670000u, 0xFFFD8000u, 0x28000u, 0u, 0x50000u, 0x5A140Cu, 0u, 0x2000002u, 0xFF000400u, 0x1080000u, 0x4D0000u, 0xFFFD8000u, 0x28000u, 0u, 0x50000u, 0x5A140Cu, 0u, 0x2000002u, 0xFF000500u, 0x1140000u, 0x400000u, 0xFFFD8000u, 0x28000u, 0u, 0x50000u, 0x5A140Cu, 0u, 0x2000002u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x21000000u, 0x1000002u, 0u, 0x7D8000u, 0x600000u, 0xFFFD8000u, 0u, 0u, 0x40000u, 0u, 0u, 0x1000003u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x2000003u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x2100u, 0x1000002u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x20100u, 0u, 0x1000002u, 0xFF000000u, 0x800000u, 0x600000u, 0xFFFCAC94u, 0x238E4u, 0u, 0x50000u, 0x2010Du, 0u, 0x1000002u, 0xFF000000u, 0x800000u, 0x600000u, 0x3EC50u, 0xC7C4u, 0u, 0x50000u, 0x20101u, 0u, 0x1000002u, 0xFF000000u, 0x800000u, 0x600000u, 0x3536Cu, 0xFFFDC71Cu, 0u, 0x50000u, 0x2011Du, 0u, 0x1000002u, 0xFF000000u, 0x800000u, 0x600000u, 0x3B20Cu, 0x187DCu, 0u, 0x50000u, 0x20102u, 0u, 0x1000002u, 0xFF000000u, 0x800000u, 0x600000u, 0xFFFDC71Cu, 0xFFFCAC94u, 0u, 0x50000u, 0x20115u, 0u, 0x1000002u, 0xFF000000u, 0x800000u, 0x600000u, 0x3EC50u, 0xFFFF383Cu, 0u, 0x50000u, 0x2011Fu, 0u };

static u32 test_gunship_shot_states(u32 row)
{
    return object_run(gunship_shot_states_cases[row], row, &gunship_shot_states_expected[row * 10]);
}

#define ss state_room.shot
#define HOME(timer, cur, px, py) (state_reset(0, 0, 0), ss.active = 1, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x80, ss.unk90.bytes[0] = cur, ss.unk90.bytes[1] = timer, g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, func_800A6DF4(&ss), state_extra = ss.unk90.bytes[0] | ss.unk90.bytes[1] << 8)
static void gh_wait(void)
{
    HOME(2, 0, 0x80, 0x40);
}
static void gh_turn_up(void) { HOME(0, 0, 0x80, 0x40); }
static void gh_turn_down(void) { HOME(0, 0, 0x80, 0xC0); }
static void gh_near_up(void) { HOME(0, 7, 0x80, 0x40); }
static void gh_back_up(void) { HOME(0, 0x10, 0x80, 0x40); }
static void gh_wrap_up(void) { HOME(0, 0x1F, 0x80, 0x40); }
static void gh_near_down(void) { HOME(0, 9, 0x80, 0x40); }
static void gh_locked(void) { HOME(0, 8, 0x80, 0x40); }

static void (*const gunship_homing_cases[])(void) = {
    gh_wait,
    gh_turn_up,
    gh_turn_down,
    gh_near_up,
    gh_back_up,
    gh_wrap_up,
    gh_near_down,
    gh_locked,
};
static const u32 gunship_homing_expected[] = { 0u, 1u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x100u, 0u, 0u, 0xFF000001u, 0x800000u, 0x800000u, 0x3EC50u, 0xC7C4u, 0u, 0x50000u, 0x101u, 0u, 0u, 0xFF000001u, 0x800000u, 0x800000u, 0x3EC50u, 0xFFFF383Cu, 0u, 0x50000u, 0x11Fu, 0u, 0u, 1u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x107u, 0u, 0u, 0xFF000001u, 0x800000u, 0x800000u, 0xFFFC13B0u, 0xC7C4u, 0u, 0x50000u, 0x10Fu, 0u, 0u, 0xFF000001u, 0x800000u, 0x800000u, 0x40000u, 0u, 0u, 0x50000u, 0x100u, 0u, 0u, 1u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x109u, 0u, 0u, 1u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x108u, 0u };

static u32 test_gunship_homing(u32 row)
{
    return object_run(gunship_homing_cases[row], row, &gunship_homing_expected[row * 10]);
}

void gunship_shot_missile_fly(struct ShotObj*);
extern u8 gunship_shot_missile_hit_box[4];
static struct Unk_unk68 player_bounds = { 0, 0, 12, 24 };
static struct MiscObj misc_before[64];
static struct VisualObj visuals_before[32];
static struct WeaponObj weapons_before[16];
static u32 missile(u32 row)
{
    struct ShotObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 hit = row % 2, armor = row / 2 % 2, face = row / 4 % 2, layer = row / 8, i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    for (i = 0; i < 32; i++)
        visual_objects[i].active = 1;
    c_test_copy_words((u32*)misc_before, (u32*)misc_objects, sizeof(misc_before) / 4);
    c_test_copy_words((u32*)visuals_before, (u32*)visual_objects, sizeof(visuals_before) / 4);
    c_test_copy_words((u32*)weapons_before, (u32*)weapon_objects, sizeof(weapons_before) / 4);
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    obj.active = 0x41;
    obj.id = 43;
    obj.unk2 = 2;
    obj.state = 2;
    obj.on_screen = 1;
    obj.unk60 = 6;
    obj.unk5C = 1;
    obj.bg_offset = layer;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk50.data = obj.unk54 = gunship_shot_missile_hit_box;
    obj.unk58.data = (u8*)D_80105FF0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = face ? 0x28000 : -0x28000;
    obj.y_vel.val = 0x28000;
    obj.animation_table = (u32**)gunship_animations;
    set_animation(&obj, 5);
    assert(obj.animation_step.packed == 0x0E010001);
    expected = obj;
    expected.x_pos.val += obj.x_vel.val;
    expected.y_pos.val -= obj.y_vel.val;
    expected.animation_cursor++;
    expected.animation_step.packed = 0x0F010001;
    g_Player.hp = 30;
    g_Player.armor_parts = armor ? 2 : 0;
    g_Player.unk54 = (const u32*)&player_bounds;
    g_Player.unk15 = obj.unk15;
    g_Player.stun_timer = 3;
    g_Player.x_pos = expected.x_pos;
    g_Player.y_pos = expected.y_pos;
    if (!hit)
        g_Player.x_pos.i.hi += 100;
    player_expected = g_Player;
    if (hit) {
        player_expected.hp = (armor ? 26 : 24) | 0x80;
        player_expected.hurt_type = armor ? 4 : 2;
        player_expected.stun_timer = 0;
        if (armor)
            player_expected.weapon_energy[0] = 6;
        expected.state = 3;
    } else
        expected.unk7 = 2;
    cur_random = 0x1234;
    gunship_shot_missile_fly(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((u32*)misc_objects, (u32*)misc_before, sizeof(misc_before) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals_before, sizeof(visuals_before) / 4) == 0 && c_test_word_difference((u32*)weapon_objects, (u32*)weapons_before, sizeof(weapons_before) / 4) == 0 && cur_random == (hit ? 0x366A : 0x1234));
    assert(player_bounds.unk0 == 0 && player_bounds.unk1 == 0 && player_bounds.unk2 == 12 && player_bounds.unk3 == 24);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "gunship_homing", 0, 0, COUNT(gunship_homing_cases), test_gunship_homing },
    { "gunship_shot_states", 0, 0, COUNT(gunship_shot_states_cases), test_gunship_shot_states },
    { "real_missile_contact_armor_and_full_smoke_explosion_pools", NULL, NULL, 24, missile },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(gunship_homing_cases) + COUNT(gunship_shot_states_cases) + 24;
