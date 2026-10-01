// ItemObj, item_object_update_funcs[26]
// 800C62DC..800C7164
#include "common.h"

void light_capsule_update(struct ItemObj* self)
{
    struct MainObj* linked_object;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (self->unk2 != 6) {
        if (self->state == 0) {
            func_800C63BC(self);
            return;
        }
        light_capsule_main(self);
        return;
    }
    linked_object = self->unk7C.object;
    if (linked_object->active == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    if (self->state == 0) {
        self->unk68 = &light_capsule_platform_box;
        self->unk75 = 1;
        self->x_pos.i.hi = linked_object->x_pos.i.hi;
        self->y_pos.i.hi = linked_object->y_pos.i.hi - 0x4E;
        self->state++;
    }
    collide_with_players(self);
}

// light_capsule_init
INCLUDE_ASM("main/nonmatchings/items/item_26_light_capsule", func_800C63BC);

void light_capsule_spawn_visual(struct ItemObj* arg0, s8 arg1, s8 arg2)
{
    struct VisualObj* visualObj;

    visualObj = find_free_visual_obj();
    if (visualObj != NULL) {
        visualObj->active = 0x41;
        visualObj->id = arg1;
        visualObj->unk2 = arg2;
        visualObj->bg_offset = arg0->bg_offset;
        visualObj->unk50 = PLAYER_OBJECT(arg0);
    }
}

void light_capsule_main(struct ItemObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x88, 0x88) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        light_capsule_step_funcs[arg0->unk5](arg0);
        collide_with_players(PLAYER_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0x88, 0x88);
        return;
    }
    despawn_object(OBJECT_HEADER(arg0));
}

void light_capsule_wait_player(struct ItemObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s16 dx;
    s16 dy;
    s8 close;

    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0) {
        dx = -dx;
    }
    if (dx <= 0x40) {
        dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
        if (dy > 0) {
            close = dy <= 0x10;
        } else {
            dy = -dy;
            close = dy <= 0x68;
        }
        if (close) {
            set_animation(ANIMATED_OBJECT(arg0), 0xA);
            if (player->x_pos.val - arg0->x_pos.val > 0) {
                player_start_script_action(0x14, 0);
                arg0->unk15 = 0x40;
            } else {
                player_start_script_action(0x14, 0x40);
                arg0->unk15 = 0;
            }
            func_80016F0C();
            func_8001663C(MUSIC_LIGHT_CAPSULE, 0x7F);
            arg0->unk5++;
        }
    }
}

void light_capsule_start_dialogue(struct ItemObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        if (engine_obj.unk37 != 0) {
            func_8002217C(0x35, 0xFF, 0);
        } else {
            func_8002217C(light_capsule_dialogue_ids[arg0->unk2], 0xFF, 0);
        }
        arg0->unk5 = (u8)arg0->unk5 + 1;
    }
}

void light_capsule_wait_dialogue_open(struct ItemObj* arg0)
{
    if (abc_object.unkC == 1) {
        set_animation(arg0, 0xB);
        arg0->unk5++;
    }
}

void light_capsule_wait_dialogue_close(struct ItemObj* arg0)
{
    if (abc_object.unkC == 0) {
        set_animation(arg0, 0xC);
        arg0->unk5++;
    }
}

void light_capsule_end_dialogue(struct ItemObj* arg0)
{
    if (ANIMATED_OBJECT(arg0)->animation_step.fields.event != 0) {
        player_end_script_action();
        func_80016F0C();
        func_800164D8();
        arg0->unk5 = (u8)arg0->unk5 + 1;
    }
}

void light_capsule_wait_enter(struct ItemObj* arg0)
{
    s32 x_pos;

    if ((u8)arg0->unk72 & 8) {
        set_animation(arg0, 1);
        player_start_script_action(0x18, g_Player.unk15);
        light_capsule_spawn_visual(arg0, 0x24, 0);
        x_pos = arg0->x_pos.val;
        g_Player.x_pos.val = x_pos;
        g_Player.item_step = 1;
        arg0->unk5 = (u8)arg0->unk5 + 1;
    }
}

void light_capsule_wait_scan(struct ItemObj* arg0)
{
    if (g_Player.item_step == 2) {
        light_capsule_spawn_visual(arg0, 0x25, 0);
        light_capsule_spawn_visual(arg0, 0x25, 1);
        light_capsule_spawn_visual(arg0, 0x25, 2);
        arg0->unk5 = (u8)arg0->unk5 + 1;
    }
}

void light_capsule_wait_beams(struct ItemObj* arg0)
{
    if (g_Player.item_step == 3) {
        set_animation(arg0, 2);
        arg0->unk7C.item_26_value = 0x14;
        arg0->unk5++;
    }
}

void light_capsule_grant_part(struct ItemObj* arg0)
{
    s32 timer;

    timer = arg0->unk7C.timer;
    if (timer == 0) {
        set_animation(arg0, 1);
        light_capsule_spawn_visual(arg0, 0x26, arg0->unk2);
        arg0->unk5 = (u8)arg0->unk5 + 1;
        return;
    }
    arg0->unk7C.timer = timer - 1;
}

void light_capsule_wait_done(struct ItemObj* arg0)
{
    if (g_Player.item_step == 4) {
        set_animation(arg0, 13);
        arg0->unk5++;
    }
}

void light_capsule_idle(struct ItemObj* arg0)
{
}

void capsule_glass_update(struct VisualObj* arg0)
{
    struct PlayerObj* owner = arg0->unk50;

    if (owner->active == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    } else if (arg0->state == 0) {
        capsule_visual_init(arg0, owner);
        update_on_screen(BASE_OBJECT(arg0), 0x88, 0x88);
    } else if (g_Player.item_step == 1) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    } else {
        animate_object(ANIMATED_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0x88, 0x88);
    }
}

void capsule_scan_update(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a1 = arg0->unk50;
    if (arg0->state == 0) {
        capsule_visual_init(arg0, temp_a1);
        arg0->unk54 = 0x78;
        func_8001540C(2, 0x23, 0);
    } else if (arg0->unk54 == 0) {
        g_Player.item_step = 2;
        stop_sound(2, 0x23);
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    } else {
        animate_object(ANIMATED_OBJECT(arg0));
        arg0->unk54--;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x88, 0x88);
}

void capsule_beam_update(struct VisualObj* self)
{
    struct PlayerObj* owner;

    owner = self->unk50;
    if (self->state == 0) {
        capsule_visual_init(self, owner);
        if (self->unk2 == 1) {
            self->x_pos.i.hi = (u16)self->x_pos.i.hi - 0x58;
        }
        if (self->unk2 == 2) {
            self->unk15 = 0x40;
            self->x_pos.i.hi = (u16)self->x_pos.i.hi + 0x58;
        }
        self->y_pos.i.hi = (u16)self->y_pos.i.hi - 0x6A;
        func_8001540C(2, 0x24, NULL);
    } else if (self->animation_step.fields.relative_step == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.frame_index == 0x24) {
            g_Player.item_step = 3;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x88, 0x88);
}

void capsule_visual_init(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->on_screen = 1;
    arg0->unk3C = arg1->unk3C;
    arg0->animation_table = arg1->animation_table;
    arg0->unk40 = arg1->unk40;
    arg0->unk42 = arg1->unk42;
    arg0->unk15 = 0;
    arg0->x_pos.val = arg1->x_pos.val;
    arg0->y_pos.val = arg1->y_pos.val;
    switch (arg0->id) {
    case 35:
        arg0->unk16 = 3;
        set_animation(arg0, arg0->unk2);
        break;
    case 36:
        arg0->unk16 = 1;
        set_animation(arg0, 7);
        break;
    case 37:
        arg0->unk16 = 0;
        if (arg0->unk2 == 0) {
            set_animation(arg0, 8);
        } else {
            set_animation(arg0, 9);
        }
        break;
    }
    arg0->unk5 = 0;
    arg0->state++;
}

// capsule_part_update
INCLUDE_ASM("main/nonmatchings/items/item_26_light_capsule", func_800C6EDC);

struct Item26AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

u8 light_capsule_terrain_box[4] = { 0, 0, 0x10, 0x0C };
struct Unk_unk68 light_capsule_platform_box = { 0, 0, 0x20, 0x0C };
u8 light_capsule_part_bits[8] = { 1, 2, 4, 4, 8, 0, 0, 0 };
u8 light_capsule_part_visuals[8] = { 3, 4, 5, 5, 6, 0, 0, 0 };

void (*light_capsule_step_funcs[])(struct ItemObj*) = {
    light_capsule_wait_player,
    light_capsule_start_dialogue,
    light_capsule_wait_dialogue_open,
    light_capsule_wait_dialogue_close,
    light_capsule_end_dialogue,
    light_capsule_wait_enter,
    light_capsule_wait_scan,
    light_capsule_wait_beams,
    light_capsule_grant_part,
    light_capsule_wait_done,
    light_capsule_idle,
};

u8 light_capsule_dialogue_ids[8] = { 0x1A, 0x1B, 0x1D, 0x1C, 0x19, 0, 0, 0 };
u8 light_capsule_part_animations[8] = { 0, 1, 2, 2, 3, 0, 0, 0 };

struct Item26AnimationStep light_capsule_anim_0[1] = {
    { 96, 0, 0, 0 },
};

struct Item26AnimationStep D_8010D420[5] = {
    { 8, 0, 1, 0 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 10 },
    { 96, 0, 0, 1 },
};

struct Item26AnimationStep light_capsule_anim_1[2] = {
    { 2, 0, 1, 28 },
    { 2, 0, 255, 1 },
};

struct Item26AnimationStep light_capsule_anim_2[2] = {
    { 2, 0, 1, 29 },
    { 2, 0, 255, 28 },
};

struct Item26AnimationStep light_capsule_anim_13[1] = {
    { 96, 0, 0, 1 },
};

struct Item26AnimationStep light_capsule_anim_3[4] = {
    { 8, 0, 1, 2 },
    { 10, 0, 1, 3 },
    { 12, 0, 1, 2 },
    { 20, 0, 253, 4 },
};

struct Item26AnimationStep light_capsule_anim_4[4] = {
    { 8, 0, 1, 12 },
    { 10, 0, 1, 13 },
    { 12, 0, 1, 12 },
    { 20, 0, 253, 14 },
};

struct Item26AnimationStep light_capsule_anim_5[4] = {
    { 8, 0, 1, 18 },
    { 10, 0, 1, 19 },
    { 12, 0, 1, 18 },
    { 20, 0, 253, 20 },
};

struct Item26AnimationStep light_capsule_anim_6[4] = {
    { 8, 0, 1, 15 },
    { 10, 0, 1, 16 },
    { 12, 0, 1, 15 },
    { 20, 0, 253, 17 },
};

struct Item26AnimationStep light_capsule_anim_7[6] = {
    { 2, 0, 1, 27 },
    { 2, 0, 1, 26 },
    { 2, 0, 1, 25 },
    { 2, 0, 1, 24 },
    { 2, 0, 1, 23 },
    { 2, 0, 251, 22 },
};

struct Item26AnimationStep light_capsule_anim_8[15] = {
    { 1, 0, 1, 30 },
    { 1, 0, 1, 31 },
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, 1, 34 },
    { 1, 0, 1, 35 },
    { 1, 0, 1, 36 },
    { 1, 0, 1, 37 },
    { 1, 0, 1, 38 },
    { 1, 0, 1, 39 },
    { 1, 0, 1, 40 },
    { 1, 0, 1, 41 },
    { 1, 0, 1, 42 },
    { 1, 0, 1, 43 },
    { 96, 0, 0, 43 },
};

struct Item26AnimationStep light_capsule_anim_9[15] = {
    { 1, 0, 1, 44 },
    { 1, 0, 1, 45 },
    { 1, 0, 1, 46 },
    { 1, 0, 1, 47 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 49 },
    { 1, 0, 1, 50 },
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, 1, 57 },
    { 96, 0, 0, 57 },
};

struct Item26AnimationStep light_capsule_anim_10[38] = {
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 1, 1, 6 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 6 },
    { 2, 0, 255, 0 },
};

struct Item26AnimationStep light_capsule_anim_11[14] = {
    { 1, 0, 1, 7 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 7 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 7 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 7 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 6 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 6 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 6 },
    { 1, 0, 243, 0 },
};

struct Item26AnimationStep light_capsule_anim_12[39] = {
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 8, 0, 1, 0 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 10 },
    { 1, 1, 1, 1 },
    { 96, 0, 0, 1 },
};

struct Item26AnimationStep* light_capsule_animations[14] = {
    light_capsule_anim_0,
    light_capsule_anim_1,
    light_capsule_anim_2,
    light_capsule_anim_3,
    light_capsule_anim_4,
    light_capsule_anim_5,
    light_capsule_anim_6,
    light_capsule_anim_7,
    light_capsule_anim_8,
    light_capsule_anim_9,
    light_capsule_anim_10,
    light_capsule_anim_11,
    light_capsule_anim_12,
    light_capsule_anim_13,
};
