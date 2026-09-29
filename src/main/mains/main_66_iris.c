// MainObj, main_object_update_funcs[66]
// 800806A0..80082434
#include "common.h"
#include "func_tables.h"

void iris_update(struct MainObj* self)
{
    iris_state_funcs[self->state](self);
    if (self->unk2 == 0) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// iris_init
INCLUDE_ASM("main/nonmatchings/mains/main_66_iris", func_80080700);

// iris_run
INCLUDE_ASM("main/nonmatchings/mains/main_66_iris", func_80080834);

void iris_death(struct BarObj* self)
{
    iris_death_funcs[self->unk5](self);
}

void iris_death_start(struct MainObj* self)
{
    struct MainObj* other;

    g_Player.stun_timer = 0;
    player_start_script_action(0x14, g_Player.unk15);
    self->unk5 = 1;
    other = self->ext.main_66.partner;
    self->unk42 &= 0x7FFF;
    other->unk42 &= 0x7FFF;
    set_animation(self->ext.main_66.partner, 8);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->invincibility_timer = 0x19;
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

// iris_death_blink
INCLUDE_ASM("main/nonmatchings/mains/main_66_iris", func_80080DF4);

void iris_death_wait_explosion(struct MainObj* self)
{
    struct EffectObj* effect;
    struct MainObj* linked;

    self->on_screen = 0;
    self->ext.main_66.partner->on_screen = 0;
    self->on_screen = 0;
    effect = self->ext.main_66.effect;

    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (self->unk7E-- == 0) {
                linked = self->ext.main_66.partner;
                linked->unk42 ^= 0x8000;
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            update_on_screen(BASE_OBJECT(self->ext.main_66.partner), 0x60, 0x60);
        } else {
            linked = self->ext.main_66.partner;
            if (linked->active != 0) {
                linked->unk5 = 1;
            }
            self->unk15 = self->ext.main_66.partner->unk15 ^ 0x40;
            self->x_pos.i.hi = self->ext.main_66.partner->x_pos.i.hi;
            self->y_pos.i.hi = 0x1CA;
            self->unk16 = 0;
            set_animation(self, 0x23);
        }
        update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
        return;
    }

    if (g_Player.x_pos.i.hi > self->x_pos.i.hi) {
        player_start_script_action(0x14, 0);
    } else {
        player_start_script_action(0x14, 0x40);
    }
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = 0;
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
    self->unk7C = 0x3C;
    self->unk5 = 3;
}

void iris_death_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        engine_obj.unkF = 0x40;
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void iris_despawn(struct MainObj* self)
{
    if (self->unk5 == 0) {
        update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
    } else {
        self->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void iris_robot_decide(struct MainObj* self)
{
    s8 state;

    if ((self->ext.main_66.crystal_released == 0) && (--self->ext.main_66.release_countdown == 0)) {
        set_animation(self, 0x20);
        self->collision_data = (const u16*)D_80107E84;
        state = 5;
    } else {
        set_animation(self, 1);
        func_8001540C(2, 0xE1, self);
        state = 3;
    }
    self->unk5 = state;
    self->unk6 = 0;
}

void iris_intro(struct MainObj* self)
{
    iris_intro_funcs[self->unk6](self);
}

void iris_intro_wait_player(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (g_Player.x_pos.i.hi >= 0x80B) {
        background_objects[0].unk26 = 0x7F0;
        background_objects[0].unk24 = 0x830;
        self->unk6 = 1;
    }
}

void iris_intro_wait_camera(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (background_objects[0].x_pos.i.hi == 0x7F0) {
        player_start_script_action(0x15, 0);
        self->unk6 = 2;
    }
}

void iris_intro_warning(struct MainObj* self)
{
    struct EffectObj* effect;

    animate_object(ANIMATED_OBJECT(self));
    if (g_Player.script_state == -1) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_66.effect = effect;
        }
        self->unk6 = 3;
    }
}

void iris_intro_wait_warning(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->ext.main_66.effect->active == 0) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = self;
        self->unk7C = 0x3C;
        self->unk6 = 4;
    }
}

void iris_intro_dialogue(struct MainObj* self)
{
    s8* state;
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        state = &engine_obj.character_state.bytes[9];
        func_8002217C(0x20, 0xFF, *state);
        *state = 1;
        self->unk6 = 5;
    }
}

void iris_intro_wait_dialogue(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (abc_object.unkC == 0) {
        self->unk7C = 0x28;
        self->unk6 = 6;
    }
}

void iris_intro_toss_crystal(struct MainObj* self)
{
    struct MiscObj* obj;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 0xA);
        obj = find_free_misc_obj();
        if (obj != 0) {
            obj->active = 0x41;
            obj->id = 0x27;
            obj->x_pos.val = self->x_pos.val + FIXED(-1);
            obj->y_pos.val = self->y_pos.val + FIXED(-31);
            obj->bg_offset = self->bg_offset;
            obj->animation_table = self->animation_table;
            obj->unk40 = self->unk40;
            obj->unk3C = self->sprite_frames;
            obj->unk42 = self->unk42 & 0x7FFF;
            obj->ext.misc_7.position = self;
            obj->state = 0;
            obj->unk5 = 0;
        }
        self->unk7C = 0x3E;
        self->unk6 = 7;
    }
}

void iris_intro_wait_transform(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
}

void iris_intro_transform(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        set_animation(self, 0x1F);
        self->unk7C = 0xC8;
        self->unk6 = 9;
    }
}

void iris_intro_pose(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        set_animation(self, 0);
        self->unk6 = 0xA;
    }
}

void iris_intro_voice(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, 0xDF, self);
    }
    if (self->animation_step.fields.event == 1) {
        self->unk6 = 0xB;
        self->unk7E = 3;
        play_boss_music(9);
    }
}

void iris_intro_fill_health(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (update_boss_music_delay() == 0) {
        if (--self->unk7E == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7E = 3;
        }
        if (++self->hp == 0x30) {
            self->ext.main_66.active = 1;
            set_animation(self, 1);
            func_8001540C(2, 0xE1, self);
            self->unk5 = 3;
            self->unk6 = 0;
            player_end_script_action();
        }
    }
}

void iris_robot_hover(struct MainObj* self)
{
    iris_robot_hover_funcs[self->unk6](self);
}

// iris_robot_hover_chase
INCLUDE_ASM("main/nonmatchings/mains/main_66_iris", func_80081718);

void iris_robot_dash(struct MainObj* self)
{
    iris_robot_dash_funcs[self->unk6](self);
}

void iris_robot_dash_land(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        set_animation(self, 3);
        self->y_speed = 0;
        self->unk6 = 1;
    }
}

// iris_robot_dash_start
INCLUDE_ASM("main/nonmatchings/mains/main_66_iris", func_800818C4);

void iris_robot_dash_run(struct MainObj* self)
{
    s32 flags;

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk15 == 0) {
        flags = self->collision_flags & 1;
    } else {
        flags = self->collision_flags & 2;
    }
    if (flags != 0) {
        set_animation(self, 5);
        self->unk6 = 3;
    }
}

void iris_robot_dash_laser(struct MainObj* self)
{
    s32 i;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_8001540C(2, 0xE2, self);
        set_animation(self, 6);
        i = 0;
        self->x_speed = 0;
        self->unk7C = 0xB4;
        do {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x2C;
                shot->unk2 = i;
                shot->x_pos.val = self->x_pos.val;
                shot->y_pos.val = self->y_pos.val;
                shot->unk67 = 0;
                shot->bg_offset = self->bg_offset;
                shot->animation_table = (u32**)self->animation_table;
                shot->unk40 = self->unk40;
                shot->unk3C = (void*)self->sprite_frames;
                shot->unk42 = self->unk42 & 0x7FFF;
                shot->unk15 = self->unk15;
                shot->unk7C = WEAPON_OBJECT(self);
                shot->state = 3;
            }
            i++;
        } while (i < 2);
        self->unk6 = 4;
    }
}

// iris_robot_dash_recover
INCLUDE_ASM("main/nonmatchings/mains/main_66_iris", func_80081AD0);

void iris_robot_release_crystal(struct MainObj* self)
{
    iris_robot_release_crystal_funcs[self->unk6](self);
}

// iris_robot_release_crystal_spawn
INCLUDE_ASM("main/nonmatchings/mains/main_66_iris", func_80081BA0);

void iris_robot_release_crystal_wait(struct MainObj* self)
{
    if (self->hp >= 0x18) {
        self->ext.main_66.hover_timer = 0xF0;
    } else {
        self->ext.main_66.hover_timer = 0xB4;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void iris_robot_release_crystal_finish(struct MainObj* self)
{
    struct MainObj* crystal;
    s16 timer;
    s16* out_y;
    u16* out_x;
    s32 i;

    if (self->unk7C >= 0x11) {
        move_object(MOVING_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));

    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->y_speed = 0;
        self->ext.main_66.partner->ext.main_66.crystal_released = 1;
        set_animation(self->ext.main_66.partner, 1);
        self->ext.main_66.partner->collision_data = D_80107DFC;
        func_8001540C(2, 0xE1, self);

        i = 0;
        out_y = D_8013B878;
        self->ext.main_66.partner->unk5 = 3;
        out_x = D_8013B858;
        self->ext.main_66.partner->unk6 = 0;
        do {
            *out_x++ = self->ext.main_66.partner->x_pos.i.hi;
            *out_y++ = self->ext.main_66.partner->y_pos.i.hi - 0x50;
        } while (++i < 0xF);

        self->ext.main_66.trail_write = 0xF;
        self->ext.main_66.trail_read = 0;
        self->unk5 = 6;
        self->unk6 = 0;
    }
}

// iris_crystal_follow
INCLUDE_ASM("main/nonmatchings/mains/main_66_iris", func_80081E44);

void iris_crystal_drop(struct MainObj* self)
{
    iris_crystal_drop_funcs[self->unk6](self);
}

void iris_crystal_drop_fall(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi >= 0x1DD) {
        self->y_pos.i.hi = 0x1DC;
        self->y_speed = 0;
        self->unk6 = 1;
    }
}

void iris_crystal_drop_chase(struct MainObj* self)
{
    s16 x_pos;

    animate_object(ANIMATED_OBJECT(self));
    if (!(D_80141BD8.unk0 & 1)) {
        if (self->x_pos.i.hi < g_Player.x_pos.i.hi) {
            self->x_speed = FIXED(4);
        } else {
            self->x_speed = FIXED(-4);
        }
    }

    x_pos = self->x_pos.i.hi;
    if (x_pos - g_Player.x_pos.i.hi >= 0) {
        if (x_pos - g_Player.x_pos.i.hi < 3) {
        } else {
            move_object(MOVING_OBJECT(self));
        }
    } else if (g_Player.x_pos.i.hi - x_pos >= 3) {
        move_object(MOVING_OBJECT(self));
    }

    if (self->ext.main_66.partner->unk6 == 4) {
        self->unk7C = 0x3C;
        self->unk6 = 2;
    }
}

void iris_crystal_drop_aim(struct MainObj* self)
{
    s16 x_pos;

    animate_object(ANIMATED_OBJECT(self));
    if (!(D_80141BD8.unk0 & 1)) {
        if (self->x_pos.i.hi < g_Player.x_pos.i.hi) {
            self->x_speed = FIXED(4);
        } else {
            self->x_speed = FIXED(-4);
        }
    }

    x_pos = self->x_pos.i.hi;
    if (x_pos - g_Player.x_pos.i.hi >= 0) {
        if (x_pos - g_Player.x_pos.i.hi < 3) {
        } else {
            move_object(MOVING_OBJECT(self));
        }
    } else if (g_Player.x_pos.i.hi - x_pos >= 3) {
        move_object(MOVING_OBJECT(self));
    }

    if (--self->unk7C == 0) {
        func_8001540C(2, 0xE2, self);
        set_animation(self, 0x11);
        self->unk7C = 0x3C;
        self->unk6 = 3;
    }
}

void iris_crystal_drop_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    u32 timer;
    u8 facing;

    animate_object(ANIMATED_OBJECT(self));
    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 16) == 0) {
        func_8001540C(2, 0xE3, self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x2C;
            shot->unk2 = 0;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk67 = 0;
            shot->bg_offset = self->bg_offset;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk40 = self->unk40;
            shot->unk3C = (void*)self->sprite_frames;
            shot->unk42 = self->unk42 & 0x7FFF;
            facing = self->unk15;
            shot->timer = 0x3C;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->state = 6;
            shot->unk15 = facing;
        }
        self->unk7C = 0x86;
        self->unk6 = 4;
    }
}

void iris_crystal_drop_return(struct MainObj* self)
{
    s16* dst_y;
    u16* dst_x;
    s32 i;

    animate_object(ANIMATED_OBJECT(self));
    self->unk7C--;
    i = 0;
    if (self->unk7C == 0) {
        dst_y = D_8013B878;
        dst_x = D_8013B858;
        do {
            *dst_x++ = self->ext.main_66.partner->x_pos.i.hi;
            i++;
            *dst_y++ = self->ext.main_66.partner->y_pos.i.hi - 0x50;
        } while (i < 0xF);
        self->ext.main_66.trail_write = 0xF;
        self->ext.main_66.trail_read = 0;
        set_animation(self, 0x10);
        self->unk5 = 6;
        self->unk6 = 0;
    }
}

void iris_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

struct Unk_unk68 D_801035BC = { -21, -26, 36, 51 };

struct Unk_unk68 D_801035C0 = { -27, -31, 51, 62 };

struct Unk_unk68 D_801035C4 = { -8, -9, 13, 16 };

struct Unk_unk68 D_801035C8 = { -12, -11, 22, 20 };

struct Unk_unk68 D_801035CC = { 0, 0, 28, 20 };

union AnimationStep D_801035D0[] = {
    { 0x00010014 },
    { 0x01010008 },
    { 0x02010004 },
    { 0x03010204 },
    { 0x04010003 },
    { 0x05010014 },
    { 0x06010012 },
    { 0x07010002 },
    { 0x07000101 },
};

struct Unk_unk68 D_801035F4[4] = {
    { 1, 0, 1, 8 },
    { 1, 0, 1, 9 },
    { 1, 0, 1, 10 },
    { 1, 1, -3, 11 },
};

struct Unk_unk68 D_80103604[4] = {
    { 1, 0, 1, 12 },
    { 1, 0, 1, 13 },
    { 1, 0, 1, 14 },
    { 1, 1, -3, 15 },
};

union AnimationStep D_80103614[] = {
    { 0x10010004 },
    { 0x11010003 },
    { 0x10010004 },
    { 0x02010005 },
    { 0x02000101 },
};

struct Unk_unk68 D_80103628[4] = {
    { 2, 0, 1, 18 },
    { 2, 0, 1, 19 },
    { 2, 0, 1, 20 },
    { 2, 1, -3, 21 },
};

union AnimationStep D_80103638[] = {
    { 0x01010004 },
    { 0x16010003 },
    { 0x01010004 },
    { 0x17010005 },
    { 0x17000101 },
};

struct Unk_unk68 D_8010364C[4] = {
    { 1, 0, 1, 24 },
    { 1, 0, 1, 25 },
    { 1, 0, 1, 26 },
    { 1, 1, -3, 23 },
};

struct Unk_unk68 D_8010365C[4] = {
    { 1, 0, 1, 27 },
    { 1, 0, 1, 28 },
    { 1, 0, 1, 29 },
    { 1, 1, -3, 30 },
};

union AnimationStep D_8010366C[] = {
    { 0x1F000101 },
};

struct Unk_unk68 D_80103670[4] = {
    { 5, 0, 1, 40 },
    { 5, 0, 1, 41 },
    { 5, 0, 1, 42 },
    { 5, 1, -3, 43 },
};

union AnimationStep D_80103680[] = {
    { 0x2C000101 },
};

union AnimationStep D_80103684[] = {
    { 0x2D000101 },
};

struct Unk_unk68 D_80103688[3] = {
    { 3, 0, 1, 46 },
    { 3, 0, 1, 47 },
    { 3, 1, -2, 48 },
};

struct Unk_unk68 D_80103694[4] = {
    { 5, 0, 1, 49 },
    { 5, 0, 1, 50 },
    { 5, 0, 1, 51 },
    { 5, 1, -3, 52 },
};

union AnimationStep D_801036A4[] = {
    { 0x35010002 },
    { 0x36010002 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3D010002 },
    { 0x3E010002 },
    { 0x3D010001 },
    { 0x3D010001 },
    { 0x3F010001 },
    { 0x3F010001 },
    { 0x40010005 },
    { 0x40000101 },
};

union AnimationStep D_801036E4[] = {
    { 0x41010003 },
    { 0x42010003 },
    { 0x43010003 },
    { 0x44010003 },
    { 0x45010005 },
    { 0x46010002 },
    { 0x47000101 },
};

union AnimationStep D_80103700[] = {
    { 0x47010002 },
    { 0x48010002 },
    { 0x49010002 },
    { 0x47010002 },
    { 0x48010002 },
    { 0x49010002 },
    { 0x47010001 },
    { 0x48010001 },
    { 0x49000101 },
};

union AnimationStep D_80103724[] = {
    { 0x4A010003 },
    { 0x4B010003 },
    { 0x4C010004 },
    { 0x4D010003 },
    { 0x4E010203 },
    { 0x4F010002 },
    { 0x50010002 },
    { 0x51010003 },
    { 0x52010003 },
    { 0x53010003 },
    { 0x54010003 },
    { 0x54000101 },
};

struct Unk_unk68 D_80103754[20] = {
    { 3, 0, 1, 85 },
    { 3, 0, 1, 86 },
    { 1, 0, 1, 93 },
    { 1, 0, 1, 87 },
    { 1, 0, 1, 93 },
    { 1, 0, 1, 88 },
    { 1, 0, 1, 94 },
    { 1, 0, 1, 88 },
    { 1, 0, 1, 95 },
    { 1, 0, 1, 89 },
    { 1, 0, 1, 96 },
    { 1, 0, 1, 90 },
    { 1, 0, 1, 96 },
    { 1, 0, 1, 90 },
    { 1, 0, 1, 97 },
    { 1, 0, 1, 91 },
    { 1, 0, 1, 97 },
    { 1, 0, 1, 92 },
    { 1, 0, 1, 98 },
    { 1, 1, -19, 92 },
};

struct Unk_unk68 D_801037A4[8] = {
    { 3, 0, 1, 85 },
    { 3, 0, 1, 99 },
    { 3, 0, 1, 100 },
    { 3, 0, 1, 101 },
    { 3, 0, 1, 102 },
    { 3, 0, 1, 103 },
    { 3, 0, 1, 104 },
    { 3, 1, -7, 105 },
};

struct Unk_unk68 D_801037C4[8] = {
    { 2, 0, 1, 108 },
    { 2, 0, 1, 109 },
    { 2, 0, 1, 108 },
    { 2, 0, 1, 109 },
    { 2, 0, 1, 108 },
    { 2, 0, 1, 109 },
    { 2, 0, 1, 110 },
    { 2, 1, -7, 111 },
};

u8 D_801037E4[8] = { 1, 0, 1, 107, 1, 1, 255, 106 };

struct Unk_unk68 D_801037EC[8] = {
    { 2, 0, 1, 114 },
    { 2, 0, 1, 115 },
    { 2, 0, 1, 114 },
    { 2, 0, 1, 115 },
    { 2, 0, 1, 114 },
    { 2, 0, 1, 115 },
    { 2, 0, 1, 116 },
    { 2, 1, -7, 117 },
};

u8 D_8010380C[8] = { 1, 0, 1, 113, 1, 1, 255, 112 };

struct Unk_unk68 D_80103814[6] = {
    { 1, 0, 1, 118 },
    { 2, 0, 1, 119 },
    { 1, 0, 1, 120 },
    { 2, 0, 1, 121 },
    { 1, 0, 1, 122 },
    { 2, 1, -5, 123 },
};

struct Unk_unk68 D_8010382C[3] = {
    { 1, 0, 1, 124 },
    { 1, 0, 1, 125 },
    { 1, 1, -2, 126 },
};

union AnimationStep D_80103838[] = {
    { 0x8A010001 },
    { 0x89010001 },
    { 0x88010001 },
    { 0x87010001 },
    { 0x86010001 },
    { 0x85010001 },
    { 0x84010001 },
    { 0x83010001 },
    { 0x82010001 },
    { 0x81010001 },
    { 0x80010001 },
    { 0x7F010001 },
    { 0x95010001 },
    { 0x94010001 },
    { 0x93010001 },
    { 0x92010001 },
    { 0x91010001 },
    { 0x90010001 },
    { 0x8F010001 },
    { 0x8E010001 },
    { 0x8D010001 },
    { 0x8C010001 },
    { 0x8BEA0001 },
};

struct Unk_unk68 D_80103894[31] = {
    { 2, 0, 1, -106 },
    { 2, 0, 1, -105 },
    { 2, 0, 1, -104 },
    { 2, 0, 1, -103 },
    { 2, 0, 1, -102 },
    { 2, 0, 1, -101 },
    { 2, 0, 1, -100 },
    { 1, 2, 1, -99 },
    { 1, 0, 1, -98 },
    { 1, 0, 1, -99 },
    { 1, 0, 1, -96 },
    { 1, 0, 1, -97 },
    { 1, 0, 1, -96 },
    { 1, 0, 1, -95 },
    { 1, 0, 1, -94 },
    { 1, 0, 1, -95 },
    { 1, 0, 1, -92 },
    { 1, 0, 1, -93 },
    { 1, 0, 1, -92 },
    { 1, 0, 1, -91 },
    { 1, 0, 1, -90 },
    { 1, 0, 1, -91 },
    { 1, 0, 1, -88 },
    { 1, 0, 1, -89 },
    { 1, 0, 1, -88 },
    { 1, 0, 1, -87 },
    { 1, 0, 1, -86 },
    { 1, 0, 1, -87 },
    { 1, 0, 1, -84 },
    { 1, 0, 1, -85 },
    { 1, 0, -23, -84 },
};

union AnimationStep D_80103910[] = {
    { 0x9C010002 },
    { 0x9B010002 },
    { 0x9A010002 },
    { 0x99010002 },
    { 0x98010002 },
    { 0x97010002 },
    { 0x96010001 },
    { 0x96000101 },
};

struct Unk_unk68 D_80103930[31] = {
    { 2, 0, 1, -69 },
    { 2, 0, 1, -83 },
    { 2, 0, 1, -82 },
    { 2, 0, 1, -81 },
    { 2, 0, 1, -80 },
    { 2, 0, 1, -79 },
    { 2, 0, 1, -78 },
    { 1, 2, 1, -77 },
    { 1, 0, 1, -76 },
    { 1, 0, 1, -77 },
    { 1, 0, 1, -74 },
    { 1, 0, 1, -75 },
    { 1, 0, 1, -74 },
    { 1, 0, 1, -73 },
    { 1, 0, 1, -72 },
    { 1, 0, 1, -73 },
    { 1, 0, 1, -70 },
    { 1, 0, 1, -71 },
    { 1, 0, 1, -70 },
    { 1, 0, 1, -66 },
    { 1, 0, 1, -65 },
    { 1, 0, 1, -66 },
    { 1, 0, 1, -63 },
    { 1, 0, 1, -64 },
    { 1, 0, 1, -63 },
    { 1, 0, 1, -62 },
    { 1, 0, 1, -61 },
    { 1, 0, 1, -62 },
    { 1, 0, 1, -59 },
    { 1, 0, 1, -60 },
    { 1, 0, -23, -59 },
};

union AnimationStep D_801039AC[] = {
    { 0xB2010002 },
    { 0xB1010002 },
    { 0xB0010002 },
    { 0xAF010002 },
    { 0xAE010002 },
    { 0xAD010002 },
    { 0xBB010001 },
    { 0xBB000101 },
};

struct Unk_unk68 D_801039CC[31] = {
    { 2, 0, 1, -69 },
    { 2, 0, 1, -69 },
    { 2, 0, 1, -104 },
    { 2, 0, 1, -103 },
    { 2, 0, 1, -102 },
    { 2, 0, 1, -101 },
    { 2, 0, 1, -100 },
    { 1, 2, 1, -99 },
    { 1, 0, 1, -98 },
    { 1, 0, 1, -99 },
    { 1, 0, 1, -96 },
    { 1, 0, 1, -97 },
    { 1, 0, 1, -96 },
    { 1, 0, 1, -95 },
    { 1, 0, 1, -94 },
    { 1, 0, 1, -95 },
    { 1, 0, 1, -92 },
    { 1, 0, 1, -93 },
    { 1, 0, 1, -92 },
    { 1, 0, 1, -91 },
    { 1, 0, 1, -90 },
    { 1, 0, 1, -91 },
    { 1, 0, 1, -88 },
    { 1, 0, 1, -89 },
    { 1, 0, 1, -88 },
    { 1, 0, 1, -87 },
    { 1, 0, 1, -86 },
    { 1, 0, 1, -87 },
    { 1, 0, 1, -84 },
    { 1, 0, 1, -85 },
    { 1, 0, -23, -84 },
};

union AnimationStep D_80103A48[] = {
    { 0x9C010002 },
    { 0x9B010002 },
    { 0x9A010002 },
    { 0x99010002 },
    { 0x98010002 },
    { 0x97010002 },
    { 0x96010001 },
    { 0x96000101 },
};

union AnimationStep D_80103A68[] = {
    { 0xC6010002 },
    { 0xC7010002 },
    { 0xC8010002 },
    { 0xC9010002 },
    { 0xCA010002 },
    { 0xCB010002 },
    { 0xCC010002 },
    { 0xCD010002 },
    { 0xCE010002 },
    { 0xCF010002 },
    { 0xD0010002 },
    { 0xD1010002 },
    { 0xD2010002 },
    { 0xD3010002 },
    { 0xD4010002 },
    { 0xD5010002 },
    { 0xD6010002 },
    { 0xD7010002 },
    { 0xD8010002 },
    { 0xD9010002 },
    { 0xDA010002 },
    { 0xDB010002 },
    { 0xDC010002 },
    { 0xDD010002 },
    { 0xDE010002 },
    { 0xDF010002 },
    { 0xE0010002 },
    { 0xE1010002 },
    { 0xE2010002 },
    { 0xE3010002 },
    { 0xE4010002 },
    { 0xE5010002 },
    { 0xE6010002 },
    { 0xE7010002 },
    { 0xE8010002 },
    { 0xE9010002 },
    { 0xEA010002 },
    { 0xEB010002 },
    { 0xEC010008 },
    { 0xEB010013 },
    { 0xEB000101 },
};

union AnimationStep D_80103B0C[] = {
    { 0xEC010007 },
    { 0xEC000101 },
};

union AnimationStep D_80103B14[] = {
    { 0x20010002 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22010001 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25000101 },
};

union AnimationStep D_80103B44[] = {
    { 0x26000101 },
};

void* iris_animations[37] = {
    D_801035D0,
    D_801035F4,
    D_80103604,
    D_80103614,
    D_80103628,
    D_80103638,
    D_8010364C,
    D_8010365C,
    D_8010366C,
    D_80103670,
    D_80103680,
    D_80103694,
    D_801036A4,
    D_801036E4,
    D_80103700,
    D_80103724,
    D_80103754,
    D_801037A4,
    D_801037C4,
    D_801037E4,
    D_801037EC,
    D_8010380C,
    D_80103814,
    D_8010382C,
    D_80103838,
    D_80103894,
    D_80103910,
    D_80103930,
    D_801039AC,
    D_801039CC,
    D_80103A48,
    D_80103A68,
    D_80103B0C,
    D_80103684,
    D_80103B14,
    D_80103B44,
    D_80103688,
};

void (*iris_state_funcs[4])() = {
    func_80080700,
    func_80080834,
    iris_death,
    iris_despawn,
};

void (*iris_step_funcs[8])() = {
    enemy_hit_reaction,
    iris_robot_decide,
    iris_intro,
    iris_robot_hover,
    iris_robot_dash,
    iris_robot_release_crystal,
    func_80081E44,
    iris_crystal_drop,
};

void (*iris_death_funcs[4])() = {
    iris_death_start,
    func_80080DF4,
    iris_death_wait_explosion,
    iris_death_finish,
};

void (*iris_intro_funcs[12])(struct MainObj*) = {
    iris_intro_wait_player,
    iris_intro_wait_camera,
    iris_intro_warning,
    iris_intro_wait_warning,
    iris_intro_dialogue,
    iris_intro_wait_dialogue,
    iris_intro_toss_crystal,
    iris_intro_wait_transform,
    iris_intro_transform,
    iris_intro_pose,
    iris_intro_voice,
    iris_intro_fill_health,
};

void (*iris_robot_hover_funcs[1])() = {
    func_80081718,
};

void (*iris_robot_dash_funcs[5])() = {
    iris_robot_dash_land,
    func_800818C4,
    iris_robot_dash_run,
    iris_robot_dash_laser,
    func_80081AD0,
};

void (*iris_robot_release_crystal_funcs[3])() = {
    func_80081BA0,
    iris_robot_release_crystal_wait,
    iris_robot_release_crystal_finish,
};

void (*iris_crystal_drop_funcs[5])(struct MainObj*) = {
    iris_crystal_drop_fall,
    iris_crystal_drop_chase,
    iris_crystal_drop_aim,
    iris_crystal_drop_fire,
    iris_crystal_drop_return,
};
