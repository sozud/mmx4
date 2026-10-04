// MainObj, main_object_update_funcs[74]
// 8008D3B8..8008FA0C
#include "common.h"
#include "func_tables.h"

// double_init

// double_intro_warning

void double_intro_dialogue(struct MainObj* self);

void double_intro_wait_dialogue(struct MainObj* self);

void double_intro_voice(struct MainObj* self);

void double_intro_fill_health(struct MainObj* self);

void double_intro_talk(struct MainObj* self);

void double_intro(struct MainObj* self);

void double_face_player(struct MainObj* self);

void double_spawn_shot(struct MainObj* self, s32 arg1, s32 arg2);

void double_spawn_afterimage(struct MainObj* self, s8 arg1);

void double_wait_start(struct MainObj* self);

// double_pick_attack

void double_wait(struct MainObj* self);

void double_energy_ball_windup(struct MainObj* self);

void double_spawn_shot(struct MainObj*, s32, s32);

void double_energy_ball_throw(struct MainObj* self);

void double_energy_ball_recover(struct MainObj* self);

void double_energy_ball(struct MainObj* self);

void double_dive_leap(struct MainObj* self);

void double_dive_rise(struct MainObj* self);

void double_dive_climb(struct MainObj* self);

void double_dive_aim(struct MainObj* self);

void double_dive_fall(struct MainObj* self);

// double_dive_slide

void double_dive_hit_wall(struct MainObj* self);

void double_dive_stun(struct MainObj* self);

void double_dive_land(struct MainObj* self);

void double_dive(struct MainObj* self);

void double_aerial_shot_jump(struct MainObj* self);

void double_aerial_shot_fire(struct MainObj* self);

void double_aerial_shot_hang(struct MainObj* self);

void double_aerial_shot_fire_again(struct MainObj* arg);

// double_aerial_shot_wait

void double_aerial_shot_drop(struct MainObj* self);

void double_aerial_shot_land(struct MainObj* self);

void double_aerial_shot(struct MainObj* self);

// double_run

void double_death_flicker(struct MainObj* self);

void double_death_start(struct MainObj* self);

void double_death_fall(struct MainObj* self);

void double_death_wait(struct MainObj* self);

void double_death_wait_dialogue(struct MainObj* self);

void double_death_blink(struct MainObj* self);

void double_death_wait_explosion(struct MainObj* self);

void double_death_finish(struct MainObj* self);

void double_death(struct MainObj* self);

void double_update(struct MainObj* self);

s32 sigma_spawn_sequencer(struct MainObj* self, s8 arg1)
{
    struct EffectObj* effect;

    self->ext.main_73_parts.object_id = arg1;
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x2A;
        effect->unk2 = 0;
        effect->ext.effect_42.owner.main = self;
        sigma_sequencer = effect;
    }
}

void sigma_emit_explosions(struct MainObj* self)
{
    if (--self->ext.main_74.unk97 == 0) {
        self->ext.main_74.unk97 = 4;
        func_800AF95C(OBJECT_HEADER(self), 1, 0x60, 0x60, 2);
    }
}

void sigma_final_intro_lock_camera(struct MainObj* self)
{
    D_8013B8B8 = 0;
    self->ext.main_74.death_kind = 0;
    self->ext.main_74.pattern_index = 0;
    background_objects[0].unk26 = 0x410;
    background_objects[0].unk24 = 0x480;
    background_objects[0].unk2A = 0x200;
    background_objects[0].unk28 = 0x200;
    player_start_script_action(0x14, 0x40);
    self->ext.main_74.timer = 0x64;
    self->unk5++;
    func_80016FB4(3);
}

void sigma_final_intro_start_music(struct MainObj* self)
{
    if (--self->ext.main_74.timer == 0) {
        func_80013AD8(
#ifdef VERSION_JP
            0x80,
#elif defined(VERSION_EU)
            0x82,
#else
            0x81,
#endif
            4, D_80141F30[2]);
        self->unk5++;
    }
}

void sigma_final_intro_wait_load(struct MainObj* self)
{
    if ((D_801406AC == 2) && (D_8013BD40 == 0)) {
        D_80171EA8 = 1;
        self->unk5++;
    }
}

void sigma_final_intro_load(struct MainObj* self)
{
    func_8001653C();
    self->unk5++;
}

// sigma_final_init
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", func_8008D5C8);

extern void* D_8013B8B4;
#define MAIN_74_COLLISION_BOUNDS D_8013B8B4

void sigma_final_set_target(struct MainObj* self, s32 arg1)
{
    switch (arg1 & 0xFF) {
    case 0:
        D_8013B8B0 = 0;
        MAIN_74_COLLISION_BOUNDS = 0;
        self->attack_box = 0;
        break;
    case 1:
        D_8013B8B0 = &D_80105368;
        MAIN_74_COLLISION_BOUNDS = &D_8010536C;
        self->hp = self->ext.main_74.upper_health;
        self->unk5D = self->ext.main_74.upper_health;
        self->attack_box = &D_8010535C;
        break;
    case 2:
        D_8013B8B0 = 0;
        MAIN_74_COLLISION_BOUNDS = &D_80105370;
        self->hp = self->ext.main_74.lower_health;
        self->unk5D = self->ext.main_74.lower_health;
        self->attack_box = &D_80105360;
        break;
    }

    self->ext.main_74.target = arg1;
}

void sigma_final_intro(struct MainObj* self)
{
    sigma_final_intro_funcs[self->unk5](self);
}

void sigma_final_idle(struct MainObj* self)
{
}

void sigma_final_appear_start(struct MainObj* self)
{
    self->x_pos.i.hi = 0x567;
    self->y_pos.i.hi = 0x287;
    self->unk6++;
    set_animation(self, 0x18);
    func_8001540C(2, 9, self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_appear_pose(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk6++;
        if (engine_obj.cur_character == 0) {
            func_8002217C(0x32, 0xFF, 0);
        } else {
            func_8002217C(0x2D, 0xFF, 0);
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_appear_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        sigma_final_set_target(self, 1);
        self->unk7E = 3;
        self->unk6++;
        play_boss_voice(0xC);
    }
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_appear_fill_health(struct MainObj* self)
{

    if (self->hp < 0x30) {
        if (update_boss_music_delay() == 0) {
            if (--self->unk7E == 0) {
                func_8001540C(0, 0xE, 0);
                self->unk7E = 3;
            }
            self->hp++;
        }
    } else {
        set_animation(self, 0);
        self->unk5 = 2;
        self->unk6 = 0;
        *D_8013B8A0 = 0xA;
        D_8013B8B0 = &D_80105368;
        MAIN_74_COLLISION_BOUNDS = &D_8010536C;
        player_end_script_action();
    }
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_appear(struct MainObj* self)
{
    sigma_final_appear_funcs[self->unk6](self);
}

// sigma_final_pick_attack
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", func_8008DAE8);

void sigma_final_laser_start(struct MainObj* self)
{
    sigma_spawn_sequencer(self, 5);
    self->unk7C = 5;
    self->unk6++;
}

void sigma_final_laser_aim(struct MainObj* self)
{
    if (g_Player.y_pos.i.hi < 0x250) {
        self->ext.main_74.animation_index = 3;
    } else if (g_Player.y_pos.i.hi < 0x270) {
        self->ext.main_74.animation_index = 2;
    } else if (g_Player.y_pos.i.hi < 0x290) {
        self->ext.main_74.animation_index = 1;
    } else {
        self->ext.main_74.animation_index = 0;
    }
    set_animation(self,
        sigma_final_laser_animations[self->ext.main_74.animation_index * 2]);
    self->unk6++;
}

void sigma_final_laser_fire(struct PlayerObj* player)
{
    struct QuadObj* quad;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(player));
    if (player->animation_step.fields.relative_step < 0) {
        player->unk6 += 1;
        func_8001540C(2, 5, player);

        quad = find_free_quad_obj();
        if (quad != 0) {
            quad->active = 1;
            quad->id = 0x10;
            quad->unk2 = player->attack_ended;
            quad->unk5C = player;
        }
        D_8013B8A8 = OBJECT_HEADER(quad);

        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 1;
            shot->id = 0x39;
            shot->unk2 = player->attack_ended;
            shot->unk7C = WEAPON_OBJECT(player);
        }
    }
}

void sigma_final_laser_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (D_8013B8A8->active == 0) {
        stop_sound(2, 5);
        self->unk6++;
        set_animation(self,
            sigma_final_laser_animations[self->ext.main_74.animation_index * 2 + 1]);
    }
}

void sigma_final_laser_repeat(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        if (--self->unk7C == 0) {
            self->unk5 = 5;
            self->unk6 = 0;
        } else {
            self->unk6 = 1;
        }
    }
}

void sigma_final_laser(struct MainObj* self)
{
    sigma_final_laser_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_big_beam_start(struct MainObj* self)
{
    self->ext.main_74.animation_index = 1;
    set_animation(self, 0x1D);
    sigma_spawn_sequencer(self, 3);
    func_8001540C(2, 6, self);
    func_8001540C(2, 1, self);
    self->unk6++;
}

void sigma_final_big_beam_charge(struct MainObj* self)
{
    struct MiscObj* miscObj;
    struct ShotObj* shotObj;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        miscObj = find_free_misc_obj();
        if (miscObj != NULL) {
            miscObj->active = 0x41;
            miscObj->id = 0x37;
            miscObj->unk2 = self->ext.main_74.animation_index;
            miscObj->ext.misc_55.owner = self;
        }
        shotObj = find_free_shot_obj();
        if (shotObj != NULL) {
            shotObj->active = 1;
            shotObj->id = 0x39;
            shotObj->unk2 = self->ext.main_74.animation_index + 4;
            shotObj->unk7C = WEAPON_OBJECT(self);
        }
        self->unk6++;
        D_8013B8A8 = OBJECT_HEADER(miscObj);
    }
}

void sigma_final_big_beam_fire(struct MainObj* self)
{
    struct QuadObj* quad;

    animate_object(ANIMATED_OBJECT(self));
    if (D_8013B8A8->active == 0) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 0x10;
            quad->unk2 = self->ext.main_74.animation_index + 0x10;
            quad->unk5C = PLAYER_OBJECT(self);
        }
        D_8013B8A8 = OBJECT_HEADER(quad);
        self->unk6++;
    }
}

void sigma_final_big_beam_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (D_8013B8A8->active == 0) {
        stop_sound(2, 1);
        if (self->ext.main_74.animation_index != 0) {
            set_animation(self, 0x22);
        } else {
            set_animation(self, 0x24);
        }
        self->unk6++;
    }
}

void sigma_final_big_beam_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void sigma_final_big_beam(struct MainObj* self)
{
    sigma_final_big_beam_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_hide_upper_start(struct MainObj* self)
{
    self->ext.main_74.unk8C = 3;
    self->unk6++;
    set_animation(self, 0x19);
    func_8001540C(2, 9, self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", sigma_final_hide_upper_wait);
#else
void sigma_final_hide_upper_wait(struct MainObj* self)
{
    s32 count;
    u32 i;

    count = 0;
    for (i = 0; i < COUNT(self->ext.main_74.children); i++) {
        if (self->ext.main_74.children[i]->unk5 == 3) {
            count++;
        }
    }
    if ((self->animation_step.fields.relative_step == 0) && (count == 3)) {
        self->unk5 = 2;
        self->unk6 = 0;
        sigma_final_set_target(self, 0);
        D_8013B8A0[0] = 0x1E;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
        return;
    }
    self->x_pos.i.hi = 0;
    self->y_pos.i.hi = 0;
}
#endif

void sigma_final_hide_upper(struct MainObj* self)
{
    sigma_final_hide_upper_funcs[self->unk6](self);
}

void sigma_final_show_upper_start(struct MainObj* self)
{
    self->contact_damage = 9;
    self->x_pos.i.hi = 0x567;
    self->y_pos.i.hi = 0x287;
    sigma_final_set_target(self, 1);
    self->unk6++;
    set_animation(self, 0x18);
    func_8001540C(2, 9, self);
}

void sigma_final_show_upper_wait(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        D_8013B8A0[0] = 0x1E;
    }

    animate_object(ANIMATED_OBJECT(self));
}

void sigma_final_show_upper(struct MainObj* self)
{
    sigma_final_show_upper_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_hide_lower_start(struct MainObj* self)
{
    self->ext.main_74.unk8C = 3;
    self->unk6++;
    set_animation(self, 0x1B);
    func_8001540C(2, 9, self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", sigma_final_hide_lower_wait);
#else
void sigma_final_hide_lower_wait(struct MainObj* self)
{
    u32 i;
    s32 count = 0;
    for (i = 0; i < COUNT(self->ext.main_74.children); i++) {
        if (self->ext.main_74.children[i]->unk5 == 3) {
            count++;
        }
    }
    if ((self->animation_step.fields.relative_step == 0) && (count == 3)) {
        self->unk5 = 2;
        self->unk6 = 0;
        sigma_final_set_target(self, 0);
        D_8013B8A0[0] = 0x1E;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
        return;
    }
    self->x_pos.i.hi = 0;
    self->y_pos.i.hi = 0;
}
#endif

void sigma_final_hide_lower(struct MainObj* self)
{
    sigma_final_hide_lower_funcs[self->unk6](self);
}

void sigma_final_show_lower_start(struct MainObj* self)
{
    self->contact_damage = 9;
    self->x_pos.i.hi = 0x450;
    self->y_pos.i.hi = 0x2B8;
    sigma_final_set_target(self, 2);
    self->unk6++;
    set_animation(self, 0x1A);
    func_8001540C(2, 9, self);
}

void sigma_final_show_lower_wait(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        D_8013B8A0[0] = 0xA;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void sigma_final_show_lower(struct MainObj* self)
{
    sigma_final_show_lower_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_grab_start(struct MainObj* self)
{
    sigma_spawn_sequencer(self, 7);
    set_animation(self, 2);
    self->unk7C = 0x3C;
    self->unk62 = 3;
    self->attack_box = (const u8*)&D_80105364;
    self->contact_damage = 0;
    self->unk6++;
    func_8001540C(2, 0xB, self);
}

// sigma_final_grab_hold
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", func_8008E748);

void sigma_final_grab_release(struct MainObj* self)
{
    struct ShotObj* current;
    s32 found;
    s16 timer;

    timer = self->unk7C;
    if (timer != 0) {
        self->unk7C = timer - 1;
        return;
    }

    found = 0;
    for (current = shot_objects; current < &shot_objects[0x20]; current++) {
        if (current->id == 0x38) {
            s32 active = current->active;
            if ((active & 1) == 1) {
                found = 1;
            }
        }
    }

    if (!found) {
        stop_sound(2, 0xB);
        g_Player.stun_timer = 0;
        self->unk62 = 2;
        self->contact_damage = 9;
        self->attack_box = &D_80105360;
        self->unk6++;
    }
}

void sigma_final_grab_finish(struct MainObj* self)
{
    self->unk62 = 0;
    self->contact_damage = 9;
    self->unk5 = 0xB;
    self->unk6 = 0;
}

void sigma_final_grab(struct MainObj* self)
{
    sigma_final_grab_funcs[self->unk6](self);
    if (self->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
    } else {
        D_8013B8B0 = NULL;
    }
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_spit_open(struct MainObj* self)
{
    set_animation(self, 3);
    self->unk7C = 0x1E;
    self->unk6++;
    self->attack_box = (const u8*)&D_80105360;
}

void sigma_final_spit_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6++;
        set_animation(self, 4);
        self->unk7C = 0xF1;
    }
}

void sigma_final_spit_fire(struct MainObj* self)
{
    s16 timer;
    struct ShotObj* shot;

    timer = --self->unk7C;
    if (timer == 0) {
        self->unk5 = 7;
        self->unk6 = 0;
        return;
    }
    if ((timer % 10) == 0) {
        func_8001540C(2, 0, self);
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x38;
            shot->unk2 = 1;
            shot->x_pos.i.hi = (u16)self->x_pos.i.hi + 0x10;
            shot->y_pos.i.hi = (u16)self->y_pos.i.hi + 0x10;
            shot->unk7C = WEAPON_OBJECT(self);
        }
    }
}

void sigma_final_spit(struct MainObj* self)
{
    sigma_final_spit_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
    if (self->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
    } else {
        D_8013B8B0 = NULL;
    }
}

// sigma_final_wind_spikes
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", func_8008EC48);

void sigma_final_wind_start(struct MainObj* self)
{
    struct MiscObj* miscObj;

    self->unk7C--;
    if (self->unk7C == 0) {
        self->unk7C = 0x3C;
        self->unk6++;
    }
    if ((self->unk7C % 10) == 0) {
        func_8001540C(2, 0xA, self);
        miscObj = find_free_misc_obj();
        if (miscObj != 0) {
            miscObj->active = 0x41;
            miscObj->id = 0x37;
            miscObj->unk2 = 2;
            miscObj->ext.misc_55.owner = self;
        }
    }
}

void sigma_final_wind_push(struct MainObj* self)
{
    struct MiscObj* misc;

    g_Player.x_pos.i.hi += 3;
    animate_object(ANIMATED_OBJECT(self));

    if (--self->unk7C == 0) {
        self->unk7C = 0x5A;
        self->unk6++;
    }
    if (self->unk7C % 10 == 0) {
        func_8001540C(2, 10, self);
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x41;
            misc->id = 0x37;
            misc->unk2 = 2;
            misc->ext.misc_7.position = self;
        }
    }
}

void sigma_final_wind_push_hard(struct MainObj* self)
{
    g_Player.x_pos.i.hi += 4;
    animate_object(ANIMATED_OBJECT(self));

    if (--self->unk7C == 0) {
        self->unk7C = 0x5A;
        self->unk6++;
    }

    if (self->unk7C % 10 == 0) {
        func_8001540C(2, 0xA, self);
    }
}

void sigma_final_wind_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 7;
        self->unk6 = 0;
        return;
    }
    if ((self->unk7C % 10) == 0) {
        func_8001540C(2, 10, self);
    }
}

void sigma_final_wind(struct MainObj* self)
{
    sigma_final_wind_funcs[self->unk6](self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
    if (self->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
        return;
    }
    D_8013B8B0 = NULL;
}

void sigma_final_summon_start(struct MainObj* self)
{
    u8 choice = (u32)(get_random() & 0xFF) % 3;
    switch (choice) {
    case 0:
        sigma_spawn_sequencer(self, 1);
        break;
    case 1:
        sigma_spawn_sequencer(self, 2);
        break;
    default:
        sigma_spawn_sequencer(self, 0);
        break;
    }
    self->unk6++;
}

void sigma_final_summon_wait(struct MainObj* self)
{
    if (sigma_sequencer->active == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        D_8013B8A0[0] = 0x1E;
    }
}

void sigma_final_summon(struct MainObj* self)
{
    sigma_final_summon_funcs[self->unk6](self);
}

// sigma_final_fight
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", func_8008F1A8);

// sigma_final_death_start
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", func_8008F3F4);

void sigma_final_death_blink(struct MainObj* self)
{

    if (--self->unk7E == 0) {
        self->unk7C = 0x12C;
        self->unk42 ^= 0x8000;
        self->invincibility_timer -= 5;
        if (self->invincibility_timer > 0x19) {
            self->invincibility_timer = 0;
        }
        self->unk7E = self->invincibility_timer > 5 ? self->invincibility_timer : 5;
        self->ext.main_74.unk97 = 4;
        self->unk5 = 2;
    }
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

// sigma_final_death_explode
INCLUDE_ASM("main/nonmatchings/mains/main_74_sigma_final", func_8008F578);

void sigma_final_death_collapse(struct MainObj* self)
{
    struct EffectObj* effect;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 4;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x2B;
            effect->unk2 = 1;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_death_wait_player(struct MainObj* self)
{
    if (g_Player.script_state != -1) {
        update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
        return;
    }
    sigma_final_set_target(self, 0);
    if (engine_obj.cur_character == 0) {
        func_8002217C(0x2C, 7, 0);
    } else {
        func_8002217C(0x25, 7, 0);
    }
    self->unk5 = 5;
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_death_explosion(struct MainObj* self)
{
    struct EffectObj* effect;

    if (abc_object.unkC == 0) {
        self->unk5 = 6;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = -0x7F;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            D_8013B8A8 = OBJECT_HEADER(effect);
        }
        set_animation(self, 0);
    }
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_death_finish(struct MainObj* self)
{
    if (D_8013B8A8->active == 0) {
        player_end_script_action();
        engine_obj.character_state.fields.active = 1;
        background_objects[0].unk26 = 0x450;
        background_objects[0].unk24 = 0x480;
        g_Player.spike_immune = 0;
        apply_tile_effect(8U, 0, 0);
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }

    if (D_8013B8A8->unk7 == 0) {
        animate_object(ANIMATED_OBJECT(self));
        update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
    }
}

void sigma_final_death(struct MainObj* self)
{
    sigma_final_death_funcs[self->unk5](self);
}

void sigma_final_update(struct MainObj* self)
{
#define MAIN_74_BOSS_ACTIVE engine_obj.enable_boss

    self->on_screen = 0;
    sigma_final_state_funcs[self->state](self);
    if (self->ext.main_74.target == 0) {
        MAIN_74_BOSS_ACTIVE = 0;
        return;
    }
    MAIN_74_BOSS_ACTIVE = 1;
    if (self->ext.main_74.target == 1) {
        self->ext.main_74.upper_health = self->hp;
        return;
    }
    self->ext.main_74.lower_health = self->hp;
}

struct Unk_unk68 D_8010535C = { -10, -81, 103, 70 };

struct Unk_unk68 D_80105360 = { -59, -31, 68, 74 };

struct Unk_unk68 D_80105364 = { 5, 5, 23, 21 };

struct Unk_unk68 D_80105368 = { -4, -99, 38, 38 };

struct Unk_unk68 D_8010536C = { 17, -51, 46, 46 };

struct Unk_unk68 D_80105370 = { -67, -40, 71, 83 };

struct Unk_unk68 D_80105374 = { 9, -1, 30, 27 };

struct Unk_unk68 D_80105378[5] = {
    { 22, 0, 1, 79 },
    { 21, 0, 1, 80 },
    { 22, 0, 1, 81 },
    { 20, 0, 1, 80 },
    { 1, 0, -4, 80 },
};

struct Unk_unk68 D_8010538C[5] = {
    { 18, 0, 1, 5 },
    { 17, 0, 1, 72 },
    { 18, 0, 1, 5 },
    { 17, 0, 1, 73 },
    { 1, 0, -4, 73 },
};

struct Unk_unk68 D_801053A0[3] = {
    { 2, 1, 1, 6 },
    { 1, 1, 1, 7 },
    { 1, 1, -2, 7 },
};

u8 D_801053AC[8] = { 8, 0, 1, 8, 1, 0, 255, 9 };

u8 D_801053B4[8] = { 8, 1, 1, 7, 1, 1, 255, 6 };

struct Unk_unk68 D_801053BC[5] = {
    { 30, 0, 1, 5 },
    { 10, 0, 1, 7 },
    { 2, 0, 1, 8 },
    { 30, 0, 1, 9 },
    { 1, 0, -4, 5 },
};

struct Unk_unk68 D_801053D0[6] = {
    { 30, 0, 1, 5 },
    { 2, 0, 1, 8 },
    { 7, 0, 1, 9 },
    { 2, 1, 1, 6 },
    { 1, 1, 1, 7 },
    { 1, 1, -5, 7 },
};

union AnimationStep D_801053E8[] = {
    { 0x0D000008 },
};

union AnimationStep D_801053EC[] = {
    { 0x0E010008 },
    { 0x0F010008 },
    { 0x10010007 },
    { 0x10000001 },
};

union AnimationStep D_801053FC[] = {
    { 0x0C010008 },
    { 0x0B010008 },
    { 0x0A010007 },
    { 0x0A000001 },
};

union AnimationStep D_8010540C[] = {
    { 0x0D01001E },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13010006 },
    { 0x1401001D },
    { 0x14000001 },
};

union AnimationStep D_80105424[] = {
    { 0x0D01001E },
    { 0x42010001 },
    { 0x43010001 },
    { 0x44010106 },
    { 0x4501001D },
    { 0x45000001 },
};

union AnimationStep D_8010543C[] = {
    { 0x0A000001 },
};

struct Unk_unk68 D_80105440[6] = {
    { 6, 0, 1, 21 },
    { 6, 0, 1, 22 },
    { 6, 0, 1, 23 },
    { 6, 0, 1, 24 },
    { 5, 0, 1, 25 },
    { 1, 0, -5, 25 },
};

struct Unk_unk68 D_80105458[4] = {
    { 1, 0, 1, 26 },
    { 1, 0, 1, 27 },
    { 1, 0, 1, 28 },
    { 1, 0, -3, 29 },
};

struct Unk_unk68 D_80105468[7] = {
    { 3, 0, 1, 30 },
    { 3, 0, 1, 31 },
    { 3, 0, 1, 32 },
    { 3, 0, 1, 33 },
    { 3, 0, 1, 34 },
    { 2, 0, 1, 35 },
    { 1, 0, -6, 35 },
};

struct Unk_unk68 D_80105484[7] = {
    { 3, 0, 1, 44 },
    { 4, 0, 1, 45 },
    { 5, 0, 1, 46 },
    { 7, 0, 1, 47 },
    { 7, 0, 1, 48 },
    { 6, 0, 1, 49 },
    { 1, 0, -3, 49 },
};

union AnimationStep D_801054A0[] = {
    { 0x32010007 },
    { 0x33010008 },
    { 0x34010008 },
    { 0x34000001 },
};

struct Unk_unk68 D_801054B0[5] = {
    { 2, 0, 1, 36 },
    { 2, 0, 1, 37 },
    { 2, 0, 1, 38 },
    { 1, 0, 1, 39 },
    { 1, 0, -4, 39 },
};

struct Unk_unk68 D_801054C4[5] = {
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 42 },
    { 1, 0, 1, 43 },
    { 1, 0, -4, 43 },
};

union AnimationStep D_801054D8[] = {
    { 0x35000001 },
};

union AnimationStep D_801054DC[] = {
    { 0x3A000001 },
    { 0x63000001 },
    { 0x64000001 },
    { 0x65000001 },
};

struct Unk_unk68 D_801054EC[5] = {
    { 3, 0, 1, 59 },
    { 3, 0, 1, 60 },
    { 3, 0, 1, 61 },
    { 2, 0, 1, 62 },
    { 1, 0, -4, 62 },
};

struct Unk_unk68 D_80105500[5] = {
    { 2, 0, 1, 54 },
    { 2, 0, 1, 55 },
    { 2, 0, 1, 56 },
    { 1, 0, 1, 57 },
    { 1, 0, -4, 57 },
};

struct Unk_unk68 D_80105514[27] = {
    { 2, 0, 1, 77 },
    { 2, 0, 1, 78 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 1, 0, 1, 79 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 1, 0, 1, 79 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 1, 0, 1, 79 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 1, 0, 1, 79 },
    { 1, 0, 1, 77 },
    { 1, 0, 1, 78 },
    { 22, 0, 1, 79 },
    { 21, 0, 1, 80 },
    { 22, 0, 1, 81 },
    { 20, 0, 1, 80 },
    { 1, 0, -4, 80 },
};

union AnimationStep D_80105580[] = {
    { 0x4F010002 },
    { 0x4D010002 },
    { 0x4E010002 },
    { 0x4F010001 },
    { 0x4D010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x4D010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x4D010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x4D010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x4D010001 },
    { 0x4F000001 },
    { 0x4F010001 },
    { 0x4D010001 },
    { 0x4F010001 },
    { 0x4D010001 },
    { 0x4F010001 },
    { 0x4D000001 },
};

struct Unk_unk68 D_801055E0[27] = {
    { 2, 0, 1, 70 },
    { 2, 0, 1, 71 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 5 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 5 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 5 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 5 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 17, 0, 1, 5 },
    { 18, 0, 1, 72 },
    { 17, 0, 1, 5 },
    { 17, 0, 1, 73 },
    { 1, 0, -4, 73 },
};

union AnimationStep D_8010564C[] = {
    { 0x05010002 },
    { 0x46010002 },
    { 0x47010002 },
    { 0x05010001 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x05010001 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x05010001 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x05010001 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x05010001 },
    { 0x46010001 },
    { 0x05000001 },
    { 0x05010001 },
    { 0x46010001 },
    { 0x05010001 },
    { 0x46010001 },
    { 0x05010001 },
    { 0x46000001 },
};

u8 D_801056AC[24] = { 30, 0, 1, 79, 6, 0, 1, 82, 1, 0, 1, 88, 20, 0, 1, 84, 1, 0, 1, 85, 1, 0, 255, 94 };

u8 D_801056C4[32] = { 30, 0, 1, 79, 3, 0, 1, 82, 2, 0, 1, 88, 4, 0, 1, 84, 4, 0, 1, 90, 20, 0, 1, 86, 1, 0, 1, 87, 1, 0, 255, 95 };

u8 D_801056E4[20] = { 30, 0, 1, 79, 6, 0, 1, 82, 20, 0, 1, 88, 1, 0, 1, 89, 1, 0, 255, 96 };

u8 D_801056F8[28] = { 30, 0, 1, 79, 4, 0, 1, 82, 4, 0, 1, 88, 2, 0, 1, 84, 20, 0, 1, 90, 1, 0, 1, 91, 1, 0, 255, 97 };

u8 D_80105714[36] = { 30, 0, 1, 79, 3, 0, 1, 82, 2, 0, 1, 88, 3, 0, 1, 84, 3, 0, 1, 90, 3, 0, 1, 86, 20, 0, 1, 92, 1, 0, 1, 93, 1, 0, 255, 98 };

union AnimationStep D_80105738[] = {
    { 0x5E010002 },
    { 0x55010002 },
    { 0x54010002 },
    { 0x52010002 },
    { 0x4F010001 },
    { 0x4F000001 },
};

union AnimationStep D_80105750[] = {
    { 0x5F010002 },
    { 0x57010002 },
    { 0x56010002 },
    { 0x5A010002 },
    { 0x54010002 },
    { 0x58010002 },
    { 0x52010002 },
    { 0x4F010001 },
    { 0x4F000001 },
};

union AnimationStep D_80105774[] = {
    { 0x60010002 },
    { 0x59010002 },
    { 0x58010002 },
    { 0x52010002 },
    { 0x4F010001 },
    { 0x4F000001 },
};

union AnimationStep D_8010578C[] = {
    { 0x61010002 },
    { 0x5B010002 },
    { 0x5A010002 },
    { 0x54010002 },
    { 0x58010002 },
    { 0x52010002 },
    { 0x4F010001 },
    { 0x4F000001 },
};

union AnimationStep D_801057AC[] = {
    { 0x62010002 },
    { 0x5D010002 },
    { 0x5C010002 },
    { 0x56010002 },
    { 0x5A010002 },
    { 0x54010002 },
    { 0x58010002 },
    { 0x52010002 },
    { 0x4F010001 },
    { 0x4F000001 },
};

union AnimationStep D_801057D4[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010002 },
    { 0x04000001 },
};

void* sigma_final_animations[39] = {
    D_80105378,
    D_8010538C,
    D_801053A0,
    D_801053AC,
    D_801053B4,
    D_801053BC,
    D_801053D0,
    D_801053E8,
    D_801053EC,
    D_801053FC,
    D_8010540C,
    D_80105424,
    D_8010543C,
    D_80105440,
    D_80105458,
    D_80105468,
    D_80105484,
    D_801054A0,
    D_801054B0,
    D_801054C4,
    D_801054D8,
    D_801054DC,
    D_801054EC,
    D_80105500,
    D_80105514,
    D_80105580,
    D_801055E0,
    D_8010564C,
    D_801056AC,
    D_801056C4,
    D_801056E4,
    D_801056F8,
    D_80105714,
    D_80105738,
    D_80105750,
    D_80105774,
    D_8010578C,
    D_801057AC,
    D_801057D4,
};

void (*sigma_final_intro_funcs[5])() = {
    sigma_final_intro_lock_camera,
    sigma_final_intro_start_music,
    sigma_final_intro_wait_load,
    sigma_final_intro_load,
    func_8008D5C8,
};

void (*sigma_final_appear_funcs[4])() = {
    sigma_final_appear_start,
    sigma_final_appear_pose,
    sigma_final_appear_dialogue,
    sigma_final_appear_fill_health,
};

u8 sigma_final_laser_animations[8] = { 0x1C, 0x21, 0x1F, 0x24, 0x1D, 0x22, 0x20, 0x25 };

void (*sigma_final_laser_funcs[5])() = {
    sigma_final_laser_start,
    sigma_final_laser_aim,
    sigma_final_laser_fire,
    sigma_final_laser_wait,
    sigma_final_laser_repeat,
};

void (*sigma_final_big_beam_funcs[5])() = {
    sigma_final_big_beam_start,
    sigma_final_big_beam_charge,
    sigma_final_big_beam_fire,
    sigma_final_big_beam_wait,
    sigma_final_big_beam_recover,
};

void (*sigma_final_hide_upper_funcs[2])() = {
    sigma_final_hide_upper_start,
    sigma_final_hide_upper_wait,
};

void (*sigma_final_show_upper_funcs[2])() = {
    sigma_final_show_upper_start,
    sigma_final_show_upper_wait,
};

void (*sigma_final_hide_lower_funcs[2])() = {
    sigma_final_hide_lower_start,
    sigma_final_hide_lower_wait,
};

void (*sigma_final_show_lower_funcs[2])() = {
    sigma_final_show_lower_start,
    sigma_final_show_lower_wait,
};

void (*sigma_final_grab_funcs[4])(struct MainObj*) = {
    sigma_final_grab_start,
    func_8008E748,
    sigma_final_grab_release,
    sigma_final_grab_finish,
};

void (*sigma_final_spit_funcs[3])(struct MainObj*) = {
    sigma_final_spit_open,
    sigma_final_spit_wait,
    sigma_final_spit_fire,
};

void (*sigma_final_wind_funcs[5])(struct MainObj*) = {
    func_8008EC48,
    sigma_final_wind_start,
    sigma_final_wind_push,
    sigma_final_wind_push_hard,
    sigma_final_wind_finish,
};

void (*sigma_final_summon_funcs[2])() = {
    sigma_final_summon_start,
    sigma_final_summon_wait,
};

void (*sigma_final_step_funcs[14])() = {
    enemy_hit_reaction,
    sigma_final_idle,
    func_8008DAE8,
    sigma_final_appear,
    sigma_final_show_upper,
    sigma_final_hide_upper,
    sigma_final_show_lower,
    sigma_final_hide_lower,
    sigma_final_summon,
    sigma_final_laser,
    sigma_final_big_beam,
    sigma_final_spit,
    sigma_final_wind,
    sigma_final_grab,
};

void (*sigma_final_death_funcs[7])() = {
    func_8008F3F4,
    sigma_final_death_blink,
    func_8008F578,
    sigma_final_death_collapse,
    sigma_final_death_wait_player,
    sigma_final_death_explosion,
    sigma_final_death_finish,
};

void (*sigma_final_state_funcs[3])(struct MainObj*) = {
    sigma_final_intro,
    func_8008F1A8,
    sigma_final_death,
};
