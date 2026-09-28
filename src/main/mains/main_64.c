// MainObj, main_object_update_funcs[64]
// 8007C30C..8007DD98
#include "common.h"
#include "func_tables.h"

INCLUDE_ASM("main/nonmatchings/mains/main_64", func_8007C30C);

void func_8007C3FC(struct MainObj* arg0)
{
    struct EffectObj* effect;
    s32* archive;
    s32 offset;

    if (g_Player.capsule_state != 0) {
        return;
    }
    switch (arg0->unk6) {
    case 0:
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            arg0->ext.main_64.object = effect;
        }
        player_start_script_action(0x14, 0x40);
        arg0->unk6 = 1;
        arg0->unk7 = 0;
        break;
    case 1:
        effect = arg0->ext.main_64.object;
        if (effect->active != 0) {
            break;
        }
        arg0->unk6 = 2;
        arg0->bg_offset = g_Player.bg_offset;
        if (engine_obj.stage != 0xC) {
            arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
        } else {
            archive = SP_MENU_FRAMES;
            arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
            offset = archive[4];
            arg0->unk42 = 0x7888;
            arg0->sprite_frames = (u8*)archive + offset;
        }
        arg0->animation_table = (const u8* const*)cyber_peacock_animations;
        arg0->unk16 = 4;
        arg0->unk60 = 5;
        arg0->unk61 = -0x80;
        arg0->unk63 = 2;
        arg0->unk5C = 0;
        arg0->unk62 = 0;
        arg0->unk7C = 0x20;
        engine_obj.enable_boss = 0;
        engine_obj.unk25 = 0;
        engine_obj.boss_ptr = arg0;
        break;
    case 2:
        if (--arg0->unk7C == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
        }
        break;
    }
}

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
        player_end_script_action();
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

void func_8007D174(struct MainObj* arg0)
{
    u8 unk15;
    s8 active;

    struct ItemObj* item = find_free_item_obj();
    if (item != NULL) {
        active = arg0->active;
        item->id = 0x17;
        item->active = active;
        item->unk2 = arg0->ext.main_64.shot_count;
        item->x_pos.val = arg0->x_pos.val;
        item->y_pos.val = arg0->y_pos.val;
        item->animation_table = (void*)arg0->animation_table;
        item->unk40 = arg0->unk40;
        item->sprite_frames = (void*)arg0->sprite_frames;
        item->unk42 = arg0->unk42 & 0x7FFF;
        item->unk16 = arg0->unk16;
        unk15 = arg0->unk15;
        item->backref = (void*)arg0;
        item->unk15 = unk15;
        arg0->ext.main_64.object = item;
        func_8001540C(2, 0xC4, arg0);
    }
}

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
    player_start_script_action(0x14, g_Player.unk15);
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

union AnimationStep D_8010248C[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010103 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1E010003 },
    { 0x1F010003 },
    { 0x20010003 },
    { 0x21010003 },
    { 0x22010003 },
    { 0x23010004 },
    { 0x24010005 },
    { 0x01010002 },
    { 0x18010002 },
    { 0x01010002 },
    { 0x18010002 },
    { 0x01010002 },
    { 0x18010002 },
    { 0x0101000F },
    { 0x01000001 },
};

union AnimationStep D_80102550[] = {
    { 0x01010003 },
    { 0x02010003 },
    { 0x0301000A },
    { 0x03010101 },
    { 0x04010003 },
    { 0x2C010003 },
    { 0x2D010012 },
    { 0x05010014 },
    { 0x2E010003 },
    { 0x2E000003 },
};

union AnimationStep D_80102578[] = {
    { 0x00010002 },
    { 0x25010002 },
    { 0x00010002 },
    { 0x25010002 },
    { 0x00010002 },
    { 0x25010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x26010002 },
    { 0x26000002 },
};

union AnimationStep D_801025A8[] = {
    { 0x27010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x26010002 },
    { 0x25010002 },
    { 0x00010002 },
    { 0x25010002 },
    { 0x00010002 },
    { 0x25010002 },
    { 0x00000002 },
};

union AnimationStep D_801025D8[] = {
    { 0x27010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x26010002 },
    { 0x25010002 },
    { 0x28010002 },
    { 0x25010002 },
    { 0x28010002 },
    { 0x25010002 },
    { 0x28000006 },
    { 0x29010005 },
    { 0x2A010005 },
    { 0x2B000006 },
};

struct Unk_unk68 D_80102614[8] = {
    { 3, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 42 },
    { 3, 1, 1, 43 },
    { 1, 0, 1, 47 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 49 },
    { 1, 0, -3, 50 },
};

union AnimationStep D_80102634[] = {
    { 0x2F010001 },
    { 0x33010001 },
    { 0x34010001 },
    { 0x2F010001 },
    { 0x33010001 },
    { 0x34010001 },
    { 0x2F010001 },
    { 0x33010001 },
    { 0x34000001 },
};

struct Unk_unk68 D_80102658[18] = {
    { 6, 0, 1, 0 },
    { 4, 0, 1, 53 },
    { 4, 0, 1, 54 },
    { 5, 0, 1, 55 },
    { 3, 0, 1, 56 },
    { 3, 0, 1, 57 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 59 },
    { 1, 0, 1, 57 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 59 },
    { 1, 0, 1, 60 },
    { 1, 0, 1, 61 },
    { 1, 1, 1, 62 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 61 },
    { 1, 0, 1, 62 },
    { 1, 0, -2, 58 },
};

union AnimationStep D_801026A0[] = {
    { 0x3D010001 },
    { 0x3F010002 },
    { 0x40010003 },
    { 0x41010004 },
    { 0x42010005 },
    { 0x39010006 },
    { 0x43010001 },
    { 0x39010001 },
    { 0x43010001 },
    { 0x39010001 },
    { 0x43010001 },
    { 0x39010001 },
    { 0x43010001 },
    { 0x39010001 },
    { 0x43010001 },
    { 0x39000001 },
};

union AnimationStep D_801026E0[] = {
    { 0x27010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x26010002 },
    { 0x25010002 },
    { 0x44010002 },
    { 0x25010002 },
    { 0x44010002 },
    { 0x25010002 },
    { 0x44000002 },
};

union AnimationStep D_80102710[] = {
    { 0x45010003 },
    { 0x46010012 },
    { 0x00000014 },
};

union AnimationStep D_8010271C[] = {
    { 0x00010008 },
    { 0x47010008 },
    { 0x48010008 },
    { 0x49010012 },
    { 0x4A010002 },
    { 0x4B010002 },
    { 0x4C010002 },
    { 0x4A010002 },
    { 0x4B010002 },
    { 0x4C010002 },
    { 0x4D010003 },
    { 0x4E010003 },
    { 0x4F010003 },
    { 0x5001000A },
    { 0x51010003 },
    { 0x52010003 },
    { 0x53010003 },
    { 0x54010001 },
    { 0x53010001 },
    { 0x54010001 },
    { 0x53010001 },
    { 0x54000014 },
};

u8 D_80102774[8] = { 1, 0, 1, 88, 1, 0, 255, 89 };

struct Unk_unk68 D_8010277C[4] = {
    { 2, 0, 1, 88 },
    { 2, 0, 1, 90 },
    { 2, 0, 1, 91 },
    { 2, 0, -3, 92 },
};

union AnimationStep D_8010278C[] = {
    { 0x55010008 },
    { 0x56010002 },
    { 0x57010001 },
    { 0x55010002 },
    { 0x91010002 },
    { 0x9200001E },
};

union AnimationStep D_801027A4[] = {
    { 0x55000001 },
};

u8 D_801027A8[8] = { 2, 0, 1, 109, 2, 0, 255, 110 };

u8 D_801027B0[8] = { 2, 0, 1, 111, 2, 0, 255, 112 };

u8 D_801027B8[8] = { 2, 0, 1, 113, 2, 0, 255, 114 };

u8 D_801027C0[8] = { 2, 0, 1, 115, 2, 0, 255, 116 };

u8 D_801027C8[8] = { 2, 0, 1, 117, 2, 0, 255, 118 };

u8 D_801027D0[8] = { 2, 0, 1, 119, 2, 0, 255, 120 };

u8 D_801027D8[8] = { 2, 0, 1, 121, 2, 0, 255, 122 };

u8 D_801027E0[8] = { 2, 0, 1, 123, 2, 0, 255, 124 };

u8 D_801027E8[8] = { 2, 0, 1, 93, 2, 0, 255, 94 };

u8 D_801027F0[8] = { 2, 0, 1, 95, 2, 0, 255, 96 };

u8 D_801027F8[8] = { 2, 0, 1, 97, 2, 0, 255, 98 };

u8 D_80102800[8] = { 2, 0, 1, 99, 2, 0, 255, 100 };

u8 D_80102808[8] = { 2, 0, 1, 101, 2, 0, 255, 102 };

u8 D_80102810[8] = { 2, 0, 1, 103, 2, 0, 255, 104 };

u8 D_80102818[8] = { 2, 0, 1, 105, 2, 0, 255, 106 };

u8 D_80102820[8] = { 2, 0, 1, 107, 2, 0, 255, 108 };

union AnimationStep D_80102828[] = {
    { 0x7D010001 },
    { 0x7E010002 },
    { 0x7F010003 },
    { 0x80010003 },
    { 0x81000004 },
};

struct Unk_unk68 D_8010283C[3] = {
    { 2, 0, 1, -123 },
    { 1, 0, 1, -122 },
    { 1, 0, -2, -112 },
};

struct Unk_unk68 D_80102848[3] = {
    { 1, 0, 1, -126 },
    { 2, 0, 1, -125 },
    { 2, 0, -2, -124 },
};

union AnimationStep D_80102854[] = {
    { 0x87010002 },
    { 0x88010002 },
    { 0x87010002 },
    { 0x88010002 },
    { 0x87010002 },
    { 0x88010002 },
    { 0x87010002 },
    { 0x88010002 },
    { 0x87010002 },
    { 0x88010002 },
    { 0x87010002 },
    { 0x88000002 },
};

struct Unk_unk68 D_80102884[10] = {
    { 4, 0, 1, -121 },
    { 4, 0, 1, -119 },
    { 4, 0, 1, -118 },
    { 4, 0, 1, -117 },
    { 4, 0, 1, -118 },
    { 4, 0, 1, -116 },
    { 4, 0, 1, -115 },
    { 4, 0, 1, -114 },
    { 4, 0, 1, -113 },
    { 4, 0, -9, -116 },
};

union AnimationStep D_801028AC[] = {
    { 0x34000004 },
};

void* cyber_peacock_animations[38] = {
    D_8010248C,
    D_80102550,
    D_80102578,
    D_801025A8,
    D_80102614,
    D_80102634,
    D_80102658,
    D_801026A0,
    D_801026E0,
    D_8010271C,
    D_80102774,
    D_8010277C,
    D_8010278C,
    D_801027A8,
    D_801027B0,
    D_801027B8,
    D_801027C0,
    D_801027C8,
    D_801027D0,
    D_801027D8,
    D_801027E0,
    D_801027E8,
    D_801027F0,
    D_801027F8,
    D_80102800,
    D_80102808,
    D_80102810,
    D_80102818,
    D_80102820,
    D_80102828,
    D_8010283C,
    D_80102848,
    D_80102854,
    D_80102884,
    D_801028AC,
    D_801025D8,
    D_801027A4,
    D_80102710,
};

struct Unk_unk68 D_80102948 = { -6, -27, 17, 64 };

struct Unk_unk68 D_8010294C = { -11, -27, 27, 70 };

struct Unk_unk68 D_80102950 = { -30, -35, 56, 64 };

struct Unk_unk68 D_80102954 = { -18, -37, 32, 71 };

struct Unk_unk68 D_80102958 = { -12, -9, 28, 52 };

struct Unk_unk68 D_8010295C = { -32, -12, 44, 55 };

struct Unk_unk68 D_80102960 = { -87, -50, -61, 92 };

struct Unk_unk68 D_80102964 = { -32, -12, 44, 55 };

void (*cyber_peacock_intro_appear_funcs[4])() = {
    cyber_peacock_intro_appear_start,
    cyber_peacock_intro_pose,
    cyber_peacock_intro_start_health_bar,
    func_8007C6E8,
};

void (*cyber_peacock_intro_funcs[3])() = {
    func_8007C30C,
    func_8007C3FC,
    cyber_peacock_intro_appear,
};

u8 cyber_peacock_attacks[32] = { 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03 };

u8 cyber_peacock_attacks_low_health[32] = { 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 };

u8 cyber_peacock_attack_animations[8] = { 0x03, 0x23, 0x03, 0x08, 0x23, 0x00, 0x00, 0x00 };

u8 cyber_peacock_attack_steps[8] = { 0x02, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00 };

void (*cyber_peacock_teleport_funcs[5])() = {
    cyber_peacock_teleport_start,
    cyber_peacock_teleport_vanish,
    func_8007CA68,
    cyber_peacock_teleport_appear,
    cyber_peacock_teleport_wait,
};

void (*cyber_peacock_rising_kick_funcs[4])() = {
    cyber_peacock_rising_kick_start,
    cyber_peacock_rising_kick_jump,
    cyber_peacock_rising_kick_rise,
    cyber_peacock_rising_kick_finish,
};

void (*cyber_peacock_slash_funcs[3])() = {
    cyber_peacock_slash_start,
    cyber_peacock_slash_swing,
    cyber_peacock_slash_finish,
};

void (*cyber_peacock_aiming_laser_funcs[7])() = {
    cyber_peacock_aiming_laser_start,
    cyber_peacock_aiming_laser_raise,
    cyber_peacock_aiming_laser_target,
    cyber_peacock_aiming_laser_wait,
    cyber_peacock_aiming_laser_fire,
    cyber_peacock_aiming_laser_next,
    cyber_peacock_aiming_laser_finish,
};

void (*cyber_peacock_attack_funcs[4])() = {
    cyber_peacock_rising_kick,
    cyber_peacock_slash,
    cyber_peacock_aiming_laser,
    cyber_peacock_rising_kick,
};

void (*cyber_peacock_step_funcs[6])() = {
    func_8009216C,
    func_8009216C,
    cyber_peacock_teleport,
    cyber_peacock_attack,
    func_8007D5D0,
    func_8007D710,
};

void (*cyber_peacock_death_funcs[3])() = {
    cyber_peacock_death_start,
    cyber_peacock_death_explode,
    cyber_peacock_death_finish,
};

void (*cyber_peacock_state_funcs[3])() = {
    cyber_peacock_intro,
    func_8007D838,
    cyber_peacock_death,
};
