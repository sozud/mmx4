// MainObj, main_object_update_funcs[65]
// 8007DD98..800806A0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007DD98);

void magma_dragoon_intro_warning(struct MainObj* self)
{
    struct EffectObj* effect;

    effect = find_free_effect_obj();
    if (effect != 0) {
        effect->active = 1;
        effect->id = 0x18;
        effect->x_pos.i.hi = self->x_pos.i.hi;
        effect->y_pos.i.hi = self->y_pos.i.hi;
        self->ext.main_65.object = (struct MainObj*)effect;
    }
    self->unk15 = 0;
    self->unk6++;
    func_80036AE4(0x14, 0x40);
    if (engine_obj.stage == 0xC) {
        background_objects[0].unk26 = 0x1B0;
        background_objects[0].unk24 = 0x1B0;
        background_objects[0].unk2A = 0x5FB;
        background_objects[0].unk28 = 0x5FB;
    } else {
        background_objects[0].unk26 = 0x1490;
        background_objects[0].unk24 = 0x1490;
        background_objects[0].unk2A = 0x1EB;
        background_objects[0].unk28 = 0x1EB;
    }
}

void magma_dragoon_intro_leap(struct MainObj* self)
{
    if (self->ext.main_65.object->active == 0) {
        self->unk24 = FIXED(2);
        self->unk20 = 0;
        self->unk28 = FIXED(0.0078125);
        self->unk6++;
        func_80015D60(self, 0xF);
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 0);
        self->unk67 = 1;
        self->unk7E = 0x14;
    }
}

void magma_dragoon_intro_descend(struct MainObj* self)
{
    if ((self->y_pos.i.hi - background_objects[0].y_pos.i.hi) < 0x20) {
        self->unk20 = FIXED(-2);
        self->unk24 = FIXED(-2);
        self->unk2C = FIXED(0.1875);
        self->unk28 = 0;
        self->unk68 = &D_80102A60;
        self->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_land(struct MainObj* self)
{
    if (self->unk70 & 8) {
        func_80015D60(self, 0x10);
        self->unk67 = 0;
        func_8001540C(2, 2, self);
        self->unk20 = 0;
        self->unk24 = 0;
        self->unk2C = 0;
        self->unk6++;
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_pose(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 0x11);
        self->unk6++;
        if (engine_obj.stage == 4) {
            ((void (*)(u16, u8, s8))func_8002217C)(
                0xB, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk6++;
        func_800921E8(3);
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_ready(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0 && func_8009227C() == 0) {
        func_80015D60(self, 0x12);
        engine_obj.enable_boss = 1;
        self->unk7E = 3;
        self->unk20 = 0;
        self->unk24 = 0;
        self->unk2C = 0;
        self->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void func_8007E350(struct MainObj* arg0)
{
    if (arg0->unk5C < 0x30) {
        if (--arg0->unk7E == 0) {
            func_8001540C(0, 0xE, 0);
            arg0->unk7E = 3;
        }
        arg0->unk5C++;
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
    } else {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk54 = &D_80102A64;
        func_80036B18();
        if (engine_obj.stage == 0xC) {
            background_objects[0].unk26 = 0x110;
            background_objects[0].unk24 = 0x1B0;
        } else {
            background_objects[0].unk26 = 0x13F0;
            background_objects[0].unk24 = 0x1490;
        }
        background_objects[0].unk48 = 4;
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
    }
}

void magma_dragoon_intro(struct MainObj* self)
{
    magma_dragoon_intro_funcs[self->unk6](self);
}

void magma_dragoon_face_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi > self->x_pos.i.hi) {
        self->unk15 = 0x40;
    } else {
        self->unk15 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E4C8);

void magma_dragoon_dive_kick_jump(struct MainObj* self)
{
    s32 var_a0;

    magma_dragoon_face_player(self);
    func_80015D60(self, 3);
    magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
    self->unk67 = 1;
    func_8001540C(2, 0, self);
    var_a0 = FIXED(-0.75);
    self->unk6 = (u8)self->unk6 + 1;
    if (self->unk15 != 0) {
        var_a0 = FIXED(0.75);
    }
    self->unk24 = FIXED(4);
    self->unk28 = FIXED(0.03125);
    self->unk20 = var_a0;
    self->unk2C = FIXED(-0.03125);
    self->ext.main_65.jump_start_y = (u16)self->y_pos.i.hi;
}

void magma_dragoon_dive_kick_rise(struct MainObj* self)
{
    if ((self->ext.main_65.jump_start_y - self->y_pos.i.hi) >= 0x51) {
        self->unk6++;
        func_80015D60(self, 4);
        func_8001540C(2, 1, self);
        self->unk60 = 6;
        self->unk24 = FIXED(-6);
        self->unk28 = 0;
        self->unk2C = 0;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E6F8);

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E848);

void magma_dragoon_dive_kick(struct MainObj* self)
{
    magma_dragoon_dive_kick_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_flame_burst_start(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    func_80015D60(ANIMATED_OBJECT(self), 0xB);
    self->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007E95C);

void magma_dragoon_flame_burst(struct MainObj* self)
{
    magma_dragoon_flame_burst_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_fire_volley_start(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    func_80015D60(self, 0xC);
    func_8001540C(2, 3, self);
    self->unk6++;
}

void magma_dragoon_fire_volley_fire(struct MainObj* self)
{
    s8 event;
    s8 shot_index;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    if (event != 0) {
        if (event == 0xA) {
            self->unk7C = 0xF0;
            self->unk6 = (u8)self->unk6 + 1;
        }
        func_800C813C(4, &D_801034B4, self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x29;
            shot->unk2 = 1;
            shot->unk7C = WEAPON_OBJECT(self);
            shot_index = self->animation_step.fields.event;
            if (shot_index == 0xA) {
                self->ext.main_65.object = MAIN_OBJECT(shot);
                shot->unk7 = 1;
            } else {
                shot->unk7 = shot_index - 1;
            }
        }
        if ((u8)self->animation_step.fields.event & 1) {
            func_8001540C(2, 6, shot);
        } else {
            func_8001540C(2, 7, shot);
        }
        self->animation_step.fields.event = 0;
    }
}

void magma_dragoon_fire_volley_wait(struct MainObj* self)
{
    func_80015DC8((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->unk5 = 9;
        self->unk6 = 0;
    }
}

void magma_dragoon_fire_volley(struct MainObj* self)
{
    magma_dragoon_fire_volley_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_breath_start(struct MainObj* self)
{
    if (self->x_pos.i.hi > magma_dragoon_arena_center[0]) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
    func_80015D60(self, 0xA);
    func_8001540C(2, 3, self);
    self->unk6++;
}

void magma_dragoon_breath_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x29;
            shot->unk2 = 2;
            shot->unk7C = WEAPON_OBJECT(self);
        }
        self->ext.main_65.object = (struct MainObj*)shot;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.event == 2) {
        self->ext.main_65.object->unk6++;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 0;
        if (self->ext.main_65.attack == 3) {
            self->unk5 = 0xC;
        } else {
            self->unk5 = 3;
        }
        func_80015D60(self, 0);
    }
}

void magma_dragoon_breath(struct MainObj* self)
{
    magma_dragoon_breath_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_leap_center_start(struct MainObj* self)
{
    s32 var_v1;

    if (self->x_pos.i.hi > magma_dragoon_arena_center[0]) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
    func_80015D60(self, 3);
    magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
    self->unk67 = 1;
    func_8001540C(2, 0, self);
    var_v1 = FIXED(-5);
    if (self->unk15 != 0) {
        var_v1 = FIXED(5);
    }
    self->unk24 = FIXED(3);
    self->unk2C = FIXED(-0.03125);
    self->unk20 = var_v1;
    self->unk28 = 0;
    self->unk50 = (const u8*)&D_80102A70;
    self->unk6++;
}

void magma_dragoon_leap_center_glide(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));

    if (self->y_pos.i.hi < magma_dragoon_arena_ceiling[0]) {
        self->y_pos.i.hi = magma_dragoon_arena_ceiling[0];
        self->unk24 = 0;
        self->unk2C = 0;
    }

    if (self->unk15 == 0
            ? self->x_pos.i.hi < (*magma_dragoon_arena_center - 0x10)
            : (*magma_dragoon_arena_center + 0x10) < self->x_pos.i.hi) {
        self->unk2C = FIXED(0.12109375);
        self->unk6++;
    }
}

void magma_dragoon_leap_center_land(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk6++;
        func_80015D60(self, 6);
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
        self->unk67 = 0;
        func_8001540C(2, 2, self);
    }
}

void magma_dragoon_leap_center_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk50 = (const u8*)&D_80102A6C;
        self->unk6 = 0;
        self->unk5 = 7;
    }
}

void magma_dragoon_leap_center(struct MainObj* self)
{
    magma_dragoon_leap_center_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_leap_wall_start(struct MainObj* self)
{
    self->ext.main_65.leap_frames = 0x40;
    magma_dragoon_face_player(self);
    self->unk24 = FIXED(6);
    self->unk2C = FIXED(0.1875);
    self->unk28 = 0;
    self->unk50 = (const u8*)&D_80102A70;
    func_80015D60(self, 3);
    magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
    self->unk67 = 1;
    func_8001540C(2, 0, self);
    if (self->x_pos.i.hi < magma_dragoon_arena_center[0]) {
        self->ext.main_65.leap_to_right = 1;
    } else {
        self->ext.main_65.leap_to_right = 0;
    }
    self->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007F174);

void magma_dragoon_leap_wall_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        if (self->ext.main_65.attack == 3) {
            self->unk5 = 5;
        } else {
            self->unk5 = 3;
            func_80015D60(self, 0);
        }
        self->unk6 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void magma_dragoon_leap_wall(struct MainObj* self)
{
    magma_dragoon_leap_wall_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_fireball_start(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    func_80015D60(self, 8);
    self->unk50 = (const u8*)&D_80102A70;
    self->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007F404);

void magma_dragoon_fireball(struct MainObj* self)
{
    magma_dragoon_fireball_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_fireball_low_start(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    func_80015D60(self, 9);
    self->unk50 = (const u8*)&D_80102A70;
    self->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007F5B0);

void magma_dragoon_fireball_low(struct MainObj* self)
{
    magma_dragoon_fireball_low_funcs[self->unk6](self);
    if ((u32)(self->animation_step.fields.frame_index - 0x19) < 2U) {
        self->unk54 = (const u8*)&D_80102A68;
    } else {
        self->unk54 = (const u8*)&D_80102A64;
    }
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_rising_punch_start(struct MainObj* self)
{
    self->unk60 = 8;
    magma_dragoon_face_player(self);
    func_80015D60(self, 5);
    func_8001540C(2, 5, self);
    self->unk50 = (const u8*)&D_80102A70;
    self->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007F780);

void magma_dragoon_rising_punch_rise(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 2) {
        self->unk50 = (const u8*)&D_80102A74;
    }

    if (self->unk15 != 0) {
        if (self->unk20 < 0) {
            goto reset_velocity;
        }
    } else if (self->unk20 >= 0) {
    reset_velocity:
        self->unk20 = 0;
        self->unk28 = 0;
    }

    if (self->unk24 < 0) {
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk6++;
        func_80015D60(self, 7);
        self->unk50 = (const u8*)&D_80102A6C;
    }
}

void magma_dragoon_rising_punch_land(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk6++;
        func_80015D60(self, 6);
        self->unk50 = (const u8*)&D_80102A6C;
        self->unk60 = 4;
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
        self->unk67 = 0;
        func_8001540C(2, 2, self);
    }
}

void magma_dragoon_rising_punch_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        return;
    }
    self->unk6 = 0;
    if ((self->y_pos.i.hi <= magma_dragoon_arena_floor[0]) && (self->ext.main_65.attack == 3)) {
        if (self->ext.main_65.attack_repeat++ == 0) {
            return;
        }
    }
    self->unk5 = 9;
}

void magma_dragoon_rising_punch(struct MainObj* self)
{
    magma_dragoon_rising_punch_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FAA4);

void magma_dragoon_stagger_rise(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk24 < 0) {
        self->unk6++;
    }
}

void magma_dragoon_stagger_burn(struct MainObj* self)
{
    struct MainObj* child;

    func_80015DC8(ANIMATED_OBJECT(self));
    child = self->ext.main_65.object;
    if (child->animation_step.fields.relative_step < 0) {
        child->state = 2;
        self->unk24 = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk6++;
    }
}

void magma_dragoon_stagger_fall(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk6++;
        func_80015D60(self, 0);
        if (self->ext.main_65.flash_timer & 1) {
            self->ext.main_65.flash_timer = 0x3D;
        } else {
            self->ext.main_65.flash_timer = 0x3E;
        }
        self->unk7C = 1;
    }
}

void magma_dragoon_stagger_recover(struct MainObj* self)
{
    func_80015DC8((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->unk5 = 9;
        self->unk6 = 0;
    }
}

void magma_dragoon_stagger(struct MainObj* self)
{
    magma_dragoon_stagger_funcs[self->unk6](self);
    func_8002B318((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_hold(struct MainObj* self)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FD24);

void magma_dragoon_death_start(struct MainObj* self)
{
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->unk61 = 0x19;
    self->unk5++;
    self->unk42 &= 0x7FFF;
    func_80015D60(self, 0xD);
    func_80036AE4(0x14, g_Player.unk15);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FF00);

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FFFC);

void magma_dragoon_death_wait_explosion(struct MainObj* self, s32 arg1, s32 arg2)
{
    if (self->ext.main_65.object->active == 0) {
        self->unk5++;
        ((void (*)(u16, u8, s32))func_8002217C)(0xC, 0xFF, arg2);
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_death_wait_dialog(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        func_80015D60(self, 0x13);
        self->unk7C = 0x50;
        self->unk5++;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_death_smoke(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x28;
        self->unk5++;
    }

    if ((self->unk7C & 7) == 0) {
        func_800AFAB4(0, self->x_pos.i.hi + (get_random() & 0x3F) - 0x20,
            self->y_pos.i.hi + (get_random() & 0x1F), 0);
    }

    if ((self->unk7C & 3) == 4) {
        func_800AFAB4(0, self->x_pos.i.hi + (get_random() & 0x3F) - 0x20,
            self->y_pos.i.hi + (get_random() & 0x1F), 1);
    }

    if ((self->unk7C & 3) != 0) {
        func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
    }
}

void magma_dragoon_death_vanish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x1E;
        self->unk5++;
        ZeroObjectState(OBJECT_HEADER(self->ext.main_65.smoke));
    }

    if ((self->unk7C & 7) == 0) {
        func_800AFAB4(0, self->x_pos.i.hi + (get_random() & 0x3F) - 0x20,
            self->y_pos.i.hi + (get_random() & 0x1F), 0);
    }

    if ((self->unk7C & 3) == 4) {
        func_800AFAB4(0, self->x_pos.i.hi + (get_random() & 0x3F) - 0x20,
            self->y_pos.i.hi + (get_random() & 0x1F), 1);
    }

    if ((self->unk7C & 1) != 0) {
        func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
    }
}

void magma_dragoon_death_end(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        engine_obj.unkF = 1;
    }
}

void magma_dragoon_death(struct MainObj* self)
{
    magma_dragoon_death_funcs[self->unk5](self);
}

void magma_dragoon_update(struct MainObj* self)
{
    self->on_screen = 0;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated((struct PlayerObj*)self);
    magma_dragoon_state_funcs[self->state](self);
}
