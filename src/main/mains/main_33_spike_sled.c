// MainObj, main_object_update_funcs[33]
// 8005D1F4..8005E570
#include "common.h"
#include "func_tables.h"

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

    self->hp = 0;
    self->contact_damage = 6;
    self->invincibility_timer = 0;
    self->collision_data = D_801072F4;
    bg_offset = (u8)g_Player.bg_offset;
    self->unk16 = 6;
    x_pos = self->x_pos.val;
    self->y_pos.i.hi = 0x2E8;
    y_pos = self->y_pos.val;
    self->animation_table = (const u8* const*)spike_sled_animations;
    self->hurt_box = &D_800FDD88;
    self->attack_box = &D_800FDD8C;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->terrain_box = NULL;
    self->unk15 = 0x40;
    self->bg_offset = bg_offset;
    self->unk18.val = x_pos;
    self->unk1C.val = y_pos;
    set_animation(self, 0);
    self->ext.main_33.unk80 = 0x7F;
    unk42 = self->unk42;
    self->ext.main_33.flash_timer = 0;
    self->ext.main_33.intro_active = 1;
    self->ext.main_33.intro_laps = 2;
    self->ext.main_33.unk8E = unk42;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = self;
    player_start_script_action(0x14, 0);
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
            g_Player.spike_immune = 1;
            g_Player.invincibility_timer = 0x7F;
            spawn_explosion(BASE_OBJECT(self));
            spawn_debris(9, D_800FDF40, self);
            self->hurt_box = NULL;
            self->attack_box = NULL;
            apply_tile_effect(1, 0, 0);
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
    update_on_screen(BASE_OBJECT(self), 0x48, 0x48);
}

// spike_sled_death
INCLUDE_ASM("main/nonmatchings/mains/main_33_spike_sled", func_8005D4E0);

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
    g_Player.invincibility_timer = 0;
    despawn_object_permanently(OBJECT_HEADER(self));
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
        self->x_speed = FIXED(-2.5);
    } else {
        self->x_speed = FIXED(2.5);
    }
    self->unk6 = 1;
}

void spike_sled_patrol_drive(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->unk15 == 0 ? self->x_pos.i.hi >= 0x1220 : self->x_pos.i.hi < 0x1321) {
    } else {
        set_animation(self, 1);
        self->x_accel = FIXED(-0.125);
        self->unk6 = 2;
        return;
    }
    if (self->ext.main_33.intro_active == 0 && --self->unk7C == 0) {
        self->unk7C = 1;
        if (self->unk15 == 0 ? self->x_pos.i.hi < 0x1231 : self->x_pos.i.hi >= 0x1310) {
        } else {
            set_animation(self, 2);
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
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_speed != 0) {
        return;
    }
    if (self->unk15 == 0) {
        self->unk15 = 0x40;
        self->x_speed = FIXED(2.5);
    } else {
        self->unk15 = 0;
        self->x_speed = -FIXED(2.5);
    }
    set_animation(self, 0);
    self->x_accel = 0;
    if (--self->ext.main_33.intro_laps == 0 && self->ext.main_33.intro_active != 0) {
        self->unk7C = 0x40;
        self->x_speed = FIXED(1);
        self->unk5 = 6;
        self->unk6 = 0;
        return;
    }
    self->unk6 = 1;
}

void spike_sled_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));

    if (self->unk6 == 0) {
        move_with_gravity(ANIMATED_OBJECT(self));

        if (self->unk1C.i.hi == self->y_pos.i.hi) {
            if (self->ext.main_33.unk84 == 0) {
                self->unk7C = 0x1E;
                self->unk6 = 1;
            }
        }

        if (self->y_pos.i.hi > 0x2E8) {
            self->y_pos.i.hi = 0x2E8;
            self->y_speed = 0;
            self->gravity = 0;
            set_animation(self, 2);
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
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, 0x52, self);
    }
    if (self->animation_step.fields.event == 1) {
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-4);
        } else {
            self->x_speed = FIXED(4);
        }
        set_animation(self, 3);
        self->unk7C = 0xB4;
        self->unk6 = 1;
    }
}

// spike_sled_charge_dash
INCLUDE_ASM("main/nonmatchings/mains/main_33_spike_sled", func_8005DC58);

// spike_sled_charge_target
INCLUDE_ASM("main/nonmatchings/mains/main_33_spike_sled", func_8005DED4);

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
        set_animation(self, 5);
        self->unk7C = 0x1E;
        self->unk6 = 4;
    } else if (distance < 6) {
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-1);
        } else {
            self->x_speed = FIXED(1);
        }
    } else if (distance < 0x18) {
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-2);
        } else {
            self->x_speed = FIXED(2);
        }
    }

    move_object(MOVING_OBJECT(self));
}

void spike_sled_charge_leap(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, 0x53, self);
    }
    if (self->animation_step.fields.event == 1) {
        self->y_speed = FIXED(4);
        self->x_speed = 0;
        func_8001540C(2, 0x54, self);
        set_animation(self, 6);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void spike_sled_bomb(struct MainObj* self)
{
    spike_sled_bomb_funcs[self->unk6](self);
}

// spike_sled_bomb_jump
INCLUDE_ASM("main/nonmatchings/mains/main_33_spike_sled", func_8005E108);

void spike_sled_bomb_rise(struct MainObj* self)
{
    s32 variant;
    s32 should_transition;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

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
    if (--self->unk7C == 0) {
        self->gravity = FIXED(0.2578125);
        self->ext.main_33.unk84 = 0;
        self->unk5 = 3;
        self->unk6 = 0;
        set_animation(self, 7);
    }
}

// spike_sled_bomb_drop
INCLUDE_ASM("main/nonmatchings/mains/main_33_spike_sled", func_8005E298);

void spike_sled_intro(struct MainObj* self)
{
    spike_sled_intro_funcs[self->unk6](self);
}

void spike_sled_intro_drive(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk7E = 3;
        self->unk6 = 1;
    }
}

void spike_sled_intro_fill_health(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        self->unk7E = 3;
    }
    if (++self->hp == 0x30) {
        self->unk6 = 2;
        self->unk7C = 0x3C;
    }
}

void spike_sled_intro_start_fight(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        apply_tile_effect(0, 0x1340, 0x2A0);
        self->ext.main_33.intro_active = 0;
        player_end_script_action();
        set_animation(self, 2);
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

struct Unk_unk68 D_800FDD88 = { -26, -17, 52, 42 };

struct Unk_unk68 D_800FDD8C = { -18, -14, 35, 30 };

u8 D_800FDD90[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00 };

u8 D_800FDD98[8] = {
    0x21,
    0x22,
    0x04,
    0x48,
    0x50,
    0x00,
    0x00,
    0x00,
};

u16 D_800FDDA0[14] = {
    0x1200,
    0x02A0,
    0x1240,
    0x02A0,
    0x1280,
    0x02A0,
    0x12C0,
    0x02A0,
    0x1300,
    0x02A0,
    0x1230,
    0x0240,
    0x12D0,
    0x0240,
};

union AnimationStep D_800FDDBC[] = {
    { 0x17010001 },
    { 0x18010001 },
    { 0x19FE0001 },
};

union AnimationStep D_800FDDC8[] = {
    { 0x1A010005 },
    { 0x1B010004 },
    { 0x1B000101 },
};

union AnimationStep D_800FDDD4[] = {
    { 0x0D010006 },
    { 0x0E010201 },
    { 0x0E010003 },
    { 0x0E000101 },
};

union AnimationStep D_800FDDE4[] = {
    { 0x0F010002 },
    { 0x10FF0002 },
};

union AnimationStep D_800FDDEC[] = {
    { 0x15010002 },
    { 0x16010001 },
    { 0x16000101 },
};

union AnimationStep D_800FDDF8[] = {
    { 0x0E010006 },
    { 0x0D010002 },
    { 0x0C010002 },
    { 0x0B010201 },
    { 0x0B010001 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x08010002 },
    { 0x11010004 },
    { 0x14010002 },
    { 0x13010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x07010004 },
    { 0x07000101 },
};

union AnimationStep D_800FDE5C[] = {
    { 0x00010005 },
    { 0x01010004 },
    { 0x02010004 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x00010003 },
    { 0x01010003 },
    { 0x02F90003 },
};

union AnimationStep D_800FDE88[] = {
    { 0x00010005 },
    { 0x01010005 },
    { 0x02010005 },
    { 0x03010005 },
    { 0x04010005 },
    { 0x05010005 },
    { 0x06010005 },
    { 0x07F90005 },
};

union AnimationStep D_800FDEA8[] = {
    { 0x1C000001 },
};

union AnimationStep D_800FDEAC[] = {
    { 0x1D000001 },
};

union AnimationStep D_800FDEB0[] = {
    { 0x1E000001 },
};

union AnimationStep D_800FDEB4[] = {
    { 0x1F000001 },
};

union AnimationStep D_800FDEB8[] = {
    { 0x20000001 },
};

union AnimationStep D_800FDEBC[] = {
    { 0x21000001 },
};

union AnimationStep D_800FDEC0[] = {
    { 0x22000001 },
};

union AnimationStep D_800FDEC4[] = {
    { 0x23000001 },
};

union AnimationStep D_800FDEC8[] = {
    { 0x24000001 },
};

union AnimationStep D_800FDECC[] = {
    { 0x25000001 },
};

union AnimationStep D_800FDED0[] = {
    { 0x26000001 },
};

union AnimationStep D_800FDED4[] = {
    { 0x27000001 },
};

union AnimationStep D_800FDED8[] = {
    { 0x28000001 },
};

union AnimationStep D_800FDEDC[] = {
    { 0x29000001 },
};

union AnimationStep D_800FDEE0[] = {
    { 0x2A000001 },
};

union AnimationStep* spike_sled_animations[23] = {
    D_800FDDBC,
    D_800FDDC8,
    D_800FDDD4,
    D_800FDDE4,
    D_800FDDEC,
    D_800FDDF8,
    D_800FDE5C,
    D_800FDE88,
    D_800FDEA8,
    D_800FDEAC,
    D_800FDEB0,
    D_800FDEB4,
    D_800FDEB8,
    D_800FDEBC,
    D_800FDEC0,
    D_800FDEC4,
    D_800FDEC8,
    D_800FDECC,
    D_800FDED0,
    D_800FDED4,
    D_800FDED8,
    D_800FDEDC,
    D_800FDEE0,
};

u8 D_800FDF40[12] = { 0x08, 0x09, 0x0D, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x00, 0x00, 0x00 };

u8 D_800FDF4C[8] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x00, 0x00 };

void (*spike_sled_state_funcs[])(struct MainObj*) = {
    spike_sled_init,
    spike_sled_run,
    func_8005D4E0,
    spike_sled_despawn,
};

void (*spike_sled_step_funcs[7])() = {
    enemy_hit_reaction,
    spike_sled_resume_step,
    spike_sled_patrol,
    spike_sled_fall,
    spike_sled_charge,
    spike_sled_bomb,
    spike_sled_intro,
};

void (*spike_sled_patrol_funcs[3])() = {
    spike_sled_patrol_start,
    spike_sled_patrol_drive,
    spike_sled_patrol_turn,
};

void (*spike_sled_charge_funcs[5])(struct MainObj*) = {
    spike_sled_charge_start,
    func_8005DC58,
    func_8005DED4,
    spike_sled_charge_approach,
    spike_sled_charge_leap,
};

void (*spike_sled_bomb_funcs[3])() = {
    func_8005E108,
    spike_sled_bomb_rise,
    func_8005E298,
};

void (*spike_sled_intro_funcs[3])() = {
    spike_sled_intro_drive,
    spike_sled_intro_fill_health,
    spike_sled_intro_start_fight,
};
