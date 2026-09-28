// MainObj, main_object_update_funcs[73]
// 8008BA38..8008D460
#include "common.h"
#include "func_tables.h"

// double_init
INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BA38);

// double_intro_warning
INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BB6C);

void double_intro_dialogue(struct MainObj* self)
{
    typedef void (*SignedSoundFunction)(u16, u8, s8);
    s8* engine_state = &engine_obj.character_state.bytes[9];

    self->on_screen = 1;
    self->unk7C = 2;
    self->unk6++;
    ((SignedSoundFunction)func_8002217C)(0x27, 0xFF, *engine_state);
    *engine_state = 1;
}

void double_intro_wait_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk6++;
        engine_obj.enable_boss = 1;
        func_8001540C(2, 0xF8, NULL);
    }
}

void double_intro_voice(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        func_800921E8(0xA);
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_intro_fill_health(struct MainObj* self)
{
    s16 temp_v0;

    if (func_8009227C() == 0) {
        if (self->animation_step.fields.relative_step == 0) {
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
            self->state = 1;
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk61 = 0;
            self->ext.main_73.cycle_step = 0;
            func_80036B18();
            return;
        }
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void double_intro_talk(struct MainObj* self)
{
    double_intro_talk_funcs[self->unk6](self);
    is_on_screen(BASE_OBJECT(self));
}

void double_intro(struct MainObj* self)
{
    double_intro_funcs[self->unk5](self);
}

void double_face_player(struct MainObj* self)
{
    if (self->unk70 & 3) {
        if (self->unk70 & 1) {
            self->unk15 = 0;
        } else {
            self->unk15 = 0x40;
        }
    } else if ((self->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
}

void double_spawn_shot(struct MainObj* self, s32 arg1, s32 arg2)
{
    struct ShotObj* temp_v0;

    temp_v0 = find_free_shot_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = arg1 + 0x30;
        temp_v0->unk2 = arg2;
        temp_v0->x_pos.val = self->x_pos.val;
        temp_v0->y_pos.val = self->y_pos.val;
        temp_v0->animation_table = (u32**)self->animation_table;
        temp_v0->unk40 = self->unk40;
        temp_v0->unk3C = (u8*)self->sprite_frames;
        temp_v0->unk42 = self->unk42 & 0x7FFF;
        temp_v0->unk16 = self->unk16;
        temp_v0->unk7C = WEAPON_OBJECT(self);
        temp_v0->unk15 = self->unk15;
    }
}

void double_spawn_afterimage(struct MainObj* self, s8 arg1)
{
    struct MainObj* source;
    struct MiscObj* temp_v0;

    source = self;
    temp_v0 = find_free_misc_obj();
    if (temp_v0 != 0) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x31;
        temp_v0->unk2 = arg1;
        temp_v0->x_pos.val = source->x_pos.val;
        temp_v0->y_pos.val = source->y_pos.val;
        temp_v0->animation_table = (u32**)source->animation_table;
        temp_v0->unk40 = source->unk40;
        temp_v0->unk3C = (u8*)source->sprite_frames;
        temp_v0->unk42 = source->unk42 & 0x7FFF;
        temp_v0->unk16 = source->unk16;
        temp_v0->ext.pointer.unk50 = source;
        temp_v0->unk15 = 0;
    }
}

void double_wait_start(struct MainObj* self)
{
    self->unk7 = 0;
    self->unk7C = 0x3C;
    self->unk6++;
    double_face_player(self);
    func_80015D60(self, 1);
}

// double_pick_attack
INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C10C);

void double_wait(struct MainObj* self)
{
    double_wait_funcs[self->unk6](self);
}

void double_energy_ball_windup(struct MainObj* self)
{
    self->unk6++;
    func_80015D60(self, 3);
    func_8001540C(2, 0xF4, NULL);
}

void double_spawn_shot(struct MainObj*, s32, s32);

void double_energy_ball_throw(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x32;
        self->unk6++;
        double_face_player(self);
        return;
    }

    if (self->animation_step.fields.event != 0) {
        double_face_player(self);
        double_spawn_shot(self, 0, 0);
        func_8001540C(2, 0xF5, 0);
    }

    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_energy_ball_recover(struct MainObj* self)
{
    s16 timer = self->unk7C;

    if (timer == 0) {
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7C = 0;
        double_face_player(self);
        return;
    }
    self->unk7C = timer - 1;
    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_energy_ball(struct MainObj* self)
{
    double_energy_ball_funcs[self->unk6](self);
}

void double_dive_leap(struct MainObj* self)
{
    self->unk24 = FIXED(8);
    self->unk28 = 0;
    self->unk20 = 0;
    self->unk2C = 0;
    self->unk60 = 9;
    self->unk6++;
    func_80015D60(self, 4);
    func_8001540C(2, 0xF6, NULL);
}

void double_dive_rise(struct MainObj* self)
{
    func_80015DC8((struct AnimatedObj*)self);
    if (self->animation_step.fields.event != 0) {
        self->unk6++;
    }
}

void double_dive_climb(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 4) {
        self->unk6 += 1;
        func_80015D60(self, 5);
        func_8001540C(2, 0xF7, NULL);
    } else {
        func_8002B694(ANIMATED_OBJECT(self));
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void double_dive_aim(struct MainObj* self)
{
    u32 animation;

    if (self->animation_step.fields.relative_step < 0) {
        self->unk54 = &D_80105270;
        self->animation_step.fields.event = 0;
        self->unk50 = &D_8010526C;
        self->unk6++;
        animation = func_8002B7DC(
                        OBJECT_HEADER(self), OBJECT_HEADER(&g_Player))
            | 0x10;
        if ((animation & 0xFF) < 0x14U) {
            animation = 0x14;
        }
        if ((animation & 0xFF) >= 0x1DU) {
            animation = 0x1C;
        }
        func_8002B93C(MOVING_OBJECT(self), animation & 0xFF);
        self->unk2C = 0;
        self->unk28 = 0;
        self->unk20 *= 8;
        self->unk24 *= 8;
        if ((self->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
            self->unk15 = 0x40;
        } else {
            self->unk15 = 0;
        }
        func_8002B694(ANIMATED_OBJECT(self));
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_dive_fall(struct MainObj* self)
{
    s32 flags;
    s32 mask;

    flags = self->unk70;
    if (flags & 8) {
        self->unk7C = 0x1E;
        self->unk6++;
        func_80015D60(self, 6);
        self->unk54 = &D_80105264;
        self->unk50 = &D_80105260;
        func_8001540C(2, 0xF1, 0);
        return;
    }

    mask = 1;
    if (self->unk15 != 0) {
        mask = 2;
    }
    if (mask & flags) {
        self->unk20 = 0;
        self->unk28 = 0;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

// double_dive_slide
INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C664);

void double_dive_hit_wall(struct MainObj* self)
{
    if (self->unk70 & 3) {
        self->unk7C = 0x1E;
        self->unk6++;
        func_80028B68(8, 4, 2);
        func_80015D60(self, 8);
        self->unk54 = (const u8*)&D_80105264;
        self->unk50 = (const u8*)&D_80105260;
        func_8001540C(2, 0xF7, 0);
    } else {
        func_8002B694(ANIMATED_OBJECT(self));
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void double_dive_stun(struct MainObj* self)
{
    s16 timer = self->unk7C;

    if (timer == 0) {
        self->unk24 = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk28 = 0;
        self->unk20 = 0;
        self->unk6++;
        return;
    }
    self->unk7C = timer - 1;
    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_dive_land(struct MainObj* self)
{
    if (self->unk70 & 8) {
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7C = 0;
        self->unk60 = 6;
        double_face_player(self);
        func_8001540C(2, 0xF1, NULL);
        return;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_dive(struct MainObj* self)
{
    double_dive_funcs[self->unk6](self);
}

void double_aerial_shot_jump(struct MainObj* self)
{
    self->unk24 = FIXED(5);
    self->unk28 = 0;
    self->unk20 = 0;
    self->unk2C = FIXED(0.2578125);
    self->ext.main_73.shot_count = 0;
    self->unk6++;
    func_80015D60(self, 2);
}

void double_aerial_shot_fire(struct MainObj* self)
{
    if (self->unk24 < 0) {
        self->unk7C = 0x32;
        self->unk6++;
        func_80015D60(self, 9);
        double_spawn_shot(self, 1, 0);
        self->ext.main_73.shot_count++;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_aerial_shot_hang(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C;
    if (timer == 0) {
        func_80015D60(self, 0xA);
        if (self->ext.main_73.shot_count < 2) {
            self->unk7C = 0x14;
            self->unk20 = 0;
            self->unk28 = 0;
            self->unk24 = 0;
            self->unk2C = FIXED(0.2578125);
            self->unk6 += 1;
            func_80015D60(self, 2);
            self->ext.main_73.effect.position.x = self->x_pos.u.hi;
            self->ext.main_73.effect.position.y = self->y_pos.u.hi + 0x28;
            return;
        }
        self->unk7C = 0x1E;
        self->unk24 = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk6 += 3;
        return;
    }
    self->unk7C = timer - 1;
    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_aerial_shot_fire_again(struct MainObj* arg)
{
    struct MainObj* self;
    s16 targetY;

    self = arg;

    if (--self->unk7C == 0) {
        self->unk6 = 2;
        *(volatile u16*)&self->unk7C = 0;
        self->unk7C = 0x32;
        func_80015D60(self, 9);
        double_spawn_shot(self, 1, 1);
        self->ext.main_73.shot_count++;
        return;
    }

    targetY = (s16)self->ext.main_5.part_index;
    if (self->y_pos.i.hi < targetY) {
        if (self->unk24 < FIXED(-4)) {
            self->unk24 = FIXED(-4);
            self->unk2C = 0;
        }
        func_8002B694(ANIMATED_OBJECT(self));
    } else {
        self->y_pos.i.hi = targetY;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

// double_aerial_shot_wait
INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CBF8);

void double_aerial_shot_drop(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6++;
        func_80015D60(self, 2);
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void double_aerial_shot_land(struct MainObj* self)
{
    if (self->unk70 & 8) {
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7C = 0;
        double_face_player(self);
        func_80015D60(self, 1);
        return;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

void double_aerial_shot(struct MainObj* self)
{
    double_aerial_shot_funcs[self->unk6](self);
}

// double_run
INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CD80);

void double_death_flicker(struct MainObj* self)
{
    s16 timer = self->unk7C, next_timer = timer;
    u16 flags;
    if (timer == 0) {
        next_timer = 0x10;
        self->unk7C = next_timer;
        flags = self->unk42 | 0x8000;
    } else {
        next_timer--;
        self->unk7C = next_timer;
        flags = self->unk42 & 0x7FFF;
    }
    self->unk42 = flags;
}

void double_death_start(struct MainObj* self)
{
    s32 var_a1;

    var_a1 = 0x40;
    if ((self->x_pos.val - g_Player.x_pos.val) < 0) {
        var_a1 = 0;
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
    func_80036AE4(0x14, var_a1);
    self->unk5 = 1;
    self->unk2C = FIXED(0.2578125);
    self->unk28 = 0;
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk7C = 0x10;
    self->unk7E = 0x10;
    self->unk42 &= 0x7FFF;
    func_80015D60(self, 0xB);
    is_on_screen(BASE_OBJECT(self));
}

void double_death_fall(struct MainObj* self)
{
    double_death_flicker(self);
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk5 = 2;
        self->unk2C = 0;
        self->unk24 = 0;
        func_80015D60(self, 0);
        self->unk7E = 0x3C;
        func_80015D60(self, 0x1E);
    }
    CollisionRelated(PLAYER_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void double_death_wait(struct MainObj* self)
{
    double_death_flicker(self);
    if (--self->unk7E == 0) {
        self->unk5 = 3;
        func_8002217C(0x28, 5, 0);
        engine_obj.enable_boss = 0;
    }
    is_on_screen(BASE_OBJECT(self));
}

void double_death_wait_dialogue(struct MainObj* self)
{
    double_death_flicker(self);
    if (abc_object.unkC == 0) {
        self->unk5 = 4;
        self->unk7C = 0x19;
        self->ext.main_73.blink_delay = 0x19;
        self->unk42 &= 0x7FFF;
    }
    is_on_screen(BASE_OBJECT(self));
}

void double_death_blink(struct MainObj* self)
{
    struct EffectObj* effect;
    if (--self->unk7C == 0) {
        self->unk5 = 5;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.u.hi = self->x_pos.u.hi;
            effect->y_pos.u.hi = self->y_pos.u.hi;
            self->ext.main_73.unk80.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- == 0) {
        u8 unk8B;
        self->ext.main_73.blink_delay = unk8B = self->ext.main_73.blink_delay - 5;
        self->unk42 ^= 0x8000;
        if (unk8B >= 0x1A) {
            self->ext.main_73.blink_delay = 0;
        }
        self->unk7E = self->ext.main_73.blink_delay < 6 ? 5 : self->ext.main_73.blink_delay;
    }
}

void double_death_wait_explosion(struct MainObj* self)
{
    s8* script = self->ext.main_73.unk80.script;

    self->on_screen = 0;
    if (*script != 0) {
        if (script[7] == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        self->unk7C = 1;
        self->unk5 = 6;
    }
}

void double_death_finish(struct MainObj* self)
{
    s16 temp_v0;

    temp_v0 = self->unk7C - 1;
    self->unk7C = temp_v0;
    if (temp_v0 == 0) {
        engine_obj.unkF = 1;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void double_death(struct MainObj* self)
{
    double_death_funcs[self->unk5](self);
}

void double_update(struct MainObj* self)
{
    double_state_funcs[self->state](self);
}

s32 func_8008D3B8(struct MainObj* self, s8 arg1)
{
    struct EffectObj* effect;

    self->ext.main_73_parts.object_id = arg1;
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x2A;
        effect->unk2 = 0;
        effect->ext.effect_42.owner.main = self;
        D_8013B8AC = effect;
    }
}

void func_8008D410(struct MainObj* self)
{
    if (--self->ext.main_74.unk97 == 0) {
        self->ext.main_74.unk97 = 4;
        func_800AF95C(OBJECT_HEADER(self), 1, 0x60, 0x60, 2);
    }
}

union AnimationStep D_80104F54[] = {
    { 0x00010008 },
    { 0x01010003 },
    { 0x02010006 },
    { 0x03010006 },
    { 0x04010003 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010002 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08010006 },
    { 0x09010008 },
    { 0x0A010004 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010024 },
    { 0x0A000001 },
};

struct Unk_unk68 D_80104FD4[4] = {
    { 12, 0, 1, 12 },
    { 10, 0, 1, 13 },
    { 12, 0, 1, 14 },
    { 10, 0, -3, 13 },
};

struct Unk_unk68 D_80104FE4[6] = {
    { 3, 0, 1, 15 },
    { 6, 0, 1, 16 },
    { 12, 0, 1, 19 },
    { 10, 0, 1, 20 },
    { 12, 0, 1, 21 },
    { 10, 0, -3, 20 },
};

union AnimationStep D_80104FFC[] = {
    { 0x0F010003 },
    { 0x10010005 },
    { 0x16010004 },
    { 0x1701000C },
    { 0x18010002 },
    { 0x19010101 },
    { 0x19010001 },
    { 0x1A010002 },
    { 0x1B00000C },
};

u8 D_80105020[16] = { 3, 0, 1, 15, 6, 0, 1, 16, 2, 1, 1, 17, 2, 0, 255, 18 };

struct Unk_unk68 D_80105030[7] = {
    { 4, 0, 1, 28 },
    { 12, 0, 1, 29 },
    { 2, 0, 1, 30 },
    { 2, 1, 1, 31 },
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, -2, 34 },
};

union AnimationStep D_8010504C[] = {
    { 0x23010004 },
    { 0x2400000C },
};

struct Unk_unk68 D_80105054[5] = {
    { 2, 0, 1, 37 },
    { 2, 1, 1, 38 },
    { 1, 0, 1, 39 },
    { 1, 0, 1, 40 },
    { 1, 0, -2, 41 },
};

union AnimationStep D_80105068[] = {
    { 0x2A010002 },
    { 0x13000003 },
};

u8 D_80105070[8] = { 2, 0, 1, 43, 2, 0, 255, 44 };

union AnimationStep D_80105078[] = {
    { 0x2D010002 },
    { 0x2E010002 },
    { 0x2D010002 },
    { 0x2E010002 },
    { 0x2D010001 },
    { 0x2E010001 },
    { 0x2D010001 },
    { 0x2E010001 },
    { 0x2D010001 },
    { 0x2E010001 },
    { 0x2D000012 },
};

union AnimationStep D_801050A4[] = {
    { 0x32010004 },
    { 0x31010003 },
    { 0x30010002 },
    { 0x2F010002 },
    { 0x30010001 },
    { 0x2F010001 },
    { 0x30010001 },
    { 0x2F000008 },
};

struct Unk_unk68 D_801050C4[4] = {
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 53 },
    { 1, 0, -3, 54 },
};

union AnimationStep D_801050D4[] = {
    { 0x37010001 },
    { 0x38010002 },
    { 0x39010003 },
    { 0x3A000004 },
};

u8 D_801050E4[8] = { 2, 0, 1, 59, 2, 0, 255, 60 };

u8 D_801050EC[8] = { 2, 0, 1, 61, 2, 0, 255, 62 };

struct Unk_unk68 D_801050F4[5] = {
    { 2, 0, 1, 63 },
    { 2, 0, 1, 64 },
    { 1, 0, 1, 65 },
    { 1, 0, 1, 66 },
    { 1, 0, -2, 67 },
};

union AnimationStep D_80105108[] = {
    { 0x44010002 },
    { 0x45010003 },
    { 0x46010003 },
    { 0x47010003 },
    { 0x48010003 },
    { 0x46010002 },
    { 0x47010002 },
    { 0x48010002 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x48010001 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x48010001 },
    { 0x46000018 },
};

u8 D_80105144[8] = { 3, 0, 1, 73, 3, 0, 255, 74 };

u8 D_8010514C[8] = { 3, 0, 1, 75, 3, 0, 255, 76 };

struct Unk_unk68 D_80105154[8] = {
    { 4, 0, 1, 70 },
    { 4, 0, 1, 77 },
    { 6, 0, 1, 78 },
    { 4, 0, 1, 77 },
    { 4, 0, 1, 70 },
    { 4, 0, 1, 79 },
    { 6, 0, 1, 80 },
    { 4, 0, -7, 79 },
};

union AnimationStep D_80105174[] = {
    { 0x51010006 },
    { 0x52010004 },
    { 0x53010003 },
    { 0x54010002 },
    { 0x58000012 },
};

union AnimationStep D_80105188[] = {
    { 0x58010002 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010101 },
    { 0x5D010002 },
    { 0x5E010002 },
    { 0x5F000002 },
};

struct Unk_unk68 D_801051A8[3] = {
    { 1, 0, 1, 96 },
    { 1, 0, 1, 97 },
    { 1, 0, -2, 98 },
};

union AnimationStep D_801051B4[] = {
    { 0x55010005 },
    { 0x56010004 },
    { 0x57010003 },
    { 0x6300000C },
};

struct Unk_unk68 D_801051C4[3] = {
    { 1, 0, 1, 99 },
    { 1, 0, 1, 100 },
    { 1, 0, -2, 101 },
};

union AnimationStep D_801051D0[] = {
    { 0x66000002 },
};

union AnimationStep D_801051D4[] = {
    { 0x67000002 },
};

union AnimationStep D_801051D8[] = {
    { 0x68000002 },
};

union AnimationStep D_801051DC[] = {
    { 0x69000002 },
};

union AnimationStep D_801051E0[] = {
    { 0x6A000002 },
};

void* D_801051E4[31] = {
    D_80104F54,
    D_80104FD4,
    D_80104FE4,
    D_80104FFC,
    D_80105020,
    D_80105030,
    D_8010504C,
    D_80105054,
    D_80105068,
    D_80105070,
    D_80105078,
    D_801050A4,
    D_801050C4,
    D_801050D4,
    D_801050E4,
    D_801050EC,
    D_801050F4,
    D_80105108,
    D_80105144,
    D_8010514C,
    D_80105154,
    D_80105174,
    D_80105188,
    D_801051A8,
    D_801051B4,
    D_801051C4,
    D_801051D0,
    D_801051D4,
    D_801051D8,
    D_801051DC,
    D_801051E0,
};

struct Unk_unk68 D_80105260 = { -9, -36, 29, 54 };

struct Unk_unk68 D_80105264 = { -14, -41, 35, 59 };

struct Unk_unk68 D_80105268 = { 0, 0, 19, 19 };

struct Unk_unk68 D_8010526C = { -5, -23, 20, 84 };

struct Unk_unk68 D_80105270 = { -14, -53, 32, 79 };

struct Unk_unk68 D_80105274 = { -57, -11, 90, 23 };

struct Unk_unk68 D_80105278 = { -27, -8, 85, 30 };

u8 D_8010527C[8] = { 2, 3, 2, 4, 255, 0, 0, 0 };

u8 D_80105284[8] = { 2, 4, 2, 4, 255, 0, 0, 0 };

u8 D_8010528C[8] = { 2, 3, 3, 2, 4, 255, 0, 0 };

union AnimationStep D_80105294[] = {
    { 0x04020402 },
    { 0x0000FF05 },
};

u8* D_8010529C[2] = {
    D_8010527C,
    D_80105284,
};

void* D_801052A4[2] = {
    D_8010528C,
    D_80105294,
};

void (*double_intro_talk_funcs[4])(struct MainObj*) = {
    double_intro_dialogue,
    double_intro_wait_dialogue,
    double_intro_voice,
    double_intro_fill_health,
};

void (*double_intro_funcs[3])() = {
    func_8008BA38,
    func_8008BB6C,
    double_intro_talk,
};

void (*double_wait_funcs[2])() = {
    double_wait_start,
    func_8008C10C,
};

void (*double_energy_ball_funcs[3])() = {
    double_energy_ball_windup,
    double_energy_ball_throw,
    double_energy_ball_recover,
};

void (*double_dive_funcs[9])() = {
    double_dive_leap,
    double_dive_rise,
    double_dive_climb,
    double_dive_aim,
    double_dive_fall,
    func_8008C664,
    double_dive_hit_wall,
    double_dive_stun,
    double_dive_land,
};

void (*double_aerial_shot_funcs[7])() = {
    double_aerial_shot_jump,
    double_aerial_shot_fire,
    double_aerial_shot_hang,
    double_aerial_shot_fire_again,
    func_8008CBF8,
    double_aerial_shot_drop,
    double_aerial_shot_land,
};

void (*double_step_funcs[6])() = {
    func_8009216C,
    func_8009216C,
    double_wait,
    double_energy_ball,
    double_dive,
    double_aerial_shot,
};

void (*double_death_funcs[7])(struct MainObj*) = {
    double_death_start,
    double_death_fall,
    double_death_wait,
    double_death_wait_dialogue,
    double_death_blink,
    double_death_wait_explosion,
    double_death_finish,
};

void (*double_state_funcs[3])() = {
    double_intro,
    func_8008CD80,
    double_death,
};
