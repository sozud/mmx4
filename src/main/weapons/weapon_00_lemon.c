// WeaponObj, weapon_object_update_funcs[0, 12, 23, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]
// 800922D8..80092648
#include "common.h"

void lemon_update(struct WeaponObj* arg0)
{
    lemon_state_funcs[arg0->state](arg0);
}

void lemon_init(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    arg0->active = 0x21;
    arg0->on_screen = 1;
    arg0->unk50 = (const u8*)lemon_hit_box;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    arg0->animation_table = D_8011BF40;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7802;
    arg0->unk16 = 0;
    owner = arg0->owner;
    arg0->unk15 = owner->unk15;
    arg0->unk84.word = 0;
    buster_shot_follow_muzzle(WEAPON_OBJECT(arg0));
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(6.75);
    } else {
        arg0->x_vel.val = FIXED(-6.75);
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    set_animation(arg0, 0x15);
    func_8001540C(1, 8, arg0);
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0xC, 8);
}

void lemon_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0xC, 8) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->unk98 == 0) {
            buster_shot_launch(ANIMATED_OBJECT(arg0));
            update_on_screen(BASE_OBJECT(arg0), 0xC, 8);
            return;
        }
        lemon_deflect(arg0);
        return;
    }
    buster_shot_hide(arg0);
}

void buster_shot_launch(struct AnimatedObj* arg0)
{
    if (arg0->unk5 == 0) {
        buster_shot_follow_muzzle(WEAPON_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            arg0->unk5++;
        }
    } else {
        move_object(MOVING_OBJECT(arg0));
    }
}
void lemon_deflect(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    if (arg0->unk98 > 0) {
        buster_shot_hide(arg0);
        return;
    }
    arg0->x_vel.val = -arg0->x_vel.val;
    if (get_random() & 1) {
        arg0->y_vel.val = FIXED(4.05) - 1;
    } else {
        arg0->y_vel.val = -(FIXED(4.05) - 1);
    }

    arg0->unk15 ^= 0x40;
    arg0->state = 2;
    arg0->unk5 = 0;
    update_on_screen(BASE_OBJECT(arg0), 0xC, 8);
}

void lemon_deflected(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0xC, 8) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        move_object(MOVING_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0xC, 8);
        return;
    }
    buster_shot_hide(arg0);
}

void buster_shot_hide(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}

void buster_shot_despawn(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    owner = arg0->owner;
    arg0->unk50 = 0;
    owner->shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*lemon_state_funcs[])(struct WeaponObj*) = {
    lemon_init,
    lemon_main,
    lemon_deflected,
    buster_shot_despawn,
};
