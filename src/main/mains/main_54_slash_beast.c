// MainObj, main_object_update_funcs[54]
// 8006BB00..8006EB40
#include "common.h"
#include "func_tables.h"

void slash_beast_update(struct MainObj* self)
{
    slash_beast_state_funcs[self->state](self);
    CollisionRelated(self);
    if (!(g_Player.hp & 0x7F)) {
        func_8006E920(self, 0x38);
    }
}

// slash_beast_init
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006BB70);

// slash_beast_run
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006BD1C);

void slash_beast_death(struct MainObj* self)
{
    slash_beast_death_funcs[self->unk5](self);
}

void slash_beast_death_start(struct MainObj* self)
{
    g_Player.stun_timer = 0;
    player_start_script_action(0x14, g_Player.unk15);
    self->unk5 = 1;
    self->unk42 &= 0x7FFF;
    set_animation(self, 0x13);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->invincibility_timer = 0x19;
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_death_blink(struct MainObj* self)
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
            self->ext.main_54.effect = effect;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        delay = self->invincibility_timer - 5;
        self->invincibility_timer = delay;
        if (delay >= 0x1A) {
            self->invincibility_timer = 0;
        }
        next_delay = self->invincibility_timer;
        if (self->invincibility_timer < 5) {
            next_delay = 5;
        }
        self->unk7E = next_delay;
    }
}

void slash_beast_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_54.effect;
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
        engine_obj.boss_ptr = 0;
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

void slash_beast_start_pattern(struct MainObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void slash_beast_crescent(struct MainObj* self)
{
    slash_beast_crescent_funcs[self->unk6](self);
}

void slash_beast_crescent_jump(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->attack_box = &D_80100220;
        self->hurt_box = &D_80100224;
    }
    if (self->animation_step.fields.event == 1) {
        if (self->unk15 != 0) {
            self->x_speed = FIXED(3);
        } else {
            self->x_speed = FIXED(-3);
        }
        self->x_accel = FIXED(-0.125);
        self->y_speed = FIXED(3);
        self->gravity = FIXED(0.125);
        set_animation(self, 9);
        func_8001540C(2, 0x81, self);
        self->unk6 = 1;
    }
}

// slash_beast_crescent_slash
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006C378);

void slash_beast_crescent_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        func_8001540C(2, 0x82, self);
        set_animation(self, 0xA);
        self->hurt_box = (const u8*)D_801001FC;
        self->attack_box = (const u8*)D_801001F8;
        self->y_speed = 0;
        self->gravity = 0;
        self->unk6 = 3;
    }
}

void slash_beast_crescent_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 0);
        slash_beast_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void slash_beast_decide(struct MainObj* self)
{
    slash_beast_decide_funcs[self->unk6](self);
}

// slash_beast_pick_attack
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006C6AC);

void slash_beast_crouch(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->hurt_box = (const u8*)&D_80100204;
        self->attack_box = (const u8*)&D_80100200;
        func_8001540C(2, 0x87, self);
    }
    if (--self->unk7C == 0) {
        self->hurt_box = (const u8*)D_801001FC;
        self->attack_box = (const u8*)D_801001F8;
        self->unk6 = 0;
    }
}

void slash_beast_jump(struct MainObj* self)
{
    slash_beast_jump_funcs[self->unk6](self);
}

// slash_beast_jump_start
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006CB50);

// slash_beast_jump_air
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006CC3C);

void slash_beast_jump_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 0);
        slash_beast_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

// slash_beast_guard
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006CDD4);

void slash_beast_dash(struct MainObj* self)
{
    slash_beast_dash_funcs[self->unk6](self);
}

void slash_beast_dash_windup(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 0xD);
        self->unk6 = 1;
    }
}

void slash_beast_dash_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->contact_damage = 9;
        set_animation(self, 0xE);
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-1);
        } else {
            self->x_speed = FIXED(1);
        }
        self->ext.main_54.claw_hitbox = 1;
        self->ext.main_54.afterimage_timer = 1;
        func_8001540C(2, 0x83, self);
        self->x_accel = FIXED(0.5);
        self->unk6 = 2;
    }
}

// slash_beast_dash_run
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006CFB8);

// slash_beast_dash_crash
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006D280);

void slash_beast_dash_turn(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->contact_damage = 9;
        self->ext.main_54.claw_hitbox = 1;
        self->x_speed = -self->x_speed;
        set_animation(self, 0xE);
        func_8001540C(2, 0x83, self);
        self->unk6 = 2;
    }
}

// slash_beast_pounce
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006D3DC);

void slash_beast_grab(struct MainObj* self)
{
    slash_beast_grab_funcs[self->unk6](self);
}

void slash_beast_grab_check(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 6);
        self->unk16 = 6;
        self->contact_damage = 6;
        self->hurt_box = D_801001FC;
        self->attack_box = D_801001F8;
        self->unk5 = 4;
        self->unk62 = 0;
        self->ext.main_54.grab = 0;
        self->unk6 = 2;
    }
    if (g_Player.stun_timer == 0) {
        return;
    }
    func_8001540C(2, 0x86, self);
    if (self->x_pos.i.hi - background_objects[0].x_pos.i.hi >= 0xA1) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
    g_Player.unk15 = self->unk15;
    g_Player.y_pos.i.hi = self->y_pos.i.hi - 8;
    if (self->unk15 == 0) {
        g_Player.x_pos.i.hi = self->x_pos.i.hi - 0x23;
        self->x_speed = FIXED(-6);
    } else {
        g_Player.x_pos.i.hi = self->x_pos.i.hi + 0x23;
        self->x_speed = FIXED(6);
    }
    set_animation(self, 5);
    self->unk16 = 1;
    self->unk7C = 0x30;
    self->unk6 = 1;
}

void slash_beast_grab_windup(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 7);
        self->unk6 = 2;
        self->ext.main_54.afterimage_timer = 1;
    }
}

// slash_beast_grab_drag
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006D888);

void slash_beast_grab_throw(struct MainObj* self)
{
    g_Player.x_pos.i.hi = self->x_pos.u.hi;
    start_screen_shake_x(0x1E, 8, 2);
    set_animation(self, 2);
    self->unk16 = 6;
    self->hurt_box = &D_8010020C;
    self->attack_box = &D_80100208;
    self->x_accel = 0;
    if (self->unk15 != 0) {
        self->x_speed = FIXED(-3.244140625);
    } else {
        self->x_speed = FIXED(3.244140625);
    }
    self->gravity = FIXED(0.21875);
    self->y_speed = FIXED(6.5625);
    move_with_gravity(ANIMATED_OBJECT(self));
    func_8001540C(2, 0x81, self);
    self->unk5 = 4;
    self->unk6 = 1;
    self->unk62 = 0;
    self->contact_damage = 9;
    self->ext.main_54.grab = 0;
    g_Player.stun_timer = 0;
}

void slash_beast_intro(struct MainObj* self)
{
    slash_beast_intro_funcs[self->unk6](self);
}

void slash_beast_intro_wait_player(struct MainObj* self)
{
    struct EffectObj* temp_v0;

    if (g_Player.x_pos.i.hi >= 0x2500 || engine_obj.stage == 0xC) {
        temp_v0 = find_free_effect_obj();
        if (temp_v0 != 0) {
            temp_v0->active = 1;
            temp_v0->id = 0x18;
            self->ext.main_54.effect = temp_v0;
        }

        player_start_script_action(0x14, 0x40);
        if (engine_obj.stage == 8) {
            background_objects[0].unk26 = 0x24A0;
            background_objects[0].unk24 = 0x24E0;
            background_objects[0].unk2A = 0xF8;
            background_objects[0].unk28 = 0xF8;
        }

        self->unk7C = 3;
        self->unk7E = 1;
        self->unk6 = 1;
    }
}

void slash_beast_intro_wait_warning(struct MainObj* self)
{
    if (self->ext.main_54.effect->active == 0 && (background_objects[0].x_pos.i.hi == 0x24A0 || engine_obj.stage == 0xC)) {
        self->unk6 = 2;
    }
}

// slash_beast_intro_appear
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006DD44);

void slash_beast_intro_leap(struct MainObj* self)
{
    s16 timer;

    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        background_objects[0].unk26 = 0x24C0;
        background_objects[0].unk24 = 0x24D0;
        background_objects[0].unk2A = 0xD0;
        background_objects[0].unk28 = 0xD0;
        set_animation(self, 0x16);
        self->gravity = FIXED(0.125);
        self->y_speed = FIXED(7.5);
        self->x_speed = FIXED(1.875);
        self->unk7E = 0;
        func_8001540C(2, 0x81, self);
        self->unk6 = 4;
    }
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_intro_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->x_pos.i.hi - background_objects[0].x_pos.i.hi >= 0xE0) {
        self->x_speed = 0;
        self->gravity = FIXED(1);
    }
    if (self->y_speed == 0) {
        self->terrain_box = &D_8010024C;
        set_animation(self, 0x17);
    }
    if (self->y_speed < 0) {
        switch (self->unk7E) {
        case 0:
            if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi + self->terrain_box->unk0,
                    self->terrain_box->unk3 + (self->y_pos.i.hi + self->terrain_box->unk1) + 0x40)
                == 0x38) {
                if (engine_obj.stage == 8) {
                    apply_tile_effect(8, 0x2580, 0x140);
                    func_8001540C(2, 0x80, self);
                    spawn_debris(4, D_801005B0, self);
                }
                self->unk7E = 1;
            }
            break;
        case 1:
            if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi + self->terrain_box->unk0,
                    self->terrain_box->unk3 + (self->y_pos.i.hi + self->terrain_box->unk1) + 0x10)
                == 0x38) {
                self->unk7E = 2;
                set_animation(self, 3);
                if (engine_obj.stage == 0xC) {
                    func_8001540C(2, 0x82, self);
                }
            }
            break;
        }
    }
    if (self->collision_flags & 8) {
        start_screen_shake_y(0x10, 4, 2);
        self->ext.main_54.active = 1;
        self->unk6 = 5;
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void slash_beast_intro_pose(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        if (engine_obj.stage == 8) {
            self->unk15 = 0;
            set_animation(self, 0x18);
            func_8002217C(0x10, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        self->unk6 = 6;
    }
}

void slash_beast_intro_wait_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        set_animation(self, 0x19);
        self->unk7E = 3;
        self->unk6 = 7;
        play_boss_voice(7);
    }
}

void slash_beast_intro_fill_health(struct MainObj* self)
{
    if (update_boss_music_delay() == 0) {
        if (engine_obj.stage == 8) {
            s16* background_object = &background_objects[0].unk26;

            if (*background_object != 0x24B0) {
                *background_object -= 1;
            }
        }

        if (--self->unk7E == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7E = 3;
        }

        if (++self->hp == 0x30) {
            self->ext.main_54.pattern_set = 0;
            self->ext.main_54.fight_started = 1;
            slash_beast_pick_pattern(self);
            self->unk5 = 3;
            self->unk6 = 0;
            self->ext.main_54.pattern--;
            player_end_script_action();
        }
    }
}

void slash_beast_stagger(struct MainObj* self)
{
    slash_beast_stagger_funcs[self->unk6](self);
}

// slash_beast_stagger_start
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006E450);

void slash_beast_stagger_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        func_8001540C(2, 0x88, self);
        self->x_speed = 0;
        self->y_speed = 0;
        self->gravity = 0;
        set_animation(self, 0x12);
        self->unk6 = 2;
    }
}

void slash_beast_stagger_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        slash_beast_face_player(self);
        set_animation(self, 0xC);
        self->unk7C = 0x14;
        self->unk7E = 1;
        self->unk5 = 6;
        self->unk6 = 0;
        self->ext.main_54.claw_hitbox = 1;
    }
}

void slash_beast_high_leap(struct MainObj* self)
{
    slash_beast_high_leap_funcs[self->unk6](self);
}

void slash_beast_high_leap_jump(struct AnimatedObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.event != 0) {
        if (self->unk15 == 0) {
            self->x_vel.val = FIXED(-1.75);
        } else {
            self->x_vel.val = FIXED(1.75);
        }
        self->y_vel.val = FIXED(7.4375);
        self->unk28 = 0;
        self->unk2C = FIXED(0.21875);
        move_with_gravity(self);
        func_8001540C(2, 0x81, self);
        set_animation(self, 2);
        self->unk6 = 1;
    }
}

void slash_beast_high_leap_fall(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_speed == 0) {
        self->gravity = FIXED(2);
        self->x_speed = 0;
        self->unk6 = 2;
        set_animation(self, 0x17);
        self->contact_damage = 7;
        self->attack_box = (const u8*)&D_80100210;
        self->hurt_box = (const u8*)&D_80100214;
    }
}

void slash_beast_high_leap_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if ((func_8002D724(
             PLAYER_OBJECT(self),
             (s16)((u16)self->x_pos.i.hi + self->terrain_box->unk0),
             (s16)(self->terrain_box->unk3 + ((u16)self->y_pos.i.hi + self->terrain_box->unk1) + 0x10))
            & 0xFF)
        == 0x38) {
        func_8001540C(2, 0x88, self);
        start_screen_shake_y(0x10, 4, 2);
        set_animation(self, 3);
        self->unk6 = 3;
    }
}

void slash_beast_high_leap_recover(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->contact_damage = 5;
        self->y_speed = 0;
        self->gravity = 0;
    }
    if (self->animation_step.fields.event != 0) {
        self->attack_box = (const u8*)D_801001F8;
        self->hurt_box = (const u8*)D_801001FC;
        set_animation(self, 0);
        slash_beast_face_player(self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

// slash_beast_set_floor_palette
INCLUDE_ASM("main/nonmatchings/mains/main_54_slash_beast", func_8006E920);

void slash_beast_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

void slash_beast_pick_pattern(struct MainObj* self)
{
    u8* base;
    u8* current;
    u8* thresholds;
    u32 random;
    u8 index;
    s32 i;

    random = get_random();
    i = 0;
    random &= 0xF;
    index = self->ext.main_54.pattern_set;
    thresholds = slash_beast_pattern_weights;
    base = slash_beast_patterns[index][0];
    thresholds += (index << 1) + index;
    current = base;

    for (; i < 3; i++) {
        if (random < *thresholds) {
            self->ext.main_54.pattern = current;
            return;
        }
        current += 4;
        thresholds++;
    }

    self->ext.main_54.pattern = base + i * 4;
}

union AnimationStep D_801001F8[] = {
    { 0x2225F1EF },
};

union AnimationStep D_801001FC[] = {
    { 0x313AEBE5 },
};

struct Unk_unk68 D_80100200 = { -28, -16, 34, 38 };

struct Unk_unk68 D_80100204 = { -37, -24, 64, 48 };

struct Unk_unk68 D_80100208 = { -11, -30, 29, 57 };

struct Unk_unk68 D_8010020C = { -17, -32, 43, 66 };

struct Unk_unk68 D_80100210 = { -16, -38, 31, 81 };

struct Unk_unk68 D_80100214 = { -22, -43, 43, 93 };

struct Unk_unk68 D_80100218 = { -42, -19, 33, 27 };

struct Unk_unk68 D_8010021C = { -66, -10, 26, 6 };

struct Unk_unk68 D_80100220 = { -15, -29, 26, 50 };

struct Unk_unk68 D_80100224 = { -22, -36, 40, 64 };

struct Unk_unk68 D_80100228 = { -11, -13, 39, 27 };

struct Unk_unk68 D_8010022C = { -20, -22, 57, 46 };

union AnimationStep D_80100230[] = {
    { 0x2244F5C4 },
};

union AnimationStep D_80100234[] = {
    { 0x3959E8C2 },
};

union AnimationStep D_80100238[] = {
    { 0x1F47D0B1 },
};

struct Unk_unk68 D_8010023C = { -48, -73, 49, 48 };

struct Unk_unk68 D_80100240 = { -74, -69, 105, 90 };

struct Unk_unk68 D_80100244 = { -6, -68, 32, 80 };

struct Unk_unk68 D_80100248 = { -15, -71, 48, 96 };

struct Unk_unk68 D_8010024C = { 0, 0, 28, 26 };

u8 slash_beast_pattern_steps[9][4] = {
    { 0, 1, 1, 255 },
    { 0, 7, 2, 255 },
    { 0, 3, 4, 255 },
    { 0, 7, 2, 255 },
    { 5, 3, 4, 6 },
    { 255, 0, 0, 0 },
    { 0, 7, 2, 2 },
    { 255, 0, 0, 0 },
    { 5, 6, 6, 255 },
};

u8* D_80100274[4] = {
    slash_beast_pattern_steps[0],
    slash_beast_pattern_steps[1],
    0x00000000,
    0x00000000,
};

u8* D_80100284[4] = {
    slash_beast_pattern_steps[2],
    slash_beast_pattern_steps[3],
    0x00000000,
    0x00000000,
};

u8* D_80100294[4] = {
    slash_beast_pattern_steps[4],
    slash_beast_pattern_steps[6],
    slash_beast_pattern_steps[8],
    0x00000000,
};

u8** slash_beast_patterns[3] = {
    D_80100274,
    D_80100284,
    D_80100294,
};

u8 slash_beast_pattern_weights[12] = { 0x07, 0x10, 0x00, 0x09, 0x10, 0x00, 0x07, 0x0A, 0x10, 0x00, 0x00, 0x00 };

union AnimationStep D_801002BC[] = {
    { 0x00000101 },
};

union AnimationStep D_801002C0[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010004 },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_801002D8[] = {
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010202 },
    { 0x06FF0102 },
};

union AnimationStep D_80100308[] = {
    { 0x02010002 },
    { 0x01010002 },
    { 0x0201000C },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_80100320[] = {
    { 0x07010002 },
    { 0x08FF0102 },
};

union AnimationStep D_80100328[] = {
    { 0x09010013 },
    { 0x09000101 },
};

union AnimationStep D_80100330[] = {
    { 0x02010002 },
    { 0x01010002 },
    { 0x0201001C },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_80100348[] = {
    { 0x0A000101 },
};

union AnimationStep D_8010034C[] = {
    { 0x01010002 },
    { 0x02010002 },
    { 0x01010002 },
    { 0x1F010202 },
    { 0x20010010 },
    { 0x20000101 },
};

union AnimationStep D_80100364[] = {
    { 0x1F010002 },
    { 0x21010002 },
    { 0x22010402 },
    { 0x23010002 },
    { 0x24010201 },
    { 0x25010301 },
    { 0x26010501 },
    { 0x27010001 },
    { 0x28010002 },
    { 0x2701000A },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010602 },
    { 0x2C010702 },
    { 0x2B010001 },
    { 0x2B000101 },
};

union AnimationStep D_801003A4[] = {
    { 0x01010002 },
    { 0x0201001E },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_801003B8[] = {
    { 0x00010002 },
    { 0x1A010002 },
    { 0x1B010201 },
    { 0x1B010007 },
    { 0x1A010002 },
    { 0x00010002 },
    { 0x17010001 },
    { 0x18FF0101 },
};

union AnimationStep D_801003D8[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x0B010001 },
    { 0x0D010001 },
    { 0x0CFE0101 },
};

union AnimationStep D_801003EC[] = {
    { 0x02010001 },
    { 0x0E010001 },
    { 0x09000101 },
};

union AnimationStep D_801003F8[] = {
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11FE0101 },
};

union AnimationStep D_80100404[] = {
    { 0x12010002 },
    { 0x13010202 },
    { 0x14010002 },
    { 0x15010014 },
    { 0x14010002 },
    { 0x13010001 },
    { 0x13000101 },
};

union AnimationStep D_80100420[] = {
    { 0x16010001 },
    { 0x0A000101 },
};

union AnimationStep D_80100428[] = {
    { 0x33010002 },
    { 0x34FF0102 },
};

union AnimationStep D_80100430[] = {
    { 0x35010002 },
    { 0x36010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x35010002 },
    { 0x36010018 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x02010002 },
    { 0x01010002 },
    { 0x00010001 },
    { 0x00000101 },
};

union AnimationStep D_80100460[] = {
    { 0x37000101 },
};

union AnimationStep D_80100464[] = {
    { 0x30010001 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x1BFD0101 },
};

union AnimationStep D_80100474[] = {
    { 0x2D010001 },
    { 0x2E010001 },
    { 0x2FFE0101 },
};

union AnimationStep D_80100480[] = {
    { 0x03010002 },
    { 0x04FF0102 },
};

union AnimationStep D_80100488[] = {
    { 0x05010002 },
    { 0x06010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x1C010002 },
    { 0x1DFF0102 },
};

union AnimationStep D_801004A0[] = {
    { 0x19000101 },
};

union AnimationStep D_801004A4[] = {
    { 0x00010002 },
    { 0x1A010002 },
    { 0x1B010014 },
    { 0x1A010002 },
    { 0x00010002 },
    { 0x17010001 },
    { 0x18FF0101 },
};

union AnimationStep D_801004C0[] = {
    { 0x38010001 },
    { 0x39FF0101 },
};

union AnimationStep D_801004C8[] = {
    { 0x3A010001 },
    { 0x3BFF0101 },
};

union AnimationStep D_801004D0[] = {
    { 0x74000101 },
};

union AnimationStep D_801004D4[] = {
    { 0x75000101 },
};

union AnimationStep D_801004D8[] = {
    { 0x76000101 },
};

union AnimationStep D_801004DC[] = {
    { 0x77000101 },
};

union AnimationStep D_801004E0[] = {
    { 0x78000101 },
};

union AnimationStep D_801004E4[] = {
    { 0x79000101 },
};

union AnimationStep D_801004E8[] = {
    { 0x7A000101 },
};

union AnimationStep D_801004EC[] = {
    { 0x7B000101 },
};

union AnimationStep D_801004F0[] = {
    { 0x7C000101 },
};

union AnimationStep D_801004F4[] = {
    { 0x05010002 },
    { 0x06FF0102 },
};

union AnimationStep D_801004FC[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010006 },
    { 0x01010003 },
    { 0x00010002 },
    { 0x00000101 },
};

union AnimationStep* slash_beast_animations[39] = {
    D_801002BC,
    D_801002C0,
    D_801002D8,
    D_80100308,
    D_80100320,
    D_80100328,
    D_80100330,
    D_80100348,
    D_8010034C,
    D_80100364,
    D_801003A4,
    D_801003B8,
    D_801003D8,
    D_801003EC,
    D_801003F8,
    D_80100404,
    D_80100420,
    D_80100428,
    D_80100430,
    D_80100460,
    D_80100464,
    D_80100474,
    D_80100480,
    D_80100488,
    D_801004A0,
    D_801004A4,
    D_801004C0,
    D_801004C8,
    D_801004D0,
    D_801004D4,
    D_801004D8,
    D_801004DC,
    D_801004E0,
    D_801004E4,
    D_801004E8,
    D_801004EC,
    D_801004F0,
    D_801004F4,
    D_801004FC,
};

u8 D_801005B0[4] = { 29, 30, 31, 32 };

char D_801005B4[] = "\"#$";

u16 D_801005B8[8] = {
    0x0070,
    0x0072,
    0x0074,
    0x0076,
    0x0065,
    0x0067,
    0x0069,
    0x006B,
};

u16 D_801005C8[14] = {
    0x0388,
    0x038D,
    0x03AC,
    0x03AF,
    0x03B2,
    0x03B5,
    0x03C3,
    0x0380,
    0x0383,
    0x0390,
    0x0392,
    0x0394,
    0x0396,
    0x03A0,
};

void (*slash_beast_state_funcs[])(struct MainObj*) = {
    func_8006BB70,
    func_8006BD1C,
    slash_beast_death,
};

void (*slash_beast_step_funcs[12])() = {
    enemy_hit_reaction,
    slash_beast_start_pattern,
    slash_beast_crescent,
    slash_beast_decide,
    slash_beast_jump,
    func_8006CDD4,
    slash_beast_dash,
    func_8006D3DC,
    slash_beast_grab,
    slash_beast_intro,
    slash_beast_stagger,
    slash_beast_high_leap,
};

void (*slash_beast_death_funcs[3])(struct MainObj*) = {
    slash_beast_death_start,
    slash_beast_death_blink,
    slash_beast_death_finish,
};

void (*slash_beast_crescent_funcs[4])(struct MainObj*) = {
    slash_beast_crescent_jump,
    func_8006C378,
    slash_beast_crescent_land,
    slash_beast_crescent_recover,
};

void (*slash_beast_decide_funcs[2])() = {
    func_8006C6AC,
    slash_beast_crouch,
};

void (*slash_beast_jump_funcs[3])(struct MainObj*) = {
    func_8006CB50,
    func_8006CC3C,
    slash_beast_jump_recover,
};

void (*slash_beast_dash_funcs[5])(struct MainObj*) = {
    slash_beast_dash_windup,
    slash_beast_dash_start,
    func_8006CFB8,
    func_8006D280,
    slash_beast_dash_turn,
};

void (*slash_beast_grab_funcs[4])(struct MainObj*) = {
    slash_beast_grab_check,
    slash_beast_grab_windup,
    func_8006D888,
    slash_beast_grab_throw,
};

void (*slash_beast_intro_funcs[8])(struct MainObj*) = {
    slash_beast_intro_wait_player,
    slash_beast_intro_wait_warning,
    func_8006DD44,
    slash_beast_intro_leap,
    slash_beast_intro_land,
    slash_beast_intro_pose,
    slash_beast_intro_wait_dialogue,
    slash_beast_intro_fill_health,
};

void (*slash_beast_stagger_funcs[3])(struct MainObj*) = {
    func_8006E450,
    slash_beast_stagger_land,
    slash_beast_stagger_recover,
};

void (*slash_beast_high_leap_funcs[4])(struct MainObj*) = {
    slash_beast_high_leap_jump,
    slash_beast_high_leap_fall,
    slash_beast_high_leap_land,
    slash_beast_high_leap_recover,
};
