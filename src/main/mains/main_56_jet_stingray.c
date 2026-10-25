// MainObj, main_object_update_funcs[56]
// 8006FABC..80072194
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_55_jet_stingray_flyby.h"
#include "main/mains/main_56_jet_stingray.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"

extern struct Unk_unk68 jet_stingray_swim_attack_box;
extern struct Unk_unk68 jet_stingray_swim_hurt_box;

extern struct Unk_unk68 jet_stingray_debris[2];

extern struct Unk_unk68 jet_stingray_dash_attack_box;
extern struct Unk_unk68 jet_stingray_dash_hurt_box;

// jet_stingray_intro_funcs
extern s8 jet_stingray_bubble_offsets[];
extern void (*jet_stingray_intro_funcs[])(struct MainObj*);
void jet_stingray_intro_setup(struct MainObj*);

void jet_stingray_intro_emerge(struct MainObj*);
void jet_stingray_intro_rise(struct MainObj*);
void jet_stingray_intro_pose(struct MainObj*);
void jet_stingray_intro_fill_health(struct MainObj*);
void jet_stingray_intro_finish(struct MainObj*);

// jet_stingray_swim_funcs
extern void (*jet_stingray_swim_funcs[])(struct MainObj*);
void jet_stingray_swim_start(struct MainObj*);

void jet_stingray_swim_next(struct MainObj*);

// jet_stingray_vortex_funcs
extern void (*jet_stingray_vortex_funcs[])(struct MainObj*);
void jet_stingray_vortex_start(struct MainObj*);

void jet_stingray_vortex_wait(struct MainObj*);
void jet_stingray_vortex_finish(struct MainObj*);

extern struct Unk_unk68 jet_stingray_ambush_hurt_box;
void jet_stingray_ambush_exit(struct MainObj*);

// jet_stingray_dash_funcs
extern void (*jet_stingray_dash_funcs[])(struct MainObj*);
void jet_stingray_dash_start(struct MainObj*);
void jet_stingray_dash_charge(struct MainObj*);
void jet_stingray_dash_return(struct MainObj*);

// jet_stingray_leap_funcs
extern struct Unk_unk68 jet_stingray_leap_attack_box;
extern struct Unk_unk68 jet_stingray_leap_hurt_boxes[];
extern void (*jet_stingray_leap_funcs[])(struct MainObj*);
void jet_stingray_leap_start(struct MainObj*);
void jet_stingray_leap_fall(struct MainObj*);
void jet_stingray_leap_return(struct MainObj*);

// jet_stingray_missiles_funcs
extern void (*jet_stingray_missiles_funcs[])(struct MainObj*);

void jet_stingray_missiles_repeat(struct MainObj*);
void jet_stingray_missiles_finish(struct MainObj*);

// jet_stingray_missiles_wide_funcs
extern void (*jet_stingray_missiles_wide_funcs[])(struct MainObj*);

// jet_stingray_stagger_funcs
extern void (*jet_stingray_stagger_funcs[])(struct MainObj*);
void jet_stingray_stagger_start(struct MainObj*);
void jet_stingray_stagger_wait(struct MainObj*);
void jet_stingray_stagger_shake(struct MainObj*);
void jet_stingray_stagger_flee(struct MainObj*);
void jet_stingray_stagger_return(struct MainObj*);

// jet_stingray_step_funcs
void jet_stingray_reset(struct MainObj* arg0);
void jet_stingray_swim(struct MainObj* arg0);
void jet_stingray_land(struct MainObj* arg0);
void jet_stingray_vortex(struct MainObj* arg0);

void jet_stingray_dash(struct MainObj* arg0);
void jet_stingray_apply_leap(struct MainObj* arg0);
void jet_stingray_leap(struct MainObj* arg0);
void jet_stingray_missiles(struct MainObj* arg0);
void jet_stingray_missiles_wide(struct MainObj* arg0);

// jet_stingray_death_funcs
extern void (*jet_stingray_death_funcs[])(struct MainObj*);
void jet_stingray_death_start(struct MainObj*);

void jet_stingray_death_finish(struct MainObj*);

// jet_stingray_state_funcs
extern void (*jet_stingray_state_funcs[])(struct MainObj*);
void jet_stingray_intro(struct MainObj*);

void jet_stingray_death(struct MainObj* arg0);
void jet_stingray_stagger(struct MainObj*);

extern void (*jet_stingray_step_funcs[10])();

// jet_stingray_flyby_init

void jet_stingray_flyby_wait_on_screen(struct MainObj* self);

// jet_stingray_flyby_enter_straight

// jet_stingray_flyby_enter_aimed

void jet_stingray_flyby_enter(struct MainObj* self);

// jet_stingray_flyby_cruise

void jet_stingray_flyby_attack_rise(struct MainObj* self);

void jet_stingray_flyby_attack_fire(struct MainObj* self);

void jet_stingray_flyby_attack_end(struct MainObj* self);

void jet_stingray_flyby_attack_align(struct MainObj* self);

void jet_stingray_flyby_attack(struct MainObj* self);

void jet_stingray_flyby_charge_windup(struct MainObj* self);

// jet_stingray_flyby_charge_fire

void jet_stingray_flyby_charge(struct MainObj* self);

void jet_stingray_flyby_drift(struct MainObj* self);

// jet_stingray_flyby_destroyed

void jet_stingray_flyby_main(struct MainObj* self);

void jet_stingray_flyby_despawn(struct MainObj* self)
{
    engine_obj.enable_boss = 0;
    despawn_object_permanently(OBJECT_HEADER(self));
}

void jet_stingray_flyby_update(struct MainObj* self)
{
    jet_stingray_flyby_state_funcs[self->state](self);
}

// jet_stingray_spawn_water
struct MainObj* func_8006FB20(struct MainObj* self, s32 dx, s32 dy)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0x17;
        visual->unk2 = 1;
        visual->x_pos.i.hi = self->x_pos.i.hi + dx;
        visual->y_pos.i.hi = self->y_pos.i.hi + dy;
        visual->unk40 = self->unk40;
        visual->animation_table = ANIMATED_OBJECT(self)->animation_table;
        visual->unk3C = ANIMATED_OBJECT(self)->unk3C;
        visual->unk42 = self->unk42;
        visual->unk15 = self->unk15;
        visual->bg_offset = self->bg_offset;
        visual->unk50 = PLAYER_OBJECT(self);
        visual->x_vel.val = 0;
        visual->y_vel.val = 0;
        return MAIN_OBJECT(visual);
    }
    return NULL;
}

struct VisualObj* jet_stingray_spawn_splash(struct MainObj* self)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual != 0) {
        visual->active = 0x41;
        visual->id = 0x17;
        visual->unk2 = 2;
        visual->x_pos.val = self->x_pos.val;
        visual->y_pos.val = self->y_pos.val - FIXED(8);
        visual->unk40 = self->unk40;
        visual->animation_table = ANIMATED_OBJECT(self)->animation_table;
        visual->unk3C = ANIMATED_OBJECT(self)->unk3C;
        visual->unk15 = self->unk15;
        visual->bg_offset = self->bg_offset;
        visual->unk50 = PLAYER_OBJECT(self);
        func_8001540C(2, SATURN_SOUND(0xAE, 0x19), self);
        return visual;
    }
    return 0;
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_56_jet_stingray", jet_stingray_check_surface);
#else
u8 jet_stingray_check_surface(struct PlayerObj* self, s32 arg1, s32 arg2)
{
    s16 temp_a1;
    s16 temp_a2;
    s32 temp_v0;
    u8 tile;
    u8 temp_v1;
    s32 var_v0;

    temp_a1 = self->x_pos.u.hi + arg1;
    temp_a2 = self->y_pos.u.hi + arg2;
    temp_v0 = ((s32(*)(struct PlayerObj*, s16, s16))func_8002D724)(
        self, temp_a1, temp_a2);
    tile = temp_v0;
    var_v0 = 1;
    if (9U <= (u32)((temp_v0 - 0x10) & 0xFF)) {
        temp_v1 = tile;
        if (temp_v1 == 0x38) {
            return (self->y_pos.i.hi >= 0x121) * 2;
        }
        var_v0 = -(temp_v1 == 0x24) & 3;
        return var_v0;
    }
    return var_v0;
}
#endif

extern struct Unk_unk68 jet_stingray_ambush_attack_box;
extern struct Unk_unk68 jet_stingray_ambush_drop_attack_box;

extern void* jet_stingray_patterns[];
extern u8 jet_stingray_pattern_weights[];

void jet_stingray_intro_setup(struct MainObj* self)
{
    if (g_Player.capsule_state == 0) {
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        self->unk5++;
        self->on_screen = 0;
        self->hurt_box = NULL;
        self->attack_box = NULL;
        self->terrain_box = NULL;
        self->collision_data = D_801079F8;
        self->bg_offset = g_Player.bg_offset;
        if (engine_obj.stage != 0xC) {
            self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
        } else {
            self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0x160);
            self->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
            self->unk42 = OBJECT_CLUT(0x7888);
        }
        self->animation_table = (const u8* const*)jet_stingray_animations;
        self->unk16 = VISUAL_SATURN_LAYER(6);
        self->hp = 0;
        self->contact_damage = 4;
        self->x_pos.val = (background_objects[self->bg_offset].unk1E + 0x10B) << 16;
        self->y_pos.val = (background_objects[self->bg_offset].unk22 + 0x130) << 16;
        self->unk62 = 0;
        self->unk63 = 2;
        self->ext.main_56.object.effect = NULL;
        self->ext.main_56.pattern = NULL;
    }
}

void jet_stingray_intro_warning(struct MainObj* self)
{
    s16 countdown;
    struct EffectObj* effect;

    self->on_screen = 0;
    switch (self->unk6) {
    case 0:
        effect = find_free_effect_obj();
        if (effect != 0) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_56.object.effect = effect;
            self->unk6 = (u8)self->unk6 + 1;
        }
        break;
    case 1:
        if (self->ext.main_56.object.effect->active == 0) {
            self->unk6++;
            self->unk7C = 0x3C;
        }
        break;
    case 2:
        countdown = --self->unk7C;
        if (countdown == 0) {
            self->unk5 = (u8)self->unk5 + 1;
            self->unk6 = 0;
            set_animation(self, 0x1D);
        }
        break;
    }
}

void jet_stingray_intro_emerge(struct MainObj* self)
{
    struct MainObj* obj;
    u8 counter;

    self->on_screen = 1;
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = (u8)self->unk5 + 1;
        self->unk7C = 0x1E;
        self->y_speed = FIXED(1);
        set_animation(self, 0x26);
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = self;
        jet_stingray_bubble_index = 0;
        do {
            obj = func_8006FB20(self, jet_stingray_bubble_offsets[jet_stingray_bubble_index], 0x18);
            obj->y_speed = FIXED(0.875);
            counter = jet_stingray_bubble_index + 1;
            jet_stingray_bubble_index = counter;
        } while ((u32)(counter & 0xFF) < 3U);
        func_8001540C(2, SATURN_SOUND(0xAD, 0x18), self);
    }
}

void jet_stingray_intro_rise(struct MainObj* self)
{
    self->on_screen = 1;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5++;
        self->y_speed = 0;
        set_animation(self, 0x27);
    }
}

void jet_stingray_intro_pose(struct MainObj* self)
{
    self->on_screen = 1;
    if (self->unk6 == 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            if (engine_obj.stage == 5) {
                func_8002217C(0xD, 0xFF, engine_obj.character_state.bytes[8]);
                engine_obj.character_state.bytes[8] = 1;
            }
            self->unk6 = (u8)self->unk6 + 1;
        }
    } else if (abc_object.unkC == 0) {
        self->unk6 = 0;
        self->unk5 = (u8)self->unk5 + 1;
        self->unk7C = 2;
        play_boss_voice(4);
    }
}

void jet_stingray_intro_fill_health(struct MainObj* self)
{

    self->on_screen = 1;
    animate_object(ANIMATED_OBJECT(self));
    if ((update_boss_music_delay() == 0) && (self->animation_step.fields.relative_step == 0)) {
        if (self->hp < 0x30) {
            if (--self->unk7C == 0) {
                func_8001540C(0, SATURN_SOUND(0xE, 0x14), 0);
                self->unk7C = 2;
            }
            self->hp++;
            return;
        }
        self->unk7C = 0x3C;
        self->unk5++;
    }
}

void jet_stingray_intro_finish(struct MainObj* self)
{
    self->on_screen = 1;
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->state++;
        self->unk7 = 0;
        player_end_script_action();
    }
}

void jet_stingray_intro(struct MainObj* self)
{
    jet_stingray_intro_funcs[self->unk5](self);
    if (self->on_screen != 0) {
        is_on_screen(BASE_OBJECT(self));
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_56_jet_stingray", jet_stingray_at_target);
#else
s32 jet_stingray_at_target(struct MainObj* self, s32 arg1, s32 arg2)
{
    s32 v1, v2;
    v1 = arg1 << 0x10;
    v2 = arg2 << 0x10;
    POS_BOUNDS_CHECK_FAIL_RET0(self->x_pos.val, v1)
    POS_BOUNDS_CHECK_FAIL_RET0(self->y_pos.val, v2)
    return 1;
}
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_56_jet_stingray", jet_stingray_choose_pattern);
#else
void jet_stingray_choose_pattern(struct MainObj* self)
{
    u32 idx;
    u8** table;
    u8* weights;
    u8* base;
    u8 i;
    u8 rnd;
    u32 gr;

    idx = self->hp - 1;
    if ((s32)idx < 0)
        idx = self->hp + 0xE;
    idx >>= 4;
    idx &= 0xFF;
    table = ((u8**)jet_stingray_patterns)[idx];
    gr = get_random();
    i = 0;
    base = jet_stingray_pattern_weights;
    weights = base + idx * 3;
    rnd = (gr >> 2) & 0xF;
    while (i < 3) {
        if (rnd < weights[i]) {
            self->ext.main_56.pattern = table[i];
            return;
        }
        i++;
    }
}
#endif

void jet_stingray_swim_start(struct MainObj* self)
{
    self->unk6++;
    self->contact_damage = 6;
    self->attack_box = (const u8*)&jet_stingray_swim_attack_box;
    self->hurt_box = (const u8*)&jet_stingray_swim_hurt_box;
    self->air_state = 1;
    self->terrain_box = NULL;
    self->collision_flags = 0;
    self->ext.main_56.flags &= ~2;
    set_animation(self, 1);
}

// jet_stingray_swim_move

extern u8 jet_stingray_splash_x_offsets[4];
extern u8 jet_stingray_splash_y_offsets[4];
extern void (*jet_stingray_ambush_funcs[])(struct MainObj*);
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80070514(struct MainObj* arg0);
void func_80070A38(struct MainObj* arg0);
void func_800710D4(struct MainObj* arg0);
void func_80071740(struct MainObj* arg0);
extern s16 jet_stingray_vortex_debris_offsets[24];
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_56_jet_stingray", func_80070514);
#else
void func_80070514(struct MainObj* arg0)
{
    s16 target_x;
    s16 target_y;
    u8 angle;

    if (arg0->x_pos.val < background_objects[arg0->bg_offset].x_pos.val + 0xA00000) {
        target_x = background_objects[arg0->bg_offset].unk1E + 0x40;
        target_y = background_objects[arg0->bg_offset].unk22 + 0x98;
        arg0->unk15 = PLAYER_FACING_RIGHT;
    } else {
        target_x = background_objects[arg0->bg_offset].unk1E + 0x120;
        target_y = background_objects[arg0->bg_offset].unk22 + 0x98;
        arg0->unk15 = 0;
    }
    angle = angle_to_point(OBJECT_HEADER(arg0), target_x << 16, target_y << 16);
    set_velocity_from_angle(MOVING_OBJECT(arg0), angle);
    arg0->x_speed <<= 1;
    arg0->y_speed <<= 1;
    if (jet_stingray_at_target(arg0, target_x, target_y) & 0xFF) {
        arg0->x_speed = 0;
        arg0->y_speed = 0;
        arg0->unk6++;
        arg0->unk7C = 0;
    }
}
#endif

void jet_stingray_swim_next(struct MainObj* self)
{
    if (self->unk7C == 0) {
        if (self->ext.main_56.pattern == NULL) {
            jet_stingray_choose_pattern(self);
        } else if (*self->ext.main_56.pattern == 0xFF) {
            jet_stingray_choose_pattern(self);
        }
        self->unk5 = (*self->ext.main_56.pattern);
        self->unk6 = 0;
        self->unk7 = 0;
        self->ext.main_56.pattern++;
    } else {
        self->unk7C--;
    }
}

void jet_stingray_swim(struct MainObj* self)
{
    jet_stingray_swim_funcs[self->unk6](self);
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (((jet_stingray_check_surface(PLAYER_OBJECT(self), 0, 0) & 0xFF) == 3) && !(self->ext.main_56.flags & 2)) {
        jet_stingray_spawn_splash(self);
        self->ext.main_56.flags |= 2;
    }
}

void jet_stingray_land(struct MainObj* self)
{
    switch (self->unk6) {
    case 0:
        self->air_state = -1;
        self->terrain_box = &jet_stingray_terrain_box;
        self->x_speed = 0;
        self->y_speed = -FIXED(2);
        self->ext.main_56.flags &= 2;
        /* fall through */
    case 1:
        if (self->collision_flags & 8) {
            self->unk6 = (u8)self->unk6 + 1;
            self->air_state = 0;
            self->y_speed = 0;
            set_animation(self, 0);
            self->unk7C = 0x28;
            self->attack_box = &jet_stingray_land_attack_box;
            self->hurt_box = &jet_stingray_land_hurt_box;
        }
        break;
    case 2:
        if (--self->unk7C == 0) {
            self->unk5 = 4;
            self->unk6 = 0;
        }
        break;
    }

    CollisionRelated(PLAYER_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if ((jet_stingray_check_surface(PLAYER_OBJECT(self), 0, 0) & 0xFF) == 3
        && !(self->ext.main_56.flags & 2)) {
        jet_stingray_spawn_splash(self);
        self->ext.main_56.flags |= 2;
    }
}

void jet_stingray_vortex_start(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->unk7++;
        self->ext.main_56.vortex_result = 0;
        set_animation(self, 2);
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7 = 0;
        self->unk7C = 0x14;
        self->unk6++;
    }
}

void jet_stingray_vortex_spawn(struct MainObj* self)
{
    struct VisualObj* visual_obj;

    if (--self->unk7C == 0) {
        self->unk6++;
        set_animation(self, 3);
        self->unk7C = 0xF0;
        visual_obj = find_free_visual_obj();
        if (visual_obj != NULL) {
            visual_obj->active = 0x41;
            visual_obj->id = 0x17;
            visual_obj->unk40 = self->unk40;
            visual_obj->animation_table = (u32**)self->animation_table;
            visual_obj->unk3C = (void*)self->sprite_frames;
            visual_obj->unk42 = self->unk42;
            visual_obj->unk15 = self->unk15;
            visual_obj->bg_offset = self->bg_offset;
            visual_obj->x_pos.val = self->x_pos.val;
            visual_obj->y_pos.val = self->y_pos.val;
            visual_obj->unk50 = PLAYER_OBJECT(self);
            visual_obj->unk2 = 0;
            self->ext.main_56.object.visual = visual_obj;
        }
        func_8001540C(2, SATURN_SOUND(0xB0, 0x1B), self);
    }
}

// jet_stingray_vortex_spin
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80070A38(struct MainObj* arg0)
{
    struct MainObj* debris;
    s16 dx;
    s16 dy;
    u32 roll;

    if (g_Player.x_pos.i.hi < arg0->x_pos.i.hi)
        g_Player.x_pos.i.hi += 3;
    else
        g_Player.x_pos.i.hi -= 3;
    if (arg0->y_pos.i.hi < g_Player.y_pos.i.hi)
        g_Player.y_pos.i.hi -= 1;
    else
        g_Player.y_pos.i.hi += 1;
    g_Player.y_pos.i.hi += 1;
    dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if ((dy < 0 ? -dy : dy) < 0x30 && (dx < 0 ? -dx : dx) < 0x20) {
        arg0->ext.main_56.vortex_result = 2;
        arg0->unk6++;
        return;
    }
    if (--arg0->unk7C == 0) {
        arg0->ext.main_56.vortex_result = 1;
        arg0->unk6++;
    }
    if (WEAPON_FRAME_COUNTER % 5 != 0)
        return;
    debris = func_8006FB20(arg0, 0, 0);
    roll = get_random();
    if (debris != NULL)
        debris->x_pos.i.hi = background_objects[0].unk1E + ((u16*)jet_stingray_vortex_debris_offsets)[(arg0->unk15 != 0 ? 8 : 0) + (roll & 7)];
    roll = get_random();
    if (debris == NULL)
        return;
    debris->y_pos.i.hi = background_objects[0].unk22 + ((u16*)jet_stingray_vortex_debris_offsets)[0x10 + (roll & 7)];
    debris->x_speed = arg0->unk15 != 0 ? -0x38000 : 0x38000;
    debris->y_speed = arg0->y_pos.i.hi < debris->y_pos.i.hi ? 0x10000 : -0x10000;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_56_jet_stingray", func_80070A38);
#endif

void jet_stingray_vortex_wait(struct MainObj* self)
{
    if (self->ext.main_56.object.effect->active == 0) {
        self->unk5 = 6;
        self->unk6 = 0;
    }
}

void jet_stingray_vortex_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void jet_stingray_vortex(struct MainObj* self)
{
    jet_stingray_vortex_funcs[self->unk6](self);
    animate_object(ANIMATED_OBJECT(self));
}

void jet_stingray_ambush_exit(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->ext.main_56.flags &= 0xFC;
        self->contact_damage = 9;
        self->attack_box = &jet_stingray_ambush_attack_box;
        self->hurt_box = &jet_stingray_ambush_hurt_box;
        self->unk7++;
        self->y_speed = FIXED(9);
        self->x_speed = 0;
        set_animation(self, 7);
        func_8001540C(2, SATURN_SOUND(0xAF, 0x1A), self);
    }

    if (self->on_screen == 0) {
        self->unk7 = 0;
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void jet_stingray_ambush_drop(struct MainObj* self)
{
    switch (self->unk7) {
    case 0:
        if (--self->unk7C != 0)
            break;
        self->unk7++;
        self->x_pos = g_Player.x_pos;
        self->y_speed = 0xFFF70000;
        self->attack_box = &jet_stingray_ambush_drop_attack_box;
        self->ext.main_56.flags &= 0xFE;
        set_animation(self, 8);
        break;
    case 1:
        if (self->on_screen == 0)
            break;
        self->unk7++;
        func_8001540C(2, SATURN_SOUND(0xAF, 0x1A), self);
        break;
    case 2:
        if (self->on_screen != 0)
            break;
        self->unk7 = 0;
        self->unk7C = 0x28;
        self->unk6++;
        break;
    }
}

void jet_stingray_ambush_rise(struct MainObj* self)
{
    switch (self->unk7) {
    case 0:
        if (--self->unk7C == 0) {
            self->unk7++;
            self->x_pos.val = g_Player.x_pos.val;
            self->y_pos.val = (background_objects[0].unk20 + 0x140) << 0x10;
            self->y_speed = 0x90000;
            self->attack_box = &jet_stingray_ambush_attack_box;
            self->ext.main_56.flags &= 0xFE;
            set_animation(self, 7);
        }
        break;
    case 1:
        if (self->on_screen != 0) {
            self->unk7++;
            func_8001540C(2, SATURN_SOUND(0xAF, 0x1A), self);
        }
        break;
    case 2:
        if (self->on_screen == 0) {
            self->unk7 = 0;
            self->unk7C = 0x5A;
            self->unk6++;
        }
        break;
    }
}

void jet_stingray_ambush_return(struct MainObj* self)
{

    if (--self->unk7C != 0) {
        return;
    }
    self->unk5 = 2;
    self->unk6 = 0;
    self->unk7 = 0;
    if (self->x_pos.i.hi < background_objects[self->bg_offset].x_pos.i.hi + 0xA0) {
        self->x_pos.i.hi = background_objects[self->bg_offset].unk1E + 0x40;
    } else {
        self->x_pos.i.hi = background_objects[self->bg_offset].unk1E + 0x120;
    }
    self->y_pos.i.hi = background_objects[self->bg_offset].y_pos.u.hi - 0x50;
}

// jet_stingray_ambush
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_56_jet_stingray", func_800710D4);
#else
void func_800710D4(struct MainObj* arg0)
{
    struct MainObj* debris;
    u8 tile;
    s8 i;

    jet_stingray_ambush_funcs[arg0->unk6](arg0);
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    tile = jet_stingray_check_surface(PLAYER_OBJECT(arg0), 0, 0);
    if (tile == 0)
        return;
    switch (tile) {
    case 1:
    case 2:
        if (!(arg0->ext.main_56.flags & 1)) {
            for (i = 0; i < 4; i++) {
                debris = func_8006FB20(arg0, ((s8*)jet_stingray_splash_x_offsets)[get_random() & 3], 0);
#ifdef MMX4_PC
                if (debris == NULL) {
                    get_random();
                    continue;
                }
#endif
                debris->y_pos.i.hi = ((s8*)jet_stingray_splash_y_offsets)[get_random() & 3] + 0x13B;
            }
            arg0->ext.main_56.flags |= 1;
        }
        break;
    case 3:
        if (!(arg0->ext.main_56.flags & 2)) {
            jet_stingray_spawn_splash(arg0);
            arg0->ext.main_56.flags |= 2;
        }
        break;
    }
}
#endif

void jet_stingray_dash_start(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->unk7++;
        self->contact_damage = 9;
        self->terrain_box = NULL;
        self->x_speed = 0;
        self->y_speed = 0;
        set_animation(self, 5);
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7 = 0;
        self->unk7C = 0x14;
        self->unk6++;
    }
}

void jet_stingray_dash_charge(struct MainObj* self)
{
    s16 timer;
    s32 x_velocity;

    if (self->unk7 == 0) {
        timer = --self->unk7C;
        x_velocity = FIXED(-6);
        if (timer == 0) {
            self->unk7 = (u8)self->unk7 + 1;
            if (self->unk15 != 0) {
                x_velocity = FIXED(6);
            }
            self->attack_box = &jet_stingray_dash_attack_box;
            self->x_speed = x_velocity;
            self->hurt_box = &jet_stingray_dash_hurt_box;
            set_animation(self, 6);
            func_8001540C(2, SATURN_SOUND(0xAF, 0x1A), self);
        }
    } else if (self->on_screen == 0) {
        self->unk7 = 0;
        self->unk7C = 0x78;
        self->x_speed = 0;
        self->unk6 = (u8)self->unk6 + 1;
        self->y_pos.i.hi = background_objects[self->bg_offset].unk22 - 0x50;
    }
}

void jet_stingray_dash_return(struct MainObj* self)
{

    if (--self->unk7C != 0) {
        return;
    }
    self->unk5 = 2;
    self->unk6 = 0;

    if (self->x_pos.i.hi < background_objects[self->bg_offset].x_pos.i.hi) {
        self->x_pos.i.hi = background_objects[self->bg_offset].unk1E + 0x40;
    } else {
        self->x_pos.i.hi = background_objects[self->bg_offset].unk1E + 0x120;
    }

    self->y_pos.i.hi = background_objects[self->bg_offset].y_pos.u.hi - 0x50;
}

void jet_stingray_dash(struct MainObj* self)
{
    jet_stingray_dash_funcs[self->unk6](self);
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void jet_stingray_apply_leap(struct MainObj* self)
{
    self->x_pos.val += self->x_speed;
    self->y_pos.val -= self->y_speed;
    self->y_speed -= self->gravity;
}

void jet_stingray_leap_start(struct MainObj* self)
{
    s32 value = -0x50000;

    self->contact_damage = 7;
    self->attack_box = &jet_stingray_leap_attack_box;
    self->hurt_box = &jet_stingray_leap_hurt_boxes;
    self->unk6++;

    if (self->unk15 != 0) {
        value = 0x50000;
    }

    self->x_speed = value;
    self->x_accel = 0;
    self->y_speed = FIXED(-9.5);
    self->gravity = FIXED(-0.2578125);
    self->ext.main_56.flags &= 0xFD;

    set_animation(self, 4);
    func_8001540C(2, SATURN_SOUND(0xAF, 0x1A), self);
}

void jet_stingray_leap_fall(struct MainObj* self)
{
    if (self->y_speed > 0) {
        self->unk6++;
        self->ext.main_56.flags &= ~2;
        self->y_speed = 0;
        self->gravity = -FIXED(0.8125);
    }
}

void jet_stingray_leap_return(struct MainObj* entity)
{
    if (entity->on_screen == 0) {
        entity->unk5 = 2;
        entity->unk6 = 0;

        if (entity->x_pos.i.hi < background_objects[entity->bg_offset].x_pos.i.hi) {
            entity->x_pos.i.hi = background_objects[entity->bg_offset].unk1E + 0x40;
        } else {
            entity->x_pos.i.hi = background_objects[entity->bg_offset].unk1E + 0x120;
        }

        entity->y_pos.i.hi = background_objects[entity->bg_offset].y_pos.i.hi - 0x50;
    }
}

void jet_stingray_leap(struct MainObj* self)
{
    jet_stingray_leap_funcs[self->unk6](self);
    animate_object(ANIMATED_OBJECT(self));
    jet_stingray_apply_leap(self);

    if (((jet_stingray_check_surface(PLAYER_OBJECT(self), (self->unk15 != 0 ? 0x30 : -0x30), 0)) & 0xFF) == 3) {
        if (!(self->ext.main_56.flags & 2)) {
            jet_stingray_spawn_splash(self);
            self->ext.main_56.flags |= 2;
        }
    }
}

// jet_stingray_missiles_fire
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_56_jet_stingray", func_80071740);
#else
void func_80071740(struct MainObj* arg0)
{
    struct ShotObj* shot;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7++;
        func_8001540C(2, SATURN_SOUND(0xB2, 0x1D), arg0);
        arg0->unk7C = 0x32;
    case 1:
        if (--arg0->unk7C == 0) {
            if (arg0->unk5 == 9)
                arg0->unk7E = 4;
            else
                arg0->unk7E = 3;
            arg0->unk7++;
            set_animation(arg0, 9);
        }
        break;
    case 2:
        if (arg0->animation_step.fields.event == 1) {
            func_8001540C(2, SATURN_SOUND(0xB1, 0x1C), arg0);
            arg0->animation_step.fields.event = 0;
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x22;
                if (arg0->unk5 == 9)
                    shot->unk2 = 3;
                else
                    shot->unk2 = 2;
                shot->unk40 = arg0->unk40;
                shot->animation_table = (u32**)arg0->animation_table;
                shot->unk3C = (void*)arg0->sprite_frames;
                shot->unk42 = arg0->unk42;
                shot->bg_offset = arg0->bg_offset;
                shot->x_pos.val = arg0->x_pos.val;
                shot->y_pos.val = arg0->y_pos.val;
                shot->unk15 = arg0->unk15;
                shot->unk7C = (struct WeaponObj*)arg0;
            }
        }
        if (arg0->animation_step.fields.event == 2) {
            arg0->animation_step.fields.event = 0;
            arg0->unk7C = 0x14;
            arg0->unk6++;
        }
        break;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}
#endif

void jet_stingray_missiles_repeat(struct MainObj* self)
{
    if (self->unk7C == 0) {
        if (self->unk7E != 0) {
            self->unk6--;
            self->unk7E--;
        } else {
            self->unk6++;
            self->unk7 = 0;
            set_animation(self, 0xA);
        }
    } else {
        self->unk7C--;
    }
}

void jet_stingray_missiles_finish(struct MainObj* self)
{
    if (self->unk7 == 0 && self->animation_step.fields.relative_step == 0) {
        self->unk7++;
        self->unk7C = 0x28;
        set_animation_frame(ANIMATED_OBJECT(self), 1, 2);
    }
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void jet_stingray_missiles(struct MainObj* self)
{
    jet_stingray_missiles_funcs[self->unk6](self);
}

void jet_stingray_missiles_wide(struct MainObj* self)
{
    jet_stingray_missiles_wide_funcs[self->unk6](self);
}

void jet_stingray_stagger_start(struct MainObj* self)
{
    self->collision_data = (const u16*)D_801060F0;
    self->unk42 &= 0x7FFF;
    self->unk6++;
    func_8001540C(2, SATURN_SOUND(0xB3, 0x1E), self);
    set_animation(self, 0x16);
}

void jet_stingray_stagger_wait(struct MainObj* self)
{
    if (self->unk7 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk7++;
            self->unk7C = 0x78;
        }
    } else if (--self->unk7C == 0) {
        self->unk7 = 0;
        self->unk7C = 0xA;
        self->unk6++;
        self->ext.main_56.unk89.value = 5;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void jet_stingray_stagger_shake(struct MainObj* self)
{
    s16 timer;
    s8 step;

    timer = --self->unk7C;
    if (timer != 0) {
        step = self->ext.main_56.unk89.value;
        self->x_pos.i.hi = self->x_pos.u.hi + step;
        self->ext.main_56.unk89.signed_value *= -1;
        return;
    }

    self->unk6++;
    set_animation(self, 0x17);
    func_8001540C(2, SATURN_SOUND(0xCA, 0x17), self);
    spawn_debris(6, jet_stingray_debris, self);
}

void jet_stingray_stagger_flee(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        self->y_speed = FIXED(8);
        self->x_speed = 0;
        set_animation(self, 7);
        func_8001540C(2, SATURN_SOUND(0xAF, 0x1A), self);
    }
}

void jet_stingray_stagger_return(struct MainObj* self)
{
    if (self->on_screen == 0) {
        self->state = 1;
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
        self->collision_data = (const u16*)D_801079F8;
    }
    move_object(MOVING_OBJECT(self));
}

void jet_stingray_stagger(struct MainObj* self)
{
    func_8002DD04(self);
    jet_stingray_stagger_funcs[self->unk6](self);
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x80, 0x80);
}

void jet_stingray_reset(struct MainObj* self)
{
    self->unk5 = 2;
    self->unk6 = 0;
    self->unk7 = 0;
}

// jet_stingray_main
void func_80071D30(struct MainObj* self)
{
    s32 check;

    check = func_8002DD04(self);

    if (self->ext.main_56.flash_timer != 0) {
        if (--self->ext.main_56.flash_timer & 1) {
            self->unk42 |= 0x8000;
        } else {
            self->unk42 &= 0x7FFF;
        }
    } else {
        self->collision_data = D_801079F8;
    }

    if (check < 0) {
        self->unk5 = 0;
        self->state++;
        self->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        return;
    }

    if (check != 0) {
        if (engine_obj.cur_character == CHARACTER_X) {
            switch (check) {
            case 0xC:
            case 3:
                self->state = 3;
                self->unk6 = 0;
                self->unk7 = 0;
                return;
            default:
                if (self->ext.main_56.flash_timer == 0) {
                    self->collision_data = D_801060F0;
                    self->ext.main_56.flash_timer = 0x40;
                }
                break;
            case 0x7F:
                break;
            }
        } else {
            switch (check) {
            case 0x7F:
            case 0x19:
            case 0x1A:
                break;
            case 0x22:
                self->state = 3;
                self->unk6 = 0;
                self->unk7 = 0;
                return;
            default:
                if (self->ext.main_56.flash_timer == 0) {
                    self->collision_data = D_801060F0;
                    self->ext.main_56.flash_timer = 0x40;
                }
                break;
            }
        }
    }

    jet_stingray_step_funcs[self->unk5](self);
    update_on_screen(BASE_OBJECT(self), 0x80, 0x80);
    func_8002D9BC(self);
}

void jet_stingray_death_start(struct MainObj* self)
{
    player_start_script_action(0x14, g_Player.unk15);
    self->unk5++;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_56.unk89.value = 0x19;
    set_animation_frame(ANIMATED_OBJECT(self), 0x16, 0);
    is_on_screen(BASE_OBJECT(self));
}

void jet_stingray_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 var_a0;
    s16 next_unk7e;

    if (--self->unk7C == 0) {
        self->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_56.object.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        self->ext.main_56.unk89.value -= 5;
        var_a0 = self->ext.main_56.unk89.value;
        next_unk7e = var_a0 > 5 ? var_a0 : 5;
        self->unk7E = next_unk7e;
    }
}

void jet_stingray_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_56.object.effect;
    self->on_screen = 0;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        if (engine_obj.stage != 0xC) {
            engine_obj.unkF = 0x10;
        } else {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        }
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
}

void jet_stingray_death(struct MainObj* self)
{
    jet_stingray_death_funcs[self->unk5](self);
}

void jet_stingray_update(struct MainObj* self)
{
    jet_stingray_state_funcs[self->state](self);
}

struct Unk_unk68 jet_stingray_swim_attack_box = { -17, -22, 25, 47 };

struct Unk_unk68 jet_stingray_swim_hurt_box = { -20, -32, 40, 75 };

struct Unk_unk68 jet_stingray_land_attack_box = { -17, -22, 25, 47 };

struct Unk_unk68 jet_stingray_land_hurt_box = { -29, -32, 49, 59 };

struct Unk_unk68 jet_stingray_dash_attack_box = { -18, -10, 37, 18 };

struct Unk_unk68 jet_stingray_dash_hurt_box = { -30, -14, 75, 25 };

struct Unk_unk68 jet_stingray_ambush_attack_box = { -10, -23, 19, 59 };

struct Unk_unk68 jet_stingray_ambush_hurt_box = { -19, -40, 37, 80 };

struct Unk_unk68 jet_stingray_ambush_drop_attack_box = { -10, -39, 19, 59 };

struct Unk_unk68 jet_stingray_leap_attack_box = { -19, -8, 54, 12 };

struct Unk_unk68 jet_stingray_leap_hurt_boxes[6] = {
    { -28, -12, 63, 24 },
    { -20, -19, 44, 47 },
    { -10, -19, 29, 47 },
    { -26, -11, 69, 20 },
    { -30, -35, 59, 73 },
    { -36, -15, 91, 25 },
};

struct Unk_unk68 jet_stingray_terrain_box = { 0, 28, 27, 3 };

union AnimationStep jet_stingray_pattern_2_0[] = {
    { 7, -1, 0, 0x00 },
};

u8 jet_stingray_pattern_2_1[4] = { 8, 7, 255, 0 };

union AnimationStep jet_stingray_pattern_1_0[] = {
    { 7, -1, 0, 0x00 },
};

u8 jet_stingray_pattern_1_1[4] = { 8, 7, 255, 0 };

u8 jet_stingray_pattern_1_2[4] = { 8, 3, 255, 0 };

u8 jet_stingray_pattern_0_0[4] = { 9, 7, 255, 0 };

u8 jet_stingray_pattern_0_1[4] = { 9, 3, 255, 0 };

u8 jet_stingray_pattern_0_2[4] = { 9, 5, 255, 0 };

void* jet_stingray_pattern_2[2] = {
    jet_stingray_pattern_2_0,
    jet_stingray_pattern_2_1,
};

void* jet_stingray_pattern_1[3] = {
    jet_stingray_pattern_1_0,
    jet_stingray_pattern_1_1,
    jet_stingray_pattern_1_2,
};

u8* jet_stingray_pattern_0[3] = {
    jet_stingray_pattern_0_0,
    jet_stingray_pattern_0_1,
    jet_stingray_pattern_0_2,
};

void* jet_stingray_patterns[3] = {
    jet_stingray_pattern_0,
    jet_stingray_pattern_1,
    jet_stingray_pattern_2,
};

u8 jet_stingray_pattern_weights[12] = { 0x02, 0x08, 0x10, 0x03, 0x06, 0x10, 0x06, 0x10, 0x10, 0x00, 0x00, 0x00 };

struct Unk_unk68 jet_stingray_anim_0[4] = {
    { 9, 0, 1, 0 },
    { 11, 0, 1, 1 },
    { 7, 0, 1, 2 },
    { 7, 0, -3, 3 },
};

struct Unk_unk68 jet_stingray_anim_1[4] = {
    { 9, 0, 1, 4 },
    { 11, 0, 1, 5 },
    { 7, 0, 1, 6 },
    { 7, 0, -3, 7 },
};

union AnimationStep jet_stingray_anim_2[] = {
    { 8, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 10, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 5, 0, 1, 0x0D },
    { 7, 0, 0, 0x0E },
};

struct Unk_unk68 jet_stingray_anim_3[3] = {
    { 2, 0, 1, 15 },
    { 2, 0, 1, 16 },
    { 2, 0, -2, 14 },
};

struct Unk_unk68 jet_stingray_anim_4[16] = {
    { 5, 0, 1, 17 },
    { 5, 0, 1, 18 },
    { 5, 0, 1, 19 },
    { 5, 0, 1, 20 },
    { 5, 0, 1, 21 },
    { 6, 0, 1, 22 },
    { 6, 0, 1, 23 },
    { 6, 0, 1, 24 },
    { 6, 0, 1, 21 },
    { 5, 0, 1, 22 },
    { 5, 0, 1, 19 },
    { 5, 0, 1, 20 },
    { 5, 0, 1, 17 },
    { 6, 0, 1, 18 },
    { 6, 0, 1, 25 },
    { 6, 0, -15, 26 },
};

union AnimationStep jet_stingray_anim_5[] = {
    { 6, 0, 1, 0x02 },
    { 10, 0, 1, 0x1B },
    { 3, 0, 1, 0x1C },
    { 5, 0, 0, 0x1D },
};

struct Unk_unk68 jet_stingray_anim_6[4] = {
    { 2, 0, 1, 30 },
    { 2, 0, 1, 31 },
    { 2, 0, 1, 32 },
    { 2, 0, -3, 33 },
};

struct Unk_unk68 jet_stingray_anim_7[4] = {
    { 2, 0, 1, 34 },
    { 2, 0, 1, 35 },
    { 2, 0, 1, 36 },
    { 2, 0, -3, 37 },
};

struct Unk_unk68 jet_stingray_anim_8[4] = {
    { 2, 0, 1, 38 },
    { 2, 0, 1, 39 },
    { 2, 0, 1, 40 },
    { 2, 0, -3, 41 },
};

struct Unk_unk68 jet_stingray_anim_9[9] = {
    { 8, 0, 1, 42 },
    { 6, 0, 1, 43 },
    { 2, 0, 1, 44 },
    { 2, 0, 1, 45 },
    { 8, 0, 1, 46 },
    { 2, 1, 1, 47 },
    { 3, 0, 1, 48 },
    { 2, 0, 1, 47 },
    { 6, 2, -3, 46 },
};

union AnimationStep jet_stingray_anim_10[] = {
    { 2, 0, 1, 0x2D },
    { 2, 0, 1, 0x2C },
    { 7, 2, 0, 0x2B },
};

struct Unk_unk68 jet_stingray_anim_11[4] = {
    { 2, 0, 1, 49 },
    { 2, 0, 1, 50 },
    { 2, 0, 1, 51 },
    { 2, 0, -3, 52 },
};

struct Unk_unk68 jet_stingray_anim_12[4] = {
    { 2, 0, 1, 53 },
    { 2, 0, 1, 54 },
    { 2, 0, 1, 55 },
    { 2, 0, -3, 56 },
};

union AnimationStep jet_stingray_anim_13[] = {
    { 2, 0, 1, 0x39 },
    { 2, 0, 0, 0x3A },
};

union AnimationStep jet_stingray_anim_14[] = {
    { 2, 0, 1, 0x3B },
    { 2, 0, 0, 0x3C },
};

struct Unk_unk68 jet_stingray_anim_15[4] = {
    { 2, 0, 1, 61 },
    { 2, 0, 1, 62 },
    { 2, 0, 1, 63 },
    { 2, 0, -3, 64 },
};

struct Unk_unk68 jet_stingray_anim_16[4] = {
    { 2, 0, 1, 65 },
    { 2, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 2, 0, -3, 68 },
};

union AnimationStep jet_stingray_anim_17[] = {
    { 2, 0, 1, 0x45 },
    { 2, 0, 0, 0x46 },
};

union AnimationStep jet_stingray_anim_18[] = {
    { 2, 0, 1, 0x47 },
    { 2, 0, 0, 0x48 },
};

union AnimationStep jet_stingray_anim_19[] = {
    { 4, 0, 1, 0x49 },
    { 4, 0, 1, 0x4A },
    { 4, 0, 1, 0x4B },
    { 4, 0, 1, 0x4C },
    { 3, 0, 1, 0x4D },
    { 3, 0, 1, 0x4E },
    { 4, 0, 1, 0x4F },
    { 3, 0, 0, 0x50 },
};

struct Unk_unk68 jet_stingray_anim_20[4] = {
    { 2, 0, 1, 77 },
    { 2, 0, 1, 78 },
    { 2, 0, 1, 79 },
    { 2, 0, -3, 80 },
};

union AnimationStep jet_stingray_anim_21[] = {
    { 3, 0, 1, 0x4D },
    { 3, 0, 1, 0x4E },
    { 3, 0, 1, 0x4F },
    { 3, 0, 1, 0x50 },
    { 3, 0, 1, 0x4B },
    { 3, 0, 1, 0x4A },
    { 3, 0, 0, 0x49 },
};

union AnimationStep jet_stingray_anim_22[] = {
    { 3, 0, 1, 0x51 },
    { 3, 0, 1, 0x52 },
    { 3, 0, 1, 0x51 },
    { 3, 0, 1, 0x52 },
    { 3, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 0, 0x54 },
};

union AnimationStep jet_stingray_anim_23[] = {
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x56 },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x56 },
    { 15, 0, 0, 0x57 },
};

union AnimationStep jet_stingray_anim_24[] = {
    { 1, 0, 0, 0x58 },
};

union AnimationStep jet_stingray_anim_25[] = {
    { 1, 0, 0, 0x59 },
};

union AnimationStep jet_stingray_anim_26[] = {
    { 1, 0, 0, 0x5A },
};

union AnimationStep jet_stingray_anim_27[] = {
    { 2, 0, 1, 0x5B },
    { 2, 0, 1, 0x5C },
    { 4, 0, 1, 0x5D },
    { 3, 0, 1, 0x5C },
    { 3, 0, 0, 0x5B },
    { 5, 0, 0, 0x5E },
    { 3, 0, 1, 0x5F },
    { 3, 0, 1, 0x60 },
    { 3, 0, 1, 0x61 },
    { 3, 0, 1, 0x62 },
    { 10, 0, 1, 0x63 },
    { 5, 0, 1, 0x15 },
    { 5, 0, 1, 0x16 },
    { 5, 0, 1, 0x13 },
    { 5, 0, 1, 0x14 },
    { 5, 0, 1, 0x5E },
    { 6, 1, 1, 0x64 },
    { 7, 0, 1, 0x65 },
    { 2, 0, 1, 0x5B },
    { 2, 0, 1, 0x5C },
    { 4, 0, 1, 0x5D },
    { 3, 0, 1, 0x5C },
    { 3, 0, 1, 0x5B },
    { 10, 0, 1, 0x66 },
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x56 },
    { 15, 0, 0, 0x57 },
};

union AnimationStep jet_stingray_anim_29[] = {
    { 3, 0, 1, 0x5F },
    { 3, 0, 1, 0x60 },
    { 3, 0, 1, 0x61 },
    { 3, 0, 1, 0x62 },
    { 9, 0, 1, 0x63 },
    { 1, 0, 0, 0x63 },
};

u8 jet_stingray_anim_38[8] = { 5, 0, 1, 21, 5, 0, 255, 22 };

union AnimationStep jet_stingray_anim_39[] = {
    { 5, 0, 1, 0x13 },
    { 5, 0, 1, 0x14 },
    { 5, 0, 1, 0x5E },
    { 6, 1, 1, 0x64 },
    { 7, 0, 1, 0x65 },
    { 2, 0, 1, 0x5B },
    { 2, 0, 1, 0x5C },
    { 4, 0, 1, 0x5D },
    { 3, 0, 1, 0x5C },
    { 3, 0, 1, 0x5B },
    { 10, 0, 1, 0x66 },
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x56 },
    { 15, 0, 0, 0x57 },
};

union AnimationStep jet_stingray_anim_30[] = {
    { 3, 0, 1, 0x67 },
    { 3, 0, 1, 0x68 },
    { 3, 0, 1, 0x69 },
    { 3, 0, 0, 0x6A },
};

struct Unk_unk68 jet_stingray_anim_31[4] = {
    { 8, 0, 1, 107 },
    { 8, 0, 1, 108 },
    { 8, 0, 1, 109 },
    { 8, 0, -3, 108 },
};

union AnimationStep jet_stingray_anim_32[] = {
    { 8, 0, 1, 0x6E },
    { 8, 0, 1, 0x6F },
    { 8, 0, 1, 0x70 },
    { 8, 0, 1, 0x71 },
    { 8, 0, 0, 0x72 },
};

union AnimationStep jet_stingray_anim_33[] = {
    { 2, 0, 1, 0x73 },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x75 },
    { 2, 0, 0, 0x76 },
};

struct Unk_unk68 jet_stingray_anim_34[4] = {
    { 2, 0, 1, 118 },
    { 2, 0, 1, 119 },
    { 2, 0, 1, 120 },
    { 2, 0, -3, 121 },
};

union AnimationStep jet_stingray_anim_35[] = {
    { 3, 0, 1, 0x5F },
    { 3, 0, 1, 0x60 },
    { 3, 0, 1, 0x61 },
    { 3, 0, 1, 0x62 },
    { 3, 0, 1, 0x63 },
    { 5, 0, 1, 0x15 },
    { 5, 0, 1, 0x16 },
    { 5, 0, 1, 0x13 },
    { 5, 0, 1, 0x14 },
    { 5, 0, 1, 0x11 },
    { 5, 0, 1, 0x12 },
    { 5, 0, 1, 0x19 },
    { 5, 0, 0, 0x1A },
};

struct Unk_unk68 jet_stingray_anim_36[6] = {
    { 2, 0, 1, 123 },
    { 2, 0, 1, 124 },
    { 2, 0, 1, 125 },
    { 2, 0, 1, 126 },
    { 2, 0, 1, 125 },
    { 2, 0, -5, 124 },
};

union AnimationStep jet_stingray_anim_37[] = {
    { 2, 0, 1, 0x7F },
    { 2, 0, 1, 0x80 },
    { 2, 0, 1, 0x81 },
    { 2, 0, 1, 0x82 },
    { 2, 0, 1, 0x81 },
    { 2, 0, -5, 0x80 },
};

union AnimationStep jet_stingray_anim_40[] = {
    { 1, 0, 0, 0x83 },
};

union AnimationStep jet_stingray_anim_41[] = {
    { 1, 0, 0, 0x85 },
};

union AnimationStep jet_stingray_anim_42[] = {
    { 1, 0, 0, 0x84 },
};

union AnimationStep jet_stingray_anim_43[] = {
    { 3, 0, 1, 0x86 },
    { 3, 0, 1, 0x87 },
    { 4, 0, 1, 0x88 },
    { 4, 0, 1, 0x89 },
    { 4, 0, 1, 0x8A },
    { 3, 0, 1, 0x8B },
    { 3, 0, 1, 0x8C },
    { 3, 0, 1, 0x8D },
    { 3, 0, 0, 0x8E },
};

struct Unk_unk68 jet_stingray_anim_44[3] = {
    { 4, 0, 1, -113 },
    { 4, 0, 1, -112 },
    { 4, 0, -2, -111 },
};

void* jet_stingray_animations[45] = {
    jet_stingray_anim_0,
    jet_stingray_anim_1,
    jet_stingray_anim_2,
    jet_stingray_anim_3,
    jet_stingray_anim_4,
    jet_stingray_anim_5,
    jet_stingray_anim_6,
    jet_stingray_anim_7,
    jet_stingray_anim_8,
    jet_stingray_anim_9,
    jet_stingray_anim_10,
    jet_stingray_anim_11,
    jet_stingray_anim_12,
    jet_stingray_anim_13,
    jet_stingray_anim_14,
    jet_stingray_anim_15,
    jet_stingray_anim_16,
    jet_stingray_anim_17,
    jet_stingray_anim_18,
    jet_stingray_anim_19,
    jet_stingray_anim_20,
    jet_stingray_anim_21,
    jet_stingray_anim_22,
    jet_stingray_anim_23,
    jet_stingray_anim_24,
    jet_stingray_anim_25,
    jet_stingray_anim_26,
    jet_stingray_anim_27,
    &jet_stingray_anim_27[5],
    jet_stingray_anim_29,
    jet_stingray_anim_30,
    jet_stingray_anim_31,
    jet_stingray_anim_32,
    jet_stingray_anim_33,
    jet_stingray_anim_34,
    jet_stingray_anim_35,
    jet_stingray_anim_36,
    jet_stingray_anim_37,
    jet_stingray_anim_38,
    jet_stingray_anim_39,
    jet_stingray_anim_40,
    jet_stingray_anim_41,
    jet_stingray_anim_42,
    jet_stingray_anim_43,
    jet_stingray_anim_44,
};

struct Unk_unk68 jet_stingray_debris[2] = {
    { 24, 25, 26, 24 },
    { 25, 26, 0, 0 },
};

s8 jet_stingray_bubble_offsets[4] = { 0xE0, 0x00, 0x20, 0x00 };

void (*jet_stingray_intro_funcs[7])(struct MainObj*) = {
    jet_stingray_intro_setup,
    jet_stingray_intro_warning,
    jet_stingray_intro_emerge,
    jet_stingray_intro_rise,
    jet_stingray_intro_pose,
    jet_stingray_intro_fill_health,
    jet_stingray_intro_finish,
};

void (*jet_stingray_swim_funcs[3])(struct MainObj*) = {
    jet_stingray_swim_start,
    func_80070514,
    jet_stingray_swim_next,
};

s16 jet_stingray_vortex_debris_offsets[24] = {
    (s16)0x0008,
    (s16)0x003C,
    (s16)0x0078,
    (s16)0x00A8,
    (s16)0x006C,
    (s16)0x004C,
    (s16)0x00C0,
    (s16)0x0094,
    (s16)0x0173,
    (s16)0x012B,
    (s16)0x00EF,
    (s16)0x00F3,
    (s16)0x00BF,
    (s16)0x0147,
    (s16)0x00C7,
    (s16)0x009F,
    (s16)0x011F,
    (s16)0x013F,
    (s16)0x0133,
    (s16)0x0103,
    (s16)0x00FF,
    (s16)0x0113,
    (s16)0x0143,
    (s16)0x00F3,
};

void (*jet_stingray_vortex_funcs[])(struct MainObj*) = {
    jet_stingray_vortex_start,
    jet_stingray_vortex_spawn,
    func_80070A38,
    jet_stingray_vortex_wait,
    jet_stingray_vortex_finish,
#ifdef MMX4_WIN32
    NULL,
#endif
};

u8 jet_stingray_splash_x_offsets[4] = { 0x15, 0xEB, 0xF0, 0x23 };

u8 jet_stingray_splash_y_offsets[4] = { 0xED, 0x02, 0xE7, 0x0D };

void (*jet_stingray_ambush_funcs[4])() = {
    jet_stingray_ambush_exit,
    jet_stingray_ambush_drop,
    jet_stingray_ambush_rise,
    jet_stingray_ambush_return,
};

void (*jet_stingray_dash_funcs[3])(struct MainObj*) = {
    jet_stingray_dash_start,
    jet_stingray_dash_charge,
    jet_stingray_dash_return,
};

void (*jet_stingray_leap_funcs[3])(struct MainObj*) = {
    jet_stingray_leap_start,
    jet_stingray_leap_fall,
    jet_stingray_leap_return,
};

void (*jet_stingray_missiles_funcs[3])(struct MainObj*) = {
    func_80071740,
    jet_stingray_missiles_repeat,
    jet_stingray_missiles_finish,
};

void (*jet_stingray_missiles_wide_funcs[3])(struct MainObj*) = {
    func_80071740,
    jet_stingray_missiles_repeat,
    jet_stingray_missiles_finish,
};

void (*jet_stingray_stagger_funcs[5])(struct MainObj*) = {
    jet_stingray_stagger_start,
    jet_stingray_stagger_wait,
    jet_stingray_stagger_shake,
    jet_stingray_stagger_flee,
    jet_stingray_stagger_return,
};

void (*jet_stingray_step_funcs[10])() = {
    enemy_hit_reaction,
    jet_stingray_reset,
    jet_stingray_swim,
    jet_stingray_land,
    jet_stingray_vortex,
    func_800710D4,
    jet_stingray_dash,
    jet_stingray_leap,
    jet_stingray_missiles,
    jet_stingray_missiles_wide,
};

void (*jet_stingray_death_funcs[3])(struct MainObj*) = {
    jet_stingray_death_start,
    jet_stingray_death_explode,
    jet_stingray_death_finish,
};

void (*jet_stingray_state_funcs[4])(struct MainObj*) = {
    jet_stingray_intro,
    func_80071D30,
    jet_stingray_death,
    jet_stingray_stagger,
};
