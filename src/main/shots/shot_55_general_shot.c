// ShotObj, shot_object_update_funcs[55]
// 800AC8C4..800ADF30
#include "common.h"

extern s8 general_shot_boxes[3][4];

extern s16 D_8013B8C8;

extern s16 D_8013B8CC;

extern u8 D_8013B8D0[0xC];

extern u8 general_shot_prop_debris[6];

extern s8 general_shot_attack_boxes[][4];

#ifdef MMX4_WIN32
s8 general_shot_attack_boxes_tail[2][4] = {
    { -10, -9, 18, 16 },
    { -99, 53, -60, 38 },
};
#endif

s16 general_fist_rows[4] = { 0x208, 0x238, 0x268, 0x290 };

u8 general_fist_row_order[4] = { 2, 3, 0, 1 };

void (*general_fist_leader_funcs[])(struct ShotObj*) = {
    general_fist_wait_launch,
    func_800ACDE4,
    general_fist_fly_to_row,
    func_800ACF60,
    general_fist_hold,
    general_fist_turn,
    general_fist_approach,
    general_fist_pause,
    general_fist_sweep_turn,
    func_800AD338,
    general_fist_docked,
};

void (*general_fist_follower_funcs[])(struct ShotObj*) = {
    general_fist_follower_wait_launch,
    general_fist_follower_launch,
    general_fist_follower_fly_to_row,
    func_800ACF60,
    general_fist_hold,
    general_fist_turn,
    general_fist_approach,
    general_fist_pause,
    general_fist_sweep_turn,
    func_800AD338,
    general_fist_docked,
};

void (*general_fist_funcs[2])(struct ShotObj*) = {
    general_fist_follower,
    general_fist_leader,
};

s8 general_ring_offsets[4] = { -63, -40, 13, -40 };

void (*general_ring_funcs[])(struct ShotObj*) = {
    func_800AD6DC,
    general_ring_fly,
};

void (*general_dust_funcs[])(struct ShotObj*) = {
    general_dust_start,
    general_dust_burst,
    general_dust_end,
};

void (*general_orb_funcs[])(struct ShotObj*) = {
    general_orb_spread,
    general_orb_wait,
    general_orb_aim,
    general_orb_fly,
};

void (*general_shot_subtype_funcs[])(struct ShotObj*) = {
    general_shot_thruster,
    general_shot_intro_prop,
    general_shot_fist,
    general_shot_fist,
    general_shot_ring,
    general_shot_ring,
    general_shot_dust,
    general_shot_dust,
    general_shot_hit_flash,
    general_shot_orb_launcher,
    general_shot_orb,
    general_shot_orb,
};

// general_shot_init
INCLUDE_ASM("main/nonmatchings/shots/shot_55_general_shot", func_800AC8C4);

void general_shot_intro_prop(struct ShotObj* self)
{
    if (self->unk5 == 0) {
        update_on_screen(BASE_OBJECT(self), 0xA0, 0xA0);
        return;
    }

    self->state++;
    spawn_debris(6, general_shot_prop_debris, self);
}

void general_shot_thruster(struct ShotObj* self)
{
    struct WeaponObj* weapon = self->unk7C;

    self->on_screen = 0;
    self->x_pos.u.hi = weapon->x_pos.u.hi + self->unk84.halves[0];
    self->y_pos.u.hi = weapon->y_pos.u.hi + self->unk84.halves[1];
    self->unk15 = weapon->unk15;
    if (self->timer != 0) {
        animate_object(self);
        update_on_screen(BASE_OBJECT(self), 0xA0, 0xA0);
    }
}

void general_fist_wait_launch(struct ShotObj* self)
{
    if (self->unk7C->unk6 == 3) {
        self->unk5++;
        set_animation(self, 0x13);
        func_8001540C(2, 6, self);
    }
}

// general_fist_launch
INCLUDE_ASM("main/nonmatchings/shots/shot_55_general_shot", func_800ACDE4);

void general_fist_fly_to_row(struct ShotObj* self)
{
    s32 velocity;

    set_velocity_from_angle(MOVING_OBJECT(self),
        angle_to_point(OBJECT_HEADER(self), FIXED(3616), general_fist_rows[self->timer] << 16) & 0xFF);
    self->x_vel.val *= 4;
    self->y_vel.val *= 4;
    if (sigma_final_shot_at_position(self, 0xE20, general_fist_rows[self->timer]) & 0xFF) {
        velocity = FIXED(-1.5);
        self->y_vel.val = 0;
        self->unk5++;
        if (self->unk15 != 0) {
            velocity = FIXED(1.5);
        }
        self->x_vel.val = velocity;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

// general_fist_sweep
#ifdef VERSION_EU
void func_800ACF60(struct ShotObj* self)
{
    s32 origin_x;
    s16 probe_x;
    u16 probe_y;
    s16* probe_slot = &D_8013B8C8;
    u8* tile_slot;

    self->unk68 = (struct Unk_unk68*)general_shot_boxes;
    origin_x = self->x_pos.i.hi;
    probe_x = self->unk15 != 0 ? origin_x + 0x59 : origin_x - 0x59;
    probe_y = self->y_pos.u.hi;
    tile_slot = D_8013B8D0;
    *probe_slot = probe_x;
    D_8013B8CC = probe_y;
    *tile_slot = func_8002D724(PLAYER_OBJECT(self), D_8013B8C8, probe_y);
    if (*tile_slot == 0x38) {
        self->x_vel.val = 0;
        self->unk90.u.lo = 0x3C;
        self->unk5++;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}
#else
void func_800ACF60(struct ShotObj* self)
{
    s32 origin_x;
    s16 probe_x;
    u16 probe_y;
    u8 tile;

    self->unk68 = (struct Unk_unk68*)general_shot_boxes;
    origin_x = self->x_pos.i.hi;
    probe_x = self->unk15 != 0 ? origin_x + 0x59 : origin_x - 0x59;
    probe_y = self->y_pos.u.hi;
    D_8013B8C8 = probe_x;
    D_8013B8CC = probe_y;
    tile = func_8002D724(PLAYER_OBJECT(self), probe_x, probe_y);
    D_8013B8D0[0] = tile;
    if (tile == 0x38) {
        self->x_vel.val = 0;
        self->unk90.u.lo = 0x3C;
        self->unk5++;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}
#endif

void general_fist_hold(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk90.i.lo = self->unk90.u.lo - 1;
    if (self->unk90.i.lo == 0) {
        self->unk5++;
        if (self->unk2 == 3) {
            set_animation(self, 0x16);
        } else {
            set_animation(self, 0x11);
        }
    }
}

void general_fist_turn(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        self->unk15 ^= 0x40;
        self->x_vel.val = self->unk15 != 0 ? FIXED(1.5) : FIXED(-1.5);
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5++;
        if (self->unk2 == 3) {
            set_animation(self, 0xF);
            func_8001540C(2, 5, self);
        } else {
            set_animation(self, 0x14);
            func_8001540C(2, 5, self);
        }
    }
}

void general_fist_approach(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (ABS(self->x_pos.i.hi, self->unk7C->x_pos.i.hi) < 0x30) {
        self->x_vel.val = 0;
        self->unk90.u.lo = 0x3C;
        self->unk5++;
    }
}

void general_fist_pause(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk90.i.lo = self->unk90.u.lo - 1;
    if (self->unk90.i.lo == 0) {
        self->unk5++;
        if (self->unk2 == 3) {
            set_animation(self, 0x11);
        } else {
            set_animation(self, 0x16);
        }
    }
}

void general_fist_sweep_turn(struct ShotObj* self)
{
    struct WeaponObj* owner;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        self->unk15 ^= 0x40;
        self->x_vel.val = self->unk15 != 0 ? FIXED(1.5) : FIXED(-1.5);
    }
    if (self->animation_step.fields.relative_step == 0) {
        if ((++self->unk8A) == 2) {
            self->unk5++;
            if (self->unk2 == 3) {
                self->unk7C->unk6++;
                set_animation(self, 0x15);
                return;
            }
            set_animation(self, 0x10);
            return;
        }
        self->unk5 = 3;
        if (self->unk2 == 3) {
            set_animation(self, 0x14);
            func_8001540C(2, 5, self);
        } else {
            set_animation(self, 0xF);
            func_8001540C(2, 5, self);
        }
    }
}

// general_fist_return
INCLUDE_ASM("main/nonmatchings/shots/shot_55_general_shot", func_800AD338);

void general_fist_docked(struct ShotObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.relative_step == 0) {
        self->timer = 0x80;
    }
}

void general_fist_leader(struct ShotObj* self)
{
    general_fist_leader_funcs[self->unk5](self);
}

void general_fist_follower_wait_launch(struct ShotObj* self)
{
    if (self->unk8C.object->unk5 == 3) {
        self->unk5++;
        set_animation(self, 0xE);
        func_8001540C(2, 6, self);
    }
}

void general_fist_follower_launch(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5++;
        set_animation(self, 0xF);
        func_8001540C(2, 5, self);
    }
}

void general_fist_follower_fly_to_row(struct ShotObj* self)
{
    s32 velocity;

    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_point(
            OBJECT_HEADER(self), FIXED(3616),
            general_fist_rows[general_fist_row_order[SHOT_OBJECT(self->unk8C.object)->timer]]
                << 16)
            & 0xFF);
    self->x_vel.val *= 4;
    self->y_vel.val *= 4;
    if (sigma_final_shot_at_position(
            self, 0xE20,
            general_fist_rows[general_fist_row_order[SHOT_OBJECT(self->unk8C.object)->timer]])
        & 0xFF) {
        self->y_vel.val = 0;
        self->unk5 = (u8)self->unk5 + 1;
        velocity = self->unk15 != 0 ? FIXED(1.5) : FIXED(-1.5);
        self->x_vel.val = velocity;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void general_fist_follower(struct ShotObj* self)
{
    general_fist_follower_funcs[self->unk5](self);
}

void general_shot_fist(struct ShotObj* self)
{
    general_fist_funcs[self->unk2 - 2](self);
    self->unk42 = self->unk7C->unk42;
    collide_with_players(PLAYER_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0xA0, 0xA0);
}

// general_ring_init
INCLUDE_ASM("main/nonmatchings/shots/shot_55_general_shot", func_800AD6DC);

void general_ring_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002B160(BASE_OBJECT(self)) == 1) {
        self->state = 2;
    }
}

void general_shot_ring(struct ShotObj* self)
{
    general_ring_funcs[self->unk5](self);
    update_on_screen(BASE_OBJECT(self), 0xA0, 0xA0);
}

void general_dust_start(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5++;
        self->timer = 0x19;
        if (self->unk2 == 6) {
            set_animation(self, 0x19);
        } else {
            set_animation(self, 0x1C);
        }
    }
}

void general_dust_burst(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
#ifdef MMX4_WIN32
        self->unk50.data = (u8*)&general_shot_attack_boxes_tail[1];
#else
        self->unk50.data = (u8*)&general_shot_attack_boxes[2];
#endif
        self->timer--;
    }
    if (self->timer == 0) {
        self->unk50.data = NULL;
        self->unk5++;
        if (self->unk2 == 6) {
            set_animation(self, 0x1A);
        } else {
            set_animation(self, 0x1D);
        }
    }
}

void general_dust_end(struct ShotObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.relative_step == 0) {
        self->state++;
    }
}

void general_shot_dust(struct ShotObj* self)
{
    general_dust_funcs[self->unk5](self);
    update_on_screen(BASE_OBJECT(self), 0xA0, 0xA0);
}

void general_shot_hit_flash(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    self->x_pos.val = weapon->x_pos.val;
    self->y_pos.val = weapon->y_pos.val;
    animate_object(ANIMATED_OBJECT(self));
    if (MAIN_OBJECT(weapon)->ext.main_75.hit_active == 0) {
        self->state++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void general_shot_orb_launcher(struct ShotObj* self)
{
    u8 i;
    struct ShotObj* shot;
    struct WeaponObj* owner;

    if (self->unk5 == 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step == 0) {
            owner = self->unk7C;
            self->unk5 = (u8)self->unk5 + 1;
            i = 0;
            do {
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x37;
                    shot->unk2 = i + 0xA;
                    shot->timer = 0;
                    shot->unk7C = owner;
                    shot->unk84.halves[0] = self->x_pos.u.hi - owner->x_pos.u.hi;
                    shot->unk84.halves[1] = self->y_pos.u.hi - owner->y_pos.u.hi;
                    func_8001540C(2, 4, self);
                }
                i++;
            } while (i < 2);
        }
    } else {
        self->state = (u8)self->state + 1;
    }
    is_on_screen(BASE_OBJECT(self));
}

void general_orb_spread(struct ShotObj* self)
{
    struct ShotObj* shot;
    struct WeaponObj* owner;

    animate_object(ANIMATED_OBJECT(self));
    if (self->unk8A != 0) {
        move_object(MOVING_OBJECT(self));
        self->unk8A = (u16)self->unk8A - 1;
        return;
    }
    owner = self->unk7C;
    self->unk5 = (u8)self->unk5 + 1;
    set_animation(self, 0x20);
    self->unk50.data = (u8*)general_shot_attack_boxes;
    if (self->timer < 2) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = (u8)self->unk2;
            shot->timer = (u16)self->timer + 1;
            shot->unk7C = self->unk7C;
            shot->unk84.halves[0] = self->x_pos.u.hi - owner->x_pos.u.hi;
            shot->unk84.halves[1] = self->y_pos.u.hi - owner->y_pos.u.hi;
        }
    } else {
        MAIN_OBJECT(owner)->ext.main_75.orbs_ready = 1;
    }
}

void general_orb_wait(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    animate_object(ANIMATED_OBJECT(self));
    if (MAIN_OBJECT(weapon)->ext.main_75.orbs_ready != 0) {
        self->unk8A = 0x14;
        self->unk5++;
    }
}

void general_orb_aim(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk8A == 0) {
        self->unk5 = (u8)self->unk5 + 1;
        self->x_vel.val = self->unk15 ? FIXED(5) : FIXED(-5);
        self->y_vel.val = 0;
        func_8001540C(2, 4, self);
    }
}

void general_orb_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x50, 0x30) == 1) {
        self->state = 2;
    }
}

void general_shot_orb(struct ShotObj* self)
{
    general_orb_funcs[self->unk5](self);
    is_on_screen(BASE_OBJECT(self));
}

void general_shot_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    func_8002DD04(MAIN_OBJECT(self));
    general_shot_subtype_funcs[self->unk2](self);
    func_8002D9BC(self);
    if (self->unk7C->state == 2) {
        self->state = 2;
    }
}

void general_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void general_shot_update(struct ShotObj* self)
{
    general_shot_state_funcs[self->state](self);
}

void (*general_shot_state_funcs[])(struct ShotObj*) = {
    func_800AC8C4,
    general_shot_run,
    general_shot_despawn,
};
