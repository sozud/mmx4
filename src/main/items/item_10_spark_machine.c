// ItemObj, item_object_update_funcs[10]
// 800C24E0..800C2BE0
#include "common.h"

struct Item10AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item10Offset {
    s16 x;
    s16 y;
};

struct Item10AnimationStep spark_machine_anim_0[4] = {
    { 3, 0, 1, 0 },
    { 3, 0, 1, 1 },
    { 3, 0, 1, 2 },
    { 3, 0, 253, 1 },
};

struct Item10AnimationStep spark_machine_anim_1[4] = {
    { 3, 0, 1, 3 },
    { 3, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 3, 0, 253, 4 },
};

struct Item10AnimationStep spark_machine_anim_2[4] = {
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 8 },
    { 3, 0, 253, 7 },
};

struct Item10AnimationStep spark_machine_anim_3[4] = {
    { 3, 0, 1, 9 },
    { 3, 0, 1, 10 },
    { 3, 0, 1, 11 },
    { 3, 0, 253, 10 },
};

struct Item10AnimationStep spark_machine_anim_4[4] = {
    { 3, 0, 1, 12 },
    { 3, 0, 1, 13 },
    { 3, 0, 1, 14 },
    { 3, 0, 253, 13 },
};

struct Item10AnimationStep spark_machine_anim_5[4] = {
    { 3, 0, 1, 15 },
    { 3, 0, 1, 16 },
    { 3, 0, 1, 17 },
    { 3, 0, 253, 16 },
};

struct Item10AnimationStep spark_machine_anim_6[4] = {
    { 3, 0, 1, 18 },
    { 3, 0, 1, 19 },
    { 3, 0, 1, 20 },
    { 3, 0, 253, 19 },
};

struct Item10AnimationStep spark_machine_anim_7[19] = {
    { 3, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 0, 1, 23 },
    { 3, 0, 1, 24 },
    { 3, 0, 1, 25 },
    { 3, 0, 1, 26 },
    { 3, 0, 1, 27 },
    { 3, 0, 1, 28 },
    { 3, 0, 1, 29 },
    { 3, 0, 1, 30 },
    { 3, 0, 1, 31 },
    { 3, 0, 1, 32 },
    { 3, 0, 1, 33 },
    { 3, 0, 1, 34 },
    { 3, 0, 1, 35 },
    { 3, 0, 1, 36 },
    { 3, 0, 1, 37 },
    { 3, 0, 1, 38 },
    { 3, 0, 249, 39 },
};

struct Item10AnimationStep spark_machine_anim_8[12] = {
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 40 },
    { 6, 0, 1, 42 },
    { 6, 0, 1, 43 },
    { 6, 1, 0, 44 },
};

struct Item10AnimationStep spark_machine_anim_9[11] = {
    { 3, 0, 1, 45 },
    { 3, 0, 1, 46 },
    { 3, 0, 1, 47 },
    { 3, 0, 1, 48 },
    { 3, 0, 1, 49 },
    { 3, 0, 1, 50 },
    { 3, 0, 1, 51 },
    { 3, 0, 1, 52 },
    { 3, 0, 1, 53 },
    { 3, 0, 1, 54 },
    { 3, 1, 0, 62 },
};

struct Item10AnimationStep spark_machine_anim_10[7] = {
    { 3, 0, 1, 55 },
    { 3, 0, 1, 56 },
    { 3, 0, 1, 57 },
    { 3, 0, 1, 58 },
    { 3, 0, 1, 59 },
    { 3, 0, 1, 60 },
    { 3, 0, 250, 61 },
};

struct Item10AnimationStep spark_machine_anim_11[7] = {
    { 3, 0, 1, 45 },
    { 3, 0, 1, 46 },
    { 3, 0, 1, 47 },
    { 3, 0, 1, 48 },
    { 3, 0, 1, 49 },
    { 3, 0, 1, 50 },
    { 3, 0, 250, 51 },
};

struct Item10AnimationStep spark_machine_anim_12[2] = {
    { 3, 0, 1, 63 },
    { 3, 0, 255, 64 },
};

struct Item10AnimationStep spark_machine_anim_13[1] = {
    { 3, 0, 0, 65 },
};

struct Item10AnimationStep* spark_machine_animations[14] = {
    spark_machine_anim_0,
    spark_machine_anim_1,
    spark_machine_anim_2,
    spark_machine_anim_3,
    spark_machine_anim_4,
    spark_machine_anim_5,
    spark_machine_anim_6,
    spark_machine_anim_7,
    spark_machine_anim_8,
    spark_machine_anim_9,
    spark_machine_anim_10,
    spark_machine_anim_11,
    spark_machine_anim_12,
    spark_machine_anim_13,
};

void spark_machine_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    spark_machine_state_funcs[arg0->state](arg0);
}

// spark_machine_init
INCLUDE_ASM("main/nonmatchings/items/item_10_spark_machine", func_800C2528);

// spark_machine_main
INCLUDE_ASM("main/nonmatchings/items/item_10_spark_machine", func_800C2638);

void spark_machine_sparking(struct ItemObj* arg0)
{
    if (--arg0->tail_ext.unk1.unk84.bytes[3] == 0) {
        arg0->state++;
    }
    spark_machine_spawn_spark_a(arg0);
    spark_machine_spawn_spark_b(arg0);
    spark_machine_spawn_spark_c(arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

void spark_machine_break(struct ItemObj* arg0)
{
    arg0->ext.timer = 1;
    arg0->unk42 &= 0x7FFF;
    spawn_debris(5, spark_machine_debris, arg0);
    apply_tile_effect(
        (u8)arg0->unk2,
        (s16)(arg0->x_pos.u.hi - 0x20),
        (s16)(arg0->y_pos.u.hi - 0x28));
    set_animation(arg0, 0xC);
    is_on_screen(BASE_OBJECT(arg0));
    arg0->state = (u8)arg0->state + 1;
}

void spark_machine_broken(struct ItemObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

extern struct Item10Offset spark_machine_spark_offsets[5];

void spark_machine_spawn_spark_a(struct ItemObj* arg0)
{
    if (arg0->tail_ext.unk2.timer == 0) {
        struct MiscObj* obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x24;
            obj->unk15 = get_random() & 0x40;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            obj->x_pos.u.hi = arg0->x_pos.u.hi + spark_machine_spark_offsets[get_random() & 3].x;
            obj->y_pos.u.hi = arg0->y_pos.u.hi + spark_machine_spark_offsets[get_random() & 3].y;
            obj->unk2 = 0;
            obj->ext.pointer.unk50 = arg0;
        }
        arg0->tail_ext.unk2.timer = (get_random() & 3) * 10;
        return;
    }
    arg0->tail_ext.unk2.timer--;
}

void spark_machine_spawn_spark_b(struct ItemObj* arg0)
{
    if (arg0->tail_ext.unk2.previous_value == 0) {
        struct MiscObj* obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x24;
            obj->unk15 = get_random() & 0x40;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            obj->x_pos.u.hi = arg0->x_pos.u.hi + spark_machine_spark_offsets[(get_random() & 3)].x;
            obj->y_pos.u.hi = arg0->y_pos.u.hi + spark_machine_spark_offsets[(get_random() & 3)].y;
            obj->unk2 = 1;
            obj->ext.pointer.unk50 = arg0;
        }
        arg0->tail_ext.unk2.previous_value = (get_random() & 3) * 15;
        return;
    }
    arg0->tail_ext.unk2.previous_value--;
}

void spark_machine_spawn_spark_c(struct ItemObj* arg0)
{
    if (arg0->tail_ext.unk2.value == 0) {
        struct MiscObj* obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x24;
            obj->unk15 = get_random() & 0x40;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            obj->x_pos.u.hi = arg0->x_pos.u.hi + spark_machine_spark_offsets[get_random() & 3].x;
            obj->y_pos.u.hi = arg0->y_pos.u.hi + spark_machine_spark_offsets[get_random() & 3].y;
            obj->unk2 = 2;
            obj->ext.pointer.unk50 = arg0;
        }
        arg0->tail_ext.unk2.value = (get_random() & 3) * 12;
        return;
    }
    arg0->tail_ext.unk2.value--;
}

void (*spark_machine_state_funcs[])(struct ItemObj*) = {
    func_800C2528,
    func_800C2638,
    spark_machine_sparking,
    spark_machine_break,
    spark_machine_broken,
    spark_machine_spawn_spark_a,
};

u8 spark_machine_terrain_box[4] = { 0, 0xF8, 0x20, 0x18 };
u8 spark_machine_hit_box[4] = { 0xE0, 0xE8, 0x40, 0x30 };
u8 spark_machine_debris[8] = { 1, 2, 3, 4, 5, 0, 0, 0 };

struct Item10Offset spark_machine_spark_offsets[5] = {
    { 0, 12 },
    { -16, -8 },
    { 16, -10 },
    { -19, 16 },
    { -16, -6 },
};
