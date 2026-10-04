// MiscObj, misc_object_update_funcs[46]
// 800D1284..800D1990
#include "common.h"

void post_boss_cutscene_update(struct MiscObj* self)
{
    post_boss_cutscene_state_funcs[self->state](self);
}

// post_boss_cutscene_init
INCLUDE_ASM("main/nonmatchings/misc/misc_46_post_boss_cutscene", func_800D12C0);

void post_boss_cutscene_main(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    post_boss_cutscene_step_funcs[self->unk5](UNK_OBJECT(self));
    if (self->unk5 < 8) {
        update_on_screen(BASE_OBJECT(self), 0x48, 0x48);
    }
}

void post_boss_cutscene_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void post_boss_cutscene_wait_scroll(struct UnkObj* self)
{
    if (background_objects[g_Player.bg_offset].x_pos.i.hi == g_Player.x_pos.i.hi - 0x30) {
        self->ext.timer = 0x3C;
        self->unk5 = 1;
    }
}

void post_boss_cutscene_arrive(struct UnkObj* self)
{
    s8 timer;

    timer = self->ext.timer - 1;
    self->ext.timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x2A, self);
        self->unk4B = 1;
        self->unk5 = 2;
    }
}

void post_boss_cutscene_fly_in(struct UnkObj* self)
{
    move_object(MOVING_OBJECT(self));
    if (self->x_pos.i.hi < background_objects[g_Player.bg_offset].x_pos.i.hi + 0x134) {
        self->unk5 = 3;
    }
}

void post_boss_cutscene_stop(struct UnkObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->x_vel.val > 0) {
        self->unk4B = -1;
        set_animation(self, 0);
        self->ext.timer = 0x1E;
        self->unk5 = 4;
    }
}

void post_boss_cutscene_first_line(struct UnkObj* self)
{
    if (--self->ext.timer != 0) {
        return;
    }
    if (engine_obj.cur_character == 0) {
        func_8002217C(0x1F, 1, 0);
        self->unk5 = 5;
    } else {
        func_8002217C(0x1A, 3, 0);
        self->unk5 = 5;
    }
}

void post_boss_cutscene_wait_first(struct UnkObj* self)
{
    if (abc_object.unkC == 0) {
        self->ext.timer = 0x1E;
        self->unk5 = 6;
    }
}

void post_boss_cutscene_shake_start(struct UnkObj* self)
{
    s8 timer;

    timer = self->ext.timer - 1;
    self->ext.timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x2A, self);
        self->x_vel.val = 0;
        self->unk28 = FIXED(1);
        set_animation(self, 1);
        self->ext.timer = 0x20;
        self->unk5 = 7;
    }
}

void post_boss_cutscene_shake(struct UnkObj* self)
{
    if (--self->ext.timer == 0) {
        self->ext.timer = 0x3C;
        self->on_screen = 0;
        self->unk5 = 8;
        return;
    }
    self->x_vel.val = self->x_vel.val + self->unk28;
    if (SHAKE_ENABLED) {
        if (BLINK_CLOCK(self->ext.timer) & 1) {
            self->x_pos.val += self->x_vel.val;
        } else {
            self->x_pos.val -= self->x_vel.val;
        }
    }
}

void post_boss_cutscene_second_line(struct UnkObj* self)
{
    self->ext.timer -= 1;
    if (self->ext.timer == 0) {
        if (engine_obj.cur_character == 0) {
            func_8002217C(0x30, 2, 0);
            self->unk5 = 9;
        } else {
            func_8002217C(0x2B, 4, 0);
            self->unk5 = 9;
        }
    }
}

void post_boss_cutscene_wait_second(struct UnkObj* self)
{
    if (abc_object.unkC == 0) {
        self->ext.timer = 0x3C;
        self->unk5 = 10;
    }
}

void post_boss_cutscene_finish(struct UnkObj* self)
{
    if (--self->ext.timer == 0) {
        engine_obj.unkF = 1;
        self->state = 2;
    }
}

void post_boss_cutscene_spawn_afterimages(struct UnkObj* self)
{
    u8 var_s1;
    struct VisualObj* temp_v0;
    struct VisualObj* var_s2;

    var_s1 = 0;
    do {
        temp_v0 = func_8002AF4C(NULL, 1);
        if (temp_v0 != 0) {
            temp_v0->active = 0x41;
            temp_v0->id = 5;
            temp_v0->unk2 = var_s1;
            temp_v0->bg_offset = g_Player.bg_offset;
            temp_v0->unk40 = (u16)self->unk40;
            temp_v0->unk3C = self->unk3C;
            temp_v0->animation_table = self->animation_table;
            temp_v0->unk42 = (u16)self->unk42;
            temp_v0->unk16 = 6;
            temp_v0->unk5C.owner = PLAYER_OBJECT(self);
            if (var_s1 & 0xFF) {
                temp_v0->unk50 = PLAYER_OBJECT(var_s2);
            } else {
                temp_v0->unk50 = PLAYER_OBJECT(self);
            }
        }
        var_s1 += 1;
        var_s2 = temp_v0;
    } while ((u32)(var_s1 & 0xFF) < 3U);
}

union AnimationStep D_8010F194[1] = {
    { 0x00000101 },
};

union AnimationStep D_8010F198[1] = {
    { 0x01000101 },
};

union AnimationStep* D_8010F19C[2] = {
    D_8010F194,
    D_8010F198,
};

void (*post_boss_cutscene_state_funcs[3])(struct MiscObj*) = {
    func_800D12C0,
    post_boss_cutscene_main,
    post_boss_cutscene_despawn,
};

void (*post_boss_cutscene_step_funcs[11])(struct UnkObj*) = {
    post_boss_cutscene_wait_scroll,
    post_boss_cutscene_arrive,
    post_boss_cutscene_fly_in,
    post_boss_cutscene_stop,
    post_boss_cutscene_first_line,
    post_boss_cutscene_wait_first,
    post_boss_cutscene_shake_start,
    post_boss_cutscene_shake,
    post_boss_cutscene_second_line,
    post_boss_cutscene_wait_second,
    post_boss_cutscene_finish,
};
