// VisualObj, visual_object_update_funcs[29]
// 800B41CC..800B4610
#include "common.h"

void func_800B41CC(struct VisualObj* arg0)
{
    D_8010A6AC[arg0->state](arg0);
}

void func_800B4208(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 2;
    arg0->unk54 = 0x3C;
    arg0->unk5 = 0;
    arg0->unk56 = 4;
    arg0->unk2C = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->x_vel.val = 0;
    func_80015D60(arg0, 0xA);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800B4274(struct VisualObj* arg0)
{
    u16 x_distance;
    u16 y_distance;

    if (--arg0->unk54 != 0) {
        if (--arg0->unk56 == 0) {
            arg0->unk56 = 1;
            x_distance = ABS(arg0->x_pos.i.hi, g_Player.x_pos.i.hi);
            y_distance = ABS(arg0->y_pos.i.hi, g_Player.y_pos.i.hi);
            func_8002B93C(MOVING_OBJECT(arg0), (u8)func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)));
            // pursuit/homing missile?
            if (x_distance >= 17 || y_distance >= 17) {
                arg0->x_vel.val *= 4;
                arg0->y_vel.val *= 4;
            } else if (x_distance >= 9 || y_distance >= 9) {
                arg0->x_vel.val *= 3;
                arg0->y_vel.val *= 3;
            } else if (x_distance >= 5 || y_distance >= 5) {
                arg0->x_vel.val *= 2;
                arg0->y_vel.val *= 2;
            } else if (x_distance >= 3 || y_distance >= 3) {
                arg0->x_vel.val *= 1;
                arg0->y_vel.val *= 1;
            } else {
                arg0->x_pos.val = g_Player.x_pos.val;
                arg0->y_pos.val = g_Player.y_pos.val;
            }
        }
        func_8002B694(ANIMATED_OBJECT(arg0));
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        arg0->unk5++;
        func_80015D60(arg0, 0xB);
    }
}

void func_800B4450(struct VisualObj* arg0)
{
    arg0->unk5++;
    arg0->unk50->input.buttons.held = 0;
    func_80015DC8(arg0);
}

void func_800B4480(struct VisualObj* arg0)
{
    struct ShotObj* shot;

    if ((s16)arg0->unk50->input.buttons.previous != 0) {
        arg0->unk5++;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = (u8)arg0->active;
            shot->id = 0x2A;
            shot->unk2 = (u8)arg0->unk2;
            shot->x_pos.val = arg0->x_pos.val;
            shot->y_pos.val = arg0->y_pos.val;
            shot->animation_table = arg0->animation_table;
            shot->unk40 = arg0->unk40;
            shot->unk3C = arg0->unk3C;
            shot->unk42 = arg0->unk42 & 0x7FFF;
            shot->unk16 = arg0->unk16;
            shot->unk15 = 0;
            shot->unk7C = WEAPON_OBJECT(arg0);
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800B4558(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
}

void func_800B4578(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B4598(struct VisualObj* arg0)
{
    if (arg0->unk50->state != 1) {
        ZeroObjectState(arg0);
    } else {
        D_8010A6B8[arg0->unk5](arg0);
        is_on_screen(arg0);
    }
}

void (*D_8010A6AC[])(struct VisualObj*) = {
    func_800B4208,
    func_800B4598,
    func_800B4578,
};

void (*D_8010A6B8[])(struct VisualObj*) = {
    func_800B4274,
    func_800B4450,
    func_800B4480,
    func_800B4558,
};
