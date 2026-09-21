// ItemObj, item_object_update_funcs[23]
// 800C5C4C..800C6054
#include "common.h"

void func_800C5C4C(struct ItemObj* arg0)
{
    D_8010D344[arg0->state](arg0);
}

void func_800C5C88(struct ItemObj* self)
{
    struct MainObj* owner;

    owner = self->backref;
    self->state = 1;
    self->on_screen = 1;
    self->unk16 = 2;
    self->ext.item_23.unk80 = 0x12C;
    self->ext.item_23.timer = 4;
    self->unk5 = 0;
    self->backref = NULL;
    self->tail_ext.unk1.unk84.previous_value = 0;
    self->unk68 = &D_8010D340;
    self->unk2C = 0;
    self->unk28 = 0;
    self->unk7C.owner = owner;
    func_8002B93C(MOVING_OBJECT(self),
        func_8002B7DC(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
    self->x_vel.val *= 8;
    self->y_vel.val *= 8;
    func_80015D60(self, 0xA);
    func_8001540C(2, 0xC5, self);
}

void func_800C5D44(struct ItemObj* arg0)
{
    u16 x_distance;
    u16 y_distance;

    if (arg0->ext.item_23.unk80 != 0) {
        if (--arg0->ext.item_23.timer == 0) {
            arg0->ext.item_23.timer = 1;
            x_distance = ABS(arg0->x_pos.i.hi, g_Player.x_pos.i.hi);
            y_distance = ABS(arg0->y_pos.i.hi, g_Player.y_pos.i.hi);
            func_8002B93C(MOVING_OBJECT(arg0), (u8)func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)));
            if (x_distance >= 17 || y_distance >= 17) {
                arg0->x_vel.val *= 8;
                arg0->y_vel.val *= 8;
            } else if (x_distance >= 9 || y_distance >= 9) {
                arg0->x_vel.val *= 4;
                arg0->y_vel.val *= 4;
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

void func_800C5F04(struct ItemObj* arg0)
{
    arg0->unk5++;
    func_80015DC8(arg0);
}

void func_800C5F30(struct ItemObj* arg0)
{
    func_80015DC8(arg0);
}

void func_800C5F50(struct ItemObj* arg0)
{
    func_80015DC8(arg0);
}

void func_800C5F70(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/items/item_23", func_800C5F90);

struct Unk_unk68 D_8010D340 = { 0, 0, 4, 4 };

void (*D_8010D344[])(struct ItemObj*) = {
    func_800C5C88,
    func_800C5F90,
    func_800C5F70,
};

void (*D_8010D350[])(struct ItemObj*) = {
    func_800C5D44,
    func_800C5F04,
    func_800C5F50,
    func_800C5F30,
};
