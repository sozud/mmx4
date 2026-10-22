// ShotObj, shot_object_update_funcs[22]
// 8009D74C..8009DD40
#include "common.h"
#include "main/shots/shot_22_web_shot.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/player_common.h"
#include "main/collision_bounds.h"

// web_shot_state_funcs
extern void (*web_shot_state_funcs[])(struct ShotObj*);

void web_shot_despawn(struct ShotObj*);

void web_shot_fly(struct ShotObj*);
void web_shot_home(struct ShotObj*);
void web_shot_catch(struct ShotObj*);
void web_shot_hold(struct ShotObj*);
void web_shot_fade(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

u8 web_shot_hit_box[4] = { 0xF7, 0xF8, 0x11, 0x10 };

void web_shot_update(struct ShotObj* self)
{
    web_shot_state_funcs[self->state](self);
}

// web_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009D788(struct ShotObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009D788(struct ShotObj* arg0)
{
    s32 direction;

    arg0->unk54 = web_shot_hit_box;
    arg0->unk50.data = web_shot_hit_box;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk68 = NULL;
    arg0->unk58.data = (u8*)D_80106070;
    direction = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    arg0->unk84.value = direction;
    set_velocity_from_angle(MOVING_OBJECT(arg0), direction);
    arg0->timer = 0x14;
    arg0->unk8A = 0;
    arg0->unk5C = 1;
    arg0->unk60 = 0;
    arg0->unk8C.word = 1;
    arg0->unk62 = 3;
    arg0->unk90.val = 0;
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    set_animation(arg0, 0x16);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_22_web_shot", func_8009D788);
#endif

void web_shot_fly(struct ShotObj* self)
{
    if ((self->unk8C.word == 3) && (g_Player.stun_timer != 0)) {
        self->unk5 = 2;
        web_shot_catch(self);
        return;
    }

    if (--self->timer == 0) {
        self->timer = 0x28;
        self->unk5++;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_22_web_shot", web_shot_home);
#else
void web_shot_home(struct ShotObj* self)
{
    s32 target;
    s32 direction;

    if (self->unk8C.word == 3 && g_Player.stun_timer != 0) {
        self->unk5 = 2;
        web_shot_catch(self);
        return;
    }
    if (self->timer != 0) {
        if (!(WEAPON_FRAME_COUNTER & 3)) {
            target = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
            direction = self->unk84.value;
            if ((direction - (target & 0xFF)) & 0x1F) {
                self->unk84.value = (u32)((target - direction) & 0x1F) < 0x10 ? direction + 1 : direction - 1;
                self->unk84.value &= 0x1F;
                set_velocity_from_angle(MOVING_OBJECT(self), self->unk84.value);
                self->x_vel.val *= 3;
                self->y_vel.val *= 3;
            }
        }
        self->timer--;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}
#endif

void web_shot_pin_player(struct ShotObj* self)
{
    g_Player.x_pos.val = self->x_pos.val;
    g_Player.y_pos.val = self->y_pos.val;
}

void web_shot_catch(struct ShotObj* self)
{
    self->unk5++;
    self->timer = 0x78;
    self->unk2C = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->x_vel.val = 0;
    web_shot_pin_player(self);
    self->unk90.val = 0x30;
}

void web_shot_hold(struct ShotObj* self)
{
    s32 temp_v0;

    web_shot_pin_player(self);
    self->timer -= func_8002BAA4();
    if (self->timer < 0) {
        self->timer = 0x1E;
        self->unk5++;
        g_Player.stun_timer = 0;
        self->unk50.data = 0;
        self->unk54 = 0;
        return;
    }
    self->timer = self->timer - 1;
    temp_v0 = self->unk90.val - 1;
    self->unk90.val = temp_v0;
    if (temp_v0 == 0) {
        player_damage(4);
        self->unk90.val = 0x30;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_shot_fade(struct ShotObj* self)
{

    if (--self->timer == 0) {
        self->on_screen = 0;
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        return;
    }
    if (!(BLINK_CLOCK(WEAPON_FRAME_COUNTER) & 3)) {
        self->on_screen = 0;
        self->unk8A = 1;
    } else {
        self->on_screen = 1;
        self->unk8A = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_shot_main(struct ShotObj* self)
{
    struct WeaponObj* owner;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    web_shot_step_funcs[self->unk5](self);
    owner = self->unk7C;
    if (owner->state == 1 && self->unk8C.word != 0 && g_Player.stun_timer == 0
        && func_8002D9BC(self) != 0 && g_Player.stun_timer != 0) {
        self->unk8C.word = 3;
        self->x_pos.val = g_Player.x_pos.val;
        self->y_pos.val = g_Player.y_pos.val;
    }
    owner = self->unk7C;
    if (self->unk8C.word == 3 && g_Player.stun_timer != 0 && owner->state == 2) {
        self->state = 2;
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        if (self->unk8A == 0) {
            update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        }
    } else {
        self->state = 2;
    }
}

void web_shot_despawn(struct ShotObj* self)
{
    if (self->unk8C.word == 3 && g_Player.stun_timer != 0) {
        g_Player.stun_timer = 0;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*web_shot_state_funcs[])(struct ShotObj*) = {
    func_8009D788,
    web_shot_main,
    web_shot_despawn,
};

void (*web_shot_step_funcs[5])(struct ShotObj*) = {
    web_shot_fly,
    web_shot_home,
    web_shot_catch,
    web_shot_hold,
    web_shot_fade,
};
