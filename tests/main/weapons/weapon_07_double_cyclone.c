#include "test_runtime.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/weapons/weapon_07_double_cyclone.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern s32 player_gfx_buf_0[1024];

static const u32 double_cyclone_update_expected[] = { 0x10200u };
static u32 test_double_cyclone_update(u32 row)
{
    u32 observed_values[1];
    struct WeaponObj obj, before;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));

    memset(&player_gfx_buf_0, 0, sizeof(player_gfx_buf_0));
    memset(&player_gfx_buf_1, 0, sizeof(player_gfx_buf_1));
#ifndef MMX4_SATURN
    memset(&vram_rect_ptr, 0, sizeof(vram_rect_ptr));
#endif
    g_Player.input_locked = 0;
    g_Player.capsule_state = -1;
    g_Player.weapon = 0;
    g_Player.shot_type = 16;
    obj.state = 0;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    obj.active = 0x41;
    obj.id = 7;
    obj.unk2 = 1;
    obj.on_screen = 1;
    obj.unk5 = 5;
    obj.unk6 = 6;
    obj.unk7 = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.unk50 = &obj;
    before = obj;
    player_before = g_Player;
    double_cyclone_update(&obj);
    before.active = before.id = before.unk2 = before.on_screen = 0;
    before.state = before.unk5 = before.unk6 = before.unk7 = 0;
    before.unk50 = NULL;
    --player_before.shot_count;
    --player_before.special_shot_count;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u8)obj.state | ((u32)(u8)g_Player.shot_count << 8) | ((u32)(u8)g_Player.special_shot_count << 16) | ((u32)(u8)obj.active << 24);
    return c_test_observe(0, row, observed_values, double_cyclone_update_expected, 1);
}

#include "support/charged_dispatch.h"
CHARGED_BASIC(3)
CHARGED_CASE(3, 4)
CHARGED_CASE(3, 5)
CHARGED_CASE(3, 6)
static const CTestCase double_cyclone_charged_dispatch_cases[] = { CHARGED_BASIC_ENTRIES(3) CHARGED_ENTRIES(3, 4) CHARGED_ENTRIES(3, 5) CHARGED_ENTRIES(3, 6) };

static const u32 double_cyclone_charged_dispatch_cases_expected[] = { 0x10391u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x504u };
static u32 cyclone_paths(u32 index);
const struct CTestGroup c_test_groups[] = {
    { "cyclone_paths", 0, 0, 20, cyclone_paths },
    { "double_cyclone_update", 0, 0, 1, test_double_cyclone_update },
    { "double_cyclone_charged_dispatch", double_cyclone_charged_dispatch_cases, double_cyclone_charged_dispatch_cases_expected, COUNT(double_cyclone_charged_dispatch_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(double_cyclone_charged_dispatch_cases) + 20;

#include "main/55C4.h"
#include "support/player_gfx_archive.h"
void double_cyclone_main(struct WeaponObj*);
void double_cyclone_form(struct WeaponObj*);
void double_cyclone_fly(struct WeaponObj*);
void double_cyclone_spin(struct WeaponObj*);
void double_cyclone_dissipate(struct WeaponObj*);
void func_80096EA4(struct WeaponObj*);
void func_80097430(struct WeaponObj*);
void double_cyclone_charged_main(struct WeaponObj*);
void double_cyclone_charged_offscreen(struct WeaponObj*);
extern union AnimationStep* D_8011C0F0[5];
extern struct Unk_unk68 double_cyclone_hit_box[];
static struct {
    u32 root[9];
    u32 bank[256];
    u16 stream[24];
} cyclone_gfx;
static s32 cyclone_frames[0x12];
#ifdef MMX4_SATURN
#define UPLOAD_Y(y) 0
#else
#define UPLOAD_Y(y) (y)
#endif
static u32 upload_y(void)
{
#ifdef MMX4_SATURN
    return 0;
#else
    return vram_rect_ptr == vram_rect_ptrs ? 0 : (u16)vram_rect_ptrs[0].rect.y;
#endif
}
static u32 cyclone_paths(u32 index)
{
    static const u8 scenarios[] = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 15, 17, 18, 20, 21, 22, 23 };
    u32 row = scenarios[index];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    GFX_QUEUE_RESET();
    gfx_archive_fill();
    memcpy(cyclone_gfx.bank, gfx_archive.bank, sizeof(cyclone_gfx.bank) + sizeof(cyclone_gfx.stream));
    cyclone_gfx.root[8] = 0x24;
    TEST_PLAYER_GFX = (u8*)&cyclone_gfx;
    TEST_SPRITE_FRAMES = (u8*)cyclone_frames;
    memset(D_8013E198, -1, sizeof(D_8013E198));
    g_Player.weapon = 7;
    g_Player.hp = 16;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    g_Player.x_pos.i.hi = 100;
    g_Player.y_pos.i.hi = 100;
    obj.active = 0x41;
    obj.id = 7;
    obj.state = 1;
    obj.unk5 = 1;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.unk38 = (u8*)cyclone_gfx.bank;
    obj.animation_table = D_8011C0F0;
    set_animation(&obj, 1);
    obj.previous_animation_index = obj.animation_step.fields.frame_index;
    obj.unk50 = double_cyclone_hit_box;
    obj.ext.weapon_7.timer = 5;
    switch (row) {
    case 0:
    case 1:
        g_Player.input_locked = row == 0;
        obj.ext.weapon_7.unk91 = 3;
        double_cyclone_update(&obj);
        assert(obj.active == (row == 0 ? 0 : 0x41) && g_Player.shot_count == (row == 0 ? 2 : 3));
        assert(obj.ext.weapon_7.unk91 == (row == 0 ? 3 : 2));
        break;
    case 2:
    case 3:
        obj.state = 0;
        obj.unk2 = row == 3;
        g_Player.unk15 = row == 3 ? PLAYER_FACING_RIGHT : 0;
        func_80096EA4(&obj);
        assert(obj.state == 1 && obj.ext.weapon_7.timer == 0x23 && obj.ext.weapon_7.unk90 == 8);
        assert(obj.x_pos.i.hi == (row == 2 ? 100 - 0x11 : 100 - 0x1A) && obj.y_pos.i.hi == 100 - 7);
        assert(obj.x_vel.val == -0x26000 && obj.unk15 == 0);
        assert(obj.unk40 == (row == 2 ? WEAPON_TEXTURE_SPECIAL_0 : WEAPON_TEXTURE_SPECIAL_1));
        assert(upload_y() == UPLOAD_Y(row == 2 ? 0x20 : 0x30));
        break;
    case 4:
    case 6:
    case 7:
        obj.ext.weapon_7.unk91 = row == 4 ? 0 : 3;
        obj.unk64 = 1;
        if (row == 6)
            obj.unk50 = NULL;
        if (row == 7)
            obj.x_pos.i.hi = 0x400;
        double_cyclone_main(&obj);
        assert(obj.state == (row == 7 ? 3 : 1) && obj.unk64 == (row == 4 ? 2 : 1));
        assert(obj.ext.weapon_7.unk91 == (row == 4 ? 4 : 3));
        assert(row == 7 ? obj.unk50 == NULL && obj.on_screen == 0 : obj.ext.weapon_7.timer == 4);
        break;
    case 8:
    case 9:
        obj.unk5 = 0;
        set_animation(&obj, 0);
        obj.previous_animation_index = obj.animation_step.fields.frame_index;
        obj.animation_step.fields.duration = 2;
        obj.animation_step.fields.relative_step = row == 8 ? 0 : 1;
        double_cyclone_form(&obj);
        assert(obj.unk5 == (row == 8) && obj.unk17 == (row == 8));
        break;
    case 10:
    case 11:
    case 12:
    case 13:
        obj.ext.weapon_7.timer = row == 10 ? 0 : 5;
        obj.unk98 = row == 11;
        obj.ext.weapon_7.unk90 = row == 12 ? 1 : row == 13 ? 2
                                                           : 0;
        obj.x_vel.val = -0x26000;
        double_cyclone_fly(&obj);
        assert(obj.unk5 == (row == 10 ? 3 : row == 11 ? 2
                                                      : 1)
            && obj.unk98 == 0);
        assert(obj.unk50 == (row == 10 ? NULL : double_cyclone_hit_box) && obj.unk17 == (row == 10 ? 2 : 1));
        assert(obj.ext.weapon_7.unk90 == (row == 13 ? 1 : 0));
        assert(obj.unk2C == (row == 12 ? -0x3700 : 0));
        assert(obj.x_pos.val == (row <= 11 ? 100 << 16 : (100 << 16) - 0x26000));
        break;
    case 15:
        obj.unk5 = 2;
        obj.ext.weapon_7.timer = 0;
        double_cyclone_spin(&obj);
        assert(obj.unk5 == 3 && obj.ext.weapon_7.timer == 0 && obj.unk17 == 2);
        break;
    case 17:
    case 18:
        obj.unk5 = 3;
        obj.animation_step.fields.duration = 2;
        obj.animation_step.fields.relative_step = row == 17 ? 0 : 1;
        double_cyclone_dissipate(&obj);
        assert(obj.state == (row == 17 ? 3 : 1) && obj.on_screen == (row == 17 ? 0 : 1));
        break;
    case 20:
        obj.unk2 = 1;
        obj.unk5 = 2;
        obj.previous_animation_index = 0xFF;
        double_cyclone_spin(&obj);
        assert(upload_y() == UPLOAD_Y(0x30) && obj.ext.weapon_7.timer == 4);
        assert(obj.previous_animation_index == GFX_DECODED_FRAME(obj.animation_step.fields.frame_index));
        break;
    case 21:
        obj.state = 0;
        obj.unk2 = 0x82;
        func_80097430(&obj);
        assert(obj.state == 1 && obj.unk15 == PLAYER_FACING_RIGHT && obj.x_vel.val == 0x60000);
        assert(obj.x_pos.i.hi == 100 + 0x1F && obj.ext.weapon_16.delay == 8 && obj.unk17 == 4);
        break;
    case 22:
        obj.unk2 = 0;
        obj.ext.weapon_16.timer = 5;
        obj.x_pos.i.hi = 0x400;
        obj.previous_animation_index = 0xFF;
        double_cyclone_charged_main(&obj);
        assert(obj.state == 2 && obj.unk50 == NULL && obj.on_screen == 0);
        assert(upload_y() == UPLOAD_Y(0x30));
        break;
    default:
        obj.state = 2;
        obj.unk2 = 1;
        obj.ext.weapon_16.timer = 5;
        obj.animation_step.fields.duration = 2;
        double_cyclone_charged_offscreen(&obj);
        assert(obj.state == 2 && obj.ext.weapon_16.timer == 4 && obj.animation_step.fields.duration == 1);
        break;
    }
    return 1;
}
