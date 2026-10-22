// MainObj, main_object_update_funcs[54]
// 8006BB00..8006EB40
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_54_slash_beast.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/1CF60.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/collision.h"
#include "main/stage_objects.h"
#include "main/collision_bounds.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/collision_bounds.h"
#endif

extern struct Unk_unk68 D_80100200;
extern struct Unk_unk68 D_80100204;
extern struct Unk_unk68 D_80100210;
extern struct Unk_unk68 D_80100214;

extern u8 D_801005B0[4];

extern u8** slash_beast_patterns[3];
extern u8 slash_beast_pattern_weights[12];

extern struct Unk_unk68 D_80100220;
extern struct Unk_unk68 D_80100224;

// slash_beast_state_funcs
extern void (*slash_beast_state_funcs[])(struct MainObj*);

void slash_beast_death(struct MainObj*);

void slash_beast_start_pattern(struct MainObj*);
void slash_beast_crescent(struct MainObj*);
void slash_beast_decide(struct MainObj*);
void slash_beast_jump(struct MainObj*);

void slash_beast_dash(struct MainObj*);

void slash_beast_grab(struct MainObj*);
void slash_beast_intro(struct MainObj*);
void slash_beast_stagger(struct MainObj*);
void slash_beast_high_leap(struct MainObj*);

// slash_beast_death_funcs
extern void (*slash_beast_death_funcs[])(struct MainObj*);
void slash_beast_death_start(struct MainObj*);

void slash_beast_death_finish(struct MainObj*);

// slash_beast_crescent_funcs
extern void (*slash_beast_crescent_funcs[])(struct MainObj*);
void slash_beast_crescent_jump(struct MainObj*);

void slash_beast_crescent_land(struct MainObj*);
void slash_beast_crescent_recover(struct MainObj*);

// slash_beast_decide_funcs
extern void (*slash_beast_decide_funcs[])(struct MainObj*);

void slash_beast_crouch(struct MainObj*);

// slash_beast_jump_funcs
extern void (*slash_beast_jump_funcs[])(struct MainObj*);

void slash_beast_jump_recover(struct MainObj*);

// slash_beast_dash_funcs
extern void (*slash_beast_dash_funcs[])(struct MainObj*);
void slash_beast_dash_windup(struct MainObj*);
void slash_beast_dash_start(struct MainObj*);
void func_8006CFB8(struct MainObj*);

void slash_beast_dash_turn(struct MainObj*);

// slash_beast_grab_funcs
extern void (*slash_beast_grab_funcs[])(struct MainObj*);
void slash_beast_grab_check(struct MainObj*);
void slash_beast_grab_windup(struct MainObj*);
void func_8006D888(struct MainObj*);
void slash_beast_grab_throw(struct MainObj*);

// slash_beast_intro_funcs
extern void (*slash_beast_intro_funcs[])(struct MainObj*);

void slash_beast_intro_leap(struct MainObj*);
void slash_beast_intro_land(struct MainObj*);
void slash_beast_intro_pose(struct MainObj*);
void slash_beast_intro_wait_dialogue(struct MainObj*);
void slash_beast_intro_fill_health(struct MainObj*);

// slash_beast_stagger_funcs
extern void (*slash_beast_stagger_funcs[])(struct MainObj*);

void slash_beast_stagger_land(struct MainObj*);
void slash_beast_stagger_recover(struct MainObj*);

// slash_beast_high_leap_funcs
extern void (*slash_beast_high_leap_funcs[])(struct MainObj*);
void slash_beast_high_leap_jump(struct MainObj*);
void slash_beast_high_leap_fall(struct MainObj*);
void slash_beast_high_leap_land(struct MainObj*);

void slash_beast_high_leap_recover(struct MainObj*);

void slash_beast_update(struct MainObj* self)
{
    slash_beast_state_funcs[self->state](self);
    CollisionRelated(self);
    if (!HP_VALUE(g_Player.hp)) {
        func_8006E920(self, TILE_ATTR_VALUE(0x38));
    }
}

// slash_beast_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006E920(struct MainObj* arg0, s32 value);
void func_8006BB70(struct MainObj* arg0);
void func_8006BD1C(struct MainObj* arg0);
static void main54_spawn_shot(struct MainObj* arg0, s8 subtype);
void func_8006C378(struct MainObj* arg0);
static s32 main54_player_dx(struct MainObj* arg0);
static void main54_face_anim(struct MainObj* arg0, s32 anim);
void func_8006C6AC(struct MainObj* arg0);
void func_8006CB50(struct MainObj* arg0);
void func_8006CC3C(struct MainObj* arg0);
void func_8006CDD4(struct MainObj* arg0);
void func_8006D280(struct MainObj* arg0);
void func_8006D3DC(struct MainObj* arg0);
void func_8006DD44(struct MainObj* arg0);
void func_8006E450(struct MainObj* arg0);
extern char D_801005B4[];
extern u16 D_801005B8[];
extern u16 D_801005C8[];
extern union AnimationStep* slash_beast_animations[];
extern struct Unk_unk68 D_801078F8[];
extern struct Unk_unk68 D_8010020C;
extern struct Unk_unk68 D_80100218;
extern struct Unk_unk68 D_8010021C;
extern struct Unk_unk68 D_8010023C;
extern struct Unk_unk68 D_80100228;
extern struct Unk_unk68 D_8010022C;
extern union AnimationStep D_80100230[];
extern union AnimationStep D_80100234[];
extern union AnimationStep D_80100238[];
extern struct Unk_unk68 D_80100240;
extern struct Unk_unk68 D_80100244;
extern struct Unk_unk68 D_80100248;
#define M54_FLASH(o) ((o)->ext.main_54.flash_timer)
#define M54_81(o) ((o)->ext.main_54.powered_up)
#define M54_82(o) ((o)->ext.main_54.was_hit)
#define M54_84(o) ((o)->ext.main_54.grab)
#define M54_85(o) ((o)->ext.main_54.active)
extern u8 slash_beast_pattern_steps[9][4];
static void main54_spawn_shot(struct MainObj* arg0, s8 subtype)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x1F;
    shot->unk2 = subtype;
    shot->unk40 = arg0->unk40;
    shot->unk42 = arg0->unk42;
    shot->animation_table = (void*)arg0->animation_table;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->y_pos.val = arg0->y_pos.val;
    shot->unk7C = (struct WeaponObj*)arg0;
    shot->state = 0;
    shot->unk15 = arg0->unk15;
}
static s32 main54_player_dx(struct MainObj* arg0)
{
    s32 dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;

    return dx < 0 ? -dx : dx;
}
static void main54_face_anim(struct MainObj* arg0, s32 anim)
{
    slash_beast_face_player(arg0);
    set_animation(arg0, anim);
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006BB70(struct MainObj* arg0)
{
    arg0->contact_damage = 6;
    arg0->hp = 0;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_801078F8;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
    } else {
        arg0->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0x160);
        arg0->unk42 = OBJECT_CLUT(0x7888);
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
        arg0->y_pos.val = background_objects[g_Player.bg_offset].y_pos.val + (s32)0xFFD00000;
    }
    arg0->animation_table = (const u8* const*)slash_beast_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->hurt_box = D_801001FC;
    arg0->attack_box = D_801001F8;
    arg0->unk15 = PLAYER_FACING_RIGHT;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->terrain_box = NULL;
    M54_FLASH(arg0) = 0;
    M54_81(arg0) = 1;
    M54_82(arg0) = 0;
    M54_84(arg0) = 0;
    M54_85(arg0) = 0;
    arg0->ext.main_54.claw_hitbox = 0;
    arg0->ext.main_54.pattern_set = 0;
    arg0->ext.main_54.power_hits = 1;
    arg0->ext.main_54.fight_started = 0;
    arg0->ext.main_54.high_jump = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8006E920(arg0, TILE_ATTR_VALUE(0x38));
    set_animation(arg0, 0);
    arg0->state = 1;
    arg0->unk5 = 9;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006BB70);
#endif

// slash_beast_run
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006BD1C(struct MainObj* arg0)
{
    s32 hit;
    s8 flash;
    const void* saved;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    slash_beast_step_funcs[arg0->unk5](arg0);
    if (arg0->ext.main_54.crash_timer != 0) {
        if (--arg0->ext.main_54.crash_timer == 0)
            func_8006E920(arg0, TILE_ATTR_VALUE(0x38));
    }
    if (engine_obj.stage == 8 && arg0->ext.main_54.pattern_set == 1 && arg0->ext.main_54.fight_started != 0)
        engine_obj.character_state.bytes[1] = 1;
    if (M54_85(arg0) == 0)
        return;
    hit = func_8002DD04(arg0);
    flash = (s8)M54_FLASH(arg0);
    M54_82(arg0) = 0;
    if (flash == 0) {
        if (hit < 0) {
            func_8006E920(arg0, TILE_ATTR_VALUE(0x38));
            g_Player.spike_immune = 1;
            arg0->state = 2;
            arg0->unk5 = 0;
            return;
        }
        if (hit != 0 && hit != 0x7F) {
            M54_82(arg0) = 1;
            arg0->collision_data = D_801060F0;
            arg0->unk42 |= 0x8000;
            M54_FLASH(arg0) = (u32)(hit - 0x19) < 2 ? 4 : 0x40;
            if ((hit == 6 || hit == 0xF) && M54_84(arg0) == 0 && arg0->ext.main_54.claw_hitbox == 0) {
                arg0->contact_damage = 6;
                arg0->unk5 = 0xA;
                arg0->unk6 = 0;
            }
        }
    } else {
        M54_FLASH(arg0) = --flash;
        if (flash == 0) {
            arg0->collision_data = D_801078F8;
            arg0->unk42 &= 0x7FFF;
        } else if (flash & 1) {
            arg0->unk42 &= 0x7FFF;
        } else {
            arg0->unk42 |= 0x8000;
        }
    }
    if (arg0->hp < 0x11)
        arg0->ext.main_54.pattern_set = 2;
    else if (arg0->hp < 0x21)
        arg0->ext.main_54.pattern_set = 1;
    if (M54_84(arg0) & 0x80)
        arg0->attack_box = &D_80100218;
    func_8002D9BC(arg0);
    if (arg0->ext.main_54.claw_hitbox != 0) {
        saved = arg0->attack_box;
        arg0->attack_box = &D_8010021C;
        func_8002D9BC(arg0);
        arg0->attack_box = saved;
    }
    if (arg0->animation_step.fields.frame_index == 0x25) {
        saved = arg0->attack_box;
        arg0->attack_box = &D_8010023C;
        func_8002D9BC(arg0);
        arg0->attack_box = saved;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006BD1C);
#endif

void slash_beast_death(struct MainObj* self)
{
    slash_beast_death_funcs[self->unk5](self);
}

void slash_beast_death_start(struct MainObj* self)
{
    g_Player.stun_timer = 0;
    player_start_script_action(0x14, g_Player.unk15);
    self->unk5 = 1;
    self->unk42 &= 0x7FFF;
    set_animation(self, 0x13);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->invincibility_timer = 0x19;
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_death_blink(struct MainObj* self)
{
    struct EffectObj* effect;

    self->unk7C--;
    if (self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.u.hi;
            effect->y_pos.i.hi = self->y_pos.u.hi;
            self->ext.main_54.effect = effect;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        self->invincibility_timer -= 5;
        if (self->invincibility_timer > 0x19) {
            self->invincibility_timer = 0;
        }
        self->unk7E = self->invincibility_timer > 5 ? self->invincibility_timer : 5;
    }
}

void slash_beast_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_54.effect;
    self->on_screen = 0;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
        }
    } else {
        self->ext.raw[0] = 0;
        self->ext.raw[1] = 0;
        self->ext.raw[2] = 0;
        self->ext.raw[3] = 0;
        self->ext.raw[4] = 0;
        self->ext.raw[5] = 0;
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = 0;
        if (engine_obj.stage != 0xC) {
            engine_obj.unkF = 0x10;
        } else {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        }
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void slash_beast_start_pattern(struct MainObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void slash_beast_crescent(struct MainObj* self)
{
    slash_beast_crescent_funcs[self->unk6](self);
}

void slash_beast_crescent_jump(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->attack_box = &D_80100220;
        self->hurt_box = &D_80100224;
    }
    if (self->animation_step.fields.event == 1) {
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-3);
        } else {
            self->x_speed = FIXED(3);
        }
        self->x_accel = FIXED(-0.125);
        self->y_speed = FIXED(3);
        self->gravity = FIXED(0.125);
        set_animation(self, 9);
        func_8001540C(2, SATURN_SOUND(0x81, 0x52), self);
        self->unk6 = 1;
    }
}

// slash_beast_crescent_slash
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006C378(struct MainObj* arg0)
{
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->x_speed == 0) {
        arg0->x_accel = 0;
        arg0->gravity = 0;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    switch (arg0->animation_step.fields.event) {
    case 1:
        set_animation(arg0, 0x25);
        arg0->gravity = 0x3800;
        arg0->unk6 = 2;
        break;
    case 2:
        arg0->attack_box = D_80100230;
        arg0->hurt_box = D_80100234;
        func_8001540C(2, SATURN_SOUND(0x84, 0x55), arg0);
        main54_spawn_shot(arg0, 0);
        break;
    case 3:
        arg0->attack_box = D_80100238;
        arg0->hurt_box = &D_80100240;
        func_8001540C(2, SATURN_SOUND(0x84, 0x55), arg0);
        if (M54_81(arg0) != 0)
            main54_spawn_shot(arg0, 1);
        break;
    case 4:
        arg0->attack_box = &D_80100228;
        arg0->hurt_box = &D_8010022C;
        break;
    case 5:
        arg0->attack_box = &D_80100244;
        arg0->hurt_box = &D_80100248;
        break;
    case 6:
        arg0->attack_box = D_801001F8;
        arg0->hurt_box = D_801001FC;
    case 7:
        arg0->attack_box = &D_80100208;
        arg0->hurt_box = &D_8010020C;
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006C378);
#endif

void slash_beast_crescent_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        func_8001540C(2, SATURN_SOUND(0x82, 0x53), self);
        set_animation(self, 0xA);
        self->hurt_box = (const u8*)D_801001FC;
        self->attack_box = (const u8*)D_801001F8;
        self->y_speed = 0;
        self->gravity = 0;
        self->unk6 = 3;
    }
}

void slash_beast_crescent_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 0);
        slash_beast_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void slash_beast_decide(struct MainObj* self)
{
    slash_beast_decide_funcs[self->unk6](self);
}

// slash_beast_pick_attack
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006C6AC(struct MainObj* arg0)
{
    u8* cursor;
    s8 next;

    if (main54_player_dx(arg0) >= 0xA1 && (get_random() & 7) == 0) {
        if (arg0->hp < 0x10) {
            main54_face_anim(arg0, 0x26);
            M54_84(arg0) = 1;
            next = 7;
        } else {
            main54_face_anim(arg0, 8);
            next = 2;
        }
        goto set_state;
    }
    cursor = arg0->ext.main_54.pattern;
    arg0->ext.main_54.pattern = cursor + 1;
    if ((cursor + 1 == slash_beast_pattern_steps[0] ? (u8)D_8010024C.unk3 : *cursor) == 0xFF)
        slash_beast_pick_pattern(arg0);
    switch (*arg0->ext.main_54.pattern) {
    case 0:
        if ((get_random() & 7) == 0) {
            main54_face_anim(arg0, 8);
            next = 2;
            goto set_state;
        }
        main54_face_anim(arg0, 0xB);
        arg0->unk7C = 0x3C;
        arg0->unk6 = 1;
        return;
    case 1:
        if ((get_random() & 7) == 0) {
            main54_face_anim(arg0, 8);
            next = 2;
        } else if (main54_player_dx(arg0) < 0x70) {
            if (M54_81(arg0) != 0) {
                set_animation(arg0, 0x26);
                next = 0xB;
            } else {
                main54_face_anim(arg0, 0xC);
                arg0->unk7C = 0x24;
                arg0->unk7E = 2;
                next = 6;
            }
        } else {
            main54_face_anim(arg0, 1);
            arg0->ext.main_54.high_jump = 0;
            next = 4;
        }
        break;
    case 2:
        if (main54_player_dx(arg0) < 0x70 && (get_random() & 7) != 0) {
            if (M54_81(arg0) != 0) {
                set_animation(arg0, 0x26);
                next = 0xB;
            } else {
                main54_face_anim(arg0, 0xC);
                arg0->unk7C = 0x24;
                arg0->unk7E = 2;
                next = 6;
            }
        } else {
            main54_face_anim(arg0, 8);
            next = 2;
        }
        break;
    case 3:
        main54_face_anim(arg0, 0x26);
        next = 7;
        break;
    case 4:
        main54_face_anim(arg0, 0xC);
        arg0->unk7C = 0x24;
        arg0->unk7E = 2;
        next = 6;
        break;
    case 5:
        main54_face_anim(arg0, 0x14);
        func_8001540C(2, SATURN_SOUND(0x85, 0x56), arg0);
        arg0->unk7C = 0x5A;
        next = 5;
        break;
    case 6:
        main54_face_anim(arg0, 0x26);
        M54_84(arg0) = 1;
        next = 7;
        break;
    case 7:
        main54_face_anim(arg0, 1);
        arg0->ext.main_54.high_jump = 1;
        next = 4;
        break;
    default:
        return;
    }
set_state:
    arg0->unk5 = next;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006C6AC);
#endif

void slash_beast_crouch(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->hurt_box = (const u8*)&D_80100204;
        self->attack_box = (const u8*)&D_80100200;
        func_8001540C(2, SATURN_SOUND(0x87, 0x58), self);
    }
    if (--self->unk7C == 0) {
        self->hurt_box = (const u8*)D_801001FC;
        self->attack_box = (const u8*)D_801001F8;
        self->unk6 = 0;
    }
}

void slash_beast_jump(struct MainObj* self)
{
    slash_beast_jump_funcs[self->unk6](self);
}

// slash_beast_jump_start
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006CB50(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->x_accel = 0;
    set_animation(arg0, 2);
    arg0->hurt_box = &D_8010020C;
    arg0->attack_box = &D_80100208;
    if (arg0->ext.main_54.high_jump == 0) {
        arg0->x_speed = arg0->unk15 != 0 ? 0x24000 : -0x24000;
        arg0->y_speed = 0x5C000;
    } else {
        arg0->x_speed = arg0->unk15 != 0 ? 0x36000 : -0x36000;
        arg0->y_speed = 0x7C000;
    }
    arg0->gravity = 0x3800;
    func_8001540C(2, SATURN_SOUND(0x81, 0x52), arg0);
    move_with_gravity(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006CB50);
#endif

// slash_beast_jump_air
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006CC3C(struct MainObj* arg0)
{
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->contact_damage = 6;
        arg0->hurt_box = D_801001FC;
        arg0->unk62 = 0;
        arg0->attack_box = D_801001F8;
    }
    if (M54_84(arg0) != 0 && g_Player.stun_timer != 0) {
        func_8001540C(2, SATURN_SOUND(0x86, 0x57), arg0);
        g_Player.unk15 = arg0->unk15;
        if (arg0->unk15 == 0)
            g_Player.x_pos.i.hi = arg0->x_pos.i.hi - 0x12;
        else
            g_Player.x_pos.i.hi = arg0->x_pos.i.hi + 0x12;
        g_Player.y_pos.i.hi = arg0->y_pos.i.hi - 8;
        arg0->unk6 = 1;
    }
    if (arg0->collision_flags & 8) {
        func_8001540C(2, SATURN_SOUND(0x82, 0x53), arg0);
        arg0->y_speed = 0;
        arg0->gravity = 0;
        if (M54_84(arg0) != 0) {
            arg0->unk7C = 0xA;
            arg0->unk5 = 8;
            arg0->unk6 = 0;
        } else {
            set_animation(arg0, 3);
            arg0->unk6 = 2;
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006CC3C);
#endif

void slash_beast_jump_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 0);
        slash_beast_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

// slash_beast_guard
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006CDD4(struct MainObj* arg0)
{
    s32 behind;

    animate_object(ANIMATED_OBJECT(arg0));
    if (M54_82(arg0) != 0) {
        if (arg0->unk15 == 0)
            behind = g_Player.x_pos.i.hi < arg0->x_pos.i.hi;
        else
            behind = arg0->x_pos.i.hi < g_Player.x_pos.i.hi;
        if (behind) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            return;
        }
    }
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x1E;
        set_animation(arg0, 0);
        slash_beast_face_player(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 1;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006CDD4);
#endif

void slash_beast_dash(struct MainObj* self)
{
    slash_beast_dash_funcs[self->unk6](self);
}

void slash_beast_dash_windup(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 0xD);
        self->unk6 = 1;
    }
}

void slash_beast_dash_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->contact_damage = 9;
        set_animation(self, 0xE);
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-1);
        } else {
            self->x_speed = FIXED(1);
        }
        self->ext.main_54.claw_hitbox = 1;
        self->ext.main_54.afterimage_timer = 1;
        func_8001540C(2, SATURN_SOUND(0x83, 0x54), self);
        self->x_accel = FIXED(0.5);
        self->unk6 = 2;
    }
}

// slash_beast_dash_run
void func_8006CFB8(struct MainObj* self)
{
    struct MiscObj* afterimage;

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    if (--self->ext.main_54.afterimage_timer == 0) {
        afterimage = find_free_misc_obj();
        if (afterimage != NULL) {
            afterimage->active = 0x41;
            afterimage->id = 0x1A;
            afterimage->unk2 = 1;
            afterimage->unk16 = 0x21;
            afterimage->unk40 = self->unk40;
            afterimage->unk42 = self->unk42 & 0x7FFF;
            afterimage->animation_table = (u32**)self->animation_table;
            afterimage->unk3C = self->sprite_frames;
            afterimage->bg_offset = self->bg_offset;
            afterimage->x_pos.val = self->x_pos.val;
            afterimage->y_pos.val = self->y_pos.val;
            afterimage->unk15 = self->unk15;
            afterimage->animation_step.fields.frame_index = self->animation_step.fields.frame_index;
            afterimage->ext.misc_26.timer = 0x1E;
            afterimage->ext.misc_26.owner = self;
            afterimage->state = 0;
        }

        if (self->ext.main_54.powered_up != 0) {
            afterimage = find_free_misc_obj();
            if (afterimage != NULL) {
                afterimage->active = 0x41;
                afterimage->id = 0x1A;
                afterimage->unk2 = 1;
                afterimage->unk16 = 0x20;
                afterimage->unk40 = self->unk40;
                afterimage->unk42 = self->unk42 & 0x7FFF;
                afterimage->animation_table = (u32**)self->animation_table;
                afterimage->unk3C = self->sprite_frames;
                afterimage->bg_offset = self->bg_offset;
                afterimage->x_pos.val = self->x_pos.val;
                afterimage->y_pos.val = self->y_pos.val;
                afterimage->unk15 = self->unk15;
                afterimage->animation_step.fields.frame_index = self->animation_step.fields.frame_index + 0x3C;
                afterimage->ext.misc_26.timer = 0x1E;
                afterimage->ext.misc_26.owner = self;
                afterimage->state = 0;
            }
        }

        self->ext.main_54.afterimage_timer = 0xA;
    }

    if (self->ext.main_54.powered_up != 0) {
        if ((self->x_speed >= 0 ? self->x_speed : -self->x_speed) >= FIXED(7.5)) {
            self->x_accel = 0;
        }
    } else {
        if ((self->x_speed >= 0 ? self->x_speed : -self->x_speed) >= FIXED(6)) {
            self->x_accel = 0;
        }
    }

    animate_object(ANIMATED_OBJECT(self));

    if (self->unk15 == 0) {
        if (!(self->collision_flags & 2)) {
            return;
        }
        start_screen_shake_x(0x1E, 8, 2);
        self->contact_damage = 6;
        set_animation(self, 0xF);
        self->unk6 = 3;
        self->hurt_box = NULL;
        self->attack_box = NULL;
        self->ext.main_54.crash_timer = 0x1E;
        func_8001540C(2, SATURN_SOUND(0x88, 0x59), self);
        func_8006E920(self, TILE_ATTR_VALUE(0x39));
    } else {
        if (!(self->collision_flags & 1)) {
            return;
        }
        start_screen_shake_x(0x1E, 8, 2);
        set_animation(self, 0xF);
        self->contact_damage = 6;
        self->unk6 = 3;
        self->hurt_box = NULL;
        self->attack_box = NULL;
        self->ext.main_54.crash_timer = 0x1E;
        func_8001540C(2, SATURN_SOUND(0x88, 0x59), self);
        func_8006E920(self, TILE_ATTR_VALUE(0x39));
    }
}

// slash_beast_dash_crash
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006D280(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->hurt_box = D_801001FC;
        arg0->ext.main_54.claw_hitbox = 0;
        arg0->attack_box = D_801001F8;
    }
    if (arg0->animation_step.fields.event != 1)
        return;
    arg0->unk15 ^= PLAYER_FACING_RIGHT;
    if (--arg0->unk7E == 0) {
        set_animation(arg0, 0x25);
        arg0->gravity = 0x3800;
        arg0->unk5 = 4;
        arg0->unk6 = 1;
    } else {
        set_animation(arg0, 0x10);
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi -= 0x20;
        else
            arg0->x_pos.i.hi += 0x20;
        arg0->unk6 = 4;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006D280);
#endif

void slash_beast_dash_turn(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->contact_damage = 9;
        self->ext.main_54.claw_hitbox = 1;
        self->x_speed = -self->x_speed;
        set_animation(self, 0xE);
        func_8001540C(2, SATURN_SOUND(0x83, 0x54), self);
        self->unk6 = 2;
    }
}

// slash_beast_pounce
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006D3DC(struct MainObj* arg0)
{
    s32 target;
    s32 steps;
    s32 dist;
    s32 speed;
    s32 d;

    if (main54_player_dx(arg0) < 0x70) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        return;
    }
    if (arg0->animation_step.fields.event == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->x_accel = 0;
    if (M54_84(arg0) == 0) {
        set_animation(arg0, 2);
        target = arg0->x_pos.val;
        arg0->hurt_box = &D_8010020C;
        arg0->attack_box = &D_80100208;
    } else {
        M54_84(arg0) |= 0x80;
        target = arg0->x_pos.val + (arg0->unk15 != 0 ? 0x100000 : (s32)0xFFF00000);
        arg0->contact_damage = 0;
        arg0->unk62 = 3;
        set_animation(arg0, 4);
        func_8001540C(2, SATURN_SOUND(0x87, 0x58), arg0);
    }
    d = target - g_Player.x_pos.val;
    if (M54_84(arg0) != 0) {
        if (d >= 0) {
            steps = (u32)d >> 16;
        } else {
            d = g_Player.x_pos.val - target;
            if (d < 0)
                d += 0xFFFF;
            steps = (u32)d >> 16;
        }
        arg0->gravity = 0x6800;
    } else {
        if (d < 0)
            d = g_Player.x_pos.val - target;
        steps = d / 0x24000;
        arg0->gravity = 0x3800;
    }
    if (arg0->unk15 == 0)
        arg0->x_speed = -0x1C000 - (s16)steps * 0x480;
    else
        arg0->x_speed = (s16)steps * 0x480 + 0x1C000;
    dist = target - g_Player.x_pos.val;
    if (dist < 0)
        dist = g_Player.x_pos.val - target;
    speed = arg0->x_speed < 0 ? -arg0->x_speed : arg0->x_speed;
    arg0->y_speed = (((s16)(dist / speed) + 1) * arg0->gravity) / 2;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    func_8001540C(2, SATURN_SOUND(0x81, 0x52), arg0);
    arg0->unk5 = 4;
    arg0->unk6 = 1;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006D3DC);
#endif

void slash_beast_grab(struct MainObj* self)
{
    slash_beast_grab_funcs[self->unk6](self);
}

void slash_beast_grab_check(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 6);
        self->unk16 = VISUAL_SATURN_LAYER(6);
        self->contact_damage = 6;
        self->unk62 = 0;
        self->ext.main_54.grab = 0;
        self->hurt_box = D_801001FC;
        self->attack_box = D_801001F8;
        self->unk5 = 4;
        self->unk6 = 2;
    }
    if (g_Player.stun_timer == 0) {
        return;
    }
    func_8001540C(2, SATURN_SOUND(0x86, 0x57), self);
    if (self->x_pos.i.hi - background_objects[0].x_pos.i.hi > 0xA0) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
    g_Player.unk15 = self->unk15;
    g_Player.y_pos.i.hi = self->y_pos.i.hi - 8;
    if (self->unk15 == 0) {
        g_Player.x_pos.i.hi = self->x_pos.i.hi - 0x23;
        self->x_speed = FIXED(-6);
    } else {
        g_Player.x_pos.i.hi = self->x_pos.i.hi + 0x23;
        self->x_speed = FIXED(6);
    }
    set_animation(self, 5);
    self->unk16 = 1;
    self->unk7C = 0x30;
    self->unk6 = 1;
}

void slash_beast_grab_windup(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 7);
        self->unk6 = 2;
        self->ext.main_54.afterimage_timer = 1;
    }
}

// slash_beast_grab_drag
void func_8006D888(struct MainObj* self)
{
    s16 terrain_y;
    struct MiscObj* afterimage;

    move_object(MOVING_OBJECT(self));

    if (--self->ext.main_54.afterimage_timer == 0) {
        afterimage = find_free_misc_obj();
        if (afterimage != NULL) {
            afterimage->active = 0x41;
            afterimage->id = 0x1A;
            afterimage->unk2 = 1;
            afterimage->unk16 = 0x21;
            afterimage->unk40 = self->unk40;
            afterimage->unk42 = self->unk42 & 0x7FFF;
            afterimage->animation_table = (u32**)self->animation_table;
            afterimage->unk3C = self->sprite_frames;
            afterimage->bg_offset = self->bg_offset;
            afterimage->x_pos.val = self->x_pos.val;
            afterimage->y_pos.val = self->y_pos.val;
            afterimage->unk15 = self->unk15;
            afterimage->animation_step.fields.frame_index = self->animation_step.fields.frame_index;
            afterimage->ext.misc_26.timer = 0x1E;
            afterimage->ext.misc_26.owner = self;
            afterimage->state = 0;
        }

        if (self->ext.main_54.powered_up != 0) {
            afterimage = find_free_misc_obj();
            if (afterimage != NULL) {
                afterimage->active = 0x41;
                afterimage->id = 0x1A;
                afterimage->unk2 = 1;
                afterimage->unk16 = 0x20;
                afterimage->unk40 = self->unk40;
                afterimage->unk42 = self->unk42 & 0x7FFF;
                afterimage->animation_table = (u32**)self->animation_table;
                afterimage->unk3C = self->sprite_frames;
                afterimage->bg_offset = self->bg_offset;
                afterimage->x_pos.val = self->x_pos.val;
                afterimage->y_pos.val = self->y_pos.val;
                afterimage->unk15 = self->unk15;
                afterimage->animation_step.fields.frame_index = self->animation_step.fields.frame_index + 0x3C;
                afterimage->ext.misc_26.timer = 0x1E;
                afterimage->ext.misc_26.owner = self;
                afterimage->state = 0;
            }
        }

        self->ext.main_54.afterimage_timer = 0xA;
    }

    terrain_y = self->y_pos.u.hi + self->terrain_box->unk1;

    if (self->unk15 == 0) {
        g_Player.x_pos.i.hi = self->x_pos.u.hi - 35;
        if ((func_8002D724(PLAYER_OBJECT(self),
                 (s16)(self->x_pos.u.hi + self->terrain_box->unk0 - 48), terrain_y)
                & 0xFF)
            == 0x38) {
            func_8001540C(2, SATURN_SOUND(0x88, 0x59), self);
            self->unk6 = 3;
        }
    } else {
        g_Player.x_pos.i.hi = self->x_pos.u.hi + 35;
        if ((func_8002D724(PLAYER_OBJECT(self),
                 (s16)(self->x_pos.u.hi + self->terrain_box->unk0 + 48), terrain_y)
                & 0xFF)
            == 0x38) {
            func_8001540C(2, SATURN_SOUND(0x88, 0x59), self);
            self->unk6 = 3;
        }
    }
}

void slash_beast_grab_throw(struct MainObj* self)
{
    g_Player.x_pos.i.hi = self->x_pos.u.hi;
    start_screen_shake_x(0x1E, 8, 2);
    set_animation(self, 2);
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->hurt_box = &D_8010020C;
    self->attack_box = &D_80100208;
    self->x_accel = 0;
    if (self->unk15 != 0) {
        self->x_speed = FIXED(-3.244140625);
    } else {
        self->x_speed = FIXED(3.244140625);
    }
    self->gravity = FIXED(0.21875);
    self->y_speed = FIXED(6.5625);
    move_with_gravity(ANIMATED_OBJECT(self));
    func_8001540C(2, SATURN_SOUND(0x81, 0x52), self);
    self->unk5 = 4;
    self->unk6 = 1;
    self->unk62 = 0;
    self->contact_damage = 9;
    self->ext.main_54.grab = 0;
    g_Player.stun_timer = 0;
}

void slash_beast_intro(struct MainObj* self)
{
    slash_beast_intro_funcs[self->unk6](self);
}

void slash_beast_intro_wait_player(struct MainObj* self)
{
    struct EffectObj* temp_v0;

    if (g_Player.x_pos.i.hi >= 0x2500 || engine_obj.stage == 0xC) {
        temp_v0 = find_free_effect_obj();
        if (temp_v0 != 0) {
            temp_v0->active = 1;
            temp_v0->id = 0x18;
            self->ext.main_54.effect = temp_v0;
        }

        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        if (engine_obj.stage == 8) {
            background_objects[0].unk26 = 0x24A0;
            background_objects[0].unk24 = 0x24E0;
            background_objects[0].unk2A = 0xF8;
            background_objects[0].unk28 = 0xF8;
        }

        self->unk7C = 3;
        self->unk7E = 1;
        self->unk6 = 1;
    }
}

void slash_beast_intro_wait_warning(struct MainObj* self)
{
    if (self->ext.main_54.effect->active == 0 && (background_objects[0].x_pos.i.hi == 0x24A0 || engine_obj.stage == 0xC)) {
        self->unk6 = 2;
    }
}

// slash_beast_intro_appear
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006DD44(struct MainObj* arg0)
{
    struct ItemObj* item;
    struct MiscObj* misc;

    if (--arg0->unk7E != 0)
        return;
    if (engine_obj.stage != 0xC) {
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x41;
            item->id = 0x12;
            item->unk16 = VISUAL_SATURN_LAYER(5);
            item->unk2 = 3 - (u8)arg0->unk7C;
            item->unk40 = arg0->unk40;
            item->unk42 = arg0->unk42 & 0x7FFF;
            item->animation_table = arg0->animation_table;
            item->sprite_frames = arg0->sprite_frames;
            item->animation_step.fields.frame_index = 0x79;
            item->state = 0;
            item->bg_offset = arg0->bg_offset;
        }
    }
    if (--arg0->unk7C != 0 && engine_obj.stage != 0xC) {
        arg0->unk7E = 0x1E;
        return;
    }
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
    arg0->unk7C = 0xC8;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x1A;
        misc->unk2 = 0;
        misc->unk16 = VISUAL_SATURN_LAYER(5);
        misc->unk40 = arg0->unk40;
        misc->unk42 = arg0->unk42 & 0x7FFF;
        misc->animation_table = (void*)arg0->animation_table;
        misc->unk3C = (void*)arg0->sprite_frames;
        misc->bg_offset = arg0->bg_offset;
        misc->x_pos.val = arg0->x_pos.val;
        misc->y_pos.val = arg0->y_pos.val;
        misc->unk15 = arg0->unk15;
        misc->ext.misc_26.owner = arg0;
        misc->state = 0;
        misc->animation_step.fields.frame_index = arg0->animation_step.fields.frame_index + 0x3C;
    }
    if (engine_obj.stage == 8) {
        arg0->unk15 = PLAYER_FACING_RIGHT;
        set_animation(arg0, 0x15);
        arg0->x_speed = 0x10000;
        arg0->unk6 = 3;
    } else {
        arg0->unk15 = 0;
        set_animation(arg0, 0x17);
        arg0->unk7E = 1;
        arg0->unk6 = 4;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006DD44);
#endif

void slash_beast_intro_leap(struct MainObj* self)
{
    s16 timer;

    timer = --self->unk7C;
    if (timer == 0) {
        background_objects[0].unk26 = 0x24C0;
        background_objects[0].unk24 = 0x24D0;
        background_objects[0].unk2A = 0xD0;
        background_objects[0].unk28 = 0xD0;
        set_animation(self, 0x16);
        self->gravity = FIXED(0.125);
        self->y_speed = FIXED(7.5);
        self->x_speed = FIXED(1.875);
        self->unk7E = 0;
        func_8001540C(2, SATURN_SOUND(0x81, 0x52), self);
        self->unk6 = 4;
    }
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_intro_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->x_pos.i.hi - background_objects[0].x_pos.i.hi >= 0xE0) {
        self->x_speed = 0;
        self->gravity = FIXED(1);
    }
    if (self->y_speed == 0) {
        self->terrain_box = &D_8010024C;
        set_animation(self, 0x17);
    }
    if (self->y_speed < 0) {
        switch (self->unk7E) {
        case 0:
            if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi + self->terrain_box->unk0,
                    self->terrain_box->unk3 + (self->y_pos.i.hi + self->terrain_box->unk1) + 0x40)
                == 0x38) {
                if (engine_obj.stage == 8) {
                    apply_tile_effect(8, 0x2580, 0x140);
                    func_8001540C(2, SATURN_SOUND(0x80, 0x51), self);
                    spawn_debris(4, D_801005B0, self);
                }
                self->unk7E = 1;
            }
            break;
        case 1:
            if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi + self->terrain_box->unk0,
                    self->terrain_box->unk3 + (self->y_pos.i.hi + self->terrain_box->unk1) + 0x10)
                == 0x38) {
                self->unk7E = 2;
                set_animation(self, 3);
                if (engine_obj.stage == 0xC) {
                    func_8001540C(2, SATURN_SOUND(0x82, 0x53), self);
                }
            }
            break;
        }
    }
    if (self->collision_flags & 8) {
        start_screen_shake_y(0x10, 4, 2);
        self->ext.main_54.active = 1;
        self->unk6 = 5;
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_intro_pose(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        if (engine_obj.stage == 8) {
            self->unk15 = 0;
            set_animation(self, 0x18);
            func_8002217C(0x10, 0xFF, (u8)engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        self->unk6 = 6;
    }
}

void slash_beast_intro_wait_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        set_animation(self, 0x19);
        self->unk7E = 3;
        self->unk6 = 7;
        play_boss_voice(7);
    }
}

void slash_beast_intro_fill_health(struct MainObj* self)
{
    if (update_boss_music_delay() == 0) {
        if (engine_obj.stage == 8) {
            if (background_objects[0].unk26 != 0x24B0) {
                background_objects[0].unk26 -= 1;
            }
        }

        if (--self->unk7E == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), 0);
            self->unk7E = 3;
        }

        if (++self->hp == 0x30) {
            self->ext.main_54.pattern_set = 0;
            self->ext.main_54.fight_started = 1;
            slash_beast_pick_pattern(self);
            self->unk5 = 3;
            self->ext.main_54.pattern--;
            self->unk6 = 0;
            player_end_script_action();
        }
    }
}

void slash_beast_stagger(struct MainObj* self)
{
    slash_beast_stagger_funcs[self->unk6](self);
}

// slash_beast_stagger_start
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006E450(struct MainObj* arg0)
{
    s16 x;
    s16 y;

    if (--arg0->ext.main_54.power_hits == 0) {
        y = arg0->y_pos.i.hi;
        arg0->y_pos.i.hi = y - 4;
        x = arg0->x_pos.i.hi;
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = x + 0x1B;
        else
            arg0->x_pos.i.hi = x - 0x1B;
        spawn_debris(3, D_801005B4, arg0);
        arg0->y_pos.i.hi = y + 0xC;
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = x + 0x1D;
        else
            arg0->x_pos.i.hi = x - 0x1D;
        spawn_debris(3, D_801005B4, arg0);
        arg0->x_pos.i.hi = x;
        arg0->y_pos.i.hi = y;
        M54_81(arg0) = 0;
    }
    set_animation(arg0, 0x11);
    if (arg0->x_pos.i.hi < g_Player.x_pos.i.hi) {
        arg0->unk15 = 0;
        arg0->x_speed = -0x10000;
    } else {
        arg0->unk15 = PLAYER_FACING_RIGHT;
        arg0->x_speed = 0x10000;
    }
    arg0->y_speed = 0x40000;
    arg0->x_accel = 0;
    arg0->gravity = 0x8000;
    move_object(MOVING_OBJECT(arg0));
    arg0->unk6 = 1;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006E450);
#endif

void slash_beast_stagger_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        func_8001540C(2, SATURN_SOUND(0x88, 0x59), self);
        self->x_speed = 0;
        self->y_speed = 0;
        self->gravity = 0;
        set_animation(self, 0x12);
        self->unk6 = 2;
    }
}

void slash_beast_stagger_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        slash_beast_face_player(self);
        set_animation(self, 0xC);
        self->unk7C = 0x14;
        self->unk7E = 1;
        self->unk5 = 6;
        self->unk6 = 0;
        self->ext.main_54.claw_hitbox = 1;
    }
}

void slash_beast_high_leap(struct MainObj* self)
{
    slash_beast_high_leap_funcs[self->unk6](self);
}

void slash_beast_high_leap_jump(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-1.75);
        } else {
            self->x_speed = FIXED(1.75);
        }
        self->x_accel = 0;
        self->y_speed = FIXED(7.4375);
        self->gravity = FIXED(0.21875);
        move_with_gravity(ANIMATED_OBJECT(self));
        func_8001540C(2, SATURN_SOUND(0x81, 0x52), self);
        set_animation(self, 2);
        self->unk6 = 1;
    }
}

void slash_beast_high_leap_fall(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_speed == 0) {
        self->gravity = FIXED(2);
        self->x_speed = 0;
        self->unk6 = 2;
        set_animation(self, 0x17);
        self->contact_damage = 7;
        self->attack_box = (const u8*)&D_80100210;
        self->hurt_box = (const u8*)&D_80100214;
    }
}

void slash_beast_high_leap_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if ((func_8002D724(
             PLAYER_OBJECT(self),
             (s16)((u16)self->x_pos.i.hi + self->terrain_box->unk0),
             (s16)(self->terrain_box->unk3 + ((u16)self->y_pos.i.hi + self->terrain_box->unk1) + 0x10))
            & 0xFF)
        == 0x38) {
        func_8001540C(2, SATURN_SOUND(0x88, 0x59), self);
        start_screen_shake_y(0x10, 4, 2);
        set_animation(self, 3);
        self->unk6 = 3;
    }
}

void slash_beast_high_leap_recover(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->contact_damage = 5;
        self->y_speed = 0;
        self->gravity = 0;
    }
    if (self->animation_step.fields.event != 0) {
        self->attack_box = (const u8*)D_801001F8;
        self->hurt_box = (const u8*)D_801001FC;
        set_animation(self, 0);
        slash_beast_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

// slash_beast_set_floor_palette
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006E920(struct MainObj* arg0, s32 value)
{
    s32 start = 0;
    s32 end;
    s32 i;
    u32* attrs;
    u16 index;

    if (value == TILE_ATTR_VALUE(0x38)) {
        end = engine_obj.stage == 0xC ? 0xE : 8;
    } else if (arg0->unk15 == 0) {
        if (engine_obj.stage == 0xC) {
            start = 7;
            end = 0xE;
        } else {
            start = 4;
            end = 8;
        }
    } else {
        end = engine_obj.stage == 0xC ? 7 : 4;
    }
    for (i = start; i < end; i++) {
        index = engine_obj.stage == 0xC ? D_801005C8[i] : D_801005B8[i];
#ifdef MMX4_SATURN
        attrs = SATURN_TILE_ATTRS;
        attrs[index] = (attrs[index] & 0xFFFFFF) | value;
#else
        attrs = SP_BG_TILE_ATTRS;
        attrs[index] &= ~0xFF;
        attrs[index] |= value;
#endif
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006E920);
#endif

void slash_beast_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", slash_beast_pick_pattern);
#else
void slash_beast_pick_pattern(struct MainObj* self)
{
    u8* base;
    u8* current;
    u8* thresholds;
    u32 random;
    u8 index;
    s32 i;

    random = get_random();
    i = 0;
    random &= 0xF;
    index = self->ext.main_54.pattern_set;
    thresholds = slash_beast_pattern_weights;
    base = slash_beast_patterns[index][0];
    current = base;
    thresholds += (index << 1) + index;

    for (; i < 3; i++) {
        if (random < *thresholds) {
            self->ext.main_54.pattern = current;
            return;
        }
        current += 4;
        thresholds++;
    }

    self->ext.main_54.pattern = base + i * 4;
}
#endif

union AnimationStep D_801001F8[] = {
    { -17, -15, 37, 0x22 },
};

union AnimationStep D_801001FC[] = {
    { -27, -21, 58, 0x31 },
};

struct Unk_unk68 D_80100200 = { -28, -16, 34, 38 };

struct Unk_unk68 D_80100204 = { -37, -24, 64, 48 };

struct Unk_unk68 D_80100208 = { -11, -30, 29, 57 };

struct Unk_unk68 D_8010020C = { -17, -32, 43, 66 };

struct Unk_unk68 D_80100210 = { -16, -38, 31, 81 };

struct Unk_unk68 D_80100214 = { -22, -43, 43, 93 };

struct Unk_unk68 D_80100218 = { -42, -19, 33, 27 };

struct Unk_unk68 D_8010021C = { -66, -10, 26, 6 };

struct Unk_unk68 D_80100220 = { -15, -29, 26, 50 };

struct Unk_unk68 D_80100224 = { -22, -36, 40, 64 };

struct Unk_unk68 D_80100228 = { -11, -13, 39, 27 };

struct Unk_unk68 D_8010022C = { -20, -22, 57, 46 };

union AnimationStep D_80100230[] = {
    { -60, -11, 68, 0x22 },
};

union AnimationStep D_80100234[] = {
    { -62, -24, 89, 0x39 },
};

union AnimationStep D_80100238[] = {
    { -79, -48, 71, 0x1F },
};

struct Unk_unk68 D_8010023C = { -48, -73, 49, 48 };

struct Unk_unk68 D_80100240 = { -74, -69, 105, 90 };

struct Unk_unk68 D_80100244 = { -6, -68, 32, 80 };

struct Unk_unk68 D_80100248 = { -15, -71, 48, 96 };

struct Unk_unk68 D_8010024C = { 0, 0, 28, 26 };

u8 slash_beast_pattern_steps[9][4] = {
    { 0, 1, 1, 255 },
    { 0, 7, 2, 255 },
    { 0, 3, 4, 255 },
    { 0, 7, 2, 255 },
    { 5, 3, 4, 6 },
    { 255, 0, 0, 0 },
    { 0, 7, 2, 2 },
    { 255, 0, 0, 0 },
    { 5, 6, 6, 255 },
};

u8* D_80100274[4] = {
    slash_beast_pattern_steps[0],
    slash_beast_pattern_steps[1],
    0x00000000,
    0x00000000,
};

u8* D_80100284[4] = {
    slash_beast_pattern_steps[2],
    slash_beast_pattern_steps[3],
    0x00000000,
    0x00000000,
};

u8* D_80100294[4] = {
    slash_beast_pattern_steps[4],
    slash_beast_pattern_steps[6],
    slash_beast_pattern_steps[8],
    0x00000000,
};

u8** slash_beast_patterns[3] = {
    D_80100274,
    D_80100284,
    D_80100294,
};

u8 slash_beast_pattern_weights[12] = { 0x07, 0x10, 0x00, 0x09, 0x10, 0x00, 0x07, 0x0A, 0x10, 0x00, 0x00, 0x00 };

union AnimationStep D_801002BC[] = {
    { 1, 1, 0, 0x00 },
};

union AnimationStep D_801002C0[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 4, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 1, 0, 0x00 },
};

union AnimationStep D_801002D8[] = {
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 2, 1, 0x05 },
    { 2, 1, -1, 0x06 },
};

union AnimationStep D_80100308[] = {
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 12, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 1, 0, 0x00 },
};

union AnimationStep D_80100320[] = {
    { 2, 0, 1, 0x07 },
    { 2, 1, -1, 0x08 },
};

union AnimationStep D_80100328[] = {
    { 19, 0, 1, 0x09 },
    { 1, 1, 0, 0x09 },
};

union AnimationStep D_80100330[] = {
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 28, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 1, 0, 0x00 },
};

union AnimationStep D_80100348[] = {
    { 1, 1, 0, 0x0A },
};

union AnimationStep D_8010034C[] = {
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 2, 2, 1, 0x1F },
    { 16, 0, 1, 0x20 },
    { 1, 1, 0, 0x20 },
};

union AnimationStep D_80100364[] = {
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x21 },
    { 2, 4, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 1, 2, 1, 0x24 },
    { 1, 3, 1, 0x25 },
    { 1, 5, 1, 0x26 },
    { 1, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 10, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x29 },
    { 2, 6, 1, 0x2A },
    { 2, 7, 1, 0x2C },
    { 1, 0, 1, 0x2B },
    { 1, 1, 0, 0x2B },
};

union AnimationStep D_801003A4[] = {
    { 2, 0, 1, 0x01 },
    { 30, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 1, 0, 0x00 },
};

union AnimationStep D_801003B8[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x1A },
    { 1, 2, 1, 0x1B },
    { 7, 0, 1, 0x1B },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x00 },
    { 1, 0, 1, 0x17 },
    { 1, 1, -1, 0x18 },
};

union AnimationStep D_801003D8[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 1, 0, 1, 0x0B },
    { 1, 0, 1, 0x0D },
    { 1, 1, -2, 0x0C },
};

union AnimationStep D_801003EC[] = {
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x0E },
    { 1, 1, 0, 0x09 },
};

union AnimationStep D_801003F8[] = {
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x10 },
    { 1, 1, -2, 0x11 },
};

union AnimationStep D_80100404[] = {
    { 2, 0, 1, 0x12 },
    { 2, 2, 1, 0x13 },
    { 2, 0, 1, 0x14 },
    { 20, 0, 1, 0x15 },
    { 2, 0, 1, 0x14 },
    { 1, 0, 1, 0x13 },
    { 1, 1, 0, 0x13 },
};

union AnimationStep D_80100420[] = {
    { 1, 0, 1, 0x16 },
    { 1, 1, 0, 0x0A },
};

union AnimationStep D_80100428[] = {
    { 2, 0, 1, 0x33 },
    { 2, 1, -1, 0x34 },
};

union AnimationStep D_80100430[] = {
    { 2, 0, 1, 0x35 },
    { 2, 0, 1, 0x36 },
    { 2, 0, 1, 0x35 },
    { 2, 0, 1, 0x36 },
    { 2, 0, 1, 0x35 },
    { 24, 0, 1, 0x36 },
    { 2, 0, 1, 0x35 },
    { 2, 0, 1, 0x36 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 1, 0, 0x00 },
};

union AnimationStep D_80100460[] = {
    { 1, 1, 0, 0x37 },
};

union AnimationStep D_80100464[] = {
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x32 },
    { 1, 1, -3, 0x1B },
};

union AnimationStep D_80100474[] = {
    { 1, 0, 1, 0x2D },
    { 1, 0, 1, 0x2E },
    { 1, 1, -2, 0x2F },
};

union AnimationStep D_80100480[] = {
    { 2, 0, 1, 0x03 },
    { 2, 1, -1, 0x04 },
};

union AnimationStep D_80100488[] = {
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x1C },
    { 2, 1, -1, 0x1D },
};

union AnimationStep D_801004A0[] = {
    { 1, 1, 0, 0x19 },
};

union AnimationStep D_801004A4[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x1A },
    { 20, 0, 1, 0x1B },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x00 },
    { 1, 0, 1, 0x17 },
    { 1, 1, -1, 0x18 },
};

union AnimationStep D_801004C0[] = {
    { 1, 0, 1, 0x38 },
    { 1, 1, -1, 0x39 },
};

union AnimationStep D_801004C8[] = {
    { 1, 0, 1, 0x3A },
    { 1, 1, -1, 0x3B },
};

union AnimationStep D_801004D0[] = {
    { 1, 1, 0, 0x74 },
};

union AnimationStep D_801004D4[] = {
    { 1, 1, 0, 0x75 },
};

union AnimationStep D_801004D8[] = {
    { 1, 1, 0, 0x76 },
};

union AnimationStep D_801004DC[] = {
    { 1, 1, 0, 0x77 },
};

union AnimationStep D_801004E0[] = {
    { 1, 1, 0, 0x78 },
};

union AnimationStep D_801004E4[] = {
    { 1, 1, 0, 0x79 },
};

union AnimationStep D_801004E8[] = {
    { 1, 1, 0, 0x7A },
};

union AnimationStep D_801004EC[] = {
    { 1, 1, 0, 0x7B },
};

union AnimationStep D_801004F0[] = {
    { 1, 1, 0, 0x7C },
};

union AnimationStep D_801004F4[] = {
    { 2, 0, 1, 0x05 },
    { 2, 1, -1, 0x06 },
};

union AnimationStep D_801004FC[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 6, 0, 1, 0x02 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 1, 0, 0x00 },
};

union AnimationStep* slash_beast_animations[39] = {
    D_801002BC,
    D_801002C0,
    D_801002D8,
    D_80100308,
    D_80100320,
    D_80100328,
    D_80100330,
    D_80100348,
    D_8010034C,
    D_80100364,
    D_801003A4,
    D_801003B8,
    D_801003D8,
    D_801003EC,
    D_801003F8,
    D_80100404,
    D_80100420,
    D_80100428,
    D_80100430,
    D_80100460,
    D_80100464,
    D_80100474,
    D_80100480,
    D_80100488,
    D_801004A0,
    D_801004A4,
    D_801004C0,
    D_801004C8,
    D_801004D0,
    D_801004D4,
    D_801004D8,
    D_801004DC,
    D_801004E0,
    D_801004E4,
    D_801004E8,
    D_801004EC,
    D_801004F0,
    D_801004F4,
    D_801004FC,
};

u8 D_801005B0[4] = { 29, 30, 31, 32 };

char D_801005B4[] = "\"#$";

u16 D_801005B8[8] = {
    0x0070,
    0x0072,
    0x0074,
    0x0076,
    0x0065,
    0x0067,
    0x0069,
    0x006B,
};

u16 D_801005C8[14] = {
    0x0388,
    0x038D,
    0x03AC,
    0x03AF,
    0x03B2,
    0x03B5,
    0x03C3,
    0x0380,
    0x0383,
    0x0390,
    0x0392,
    0x0394,
    0x0396,
    0x03A0,
};

void (*slash_beast_state_funcs[])(struct MainObj*) = {
    func_8006BB70,
    func_8006BD1C,
    slash_beast_death,
};

void (*slash_beast_step_funcs[12])() = {
    enemy_hit_reaction,
    slash_beast_start_pattern,
    slash_beast_crescent,
    slash_beast_decide,
    slash_beast_jump,
    func_8006CDD4,
    slash_beast_dash,
    func_8006D3DC,
    slash_beast_grab,
    slash_beast_intro,
    slash_beast_stagger,
    slash_beast_high_leap,
};

void (*slash_beast_death_funcs[3])(struct MainObj*) = {
    slash_beast_death_start,
    slash_beast_death_blink,
    slash_beast_death_finish,
};

void (*slash_beast_crescent_funcs[4])(struct MainObj*) = {
    slash_beast_crescent_jump,
    func_8006C378,
    slash_beast_crescent_land,
    slash_beast_crescent_recover,
};

void (*slash_beast_decide_funcs[2])() = {
    func_8006C6AC,
    slash_beast_crouch,
};

void (*slash_beast_jump_funcs[3])(struct MainObj*) = {
    func_8006CB50,
    func_8006CC3C,
    slash_beast_jump_recover,
};

void (*slash_beast_dash_funcs[5])(struct MainObj*) = {
    slash_beast_dash_windup,
    slash_beast_dash_start,
    func_8006CFB8,
    func_8006D280,
    slash_beast_dash_turn,
};

void (*slash_beast_grab_funcs[4])(struct MainObj*) = {
    slash_beast_grab_check,
    slash_beast_grab_windup,
    func_8006D888,
    slash_beast_grab_throw,
};

void (*slash_beast_intro_funcs[8])(struct MainObj*) = {
    slash_beast_intro_wait_player,
    slash_beast_intro_wait_warning,
    func_8006DD44,
    slash_beast_intro_leap,
    slash_beast_intro_land,
    slash_beast_intro_pose,
    slash_beast_intro_wait_dialogue,
    slash_beast_intro_fill_health,
};

void (*slash_beast_stagger_funcs[3])(struct MainObj*) = {
    func_8006E450,
    slash_beast_stagger_land,
    slash_beast_stagger_recover,
};

void (*slash_beast_high_leap_funcs[4])(struct MainObj*) = {
    slash_beast_high_leap_jump,
    slash_beast_high_leap_fall,
    slash_beast_high_leap_land,
    slash_beast_high_leap_recover,
};
