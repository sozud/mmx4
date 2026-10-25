// ShotObj, shot_object_update_funcs[55]
// 800AC8C4..800ADF30
#include "common.h"
#include "main/objects.h"
#include "main/shots/shot_54_sigma_final_shot.h"
#include "main/shots/shot_55_general_shot.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/shots/general_shot_debris_data.h"
#include "main/collision_bounds.h"

// general_fist_leader_funcs
extern void (*general_fist_leader_funcs[])(struct ShotObj*);
void general_fist_wait_launch(struct ShotObj*);

void general_fist_fly_to_row(struct ShotObj*);
void func_800ACF60(struct ShotObj*);
void general_fist_hold(struct ShotObj*);
void general_fist_turn(struct ShotObj*);

void general_fist_pause(struct ShotObj*);
void general_fist_sweep_turn(struct ShotObj*);

void general_fist_docked(struct ShotObj*);

// general_fist_follower_funcs
extern void (*general_fist_follower_funcs[])(struct ShotObj*);
void general_fist_follower_wait_launch(struct ShotObj*);
void general_fist_follower_launch(struct ShotObj*);
void general_fist_follower_fly_to_row(struct ShotObj*);
void func_800ACF60(struct ShotObj*);
void general_fist_hold(struct ShotObj*);
void general_fist_turn(struct ShotObj*);

void general_fist_pause(struct ShotObj*);
void general_fist_sweep_turn(struct ShotObj*);

void general_fist_docked(struct ShotObj*);
void general_fist_follower(struct ShotObj*);
void general_fist_leader(struct ShotObj*);

// general_ring_funcs
extern void (*general_ring_funcs[])(struct ShotObj*);

void general_ring_fly(struct ShotObj*);

// general_dust_funcs
extern void (*general_dust_funcs[])(struct ShotObj*);

// general_orb_funcs
extern void (*general_orb_funcs[])(struct ShotObj*);
void general_orb_spread(struct ShotObj*);
void general_orb_wait(struct ShotObj*);

// general_shot_subtype_funcs
extern void (*general_shot_subtype_funcs[])(struct ShotObj*);
void general_shot_thruster(struct ShotObj*);
void general_shot_intro_prop(struct ShotObj*);
void general_shot_fist(struct ShotObj*);
void general_shot_fist(struct ShotObj*);
void general_shot_ring(struct ShotObj*);
void general_shot_ring(struct ShotObj*);
void general_shot_dust(struct ShotObj*);
void general_shot_dust(struct ShotObj*);
void general_shot_hit_flash(struct ShotObj*);
void general_shot_orb_launcher(struct ShotObj*);
void general_shot_orb(struct ShotObj*);
void general_shot_orb(struct ShotObj*);

// general_shot_state_funcs
extern void (*general_shot_state_funcs[])(struct ShotObj*);

void general_shot_run(struct ShotObj*);
void general_shot_despawn(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

extern u8 D_8013B8DC[4];

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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800AC8C4(struct ShotObj* self);
void func_800ACDE4(struct ShotObj* self);
void func_800AD338(struct ShotObj* self);
void func_800AD6DC(struct ShotObj* self);
extern u8 D_8013B8DC[4];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800AC8C4(struct ShotObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk7C;
    s32 animation;

    self->state++;
    self->unk40 = parent->unk40;
    self->animation_table = (u32**)parent->animation_table;
    self->unk3C = (void*)parent->sprite_frames;
    self->unk42 = parent->unk42;
    self->unk15 = parent->unk15;
    self->bg_offset = parent->bg_offset;
    self->unk16 = parent->unk16;
    self->x_pos.val = parent->x_pos.val;
    self->unk58.data = NULL;
    self->unk50.data = NULL;
    self->unk54 = NULL;
    self->unk68 = NULL;
    self->unk75 = 0;
    self->y_pos.val = parent->y_pos.val;
    self->unk60 = 3;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    switch ((u8)self->unk2) {
    case 0:
        self->unk16 = VISUAL_SATURN_LAYER(7);
        self->unk84.value = 0;
        self->timer = 0;
        animation = 2;
        break;
    case 1:
        self->unk16 = VISUAL_SATURN_LAYER(7);
        animation = 0x27;
        break;
    case 2:
        self->unk16 = VISUAL_SATURN_LAYER(5);
        self->timer = 0;
        self->unk8A = 0;
        if (self->unk15 != 0)
            self->x_pos.i.hi += 0x50;
        else
            self->x_pos.i.hi -= 0x50;
        self->unk75 = 1;
        self->unk50.data = (u8*)general_shot_boxes[1];
        self->unk54 = (u8*)general_shot_boxes[2];
        self->y_pos.i.hi -= 0x28;
        self->unk58.collision_bounds = D_801060F0;
        self->unk84.shot_55.x = self->x_pos.i.hi;
        self->unk84.shot_55.y = self->y_pos.i.hi;
        set_animation(self, 0xD);
        self->unk60 = 6;
        return;
    case 3:
        self->unk16 = VISUAL_SATURN_LAYER(5);
        self->y_pos.i.hi -= 0x28;
        self->timer = 0;
        self->unk8A = 0;
        self->unk75 = 1;
        self->unk84.shot_55.x = self->x_pos.i.hi;
        self->unk84.shot_55.y = self->y_pos.i.hi;
        set_animation(self, 0x12);
        self->unk50.data = (u8*)general_shot_boxes[1];
        self->unk54 = (u8*)general_shot_boxes[2];
        self->unk58.collision_bounds = D_801060F0;
        self->unk60 = 6;
        return;
    case 4:
    case 5:
        self->unk50.data = (u8*)general_shot_attack_boxes[1];
        self->timer = 0x20;
        self->unk8A = 0;
        self->unk60 = 6;
        animation = self->unk2 == 4 ? 0x21 : 0x22;
        break;
    case 6:
        self->unk16 = VISUAL_SATURN_LAYER(5);
        self->unk60 = 9;
        animation = 0x18;
        break;
    case 7:
        self->unk16 = VISUAL_SATURN_LAYER(7);
        animation = 0x1B;
        break;
    case 8:
        self->unk42 &= 0x7FFF;
        animation = 0x26;
        break;
    case 9:
        D_8013B8DC[0] = 0;
        if (self->unk15 != 0)
            self->x_pos.i.hi += 0x1B;
        else
            self->x_pos.i.hi -= 0x1B;
        self->y_pos.i.hi -= 0x1A;
        animation = 0x1E;
        break;
    case 10:
    case 11:
        self->unk8A = self->timer != 0 ? 0xF : 0x1E;
        self->x_pos.i.hi += self->unk84.shot_55.x;
        self->y_pos.i.hi += self->unk84.shot_55.y;
        self->x_vel.val = self->unk15 != 0 ? 0x10000 : 0xFFFF0000;
        self->y_vel.val = self->unk2 == 10 ? 0x18000 : 0xFFFE8000;
        animation = 0x1F;
        break;
    default:
        return;
    }
    set_animation(self, animation);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_55_general_shot", func_800AC8C4);
#endif

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
        func_8001540C(2, SATURN_SOUND(6, 0xE0), self);
    }
}

// general_fist_launch
void func_800ACDE4(struct ShotObj* self)
{
    s16 player_y;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0)
        return;
    self->unk5++;
    self->x_vel.val = self->unk15 != 0 ? 0x40000 : 0xFFFC0000;
    set_animation(self, 0x14);
    func_8001540C(2, SATURN_SOUND(5, 0xDF), self);
    player_y = g_Player.y_pos.i.hi;
    if (player_y < 0x210)
        self->timer = 0;
    else if (player_y < 0x240)
        self->timer = 1;
    else if (player_y < 0x270)
        self->timer = 2;
    else
        self->timer = 3;
}

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
        self->unk15 ^= PLAYER_FACING_RIGHT;
        self->x_vel.val = self->unk15 != 0 ? FIXED(1.5) : FIXED(-1.5);
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5++;
        if (self->unk2 == 3) {
            set_animation(self, 0xF);
            func_8001540C(2, SATURN_SOUND(5, 0xDF), self);
        } else {
            set_animation(self, 0x14);
            func_8001540C(2, SATURN_SOUND(5, 0xDF), self);
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
        self->unk15 ^= PLAYER_FACING_RIGHT;
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
            func_8001540C(2, SATURN_SOUND(5, 0xDF), self);
        } else {
            set_animation(self, 0xF);
            func_8001540C(2, SATURN_SOUND(5, 0xDF), self);
        }
    }
}

// general_fist_return
void func_800AD338(struct ShotObj* self)
{
    self->unk68 = NULL;
    set_velocity_from_angle(MOVING_OBJECT(self),
        (u8)angle_to_point(OBJECT_HEADER(self), self->unk84.shot_55.x << 16,
            self->unk84.shot_55.y << 16));
    self->x_vel.val *= 4;
    self->y_vel.val *= 4;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (sigma_final_shot_at_position(self, self->unk84.shot_55.x, self->unk84.shot_55.y) & 0xFF) {
        self->unk5++;
        if (self->unk2 == 3)
            set_animation(self, 0x13);
        else
            set_animation(self, 0xE);
        func_8001540C(2, SATURN_SOUND(6, 0xE0), self);
    }
}

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
        func_8001540C(2, SATURN_SOUND(6, 0xE0), self);
    }
}

void general_fist_follower_launch(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5++;
        set_animation(self, 0xF);
        func_8001540C(2, SATURN_SOUND(5, 0xDF), self);
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
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_55_general_shot", func_800AD6DC);
#else
void func_800AD6DC(struct ShotObj* self)
{
    u8 angle;

    animate_object(ANIMATED_OBJECT(self));
    self->unk42 = self->unk7C->unk42;
    if (--self->timer != 0)
        return;
    self->unk5++;
    self->x_pos.i.hi += self->unk15 != 0 ? -general_ring_offsets[(self->unk2 - 4) << 1] : general_ring_offsets[(self->unk2 - 4) << 1];
    self->y_pos.i.hi += general_ring_offsets[((self->unk2 - 4) << 1) + 1];
    set_animation(self, 0x23);
    angle = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    set_velocity_from_angle(MOVING_OBJECT(self), angle);
    self->x_vel.val *= 3;
    self->y_vel.val *= 3;
    self->unk42 &= 0x7FFF;
    func_8001540C(2, SATURN_SOUND(7, 0xE1), self);
}
#endif

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
                    func_8001540C(2, SATURN_SOUND(4, 0xDE), self);
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
        func_8001540C(2, SATURN_SOUND(4, 0xDE), self);
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
