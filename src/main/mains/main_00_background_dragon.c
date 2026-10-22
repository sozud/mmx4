// MainObj, main_object_update_funcs[0]
// 80040608..80042120
#include "common.h"
#include "main/mains/main_00_background_dragon.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/object_motion.h"
#include "main/stage_objects.h"

#ifdef MMX4_PC
#include "main/1E1BC.h"
#include "main/visuals/visual_03_small_effect.h"
#endif

extern s32 background_dragon_perch_points[][2];
extern struct FixedPointPosition background_dragon_route_starts[];
extern struct FixedPointPosition background_dragon_staging_offsets[];

// background_dragon_state_funcs
extern void (*background_dragon_state_funcs[])(struct MainObj*);

void background_dragon_cleanup(struct MainObj*);

void background_dragon_reset(struct MainObj*);
void background_dragon_wait_for_animation(struct MainObj*);
void background_dragon_fireball(struct MainObj*);
void background_dragon_projectile_attack(struct MainObj*);
void background_dragon_multi_shot(struct MainObj*);
void background_dragon_sequence_begin(struct MainObj*);

void background_dragon_sequence_bob(struct MainObj*);
void background_dragon_sequence(struct MainObj*);

void background_dragon_fly_to_route_start(struct MainObj*);
void background_dragon_fly_offscreen(struct MainObj*);
void background_dragon_fly_to_staging_position(struct MainObj*);
void background_dragon_attach_to_background(struct MainObj*);
void background_dragon_noop(struct MainObj*);

void background_dragon_update(struct MainObj* self)
{
    background_dragon_state_funcs[self->state](self);
}

// background_dragon_init
#ifdef MMX4_PC
void func_80040644(struct MainObj* arg0);
void func_80040838(struct MainObj* arg0);
void func_800419B8(struct MainObj* arg0);
void func_80040CCC(struct MainObj* arg0);
s32 func_80040ABC(struct MainObj* arg0);
void func_80041060(struct MainObj* arg0);
void func_800415B0(struct MainObj* arg0);
extern union AnimationStep* D_800F9934[16];
extern struct Unk_unk68 D_801062F0[32];
void background_dragon_spawn_trail(struct PlayerObj*, s8);
extern void (*background_dragon_step_funcs[13])(struct MainObj*);
extern s16 D_800F98EC[36];
extern u8 background_dragon_attack_map[128];
extern u16 D_800F99BC[4];
#endif

#ifdef MMX4_PC
void func_80040644(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;

    arg0->hp = 0x30;
    arg0->animation_table = (const u8* const*)D_800F9934;
    arg0->unk16 = 0x22;
    arg0->collision_data = (const u16*)D_801062F0;
    arg0->on_screen = 1;
    arg0->unk15 = 0;
    arg0->bg_offset = 0;
    arg0->contact_damage = 1;
    arg0->invincibility_timer = 0;
    arg0->attack_box = NULL;
    arg0->hurt_box = NULL;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = arg0;
    arg0->x_pos.val = 0;
    arg0->y_pos.val = 0;
    background_dragon_spawn_trail(PLAYER_OBJECT(arg0), 0);
    background_dragon_spawn_trail(PLAYER_OBJECT(arg0), 1);
    set_animation(arg0, 0);

    arg0->unk5 = 6;
    arg0->y_speed = 0x18000;
    arg0->x_pos.val = 0x06200000;
    arg0->y_pos.val = 0;
    arg0->x_speed = 0;
    ext[0] = 1;
    ext[2] = 0;
    ext[3] = 0;
    ext[4] = 0;
    arg0->unk7C = 0;
    arg0->unk7E = 0;
    ext[6] = 0;
    ext[5] = 0;
    ext[1] = 0;
    arg0->state = (u8)arg0->state + 1;
    update_on_screen(BASE_OBJECT(arg0), 0xA0, 0xA0);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80040644);
#endif

void background_dragon_spawn_trail(struct PlayerObj* self, s8 arg1)
{
    struct VisualObj* visual_obj;

    visual_obj = find_free_visual_obj();
    if (visual_obj != 0) {
        visual_obj->unk50 = self;
        visual_obj->active = 0x41;
        visual_obj->id = 0x0A;
        visual_obj->unk2 = arg1;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        visual_obj->unk38 = 0;
        visual_obj->unk3C = self->unk3C;
        visual_obj->animation_table = self->animation_table;
        visual_obj->unk40 = self->unk40;
        visual_obj->unk42 = self->unk42;
        visual_obj->unk16 = 0x23;
        visual_obj->x_pos = self->x_pos;
        visual_obj->y_pos = self->y_pos;
    }
}

void background_dragon_reset(struct MainObj* self)
{
    self->unk5 = 0xC;
    set_animation(self, 0);
}

// background_dragon_main
#ifdef MMX4_PC
void func_80040838(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    s32 result;
    u8 saved_step;
    u8 saved_substep;
    s8 flash;
    s32 spawn;
    s32 blocked;
    u8 timer;
    u8 next;
    s16 x;
    s16 y;
    u8 offset_index;

    if (engine_obj.character_state.bytes[0] != 0) {
        ext[5] = 1;
    }
    saved_step = (u8)arg0->unk5;
    saved_substep = (u8)arg0->unk6;
    result = func_8002DD04(arg0);
    if (result < 0) {
        ext[5] = 2;
        arg0->unk5 = saved_step;
        arg0->unk6 = saved_substep;
        arg0->invincibility_timer = 0x1E;
        arg0->unk42 &= 0x7FFF;
        update_on_screen(BASE_OBJECT(arg0), 0xA0, 0xA0);
        return;
    }
    if (result > 0) {
        arg0->unk5 = saved_step;
        arg0->unk6 = saved_substep;
        func_8001540C(2, 0xC, arg0);
        arg0->invincibility_timer = 0x1E;
    }

    flash = arg0->invincibility_timer;
    if (flash != 0) {
        arg0->invincibility_timer = flash - 1;
        if (flash & 2) {
            arg0->unk42 |= 0x8000;
        } else {
            arg0->unk42 &= ~0x8000;
        }
        if (arg0->invincibility_timer == 0) {
            arg0->unk42 &= 0x7FFF;
        }
    }

    background_dragon_step_funcs[arg0->unk5](arg0);

    blocked = get_random_nonzero() & 1;
    if (!blocked && ext[5] == 2) {
        spawn = ((u8)main_bss_state.frame_counter ^ 1) & 1;
        x = arg0->x_pos.i.hi;
        offset_index = (get_random() & 0x1F) % (COUNT(D_800F98EC) / 2);
        if (arg0->unk15 != 0) {
            x -= D_800F98EC[offset_index * 2];
        } else {
            x += D_800F98EC[offset_index * 2];
        }
        offset_index = (get_random() & 0x1F) % (COUNT(D_800F98EC) / 2);
        y = (s16)(arg0->y_pos.u.hi
            + (u16)D_800F98EC[offset_index * 2 + 1]);
        spawn_explosion_at(0, x, y, (u8)spawn)->unk16 = 0x21;
        blocked = 1;
    }

    if (blocked && ext[5] == 2) {
        timer = ext[6];
        ext[6] = timer - 1;
        if (timer != 0) {
            return;
        }
        next = 4;
    } else {
        if (arg0->hp >= 0x18) {
            return;
        }
        timer = ext[6];
        ext[6] = timer - 1;
        if (timer != 0) {
            return;
        }
        next = 0x1E;
    }
    ext[6] = next;
    arg0->unk42 ^= 0x8000;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80040838);
#endif

// background_dragon_pick_step
#ifdef MMX4_PC
s32 func_80040ABC(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    const s8* flags = &engine_obj.character_state.bytes[1];
    s32 distance;
    s32 index;
    s32 kind;
    s32 value;
    s32 remainder;

    arg0->unk2 = get_random() & 1;
    if (ext[5] != 0) {
        return 8;
    }

    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance < 0) {
        distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    }
    if (distance >= 0x49) {
        return 6;
    }

    index = (s32)(s16)arg0->x_pos.i.hi >> 4;
    if (index < 0x50) {
        return 0xC;
    }
    index -= 0x50;
    kind = background_dragon_attack_map[index];

    switch (kind) {
    case 0:
        value = get_random() & 3;
        if (value == 1) {
            ext[1] = 3;
            return 3;
        }
        if (value == 0) {
            return 0xC;
        }
        return value == 2 ? 2 : 5;
    case 1:
    case 2:
    case 3:
        ext[2 + ext[1]] = (u8)flags[ext[1]];
        kind = background_dragon_attack_map[index];
        if (ext[1 + kind] != 0) {
            return 2;
        }
        ext[1] = kind - 1;
        return 3;
    case 4:
        ext[1] = 3;
        return 3;
    case 5:
        return 2;
    case 6:
        return 5;
    case 8:
        value = get_random_nonzero();
        remainder = value - ((value >= 0 ? value >> 2 : (value + 3) >> 2) * 4);
        if (remainder >= 3) {
            return 0xC;
        }
        if (remainder > 0) {
            return 2;
        }
        if (remainder != 0) {
            return 0xC;
        }
        return 8;
    default:
        remainder = get_random_nonzero() % 3;
        if (remainder == 1) {
            ext[1] = 3;
            return 3;
        }
        return remainder == 0 ? 2 : 5;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80040ABC);
#endif

// background_dragon_hover
#ifdef MMX4_PC
void func_80040CCC(struct MainObj* arg0)
{
    s32 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    arg0->y_pos.u.hi += (s8)arg0->animation_step.fields.event;

    distance = g_Player.x_pos.val - arg0->x_pos.val;
    if (distance < 0) {
        distance = arg0->x_pos.val - g_Player.x_pos.val;
    }
    if (distance > 0x20000) {
        distance = 0x20000;
    }
    arg0->x_speed = distance;
    if (arg0->x_pos.val < g_Player.x_pos.val) {
        arg0->x_speed = -distance;
    }

    arg0->y_speed = 0;
    move_object(MOVING_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);

    arg0->unk15 = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0x40 : 0;
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = func_80040ABC(arg0);
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80040CCC);
#endif

void background_dragon_wait_for_animation(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen((struct BaseObj*)self, 0x90, 0x90);
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 4;
    }
}

void background_dragon_fireball_begin(struct MainObj* self)
{
    s16 x_pos_hi;

    x_pos_hi = self->x_pos.i.hi;
    if (x_pos_hi > 0xC90) {
        set_animation(self, 0);
        self->unk5 = 0xC;
        self->unk6 = 0;
        update_on_screen((struct BaseObj*)self, 0x90, 0x90);
    } else {
        if (x_pos_hi > 0xC40) {
            self->unk15 = 0x40;
        }
        self->unk6++;
        self->y_pos.val = FIXED(368);
        set_animation(self, 3);
        self->x_speed = FIXED(self->unk15 != 0 ? 1 : -1);
        self->y_speed = 0;
        update_on_screen((struct BaseObj*)self, 0x90, 0x90);
    }
}

void background_dragon_fireball_update(struct MainObj* self)
{
    struct ShotObj* shot_obj;
    struct MiscObj* misc_obj;
    s32 x_pos;

    move_object((struct MovingObj*)self);
    animate_object(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 1) {
        shot_obj = find_free_shot_obj();
        if (shot_obj != 0) {
            shot_obj->active = 0x41;
            shot_obj->id = 0;
            shot_obj->unk7C = (struct WeaponObj*)self;
            shot_obj->state = 0;
            shot_obj->unk5 = 0;
            shot_obj->unk6 = 0;
            shot_obj->unk2 = 1;
        }

        misc_obj = find_free_misc_obj();
        if (misc_obj != 0) {
            misc_obj->active = 0x41;
            misc_obj->id = 4;
            misc_obj->unk2 = 3;
            misc_obj->ext.ready_text.owner = (struct EffectObj*)self;
            misc_obj->state = 0;

            x_pos = self->x_pos.val;
            misc_obj->x_pos.val = x_pos + (FIXED((self->unk15 == 0) ? 60 : -60));
            misc_obj->y_pos.val = self->y_pos.val + FIXED(68);
        }

        self->animation_step.fields.event = 0;
        self->x_speed = 0;
        self->y_speed = FIXED(-0.25);
        func_8001540C(2, 4, self);
    }

    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        self->unk5 = 0xC;
        self->unk6 = 0;
    }

    update_on_screen((struct BaseObj*)self, 0x90, 0x90);
}

void background_dragon_fireball_begin(struct MainObj* self);

void background_dragon_fireball_update(struct MainObj* self);

void background_dragon_fireball(struct MainObj* self)
{
    if (self->unk6 == 0) {
        background_dragon_fireball_begin(self);
    } else {
        background_dragon_fireball_update(self);
    }
}

// background_dragon_projectile_attack_begin
#ifdef MMX4_PC
void func_80041060(struct MainObj* arg0)
{
    s32 velocity;
    u8 next_substep;
    u8 index = arg0->ext.main_0.index;
    s32 distance;

    if (index != 3) {
        distance = arg0->x_pos.i.hi - D_800F99BC[index];
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 2) {
            distance = arg0->y_pos.i.hi - 0x170;
            if (distance < 0) {
                distance = -distance;
            }
            if (distance < 2) {
                arg0->y_pos.val = 0x01700000;
                next_substep = (u8)arg0->unk6;
                velocity = -0xC000;
                arg0->unk15 = 0;
                goto start_attack;
            }
        }

        set_velocity_from_angle(MOVING_OBJECT(arg0),
            angle_to_point(OBJECT_HEADER(arg0),
                (s32)D_800F99BC[index] << 16, 0x01700000));
        arg0->x_speed *= 2;
        arg0->y_speed *= 2;
        move_object(MOVING_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
    } else {
        velocity = -0xC000;
        arg0->y_pos.val = 0x01700000;
        next_substep = (u8)arg0->unk6;

    start_attack:
        arg0->unk6 = next_substep + 1;
        if (arg0->unk15 != 0) {
            velocity = 0xC000;
        }
        arg0->x_speed = velocity;
        arg0->y_speed = 0x8000;
        set_animation(arg0, 1);
    }

    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80041060);
#endif

void background_dragon_projectile_attack_update(struct MainObj* self)
{
    struct MiscObj* misc;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 3) {
        move_object((struct MovingObj*)self);
    }
    if (self->animation_step.fields.event == 1) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0;
            shot->unk7C = (struct WeaponObj*)self;
            shot->state = 0;
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->unk2 = 0;
        }
        self->animation_step.fields.event = 0;
        self->x_speed = self->unk15 != 0 ? FIXED(-3.75) : FIXED(3.75);
        self->y_speed = FIXED(-1);
        func_8001540C(2, 4, self);
    }
    if (self->animation_step.fields.event == 2) {
        if (self->ext.main_0.index < 3U && engine_obj.character_state.bytes[self->ext.main_0.index + 1] == 0) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 1;
                misc->id = 4;
                misc->ext.ready_text.owner = (struct EffectObj*)self;
                misc->state = 4;
                misc->unk5 = 0;
                misc->unk6 = 0;
                misc->unk2 = self->ext.main_0.index;
            }
            self->animation_step.fields.event = 0;
            apply_tile_effect(self->ext.main_0.index + 1, 0, 0);
            self->ext.main_0.flags[self->ext.main_0.index] = 1;
            engine_obj.character_state.bytes[self->ext.main_0.index + 1] = 1;
            start_screen_shake_y(0x18, 3, 1);
        }
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        self->unk5 = 0xC;
        self->unk6 = 0;
    }
    update_on_screen((struct BaseObj*)self, 0x90, 0x90);
}

void func_80041060(struct MainObj* self);

void background_dragon_projectile_attack_update(struct MainObj* self);

void background_dragon_projectile_attack(struct MainObj* self)
{
    if (self->unk6 == 0) {
        func_80041060(self);
    } else {
        background_dragon_projectile_attack_update(self);
    }
}

void background_dragon_multi_shot_begin(struct BaseObj* self)
{
    self->unk6++;
    set_animation(self, 7);
    update_on_screen(self, 0x90, 0x90);
}

void background_dragon_multi_shot_update(struct MainObj* self)
{
    struct VisualObj* visual;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0xA;
            visual->unk50 = (struct PlayerObj*)self;
            visual->state = 2;
            visual->unk5 = 0;
            visual->unk6 = 0;
        }
        self->animation_step.fields.event = 0;
        func_8001540C(2, 0xB, self);
    }
    if ((self->animation_step.fields.event == 2 || self->animation_step.fields.event == 3)) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0;
            shot->unk7C = (struct WeaponObj*)self;
            shot->state = 0;
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->unk2 = self->animation_step.fields.event;
        }
        self->animation_step.fields.event = 0;
        func_8001540C(2, 9, self);
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 6);
        self->unk5 = 9;
        self->unk6 = 0;
    }
    update_on_screen((struct BaseObj*)self, 0x90, 0x90);
}

void background_dragon_multi_shot_update(struct MainObj* self);

void background_dragon_multi_shot(struct MainObj* self)
{
    if (self->unk6 == 0) {
        background_dragon_multi_shot_begin((struct BaseObj*)self);
    } else {
        background_dragon_multi_shot_update(self);
    }
}

void background_dragon_sequence_begin(struct MainObj* self)
{
    self->unk15 = 0;
    set_animation(self, 0);
    self->unk6++;
    update_on_screen(self, 0x90, 0x90);
}

// background_dragon_swoop
#ifdef MMX4_PC
void func_800415B0(struct MainObj* arg0)
{
    s32 offset = engine_obj.cur_character == 0 ? 0x480000 : 0x4A0000;
    struct ShotObj* shot;
    struct MiscObj* misc;
    s32 target;
    s32 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    target = arg0->unk15 != 0 ? g_Player.x_pos.val + offset
                              : g_Player.x_pos.val - offset;
    set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_point(OBJECT_HEADER(arg0), target, 0x02140000));
    arg0->x_speed *= 4;
    arg0->y_speed *= 4;
    move_object(MOVING_OBJECT(arg0));

    distance = arg0->x_pos.val - target;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance <= 0x7FFFF) {
        distance = arg0->y_pos.i.hi - 0x214;
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 8) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0;
                shot->unk2 = 4;
                shot->unk7C = (struct WeaponObj*)arg0;
                shot->state = 0;
            }
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 4;
                misc->unk2 = 0;
                misc->ext.pointer.unk50 = arg0;
                misc->state = 2;
            }
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 4;
                misc->unk2 = 1;
                misc->ext.pointer.unk50 = arg0;
                misc->state = 2;
            }
            set_animation(arg0, arg0->unk7E != 0 ? 0xD : 0xF);
            arg0->x_speed = 0;
            arg0->x_pos.val = target;
            arg0->y_pos.i.hi = 0x214;
            arg0->unk6 = (u8)arg0->unk6 + 1;
            func_8001540C(2, 4, arg0);
        }
    }
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_800415B0);
#endif

void background_dragon_sequence_bob(struct MainObj* self)
{

    if (self->animation_step.fields.event == 0) {
        self->y_speed = 0;
    }
    if (self->animation_step.fields.event == 1) {
        self->y_speed = FIXED(5.33333);
    }
    if (self->animation_step.fields.event == 2) {
        self->y_speed = FIXED(-5.33333);
    }
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        if (++self->unk7E > 2) {
            self->unk7E = 0;
            if (self->ext.main_0.exit_mode != 0) {
                self->unk5 = 8;
            } else {
                self->unk5 = 6;
            }
        } else {
            if (self->ext.main_0.exit_mode != 0) {
                self->unk5 = 8;
            } else {
                self->unk5 = 5;
            }
        }
        self->unk6 = 0;
    }
    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void background_dragon_sequence(struct MainObj* self)
{
    s32 state;

    state = self->unk6;
    if (state != 1) {
        if (state <= 1) {
            if (state == 0) {
                background_dragon_sequence_begin(self);
                return;
            }
        }
    } else {
        func_800415B0(self);
        return;
    }
    background_dragon_sequence_bob(self);
}

// background_dragon_chase
#ifdef MMX4_PC
void func_800419B8(struct MainObj* arg0)
{
    s32 distance;

    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), g_Player.x_pos.val, 0x01700000));

    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0x38) {
        distance = 0x38;
    } else if (distance >= 0x40) {
        distance = 0x40;
    }
    arg0->x_speed = (arg0->x_speed * distance) >> 4;

    distance = g_Player.y_pos.i.hi - (arg0->y_pos.i.hi + 0x40);
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0x18) {
        distance = 0x18;
    } else if (distance >= 0x40) {
        distance = 0x40;
    }
    arg0->y_speed = (arg0->y_speed * distance) >> 4;

    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));

    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 8) {
        s32 height = arg0->y_pos.i.hi - 0x170;

        if (height < 0) {
            height = -height;
        }
        if (height < 8) {
            arg0->y_pos.i.hi = 0x170;
            arg0->unk5 = 0xC;
            arg0->x_pos.i.hi = g_Player.x_pos.u.hi;
        }
    }

    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_800419B8);
#endif

void background_dragon_fly_to_route_start(struct MainObj* self)
{
    s32 temp_a0;

    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_point(
            OBJECT_HEADER(self), background_dragon_perch_points[self->unk2 >> 1][0],
            background_dragon_perch_points[self->unk2 >> 1][1]));

    self->x_speed *= 2;
    self->y_speed *= 2;
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    temp_a0 = self->x_pos.val - background_dragon_perch_points[self->unk2 >> 1][0];
    if (0 <= temp_a0) {
        if (temp_a0 >= 0x20000) {
            update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
            return;
        }
    } else if (background_dragon_perch_points[self->unk2 >> 1][0] - self->x_pos.val >= 0x20000) {
        update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
        return;
    }

    temp_a0 = self->y_pos.val - background_dragon_perch_points[self->unk2 >> 1][1];
    if (temp_a0 >= 0) {
        if (temp_a0 > 0x1FFFF) {
            update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
            return;
        }
    } else if (background_dragon_perch_points[self->unk2 >> 1][1] - self->y_pos.val >= 0x20000) {
        update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
        return;
    }
    self->unk5 = 1;

    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void background_dragon_fly_offscreen(struct MainObj* self)
{
    s32 target_x;
    s32 target_y;

    switch (self->unk2) {
    case 0:
        target_x = background_objects[0].x_pos.val + FIXED(-256);
        target_y = background_objects[0].y_pos.val + FIXED(-256);
        break;
    case 1:
        target_x = background_objects[0].x_pos.val + FIXED(-256);
        target_y = background_objects[0].y_pos.val + FIXED(496);
        break;
    }

    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_point(OBJECT_HEADER(self), target_x, target_y));

    if (self->ext.main_0.exit_mode == 2) {
        self->x_speed = self->x_speed * 2;
        *(volatile s32*)&self->y_speed = self->y_speed * 2;
    } else {
        self->x_speed = self->x_speed * 4;
        *(volatile s32*)&self->y_speed = self->y_speed * 4;
    }

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    if (self->on_screen == 0) {
        if (self->ext.main_0.exit_mode != 0) {
            self->state = 2;
            return;
        }

        self->unk16 = 0x12;
        self->unk5 = 7;
        self->bg_offset = -1;
        self->x_pos.val = background_dragon_route_starts[self->unk2].x;
        self->y_pos.val = background_dragon_route_starts[self->unk2].y;
        self->ext.main_0.background_relative = 0;
        set_animation(self, 6);

        if ((self->unk2 == 2 || self->unk2 == 3)) {
            self->unk15 = 0x40;
        } else {
            self->unk15 = 0;
        }
    }

    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void background_dragon_fly_to_staging_position(struct MainObj* self)
{
    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_point(
            OBJECT_HEADER(self),
            background_dragon_route_starts[self->unk2].x,
            background_dragon_route_starts[self->unk2].y));
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    if (self->on_screen == 0) {
        if (self->ext.main_0.exit_mode != 0) {
            self->state = 2;
            return;
        }

        self->unk16 = 0x22;
        self->unk5 = 0xA;
        if ((self->unk2 == 2 || self->unk2 == 3)) {
            self->unk15 = 0x40;
        } else {
            self->unk15 = 0;
        }
    }

    update_on_screen((struct BaseObj*)self, 0x70, 0x70);
}

void background_dragon_attach_to_background(struct MainObj* self)
{
    set_animation(self, 0);
    self->x_pos.val = background_objects[0].x_pos.val + background_dragon_staging_offsets[self->unk2].x;
    self->y_pos.val = background_objects[0].y_pos.val + background_dragon_staging_offsets[self->unk2].y;
    self->unk5 = 6;
    self->unk15 = 0;
    self->bg_offset = 0;
    self->ext.main_0.background_relative = 1;
}

void background_dragon_noop(struct MainObj* self)
{
}

void background_dragon_cleanup(struct MainObj* self)
{
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

union AnimationStep D_800F96F4[] = {
    { 0x0001FF10 },
    { 0x01010108 },
    { 0x02010110 },
    { 0x01FDFF08 },
};

union AnimationStep D_800F9704[] = {
    { 0x00010008 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x0501000A },
    { 0x06010019 },
    { 0x0601030F },
    { 0x07010102 },
    { 0x08010213 },
    { 0x08F80001 },
};

union AnimationStep D_800F9728[] = {
    { 0x09010105 },
    { 0x0A010010 },
    { 0x0AFE0001 },
};

union AnimationStep D_800F9734[] = {
    { 0x00010008 },
    { 0x0B01000A },
    { 0x0C010003 },
    { 0x0D010004 },
    { 0x0E010019 },
    { 0x0F010102 },
    { 0x10010028 },
    { 0x10F90001 },
};

union AnimationStep D_800F9754[] = {
    { 0x11010105 },
    { 0x12010025 },
    { 0x12FE0001 },
};

union AnimationStep D_800F9760[] = {
    { 0x13010008 },
    { 0x14010008 },
    { 0x15010008 },
    { 0x16010008 },
    { 0x17010008 },
    { 0x18FB0108 },
};

union AnimationStep D_800F9778[] = {
    { 0x19010008 },
    { 0x1A010008 },
    { 0x1B010008 },
    { 0x1CFD0008 },
};

union AnimationStep D_800F9788[] = {
    { 0x1B010003 },
    { 0x1D010003 },
    { 0x1E010003 },
    { 0x1F010136 },
    { 0x1F010003 },
    { 0x1E010203 },
    { 0x1F010014 },
    { 0x1F010003 },
    { 0x1E010303 },
    { 0x1F010013 },
    { 0x1FF30001 },
};

union AnimationStep D_800F97B4[] = {
    { 0x20010003 },
    { 0x21010003 },
    { 0x22010003 },
    { 0x23010003 },
    { 0x24010003 },
    { 0x25010003 },
    { 0x20010003 },
    { 0x21010003 },
    { 0x22010003 },
    { 0x23010003 },
    { 0x24010003 },
    { 0x25010002 },
    { 0x25EE0001 },
};

#if defined(MMX4_PC) && !defined(MMX4_WIN32)
static struct {
    union AnimationStep D_800F9778[4];
    union AnimationStep D_800F9788[11];
    union AnimationStep D_800F97B4[13];
} background_dragon_anim_run = {
    {
        { 0x19010008 },
        { 0x1A010008 },
        { 0x1B010008 },
        { 0x1CFD0008 },
    },
    {
        { 0x1B010003 },
        { 0x1D010003 },
        { 0x1E010003 },
        { 0x1F010136 },
        { 0x1F010003 },
        { 0x1E010203 },
        { 0x1F010014 },
        { 0x1F010003 },
        { 0x1E010303 },
        { 0x1F010013 },
        { 0x1FF30001 },
    },
    {
        { 0x20010003 },
        { 0x21010003 },
        { 0x22010003 },
        { 0x23010003 },
        { 0x24010003 },
        { 0x25010003 },
        { 0x20010003 },
        { 0x21010003 },
        { 0x22010003 },
        { 0x23010003 },
        { 0x24010003 },
        { 0x25010002 },
        { 0x25EE0001 },
    },
};
#define D_800F9778 background_dragon_anim_run.D_800F9778
#define D_800F9788 background_dragon_anim_run.D_800F9788
#define D_800F97B4 background_dragon_anim_run.D_800F97B4
#endif

union AnimationStep D_800F97E8[] = {
    { 0x1F010003 },
    { 0x1E010003 },
    { 0x1FFE0014 },
};

union AnimationStep D_800F97F4[] = {
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010002 },
    { 0x29FD0002 },
};

union AnimationStep D_800F9804[] = {
    { 0x2A010001 },
    { 0x2B010003 },
    { 0x2C010003 },
    { 0x2D010003 },
    { 0x2E010003 },
    { 0x2FFB0003 },
};

union AnimationStep D_800F981C[] = {
    { 0x31010003 },
    { 0x3201003C },
    { 0x31010002 },
    { 0x31FD0001 },
};

union AnimationStep D_800F982C[] = {
    { 0x30010103 },
    { 0x30010103 },
    { 0x3001003C },
    { 0x30010203 },
    { 0x30010202 },
    { 0x30FF0201 },
};

union AnimationStep D_800F9844[] = {
    { 0x31010003 },
    { 0x32010003 },
    { 0x3301003C },
    { 0x32010003 },
    { 0x31010002 },
    { 0x31FB0001 },
};

union AnimationStep D_800F985C[] = {
    { 0x30010103 },
    { 0x3001003C },
    { 0x30010202 },
    { 0x30FF0201 },
};

u8 background_dragon_attack_map[128] = {
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x00,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x06,
    0x06,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x07,
    0x07,
    0x07,
    0x07,
    0x07,
    0x07,
    0x07,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
};

s16 D_800F98EC[36] = {
    (s16)0xFFD3,
    (s16)0x0021,
    (s16)0x0000,
    (s16)0x001E,
    (s16)0xFFD4,
    (s16)0x001F,
    (s16)0xFFE0,
    (s16)0x003B,
    (s16)0xFFDF,
    (s16)0x0050,
    (s16)0x0029,
    (s16)0x0053,
    (s16)0x0013,
    (s16)0xFFFF,
    (s16)0xFFDD,
    (s16)0xFFF5,
    (s16)0xFFDD,
    (s16)0xFFF5,
    (s16)0xFFF3,
    (s16)0xFFF5,
    (s16)0xFFF3,
    (s16)0xFFE0,
    (s16)0x0037,
    (s16)0x000B,
    (s16)0xFFCC,
    (s16)0x000F,
    (s16)0xFFEE,
    (s16)0x000D,
    (s16)0xFFE7,
    (s16)0x0024,
    (s16)0x0010,
    (s16)0x0021,
    (s16)0x0016,
    (s16)0xFFE3,
    (s16)0xFFE7,
    (s16)0xFFE3,
};

union AnimationStep* D_800F9934[16] = {
    D_800F96F4,
    D_800F9704,
    D_800F9728,
    D_800F9734,
    D_800F9754,
    D_800F9760,
    D_800F9778,
    D_800F9788,
    D_800F97B4,
    D_800F97E8,
    D_800F97F4,
    D_800F9804,
    D_800F981C,
    D_800F982C,
    D_800F9844,
    D_800F985C,
};

void (*background_dragon_state_funcs[])(struct MainObj*) = {
    func_80040644,
    func_80040838,
    background_dragon_cleanup,
};

s16 D_800F9980[4] = { -1, 1, 1, -1 };

void (*background_dragon_step_funcs[13])(struct MainObj*) = {
    background_dragon_reset,
    background_dragon_wait_for_animation,
    background_dragon_fireball,
    background_dragon_projectile_attack,
    background_dragon_multi_shot,
    background_dragon_sequence,
    func_800419B8,
    background_dragon_fly_to_route_start,
    background_dragon_fly_offscreen,
    background_dragon_fly_to_staging_position,
    background_dragon_attach_to_background,
    background_dragon_noop,
    func_80040CCC,
};

u16 D_800F99BC[4] = { 0x6A0, 0x8A0, 0xAA0, 0 };

s32 background_dragon_perch_points[][2] = {
    { FIXED(40), FIXED(179) },
    { FIXED(280), FIXED(179) },
};

struct FixedPointPosition background_dragon_route_starts[2] = {
    { -0x800000, 0xB30000 },
    { -0x800000, 0x1700000 },
};

struct FixedPointPosition background_dragon_staging_offsets[4] = {
    { -0x800000, -0x800000 },
    { -0x800000, 0x1700000 },
    { 0x1C00000, -0x800000 },
    { 0x1C00000, 0x1700000 },
};
