// MainObj, main_object_update_funcs[27]
// 800586F0..80059C48
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_27_dash_gunner.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/collision_bounds.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/collision_bounds.h"
#endif

// dash_gunner_state_funcs
extern void (*dash_gunner_state_funcs[])(struct MainObj*);

void dash_gunner_explode(struct MainObj*);
void dash_gunner_despawn(struct MainObj*);

// dash_gunner_step_funcs
void dash_gunner_resume_step(struct MainObj* arg0);
void dash_gunner_run(struct MainObj* arg0);
void dash_gunner_wait_for_player(struct MainObj* arg0);
void dash_gunner_turn(struct MainObj* arg0);
void dash_gunner_shoot(struct MainObj* arg0);

void dash_gunner_dash(struct MainObj* arg0);

// dash_gunner_turn_funcs
void dash_gunner_turn_brake(struct MainObj*);

void func_80059154(struct MainObj*);

// dash_gunner_shoot_funcs
void dash_gunner_shoot_raise(struct MainObj*);
void dash_gunner_shoot_aim(struct MainObj*);

void dash_gunner_shoot_wait(struct MainObj*);
void dash_gunner_shoot_lower(struct MainObj*);
void func_80059590(struct MainObj*);

void dash_gunner_dash_brake(struct MainObj*);

extern void (*dash_gunner_run_funcs[])(struct MainObj*);
extern void (*dash_gunner_turn_funcs[])(struct MainObj*);
extern void (*dash_gunner_shoot_funcs[])(struct MainObj*);
extern void (*dash_gunner_dash_funcs[])(struct MainObj*);

#if defined(MMX4_PC) || defined(MMX4_SATURN)
extern union AnimationStep* dash_gunner_animations[12];
extern struct Unk_unk68 dash_gunner_boxes[10];
extern struct Unk_unk68* D_8013B828;
extern struct Unk_unk68* D_8013B82C;
extern struct Unk_unk68* D_8013B830;
extern struct Unk_unk68* D_8013B834;
extern void (*dash_gunner_step_funcs[])(struct MainObj*);
extern struct Unk_unk68 D_80106FF4[];
extern u8 dash_gunner_debris[4];
#endif

void dash_gunner_update(struct MainObj* self)
{
    dash_gunner_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// dash_gunner_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80058740(struct MainObj* arg0);
void func_80058AC8(struct MainObj* arg0);
void func_80059640(struct MainObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80058740(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    u8 subtype;

    arg0->hp = 6;
    arg0->invincibility_timer = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->air_state = 0;
    arg0->animation_table = (const u8* const*)dash_gunner_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->hurt_box = NULL;
    arg0->attack_box = NULL;
    arg0->collision_flags = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    ext->unk8B = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    switch ((u8)arg0->unk2) {
    case 0:
    case 4:
        arg0->x_speed = -0x18000;
        ext->unk90 = 0;
        arg0->unk15 = 0;
        ext->unk80 = 0;
        ext->unk8C = 0x1E;
        func_8001540C(2, SATURN_SOUND(0x51, 0x42), arg0);
        arg0->unk5 = 2;
        break;
    case 1:
    case 5:
        arg0->unk15 = PLAYER_FACING_RIGHT;
        ext->unk8C = 0x1E;
        arg0->unk5 = 3;
        ext->unk90 = 0;
        arg0->x_speed = 0x18000;
        ext->unk80 = 0;
        arg0->unk7A = 1;
        break;
    case 2:
    case 6:
        ext->unk82 = 0x1E;
        ext->unk80 = 1;
        ext->unk8C = 0x12C;
        ext->unk90 = 0;
        arg0->unk15 = 0;
        ext->unk88 = 0;
        ext->unk89 = 0x14;
        ext->unk8A = 0;
        func_8001540C(2, SATURN_SOUND(0x51, 0x42), arg0);
        arg0->unk5 = 6;
        break;
    case 3:
    case 7:
        arg0->unk15 = PLAYER_FACING_RIGHT;
        ext->unk82 = 0x1E;
        ext->unk8C = 0x12C;
        ext->unk89 = 0x14;
        ext->unk90 = 0;
        ext->unk80 = 1;
        ext->unk88 = 1;
        ext->unk8A = 0;
        arg0->unk7A = 1;
        arg0->unk5 = 3;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
        subtype = arg0->unk2;
        ext->unk90 = subtype < 10 ? 1 : 2;
        ext->unk91 = 0x30;
        if (subtype >= 10)
            ext->unk92 = 2;
        arg0->unk15 = (subtype & 1) ? PLAYER_FACING_RIGHT : 0;
        ext->unk80 = 0;
        ext->unk8A = 0;
        func_8001540C(2, SATURN_SOUND(0x51, 0x42), arg0);
        arg0->x_speed = (subtype & 1) ? 0x18000 : -0x18000;
        arg0->unk5 = 2;
        break;
    }

    subtype = arg0->unk2;
    if (subtype < 4 || (u8)(subtype - 8) < 4) {
        arg0->contact_damage = 6;
        arg0->terrain_box = &dash_gunner_boxes[4];
        D_8013B828 = &dash_gunner_boxes[0];
        D_8013B82C = &dash_gunner_boxes[1];
        D_8013B830 = &dash_gunner_boxes[3];
        D_8013B834 = &dash_gunner_boxes[2];
    } else {
        arg0->contact_damage = 7;
        arg0->terrain_box = &dash_gunner_boxes[9];
        D_8013B828 = &dash_gunner_boxes[5];
        D_8013B82C = &dash_gunner_boxes[6];
        D_8013B830 = &dash_gunner_boxes[8];
        D_8013B834 = &dash_gunner_boxes[7];
    }
    set_animation(arg0, 1);
    arg0->state = 1;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_27_dash_gunner", func_80058740);
#endif

// dash_gunner_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80058AC8(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    s32 facing_player;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    dash_gunner_step_funcs[arg0->unk5](arg0);
    if (engine_obj.stage == 3 && arg0->x_pos.i.hi < 0x20)
        arg0->x_pos.i.hi = 0x20;
    if ((u8)arg0->unk2 < 4) {
        if (arg0->x_pos.i.hi > 0x780)
            arg0->x_pos.i.hi = 0x780;
    } else if (arg0->x_pos.i.hi > 0x980) {
        arg0->x_pos.i.hi = 0x980;
    }
    if (arg0->unk5 == 3)
        return;
    ext->saved_unk5 = arg0->unk5;
    ext->unk84 = g_Player.x_pos.val;
    if (arg0->state != 2) {
        arg0->attack_box = (const u8*)(ext->unk8B != 0 ? D_8013B82C : D_8013B828);
        func_8002D9BC(arg0);
        arg0->attack_box = (const u8*)D_8013B834;
        func_8002D9BC(arg0);
    }
    facing_player = arg0->unk15 == 0 ? g_Player.x_pos.i.hi < arg0->x_pos.i.hi
                                     : arg0->x_pos.i.hi < g_Player.x_pos.i.hi;
    if (ext->unk8B == 0 && facing_player) {
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->hurt_box = (const u8*)D_8013B828;
        func_8002DD04(arg0);
    } else {
        arg0->collision_data = (const u16*)D_80106FF4;
        arg0->hurt_box = (const u8*)D_8013B830;
        if (func_8002DD04(arg0) < 0) {
            spawn_explosion(BASE_OBJECT(arg0));
            spawn_debris(4, dash_gunner_debris, arg0);
            drop_item(BASE_OBJECT(arg0), 0x11);
            arg0->unk7C = 0x20;
            arg0->unk7E = 6;
            arg0->on_screen = 0;
            STOP_SOUND(2, 0x51, 0x5);
            arg0->state = 2;
            return;
        }
    }
    if (arg0->state == 2)
        return;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x60, 0x60) != 0) {
        STOP_SOUND(2, 0x51, 0x5);
        arg0->state = 3;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_27_dash_gunner", func_80058AC8);
#endif

void dash_gunner_explode(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->state = 3;
    } else if (--self->unk7E == 0) {
        self->unk7E = 6;
        func_800AF878(self, 1, 16, 16);
    }
}

void dash_gunner_despawn(struct MainObj* self)
{
    self->unk7A = 0;
    self->ext.raw[0] = 0;
    self->ext.raw[1] = 0;
    self->ext.raw[2] = 0;
    self->ext.raw[3] = 0;
    self->ext.raw[5] = 0;
    despawn_object(OBJECT_HEADER(self));
}

void dash_gunner_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_27.saved_unk5;
}

void dash_gunner_run(struct MainObj* self)
{
    dash_gunner_run_funcs[self->unk6](self);
}

void dash_gunner_run_move(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_27.unk8C == 0) {
        set_animation(self, 3);
        self->x_speed = 0;
        STOP_SOUND(2, 0x51, 0x5);
        self->unk5 = 5;
        self->unk6 = 0;
        return;
    }
    if (self->ext.main_27.unk90 != 0 && --self->ext.main_27.unk91 == 0) {
        if (self->ext.main_27.unk90 == 2) {
            self->ext.main_27.unk91 = 0x30;
            if (--self->ext.main_27.unk92 == 0) {
                self->ext.main_27.unk92 = 2;
                set_animation(self, 3);
                self->x_speed = 0;
                STOP_SOUND(2, 0x51, 0x5);
                self->unk5 = 5;
                self->unk6 = 0;
                return;
            }
        } else {
            self->ext.main_27.unk91 = 0x60;
        }
        self->unk7C = 0x14;
        self->y_speed = 0;
        self->unk5 = 4;
        self->unk6 = 0;
    }
    if (self->unk15 == 0 ? (self->collision_flags & 2) : (self->collision_flags & 1)) {
        self->unk7C = 0x14;
        self->y_speed = 0;
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

void dash_gunner_wait_for_player(struct MainObj* self)
{
    if ((g_Player.x_pos.i.hi - self->x_pos.i.hi) > 0xBC) {
        func_8001540C(2, SATURN_SOUND(0x51, 0x42), self);
        self->unk7A = 0;
        if (self->ext.main_27.unk80 == 0) {
            self->unk5 = 2;
        } else {
            self->unk7C = 1;
            self->unk5 = 7;
        }
        self->unk6 = 0;
    }
}

void dash_gunner_turn(struct MainObj* self)
{
    dash_gunner_turn_funcs[self->unk6](self);
}

void dash_gunner_turn_brake(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_speed == 0) {
        self->x_accel = 0;
    }
    if (--self->unk7C == 0) {
        set_animation(self, 2);
        self->unk6 = 1;
    }
}

void dash_gunner_turn_flip(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk15 ^= PLAYER_FACING_RIGHT;
        set_animation(self, 1);
        self->unk7C = 0x14;
        if (self->ext.main_27.unk8A == 0) {
            self->unk6 = 2;
        } else {
            if (self->unk15 == 0) {
                self->x_speed = FIXED(-4);
            } else {
                self->x_speed = FIXED(4);
            }
            set_animation(self, 7);
            self->unk5 = 7;
            self->unk6 = 1;
        }
    }
}

// dash_gunner_turn_end
void func_80059154(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 1);
        if (self->ext.main_27.unk80 == 0) {
            if (self->unk15 == 0) {
                self->x_speed = FIXED(-1.5);
            } else {
                self->x_speed = FIXED(1.5);
            }
            self->unk5 = 2;
        } else {
            self->ext.main_27.unk89 = 0x14;
            self->ext.main_27.unk88 = 0;
            self->unk5 = 6;
        }
        self->unk6 = 0;
    }
}

void dash_gunner_shoot(struct MainObj* self)
{
    dash_gunner_shoot_funcs[self->unk6](self);
}

void dash_gunner_shoot_raise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->ext.main_27.unk8B = 1;
    }
    if (self->animation_step.fields.event == 1) {
        self->unk7C = 4;
        self->unk7E = 0x1E;
        self->unk6 = 1;
    }
}

void dash_gunner_shoot_aim(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7E == 0) {
        if (self->unk15 == 0) {
            self->x_pos.i.hi -= 6;
        } else {
            self->x_pos.u.hi += 6;
        }
        self->ext.main_27.collision_direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
        if (self->unk15 == 0) {
            self->x_pos.u.hi += 6;
        } else {
            self->x_pos.i.hi -= 6;
        }
        self->unk6 = 2;
    }
}

void dash_gunner_shoot_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    u8 direction;

    animate_object(ANIMATED_OBJECT(self));
    direction = self->ext.main_27.collision_direction;
    if ((direction > 8 && direction < 24)) {
        if (self->unk15 != 0) {
            self->unk7C = 0xA;
            self->unk6 = 3;
        }
    } else if ((direction < 8 || direction > 24) && self->unk15 == 0) {
        self->unk7C = 0xA;
        self->unk6 = 3;
    }
    if (self->unk6 == 3) {
        return;
    }
    set_animation(self, 4);
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0xE;
        shot->unk2 = self->unk2;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk15 = self->unk15;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        set_velocity_from_angle(MOVING_OBJECT(shot), self->ext.main_27.collision_direction);
        shot->state = 0;
        shot->x_vel.val *= 3;
        shot->y_vel.val *= 3;
    }
    if (--self->unk7C == 0) {
        self->unk7C = 0xA;
        self->unk6 = 3;
    } else {
        self->unk7E = 0x14;
        self->unk6 = 1;
    }
}

void dash_gunner_shoot_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 6);
        self->unk6 = 4;
    }
}

void dash_gunner_shoot_lower(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->ext.main_27.unk8B = 0;
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 1);
        self->unk7C = 10;
        self->unk6 = 5;
    }
}

// dash_gunner_shoot_end
void func_80059590(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 1);
        func_8001540C(2, SATURN_SOUND(0x51, 0x42), self);
        if (self->ext.main_27.unk80 == 0) {
            self->ext.main_27.unk8C = 0xB4;
            if (self->unk15 == 0) {
                self->x_speed = FIXED(-1.5);
            } else {
                self->x_speed = FIXED(1.5);
            }
            self->unk5 = 2;
        } else {
            self->ext.main_27.unk89 = 0x14;
            self->ext.main_27.unk8C = 0x12C;
            self->ext.main_27.unk88 = 0;
            self->unk5 = 6;
        }
        self->unk6 = 0;
    }
}

// dash_gunner_hop
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80059640(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    s32 dy;
    s32 dx;

    if (--ext->unk8C == 0 && (arg0->unk15 == 0 ? g_Player.x_pos.i.hi < arg0->x_pos.i.hi : arg0->x_pos.i.hi < g_Player.x_pos.i.hi)) {
        set_animation(arg0, 3);
        arg0->x_speed = 0;
        STOP_SOUND(2, 0x51, 0x5);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        return;
    }
    if (--ext->unk82 == 0) {
        ext->unk82 = 0x1E;
        if ((get_random() & 7) < 5) {
            arg0->unk7C = 0xA;
            arg0->x_speed = 0;
            arg0->unk5 = 7;
            arg0->unk6 = 0;
            return;
        }
    }
    if (ext->unk89 != 0)
        ext->unk89--;
    animate_object(ANIMATED_OBJECT(arg0));
    if (ext->unk88 == 0) {
        dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
        if (dy < 0)
            dy = -dy;
        if (dy < 0x31) {
            dx = arg0->unk15 == 0 ? ext->unk84 - g_Player.x_pos.val
                                  : g_Player.x_pos.val - ext->unk84;
            if (dx > 0x3FFFF) {
                ext->unk88 = 1;
                set_animation(arg0, 7);
            }
        }
    } else {
        dx = g_Player.x_pos.val - ext->unk84;
        if (dx < 0)
            dx = ext->unk84 - g_Player.x_pos.val;
        if (dx <= 0x3FFFF) {
            ext->unk88 = 0;
            set_animation(arg0, 1);
        }
    }
    if (arg0->unk15 == 0 ? (arg0->collision_flags & 2) : (arg0->collision_flags & 1)) {
        arg0->unk7C = 0x14;
        arg0->x_accel = 0;
        arg0->y_speed = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (ext->unk89 == 0 && (arg0->unk15 == 0 ? arg0->x_pos.i.hi < g_Player.x_pos.i.hi : g_Player.x_pos.i.hi < arg0->x_pos.i.hi)) {
        arg0->unk7C = 0x14;
        arg0->x_accel = -0x2000;
        arg0->y_speed = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (ext->unk88 == 0)
        arg0->x_speed = arg0->unk15 != 0 ? 0x20000 : -0x20000;
    else
        arg0->x_speed = arg0->unk15 != 0 ? 0x40000 : -0x40000;
    move_object(MOVING_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_27_dash_gunner", func_80059640);
#endif

void dash_gunner_dash(struct MainObj* self)
{
    dash_gunner_dash_funcs[self->unk6](self);
}

void dash_gunner_dash_start(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = --self->unk7C;
    if (timer != 0) {
        return;
    }

    self->ext.main_27.unk8A = 1;
    if ((self->unk15 == 0 && g_Player.x_pos.i.hi > self->x_pos.i.hi) || (self->unk15 != 0 && g_Player.x_pos.i.hi < self->x_pos.i.hi)) {
        set_animation(self, 2);
        self->unk5 = 4;
        self->unk6 = 1;
        self->unk7C = 1;
        return;
    }
    self->unk7C = 0x14;
    self->unk6 = 1;
    if (self->unk15 == 0) {
        self->x_speed = FIXED(-4);
    } else {
        self->x_speed = FIXED(4);
    }
}

void dash_gunner_dash_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->ext.main_27.unk8C != 1) {
        self->ext.main_27.unk8C--;
    }
    if (--self->unk7C == 0) {
        set_animation(self, 1);
        self->x_accel = FIXED(-0.125);
        self->unk6 = 2;
    }
}

void dash_gunner_dash_brake(struct MainObj* self)
{
    if (self->ext.main_27.unk8C != 1) {
        self->ext.main_27.unk8C--;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_speed == 0) {
        self->x_accel = 0;
        self->x_speed = 0;
        self->ext.main_27.unk88 = 0;
        self->unk7C = 10;
        self->unk6 = 3;
    }
}

void dash_gunner_dash_end(struct MainObj* self)
{
    s16 timer;

    if (self->ext.main_27.unk8C != 1) {
        self->ext.main_27.unk8C--;
    }
    animate_object(ANIMATED_OBJECT(self));
    timer = --self->unk7C;
    if (timer == 0) {
        self->ext.main_27.unk89 = 0;
        self->ext.main_27.unk8A = 0;
        if (((self->unk15 == 0) && (g_Player.x_pos.i.hi > self->x_pos.i.hi)) || ((self->unk15 != 0) && (g_Player.x_pos.i.hi < self->x_pos.i.hi))) {
            self->unk7C = 0x14;
            self->x_accel = 0;
            self->y_speed = 0;
            self->unk5 = 4;
            self->unk6 = 0;
        } else {
            self->unk5 = 6;
            self->unk6 = 0;
        }
    }
}

struct Unk_unk68 dash_gunner_boxes[10] = {
    { -17, -16, 10, 34 },
    { -21, -26, 42, 16 },
    { -8, -2, 33, 6 },
    { -8, -7, 34, 16 },
    { 0, 7, 25, 23 },
    { -24, -27, 17, 54 },
    { -42, -33, 80, 17 },
    { -15, -2, 39, 6 },
    { -15, -7, 40, 16 },
    { 0, 7, 32, 39 },
};

union AnimationStep dash_gunner_anim_0[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, -3, 0x03 },
};

union AnimationStep dash_gunner_anim_1[] = {
    { 3, 0, 1, 0x04 },
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x06 },
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 3, 0, 1, 0x0A },
    { 3, 1, -7, 0x0B },
};

union AnimationStep dash_gunner_anim_2[] = {
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 1, 0, 1, 0x11 },
    { 1, 1, 0, 0x11 },
};

union AnimationStep dash_gunner_anim_3[] = {
    { 2, 0, 1, 0x12 },
    { 6, 0, 1, 0x13 },
    { 3, 0, 1, 0x14 },
    { 3, 0, 1, 0x15 },
    { 4, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 2, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 9, 0, 1, 0x1A },
    { 1, 1, 0, 0x1A },
};

union AnimationStep dash_gunner_anim_4[] = {
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 1, 1, 0, 0x1A },
};

union AnimationStep dash_gunner_anim_5[] = {
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 3, 0, 1, 0x22 },
    { 3, 0, 1, 0x23 },
    { 3, 0, -5, 0x24 },
};

union AnimationStep dash_gunner_anim_6[] = {
    { 6, 0, 1, 0x1A },
    { 2, 0, 1, 0x17 },
    { 2, 2, 1, 0x16 },
    { 2, 0, 1, 0x25 },
    { 4, 0, 1, 0x16 },
    { 3, 0, 1, 0x15 },
    { 3, 0, 1, 0x14 },
    { 6, 0, 1, 0x13 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x26 },
    { 1, 0, 1, 0x27 },
    { 1, 1, 0, 0x27 },
};

union AnimationStep dash_gunner_anim_7[] = {
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2A },
    { 2, 0, 1, 0x2B },
    { 2, 0, 1, 0x2C },
    { 1, 0, 1, 0x2D },
    { 1, 0, 1, 0x2E },
    { 2, 0, 1, 0x2F },
    { 2, 0, 1, 0x30 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 2, 0, 1, 0x34 },
    { 1, 0, 1, 0x35 },
    { 2, 0, 1, 0x36 },
    { 2, 0, -15, 0x37 },
};

union AnimationStep dash_gunner_anim_8[] = {
    { 1, 1, 0, 0x38 },
};

union AnimationStep dash_gunner_anim_9[] = {
    { 1, 1, 0, 0x39 },
};

union AnimationStep dash_gunner_anim_10[] = {
    { 1, 1, 0, 0x3A },
};

union AnimationStep dash_gunner_anim_11[] = {
    { 1, 1, 0, 0x3B },
};

union AnimationStep* dash_gunner_animations[] = {
    dash_gunner_anim_0,
    dash_gunner_anim_1,
    dash_gunner_anim_2,
    dash_gunner_anim_3,
    dash_gunner_anim_4,
    dash_gunner_anim_5,
    dash_gunner_anim_6,
    dash_gunner_anim_7,
    dash_gunner_anim_8,
    dash_gunner_anim_9,
    dash_gunner_anim_10,
    dash_gunner_anim_11,
};

u8 dash_gunner_debris[] = {
    0x08,
    0x09,
    0x0A,
    0x0B,
};

void (*dash_gunner_state_funcs[])() = {
    func_80058740,
    func_80058AC8,
    dash_gunner_explode,
    dash_gunner_despawn,
};

void (*dash_gunner_step_funcs[])() = {
    enemy_hit_reaction,
    dash_gunner_resume_step,
    dash_gunner_run,
    dash_gunner_wait_for_player,
    dash_gunner_turn,
    dash_gunner_shoot,
    func_80059640,
    dash_gunner_dash,
};

void (*dash_gunner_run_funcs[])() = {
    dash_gunner_run_move,
};

void (*dash_gunner_turn_funcs[])(struct MainObj*) = {
    dash_gunner_turn_brake,
    dash_gunner_turn_flip,
    func_80059154,
};

void (*dash_gunner_shoot_funcs[])(struct MainObj*) = {
    dash_gunner_shoot_raise,
    dash_gunner_shoot_aim,
    dash_gunner_shoot_fire,
    dash_gunner_shoot_wait,
    dash_gunner_shoot_lower,
    func_80059590,
};

void (*dash_gunner_dash_funcs[])() = {
    dash_gunner_dash_start,
    dash_gunner_dash_move,
    dash_gunner_dash_brake,
    dash_gunner_dash_end,
};
