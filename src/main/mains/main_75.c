// MainObj, main_object_update_funcs[75]
// 8008FB38..800919C4
#include "common.h"

void general_intro_wait_player(struct MainObj* self)
{
    struct EffectObj* effect;

    if (g_Player.unkC4 == 0) {
        if (g_Player.x_pos.i.hi >= 0xD31) {
            background_objects[1].unk3 = 0;
        }
        self->active |= 4;
        func_80036AE4(0x14, 0x40);
        self->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_75.object.effect = effect;
        }
    }
}

// general_intro_init
INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FBCC);

void general_intro_lock_camera(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi >= 0xDF1) {
        self->unk5++;
        self->ext.main_75.background_unk1E = background_objects[0].unk1E;
        func_80036AE4(0x14, 0x40);
        background_objects[0].unk26 = 0xDD0;
        background_objects[0].unk2A = 0x190;
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = self;
    }
}

void general_intro_enter(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
            func_80015D60(self, 1);
            self->unk6++;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            self->animation_step.fields.event = 0;
            func_80015D60(self->ext.main_75.thruster, 2);
            self->ext.main_75.thruster->timer = 1;
            self->ext.main_75.thruster->unk84.shot_55.x = 0x18;
            self->ext.main_75.thruster->unk84.shot_55.y = 0;
        }
        if (self->animation_step.fields.relative_step == 0) {
            self->unk6 = 0;
            self->unk5++;
            func_80015D60(self, 3);
            func_80015D60(self->ext.main_75.thruster, 4);
        }
    }
}

void general_intro_land(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->ext.main_75.thruster->animation_step.fields.relative_step == 0) {
        self->unk5++;
        self->ext.main_75.object.shot->unk5++;
        func_8001540C(2, 8, self);
        self->unk7C = 0x1E;
    }
}

void general_intro_dialogue(struct MainObj* self)
{
    u16 sound_id;

    if (self->unk6 == 0) {
        if (--self->unk7C == 0) {
            if (engine_obj.stage == 0xB) {
                sound_id = 0x21;
                if (engine_obj.cur_character == 0) {
                    sound_id = 0x29;
                }
                ((void (*)(u16, u8, s8))func_8002217C)(
                    sound_id, 0xFF, engine_obj.character_state.bytes[8]);
                engine_obj.character_state.bytes[8] = 1;
            }
            self->unk6++;
        }
    } else if (abc_object.unkC == 0) {
        self->unk6 = 0;
        self->unk5++;
        func_800921E8(0xB);
        self->unk7C = 1;
    }
}

void general_intro_fill_health(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (func_8009227C() != 0) {
        return;
    }

    if (self->unk5C < 0x30) {
        if (--self->unk7C == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7C = 2;
        }
        self->unk5C++;
    } else {
        self->unk5++;
        background_objects[0].unk26 = self->ext.main_75.background_unk1E;
        background_objects[0].unk48 = 2;
    }
}

void general_intro_finish(struct MainObj* self)
{
    if (background_objects[0].unk1E == background_objects[0].unk26) {
        func_80036B18();
        background_objects[0].unk48 = 8;
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
        self->state++;
    }
}

void general_intro(struct MainObj* self)
{
    general_intro_funcs[self->unk5](self);
    if (self->unk5 >= 2) {
        func_8002B318(BASE_OBJECT(self), 0xA0, 0xA0);
    }
}

void general_rise(struct MainObj* self)
{
    u8 temp_unk6;

    if (self->unk7 == 0) {
        self->unk7++;
        func_80015D60(self, 8);
        func_80015D60(self->ext.main_75.thruster, 5);
        self->ext.main_75.thruster->unk84.shot_55.x = 0x18;
        self->ext.main_75.thruster->unk84.shot_55.y = 4;
        self->unk24 = FIXED(0.5);
        self->unk7C = 0x3C;
        self->unk68 = &D_801059D8;
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
        func_8002B718(MOVING_OBJECT(self));
        if (--self->unk7C == 0) {
            temp_unk6 = self->unk6;
            self->unk5 = 2;
            self->unk7 = 0;
            *(volatile u8*)&self->unk6 = temp_unk6 + 1;
            self->unk6 = 0;
        }
    }
}

// general_move
INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8009027C);

void general_fly_descend(struct MainObj* self)
{
    self->unk6++;
    func_80015D60(self->ext.main_75.thruster, 6);
    func_8001540C(2, 2, self);
    self->unk20 = 0;
    self->unk24 = FIXED(-0.5);
    self->ext.main_75.random_index = (get_random() & 0xFF) % 3U;
    self->unk7C = self->ext.main_75.random_index * 0x3C;
}

void general_fly_start(struct MainObj* self)
{
    s16 temp_v0;
    s16 var_a0;
    s32 var_v1;
    struct WeaponObj* weapon;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    temp_v0 = self->unk7C;
    if (temp_v0 == 0) {
        self->unk6++;
        func_80015930(2, 2);
        func_80015D60(self->ext.main_75.thruster, 5);
        func_8001540C(2, 1, self);
        var_v1 = FIXED(-2);
        if (self->unk15 != 0) {
            var_v1 = FIXED(2);
        }
        self->unk68 = &D_801059D8;
        self->unk20 = var_v1;
        weapon = (struct WeaponObj*)self->ext.main_75.thruster;
        var_a0 = 0x18;
        self->unk24 = 0;
        if (self->unk15 != 0) {
            var_a0 = -0x18;
        }
        ((u16*)&weapon->unk84)[0] = var_a0;
        ((u16*)&self->ext.main_75.thruster->unk84)[1] = 4;
        return;
    }
    self->unk7C = temp_v0 - 1;
}

// general_fly_cross
INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800905D4);

void general_fly(struct MainObj* self)
{
    general_fly_funcs[self->unk6](self);
}

void general_punch_rise(struct MainObj* self)
{
    struct ShotObj* shot;
    s16 timer;
    s16 x_offset;
    s8 state;

    state = self->unk7;
    if (state == 0) {
        self->unk7++;
        func_80015D60(self, 8);
        func_80015D60(self->ext.main_75.thruster, 5);
        func_8001540C(2, 1, self);
        shot = self->ext.main_75.thruster;
        x_offset = 0x18;
        if (self->unk15 != 0) {
            x_offset = -0x18;
        }
        shot->unk84.shot_55.x = x_offset;
        self->ext.main_75.thruster->unk84.shot_55.y = 4;
        self->unk24 = FIXED(0.5);
        self->unk7C = 0x3C;
        self->unk68 = &D_801059D8;
        self->ext.main_75.bob_step = 1;
        self->unk20 = 0;
        self->ext.main_75.bob_timer = 0xA;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk7 = 0;
        self->unk6++;
        func_80015D60(self, 0xB);
        func_80015930(2U, 1U);
        func_80015D60(self->ext.main_75.thruster, 7);
        self->unk24 = 0;
    }
}

void general_punch_launch(struct MainObj* self)
{
    struct ShotObj* first;
    struct ShotObj* second;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        first = find_free_shot_obj();
        if (first != NULL) {
            first->active = 0x41;
            first->id = 0x37;
            first->unk2 = 2;
            first->unk7C = WEAPON_OBJECT(self);
            D_8013B8C0 = first;
        }
        second = find_free_shot_obj();
        if (second != NULL) {
            second->active = 0x41;
            second->id = 0x37;
            second->unk2 = 3;
            second->unk7C = WEAPON_OBJECT(self);
            D_8013B8C4 = second;
        }
        first->unk8C.shot = second;
        second->unk8C.shot = first;
    }
    if (self->animation_step.fields.frame_index == 0x1E) {
        shot = self->ext.main_75.thruster;
        shot->unk84.shot_55.x = self->unk15 != 0 ? -0x20 : 0x20;
        self->ext.main_75.thruster->unk84.shot_55.y = -4;
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void general_punch_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6++;
        func_80015D60(self, 0xC);
        self->unk7C = 0x46;
        self->unk7E = 0;
    }
}

void general_punch_rings(struct MainObj* self)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = self->unk7E + 4;
            shot->unk7C = WEAPON_OBJECT(self);
            self->unk7E ^= 1;
        }
        self->unk7C = 0x3C;
    }
}

void general_punch_wait_return(struct MainObj* self)
{
    s16 timer;

    timer = D_8013B8C0->timer;
    if ((timer == 0x80) && (D_8013B8C4->timer == timer)) {
        self->unk6++;
        D_8013B8C0->state++;
        D_8013B8C4->state++;
        func_80015D60(self, 0x17);
    }
}

void general_punch_recover(struct MainObj* self)
{
    func_80015DC8((struct AnimatedObj*)self);
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void general_punch(struct MainObj* self)
{
    general_punch_funcs[self->unk6](self);
    if ((self->unk6 >= 3) && (D_80141BD8.unk0 % 10 == 0)) {
        u8 unk93;
        self->y_pos.i.hi += self->ext.main_75.bob_step;
        unk93 = --self->ext.main_75.bob_timer;
        if (unk93 == 0) {
            self->ext.main_75.bob_timer = 0xA;
            self->ext.main_75.bob_step *= -1;
        }
    }
}

void general_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_75.saved_unk5;
}

void general_orbs_descend(struct MainObj* self)
{
    self->unk6++;
    func_80015D60(self->ext.main_75.thruster, 6);
    func_8001540C(2, 2, NULL);
    self->unk24 = FIXED(-0.5);
    self->unk7C = 0x64;
    self->ext.main_75.bob_step = 1;
    self->unk20 = 0;
    self->ext.main_75.orbs_ready = 0;
    self->ext.main_75.bob_timer = 0xA;
}

void general_orbs_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
        func_80015930(2, 2);
        func_80015D60(self->ext.main_75.thruster, 7);
        self->unk6++;
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = 9;
            shot->unk7C = WEAPON_OBJECT(self);
        }
        func_8001540C(2, 3, self);
    }
}

void general_orbs_wait(struct MainObj* self)
{
    if (self->ext.main_75.orbs_ready != 0) {
        self->unk7C = 0x78;
        self->unk6++;
    }
}

void general_orbs_recover(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void general_orbs(struct MainObj* self)
{
    general_orbs_funcs[self->unk6](self);
    if (D_80141BD8.unk0 % 10 == 0) {
        u8 unk93;
        self->y_pos.i.hi += self->ext.main_75.bob_step;
        unk93 = --self->ext.main_75.bob_timer;
        if (unk93 == 0) {
            self->ext.main_75.bob_timer = 0xA;
            self->ext.main_75.bob_step *= -1;
        }
    }
}

void general_slam_windup(struct MainObj* self)
{
    struct ShotObj* shot;
    s16 var_a0;
    u8 direction;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk7 == 0) {
        if (--self->unk7C == 0) {
            self->unk7++;
            func_80015D60(self, 9);
            func_80015D60(self->ext.main_75.thruster, 6);
            func_8001540C(2, 2, 0);
            direction = self->unk15;
            shot = self->ext.main_75.thruster;
            var_a0 = 0x18;
            if (direction != 0) {
                var_a0 = -0x18;
            }
            shot->unk84.shot_55.x = var_a0;
            self->ext.main_75.thruster->unk84.shot_55.y = -0x10;
            self->unk68 = &D_801059DC;
        }
    } else if (self->animation_step.fields.event != 0) {
        self->unk20 = 0;
        self->unk24 = FIXED(-5);
        self->unk7 = 0;
        self->unk6++;
    }
}

void general_slam_fall(struct MainObj* self)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk6++;
        func_80015930(2, 2);
        func_80015D60(self, 0xA);
        func_8001540C(2, 0, self);
        self->ext.main_75.thruster->timer = 0;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = 6;
            shot->unk7C = WEAPON_OBJECT(self);
        }
        func_80028B68(0x14, 4, 2);
    }
}

void general_slam_land(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 0x28;
        self->unk6++;
    }
}

void general_slam_rise(struct MainObj* self)
{
    s16 temp_v0;
    s16 var_a0;
    u8 temp_unk15;
    struct ShotObj* weapon_view;

    temp_v0 = self->unk7C;
    if (temp_v0 == 0) {
        func_80015DC8(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step == 0) {
            self->unk6++;
            func_80015D60(self, 8);
            func_80015D60(self->ext.main_75.thruster, 5);
            func_8001540C(2, 1, self);
            self->ext.main_75.thruster->timer = 1;
            temp_unk15 = self->unk15;
            weapon_view = self->ext.main_75.thruster;
            var_a0 = 0x18;
            if (temp_unk15 != 0) {
                var_a0 = -0x18;
            }
            weapon_view->unk84.halves[0] = var_a0;
            self->ext.main_75.thruster->unk84.halves[1] = 4;
            self->unk24 = FIXED(5);
            self->unk7C = 0xF;
            self->unk20 = 0;
            self->unk68 = &D_801059D8;
        }
    } else {
        self->unk7C = temp_v0 - 1;
    }
}

void general_slam_ascend(struct MainObj* self)
{
    s32 velocity;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk6++;
        velocity = FIXED(-2);
        if (self->unk15 != 0) {
            velocity = FIXED(2);
        }
        self->unk20 = velocity;
        self->unk24 = 0;
    }
}

void general_slam_leave(struct MainObj* self)
{
    u8 flags;
    u8 reset;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    flags = self->unk70;
    reset = 0;
    if (flags & 3) {
        if (self->unk15 != 0) {
            reset = flags & 1;
        } else if (flags & 2) {
            reset = 1;
        }
        if (reset != 0) {
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk20 = 0;
            self->unk15 ^= 0x40;
        }
    }
}

void general_slam(struct MainObj* self)
{
    general_slam_funcs[self->unk6](self);
}

// general_fight
INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091218);

void general_death_start(struct MainObj* self)
{
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_75.blink_delay = 0x19;
    g_Player.unkBA = 0;
    background_objects[0].unk26 = background_objects[0].x_pos.u.hi;
    func_80036AE4(0x15, 0);
    self->unk6 = 0;
    self->unk5++;
    self->unk42 &= 0x7FFF;
    func_80015D60(self, 0x24);
    self->ext.main_75.thruster->timer = 0;
    self->ext.main_75.bob_timer = 0xA;
    self->ext.main_75.bob_step = 1;
}

void general_death_blink(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 var_a0;

    if (--self->unk7C == 0) {
        self->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = -0x7F;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_75.object.effect = effect;
        }
    }
    if (self->unk7E-- == 0) {
        self->ext.main_75.blink_delay -= 5;
        var_a0 = self->ext.main_75.blink_delay;
        self->unk42 ^= 0x8000;
        if (var_a0 < 5) {
            var_a0 = 5;
        }
        self->unk7E = var_a0;
    }
}

// general_death_explode
INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800915C4);

void general_death_wait_explosion(struct MainObj* self)
{
    if (self->ext.main_75.object.child->active == 0) {
        func_80036AE4(0x14, 0x40);
        self->unk7C = 0x78;
        self->unk5++;
    }
}

// general_death_finish
INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800917AC);

// general_death
INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091898);

void general_update(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    general_state_funcs[self->state](self);
}

void (*general_state_funcs[])(struct MainObj*) = {
    general_intro,
    func_80091218,
    func_80091898,
};
