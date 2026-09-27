// MainObj, main_object_update_funcs[68]
// 80083218..80085F08
#include "common.h"

extern void (*sigma_cloak_teleport_funcs[])(struct MainObj*);

void sigma_intro_wait_player(struct MainObj* self)
{
    struct EffectObj* effect;

    if (g_Player.unkC4 == 0) {
        self->on_screen = 0;
        background_objects[0].unk24 -= 0x10;
        func_80036AE4(0x14, 0x40);
        self->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_68.effect = effect;
        }
    }
}

// sigma_intro_init
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008329C);

void sigma_intro_fill_health(struct MainObj* self)
{
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk7E == 0) {
        if (self->unk5C < 0x30) {
            if (func_8009227C() == 0) {
                temp_v0 = self->unk7C - 1;
                self->unk7C = temp_v0;
                if (temp_v0 == 0) {
                    func_8001540C(0, 0xE, 0);
                    self->unk7C = 2;
                }
                self->unk5C++;
            }
        } else {
            self->unk7C = 0x1E;
            self->unk5++;
        }
    } else {
        self->unk7E--;
    }
    self->on_screen = 0;
    if (D_80141BD8.unk0 & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void sigma_intro_wait(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 3, self);
        self->unk7C = 0x3C;
        self->on_screen = 0;
        self->unk5 += 1;
        func_80036B18();
        return;
    }
    self->on_screen = 0;
    if (D_80141BD8.unk0 & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void sigma_intro_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->state = 1;
        self->unk5 = 2;
    }
}

void sigma_intro(struct MainObj* self)
{
    sigma_intro_funcs[self->unk5](self);
}

void sigma_cloak_teleport_appear(struct MainObj* self)
{
    s16 x_pos;

    self->on_screen = 0;
    self->unk6++;
    self->x_pos.val = g_Player.x_pos.val;
    x_pos = self->x_pos.i.hi;
    if (x_pos < 0x470) {
        self->x_pos.i.hi = 0x470;
    } else if (x_pos >= 0x531) {
        self->x_pos.i.hi = 0x530;
    }
    self->y_pos.val = FIXED(0x150);
    self->unk7C = 5;
    self->ext.main_68.bob_step = 2;
    self->ext.main_68.count = 0;
    self->ext.main_68.active_shots = 0;
    self->unk7E = 4;
    if (self->x_pos.i.hi >= 0x4D1) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
    func_80015D60(self, 0);
    func_80015D60(self->ext.main_68.scythe, 5);
    func_8001540C(2, 3, self);
}

void sigma_cloak_teleport_fade_in(struct MainObj* self)
{
    self->unk54 = (const u8*)&D_80103EE8;
    self->unk50 = (const u8*)&D_80103EE4;
    if (self->unk7C == 0) {
        self->unk7C = 0x28;
        self->unk6++;
        return;
    }
    self->on_screen = 0;
    if (self->unk7C & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
    self->unk7C--;
}

// sigma_cloak_teleport_windup
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083710);

// sigma_cloak_teleport_fire
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_800837FC);

void sigma_cloak_teleport_wait_shots(struct MainObj* self)
{
    if (self->ext.main_68.active_shots == 0) {
        self->unk7C = 0xA;
        self->unk6++;
        func_8001540C(2, 3, self);
    }
    is_on_screen(BASE_OBJECT(self));
}

void sigma_cloak_teleport_fade_out(struct MainObj* self)
{
    s16 timer = self->unk7C - 1;

    self->unk7C = timer;
    if (timer == 0) {
        self->unk7C = 0x78;
        self->unk54 = NULL;
        self->unk50 = NULL;
        self->unk6++;
    }
    self->on_screen = 0;
    if (self->unk7C & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void sigma_cloak_teleport_finish(struct MainObj* self)
{
    s16 timer;
    self->on_screen = 0;
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->x_pos.i.hi = background_objects[0].x_pos.i.hi - 0x100;
    }
}

void sigma_cloak_teleport(struct MainObj* self)
{
    sigma_cloak_teleport_funcs[self->unk6](self);
    func_80015DC8(ANIMATED_OBJECT(self));
    if (D_80141BD8.unk0 % 10 == 0) {
        self->y_pos.i.hi += self->ext.main_68.bob_step;
        if (--self->unk7E == 0) {
            s32 t;
            self->unk7E = 4;
            t = self->ext.main_68.bob_step;
            self->ext.main_68.bob_step = -t;
        }
    }
}

void sigma_cloak_dash_appear(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi >= 0x4D1) {
        self->x_pos.i.hi = 0x460;
        self->unk15 = 0x40;
    } else {
        self->x_pos.i.hi = 0x540;
        self->unk15 = 0;
    }
    self->y_pos.i.hi = 0x150;
    self->unk7C = 0xA;
    self->unk6++;
    func_80015D60(self, 0);
    func_80015D60(self->ext.main_68.scythe, 5);
    func_8001540C(2, 3, self);
}

void sigma_cloak_dash_fade_in(struct MainObj* self)
{
    s16 timer = self->unk7C - 1;

    self->unk7C = timer;
    if (timer == 0) {
        self->unk7C = 0x28;
        self->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    self->on_screen = 0;
    if (self->unk7C & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

// sigma_cloak_dash_start
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80083C2C);

void sigma_cloak_dash_run(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (self->unk70 & 3) {
        self->unk7C = 0xA;
        self->unk68 = NULL;
        self->unk6++;
        func_8001540C(2, 3, self);
        self->unk4B = -1;
        self->ext.main_68.scythe->unk50 = NULL;
    }
    CollisionRelated(PLAYER_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void sigma_cloak_dash_fade_out(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk7C = 0x78;
        self->unk54 = 0;
        self->unk50 = 0;
        self->unk6++;
        self->x_pos.i.hi = background_objects[0].x_pos.u.hi - 0x100;
    }
    self->on_screen = 0;
    if (self->unk7C & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void sigma_cloak_dash_finish(struct MainObj* self)
{
    self->on_screen = 0;
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void sigma_cloak_dash(struct MainObj* self)
{
    sigma_cloak_dash_funcs[self->unk6](self);
}

void sigma_scythe_spin_jump(struct MainObj* self)
{
    s8 state;
    s32 x_pos;

    state = self->unk7;
    if (state == 0) {
        self->unk7 = state + 1;
        x_pos = self->x_pos.val;
        self->unk15 = (g_Player.x_pos.val >= x_pos) << 6;
        func_80015D60(self, 0x16);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk50 = &D_80103F08;
        self->unk7 = 0;
        self->unk54 = &D_80103F0C;
        self->unk6++;
        func_80015D60(self, 0x17);
        func_8001540C(2, 0, self);
    }
}

void sigma_scythe_spin_rise(struct MainObj* self)
{
    func_8002B93C(MOVING_OBJECT(self),
        func_8002B7B0(OBJECT_HEADER(self), FIXED(1232), FIXED(336)) & 0xFF);
    self->unk20 *= 4;
    self->unk24 *= 4;
    if (func_8008318C(self, FIXED(1232), FIXED(336)) & 0xFF) {
        self->unk7C = 0x28;
        self->unk6++;
    }
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

void sigma_scythe_spin_throw(struct MainObj* self)
{
    s16 timer;
    struct ShotObj* shot;

    if (self->unk7 == 0) {
        timer = self->unk7C;
        timer--;
        self->unk7C = timer;
        if (timer == 0) {
            self->unk7++;
            func_80015D60(self, 0x1A);
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            self->animation_step.fields.event = 0;
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x2E;
                shot->unk2 = 7;
                shot->unk7C = WEAPON_OBJECT(self);
                self->ext.main_68.scythe = (struct MainObj*)shot;
            }
        }
        if (self->animation_step.fields.relative_step == 0) {
            self->unk7 = 0;
            self->unk6++;
        }
    }
}

void sigma_scythe_spin_wait(struct MainObj* self)
{
    if (self->ext.main_68.scythe->active == 0) {
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk24 = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk6++;
        func_80015D60(self, 0x18);
        func_80015930(2, 5);
        func_8001540C(2, 8, self);
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void sigma_scythe_spin_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk50 = (const u8*)&D_80103F00;
        self->unk54 = (const u8*)&D_80103F04;
        self->unk6++;
        func_80015D60(self, 0x19);
        func_8001540C(2, 1, self);
    }
}

void sigma_scythe_spin_recover(struct MainObj* self)
{
    func_80015DC8(self);
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void sigma_scythe_spin(struct MainObj* self)
{
    sigma_scythe_spin_funcs[self->unk6](self);
}

void sigma_scythe_plant_jump(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->ext.main_68.next_attack = 0;
        self->unk15 = (self->x_pos.val <= g_Player.x_pos.val) << 6;
        self->unk7 = (u8)(*(volatile u8*)&self->unk7 + 1);
        func_80015D60(self, 0x16);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk24 = FIXED(6.5);
        self->unk2C = FIXED(0.2578125);
        self->unk50 = &D_80103F08;
        self->unk7 = 0;
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk54 = &D_80103F0C;
        self->unk6++;
        func_80015D60(self, 0x17);
        func_8001540C(2, 0, self);
    }
}

void sigma_scythe_plant_apex(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk24 < 0) {
        self->unk24 = 0;
        self->unk2C = 0;
        self->unk6++;
        func_80015D60(self, 0x1A);
    }
}

void sigma_scythe_plant_throw(struct MainObj* self)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x2E;
            shot->unk2 = 3;
            shot->unk7C = WEAPON_OBJECT(self);
            self->ext.main_68.scythe = (struct MainObj*)shot;
        }
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk24 = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk6++;
        func_80015D60(self, 0x13);
    }
}

void sigma_scythe_plant_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk50 = (const u8*)&D_80103F00;
        self->unk54 = (const u8*)&D_80103F04;
        self->unk6++;
        func_80015D60(self, 0x14);
        func_8001540C(2, 1, self);
    }
}

void sigma_scythe_plant_wait(struct MainObj* self)
{
    s8 step;
    u8 index;
    u8 state;

    func_80015DC8(ANIMATED_OBJECT(self));
    step = self->unk7;
    if (step == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk7 = step + 1;
            func_80015D60(self, 0x10);
        }
    } else {
        index = self->ext.main_68.next_attack;
        if (index != 0) {
            state = sigma_scythe_plant_next[index - 1];
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk5 = state;
        }
    }
}

void sigma_scythe_plant(struct MainObj* self)
{
    sigma_scythe_plant_funcs[self->unk6](self);
}

void sigma_cloak_pick_attack(struct MainObj* self)
{
    u8 index;

    self->unk5 = sigma_cloak_pattern[self->ext.main_68.next_attack];
    index = self->ext.main_68.next_attack + 1;
    self->ext.main_68.next_attack = index;
    self->unk54 = (const u8*)&D_80103EF4;
    self->unk6 = 0;
    self->unk7 = 0;
    if (index == 3) {
        self->ext.main_68.next_attack = 0;
    }
}

void sigma_darts_start(struct MainObj* self)
{
    self->unk6++;
    self->unk15 = (self->x_pos.val <= g_Player.x_pos.val) << 6;
    self->ext.main_68.count = 0;
    func_80015D60(self, 0x1B);
}

void sigma_darts_spawn(struct MainObj* self)
{
    u8 var_s1;
    struct ShotObj* temp_v0;

    func_80015DC8(ANIMATED_OBJECT(self));
    var_s1 = 0;
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        self->unk6 = (u8)self->unk6 + 1;
        do {
            temp_v0 = find_free_shot_obj();
            if (temp_v0 != 0) {
                temp_v0->active = 0x41;
                temp_v0->id = 0x2E;
                temp_v0->unk2 = 6;
                temp_v0->timer = var_s1;
                temp_v0->unk7C = WEAPON_OBJECT(self);
                self->ext.main_68.count += 1;
                func_8001540C(2, 0xA, self);
            }
            var_s1 += 1;
        } while (var_s1 < 4);
    }
}

void sigma_darts_pose(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x5A;
        self->unk6++;
        func_80015D60(self, 0x2B);
    }
}

void sigma_darts_wait(struct MainObj* self)
{
    func_80015DC8(self);
    if (--self->unk7C == 0) {
        self->unk5 = 5;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void sigma_darts(struct MainObj* self)
{
    sigma_darts_funcs[self->unk6](self);
}

void sigma_scythe_retrieve_jump(struct MainObj* self)
{
    if (self->unk7 == 0) {
        s32 other_x = self->ext.main_68.scythe->x_pos.val;

        self->unk7 = (u8)(*(volatile u8*)&self->unk7 + 1);
        self->unk15 = (self->x_pos.val < other_x) << 6;
        func_80015D60(self, 0x11);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk50 = &D_80103F08;
        self->unk7 = 0;
        self->unk54 = &D_80103F0C;
        self->unk6 = (u8)self->unk6 + 1;
        func_80015D60(self, 0x12);
        func_8001540C(2, 0, self);
    }
}

void sigma_scythe_retrieve_rise(struct MainObj* self)
{
    struct ObjectHeader* temp_v1;

    func_8002B93C(MOVING_OBJECT(self),
        func_8002B7B0(OBJECT_HEADER(self), FIXED(1232), FIXED(336)) & 0xFF);
    self->unk20 *= 4;
    self->unk24 *= 4;
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (func_8008318C(self, FIXED(1232), FIXED(336)) & 0xFF) {
        temp_v1 = OBJECT_HEADER(self->ext.main_68.scythe);
        self->unk6++;
        temp_v1->unk5++;
    }
}

void sigma_scythe_retrieve_wait(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->ext.main_68.scythe == NULL) {
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk24 = 0;
        self->unk2C = FIXED(0.2578125);
        self->unk6++;
        func_80015D60(self, 0x18);
        func_80015930(2, 5);
        func_8001540C(2, 8, self);
    }
}

void sigma_scythe_retrieve_land(struct MainObj* self)
{
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        self->unk50 = (const u8*)&D_80103F00;
        self->unk54 = (const u8*)&D_80103F04;
        self->unk6++;
        func_80015D60(self, 0x19);
    }
}

void sigma_scythe_retrieve_recover(struct MainObj* self)
{
    func_80015DC8(self);
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 6;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void sigma_scythe_retrieve(struct MainObj* self)
{
    sigma_scythe_retrieve_funcs[self->unk6](self);
}

void sigma_land_pause(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk50 = (const u8*)&D_80103F00;
        self->unk54 = (const u8*)&D_80103F04;
        self->unk6++;
        func_80015D60(self, 0x15);
        self->unk7C = 0x28;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

// sigma_eye_laser_jump
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084B14);

void sigma_eye_laser_fire(struct MainObj* self)
{
    struct QuadObj* quad;
    s8 quad_type;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        func_8001540C(2, 9, self);

        quad = find_free_quad_obj();
        if (quad != 0) {
            quad->active = 1;
            quad->id = 0xF;
            quad->unk2 = (self->unk15 != 0) * 2;
            quad->unk5C = PLAYER_OBJECT(self);
            self->ext.main_68.effect = (struct EffectObj*)quad;
        }

        quad = find_free_quad_obj();
        if (quad != 0) {
            quad->active = 1;
            quad->id = 0xF;
            quad_type = 1;
            if (self->unk15 != 0) {
                quad_type = 3;
            }
            quad->unk2 = quad_type;
            quad->unk5C = PLAYER_OBJECT(self);
            self->ext.main_68.effect = (struct EffectObj*)quad;
        }
    }

    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        func_80015D60(self, 0x1D);
    }
}

void sigma_eye_laser_wait(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (*(s8*)self->ext.main_68.effect == 0) {
        func_80015930(2, 9);
        self->unk5 = 5;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void sigma_eye_laser(struct MainObj* self)
{
    sigma_eye_laser_funcs[self->unk6](self);
}

void sigma_idle(struct MainObj* self)
{
}

void sigma_pose(struct MainObj* self)
{
    struct VisualObj* visual;

    if (self->unk7 == 0) {
        self->unk7++;
        self->unk7C = 0x78;
        func_80015D60(self, 0x29);
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 5;
        }
    } else {
        func_80015DC8(self);
        self->unk7C--;
    }
}

// sigma_cloak_fight
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80084EE4);

// sigma_revealed_fight
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_8008502C);

void sigma_fight(struct BarObj* self)
{
    sigma_fight_funcs[self->unk2](self);
}

void sigma_death_start(struct MainObj* self)
{
    func_80015930(2, 5);
    func_80015930(2, 9);
    func_80036AE4(0x15, 0);
    engine_obj.unk1C = 1;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_68.blink_delay = 0x19;
    self->unk5++;
    func_80015D60(self, 0x29);
    is_on_screen(BASE_OBJECT(self));
}

void sigma_death_blink(struct MainObj* self)
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
            self->ext.main_68.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- == 0) {
        self->ext.main_68.blink_delay -= 5;
        var_a0 = self->ext.main_68.blink_delay;
        self->unk42 ^= 0x8000;
        if (var_a0 < 5) {
            var_a0 = 5;
        }
        self->unk7E = var_a0;
    }
}

void sigma_death_wait_explosion(struct MainObj* self)
{
    struct MainObj* target;

    target = self->ext.main_68.effect;
    self->on_screen = 0;
    if (target->active != 0) {
        if (target->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        func_80036AE4(0x14, 0x40);
        self->unk7C = 0x78;
        self->unk5++;
        background_objects[0].unk28 += 0x100;
    }
}

// sigma_death_explode
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085460);

void sigma_death_finish(struct MainObj* self)
{
    if (background_objects[0].y_pos.i.hi == background_objects[0].unk20) {
        func_800DABE4(7, 0, 0);
        background_objects[0].unk2A = background_objects[0].unk28;
        background_objects[0].unk24 += 0x280;
        func_80036B18();
        g_Player.unk7A = 0;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void sigma_death(struct MainObj* self)
{
    sigma_death_funcs[self->unk5](self);
}

void sigma_cloak_stagger_start(struct MainObj* self)
{
    self->unk4B = -1;
    self->unk7C = 0x40;
    self->unk7E = 4;
    self->unk54 = NULL;
    self->unk42 &= 0x7FFF;
    self->unk5++;
    func_80015D60(self, 8);
    func_80015D60(self->ext.main_68.scythe, 9);
    func_8001540C(2, 4, self);
    is_on_screen(BASE_OBJECT(self));
}

void sigma_cloak_stagger_trail(struct MainObj* self)
{
    struct VisualObj* visual;
    s16 held;

    if (!(D_80141BD8.unk0 & 7)) {
        visual = find_free_visual_obj();
        if (visual != 0) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 2;
            visual->unk50 = PLAYER_OBJECT(self);
        }
    }

    held = self->unk7C - 1;
    self->unk7C = held;
    if (held == 0) {
        self->unk7C = 10;
        self->unk5++;
        func_8001540C(2, 3, self);
    }

    is_on_screen(BASE_OBJECT(self));
}

void sigma_cloak_stagger_fade(struct MainObj* self)
{
    s16 timer = self->unk7C - 1;

    self->unk7C = timer;
    if (timer == 0) {
        self->unk7C = 0x78;
        self->unk5++;
    }
    self->on_screen = 0;
    if (self->unk7C & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void sigma_cloak_stagger_finish(struct MainObj* self)
{
    s16 timer = self->unk7C;
    self->on_screen = 0;
    timer--;
    self->unk7C = timer;
    if (timer == 0) {
        self->state = 1;
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
        self->x_pos.i.hi = background_objects[0].x_pos.i.hi - 0x70;
    }
}

void sigma_cloak_stagger(struct MainObj* self)
{
    sigma_cloak_stagger_funcs[self->unk5](self);
    func_80015DC8(ANIMATED_OBJECT(self));
    if (D_80141BD8.unk0 % 10 == 0) {
        self->y_pos.i.hi += self->ext.main_68.bob_step;
        if (--self->unk7E == 0) {
            s32 t;
            self->unk7E = 4;
            t = self->ext.main_68.bob_step;
            self->ext.main_68.bob_step = -t;
        }
    }
}

void sigma_reveal_start(struct MainObj* self)
{
    u8 state = self->unk5;

    self->unk4B = -1;
    self->unk68 = &D_80103EF0;
    self->unk24 = FIXED(-1);
    self->unk54 = 0;
    self->ext.main_68.count = 0;
    self->unk20 = 0;
    state++;
    self->unk42 &= 0x7FFF;
    self->unk5 = state;
    self->unk15 = (g_Player.x_pos.i.hi >= self->x_pos.i.hi) << 6;
    func_80015D60(self, 8);
    func_8001540C(2, 0xE, self);
    func_80015D60(self->ext.main_68.scythe, 9);
    is_on_screen(BASE_OBJECT(self));
}

void sigma_reveal_fall(struct MainObj* self)
{
    struct VisualObj* temp_v0;

    if (D_80141BD8.unk0 == ((D_80141BD8.unk0 / 5) * 5)) {
        temp_v0 = find_free_visual_obj();
        if (temp_v0 != 0) {
            temp_v0->active = 0x41;
            temp_v0->id = 0x20;
            temp_v0->unk2 = 2;
            temp_v0->unk50 = PLAYER_OBJECT(self);
        }
    }
    if (self->unk70 & 8) {
        self->unk7C = 0x78;
        self->unk5++;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

// sigma_reveal_burn_cloak
INCLUDE_ASM("main/nonmatchings/mains/main_68", func_80085A44);

void sigma_reveal_wait_cloak(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->ext.main_68.count == 0) {
        self->unk5++;
        func_80015D60(self, 0xF);
    }
    is_on_screen(BASE_OBJECT(self));
}

void sigma_reveal_dialogue(struct MainObj* self)
{
    u16 sound_id;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk15 = (g_Player.x_pos.i.hi >= self->x_pos.i.hi) << 6;
            func_80036AE4(0x14, (self->x_pos.i.hi >= g_Player.x_pos.i.hi) << 6);
            self->unk6 = (u8)self->unk6 + 1;
            sound_id = 0x2C;
            if (engine_obj.cur_character == 0) {
                sound_id = 0x31;
            }
            ((void (*)(s32, s32, s32))func_8002217C)(
                sound_id, 0xFFU, engine_obj.character_state.bytes[9]);
            engine_obj.character_state.bytes[9] = 1;
        }
    } else if (abc_object.unkC == 0) {
        self->unk6 = 0;
        self->unk7C = 1;
        self->unk5 = (u8)self->unk5 + 1;
    }
    is_on_screen(BASE_OBJECT(self));
}

void sigma_reveal_fill_health(struct MainObj* self)
{
    u16 temp_v0;

    if (self->unk5C < 0x30) {
        temp_v0 = self->unk7C - 1;
        self->unk7C = temp_v0;
        if ((temp_v0 << 0x10) == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7C = 2;
        }
        self->unk5C = (s8)((u8)self->unk5C + 1);
    } else {
        self->unk7C = 0x5A;
        self->unk5 = (s8)((u8)self->unk5 + 1);
    }
    is_on_screen(BASE_OBJECT(self));
}

void sigma_reveal_finish(struct MainObj* self)
{
    s16 temp_v0;
    unsigned long temp_v1;

    temp_v0 = self->unk7C - 1;
    self->unk7C = temp_v0;
    if (temp_v0 == 0) {
        temp_v1 = 1;
        self->collision_data = (const u16*)D_80108004;
        self->unk50 = (const u8*)&D_80103F00;
        self->unk54 = (const u8*)&D_80103F04;
        self->unk2 = temp_v1;
        self->state = temp_v1;
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
        self->ext.main_68.flash_timer = 0;
        func_80036B18();
        temp_v1 = (unsigned long)self->ext.main_68.scythe;
        ((struct MainObj*)temp_v1)->state++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void sigma_reveal(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    sigma_reveal_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

void sigma_update(struct MainObj* self)
{
    sigma_state_funcs[self->state](self);
}
