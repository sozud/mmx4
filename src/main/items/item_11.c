// ItemObj, item_object_update_funcs[11]
// 800C2BE0..800C3224
#include "common.h"

struct Item11AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item11AnimationStep teleporter_anim_0[1] = {
    { 1, 0, 0, 0 },
};

struct Item11AnimationStep teleporter_anim_1[4] = {
    { 1, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 2, 0, 1, 0 },
    { 1, 0, 253, 2 },
};

struct Item11AnimationStep teleporter_anim_2[19] = {
    { 1, 0, 1, 13 },
    { 1, 0, 1, 14 },
    { 1, 0, 1, 15 },
    { 1, 0, 1, 16 },
    { 1, 0, 1, 17 },
    { 1, 0, 1, 18 },
    { 1, 0, 1, 22 },
    { 1, 0, 1, 23 },
    { 1, 0, 1, 24 },
    { 1, 0, 1, 25 },
    { 1, 0, 1, 26 },
    { 1, 0, 1, 27 },
    { 1, 0, 1, 28 },
    { 1, 0, 1, 29 },
    { 1, 0, 1, 30 },
    { 1, 0, 1, 31 },
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, 238, 34 },
};

struct Item11AnimationStep teleporter_anim_3[18] = {
    { 1, 0, 1, 19 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 20 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 20 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 21 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 21 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 12 },
    { 1, 0, 1, 3 },
    { 1, 1, 0, 4 },
};

struct Item11AnimationStep teleporter_anim_4[32] = {
    { 1, 0, 1, 3 },
    { 1, 0, 1, 5 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 5 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 6 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 6 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 7 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 7 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 8 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 9 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 9 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 10 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 10 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 11 },
    { 1, 0, 1, 4 },
    { 1, 0, 1, 11 },
    { 1, 0, 1, 3 },
    { 1, 0, 1, 12 },
    { 1, 0, 1, 4 },
    { 1, 0, 225, 12 },
};

struct Item11AnimationStep* teleporter_animations[5] = {
    teleporter_anim_0,
    teleporter_anim_1,
    teleporter_anim_2,
    teleporter_anim_3,
    teleporter_anim_4,
};

void teleporter_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    teleporter_state_funcs[arg0->state](arg0);
    collide_with_players(arg0);
}

// teleporter_init
INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2C3C);

void teleporter_main(struct ItemObj* arg0)
{
    teleporter_step_funcs[arg0->unk5](arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 2;
}

void teleporter_despawn(struct ItemObj* arg0)
{
    despawn_object(OBJECT_HEADER(arg0));
}

void teleporter_idle(struct ItemObj* arg0)
{
    is_on_screen(BASE_OBJECT(arg0));
}

void teleporter_wait_player(struct ItemObj* arg0)
{
    if ((u8)arg0->unk72 & 8) {
        g_Player.x_pos.u.hi = arg0->x_pos.u.hi;
        g_Player.y_pos.i.hi = ((u16)arg0->y_pos.i.hi - arg0->unk68->unk3) - g_Player.unk68->unk3;
        player_start_script_action(0x14, g_Player.unk15);
        reset_main_and_shots();
        arg0->unk5 = 1;
    }
}

void teleporter_activate(struct ItemObj* arg0)
{
    if (g_Player.script_state < 0) {
        arg0->tail_ext.unk1.unk84.timer = 0;
        background_objects[0].unk26 = background_objects[0].x_pos.u.hi;
        background_objects[0].unk24 = background_objects[0].x_pos.u.hi;
        set_animation(arg0, 1);
        arg0->unk5 = 2;
        func_8001540C(5, 0, NULL);
    }
}

void teleporter_warp(struct ItemObj* arg0)
{
    teleporter_warp_funcs[arg0->unk6](arg0);
}

void teleporter_spawn_beam(struct ItemObj* arg0)
{
    struct MiscObj* slot;
    void* sprite_frames;
    s8 bg_off;

    if (++arg0->tail_ext.unk1.unk84.timer == 0x60) {
        slot = find_free_misc_obj();
        if (slot == NULL) {
            return;
        }
        slot->active = 0x41;
        slot->id = 0xB;
        slot->unk2 = 1;
        bg_off = g_Player.bg_offset;
        slot->unk16 = 1;
        slot->bg_offset = bg_off;
        slot->unk15 = arg0->unk15;
        slot->unk40 = arg0->unk40;
        slot->unk42 = arg0->unk42;
        sprite_frames = (void*)arg0->sprite_frames;
        slot->animation_table = (u32**)teleporter_animations;
        slot->unk3C = sprite_frames;
        slot->x_pos.val = arg0->x_pos.val;
        slot->y_pos.val = arg0->y_pos.val;
        slot->ext.misc_11.active = 0;
        arg0->unk7C.misc = slot;
        arg0->tail_ext.unk1.unk84.timer = 0;
        arg0->unk6++;
    }
}

void teleporter_spawn_glow(struct ItemObj* arg0)
{
    struct MiscObj* slot;
    void* sprite_frames;

    if (++arg0->tail_ext.unk1.unk84.timer == 0x60) {
        slot = find_free_misc_obj();
        if (slot == NULL) {
            return;
        }
        slot->active = 0x41;
        slot->id = 0xB;
        slot->unk2 = 2;
        slot->unk16 = 0x10;
        slot->bg_offset = g_Player.bg_offset;
        slot->unk15 = arg0->unk15;
        slot->unk40 = arg0->unk40;
        slot->unk42 = arg0->unk42;
        sprite_frames = (void*)arg0->sprite_frames;
        slot->animation_table = (u32**)teleporter_animations;
        slot->unk3C = sprite_frames;
        slot->x_pos.val = arg0->x_pos.val;
        slot->y_pos.val = arg0->y_pos.val;
        slot->ext.misc_11.active = 0;
        arg0->ext.owner = (struct MainObj*)slot;
        arg0->tail_ext.unk1.unk84.timer = 0;
        arg0->unk6++;
    }
}

void teleporter_wait_flash(struct ItemObj* arg0)
{
    struct MainObj* owner;

    owner = arg0->ext.owner;
    if (owner->animation_step.fields.event == 1) {
        set_animation(owner, 4);
        arg0->unk7C.misc->ext.misc_11.active = 1;
        arg0->tail_ext.unk1.unk84.timer = 0;
        player_start_script_action(0x16, g_Player.unk15);
        func_8001540C(5, 1, NULL);
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void teleporter_delay(struct ItemObj* arg0)
{
    if (++arg0->tail_ext.unk1.unk84.timer == 0x32) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void teleporter_finish(struct ItemObj* arg0)
{
    u8 checkpoint;

    if (g_Player.script_state < 0) {
        player_end_script_action();
        checkpoint = arg0->unk2;
        engine_obj.unkF = -0x40;
        engine_obj.checkpoint = checkpoint & 0xF;
        arg0->state = 3;
        arg0->unk5 = 0;
    }
}

void (*teleporter_state_funcs[])(struct ItemObj*) = {
    func_800C2C3C,
    teleporter_main,
    teleporter_despawn,
    teleporter_idle,
};

void (*teleporter_step_funcs[])(struct ItemObj*) = {
    teleporter_wait_player,
    teleporter_activate,
    teleporter_warp,
    teleporter_finish,
};

u8 teleporter_terrain_box[4] = { 0, 0, 0x1C, 8 };

void (*teleporter_warp_funcs[])(struct ItemObj*) = {
    teleporter_spawn_beam,
    teleporter_spawn_glow,
    teleporter_wait_flash,
    teleporter_delay,
};
