// MainObj, main_object_update_funcs[66]
// 800806A0..80082434
#include "common.h"

void iris_update(struct MainObj* self)
{
    iris_state_funcs[self->state](self);
    if (self->unk2 == 0) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

// iris_init
INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080700);

// iris_run
INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080834);

void iris_death(struct BarObj* self)
{
    iris_death_funcs[self->unk5](self);
}

void iris_death_start(struct MainObj* self)
{
    struct MainObj* other;

    g_Player.unkBA = 0;
    func_80036AE4(0x14, g_Player.unk15);
    self->unk5 = 1;
    other = self->ext.main_66.partner;
    self->unk42 &= 0x7FFF;
    other->unk42 &= 0x7FFF;
    func_80015D60(self->ext.main_66.partner, 8);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
}

// iris_death_blink
INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080DF4);

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
            func_8002B318(BASE_OBJECT(self->ext.main_66.partner), 0x60, 0x60);
        } else {
            linked = self->ext.main_66.partner;
            if (linked->active != 0) {
                linked->unk5 = 1;
            }
            self->unk15 = self->ext.main_66.partner->unk15 ^ 0x40;
            self->x_pos.i.hi = self->ext.main_66.partner->x_pos.i.hi;
            self->y_pos.i.hi = 0x1CA;
            self->unk16 = 0;
            func_80015D60(self, 0x23);
        }
        func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
        return;
    }

    if (g_Player.x_pos.i.hi > self->x_pos.i.hi) {
        func_80036AE4(0x14, 0);
    } else {
        func_80036AE4(0x14, 0x40);
    }
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = 0;
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
    self->unk7C = 0x3C;
    self->unk5 = 3;
}

void iris_death_finish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        engine_obj.unkF = 0x40;
    }
    func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
}

void iris_despawn(struct MainObj* self)
{
    if (self->unk5 == 0) {
        func_8002B318(BASE_OBJECT(self), 0x60, 0x60);
    } else {
        self->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void iris_robot_decide(struct MainObj* self)
{
    s8 state;

    if ((self->ext.main_66.crystal_released == 0) && (--self->ext.main_66.release_countdown == 0)) {
        func_80015D60(self, 0x20);
        self->collision_data = (const u16*)D_80107E84;
        state = 5;
    } else {
        func_80015D60(self, 1);
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
    func_80015DC8(ANIMATED_OBJECT(self));
    if (g_Player.x_pos.i.hi >= 0x80B) {
        background_objects[0].unk26 = 0x7F0;
        background_objects[0].unk24 = 0x830;
        self->unk6 = 1;
    }
}

void iris_intro_wait_camera(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (background_objects[0].x_pos.i.hi == 0x7F0) {
        func_80036AE4(0x15, 0);
        self->unk6 = 2;
    }
}

void iris_intro_warning(struct MainObj* self)
{
    struct EffectObj* effect;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (g_Player.unkC0 == -1) {
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
    func_80015DC8(ANIMATED_OBJECT(self));
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

    func_80015DC8(ANIMATED_OBJECT(self));
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
    func_80015DC8(ANIMATED_OBJECT(self));
    if (abc_object.unkC == 0) {
        self->unk7C = 0x28;
        self->unk6 = 6;
    }
}

void iris_intro_toss_crystal(struct MainObj* self)
{
    struct MiscObj* obj;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_80015D60(self, 0xA);
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
    func_80015DC8(ANIMATED_OBJECT(self));
}

void iris_intro_transform(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_80015D60(self, 0x1F);
        self->unk7C = 0xC8;
        self->unk6 = 9;
    }
}

void iris_intro_pose(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_80015D60(self, 0);
        self->unk6 = 0xA;
    }
}

void iris_intro_voice(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, 0xDF, self);
    }
    if (self->animation_step.fields.event == 1) {
        self->unk6 = 0xB;
        self->unk7E = 3;
        func_800921E8(9);
    }
}

void iris_intro_fill_health(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (func_8009227C() == 0) {
        if (--self->unk7E == 0) {
            func_8001540C(0, 0xE, 0);
            self->unk7E = 3;
        }
        if (++self->unk5C == 0x30) {
            self->ext.main_66.active = 1;
            func_80015D60(self, 1);
            func_8001540C(2, 0xE1, self);
            self->unk5 = 3;
            self->unk6 = 0;
            func_80036B18();
        }
    }
}

void iris_robot_hover(struct MainObj* self)
{
    iris_robot_hover_funcs[self->unk6](self);
}

// iris_robot_hover_chase
INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081718);

void iris_robot_dash(struct MainObj* self)
{
    iris_robot_dash_funcs[self->unk6](self);
}

void iris_robot_dash_land(struct MainObj* self)
{
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk70 & 8) {
        func_80015D60(self, 3);
        self->unk24 = 0;
        self->unk6 = 1;
    }
}

// iris_robot_dash_start
INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800818C4);

void iris_robot_dash_run(struct MainObj* self)
{
    s32 flags;

    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk15 == 0) {
        flags = self->unk70 & 1;
    } else {
        flags = self->unk70 & 2;
    }
    if (flags != 0) {
        func_80015D60(self, 5);
        self->unk6 = 3;
    }
}

void iris_robot_dash_laser(struct MainObj* self)
{
    s32 i;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_8001540C(2, 0xE2, self);
        func_80015D60(self, 6);
        i = 0;
        self->unk20 = 0;
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
INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081AD0);

void iris_robot_release_crystal(struct MainObj* self)
{
    iris_robot_release_crystal_funcs[self->unk6](self);
}

// iris_robot_release_crystal_spawn
INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081BA0);

void iris_robot_release_crystal_wait(struct MainObj* self)
{
    if (self->unk5C >= 0x18) {
        self->ext.main_66.hover_timer = 0xF0;
    } else {
        self->ext.main_66.hover_timer = 0xB4;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void iris_robot_release_crystal_finish(struct MainObj* self)
{
    struct MainObj* crystal;
    s16 timer;
    s16* out_y;
    u16* out_x;
    s32 i;

    if (self->unk7C >= 0x11) {
        func_8002B718(MOVING_OBJECT(self));
    }
    func_80015DC8(ANIMATED_OBJECT(self));

    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk24 = 0;
        self->ext.main_66.partner->ext.main_66.crystal_released = 1;
        func_80015D60(self->ext.main_66.partner, 1);
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
INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081E44);

void iris_crystal_drop(struct MainObj* self)
{
    iris_crystal_drop_funcs[self->unk6](self);
}

void iris_crystal_drop_fall(struct MainObj* self)
{
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi >= 0x1DD) {
        self->y_pos.i.hi = 0x1DC;
        self->unk24 = 0;
        self->unk6 = 1;
    }
}

void iris_crystal_drop_chase(struct MainObj* self)
{
    s16 x_pos;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (!(D_80141BD8.unk0 & 1)) {
        if (self->x_pos.i.hi < g_Player.x_pos.i.hi) {
            self->unk20 = FIXED(4);
        } else {
            self->unk20 = FIXED(-4);
        }
    }

    x_pos = self->x_pos.i.hi;
    if (x_pos - g_Player.x_pos.i.hi >= 0) {
        if (x_pos - g_Player.x_pos.i.hi < 3) {
        } else {
            func_8002B718(MOVING_OBJECT(self));
        }
    } else if (g_Player.x_pos.i.hi - x_pos >= 3) {
        func_8002B718(MOVING_OBJECT(self));
    }

    if (self->ext.main_66.partner->unk6 == 4) {
        self->unk7C = 0x3C;
        self->unk6 = 2;
    }
}

void iris_crystal_drop_aim(struct MainObj* self)
{
    s16 x_pos;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (!(D_80141BD8.unk0 & 1)) {
        if (self->x_pos.i.hi < g_Player.x_pos.i.hi) {
            self->unk20 = FIXED(4);
        } else {
            self->unk20 = FIXED(-4);
        }
    }

    x_pos = self->x_pos.i.hi;
    if (x_pos - g_Player.x_pos.i.hi >= 0) {
        if (x_pos - g_Player.x_pos.i.hi < 3) {
        } else {
            func_8002B718(MOVING_OBJECT(self));
        }
    } else if (g_Player.x_pos.i.hi - x_pos >= 3) {
        func_8002B718(MOVING_OBJECT(self));
    }

    if (--self->unk7C == 0) {
        func_8001540C(2, 0xE2, self);
        func_80015D60(self, 0x11);
        self->unk7C = 0x3C;
        self->unk6 = 3;
    }
}

void iris_crystal_drop_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    u32 timer;
    u8 facing;

    func_80015DC8(ANIMATED_OBJECT(self));
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

    func_80015DC8(ANIMATED_OBJECT(self));
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
        func_80015D60(self, 0x10);
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
