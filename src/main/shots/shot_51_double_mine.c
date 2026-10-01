// ShotObj, shot_object_update_funcs[51]
// 800AA5E0..800AAAD4
#include "common.h"

void (*double_mine_step_funcs[])(struct ShotObj*) = {
    double_toss_land,
    func_800AA5E0,
    func_800AA68C,
    double_mine_dash_start,
    double_mine_dash,
    double_mine_fire,
    double_mine_cooldown,
};

// double_mine_wait
INCLUDE_ASM("main/nonmatchings/shots/shot_51_double_mine", func_800AA5E0);

// double_mine_arm
INCLUDE_ASM("main/nonmatchings/shots/shot_51_double_mine", func_800AA68C);

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_51_double_mine", double_mine_dash_start);
#else
void double_mine_dash_start(struct ShotObj* self)
{
    s32 angle;

    self->timer = 0x3C;
    self->unk5++;
    self->unk8C.half = g_Player.x_pos.u.hi;
    angle = angle_from_delta(self->x_pos.val - (self->unk8C.half << 16), 0);
    self->unk84.value = angle;
    if (angle & 0x10) {
        self->x_vel.val = FIXED(-8);
    } else {
        self->x_vel.val = FIXED(8);
    }
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    animate_object(self);
}
#endif

void double_mine_dash(struct ShotObj* self)
{
    u8 angle;

    angle = angle_from_delta(self->x_pos.val - (self->unk8C.halves[0] << 16), 0);
    if ((angle ^ self->unk84.value) & 0x10) {
        self->unk5++;
        self->x_pos.val = self->unk8C.halves[0] << 16;
        self->y_pos.val = self->unk8C.halves[1] << 16;
        set_animation(self, 0x16);
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    self->unk84.value = angle & 0xFF;
    animate_object(ANIMATED_OBJECT(self));
}

void double_mine_fire(struct ShotObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.relative_step == 0) {
        self->unk5++;
        self->timer = 0x3C;
        set_animation_frame(ANIMATED_OBJECT(self), 0x15, 7);
        return;
    }

    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x34;
            shot->unk2 = 0;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->animation_table = self->animation_table;
            shot->unk40 = self->unk40;
            shot->unk3C = self->unk3C;
            shot->unk42 = self->unk42 & 0x7FFF;
            shot->unk16 = self->unk16;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk15 = self->unk15;
        }
    }

    animate_object(ANIMATED_OBJECT(self));
}

void double_mine_cooldown(struct ShotObj* self)
{
    self->timer--;
    if (self->timer == 0) {
        self->unk5 = 3;
    }
    animate_object(self);
}

void double_mine_main(struct ShotObj* self)
{
    extern u8 double_ball_debris_1[];

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    double_mine_step_funcs[self->unk5](self);
    if (self->unk7C->state == 2) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, double_ball_debris_1, self);
        self->state = 2;
        self->on_screen = 0;
        return;
    }
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, double_ball_debris_1, self);
        self->state = 2;
        self->on_screen = 0;
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 2;
    self->unk5 = 0;
    self->unk6 = 0;
    self->on_screen = 0;
}

void double_mine_update(struct ShotObj* self)
{
    double_mine_state_funcs[self->state](self);
}

void (*double_mine_state_funcs[])(struct ShotObj*) = {
    double_toss_init,
    double_mine_main,
    double_ball_despawn,
};
