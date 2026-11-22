// ItemObj, item_object_update_funcs[11]
// 800C2BE0..800C3224
#include "common.h"
#include "main/items/item_11_teleporter.h"
#include "main/objects.h"
#include "main/player_common.h"
#include "main/1E1BC.h"
#include "main/55C4.h"

// teleporter_state_funcs
extern void (*teleporter_state_funcs[])(struct ItemObj*);
void func_800C2C3C(struct ItemObj*);
void teleporter_main(struct ItemObj*);
void teleporter_despawn(struct ItemObj*);
void teleporter_idle(struct ItemObj*);

// teleporter_step_funcs
extern void (*teleporter_step_funcs[])(struct ItemObj*);
void teleporter_wait_player(struct ItemObj*);
#ifdef VERSION_DEMO
s8 func_800A6114_demo(struct ItemObj*, struct PlayerObj*);
#endif
void teleporter_activate(struct ItemObj*);
void teleporter_warp(struct ItemObj*);
void teleporter_finish(struct ItemObj*);

// teleporter_warp_funcs
extern void (*teleporter_warp_funcs[])(struct ItemObj*);
void teleporter_spawn_beam(struct ItemObj*);
void teleporter_spawn_glow(struct ItemObj*);
void teleporter_wait_flash(struct ItemObj*);
void teleporter_delay(struct ItemObj*);
#include "weapon_resources.h"

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
void func_800C2C3C(struct ItemObj* arg0)
{
    arg0->active = 0x41;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->unk15 = 0;
    arg0->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x88));
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x88)];
    arg0->unk42 = VISUAL_STAGE_PALETTE(func_8002938C(0x88));
    arg0->animation_table = (const u8* const*)teleporter_animations;
    arg0->unk67 = 0;
    arg0->unk75 = 0;
    arg0->unk68 = (struct Unk_unk68*)teleporter_terrain_box;
    set_animation(ANIMATED_OBJECT(arg0), 0);
    if (arg0->unk2 & 0x80) {
        arg0->state = 3;
        arg0->unk5 = 0;
    } else {
        arg0->state = 1;
        arg0->unk5 = 0;
    }
    arg0->unk6 = 0;
}

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
    if (DEMO_ALT((u8)arg0->unk72 & 8, func_800A6114_demo(arg0, &g_Player))) {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi;
        g_Player.y_pos.i.hi = (arg0->y_pos.i.hi - arg0->unk68->unk3) - g_Player.unk68->unk3;
        player_start_script_action(0x14, g_Player.unk15);
        reset_main_and_shots();
        arg0->unk5 = 1;
    }
}

void teleporter_activate(struct ItemObj* arg0)
{
    if (g_Player.script_state < 0) {
        arg0->tail_ext.unk1.unk84.timer = 0;
        background_objects[0].unk26 = background_objects[0].x_pos.i.hi;
        background_objects[0].unk24 = background_objects[0].x_pos.i.hi;
        set_animation(arg0, 1);
        arg0->unk5 = 2;
        func_8001540C(5, SATURN_SOUND(0, 0x29), NULL);
    }
}

void teleporter_warp(struct ItemObj* arg0)
{
    teleporter_warp_funcs[arg0->unk6](arg0);
}

void teleporter_spawn_beam(struct ItemObj* arg0)
{
    struct MiscObj* slot;

    if (++arg0->tail_ext.unk1.unk84.timer == 0x60) {
        slot = find_free_misc_obj();
        if (slot == NULL) {
            return;
        }
        slot->active = 0x41;
        slot->id = 0xB;
        slot->unk2 = 1;
        slot->bg_offset = g_Player.bg_offset;
        slot->unk16 = 1;
        slot->unk15 = arg0->unk15;
        slot->unk40 = arg0->unk40;
        slot->unk42 = arg0->unk42;
        slot->unk3C = (void*)arg0->sprite_frames;
        slot->animation_table = (u32**)teleporter_animations;
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
        slot->unk3C = (void*)arg0->sprite_frames;
        slot->animation_table = (u32**)teleporter_animations;
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
#ifdef MMX4_GAMECUBE
        stop_sound(5, 0);
#endif
        func_8001540C(5, 1, NULL);
        arg0->unk6++;
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
    if (g_Player.script_state < 0) {
        player_end_script_action();
        engine_obj.checkpoint = arg0->unk2 & 0xF;
        engine_obj.unkF = -0x40;
        arg0->state = 3;
        arg0->unk5 = 0;
    }
}

#ifdef VERSION_DEMO
s8 func_800A6114_demo(struct ItemObj* self, struct PlayerObj* player)
{
    struct Unk_unk68* box = player->unk68;
    struct PlayerObj* rider;
    struct ItemObj* pad_obj;
    struct Unk_unk68* pad;
    s16 pad_right;
    s16 player_right;
    s16 pad_y;
    s16 player_y;
    s16 dist;

    if (box == NULL) {
        return 0;
    }
    pad_obj = self;
    rider = player;
    pad = pad_obj->unk68;
    if ((s16)(pad_obj->x_pos.i.hi - (pad->unk2 - 0x10)) > (s16)(rider->x_pos.i.hi - box->unk2)) {
        return 0;
    }
    pad_right = pad_obj->x_pos.i.hi + (pad->unk2 - 0x10);
    player_right = rider->x_pos.i.hi + box->unk2;
    if (pad_right < player_right) {
        return 0;
    }
    pad_y = pad_obj->y_pos.i.hi + pad->unk1;
    player_y = rider->y_pos.i.hi + box->unk1;
    dist = ABS(pad_y, player_y);
    return dist <= pad_obj->unk68->unk3 + rider->unk68->unk3;
}
#endif

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

u8 teleporter_terrain_box[4] = { 0, 0, DEMO_ALT(0x1C, 0x20), 8 };

void (*teleporter_warp_funcs[])(struct ItemObj*) = {
    teleporter_spawn_beam,
    teleporter_spawn_glow,
    teleporter_wait_flash,
    teleporter_delay,
};
