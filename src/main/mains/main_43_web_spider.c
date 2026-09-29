// MainObj, main_object_update_funcs[43]
// 800631C8..80065930
#include "common.h"
#include "func_tables.h"

void func_800643B0(struct MainObj* arg0);
void web_spider_attack_web(struct MainObj* arg0);

void web_spider_update(struct MainObj* self)
{
    if (self->unk2 == 0) {
        web_spider_state_funcs[self->state](self);
    } else {
        spiderling_state_funcs[self->state](self);
    }
}

void web_spider_intro(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    web_spider_intro_funcs[self->unk5](self);
    if (self->unk5 >= 2) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void web_spider_intro_warning(struct MainObj* self)
{
    struct EffectObj* effect;

    if (g_Player.capsule_state == 0) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_43.effect = effect;
        }
        player_start_script_action(0x14, 0x40);
        web_spider_arena_x = background_objects[0].unk26;
        web_spider_arena_y = background_objects[0].unk2A;
        self->unk5 = 1;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void web_spider_intro_setup(struct MainObj* self)
{
    s32* archive;
    s32 offset;

    if (self->ext.main_43.effect->active == 0) {
        self->unk5 = 2;
        self->hurt_box = &web_spider_hurt_box;
        self->attack_box = &web_spider_attack_box;
        self->terrain_box = NULL;
        self->collision_data = D_801075F4;
        self->bg_offset = g_Player.bg_offset;
        if (engine_obj.stage != 0xC) {
            self->unk40 = (D_801406A8[0] >> 7) + 0xB0;
        } else {
            archive = SP_MENU_FRAMES;
            self->unk40 = (D_801406A8[0] >> 7) + 0x160;
            offset = archive[4];
            self->unk42 = 0x7888;
            self->sprite_frames = (u8*)archive + offset;
        }
        self->animation_table = (const u8* const*)web_spider_animations;
        self->unk16 = 4;
        self->contact_damage = 6;
        self->invincibility_timer = -0x80;
        self->unk63 = 2;
        self->unk7C = 7;
        self->hp = 0;
        self->unk62 = 0;
        self->ext.main_43.flash_timer = 0;
        self->ext.main_43.shot = NULL;
        self->ext.main_43.hurt_collision = 0;
        self->ext.main_43.big_web_done = 0;
        engine_obj.enable_boss = 0;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = self;
    }
}

// web_spider_intro_enter
INCLUDE_ASM("main/nonmatchings/mains/main_43_web_spider", func_8006346C);

void web_spider_intro_spawn_thread(struct MainObj* self)
{
    vent_spawn_mixed_puffs(self, 8);
    self->unk7C = 0x40;
    self->unk5 = 4;
    self->ext.main_43.shot = web_spider_spawn_thread(self, 0);
}

void web_spider_intro_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 5;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = FIXED(-8);
        self->gravity = 0;
        set_animation(self, 0);
    }
}

void web_spider_intro_descend(struct MainObj* self)
{
    s16 timer;

    if (self->unk6 == 0) {
        if (self->y_pos.i.hi - background_objects[self->bg_offset].y_pos.i.hi >= 0x88) {
            self->unk6 = 1;
            self->unk7C = 0x1E;
            self->y_speed = FIXED(1);
            set_animation(self, 1);
        } else {
            move_with_gravity(ANIMATED_OBJECT(self));
        }
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        timer = (u16)self->unk7C - 1;
        self->unk7C = timer;
        if (timer == 0) {
            self->unk5 = 6;
            self->y_speed = 0;
            self->gravity = 0;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7C = 2;
        } else if (timer == 0xF) {
            self->y_speed = FIXED(-1);
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_spider_intro_pose(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->unk5 = 7;
        if (engine_obj.stage == 1) {
            ((void (*)(u16, u8, s8))func_8002217C)(8, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void web_spider_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk5 = 8;
        engine_obj.enable_boss = 1;
        play_boss_music(0);
    }
}

void web_spider_intro_fill_health(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    if ((update_boss_music_delay() == 0) && (self->animation_step.fields.relative_step == 0)) {
        if (self->hp < 0x30) {
            timer = (u16)self->unk7C - 1;
            self->unk7C = timer;
            if (timer == 0) {
                func_8001540C(0, 0xE, 0);
                self->unk7C = 2;
            }
            self->hp = (u8)self->hp + 1;
            return;
        }
        self->unk5 = 9;
        self->y_speed = FIXED(3.5);
        player_end_script_action();
        set_animation(self, 0x1F);
    }
}

void web_spider_intro_climb(struct MainObj* self)
{
    if (self->on_screen == 0) {
        self->state = 1;
        self->unk5 = 2;
        self->invincibility_timer = 0;
        return;
    }
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        func_8001540C(2, 0x70, self);
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

// web_spider_main
INCLUDE_ASM("main/nonmatchings/mains/main_43_web_spider", func_8006398C);

void web_spider_drop(struct MainObj* self)
{
    web_spider_drop_funcs[self->unk6](self);
}

// web_spider_drop_start
INCLUDE_ASM("main/nonmatchings/mains/main_43_web_spider", func_80063B20);

void web_spider_drop_climb(struct MainObj* self)
{
    switch (self->unk7) {
    case 0:
        if (self->unk7C == 0) {
            if ((get_random() & 0xF) != 0 && g_Player.stun_timer == 0) {
                self->unk5 = 3;
                self->unk6 = 0;
                self->unk7 = 0;
                if (self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0) {
                    self->unk15 = 0;
                } else {
                    self->unk15 = 0x40;
                }
            } else {
                self->y_speed = FIXED(3.5);
                self->gravity = 0;
                self->unk7 = 1;
                set_animation(self, 0x1F);
                func_8001540C(2, 0x70, self);
            }
        } else {
            self->unk7C--;
        }
        break;
    case 1:
        if (self->on_screen == 0) {
            self->unk7 = 2;
            self->unk7C = 8;
            if (self->ext.main_43.hurt_collision != 0) {
                self->collision_data = D_801075F4;
                self->ext.main_43.hurt_collision = 0;
            }
        }
        if (self->animation_step.fields.event != 0) {
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0x70, self);
        }
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
        break;
    case 2:
        if (--self->unk7C == 0) {
            self->unk6 = 0;
            self->unk7 = 0;
        }
        break;
    }
}

void web_spider_shoot(struct MainObj* self)
{
    web_spider_shoot_funcs[self->unk6](self);
}

void web_spider_shoot_start(struct MainObj* self)
{
    self->unk6 = 1;
    set_animation(self, 3);
}

void web_spider_shoot_fire(struct AnimatedObj* self)
{
    if (self->animation_step.fields.relative_step != 0) {
        if (self->animation_step.fields.event == 1) {
            web_spider_spawn_web_shot(self, self->unk7);
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0x72, self);
        }
        if (self->animation_step.fields.event == 2) {
            self->animation_step.fields.event = 0;
            web_spider_spawn_web_flash(self);
        }
    } else {
        self->y_vel.val = FIXED(3.5);
        self->unk5 = 2;
        self->unk2C = 0;
        self->unk6 = 1;
        self->unk7 = 1;
        set_animation(self, 0x1F);
        func_8001540C(2, 0x70, self);
    }
    animate_object(self);
}

void web_spider_swing(struct MainObj* self)
{
    web_spider_swing_funcs[self->unk6](self);
}

void web_spider_swing_start(struct MainObj* self)
{
    self->unk6 = 1;
    self->ext.main_43.move_direction = 0;
    self->ext.main_43.animation_set = web_spider_swing_sets[get_random() & 0xF];
    web_spider_set_move_timer(self);
    self->ext.main_43.animation_index = 0;
    self->ext.main_43.animation_length = 7;
    web_spider_set_swing_animation(self);
}

// web_spider_swing_move
INCLUDE_ASM("main/nonmatchings/mains/main_43_web_spider", func_80064154);

void web_spider_swing_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6 = 0;
    }
}

void web_spider_attack(struct MainObj* self)
{
    if ((self->ext.main_43.unk94 == 0) && (self->ext.main_43.attack_count != 0)) {
        web_spider_attack_web(self);
    } else {
        func_800643B0(self);
    }
}

// web_spider_attack_spiderlings
INCLUDE_ASM("main/nonmatchings/mains/main_43_web_spider", func_800643B0);

void web_spider_attack_web(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        set_animation(self, 0xA);
        if (self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0) {
            self->unk15 = 0;
        } else {
            self->unk15 = 0x40;
        }
        return;
    }
    if (self->animation_step.fields.relative_step != 0) {
        if (self->animation_step.fields.event == 1) {
            web_spider_spawn_web_shot(ANIMATED_OBJECT(self), self->unk7);
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0x72, self);
        }
        if (self->animation_step.fields.event == 2) {
            self->animation_step.fields.event = 0;
            web_spider_spawn_web_flash(ANIMATED_OBJECT(self));
        }
    } else {
        self->unk5 = 4;
        self->unk6 = 1;
        self->unk7 = 0;
        set_animation(self, self->ext.main_43.animation_id);
        web_spider_set_attack_cooldown(self);
        self->ext.main_43.attack_count++;
        if (self->ext.main_43.attack_count >= 3) {
            self->ext.main_43.attack_count = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_spider_big_web(struct MainObj* self)
{
    web_spider_big_web_funcs[self->unk6](self);
}

// web_spider_big_web_start
INCLUDE_ASM("main/nonmatchings/mains/main_43_web_spider", func_800646EC);

void web_spider_big_web_spin(struct MainObj* arg0)
{
    struct VisualObj* self = VISUAL_OBJECT(arg0);
    s8 state = self->unk7;
    u32 i;

    switch (state) {
    case 0:
        self->unk7 = 1;
        set_animation(self, 4);
        break;
    case 1:
        if (self->animation_step.fields.relative_step == 0) {
            self->unk7 = 2;
        } else if (self->animation_step.fields.event != 0) {
            for (i = 0; i < 4U; i++) {
                web_spider_spawn_web_piece(self, (i + 1) & 0xFF);
            }
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0x73, self);
        }
        animate_object(ANIMATED_OBJECT(self));
        break;
    case 2:
        self->unk6 = 2;
        self->unk7 = 0;
        break;
    }
}

void web_spider_big_web_center(struct MainObj* self)
{
    switch (self->unk7) {
    case 0:
        self->unk7 = 1;
        self->ext.main_43.shot->state = 2;
        self->y_speed = FIXED(1);
        self->gravity = FIXED(0.5);
        set_animation(self, 5);
        break;
    case 1:
        if (self->animation_step.fields.relative_step != 0) {
            if (self->animation_step.fields.event != 0) {
                self->animation_step.fields.event = 0;
                self->y_speed = 0;
                self->gravity = 0;
            }
            animate_object(ANIMATED_OBJECT(self));
            move_with_gravity(ANIMATED_OBJECT(self));
        } else {
            self->unk7 = 2;
        }
        break;
    case 2:
        self->unk5 = 4;
        self->unk6 = 0;
        self->unk7 = 0;
        self->x_pos.i.lo = 0;
        self->y_pos.i.lo = 0;
        self->x_pos.i.hi = web_spider_arena_x + 0xA0;
        self->y_pos.i.hi = web_spider_arena_y + 0x70;
        web_spider_set_attack_cooldown(self);
        self->collision_data = D_801075F4;
        break;
    }
}

void web_spider_fall(struct MainObj* self)
{
    web_spider_fall_funcs[self->unk6](self);
    CollisionRelated((struct PlayerObj*)self);
}

void web_spider_fall_start(struct MainObj* self)
{
    self->unk6 = 1;
    self->y_speed = FIXED(4);
    self->x_speed = 0;
    self->x_accel = 0;
    self->gravity = FIXED(0.25);
    set_animation(self, 0xD);
    self->terrain_box = &D_800FF5B0;
    self->collision_data = (const u16*)D_801060F0;
    self->ext.main_43.hurt_collision = 1;
}

void web_spider_fall_slow(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 2;
        self->y_speed = 0;
        self->gravity = FIXED(0.5);
        set_animation(self, 0xE);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void web_spider_fall_land(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        self->unk6 = 3;
        self->y_speed = 0;
        self->gravity = 0;
        set_animation(self, 0xF);
        self->terrain_box = NULL;
        func_8001540C(2, 0x74, self);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void web_spider_fall_crash(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 4;
        set_animation(self, 0x10);
    } else if (self->animation_step.fields.event != 0) {
        self->hp -= 4;
        self->animation_step.fields.event = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_spider_fall_rethread(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.relative_step != 0) {
        if (self->animation_step.fields.event != 0) {
            self->ext.main_43.shot = web_spider_spawn_thread(self, 1);
            self->animation_step.fields.event = 0;
            if (self->unk15 == 0) {
                self->ext.main_43.shot->unk84.value = FIXED(8);
            } else {
                self->ext.main_43.shot->unk84.value = FIXED(-8);
            }
        }
    } else {
        shot = self->ext.main_43.shot;
        if (shot->unk5 == 0) {
            self->y_speed = FIXED(3.5);
            self->unk5 = 2;
            self->gravity = 0;
            self->unk6 = 1;
            self->unk7 = 1;
            set_animation(self, 0x1F);
            shot->unk84.value = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_spider_check_big_web(struct MainObj* self)
{
    if (self->ext.main_43.big_web_done == 0 && self->state < 2 && self->unk5 == 2 && (*(u32*)&self->state & 0xFFFF0000) == 0x02010000 && self->hp < 0x18) {
        self->unk5 = 6;
        self->ext.main_43.big_web_done = 1;
        self->collision_data = (const u16*)D_801060F0;
        self->unk6 = 0;
        self->unk7 = 0;
        self->ext.main_43.hurt_collision = 1;
    }
}

struct ShotObj* web_spider_spawn_thread(struct MainObj* self, s32 variant)
{
    struct ShotObj* shot;
    struct ShotObj* result = self->ext.main_43.shot;

    if (result == NULL) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x17;
            shot->unk2 = variant;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->animation_table = ANIMATED_OBJECT(self)->animation_table;
            shot->unk40 = self->unk40;
            shot->unk3C = ANIMATED_OBJECT(self)->unk3C;
            shot->unk42 = self->unk42 & 0x7FFF;
            shot->unk16 = self->unk16;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk15 = self->unk15;
            shot->unk84.value = 0;
            self->ext.main_43.shot = shot;
        }
        result = shot;
    }
    return result;
}

void web_spider_spawn_web_piece(struct VisualObj* self, u8 arg1)
{
    struct VisualObj* temp_v0;

    temp_v0 = find_free_visual_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x11;
        temp_v0->unk2 = arg1;
        temp_v0->x_pos.val = self->x_pos.val;
        temp_v0->y_pos.val = self->y_pos.val;
        temp_v0->animation_table = self->animation_table;
        temp_v0->unk40 = self->unk40;
        temp_v0->unk3C = self->unk3C;
        temp_v0->unk42 = self->unk42 & 0x7FFF;
        temp_v0->unk16 = self->unk16;
        temp_v0->unk50 = (struct PlayerObj*)self;
        temp_v0->unk15 = self->unk15;
    }
}

void web_spider_spawn_web_flash(struct AnimatedObj* arg0)
{
    struct AnimatedObj* self;
    struct VisualObj* temp_v0;

    self = arg0;
    temp_v0 = find_free_visual_obj();
    if (temp_v0 != 0) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x14;
        temp_v0->unk2 = 1;
        temp_v0->x_pos.val = self->x_pos.val;
        temp_v0->y_pos.val = self->y_pos.val + FIXED(28);
        temp_v0->animation_table = self->animation_table;
        temp_v0->unk40 = self->unk40;
        temp_v0->unk3C = self->unk3C;
        temp_v0->unk42 = self->unk42 & 0x7FFF;
        temp_v0->unk16 = self->unk16;
        temp_v0->unk50 = (struct PlayerObj*)self;
        temp_v0->unk15 = self->unk15;
    }
}

void web_spider_spawn_web_shot(struct AnimatedObj* self, u8 arg1)
{
    struct ShotObj* shot;
    s32 x_offset;

    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x16;
        shot->unk2 = arg1;
        x_offset = -0x12;
        if (self->unk15 != 0) {
            x_offset = 0x12;
        }
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->x_pos.i.hi += x_offset;
        shot->y_pos.i.hi += 0x26;
        shot->animation_table = self->animation_table;
        shot->unk40 = self->unk40;
        shot->unk3C = self->unk3C;
        shot->unk42 = self->unk42 & 0x7FFF;
        shot->unk16 = self->unk16;
        shot->unk7C = WEAPON_OBJECT(self);
        shot->unk15 = self->unk15;
    }
}

// web_spider_aim_swing
INCLUDE_ASM("main/nonmatchings/mains/main_43_web_spider", func_80065168);

void web_spider_set_move_timer(struct MainObj* self)
{
    self->unk7C = web_spider_move_timers[(self->hp & 0x7F) >> 3];
}

void web_spider_set_attack_cooldown(struct MainObj* self)
{
    if (self->ext.main_43.attack_cooldown == 0) {
        self->ext.main_43.attack_cooldown = web_spider_attack_cooldowns[(self->hp & 0x7F) >> 3];
    }
}

void web_spider_set_swing_animation(struct MainObj* self)
{
    u8 animation_id;
    animation_id = web_spider_swing_animations[self->ext.main_43.animation_set]
                                              [self->ext.main_43.animation_index];
    self->ext.main_43.animation_id = animation_id;
    set_animation(self, animation_id);
}

void web_spider_death_start(struct MainObj* self)
{
    self->unk5 = 1;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_43.flash_timer = 0x19;
    self->unk42 &= 0x7FFF;
    player_start_script_action(0x14, g_Player.unk15);
    set_animation(self, 0x22);
    is_on_screen(BASE_OBJECT(self));
}

void web_spider_death_explode(struct MainObj* self)
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
            self->ext.main_43.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- == 0) {
        u16 temp;
        self->ext.main_43.flash_timer = temp = self->ext.main_43.flash_timer - 5;
        self->unk42 ^= 0x8000;
        if (temp >= 0x1A) {
            self->ext.main_43.flash_timer = 0;
        }
        self->unk7E = self->ext.main_43.flash_timer < 6 ? 5 : self->ext.main_43.flash_timer;
    }
}

void web_spider_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_43.effect;
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
        if (engine_obj.stage == 1) {
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

void web_spider_death(struct MainObj* self)
{
    web_spider_death_funcs[self->unk5](self);
}

// spiderling_init
INCLUDE_ASM("main/nonmatchings/mains/main_43_web_spider", func_80065574);

void spiderling_run(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    spiderling_step_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    if ((func_8002DD04(self) < 0) || (self->ext.main_43.effect->state == 2)) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
        return;
    }
    func_8002D9BC(self);
    is_on_screen(BASE_OBJECT(self));
}

void spiderling_fall(struct MainObj* self)
{
    if (self->collision_flags & 3) {
        self->x_speed = 0;
        self->x_accel = 0;
    }
    if (self->collision_flags & 8) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        set_animation(self, 0x1C);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void spiderling_crawl(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            if (self->x_pos.val - g_Player.x_pos.val < 0) {
                self->x_speed = FIXED(1.5);
                self->unk15 = 0x40;
            } else {
                self->x_speed = FIXED(-1.5);
                self->unk15 = 0;
            }
            self->unk6 = 1;
            set_animation(self, 0x1D);
        }
        animate_object(ANIMATED_OBJECT(self));
        return;
    }
    if (self->collision_flags & 3) {
        self->unk5 = 4;
        self->unk6 = 0;
        self->unk7 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        self->unk15 = 0;
        if (self->collision_flags & 1) {
            self->unk15 = 0x40;
        }
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void spiderling_leave(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->y_speed = FIXED(1.5);
        self->unk6 = 1;
        set_animation(self, 0x1E);
        return;
    }
    if (self->on_screen == 0) {
        self->state = 2;
    }
    animate_object(self);
    move_with_gravity(ANIMATED_OBJECT(self));
}

void spiderling_despawn(struct MainObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

union AnimationStep D_800FEF94[] = {
    { 0x00010007 },
    { 0x00FF0001 },
};

union AnimationStep D_800FEF9C[] = {
    { 0x01010002 },
    { 0x02010005 },
    { 0x03010011 },
    { 0x04010006 },
    { 0x05010008 },
    { 0x06010006 },
    { 0x07010008 },
    { 0x06010006 },
    { 0x05010007 },
    { 0x08010007 },
    { 0x09010008 },
    { 0x08010008 },
    { 0x0501010A },
    { 0x0601000A },
    { 0x07010008 },
    { 0x0A01002B },
    { 0x0B010002 },
    { 0x0C010020 },
    { 0x0C000001 },
};

union AnimationStep D_800FEFE8[] = {
    { 0x05010102 },
    { 0x0D010002 },
    { 0x0F010003 },
    { 0x0D010002 },
    { 0x05010102 },
    { 0x0E010003 },
    { 0x0EFA0001 },
};

union AnimationStep D_800FF004[] = {
    { 0x05010105 },
    { 0x0D010005 },
    { 0x0F010007 },
    { 0x0D010105 },
    { 0x05010005 },
    { 0x0E010007 },
    { 0x0EFA0001 },
};

union AnimationStep D_800FF020[] = {
    { 0x05010005 },
    { 0x10010008 },
    { 0x01010004 },
    { 0x02010004 },
    { 0x11010205 },
    { 0x12010005 },
    { 0x1301000F },
    { 0x14010102 },
    { 0x15010028 },
    { 0x15000001 },
};

union AnimationStep D_800FF048[] = {
    { 0x05010003 },
    { 0x10010004 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x11010203 },
    { 0x12010003 },
    { 0x13010008 },
    { 0x14010102 },
    { 0x15010018 },
    { 0x12010003 },
    { 0x13010008 },
    { 0x14010102 },
    { 0x15010018 },
    { 0x15000001 },
};

union AnimationStep D_800FF080[] = {
    { 0x05010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x11010105 },
    { 0x02010003 },
    { 0x01010003 },
    { 0x0001003C },
    { 0x00000001 },
};

union AnimationStep D_800FF0B8[] = {
    { 0x0501000D },
    { 0x16010103 },
    { 0x17010005 },
    { 0x18010008 },
    { 0x17010004 },
    { 0x16010013 },
    { 0x16000001 },
};

union AnimationStep D_800FF0D4[] = {
    { 0x16010005 },
    { 0x19010105 },
    { 0x1A010005 },
    { 0x1B010005 },
    { 0x1C010105 },
    { 0x1D010005 },
    { 0x1E010005 },
    { 0x1F010105 },
    { 0x1F000001 },
};

union AnimationStep D_800FF0F8[] = {
    { 0x20010005 },
    { 0x21010105 },
    { 0x22010005 },
    { 0x23010005 },
    { 0x24010105 },
    { 0x25010005 },
    { 0x26010005 },
    { 0x27010105 },
    { 0x27000001 },
};

union AnimationStep D_800FF11C[] = {
    { 0x16010005 },
    { 0x1F010105 },
    { 0x1E010005 },
    { 0x1D010005 },
    { 0x1C010105 },
    { 0x1B010005 },
    { 0x1A010005 },
    { 0x19010105 },
    { 0x19000001 },
};

union AnimationStep D_800FF140[] = {
    { 0x20010005 },
    { 0x27010105 },
    { 0x26010005 },
    { 0x25010005 },
    { 0x24010105 },
    { 0x23010005 },
    { 0x22010005 },
    { 0x21010105 },
    { 0x21000001 },
};

union AnimationStep D_800FF164[] = {
    { 0x16010003 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2A010003 },
    { 0x2B010203 },
    { 0x2C010003 },
    { 0x2D01000A },
    { 0x2E010102 },
    { 0x2F010040 },
    { 0x2F000001 },
};

union AnimationStep D_800FF18C[] = {
    { 0x16010003 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2A010003 },
    { 0x2B010203 },
    { 0x2C010003 },
    { 0x2D01000A },
    { 0x2E010102 },
    { 0x2F010040 },
    { 0x2C010003 },
    { 0x2D01000A },
    { 0x2E010102 },
    { 0x2F010016 },
    { 0x2F000001 },
};

union AnimationStep D_800FF1C4[] = {
    { 0x1601000A },
    { 0x30010001 },
    { 0x31010001 },
    { 0x30010001 },
    { 0x32010001 },
    { 0x30010001 },
    { 0x31010001 },
    { 0x30010001 },
    { 0x32010001 },
    { 0x30010001 },
    { 0x31010001 },
    { 0x30010001 },
    { 0x32010001 },
    { 0x2D010002 },
    { 0x2C010002 },
    { 0x2B010002 },
    { 0x2A010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x37010002 },
    { 0x36010002 },
    { 0x37010020 },
    { 0x37010101 },
    { 0x36010002 },
    { 0x37010028 },
    { 0x37000001 },
};

union AnimationStep D_800FF230[] = {
    { 0x35010002 },
    { 0x34010002 },
    { 0x38010002 },
    { 0x16010020 },
    { 0x16000001 },
};

union AnimationStep D_800FF244[] = {
    { 0x05010003 },
    { 0x39010003 },
    { 0x3A010003 },
    { 0x3B010003 },
    { 0x3B000001 },
};

union AnimationStep D_800FF258[] = {
    { 0x3C010003 },
    { 0x3DFF0003 },
};

union AnimationStep D_800FF260[] = {
    { 0x3E010102 },
    { 0x3F010002 },
    { 0x40010003 },
    { 0x41010003 },
    { 0x3B010005 },
    { 0x3C010004 },
    { 0x3E010103 },
    { 0x3A010004 },
    { 0x3B010004 },
    { 0x42010014 },
    { 0x43010006 },
    { 0x44010003 },
    { 0x45010003 },
    { 0x4601000A },
    { 0x45010003 },
    { 0x44010003 },
    { 0x43010003 },
    { 0x47010003 },
    { 0x48010003 },
    { 0x49010003 },
    { 0x4A010003 },
    { 0x4B010006 },
    { 0x4A01001E },
    { 0x4A000001 },
};

union AnimationStep D_800FF2C0[] = {
    { 0x4B010004 },
    { 0x4C010004 },
    { 0x4D010004 },
    { 0x4F010003 },
    { 0x4E010103 },
    { 0x4F010003 },
    { 0x50010003 },
    { 0x4F010003 },
    { 0x4E01001F },
    { 0x4E000001 },
};

union AnimationStep D_800FF2E8[] = {
    { 0x51010001 },
    { 0x52010001 },
    { 0x53010001 },
    { 0x54FD0001 },
};

union AnimationStep D_800FF2F8[] = {
    { 0x55010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x5E010001 },
    { 0x5F010001 },
    { 0x60010001 },
    { 0x61010001 },
    { 0x62010001 },
    { 0x63010001 },
    { 0x63000001 },
};

union AnimationStep D_800FF338[] = {
    { 0x64010001 },
    { 0x65010001 },
    { 0x66FE0001 },
};

union AnimationStep D_800FF344[] = {
    { 0x66010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x66010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x66010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x68000001 },
};

union AnimationStep D_800FF384[] = {
    { 0x69010002 },
    { 0x6A010002 },
    { 0x69010002 },
    { 0x6A010002 },
    { 0x69010001 },
    { 0x6A010001 },
    { 0x69010001 },
    { 0x6AF90001 },
};

union AnimationStep D_800FF3A4[] = {
    { 0x6B010001 },
    { 0x6C010001 },
    { 0x6D010001 },
    { 0x6EFD0001 },
};

union AnimationStep D_800FF3B4[] = {
    { 0x6F010001 },
    { 0x70010001 },
    { 0x71010001 },
    { 0x70010001 },
    { 0x72010001 },
    { 0x70010001 },
    { 0x70FA0001 },
};

union AnimationStep D_800FF3D0[] = {
    { 0x73010001 },
    { 0x76010001 },
    { 0x74010001 },
    { 0x76010001 },
    { 0x75010001 },
    { 0x76010001 },
    { 0x76FA0001 },
};

union AnimationStep D_800FF3EC[] = {
    { 0x77010005 },
    { 0x78010005 },
    { 0x79010005 },
    { 0x7A010005 },
    { 0x7B010106 },
    { 0x7C010005 },
    { 0x7D010004 },
    { 0x7E010004 },
    { 0x7F010004 },
    { 0x80010004 },
    { 0x81010006 },
    { 0x82010106 },
    { 0x83010006 },
    { 0x84F30006 },
};

union AnimationStep D_800FF424[] = {
    { 0x77010108 },
    { 0x78010004 },
    { 0x79010004 },
    { 0x7A010004 },
    { 0x7B010108 },
    { 0x7A010004 },
    { 0x79010004 },
    { 0x78F90004 },
};

union AnimationStep D_800FF444[] = {
    { 0x85010008 },
    { 0x86010004 },
    { 0x87010004 },
    { 0x88010004 },
    { 0x89010008 },
    { 0x8A010004 },
    { 0x8B010004 },
    { 0x8C010004 },
    { 0x8CF80001 },
};

union AnimationStep D_800FF468[] = {
    { 0x8D010004 },
    { 0x8E010002 },
    { 0x8F010008 },
    { 0x8E010004 },
    { 0x8D010004 },
    { 0x8D000001 },
};

union AnimationStep D_800FF480[] = {
    { 0x8D010004 },
    { 0x90010002 },
    { 0x91010008 },
    { 0x92010004 },
    { 0x93010004 },
    { 0x90010004 },
    { 0x8DFA0004 },
};

union AnimationStep D_800FF49C[] = {
    { 0x94010004 },
    { 0x95010002 },
    { 0x96010008 },
    { 0x97010004 },
    { 0x98010004 },
    { 0x95010004 },
    { 0x94FA0004 },
};

union AnimationStep D_800FF4B8[] = {
    { 0x01010002 },
    { 0x02010005 },
    { 0x03010011 },
    { 0x04010006 },
    { 0x05010008 },
    { 0x06010006 },
    { 0x07010008 },
    { 0x06010006 },
    { 0x06000001 },
};

union AnimationStep D_800FF4DC[] = {
    { 0x05010007 },
    { 0x08010007 },
    { 0x09010008 },
    { 0x08010008 },
    { 0x0501000A },
    { 0x0601000A },
    { 0x07010008 },
    { 0x06010008 },
    { 0x06000001 },
};

union AnimationStep D_800FF500[] = {
    { 0x3C000001 },
};

union AnimationStep* web_spider_animations[40] = {
    D_800FEF94,
    D_800FEF9C,
    D_800FF004,
    D_800FF020,
    D_800FF080,
    D_800FF0B8,
    D_800FF0D4,
    D_800FF0F8,
    D_800FF11C,
    D_800FF140,
    D_800FF164,
    D_800FF1C4,
    D_800FF230,
    D_800FF244,
    D_800FF258,
    D_800FF260,
    D_800FF2C0,
    D_800FF2E8,
    D_800FF2F8,
    D_800FF338,
    D_800FF344,
    D_800FF384,
    D_800FF3A4,
    D_800FF3B4,
    D_800FF3D0,
    D_800FF3EC,
    D_800FF424,
    D_800FF444,
    D_800FF468,
    D_800FF480,
    D_800FF49C,
    D_800FEFE8,
    D_800FF4B8,
    D_800FF4DC,
    D_800FF500,
    D_800FF500,
    D_800FF500,
    D_800FF500,
    D_800FF048,
    D_800FF18C,
};

u8 web_spider_debris[4] = { 13, 14, 15, 16 };

struct Unk_unk68 web_spider_attack_box = { -21, -21, 40, 34 };

struct Unk_unk68 web_spider_hurt_box = { -23, -30, 44, 57 };

struct Unk_unk68 D_800FF5B0 = { 0, 0, 24, 19 };

struct Unk_unk68 D_800FF5B4 = { -5, -8, 11, 15 };

struct Unk_unk68 D_800FF5B8 = { -10, -8, 18, 15 };

struct Unk_unk68 D_800FF5BC = { 0, 0, 8, 8 };

RECT D_800FF5C0[4] = {
    { 112, 56, 160, 0 },
    { 208, 56, 160, 104 },
    { 112, 152, 160, 192 },
    { 208, 152, 160, 104 },
};

RECT D_800FF5E0[4] = {
    { 112, 56, 64, 104 },
    { 112, 152, 160, 104 },
    { 208, 56, 256, 104 },
    { 208, 152, 160, 104 },
};

RECT D_800FF600[4] = {
    { 112, 152, 64, 104 },
    { 112, 152, 160, 104 },
    { 208, 135, 256, 104 },
    { 208, 152, 160, 104 },
};

RECT D_800FF620[4] = {
    { 208, 56, 160, 16 },
    { 112, 56, 160, 104 },
    { 208, 152, 160, 192 },
    { 112, 152, 160, 104 },
};

RECT D_800FF640[4] = {
    { 208, 56, 256, 104 },
    { 208, 152, 160, 104 },
    { 112, 56, 64, 104 },
    { 112, 152, 160, 104 },
};

RECT D_800FF660[4] = {
    { 208, 152, 256, 104 },
    { 208, 152, 160, 104 },
    { 112, 152, 64, 104 },
    { 112, 152, 160, 104 },
};

u8 D_800FF680[8] = { 8, 9, 6, 7, 7, 6, 9, 8 };

u8 D_800FF688[8] = { 8, 7, 6, 9, 9, 6, 7, 8 };

u8 D_800FF690[8] = { 7, 8, 6, 9, 6, 9, 7, 8 };

u8 D_800FF698[8] = { 6, 9, 8, 7, 9, 6, 7, 8 };

u8 D_800FF6A0[8] = { 9, 6, 7, 9, 8, 7, 6, 8 };

u8 D_800FF6A8[8] = { 6, 9, 7, 9, 7, 8, 6, 8 };

RECT* web_spider_swing_paths[6] = {
    D_800FF5C0,
    D_800FF5E0,
    D_800FF600,
    D_800FF620,
    D_800FF640,
    D_800FF660,
};

const u8* web_spider_swing_animations[6] = {
    D_800FF680,
    D_800FF688,
    D_800FF690,
    D_800FF698,
    D_800FF6A0,
    D_800FF6A8,
};

u16 web_spider_arena_x = 0x0000;

u16 web_spider_arena_y = 0x0000;

void (*web_spider_state_funcs[3])(struct MainObj*) = {
    web_spider_intro,
    func_8006398C,
    web_spider_death,
};

void (*spiderling_state_funcs[3])() = {
    func_80065574,
    spiderling_run,
    spiderling_despawn,
};

void (*web_spider_intro_funcs[10])(struct MainObj*) = {
    web_spider_intro_warning,
    web_spider_intro_setup,
    func_8006346C,
    web_spider_intro_spawn_thread,
    web_spider_intro_wait,
    web_spider_intro_descend,
    web_spider_intro_pose,
    web_spider_intro_start_health_bar,
    web_spider_intro_fill_health,
    web_spider_intro_climb,
};

u8 D_800FF724[16] = { 0x07, 0x05, 0x06, 0x04, 0x02, 0x03, 0x01, 0x00, 0x01, 0x00, 0x03, 0x02, 0x05, 0x04, 0x07, 0x06 };

void (*web_spider_step_funcs[7])() = {
    enemy_hit_reaction,
    web_spider_fall,
    web_spider_drop,
    web_spider_shoot,
    web_spider_swing,
    web_spider_attack,
    web_spider_big_web,
};

void (*web_spider_drop_funcs[3])() = {
    func_80063B20,
    web_spider_drop_climb,
    web_spider_drop_climb,
};

void (*web_spider_shoot_funcs[3])() = {
    web_spider_shoot_start,
    web_spider_shoot_fire,
    web_spider_shoot_fire,
};

void (*web_spider_swing_funcs[3])(struct MainObj*) = {
    web_spider_swing_start,
    func_80064154,
    web_spider_swing_wait,
};

u8 web_spider_swing_sets[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03 };

void (*web_spider_big_web_funcs[3])() = {
    func_800646EC,
    web_spider_big_web_spin,
    web_spider_big_web_center,
};

void (*web_spider_fall_funcs[5])(struct MainObj*) = {
    web_spider_fall_start,
    web_spider_fall_slow,
    web_spider_fall_land,
    web_spider_fall_crash,
    web_spider_fall_rethread,
};

u8 web_spider_move_timers[4] = { 0x10, 0x14, 0x18, 0x20 };

u8 web_spider_attack_cooldowns[4] = { 0x5A, 0x50, 0x44, 0x32 };

void (*web_spider_death_funcs[3])(struct MainObj*) = {
    web_spider_death_start,
    web_spider_death_explode,
    web_spider_death_finish,
};

struct FixedPointPosition spiderling_velocities[8] = {
    { (s32)0x00010000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0x00028000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0xFFFD8000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0xFFFF0000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
};

void (*spiderling_step_funcs[5])(struct MainObj*) = {
    enemy_hit_reaction,
    enemy_hit_reaction,
    spiderling_fall,
    spiderling_crawl,
    spiderling_leave,
};
