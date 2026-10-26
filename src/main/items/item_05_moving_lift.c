// ItemObj, item_object_update_funcs[5]
// 800C0E74..800C1390
#include "common.h"
#include "main/items/item_05_moving_lift.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/object_motion.h"

// moving_lift_state_funcs
extern void (*moving_lift_state_funcs[])(struct ItemObj*);

void moving_lift_despawn(struct ItemObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/55C4.h"
#include "main/object_motion.h"
#endif

struct Item05AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item05MotionConfig {
    u32 collision_mode;
    s32 velocity;
    s16 acceleration;
    s16 unused;
};

struct Item05StageConfig {
    u16 tile;
    u16 index;
    u16 x;
    u16 y;
};

struct Item05AnimationStep moving_lift_anim_0[11] = {
    { 3, 0, 1, 0 },
    { 3, 0, 1, 1 },
    { 3, 0, 1, 2 },
    { 3, 0, 1, 3 },
    { 3, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 8 },
    { 3, 0, 1, 9 },
    { 3, 0, 0xF6, 10 },
};

struct Item05AnimationStep moving_lift_anim_1[8] = {
    { 3, 0, 1, 11 },
    { 3, 0, 1, 12 },
    { 3, 0, 1, 13 },
    { 3, 0, 1, 14 },
    { 3, 0, 1, 15 },
    { 3, 0, 1, 16 },
    { 3, 0, 1, 17 },
    { 3, 0, 0xF9, 18 },
};

struct Item05AnimationStep moving_lift_anim_2[8] = {
    { 4, 0, 1, 19 },
    { 4, 0, 1, 20 },
    { 4, 0, 1, 21 },
    { 4, 0, 1, 22 },
    { 4, 0, 1, 23 },
    { 4, 0, 1, 22 },
    { 4, 0, 1, 21 },
    { 4, 0, 0xF9, 20 },
};

struct Item05AnimationStep moving_lift_anim_3[8] = {
    { 3, 0, 1, 24 },
    { 3, 0, 1, 25 },
    { 3, 0, 1, 26 },
    { 3, 0, 1, 27 },
    { 3, 0, 1, 28 },
    { 3, 0, 1, 29 },
    { 3, 0, 1, 30 },
    { 3, 0, 0xF9, 31 },
};

struct Item05AnimationStep* moving_lift_animations[4] = {
    moving_lift_anim_0,
    moving_lift_anim_1,
    moving_lift_anim_2,
    moving_lift_anim_3,
};

struct Item05MotionConfig moving_lift_motion[9] = {
    { 0, -0x10000, 0x100, 0 },
    { 0, -0x10000, 0x100, 0 },
    { 0, -0x10000, 0x100, 0 },
    { 1, -0x10000, 0x100, 0 },
    { 1, -0x10000, 0x100, 0 },
    { 1, -0x10000, 0x100, 0 },
    { 0, -0x10000, 0x100, 0 },
    { 0, -0x10000, 0x100, 0 },
    { 1, -0x10000, 0x100, 0 },
};

struct Item05StageConfig moving_lift_placements[9] = {
    { 0x0541, 0, 0x10A0, 0x04E0 },
    { 0x0541, 1, 0x1110, 0x04C0 },
    { 0x0541, 2, 0x1178, 0x04A0 },
    { 0x0541, 3, 0x11D8, 0x0480 },
    { 0x0541, 4, 0x1218, 0x0430 },
    { 0x0541, 5, 0x1318, 0x0420 },
    { 0x0541, 6, 0x1378, 0x03E0 },
    { 0x0541, 7, 0x13E8, 0x03B0 },
    { 0x0541, 8, 0x1478, 0x0350 },
};

u8 moving_lift_boxes[9][4] = {
    { 0, 4, 0x20, 0x0A },
    { 0, 4, 0x20, 0x0A },
    { 0, 4, 0x20, 0x0A },
    { 0, 0, 0x10, 0x20 },
    { 0, 0, 0x10, 0x20 },
    { 0, 0, 0x10, 0x20 },
    { 0, 4, 0x20, 0x0A },
    { 0, 4, 0x20, 0x0A },
    { 0, 0, 0x10, 0x20 },
};

void moving_lift_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    moving_lift_state_funcs[arg0->state](arg0);
}

// moving_lift_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C0EBC(struct ItemObj* arg0);
void func_800C1050(struct ItemObj* arg0);
void moving_lift_spawn_effect(struct ItemObj*);
void moving_lift_spawn_all(void);
void collide_with_players(struct PlayerObj*);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/items/item_05_moving_lift", func_800C0EBC);
#else
void func_800C0EBC(struct ItemObj* arg0)
{

    arg0->active = 0x41;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)moving_lift_animations;
    arg0->unk40 = OBJECT_STAGE_TEXTURE(5);
    arg0->unk42 = OBJECT_CLUT(0x788C);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[5];
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->unk5C = 0xF;
    arg0->unk61 = 0;
    arg0->unk54 = NULL;
    arg0->unk68 = (struct Unk_unk68*)moving_lift_boxes[arg0->unk2];
    arg0->x_pos.i.hi = moving_lift_placements[arg0->unk2].x;
    arg0->y_pos.i.hi = moving_lift_placements[arg0->unk2].y;
    arg0->y_vel.val = moving_lift_motion[arg0->unk2].velocity;
    arg0->unk2C = (u16)moving_lift_motion[arg0->unk2].acceleration;
    arg0->unk75 = 1;
    arg0->unk76 = 0;
    if ((u8)moving_lift_motion[arg0->unk2].collision_mode != 0)
        set_animation(arg0, 2);
    else
        set_animation(arg0, 0);
    moving_lift_spawn_effect(arg0);
    if (arg0->unk2 == 0)
        ((void (*)(struct ItemObj*))moving_lift_spawn_all)(arg0);
}
#endif

// moving_lift_move
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/items/item_05_moving_lift", func_800C1050);
#else
void func_800C1050(struct ItemObj* arg0)
{
    s32 offset;
    s32 y;
    s32 velocity;
    u8 old_flags;

    update_on_screen(BASE_OBJECT(arg0), moving_lift_boxes[arg0->unk2][2], moving_lift_boxes[arg0->unk2][3]);
    if (arg0->unk76 == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        arg0->y_vel.val = moving_lift_motion[arg0->unk2].velocity;
    } else if ((u8)moving_lift_motion[arg0->unk2].collision_mode != 0) {
        arg0->y_vel.val = -0x1A000;
    }

    old_flags = g_Player.unk71;
    offset = arg0->y_pos.val - g_Player.y_pos.val;
    move_object((struct MovingObj*)arg0);
    collide_with_players(PLAYER_OBJECT(arg0));
    if ((u8)g_Player.unk71 != old_flags && ((u8)g_Player.unk71 & 3)) {
        y = arg0->y_pos.val - offset - arg0->y_vel.val / 4;
        old_flags = g_Player.unk71;
        g_Player.y_pos.val = y;
        g_Player.unk71 = 0;
        collide_with_players(PLAYER_OBJECT(arg0));
        g_Player.y_pos.val = y;
        if (g_Player.unk71 & 3)
            g_Player.y_pos.val = y + g_Player.y_vel.val;
        else
            g_Player.y_pos.val = y - arg0->y_vel.val * 3;
        g_Player.unk71 = old_flags;
    }

    if (arg0->y_pos.i.hi >= 0x621) {
        velocity = moving_lift_motion[arg0->unk2].velocity;
        arg0->y_pos.i.hi = 0x4E0;
        arg0->y_vel.val = velocity;
    }
}
#endif

void moving_lift_despawn(struct ItemObj* arg0)
{
    despawn_object(OBJECT_HEADER(arg0));
}

void moving_lift_spawn_effect(struct ItemObj* arg0)
{
    struct VisualObj* visualObj;

    visualObj = find_free_visual_obj();
    if (visualObj != 0) {
        visualObj->active = 0x41;
        visualObj->unk50 = PLAYER_OBJECT(arg0);
        visualObj->id = 0xE;
        if (((u8*)moving_lift_motion)[arg0->unk2 * sizeof(struct Item05MotionConfig)] == 0) {
            visualObj->unk2 = 1;
        } else {
            visualObj->unk2 = 3;
        }
        visualObj->state = 0;
        visualObj->unk5 = 0;
        visualObj->unk6 = 0;
        visualObj->unk38 = 0;
        visualObj->unk3C = (void*)arg0->sprite_frames;
        visualObj->animation_table = (u32**)arg0->animation_table;
        visualObj->unk40 = arg0->unk40;
        visualObj->unk42 = arg0->unk42;
        visualObj->unk16 = VISUAL_SATURN_LAYER(5);
        visualObj->x_pos.val = arg0->x_pos.val;
        visualObj->y_pos.val = arg0->y_pos.val;
    }
}

void moving_lift_spawn_all(void)
{
    s8 index;
    struct ItemObj* item;

    index = 1;
    while ((u8)index < 9U) {
        item = find_free_item_obj();
        if (item == NULL) {
            break;
        }
        item->unk2 = index;
        index += 1;
        item->active = 0x41;
        item->id = 5;
        item->state = 0;
        item->unk5 = 0;
        item->unk6 = 0;
    }
}

void (*moving_lift_state_funcs[])(struct ItemObj*) = {
    func_800C0EBC,
    func_800C1050,
    moving_lift_despawn,
};
