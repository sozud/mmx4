// MainObj, main_object_update_funcs[69]
// 80085F08..80088BA0
#include "common.h"
#include "func_tables.h"

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
    u8 value;

    value = self->unk2;
    self->ext.main_69.state.bytes.variant = value;
    if (value != 1) {
        effect = find_free_effect_obj();
        if (effect == NULL) {
            return;
        }
        effect->active = 1;
        effect->id = 0x18;
        self->ext.main_69.effect = effect;
        player_start_script_action(0x15, 0);
    }
    self->unk5++;
}

// colonel_init
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_80086008);

// colonel_run
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_80086124);

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
    s32 facing;

    if (self->x_pos.i.hi > g_Player.x_pos.i.hi) {
        facing = 1;
    } else {
        facing = 0;
    }
    facing <<= 6;
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
        func_8001540C(2, 0xD1, self);
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
    s16 timer;
    s8 level;

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
    timer = self->unk7E;
    self->unk7E = timer - 1;
    if (timer != 0)
        return;
    self->unk42 ^= 0x8000;
    self->invincibility_timer -= 5;
    if (self->invincibility_timer > 0x19)
        self->invincibility_timer = 0;
    level = self->invincibility_timer;
    if (level < 5)
        level = 5;
    self->unk7E = level;
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
    func_8001540C(2, 0xD3, self);
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
        if (self->unk7C & 1) {
            self->x_pos.val += self->x_speed;
        } else {
            self->x_pos.val -= self->x_speed;
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

// colonel_retreat_wait
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_80086860);

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
        if (self->unk7C & 1) {
            self->x_pos.val += self->x_speed;
        } else {
            self->x_pos.val -= self->x_speed;
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
    func_8001540C(2, 0xD3, self);
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
        if (self->unk7C & 1) {
            self->x_pos.val += self->x_speed;
        } else {
            self->x_pos.val -= self->x_speed;
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
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_80086C00);

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
    self->on_screen ^= 1;
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
    u16 value;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_8001540C(2, 0xD5, self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 0);
        value = 0x1E;
        if (engine_obj.cur_character == 0) {
            value = 0x25;
        }
        func_8002217C(value, 0xFFU, engine_obj.character_state.bytes[8]);
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
            func_8001540C(0, 0xE, NULL);
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
    s32 delta;

    object_x = self->x_pos.i.hi;
    delta = g_Player.x_pos.i.hi - object_x;
    if ((delta >= 0) ? (delta < 0xB1)
                     : ((object_x - g_Player.x_pos.i.hi) <= 0xB0)) {
        player_start_script_action(0x14, 0x40);
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
        func_8002217C(0x22, 0xFF, engine_obj.character_state.bytes[8]);
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
            func_8001540C(0, 0xE, NULL);
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
    func_8001540C(2, 0xD3, self);
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
        if (self->unk7C & 1) {
            self->x_pos.val += self->x_speed;
        } else {
            self->x_pos.val -= self->x_speed;
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

// colonel_teleport_slash_reappear
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_800877A4);

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
    func_8001540C(2, 0xD2, self);
    self->unk6++;
}

// colonel_dash_run
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_80087A00);

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
    func_8001540C(2, 0xDA, self);
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
            func_8001540C(2, 0xDA, self);
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
            func_8001540C(2, 0xDA, self);
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
    func_8001540C(2, 0xD3, self);
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
        if (self->unk7C & 1) {
            self->x_pos.val += self->x_speed;
        } else {
            self->x_pos.val -= self->x_speed;
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
        func_8001540C(2, 0xD3, self);
        self->unk6++;
    }
}

void colonel_flash_strike_slide(struct MainObj* self)
{
    u16 timer;
    s32 delta;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 0x10) == 0) {
        self->hurt_box = &D_801044FC;
        self->attack_box = &D_80104500;
        set_animation(self, 7);
        self->unk6 = (u8)self->unk6 + 1;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        delta = self->x_speed + self->x_accel;
        self->x_speed = delta;
        if (self->unk7C & 1) {
            self->x_pos.val += delta;
        } else {
            self->x_pos.val -= delta;
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

// colonel_flash_strike_strike
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_800881F8);

void colonel_flash_strike_flash(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->ext.main_69.linked_object->unk5C.value = 1;
        func_8002B560(0x25, 0x10);
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        func_8001540C(2, 0xD6, self);
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

// colonel_flash_strike_hold
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_800883CC);

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
    func_8001540C(2, 0xD0, self);
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
        func_8001540C(2, 0xD8, self);
    }

    if (self->air_state == -1 && (self->collision_flags & 8)) {
        func_8001540C(2, 0xD1, self);
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
        func_8001540C(2, 0xD5, self);
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
        func_8001540C(2, 0xD9, self);
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

s32 colonel_shot_incoming(struct MainObj* self)
{
    volatile struct WeaponObj* weapon;
    s32 active;
    s32 i;
    s32 x_diff;

    i = 0;
    weapon = weapon_objects;
    active = weapon_objects->active;
    do {
        if (active != 0 && weapon->unk50 != 0) {
            x_diff = (u16)weapon->x_pos.i.hi - (u16)self->x_pos.i.hi;
            if (self->unk15 == 0) {
                if ((x_diff << 16) <= 0 && weapon->x_vel.val >= 0) {
                    return 1;
                }
            } else if ((x_diff << 16) >= 0 && weapon->x_vel.val <= 0) {
                return 1;
            }
        }
        i += 1;
    } while ((u32)(i & 0xFF) < 0x10U);

    return 0;
}

void colonel_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

void colonel_face_center(struct BaseObj* self)
{
    s16 right_edge = background_objects[0].x_pos.i.hi + 0xB0;

    if (self->x_pos.i.hi < right_edge) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
}

// colonel_pick_script
INCLUDE_ASM("main/nonmatchings/mains/main_69_colonel", func_800889DC);

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
            visual_obj->unk5C.owner = PLAYER_OBJECT(self);
            visual_obj->unk16 = 6;
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
    { 0x00000018 },
};

union AnimationStep D_80104518[] = {
    { 0x01010002 },
    { 0x0201000A },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010004 },
    { 0x06010004 },
    { 0x07010004 },
    { 0x08010004 },
    { 0x09010006 },
    { 0x0A010003 },
    { 0x0B000002 },
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
    { 0x14010006 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010101 },
    { 0x18010002 },
    { 0x19000004 },
};

union AnimationStep D_80104580[] = {
    { 0x1A010006 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010101 },
    { 0x1E010002 },
    { 0x1F010003 },
    { 0x1F000001 },
};

struct Unk_unk68 D_8010459C[4] = {
    { 4, 0, 1, 32 },
    { 2, 0, 1, 33 },
    { 2, 0, 1, 34 },
    { 2, 0, -3, 35 },
};

union AnimationStep D_801045AC[] = {
    { 0x24010002 },
    { 0x2501000A },
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010003 },
    { 0x28010101 },
    { 0x29010004 },
    { 0x2A010004 },
    { 0x2B010004 },
    { 0x2C010006 },
    { 0x2D010003 },
    { 0x2E010002 },
    { 0x2F010003 },
    { 0x3001000C },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33000008 },
};

union AnimationStep D_801045F0[] = {
    { 0x2F010003 },
    { 0x3000000C },
};

union AnimationStep D_801045F8[] = {
    { 0x34010002 },
    { 0x3500000C },
};

union AnimationStep D_80104600[] = {
    { 0x36000018 },
};

union AnimationStep D_80104604[] = {
    { 0x3D010002 },
    { 0x3E010101 },
    { 0x3E010001 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x37010002 },
    { 0x3E010002 },
    { 0x3D000002 },
};

union AnimationStep D_80104624[] = {
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x37010101 },
    { 0x37010001 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x38010002 },
    { 0x37010002 },
    { 0x3E010002 },
    { 0x3D000002 },
};

union AnimationStep D_8010464C[] = {
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x37010002 },
    { 0x38010101 },
    { 0x38010001 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3B010002 },
    { 0x3A010002 },
    { 0x39010002 },
    { 0x38010002 },
    { 0x37010002 },
    { 0x3E010002 },
    { 0x3D000002 },
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
    { 0x04010002 },
    { 0x05010004 },
    { 0x06010003 },
    { 0x06010101 },
    { 0x07010004 },
    { 0x08010004 },
    { 0x09010008 },
    { 0x0A010006 },
    { 0x0B010005 },
    { 0x0B000001 },
};

union AnimationStep D_80104764[] = {
    { 0x0F010003 },
    { 0x10000006 },
};

union AnimationStep D_8010476C[] = {
    { 0x65000003 },
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
