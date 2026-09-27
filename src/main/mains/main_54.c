// MainObj, main_object_update_funcs[54]
// 8006BB00..8006EB40
#include "common.h"

void slash_beast_update(struct MainObj* self)
{
    slash_beast_state_funcs[self->state](self);
    CollisionRelated(self);
    if (!(g_Player.unk5C & 0x7F)) {
        func_8006E920(self, 0x38);
    }
}

// slash_beast_init
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006BB70);

// slash_beast_run
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006BD1C);

void slash_beast_death(struct MainObj* self)
{
    slash_beast_death_funcs[self->unk5](self);
}

void slash_beast_death_start(struct MainObj* self)
{
    g_Player.unkBA = 0;
    func_80036AE4(0x14, g_Player.unk15);
    self->unk5 = 1;
    self->unk42 &= 0x7FFF;
    func_80015D60(self, 0x13);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_death_blink(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 delay;
    s8 next_delay;

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
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        delay = self->unk61 - 5;
        self->unk61 = delay;
        if (delay >= 0x1A) {
            self->unk61 = 0;
        }
        next_delay = self->unk61;
        if (self->unk61 < 5) {
            next_delay = 5;
        }
        self->unk7E = next_delay;
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
            func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
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
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->unk50 = &D_80100220;
        self->unk54 = &D_80100224;
    }
    if (self->animation_step.fields.event == 1) {
        if (self->unk15 != 0) {
            self->unk20 = FIXED(3);
        } else {
            self->unk20 = FIXED(-3);
        }
        self->unk28 = FIXED(-0.125);
        self->unk24 = FIXED(3);
        self->unk2C = FIXED(0.125);
        func_80015D60(self, 9);
        func_8001540C(2, 0x81, self);
        self->unk6 = 1;
    }
}

// slash_beast_crescent_slash
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C378);

void slash_beast_crescent_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        func_8001540C(2, 0x82, self);
        func_80015D60(self, 0xA);
        self->unk54 = (const u8*)D_801001FC;
        self->unk50 = (const u8*)D_801001F8;
        self->unk24 = 0;
        self->unk2C = 0;
        self->unk6 = 3;
    }
}

void slash_beast_crescent_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_80015D60(self, 0);
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
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C6AC);

void slash_beast_crouch(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->unk54 = (const u8*)&D_80100204;
        self->unk50 = (const u8*)&D_80100200;
        func_8001540C(2, 0x87, self);
    }
    if (--self->unk7C == 0) {
        self->unk54 = (const u8*)D_801001FC;
        self->unk50 = (const u8*)D_801001F8;
        self->unk6 = 0;
    }
}

void slash_beast_jump(struct MainObj* self)
{
    slash_beast_jump_funcs[self->unk6](self);
}

// slash_beast_jump_start
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CB50);

// slash_beast_jump_air
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CC3C);

void slash_beast_jump_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_80015D60(self, 0);
        slash_beast_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

// slash_beast_guard
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CDD4);

void slash_beast_dash(struct MainObj* self)
{
    slash_beast_dash_funcs[self->unk6](self);
}

void slash_beast_dash_windup(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_80015D60(self, 0xD);
        self->unk6 = 1;
    }
}

void slash_beast_dash_start(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk60 = 9;
        func_80015D60(self, 0xE);
        if (self->unk15 == 0) {
            self->unk20 = FIXED(-1);
        } else {
            self->unk20 = FIXED(1);
        }
        self->ext.main_54.claw_hitbox = 1;
        self->ext.main_54.afterimage_timer = 1;
        func_8001540C(2, 0x83, self);
        self->unk28 = FIXED(0.5);
        self->unk6 = 2;
    }
}

// slash_beast_dash_run
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CFB8);

// slash_beast_dash_crash
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D280);

void slash_beast_dash_turn(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk60 = 9;
        self->ext.main_54.claw_hitbox = 1;
        self->unk20 = -self->unk20;
        func_80015D60(self, 0xE);
        func_8001540C(2, 0x83, self);
        self->unk6 = 2;
    }
}

// slash_beast_pounce
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D3DC);

void slash_beast_grab(struct MainObj* self)
{
    slash_beast_grab_funcs[self->unk6](self);
}

void slash_beast_grab_check(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_80015D60(self, 6);
        self->unk16 = 6;
        self->unk60 = 6;
        self->unk54 = D_801001FC;
        self->unk50 = D_801001F8;
        self->unk5 = 4;
        self->unk62 = 0;
        self->ext.main_54.grab = 0;
        self->unk6 = 2;
    }
    if (g_Player.unkBA == 0) {
        return;
    }
    func_8001540C(2, 0x86, self);
    if (self->x_pos.i.hi - background_objects[0].x_pos.i.hi >= 0xA1) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
    g_Player.unk15 = self->unk15;
    g_Player.y_pos.i.hi = self->y_pos.i.hi - 8;
    if (self->unk15 == 0) {
        g_Player.x_pos.i.hi = self->x_pos.i.hi - 0x23;
        self->unk20 = FIXED(-6);
    } else {
        g_Player.x_pos.i.hi = self->x_pos.i.hi + 0x23;
        self->unk20 = FIXED(6);
    }
    func_80015D60(self, 5);
    self->unk16 = 1;
    self->unk7C = 0x30;
    self->unk6 = 1;
}

void slash_beast_grab_windup(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        func_80015D60(self, 7);
        self->unk6 = 2;
        self->ext.main_54.afterimage_timer = 1;
    }
}

// slash_beast_grab_drag
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D888);

void slash_beast_grab_throw(struct MainObj* self)
{
    g_Player.x_pos.i.hi = self->x_pos.u.hi;
    func_80028B68(0x1E, 8, 2);
    func_80015D60(self, 2);
    self->unk16 = 6;
    self->unk54 = &D_8010020C;
    self->unk50 = &D_80100208;
    self->unk28 = 0;
    if (self->unk15 != 0) {
        self->unk20 = FIXED(-3.244140625);
    } else {
        self->unk20 = FIXED(3.244140625);
    }
    self->unk2C = FIXED(0.21875);
    self->unk24 = FIXED(6.5625);
    func_8002B694(ANIMATED_OBJECT(self));
    func_8001540C(2, 0x81, self);
    self->unk5 = 4;
    self->unk6 = 1;
    self->unk62 = 0;
    self->unk60 = 9;
    self->ext.main_54.grab = 0;
    g_Player.unkBA = 0;
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

        func_80036AE4(0x14, 0x40);
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
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DD44);

void slash_beast_intro_leap(struct MainObj* self)
{
    s16 timer;

    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        background_objects[0].unk26 = 0x24C0;
        background_objects[0].unk24 = 0x24D0;
        background_objects[0].unk2A = 0xD0;
        background_objects[0].unk28 = 0xD0;
        func_80015D60(self, 0x16);
        self->unk2C = FIXED(0.125);
        self->unk24 = FIXED(7.5);
        self->unk20 = FIXED(1.875);
        self->unk7E = 0;
        func_8001540C(2, 0x81, self);
        self->unk6 = 4;
    }
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_intro_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->x_pos.i.hi - background_objects[0].x_pos.i.hi >= 0xE0) {
        self->unk20 = 0;
        self->unk2C = FIXED(1);
    }
    if (self->unk24 == 0) {
        self->unk68 = &D_8010024C;
        func_80015D60(self, 0x17);
    }
    if (self->unk24 < 0) {
        switch (self->unk7E) {
        case 0:
            if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi + self->unk68->unk0,
                    self->unk68->unk3 + (self->y_pos.i.hi + self->unk68->unk1) + 0x40)
                == 0x38) {
                if (engine_obj.stage == 8) {
                    func_800DABE4(8, 0x2580, 0x140);
                    func_8001540C(2, 0x80, self);
                    func_800C813C(4, D_801005B0, self);
                }
                self->unk7E = 1;
            }
            break;
        case 1:
            if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi + self->unk68->unk0,
                    self->unk68->unk3 + (self->y_pos.i.hi + self->unk68->unk1) + 0x10)
                == 0x38) {
                self->unk7E = 2;
                func_80015D60(self, 3);
                if (engine_obj.stage == 0xC) {
                    func_8001540C(2, 0x82, self);
                }
            }
            break;
        }
    }
    if (self->unk70 & 8) {
        func_80028BAC(0x10, 4, 2);
        self->ext.main_54.active = 1;
        self->unk6 = 5;
    }
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_intro_pose(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        if (engine_obj.stage == 8) {
            self->unk15 = 0;
            func_80015D60(self, 0x18);
            func_8002217C(0x10, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        self->unk6 = 6;
    }
}

void slash_beast_intro_wait_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        func_80015D60(self, 0x19);
        self->unk7E = 3;
        self->unk6 = 7;
        func_800921E8(7);
    }
}

void slash_beast_intro_fill_health(struct MainObj* self)
{
    if (func_8009227C() == 0) {
        if (engine_obj.stage == 8) {
            s16* background_object = &background_objects[0].unk26;

            if (*background_object != 0x24B0) {
                *background_object -= 1;
            }
        }

        if (--self->unk7E == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7E = 3;
        }

        if (++self->unk5C == 0x30) {
            self->ext.main_54.pattern_set = 0;
            self->ext.main_54.fight_started = 1;
            slash_beast_pick_pattern(self);
            self->unk5 = 3;
            self->unk6 = 0;
            self->ext.main_54.pattern--;
            func_80036B18();
        }
    }
}

void slash_beast_stagger(struct MainObj* self)
{
    slash_beast_stagger_funcs[self->unk6](self);
}

// slash_beast_stagger_start
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E450);

void slash_beast_stagger_land(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        func_8001540C(2, 0x88, self);
        self->unk20 = 0;
        self->unk24 = 0;
        self->unk2C = 0;
        func_80015D60(self, 0x12);
        self->unk6 = 2;
    }
}

void slash_beast_stagger_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        slash_beast_face_player(self);
        func_80015D60(self, 0xC);
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

void slash_beast_high_leap_jump(struct AnimatedObj* self)
{
    func_80015DC8(self);
    if (self->animation_step.fields.event != 0) {
        if (self->unk15 == 0) {
            self->x_vel.val = FIXED(-1.75);
        } else {
            self->x_vel.val = FIXED(1.75);
        }
        self->y_vel.val = FIXED(7.4375);
        self->unk28 = 0;
        self->unk2C = FIXED(0.21875);
        func_8002B694(self);
        func_8001540C(2, 0x81, self);
        func_80015D60(self, 2);
        self->unk6 = 1;
    }
}

void slash_beast_high_leap_fall(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk24 == 0) {
        self->unk2C = FIXED(2);
        self->unk20 = 0;
        self->unk6 = 2;
        func_80015D60(self, 0x17);
        self->unk60 = 7;
        self->unk50 = (const u8*)&D_80100210;
        self->unk54 = (const u8*)&D_80100214;
    }
}

void slash_beast_high_leap_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if ((func_8002D724(
             PLAYER_OBJECT(self),
             (s16)((u16)self->x_pos.i.hi + self->unk68->unk0),
             (s16)(self->unk68->unk3 + ((u16)self->y_pos.i.hi + self->unk68->unk1) + 0x10))
            & 0xFF)
        == 0x38) {
        func_8001540C(2, 0x88, self);
        func_80028BAC(0x10, 4, 2);
        func_80015D60(self, 3);
        self->unk6 = 3;
    }
}

void slash_beast_high_leap_recover(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk60 = 5;
        self->unk24 = 0;
        self->unk2C = 0;
    }
    if (self->animation_step.fields.event != 0) {
        self->unk50 = (const u8*)D_801001F8;
        self->unk54 = (const u8*)D_801001FC;
        func_80015D60(self, 0);
        slash_beast_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

// slash_beast_set_floor_palette
INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E920);

void slash_beast_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

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
    thresholds += (index << 1) + index;
    current = base;

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

void (*slash_beast_state_funcs[])(struct MainObj*) = {
    func_8006BB70,
    func_8006BD1C,
    slash_beast_death,
};
