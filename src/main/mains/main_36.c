// MainObj, main_object_update_funcs[36]
// 8005F510..8005FDBC
#include "common.h"
#include "func_tables.h"

void latcher_update(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    latcher_state_funcs[self->state](self);
}

// latcher_init
INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005F558);

extern void (*latcher_step_funcs[])(struct MainObj*);

void latcher_main(struct MainObj* self)
{
    latcher_step_funcs[self->unk5](self);
    animate_object(ANIMATED_OBJECT(self));

    if ((SP_CUR_MAIN_OBJ->ext.main_36.unk8D == 0) && (g_Player.stun_timer == 0) && (func_8002D9BC(self) != 0) && (g_Player.stun_timer != 0)) {
        SP_CUR_MAIN_OBJ->ext.main_36.unk8D = 1;
    }

    SP_CUR_MAIN_OBJ->ext.main_36.saved_unk5 = self->unk5;
    latcher_check_hit(self);

    if (func_8002B160(BASE_OBJECT(self)) == 1) {
        self->state = 2;
    }
}

void latcher_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void latcher_resume_step(struct MainObj* self)
{
    self->unk5 = SP_CUR_MAIN_OBJ->ext.main_36.saved_unk5;
}

void latcher_drift(struct MainObj* self)
{
    struct MiscObj* misc;

    if (SP_CUR_MAIN_OBJ->ext.main_36.unk8D != 0 && g_Player.stun_timer != 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            SP_CUR_MAIN_OBJ->ext.main_36.unk8C = 1;
            misc->active = 0x41;
            misc->id = 0xB;
            misc->unk16 = 1;
            misc->unk15 = self->unk15;
            misc->unk40 = self->unk40;
            misc->unk42 = self->unk42;
            misc->unk3C = (void*)self->sprite_frames;
            misc->animation_table = (u32**)latcher_animations;
            misc->x_pos.val = self->x_pos.val;
            misc->y_pos.val = self->y_pos.val;
            misc->bg_offset = g_Player.bg_offset;
            misc->ext.misc_11.active = 0;
            SP_CUR_MAIN_OBJ->ext.main_36.unk84 = misc;
            set_animation(misc, 0);
            self->unk5 = 3;
            self->unk6 = 0;
            set_animation(self, 0);
        }
    }
    move_object(MOVING_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void latcher_grab(struct MainObj* self)
{
    latcher_grab_funcs[self->unk6](self);
    is_on_screen((struct BaseObj*)self);
}

void latcher_grab_home(struct MainObj* self)
{
    s32 distance;

    SP_CUR_MAIN_OBJ->ext.main_36.unk89 = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    set_velocity_from_angle(MOVING_OBJECT(self), SP_CUR_MAIN_OBJ->ext.main_36.unk89);
    SP_CUR_MAIN_OBJ->ext.main_36.unk84->x_vel.val = self->x_speed;
    SP_CUR_MAIN_OBJ->ext.main_36.unk84->y_vel.val = self->y_speed;
    move_object(MOVING_OBJECT(self));
    move_object(MOVING_OBJECT(SP_CUR_MAIN_OBJ->ext.main_36.unk84));
    distance = g_Player.x_pos.i.hi - self->x_pos.i.hi;
    if (distance >= 0 ? distance < 2 : self->x_pos.i.hi - g_Player.x_pos.i.hi < 2) {
        distance = g_Player.y_pos.i.hi - self->y_pos.i.hi;
        if (distance >= 0 ? distance < 2 : self->y_pos.i.hi - g_Player.y_pos.i.hi < 2) {
            set_animation(self, 3);
            set_animation(SP_CUR_MAIN_OBJ->ext.main_36.unk84, 3);
            self->unk6++;
        }
    }
}

void latcher_grab_clamp(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        if (SP_CUR_MAIN_OBJ->ext.main_36.unk8C != 0) {
            set_animation(self, 4);
            set_animation(SP_CUR_MAIN_OBJ->ext.main_36.unk84, 5);
        }
        self->unk6++;
    }
}

void latcher_grab_drain(struct MainObj* self)
{
    struct MainObj* current;
    u16 timer;

    current = SP_CUR_MAIN_OBJ;
    timer = current->ext.main_36.unk8A - 1;
    current->ext.main_36.unk8A = timer;
    if (timer == 0) {
        self->unk62 = 0;
        self->attack_box = NULL;
        self->hurt_box = NULL;
        g_Player.stun_timer = 0;
        self->unk6++;
        current = SP_CUR_MAIN_OBJ;
        if (current->ext.main_36.unk8C != 0) {
            current->ext.main_36.unk84->ext.misc_11.active = 1;
        }
        set_animation(self, 6);
        return;
    }
    if (current->ext.main_36.unk8C != 0 && timer == 0x40) {
        player_damage(4);
    }
    if ((SP_CUR_MAIN_OBJ->ext.main_36.unk8A & 7) == 0) {
        func_8001540C(2, 0xED, self);
    }
}

void latcher_grab_release(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->unk5 = 0;
        self->unk6 = 0;
        self->state++;
    }
}

void latcher_check_hit(struct MainObj* self)
{
    s32 result;

    result = func_8002DD04(self);
    if (result == 0) {
        return;
    }
    if (result < 0) {
        set_animation(self, 3);
        self->unk5 = 3;
        self->unk6 = 1;
        self->attack_box = NULL;
        self->hurt_box = NULL;
        SP_CUR_MAIN_OBJ->ext.main_36.unk8A = 1;
        return;
    }

    self->hp = 0x10;
    if (self->unk5 == 3) {
        return;
    }

    if (g_Player.x_pos.i.hi <= self->x_pos.i.hi) {
        self->x_speed += FIXED(0.28125);
        if (self->x_speed == FIXED(0.28125)) {
            set_animation(self, 1);
        }
    } else {
        self->x_speed -= FIXED(0.28125);
        if (self->x_speed == FIXED(-0.28125)) {
            set_animation(self, 2);
        }
    }
}

struct Unk_unk68 latcher_hurt_box = { -14, -14, 28, 28 };

union AnimationStep latcher_anim_0[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07F90002 },
};

union AnimationStep latcher_anim_1[] = {
    { 0x00010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1AED0002 },
};

union AnimationStep latcher_anim_2[] = {
    { 0x00010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x15010002 },
    { 0x14010002 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x11010002 },
    { 0x10010002 },
    { 0x0F010002 },
    { 0x0E010002 },
    { 0x0D010002 },
    { 0x0C010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x08ED0002 },
};

union AnimationStep latcher_anim_3[] = {
    { 0x00010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F000102 },
};

union AnimationStep latcher_anim_4[] = {
    { 0x20010002 },
    { 0x24010002 },
    { 0x23010002 },
    { 0x25010002 },
    { 0x21010002 },
    { 0x26010002 },
    { 0x22010002 },
    { 0x27F90002 },
};

union AnimationStep latcher_anim_5[] = {
    { 0x28010002 },
    { 0x3D010002 },
    { 0x24010002 },
    { 0x3D010002 },
    { 0x28010002 },
    { 0x3D010002 },
    { 0x25010002 },
    { 0x3D010002 },
    { 0x38010002 },
    { 0x3D010002 },
    { 0x36010002 },
    { 0x3D010002 },
    { 0x38010002 },
    { 0x3D010002 },
    { 0x37010002 },
    { 0x3DF10002 },
};

union AnimationStep latcher_anim_6[] = {
    { 0x1F010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1C010002 },
    { 0x1B010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B010002 },
    { 0x2C010002 },
    { 0x2D010002 },
    { 0x2E010002 },
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3D000102 },
};

union AnimationStep* latcher_animations[7] = {
    latcher_anim_0,
    latcher_anim_1,
    latcher_anim_2,
    latcher_anim_3,
    latcher_anim_4,
    latcher_anim_5,
    latcher_anim_6,
};

void (*latcher_state_funcs[3])() = {
    func_8005F558,
    latcher_main,
    latcher_despawn,
};

void (*latcher_step_funcs[4])() = {
    enemy_hit_reaction,
    latcher_resume_step,
    latcher_drift,
    latcher_grab,
};

void (*latcher_grab_funcs[4])() = {
    latcher_grab_home,
    latcher_grab_clamp,
    latcher_grab_drain,
    latcher_grab_release,
};
