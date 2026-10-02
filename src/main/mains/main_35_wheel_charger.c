// MainObj, main_object_update_funcs[35]
// 8005EC58..8005F510
#include "common.h"
#include "func_tables.h"

void wheel_charger_update(struct MainObj* self)
{
    wheel_charger_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// wheel_charger_init
INCLUDE_ASM("main/nonmatchings/mains/main_35_wheel_charger", func_8005ECA8);

void wheel_charger_main(struct MainObj* self)
{
    s32 hit;

    wheel_charger_check_fall(self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    wheel_charger_step_funcs[self->unk5](self);
    if (self->unk5 == 4) {
        return;
    }
    if (engine_obj.stage != 3 || g_Player.x_pos.i.hi <= 0x9B6) {
        func_8002D9BC(self);
    }
    self->ext.main_35.saved_unk5 = self->unk5;
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, wheel_charger_debris, self);
        drop_item(BASE_OBJECT(self), 0xC);
        self->state = 2;
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state = 2;
    }
}

void wheel_charger_despawn(struct MainObj* self)
{
    self->unk7A = 0;
    self->ext.main_35.unk80 = 0;
    self->ext.main_35.sound_timer = 0;
    self->ext.main_35.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void wheel_charger_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_35.saved_unk5;
}

void wheel_charger_drop(struct MainObj* self)
{
    animate_object(self);
    self->y_speed = 0x60000;
    move_object((struct MovingObj*)self);
}

// wheel_charger_fall
INCLUDE_ASM("main/nonmatchings/mains/main_35_wheel_charger", func_8005EFB0);

void wheel_charger_wait_for_player(struct MainObj* self)
{
    if ((g_Player.x_pos.i.hi - self->x_pos.i.hi) > 0xB4) {
        self->unk7A = 0;
        self->unk5 = 2;
    }
}

void wheel_charger_charge(struct MainObj* self)
{
    wheel_charger_charge_funcs[self->unk6](self);
}

void wheel_charger_charge_ready(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 10;
        self->unk6 = 1;
    }
}

void wheel_charger_charge_open(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        self->hurt_box = (const u8*)&wheel_charger_open_hurt_box;
        self->attack_box = (const u8*)&wheel_charger_open_attack_box;
    }
    if (--self->unk7C == 0) {
        wheel_charger_face_player(self);
        set_animation(self, 2);
        self->unk7E = 3;
        self->unk6 = 2;
    }
}

void wheel_charger_charge_spin(struct MainObj* self)
{
    if (--self->ext.main_35.sound_timer == 0) {
        func_8001540C(2, 0x58, self);
        self->ext.main_35.sound_timer = 0x14;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7E == 0) {
        func_800B0CA0(1, 2, self, 8, 1);
        self->unk7E = 3;
    }
    if (self->animation_step.fields.event != 0) {
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-4);
            self->unk6 = 3;
        } else {
            self->x_speed = FIXED(4);
            self->unk6 = 3;
        }
    }
}

void wheel_charger_charge_roll(struct MainObj* self)
{
    s32 value;
    u8 mask;

    if (--self->ext.main_35.sound_timer == 0) {
        func_8001540C(2, 0x58, self);
        self->ext.main_35.sound_timer = 0x14;
    }

    if (--self->unk7E == 0) {
        func_800B0CA0(1, 2, self, 8, 1);
        self->unk7E = 2;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    mask = 9;
    if (self->unk15 == 0) {
        value = self->collision_flags & 0xA;
        mask = 0xA;
    } else {
        value = self->collision_flags & 9;
    }

    if (value == mask) {
        self->unk7C = 0x3C;
        self->unk5 = 6;
        self->unk6 = 0;
    }
}

void wheel_charger_crash(struct MainObj* self)
{
    if (--self->unk7E == 0) {
        func_800B0CA0(1, 2, self, 8, 1);
        self->unk7E = 2;
    }

    animate_object(ANIMATED_OBJECT(self));

    if (--self->unk7C == 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, wheel_charger_debris, self);
        self->state = 2;
    }
}

void wheel_charger_check_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (3 != self->unk5 && self->unk5 != 4) {
        if (!(self->collision_flags & 8)) {
            self->unk5 = 3;
            self->unk6 = 0;
            self->gravity = FIXED(0.234375);
        }
    }
}

void wheel_charger_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

struct Unk_unk68 D_800FE1B0 = { -16, -15, 29, 28 };

struct Unk_unk68 D_800FE1B4 = { -12, -11, 22, 20 };

struct Unk_unk68 D_800FE1B8 = { 0, 0, 14, 13 };

struct Unk_unk68 wheel_charger_open_hurt_box = { -16, -2, 29, 15 };

struct Unk_unk68 wheel_charger_open_attack_box = { -13, 0, 23, 11 };

union AnimationStep wheel_charger_anim_0[] = {
    { 0x05010001 },
    { 0x04010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x01010001 },
    { 0x00FB0001 },
};

union AnimationStep wheel_charger_anim_1[] = {
    { 0x00010006 },
    { 0x06010005 },
    { 0x07010004 },
    { 0x08010203 },
    { 0x09010003 },
    { 0x0A010003 },
    { 0x0B010003 },
    { 0x0C010003 },
    { 0x0E010003 },
    { 0x0D010004 },
    { 0x0C010005 },
    { 0x0E000101 },
};

union AnimationStep wheel_charger_anim_2[] = {
    { 0x0E010001 },
    { 0x14010002 },
    { 0x15010003 },
    { 0x1B010004 },
    { 0x15010003 },
    { 0x14010002 },
    { 0x0E01000E },
    { 0x0F010003 },
    { 0x10010003 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010102 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13FB0001 },
};

union AnimationStep wheel_charger_anim_4[] = {
    { 0x16000101 },
};

union AnimationStep wheel_charger_anim_5[] = {
    { 0x17000101 },
};

union AnimationStep wheel_charger_anim_6[] = {
    { 0x18000101 },
};

union AnimationStep wheel_charger_anim_7[] = {
    { 0x19000101 },
};

union AnimationStep wheel_charger_anim_8[] = {
    { 0x1A000101 },
};

union AnimationStep* wheel_charger_animations[9] = {
    wheel_charger_anim_0,
    wheel_charger_anim_1,
    wheel_charger_anim_2,
    &wheel_charger_anim_2[18],
    wheel_charger_anim_4,
    wheel_charger_anim_5,
    wheel_charger_anim_6,
    wheel_charger_anim_7,
    wheel_charger_anim_8,
};

u8 wheel_charger_debris[8] = { 4, 5, 6, 7, 8, 0, 0, 0 };

void (*wheel_charger_state_funcs[3])() = {
    func_8005ECA8,
    wheel_charger_main,
    wheel_charger_despawn,
};

void (*wheel_charger_step_funcs[7])() = {
    enemy_hit_reaction,
    wheel_charger_resume_step,
    wheel_charger_drop,
    func_8005EFB0,
    wheel_charger_wait_for_player,
    wheel_charger_charge,
    wheel_charger_crash,
};

void (*wheel_charger_charge_funcs[4])() = {
    wheel_charger_charge_ready,
    wheel_charger_charge_open,
    wheel_charger_charge_spin,
    wheel_charger_charge_roll,
};
