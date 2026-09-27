// ShotObj, shot_object_update_funcs[30]
// 8009FB60..8009FF10
#include "common.h"

void func_8009FB60(struct ShotObj* arg0)
{
    D_8010922C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_30", func_8009FB9C);

INCLUDE_ASM("main/nonmatchings/shots/shot_30", func_8009FD00);

void func_8009FE38(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009FE58(struct ShotObj* arg0)
{
}

void func_8009FE60(struct ShotObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 1;
        obj->unk50 = (struct PlayerObj*)arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = arg0->animation_table;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

void (*D_80109200[3])(struct ShotObj*) = {
    func_8009F89C,
    func_8009F94C,
    func_8009F9E0,
};

u8 D_8010920C[4][4] = {
    { 0xF3, 0xFA, 0x17, 0x0A },
    { 0xF5, 0xFD, 0x1B, 0x0A },
    { 0xFF, 0xFF, 0x0A, 0x04 },
    { 0x02, 0x02, 0x0D, 0x04 },
};

s32 D_8010921C[4] = { -0x22000, 0x22000, -0x10000, 0x10000 };

void (*D_8010922C[])(struct ShotObj*) = {
    func_8009FB9C,
    func_8009FD00,
    func_8009FE38,
    func_8009FE58,
};
