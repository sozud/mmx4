// MiscObj, misc_object_update_funcs[52]
// 800D2190..800D2A74
#include "common.h"
#include "main/misc/misc_52_npc_cutscene.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/55C4.h"
#include "main/objects.h"

// npc_cutscene_talk_funcs
extern void (*npc_cutscene_talk_funcs[])(struct MiscObj*);

// npc_cutscene_type_funcs
void npc_cutscene_talk(struct MiscObj* arg0);
void npc_cutscene_reply(struct MiscObj*);
void func_800D26F4(struct MiscObj*);
void func_800D26F4(struct MiscObj*);

// npc_cutscene_finish_fade_funcs
extern void (*npc_cutscene_finish_fade_funcs[])(struct MiscObj*);
void npc_cutscene_blink(struct MiscObj*);

// npc_cutscene_finish_leave_funcs
extern void (*npc_cutscene_finish_leave_funcs[])(struct MiscObj*);
void npc_cutscene_leave(struct MiscObj*);

// npc_cutscene_finish_funcs
extern void (*npc_cutscene_finish_funcs[])(struct MiscObj*);
void npc_cutscene_finish_fade(struct MiscObj*);

void npc_cutscene_finish_leave(struct MiscObj*);

// npc_cutscene_state_funcs
extern void (*npc_cutscene_state_funcs[])(struct MiscObj*);
void func_800D2190(struct MiscObj*);
void npc_cutscene_main(struct MiscObj*);
void npc_cutscene_finish(struct MiscObj*);
#include "weapon_resources.h"

extern void (*npc_cutscene_type_funcs[])(struct MiscObj*);

// npc_cutscene_init
#ifdef MMX4_SATURN
#define NPC_RESOURCE 0xA5
#define NPC_LAYER 0x42
#define NPC_LISTENER 2
#define NPC_LISTENER_ID 0x34
#define NPC_SEEN 8
#define NPC_TALKED 9
#define NPC_BOB_PERIOD 7
#define NPC_TALK_DELAY 30

extern union AnimationStep* npc_cutscene_animations[];
#define NPC_SCRIPT_ACTION 20
#define NPC_SCRIPT_ARG 16

void func_800D2190(struct MiscObj* self)
{
    struct MiscObj* listener;
    u8 resource;

    if (self->unk2 != NPC_LISTENER) {
        if (engine_obj.substage == 0) {
            engine_obj.character_state.bytes[NPC_SEEN] = 0;
            engine_obj.character_state.bytes[NPC_TALKED] = 0;
        } else if (engine_obj.substage == 1) {
            if (engine_obj.character_state.bytes[NPC_SEEN] != 0) {
                ZeroObjectState(OBJECT_HEADER(self));
                return;
            }
            engine_obj.character_state.bytes[NPC_SEEN] = 1;
        }
    }
    self->state++;
    self->bg_offset = g_Player.bg_offset;
    self->unk16 = NPC_LAYER;
    self->animation_table = (u32**)npc_cutscene_animations;
    self->unk15 = 0;
    resource = func_8002938C(NPC_RESOURCE);
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    self->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(NPC_RESOURCE));
    self->unk42 = OBJECT_STAGE_CLUT(NPC_RESOURCE);
    self->ext.misc_52.unk56 = NPC_BOB_PERIOD;
    self->ext.misc_52.unk57 = 1;
    switch (self->unk2) {
    case 0:
        self->x_pos.i.hi = 0x9A0;
        self->y_pos.i.hi = 0x998;
        set_animation(self, 0);
        break;
    case 1:
        player_start_script_action(NPC_SCRIPT_ACTION, NPC_SCRIPT_ARG);
        self->x_pos.i.hi = 0x2A0;
        self->y_pos.i.hi = 0x198;
        set_animation(self, 0);
        self->ext.misc_52.timer = NPC_TALK_DELAY;
        break;
    case NPC_LISTENER:
        set_animation(self, 1);
        break;
    }
    if (self->unk2 == NPC_LISTENER) {
        return;
    }
    listener = find_free_misc_obj();
    if (listener != NULL) {
        listener->active = 0x41;
        listener->id = NPC_LISTENER_ID;
        listener->unk2 = NPC_LISTENER;
        listener->ext.misc_52.parent = self;
        listener->unk40 = self->unk40;
        listener->unk3C = self->unk3C;
        listener->unk42 = self->unk42;
        listener->x_pos.i.hi = self->x_pos.i.hi;
        listener->y_pos.i.hi = self->y_pos.i.hi;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_52_npc_cutscene", func_800D2190);
#endif

void npc_cutscene_talk_wait_player(struct MiscObj* self)
{
    if (self->unk6 == 0) {
        if (g_Player.x_pos.i.hi > 0x910) {
            self->unk6++;
            background_objects[0].unk26 = 0x8C0;
            player_start_script_action(0x14, PLAYER_FACING_RIGHT);
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
        if (engine_obj.cur_character == 0) {
            func_8002217C(0x2B, 0xFF, 0);
        } else {
            func_8002217C(0x23, 0xFF, 0);
        }
    } else {
        self->ext.misc_52.timer = timer - 1;
    }

    self->on_screen = 0;
    if (BLINK_CLOCK(WEAPON_FRAME_COUNTER) & 1) {
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

    if (main_bss_state.transition.active == 0) {
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
#ifdef MMX4_SATURN
void func_800D26F4(struct MiscObj* self)
{
    struct MiscObj* parent = self->ext.misc_52.parent;

    if (self->unk5 != 0) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    self->x_pos.i.hi = parent->x_pos.i.hi;
    self->y_pos.i.hi = parent->y_pos.i.hi;
    self->on_screen = 0;
    if (parent->on_screen != 0)
        is_on_screen(BASE_OBJECT(self));
    if (parent->active == 0)
        self->unk5++;
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_52_npc_cutscene", func_800D26F4);
#endif

void npc_cutscene_main(struct MiscObj* self)
{
    npc_cutscene_type_funcs[self->unk2](self);
    if (WEAPON_FRAME_COUNTER % 10 == 0) {
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
    if (BLINK_CLOCK(WEAPON_FRAME_COUNTER) & 1) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void npc_cutscene_fade_out(struct MiscObj* self)
{
    self->on_screen = 0;
    if (--self->ext.misc_52.timer == 0) {
        engine_obj.unkF = 0x40;
    }
}

void npc_cutscene_finish_fade(struct MiscObj* self)
{
    npc_cutscene_finish_fade_funcs[self->unk6](self);
}

void npc_cutscene_finish_wait(struct MiscObj* self)
{
    is_on_screen(BASE_OBJECT(self));
    if (--self->ext.misc_52.timer == 0) {
        engine_obj.unkF = 0x40;
    }
}

void npc_cutscene_leave(struct MiscObj* self)
{
    self->on_screen = 0;
    if (--self->ext.misc_52.timer == 0) {
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
    { 58, 0, 1, 0x00 },
    { 8, 0, 1, 0x04 },
    { 33, 0, 1, 0x05 },
    { 8, 0, 1, 0x04 },
    { 58, 0, -4, 0x00 },
};

union AnimationStep npc_cutscene_anim_1[3] = {
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x02 },
    { 1, 0, -2, 0x03 },
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
