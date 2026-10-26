// MainObj, main_object_update_funcs[36]
// 8005F510..8005FDBC
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_36_latcher.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/player_common.h"

// latcher_state_funcs
extern void (*latcher_state_funcs[])(struct MainObj*);

void latcher_despawn(struct MainObj* arg0);

// latcher_step_funcs
void latcher_resume_step(struct MainObj* arg0);

void latcher_grab(struct MainObj* arg0);

// latcher_grab_funcs
extern void (*latcher_grab_funcs[])(struct MainObj*);

void latcher_grab_release(struct MainObj*);

struct Unk_unk68 D_800FE2E4 = { -20, -20, 38, 38 };

void latcher_update(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    latcher_state_funcs[self->state](self);
}

// latcher_init

extern struct Unk_unk68 latcher_hurt_box;
extern struct Unk_unk68 D_801073F4[];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005F558(struct MainObj* arg0);
extern ret_u8 func_8002938C(s32);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_36_latcher", func_8005F558);
#else
void func_8005F558(struct MainObj* arg0)
{
    struct MainObj* current;
    s32 resource;

    resource = func_8002938C(0x24);
    arg0->unk40 = OBJECT_STAGE_TEXTURE(resource);
    arg0->unk42 = OBJECT_STAGE_CLUT(0x24);
    resource = func_8002938C(0x24);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->bg_offset = g_Player.bg_offset;
    arg0->attack_box = &latcher_hurt_box;
    arg0->animation_table = (const u8* const*)latcher_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->unk62 = 3;
    arg0->collision_data = D_801073F4;
    arg0->hp = 0x10;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk15 = 0;
    arg0->contact_damage = 0;
    arg0->hurt_box = &latcher_hurt_box;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    switch (arg0->unk2) {
    case 0:
        set_animation(arg0, 0);
        *(u32*)SP_CUR_MAIN_OBJ->ext.main_36.unk80 = 0;
        break;
    case 1:
        set_animation(arg0, 1);
        arg0->x_speed = 0x18000;
        break;
    case 2:
        set_animation(arg0, 1);
        arg0->unk15 = PLAYER_FACING_RIGHT;
        arg0->x_speed = -0x18000;
        break;
    }
    current = SP_CUR_MAIN_OBJ;
    current->ext.main_36.unk8A = 0x80;
    current->ext.main_36.unk8C = 0;
    SP_CUR_MAIN_OBJ->ext.main_36.unk8D = 0;
    arg0->state = 1;
    arg0->unk5 = 2;
}
#endif

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
    SP_CUR_MAIN_OBJ->ext.main_36.unk89 = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    set_velocity_from_angle(MOVING_OBJECT(self), SP_CUR_MAIN_OBJ->ext.main_36.unk89);
    SP_CUR_MAIN_OBJ->ext.main_36.unk84->x_vel.val = self->x_speed;
    SP_CUR_MAIN_OBJ->ext.main_36.unk84->y_vel.val = self->y_speed;
    move_object(MOVING_OBJECT(self));
    move_object(MOVING_OBJECT(SP_CUR_MAIN_OBJ->ext.main_36.unk84));
    if (ABS(g_Player.x_pos.i.hi, self->x_pos.i.hi) < 2) {
        if (ABS(g_Player.y_pos.i.hi, self->y_pos.i.hi) < 2) {
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

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_36_latcher", latcher_grab_drain);
#else
void latcher_grab_drain(struct MainObj* self)
{
    struct MainObj* current;

    current = SP_CUR_MAIN_OBJ;
    current->ext.main_36.unk8A -= 1;
    if (current->ext.main_36.unk8A == 0) {
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
    if (current->ext.main_36.unk8C != 0) {
        if (current->ext.main_36.unk8A == 0x40) {
            player_damage(4);
        }
    }
    if ((SP_CUR_MAIN_OBJ->ext.main_36.unk8A & 7) == 0) {
        func_8001540C(2, SATURN_SOUND(0xED, 0xAE), self);
    }
}
#endif

void latcher_grab_release(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->unk5 = 0;
        self->state++;
        self->unk6 = 0;
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
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, -7, 0x07 },
};

union AnimationStep latcher_anim_1[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x19 },
    { 2, 0, -19, 0x1A },
};

union AnimationStep latcher_anim_2[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x09 },
    { 2, 0, -19, 0x08 },
};

union AnimationStep latcher_anim_3[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 2, 1, 0, 0x1F },
};

union AnimationStep latcher_anim_4[] = {
    { 2, 0, 1, 0x20 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x22 },
    { 2, 0, -7, 0x27 },
};

union AnimationStep latcher_anim_5[] = {
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x36 },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x37 },
    { 2, 0, -15, 0x3D },
};

union AnimationStep latcher_anim_6[] = {
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x2B },
    { 2, 0, 1, 0x2C },
    { 2, 0, 1, 0x2D },
    { 2, 0, 1, 0x2E },
    { 2, 0, 1, 0x2F },
    { 2, 0, 1, 0x30 },
    { 2, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 2, 0, 1, 0x34 },
    { 2, 0, 1, 0x35 },
    { 2, 0, 1, 0x36 },
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x3B },
    { 2, 0, 1, 0x3C },
    { 2, 1, 0, 0x3D },
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
