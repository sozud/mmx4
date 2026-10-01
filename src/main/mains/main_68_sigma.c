// MainObj, main_object_update_funcs[68]
// 80083218..80085F08
#include "common.h"
#include "func_tables.h"

extern void (*sigma_cloak_teleport_funcs[])(struct MainObj*);

void sigma_intro_wait_player(struct MainObj* self)
{
    struct EffectObj* effect;

    if (g_Player.capsule_state == 0) {
        self->on_screen = 0;
        background_objects[0].unk24 -= 0x10;
        player_start_script_action(0x14, 0x40);
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
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_8008329C);

void sigma_intro_fill_health(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (self->unk7E == 0) {
        if (self->hp < 0x30) {
            if (update_boss_music_delay() == 0) {
                if (--self->unk7C == 0) {
                    func_8001540C(0, 0xE, 0);
                    self->unk7C = 2;
                }
                self->hp++;
            }
        } else {
            self->unk7C = 0x1E;
            self->unk5++;
        }
    } else {
        self->unk7E--;
    }
    self->on_screen = 0;
    if (BLINK_TIMER.unk0 & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void sigma_intro_wait(struct MainObj* self)
{

    if (--self->unk7C == 0) {
        func_8001540C(2, 3, self);
        self->unk7C = 0x3C;
        self->unk5 += 1;
        self->on_screen = 0;
        player_end_script_action();
        return;
    }
    self->on_screen = 0;
    if (BLINK_TIMER.unk0 & 1) {
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
    } else if (x_pos > 0x530) {
        self->x_pos.i.hi = 0x530;
    }
    self->y_pos.val = FIXED(0x150);
    self->unk7C = 5;
    self->ext.main_68.count = 0;
    self->ext.main_68.active_shots = 0;
    self->ext.main_68.bob_step = 2;
    self->unk7E = 4;
    if (self->x_pos.i.hi > 0x4D0) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
    set_animation(self, 0);
    set_animation(self->ext.main_68.scythe, 5);
    func_8001540C(2, 3, self);
}

void sigma_cloak_teleport_fade_in(struct MainObj* self)
{
    self->hurt_box = (const u8*)&D_80103EE8;
    self->attack_box = (const u8*)&D_80103EE4;
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
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_80083710);

// sigma_cloak_teleport_fire
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_800837FC);

void sigma_cloak_teleport_wait_shots(struct MainObj* self)
{
    if (self->ext.main_68.active_shots == 0) {
        self->unk6++;
        self->unk7C = 0xA;
        func_8001540C(2, 3, self);
    }
    is_on_screen(BASE_OBJECT(self));
}

void sigma_cloak_teleport_fade_out(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x78;
        self->hurt_box = NULL;
        self->unk6++;
        self->attack_box = NULL;
    }
    self->on_screen = 0;
    if (self->unk7C & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void sigma_cloak_teleport_finish(struct MainObj* self)
{
    self->on_screen = 0;
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->x_pos.i.hi = background_objects[0].x_pos.i.hi - 0x100;
    }
}

void sigma_cloak_teleport(struct MainObj* self)
{
    sigma_cloak_teleport_funcs[self->unk6](self);
    animate_object(ANIMATED_OBJECT(self));
    if (D_80141BD8.unk0 % 10 == 0) {
        self->y_pos.i.hi += self->ext.main_68.bob_step;
        if (--self->unk7E == 0) {
            self->unk7E = 4;
            self->ext.main_68.bob_step *= -1;
        }
    }
}

void sigma_cloak_dash_appear(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi > 0x4D0) {
        self->x_pos.i.hi = 0x460;
        self->unk15 = 0x40;
    } else {
        self->x_pos.i.hi = 0x540;
        self->unk15 = 0;
    }
    self->y_pos.i.hi = 0x150;
    self->unk7C = 0xA;
    self->unk6++;
    set_animation(self, 0);
    set_animation(self->ext.main_68.scythe, 5);
    func_8001540C(2, 3, self);
}

void sigma_cloak_dash_fade_in(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x28;
        self->unk6++;
    }
    animate_object(ANIMATED_OBJECT(self));
    self->on_screen = 0;
    if (self->unk7C & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

// sigma_cloak_dash_start
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_80083C2C);

void sigma_cloak_dash_run(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->collision_flags & 3) {
        self->unk6++;
        self->unk7C = 0xA;
        self->terrain_box = NULL;
        func_8001540C(2, 3, self);
        self->unk4B = -1;
        self->ext.main_68.scythe->attack_box = NULL;
    }
    CollisionRelated(PLAYER_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void sigma_cloak_dash_fade_out(struct MainObj* self)
{

    if (--self->unk7C == 0) {
        self->unk7C = 0x78;
        self->hurt_box = 0;
        self->unk6++;
        self->attack_box = 0;
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
    s8 state = self->unk7;

    if (state == 0) {
        self->unk7 = state + 1;
        self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : 0x40;
        set_animation(self, 0x16);
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        self->unk7 = 0;
        self->attack_box = &D_80103F08;
        self->hurt_box = &D_80103F0C;
        set_animation(self, 0x17);
        func_8001540C(2, 0, self);
    }
}

void sigma_scythe_spin_rise(struct MainObj* self)
{
    set_velocity_from_angle(MOVING_OBJECT(self),
        angle_to_point(OBJECT_HEADER(self), FIXED(1232), FIXED(336)) & 0xFF);
    self->x_speed *= 4;
    self->y_speed *= 4;
    if (gunship_is_within(self, FIXED(1232), FIXED(336)) & 0xFF) {
        self->unk7C = 0x28;
        self->unk6++;
    }
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void sigma_scythe_spin_throw(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->unk7 == 0) {
        if (--self->unk7C == 0) {
            self->unk7++;
            set_animation(self, 0x1A);
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
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
        self->unk6++;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        set_animation(self, 0x18);
        stop_sound(2, 5);
        func_8001540C(2, 8, self);
    }
    animate_object(ANIMATED_OBJECT(self));
}

void sigma_scythe_spin_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        self->attack_box = (const u8*)&D_80103F00;
        self->hurt_box = (const u8*)&D_80103F04;
        set_animation(self, 0x19);
        func_8001540C(2, 1, self);
    }
}

void sigma_scythe_spin_recover(struct MainObj* self)
{
    animate_object(self);
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
        self->unk15 = self->x_pos.val <= g_Player.x_pos.val ? 0x40 : 0;
        self->unk7 = (u8)(*(volatile u8*)&self->unk7 + 1);
        set_animation(self, 0x16);
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        self->unk7 = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = FIXED(6.5);
        self->gravity = FIXED(0.2578125);
        self->attack_box = &D_80103F08;
        self->hurt_box = &D_80103F0C;
        set_animation(self, 0x17);
        func_8001540C(2, 0, self);
    }
}

void sigma_scythe_plant_apex(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_speed < 0) {
        self->unk6++;
        self->y_speed = 0;
        self->gravity = 0;
        set_animation(self, 0x1A);
    }
}

void sigma_scythe_plant_throw(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
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
        self->unk6++;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        set_animation(self, 0x13);
    }
}

void sigma_scythe_plant_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        self->attack_box = (const u8*)&D_80103F00;
        self->hurt_box = (const u8*)&D_80103F04;
        set_animation(self, 0x14);
        func_8001540C(2, 1, self);
    }
}

void sigma_scythe_plant_wait(struct MainObj* self)
{
    s8 step;
    u8 state;

    animate_object(ANIMATED_OBJECT(self));
    step = self->unk7;
    if (step == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk7 = step + 1;
            set_animation(self, 0x10);
        }
    } else {
        if (self->ext.main_68.next_attack != 0) {
            state = sigma_scythe_plant_next[self->ext.main_68.next_attack - 1];
            self->unk6 = 0;
            self->unk5 = state;
            self->unk7 = 0;
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
    self->hurt_box = (const u8*)&D_80103EF4;
    self->unk6 = 0;
    index = self->ext.main_68.next_attack + 1;
    self->unk7 = 0;
    self->ext.main_68.next_attack = index;
    if (index == 3) {
        self->ext.main_68.next_attack = 0;
    }
}

void sigma_darts_start(struct MainObj* self)
{
    self->unk6++;
    self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : 0x40;
    self->ext.main_68.count = 0;
    set_animation(self, 0x1B);
}

void sigma_darts_spawn(struct MainObj* self)
{
    u8 var_s1;
    struct ShotObj* temp_v0;

    animate_object(ANIMATED_OBJECT(self));
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
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        self->unk7C = 0x5A;
        set_animation(self, 0x2B);
    }
}

void sigma_darts_wait(struct MainObj* self)
{
    animate_object(self);
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

        self->unk15 = self->ext.main_68.scythe->x_pos.val > self->x_pos.val ? 0x40 : 0;

        self->unk7 = (u8)(*(volatile u8*)&self->unk7 + 1);
        set_animation(self, 0x11);
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = (u8)self->unk6 + 1;
        self->unk7 = 0;
        self->attack_box = &D_80103F08;
        self->hurt_box = &D_80103F0C;
        set_animation(self, 0x12);
        func_8001540C(2, 0, self);
    }
}

void sigma_scythe_retrieve_rise(struct MainObj* self)
{
    struct ObjectHeader* temp_v1;

    set_velocity_from_angle(MOVING_OBJECT(self),
        angle_to_point(OBJECT_HEADER(self), FIXED(1232), FIXED(336)) & 0xFF);
    self->x_speed *= 4;
    self->y_speed *= 4;
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (gunship_is_within(self, FIXED(1232), FIXED(336)) & 0xFF) {
        self->unk6++;
        temp_v1 = OBJECT_HEADER(self->ext.main_68.scythe);
        temp_v1->unk5++;
    }
}

void sigma_scythe_retrieve_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->ext.main_68.scythe == NULL) {
        self->unk6++;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        set_animation(self, 0x18);
        stop_sound(2, 5);
        func_8001540C(2, 8, self);
    }
}

void sigma_scythe_retrieve_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        self->attack_box = (const u8*)&D_80103F00;
        self->hurt_box = (const u8*)&D_80103F04;
        set_animation(self, 0x19);
    }
}

void sigma_scythe_retrieve_recover(struct MainObj* self)
{
    animate_object(self);
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
        self->attack_box = (const u8*)&D_80103F00;
        self->hurt_box = (const u8*)&D_80103F04;
        self->unk6++;
        set_animation(self, 0x15);
        self->unk7C = 0x28;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

// sigma_eye_laser_jump
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_80084B14);

void sigma_eye_laser_fire(struct MainObj* self)
{
    struct QuadObj* quad;
    s8 quad_type;

    animate_object(ANIMATED_OBJECT(self));
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
        set_animation(self, 0x1D);
    }
}

void sigma_eye_laser_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (*(s8*)self->ext.main_68.effect == 0) {
        stop_sound(2, 9);
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
        set_animation(self, 0x29);
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 5;
        }
    } else {
        animate_object(self);
        self->unk7C--;
    }
}

// sigma_cloak_fight
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_80084EE4);

// sigma_revealed_fight
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_8008502C);

void sigma_fight(struct BarObj* self)
{
    sigma_fight_funcs[self->unk2](self);
}

void sigma_death_start(struct MainObj* self)
{
    stop_sound(2, 5);
    stop_sound(2, 9);
    player_start_script_action(0x15, 0);
    engine_obj.unk1C = 1;
    self->unk5++;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_68.blink_delay = 0x19;
    set_animation(self, 0x29);
    is_on_screen(BASE_OBJECT(self));
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", sigma_death_blink);
#else
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
        self->unk42 ^= 0x8000;
        self->ext.main_68.blink_delay -= 5;
        var_a0 = self->ext.main_68.blink_delay;
        self->unk7E = var_a0 > 5 ? var_a0 : 5;
    }
}
#endif

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
        player_start_script_action(0x14, 0x40);
        self->unk7C = 0x78;
        self->unk5++;
        background_objects[0].unk28 += 0x100;
    }
}

// sigma_death_explode
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_80085460);

void sigma_death_finish(struct MainObj* self)
{
    if (background_objects[0].y_pos.i.hi == background_objects[0].unk20) {
        apply_tile_effect(7, 0, 0);
        background_objects[0].unk2A = background_objects[0].unk28;
        background_objects[0].unk24 += 0x280;
        player_end_script_action();
        g_Player.spike_immune = 0;
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
    self->hurt_box = NULL;
    self->unk42 &= 0x7FFF;
    self->unk5++;
    set_animation(self, 8);
    set_animation(self->ext.main_68.scythe, 9);
    func_8001540C(2, 4, self);
    is_on_screen(BASE_OBJECT(self));
}

void sigma_cloak_stagger_trail(struct MainObj* self)
{
    struct VisualObj* visual;

    if (!(D_80141BD8.unk0 % 8)) {
        visual = find_free_visual_obj();
        if (visual != 0) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 2;
            visual->unk50 = PLAYER_OBJECT(self);
        }
    }

    if (--self->unk7C == 0) {
        self->unk5++;
        self->unk7C = 10;
        func_8001540C(2, 3, self);
    }

    is_on_screen(BASE_OBJECT(self));
}

void sigma_cloak_stagger_fade(struct MainObj* self)
{
    if (--self->unk7C == 0) {
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
    animate_object(ANIMATED_OBJECT(self));
    if (D_80141BD8.unk0 % 10 == 0) {
        self->y_pos.i.hi += self->ext.main_68.bob_step;
        if (--self->unk7E == 0) {
            self->unk7E = 4;
            self->ext.main_68.bob_step *= -1;
        }
    }
}

void sigma_reveal_start(struct MainObj* self)
{
    u8 state = self->unk5;

    self->unk4B = -1;
    self->terrain_box = &D_80103EF0;
    self->y_speed = FIXED(-1);
    self->hurt_box = 0;
    self->ext.main_68.count = 0;
    self->x_speed = 0;
    state++;
    self->unk42 &= 0x7FFF;
    self->unk5 = state;
    self->unk15 = g_Player.x_pos.i.hi < self->x_pos.i.hi ? 0 : 0x40;
    set_animation(self, 8);
    func_8001540C(2, 0xE, self);
    set_animation(self->ext.main_68.scythe, 9);
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
    if (self->collision_flags & 8) {
        self->unk7C = 0x78;
        self->unk5++;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

// sigma_reveal_burn_cloak
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", func_80085A44);

void sigma_reveal_wait_cloak(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->ext.main_68.count == 0) {
        self->unk5++;
        set_animation(self, 0xF);
    }
    is_on_screen(BASE_OBJECT(self));
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_68_sigma", sigma_reveal_dialogue);
#else
void sigma_reveal_dialogue(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk15 = g_Player.x_pos.i.hi < self->x_pos.i.hi ? 0 : 0x40;
            player_start_script_action(0x14, (self->x_pos.i.hi >= g_Player.x_pos.i.hi) << 6);
            self->unk6 = (u8)self->unk6 + 1;
            ((void (*)(u16, u8, s8))func_8002217C)(
                (engine_obj.cur_character == 0 ? 0x31 : 0x2C), 0xFFU, engine_obj.character_state.bytes[9]);
            engine_obj.character_state.bytes[9] = 1;
        }
    } else if (abc_object.unkC == 0) {
        self->unk6 = 0;
        self->unk7C = 1;
        self->unk5 = (u8)self->unk5 + 1;
    }
    is_on_screen(BASE_OBJECT(self));
}
#endif

void sigma_reveal_fill_health(struct MainObj* self)
{
    u16 temp_v0;

    if (self->hp < 0x30) {
        temp_v0 = --self->unk7C;
        if ((temp_v0 << 0x10) == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7C = 2;
        }
        self->hp = (s8)((u8)self->hp + 1);
    } else {
        self->unk7C = 0x5A;
        self->unk5 = (s8)((u8)self->unk5 + 1);
    }
    is_on_screen(BASE_OBJECT(self));
}

void sigma_reveal_finish(struct MainObj* self)
{
    unsigned long temp_v1;

    if (--self->unk7C == 0) {
        temp_v1 = 1;
        self->unk2 = temp_v1;
        self->collision_data = (const u16*)D_80108004;
        self->attack_box = (const u8*)&D_80103F00;
        self->hurt_box = (const u8*)&D_80103F04;
        self->state = temp_v1;
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
        self->ext.main_68.flash_timer = 0;
        player_end_script_action();
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

struct Unk_unk68 D_80103EE4 = { -14, -21, 29, 57 };

struct Unk_unk68 D_80103EE8 = { -21, -26, 41, 61 };

struct Unk_unk68 D_80103EEC = { 0, 0, 13, 25 };

struct Unk_unk68 D_80103EF0 = { 0, 40, 37, 6 };

struct Unk_unk68 D_80103EF4 = { -9, -19, 27, 56 };

struct Unk_unk68 D_80103EF8 = { -18, -23, 29, 56 };

struct Unk_unk68 D_80103EFC = { -36, -18, 53, 53 };

struct Unk_unk68 D_80103F00 = { -19, -21, 25, 66 };

struct Unk_unk68 D_80103F04 = { -25, -27, 40, 72 };

struct Unk_unk68 D_80103F08 = { -11, -34, 21, 67 };

struct Unk_unk68 D_80103F0C = { -19, -37, 37, 78 };

struct Unk_unk68 D_80103F10[4] = {
    { 58, 0, 1, 0 },
    { 8, 0, 1, 22 },
    { 33, 0, 1, 22 },
    { 8, 0, -3, 21 },
};

struct Unk_unk68 D_80103F20[3] = {
    { 1, 0, 1, 1 },
    { 1, 0, 1, 2 },
    { 1, 0, -2, 3 },
};

union AnimationStep D_80103F2C[] = {
    { 0x04010005 },
    { 0x05010004 },
    { 0x09010003 },
    { 0x0D010015 },
    { 0x09010003 },
    { 0x05010003 },
    { 0x04010003 },
    { 0x11000121 },
};

u32 D_80103F4C[38] = {
    0x21010005,
    0x06010001,
    0x07010001,
    0x08010001,
    0x06010001,
    0x07010001,
    0x0A010001,
    0x0B010001,
    0x0C010001,
    0x0E010001,
    0x0F010001,
    0x10010001,
    0x0E010001,
    0x0F010001,
    0x10010001,
    0x0E010001,
    0x0F010001,
    0x10010001,
    0x0E010001,
    0x0F010001,
    0x10010001,
    0x0E010001,
    0x0F010001,
    0x10010001,
    0x0E010001,
    0x0F010001,
    0x10010001,
    0x0E010001,
    0x0A010001,
    0x0B010001,
    0x0C010001,
    0x06010001,
    0x07010001,
    0x08010001,
    0x21010103,
    0x12010101,
    0x13010101,
    0x14FE0101,
};

struct Unk_unk68 D_80103FE4[3] = {
    { 3, 0, 1, 27 },
    { 3, 0, 1, 28 },
    { 3, 0, -2, 29 },
};

struct Unk_unk68 D_80103FF0[3] = {
    { 3, 0, 1, 30 },
    { 3, 0, 1, 31 },
    { 3, 0, -2, 32 },
};

union AnimationStep D_80103FFC[] = {
    { 0x17000021 },
};

struct Unk_unk68 D_80104000[3] = {
    { 1, 0, 1, 24 },
    { 1, 0, 1, 25 },
    { 1, 0, -2, 26 },
};

u8 D_8010400C[8] = { 1, 0, 1, 0, 3, 0, 255, 34 };

u8 D_80104014[8] = { 1, 0, 1, 1, 3, 0, 255, 35 };

struct Unk_unk68 D_8010401C[11] = {
    { 2, 0, 1, 36 },
    { 2, 0, 1, 37 },
    { 2, 0, 1, 38 },
    { 2, 0, 1, 39 },
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 42 },
    { 2, 0, 1, 43 },
    { 2, 0, 1, 44 },
    { 2, 0, 1, 45 },
    { 5, 1, -10, 33 },
};

struct Unk_unk68 D_80104048[4] = {
    { 2, 0, 1, 46 },
    { 2, 0, 1, 47 },
    { 2, 0, 1, 48 },
    { 2, 0, -3, 49 },
};

struct Unk_unk68 D_80104058[4] = {
    { 2, 0, 1, 50 },
    { 2, 0, 1, 51 },
    { 2, 0, 1, 52 },
    { 2, 0, -3, 53 },
};

u8 D_80104068[8] = { 1, 0, 1, 54, 3, 0, 255, 55 };

union AnimationStep D_80104070[] = {
    { 0x39010003 },
    { 0x38010003 },
    { 0x39010003 },
    { 0x38010003 },
    { 0x39010003 },
    { 0x38010003 },
    { 0x39010003 },
    { 0x38010003 },
    { 0x39000021 },
};

union AnimationStep D_80104094[] = {
    { 0x3C010005 },
    { 0x3A010005 },
    { 0x3B01000C },
    { 0x3A010003 },
    { 0x3C010003 },
    { 0x3D010003 },
    { 0x3C000021 },
};

struct Unk_unk68 D_801040B0[4] = {
    { 21, 0, 1, 62 },
    { 8, 0, 1, 64 },
    { 21, 0, 1, 63 },
    { 8, 0, -3, 64 },
};

union AnimationStep D_801040C0[] = {
    { 0x41010008 },
    { 0x42010003 },
    { 0x41010004 },
    { 0x41000001 },
};

u8 D_801040D0[8] = { 5, 0, 1, 67, 5, 0, 255, 68 };

u8 D_801040D8[8] = { 5, 0, 1, 69, 5, 0, 255, 70 };

union AnimationStep D_801040E0[] = {
    { 0x41010003 },
    { 0x4201000C },
    { 0x41010005 },
    { 0x3F010005 },
    { 0x3E000008 },
};

struct Unk_unk68 D_801040F4[4] = {
    { 21, 0, 1, 71 },
    { 8, 0, 1, 73 },
    { 21, 0, 1, 72 },
    { 8, 0, -3, 73 },
};

union AnimationStep D_80104104[] = {
    { 0x4A010008 },
    { 0x4B010003 },
    { 0x4A010004 },
    { 0x4A000001 },
};

u8 D_80104114[8] = { 5, 0, 1, 76, 5, 0, 255, 77 };

u8 D_8010411C[8] = { 5, 0, 1, 78, 5, 0, 255, 79 };

union AnimationStep D_80104124[] = {
    { 0x4A010003 },
    { 0x4B01000C },
    { 0x4A010005 },
    { 0x48010005 },
    { 0x47000008 },
};

union AnimationStep D_80104138[] = {
    { 0x50010005 },
    { 0x5101000C },
    { 0x50010005 },
    { 0x52010003 },
    { 0x5301010C },
    { 0x43010004 },
    { 0x43000001 },
};

union AnimationStep D_80104154[] = {
    { 0x3C010019 },
    { 0x3A010005 },
    { 0x3B01000F },
    { 0x3A010005 },
    { 0x90010105 },
    { 0x91010002 },
    { 0x90010028 },
    { 0x90000001 },
};

union AnimationStep D_80104174[] = {
    { 0x54010005 },
    { 0x55010019 },
    { 0x55010003 },
    { 0x39010105 },
    { 0x38000003 },
};

u8 D_80104188[8] = { 3, 0, 1, 57, 3, 0, 255, 56 };

struct Unk_unk68 D_80104190[4] = {
    { 1, 0, 1, 86 },
    { 1, 0, 1, 87 },
    { 1, 0, 1, 88 },
    { 1, 0, -3, 89 },
};

struct Unk_unk68 D_801041A0[3] = {
    { 1, 0, 1, 90 },
    { 1, 0, 1, 91 },
    { 1, 0, -2, 92 },
};

struct Unk_unk68 D_801041AC[3] = {
    { 1, 0, 1, 93 },
    { 1, 0, 1, 94 },
    { 1, 0, -2, 95 },
};

struct Unk_unk68 D_801041B8[12] = {
    { 1, 0, 1, 107 },
    { 1, 0, 1, 106 },
    { 1, 0, 1, 105 },
    { 1, 0, 1, 104 },
    { 1, 0, 1, 103 },
    { 1, 0, 1, 102 },
    { 1, 0, 1, 101 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 99 },
    { 1, 0, 1, 98 },
    { 1, 0, 1, 97 },
    { 1, 0, -11, 96 },
};

union AnimationStep D_801041E8[] = {
    { 0x6C010002 },
    { 0x6D010002 },
    { 0x6E010002 },
    { 0x6F010002 },
    { 0x70010102 },
    { 0x71010002 },
    { 0x72000002 },
};

struct Unk_unk68 D_80104204[4] = {
    { 2, 0, 1, 115 },
    { 2, 0, 1, 116 },
    { 2, 0, 1, 117 },
    { 2, 0, -3, 118 },
};

union AnimationStep D_80104214[] = {
    { 0x77010002 },
    { 0x78010002 },
    { 0x79010002 },
    { 0x7A010002 },
    { 0x7B010102 },
    { 0x7C010002 },
    { 0x7D000002 },
};

union AnimationStep D_80104230[] = {
    { 0x7E010002 },
    { 0x7F010002 },
    { 0x80010002 },
    { 0x81FD0002 },
};

union AnimationStep D_80104240[] = {
    { 0x82010001 },
    { 0x83010001 },
    { 0x84010001 },
    { 0x85010001 },
    { 0x86010001 },
    { 0x87000001 },
};

union AnimationStep D_80104258[] = {
    { 0x88000001 },
};

union AnimationStep D_8010425C[] = {
    { 0x89000001 },
};

union AnimationStep D_80104260[] = {
    { 0x8A000001 },
};

struct Unk_unk68 D_80104264[4] = {
    { 1, 0, 1, -114 },
    { 1, 0, 1, -115 },
    { 1, 0, 1, -116 },
    { 1, 0, -3, -117 },
};

union AnimationStep D_80104274[] = {
    { 0x3A010005 },
    { 0x3B01000C },
    { 0x3A010003 },
    { 0x3C010003 },
    { 0x8F010003 },
    { 0x3C010020 },
    { 0x3C000001 },
};

void* sigma_animations[44] = {
    D_80103F10,
    D_80103F2C,
    D_80103FE4,
    D_80103FF0,
    D_80103FFC,
    D_80103F20,
    D_80103F4C,
    D_80104000,
    D_8010400C,
    D_80104014,
    D_8010401C,
    D_80104048,
    D_80104058,
    D_80104068,
    D_80104070,
    D_80104094,
    D_801040B0,
    D_801040C0,
    D_801040D0,
    D_801040D8,
    D_801040E0,
    D_801040F4,
    D_80104104,
    D_80104114,
    D_8010411C,
    D_80104124,
    D_80104138,
    D_80104154,
    D_80104174,
    D_80104188,
    D_80104190,
    D_801041A0,
    D_801041AC,
    D_801041B8,
    D_801041E8,
    D_80104204,
    D_80104214,
    D_80104230,
    D_80104240,
    D_80104258,
    D_8010425C,
    D_80104260,
    D_80104264,
    D_80104274,
};

void (*sigma_intro_funcs[5])(struct MainObj*) = {
    sigma_intro_wait_player,
    func_8008329C,
    sigma_intro_fill_health,
    sigma_intro_wait,
    sigma_intro_finish,
};

void (*sigma_cloak_teleport_funcs[7])(struct MainObj*) = {
    sigma_cloak_teleport_appear,
    sigma_cloak_teleport_fade_in,
    func_80083710,
    func_800837FC,
    sigma_cloak_teleport_wait_shots,
    sigma_cloak_teleport_fade_out,
    sigma_cloak_teleport_finish,
};

void (*sigma_cloak_dash_funcs[6])() = {
    sigma_cloak_dash_appear,
    sigma_cloak_dash_fade_in,
    func_80083C2C,
    sigma_cloak_dash_run,
    sigma_cloak_dash_fade_out,
    sigma_cloak_dash_finish,
};

void (*sigma_scythe_spin_funcs[6])(struct MainObj*) = {
    sigma_scythe_spin_jump,
    sigma_scythe_spin_rise,
    sigma_scythe_spin_throw,
    sigma_scythe_spin_wait,
    sigma_scythe_spin_land,
    sigma_scythe_spin_recover,
};

u8 sigma_scythe_plant_next[4] = { 0x07, 0x04, 0x00, 0x00 };

void (*sigma_scythe_plant_funcs[5])(struct MainObj*) = {
    sigma_scythe_plant_jump,
    sigma_scythe_plant_apex,
    sigma_scythe_plant_throw,
    sigma_scythe_plant_land,
    sigma_scythe_plant_wait,
};

u8 sigma_cloak_pattern[4] = { 0x03, 0x03, 0x04, 0x00 };

void (*sigma_darts_funcs[4])() = {
    sigma_darts_start,
    sigma_darts_spawn,
    sigma_darts_pose,
    sigma_darts_wait,
};

void (*sigma_scythe_retrieve_funcs[5])(struct MainObj*) = {
    sigma_scythe_retrieve_jump,
    sigma_scythe_retrieve_rise,
    sigma_scythe_retrieve_wait,
    sigma_scythe_retrieve_land,
    sigma_scythe_retrieve_recover,
};

void (*sigma_eye_laser_funcs[3])(struct MainObj*) = {
    func_80084B14,
    sigma_eye_laser_fire,
    sigma_eye_laser_wait,
};

void (*sigma_cloak_step_funcs[5])() = {
    enemy_hit_reaction,
    sigma_idle,
    sigma_cloak_pick_attack,
    sigma_cloak_teleport,
    sigma_cloak_dash,
};

void (*sigma_step_funcs[9])() = {
    enemy_hit_reaction,
    sigma_idle,
    sigma_scythe_spin,
    sigma_scythe_plant,
    sigma_darts,
    sigma_scythe_retrieve,
    sigma_land_pause,
    sigma_eye_laser,
    sigma_pose,
};

void (*sigma_fight_funcs[2])() = {
    func_80084EE4,
    func_8008502C,
};

s16 D_8010442C[16] = {
    (s16)0x000F,
    (s16)0xFFF2,
    (s16)0x0007,
    (s16)0x000E,
    (s16)0xFFF2,
    (s16)0xFFFF,
    (s16)0x0028,
    (s16)0xFFF5,
    (s16)0xFFC6,
    (s16)0x0003,
    (s16)0x0040,
    (s16)0xFFF0,
    (s16)0xFFEB,
    (s16)0x000A,
    (s16)0xFFC8,
    (s16)0x001E,
};

void (*sigma_death_funcs[5])(struct MainObj*) = {
    sigma_death_start,
    sigma_death_blink,
    sigma_death_wait_explosion,
    func_80085460,
    sigma_death_finish,
};

void (*sigma_cloak_stagger_funcs[4])(struct MainObj*) = {
    sigma_cloak_stagger_start,
    sigma_cloak_stagger_trail,
    sigma_cloak_stagger_fade,
    sigma_cloak_stagger_finish,
};

void (*sigma_reveal_funcs[7])(struct MainObj*) = {
    sigma_reveal_start,
    sigma_reveal_fall,
    func_80085A44,
    sigma_reveal_wait_cloak,
    sigma_reveal_dialogue,
    sigma_reveal_fill_health,
    sigma_reveal_finish,
};

void (*sigma_state_funcs[5])() = {
    sigma_intro,
    sigma_fight,
    sigma_death,
    sigma_cloak_stagger,
    sigma_reveal,
};
