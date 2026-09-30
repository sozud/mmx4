// ShotObj, shot_object_update_funcs[23]
// 8009DD40..8009E0B8
#include "common.h"

void web_thread_update(struct ShotObj* self)
{
    web_thread_state_funcs[self->state](self);
}

void web_thread_init(struct ShotObj* self)
{
    self->state = 1;
    self->on_screen = 1;
    self->unk16 = 5;
    self->timer = -0x32;
    if (self->unk2 != 0) {
        self->unk5 = 2;
    } else {
        self->unk5 = 0;
        self->unk84.value = 0;
    }
    self->unk54 = web_thread_hit_box;
    self->unk50.data = web_thread_hit_box;
    self->unk68 = NULL;
    self->unk58.data = web_thread_collision[0];
    self->unk5C = 3;
    self->unk60 = 3;
    self->unk61 = 0;
    set_animation(self, 0x13);
}

void web_thread_main(struct ShotObj* self)
{
    struct MainObj* owner = MAIN_OBJECT(self->unk7C);
    s32 hit;

    self->x_pos.val = owner->x_pos.val + self->unk84.value;
    self->y_pos.val = owner->y_pos.val;
    self->y_pos.i.hi += self->timer;
    if (owner->ext.main_43.flash_timer != 0) {
        self->unk61 = 1;
    }
    if (owner->state == 2) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    web_thread_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    hit = 0;
    if (owner->ext.main_43.hurt_collision == 0 && owner->ext.main_43.big_web_done == 0) {
        hit = func_8002DD04(MAIN_OBJECT(self));
    }
    if (self->unk61 != 0) {
        self->unk61--;
    } else if (hit != 0) {
        self->unk5 = 1;
        set_animation(self, 0x14);
        owner->unk5 = 1;
        owner->unk6 = 0;
        self->unk61 = 0x1E;
    }
    is_on_screen(BASE_OBJECT(self));
}

void web_thread_idle(struct ShotObj* self)
{
    animate_object(self);
}

void web_thread_snap(struct ShotObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk7C->unk80.word = 0;
    }
    animate_object(self);
}

void web_thread_pulse(struct ShotObj* self)
{
    struct VisualObj* visual;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        set_animation(self, 0x12);
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = (s8)(u8)self->active;
            visual->id = 0x14;
            visual->unk2 = 0;
            visual->x_pos.val = self->x_pos.val;
            visual->y_pos.val = self->y_pos.val;
            visual->animation_table = self->animation_table;
            visual->unk40 = self->unk40;
            visual->unk3C = self->unk3C;
            visual->unk42 = self->unk42 & 0x7FFF;
            visual->unk16 = self->unk16;
            visual->unk15 = self->unk15;
            visual->unk50 = PLAYER_OBJECT(self);
        }
    } else {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk5 = 0;
            self->unk6 = 0;
            self->unk2 = 0;
            set_animation(self, 0x13);
        }
        animate_object(ANIMATED_OBJECT(self));
    }
}

void web_thread_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

u8 web_thread_hit_box[4] = { 0xFC, 0x82, 0x07, 0x9B };

u8 web_thread_collision[32][4] = {
    { 2, 1, 2, 0 },
    { 2, 0, 2, 2 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 0, 0, 2, 1 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 0, 0 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 1 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 1, 2, 1 },
    { 2, 0x7F, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
};

void (*web_thread_state_funcs[])(struct ShotObj*) = {
    web_thread_init,
    web_thread_main,
    web_thread_despawn,
};

void (*web_thread_step_funcs[3])(struct ShotObj*) = {
    web_thread_idle,
    web_thread_snap,
    web_thread_pulse,
};
