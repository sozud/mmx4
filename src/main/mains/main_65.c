// MainObj, main_object_update_funcs[65]
// 8007DD98..800806A0
#include "common.h"
#include "func_tables.h"

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
    player_start_script_action(0x14, 0x40);
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
        player_end_script_action();
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
    player_start_script_action(0x14, g_Player.unk15);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FF00);

INCLUDE_ASM("main/nonmatchings/mains/main_65", func_8007FFFC);

void magma_dragoon_death_wait_explosion(struct MainObj* self, s32 arg1, s32 arg2)
{
    if (self->ext.main_65.object->active == 0) {
        self->unk5++;
#ifdef MMX4_PC
        func_8002217C(0xC, 0xFF, 0);
#else
        ((void (*)(u16, u8, s32))func_8002217C)(0xC, 0xFF, arg2);
#endif
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

#ifdef MMX4_PC
#define MAGMA_DRAGOON_SMOKE(self, kind)                                  \
    do {                                                                 \
        s32 smoke_x = (self)->x_pos.i.hi + (get_random() & 0x3F) - 0x20; \
        s32 smoke_y = (self)->y_pos.i.hi + (get_random() & 0x1F);        \
        func_800AFAB4(0, smoke_x, smoke_y, kind);                        \
    } while (0)
#else
#define MAGMA_DRAGOON_SMOKE(self, kind)                                 \
    func_800AFAB4(0, (self)->x_pos.i.hi + (get_random() & 0x3F) - 0x20, \
        (self)->y_pos.i.hi + (get_random() & 0x1F), kind)
#endif

void magma_dragoon_death_smoke(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x28;
        self->unk5++;
    }

    if ((self->unk7C & 7) == 0) {
        MAGMA_DRAGOON_SMOKE(self, 0);
    }

    if ((self->unk7C & 3) == 4) {
        MAGMA_DRAGOON_SMOKE(self, 1);
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
        MAGMA_DRAGOON_SMOKE(self, 0);
    }

    if ((self->unk7C & 3) == 4) {
        MAGMA_DRAGOON_SMOKE(self, 1);
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

struct Unk_unk68 D_80102A60 = { -1, 22, 13, 17 };

struct Unk_unk68 D_80102A64 = { -16, -28, 31, 67 };

struct Unk_unk68 D_80102A68 = { -13, 18, 41, 21 };

struct Unk_unk68 D_80102A6C = { -10, -19, 16, 58 };

struct Unk_unk68 D_80102A70 = { -2, -20, 19, 44 };

struct Unk_unk68 D_80102A74 = { -32, -54, 38, 76 };

struct Unk_unk68 D_80102A78 = { -41, -12, 22, 45 };

union AnimationStep D_80102A7C[] = {
    { 0x00000001 },
};

struct Unk_unk68 D_80102A80[32] = {
    { 3, 0, 1, 0 },
    { 3, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 6 },
    { 2, 0, 1, 3 },
    { 1, 0, 1, 7 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 2, 0, 1, 5 },
    { 1, 0, 1, 9 },
    { 2, 0, 1, 5 },
    { 1, 0, 1, 9 },
    { 2, 0, 1, 5 },
    { 1, 0, 1, 9 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 2, 0, 1, 3 },
    { 1, 0, 1, 7 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 6 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 6 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 6 },
    { 2, 0, 1, 3 },
    { 1, 0, 1, 7 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 2, 0, 1, 4 },
    { 1, 0, -15, 8 },
};

union AnimationStep D_80102B00[] = {
    { 0x02010002 },
    { 0x04010002 },
    { 0x05010006 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x02010002 },
    { 0x01010003 },
    { 0x00010002 },
    { 0x00000001 },
};

union AnimationStep D_80102B24[] = {
    { 0x0A000001 },
};

struct Unk_unk68 D_80102B28[18] = {
    { 2, 0, 1, -60 },
    { 2, 0, 1, -59 },
    { 2, 0, 1, -60 },
    { 2, 0, 1, -59 },
    { 1, 2, 1, 12 },
    { 1, 1, 1, 12 },
    { 1, 1, 1, -93 },
    { 1, 1, 1, -92 },
    { 1, 1, 1, -91 },
    { 1, 1, 1, -90 },
    { 1, 1, 1, -89 },
    { 1, 1, 1, -86 },
    { 1, 1, 1, -93 },
    { 1, 1, 1, -92 },
    { 1, 1, 1, -91 },
    { 1, 1, 1, -88 },
    { 1, 1, 1, -87 },
    { 1, 1, -11, -86 },
};

struct Unk_unk68 D_80102B70[19] = {
    { 2, 0, 1, 13 },
    { 2, 0, 1, 14 },
    { 2, 0, 1, 13 },
    { 2, 0, 1, 14 },
    { 2, 1, 1, 15 },
    { 2, 0, 1, 16 },
    { 2, 2, 1, 17 },
    { 1, 2, 1, 58 },
    { 1, 2, 1, 59 },
    { 1, 2, 1, 60 },
    { 1, 2, 1, 61 },
    { 1, 2, 1, 62 },
    { 1, 2, 1, 65 },
    { 1, 2, 1, 58 },
    { 1, 2, 1, 59 },
    { 1, 2, 1, 60 },
    { 1, 2, 1, 63 },
    { 1, 2, 1, 64 },
    { 1, 2, -11, 65 },
};

union AnimationStep D_80102BBC[] = {
    { 0x0B000001 },
};

union AnimationStep D_80102BC0[] = {
    { 0x15010001 },
    { 0x16010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x12010102 },
    { 0x13010028 },
    { 0x12010002 },
    { 0x01010003 },
    { 0x00010002 },
    { 0x00000001 },
};

union AnimationStep D_80102C20[] = {
    { 0x17010001 },
    { 0x18010001 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x19010102 },
    { 0x1A010028 },
    { 0x19010002 },
    { 0x01010003 },
    { 0x00010002 },
    { 0x00000001 },
};

union AnimationStep D_80102C80[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x1B010002 },
    { 0x1C010123 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F01021E },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000001 },
};

union AnimationStep D_80102CA8[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x20010003 },
    { 0x21010006 },
    { 0x22010001 },
    { 0x21010002 },
    { 0x22010001 },
    { 0x21010002 },
    { 0x22010001 },
    { 0x21010002 },
    { 0x22010001 },
    { 0x21010002 },
    { 0x22010001 },
    { 0x21010002 },
    { 0x22010001 },
    { 0x21010002 },
    { 0x22010001 },
    { 0x21010002 },
    { 0x22010001 },
    { 0x21010002 },
    { 0x22010001 },
    { 0x2301003C },
    { 0x24010001 },
    { 0x25010001 },
    { 0x24010106 },
    { 0x25010001 },
    { 0x24010206 },
    { 0x25010001 },
    { 0x24010106 },
    { 0x25010001 },
    { 0x24010206 },
    { 0x25010001 },
    { 0x24010106 },
    { 0x25010001 },
    { 0x24010206 },
    { 0x25010001 },
    { 0x24010106 },
    { 0x25010001 },
    { 0x24010206 },
    { 0x25010001 },
    { 0x24010106 },
    { 0x25010001 },
    { 0x24010206 },
    { 0x25010001 },
    { 0x24010106 },
    { 0x25010001 },
    { 0x24010206 },
    { 0x25010001 },
    { 0x24010106 },
    { 0x25010001 },
    { 0x24010206 },
    { 0x25010001 },
    { 0x24010114 },
    { 0x23010003 },
    { 0x01010003 },
    { 0x00010002 },
    { 0x00000001 },
};

u32 D_80102D8C[55] = {
    0x00010003,
    0x01010003,
    0x20010003,
    0x2101000F,
    0x26010003,
    0x27010001,
    0x27010001,
    0x26010001,
    0x2B010101,
    0x28010001,
    0x2C010001,
    0x27010001,
    0x2B010201,
    0x29010001,
    0x2C010001,
    0x27010001,
    0x27010301,
    0x26010001,
    0x2B010001,
    0x28010001,
    0x2C010401,
    0x27010001,
    0x2B010001,
    0x29010001,
    0x2C010501,
    0x27010001,
    0x27010001,
    0x26010001,
    0x2B010601,
    0x28010001,
    0x2C010001,
    0x27010001,
    0x2B010701,
    0x29010001,
    0x2C010001,
    0x27010001,
    0x27010801,
    0x26010001,
    0x2B010001,
    0x28010001,
    0x2C010101,
    0x27010001,
    0x2B010001,
    0x29010001,
    0x2C010A01,
    0x27010001,
    0x27010001,
    0x26010001,
    0x2B010001,
    0x28010001,
    0x2C010001,
    0x27010001,
    0x2B010001,
    0x29010001,
    0x2CF70001,
};

union AnimationStep D_80102E68[] = {
    { 0x2D000001 },
};

struct Unk_unk68 D_80102E6C[12] = {
    { 1, 0, 1, 46 },
    { 1, 0, 1, 47 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 49 },
    { 1, 0, 1, 50 },
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, -11, 57 },
};

struct Unk_unk68 D_80102E9C[3] = {
    { 2, 0, 1, 6 },
    { 1, 0, 1, 86 },
    { 1, 0, -2, 86 },
};

union AnimationStep D_80102EA8[] = {
    { 0x54010002 },
    { 0x55010002 },
    { 0x52010002 },
    { 0x53010002 },
    { 0x52010002 },
    { 0x53010002 },
    { 0x52010002 },
    { 0x53010002 },
    { 0x52010002 },
    { 0x53010002 },
    { 0x52010002 },
    { 0x53010002 },
    { 0x52010002 },
    { 0x53010002 },
    { 0x52010002 },
    { 0x53010002 },
    { 0x52010002 },
    { 0x53010002 },
    { 0x54010002 },
    { 0x55010002 },
    { 0x57010002 },
    { 0x58010002 },
    { 0x59010002 },
    { 0x5A010002 },
    { 0x59010002 },
    { 0x5A010002 },
    { 0x59010002 },
    { 0x5A010002 },
    { 0x59010002 },
    { 0x5A010002 },
    { 0x27010001 },
    { 0x2A010001 },
    { 0x26010001 },
    { 0x2B010001 },
    { 0x28010001 },
    { 0x2C010001 },
    { 0x27010001 },
    { 0x2B010001 },
    { 0x29010001 },
    { 0x2C010001 },
    { 0x27010001 },
    { 0x26010001 },
    { 0x01010001 },
    { 0x00010001 },
    { 0x00000001 },
};

union AnimationStep D_80102F5C[] = {
    { 0x5B000001 },
};

union AnimationStep D_80102F60[] = {
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010002 },
    { 0x0E010001 },
    { 0x0D010027 },
    { 0x0D000001 },
};

struct Unk_unk68 D_80102FC8[3] = {
    { 2, 0, 1, 92 },
    { 1, 0, 1, 93 },
    { 1, 0, -2, 93 },
};

struct Unk_unk68 D_80102FD4[12] = {
    { 50, 0, 1, 92 },
    { 6, 0, 1, 94 },
    { 6, 0, 1, 95 },
    { 5, 0, 1, 94 },
    { 1, 0, 1, 94 },
    { 50, 0, 1, 95 },
    { 2, 0, 1, 96 },
    { 30, 0, 1, 95 },
    { 2, 0, 1, 96 },
    { 6, 0, 1, 95 },
    { 1, 0, 1, 96 },
    { 1, 0, -6, 96 },
};

struct Unk_unk68 D_80103004[29] = {
    { 1, 0, 1, 100 },
    { 1, 0, 1, 101 },
    { 1, 0, 1, 102 },
    { 1, 0, 1, 103 },
    { 1, 0, 1, 104 },
    { 1, 0, 1, 105 },
    { 10, 0, 1, 118 },
    { 1, 0, 1, 106 },
    { 1, 0, 1, 107 },
    { 1, 0, 1, 108 },
    { 1, 0, 1, 109 },
    { 1, 0, 1, 110 },
    { 1, 0, 1, 111 },
    { 30, 0, 1, 118 },
    { 1, 0, 1, 112 },
    { 1, 0, 1, 113 },
    { 1, 0, 1, 114 },
    { 1, 0, 1, 115 },
    { 1, 0, 1, 116 },
    { 1, 0, 1, 117 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 106 },
    { 1, 0, 1, 107 },
    { 1, 0, 1, 108 },
    { 1, 0, 1, 109 },
    { 1, 0, 1, 110 },
    { 1, 0, 1, 111 },
    { 29, 0, 1, 118 },
    { 1, 0, -28, 118 },
};

u8 D_80103078[172] = { 50, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 1, 0, 1, 97, 1, 0, 255, 92 };

union AnimationStep D_80103124[] = {
    { 0x42010001 },
    { 0x43010001 },
    { 0x44010001 },
    { 0x45010001 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x4D010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x50010001 },
    { 0x51000001 },
};

union AnimationStep D_80103150[] = {
    { 0x63010001 },
    { 0x63010001 },
    { 0x63010001 },
    { 0x63010001 },
    { 0x63010001 },
    { 0x63010001 },
    { 0x63010001 },
    { 0x48010001 },
    { 0x49010001 },
    { 0x4A010001 },
    { 0x4B000001 },
};

struct Unk_unk68 D_8010317C[18] = {
    { 1, 0, 1, 119 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 120 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 121 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 122 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 123 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 124 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 125 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 126 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 127 },
    { 1, 0, -13, 118 },
};

union AnimationStep D_801031C4[] = {
    { 0x80010001 },
    { 0x76010001 },
    { 0x81010001 },
    { 0x76010001 },
    { 0x82010001 },
    { 0x76010001 },
    { 0x83010001 },
    { 0x76000001 },
};

union AnimationStep D_801031E4[] = {
    { 0x84010002 },
    { 0x85010002 },
    { 0x86010002 },
    { 0x87010002 },
    { 0x88010002 },
    { 0x89010002 },
    { 0x8A010002 },
    { 0x8B010002 },
    { 0x8C010002 },
    { 0x8D010001 },
    { 0x8D000001 },
};

struct Unk_unk68 D_80103210[11] = {
    { 2, 0, 1, -114 },
    { 2, 0, 1, -113 },
    { 2, 0, 1, -112 },
    { 1, 0, 1, -111 },
    { 1, 0, 1, -110 },
    { 1, 0, 1, -109 },
    { 1, 0, 1, -107 },
    { 1, 0, 1, -111 },
    { 1, 0, 1, -110 },
    { 1, 0, 1, -108 },
    { 1, 0, -7, -107 },
};

struct Unk_unk68 D_8010323C[11] = {
    { 2, 0, 1, -106 },
    { 2, 0, 1, -105 },
    { 2, 0, 1, -104 },
    { 2, 0, 1, -103 },
    { 1, 0, 1, -102 },
    { 2, 0, 1, -101 },
    { 1, 0, 1, -99 },
    { 2, 0, 1, -103 },
    { 1, 0, 1, -102 },
    { 2, 0, 1, -100 },
    { 1, 0, -7, -99 },
};

struct Unk_unk68 D_80103268[8] = {
    { 2, 0, 1, -98 },
    { 1, 0, 1, -97 },
    { 2, 0, 1, -96 },
    { 1, 0, 1, -94 },
    { 2, 0, 1, -98 },
    { 1, 0, 1, -97 },
    { 2, 0, 1, -95 },
    { 1, 0, -7, -94 },
};

struct Unk_unk68 D_80103288[5] = {
    { 2, 0, 1, -85 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, -85 },
    { 1, 0, 1, -84 },
    { 1, 0, -2, -83 },
};

union AnimationStep D_8010329C[] = {
    { 0xAE010001 },
    { 0xAF010002 },
    { 0xB0010002 },
    { 0xB1010001 },
    { 0xB2010001 },
    { 0xB3010001 },
    { 0xB4010001 },
    { 0xB5000001 },
};

union AnimationStep D_801032BC[] = {
    { 0xB6010001 },
    { 0xB7010001 },
    { 0xB8010002 },
    { 0xB9010002 },
    { 0xBA010003 },
    { 0xBB010004 },
    { 0xBC010001 },
    { 0xBD010002 },
    { 0xBE010002 },
    { 0xBF010001 },
    { 0xC0010001 },
    { 0xC1010001 },
    { 0xC2010001 },
    { 0xC3000001 },
};

union AnimationStep D_801032F4[] = {
    { 0xC6010001 },
    { 0xC7010001 },
    { 0xC8010001 },
    { 0xC9010001 },
    { 0xCA000001 },
};

struct Unk_unk68 D_80103308[31] = {
    { 1, 0, 1, -53 },
    { 1, 0, 1, -52 },
    { 1, 0, 1, -51 },
    { 1, 0, 1, -50 },
    { 1, 0, 1, -49 },
    { 1, 0, 1, -48 },
    { 1, 0, 1, -47 },
    { 1, 0, 1, -46 },
    { 1, 0, 1, -53 },
    { 1, 0, 1, -52 },
    { 1, 0, 1, -51 },
    { 1, 0, 1, -50 },
    { 1, 0, 1, -49 },
    { 1, 0, 1, -48 },
    { 1, 1, 1, -47 },
    { 1, 0, 1, -53 },
    { 1, 0, 1, -52 },
    { 1, 0, 1, -51 },
    { 1, 0, 1, -50 },
    { 1, 0, 1, -49 },
    { 1, 0, 1, -48 },
    { 1, 0, 1, -47 },
    { 1, 0, 1, -46 },
    { 1, 0, 1, -53 },
    { 1, 0, 1, -52 },
    { 1, 0, 1, -51 },
    { 1, 0, 1, -50 },
    { 1, 0, 1, -49 },
    { 1, 0, 1, -48 },
    { 1, 2, 1, -47 },
    { 1, 0, -30, -46 },
};

union AnimationStep D_80103384[] = {
    { 0x03010002 },
    { 0x07010001 },
    { 0x04010002 },
    { 0x08010001 },
    { 0x04010004 },
    { 0x03010003 },
    { 0x02010003 },
    { 0x01010003 },
    { 0x00010004 },
    { 0x00000001 },
};

union AnimationStep D_801033AC[] = {
    { 0xD3010001 },
    { 0x76010001 },
    { 0xD4010001 },
    { 0x76010001 },
    { 0xD5010001 },
    { 0x76010001 },
    { 0xD6010001 },
    { 0x76010001 },
    { 0xD7010001 },
    { 0x76010001 },
    { 0xD8010001 },
    { 0x76010001 },
    { 0xD9010001 },
    { 0x76010001 },
    { 0xDA010001 },
    { 0x76000001 },
};

union AnimationStep D_801033EC[] = {
    { 0xDB010001 },
    { 0x76010001 },
    { 0xDC010001 },
    { 0x76010001 },
    { 0xDD010001 },
    { 0x76010001 },
    { 0xDE010001 },
    { 0x76010001 },
    { 0xDF010001 },
    { 0x76010001 },
    { 0xE0010001 },
    { 0x76000001 },
};

void* magma_dragoon_animations[38] = {
    D_80102A7C,
    D_80102A80,
    D_80102B00,
    D_80102B24,
    D_80102B28,
    D_80102B70,
    D_80103384,
    D_80102BBC,
    D_80102BC0,
    D_80102C20,
    D_80102C80,
    D_80102CA8,
    D_80102D8C,
    D_80102E68,
    D_80102E6C,
    D_80102E9C,
    D_80102EA8,
    D_80102F5C,
    D_80102F60,
    D_80102FC8,
    D_80102FD4,
    D_80103004,
    D_80103078,
    D_80103150,
    D_80103124,
    D_8010317C,
    D_801031C4,
    D_801031E4,
    D_80103210,
    D_8010323C,
    D_80103268,
    D_80103288,
    D_8010329C,
    D_801032BC,
    D_801032F4,
    D_80103308,
    D_801033AC,
    D_801033EC,
};

struct Unk_unk68 D_801034B4 = { 36, 37, 36, 37 };

void (*magma_dragoon_intro_funcs[8])() = {
    magma_dragoon_intro_warning,
    magma_dragoon_intro_leap,
    magma_dragoon_intro_descend,
    magma_dragoon_intro_land,
    magma_dragoon_intro_pose,
    magma_dragoon_intro_start_health_bar,
    magma_dragoon_intro_ready,
    func_8007E350,
};

void (*magma_dragoon_dive_kick_funcs[4])() = {
    magma_dragoon_dive_kick_jump,
    magma_dragoon_dive_kick_rise,
    func_8007E6F8,
    func_8007E848,
};

void (*magma_dragoon_flame_burst_funcs[2])() = {
    magma_dragoon_flame_burst_start,
    func_8007E95C,
};

void (*magma_dragoon_fire_volley_funcs[3])() = {
    magma_dragoon_fire_volley_start,
    magma_dragoon_fire_volley_fire,
    magma_dragoon_fire_volley_wait,
};

void (*magma_dragoon_breath_funcs[2])() = {
    magma_dragoon_breath_start,
    magma_dragoon_breath_fire,
};

void (*magma_dragoon_leap_center_funcs[4])() = {
    magma_dragoon_leap_center_start,
    magma_dragoon_leap_center_glide,
    magma_dragoon_leap_center_land,
    magma_dragoon_leap_center_recover,
};

void (*magma_dragoon_leap_wall_funcs[3])() = {
    magma_dragoon_leap_wall_start,
    func_8007F174,
    magma_dragoon_leap_wall_finish,
};

void (*magma_dragoon_fireball_funcs[2])() = {
    magma_dragoon_fireball_start,
    func_8007F404,
};

void (*magma_dragoon_fireball_low_funcs[2])(struct MainObj*) = {
    magma_dragoon_fireball_low_start,
    func_8007F5B0,
};

void (*magma_dragoon_rising_punch_funcs[5])() = {
    magma_dragoon_rising_punch_start,
    func_8007F780,
    magma_dragoon_rising_punch_rise,
    magma_dragoon_rising_punch_land,
    magma_dragoon_rising_punch_recover,
};

void (*magma_dragoon_stagger_funcs[5])() = {
    func_8007FAA4,
    magma_dragoon_stagger_rise,
    magma_dragoon_stagger_burn,
    magma_dragoon_stagger_fall,
    magma_dragoon_stagger_recover,
};

void (*magma_dragoon_step_funcs[14])() = {
    func_8009216C,
    magma_dragoon_hold,
    magma_dragoon_intro,
    func_8007E4C8,
    magma_dragoon_dive_kick,
    magma_dragoon_flame_burst,
    magma_dragoon_fire_volley,
    magma_dragoon_breath,
    magma_dragoon_leap_center,
    magma_dragoon_leap_wall,
    magma_dragoon_fireball,
    magma_dragoon_fireball_low,
    magma_dragoon_rising_punch,
    magma_dragoon_stagger,
};

void (*magma_dragoon_death_funcs[8])() = {
    magma_dragoon_death_start,
    func_8007FF00,
    func_8007FFFC,
    magma_dragoon_death_wait_explosion,
    magma_dragoon_death_wait_dialog,
    magma_dragoon_death_smoke,
    magma_dragoon_death_vanish,
    magma_dragoon_death_end,
};

void (*magma_dragoon_state_funcs[3])() = {
    func_8007DD98,
    func_8007FD24,
    magma_dragoon_death,
};
