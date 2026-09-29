// ShotObj, shot_object_update_funcs[27]
// 8009F240..8009F46C
#include "common.h"

u8 jump_shooter_shot_hit_box[4] = { 0xFD, 0xFD, 5, 5 };
s8 jump_shooter_shot_muzzle_offsets[20] = {
    2,
    -0x16,
    -0x0D,
    -0x19,
    -0x12,
    -0x11,
    -0x12,
    -5,
    -0x0C,
    5,
    2,
    -0x1D,
    -9,
    -0x1E,
    -0x12,
    -0x17,
    -0x15,
    -0x0B,
    -0x0C,
    -3,
};

void jump_shooter_shot_update(struct ShotObj* self)
{
    jump_shooter_shot_state_funcs[self->state](self);
}

// jump_shooter_shot_init
INCLUDE_ASM("main/nonmatchings/shots/shot_27_jump_shooter_shot", func_8009F27C);

void jump_shooter_shot_fly(struct ShotObj* self)
{
    struct ShotObj* shot = self;

    animate_object(ANIMATED_OBJECT(shot));
    move_object(MOVING_OBJECT(shot));
    func_8002D9BC(shot);
    if (func_8002BB80(MAIN_OBJECT(shot), MAIN_OBJECT(&g_Player)) == 0) {
        if (func_8002DD04(MAIN_OBJECT(shot)) < 0) {
            spawn_explosion(BASE_OBJECT(shot));
            shot->state = 2;
        }
        if (func_8002B1E8(BASE_OBJECT(shot), 0x20, 0x20) == 0) {
            update_on_screen(BASE_OBJECT(shot), 0x10, 0x10);
            return;
        }
    }
    shot->state = 2;
}

void jump_shooter_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*jump_shooter_shot_state_funcs[])(struct ShotObj*) = {
    func_8009F27C,
    jump_shooter_shot_fly,
    jump_shooter_shot_despawn,
};
