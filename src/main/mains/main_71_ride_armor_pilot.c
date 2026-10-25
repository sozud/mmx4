// MainObj, main_object_update_funcs[71]
// 80089AA4..8008ADFC
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_71_ride_armor_pilot.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/collision.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/collision.h"
#endif

// ride_armor_pilot_despawn_funcs
extern void (*ride_armor_pilot_despawn_funcs[])(struct MainObj*);
void ride_armor_pilot_despawn_remove(struct MainObj* arg0);
void ride_armor_pilot_despawn_idle(void);
void ride_armor_pilot_despawn_idle2(void);

// ride_armor_pilot_state_funcs
extern void (*ride_armor_pilot_state_funcs[])(struct MainObj*);
void func_80089AA4(struct MainObj*);

void ride_armor_pilot_despawn(struct MainObj* arg0);

extern void* ride_armor_pilot_animations[31];
extern struct Unk_unk68 ride_armor_pilot_terrain_box;

// ride_armor_pilot_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_80089AA4);
#else
void func_80089AA4(struct MainObj* self)
{
    s32 x_pos;
    s32 y_pos;
    s8 damage;

    x_pos = self->x_pos.val;
    y_pos = self->y_pos.val;
    self->state = 1;
    self->unk5 = 2;
    self->on_screen = 1;
    self->hp = 0x18;
    damage = 5;
    do {
    } while (0); // Empty loop: scheduling barrier for perfect match
    self->animation_table = (const u8* const*)ride_armor_pilot_animations;
    self->hurt_box = ride_armor_pilot_hurt_box;
    self->attack_box = ride_armor_pilot_attack_box;
    self->terrain_box = &ride_armor_pilot_terrain_box;
    self->unk6 = 0;
    self->unk7 = 0;
    self->unk7C = 0;
    self->contact_damage = damage;
    self->invincibility_timer = 0;
    self->collision_data = D_80108184;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->ext.main_71.unk8A = 0;
    self->ext.main_71.unk89 = 0;
    self->ext.main_71.unk88 = 0;
    self->ext.main_71.unk87 = 0;
    self->ext.main_71.unk86 = 0;
    self->ext.main_71.unk8D = 0;
    self->unk18.val = x_pos;
    self->unk1C.val = y_pos;
}
#endif

void ride_armor_pilot_spawn_dust(struct VisualObj* self, u8 arg1)
{
    struct VisualObj* obj;

    obj = find_free_visual_obj();
    if (obj == NULL) {
        return;
    }
    obj->active = self->active;
    obj->id = 0xC;
    obj->unk2 = arg1;
    obj->x_pos.val = self->x_pos.val;
    obj->y_pos.val = self->y_pos.val;
    obj->animation_table = self->animation_table;
    obj->unk40 = self->unk40;
    obj->unk3C = self->unk3C;
    obj->unk42 = self->unk42 & 0x7FFF;
    obj->unk16 = self->unk16;
    obj->unk15 = self->unk15;
    obj->unk50 = (struct PlayerObj*)self;
}

u8 ride_armor_pilot_update_facing(struct MainObj* self)
{
    u8 flags;

    if (self->unk2 == 0) {
        flags = self->ext.main_71.unk8A;
        if (flags != 0) {
            if (flags & 1) {
                self->unk15 = PLAYER_FACING_RIGHT;
            } else {
                self->unk15 = 0;
            }
            return 1;
        }
    } else {
        if ((self->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
            self->unk15 = PLAYER_FACING_RIGHT;
        } else {
            self->unk15 = 0;
        }
    }

    return 0;
}

// ride_armor_pilot_check_walls
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

extern struct Unk_unk68 ride_armor_pilot_guard_box;
extern struct Unk_unk68 ride_armor_pilot_debris[2];
extern void (*ride_armor_pilot_step_funcs[12])(struct MainObj*);
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8008AAF4(struct MainObj* self);
void func_80089C7C(struct MainObj* self);
void func_8008AC40(struct MainObj* self);
void func_8008A9F4(struct MainObj* self);
void func_8008A4D8(struct MainObj* self);
void func_8008A3B0(struct MainObj* self);
void func_80089C7C(struct MainObj*);
void ride_armor_pilot_check_dash(struct MainObj*);
void ride_armor_pilot_set_step(struct BaseObj*, s8);
void ride_armor_pilot_set_jump_speed(struct MainObj*);
void ride_armor_pilot_stub(struct MainObj*, s32, s32);
void ride_armor_pilot_return_to_idle(struct MainObj*);
void ride_armor_pilot_apply_x_speed(struct MainObj*);
void ride_armor_pilot_set_walk_speed(struct MainObj*);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80089C7C(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;
    s32 dx;
    s16 x;
    s16 y;

    if (self->unk5 < 2)
        return;
    dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (dx > -0x41 && dx < 0x41) {
        ext->unk87 = 1;
    } else if (self->unk2 == 0) {
        if (dx <= -0x98 || dx >= 0x98)
            ext->unk88 = 1;
        ext->unk8A = dx < 0 ? 1 : 2;
    } else {
        ext->unk8A = 0;
    }
    if (self->air_state != 0 || ext->unk86 != 0 || ext->unk87 != 0 || (ext->unk8D & 8) != 0)
        return;
    y = self->y_pos.u.hi + self->terrain_box->unk3;
    if (ext->unk8A & self->collision_flags) {
        u32 i;
        x = self->unk15 == 0 ? self->x_pos.u.hi - self->terrain_box->unk2
                             : self->x_pos.u.hi + self->terrain_box->unk2 + 1;
        y--;
        for (i = 0; i < 5; i++, y -= 0x10) {
            if ((u8)func_8002D724(PLAYER_OBJECT(self), x, y) == 0) {
                ext->unk86 = 1;
                break;
            }
        }
        if (ext->unk86 == 0)
            ext->unk8A = 0;
    } else if ((u8)func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi, y + 2) == 0) {
        ext->unk86 = 1;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_80089C7C);
#endif

void ride_armor_pilot_set_step(struct BaseObj* self, s8 arg1)
{
    self->unk5 = arg1;
    self->unk6 = 0;
}

void ride_armor_pilot_check_dash(struct MainObj* self)
{
    if (self->unk5 < 2) {
        return;
    }
    if (self->unk5 == 6) {
        return;
    }
    if (self->unk5 == 7) {
        return;
    }
    if (self->unk5 == 0xB) {
        return;
    }
    if (self->ext.main_71.unk88 == 0) {
        return;
    }
    if (self->ext.main_71.unk8D & 8) {
        return;
    }
    if (self->air_state != 0) {
        return;
    }
    if (self->ext.main_71.unk86 == 0) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 6);
    }
}

void ride_armor_pilot_return_to_idle(struct MainObj* self)
{
    self->unk5 = 2;
    self->unk6 = 0;
    self->ext.main_71.unk88 = 0;
    self->ext.main_71.unk86 = 0;
    self->ext.main_71.unk87 = 0;
    self->hurt_box = ride_armor_pilot_hurt_box;
    self->attack_box = ride_armor_pilot_attack_box;
    self->contact_damage = 5;
}

void ride_armor_pilot_apply_x_speed(struct MainObj* self)
{
    self->x_pos.val += self->x_speed;
}

void ride_armor_pilot_set_walk_speed(struct MainObj* self)
{
    if (self->unk15 != 0) {
        self->x_speed = FIXED(1.375);
    } else {
        self->x_speed = FIXED(-1.375);
    }
}

void ride_armor_pilot_set_jump_speed(struct MainObj* self)
{
    s32 velocity;

    if (ride_armor_pilot_update_facing(self) & 0xFF) {
        velocity = self->ext.main_71.unk84 << 8;
        if (self->unk15 == 0) {
            velocity = -velocity;
        }
        self->x_speed = velocity;
    }
}

void ride_armor_pilot_set_scripted_speed(struct MainObj* self)
{
    s32 var_v1;
    u8 temp_a1;

    temp_a1 = self->ext.main_71.unk8A;
    if (temp_a1 != 0) {
        var_v1 = self->ext.main_71.unk84 << 8;
        if (!(temp_a1 & 1)) {
            var_v1 = -var_v1;
        }
        self->x_speed = var_v1;
    }
}

void ride_armor_pilot_stub(struct MainObj* self, s32 arg1, s32 arg2)
{
}

// ride_armor_pilot_idle
void func_8008A064(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        self->ext.main_71.unk8A = 0;
        set_animation(self, 0);
        self->ext.main_71.unk84 = 0x160;
        self->ext.main_71.unk8C = get_random() & 0x3F;
        ride_armor_pilot_update_facing(self);
    }
    if (!(self->collision_flags & 8)) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        return;
    }
    if (self->ext.main_71.unk8C == 0) {
        if (!(self->ext.main_71.unk8D & 2)) {
            if (ride_armor_pilot_update_facing(self)) {
                ride_armor_pilot_set_step(BASE_OBJECT(self), 3);
                return;
            }
            if (self->ext.main_71.unk86 != 0) {
                ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
                return;
            }
            if (self->ext.main_71.unk87 != 0) {
                ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
                return;
            }
        }
    } else {
        self->ext.main_71.unk8C--;
    }
    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_walk
void func_8008A180(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        set_animation(self, 1);
        self->ext.main_71.unk84 = 0x160;
        ride_armor_pilot_update_facing(self);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
        self->ext.main_71.unk8D &= 0xF3;
    }

    if (!(self->collision_flags & 8)) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        return;
    }

    if (!(self->ext.main_71.unk8D & 2)) {
        if (!(ride_armor_pilot_update_facing(self) & 0xFF)) {
            ride_armor_pilot_return_to_idle(self);
            return;
        }
        if (self->ext.main_71.unk86 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
            return;
        }
        if (self->ext.main_71.unk87 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
            return;
        }
        ride_armor_pilot_set_walk_speed(self);
        ride_armor_pilot_apply_x_speed(self);
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            func_8001540C(2, SATURN_SOUND(0x3D, 0x140), self);
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void ride_armor_pilot_punch(struct MainObj* self)
{
    s8 event;

    if (self->unk6 == 0) {
        self->unk6++;
        set_animation(self, 9);
        ride_armor_pilot_stub(self, 2, 0);
        func_8001540C(2, SATURN_SOUND(0x41, 0x144), self);
    }

    if (self->animation_step.fields.relative_step == 0) {
        ride_armor_pilot_return_to_idle(self);
        self->ext.main_71.unk87 = 0;
        return;
    }

    event = self->animation_step.fields.event;
    if (event == 1) {
        self->attack_box = &ride_armor_pilot_punch_box;
        self->contact_damage = 6;
    } else if (event == 2) {
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
    }

    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_jump
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008A3B0);
#else
void func_8008A3B0(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        self->y_speed = 0x58000;
        self->gravity = 0x4200;
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 1;
        set_animation(self, 2);
        ride_armor_pilot_stub(self, 2, 0);
        self->collision_flags &= ~8;
        ride_armor_pilot_spawn_dust((struct VisualObj*)self, 6);
        self->attack_box = &ride_armor_pilot_punch_box;
        self->contact_damage = 6;
        func_8001540C(2, SATURN_SOUND(0x40, 0x143), self);
    }
    if (self->ext.main_71.unk87) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 0xA);
        return;
    }
    if (self->ext.main_71.unk8D & 2)
        return;
    self->x_speed = 0;
    ride_armor_pilot_set_jump_speed(self);
    if (!(self->collision_flags & 4)) {
        if (self->y_speed >= 0) {
            move_with_gravity(MOVING_OBJECT(self));
            return;
        }
    }
    ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
}
#endif

// ride_armor_pilot_land
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008A4D8);
#else
void func_8008A4D8(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6++;
        ext->unk84 = 0x160;
        self->air_state = 0;
        set_animation(self, 4);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        ext->unk86 = 0;
        self->contact_damage = 5;
        self->collision_flags |= 8;
        func_8001540C(2, SATURN_SOUND(0x3D, 0x140), self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        ride_armor_pilot_return_to_idle(self);
        return;
    }
    if (!(ext->unk8D & 2)) {
        if (!(self->collision_flags & 8))
            ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        else if (ext->unk87)
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
        else if (ride_armor_pilot_update_facing(self)) {
            ride_armor_pilot_set_walk_speed(self);
            ride_armor_pilot_apply_x_speed(self);
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}
#endif

// ride_armor_pilot_jump_punch
void func_8008A60C(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        ride_armor_pilot_stub(self, 0, 1);
        set_animation(self, 0xA);
        func_8001540C(2, SATURN_SOUND(0x41, 0x144), self);
    }

    if (self->collision_flags & 8) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 5);
        return;
    }

    if (!(self->ext.main_71.unk8D & 2)) {
        self->x_speed = 0;
        self->x_accel = 0;
        ride_armor_pilot_set_scripted_speed(self);

        if ((self->y_speed >= 0) && (self->collision_flags & 4)) {
            self->y_speed = 0;
        }

        if (self->animation_step.fields.relative_step == 0) {
            s32 state = 8;
            if (self->y_speed < 0) {
                state = 4;
            }
            self->unk5 = state;
        } else {
            s32 fall_speed = FIXED(-5.875);
            if (self->y_speed < fall_speed) {
                self->y_speed = fall_speed;
            }
            move_with_gravity(ANIMATED_OBJECT(self));
        }

        if (self->animation_step.fields.event == 1) {
            self->attack_box = &ride_armor_pilot_punch_box;
            self->contact_damage = 6;
        } else if (self->animation_step.fields.event == 2) {
            self->attack_box = ride_armor_pilot_attack_box;
            self->contact_damage = 5;
        }
    }

    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_dash
void func_8008A778(struct MainObj* self)
{
    if (self->unk6 == 0) {
        ride_armor_pilot_update_facing(self);
        self->unk6 = 1;
        self->ext.main_71.unk84 = 0x420;

        if (self->unk15 != 0) {
            self->x_speed = FIXED(4.125);
        } else {
            self->x_speed = FIXED(-4.125);
        }

        self->ext.main_71.unk8E = 0x1E;
        ride_armor_pilot_spawn_dust(VISUAL_OBJECT(self), 5);
        set_animation(self, 5);
        func_8001540C(2, SATURN_SOUND(0x3F, 0x142), self);
        self->ext.main_71.unk8D |= 4;
    }

    if (!(self->ext.main_71.unk8D & 2)) {
        if (self->ext.main_71.unk86 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
        } else if (self->ext.main_71.unk87 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 0xB);
        } else if (!(self->collision_flags & 8)) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        } else if (!(self->collision_flags & 3)) {
            ride_armor_pilot_apply_x_speed(self);
            if (self->ext.main_71.unk8E-- < 0) {
                ride_armor_pilot_set_step(BASE_OBJECT(self), 7);
                return;
            }
        } else {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 7);
            return;
        }
    }

    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_dash_end
void func_8008A8E4(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->ext.main_71.unk84 = 0x160;
        set_animation(self, 6);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
        self->ext.main_71.unk8D &= 0xFB;
    }

    if (!(self->ext.main_71.unk8D & 2)) {
        if (self->animation_step.fields.relative_step == 0) {
            ride_armor_pilot_return_to_idle(self);
            return;
        }
        if (self->ext.main_71.unk86 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
            return;
        }
        if (self->ext.main_71.unk87 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
            return;
        }
        if (self->ext.main_71.unk8A != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 3);
            return;
        }
    }

    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_guard
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008A9F4);
#else
void func_8008A9F4(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        set_animation(self, 8);
        self->attack_box = &ride_armor_pilot_guard_box;
        self->contact_damage = 6;
        ext->unk8D |= 8;
        func_8001540C(2, SATURN_SOUND(0x3C, 0x13F), self);
    }

    ext->unk8E--;
    if (!(self->collision_flags & 8)) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        return;
    }
    if (!(ext->unk8D & 2)) {
        if ((self->collision_flags & 3) || (self->animation_step.fields.event & 1)) {
            if ((s8)ext->unk8E < 0) {
                ride_armor_pilot_set_step(BASE_OBJECT(self), 7);
                ext->unk8D &= ~8;
            } else {
                ride_armor_pilot_apply_x_speed(self);
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}
#endif

// ride_armor_pilot_fall
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008AAF4);
#else
void func_8008AAF4(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = 0x4200;
        self->air_state = 1;
        set_animation(self, 3);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
    }
    if (self->collision_flags & 8) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 5);
        return;
    }
    if (ext->unk8D & 2)
        return;
    if (ext->unk87 != 0) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 0xA);
        return;
    }
    if (self->id == 0x48 && ext->unk86 != 0) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 0xC);
        return;
    }
    self->x_speed = 0;
    ride_armor_pilot_set_jump_speed(self);
    if (self->y_speed < -0x5E000)
        self->y_speed = -0x5E000;
    move_with_gravity(ANIMATED_OBJECT(self));
}
#endif

void ride_armor_pilot_reset(struct MainObj* self)
{
    ride_armor_pilot_return_to_idle(self);
}

// ride_armor_pilot_main
void func_8008AC40(struct MainObj* self)
{
    s32 status;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (self->ext.main_71.unk8B != 0)
        self->ext.main_71.unk8B--;
    func_80089C7C(self);
    ride_armor_pilot_check_dash(self);
    ride_armor_pilot_step_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    func_8002D9BC(self);
    status = func_8002DD04(self);
    if (status < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(7, ride_armor_pilot_debris, self);
        drop_item(BASE_OBJECT(self), 0x11);
        self->state = 2;
        self->unk5 = 0;
    } else if (status != 0) {
        ride_armor_pilot_spawn_dust((struct VisualObj*)self, 8);
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0)
        is_on_screen(BASE_OBJECT(self));
    else {
        self->state = 2;
        self->unk5 = 0;
    }
}

void ride_armor_pilot_despawn_remove(struct MainObj* self)
{
    self->unk42 &= 0x7FFF;
    despawn_object(OBJECT_HEADER(self));
}

void ride_armor_pilot_despawn_idle(void)
{
}

void ride_armor_pilot_despawn_idle2(void)
{
}

void ride_armor_pilot_despawn(struct MainObj* self)
{
    ride_armor_pilot_despawn_funcs[self->unk5](self);
}

void ride_armor_pilot_update(struct MainObj* self)
{
    ride_armor_pilot_state_funcs[self->state](self);
}

#ifdef MMX4_WIN32
struct Unk_unk68 ride_armor_pilot_anim_0[5] = {
#else
struct Unk_unk68 ride_armor_pilot_anim_0[13] = {
#endif
    { 100, 0, 1, 0 },
    { 7, 0, 1, 11 },
    { 1, 1, 1, 12 },
    { 49, 0, 1, 12 },
    { 8, 0, -4, 11 },
#ifdef MMX4_WIN32
};

struct Unk_unk68 ride_armor_pilot_anim_1[8] = {
#endif
    { 6, 0, 1, 1 },
    { 6, 1, 1, 2 },
    { 6, 0, 1, 3 },
    { 10, 0, 1, 4 },
    { 6, 0, 1, 5 },
    { 6, 0, 1, 6 },
    { 6, 0, 1, 7 },
    { 10, 0, -8, 8 },
};

union AnimationStep ride_armor_pilot_anim_2[] = {
    { 6, 0, 0, 0x09 },
};

union AnimationStep ride_armor_pilot_anim_3[] = {
    { 6, 0, 0, 0x0A },
};

union AnimationStep ride_armor_pilot_anim_4[] = {
    { 2, 0, 1, 0x0B },
    { 8, 0, 1, 0x0C },
    { 7, 0, 1, 0x0B },
    { 8, 0, 0, 0x00 },
};

union AnimationStep ride_armor_pilot_anim_5[] = {
    { 4, 0, 1, 0x0D },
    { 8, 0, 0, 0x0E },
};

union AnimationStep ride_armor_pilot_anim_6[] = {
    { 4, 0, 0, 0x0D },
};

union AnimationStep ride_armor_pilot_anim_7[] = {
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 3, 0, 1, 0x10 },
    { 6, 0, 0, 0x0F },
};

u8 ride_armor_pilot_anim_8[16] = { 2, 0, 1, 17, 2, 0, 1, 18, 2, 17, 1, 17, 2, 17, 255, 18 };

union AnimationStep ride_armor_pilot_anim_9[] = {
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x1A },
    { 1, 0, 1, 0x1B },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x1F },
    { 1, 1, 1, 0x20 },
    { 1, 0, 1, 0x21 },
    { 1, 0, 1, 0x20 },
    { 1, 0, 1, 0x21 },
    { 1, 0, 1, 0x20 },
    { 16, 0, 0, 0x21 },
    { 5, 2, 0, 0x12 },
    { 5, 0, 0, 0x0F },
};

union AnimationStep ride_armor_pilot_anim_10[] = {
    { 1, 0, 1, 0x09 },
    { 1, 0, 1, 0x22 },
    { 1, 0, 1, 0x23 },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x28 },
    { 6, 0, 1, 0x29 },
    { 6, 0, 0, 0x2A },
    { 6, 0, 0, 0x2B },
};

union AnimationStep ride_armor_pilot_anim_11[] = {
    { 5, 0, 1, 0x16 },
    { 4, 0, 0, 0x17 },
};

union AnimationStep ride_armor_pilot_anim_12[] = {
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 0, 0x1A },
};

union AnimationStep ride_armor_pilot_anim_13[] = {
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x12 },
    { 1, 0, 0, 0x11 },
};

u8 ride_armor_pilot_anim_14[12] = { 1, 0, 1, 17, 1, 0, 1, 20, 1, 0, 255, 21 };

union AnimationStep ride_armor_pilot_anim_15[] = {
    { 5, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 0, 0x0F },
};

union AnimationStep ride_armor_pilot_anim_16[] = {
    { 5, 0, 1, 0x2C },
    { 5, 0, 1, 0x2D },
    { 5, 0, 1, 0x2E },
    { 5, 0, 1, 0x2F },
    { 5, 0, 1, 0x30 },
    { 5, 0, 1, 0x31 },
    { 5, 0, 1, 0x32 },
    { 5, 0, 1, 0x33 },
    { 5, 0, 0, 0x34 },
};

struct Unk_unk68 ride_armor_pilot_anim_17[12] = {
    { 2, 0, 1, 53 },
    { 2, 0, 1, 54 },
    { 2, 0, 1, 55 },
    { 2, 0, 1, 56 },
    { 2, 0, 1, 57 },
    { 2, 0, 1, 58 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, 1, 57 },
    { 1, 0, -11, 58 },
};

union AnimationStep ride_armor_pilot_anim_24[] = {
    { 2, 0, 0, 0x3B },
};

union AnimationStep ride_armor_pilot_anim_25[] = {
    { 2, 0, 0, 0x3C },
};

union AnimationStep ride_armor_pilot_anim_26[] = {
    { 2, 0, 0, 0x3D },
};

union AnimationStep ride_armor_pilot_anim_27[] = {
    { 2, 0, 0, 0x3E },
};

union AnimationStep ride_armor_pilot_anim_28[] = {
    { 2, 0, 0, 0x3F },
};

union AnimationStep ride_armor_pilot_anim_29[] = {
    { 2, 0, 0, 0x40 },
};

union AnimationStep ride_armor_pilot_anim_30[] = {
    { 2, 0, 0, 0x41 },
};

struct Unk_unk68 ride_armor_pilot_anim_22[4] = {
    { 1, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 1, 0, 1, 66 },
    { 2, 0, -3, 67 },
};

struct Unk_unk68 ride_armor_pilot_anim_23[4] = {
    { 1, 0, 1, 68 },
    { 2, 0, 1, 69 },
    { 1, 0, 1, 68 },
    { 2, 0, -3, 69 },
};

void* ride_armor_pilot_animations[31] = {
    ride_armor_pilot_anim_0,
#ifdef MMX4_WIN32
    ride_armor_pilot_anim_1,
#else
    &ride_armor_pilot_anim_0[5],
#endif
    ride_armor_pilot_anim_2,
    ride_armor_pilot_anim_3,
    ride_armor_pilot_anim_4,
    ride_armor_pilot_anim_5,
    ride_armor_pilot_anim_6,
    ride_armor_pilot_anim_7,
    ride_armor_pilot_anim_8,
    ride_armor_pilot_anim_9,
    ride_armor_pilot_anim_10,
    ride_armor_pilot_anim_11,
    ride_armor_pilot_anim_12,
    ride_armor_pilot_anim_13,
    ride_armor_pilot_anim_14,
    ride_armor_pilot_anim_15,
    ride_armor_pilot_anim_16,
    ride_armor_pilot_anim_17,
    ride_armor_pilot_anim_17,
    ride_armor_pilot_anim_17,
    ride_armor_pilot_anim_16,
    ride_armor_pilot_anim_17,
    ride_armor_pilot_anim_22,
    ride_armor_pilot_anim_23,
    ride_armor_pilot_anim_24,
    ride_armor_pilot_anim_25,
    ride_armor_pilot_anim_26,
    ride_armor_pilot_anim_27,
    ride_armor_pilot_anim_28,
    ride_armor_pilot_anim_29,
    ride_armor_pilot_anim_30,
};

u8 ride_armor_pilot_hurt_box[4] = { 0xED, 0xDD, 40, 69 };

u8 ride_armor_pilot_attack_box[4] = { 0xF4, 0xE7, 24, 56 };

struct Unk_unk68 ride_armor_pilot_terrain_box = { 0, -1, 15, 33 };

struct Unk_unk68 ride_armor_pilot_guard_box = { -39, -16, 49, 48 };

struct Unk_unk68 ride_armor_pilot_punch_box = { -55, -47, 65, 77 };

struct Unk_unk68 ride_armor_pilot_debris[2] = {
    { 24, 25, 26, 27 },
    { 28, 29, 30, 0 },
};

void (*ride_armor_pilot_step_funcs[12])() = {
    enemy_hit_reaction,
    ride_armor_pilot_reset,
    func_8008A064,
    func_8008A180,
    func_8008AAF4,
    func_8008A4D8,
    func_8008A778,
    func_8008A8E4,
    func_8008A3B0,
    ride_armor_pilot_punch,
    func_8008A60C,
    func_8008A9F4,
};

void (*ride_armor_pilot_despawn_funcs[3])() = {
    ride_armor_pilot_despawn_remove,
    ride_armor_pilot_despawn_idle,
    ride_armor_pilot_despawn_idle2,
};

void (*ride_armor_pilot_state_funcs[3])() = {
    func_80089AA4,
    func_8008AC40,
    ride_armor_pilot_despawn,
};
