// MainObj, main_object_update_funcs[56]
// 8006FD50..80072194
#include "common.h"

extern struct Unk_unk68 D_8010085C;
extern struct Unk_unk68 D_80100864;

extern void* jet_stingray_patterns[];
extern u8 jet_stingray_pattern_weights[];

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FD50);

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
        countdown = (u16)self->unk7C - 1;
        self->unk7C = countdown;
        if (countdown == 0) {
            self->unk6 = 0;
            self->unk5 = (u8)self->unk5 + 1;
            func_80015D60(self, 0x1D);
        }
        break;
    }
}

void jet_stingray_intro_emerge(struct MainObj* self)
{
    struct MainObj* obj;
    u8 counter;

    self->on_screen = 1;
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x1E;
        self->unk24 = FIXED(1);
        self->unk5 = (u8)self->unk5 + 1;
        func_80015D60(self, 0x26);
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = self;
        jet_stingray_bubble_index = 0;
        do {
            obj = func_8006FB20(self, jet_stingray_bubble_offsets[jet_stingray_bubble_index], 0x18);
            obj->unk24 = FIXED(0.875);
            counter = jet_stingray_bubble_index + 1;
            jet_stingray_bubble_index = counter;
        } while ((u32)(counter & 0xFF) < 3U);
        func_8001540C(2, 0xAD, self);
    }
}

void jet_stingray_intro_rise(struct MainObj* self)
{
    self->on_screen = 1;
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk24 = 0;
        self->unk5++;
        func_80015D60(self, 0x27);
    }
}

void jet_stingray_intro_pose(struct MainObj* self)
{
    self->on_screen = 1;
    if (self->unk6 == 0) {
        func_80015DC8(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            if (engine_obj.stage == 5) {
                ((void (*)(s32, s32, s32))func_8002217C)(
                    0xD, 0xFF, (s32)(s8)engine_obj.character_state.bytes[8]);
                engine_obj.character_state.bytes[8] = 1;
            }
            self->unk6 = (u8)self->unk6 + 1;
        }
    } else if (abc_object.unkC == 0) {
        self->unk6 = 0;
        self->unk7C = 2;
        self->unk5 = (u8)self->unk5 + 1;
        func_800921E8(4);
    }
}

void jet_stingray_intro_fill_health(struct MainObj* self)
{
    s16 temp_v0;

    self->on_screen = 1;
    func_80015DC8(ANIMATED_OBJECT(self));
    if ((func_8009227C() == 0) && (self->animation_step.fields.relative_step == 0)) {
        if (self->unk5C < 0x30) {
            temp_v0 = self->unk7C - 1;
            self->unk7C = temp_v0;
            if (temp_v0 == 0) {
                func_8001540C(0, 0xE, 0);
                self->unk7C = 2;
            }
            self->unk5C++;
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
        self->unk7 = 0;
        self->state++;
        func_80036B18();
    }
}

void jet_stingray_intro(struct MainObj* self)
{
    jet_stingray_intro_funcs[self->unk5](self);
    if (self->on_screen != 0) {
        is_on_screen(BASE_OBJECT(self));
    }
}

s32 jet_stingray_at_target(struct MainObj* self, s32 arg1, s32 arg2)
{
    s32 v1, v2;
    v1 = arg1 << 0x10;
    v2 = arg2 << 0x10;
    POS_BOUNDS_CHECK_FAIL_RET0(self->x_pos.val, v1)
    POS_BOUNDS_CHECK_FAIL_RET0(self->y_pos.val, v2)
    return 1;
}

void jet_stingray_choose_pattern(struct MainObj* self)
{
    u32 idx;
    u8** table;
    u8* weights;
    u8* base;
    u8 i;
    u32 rnd;
    u32 gr;

    idx = self->unk5C - 1;
    if ((s32)idx < 0)
        idx = self->unk5C + 0xE;
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

void jet_stingray_swim_start(struct MainObj* self)
{
    self->unk60 = 6;
    self->unk50 = (const u8*)&D_80100844;
    self->unk54 = (const u8*)&D_80100848;
    self->unk67 = 1;
    self->unk68 = NULL;
    self->unk70 = 0;
    self->unk6++;
    self->ext.main_56.flags &= ~2;
    func_80015D60(self, 1);
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070514);

void jet_stingray_swim_next(struct MainObj* self)
{
    u8 value;

    if (self->unk7C == 0) {
        if (self->ext.main_56.pattern == NULL) {
            jet_stingray_choose_pattern(self);
        } else if (*self->ext.main_56.pattern == 0xFF) {
            jet_stingray_choose_pattern(self);
        }
        value = *self->ext.main_56.pattern;
        self->unk6 = 0;
        self->unk7 = 0;
        self->ext.main_56.pattern++;
        self->unk5 = value;
    } else {
        self->unk7C--;
    }
}

void jet_stingray_swim(struct MainObj* self)
{
    jet_stingray_swim_funcs[self->unk6](self);
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));

    if (((jet_stingray_check_surface(PLAYER_OBJECT(self), 0, 0) & 0xFF) == 3) && !(self->ext.main_56.flags & 2)) {
        jet_stingray_spawn_splash(self);
        self->ext.main_56.flags |= 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070778);

void jet_stingray_vortex_start(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->unk7++;
        self->ext.main_56.vortex_result = 0;
        func_80015D60(self, 2);
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
        func_80015D60(self, 3);
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
        func_8001540C(2, 0xB0, self);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070A38);

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
    func_80015DC8(ANIMATED_OBJECT(self));
}

void jet_stingray_ambush_exit(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->unk60 = 9;
        self->unk50 = &D_8010085C;
        self->unk54 = &D_80100860;
        self->unk24 = FIXED(9);
        self->unk20 = 0;
        self->ext.main_56.flags &= 0xFC;
        self->unk7++;
        func_80015D60(self, 7);
        func_8001540C(2, 0xAF, self);
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
        self->unk24 = 0xFFF70000;
        self->unk50 = &D_80100864;
        self->ext.main_56.flags &= 0xFE;
        func_80015D60(self, 8);
        break;
    case 1:
        if (self->on_screen == 0)
            break;
        self->unk7++;
        func_8001540C(2, 0xAF, self);
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
            self->unk24 = 0x90000;
            self->unk50 = &D_8010085C;
            self->ext.main_56.flags &= 0xFE;
            func_80015D60(self, 7);
        }
        break;
    case 1:
        if (self->on_screen != 0) {
            self->unk7++;
            func_8001540C(2, 0xAF, self);
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
    s32 bg_idx;

    if (--self->unk7C != 0) {
        return;
    }
    bg_idx = self->bg_offset;
    self->unk5 = 2;
    self->unk6 = 0;
    self->unk7 = 0;
    if (self->x_pos.i.hi < background_objects[bg_idx].x_pos.i.hi + 0xA0) {
        self->x_pos.i.hi = background_objects[bg_idx].unk1E + 0x40;
    } else {
        self->x_pos.i.hi = background_objects[bg_idx].unk1E + 0x120;
    }
    self->y_pos.i.hi = background_objects[self->bg_offset].y_pos.u.hi - 0x50;
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800710D4);

void jet_stingray_dash_start(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->unk7++;
        self->unk60 = 9;
        self->unk68 = NULL;
        self->unk20 = 0;
        self->unk24 = 0;
        func_80015D60(self, 5);
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
        timer = (u16)self->unk7C - 1;
        self->unk7C = timer;
        x_velocity = FIXED(-6);
        if (timer == 0) {
            self->unk7 = (u8)self->unk7 + 1;
            if (self->unk15 != 0) {
                x_velocity = FIXED(6);
            }
            self->unk50 = &D_80100854;
            self->unk20 = x_velocity;
            self->unk54 = &D_80100858;
            func_80015D60(self, 6);
            func_8001540C(2, 0xAF, self);
        }
    } else if (self->on_screen == 0) {
        self->unk7C = 0x78;
        self->unk7 = 0;
        self->unk20 = 0;
        self->unk6 = (u8)self->unk6 + 1;
        self->y_pos.i.hi = background_objects[self->bg_offset].unk22 - 0x50;
    }
}

void jet_stingray_dash_return(struct MainObj* self)
{
    s32 bg_idx;

    if (--self->unk7C != 0) {
        return;
    }
    bg_idx = self->bg_offset;
    self->unk5 = 2;
    self->unk6 = 0;

    if (self->x_pos.i.hi < background_objects[bg_idx].x_pos.i.hi) {
        self->x_pos.i.hi = background_objects[bg_idx].unk1E + 0x40;
    } else {
        self->x_pos.i.hi = background_objects[bg_idx].unk1E + 0x120;
    }

    self->y_pos.i.hi = background_objects[self->bg_offset].y_pos.u.hi - 0x50;
}

void jet_stingray_dash(struct MainObj* self)
{
    jet_stingray_dash_funcs[self->unk6](self);
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
}

void jet_stingray_apply_leap(struct MainObj* self)
{
    self->x_pos.val += self->unk20;
    self->y_pos.val -= self->unk24;
    self->unk24 -= self->unk2C;
}

void jet_stingray_leap_start(struct MainObj* self)
{
    s32 value = -0x50000;

    self->unk60 = 7;
    self->unk50 = &D_80100868;
    self->unk54 = &D_8010086C;
    self->unk6++;

    if (self->unk15 != 0) {
        value = 0x50000;
    }

    self->unk24 = FIXED(-9.5);
    self->unk20 = value;
    self->unk28 = 0;
    self->unk2C = FIXED(-0.2578125);
    self->ext.main_56.flags &= 0xFD;

    func_80015D60(self, 4);
    func_8001540C(2, 0xAF, self);
}

void jet_stingray_leap_fall(struct MainObj* self)
{
    if (self->unk24 > 0) {
        self->unk2C = -FIXED(0.8125);
        self->unk24 = 0;
        self->unk6++;
        self->ext.main_56.flags &= ~2;
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
    s32 direction;
    s32 result;

    jet_stingray_leap_funcs[self->unk6](self);
    func_80015DC8(ANIMATED_OBJECT(self));
    jet_stingray_apply_leap(self);

    direction = -0x30;
    if (self->unk15 != 0) {
        direction = 0x30;
    }

    result = jet_stingray_check_surface(PLAYER_OBJECT(self), direction, 0);
    if ((result & 0xFF) == 3 && !(self->ext.main_56.flags & 2)) {
        jet_stingray_spawn_splash(self);
        self->ext.main_56.flags |= 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071740);

void jet_stingray_missiles_repeat(struct MainObj* self)
{
    if (self->unk7C == 0) {
        if (self->unk7E != 0) {
            self->unk6--;
            self->unk7E--;
        } else {
            self->unk6++;
            self->unk7 = 0;
            func_80015D60(self, 0xA);
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
        func_80015D90(ANIMATED_OBJECT(self), 1, 2);
    }
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
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
    func_8001540C(2, 0xB3, self);
    func_80015D60(self, 0x16);
}

void jet_stingray_stagger_wait(struct MainObj* self)
{
    if (self->unk7 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk7++;
            self->unk7C = 0x78;
        }
    } else if (--self->unk7C == 0) {
        self->unk7C = 0xA;
        self->unk7 = 0;
        self->ext.main_56.unk89.value = 5;
        self->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void jet_stingray_stagger_shake(struct MainObj* self)
{
    s16 timer;
    s8 step;

    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer != 0) {
        step = self->ext.main_56.unk89.value;
        self->x_pos.i.hi = self->x_pos.u.hi + step;
        self->ext.main_56.unk89.signed_value *= -1;
        return;
    }

    self->unk6++;
    func_80015D60(self, 0x17);
    func_8001540C(2, 0xCA, self);
    func_800C813C(6, D_80100D38, self);
}

void jet_stingray_stagger_flee(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk24 = FIXED(8);
        self->unk20 = 0;
        self->unk6++;
        func_80015D60(self, 7);
        func_8001540C(2, 0xAF, self);
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
    func_8002B718(MOVING_OBJECT(self));
}

void jet_stingray_stagger(struct MainObj* self)
{
    func_8002DD04(self);
    jet_stingray_stagger_funcs[self->unk6](self);
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    func_8002B318(BASE_OBJECT(self), 0x80, 0x80);
}

void jet_stingray_reset(struct MainObj* self)
{
    self->unk5 = 2;
    self->unk6 = 0;
    self->unk7 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071D30);

void jet_stingray_death_start(struct MainObj* self)
{
    func_80036AE4(0x14, g_Player.unk15);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_56.unk89.value = 0x19;
    self->unk5++;
    func_80015D90(ANIMATED_OBJECT(self), 0x16, 0);
    is_on_screen(BASE_OBJECT(self));
}

void jet_stingray_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 var_a0;

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
        self->ext.main_56.unk89.value -= 5;
        var_a0 = self->ext.main_56.unk89.value;
        self->unk42 ^= 0x8000;
        if (var_a0 < 5) {
            var_a0 = 5;
        }
        self->unk7E = var_a0;
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
