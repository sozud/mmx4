// MiscObj, misc_object_update_funcs[52]
// 800D2190..800D2A74
#include "common.h"

extern void (*npc_cutscene_type_funcs[])(struct MiscObj*);

// npc_cutscene_init
INCLUDE_ASM("main/nonmatchings/misc/misc_52_npc_cutscene", func_800D2190);

void npc_cutscene_talk_wait_player(struct MiscObj* self)
{
    if (self->unk6 == 0) {
        if (g_Player.x_pos.i.hi >= 0x911) {
            self->unk6++;
            background_objects[0].unk26 = 0x8C0;
            player_start_script_action(0x14, 0x40);
        }
    } else if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        self->unk6 = 0;
        self->ext.misc_52.timer = 0x1E;
        self->unk5++;
    }
}

void npc_cutscene_talk_line(struct MiscObj* self)
{
    u8 timer = self->ext.misc_52.timer;

    if (timer == 0) {
        self->unk5++;
        func_8002217C(engine_obj.cur_character == 0 ? 0x2B : 0x23, 0xFF, 0);
    } else {
        self->ext.misc_52.timer = timer - 1;
    }

    self->on_screen = 0;
    if (D_80141BD8.unk0 & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void npc_cutscene_talk_wait_line(struct MiscObj* self)
{
    if (abc_object.unkC == 0) {
        self->state = 2;
        self->unk6 = 0;
        self->ext.misc_52.timer = 0x1E;
        if (engine_obj.cur_character == 0) {
            self->unk5 = 0;
        } else {
            self->unk5 = 1;
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void npc_cutscene_talk(struct MiscObj* self)
{
    npc_cutscene_talk_funcs[self->unk5](self);
    animate_object(ANIMATED_OBJECT(self));
}

void npc_cutscene_reply(struct MiscObj* obj)
{
    s8 state;
    u8 timer;

    if (D_80141BDC[0] == 0) {
        state = obj->unk5;
        switch (state) {
        case 0:
            timer = obj->ext.misc_52.timer - 1;
            obj->ext.misc_52.timer = timer;
            if (timer == 0) {
                obj->unk5++;
            }
            break;
        case 1:
            obj->unk5 = state + 1;
            func_8002217C(0x24, 0xFF, 0);
            break;
        case 2:
            if (abc_object.unkC == 0) {
                obj->state = 2;
                obj->unk5 = 2;
                obj->unk6 = 0;
                obj->ext.misc_52.timer = 0x1E;
            }
            break;
        }
        animate_object(ANIMATED_OBJECT(obj));
    }
    is_on_screen(BASE_OBJECT(obj));
}

// npc_cutscene_listen
INCLUDE_ASM("main/nonmatchings/misc/misc_52_npc_cutscene", func_800D26F4);

void npc_cutscene_main(struct MiscObj* self)
{
    npc_cutscene_type_funcs[self->unk2](self);
    if (D_80141BD8.unk0 % 10 == 0) {
        self->y_pos.i.hi += self->ext.misc_52.unk57;
        if (--self->ext.misc_52.unk56 == 0) {
            self->ext.misc_52.unk56 = 7;
            self->ext.misc_52.unk57 *= -1;
        }
    }
}

void npc_cutscene_blink(struct MiscObj* self)
{
    u8 timer;

    timer = self->ext.misc_52.timer;
    if (timer == 0) {
        self->ext.misc_52.timer = 0x1E;
        self->unk6++;
    } else {
        self->ext.misc_52.timer = timer - 1;
    }
    self->on_screen = 0;
    if (D_80141BD8.unk0 & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void npc_cutscene_fade_out(struct MiscObj* self)
{
    u8 timer = self->ext.misc_52.timer;
    self->on_screen = 0;
    timer--;
    self->ext.misc_52.timer = timer;
    if (timer == 0) {
        engine_obj.unkF = 0x40;
    }
}

void npc_cutscene_finish_fade(struct MiscObj* self)
{
    npc_cutscene_finish_fade_funcs[self->unk6](self);
}

void npc_cutscene_finish_wait(struct MiscObj* self)
{
    u8 timer;

    is_on_screen(BASE_OBJECT(self));
    timer = self->ext.misc_52.timer - 1;
    self->ext.misc_52.timer = timer;
    if (timer == 0) {
        engine_obj.unkF = 0x40;
    }
}

void npc_cutscene_leave(struct MiscObj* self)
{
    u8 timer;

    self->on_screen = 0;
    timer = self->ext.misc_52.timer - 1;
    self->ext.misc_52.timer = timer;
    if (timer == 0) {
        player_end_script_action();
        despawn_object_permanently(OBJECT_HEADER(self));
    }
}

void npc_cutscene_finish_leave(struct MiscObj* self)
{
    npc_cutscene_finish_leave_funcs[self->unk6](self);
}

void npc_cutscene_finish(struct MiscObj* self)
{
    npc_cutscene_finish_funcs[self->unk5](self);
}

void npc_cutscene_update(struct MiscObj* self)
{
    npc_cutscene_state_funcs[self->state](self);
}

union AnimationStep npc_cutscene_anim_0[5] = {
    { .packed = 0x0001003A },
    { .packed = 0x04010008 },
    { .packed = 0x05010021 },
    { .packed = 0x04010008 },
    { .packed = 0x00FC003A },
};

union AnimationStep npc_cutscene_anim_1[3] = {
    { .packed = 0x01010001 },
    { .packed = 0x02010001 },
    { .packed = 0x03FE0001 },
};

union AnimationStep* npc_cutscene_animations[2] = { npc_cutscene_anim_0, npc_cutscene_anim_1 };

void (*npc_cutscene_talk_funcs[3])(struct MiscObj*) = {
    npc_cutscene_talk_wait_player,
    npc_cutscene_talk_line,
    npc_cutscene_talk_wait_line,
};
void (*npc_cutscene_type_funcs[4])(struct MiscObj*) = {
    npc_cutscene_talk,
    npc_cutscene_reply,
    func_800D26F4,
    func_800D26F4,
};
void (*npc_cutscene_finish_fade_funcs[2])(struct MiscObj*) = { npc_cutscene_blink, npc_cutscene_fade_out };
void (*npc_cutscene_finish_leave_funcs[2])(struct MiscObj*) = { npc_cutscene_blink, npc_cutscene_leave };
void (*npc_cutscene_finish_funcs[3])(struct MiscObj*) = {
    npc_cutscene_finish_fade,
    npc_cutscene_finish_wait,
    npc_cutscene_finish_leave,
};
void (*npc_cutscene_state_funcs[3])(struct MiscObj*) = {
    func_800D2190,
    npc_cutscene_main,
    npc_cutscene_finish,
};
