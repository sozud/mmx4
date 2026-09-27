// MainObj, main_object_update_funcs[74]
// 8008D460..8008FB38
#include "common.h"

void sigma_final_intro_lock_camera(struct MainObj* self)
{
    D_8013B8B8[0] = 0;
    self->ext.main_74.death_kind = 0;
    self->ext.main_74.pattern_index = 0;
    background_objects[0].unk26 = 0x410;
    background_objects[0].unk24 = 0x480;
    background_objects[0].unk2A = 0x200;
    background_objects[0].unk28 = 0x200;
    func_80036AE4(0x14, 0x40);
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
INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D5C8);

#ifdef VERSION_JP
extern void* D_8013B994_jp;
#define MAIN_74_COLLISION_BOUNDS D_8013B994_jp
#else
extern void* D_8013B8B4;
#define MAIN_74_COLLISION_BOUNDS D_8013B8B4
#endif

void sigma_final_set_target(struct MainObj* self, s32 arg1)
{
    switch (arg1 & 0xFF) {
    case 0:
        D_8013B8B0 = 0;
        MAIN_74_COLLISION_BOUNDS = 0;
        self->unk50 = 0;
        break;
    case 1:
        D_8013B8B0 = &D_80105368;
        MAIN_74_COLLISION_BOUNDS = &D_8010536C;
        self->unk5C = self->ext.main_74.upper_health;
        self->unk5D = self->ext.main_74.upper_health;
        self->unk50 = &D_8010535C;
        break;
    case 2:
        D_8013B8B0 = 0;
        MAIN_74_COLLISION_BOUNDS = &D_80105370;
        self->unk5C = self->ext.main_74.lower_health;
        self->unk5D = self->ext.main_74.lower_health;
        self->unk50 = &D_80105360;
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
    func_80015D60(self, 0x18);
    func_8001540C(2, 9, self);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_appear_pose(struct MainObj* self)
{
    u16 sound_id;

    if (self->animation_step.fields.relative_step < 0) {
        self->unk6++;
        sound_id = 0x2D;
        if (engine_obj.cur_character == 0) {
            sound_id = 0x32;
        }
        func_8002217C(sound_id, 0xFF, 0);
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_appear_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        sigma_final_set_target(self, 1);
        self->unk7E = 3;
        self->unk6++;
        func_800921E8(0xC);
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_appear_fill_health(struct MainObj* self)
{
    s16 temp_v0;

    if (self->unk5C < 0x30) {
        if (func_8009227C() == 0) {
            temp_v0 = self->unk7E - 1;
            self->unk7E = temp_v0;
            if (temp_v0 == 0) {
                func_8001540C(0, 0xE, 0);
                self->unk7E = 3;
            }
            self->unk5C++;
        }
    } else {
        func_80015D60(self, 0);
        self->unk5 = 2;
        self->unk6 = 0;
        *D_8013B8A0 = 0xA;
        D_8013B8B0 = &D_80105368;
        MAIN_74_COLLISION_BOUNDS = &D_8010536C;
        func_80036B18();
    }
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_appear(struct MainObj* self)
{
    sigma_final_appear_funcs[self->unk6](self);
}

// sigma_final_pick_attack
INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DAE8);

void sigma_final_laser_start(struct MainObj* self)
{
    func_8008D3B8(self, 5);
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
    func_80015D60(self,
        sigma_final_laser_animations[self->ext.main_74.animation_index * 2]);
    self->unk6++;
}

void sigma_final_laser_fire(struct PlayerObj* player)
{
    struct QuadObj* quad;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(player));
    if (player->animation_step.fields.relative_step < 0) {
        player->unk6 += 1;
        func_8001540C(2, 5, player);

        quad = find_free_quad_obj();
        if (quad != 0) {
            quad->active = 1;
            quad->id = 0x10;
            quad->unk2 = player->unk90;
            quad->unk5C = player;
        }
        D_8013B8A8 = OBJECT_HEADER(quad);

        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 1;
            shot->id = 0x39;
            shot->unk2 = player->unk90;
            shot->unk7C = WEAPON_OBJECT(player);
        }
    }
}

void sigma_final_laser_wait(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (D_8013B8A8->active == 0) {
        func_80015930(2, 5);
        self->unk6++;
        func_80015D60(self,
            sigma_final_laser_animations[self->ext.main_74.animation_index * 2 + 1]);
    }
}

void sigma_final_laser_repeat(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
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
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_big_beam_start(struct MainObj* self)
{
    self->ext.main_74.animation_index = 1;
    func_80015D60(self, 0x1D);
    func_8008D3B8(self, 3);
    func_8001540C(2, 6, self);
    func_8001540C(2, 1, self);
    self->unk6++;
}

void sigma_final_big_beam_charge(struct MainObj* self)
{
    struct MiscObj* miscObj;
    struct ShotObj* shotObj;

    func_80015DC8(ANIMATED_OBJECT(self));
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

    func_80015DC8(ANIMATED_OBJECT(self));
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
    func_80015DC8(ANIMATED_OBJECT(self));
    if (D_8013B8A8->active == 0) {
        func_80015930(2, 1);
        if (self->ext.main_74.animation_index != 0) {
            func_80015D60(self, 0x22);
        } else {
            func_80015D60(self, 0x24);
        }
        self->unk6++;
    }
}

void sigma_final_big_beam_recover(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void sigma_final_big_beam(struct MainObj* self)
{
    sigma_final_big_beam_funcs[self->unk6](self);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_hide_upper_start(struct MainObj* self)
{
    self->ext.main_74.unk8C = 3;
    self->unk6++;
    func_80015D60(self, 0x19);
    func_8001540C(2, 9, self);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

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
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
        return;
    }
    self->x_pos.i.hi = 0;
    self->y_pos.i.hi = 0;
}

void sigma_final_hide_upper(struct MainObj* self)
{
    sigma_final_hide_upper_funcs[self->unk6](self);
}

void sigma_final_show_upper_start(struct MainObj* self)
{
    self->unk60 = 9;
    self->x_pos.i.hi = 0x567;
    self->y_pos.i.hi = 0x287;
    sigma_final_set_target(self, 1);
    self->unk6++;
    func_80015D60(self, 0x18);
    func_8001540C(2, 9, self);
}

void sigma_final_show_upper_wait(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        D_8013B8A0[0] = 0x1E;
    }

    func_80015DC8(ANIMATED_OBJECT(self));
}

void sigma_final_show_upper(struct MainObj* self)
{
    sigma_final_show_upper_funcs[self->unk6](self);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_hide_lower_start(struct MainObj* self)
{
    self->ext.main_74.unk8C = 3;
    self->unk6++;
    func_80015D60(self, 0x1B);
    func_8001540C(2, 9, self);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

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
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
        return;
    }
    self->x_pos.i.hi = 0;
    self->y_pos.i.hi = 0;
}

void sigma_final_hide_lower(struct MainObj* self)
{
    sigma_final_hide_lower_funcs[self->unk6](self);
}

void sigma_final_show_lower_start(struct MainObj* self)
{
    self->unk60 = 9;
    self->x_pos.i.hi = 0x450;
    self->y_pos.i.hi = 0x2B8;
    sigma_final_set_target(self, 2);
    self->unk6++;
    func_80015D60(self, 0x1A);
    func_8001540C(2, 9, self);
}

void sigma_final_show_lower_wait(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        D_8013B8A0[0] = 0xA;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void sigma_final_show_lower(struct MainObj* self)
{
    sigma_final_show_lower_funcs[self->unk6](self);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_grab_start(struct MainObj* self)
{
    func_8008D3B8(self, 7);
    func_80015D60(self, 2);
    self->unk7C = 0x3C;
    self->unk62 = 3;
    self->unk50 = (const u8*)&D_80105364;
    self->unk60 = 0;
    self->unk6++;
    func_8001540C(2, 0xB, self);
}

// sigma_final_grab_hold
INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E748);

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
        func_80015930(2, 0xB);
        g_Player.unkBA = 0;
        self->unk62 = 2;
        self->unk60 = 9;
        self->unk50 = &D_80105360;
        self->unk6++;
    }
}

void sigma_final_grab_finish(struct MainObj* self)
{
    self->unk60 = 9;
    self->unk62 = 0;
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
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_spit_open(struct MainObj* self)
{
    func_80015D60(self, 3);
    self->unk7C = 0x1E;
    self->unk50 = (const u8*)&D_80105360;
    self->unk6++;
}

void sigma_final_spit_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6++;
        func_80015D60(self, 4);
        self->unk7C = 0xF1;
    }
}

void sigma_final_spit_fire(struct MainObj* self)
{
    s16 timer;
    struct ShotObj* shot;

    timer = self->unk7C - 1;
    self->unk7C = timer;
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
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
    if (self->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
    } else {
        D_8013B8B0 = NULL;
    }
}

// sigma_final_wind_spikes
INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EC48);

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
    func_80015DC8(ANIMATED_OBJECT(self));

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
    func_80015DC8(ANIMATED_OBJECT(self));

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
    s16 timer = self->unk7C - 1;

    self->unk7C = timer;
    if (timer == 0) {
        self->unk5 = 7;
        self->unk6 = 0;
        return;
    }
    if ((timer % 10) == 0) {
        func_8001540C(2, 10, self);
    }
}

void sigma_final_wind(struct MainObj* self)
{
    sigma_final_wind_funcs[self->unk6](self);
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
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
        func_8008D3B8(self, 1);
        break;
    case 1:
        func_8008D3B8(self, 2);
        break;
    default:
        func_8008D3B8(self, 0);
        break;
    }
    self->unk6++;
}

void sigma_final_summon_wait(struct MainObj* self)
{
    if (D_8013B8AC->active == 0) {
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
INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F1A8);

// sigma_final_death_start
INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F3F4);

void sigma_final_death_blink(struct MainObj* self)
{
    s16 timer;
    s8 value;
    s8 delay;

    timer = self->unk7E - 1;
    self->unk7E = timer;
    if (timer == 0) {
        self->unk7C = 0x12C;
        self->unk42 ^= 0x8000;
        value = self->unk61 - 5;
        self->unk61 = value;
        if (value >= 0x1A) {
            self->unk61 = 0;
        }
        delay = self->unk61;
        if (self->unk61 < 5) {
            delay = 5;
        }
        self->unk7E = delay;
        self->ext.main_74.unk97 = 4;
        self->unk5 = 2;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

// sigma_final_death_explode
INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F578);

void sigma_final_death_collapse(struct MainObj* self)
{
    struct EffectObj* effect;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 4;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x2B;
            effect->unk2 = 1;
        }
    }
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_death_wait_player(struct MainObj* self)
{
    u16 sound_id;

    if (g_Player.unkC0 != -1) {
        func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
        return;
    }
    sigma_final_set_target(self, 0);
    sound_id = 0x25;
    if (engine_obj.cur_character == 0) {
        sound_id = 0x2C;
    }
    func_8002217C(sound_id, 7, 0);
    self->unk5 = 5;
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
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
            D_8013B8A8 = OBJECT_HEADER(effect);
            effect->y_pos.i.hi = self->y_pos.i.hi;
        }
        func_80015D60(self, 0);
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void sigma_final_death_finish(struct MainObj* self)
{
    if (D_8013B8A8->active == 0) {
        func_80036B18();
        engine_obj.character_state.fields.active = 1;
        background_objects[0].unk26 = 0x450;
        background_objects[0].unk24 = 0x480;
        g_Player.unk7A = 0;
        func_800DABE4(8U, 0, 0);
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }

    if (D_8013B8A8->unk7 == 0) {
        func_80015DC8(ANIMATED_OBJECT(self));
        func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
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
        self->ext.main_74.upper_health = self->unk5C;
        return;
    }
    self->ext.main_74.lower_health = self->unk5C;
}

u8 general_at_position(struct ObjectHeader* self, s16 arg1, s16 arg2)
{
    s16 temp_v1;
    s16 temp_a0;

    temp_v1 = self->x_pos.i.hi;
    if ((temp_v1 - arg1 >= 0) ? (temp_v1 - arg1 < 3) : (arg1 - temp_v1 < 3)) {
        temp_a0 = self->y_pos.i.hi;
        if ((temp_a0 - arg2 >= 0) ? (temp_a0 - arg2 < 3) : (arg2 - temp_a0 < 3)) {
            return 1;
        }
    }
    return 0;
}

void general_pick_script(struct MainObj* self)
{
    s32 low_health = self->unk5C < 0x19;
    const u8** scripts = general_scripts[low_health];
    u8 roll = get_random();
    u8 i = 0;
    u8* weights = &general_script_weights[low_health * 2];
    roll = (roll >> 2) & 0xF;
    while (i < 2) {
        if (roll < weights[i]) {
            self->ext.main_75.script = scripts[i];
            return;
        }
        i++;
    }
}
