// MainObj, main_object_update_funcs[57]
// 80072194..800743FC
#include "common.h"
#include "func_tables.h"

extern u8** frost_walrus_scripts[];
extern u8 frost_walrus_script_weights[][4];

void frost_walrus_choose_script(struct MainObj* arg0);

void frost_walrus_update(struct MainObj* self)
{
    frost_walrus_state_funcs[self->state](self);
    CollisionRelated(PLAYER_OBJECT(self));
    if (!(g_Player.hp & 0x7F)) {
        frost_walrus_set_floor_tiles(0x38);
    }
}

void frost_walrus_start(struct MainObj* self)
{
    frost_walrus_start_funcs[self->unk5](self);
}

void frost_walrus_start_warning(struct MainObj* self)
{
    struct EffectObj* effect = find_free_effect_obj();

    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        self->ext.main_57.effect = effect;
        player_start_script_action(0x14, 0x40);
        self->unk5++;
    }
}

// frost_walrus_start_init
INCLUDE_ASM("main/nonmatchings/mains/main_57_frost_walrus", func_800722A0);

// frost_walrus_main
INCLUDE_ASM("main/nonmatchings/mains/main_57_frost_walrus", func_80072418);

void frost_walrus_reset(struct MainObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void frost_walrus_death(struct BarObj* self)
{
    frost_walrus_death_funcs[self->unk5](self);
}

// frost_walrus_death_start
INCLUDE_ASM("main/nonmatchings/mains/main_57_frost_walrus", func_80072628);

void frost_walrus_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 delay;
    s8 next_delay;

    self->unk7C--;
    if (self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.u.hi;
            effect->y_pos.i.hi = self->y_pos.u.hi;
            self->ext.main_57.effect = effect;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        delay = self->invincibility_timer - 5;
        self->invincibility_timer = delay;
        if (delay > 0x19) {
            self->invincibility_timer = 0;
        }
        next_delay = self->invincibility_timer;
        if (self->invincibility_timer < 5) {
            next_delay = 5;
        }
        self->unk7E = next_delay;
    }
}

void frost_walrus_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_57.effect;
    self->on_screen = 0;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
        }
    } else {
        self->ext.raw[0] = 0;
        self->ext.raw[1] = 0;
        self->ext.raw[2] = 0;
        self->ext.raw[3] = 0;
        self->ext.raw[4] = 0;
        self->ext.raw[5] = 0;
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage != 0xC) {
            engine_obj.unkF = 0x10;
        } else {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        }
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void frost_walrus_intro(struct MainObj* self)
{
    frost_walrus_intro_funcs[self->unk6](self);
}

void frost_walrus_intro_walk(struct MainObj* self)
{
    s32 x_vel = FIXED(-0.75);

    self->unk6++;
    if (self->unk15 != 0) {
        x_vel = FIXED(0.75);
    }
    self->x_speed = x_vel;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    engine_obj.enable_boss = 1;
    set_animation(self, 0x26);
}

void frost_walrus_intro_approach(struct MainObj* self)
{
    s16 temp_a0;
    s32 temp_v0;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        start_screen_shake_y(0x18, 2, 1);
        func_8001540C(2, 0x91, self);
    }

    temp_a0 = self->x_pos.i.hi;
    temp_v0 = temp_a0 - g_Player.x_pos.i.hi;
    if (temp_v0 >= 0) {
        if (temp_v0 < 0xC1) {
            goto update;
        }
        return;
    }

    if (g_Player.x_pos.i.hi - temp_a0 <= 0xC0) {
    update:
        self->x_speed = 0;
        set_animation(self, 1);
        self->unk6++;
    }
}

void frost_walrus_intro_roar(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 0x4);
        self->unk7C = 0x50;
        self->unk6++;
    }
}

void frost_walrus_intro_burst(struct MainObj* self)
{
    struct VisualObj* visual;
    u8 i;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        for (i = 0; i < 20; i++) {
            visual = find_free_visual_obj();
            if (visual != NULL) {
                visual->active = 0x41;
                visual->id = 0x18;
                visual->unk2 = frost_walrus_burst_subtypes[i];
                visual->x_pos.i.hi = self->x_pos.i.hi + frost_walrus_burst_offsets[i][0];
                visual->y_pos.i.hi = self->y_pos.i.hi + frost_walrus_burst_offsets[i][1];
                visual->unk50 = PLAYER_OBJECT(self);
            }
        }
        func_8001540C(2, 0x94, self);
    }
    if (--self->unk7C == 0) {
        set_animation(self, 0x1A);
        if (engine_obj.stage == 2) {
            func_8002217C(9, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        self->unk6++;
    }
}

void frost_walrus_intro_start_health_bar(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (abc_object.unkC == 0) {
        self->unk7E = 3;
        self->unk6++;
        play_boss_voice(1);
    }
}

void frost_walrus_intro_fill_health(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (update_boss_music_delay() != 0) {
        return;
    }
    if (--self->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        self->unk7E = 3;
    }
    if (++self->hp == 0x30) {
        frost_walrus_choose_script(self);
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk7E = 0;
        player_end_script_action();
    }
}

void frost_walrus_think(struct MainObj* self)
{
    frost_walrus_think_funcs[self->unk6](self);
    frost_walrus_face_player(self);
}

void frost_walrus_think_next(struct MainObj* self)
{
    u8 value;

    if (*self->ext.main_57.script == 0xFF) {
        frost_walrus_choose_script(self);
    }

    value = *self->ext.main_57.script;
    if ((value & 0xFF) == 3) {
        set_animation(self, 0x1A);
        self->unk7C = 0x1E;
        self->unk6++;
    } else {
        self->unk5 = value;
        self->unk6 = 0;
    }

    self->ext.main_57.script++;
}

void frost_walrus_think_pause(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C <= 0) {
        self->unk6 = 0;
    }
}

void frost_walrus_charge(struct MainObj* self)
{
    frost_walrus_charge_funcs[self->unk6](self);
}

void frost_walrus_charge_start(struct MainObj* self)
{
    s32 var_v1;

    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk6 = (u8)self->unk6 + 1;
    if (self->ext.main_57.tusks_broken != 0) {
        set_animation(self, 0x17);
        var_v1 = -0x18000;
        if (self->unk15 != 0) {
            var_v1 = 0x18000;
        }
        self->x_speed = var_v1;
        self->hurt_box = (u8*)&frost_walrus_charge_hurt_box;
        self->attack_box = (u8*)&frost_walrus_charge_attack_box;
        func_8001540C(2, 0x93, self);
        self->unk6 = 3;
        return;
    }
    self->hurt_box = (u8*)&frost_walrus_hurt_box;
    self->attack_box = (u8*)&frost_walrus_attack_box;
    set_animation(self, 1);
}

void frost_walrus_charge_windup(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, self);
    }
    if (self->animation_step.fields.event == 2) {
        set_animation(self, 2);
        self->unk6++;
    }
}

void frost_walrus_charge_run(struct MainObj* self)
{
    s32 value;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        value = FIXED(-3);
        if (self->unk15 != 0) {
            value = FIXED(3);
        }
        self->hurt_box = (const u8*)&frost_walrus_charge_hurt_box;
        self->x_speed = value;
        self->attack_box = (const u8*)&frost_walrus_charge_attack_box;
        func_8001540C(2, 0x93, self);
        self->unk6++;
    }
}

void frost_walrus_charge_slide(struct MainObj* self)
{
    s32 mask;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    mask = 2;
    if (self->unk15 != 0) {
        mask = 1;
    }
    if (mask & self->collision_flags) {
        frost_walrus_set_floor_tiles(0x39);
        start_screen_shake_x(0x1E, 4, 1);
        func_8001540C(2, 0x90, self);
        self->unk7C = 0x28;
        self->unk6++;
    }
}

void frost_walrus_charge_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C <= 0) {
        self->hurt_box = (const u8*)&frost_walrus_hurt_box;
        self->attack_box = (const u8*)&frost_walrus_attack_box;
        frost_walrus_set_floor_tiles(0x38);
        set_animation(self, 3);
        self->unk6++;
    }
}

void frost_walrus_charge_finish(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        if (self->ext.main_57.tusks_broken == 0) {
            set_animation(self, 0);
        }
        frost_walrus_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_leap(struct MainObj* self)
{
    frost_walrus_leap_funcs[self->unk6](self);
}

void frost_walrus_leap_start(struct MainObj* self)
{
    s32 x_vel = FIXED(-3);

    if (self->unk15 != 0) {
        x_vel = FIXED(3);
    }
    self->y_speed = FIXED(6.5);
    self->gravity = FIXED(0.2578125);
    self->hurt_box = (const u8*)&frost_walrus_hurt_box;
    self->x_speed = x_vel;
    self->x_accel = 0;
    self->attack_box = (const u8*)&frost_walrus_attack_box;
    set_animation(self, 1);
    self->ext.main_57.leap_grounded = 0;
    self->unk6++;
}

void frost_walrus_leap_windup(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 2);
        self->unk6++;
    }
}

void frost_walrus_leap_jump(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->hurt_box = (const u8*)&frost_walrus_charge_hurt_box;
        self->attack_box = (const u8*)&frost_walrus_charge_attack_box;
        if (self->collision_flags & 8) {
            self->ext.main_57.leap_grounded = 1;
            self->air_state = 1;
        }
        self->unk6++;
    }
}

void frost_walrus_leap_air(struct MainObj* self)
{
    s32 side_mask;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->air_state == 1 && self->y_speed < 0) {
        self->air_state = -1;
    }
    if (self->air_state == -1 && (self->collision_flags & 8)) {
        func_8001540C(2, 0x90, self);
        func_8001540C(2, 0x93, self);
        start_screen_shake_y(0x18, 3, 1);
        self->air_state = 0;
    }
    if (self->air_state == 0) {
        side_mask = 2;
        if (self->unk15 != 0) {
            side_mask = 1;
        }
        if (side_mask & self->collision_flags) {
            frost_walrus_set_floor_tiles(0x39);
            func_8001540C(2, 0x90, self);
            start_screen_shake_x(0x1E, 4, 1);
            self->unk7C = 0x28;
            self->unk6++;
        }
    }
}

void frost_walrus_leap_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C <= 0) {
        self->hurt_box = (const u8*)&frost_walrus_hurt_box;
        self->attack_box = (const u8*)&frost_walrus_attack_box;
        frost_walrus_set_floor_tiles(0x38);
        set_animation(self, 3);
        self->unk6++;
    }
}

void frost_walrus_leap_finish(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 0);
        frost_walrus_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
        self->ext.main_57.leap_grounded = 0;
    }
}

void frost_walrus_walk(struct MainObj* self)
{
    frost_walrus_walk_funcs[self->unk6](self);
}

void frost_walrus_walk_start(struct MainObj* self)
{
    s32 x_vel = FIXED(-0.75);

    self->unk6++;
    if (self->unk15 != 0) {
        x_vel = FIXED(0.75);
    }
    self->x_speed = x_vel;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    set_animation(self, 6);
    self->hurt_box = (const u8*)&frost_walrus_hurt_box;
    self->attack_box = (const u8*)&frost_walrus_attack_box;
    self->unk7C = 0x80;
}

void frost_walrus_walk_stomp(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_8001540C(2, 0x92, self);
        start_screen_shake_y(0x18, 3, 1);
    }
    if (self->animation_step.fields.event != 2) {
        move_object(MOVING_OBJECT(self));
    }
    if (--self->unk7C <= 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_shards(struct MainObj* self)
{
    frost_walrus_shards_funcs[self->unk6](self);
}

void frost_walrus_shards_start(struct MainObj* self)
{
    set_animation(self, 7);
    self->hurt_box = (const u8*)&frost_walrus_hurt_box;
    self->attack_box = (const u8*)&frost_walrus_attack_box;
    self->unk6++;
}

void frost_walrus_shards_count(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->ext.main_57.leap_grounded = 0;
        if (self->hp >= 0x18) {
            self->ext.main_57.shard_count = 4;
        } else {
            self->ext.main_57.shard_count = 8;
        }
        self->unk7C = 0;
        self->unk6++;
    }
}

void frost_walrus_shards_fire(struct MainObj* self)
{
    u8 i;
    struct ShotObj* shot;

    i = 0;
    do {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x23;
            shot->unk2 = i + self->unk7C;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk7 = self->ext.main_57.shard_count;
            self->ext.main_57.shot = shot;
        }
        i++;
    } while (i < 2);

    self->unk7E = 0x20;
    self->unk7C += 2;
    self->unk6++;
}

void frost_walrus_shards_repeat(struct MainObj* self)
{
    if (self->unk7E != 0) {
        self->unk7E--;
        return;
    }
    if (self->unk7C == self->ext.main_57.shard_count) {
        set_animation(self, 1);
        self->unk7C = 0;
        self->unk6++;
    } else {
        self->unk6--;
    }
}

void frost_walrus_shards_finish(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, self);
    }
    if (self->animation_step.fields.event == 2) {
        set_animation(self, 0x1A);
        self->unk7C = 0x40;
        self->unk6++;
    }
}

void frost_walrus_shards_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_breath(struct MainObj* self)
{
    frost_walrus_breath_funcs[self->unk6](self);
}

void frost_walrus_breath_start(struct MainObj* self)
{
    set_animation(self, 4);
    self->hurt_box = (const u8*)&frost_walrus_hurt_box;
    self->attack_box = (const u8*)&frost_walrus_attack_box;
    self->unk7C = 0x80;
    self->unk7E = 0x18;
    self->unk6++;
}

void frost_walrus_breath_blow(struct MainObj* self)
{
    struct VisualObj* vobj;
    struct ShotObj* sobj;

    animate_object(ANIMATED_OBJECT(self));

    if (--self->unk7E == 0) {
        func_8001540C(2, 0x94, self);
        self->unk7E = 0x18;
    }

    if (--self->unk7C == 0) {
        self->unk7C = 0x30;
        self->unk6++;
    }

    if (self->animation_step.fields.event == 2) {
        vobj = find_free_visual_obj();
        if (vobj != NULL) {
            vobj->active = 0x41;
            vobj->id = 0x18;
            vobj->unk2 = 0x10;
            vobj->unk15 = self->unk15;
            vobj->unk50 = self;
            vobj->x_pos.i.hi = self->x_pos.i.hi + (self->unk15 ? 0x15 : -0x15);
            vobj->y_pos.i.hi = self->y_pos.i.hi;
        }
    }

    if (self->unk7C == 0x40) {
        sobj = find_free_shot_obj();
        if (sobj != NULL) {
            sobj->active = 0x41;
            sobj->id = 0x23;
            sobj->unk2 = 0x10;
            sobj->unk7C = self;
            self->ext.main_57.shot = sobj;
        }
    }
}

void frost_walrus_breath_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 1);
        self->unk6++;
    }
}

void frost_walrus_breath_launch(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        self->ext.main_57.shot->unk8C.word = self->animation_step.fields.event;
        spawn_debris(0xA, frost_walrus_breath_debris, self->ext.main_57.shot);
    }
    if (self->animation_step.fields.event == 2) {
        set_animation(self, 0);
        self->unk7C = 0x20;
        self->unk6++;
    }
}

void frost_walrus_breath_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_blizzard(struct MainObj* self)
{
    frost_walrus_blizzard_funcs[self->unk6](self);
}

void frost_walrus_blizzard_start(struct MainObj* self)
{
    set_animation(self, 0x16);
    self->hurt_box = (const u8*)&frost_walrus_hurt_box;
    self->attack_box = (const u8*)&frost_walrus_attack_box;
    self->unk7C = 0x100;
    self->unk7E = 0x18;
    self->unk6++;
}

void frost_walrus_blizzard_blow(struct MainObj* self)
{
    struct VisualObj* vobj;
    struct ShotObj* sobj;

    animate_object(ANIMATED_OBJECT(self));

    if (--self->unk7E == 0) {
        func_8001540C(2, 0x94, self);
        self->unk7E = 0x18;
    }

    if (--self->unk7C == 0) {
        set_animation(self, 0x16);
        self->unk7C = 0x80;
        self->unk6++;
    }

    if (self->animation_step.fields.event == 2) {
        vobj = find_free_visual_obj();
        if (vobj != NULL) {
            vobj->active = 0x41;
            vobj->id = 0x18;
            vobj->unk2 = 0x30;
            vobj->unk15 = self->unk15;
            vobj->unk50 = self;
            vobj->x_pos.i.hi = self->x_pos.i.hi + (self->unk15 ? 0x15 : -0x15);
            vobj->y_pos.i.hi = self->y_pos.i.hi;
        }
    }

    if (self->unk7C == 0x40) {
        sobj = find_free_shot_obj();
        if (sobj != NULL) {
            sobj->active = 0x41;
            sobj->id = 0x23;
            sobj->unk2 = 0x20;
            sobj->unk7C = self;
            self->ext.main_57.shot = sobj;
        }
    }
}

void frost_walrus_blizzard_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x60;
        self->unk6++;
    }
}

void frost_walrus_blizzard_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_blizzard_idle(struct MainObj* self)
{
}

void frost_walrus_stagger(struct MainObj* self)
{
    frost_walrus_stagger_funcs[self->unk6](self);
}

// frost_walrus_stagger_start
INCLUDE_ASM("main/nonmatchings/mains/main_57_frost_walrus", func_80073E80);

void frost_walrus_stagger_fall(struct MainObj* self)
{
    struct VisualObj* temp_v0;

    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed < 0) {
        self->air_state = -1;
    }
    if ((self->air_state == -1) && (self->collision_flags & 8)) {
        set_animation(self, 0x14);
        if (self->ext.main_57.tusks_broken == 0) {
            temp_v0 = find_free_visual_obj();
            if (temp_v0 != 0) {
                temp_v0->active = 0x41;
                temp_v0->id = 0x18;
                temp_v0->unk2 = 0x50;
                temp_v0->unk15 = self->unk15;
                temp_v0->unk50 = PLAYER_OBJECT(self);
                self->ext.main_57.tusks_broken = 1;
            }
        }
        self->air_state = 0;
        start_screen_shake_y(0x10, 3, 1);
        self->unk6++;
    }
}

void frost_walrus_stagger_slide(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->collision_flags & 3) {
        start_screen_shake_x(0x10, 3, 1);
        self->unk7C = 0x20;
        self->unk6++;
    }
}

void frost_walrus_stagger_recover(struct MainObj* self)
{
    if (--self->unk7C != 0) {
        animate_object(ANIMATED_OBJECT(self));
        return;
    }
    if (self->hp >= 0x18) {
        self->ext.main_57.script = frost_walrus_script_recover_high;
    } else {
        self->ext.main_57.script = frost_walrus_script_recover_low;
    }
    self->unk5 = 3;
    self->unk6 = 0;
    self->ext.main_57.flashing = 0;
    self->ext.main_57.flash_timer = 1;
}

void frost_walrus_regrow(struct MainObj* self)
{
    frost_walrus_regrow_funcs[self->unk6](self);
}

void frost_walrus_regrow_start(struct MainObj* self)
{
    struct VisualObj* visual;

    self->collision_data = (const u16*)D_801060F0;
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0x18;
        visual->unk2 = 0x20;
        visual->unk15 = self->unk15;
        visual->unk50 = PLAYER_OBJECT(self);
        visual->x_pos.u.hi = self->x_pos.u.hi;
        visual->y_pos.u.hi = self->y_pos.u.hi;
        set_animation(self, 0x19);
        self->unk6++;
    }
}

void frost_walrus_regrow_finish(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->collision_data = (const u16*)D_80107A78;
        self->ext.main_57.flash_timer = 0;
        self->ext.main_57.tusks_broken = 0;
        self->ext.main_57.staggered = 0;
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void frost_walrus_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

void frost_walrus_choose_script(struct MainObj* self)
{
    u8 index;
    u8** choices;
    u8* thresholds;
    u8 i;
    u32 rnd;

    index = (self->hp - 1) / 16;
    choices = frost_walrus_scripts[index];
    rnd = get_random();
    i = 0;
    thresholds = frost_walrus_script_weights[index];
    rnd &= 0xF;
    while (i < 4) {
        if (rnd < thresholds[i]) {
            self->ext.main_57.script = choices[i];
            return;
        }
        i++;
    }
}

void frost_walrus_set_floor_tiles(s32 self)
{
    u16* list;
    u32* attrs;

    list = frost_walrus_floor_tiles;
    if (engine_obj.stage == 0xC) {
        list = frost_walrus_floor_tiles_rush;
    }
    while (*list != 0) {
        attrs = SP_BG_TILE_ATTRS;
        attrs[*list] &= ~0xFF;
        attrs[*list] |= self;
        list++;
    }
}

u8 frost_walrus_script_2_0[4] = { 3, 6, 4, 255 };

u8 frost_walrus_script_2_1[4] = { 3, 6, 5, 255 };

u8 frost_walrus_script_1_0[4] = { 6, 4, 7, 255 };

u8 frost_walrus_script_1_1[4] = { 6, 5, 7, 255 };

u8 frost_walrus_script_0_0[8] = { 6, 8, 8, 5, 255, 0, 0, 0 };

u8 frost_walrus_script_0_1[4] = { 6, 8, 4, 255 };

u8 frost_walrus_script_0_2[4] = { 6, 7, 4, 255 };

u8 frost_walrus_script_0_3[8] = { 6, 7, 7, 5, 255, 0, 0, 0 };

u8 frost_walrus_script_recover_high[4] = { 4, 11, -1, 0 };

u8 frost_walrus_script_recover_low[4] = { 9, 11, -1, 0 };

u8* frost_walrus_script_table_2[4] = {
    frost_walrus_script_2_0,
    frost_walrus_script_2_0,
    frost_walrus_script_2_1,
    frost_walrus_script_2_1,
};

u8* frost_walrus_script_table_1[4] = {
    frost_walrus_script_1_0,
    frost_walrus_script_1_0,
    frost_walrus_script_1_1,
    frost_walrus_script_1_1,
};

u8* frost_walrus_script_table_0[4] = {
    frost_walrus_script_0_0,
    frost_walrus_script_0_1,
    frost_walrus_script_0_2,
    frost_walrus_script_0_3,
};

u8** frost_walrus_scripts[3] = {
    frost_walrus_script_table_0,
    frost_walrus_script_table_1,
    frost_walrus_script_table_2,
};

u8 frost_walrus_script_weights[3][4] = {
    { 0x02, 0x0A, 0x0E, 0x10 },
    { 0x05, 0x07, 0x0C, 0x10 },
    { 0x05, 0x07, 0x0C, 0x10 },
};

union AnimationStep frost_walrus_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep frost_walrus_anim_1[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x15010002 },
    { 0x1601000A },
    { 0x15010002 },
    { 0x00010001 },
    { 0x00010101 },
    { 0x17010301 },
    { 0x17010001 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010008 },
    { 0x00010001 },
    { 0x00010201 },
    { 0x01010002 },
    { 0x15010002 },
    { 0x1601000A },
    { 0x15010002 },
    { 0x00010002 },
    { 0x17010301 },
    { 0x17010001 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17000008 },
};

u8 frost_walrus_anim_2[44] = { 2, 0, 1, 0, 2, 0, 1, 1, 2, 0, 1, 21, 16, 0, 1, 22, 2, 0, 1, 21, 1, 1, 1, 4, 3, 0, 1, 4, 4, 0, 1, 5, 1, 2, 1, 6, 7, 0, 1, 6, 2, 0, 255, 7 };

union AnimationStep frost_walrus_anim_3[] = {
    { 0x05010002 },
    { 0x04010002 },
    { 0x00000002 },
};

struct Unk_unk68 frost_walrus_anim_4[9] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 18, 0, 1, 3 },
    { 1, 0, 1, 2 },
    { 1, 1, 1, 2 },
    { 1, 2, 1, 25 },
    { 1, 0, 1, 25 },
    { 2, 0, -2, 26 },
};

union AnimationStep frost_walrus_anim_5[] = {
    { 0x04010002 },
    { 0x05010006 },
    { 0x04010002 },
    { 0x00000002 },
};

struct Unk_unk68 frost_walrus_anim_6[28] = {
    { 3, 0, 1, 62 },
    { 3, 0, 1, 63 },
    { 12, 0, 1, 64 },
    { 3, 0, 1, 65 },
    { 2, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 2, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 2, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 2, 0, 1, 66 },
    { 1, 1, 1, 67 },
    { 29, 2, 1, 67 },
    { 3, 0, 1, 66 },
    { 3, 0, 1, 68 },
    { 3, 0, 1, 69 },
    { 12, 0, 1, 70 },
    { 3, 0, 1, 71 },
    { 2, 0, 1, 60 },
    { 2, 0, 1, 61 },
    { 2, 0, 1, 60 },
    { 2, 0, 1, 61 },
    { 2, 0, 1, 60 },
    { 2, 0, 1, 61 },
    { 2, 0, 1, 60 },
    { 1, 1, 1, 61 },
    { 29, 2, 1, 61 },
    { 3, 0, -27, 60 },
};

union AnimationStep frost_walrus_anim_7[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x34000002 },
};

union AnimationStep frost_walrus_anim_8[] = {
    { 0x2F010002 },
    { 0x2E010002 },
    { 0x2D01000C },
    { 0x2C000002 },
};

union AnimationStep frost_walrus_anim_9[] = {
    { 0x33010002 },
    { 0x32010002 },
    { 0x31010002 },
    { 0x2F010002 },
    { 0x2E010002 },
    { 0x2D01000C },
    { 0x2C000002 },
};

union AnimationStep frost_walrus_anim_10[] = {
    { 0x35000001 },
};

union AnimationStep frost_walrus_anim_11[] = {
    { 0x36010001 },
    { 0x37010001 },
    { 0x36010001 },
    { 0x37010001 },
    { 0x36010001 },
    { 0x37010001 },
    { 0x36000001 },
};

union AnimationStep frost_walrus_anim_12[] = {
    { 0x38000001 },
};

union AnimationStep frost_walrus_anim_13[] = {
    { 0x39000001 },
};

union AnimationStep frost_walrus_anim_14[] = {
    { 0x3A000001 },
};

union AnimationStep frost_walrus_anim_15[] = {
    { 0x3B000001 },
};

union AnimationStep frost_walrus_anim_16[] = {
    { 0x20010002 },
    { 0x1F010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x3301001E },
    { 0x6A010002 },
    { 0x6A010002 },
    { 0x6A000002 },
};

union AnimationStep frost_walrus_anim_17[] = {
    { 0x1C010002 },
    { 0x1C010002 },
    { 0x1C010002 },
    { 0x1C010002 },
    { 0x0301001E },
    { 0x02010002 },
    { 0x01010002 },
    { 0x00000002 },
};

union AnimationStep frost_walrus_anim_18[] = {
    { 0x08000001 },
};

struct Unk_unk68 frost_walrus_anim_19[7] = {
    { 3, 0, 1, 72 },
    { 3, 0, 1, 73 },
    { 3, 0, 1, 74 },
    { 3, 0, 1, 75 },
    { 3, 0, 1, 76 },
    { 3, 0, 1, 77 },
    { 3, 0, -6, 78 },
};

u8 frost_walrus_anim_20[8] = { 2, 0, 1, 33, 2, 0, 255, 34 };

union AnimationStep frost_walrus_anim_21[] = {
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B000002 },
};

struct Unk_unk68 frost_walrus_anim_22[8] = {
    { 2, 0, 1, 20 },
    { 2, 0, 1, 27 },
    { 18, 0, 1, 28 },
    { 1, 0, 1, 27 },
    { 1, 1, 1, 27 },
    { 1, 2, 1, 107 },
    { 1, 0, 1, 107 },
    { 2, 0, -2, 108 },
};

u8 frost_walrus_anim_23[12] = { 2, 0, 1, 20, 2, 0, 1, 10, 2, 0, 255, 11 };

union AnimationStep frost_walrus_anim_24[] = {
    { 0x6A010002 },
    { 0x6A010002 },
    { 0x20010002 },
    { 0x1F010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x6A01001E },
    { 0x6A010002 },
    { 0x6A010002 },
    { 0x6A000002 },
};

union AnimationStep frost_walrus_anim_25[] = {
    { 0x14010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1C010002 },
    { 0x1C010002 },
    { 0x1C010002 },
    { 0x0301001E },
    { 0x02010002 },
    { 0x01010002 },
    { 0x00000002 },
};

struct Unk_unk68 frost_walrus_anim_26[6] = {
    { 5, 0, 1, 0 },
    { 5, 0, 1, 1 },
    { 5, 0, 1, 0 },
    { 5, 0, 1, 4 },
    { 13, 0, 1, 5 },
    { 2, 0, -5, 4 },
};

union AnimationStep frost_walrus_anim_27[] = {
    { 0x09000001 },
};

union AnimationStep frost_walrus_anim_28[] = {
    { 0x0C000001 },
};

union AnimationStep frost_walrus_anim_29[] = {
    { 0x50010003 },
    { 0x51010003 },
    { 0x52010003 },
    { 0x53010006 },
    { 0x54010006 },
    { 0x55010006 },
    { 0x56010006 },
    { 0x57010006 },
    { 0x58010006 },
    { 0x59000006 },
};

union AnimationStep frost_walrus_anim_30[] = {
    { 0x61010002 },
    { 0x62010002 },
    { 0x63010002 },
    { 0x64010002 },
    { 0x65000102 },
};

union AnimationStep frost_walrus_anim_31[] = {
    { 0x61010002 },
    { 0x62010002 },
    { 0x66010002 },
    { 0x67010002 },
    { 0x68000102 },
};

union AnimationStep frost_walrus_anim_32[] = {
    { 0x5A000001 },
};

union AnimationStep frost_walrus_anim_33[] = {
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5B000001 },
};

union AnimationStep frost_walrus_anim_34[] = {
    { 0x5D010001 },
    { 0x5E010001 },
    { 0x5D010001 },
    { 0x5E010001 },
    { 0x5D010001 },
    { 0x5E010001 },
    { 0x5D000001 },
};

union AnimationStep frost_walrus_anim_35[] = {
    { 0x5F000001 },
};

union AnimationStep frost_walrus_anim_36[] = {
    { 0x60000001 },
};

u8 frost_walrus_anim_37[8] = { 1, 0, 0, 105, 1, 0, 255, 106 };

struct Unk_unk68 frost_walrus_anim_38[24] = {
    { 3, 0, 1, 62 },
    { 3, 0, 1, 63 },
    { 6, 0, 1, 64 },
    { 3, 0, 1, 65 },
    { 1, 1, 1, 66 },
    { 1, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 2, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 2, 0, 1, 66 },
    { 6, 0, 1, 67 },
    { 3, 0, 1, 66 },
    { 3, 0, 1, 68 },
    { 3, 0, 1, 69 },
    { 6, 0, 1, 70 },
    { 3, 0, 1, 71 },
    { 1, 1, 1, 60 },
    { 1, 0, 1, 60 },
    { 2, 0, 1, 61 },
    { 2, 0, 1, 60 },
    { 2, 0, 1, 61 },
    { 2, 0, 1, 60 },
    { 6, 0, 1, 61 },
    { 3, 0, -23, 60 },
};

void* frost_walrus_animations[39] = {
    frost_walrus_anim_0,
    frost_walrus_anim_1,
    frost_walrus_anim_2,
    frost_walrus_anim_3,
    frost_walrus_anim_4,
    frost_walrus_anim_5,
    frost_walrus_anim_6,
    frost_walrus_anim_7,
    frost_walrus_anim_8,
    frost_walrus_anim_9,
    frost_walrus_anim_10,
    frost_walrus_anim_11,
    frost_walrus_anim_12,
    frost_walrus_anim_13,
    frost_walrus_anim_14,
    frost_walrus_anim_15,
    frost_walrus_anim_16,
    frost_walrus_anim_17,
    frost_walrus_anim_18,
    frost_walrus_anim_19,
    frost_walrus_anim_20,
    frost_walrus_anim_21,
    frost_walrus_anim_22,
    frost_walrus_anim_23,
    frost_walrus_anim_24,
    frost_walrus_anim_25,
    frost_walrus_anim_26,
    frost_walrus_anim_27,
    frost_walrus_anim_28,
    frost_walrus_anim_29,
    frost_walrus_anim_30,
    frost_walrus_anim_31,
    frost_walrus_anim_32,
    frost_walrus_anim_33,
    frost_walrus_anim_34,
    frost_walrus_anim_35,
    frost_walrus_anim_36,
    frost_walrus_anim_37,
    frost_walrus_anim_38,
};

struct Unk_unk68 frost_walrus_terrain_box = { 0, 23, 46, 43 };

struct Unk_unk68 frost_walrus_hurt_box = { -47, -39, 96, 110 };

struct Unk_unk68 frost_walrus_charge_hurt_box = { -67, -4, -120, 75 };

struct Unk_unk68 frost_walrus_attack_box = { -37, -28, 79, 98 };

struct Unk_unk68 frost_walrus_charge_attack_box = { -55, -9, 112, 80 };

s16 frost_walrus_burst_offsets[20][2] = {
    { -78, -6 },
    { -46, 2 },
    { -23, 2 },
    { -46, 13 },
    { -43, 27 },
    { 14, 13 },
    { 17, 24 },
    { 47, -6 },
    { -87, -7 },
    { -64, -7 },
    { -52, -12 },
    { -19, -12 },
    { -52, 10 },
    { -19, 10 },
    { 31, -4 },
    { 57, -4 },
    { 20, 36 },
    { 17, 2 },
    { -49, 2 },
    { -37, 33 },
};

u8 frost_walrus_burst_subtypes[32] = { 0x00, 0x01, 0x01, 0x03, 0x03, 0x02, 0x02, 0x00, 0x00, 0x00, 0x03, 0x02, 0x03, 0x02, 0x00, 0x00, 0x02, 0x02, 0x03, 0x03, 0x0C, 0x0D, 0x0E, 0x0F, 0x0D, 0x0F, 0x0C, 0x0E, 0x0D, 0x0F, 0x00, 0x00 };

struct Unk_unk68 frost_walrus_breath_debris[3] = {
    { 12, 13, 35, 15 },
    { 35, 15, 36, 14 },
    { 36, 15, 0, 0 },
};

u16 frost_walrus_floor_tiles[18] = {
#ifdef VERSION_JP
    0x0387,
    0x055B,
    0x038C,
    0x0720,
    0x0722,
    0x0724,
    0x06BB,
    0x03A2,
    0x03A6,
    0x03AE,
    0x03B1,
    0x03B9,
    0x03C0,
    0x0388,
    0x063A,
    0x0388,
#else
    0x0388,
    0x055D,
    0x038D,
    0x0722,
    0x0724,
    0x0726,
    0x068D,
    0x03A3,
    0x03A7,
    0x03AF,
    0x03B2,
    0x03BA,
    0x03C2,
    0x03C1,
    0x0389,
    0x063C,
#endif
    0x0000,
    0x0000,
};

u16 frost_walrus_floor_tiles_rush[20] = {
    0x0383,
    0x03A0,
    0x0390,
    0x0392,
    0x0394,
    0x0396,
    0x0380,
    0x0562,
    0x038D,
    0x03C3,
    0x03AC,
    0x03AF,
    0x03B2,
    0x03B5,
    0x0388,
    0x038D,
    0x0563,
    0x03AC,
    0x0000,
    0x0000,
};

void (*frost_walrus_state_funcs[3])() = {
    frost_walrus_start,
    func_80072418,
    frost_walrus_death,
};

void (*frost_walrus_start_funcs[2])(struct MainObj*) = {
    frost_walrus_start_warning,
    func_800722A0,
};

void (*frost_walrus_step_funcs[12])() = {
    enemy_hit_reaction,
    frost_walrus_reset,
    frost_walrus_intro,
    frost_walrus_think,
    frost_walrus_charge,
    frost_walrus_leap,
    frost_walrus_walk,
    frost_walrus_shards,
    frost_walrus_breath,
    frost_walrus_blizzard,
    frost_walrus_stagger,
    frost_walrus_regrow,
};

void (*frost_walrus_death_funcs[3])() = {
    func_80072628,
    frost_walrus_death_explode,
    frost_walrus_death_finish,
};

void (*frost_walrus_intro_funcs[6])(struct MainObj*) = {
    frost_walrus_intro_walk,
    frost_walrus_intro_approach,
    frost_walrus_intro_roar,
    frost_walrus_intro_burst,
    frost_walrus_intro_start_health_bar,
    frost_walrus_intro_fill_health,
};

void (*frost_walrus_think_funcs[2])() = {
    frost_walrus_think_next,
    frost_walrus_think_pause,
};

void (*frost_walrus_charge_funcs[6])(struct MainObj*) = {
    frost_walrus_charge_start,
    frost_walrus_charge_windup,
    frost_walrus_charge_run,
    frost_walrus_charge_slide,
    frost_walrus_charge_recover,
    frost_walrus_charge_finish,
};

void (*frost_walrus_leap_funcs[6])(struct MainObj*) = {
    frost_walrus_leap_start,
    frost_walrus_leap_windup,
    frost_walrus_leap_jump,
    frost_walrus_leap_air,
    frost_walrus_leap_recover,
    frost_walrus_leap_finish,
};

void (*frost_walrus_walk_funcs[2])() = {
    frost_walrus_walk_start,
    frost_walrus_walk_stomp,
};

void (*frost_walrus_shards_funcs[6])() = {
    frost_walrus_shards_start,
    frost_walrus_shards_count,
    frost_walrus_shards_fire,
    frost_walrus_shards_repeat,
    frost_walrus_shards_finish,
    frost_walrus_shards_wait,
};

void (*frost_walrus_breath_funcs[5])() = {
    frost_walrus_breath_start,
    frost_walrus_breath_blow,
    frost_walrus_breath_wait,
    frost_walrus_breath_launch,
    frost_walrus_breath_finish,
};

void (*frost_walrus_blizzard_funcs[5])() = {
    frost_walrus_blizzard_start,
    frost_walrus_blizzard_blow,
    frost_walrus_blizzard_wait,
    frost_walrus_blizzard_finish,
    frost_walrus_blizzard_idle,
};

void (*frost_walrus_stagger_funcs[4])() = {
    func_80073E80,
    frost_walrus_stagger_fall,
    frost_walrus_stagger_slide,
    frost_walrus_stagger_recover,
};

void (*frost_walrus_regrow_funcs[2])() = {
    frost_walrus_regrow_start,
    frost_walrus_regrow_finish,
};
