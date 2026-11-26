#include "test_runtime.h"
#include "main/weapons/weapon_00_lemon.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/sprite_animations.h"

void lemon_init(struct WeaponObj*);
void lemon_main(struct WeaponObj*);
void lemon_deflect(struct WeaponObj*);
void lemon_deflected(struct WeaponObj*);
static s32 lemon_frames[4];

static u32 lemon_paths(u32 row)
{
    struct WeaponObj obj;
    u32 seed;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memset(D_8013E198, -1, sizeof(D_8013E198));
    TEST_SPRITE_FRAMES = (u8*)lemon_frames;
    obj.active = 0x21;
    obj.id = 0;
    obj.state = 1;
    obj.owner = &g_Player;
    obj.unk84.word = 1;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.x_vel.val = 0x6C000;
    obj.animation_table = D_8011BF40;
    set_animation(&obj, 0x15);
    obj.animation_step.fields.duration = 2;
    obj.unk50 = (const u8*)lemon_frames;
    switch (row) {
    case 0:
    case 1:
        obj.state = 0;
        g_Player.unk15 = row == 0 ? PLAYER_FACING_RIGHT : 0;
        lemon_init(&obj);
        assert(obj.state == 1 && obj.unk15 == g_Player.unk15 && obj.x_vel.val == (row == 0 ? 0x6C000 : -0x6C000));
        assert(obj.unk84.word == 1 && obj.unk17 == 0x15);
        break;
    case 2:
    case 3:
        obj.animation_step.fields.event = row == 2;
        lemon_main(&obj);
        assert(obj.unk5 == (row == 2) && obj.animation_step.fields.event == 0 && obj.x_pos.i.hi == 100);
        break;
    case 4:
    case 5:
        if (row == 4)
            obj.x_pos.i.hi = 0x400;
        obj.unk98 = row == 5;
        lemon_main(&obj);
        assert(obj.state == 3 && obj.unk50 == NULL && obj.on_screen == 0);
        break;
    case 6:
    case 7:
        for (seed = 0;; seed++) {
            cur_random = seed;
            if ((get_random() & 1) == (row == 6))
                break;
        }
        cur_random = seed;
        obj.unk98 = -1;
        lemon_deflect(&obj);
        assert(obj.state == 2 && obj.unk50 == NULL && obj.x_vel.val == -0x6C000 && obj.unk15 == PLAYER_FACING_RIGHT);
        assert(obj.y_vel.val == (row == 6 ? 0x40CCB : -0x40CCB));
        break;
    default:
        obj.state = 2;
        if (row == 9)
            obj.x_pos.i.hi = 0x400;
        lemon_deflected(&obj);
        assert(obj.state == (row == 8 ? 2 : 3) && obj.x_pos.i.hi == (row == 8 ? 106 : 0x400));
        break;
    }
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "lemon_paths", 0, 0, 10, lemon_paths },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 10;
