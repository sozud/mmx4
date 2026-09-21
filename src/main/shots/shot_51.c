// ShotObj, shot_object_update_funcs[51]
// 800AA5E0..800AAAD4
#include "common.h"

void (*D_80109C04[])(struct ShotObj*) = {
    func_800AA20C,
    func_800AA5E0,
    func_800AA68C,
    func_800AA730,
    func_800AA7B4,
    func_800AA85C,
    func_800AA954,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_51", func_800AA5E0);

INCLUDE_ASM("main/nonmatchings/shots/shot_51", func_800AA68C);

void func_800AA730(struct ShotObj* arg0)
{
    s32 angle;
    u16 player_x;

    arg0->timer = 0x3C;
    arg0->unk5++;
    player_x = g_Player.x_pos.u.hi;
    arg0->unk8C.half = player_x;
    angle = func_8002B810(arg0->x_pos.val - (player_x << 16), 0);
    arg0->unk84.value = angle;
    if (angle & 0x10) {
        arg0->x_vel.val = FIXED(-8);
    } else {
        arg0->x_vel.val = FIXED(8);
    }
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    func_80015DC8(arg0);
}

void func_800AA7B4(struct ShotObj* arg0)
{
    s32 angle;

    angle = func_8002B810(arg0->x_pos.val - (arg0->unk8C.halves[0] << 16), 0);
    if ((angle ^ arg0->unk84.value) & 0x10) {
        arg0->unk5++;
        arg0->x_pos.val = arg0->unk8C.halves[0] << 16;
        arg0->y_pos.val = arg0->unk8C.halves[1] << 16;
        func_80015D60(arg0, 0x16);
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
    }
    arg0->unk84.value = angle & 0xFF;
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800AA85C(struct ShotObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.relative_step == 0) {
        self->timer = 0x3C;
        self->unk5++;
        func_80015D90(ANIMATED_OBJECT(self), 0x15, 7);
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

    func_80015DC8(ANIMATED_OBJECT(self));
}

void func_800AA954(struct ShotObj* arg0)
{
    arg0->timer--;
    if (arg0->timer == 0) {
        arg0->unk5 = 3;
    }
    func_80015DC8(arg0);
}

void func_800AA994(struct ShotObj* arg0)
{
    extern u8 D_80109BB4[];

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109C04[arg0->unk5](arg0);
    if (arg0->unk7C->state == 2) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_80109BB4, arg0);
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_80109BB4, arg0);
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 2;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->on_screen = 0;
}

void func_800AAA98(struct ShotObj* arg0)
{
    D_80109C20[arg0->state](arg0);
}

void (*D_80109C20[])(struct ShotObj*) = {
    func_800AA148,
    func_800AA994,
    func_800A9D98,
};
