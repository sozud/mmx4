// ItemObj, item_object_update_funcs[27]
// 800C7164..800C7A68
#include "common.h"

struct Item26AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

extern struct Item26AnimationStep boss_teleporter_anim_0[];
extern struct Item26AnimationStep boss_teleporter_anim_1[];
extern struct Item26AnimationStep boss_teleporter_anim_2[];
extern struct Item26AnimationStep boss_teleporter_anim_3[];
extern struct Item26AnimationStep boss_teleporter_anim_4[];
extern struct Item26AnimationStep boss_teleporter_anim_5[];
extern struct Item26AnimationStep boss_teleporter_anim_6[];
extern struct Item26AnimationStep boss_teleporter_anim_7[];
extern struct Item26AnimationStep boss_teleporter_anim_8[];
extern struct Item26AnimationStep boss_teleporter_anim_9[];
extern struct Item26AnimationStep boss_teleporter_anim_10[];

struct Item26AnimationStep* boss_teleporter_animations[11] = {
    boss_teleporter_anim_0,
    boss_teleporter_anim_1,
    boss_teleporter_anim_2,
    boss_teleporter_anim_3,
    boss_teleporter_anim_4,
    boss_teleporter_anim_5,
    boss_teleporter_anim_6,
    boss_teleporter_anim_7,
    boss_teleporter_anim_8,
    boss_teleporter_anim_9,
    boss_teleporter_anim_10,
};

void boss_teleporter_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    boss_teleporter_state_funcs[arg0->state](arg0);
    collide_with_players(arg0);
}

// boss_teleporter_init
INCLUDE_ASM("main/nonmatchings/items/item_27", func_800C71C0);

void boss_teleporter_main(struct ItemObj* arg0)
{
    boss_teleporter_step_funcs[arg0->unk5](arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 4;
}

void boss_teleporter_close(struct ItemObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 3;
        engine_obj.character_state.bytes[arg0->unk2 + 6] = 2;
    } else {
        animate_object(ANIMATED_OBJECT(arg0));
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void boss_teleporter_idle(struct ItemObj* arg0)
{
    is_on_screen(BASE_OBJECT(arg0));
}

void boss_teleporter_despawn(struct ItemObj* arg0)
{
    despawn_object(OBJECT_HEADER(arg0));
}

void boss_teleporter_wait_player(struct ItemObj* self)
{
    struct MiscObj* effect;
    u8 height;

    if (func_800C7970(self, &g_Player)) {
        g_Player.x_pos.i.hi = (s16)(u16)self->x_pos.i.hi;
        height = self->unk68->unk3;
        g_Player.y_pos.i.hi = ((u16)self->y_pos.i.hi - height) - g_Player.unk68->unk3;
        player_start_script_action(0x14, g_Player.unk15);
        reset_main_and_shots();
        effect = find_free_misc_obj();
        if (effect != NULL) {
            effect->active = 0x41;
            effect->id = 0x33;
            effect->unk2 = 0x10;
            effect->x_pos.val = self->x_pos.val;
            effect->y_pos.val = self->y_pos.val;
            effect->ext.misc_5.owner = MAIN_OBJECT(self);
        }
        self->unk5 = 1;
    }
}

void boss_teleporter_wait_enter(struct ItemObj* arg0)
{
    if (g_Player.script_state < 0) {
        arg0->tail_ext.unk1.unk84.timer = 0;
        background_objects[0].unk26 = background_objects[0].x_pos.i.hi;
        background_objects[0].unk24 = background_objects[0].x_pos.i.hi;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        func_8001540C(5, 0, NULL);
    }
}

void boss_teleporter_warp(struct ItemObj* arg0)
{
    boss_teleporter_warp_funcs[arg0->unk6](arg0);
}

void boss_teleporter_warp_start(struct ItemObj* arg0)
{
    struct MiscObj* misc;

    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x33;
        misc->unk2 = 0x20;
        misc->x_pos.val = arg0->x_pos.val;
        misc->y_pos.val = arg0->y_pos.val;
        misc->ext.misc_24.main = MAIN_OBJECT(arg0);
        arg0->tail_ext.unk1.unk84.timer = 0x78;
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void boss_teleporter_warp_charge(struct ItemObj* arg0)
{
    if (--arg0->tail_ext.unk1.unk84.timer == 0) {
        set_animation(arg0, 4);
        set_animation(arg0->unk7C.object, 8);
        arg0->tail_ext.unk1.unk84.timer = 0x78;
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void boss_teleporter_warp_leave(struct ItemObj* arg0)
{
    if (--arg0->tail_ext.unk1.unk84.timer == 0) {
        player_start_script_action(0x16, g_Player.unk15);
        func_8001540C(5, 1, NULL);
        arg0->tail_ext.unk1.unk84.timer = 0x28;
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void boss_teleporter_warp_finish(struct ItemObj* arg0)
{
    if (--arg0->tail_ext.unk1.unk84.timer == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void boss_teleporter_arrive(struct ItemObj* arg0)
{
    u8 checkpoint;

    if (g_Player.script_state < 0) {
        player_end_script_action();
        checkpoint = (u8)arg0->unk2;
        engine_obj.unkF = -0x40;
        engine_obj.checkpoint = checkpoint & 0xF;
        arg0->state = 3;
        arg0->unk5 = 0;
    }
}

void boss_teleporter_wait_bosses_cleared(struct ItemObj* self)
{
    u8 slot;
    struct MiscObj* misc;

    for (slot = 8; slot < 0x10; slot++) {
        if (engine_obj.character_state.bytes[slot] == 0) {
            break;
        }
    }

    if (slot == 0x10) {
        set_animation(self, 1);
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x33;
            misc->unk2 = 0;
            misc->x_pos.val = self->x_pos.val;
            misc->y_pos.val = self->y_pos.val;
            misc->ext.misc_51.source = MAIN_OBJECT(self);
            self->unk7C.misc = misc;
        }
        self->unk5 = 0;
    }
}

// boss_teleporter_player_inside
INCLUDE_ASM("main/nonmatchings/items/item_27", func_800C7970);

void (*boss_teleporter_state_funcs[])(struct ItemObj*) = {
    func_800C71C0,
    boss_teleporter_main,
    boss_teleporter_close,
    boss_teleporter_idle,
    boss_teleporter_despawn,
};

void (*boss_teleporter_step_funcs[])(struct ItemObj*) = {
    boss_teleporter_wait_player,
    boss_teleporter_wait_enter,
    boss_teleporter_warp,
    boss_teleporter_arrive,
    boss_teleporter_wait_bosses_cleared,
};

u8 boss_teleporter_box[4] = { 0, 0, 0x20, 8 };

u8* boss_teleporter_boss_flags[8] = {
    &engine_obj.character_state.bytes[8],
    &engine_obj.character_state.bytes[9],
    &engine_obj.character_state.bytes[10],
    &engine_obj.character_state.bytes[11],
    &engine_obj.character_state.bytes[12],
    &engine_obj.character_state.bytes[13],
    &engine_obj.character_state.bytes[14],
    &engine_obj.character_state.bytes[15],
};

void (*boss_teleporter_warp_funcs[])(struct ItemObj*) = {
    boss_teleporter_warp_start,
    boss_teleporter_warp_charge,
    boss_teleporter_warp_leave,
    boss_teleporter_warp_finish,
};
