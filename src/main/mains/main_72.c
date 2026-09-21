// MainObj, main_object_update_funcs[72]
// 8008ADFC..8008BA38
#include "common.h"

void func_8008ADFC(struct MainObj* arg0)
{
    s32 x_pos;
    s32 y_pos;

    x_pos = arg0->x_pos.val;
    y_pos = arg0->y_pos.val;
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk5C = 0x18;
    arg0->unk60 = 6;
    arg0->animation_table = (const u8* const*)D_80104E7C;
    arg0->unk54 = (const u8*)&D_80104F00;
    arg0->unk50 = (const u8*)&D_80104F00;
    arg0->unk68 = &D_80104F04;
    arg0->collision_data = (const u16*)D_80108184;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk7C = 0;
    arg0->on_screen = 0;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 5;
    arg0->unk18.val = x_pos;
    arg0->unk1C.val = y_pos;
}

void func_8008AE94(struct MainObj* arg0)
{
    if ((arg0->x_pos.val - g_Player.x_pos.val) < 0) {
        arg0->unk15 = 0x40;
        return;
    }

    arg0->unk15 = 0;
}

void func_8008AEC4(struct BaseObj* arg0, s8 arg1)
{
    arg0->unk5 = arg1;
    arg0->unk6 = 0;
}

void func_8008AED0(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
}

void func_8008AEE8(struct MainObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->unk20 = FIXED(1.375);
    } else {
        arg0->unk20 = FIXED(-1.375);
    }
}

void func_8008AF10(struct MainObj* arg0)
{
    s32 value;

    value = arg0->ext.main_72.unk84 << 8;
    if (arg0->unk15 == 0) {
        value = -value;
    }
    arg0->unk20 = value;
}

void func_8008AF30(struct MainObj* arg0, s32 arg1)
{
    s32 v;
    struct ShotObj* obj = find_free_shot_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x2F;
        obj->unk2 = arg1;
        obj->x_pos.i.hi = arg0->x_pos.i.hi;
        obj->y_pos.i.hi = arg0->y_pos.i.hi;
        obj->animation_table = arg0->animation_table;
        obj->unk40 = arg0->unk40;
        obj->unk3C = arg0->sprite_frames;
        v = (u8)func_8002938C(0x48);
        obj->unk42 = SOME_COORDINATE_CONVERSION(v);
        obj->unk16 = arg0->unk16;
        obj->unk7C = arg0;
        obj->unk15 = arg0->unk15;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B020);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B188);

void func_8008B270(struct MainObj* arg0)
{
    s8 state;
    u8 timer1;
    u8 timer2;

    state = arg0->unk6;
    if (state == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 8);
        arg0->ext.main_72.lifetime = 0x40;
        arg0->ext.main_72.spawn_timer = 0x10;
        func_8008AE94(arg0);
        func_8001540C(2, 0x4C, arg0);
    }

    timer1 = arg0->ext.main_72.lifetime - 1;
    arg0->ext.main_72.lifetime = timer1;
    if (timer1 != 0) {
        timer2 = arg0->ext.main_72.spawn_timer - 1;
        arg0->ext.main_72.spawn_timer = timer2;
        if (timer2 == 0) {
            func_8008AF30(arg0, 0);
            arg0->ext.main_72.spawn_timer = 0x10;
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        func_8008AEC4(BASE_OBJECT(arg0), 2);
    }
}

void func_8008B33C(struct MainObj* self)
{
    s8 state;

    state = self->unk6;
    if (state == 0) {
        self->unk6 = state + 1;
        func_8008AE94(self);
        self->unk24 = FIXED(5.5);
        self->unk2C = FIXED(0.2578125);
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk67 = 1;
        func_80015D60(self, 2);
        self->unk70 &= 0xF7;
        func_8001540C(2, 0x48, self);
    }
    self->unk20 = 0;
    func_8008AF10(self);
    if (!(self->unk70 & 4) && self->unk24 >= 0 && self->y_pos.i.hi - g_Player.y_pos.i.hi >= 0) {
        func_8002B694(ANIMATED_OBJECT(self));
        return;
    }
    func_8008AEC4(BASE_OBJECT(self), 2);
}

void func_8008B42C(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6++;
        arg0->unk67 = 0;
        func_80015D60(arg0, 4);
        arg0->unk70 |= 8;
        func_8001540C(2, 0x45, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_8008AEC4(BASE_OBJECT(arg0), 7);
        return;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B4B8);

void func_8008B5C0(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk67 = 1;
        func_80015D60(arg0, 3);
    }
    if (arg0->unk70 & 8) {
        func_8008AEC4(BASE_OBJECT(arg0), 5);
        return;
    }
    if ((arg0->y_pos.i.hi - g_Player.y_pos.i.hi) >= -0x30) {
        func_8008AEC4(BASE_OBJECT(arg0), 2);
        return;
    }
    arg0->unk20 = 0;
    func_8008AF10(arg0);
    if (arg0->unk24 < FIXED(-5.875)) {
        arg0->unk24 = FIXED(-5.875);
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B69C);

void func_8008B7D4(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 9);
        arg0->ext.main_72.lifetime = 0x80;
        arg0->ext.main_72.spawn_timer = 0x30;
        func_8008AE94(arg0);
        func_8001540C(2, 0x4C, arg0);
    }

    if (--arg0->ext.main_72.lifetime != 0) {
        if ((--arg0->ext.main_72.spawn_timer & 0xF) != 0) {
            func_8008AF30(arg0, 1);
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        func_8008AEC4(BASE_OBJECT(arg0), 2);
    }
}

void func_8008B898(struct MainObj* arg0)
{
    func_8008AEC4(BASE_OBJECT(arg0), 2);
}

void func_8008B8B8(struct MainObj* self)
{
    s32 result;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    D_80104F10[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    func_8002D9BC(self);
    result = func_8002DD04(self);
    if (result < 0) {
        func_800C813C(7, D_80104F08, self);
        self->state = 2;
        self->unk5 = 0;
    } else if (result != 0) {
        func_80089B58(VISUAL_OBJECT(self), 8);
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 2;
    self->unk5 = 0;
}

void func_8008B984(struct MainObj* arg0)
{
    arg0->unk42 &= 0x7FFF;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8008B9B0(void)
{
}

void func_8008B9B8(void)
{
}

void func_8008B9C0(struct MainObj* arg0)
{
    D_80104F3C[arg0->unk5](arg0);
}

void func_8008B9FC(struct MainObj* arg0)
{
    D_80104F48[arg0->state](arg0);
}
