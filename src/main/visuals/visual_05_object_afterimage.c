// VisualObj, visual_object_update_funcs[5]
// 800AFC9C..800AFF78
#include "common.h"
#include "main/visuals/visual_05_object_afterimage.h"

// object_afterimage_state_funcs
extern void (*object_afterimage_state_funcs[])(struct VisualObj*);
void object_afterimage_follow(struct VisualObj*);
void object_afterimage_start(struct VisualObj*);
void object_afterimage_wait(struct VisualObj*);
void object_afterimage_main(struct VisualObj*);
#ifdef VERSION_DEMO
void func_80096AA0_demo(struct VisualObj*);
void func_80096B88_demo(struct VisualObj*);
#endif

// object_afterimage_step_funcs
extern void (*object_afterimage_step_funcs[])(struct VisualObj*);
void object_afterimage_trail(struct VisualObj*);
void object_afterimage_linger(struct VisualObj*);
void object_afterimage_catch_up(struct VisualObj*);
#include "weapon_resources.h"
#ifdef MMX4_SATURN
extern void saturn_queue_object(void*);
#endif

#ifdef VERSION_DEMO
extern void (*object_afterimage_state_funcs[])(struct VisualObj*);
extern void (*object_afterimage_step_funcs[])(struct VisualObj*);
#else
void (*object_afterimage_state_funcs[])(struct VisualObj*) = {
    object_afterimage_wait,
    object_afterimage_main,
};

void (*object_afterimage_step_funcs[])(struct VisualObj*) = {
    object_afterimage_trail,
    object_afterimage_linger,
    object_afterimage_catch_up,
};
#endif

#ifndef VERSION_DEMO
void object_afterimage_update(struct VisualObj* arg0)
{
    u8 temp_a1;
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    arg0->animation_step.fields.frame_index = owner->animation_step.fields.frame_index;
    temp_a1 = owner->unk15;
    arg0->unk15 = temp_a1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (owner->pad4B[0] == 0) {
        arg0->on_screen = 0;
        arg0->state = 0;
        return;
    }
    object_afterimage_state_funcs[arg0->state](arg0);
}
#endif

#ifndef VERSION_DEMO
void object_afterimage_wait(struct VisualObj* arg0)
{
    s8 temp_v0;
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    temp_v0 = owner->pad4B[0];
    if (temp_v0 != 0) {
        if (temp_v0 > 0) {
            arg0->on_screen = 1;
            object_afterimage_start(arg0);
            return;
        }
        owner->pad4B[0] = 0;
    }
}
#endif

void object_afterimage_main(struct VisualObj* arg0)
{
#ifdef VERSION_DEMO
    if (arg0->state == 0) {
        func_80096AA0_demo(arg0);
    } else {
        func_80096B88_demo(arg0);
    }
#else
    object_afterimage_step_funcs[arg0->unk5](arg0);
#endif
#ifdef MMX4_SATURN
    if (arg0->on_screen)
        saturn_queue_object(arg0);
#endif
}

#ifdef VERSION_DEMO
s32 D_800D9768_demo[8] = {
    FIXED(-3),
    FIXED(-2),
    FIXED(1.5),
    FIXED(2.5),
    FIXED(-3.5),
    FIXED(-2.5),
    FIXED(2),
    FIXED(3),
};
s32 D_800D9788_demo[8] = {
    FIXED(3.5),
    FIXED(4.5),
    FIXED(6),
    FIXED(3),
    FIXED(4),
    FIXED(5),
    FIXED(5.5),
    FIXED(2.5),
};

void func_80096AA0_demo(struct VisualObj* arg0)
{
    arg0->on_screen = 1;
    arg0->unk3C = arg0->unk50->unk3C;
    arg0->animation_table = arg0->unk50->animation_table;
    arg0->unk40 = arg0->unk50->unk40;
    arg0->unk42 = arg0->unk50->unk42 & 0x7FFF;
    arg0->unk54 = 0x12C;
    arg0->unk16 = 1;
    arg0->unk2C = 0x5000;
    arg0->x_vel.val = D_800D9768_demo[get_random() & 7] + arg0->unk50->x_vel.val / 2;
    arg0->y_vel.val = D_800D9788_demo[get_random() & 7];
    set_animation(arg0, arg0->unk56);
    arg0->state++;
    is_on_screen(BASE_OBJECT(arg0));
}
#endif

#ifdef VERSION_DEMO
void func_80096B88_demo(struct VisualObj* arg0)
{
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        move_with_gravity(ANIMATED_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->on_screen ^= 1) {
            is_on_screen(BASE_OBJECT(arg0));
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}
#endif

#ifndef VERSION_DEMO
void object_afterimage_trail(struct VisualObj* arg0)
{
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    if (arg0->unk54 != 0) {
        arg0->unk54--;
    } else {
        arg0->unk54 = 3;
        object_afterimage_follow(arg0);
    }
    if (owner->pad4B[0] < 0) {
        arg0->unk5++;
    }
}
#endif

#ifndef VERSION_DEMO
void object_afterimage_linger(struct VisualObj* arg0)
{
    s16 temp_v0;

    if (arg0->unk5C.owner->pad4B[0] > 0) {
        object_afterimage_start(arg0);
        return;
    }

    temp_v0 = arg0->unk56;
    if (temp_v0 != 0) {
        arg0->unk56 = temp_v0 - 1;
        if (arg0->unk56 & 1) {
            object_afterimage_follow(arg0);
        }
    } else {
        arg0->unk5++;
    }
}
#endif

#ifndef VERSION_DEMO
void object_afterimage_catch_up(struct VisualObj* arg0)
{
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    if (arg0->unk58 != 0) {
        object_afterimage_follow(arg0);
        arg0->unk58--;
        return;
    }

    arg0->on_screen = 0;
    arg0->state = 0;
    if (arg0->unk2 == 2) {
        owner->pad4B[0] = 0;
    }
}
#endif

#ifndef VERSION_DEMO
void object_afterimage_follow(struct VisualObj* arg0)
{
    struct PlayerObj* parent;

    parent = arg0->unk50;
    arg0->x_pos.val = parent->unk18.val;
    arg0->y_pos.val = parent->unk1C.val;
}
#endif

#ifndef VERSION_DEMO
void object_afterimage_start(struct VisualObj* arg0)
{
    struct ObjectHeader* parent;
    unsigned char state;

    arg0->unk54 = 3;
    arg0->unk56 = 8;
    parent = *(struct ObjectHeader**)&arg0->unk5C;
    arg0->unk58 = (5 - arg0->unk2) * 2;
    arg0->x_pos.val = parent->x_pos.val;
    state = arg0->state;
    arg0->y_pos.val = parent->y_pos.val;
    arg0->unk5 = 0;
    arg0->state = state + 1;
}
#endif
