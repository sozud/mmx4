// MainObj, main_object_update_funcs[33]
// 8005D1F4..8005E570
#include "common.h"

void spike_sled_update(struct MainObj* self)
{
    spike_sled_state_funcs[self->state](self);
}

void spike_sled_init(struct MainObj* self)
{
    u8 bg_offset;
    u16 unk42;
    s32 x_pos;
    s32 y_pos;

    self->unk5C = 0;
    self->unk60 = 6;
    self->unk61 = 0;
    self->collision_data = D_801072F4;
    bg_offset = (u8)g_Player.bg_offset;
    self->unk16 = 6;
    x_pos = self->x_pos.val;
    self->y_pos.i.hi = 0x2E8;
    y_pos = self->y_pos.val;
    self->animation_table = (const u8* const*)spike_sled_animations;
    self->unk54 = &D_800FDD88;
    self->unk50 = &D_800FDD8C;
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk67 = 0;
    self->unk68 = NULL;
    self->unk15 = 0x40;
    self->bg_offset = bg_offset;
    self->unk18.val = x_pos;
    self->unk1C.val = y_pos;
    func_80015D60(self, 0);
    self->ext.main_33.unk80 = 0x7F;
    unk42 = self->unk42;
    self->ext.main_33.flash_timer = 0;
    self->ext.main_33.intro_active = 1;
    self->ext.main_33.intro_laps = 2;
    self->ext.main_33.unk8E = unk42;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = self;
    func_80036AE4(0x14, 0);
    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
}

void spike_sled_run(struct MainObj* self)
{
    s32 x;
    s32 y;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    spike_sled_step_funcs[self->unk5](self);
    if (self->ext.main_33.intro_active == 0) {
        self->ext.main_33.saved_unk5 = self->unk5;
        if (func_8002DD04(self) < 0) {
            g_Player.unk7A = 1;
            g_Player.unk61 = 0x7F;
            func_800AF808(BASE_OBJECT(self));
            func_800C813C(9, D_800FDF40, self);
            self->unk54 = NULL;
            self->unk50 = NULL;
            func_800DABE4(1, 0, 0);
            self->unk7C = 0x5A;
            self->unk7E = 4;
            self->on_screen = 0;
            self->state = 2;
            self->unk5 = 0;
            return;
        }
    }
    func_8002D9BC(self);
    if (self->ext.main_33.flash_timer != 0) {
        self->ext.main_33.flash_timer--;
        if (--self->ext.main_33.unk91 == 0) {
            x = self->x_pos.val;
            y = self->y_pos.val;
            self->x_pos.i.hi = D_800FDDA0[self->ext.main_33.unk87 * 2] + 0x20;
            self->y_pos.i.hi = D_800FDDA0[self->ext.main_33.unk87 * 2 + 1] + 0x20;
            func_800AF878(BASE_OBJECT(self), 1, 0x20, 0x20);
            self->x_pos.val = x;
            self->y_pos.val = y;
            self->ext.main_33.unk91 = 6;
        }
    }
    func_8002B318(BASE_OBJECT(self), 0x48, 0x48);
}

// spike_sled_death
INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005D4E0);

void spike_sled_despawn(struct MainObj* self)
{
    self->ext.raw[0] = 0;
    self->ext.raw[1] = 0;
    self->ext.raw[2] = 0;
    self->ext.raw[3] = 0;
    self->ext.raw[5] = 0;
    background_objects[0].unk26 = 0x1100;
    background_objects[0].unk2A = 0x220;
    background_objects[0].unk28 = FIXED(0.00831);
    g_Player.unk61 = 0;
    func_8002B108(OBJECT_HEADER(self));
}

void spike_sled_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_33.saved_unk5;
}

void spike_sled_patrol(struct MainObj* self)
{
    spike_sled_patrol_funcs[self->unk6](self);
}

void spike_sled_patrol_start(struct MainObj* self)
{
    self->unk7C = 0xB4;
    if (self->unk15 == 0) {
        self->unk20 = FIXED(-2.5);
    } else {
        self->unk20 = FIXED(2.5);
    }
    self->unk6 = 1;
}

void spike_sled_patrol_drive(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (self->unk15 == 0 ? self->x_pos.i.hi >= 0x1220 : self->x_pos.i.hi < 0x1321) {
    } else {
        func_80015D60(self, 1);
        self->unk28 = FIXED(-0.125);
        self->unk6 = 2;
        return;
    }
    if (self->ext.main_33.intro_active == 0 && --self->unk7C == 0) {
        self->unk7C = 1;
        if (self->unk15 == 0 ? self->x_pos.i.hi < 0x1231 : self->x_pos.i.hi >= 0x1310) {
        } else {
            func_80015D60(self, 2);
            self->unk5 = 4;
            self->unk6 = 0;
        }
    }
}

void spike_sled_patrol_turn(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 1;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk20 != 0) {
        return;
    }
    if (self->unk15 == 0) {
        self->unk15 = 0x40;
        self->unk20 = FIXED(2.5);
    } else {
        self->unk15 = 0;
        self->unk20 = -FIXED(2.5);
    }
    func_80015D60(self, 0);
    self->unk28 = 0;
    if (--self->ext.main_33.intro_laps == 0 && self->ext.main_33.intro_active != 0) {
        self->unk7C = 0x40;
        self->unk20 = FIXED(1);
        self->unk5 = 6;
        self->unk6 = 0;
        return;
    }
    self->unk6 = 1;
}

void spike_sled_fall(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));

    if (self->unk6 == 0) {
        func_8002B694(ANIMATED_OBJECT(self));

        if (self->unk1C.i.hi == self->y_pos.i.hi) {
            if (self->ext.main_33.unk84 == 0) {
                self->unk7C = 0x1E;
                self->unk6 = 1;
            }
        }

        if (self->y_pos.i.hi >= 0x2E9) {
            self->y_pos.i.hi = 0x2E8;
            self->unk24 = 0;
            self->unk2C = 0;
            func_80015D60(self, 2);
            self->unk5 = 4;
            self->unk6 = 0;
        }
    } else {
        if (--self->unk7C == 0) {
            self->ext.main_33.unk84 = 1;
            self->unk6 = 0;
        }
    }
}

void spike_sled_charge(struct MainObj* self)
{
    spike_sled_charge_funcs[self->unk6](self);
}

void spike_sled_charge_start(struct MainObj* self)
{
    self->ext.main_33.target_x = 0;
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, 0x52, self);
    }
    if (self->animation_step.fields.event == 1) {
        if (self->unk15 != 0) {
            self->unk20 = FIXED(4);
        } else {
            self->unk20 = FIXED(-4);
        }
        func_80015D60(self, 3);
        self->unk7C = 0xB4;
        self->unk6 = 1;
    }
}

// spike_sled_charge_dash
INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DC58);

// spike_sled_charge_target
INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DED4);

void spike_sled_charge_approach(struct MainObj* self)
{
    s16 target;
    s16 position;
    s16 distance;

    target = self->ext.main_33.target_x;
    position = self->x_pos.i.hi;
    if ((target - position) >= 0) {
        distance = target - position;
    } else {
        distance = position - target;
    }

    if (distance == 0) {
        func_80015D60(self, 5);
        self->unk7C = 0x1E;
        self->unk6 = 4;
    } else if (distance < 6) {
        if (self->unk15 != 0) {
            self->unk20 = FIXED(1);
        } else {
            self->unk20 = FIXED(-1);
        }
    } else if (distance < 0x18) {
        if (self->unk15 != 0) {
            self->unk20 = FIXED(2);
        } else {
            self->unk20 = FIXED(-2);
        }
    }

    func_8002B718(MOVING_OBJECT(self));
}

void spike_sled_charge_leap(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, 0x53, self);
    }
    if (self->animation_step.fields.event == 1) {
        self->unk24 = FIXED(4);
        self->unk20 = 0;
        func_8001540C(2, 0x54, self);
        func_80015D60(self, 6);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void spike_sled_bomb(struct MainObj* self)
{
    spike_sled_bomb_funcs[self->unk6](self);
}

// spike_sled_bomb_jump
INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005E108);

void spike_sled_bomb_rise(struct MainObj* self)
{
    s32 variant;
    s32 should_transition;
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));

    variant = self->ext.main_33.variant;
    if (variant == 5) {
        goto state_5;
    }
    if (variant >= 6) {
        if (variant == 6) {
            goto state_6;
        }
        goto timer_update;
    }
    if (variant >= 0) {
        goto state_low;
    }
    goto timer_update;

state_low:
    should_transition = self->y_pos.i.hi < 0x2F0;
    goto transition_check;

state_5:
    should_transition = self->y_pos.i.hi < 0x2A0;
    goto transition_check;

state_6:
    should_transition = self->y_pos.i.hi < 0x280;

transition_check:
    if (should_transition != 0) {
        self->unk7E = 4;
        self->unk6 = 2;
        return;
    }

timer_update:
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk2C = FIXED(0.2578125);
        self->ext.main_33.unk84 = 0;
        self->unk5 = 3;
        self->unk6 = 0;
        func_80015D60(self, 7);
    }
}

// spike_sled_bomb_drop
INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005E298);

void spike_sled_intro(struct MainObj* self)
{
    spike_sled_intro_funcs[self->unk6](self);
}

void spike_sled_intro_drive(struct MainObj* self)
{
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk7E = 3;
        self->unk6 = 1;
    }
}

void spike_sled_intro_fill_health(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        self->unk7E = 3;
    }
    if (++self->unk5C == 0x30) {
        self->unk6 = 2;
        self->unk7C = 0x3C;
    }
}

void spike_sled_intro_start_fight(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_800DABE4(0, 0x1340, 0x2A0);
        self->ext.main_33.intro_active = 0;
        func_80036B18();
        func_80015D60(self, 2);
        self->unk5 = 4;
        self->unk6 = 0;
    }
}
