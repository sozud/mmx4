// MainObj, main_object_update_funcs[18]
// 80050708..8005284C
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_18_ice_core.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/stage_objects.h"
#include "main/visuals/visual_03_small_effect.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#endif

extern u8 D_800FC340[4];

extern struct Unk_unk68 D_800FBF00;
extern struct Unk_unk68 D_800FBF04;

extern struct Unk_unk68 D_800FBF10;

void ice_core_death_sink(struct MainObj*);
void ice_core_death_release_camera(struct MainObj*);
void ice_core_death_wait_player(struct MainObj*);

// ice_core_step_funcs
void ice_core_resume_step(struct MainObj* arg0);
void ice_core_drift(struct MainObj* arg0);
void ice_core_bob(struct MainObj* arg0);
void ice_core_charge(struct MainObj* arg0);
void ice_core_stomp(struct MainObj* arg0);
void ice_core_fall(struct MainObj* arg0);

void ice_core_build(struct MainObj* arg0);
void ice_core_bounce(struct MainObj* arg0);
void ice_core_spray(struct MainObj* arg0);
void ice_core_intro(struct MainObj* arg0);

// ice_core_drift_funcs
void ice_core_drift_start(struct MainObj*);

// ice_core_bob_funcs
void ice_core_bob_start(struct MainObj*);

void ice_core_bob_recover(struct MainObj*);

// ice_core_charge_funcs
void ice_core_charge_face(struct MainObj*);
void ice_core_charge_back_off(struct MainObj*);

void ice_core_charge_start(struct MainObj*);

void ice_core_charge_recover(struct MainObj*);

// ice_core_stomp_funcs
void ice_core_stomp_start(struct MainObj*);
void ice_core_stomp_land(struct MainObj*);

void ice_core_stomp_impact(struct MainObj*);

// ice_core_build_funcs
void ice_core_build_open(struct MainObj*);

void ice_core_build_wait(struct MainObj*);

// ice_core_bounce_funcs
void ice_core_bounce_start(struct MainObj*);
void ice_core_bounce_move(struct MainObj*);
void ice_core_bounce_wait(struct MainObj*);
void ice_core_bounce_reform(struct MainObj*);

void ice_core_spray_wait_event(struct MainObj*);
void ice_core_spray_wait(struct MainObj*);

void ice_core_intro_wait_player(struct MainObj*);
void ice_core_intro_descend(struct MainObj*);
void ice_core_intro_slow(struct MainObj*);
void ice_core_intro_start_fight(struct MainObj*);

extern void (*ice_core_state_funcs[])(struct MainObj*);
extern void (*ice_core_drift_funcs[])(struct MainObj*);
extern void (*ice_core_bob_funcs[])(struct MainObj*);
extern void (*ice_core_charge_funcs[])(struct MainObj*);
extern void (*ice_core_stomp_funcs[])(struct MainObj*);
extern void (*ice_core_build_funcs[])(struct MainObj*);
extern void (*ice_core_bounce_funcs[])(struct MainObj*);
extern void (*ice_core_spray_funcs[])(struct MainObj*);
extern void (*ice_core_intro_funcs[])(struct MainObj*);

void ice_core_update(struct MainObj* self)
{
    ice_core_state_funcs[self->state](self);
    if (self->ext.main_18.state.runtime.unk82 == 0 && self->state < 2) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// ice_core_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

extern struct Unk_unk68 D_800FBF08;
extern void (*ice_core_step_funcs[])(struct MainObj*);
extern u8 D_800FC33C[];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005077C(struct MainObj* arg0);
void func_80050874(struct MainObj* arg0);
void func_80050D14(struct MainObj* arg0);
void func_800527F0(struct MainObj* arg0);
void func_800517D0(struct MainObj* arg0);
extern union AnimationStep* D_800FC2B4[34];
extern struct Unk_unk68 D_800FBF0C;
void ice_core_face_player(struct AnimatedObj* arg0);
void func_800527F0(struct MainObj* arg0);
void ice_core_pick_attack(struct MainObj* arg0);
void ice_core_check_rebuild(struct MainObj* arg0);
void ice_core_shed_ice(struct MainObj* arg0);
extern u16 D_800FBEDC[12];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005077C(struct MainObj* arg0)
{
    struct Main18Ext* ext = &arg0->ext.main_18;

    arg0->contact_damage = 4;
    arg0->invincibility_timer = -0x80;
    arg0->hp = 0;
    arg0->collision_data = (const u16*)D_80106B74;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FC2B4;
    arg0->unk16 = 0x22;
    arg0->air_state = 0;
    arg0->terrain_box = &D_800FBF0C;
    arg0->hurt_box = NULL;
    arg0->attack_box = NULL;
    ice_core_face_player(ANIMATED_OBJECT(arg0));
    set_animation(arg0, 0x21);
    ext->ice_pieces = 0x8000;
    *(u8*)&arg0->unk7E = 0xFF;
    ext->state.runtime.unk80 = 0;
    ext->state.runtime.unk81 = 0;
    ext->state.runtime.unk82 = 0;
    ext->state.runtime.unk83 = 0;
    ext->state.runtime.unk84 = 0;
    ext->state.runtime.unk85 = 0;
    ext->state.runtime.unk86 = 0;
    ext->state.runtime.unk87 = 0;
    ext->unk88 = 1;
    ext->shed_timer = 0;
    ext->state.runtime.unk82 = 1;
    ext->ice_pieces = 0;
    ext->unk8C = 0;
    ext->unk90 = 0;
    arg0->state = 1;
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_18_ice_core", func_8005077C);
#endif

// ice_core_run
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_18_ice_core", func_80050874);
#else
void func_80050874(struct MainObj* arg0)
{
    s32 hit;

    ice_core_pick_attack(arg0);
    ice_core_check_rebuild(arg0);
    ice_core_shed_ice(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    ice_core_step_funcs[arg0->unk5](arg0);
    if (arg0->state >= 2) {
        update_on_screen(BASE_OBJECT(arg0), 0x80, 0x80);
        return;
    }
    if (!(arg0->invincibility_timer & 0x7F)) {
        arg0->ext.main_18.saved_unk5 = arg0->unk5;
        hit = func_8002DD04(arg0);
        if (hit < 0) {
            g_Player.invincibility_timer = 0x7F;
            func_8001540C(5, SATURN_SOUND(2, 0x24), NULL);
            spawn_explosion(BASE_OBJECT(arg0));
            g_Player.spike_immune = 1;
            spawn_debris(4, D_800FC33C, arg0);
            arg0->unk7C = 4;
            arg0->unk7E = 8;
            arg0->ext.main_18.ice_pieces = 0;
            arg0->ext.main_18.shed_timer = 0;
            arg0->terrain_box = NULL;
            arg0->state = 2;
            arg0->unk42 &= 0x7FFF;
            return;
        }
        if (hit != 0 && hit != 0x7F) {
            if (engine_obj.cur_character == 0)
                arg0->invincibility_timer = 6;
            else
                arg0->invincibility_timer = 1;
            arg0->ext.main_18.state.runtime.unk87 = 1;
            arg0->unk42 |= 0x8000;
            if (!(arg0->ext.main_18.state.runtime.unk80 & 0xC0))
                arg0->ext.main_18.state.runtime.unk80 = (arg0->ext.main_18.state.runtime.unk80 | 0x40) + 1;
            if (arg0->ext.main_18.state.runtime.unk81 != 0) {
                switch (hit - 1) {
                case 0:
                    arg0->ext.main_18.state.runtime.unk83 += 2;
                    break;
                case 9:
                case 23:
                case 24:
                case 25:
                case 26:
                    arg0->ext.main_18.state.runtime.unk83 += 5;
                    break;
                case 18:
                    arg0->ext.main_18.state.runtime.unk83 += 10;
                    break;
                }
            }
        } else {
            arg0->ext.main_18.state.runtime.unk87 = 0;
        }
    } else {
        if (--arg0->invincibility_timer == 0)
            arg0->unk42 &= 0x7FFF;
    }
    func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x80, 0x80);
}
#endif

void ice_core_death_sink(struct MainObj* self)
{
    s16 value;

    value = ++self->y_pos.i.hi;
    if (value > 0x930) {
        apply_tile_effect(0x17, 0, 0);
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        self->state = 3;
    } else {
        value = --self->unk7C;
        if (value == 0) {
            self->unk7C = 4;
            func_800AF95C(OBJECT_HEADER(self), 1, 0x20, 0x30, 2);
        }

        value = --self->unk7E;
        if (value == 0) {
            self->unk7E = 8;
            self->ext.main_18.state.saved_position.x = self->x_pos.val;
            self->ext.main_18.state.saved_position.y = self->y_pos.val;
            self->x_pos.i.hi = 0x18E2;
            self->y_pos.i.hi = 0x89E;
            func_800AF95C(OBJECT_HEADER(self), 1, 0x18, 0x30, 2);
            self->x_pos.val = self->ext.main_18.state.saved_position.x;
            self->y_pos.val = self->ext.main_18.state.saved_position.y;
        }
    }

    update_on_screen(BASE_OBJECT(self), 0x80, 0x80);
}

void ice_core_death_release_camera(struct MainObj* self)
{
    player_start_script_action(0x15, PLAYER_FACING_RIGHT);
    self->state = 4;
}

void ice_core_death_wait_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi > 0x18F0) {
        player_end_script_action();
        self->ext.raw[0] = 0;
        self->ext.raw[1] = 0;
        self->ext.raw[2] = 0;
        self->ext.raw[3] = 0;
        self->ext.raw[4] = 0;
        self->ext.raw[5] = 0;
        engine_obj.unkF = 0x40;
        despawn_object(OBJECT_HEADER(self));
    }
}

void ice_core_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_18.saved_unk5;
}

void ice_core_drift(struct MainObj* self)
{
    ice_core_drift_funcs[self->unk6](self);
}

void ice_core_drift_start(struct MainObj* self)
{
    if (self->unk15 == 0) {
        self->x_speed = FIXED(-1.375);
    } else {
        self->x_speed = FIXED(1.375);
    }
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = FIXED(-0.125);
    animate_object(ANIMATED_OBJECT(self));
    self->unk6 = 1;
}

// ice_core_drift_move
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_18_ice_core", func_80050D14);
#else
void func_80050D14(struct MainObj* arg0)
{
    if (arg0->unk15 == 0) {
        if (arg0->collision_flags & 2) {
            if (arg0->ext.main_18.state.runtime.unk84 != 0) {
                ice_core_face_player(ANIMATED_OBJECT(arg0));
                set_animation(arg0, 6);
                arg0->unk5 = 3;
                arg0->unk6 = 2;
            } else {
                arg0->unk15 = PLAYER_FACING_RIGHT;
                func_800527F0(arg0);
            }
        }
    } else if (arg0->collision_flags & 1) {
        if (arg0->ext.main_18.state.runtime.unk84 != 0) {
            ice_core_face_player(ANIMATED_OBJECT(arg0));
            set_animation(arg0, 6);
            arg0->unk5 = 3;
            arg0->unk6 = 2;
        } else {
            arg0->unk15 = 0;
            func_800527F0(arg0);
        }
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->y_speed == 0x30000)
        arg0->gravity = 0x2000;
    if (arg0->y_speed == -0x30000)
        arg0->gravity = -0x2000;
    animate_object(ANIMATED_OBJECT(arg0));
}
#endif

void ice_core_bob(struct MainObj* self)
{
    ice_core_bob_funcs[self->unk6](self);
}

void ice_core_bob_start(struct MainObj* self)
{
    self->ext.main_18.state.runtime.unk84 = 1;
    set_animation(self, 1);
    self->unk7C = 1;
    self->unk6 = 1;
    self->gravity = FIXED(0.0625);
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->hurt_box = (const u8*)&D_800FBF00;
    self->attack_box = (const u8*)&D_800FBF00;
}

void ice_core_bob_move(struct MainObj* self)
{
    s16 temp_v0;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->collision_data = (const u16*)D_801060F0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed == FIXED(1.5)) {
        self->gravity = FIXED(0.0625);
    }
    if (self->y_speed == FIXED(-1.5)) {
        temp_v0 = --self->unk7C;
        if (temp_v0 == 0) {
            self->y_speed = 0;
            self->gravity = 0;
            func_800527F0(self);
            return;
        }
        self->gravity = FIXED(-0.0625);
    }
}

void ice_core_bob_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->collision_data = (const u16*)D_80106B74;
        self->hurt_box = (const u8*)&D_800FBEF4;
        self->attack_box = (const u8*)&D_800FBEF4;
    }
    if (self->animation_step.fields.event == 1) {
        self->ext.main_18.state.runtime.unk84 = 0;
        self->ext.main_18.state.runtime.unk80 &= 0x3F;
        set_animation(self, 2);
        func_800527F0(self);
    }
}

void ice_core_charge(struct MainObj* self)
{
    ice_core_charge_funcs[self->unk6](self);
}

void ice_core_charge_face(struct MainObj* self)
{
    ice_core_face_player(ANIMATED_OBJECT(self));
    self->x_speed = 0;
    self->y_speed = 0;
    self->unk7C = 0x1C;
    self->unk6 = 1;
}

void ice_core_charge_back_off(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        if (self->unk15 == 0) {
            self->x_speed = FIXED(3);
        } else {
            self->x_speed = FIXED(-3);
        }
        self->x_accel = FIXED(0.09375);
        self->unk7C = 0x14;
        self->y_speed = 0;
        self->gravity = 0;
        self->unk6 = 2;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void ice_core_charge_slide(struct MainObj* self)
{
    if (!(self->collision_flags & 3)) {
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->x_speed == 0) {
            self->x_speed = 0;
            self->x_accel = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk7C = 0x1C;
        self->unk6 = 3;
    }
}

void ice_core_charge_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_8001540C(2, SATURN_SOUND(0x35, 0x37), self);
        self->contact_damage = 6;
        self->ext.main_18.state.runtime.unk81 = 1;
        set_animation(self, 3);
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-4);
        } else {
            self->x_speed = FIXED(4);
        }
        self->unk6 = 4;
    }
}

void ice_core_charge_run(struct MainObj* self)
{
    s32 blocked;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->hurt_box = &D_800FBEFC;
        self->attack_box = &D_800FBEFC;
    }
    if (self->ext.main_18.state.runtime.unk83 >= 0xA) {
        set_animation(self, 0xC);
        self->unk6 = 5;
    }
    if (self->unk15 == 0) {
        blocked = self->collision_flags & 2;
    } else {
        blocked = self->collision_flags & 1;
    }
    if (blocked != 0) {
        func_8001540C(2, SATURN_SOUND(0x37, 0x39), self);
        start_screen_shake_x(0x10, 8, 2);
        set_animation(self, 0xC);
        self->unk6 = 5;
    }
    move_object(MOVING_OBJECT(self));
}

void ice_core_charge_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 2) {
        self->contact_damage = 4;
        self->attack_box = (const u8*)&D_800FBEF4;
        self->hurt_box = (const u8*)&D_800FBEF4;
    }

    if (self->animation_step.fields.event == 1) {
        set_animation(self, 2);
        func_800527F0(self);
        self->ext.main_18.state.runtime.unk83 = 0;
        self->ext.main_18.state.runtime.unk81 = 0;
        self->ext.main_18.state.runtime.unk80 = 0;
    }
}

void ice_core_stomp(struct MainObj* self)
{
    ice_core_stomp_funcs[self->unk6](self);
}

void ice_core_stomp_start(struct MainObj* self)
{
    self->ext.main_18.state.runtime.unk82 = 1;
    self->attack_box = (const u8*)&D_800FBF00;
    self->hurt_box = (const u8*)&D_800FBF00;
    ice_core_face_player(ANIMATED_OBJECT(self));
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = FIXED(0.2578125);
    self->unk7C = 0x5A;
    self->unk6 = 1;
}

void ice_core_stomp_land(struct MainObj* self)
{
    s16 temp_v0;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->collision_data = D_801060F0;
    }
    temp_v0 = --self->unk7C;
    if (temp_v0 == 0) {
        self->collision_flags = 0;
        self->y_speed = FIXED(6);
        self->gravity = 0;
        self->unk7C = 0x50;
        self->unk6 = 2;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    if ((self->y_pos.i.hi >= 0x8BA) && (self->gravity != 0)) {
        self->y_pos.i.hi = 0x8BA;
        self->y_speed = 0;
        self->gravity = 0;
        func_8001540C(2, SATURN_SOUND(0x38, 0x3A), self);
    }
}

void ice_core_stomp_rise(struct MainObj* self)
{
    s16 timer;

    if (self->unk7C > 0x28) {
        move_object(MOVING_OBJECT(self));
    }

    animate_object(ANIMATED_OBJECT(self));
    timer = --self->unk7C;

    if (timer == 0) {
        self->x_pos.val = g_Player.x_pos.val;
        if (self->x_pos.i.hi < 0x17CD) {
            self->x_pos.i.hi = 0x17CD;
        }
        if (self->x_pos.i.hi > 0x18B5) {
            self->x_pos.i.hi = 0x18B5;
        }
        self->y_speed = FIXED(-8);
        self->unk7C = 0xA;
        self->unk6 = 3;
    }
}

void ice_core_stomp_drop(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->ext.main_18.state.runtime.unk82 = 0;
        self->terrain_box = &D_800FBF0C;
    }
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->attack_box = &D_800FBEF4;
        self->hurt_box = &D_800FBEF4;
    }
    if (self->collision_flags & 8) {
        func_8001540C(2, SATURN_SOUND(0x37, 0x39), self);
        start_screen_shake_y(0x10, 8, 2);
        self->ext.main_18.shed_timer = 0xA6;
        set_animation(self, 5);
        self->unk6 = 4;
    }
}

void ice_core_stomp_impact(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation((struct Unk19*)self, 6);
        self->unk6 = 5;
    }
}

void ice_core_stomp_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        if (self->ext.main_18.ice_pieces == 0x8000) {
            self->ext.main_18.state.runtime.unk85 = self->hp;
        }
        self->collision_data = (const u16*)D_80106B74;
        self->attack_box = (const u8*)&D_800FBEF4;
        self->hurt_box = (const u8*)&D_800FBEF4;
    }
    if (self->animation_step.fields.event == 1) {
        ice_core_face_player(ANIMATED_OBJECT(self));
        set_animation(self, 2);
        self->y_speed = FIXED(2);
        self->gravity = FIXED(0.0625);
        self->unk5 = 6;
        self->unk6 = 0;
        self->ext.main_18.state.runtime.unk80 = 0;
    }
}

void ice_core_build(struct MainObj* self)
{
    ice_core_build_funcs[self->unk6](self);
}

void ice_core_build_open(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->attack_box = (const u8*)&D_800FBF04;
        self->hurt_box = (const u8*)&D_800FBF04;
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 8);
        self->unk6 = 1;
    }
}

// ice_core_build_gather
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_18_ice_core", func_800517D0);
#else
void func_800517D0(struct MainObj* arg0)
{
    struct ShotObj* shot;
    struct MiscObj* misc;
    s16 i;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        for (i = 0; i < 10; i++) {
            if (arg0->ext.main_18.ice_pieces & D_800FBEDC[i])
                continue;
            shot = find_free_shot_obj();
            if (shot == NULL)
                continue;
            shot->active = 0x41;
            shot->id = 0xC;
            shot->unk2 = i;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->bg_offset = arg0->bg_offset;
            shot->x_pos.val = (i << 21) + 0x17B10000;
            shot->y_pos.val = 0x8200000;
            shot->state = 3;
            shot->unk15 = 0;
            shot->unk7C = (struct WeaponObj*)&arg0->ext.main_18.ice_pieces;
        }
        arg0->ext.main_18.ice_pieces = 0x83FF;
    }
    if (arg0->animation_step.fields.event == 4) {
        arg0->attack_box = (const u8*)&D_800FBF08;
        arg0->hurt_box = (const u8*)&D_800FBF08;
    }
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, SATURN_SOUND(0x34, 0x36), arg0);
        for (i = 0; i < 8; i++) {
            misc = find_free_misc_obj();
            if (misc == NULL)
                continue;
            misc->active = 0x41;
            misc->id = 6;
            misc->unk2 = i;
            misc->unk40 = arg0->unk40;
            misc->unk42 = arg0->unk42 & 0x7FFF;
            misc->animation_table = (u32**)arg0->animation_table;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->bg_offset = arg0->bg_offset;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->unk15 = 0;
            misc->state = 0;
        }
        arg0->invincibility_timer = -0x80;
    }
    if (arg0->animation_step.fields.event != 1)
        return;
    if (arg0->ext.main_18.unk88 == 0) {
        arg0->attack_box = (const u8*)&D_800FBEF8;
        arg0->hurt_box = (const u8*)&D_800FBEF8;
        set_animation(arg0, 0xA);
    } else {
        ice_core_face_player(ANIMATED_OBJECT(arg0));
        arg0->attack_box = (const u8*)&D_800FBEF4;
        arg0->hurt_box = (const u8*)&D_800FBEF4;
        set_animation(arg0, 9);
    }
    arg0->ext.main_18.state.runtime.unk85 = 3;
    arg0->unk6 = 2;
}
#endif

void ice_core_build_grow(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (*(u8*)&self->unk7E == 0xFF && self->hp < 0x30) {
        if (--self->ext.main_18.state.runtime.unk85 == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), NULL);
            self->ext.main_18.state.runtime.unk85 = 3;
        }
        self->hp++;
    }
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, SATURN_SOUND(0x39, 0x3B), self);
    }
    if (self->animation_step.fields.event != 1) {
        return;
    }
    self->invincibility_timer = 0;
    if (self->ext.main_18.unk88 == 0) {
        self->ext.main_18.unk88 = 1;
        set_animation(self, 0xB);
        self->attack_box = &D_800FBEF8;
        ice_core_face_player(ANIMATED_OBJECT(self));
    } else {
        self->ext.main_18.unk88 = 0;
        set_animation(self, 0);
        self->attack_box = &D_800FBEF4;
    }
    self->unk6 = 3;
    self->unk7C = 0x1E;
}

void ice_core_build_wait(struct MainObj* self)
{

    if (*(u8*)&self->unk7E == 0xFF && self->hp < 0x30) {
        if (--self->ext.main_18.state.runtime.unk85 == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), NULL);
            self->ext.main_18.state.runtime.unk85 = 3;
        }
        self->hp++;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        if (self->animation_step.fields.event != 0) {
            if (self->ext.main_18.unk88 == 0) {
                self->ext.main_18.state.runtime.unk85 = 0;
                self->ext.main_18.state.runtime.unk80 = 0;
                func_800527F0(self);
                if (*(u8*)&self->unk7E == 0xFF) {
                    *(u8*)&self->unk7E = get_random() & 1;
                    player_end_script_action();
                }
            } else {
                set_animation(self, 0x10);
                self->unk5 = 9;
                self->unk6 = 0;
            }
        } else {
            self->unk7C = 1;
        }
    }
}

void ice_core_bounce(struct MainObj* self)
{
    ice_core_bounce_funcs[self->unk6](self);
}

void ice_core_bounce_start(struct MainObj* self)
{
    self->ext.main_18.state.runtime.unk80 = 0x80;
    ice_core_face_player(ANIMATED_OBJECT(self));
    self->terrain_box = &D_800FBF10;

    if (self->unk15 == 0) {
        self->x_speed = FIXED(-3.53554);
    } else {
        self->x_speed = FIXED(3.53554);
    }

    if (!(get_random() & 1)) {
        self->y_speed = FIXED(-3.53554);
    } else {
        self->y_speed = FIXED(3.53554);
    }

    self->unk7C = 0xF0;
    self->unk6 = 1;
}

void ice_core_bounce_move(struct MainObj* self)
{
    s32 hit;

    if (0 > self->x_speed) {
        if (self->collision_flags & 2) {
            spawn_debris(2, D_800FC340, self);
            func_8001540C(2, SATURN_SOUND(0x37, 0x39), self);
            start_screen_shake_x(8, 4, 2);
            self->unk15 = PLAYER_FACING_RIGHT;
            self->x_speed = -self->x_speed;
        }
    } else if (self->collision_flags & 1) {
        spawn_debris(2, D_800FC340, self);
        func_8001540C(2, SATURN_SOUND(0x37, 0x39), self);
        start_screen_shake_x(8, 4, 2);
        self->unk15 = 0;
        self->x_speed = -self->x_speed;
    }

    if (self->y_speed < 0) {
        hit = self->collision_flags & 8;
    } else {
        hit = self->collision_flags & 4;
    }
    if (hit != 0) {
        func_8001540C(5, SATURN_SOUND(2, 0x24), NULL);
        spawn_debris(2, D_800FC340, self);
        func_8001540C(2, SATURN_SOUND(0x37, 0x39), self);
        start_screen_shake_y(8, 4, 2);
        self->y_speed = -self->y_speed;
    }

    move_object(MOVING_OBJECT(self));
    if (self->ext.main_18.state.runtime.unk86 != 2) {
        if (--self->unk7C == 0) {
            if (self->y_pos.i.hi > 0x848 && self->y_pos.i.hi < 0x890 && self->x_pos.i.hi > 0x17D0 && self->x_pos.i.hi < 0x18C0) {
                self->unk7C = 0x30;
                self->unk6 = 2;
                ice_core_face_player(ANIMATED_OBJECT(self));
                return;
            }
            self->unk7C = 1;
        }
    } else if (self->ext.main_18.state.runtime.unk87 != 0) {
        set_animation(self, 0xF);
        self->unk6 = 3;
    }
}

void ice_core_bounce_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 10;
        self->unk6 = 0;
    }
}

void ice_core_bounce_reform(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->attack_box = (const u8*)&D_800FBF04;
        self->hurt_box = (const u8*)&D_800FBF04;
    }
    if (self->animation_step.fields.event == 1) {
        self->terrain_box = &D_800FBF0C;
        self->ext.main_18.state.runtime.unk86 = 0;
        self->unk5 = 8;
        self->unk6 = 0;
    }
}

void ice_core_spray(struct MainObj* self)
{
    ice_core_spray_funcs[self->unk6](self);
}

void ice_core_spray_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    s16 i;

    for (i = (self->ext.main_18.state.runtime.unk86 ^ 1) & 0xFF; i < 8; i += 2) {
        shot = find_free_shot_obj();
        if (shot == NULL) {
            continue;
        }
        shot->active = 0x41;
        shot->id = 0xC;
        shot->unk2 = i;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk15 = self->unk15;
        shot->unk7C = (struct WeaponObj*)&self->state;
        shot->state = 0;
    }
    set_animation(self, self->ext.main_18.state.runtime.unk86 + 0xD);
    self->ext.main_18.state.runtime.unk86++;
    func_8001540C(2, SATURN_SOUND(0x36, 0x38), self);
    self->unk6 = 1;
}

void ice_core_spray_wait_event(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 0x30;
        self->unk6 = 2;
    }
}

void ice_core_spray_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 9;
        self->unk6 = 0;
    }
}

void ice_core_intro(struct MainObj* self)
{
    ice_core_intro_funcs[self->unk6](self);
}

// ice_core_intro_appear
void func_80052218(struct MainObj* self)
{
    struct ItemObj* item;

    for (item = item_objects; item < &item_objects[COUNT(item_objects)]; item++) {
        if (item->id != 8) {
            item->active = 0;
        }
    }
    self->y_speed = FIXED(1);
    self->x_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk7C = 0x74;
    player_start_script_action(0x15, 0);
    self->unk6 = 1;
}

void ice_core_intro_wait_player(struct MainObj* self)
{
    if (g_Player.script_state == -1) {
        self->unk6 = 2;
    }
}

void ice_core_intro_descend(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->y_speed = 0;
        self->gravity = FIXED(0.0078125);
        self->unk16 = VISUAL_SATURN_LAYER(5);
        self->unk6 = 3;
    }
}

void ice_core_intro_slow(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed == FIXED(-0.75)) {
        self->gravity = FIXED(-0.015625);
        self->unk7C = 0x64;
        self->unk6 = 4;
    }
}

void ice_core_intro_start_fight(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 2;
        engine_obj.boss_ptr = self;
        self->ext.main_18.state.runtime.unk82 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->unk5 = 8;
        self->unk6 = 0;
    }
}

void ice_core_fall(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_speed == 0) {
        self->terrain_box = &D_800FBF0C;
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void ice_core_float(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    if (self->gravity == FIXED(0.0625)) {
        if (self->ext.main_18.state.runtime.unk84 == 0) {
            if (self->y_pos.i.hi > 0x890) {
                goto landed;
            }
            return;
        }
        if (self->y_pos.i.hi <= 0x8B0) {
            return;
        }
    } else {
        if (self->ext.main_18.state.runtime.unk84 == 0) {
            if (self->y_pos.i.hi < 0x890) {
                goto landed;
            }
            return;
        }
        if (self->y_pos.i.hi >= 0x8B0) {
            return;
        }
    }

landed:
    self->terrain_box = &D_800FBF0C;
    self->unk5 = 2;
    self->unk6 = 0;
}

void ice_core_pick_attack(struct MainObj* self)
{
    u8 flags, next_flags, phase_value;

    flags = self->ext.main_18.state.runtime.unk80;
    if ((flags & 0xC0) == 0x40) {
        next_flags = flags | 0x80;
        self->ext.main_18.state.runtime.unk80 = next_flags;
        if ((next_flags & 0x3F) < 3 && (get_random() & 3) > 1) {
            ice_core_face_player(ANIMATED_OBJECT(self));
            self->terrain_box = &D_800FBF0C;
            self->unk5 = 3;
            self->unk6 = 0;
            return;
        }
        phase_value = *(u8*)&self->unk7E;
        switch (phase_value) {
        case 0:
            self->terrain_box = &D_800FBF0C;
            self->unk5 = 4;
            self->unk6 = 0;
            *(u8*)&self->unk7E = 1;
            break;
        case 1:
            self->terrain_box = &D_800FBF0C;
            set_animation(self, 4);
            self->unk5 = 5;
            self->unk6 = 0;
            *(u8*)&self->unk7E = 0;
            break;
        }
    }
}

void ice_core_check_rebuild(struct MainObj* self)
{
    if (self->ext.main_18.state.runtime.unk81 == 0 && self->hp < self->ext.main_18.state.runtime.unk85 && self->ext.main_18.state.runtime.unk87 != 0 && self->ext.main_18.unk88 == 0) {
        self->ext.main_18.state.runtime.unk82 = 0;
        self->ext.main_18.state.runtime.unk85 = 0;
        self->ext.main_18.state.runtime.unk84 = 0;
        set_animation(self, 7);
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->unk5 = 8;
        self->unk6 = 0;
    }
}

void ice_core_shed_ice(struct MainObj* self)
{
    u8 timer;
    u8 random;

    timer = self->ext.main_18.shed_timer;
    if (timer & 0xE0) {
        if ((self->ext.main_18.ice_pieces & 0x3FF) == 0) {
            self->ext.main_18.shed_timer = 0;
            return;
        }

        timer--;
        self->ext.main_18.shed_timer = timer;
        if ((timer & 0x1F) == 0) {
            do {
                random = get_random();
                if (random) {
                    random %= 10;
                }
            } while ((self->ext.main_18.ice_pieces & D_800FBEDC[random]) == 0);

            self->ext.main_18.ice_pieces = self->ext.main_18.ice_pieces ^ D_800FBEDC[random];
            if (self->ext.main_18.ice_pieces == 0x8000) {
                self->ext.main_18.state.runtime.unk85 = self->hp;
            }
            self->ext.main_18.shed_timer = (self->ext.main_18.shed_timer - 0x20) | 0xC;
        }
    }
}

void ice_core_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

// ice_core_end_attack
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_18_ice_core", func_800527F0);
#else
void func_800527F0(struct MainObj* arg0)
{
    arg0->unk5 = 7;
    arg0->unk6 = 0;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    if ((arg0->ext.main_18.state.runtime.unk84 == 0 && arg0->y_pos.i.hi > 0x890) || (arg0->ext.main_18.state.runtime.unk84 != 0 && arg0->y_pos.i.hi > 0x8B0))
        arg0->gravity = -0x1000;
    else
        arg0->gravity = 0x1000;
}
#endif

u16 D_800FBEDC[12] = {
    0x0001,
    0x0002,
    0x0004,
    0x0008,
    0x0010,
    0x0020,
    0x0040,
    0x0080,
    0x0100,
    0x0200,
    0xF3F8,
    0x1A0F,
};

struct Unk_unk68 D_800FBEF4 = { -18, -33, 38, 70 };

struct Unk_unk68 D_800FBEF8 = { -16, -19, 34, 34 };

struct Unk_unk68 D_800FBEFC = { -24, -66, 29, 111 };

struct Unk_unk68 D_800FBF00 = { -26, -15, 33, 30 };

struct Unk_unk68 D_800FBF04 = { -14, -9, 24, 19 };

struct Unk_unk68 D_800FBF08 = { -16, -22, 27, 51 };

struct Unk_unk68 D_800FBF0C = { 0, -17, 24, 39 };

struct Unk_unk68 D_800FBF10 = { 0, -3, 24, 20 };

union AnimationStep D_800FBF14[] = {
    { 8, 0, 1, 0x00 },
    { 9, 0, 1, 0x01 },
    { 10, 0, 1, 0x02 },
    { 9, 1, -3, 0x03 },
};

union AnimationStep D_800FBF24[] = {
    { 2, 0, 1, 0x00 },
    { 4, 0, 1, 0x04 },
    { 1, 0, 1, 0x00 },
    { 2, 0, 1, 0x05 },
    { 29, 2, 1, 0x06 },
    { 1, 1, 0, 0x06 },
};

union AnimationStep D_800FBF3C[] = {
    { 18, 0, 1, 0x00 },
    { 14, 0, 1, 0x07 },
    { 16, 0, 1, 0x04 },
    { 14, 0, -3, 0x07 },
};

union AnimationStep D_800FBF4C[] = {
    { 2, 0, 1, 0x00 },
    { 6, 0, 1, 0x08 },
    { 4, 0, 1, 0x01 },
    { 3, 2, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 1, -1, 0x0B },
};

union AnimationStep D_800FBF64[] = {
    { 3, 0, 1, 0x06 },
    { 7, 0, 1, 0x0C },
    { 6, 2, 1, 0x0D },
    { 5, 0, 1, 0x0E },
    { 1, 1, 0, 0x0D },
};

union AnimationStep D_800FBF78[] = {
    { 1, 0, 1, 0x0D },
    { 7, 0, 1, 0x0E },
    { 29, 0, 1, 0x0D },
    { 1, 1, 0, 0x0D },
};

union AnimationStep D_800FBF88[] = {
    { 3, 0, 1, 0x0C },
    { 5, 0, 1, 0x06 },
    { 2, 0, 1, 0x05 },
    { 1, 2, 1, 0x40 },
    { 6, 0, 1, 0x04 },
    { 1, 1, 0, 0x40 },
};

union AnimationStep D_800FBFA0[] = {
    { 4, 0, 1, 0x00 },
    { 4, 2, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x12 },
    { 7, 0, 1, 0x13 },
    { 4, 0, 1, 0x14 },
    { 3, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x16 },
    { 1, 1, 0, 0x17 },
};

union AnimationStep D_800FBFF4[] = {
    { 3, 0, 1, 0x18 },
    { 5, 0, 1, 0x19 },
    { 3, 0, 1, 0x18 },
    { 20, 0, 1, 0x17 },
    { 5, 0, 1, 0x1A },
    { 5, 0, 1, 0x1B },
    { 5, 0, 1, 0x17 },
    { 4, 0, 1, 0x1A },
    { 4, 0, 1, 0x1B },
    { 4, 0, 1, 0x17 },
    { 3, 0, 1, 0x1A },
    { 3, 0, 1, 0x1B },
    { 3, 0, 1, 0x17 },
    { 1, 0, 1, 0x1A },
    { 1, 0, 1, 0x1B },
    { 1, 0, 1, 0x17 },
    { 1, 2, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 3, 1, 0x1F },
    { 1, 0, 1, 0x20 },
    { 1, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 1, 0, 1, 0x23 },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2A },
    { 1, 4, 1, 0x2B },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x2D },
    { 1, 0, 1, 0x55 },
    { 1, 0, 1, 0x56 },
    { 1, 0, 1, 0x57 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x2D },
    { 1, 0, 1, 0x55 },
    { 1, 0, 1, 0x56 },
    { 1, 0, 1, 0x57 },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5D },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5D },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5D },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 0, 1, 0x5C },
    { 1, 1, 0, 0x5D },
};

union AnimationStep D_800FC130[] = {
    { 10, 0, 1, 0x06 },
    { 1, 0, 1, 0x05 },
    { 1, 0, 1, 0x40 },
    { 6, 0, 1, 0x04 },
    { 1, 2, 1, 0x40 },
    { 2, 0, 1, 0x3E },
    { 4, 3, 1, 0x3F },
    { 1, 0, 1, 0x3E },
    { 1, 1, 0, 0x3E },
};

union AnimationStep D_800FC154[] = {
    { 8, 0, 1, 0x13 },
    { 1, 0, 1, 0x2E },
    { 2, 2, 1, 0x41 },
    { 5, 3, 1, 0x42 },
    { 2, 0, 1, 0x41 },
    { 1, 1, 0, 0x2E },
};

union AnimationStep D_800FC16C[] = {
    { 5, 0, 1, 0x2E },
    { 6, 0, 1, 0x3A },
    { 7, 2, 1, 0x3B },
    { 6, 0, 1, 0x3A },
    { 5, 0, 1, 0x2E },
    { 6, 0, 1, 0x3C },
    { 7, 0, 1, 0x3D },
    { 6, 0, -7, 0x3C },
};

union AnimationStep D_800FC18C[] = {
    { 4, 0, 1, 0x0B },
    { 5, 0, 1, 0x0A },
    { 7, 0, 1, 0x0F },
    { 5, 2, 1, 0x09 },
    { 4, 0, 1, 0x02 },
    { 3, 0, 1, 0x01 },
    { 14, 0, 1, 0x00 },
    { 1, 1, 0, 0x00 },
};

union AnimationStep D_800FC1AC[] = {
    { 4, 0, 1, 0x2F },
    { 5, 0, 1, 0x30 },
    { 6, 0, 1, 0x31 },
    { 1, 0, 1, 0x32 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x32 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x32 },
    { 1, 0, 1, 0x31 },
    { 1, 1, 0, 0x32 },
};

union AnimationStep D_800FC1D4[] = {
    { 4, 0, 1, 0x33 },
    { 5, 0, 1, 0x34 },
    { 6, 0, 1, 0x35 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x35 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x35 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x35 },
    { 1, 1, 0, 0x36 },
};

union AnimationStep D_800FC1FC[] = {
    { 4, 0, 1, 0x37 },
    { 5, 0, 1, 0x38 },
    { 6, 0, 1, 0x39 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x39 },
    { 7, 0, 1, 0x13 },
    { 4, 0, 1, 0x14 },
    { 3, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 1, 2, 1, 0x17 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x16 },
    { 1, 1, 0, 0x17 },
};

union AnimationStep D_800FC24C[] = {
    { 1, 1, 0, 0x3B },
};

union AnimationStep D_800FC250[] = {
    { 1, 1, 0, 0x45 },
};

union AnimationStep D_800FC254[] = {
    { 1, 1, 0, 0x44 },
};

union AnimationStep D_800FC258[] = {
    { 1, 1, 0, 0x43 },
};

union AnimationStep D_800FC25C[] = {
    { 1, 1, 0, 0x4A },
};

union AnimationStep D_800FC260[] = {
    { 1, 1, 0, 0x49 },
};

union AnimationStep D_800FC264[] = {
    { 1, 1, 0, 0x48 },
};

union AnimationStep D_800FC268[] = {
    { 1, 1, 0, 0x47 },
};

union AnimationStep D_800FC26C[] = {
    { 1, 1, 0, 0x46 },
};

union AnimationStep D_800FC270[] = {
    { 1, 1, 0, 0x4B },
};

union AnimationStep D_800FC274[] = {
    { 1, 1, 0, 0x4C },
};

union AnimationStep D_800FC278[] = {
    { 1, 1, 0, 0x4D },
};

union AnimationStep D_800FC27C[] = {
    { 1, 1, 0, 0x4E },
};

union AnimationStep D_800FC280[] = {
    { 1, 0, 1, 0x62 },
    { 9, 0, 1, 0x63 },
    { 9, 0, 1, 0x64 },
    { 9, 0, 1, 0x65 },
    { 9, 0, 1, 0x66 },
    { 9, 0, 1, 0x67 },
    { 9, 0, 1, 0x68 },
    { 9, 0, 1, 0x69 },
    { 1, 1, 0, 0x5E },
};

union AnimationStep D_800FC2A4[] = {
    { 1, 1, 0, 0x5F },
};

union AnimationStep D_800FC2A8[] = {
    { 1, 1, 0, 0x60 },
};

union AnimationStep D_800FC2AC[] = {
    { 1, 1, 0, 0x61 },
};

union AnimationStep D_800FC2B0[] = {
    { 1, 1, 0, 0x18 },
};

union AnimationStep* D_800FC2B4[34] = {
    D_800FBF14,
    D_800FBF24,
    D_800FBF3C,
    D_800FBF4C,
    D_800FBF64,
    D_800FBF78,
    D_800FBF88,
    D_800FBFA0,
    D_800FBFF4,
    D_800FC130,
    D_800FC154,
    D_800FC16C,
    D_800FC18C,
    D_800FC1AC,
    D_800FC1D4,
    D_800FC1FC,
    D_800FC24C,
    D_800FC250,
    D_800FC254,
    D_800FC258,
    D_800FC25C,
    D_800FC260,
    D_800FC264,
    D_800FC268,
    D_800FC26C,
    D_800FC270,
    D_800FC274,
    D_800FC278,
    D_800FC27C,
    D_800FC280,
    D_800FC2A4,
    D_800FC2A8,
    D_800FC2AC,
    D_800FC2B0,
};

u8 D_800FC33C[4] = { 25, 26, 27, 28 };

u8 D_800FC340[4] = { 31, 32, 0, 0 };

void (*ice_core_state_funcs[5])() = {
    func_8005077C,
    func_80050874,
    ice_core_death_sink,
    ice_core_death_release_camera,
    ice_core_death_wait_player,
};

void (*ice_core_step_funcs[12])() = {
    enemy_hit_reaction,
    ice_core_resume_step,
    ice_core_drift,
    ice_core_bob,
    ice_core_charge,
    ice_core_stomp,
    ice_core_fall,
    ice_core_float,
    ice_core_build,
    ice_core_bounce,
    ice_core_spray,
    ice_core_intro,
};

void (*ice_core_drift_funcs[2])(struct MainObj*) = {
    ice_core_drift_start,
    func_80050D14,
};

void (*ice_core_bob_funcs[3])(struct MainObj*) = {
    ice_core_bob_start,
    ice_core_bob_move,
    ice_core_bob_recover,
};

void (*ice_core_charge_funcs[6])(struct MainObj*) = {
    ice_core_charge_face,
    ice_core_charge_back_off,
    ice_core_charge_slide,
    ice_core_charge_start,
    ice_core_charge_run,
    ice_core_charge_recover,
};

void (*ice_core_stomp_funcs[6])(struct MainObj*) = {
    ice_core_stomp_start,
    ice_core_stomp_land,
    ice_core_stomp_rise,
    ice_core_stomp_drop,
    ice_core_stomp_impact,
    ice_core_stomp_recover,
};

void (*ice_core_build_funcs[4])(struct MainObj*) = {
    ice_core_build_open,
    func_800517D0,
    ice_core_build_grow,
    ice_core_build_wait,
};

void (*ice_core_bounce_funcs[4])(struct MainObj*) = {
    ice_core_bounce_start,
    ice_core_bounce_move,
    ice_core_bounce_wait,
    ice_core_bounce_reform,
};

void (*ice_core_spray_funcs[3])() = {
    ice_core_spray_fire,
    ice_core_spray_wait_event,
    ice_core_spray_wait,
};

void (*ice_core_intro_funcs[5])() = {
    func_80052218,
    ice_core_intro_wait_player,
    ice_core_intro_descend,
    ice_core_intro_slow,
    ice_core_intro_start_fight,
};
