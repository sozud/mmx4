// WeaponObj, weapon_object_update_funcs[19]
// 800927EC..800929A0
#include "common.h"

void stock_shot_update(struct WeaponObj* arg0)
{
    stock_shot_state_funcs[arg0->state](arg0);
}

void stock_shot_init(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    arg0->active = 0x21;
    arg0->on_screen = 1;
    arg0->unk50 = (const u8*)stock_shot_hit_box;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    arg0->animation_table = D_8011BF40;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7802;
    arg0->unk16 = 1;
    owner = arg0->owner;
    arg0->unk15 = owner->unk15;
    arg0->unk84.word = 0;
    buster_shot_follow_muzzle(WEAPON_OBJECT(arg0));
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(10);
    } else {
        arg0->x_vel.val = FIXED(-10);
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    set_animation(arg0, 0x18);
    func_8001540C(1, 9, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x1A, 0x12);
}

void stock_shot_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x1A, 0x12) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->unk98 == 0) {
            buster_shot_launch(ANIMATED_OBJECT(arg0));
            update_on_screen(BASE_OBJECT(arg0), 0x1A, 0x12);
            return;
        }
        buster_shot_hide(arg0);
        return;
    }
    arg0->on_screen = 0;
    arg0->state = 3;
}

void (*stock_shot_state_funcs[])(struct WeaponObj*) = {
    stock_shot_init,
    stock_shot_main,
    buster_shot_despawn,
    buster_shot_despawn,
};
