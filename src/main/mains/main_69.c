// MainObj, main_object_update_funcs[69]
// 80085F08..80088BA0
#include "common.h"

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
        func_80036AE4(0x15, 0);
    }
    self->unk5++;
}

// colonel_init
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086008);

// colonel_run
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086124);

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
    func_80036AE4(0x14, facing);
    func_8002B560(0x25, 0x10);
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    need_palette_load |= 1;
    if (self->unk67 == 0) {
        func_80015D60(self, 0x18);
        self->unk6 += 3;
    } else {
        func_80015D60(self, 0xA);
        self->unk20 = self->unk15 ? FIXED(-3) : FIXED(3);
        self->unk28 = 0;
        self->unk24 = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk6++;
    }
    is_on_screen(self);
}

void colonel_defeat_fall(struct MainObj* self)
{
    u8 flags;

    func_8002B694(ANIMATED_OBJECT(self));
    flags = self->unk70;
    if (flags & 8) {
        func_8001540C(2, 0xD1, self);
        func_80015D60(self, 4);
        func_80028BAC(0x18, 2, 1);
        self->unk67 = 0;
        func_80015D60(self, 0x18);
        self->unk6++;
        return;
    }
    if (flags & 3) {
        self->unk20 = 0;
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
        self->unk61 = 0x19;
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
    self->unk61 -= 5;
    if (self->unk61 >= 0x1A)
        self->unk61 = 0;
    level = self->unk61;
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
        func_80036B18();
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
    func_80036AE4(0x15, 0);
    func_80015D60(self, 6);
    self->unk7C = 0x20;
    self->unk20 = 0;
    self->unk28 = FIXED(1);
    self->unk24 = 0;
    self->unk2C = 0;
    self->unk54 = NULL;
    self->unk50 = NULL;
    self->unk6++;
    func_8001540C(2, 0xD3, self);
    is_on_screen(BASE_OBJECT(self));
}

void colonel_retreat_vanish(struct MainObj* self)
{
    func_80015DC8((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->on_screen = 0;
        self->unk7C = 0x20;
        self->unk6++;
    } else {
        self->unk20 += self->unk28;
        if (self->unk7C & 1) {
            self->x_pos.val += self->unk20;
        } else {
            self->x_pos.val -= self->unk20;
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

// colonel_retreat_wait
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086860);

void colonel_retreat_reappear(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_80015D60(self, 0x18);
        colonel_face_player(self);
        func_8002217C(0x23, 3, 0);
        self->unk6++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
        self->unk20 += self->unk28;
        if (self->unk7C & 1) {
            self->x_pos.val += self->unk20;
        } else {
            self->x_pos.val -= self->unk20;
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
    func_80015D60(self, 6);
    self->unk7C = 0x20;
    self->unk20 = 0;
    self->unk28 = FIXED(1);
    self->unk24 = 0;
    self->unk2C = 0;
    self->unk54 = NULL;
    self->unk50 = NULL;
    self->unk6++;
    func_8001540C(2, 0xD3, self);
    is_on_screen(BASE_OBJECT(self));
}

void colonel_retreat_vanish_again(struct MainObj* self)
{
    func_80015DC8((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->on_screen = 0;
        self->unk7C = 0x20;
        self->unk6++;
    } else {
        self->unk20 += self->unk28;
        if (self->unk7C & 1) {
            self->x_pos.val += self->unk20;
        } else {
            self->x_pos.val -= self->unk20;
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

void colonel_retreat_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_80036B18();
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
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80086C00);

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
            func_80015D60(self, 0x16);
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

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_8001540C(2, 0xD5, self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 0);
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
        func_800921E8(8);
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_intro_port_fill_health(struct MainObj* self)
{
    s16 timer;

    if (func_8009227C() == 0) {
        timer = self->unk7E - 1;
        self->unk7E = timer;
        if (timer == 0) {
            func_8001540C(0, 0xE, NULL);
            self->unk7E = 3;
        }
        if (++self->unk5C == 0x30) {
            func_800889DC(self);
            self->unk5 = 3;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7E = 0;
            func_80036B18();
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
                     : ((object_x - g_Player.x_pos.i.hi) < 0xB1)) {
        func_80036AE4(0x14, 0x40);
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
        func_80015D60(self, 2);
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
        func_80015D60(self, 1);
        engine_obj.enable_boss = 1;
        self->unk7++;
        func_800921E8(8);
    }
}

void colonel_intro_hall_flash(struct MainObj* self)
{
    struct EffectObj* effect;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 2);
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

    func_80015DC8(ANIMATED_OBJECT(self));
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
    func_80015DC8(ANIMATED_OBJECT(self));
    if (func_8009227C() == 0) {
        if (--self->unk7E == 0) {
            func_8001540C(0, 0xE, NULL);
            self->unk7E = 3;
        }
        if (++self->unk5C == 0x30) {
            func_800889DC(self);
            self->unk5 = 3;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7E = 0;
            func_80036B18();
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
    self->unk54 = &D_801044FC;
    self->unk50 = &D_80104500;
    self->collision_data = (const u16*)D_80108084;
    self->ext.main_69.state.bytes.unk8D = 0;
    value = *self->ext.main_69.script;
    if (value == 3) {
        func_80015D60(self, 2);
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
    func_80015DC8(ANIMATED_OBJECT(self));
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
        func_80015D60(self, 9);
        self->collision_data = (const u16*)D_801060F0;
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void colonel_guard_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
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
    func_80015D60(self, 6);
    self->unk7C = 0x20;
    self->unk20 = 0;
    self->unk28 = FIXED(1);
    self->unk24 = 0;
    self->unk2C = 0;
    self->unk54 = NULL;
    self->unk50 = NULL;
    func_8001540C(2, 0xD3, self);
    self->unk6++;
}

void colonel_teleport_slash_shake(struct MainObj* self)
{
    func_80015DC8((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->on_screen = 0;
        self->unk7C = 0x28;
        self->unk6++;
    } else {
        self->unk20 += self->unk28;
        if (self->unk7C & 1) {
            self->x_pos.val += self->unk20;
        } else {
            self->x_pos.val -= self->unk20;
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

// colonel_teleport_slash_reappear
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800877A4);

void colonel_teleport_slash_swing(struct MainObj* self)
{
    struct ShotObj* shot_obj;
    s16 timer;

    if (self->animation_step.fields.relative_step == 0) {
        timer = self->unk7C - 1;
        self->unk7C = timer;
        if (timer == 0) {
            self->unk54 = &D_80104508;
            self->unk50 = &D_80104504;
            self->unk5 = 3;
            self->unk6 = 0;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
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
    self->unk28 = FIXED(-0.1875);
    self->unk7C = 0x1E;
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk2C = 0;
    self->unk54 = NULL;
    self->unk50 = NULL;
    self->unk4B = 1;
    func_80015D60(self, 6);
    func_8001540C(2, 0xD2, self);
    self->unk6++;
}

// colonel_dash_run
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_80087A00);

void colonel_dash_brake(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk15 != 0) {
        if (self->unk20 < 0) {
            self->unk20 = 0;
        }
    } else if (self->unk20 > 0) {
        self->unk20 = 0;
    }
    if (self->unk20 == 0) {
        self->unk54 = (const u8*)&D_801044FC;
        self->unk50 = (const u8*)&D_80104500;
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
    func_80015D60(self, 4);
    func_8001540C(2, 0xDA, self);
    self->unk54 = (const u8*)&D_80104508;
    self->unk50 = (const u8*)&D_80104504;
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
            func_80015D60(self, 5);
            func_8001540C(2, 0xDA, self);
            self->unk7C = (s8)self->ext.main_69.state.bytes.wave_delay;
            self->unk6++;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
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
            func_80015D60(ANIMATED_OBJECT(self), 4);
            func_8001540C(2, 0xDA, self);
            self->unk7C = self->ext.main_69.state.bytes.wave_delay;
            self->unk6++;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
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
    s16 timer;

    if (self->animation_step.fields.relative_step == 0) {
        timer = self->unk7C - 1;
        self->unk7C = timer;
        if (timer == 0) {
            self->unk54 = &D_801044FC;
            self->unk50 = &D_80104500;
            func_80015D60(self, 0x17);
            self->unk7C = 0x28;
            self->unk6++;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
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
        func_80015D60(self, 2);
        self->unk6++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void colonel_saber_waves_wait(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void colonel_flash_strike(struct MainObj* self)
{
    colonel_flash_strike_funcs[self->unk6](self);
}

void colonel_flash_strike_vanish(struct MainObj* self)
{
    func_80015D60(self, 6);
    func_8001540C(2, 0xD3, self);
    self->unk7C = 0x20;
    self->unk20 = 0;
    self->unk28 = FIXED(1);
    self->unk24 = 0;
    self->unk2C = 0;
    self->unk54 = NULL;
    self->unk50 = NULL;
    self->unk6++;
}

void colonel_flash_strike_shake(struct MainObj* self)
{
    func_80015DC8((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->on_screen = 0;
        self->unk7C = 0x28;
        self->unk6++;
    } else {
        self->unk20 += self->unk28;
        if (self->unk7C & 1) {
            self->x_pos.val += self->unk20;
        } else {
            self->x_pos.val -= self->unk20;
        }
        is_on_screen(BASE_OBJECT(self));
    }
}

void colonel_flash_strike_reappear(struct MainObj* self)
{
    s16 timer;
    u16 background;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 0x10) == 0) {
        background = background_objects[0].unk1E;
        self->unk7C = 0x14;
        self->unk20 = FIXED(32);
        self->unk28 = (s32)0xFFFF0000;
        self->x_pos.i.hi = (s16)(background + 0xA0);
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
        self->unk54 = &D_801044FC;
        self->unk50 = &D_80104500;
        func_80015D60(self, 7);
        self->unk6 = (u8)self->unk6 + 1;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
        delta = self->unk20 + self->unk28;
        self->unk20 = delta;
        if (self->unk7C & 1) {
            self->x_pos.val += delta;
        } else {
            self->x_pos.val -= delta;
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

// colonel_flash_strike_strike
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800881F8);

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
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800883CC);

void colonel_flash_strike_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_80015D60(self, 8);
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void colonel_flash_strike_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 2);
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
    self->unk24 = FIXED(6.5);
    self->unk20 = 0;
    self->unk28 = 0;
    self->unk2C = FIXED(0.2578125);
    func_80015D60(self, 3);
    func_8001540C(2, 0xD0, self);
    self->unk54 = (const u8*)&D_80104510;
    self->unk50 = (const u8*)&D_8010450C;
    self->unk6++;
}

void colonel_jump_slam_rise(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        self->unk6++;
    }
}

void colonel_jump_slam_land(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk67 = 1;
        self->unk7C = 0;
        self->unk6++;
    }
}

void colonel_jump_slam_drop(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk7C == 0) {
        func_8002B694(ANIMATED_OBJECT(self));
    } else {
        self->unk7C--;
    }

    if (self->unk67 == 1 && self->unk24 < 0) {
        self->unk67 = -1;
        self->unk7C = 0x10;
        func_8001540C(2, 0xD8, self);
    }

    if (self->unk67 == -1 && (self->unk70 & 8)) {
        func_8001540C(2, 0xD1, self);
        func_80015D60(self, 4);
        func_80028BAC(0x18, 2, 1);
        self->unk67 = 0;
        self->unk6++;
    }
}

void colonel_jump_slam_shockwave(struct MainObj* self)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
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
        self->unk54 = (const u8*)&D_801044FC;
        self->unk6 = 0;
        self->unk50 = (const u8*)&D_80104500;
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
INCLUDE_ASM("main/nonmatchings/mains/main_69", func_800889DC);

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
