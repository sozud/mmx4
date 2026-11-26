#include "test_runtime.h"
#include "main/weapons/weapon_20_plasma_shot.h"
#include "main/55C4.h"
#include "main/sprite_animations.h"

void plasma_shot_main(struct WeaponObj*);
void plasma_orb_linger(struct WeaponObj*);
static s32 plasma_frames[0x10];

static u32 plasma_paths(u32 row)
{
    struct WeaponObj obj;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    TEST_SPRITE_FRAMES = (u8*)plasma_frames;
    g_Player.x_pos.i.hi = 100;
    g_Player.y_pos.i.hi = 100;
    g_Player.shot_count = 1;
    obj.active = 0x21;
    obj.id = row == 1 || row >= 8 ? 0x14 : 0x15;
    obj.state = 1;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.unk64 = 1;
    obj.animation_table = D_8011BF40;
    set_animation(&obj, 0x1E);
    obj.animation_step.fields.duration = 2;
    obj.animation_step.fields.relative_step = 1;
    obj.ext.weapon_20.lifetime = 5;
    obj.ext.weapon_20.timer = 2;
    obj.unk50 = (const u8*)plasma_frames;
    switch (row) {
    case 0:
    case 1:
        obj.state = 0;
        func_800929DC(&obj);
        assert(obj.state == 1 && obj.unk17 == (row == 0 ? 0x1E : 0x1D) && obj.unk64 == (row == 0 ? 2 : 1));
        assert(obj.x_vel.val == (row == 0 ? 0 : -0xB0000) && obj.ext.weapon_20.lifetime == (row == 0 ? 0x5A : 5));
        break;
    case 2:
    case 3:
        if (row == 2)
            obj.x_pos.i.hi = 0x400;
        obj.ext.weapon_20.lifetime = 0;
        plasma_shot_main(&obj);
        assert(obj.state == (row == 2 ? 3 : 1) && obj.unk5 == (row == 3) && obj.unk17 == (row == 3 ? 0x1F : 0x1E));
        assert((obj.unk50 == NULL) == (row == 3 || row == 2));
        break;
    case 4:
    case 5:
        obj.ext.weapon_20.timer = row == 4 ? 0 : 2;
        plasma_orb_linger(&obj);
        assert(obj.ext.weapon_20.lifetime == 4 && obj.ext.weapon_20.timer == (row == 4 ? 4 : 1));
        assert(obj.unk64 == (row == 4 ? 2 : 1));
        break;
    case 6:
    case 7:
        obj.unk5 = 1;
        obj.animation_step.fields.relative_step = row == 7;
        plasma_orb_linger(&obj);
        assert(obj.state == (row == 6 ? 3 : 1) && obj.on_screen == (row == 7));
        break;
    case 8:
    case 9:
    case 10:
        obj.x_vel.val = 0xB0000;
        obj.unk98 = row != 8;
        g_Player.shot_count = row == 9 ? 4 : 1;
        func_80092B5C(&obj);
        assert(obj.unk98 == 0 && obj.x_pos.i.hi == 111);
        assert(weapon_objects[0].active == (row == 10 ? 0x21 : 0) && g_Player.shot_count == (row == 9 ? 4 : row == 10 ? 2 : 1));
        assert(row != 10 || (weapon_objects[0].id == 0x15 && weapon_objects[0].x_pos.val == obj.x_pos.val));
        break;
    default:
        obj.unk84.word = row == 11;
        obj.owner = &g_Player;
        g_Player.attacking = 1;
        g_Player.unk15 = row == 13 ? PLAYER_FACING_RIGHT : 0;
        obj.x_pos.i.hi = 50;
        buster_shot_follow_muzzle(&obj);
        assert(obj.unk84.word == (row != 12));
        assert(row == 12 ? obj.x_pos.i.hi != 50 : obj.x_pos.i.hi == 50);
        break;
    }
    for (i = 1; i < COUNT(weapon_objects); i++)
        assert(weapon_objects[i].active == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "plasma_paths", 0, 0, 14, plasma_paths },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 14;
