// ShotObj, shot_object_update_funcs[55]
// 800AC8C4..800ADF30
#include "common.h"

s8 D_80109E04[3][4] = {
    { 0, -2, 32, 16 },
    { 15, -13, 32, 24 },
    { -36, -16, 43, 33 },
};

u8 D_80109E10[8] = { 40, 41, 42, 43, 44, 45, 0, 0 };

s8 D_80109E18[3][4] = {
    { -19, -3, 36, 4 },
    { -10, -9, 18, 16 },
    { -99, 53, -60, 38 },
};

s16 D_80109E24[4] = { 0x208, 0x238, 0x268, 0x290 };

u8 D_80109E2C[4] = { 2, 3, 0, 1 };

void (*D_80109E30[])(struct ShotObj*) = {
    func_800ACD84,
    func_800ACDE4,
    func_800ACE90,
    func_800ACF60,
    func_800AD00C,
    func_800AD080,
    func_800AD12C,
    func_800AD1B0,
    func_800AD224,
    func_800AD338,
    func_800AD404,
};

void (*D_80109E5C[])(struct ShotObj*) = {
    func_800AD47C,
    func_800AD4DC,
    func_800AD538,
    func_800ACF60,
    func_800AD00C,
    func_800AD080,
    func_800AD12C,
    func_800AD1B0,
    func_800AD224,
};

void (*D_80109E80[])(struct ShotObj*) = {
    func_800AD338,
    func_800AD404,
    func_800AD630,
    func_800AD440,
};

s8 D_80109E90[4] = { -63, -40, 13, -40 };

void (*D_80109E94[])(struct ShotObj*) = {
    func_800AD6DC,
    func_800AD820,
};

void (*D_80109E9C[])(struct ShotObj*) = {
    func_800AD8C0,
    func_800AD92C,
    func_800AD9C4,
};

void (*D_80109EA8[])(struct ShotObj*) = {
    func_800ADBE0,
    func_800ADCE8,
    func_800ADD40,
    func_800ADDB4,
};

void (*D_80109EB8[])(struct ShotObj*) = {
    func_800ACD04,
    func_800ACCAC,
    func_800AD66C,
    func_800AD66C,
    func_800AD868,
    func_800AD868,
    func_800ADA0C,
    func_800ADA0C,
    func_800ADA64,
    func_800ADAD8,
    func_800ADE04,
    func_800ADE04,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AC8C4);

void func_800ACCAC(struct ShotObj* arg0)
{
    if (arg0->unk5 == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
        return;
    }

    arg0->state++;
    func_800C813C(6, D_80109E10, arg0);
}

void func_800ACD04(struct ShotObj* arg0)
{
    struct WeaponObj* weapon = arg0->unk7C;

    arg0->on_screen = 0;
    arg0->x_pos.u.hi = weapon->x_pos.u.hi + arg0->unk84.halves[0];
    arg0->y_pos.u.hi = weapon->y_pos.u.hi + arg0->unk84.halves[1];
    arg0->unk15 = weapon->unk15;
    if (arg0->timer != 0) {
        func_80015DC8(arg0);
        func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
    }
}

void func_800ACD84(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk6 == 3) {
        arg0->unk5++;
        func_80015D60(arg0, 0x13);
        func_8001540C(2, 6, arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ACDE4);

void func_800ACE90(struct ShotObj* arg0)
{
    s32 velocity;

    func_8002B93C(MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0), FIXED(3616), D_80109E24[arg0->timer] << 16) & 0xFF);
    arg0->x_vel.val *= 4;
    arg0->y_vel.val *= 4;
    if (func_800AC848(arg0, 0xE20, D_80109E24[arg0->timer]) & 0xFF) {
        velocity = FIXED(-1.5);
        arg0->y_vel.val = 0;
        arg0->unk5++;
        if (arg0->unk15 != 0) {
            velocity = FIXED(1.5);
        }
        arg0->x_vel.val = velocity;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800ACF60);

void func_800AD00C(struct ShotObj* arg0)
{
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    temp_v0 = arg0->unk90.u.lo - 1;
    arg0->unk90.i.lo = temp_v0;
    if (temp_v0 == 0) {
        arg0->unk5++;
        if (arg0->unk2 == 3) {
            func_80015D60(arg0, 0x16);
        } else {
            func_80015D60(arg0, 0x11);
        }
    }
}

void func_800AD080(struct ShotObj* arg0)
{
    s32 velocity;
    u8 direction;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        velocity = FIXED(-1.5);
        arg0->animation_step.fields.event = 0;
        direction = arg0->unk15 ^ 0x40;
        arg0->unk15 = direction;
        if (direction != 0) {
            velocity = FIXED(1.5);
        }
        arg0->x_vel.val = velocity;
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5++;
        if (arg0->unk2 == 3) {
            func_80015D60(arg0, 0xF);
        } else {
            func_80015D60(arg0, 0x14);
        }
        func_8001540C(2, 5, arg0);
    }
}

void func_800AD12C(struct ShotObj* arg0)
{
    s16 x_pos;
    s16 target_x_pos;
    s32 delta;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));

    x_pos = arg0->x_pos.i.hi;
    target_x_pos = arg0->unk7C->x_pos.i.hi;
    delta = x_pos - target_x_pos;
    if (delta >= 0 ? delta < 0x30 : (target_x_pos - x_pos) < 0x30) {
        arg0->x_vel.val = 0;
        arg0->unk90.u.lo = 0x3C;
        arg0->unk5++;
    }
}

void func_800AD1B0(struct ShotObj* arg0)
{
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    temp_v0 = arg0->unk90.u.lo - 1;
    arg0->unk90.i.lo = temp_v0;
    if (temp_v0 == 0) {
        arg0->unk5++;
        if (arg0->unk2 == 3) {
            func_80015D60(arg0, 0x11);
        } else {
            func_80015D60(arg0, 0x16);
        }
    }
}

void func_800AD224(struct ShotObj* self)
{
    s16 timer;
    s32 x_velocity;
    struct WeaponObj* owner;
    u8 direction;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        x_velocity = FIXED(-1.5);
        self->animation_step.fields.event = 0;
        direction = self->unk15 ^ 0x40;
        self->unk15 = direction;
        if (direction != 0) {
            x_velocity = FIXED(1.5);
        }
        self->x_vel.val = x_velocity;
    }
    if (self->animation_step.fields.relative_step == 0) {
        timer = (u16)self->unk8A + 1;
        self->unk8A = timer;
        if (timer == 2) {
            self->unk5++;
            if (self->unk2 == 3) {
                owner = self->unk7C;
                owner->unk6++;
                func_80015D60(self, 0x15);
                return;
            }
            func_80015D60(self, 0x10);
            return;
        }
        self->unk5 = 3;
        if (self->unk2 == 3) {
            func_80015D60(self, 0x14);
        } else {
            func_80015D60(self, 0xF);
        }
        func_8001540C(2, 5, self);
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD338);

void func_800AD404(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->timer = 0x80;
    }
}

void func_800AD440(struct ShotObj* arg0)
{
    D_80109E30[arg0->unk5](arg0);
}

void func_800AD47C(struct ShotObj* arg0)
{
    if (arg0->unk8C.object->unk5 == 3) {
        arg0->unk5++;
        func_80015D60(arg0, 0xE);
        func_8001540C(2, 6, arg0);
    }
}

void func_800AD4DC(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5++;
        func_80015D60(arg0, 0xF);
        func_8001540C(2, 5, arg0);
    }
}

void func_800AD538(struct ShotObj* self)
{
    s32 velocity;

    func_8002B93C(
        MOVING_OBJECT(self),
        func_8002B7B0(
            OBJECT_HEADER(self), FIXED(3616),
            D_80109E24[D_80109E2C[SHOT_OBJECT(self->unk8C.object)->timer]]
                << 16)
            & 0xFF);
    self->x_vel.val *= 4;
    self->y_vel.val *= 4;
    if (func_800AC848(
            self, 0xE20,
            D_80109E24[D_80109E2C[SHOT_OBJECT(self->unk8C.object)->timer]])
        & 0xFF) {
        velocity = FIXED(-1.5);
        self->y_vel.val = 0;
        self->unk5 = (u8)self->unk5 + 1;
        if (self->unk15 != 0) {
            velocity = FIXED(1.5);
        }
        self->x_vel.val = velocity;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
}

void func_800AD630(struct ShotObj* arg0)
{
    D_80109E5C[arg0->unk5](arg0);
}

void func_800AD66C(struct ShotObj* arg0)
{
    D_80109E80[arg0->unk2](arg0);
    arg0->unk42 = arg0->unk7C->unk42;
    func_8002E184(PLAYER_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_55", func_800AD6DC);

void func_800AD820(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002B160(BASE_OBJECT(arg0)) == 1) {
        arg0->state = 2;
    }
}

void func_800AD868(struct ShotObj* arg0)
{
    D_80109E94[arg0->unk5](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
}

void func_800AD8C0(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->timer = 0x19;
        arg0->unk5++;
        if (arg0->unk2 == 6) {
            func_80015D60(arg0, 0x19);
        } else {
            func_80015D60(arg0, 0x1C);
        }
    }
}

void func_800AD92C(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        arg0->unk50.data = (u8*)&D_80109E18[2];
        arg0->timer--;
    }
    if (arg0->timer == 0) {
        arg0->unk50.data = NULL;
        arg0->unk5++;
        if (arg0->unk2 == 6) {
            func_80015D60(arg0, 0x1A);
        } else {
            func_80015D60(arg0, 0x1D);
        }
    }
}

void func_800AD9C4(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state++;
    }
}

void func_800ADA0C(struct ShotObj* arg0)
{
    D_80109E9C[arg0->unk5](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0xA0, 0xA0);
}

void func_800ADA64(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    arg0->x_pos.val = weapon->x_pos.val;
    arg0->y_pos.val = weapon->y_pos.val;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (weapon->ext.shot_55.unk90 == 0) {
        arg0->state++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800ADAD8(struct ShotObj* arg0)
{
    u8 i;
    struct ShotObj* shot;
    struct WeaponObj* owner;

    if (arg0->unk5 == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.relative_step == 0) {
            i = 0;
            owner = arg0->unk7C;
            arg0->unk5 = (u8)arg0->unk5 + 1;
            do {
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x37;
                    shot->unk2 = i + 0xA;
                    shot->timer = 0;
                    shot->unk7C = owner;
                    shot->unk84.halves[0] = arg0->x_pos.u.hi - owner->x_pos.u.hi;
                    shot->unk84.halves[1] = arg0->y_pos.u.hi - owner->y_pos.u.hi;
                    func_8001540C(2, 4, arg0);
                }
                i++;
            } while (i < 2);
        }
    } else {
        arg0->state = (u8)arg0->state + 1;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800ADBE0(struct ShotObj* arg0)
{
    struct ShotObj* shot;
    struct WeaponObj* owner;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk8A != 0) {
        func_8002B718(MOVING_OBJECT(arg0));
        arg0->unk8A = (u16)arg0->unk8A - 1;
        return;
    }
    owner = arg0->unk7C;
    arg0->unk5 = (u8)arg0->unk5 + 1;
    func_80015D60(arg0, 0x20);
    arg0->unk50.data = (u8*)D_80109E18;
    if (arg0->timer < 2) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = (u8)arg0->unk2;
            shot->timer = (u16)arg0->timer + 1;
            shot->unk7C = arg0->unk7C;
            shot->unk84.halves[0] = arg0->x_pos.u.hi - owner->x_pos.u.hi;
            shot->unk84.halves[1] = arg0->y_pos.u.hi - owner->y_pos.u.hi;
        }
    } else {
        owner->ext.shot_55.unk92 = 1;
    }
}

void func_800ADCE8(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (weapon->ext.shot_55.unk92 != 0) {
        arg0->unk8A = 0x14;
        arg0->unk5++;
    }
}

void func_800ADD40(struct ShotObj* arg0)
{
    s16 timer;
    s32 velocity;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk8A - 1;
    arg0->unk8A = timer;
    velocity = FIXED(-5);
    if ((timer << 0x10) == 0) {
        arg0->unk5 = (u8)arg0->unk5 + 1;
        if (arg0->unk15 != 0) {
            velocity = FIXED(5);
        }
        arg0->x_vel.val = velocity;
        arg0->y_vel.val = 0;
        func_8001540C(2, 4, arg0);
    }
}

void func_800ADDB4(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x50, 0x30) == 1) {
        arg0->state = 2;
    }
}

void func_800ADE04(struct ShotObj* arg0)
{
    D_80109EA8[arg0->unk5](arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800ADE54(struct ShotObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8002DD04(MAIN_OBJECT(arg0));
    D_80109EB8[arg0->unk2](arg0);
    func_8002D9BC(arg0);
    if (arg0->unk7C->state == 2) {
        arg0->state = 2;
    }
}

void func_800ADED4(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800ADEF4(struct ShotObj* arg0)
{
    D_80109EE8[arg0->state](arg0);
}

void (*D_80109EE8[])(struct ShotObj*) = {
    func_800AC8C4,
    func_800ADE54,
    func_800ADED4,
};
