// MainObj, main_object_update_funcs[69]
// 80085F08..80088BA0
#include "common.h"
#ifdef MMX4_SATURN
extern u8 saturn_colonel_init_mode;
#endif
#include "weapon_resources.h"
#include "main/mains/main_69_colonel.h"
#include "main/objects.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/1AC84.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/stage_objects.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#endif

extern struct Unk_unk68 D_8010450C;
extern struct Unk_unk68 D_80104510;

// colonel_state_funcs
extern void (*colonel_state_funcs[])(struct MainObj*);
void colonel_spawn(struct MainObj* arg0);

void colonel_death(struct MainObj* arg0);

// colonel_spawn_funcs
extern void (*colonel_spawn_funcs[])(struct MainObj*);

// colonel_step_funcs
void colonel_start_fight(struct MainObj* arg0);
void colonel_intro(struct MainObj* arg0);
void colonel_guard(struct MainObj* arg0);
void colonel_teleport_slash(struct MainObj* arg0);
void colonel_dash(struct MainObj* arg0);
void colonel_saber_waves(struct MainObj* arg0);
void colonel_flash_strike(struct MainObj* arg0);
void colonel_jump_slam(struct MainObj* arg0);

// colonel_death_funcs
extern void (*colonel_death_funcs[])(struct MainObj*);
void colonel_defeat(struct MainObj* arg0);
void colonel_retreat(struct MainObj* arg0);

// colonel_defeat_funcs
extern void (*colonel_defeat_funcs[])(struct MainObj*);

void colonel_defeat_next(struct MainObj* arg0);
void colonel_defeat_dialogue(struct MainObj*);
void colonel_defeat_wait_dialogue(struct MainObj*);

void colonel_defeat_wait_explosion(struct MainObj*);

// colonel_retreat_funcs
extern void (*colonel_retreat_funcs[])(struct MainObj*);
void colonel_retreat_start(struct MainObj*);
void colonel_retreat_vanish(struct MainObj*);
void func_80086860(struct MainObj*);
void colonel_retreat_reappear(struct MainObj*);
void colonel_retreat_wait_dialogue(struct MainObj*);
void colonel_retreat_start_again(struct MainObj*);
void colonel_retreat_vanish_again(struct MainObj*);
void colonel_retreat_finish(struct MainObj*);

// colonel_intro_funcs
extern void (*colonel_intro_funcs[])(struct MainObj*);
void colonel_intro_port(struct MainObj* arg0);
void colonel_intro_hall(struct MainObj* arg0);

// colonel_intro_port_funcs
extern void (*colonel_intro_port_funcs[])(struct MainObj*);

void colonel_intro_port_blink_in(struct MainObj*);
void colonel_intro_port_pose(struct MainObj*);
void colonel_intro_port_voice(struct MainObj*);
void colonel_intro_port_fill_health(struct MainObj*);

// colonel_intro_hall_funcs
extern void (*colonel_intro_hall_funcs[])(struct MainObj*);

void colonel_intro_hall_portrait_player(struct MainObj*);
void colonel_intro_hall_dialogue(struct MainObj*);
void colonel_intro_hall_portrait_colonel(struct MainObj*);
void colonel_intro_hall_wait(struct MainObj*);
void colonel_intro_hall_blink_in(struct MainObj*);
void colonel_intro_hall_flash(struct MainObj*);

void colonel_intro_hall_fill_health(struct MainObj*);

// colonel_guard_funcs
extern void (*colonel_guard_funcs[])(struct MainObj*);
void colonel_guard_pick(struct MainObj*);
void colonel_guard_watch(struct MainObj*);
void colonel_guard_block(struct MainObj*);
void colonel_guard_recover(struct MainObj*);

// colonel_teleport_slash_funcs
extern void (*colonel_teleport_slash_funcs[])(struct MainObj*);
void colonel_teleport_slash_vanish(struct MainObj*);
void colonel_teleport_slash_shake(struct MainObj*);

// colonel_dash_funcs
extern void (*colonel_dash_funcs[])(struct MainObj*);
void colonel_dash_start(struct MainObj*);

// colonel_saber_waves_funcs
extern void (*colonel_saber_waves_funcs[])(struct MainObj*);
void colonel_saber_waves_start(struct MainObj*);

void colonel_saber_waves_recover(struct MainObj*);
void colonel_saber_waves_wait(struct MainObj*);

// colonel_flash_strike_funcs
extern void (*colonel_flash_strike_funcs[])(struct MainObj*);
void colonel_flash_strike_vanish(struct MainObj*);
void colonel_flash_strike_shake(struct MainObj*);
void colonel_flash_strike_reappear(struct MainObj*);
void colonel_flash_strike_slide(struct MainObj*);
void func_800881F8(struct MainObj*);
void colonel_flash_strike_flash(struct MainObj*);
void func_800883CC(struct MainObj*);
void colonel_flash_strike_wait(struct MainObj*);
void colonel_flash_strike_recover(struct MainObj*);

// colonel_jump_slam_funcs
extern void (*colonel_jump_slam_funcs[])(struct MainObj*);
void colonel_jump_slam_jump(struct MainObj*);
void colonel_jump_slam_rise(struct MainObj*);
void colonel_jump_slam_land(struct MainObj*);
void colonel_jump_slam_drop(struct MainObj*);

void colonel_jump_slam_recover(struct MainObj*);

void colonel_face_center(struct BaseObj* self);

void colonel_update(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    colonel_state_funcs[self->state](self);
}

void colonel_spawn(struct MainObj* self)
{
    colonel_spawn_funcs[self->unk5](self);
}

void colonel_spawn_warning(struct MainObj* self)
{
    struct EffectObj* effect;

    self->ext.main_69.state.bytes.variant = self->unk2;
    if (self->ext.main_69.state.bytes.variant == 1) {
        self->unk5++;
    } else {
        effect = find_free_effect_obj();
        if (effect == NULL) {
            return;
        }
        effect->active = 1;
        effect->id = 0x18;
        self->ext.main_69.effect = effect;
        player_start_script_action(0x15, 0);
        self->unk5++;
    }
}

// colonel_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

extern struct Unk_unk68 D_801044F8;
extern void* D_80104770[25];
extern void (*colonel_step_funcs[9])();
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80086008(struct MainObj* arg0);
void func_80086124(struct MainObj* arg0);
void func_800877A4(struct MainObj* arg0);
void func_80087A00(struct MainObj* arg0);
void func_800889DC(struct MainObj* arg0);
extern u8 D_801044A0[8];
extern u8 D_801044A8[8];
extern void* D_801044EC[2];
extern u8 D_801044F4[4];
void colonel_spawn_afterimages(struct MainObj*);
void colonel_face_player(struct MainObj*);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_80086008);
#else
void func_80086008(struct MainObj* arg0)
{
    if (arg0->ext.main_69.state.bytes.variant == 0) {
        if (arg0->ext.main_69.effect->active != 0)
            return;
        arg0->unk6 = 0;
    } else {
        arg0->unk6 = 1;
    }
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk15 = 0;
    arg0->unk16 = VISUAL_SATURN_LAYER(5);
    arg0->hp = 0;
    arg0->contact_damage = 6;
    arg0->invincibility_timer = 0;
    arg0->terrain_box = &D_801044F8;
    arg0->hurt_box = NULL;
    arg0->attack_box = NULL;
    arg0->collision_data = NULL;
    arg0->animation_table = (const u8* const*)D_80104770;
    arg0->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
    set_animation(arg0, 0);
    colonel_spawn_afterimages(arg0);
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
    arg0->state = 1;
    arg0->ext.main_69.state.bytes.unk8D = 0;
    arg0->ext.main_69.state.bytes.unk8E = 0;
    arg0->unk5 = 2;
#ifdef MMX4_SATURN
    saturn_colonel_init_mode = 15;
#endif
}
#endif

// colonel_run
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_80086124);
#else
void func_80086124(struct MainObj* arg0)
{
    s32 collision;

    colonel_step_funcs[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    if (arg0->ext.main_69.state.bytes.unk8D != 0) {
        if (!(arg0->ext.main_69.state.bytes.unk8D & 1))
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (--arg0->ext.main_69.state.bytes.unk8D == 0) {
            arg0->collision_data = D_80108084;
            arg0->ext.main_69.state.bytes.unk8E = 0;
        }
    } else if (collision < 0) {
        arg0->state = 2;
        if (arg0->ext.main_69.state.bytes.variant == 0)
            arg0->unk5 = 0;
        else
            arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        is_on_screen(BASE_OBJECT(arg0));
        return;
    } else if (collision != 0 && collision != 0x7F) {
        arg0->collision_data = D_801060F0;
        arg0->ext.main_69.state.bytes.unk8D = 0x40;
        arg0->ext.main_69.state.bytes.unk8E = 1;
    }
    func_8002D9BC(arg0);
}
#endif

void colonel_death(struct MainObj* self)
{
    colonel_death_funcs[self->unk5](self);
}

void colonel_defeat(struct MainObj* self)
{
    colonel_defeat_funcs[self->unk6](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

void colonel_defeat_start(struct MainObj* self)
{
    u8 facing;

    if (self->x_pos.i.hi > g_Player.x_pos.i.hi) {
        facing = 1;
    } else {
        facing = 0;
    }
    facing <<= PLAYER_FACING_SHIFT;
    colonel_face_player(self);
    player_start_script_action(0x14, facing);
    func_8002B560(0x25, 0x10);
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    need_palette_load |= 1;
    if (self->air_state == 0) {
        set_animation(self, 0x18);
        self->unk6 += 3;
    } else {
        set_animation(self, 0xA);
        self->x_speed = self->unk15 ? FIXED(-3) : FIXED(3);
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->unk6++;
    }
    is_on_screen(self);
}

void colonel_defeat_fall(struct MainObj* self)
{
    u8 flags;

    move_with_gravity(ANIMATED_OBJECT(self));
    flags = self->collision_flags;
    if (flags & 8) {
        func_8001540C(2, SATURN_SOUND(0xD1, 0x93), self);
        set_animation(self, 4);
        start_screen_shake_y(0x18, 2, 1);
        self->air_state = 0;
        set_animation(self, 0x18);
        self->unk6++;
        return;
    }
    if (flags & 3) {
        self->x_speed = 0;
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_defeat_next(struct MainObj* self)
{
    self->unk6++;
}

void colonel_defeat_dialogue(struct MainObj* self)
{
    if (engine_obj.cur_character == 0) {
        func_8002217C(0x33, 4, 0);
    } else {
        func_8002217C(0x2E, 5, 0);
    }
    self->unk6++;
    is_on_screen(BASE_OBJECT(self));
}

void colonel_defeat_wait_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk7C = 0x7F;
        self->unk7E = 0x19;
        self->invincibility_timer = 0x19;
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_defeat_blink(struct MainObj* self)
{
    struct EffectObj* effect;

    if (--self->unk7C == 0) {
        self->unk6++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_69.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- != 0)
        return;
    self->unk42 ^= 0x8000;
    self->invincibility_timer -= 5;
    if (self->invincibility_timer > 0x19)
        self->invincibility_timer = 0;
    self->unk7E = self->invincibility_timer > 5 ? self->invincibility_timer : 5;
}

void colonel_defeat_wait_explosion(struct MainObj* self)
{
    struct MainObj* linked_object;

    linked_object = (struct MainObj*)self->ext.main_69.effect;
    self->on_screen = 0;
    if (linked_object->active != 0) {
        if (linked_object->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        self->ext.main_69.effect = NULL;
        self->ext.main_69.linked_object = NULL;
        self->ext.main_69.script = NULL;
        self->ext.main_69.state.word = 0;
        self->ext.main_69.unk90 = 0;
        self->ext.main_69.unk94 = 0;
        player_end_script_action();
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        engine_obj.unkF = 1;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void colonel_retreat(struct MainObj* self)
{
    colonel_retreat_funcs[self->unk6](self);
}

void colonel_retreat_start(struct MainObj* self)
{
    player_start_script_action(0x15, 0);
    set_animation(self, 6);
    self->unk7C = 0x20;
    self->x_speed = 0;
    self->x_accel = FIXED(1);
    self->y_speed = 0;
    self->gravity = 0;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    self->unk6++;
    func_8001540C(2, SATURN_SOUND(0xD3, 0x95), self);
    is_on_screen(BASE_OBJECT(self));
}

void colonel_retreat_vanish(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->on_screen = 0;
        self->unk7C = 0x20;
        self->unk6++;
    } else {
        self->x_speed += self->x_accel;
        if (SHAKE_ENABLED) {
            if (BLINK_CLOCK(self->unk7C) & 1) {
                self->x_pos.val += self->x_speed;
            } else {
                self->x_pos.val -= self->x_speed;
            }
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

// colonel_retreat_wait
void func_80086860(struct MainObj* self)
{
    if (self->unk7C != 0) {
        self->unk7C--;
        return;
    }

    if (g_Player.script_state == -1) {
        self->x_pos.i.hi = background_objects[0].unk1E + 0x100;
        self->unk7C = 0x20;
        self->x_speed = FIXED(32);
        self->x_accel = FIXED(-1);
        colonel_face_player(self);
        func_8001540C(2, SATURN_SOUND(0xD3, 0x95), self);
        self->unk6++;
    }
}

void colonel_retreat_reappear(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 0x18);
        colonel_face_player(self);
        func_8002217C(0x23, 3, 0);
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        self->x_speed += self->x_accel;
        if (SHAKE_ENABLED) {
            if (BLINK_CLOCK(self->unk7C) & 1) {
                self->x_pos.val += self->x_speed;
            } else {
                self->x_pos.val -= self->x_speed;
            }
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_retreat_wait_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_retreat_start_again(struct MainObj* self)
{
    set_animation(self, 6);
    self->unk7C = 0x20;
    self->x_speed = 0;
    self->x_accel = FIXED(1);
    self->y_speed = 0;
    self->gravity = 0;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    self->unk6++;
    func_8001540C(2, SATURN_SOUND(0xD3, 0x95), self);
    is_on_screen(BASE_OBJECT(self));
}

void colonel_retreat_vanish_again(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->on_screen = 0;
        self->unk7C = 0x20;
        self->unk6++;
    } else {
        self->x_speed += self->x_accel;
        if (SHAKE_ENABLED) {
            if (BLINK_CLOCK(self->unk7C) & 1) {
                self->x_pos.val += self->x_speed;
            } else {
                self->x_pos.val -= self->x_speed;
            }
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

void colonel_retreat_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        player_end_script_action();
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = 0;
        engine_obj.unkF = 1;
    }
}

void colonel_start_fight(struct MainObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
    self->unk7 = 0;
}

void colonel_intro(struct MainObj* self)
{
    colonel_intro_funcs[self->unk6](self);
}

void colonel_intro_port(struct MainObj* self)
{
    colonel_intro_port_funcs[self->unk7](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

// colonel_intro_port_appear
void func_80086C00(struct MainObj* self)
{
    struct VisualObj* visual_obj;

    visual_obj = find_free_visual_obj();
    if (visual_obj != NULL) {
        visual_obj->active = 0x41;
        visual_obj->id = 0x1E;
        visual_obj->unk2 = 0;
        visual_obj->unk50 = PLAYER_OBJECT(self);
        self->unk7C = 0x10;
        self->ext.main_69.linked_object = visual_obj;
        self->unk7++;
        func_8001540C(2, SATURN_SOUND(0xD7, 0x99), self);
    }
}

void colonel_intro_port_flash(struct PlayerObj* self)
{
    s16 timer;
    struct VisualObj* visual_obj;

    timer = (s16)self->input.buttons.held;
    if (timer == 0) {
        visual_obj = find_free_visual_obj();
        if (visual_obj != NULL) {
            visual_obj->active = 0x41;
            visual_obj->id = 0x1E;
            visual_obj->unk2 = 0x10;
            visual_obj->unk50 = self;
            visual_obj->unk54 = 0x20;
            self->input.buttons.held = 0x20;
            set_animation(self, 0x16);
            self->unk7 = (u8)self->unk7 + 1;
        }
    } else {
        self->input.buttons.held = timer - 1;
    }
}

void colonel_intro_port_blink_in(struct MainObj* self)
{
    if (FLICKER_ENABLED) {
        self->on_screen ^= 1;
    }
    if (self->on_screen != 0) {
        is_on_screen(BASE_OBJECT(self));
    }
    if (--self->unk7C == 0) {
        self->ext.main_69.linked_object->unk5C.value = 1;
        engine_obj.enable_boss = 1;
        self->unk7++;
    }
}

void colonel_intro_port_pose(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_8001540C(2, SATURN_SOUND(0xD5, 0x97), self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 0);
        if (engine_obj.cur_character == 0) {
            func_8002217C(0x25, 0xFFU, (u8)engine_obj.character_state.bytes[8]);
        } else {
            func_8002217C(0x1E, 0xFFU, (u8)engine_obj.character_state.bytes[8]);
        }
        engine_obj.character_state.bytes[8] = 1;
        self->unk7++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_intro_port_voice(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk7E = 3;
        self->unk7++;
        play_boss_voice(8);
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_intro_port_fill_health(struct MainObj* self)
{

    if (update_boss_music_delay() == 0) {
        if (--self->unk7E == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), NULL);
            self->unk7E = 3;
        }
        if (++self->hp == 0x30) {
            func_800889DC(self);
            self->unk5 = 3;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7E = 0;
            player_end_script_action();
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_intro_hall(struct MainObj* self)
{
    colonel_intro_hall_funcs[self->unk7](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

void colonel_intro_hall_wait_player(struct MainObj* self)
{
    s16 object_x;

    object_x = self->x_pos.i.hi;
    if (ABS(g_Player.x_pos.i.hi, object_x) <= 0xB0) {
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        background_objects[0].unk24 = 0x2C0;
        background_objects[0].unk26 = 0x2A0;
        self->unk7C = 0x78;
        self->unk7++;
    }
}

void colonel_intro_hall_portrait_player(struct MainObj* self)
{
    struct QuadObj* quad;

    if (--self->unk7C == 0) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 0xE;
            quad->unk2 = 0;
            quad->unk5C = PLAYER_OBJECT(self);
            self->unk7C = 0x3C;
            self->unk7++;
        }
    }
}

void colonel_intro_hall_dialogue(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_8002217C(0x22, 0xFF, (u8)engine_obj.character_state.bytes[8]);
        engine_obj.character_state.bytes[8] = 1;
        self->unk7++;
    }
}

void colonel_intro_hall_portrait_colonel(struct MainObj* self)
{
    struct QuadObj* quad;

    if (abc_object.unkC == 0) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 0xE;
            quad->unk2 = 1;
            quad->unk5C = PLAYER_OBJECT(self);
            self->unk7C = 0x3C;
            self->unk7++;
        }
    }
}

void colonel_intro_hall_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x30;
        set_animation(self, 2);
        self->unk7++;
    }
}

void colonel_intro_hall_blink_in(struct MainObj* self)
{
    if (--self->unk7C != 0) {
        if (self->on_screen ^= 1) {
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        set_animation(self, 1);
        engine_obj.enable_boss = 1;
        self->unk7++;
        play_boss_voice(8);
    }
}

void colonel_intro_hall_flash(struct MainObj* self)
{
    struct EffectObj* effect;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 2);
        self->unk7E = 3;
        self->unk7++;
        func_8002B560(2, 0xF);
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 0x41;
            effect->id = 3;
            effect->unk2 = 0;
            self->unk7C = 1;
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_intro_hall_effect(struct MainObj* self)
{
    struct EffectObj* effect;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 0x41;
            effect->id = 2;
            effect->unk2 = 0x10;
        }
        self->unk7++;
    }
}

void colonel_intro_hall_fill_health(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (update_boss_music_delay() == 0) {
        if (--self->unk7E == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), NULL);
            self->unk7E = 3;
        }
        if (++self->hp == 0x30) {
            func_800889DC(self);
            self->unk5 = 3;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7E = 0;
            player_end_script_action();
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_guard(struct MainObj* self)
{
    colonel_guard_funcs[self->unk6](self);
    colonel_face_player(self);
    is_on_screen((struct BaseObj*)self);
}

void colonel_guard_pick(struct MainObj* self)
{
    u8 value;

    if (*self->ext.main_69.script == 0xFF) {
        func_800889DC(self);
    }
    self->hurt_box = &D_801044FC;
    self->attack_box = &D_80104500;
    self->collision_data = (const u16*)D_80108084;
    self->ext.main_69.state.bytes.unk8D = 0;
    value = *self->ext.main_69.script;
    if (value == 3) {
        set_animation(self, 2);
        self->unk7C = 0x3C;
        self->unk6++;
    } else {
        self->unk5 = value;
        self->unk6 = 0;
    }
    self->ext.main_69.script++;
}

void colonel_guard_watch(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk7C--;
    if (self->unk7C <= 0) {
        self->unk6 = 0;
    } else if ((s8)colonel_shot_incoming(self)) {
        self->unk7C = 0x10;
        self->unk6++;
    }
}

void colonel_guard_block(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 9);
        self->collision_data = (const u16*)D_801060F0;
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void colonel_guard_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->collision_data = (const u16*)D_80108084;
        self->ext.main_69.state.bytes.unk8D = 0;
        self->unk6 = 0;
    }
}

void colonel_teleport_slash(struct MainObj* self)
{
    colonel_teleport_slash_funcs[self->unk6](self);
}

void colonel_teleport_slash_vanish(struct MainObj* self)
{
    set_animation(self, 6);
    self->unk7C = 0x20;
    self->x_speed = 0;
    self->x_accel = FIXED(1);
    self->y_speed = 0;
    self->gravity = 0;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    func_8001540C(2, SATURN_SOUND(0xD3, 0x95), self);
    self->unk6++;
}

void colonel_teleport_slash_shake(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->on_screen = 0;
        self->unk7C = 0x28;
        self->unk6++;
    } else {
        self->x_speed += self->x_accel;
        if (SHAKE_ENABLED) {
            if (BLINK_CLOCK(self->unk7C) & 1) {
                self->x_pos.val += self->x_speed;
            } else {
                self->x_pos.val -= self->x_speed;
            }
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

// colonel_teleport_slash_reappear
void func_800877A4(struct MainObj* arg0)
{
    s16 player_x;

    if (--arg0->unk7C != 0)
        return;
    player_x = g_Player.x_pos.i.hi;
    if (player_x < background_objects[0].x_pos.i.hi + 0xB0)
        arg0->x_pos.i.hi = player_x + 0x30;
    else
        arg0->x_pos.i.hi = player_x - 0x30;
    colonel_face_player(arg0);
    set_animation(arg0, 5);
    func_8001540C(2, SATURN_SOUND(0xD4, 0x96), arg0);
    arg0->hurt_box = &D_80104508;
    arg0->attack_box = &D_80104504;
    arg0->unk7C = 0x1E;
    arg0->unk6++;
}

void colonel_teleport_slash_swing(struct MainObj* self)
{
    struct ShotObj* shot_obj;

    if (self->animation_step.fields.relative_step == 0) {
        if (--self->unk7C == 0) {
            self->hurt_box = &D_80104508;
            self->attack_box = &D_80104504;
            self->unk5 = 3;
            self->unk6 = 0;
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            shot_obj = find_free_shot_obj();
            if (shot_obj != 0) {
                shot_obj->active = 0x41;
                shot_obj->id = 0x2D;
                shot_obj->unk2 = 0x40;
                shot_obj->unk7C = WEAPON_OBJECT(self);
                shot_obj->unk8C.object = OBJECT_HEADER(self);
            }
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_dash(struct MainObj* self)
{
    colonel_dash_funcs[self->unk6](self);
    CollisionRelated((struct PlayerObj*)self);
    is_on_screen((struct BaseObj*)self);
}

void colonel_dash_start(struct MainObj* self)
{
    colonel_face_center(BASE_OBJECT(self));
    self->x_speed = 0;
    self->x_accel = FIXED(-0.1875);
    self->y_speed = 0;
    self->gravity = 0;
    self->unk7C = 0x1E;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    self->unk4B = 1;
    set_animation(self, 6);
    func_8001540C(2, SATURN_SOUND(0xD2, 0x94), self);
    self->unk6++;
}

// colonel_dash_run
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80087A00(struct MainObj* arg0)
{
    s32 speed;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 != 0) {
        if (arg0->x_speed <= 0x41FFF)
            arg0->x_speed = 0x42000;
    } else if (arg0->x_speed > -0x42000) {
        arg0->x_speed = -0x42000;
    }
    if (arg0->unk15 != 0) {
        if (arg0->x_pos.i.hi < (s16)background_objects[0].unk1E + 0x110)
            return;
        speed = 0x42000;
    } else {
        if ((s16)background_objects[0].unk1E + 0x50 < arg0->x_pos.i.hi)
            return;
        speed = -0x42000;
    }
    arg0->x_speed = speed;
    arg0->x_accel = -0x3000;
    arg0->unk4B = -1;
    set_animation(arg0, 2);
    arg0->unk6++;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_80087A00);
#endif

void colonel_dash_brake(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->unk15 != 0) {
        if (self->x_speed < 0) {
            self->x_speed = 0;
        }
    } else if (self->x_speed > 0) {
        self->x_speed = 0;
    }
    if (self->x_speed == 0) {
        self->hurt_box = (const u8*)&D_801044FC;
        self->attack_box = (const u8*)&D_80104500;
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void colonel_saber_waves(struct MainObj* self)
{
    colonel_saber_waves_funcs[self->unk6](self);
    is_on_screen((struct BaseObj*)self);
}

void colonel_saber_waves_start(struct MainObj* self)
{
    set_animation(self, 4);
    func_8001540C(2, SATURN_SOUND(0xDA, 0x9C), self);
    self->hurt_box = (const u8*)&D_80104508;
    self->attack_box = (const u8*)&D_80104504;
    if (self->ext.main_69.state.bytes.variant == 0) {
        self->ext.main_69.state.bytes.wave_delay = 0x14;
    } else {
        self->ext.main_69.state.bytes.wave_delay = 0x28;
    }
    self->unk7C = self->ext.main_69.state.bytes.wave_delay;
    self->unk6++;
}

void colonel_saber_waves_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.relative_step == 0) {
        if (--self->unk7C == 0) {
            set_animation(self, 5);
            func_8001540C(2, SATURN_SOUND(0xDA, 0x9C), self);
            self->unk7C = (s8)self->ext.main_69.state.bytes.wave_delay;
            self->unk6++;
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x2D;
                shot->unk2 = 0;
                shot->unk7C = WEAPON_OBJECT(self);
                shot->unk8C.object = OBJECT_HEADER(self);
            }
        }
    }
}

void colonel_saber_waves_fire_high(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.relative_step == 0) {
        if (--self->unk7C == 0) {
            set_animation(ANIMATED_OBJECT(self), 4);
            func_8001540C(2, SATURN_SOUND(0xDA, 0x9C), self);
            self->unk7C = self->ext.main_69.state.bytes.wave_delay;
            self->unk6++;
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x2D;
                shot->unk2 = 1;
                shot->unk7C = WEAPON_OBJECT(self);
                shot->unk8C.object = OBJECT_HEADER(self);
            }
        }
    }
}

void colonel_saber_waves_fire_last(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.relative_step == 0) {
        if (--self->unk7C == 0) {
            self->hurt_box = &D_801044FC;
            self->attack_box = &D_80104500;
            set_animation(self, 0x17);
            self->unk7C = 0x28;
            self->unk6++;
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x2D;
                shot->unk2 = 0;
                shot->unk7C = WEAPON_OBJECT(self);
                shot->unk8C.object = OBJECT_HEADER(self);
            }
        }
    }
}

void colonel_saber_waves_recover(struct MainObj* self)
{
    self->unk7C--;
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 2);
        self->unk6++;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void colonel_saber_waves_wait(struct MainObj* self)
{

    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void colonel_flash_strike(struct MainObj* self)
{
    colonel_flash_strike_funcs[self->unk6](self);
}

void colonel_flash_strike_vanish(struct MainObj* self)
{
    set_animation(self, 6);
    func_8001540C(2, SATURN_SOUND(0xD3, 0x95), self);
    self->unk7C = 0x20;
    self->x_speed = 0;
    self->x_accel = FIXED(1);
    self->y_speed = 0;
    self->gravity = 0;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    self->unk6++;
}

void colonel_flash_strike_shake(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->on_screen = 0;
        self->unk7C = 0x28;
        self->unk6++;
    } else {
        self->x_speed += self->x_accel;
        if (SHAKE_ENABLED) {
            if (BLINK_CLOCK(self->unk7C) & 1) {
                self->x_pos.val += self->x_speed;
            } else {
                self->x_pos.val -= self->x_speed;
            }
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

void colonel_flash_strike_reappear(struct MainObj* self)
{
    s16 timer;

    timer = --self->unk7C;
    if ((timer << 0x10) == 0) {
        self->x_pos.i.hi = (s16)(background_objects[0].unk1E + 0xA0);
        self->unk7C = 0x14;
        self->x_speed = FIXED(32);
        self->x_accel = (s32)0xFFFF0000;
        func_8001540C(2, SATURN_SOUND(0xD3, 0x95), self);
        self->unk6++;
    }
}

void colonel_flash_strike_slide(struct MainObj* self)
{
    self->unk7C = self->unk7C - 1;
    if ((self->unk7C << 0x10) == 0) {
        self->hurt_box = &D_801044FC;
        self->attack_box = &D_80104500;
        set_animation(self, 7);
        self->unk6 = (u8)self->unk6 + 1;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        self->x_speed += self->x_accel;
        if (SHAKE_ENABLED) {
            if (BLINK_CLOCK(self->unk7C) & 1) {
                self->x_pos.val += self->x_speed;
            } else {
                self->x_pos.val -= self->x_speed;
            }
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

// colonel_flash_strike_strike
void func_800881F8(struct MainObj* self)
{
    struct VisualObj* visual;
    struct EffectObj* effect;

    if (self->animation_step.fields.event == 1) {
        func_8001540C(2, SATURN_SOUND(0xD5, 0x97), self);
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x1E;
            visual->unk2 = 0;
            visual->unk50 = PLAYER_OBJECT(self);
            self->unk7C = 0x30;
            self->ext.main_69.linked_object = visual;
        }
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x1E;
            visual->unk2 = 0x20;
            visual->unk50 = PLAYER_OBJECT(self);
        }
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x1E;
            visual->unk2 = 0x10;
            visual->unk54 = 0x50;
            visual->unk50 = PLAYER_OBJECT(self);
        }
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 0x41;
            effect->id = 0x25;
            effect->unk2 = 0x10;
            effect->ext.effect_37.unk1E = 8;
            effect->ext.effect_37.unk1F = 2;
            effect->ext.effect_37.unk20 = 3;
            effect->ext.effect_37.unk21 = 6;
        }
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_flash_strike_flash(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->ext.main_69.linked_object->unk5C.value = 1;
        func_8002B560(0x25, 0x10);
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        func_8001540C(2, SATURN_SOUND(0xD6, 0x98), self);
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

// colonel_flash_strike_hold
void func_800883CC(struct MainObj* self)
{
    struct ShotObj* shot;
    struct VisualObj* visual;
    u8 i;

    if (self->animation_step.fields.relative_step == 0) {
        for (i = 0; i < 2; i++) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x2D;
                shot->unk2 = i + 0x10;
                shot->unk7C = WEAPON_OBJECT(self);
                shot->unk8C.object = OBJECT_HEADER(self);
            }
            func_8001540C(2, SATURN_SOUND(0xD7, 0x99), self);
        }
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x1E;
            visual->unk2 = 0x30;
            visual->unk50 = PLAYER_OBJECT(self);
        }
        start_screen_shake_y(0x10, 2, 1);
        self->unk7C = 0x50;
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_flash_strike_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 8);
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_flash_strike_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 2);
        self->unk5 = 3;
        self->unk6 = 0;
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_jump_slam(struct MainObj* self)
{
    colonel_jump_slam_funcs[self->unk6](self);
    CollisionRelated((struct PlayerObj*)self);
    is_on_screen((struct BaseObj*)self);
}

void colonel_jump_slam_jump(struct MainObj* self)
{
    self->x_speed = 0;
    self->y_speed = FIXED(6.5);
    self->x_accel = 0;
    self->gravity = FIXED(0.2578125);
    set_animation(self, 3);
    func_8001540C(2, SATURN_SOUND(0xD0, 0x92), self);
    self->hurt_box = (const u8*)&D_80104510;
    self->attack_box = (const u8*)&D_8010450C;
    self->unk6++;
}

void colonel_jump_slam_rise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        self->unk6++;
    }
}

void colonel_jump_slam_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->air_state = 1;
        self->unk7C = 0;
        self->unk6++;
    }
}

void colonel_jump_slam_drop(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk7C == 0) {
        move_with_gravity(ANIMATED_OBJECT(self));
    } else {
        self->unk7C--;
    }

    if (self->air_state == 1 && self->y_speed < 0) {
        self->air_state = -1;
        self->unk7C = 0x10;
        func_8001540C(2, SATURN_SOUND(0xD8, 0x9A), self);
    }

    if (self->air_state == -1 && (self->collision_flags & 8)) {
        func_8001540C(2, SATURN_SOUND(0xD1, 0x93), self);
        set_animation(self, 4);
        start_screen_shake_y(0x18, 2, 1);
        self->air_state = 0;
        self->unk6++;
    }
}

void colonel_jump_slam_shockwave(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_8001540C(2, SATURN_SOUND(0xD5, 0x97), self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x2D;
            shot->unk2 = 0x50;
            shot->timer = 1;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk8C.object = OBJECT_HEADER(self);
        }
        func_8001540C(2, SATURN_SOUND(0xD9, 0x9B), self);
        self->unk7C = 0x50;
        self->unk6++;
    }
}

void colonel_jump_slam_recover(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->hurt_box = (const u8*)&D_801044FC;
        self->attack_box = (const u8*)&D_80104500;
    }
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", colonel_shot_incoming);
#else
ret_u8 colonel_shot_incoming(struct MainObj* self)
{
    volatile struct WeaponObj* weapon;
    u8 i;
    s32 x_diff;

    i = 0;
    weapon = weapon_objects;
    do {
        if (weapon_objects->active != 0 && weapon->unk50 != 0) {
            x_diff = (u16)weapon->x_pos.i.hi - (u16)self->x_pos.i.hi;
            if (self->unk15 == 0) {
                if ((s32)((u32)x_diff << 16) <= 0 && weapon->x_vel.val >= 0) {
                    return 1;
                }
            } else if ((s32)((u32)x_diff << 16) >= 0 && weapon->x_vel.val < 1) {
                return 1;
            }
        }
        i += 1;
    } while ((u32)(i & 0xFF) < 0x10U);

    return 0;
}
#endif

void colonel_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

void colonel_face_center(struct BaseObj* self)
{
    s16 right_edge = background_objects[0].x_pos.i.hi + 0xB0;

    if (self->x_pos.i.hi < right_edge) {
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk15 = 0;
    }
}

// colonel_pick_script
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800889DC(struct MainObj* arg0)
{
    struct Main69Ext* ext = &arg0->ext.main_69;
    u8 roll = get_random() & 0xF;
    u8 level;
    u8** scripts;
    u8 i;

    if (ext->state.bytes.variant == 1) {
        ext->script = roll < 10 ? D_801044A0 : D_801044A8;
        return;
    }
    level = (arg0->hp - 1) / 24;
    scripts = D_801044EC[level];
    for (i = 0; i < 2; i++) {
        if (roll < D_801044F4[level * 2 + i]) {
            ext->script = scripts[i];
            return;
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_800889DC);
#endif

void colonel_spawn_afterimages(struct MainObj* self)
{
    u8 i;
    struct VisualObj* visual_obj;
    struct VisualObj* previous;

    for (i = 0; i < 3; i++) {
        visual_obj = func_8002AF4C(NULL, 1);
        if (visual_obj != NULL) {
            visual_obj->active = 0x41;
            visual_obj->id = 5;
            visual_obj->unk2 = i;
            visual_obj->bg_offset = g_Player.bg_offset;
            visual_obj->unk40 = self->unk40;
            visual_obj->unk3C = (void*)self->sprite_frames;
            visual_obj->animation_table = (u32**)self->animation_table;
            visual_obj->unk42 = self->unk42;
            visual_obj->unk16 = VISUAL_SATURN_LAYER(6);
            visual_obj->unk5C.owner = PLAYER_OBJECT(self);
            if (i != 0) {
                visual_obj->unk50 = PLAYER_OBJECT(previous);
            } else {
                visual_obj->unk50 = PLAYER_OBJECT(self);
            }
        }
        previous = visual_obj;
    }
}

u8 D_801044A0[8] = { 3, 6, 4, 5, 255, 0, 0, 0 };

u8 D_801044A8[8] = { 3, 4, 4, 5, 255, 0, 0, 0 };

u8 D_801044B0[8] = { 3, 6, 4, 5, 7, 5, 255, 0 };

u8 D_801044B8[8] = { 3, 6, 4, 5, 255, 0, 0, 0 };

u8 D_801044C0[8] = { 3, 6, 7, 5, 8, 255, 0, 0 };

u8 D_801044C8[8] = { 3, 4, 4, 5, 7, 5, 255, 0 };

u8* D_801044D0[2] = {
    D_801044A0,
    D_801044A8,
};

u8* D_801044D8[2] = {
    D_801044B0,
    D_801044B8,
};

void* D_801044E0[3] = {
    D_801044C0,
    D_801044C8,
    D_801044D0,
};

void* D_801044EC[2] = {
    D_801044E0,
    D_801044D8,
};

u8 D_801044F4[4] = { 0x07, 0x10, 0x09, 0x10 };

struct Unk_unk68 D_801044F8 = { -1, -2, 16, 30 };

struct Unk_unk68 D_801044FC = { -12, -38, 28, 66 };

struct Unk_unk68 D_80104500 = { -4, -30, 14, 58 };

struct Unk_unk68 D_80104504 = { -22, -13, 40, 43 };

struct Unk_unk68 D_80104508 = { -29, -22, 47, 52 };

struct Unk_unk68 D_8010450C = { -22, -13, 40, 43 };

struct Unk_unk68 D_80104510 = { -29, -22, 47, 52 };

union AnimationStep D_80104514[] = {
    { 24, 0, 0, 0x00 },
};

union AnimationStep D_80104518[] = {
    { 2, 0, 1, 0x01 },
    { 10, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 4, 0, 1, 0x05 },
    { 4, 0, 1, 0x06 },
    { 4, 0, 1, 0x07 },
    { 4, 0, 1, 0x08 },
    { 6, 0, 1, 0x09 },
    { 3, 0, 1, 0x0A },
    { 2, 0, 0, 0x0B },
};

struct Unk_unk68 D_80104544[3] = {
    { 1, 0, 1, 12 },
    { 1, 0, 1, 13 },
    { 1, 0, -2, 14 },
};

struct Unk_unk68 D_80104550[6] = {
    { 3, 0, 1, 15 },
    { 5, 0, 1, 16 },
    { 1, 1, 1, 16 },
    { 1, 0, 1, 17 },
    { 1, 0, 1, 18 },
    { 1, 0, -2, 19 },
};

union AnimationStep D_80104568[] = {
    { 6, 0, 1, 0x14 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 1, 1, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 4, 0, 0, 0x19 },
};

union AnimationStep D_80104580[] = {
    { 6, 0, 1, 0x1A },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 1, 1, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 3, 0, 1, 0x1F },
    { 1, 0, 0, 0x1F },
};

struct Unk_unk68 D_8010459C[4] = {
    { 4, 0, 1, 32 },
    { 2, 0, 1, 33 },
    { 2, 0, 1, 34 },
    { 2, 0, -3, 35 },
};

union AnimationStep D_801045AC[] = {
    { 2, 0, 1, 0x24 },
    { 10, 0, 1, 0x25 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 3, 0, 1, 0x28 },
    { 1, 1, 1, 0x28 },
    { 4, 0, 1, 0x29 },
    { 4, 0, 1, 0x2A },
    { 4, 0, 1, 0x2B },
    { 6, 0, 1, 0x2C },
    { 3, 0, 1, 0x2D },
    { 2, 0, 1, 0x2E },
    { 3, 0, 1, 0x2F },
    { 12, 0, 1, 0x30 },
    { 2, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 8, 0, 0, 0x33 },
};

union AnimationStep D_801045F0[] = {
    { 3, 0, 1, 0x2F },
    { 12, 0, 0, 0x30 },
};

union AnimationStep D_801045F8[] = {
    { 2, 0, 1, 0x34 },
    { 12, 0, 0, 0x35 },
};

union AnimationStep D_80104600[] = {
    { 24, 0, 0, 0x36 },
};

union AnimationStep D_80104604[] = {
    { 2, 0, 1, 0x3D },
    { 1, 1, 1, 0x3E },
    { 1, 0, 1, 0x3E },
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x3E },
    { 2, 0, 0, 0x3D },
};

union AnimationStep D_80104624[] = {
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x3E },
    { 1, 1, 1, 0x37 },
    { 1, 0, 1, 0x37 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x3E },
    { 2, 0, 0, 0x3D },
};

union AnimationStep D_8010464C[] = {
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x3E },
    { 2, 0, 1, 0x37 },
    { 1, 1, 1, 0x38 },
    { 1, 0, 1, 0x38 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x3B },
    { 2, 0, 1, 0x3C },
    { 2, 0, 1, 0x3B },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x3E },
    { 2, 0, 0, 0x3D },
};

struct Unk_unk68 D_8010468C[3] = {
    { 2, 0, 1, 64 },
    { 2, 0, 1, 65 },
    { 2, 0, -2, 66 },
};

struct Unk_unk68 D_80104698[4] = {
    { 1, 0, 1, 67 },
    { 1, 0, 1, 68 },
    { 1, 0, 1, 69 },
    { 1, 0, -3, 70 },
};

struct Unk_unk68 D_801046A8[4] = {
    { 1, 0, 1, 71 },
    { 1, 0, 1, 72 },
    { 1, 0, 1, 73 },
    { 1, 0, -3, 74 },
};

struct Unk_unk68 D_801046B8[8] = {
    { 1, 0, 1, 75 },
    { 1, 0, 1, 76 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 1, 0, 1, 79 },
    { 1, 0, 1, 80 },
    { 1, 0, 1, 81 },
    { 1, 0, -7, 82 },
};

struct Unk_unk68 D_801046D8[3] = {
    { 1, 0, 1, 83 },
    { 1, 0, 1, 84 },
    { 1, 0, -2, 85 },
};

u8 D_801046E4[8] = { 2, 0, 1, 86, 3, 0, 255, 87 };

struct Unk_unk68 D_801046EC[16] = {
    { 1, 0, 1, 88 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 89 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 90 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 91 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 92 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 93 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 94 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 95 },
    { 1, 0, -15, 100 },
};

struct Unk_unk68 D_8010472C[4] = {
    { 1, 0, 1, 96 },
    { 1, 0, 1, 97 },
    { 2, 0, 1, 98 },
    { 3, 0, -3, 99 },
};

union AnimationStep D_8010473C[] = {
    { 2, 0, 1, 0x04 },
    { 4, 0, 1, 0x05 },
    { 3, 0, 1, 0x06 },
    { 1, 1, 1, 0x06 },
    { 4, 0, 1, 0x07 },
    { 4, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 6, 0, 1, 0x0A },
    { 5, 0, 1, 0x0B },
    { 1, 0, 0, 0x0B },
};

union AnimationStep D_80104764[] = {
    { 3, 0, 1, 0x0F },
    { 6, 0, 0, 0x10 },
};

union AnimationStep D_8010476C[] = {
    { 3, 0, 0, 0x65 },
};

void* D_80104770[25] = {
    D_80104514,
    D_80104518,
    D_80104544,
    D_80104550,
    D_80104568,
    D_80104580,
    D_8010459C,
    D_801045AC,
    D_801045F0,
    D_801045F8,
    D_80104600,
    D_80104604,
    D_80104624,
    D_8010464C,
    D_8010468C,
    D_80104698,
    D_801046A8,
    D_801046B8,
    D_801046D8,
    D_801046E4,
    D_801046EC,
    D_8010472C,
    D_8010473C,
    D_80104764,
    D_8010476C,
};

void (*colonel_state_funcs[3])() = {
    colonel_spawn,
    func_80086124,
    colonel_death,
};

void (*colonel_spawn_funcs[2])(struct MainObj*) = {
    colonel_spawn_warning,
    func_80086008,
};

void (*colonel_step_funcs[9])() = {
    enemy_hit_reaction,
    colonel_start_fight,
    colonel_intro,
    colonel_guard,
    colonel_teleport_slash,
    colonel_dash,
    colonel_saber_waves,
    colonel_flash_strike,
    colonel_jump_slam,
};

void (*colonel_death_funcs[2])() = {
    colonel_defeat,
    colonel_retreat,
};

void (*colonel_defeat_funcs[7])() = {
    colonel_defeat_start,
    colonel_defeat_fall,
    colonel_defeat_next,
    colonel_defeat_dialogue,
    colonel_defeat_wait_dialogue,
    colonel_defeat_blink,
    colonel_defeat_wait_explosion,
};

void (*colonel_retreat_funcs[8])(struct MainObj*) = {
    colonel_retreat_start,
    colonel_retreat_vanish,
    func_80086860,
    colonel_retreat_reappear,
    colonel_retreat_wait_dialogue,
    colonel_retreat_start_again,
    colonel_retreat_vanish_again,
    colonel_retreat_finish,
};

void (*colonel_intro_funcs[2])() = {
    colonel_intro_port,
    colonel_intro_hall,
};

void (*colonel_intro_port_funcs[6])() = {
    func_80086C00,
    colonel_intro_port_flash,
    colonel_intro_port_blink_in,
    colonel_intro_port_pose,
    colonel_intro_port_voice,
    colonel_intro_port_fill_health,
};

void (*colonel_intro_hall_funcs[9])() = {
    colonel_intro_hall_wait_player,
    colonel_intro_hall_portrait_player,
    colonel_intro_hall_dialogue,
    colonel_intro_hall_portrait_colonel,
    colonel_intro_hall_wait,
    colonel_intro_hall_blink_in,
    colonel_intro_hall_flash,
    colonel_intro_hall_effect,
    colonel_intro_hall_fill_health,
};

void (*colonel_guard_funcs[4])(struct MainObj*) = {
    colonel_guard_pick,
    colonel_guard_watch,
    colonel_guard_block,
    colonel_guard_recover,
};

void (*colonel_teleport_slash_funcs[4])(struct MainObj*) = {
    colonel_teleport_slash_vanish,
    colonel_teleport_slash_shake,
    func_800877A4,
    colonel_teleport_slash_swing,
};

void (*colonel_dash_funcs[3])(struct MainObj*) = {
    colonel_dash_start,
    func_80087A00,
    colonel_dash_brake,
};

void (*colonel_saber_waves_funcs[6])(struct MainObj*) = {
    colonel_saber_waves_start,
    colonel_saber_waves_fire,
    colonel_saber_waves_fire_high,
    colonel_saber_waves_fire_last,
    colonel_saber_waves_recover,
    colonel_saber_waves_wait,
};

void (*colonel_flash_strike_funcs[9])(struct MainObj*) = {
    colonel_flash_strike_vanish,
    colonel_flash_strike_shake,
    colonel_flash_strike_reappear,
    colonel_flash_strike_slide,
    func_800881F8,
    colonel_flash_strike_flash,
    func_800883CC,
    colonel_flash_strike_wait,
    colonel_flash_strike_recover,
};

void (*colonel_jump_slam_funcs[6])(struct MainObj*) = {
    colonel_jump_slam_jump,
    colonel_jump_slam_rise,
    colonel_jump_slam_land,
    colonel_jump_slam_drop,
    colonel_jump_slam_shockwave,
    colonel_jump_slam_recover,
};
