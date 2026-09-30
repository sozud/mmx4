// ItemObj, item_object_update_funcs[8]
// 800C1994..800C20AC
#include "common.h"

struct Item08AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item08AnimationStep boss_door_open_steps[30] = {
    { 1, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 3, 0, 1, 3 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 4 },
    { 3, 0, 1, 1 },
    { 3, 0, 1, 0 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 0 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 2 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 1 },
    { 3, 0, 1, 0 },
    { 4, 1, 1, 10 },
    { 4, 0, 1, 11 },
    { 4, 2, 0, 12 },
};

struct Item08AnimationStep boss_door_close_steps[30] = {
    { 4, 0, 1, 12 },
    { 4, 0, 1, 11 },
    { 4, 1, 1, 10 },
    { 3, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 2 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 1 },
    { 3, 0, 1, 0 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 0 },
    { 3, 0, 1, 9 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 0 },
    { 1, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 2 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 1 },
    { 2, 2, 0, 0 },
};

struct Unk_unk68 boss_door_terrain_box = { 0, 0, 0x10, 0x20 };

struct Item08AnimationStep* boss_door_animations[2] = {
    boss_door_open_steps,
    boss_door_close_steps,
};

void boss_door_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    boss_door_state_funcs[arg0->state](arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void boss_door_init(struct ItemObj* arg0)
{
    s32 column;
    s32 row;
    s32 x;

    arg0->active = 0x49;
    arg0->unk16 = 6;
    arg0->unk40 = D_801406A8[func_8002938C(0x80)] >> 7;
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x80)];
    column = func_8002938C(0x80);
    row = func_8002938C(0x80);
    x = column * 4 + 0x18;
    arg0->unk42 = (x % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    arg0->animation_table = (const u8* const*)boss_door_animations;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk7C.timer = (u8)arg0->unk2 & 0x10;
    arg0->unk15 = 0;
    arg0->unk67 = 0;
    arg0->unk75 = 1;
    arg0->ext.packed = (u8)arg0->unk2 & 0x40;
    if (arg0->unk2 & 0xC0) {
        arg0->state = 2;
        arg0->unk68 = NULL;
    } else {
        arg0->state = 1;
        arg0->unk68 = &boss_door_terrain_box;
    }
    arg0->unk5 = 0;
    arg0->unk2 &= 0xF;
    set_animation(ANIMATED_OBJECT(arg0), 0);
}

void boss_door_main(struct ItemObj* arg0)
{
    boss_door_step_funcs[arg0->unk5](arg0, &engine_obj, &g_Player);
}

void boss_door_wait_player(struct ItemObj* arg0, struct EngineObj* arg1,
    struct PlayerObj* arg2)
{
    collide_with_players(PLAYER_OBJECT(arg0));
    boss_door_block_player(arg0);
    if (func_800C1E7C(arg0)) {
        if (arg0->unk7C.timer == 0) {
            reset_main_and_shots();
        }
        arg2->capsule_state = 1;
        background_objects[0].unk3E.half &= 0xF;
        arg0->unk5 = 1;
    }
}

void boss_door_open(struct ItemObj* arg0, struct EngineObj* arg1, struct PlayerObj* arg2)
{
    if (arg2->capsule_state < 0) {
        arg1->unk10 = 1;
        arg1->unk12 = 1;
        func_8001540C(0, 0x10, arg0);
        arg2->unk68 = NULL;
        arg0->unk5 = 2;
    }
}

// boss_door_opening
INCLUDE_ASM("main/nonmatchings/items/item_08_boss_door", func_800C1C88);

void boss_door_walk_through(struct ItemObj* arg0, struct EngineObj* arg1,
    struct PlayerObj* arg2)
{
    arg2->x_pos.val += 0xA400;
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        arg2->capsule_state = 0;
        player_set_collision_bounds(arg2);
        arg0->unk5 = 4;
        set_animation(arg0, 1);
        func_8001540C(0, 0x11, arg0);
    }
}

void boss_door_close(struct ItemObj* arg0, struct EngineObj* arg1,
    struct PlayerObj* arg2)
{
    if (arg0->animation_step.fields.event < 2) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event == 1) {
            func_8001540C(0, 0x10, arg0);
            arg0->animation_step.fields.event = 0;
        }
    } else {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

// boss_door_player_touching
INCLUDE_ASM("main/nonmatchings/items/item_08_boss_door", func_800C1E7C);

void boss_door_locked(struct ItemObj* arg0)
{
    collide_with_players(PLAYER_OBJECT(arg0));
    boss_door_block_player(arg0);
    if (arg0->ext.packed != 0 && engine_obj.character_state.fields.active != 0) {
        arg0->state = 1;
        arg0->unk5 = 0;
        arg0->unk68 = &boss_door_terrain_box;
    }
}

void boss_door_block_player(struct ItemObj* arg0)
{
    volatile struct PlayerObj* player = &g_Player;

    if (arg0->unk72 & 4) {
        player->unk71 = (u8)(player->unk71 & 0xB);
    }
    if (arg0->unk72 & 8) {
        player->unk71 = (u8)(player->unk71 & 7);
    }
}

void (*boss_door_state_funcs[])(struct ItemObj*) = {
    boss_door_init,
    boss_door_main,
    boss_door_locked,
};

Item08StateFunc boss_door_step_funcs[5] = {
    boss_door_wait_player,
    boss_door_open,
    func_800C1C88,
    boss_door_walk_through,
    boss_door_close,
};
