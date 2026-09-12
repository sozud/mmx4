// MainObj, main_object_update_funcs[10]
// 800498C8..8004A718
#include "common.h"

void dragonfly_update(struct MainObj* self)
{
    dragonfly_state_funcs[self->state](self);
}

void dragonfly_init(struct MainObj* self)
{
    self->unk5C = 6;
    self->unk60 = 3;
    self->unk61 = 0;
    self->collision_data = D_80106770;
    self->bg_offset = g_Player.bg_offset;
    self->unk16 = 6;
    self->animation_table = dragonfly_animations;
    self->unk68 = &D_800FAEFC;
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk67 = 0;
    self->unk54 = D_800FAEF0;
    self->unk50 = D_800FAEF0;
    self->unk62 = 0;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    func_80015D60(self, 0);

    switch (self->unk2) {
    case 0:
        if (self->x_pos.val > g_Player.x_pos.val) {
            self->unk15 = 0;
        } else {
            self->unk15 = 0x40;
        }
        self->ext.main_10.hold_state = 1;
        self->ext.main_10.can_grab = 1;
        break;
    case 1:
        self->unk7A = 1;
        self->unk15 = 0x40;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 1;
        break;
    case 2:
        self->unk7A = 1;
        self->unk15 = 0;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 1;
        break;
    case 3:
    case 4:
    case 9:
    case 10:
        self->unk7A = 1;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 0;
        break;
    case 5:
    case 6:
    case 11:
    case 12:
        self->unk7A = 1;
        self->unk2C = -0x600;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 0;
        break;
    case 7:
    case 8:
    case 13:
    case 14:
        self->unk7A = 1;
        self->unk2C = 0x600;
        self->ext.main_10.hold_state = 0;
        self->ext.main_10.can_grab = 0;
        break;
    }
    self->unk7C = 1;
    self->state = 1;
    self->ext.main_10.turn_delay = 0;
    self->unk5 = 2;
    self->unk6 = 0;
}

void dragonfly_run(struct MainObj* self)
{
    s8* held;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    dragonfly_step_funcs[self->unk5](self);
    if (self->ext.main_10.hold_state != 0) {
        if (self->ext.main_10.can_grab != 0) {
            held = &g_Player.unkBA;
            if ((*held == 0) && (func_8002D9BC(self) != 0) && (*held != 0)) {
                g_Player.unkA5 = self->unk15;
                self->ext.main_10.hold_state = 3;
            }
        }
        self->ext.main_10.saved_unk5 = self->unk5;
        if (func_8002DD04(self) < 0) {
            func_800AF808(self);
            func_800C813C(6, &D_800FB0EC, self);
            func_800BF60C(self, 0x11);
            self->state = 2;
        } else if (func_8002B1E8(self, 0x40, 0x40) == 0) {
            func_8002B318(self, 0x20, 0x20);
            if (--self->unk7C == 0) {
                func_8001540C(2, 0xD, self);
                self->unk7C = 0x3C;
            }
        } else {
            self->state = 2;
        }
    }
}

void dragonfly_finish(struct MainObj* self)
{
    self->unk7A = 0;
    self->unk62 = 0;
    func_80015930(2, 0xD);
    if (self->ext.main_10.hold_state == 3) {
        g_Player.unkBA = 0;
    }
    self->ext.main_10.timer = 0;
    self->ext.main_10.turn_delay = 0;
    self->ext.main_10.struggle = 0;
    self->ext.main_10.hold_state = 0;
    self->ext.main_10.can_grab = 0;
    self->ext.main_10.saved_unk5 = 0;
    self->state = 3;
}

void dragonfly_despawn(struct MainObj* self)
{
    if (self->unk2 < 3) {
        func_8002B0C8(OBJECT_HEADER(self));
        return;
    }
    func_8002B108(OBJECT_HEADER(self));
}

void dragonfly_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_10.saved_unk5;
}

void dragonfly_wait(struct MainObj* self)
{
    switch (self->unk2) {
    case 0:
        self->unk7A = 0;
        self->unk5 = 3;
        break;
    case 1:
        if (g_Player.x_pos.i.hi - self->x_pos.i.hi >= 0xC1) {
            self->ext.main_10.hold_state = 1;
            self->unk7A = 0;
            self->unk5 = 3;
        }
        break;
    case 2:
        if (self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0xC1) {
            self->ext.main_10.hold_state = 1;
            self->unk7A = 0;
            self->unk5 = 3;
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        if (g_Player.x_pos.i.hi - self->x_pos.i.hi >= 0xC1) {
            self->ext.main_10.hold_state = 1;
            self->unk7A = 0;
            self->unk15 = 0x40;
            if (!(self->unk2 & 1)) {
                self->unk20 = FIXED(8);
            } else {
                self->unk20 = FIXED(6);
            }
            self->unk5 = 6;
        }
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        self->unk7A = 0;
        self->unk15 = 0;
        self->ext.main_10.hold_state = 1;
        if (!(self->unk2 & 1)) {
            self->unk20 = FIXED(-8);
        } else {
            self->unk20 = FIXED(-6);
        }
        self->unk5 = 6;
    }
}

void dragonfly_hunt(struct MainObj* self)
{
    D_800FB120[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_10", func_80049E24);

INCLUDE_ASM("main/nonmatchings/mains/main_10", func_80049E68);

void dragonfly_hunt_hover(struct MainObj* self)
{
    if (self->ext.main_10.turn_delay == 0) {
        dragonfly_face_player(self);
    } else {
        self->ext.main_10.turn_delay--;
    }

    if (--self->ext.main_10.timer == 0) {
        if (get_random() & 1) {
            dragonfly_face_player(self);
            func_80015D60(self, 1);
            self->unk5 = 4;
            self->unk6 = 0;
            return;
        }

        if (g_Player.y_pos.i.hi - 0x18 < self->y_pos.i.hi) {
            self->unk24 = FIXED(3);
        } else {
            self->unk24 = FIXED(-3);
        }
        self->unk6 = 3;
    }

    func_80015DC8(self);
}

void dragonfly_hunt_close(struct MainObj* self)
{
    func_8002B718((struct MovingObj*)self);
    if (self->ext.main_10.turn_delay == 0) {
        dragonfly_face_player(self);
    } else {
        self->ext.main_10.turn_delay--;
    }
    if (self->unk24 < 0
            ? (g_Player.y_pos.i.hi - 0x18) < self->y_pos.i.hi
            : self->x_pos.i.hi < (g_Player.x_pos.i.hi - 0x18)) {
        dragonfly_face_player(self);
        func_80015D60(self, 1);
        self->unk5 = 4;
        self->unk6 = 0;
    }
    func_80015DC8(self);
}

void dragonfly_carry(struct MainObj* self)
{
    D_800FB130[self->unk6](self);
    CollisionRelated((struct PlayerObj*)self);
}

void dragonfly_carry_grab(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        dragonfly_face_player(self);
        self->unk50 = D_800FAEF8;
        self->unk62 = 3;
        self->unk60 = 0;
        func_80015D60(self, 2);
        self->unk6 = 1;
        self->ext.main_10.timer = 0xB4;
        return;
    }

    func_80015DC8(self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_10", func_8004A178);

void dragonfly_carry_lift(struct MainObj* self)
{
    dragonfly_hold_player(self);
    if (self->animation_step.fields.event != 0) {
        self->unk24 = FIXED(1.5);
        self->ext.main_10.timer = 0x32;
        self->ext.main_10.struggle = 0;
        self->unk6 = 3;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}
void dragonfly_carry_rise(struct MainObj* self)
{
    u32 timer;
    s32 struggle;

    dragonfly_hold_player(self);
    struggle = self->ext.main_10.struggle + func_8002BAA4();
    self->ext.main_10.struggle = struggle;
    if (struggle >= 0x15) {
        g_Player.unkBA = 0;
        self->unk50 = D_800FAEF0;
        self->unk62 = 0;
        func_80015D60(self, 5);
        self->unk24 = 0x20000;
        self->unk50 = NULL;
        self->unk5 = 5;
        self->unk6 = 0;
        return;
    }

    timer = self->ext.main_10.timer - 1;
    self->ext.main_10.timer = timer;
    if (timer == 0) {
        func_80015D60(self, 4);
        self->ext.main_10.timer = 0xA;
        self->unk7E = 1;
        self->unk24 = 0;
        self->unk6 = 4;
    } else {
        func_80015DC8(self);
    }

    if (!(func_8004A690(self) & 0xFF)) {
        func_8002B718(MOVING_OBJECT(self));
    }
}

void dragonfly_carry_squeeze(struct MainObj* self)
{
    s16 sound_timer;
    s32 struggle;
    u32 squeeze;

    sound_timer = (u16)self->unk7E - 1;
    self->unk7E = sound_timer;
    if (sound_timer == 0) {
        func_8001540C(2, 0xE, self);
        self->unk7E = 0x14;
    }

    dragonfly_hold_player(self);
    struggle = self->ext.main_10.struggle + func_8002BAA4();
    self->ext.main_10.struggle = struggle;
    if (struggle >= 0x15) {
        func_80015930(2, 0xE);
        g_Player.unkBA = 0;
        self->unk50 = NULL;
        self->unk62 = 0;
        func_80015D60(self, 5);
        self->unk24 = 0x20000;
        self->unk5 = 5;
        self->unk6 = 0;
        return;
    }

    if (self->animation_step.fields.event != 0) {
        squeeze = self->ext.main_10.timer - 1;
        self->ext.main_10.timer = squeeze;
        if (squeeze == 9 || squeeze == 4) {
            func_80036470(2);
        }
        if (self->ext.main_10.timer == 0) {
            func_80015930(2, 0xE);
            g_Player.unkBA = 0;
            self->unk62 = 0;
            func_80015D60(self, 5);
            self->unk24 = 0x20000;
            self->unk50 = NULL;
            self->unk5 = 5;
            self->unk6 = 0;
            return;
        }
    }

    func_80015DC8(self);
}

void dragonfly_flee(struct MainObj* self)
{
    func_8002B718((struct MovingObj*)self);
    func_80015DC8(self);
}

void dragonfly_face_player(struct MainObj* self)
{
    if (self->unk15 != 0) {
        if (self->x_pos.val > g_Player.x_pos.val) {
            self->unk15 = 0;
            self->ext.main_10.turn_delay = 0x10;
        }
    } else if (self->x_pos.val < g_Player.x_pos.val) {
        self->unk15 = 0x40;
        self->ext.main_10.turn_delay = 0x10;
    }
}

void dragonfly_hold_player(struct MainObj* self)
{
    g_Player.y_pos.i.hi = self->y_pos.i.hi + 0x18;
    if (self->unk15 == 0) {
        g_Player.x_pos.i.hi = self->x_pos.i.hi - 0x18;
    } else {
        g_Player.x_pos.i.hi = self->x_pos.i.hi + 0x18;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_10", func_8004A690);

void dragonfly_fly_past(struct MainObj* self)
{
    func_8002B694((struct AnimatedObj*)self);
    func_80015DC8(self);
}

u8 D_800FAEF0[8] = { 0xEE, 0xEC, 0x2A, 0x24, 0xD7, 0xEA, 0x3F, 0x35 };

u8 D_800FAEF8[4] = { 0xDB, 0x09, 0x20, 0x17 };

struct Unk_unk68 D_800FAEFC = { -24, 3, 0x0A, 0x02 };

u8 dragonfly_anim_0[0xC] = {
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0xFE,
    0x02,
};

u8 dragonfly_anim_1[0xF0] = {
    0x01,
    0x00,
    0x01,
    0x03,
    0x01,
    0x00,
    0x01,
    0x04,
    0x01,
    0x00,
    0x01,
    0x05,
    0x01,
    0x00,
    0x01,
    0x06,
    0x01,
    0x00,
    0x01,
    0x07,
    0x01,
    0x00,
    0x01,
    0x08,
    0x01,
    0x00,
    0x01,
    0x09,
    0x01,
    0x00,
    0x01,
    0x0A,
    0x01,
    0x00,
    0x01,
    0x0B,
    0x01,
    0x00,
    0x01,
    0x0C,
    0x01,
    0x00,
    0x01,
    0x0D,
    0x01,
    0x00,
    0x01,
    0x0E,
    0x01,
    0x00,
    0x01,
    0x0F,
    0x01,
    0x00,
    0x01,
    0x10,
    0x01,
    0x00,
    0x01,
    0x11,
    0x01,
    0x00,
    0x01,
    0x12,
    0x01,
    0x00,
    0x01,
    0x13,
    0x01,
    0x00,
    0x01,
    0x14,
    0x01,
    0x00,
    0x01,
    0x15,
    0x01,
    0x00,
    0x01,
    0x16,
    0x01,
    0x00,
    0x01,
    0x17,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x1B,
    0x01,
    0x00,
    0x01,
    0x1C,
    0x01,
    0x00,
    0x01,
    0x1D,
    0x01,
    0x00,
    0x01,
    0x1E,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x1F,
    0x01,
    0x00,
    0x01,
    0x20,
    0x01,
    0x00,
    0x01,
    0x21,
    0x01,
    0x00,
    0x01,
    0x22,
    0x01,
    0x00,
    0x01,
    0x23,
    0x01,
    0x00,
    0x01,
    0x24,
    0x01,
    0x00,
    0x01,
    0x25,
    0x01,
    0x00,
    0x01,
    0x26,
    0x01,
    0x00,
    0x01,
    0x27,
    0x01,
    0x00,
    0x01,
    0x28,
    0x01,
    0x00,
    0x01,
    0x29,
    0x01,
    0x00,
    0x01,
    0x2A,
    0x01,
    0x00,
    0x01,
    0x2B,
    0x01,
    0x00,
    0x01,
    0x2C,
    0x01,
    0x00,
    0x01,
    0x2D,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x01,
    0x00,
    0x1A,
};

u8 dragonfly_anim_2[0xC] = {
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x01,
    0xFE,
    0x1A,
};

u8 dragonfly_anim_3[0x3C] = {
    0x01,
    0x00,
    0x01,
    0x2E,
    0x01,
    0x00,
    0x01,
    0x2F,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x32,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x33,
    0x01,
    0x00,
    0x01,
    0x34,
    0x01,
    0x00,
    0x01,
    0x35,
    0x01,
    0x00,
    0x01,
    0x36,
    0x01,
    0x00,
    0x01,
    0x37,
    0x01,
    0x00,
    0x01,
    0x38,
    0x01,
    0x00,
    0x01,
    0x36,
    0x01,
    0x01,
    0xFE,
    0x37,
};

u8 dragonfly_anim_4[0x3C] = {
    0x01,
    0x00,
    0x01,
    0x37,
    0x01,
    0x00,
    0x01,
    0x39,
    0x01,
    0x00,
    0x01,
    0x3A,
    0x01,
    0x00,
    0x01,
    0x3B,
    0x01,
    0x00,
    0x01,
    0x3C,
    0x01,
    0x00,
    0x01,
    0x3D,
    0x01,
    0x00,
    0x01,
    0x3E,
    0x01,
    0x00,
    0x01,
    0x3F,
    0x01,
    0x00,
    0x01,
    0x40,
    0x01,
    0x00,
    0x01,
    0x41,
    0x01,
    0x00,
    0x01,
    0x42,
    0x01,
    0x00,
    0x01,
    0x43,
    0x01,
    0x00,
    0x01,
    0x44,
    0x01,
    0x00,
    0x01,
    0x45,
    0x01,
    0x01,
    0xF5,
    0x46,
};

u8 dragonfly_anim_5[0x24] = {
    0x01,
    0x00,
    0x01,
    0x34,
    0x01,
    0x00,
    0x01,
    0x35,
    0x01,
    0x00,
    0x01,
    0x33,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x32,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0xFE,
    0x19,
};

u8 dragonfly_anim_6[4] = { 0x01, 0x01, 0x00, 0x47 };
u8 dragonfly_anim_7[4] = { 0x01, 0x01, 0x00, 0x48 };
u8 dragonfly_anim_8[4] = { 0x01, 0x01, 0x00, 0x49 };
u8 dragonfly_anim_9[4] = { 0x01, 0x01, 0x00, 0x4A };
u8 dragonfly_anim_10[4] = { 0x01, 0x01, 0x00, 0x4B };
u8 dragonfly_anim_11[4] = { 0x01, 0x01, 0x00, 0x4C };

const u8* dragonfly_animations[12] = {
    dragonfly_anim_0,
    dragonfly_anim_1,
    dragonfly_anim_2,
    dragonfly_anim_3,
    dragonfly_anim_4,
    dragonfly_anim_5,
    dragonfly_anim_6,
    dragonfly_anim_7,
    dragonfly_anim_8,
    dragonfly_anim_9,
    dragonfly_anim_10,
    dragonfly_anim_11,
};

u8 D_800FB0EC[8] = { 6, 7, 8, 9, 10, 11, 0, 0 };

void (*dragonfly_state_funcs[])(struct MainObj*) = {
    dragonfly_init,
    dragonfly_run,
    dragonfly_finish,
    dragonfly_despawn,
};

void (*dragonfly_step_funcs[])(struct MainObj*) = {
    func_8009216C,
    dragonfly_resume_step,
    dragonfly_wait,
    dragonfly_hunt,
    dragonfly_carry,
    dragonfly_flee,
    dragonfly_fly_past,
};
