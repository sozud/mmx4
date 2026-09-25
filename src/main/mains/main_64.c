// MainObj, main_object_update_funcs[64]
// 8007C30C..8007DD98
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C30C);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C3FC);

void cyber_peacock_intro_appear_start(struct MainObj* self)
{
    self->on_screen = 1;
    self->unk6++;
    func_80015D60(self, 0);
}

void cyber_peacock_intro_pose(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 2;
        self->unk6 += 1;
        if (engine_obj.stage == 6) {
            ((void (*)(u16, u8, s8))func_8002217C)(
                0xE, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
    } else {
        if (self->animation_step.fields.event != 0) {
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0xC1, self);
        }
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk6++;
        func_80015D60(self, 1);
        engine_obj.enable_boss = 1;
        func_800921E8(5);
    }
}

void func_8007C6E8(struct MainObj* arg0)
{
    s8 health;

    if (func_8009227C() != 0) {
        return;
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        health = arg0->unk5C;
        if (health < 0x30) {
            if (--arg0->unk7C == 0) {
                func_8001540C(0, 0xE, 0);
                arg0->unk7C = 2;
            }
            arg0->unk5C++;
            return;
        }
        arg0->state = 1;
        arg0->ext.main_64.saved_health = health;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->unk61 = 0;
        func_80036B18();
        return;
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0xC2, arg0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void cyber_peacock_intro_appear(struct MainObj* self)
{
    cyber_peacock_intro_appear_funcs[self->unk6](self);
    is_on_screen(BASE_OBJECT(self));
}

void cyber_peacock_intro(struct MainObj* self)
{
    cyber_peacock_intro_funcs[self->unk5](self);
}

void cyber_peacock_face_player(struct MainObj* self)
{
    if ((self->x_pos.val - g_Player.x_pos.val) < 0) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
}

u8 cyber_peacock_choose_attack(struct MainObj* self)
{
    if (self->ext.main_64.skip_attack == 0) {
        if (self->ext.main_64.force_laser == 0) {
            if (self->unk5C < 0x18) {
                return cyber_peacock_attacks_low_health[get_random() & 0x1F];
            }
            return cyber_peacock_attacks[get_random() & 0x1F];
        }
        return 3;
    }
    return 0;
}

void cyber_peacock_start_teleport(struct MainObj* self)
{
    self->unk20 = 0;
    self->unk28 = FIXED(1);
    self->unk24 = 0;
    self->unk2C = 0;
    self->unk54 = NULL;
    self->unk50 = NULL;
    self->ext.main_64.target_x = self->x_pos.u.hi;
    self->ext.main_64.target_y = self->y_pos.u.hi;
    func_8001540C(2, 0xC6, self);
}

void cyber_peacock_teleport_start(struct MainObj* self)
{
    cyber_peacock_start_teleport(self);
    self->unk7 = 0;
    self->unk6++;
    func_80015D60(self, 2);
    self->ext.main_64.skip_attack = 0;
}

void cyber_peacock_teleport_vanish(struct MainObj* self)
{
    s32 temp_v1;
    s32 var_v0;

    if (self->animation_step.fields.relative_step == 0) {
        self->unk7 = 0;
        self->unk7C = 0x50;
        self->unk6++;
        func_80015D60(self, 0x22);
        self->unk60 = 5;
        return;
    }
    temp_v1 = self->unk20 + self->unk28;
    self->unk20 = temp_v1;
    if (D_80141BD8.unk0 & 1) {
        var_v0 = ((s16)self->ext.main_64.target_x << 0x10) + temp_v1;
    } else {
        var_v0 = ((s16)self->ext.main_64.target_x << 0x10) - temp_v1;
    }
    self->x_pos.val = var_v0;
    func_80015DC8(ANIMATED_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007CA68);

void cyber_peacock_teleport_appear(struct MainObj* self)
{
    s32 temp_v1;
    s32 var_v0;

    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x14;
        self->unk54 = (const u8*)&D_80102948;
        self->unk50 = (const u8*)&D_80102948;
        self->unk7 = 0;
        self->unk60 = 5;
        self->unk6++;
        func_8001540C(2, 0xC6, self);
        return;
    }

    temp_v1 = self->unk20 - self->unk28;
    self->unk20 = temp_v1;
    if (D_80141BD8.unk0 & 1) {
        var_v0 = ((s16)self->ext.main_64.target_x << 0x10) + temp_v1;
    } else {
        var_v0 = ((s16)self->ext.main_64.target_x << 0x10) - temp_v1;
    }
    self->x_pos.val = var_v0;
    func_80015DC8(ANIMATED_OBJECT(self));
}

void cyber_peacock_teleport_wait(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk6 = 0;
        self->unk7 = 0;
        self->ext.main_64.hit_count = 0;
        self->unk5 = self->ext.main_64.next_step;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_teleport(struct MainObj* self)
{
    cyber_peacock_teleport_funcs[self->unk6](self);
}

void cyber_peacock_rising_kick_start(struct MainObj* self)
{
    self->unk6++;
    func_80015D60(self, 4);
    self->unk54 = (const u8*)&D_80102954;
    self->unk50 = (const u8*)&D_80102950;
    self->unk60 = 6;
}

void cyber_peacock_rising_kick_jump(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->unk67 = 1;
        self->unk24 = FIXED(8);
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk2C = FIXED(0.34375);
        self->unk6++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void cyber_peacock_rising_kick_rise(struct MainObj* self)
{
    if (self->unk24 < 0) {
        self->unk6++;
        func_80015D60(self, 5);
        return;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

void cyber_peacock_rising_kick_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 2;
        self->unk6 = 1;
        cyber_peacock_start_teleport(self);
        self->unk20 = FIXED(22);
        self->unk67 = 0;
        func_80015D60(self, 0x22);
        self->unk60 = 5;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_rising_kick(struct MainObj* self)
{
    cyber_peacock_rising_kick_funcs[self->unk6](self);
}

void cyber_peacock_slash_start(struct MainObj* self)
{
    self->unk7C = 0;
    self->unk6++;
    func_80015D60(self, 6);
    func_8001540C(2, 0xC9, self);
    self->unk54 = (const u8*)&D_8010295C;
    self->unk50 = (const u8*)&D_80102958;
    self->unk60 = 9;
}

void cyber_peacock_slash_swing(struct MainObj* self)
{
    u16 counter;

    if (self->animation_step.fields.relative_step < 0) {
        counter = self->unk7C + 1;
        self->unk7C = counter;
        if ((s16)counter >= 4) {
            self->unk6 += 1;
            func_80015D60(self, 7);
            self->unk54 = (const u8*)&D_8010295C;
            self->unk50 = (const u8*)&D_80102958;
            return;
        }
    } else if (self->animation_step.fields.event != 0) {
        self->unk54 = (const u8*)&D_80102964;
        self->animation_step.fields.event = 0;
        self->unk50 = (const u8*)&D_80102960;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void cyber_peacock_slash_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 2;
        self->unk6 = 1;
        cyber_peacock_start_teleport(self);
        self->unk20 = FIXED(22);
        func_80015D60(self, 0x22);
        self->unk60 = 5;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void cyber_peacock_slash(struct MainObj* self)
{
    cyber_peacock_slash_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D174);

void cyber_peacock_spawn_missile(struct MainObj* self)
{
    struct ShotObj* shot;

    shot = find_free_shot_obj();
    if (shot != 0) {
        shot->active = self->active;
        shot->id = 0x2A;
        shot->unk2 = self->ext.main_64.shot_count;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->animation_table = self->animation_table;
        shot->unk40 = self->unk40;
        shot->unk3C = self->sprite_frames;
        shot->unk42 = self->unk42 & 0x7FFF;
        shot->unk16 = self->unk16;
        shot->unk15 = 0;
        shot->unk7C = self->ext.main_64.object;
        shot->backref = self;
        func_8001540C(2, 0xC3, self);
    }
}

void cyber_peacock_aiming_laser_start(struct MainObj* self)
{
    self->ext.main_64.shot_count = 0;
    self->unk6++;
    func_80015D60(self, 0x25);
}

void cyber_peacock_aiming_laser_raise(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x1E;
        self->unk6++;
        func_80015D60(self, 9);
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_aiming_laser_target(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        func_8007D174(self);
        func_80015D60(self, 0x24);
        self->unk7C = 0x1E;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_aiming_laser_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6++;
        func_80015D60(self, 0xC);
    }
}

void cyber_peacock_aiming_laser_fire(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        cyber_peacock_spawn_missile(self);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void cyber_peacock_aiming_laser_next(struct MainObj* self)
{
    self->ext.main_64.shot_count++;
    if (self->ext.main_64.shot_count >= 8) {
        self->unk7C = 0x3C;
        self->unk6++;
        func_80015D60(self, 2);
        return;
    }
    self->unk7C = 0x5A;
    self->unk6 = 3;
    func_80015D90(ANIMATED_OBJECT(self), 9, 3);
}

void cyber_peacock_aiming_laser_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 2;
        self->ext.main_64.shot_count = 0;
        self->unk2 = 0;
        self->unk6 = 1;
        cyber_peacock_start_teleport(self);
        self->unk20 = FIXED(22);
        func_80015D60(self, 0x22);
        self->unk60 = 5;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_aiming_laser(struct MainObj* self)
{
    cyber_peacock_aiming_laser_funcs[self->unk6](self);
}

void cyber_peacock_attack(struct MainObj* self)
{
    cyber_peacock_attack_funcs[self->unk2](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D5D0);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D710);

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007D838);

void cyber_peacock_death_start(struct MainObj* self)
{
    self->unk5 = 1;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_64.flash_timer = 0x19;
    self->unk42 &= 0x7FFF;
    func_80036AE4(0x14, g_Player.unk15);
    func_80015D60(self, 0x20);
    is_on_screen(BASE_OBJECT(self));
}

void cyber_peacock_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.u.hi = self->x_pos.u.hi;
            effect->y_pos.u.hi = self->y_pos.u.hi;
            self->ext.main_64.object = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- == 0) {
        u8 unk92;
        self->ext.main_64.flash_timer = unk92 = self->ext.main_64.flash_timer - 5;
        self->unk42 ^= 0x8000;
        if (unk92 >= 0x1A) {
            self->ext.main_64.flash_timer = 0;
        }
        self->unk7E = self->ext.main_64.flash_timer < 6 ? 5 : self->ext.main_64.flash_timer;
    }
}

void cyber_peacock_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_64.object;
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

void cyber_peacock_death(struct BarObj* self)
{
    cyber_peacock_death_funcs[self->unk5](self);
}

void cyber_peacock_update(struct MainObj* self)
{
    cyber_peacock_state_funcs[self->state](self);
}

void magma_dragoon_spawn_flames(struct AnimatedObj* self, u32 arg1)
{
    struct MiscObj* obj;

    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 0x41;
        obj->id = 0x26;
        obj->unk2 = 2;
        obj->ext.misc_7.position = self;
    }

    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 0x41;
        obj->id = 0x26;
        obj->unk2 = 3;
        obj->ext.misc_7.position = self;
    }

    if (arg1 < 2U) {
        obj = find_free_misc_obj();
        if (obj != 0) {
            obj->active = 0x41;
            obj->id = 0x26;
            obj->unk2 = arg1;
            obj->ext.misc_7.position = self;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007DD0C);
