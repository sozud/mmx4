// MainObj, main_object_update_funcs[76]
// 800919C4..800922D8
#include "common.h"

void func_800919C4(struct MainObj* arg0)
{
    D_80105FB4[arg0->state](arg0);
}

void func_80091A00(struct MainObj* arg0)
{
    struct MainObj* self = arg0;

    self->state = 1;
    self->unk5C = 3;
    self->unk60 = 4;
    self->animation_table = (const u8* const*)D_80105F90;
    self->unk54 = D_80105FB0;
    self->unk50 = D_80105FAC;
    self->unk68 = (struct Unk_unk68*)D_80105FA8;
    self->collision_data = D_80108484;
    self->unk20 = FIXED(2);
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7C = 0;
    self->unk7E = 0;
    self->bg_offset = 0;
    self->unk61 = 0;
    self->unk67 = 0;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk16 = 5;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->ext.main_76.saved_x_velocity = self->unk20;
    func_80015D60(self, 0);
}

void func_80091AC4(struct MainObj* arg0)
{
    if (arg0->unk70 & 8) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk7C = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = arg0->ext.main_76.saved_x_velocity;
        return;
    }

    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091B1C);

void func_80091C64(struct MainObj* arg0)
{
    s16 object_y;
    s16 player_y;
    s16 current_timer;
    s16 new_timer;
    s32 distance;
    s32 velocity;

    object_y = arg0->y_pos.u.hi - 8;
    player_y = g_Player.y_pos.i.hi;
    distance = player_y - object_y;

    if (distance >= 0) {
        if (distance < 0x10) {
            goto close_range;
        }
        goto far_range;
    }
    if ((object_y - player_y) < 0x10) {
        goto close_range;
    }
    goto far_range;

close_range:
    velocity = arg0->unk20;
    if (velocity < 0) {
        velocity = FIXED(-4);
    } else {
        velocity = FIXED(4);
    }
    arg0->unk20 = velocity;
    new_timer = 0x78;
    goto store_timer;

far_range:
    current_timer = arg0->unk7E;
    if (current_timer == 0) {
        if (arg0->unk20 < 0) {
            arg0->unk20 = FIXED(-2);
        } else {
            arg0->unk20 = FIXED(2);
        }
        return;
    }
    new_timer = current_timer - 1;

store_timer:
    arg0->unk7E = new_timer;
}

void func_80091D1C(struct MainObj* self)
{
    s32 collision;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->on_screen = 0;

    if (self->unk5 == 0) {
        if (self->unk7C != 0) {
            self->unk7C--;
        }
        func_80091C64(self);
        if (self->unk7C == 0) {
            func_80091B1C(self);
        }
    } else {
        func_80091AC4(self);
    }

    CollisionRelated(PLAYER_OBJECT(self));
    collision = func_8002DD04(self);
    if (collision < 0) {
        func_800AF808(BASE_OBJECT(self));
        func_800C813C(4, D_80105FA4, self);
        self->state = 2;
        return;
    }

    if (collision != 0) {
        self->unk7C = 0x3C;
    }
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 2;
    }
}

void func_80091E18(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80091E38(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6++;
        arg0->unk61 = 0x28;
    }
    if (arg0->unk61 & 7) {
        arg0->unk42 &= 0x7FFF;
    } else {
        arg0->unk42 |= 0x8000;
    }
    if (--arg0->unk61 == 0) {
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091EC4);

extern s32 D_80105FC0[2];

void func_80091FC8(struct MainObj* self)
{
    s8 step;
    s32 speed;

    step = self->unk6;
    if (step == 0) {
        self->unk6 = step + 1;
        if (g_Player.x_pos.val < self->x_pos.val) {
            self->unk20 = D_80105FC0[self->unk63 - 5];
        } else {
            self->unk20 = -D_80105FC0[self->unk63 - 5];
        }
        self->unk28 = 0x3000;
        self->unk24 = 0;
        self->unk2C = 0;
        if (self->unk63 == 5) {
            self->unk61 = 0x12;
        } else {
            self->unk61 = 1;
        }
    }

    func_8002B694(ANIMATED_OBJECT(self));

    speed = self->unk20;
    if (speed < 0) {
        speed = -speed;
    }
    if (speed < 0x6000) {
        self->unk20 = 0;
        self->unk28 = 0;
    }
    if (self->unk70 & 3) {
        self->unk20 = 0;
        self->unk28 = 0;
    }

    if ((s8)self->unk61 % 9 != 0) {
        self->unk42 &= 0x7FFF;
    } else {
        self->unk42 |= 0x8000;
    }

    self->unk61--;
    if (self->unk61 == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk42 &= 0x7FFF;
    }
}

void func_8009216C(void* arg0)
{
    struct Main76HandlerTable handlers = D_80010D7C;
    struct MainObj* object = arg0;

    handlers.funcs[object->unk63](arg0);
}

union AnimationStep D_80105F40[16] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0FF10002 },
};

union AnimationStep D_80105F80[1] = { { 0x10000002 } };

union AnimationStep D_80105F84[1] = { { 0x11000002 } };

union AnimationStep D_80105F88[1] = { { 0x12000002 } };

union AnimationStep D_80105F8C[1] = { { 0x13000002 } };

union AnimationStep* D_80105F90[5] = {
    D_80105F40,
    D_80105F80,
    D_80105F84,
    D_80105F88,
    D_80105F8C,
};

u8 D_80105FA4[4] = { 1, 2, 3, 4 };

s8 D_80105FA8[4] = { -1, 0, 11, 11 };

s8 D_80105FAC[4] = { -9, -6, 16, 15 };

s8 D_80105FB0[4] = { -11, -8, 20, 18 };

const struct Main76HandlerTable D_80010D7C = { {
    NULL,
    (void (*)(void*))func_80091E38,
    NULL,
    (void (*)(void*))func_80091EC4,
    (void (*)(void*))func_80091EC4,
    (void (*)(void*))func_80091FC8,
    (void (*)(void*))func_80091FC8,
} };

void func_800921E8(s32 arg0)
{
    u32 object_id;
    u32 random_value;
    s8 value;

#ifndef VERSION_JP
    object_id = arg0 & 0xFF;
    if (object_id >= 8U) {
#endif
        random_value = get_random() & 0xFF;
        random_value %= 3U;
#ifdef VERSION_JP
        object_id = arg0 & 0xFF;
#endif
        func_8001663C(D_80105FC8[object_id][random_value & 0xFF], 0x7F);
        value = 1;
#ifndef VERSION_JP
    } else {
        value = 0x3C;
    }
#endif
    engine_obj.unk36.value = value;
}

s32 func_8009227C(void)
{
#ifdef VERSION_JP
    if (D_80173C84 == 0) {
        engine_obj.unk36.timer = 0;
        func_8001653C();
    }
#else
    if ((D_80173C84 == 0) && (engine_obj.unk36.timer != 0)) {
        engine_obj.unk36.timer--;
        if (engine_obj.unk36.timer == 0) {
            engine_obj.unk36.timer = 0;
            func_8001653C();
        }
    }
#endif
    return engine_obj.unk36.timer;
}

void (*D_80105FB4[])(struct MainObj*) = {
    func_80091A00,
    func_80091D1C,
    func_80091E18,
};

s32 D_80105FC0[2] = { FIXED(3), FIXED(10) };

u8 D_80105FC8[13][3] = {
    { 0x4F, 0x4F, 0x3F },
    { 0x45, 0x3C, 0x46 },
    { 0x35, 0x37, 0x36 },
    { 0x2A, 0x2B, 0x30 },
    { 0x34, 0x3A, 0x3D },
    { 0x29, 0x33, 0x39 },
    { 0x4B, 0x44, 0x4E },
    { 0x41, 0x38, 0x2D },
    { 0x2E, 0x31, 0x3B },
    { 0x2F, 0x2C, 0x28 },
    { 0x4D, 0x4C, 0x49 },
    { 0x42, 0x43, 0x32 },
    { 0x48, 0x4A, 0x40 },
};

u8 D_80105FEF_padding = 0;
