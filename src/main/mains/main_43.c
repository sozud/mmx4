// MainObj, main_object_update_funcs[43]
// 800631C8..80065930
#include "common.h"

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

    if (g_Player.unkC4 == 0) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_43.effect = effect;
        }
        func_80036AE4(0x14, 0x40);
        web_spider_arena_x = background_objects[0].unk26;
        web_spider_arena_y = background_objects[0].unk2A;
        self->unk5 = 1;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void func_80063334(struct MainObj* arg0)
{
    s32* archive;
    s32 offset;

    if (arg0->ext.main_43.effect->active == 0) {
        arg0->unk5 = 2;
        arg0->unk54 = &D_800FF5AC;
        arg0->unk50 = &D_800FF5A8;
        arg0->unk68 = NULL;
        arg0->collision_data = D_801075F4;
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
        arg0->animation_table = (const u8* const*)web_spider_animations;
        arg0->unk16 = 4;
        arg0->unk60 = 6;
        arg0->unk61 = -0x80;
        arg0->unk63 = 2;
        arg0->unk7C = 7;
        arg0->unk5C = 0;
        arg0->unk62 = 0;
        arg0->ext.main_43.flash_timer = 0;
        arg0->ext.main_43.shot = NULL;
        arg0->ext.main_43.hurt_collision = 0;
        arg0->ext.main_43.big_web_done = 0;
        engine_obj.enable_boss = 0;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = arg0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006346C);

void web_spider_intro_spawn_thread(struct MainObj* self)
{
    func_800CA9EC(self, 8);
    self->unk7C = 0x40;
    self->unk5 = 4;
    self->ext.main_43.shot = web_spider_spawn_thread(self, 0);
}

void web_spider_intro_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 5;
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk24 = FIXED(-8);
        self->unk2C = 0;
        func_80015D60(self, 0);
    }
}

void web_spider_intro_descend(struct MainObj* self)
{
    s16 timer;

    if (self->unk6 == 0) {
        if (self->y_pos.i.hi - background_objects[self->bg_offset].y_pos.i.hi >= 0x88) {
            self->unk6 = 1;
            self->unk7C = 0x1E;
            self->unk24 = FIXED(1);
            func_80015D60(self, 1);
        } else {
            func_8002B694(ANIMATED_OBJECT(self));
        }
    } else {
        func_8002B694(ANIMATED_OBJECT(self));
        timer = (u16)self->unk7C - 1;
        self->unk7C = timer;
        if (timer == 0) {
            self->unk5 = 6;
            self->unk24 = 0;
            self->unk2C = 0;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7C = 2;
        } else if (timer == 0xF) {
            self->unk24 = FIXED(-1);
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
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
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void web_spider_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk5 = 8;
        engine_obj.enable_boss = 1;
        func_800921E8(0);
    }
}

void web_spider_intro_fill_health(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    if ((func_8009227C() == 0) && (self->animation_step.fields.relative_step == 0)) {
        if (self->unk5C < 0x30) {
            timer = (u16)self->unk7C - 1;
            self->unk7C = timer;
            if (timer == 0) {
                func_8001540C(0, 0xE, 0);
                self->unk7C = 2;
            }
            self->unk5C = (u8)self->unk5C + 1;
            return;
        }
        self->unk5 = 9;
        self->unk24 = FIXED(3.5);
        func_80036B18();
        func_80015D60(self, 0x1F);
    }
}

void web_spider_intro_climb(struct MainObj* self)
{
    if (self->on_screen == 0) {
        self->state = 1;
        self->unk5 = 2;
        self->unk61 = 0;
        return;
    }
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        func_8001540C(2, 0x70, self);
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006398C);

void web_spider_drop(struct MainObj* self)
{
    web_spider_drop_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063B20);

void func_80063DD8(struct MainObj* arg0)
{
    switch (arg0->unk7) {
    case 0:
        if (arg0->unk7C == 0) {
            if ((get_random() & 0xF) != 0 && g_Player.unkBA == 0) {
                arg0->unk5 = 3;
                arg0->unk6 = 0;
                arg0->unk7 = 0;
                if (arg0->x_pos.i.hi - g_Player.x_pos.i.hi >= 0) {
                    arg0->unk15 = 0;
                } else {
                    arg0->unk15 = 0x40;
                }
            } else {
                arg0->unk24 = FIXED(3.5);
                arg0->unk2C = 0;
                arg0->unk7 = 1;
                func_80015D60(arg0, 0x1F);
                func_8001540C(2, 0x70, arg0);
            }
        } else {
            arg0->unk7C--;
        }
        break;
    case 1:
        if (arg0->on_screen == 0) {
            arg0->unk7 = 2;
            arg0->unk7C = 8;
            if (arg0->ext.main_43.hurt_collision != 0) {
                arg0->collision_data = D_801075F4;
                arg0->ext.main_43.hurt_collision = 0;
            }
        }
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            func_8001540C(2, 0x70, arg0);
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B694(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        if (--arg0->unk7C == 0) {
            arg0->unk6 = 0;
            arg0->unk7 = 0;
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
    func_80015D60(self, 3);
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
        func_80015D60(self, 0x1F);
        func_8001540C(2, 0x70, self);
    }
    func_80015DC8(self);
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

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064154);

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

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800643B0);

void web_spider_attack_web(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        func_80015D60(self, 0xA);
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
        func_80015D60(self, self->ext.main_43.animation_id);
        web_spider_set_attack_cooldown(self);
        self->ext.main_43.attack_count++;
        if (self->ext.main_43.attack_count >= 3) {
            self->ext.main_43.attack_count = 0;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void web_spider_big_web(struct MainObj* self)
{
    web_spider_big_web_funcs[self->unk6](self);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800646EC);

void web_spider_big_web_spin(struct MainObj* arg0)
{
    struct VisualObj* self = VISUAL_OBJECT(arg0);
    s8 state = self->unk7;
    u32 i;

    switch (state) {
    case 0:
        self->unk7 = 1;
        func_80015D60(self, 4);
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
        func_80015DC8(ANIMATED_OBJECT(self));
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
        self->unk24 = FIXED(1);
        self->unk2C = FIXED(0.5);
        func_80015D60(self, 5);
        break;
    case 1:
        if (self->animation_step.fields.relative_step != 0) {
            if (self->animation_step.fields.event != 0) {
                self->animation_step.fields.event = 0;
                self->unk24 = 0;
                self->unk2C = 0;
            }
            func_80015DC8(ANIMATED_OBJECT(self));
            func_8002B694(ANIMATED_OBJECT(self));
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
    self->unk24 = FIXED(4);
    self->unk20 = 0;
    self->unk28 = 0;
    self->unk2C = FIXED(0.25);
    func_80015D60(self, 0xD);
    self->unk68 = &D_800FF5B0;
    self->collision_data = (const u16*)D_801060F0;
    self->ext.main_43.hurt_collision = 1;
}

void web_spider_fall_slow(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 2;
        self->unk24 = 0;
        self->unk2C = FIXED(0.5);
        func_80015D60(self, 0xE);
    } else {
        func_80015DC8(ANIMATED_OBJECT(self));
    }
    func_8002B694(ANIMATED_OBJECT(self));
}

void web_spider_fall_land(struct MainObj* self)
{
    if (self->unk70 & 8) {
        self->unk6 = 3;
        self->unk24 = 0;
        self->unk2C = 0;
        func_80015D60(self, 0xF);
        self->unk68 = NULL;
        func_8001540C(2, 0x74, self);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
}

void web_spider_fall_crash(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 4;
        func_80015D60(self, 0x10);
    } else if (self->animation_step.fields.event != 0) {
        self->unk5C -= 4;
        self->animation_step.fields.event = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
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
            self->unk24 = FIXED(3.5);
            self->unk5 = 2;
            self->unk2C = 0;
            self->unk6 = 1;
            self->unk7 = 1;
            func_80015D60(self, 0x1F);
            shot->unk84.value = 0;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void web_spider_check_big_web(struct MainObj* self)
{
    if (self->ext.main_43.big_web_done == 0 && self->state < 2 && self->unk5 == 2 && (*(u32*)&self->state & 0xFFFF0000) == 0x02010000 && self->unk5C < 0x18) {
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

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065168);

void web_spider_set_move_timer(struct MainObj* self)
{
    self->unk7C = web_spider_move_timers[(self->unk5C & 0x7F) >> 3];
}

void web_spider_set_attack_cooldown(struct MainObj* self)
{
    if (self->ext.main_43.attack_cooldown == 0) {
        self->ext.main_43.attack_cooldown = web_spider_attack_cooldowns[(self->unk5C & 0x7F) >> 3];
    }
}

void web_spider_set_swing_animation(struct MainObj* self)
{
    u8 animation_id;
    animation_id = web_spider_swing_animations[self->ext.main_43.animation_set]
                                              [self->ext.main_43.animation_index];
    self->ext.main_43.animation_id = animation_id;
    func_80015D60(self, animation_id);
}

void web_spider_death_start(struct MainObj* self)
{
    self->unk5 = 1;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_43.flash_timer = 0x19;
    self->unk42 &= 0x7FFF;
    func_80036AE4(0x14, g_Player.unk15);
    func_80015D60(self, 0x22);
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

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065574);

void spiderling_run(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    spiderling_step_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    if ((func_8002DD04(self) < 0) || (self->ext.main_43.effect->state == 2)) {
        func_800AF808(BASE_OBJECT(self));
        self->state = 2;
        return;
    }
    func_8002D9BC(self);
    is_on_screen(BASE_OBJECT(self));
}

void spiderling_fall(struct MainObj* self)
{
    if (self->unk70 & 3) {
        self->unk20 = 0;
        self->unk28 = 0;
    }
    if (self->unk70 & 8) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk20 = 0;
        self->unk24 = 0;
        self->unk28 = 0;
        self->unk2C = 0;
        func_80015D60(self, 0x1C);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
}

void spiderling_crawl(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            if (self->x_pos.val - g_Player.x_pos.val < 0) {
                self->unk20 = FIXED(1.5);
                self->unk15 = 0x40;
            } else {
                self->unk20 = FIXED(-1.5);
                self->unk15 = 0;
            }
            self->unk6 = 1;
            func_80015D60(self, 0x1D);
        }
        func_80015DC8(ANIMATED_OBJECT(self));
        return;
    }
    if (self->unk70 & 3) {
        self->unk5 = 4;
        self->unk6 = 0;
        self->unk7 = 0;
        self->unk20 = 0;
        self->unk24 = 0;
        self->unk28 = 0;
        self->unk2C = 0;
        self->unk15 = 0;
        if (self->unk70 & 1) {
            self->unk15 = 0x40;
        }
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B694(ANIMATED_OBJECT(self));
}

void spiderling_leave(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk24 = FIXED(1.5);
        self->unk6 = 1;
        func_80015D60(self, 0x1E);
        return;
    }
    if (self->on_screen == 0) {
        self->state = 2;
    }
    func_80015DC8(self);
    func_8002B694(ANIMATED_OBJECT(self));
}

void spiderling_despawn(struct MainObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}
