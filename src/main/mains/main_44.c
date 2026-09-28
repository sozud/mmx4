// MainObj, main_object_update_funcs[44]
// 80065930..80065B8C
#include "common.h"
#include "func_tables.h"

void func_80065930(struct MainObj* arg0)
{
    D_800FF87C[arg0->state](arg0);
}

void func_8006596C(struct MainObj* obj)
{
    obj->active = 0x41;
    obj->unk5C = 1;
    obj->unk60 = 3;
    obj->unk61 = 0;
    obj->bg_offset = g_Player.bg_offset;
    obj->collision_data = D_801060F0;
    obj->animation_table = (const u8* const*)D_800FF874;
    obj->unk16 = 6;
    obj->unk54 = &D_800FF80C;
    // memset 0
    obj->unk20 = 0;
    obj->unk24 = 0;
    obj->unk28 = 0;
    obj->unk2C = 0;
    obj->unk67 = 0;
    obj->unk68 = NULL;
    obj->unk50 = &D_800FF810;
    obj->unk18.val = obj->x_pos.val;
    obj->unk1C.val = obj->y_pos.val;
    func_80015D60(obj, 0);
    obj->ext.main_44.unk80 = 0;
    obj->ext.main_44.unk84 = 0;
    obj->ext.main_44.unk88 = 0;
    obj->ext.main_44.unk8C = 0;
    obj->ext.main_44.unk90 = 0;
    obj->ext.main_44.saved_unk5 = 0;
    obj->unk5 = 2;
    obj->unk6 = 0;
    obj->state++;
}

extern void (*D_800FF888[])(struct MainObj*);

void func_80065A54(struct MainObj* arg0)
{
    s8 temp_v0;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FF888[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    func_8002DD04(arg0);
    temp_v0 = arg0->unk5;
    if (temp_v0 != 0) {
        arg0->ext.main_44.saved_unk5 = temp_v0;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = (u8)arg0->state + 1;
}

void func_80065B04(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80065B24(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_44.saved_unk5;
}

void func_80065B30(struct MainObj* arg0)
{
    D_800FF894[arg0->unk6](arg0);
}

void func_80065B6C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}

struct Unk_unk68 D_800FF80C = { -11, -10, 21, 23 };

struct Unk_unk68 D_800FF810 = { -11, -10, 20, 42 };

union AnimationStep D_800FF814[] = {
    { 0x05010007 },
    { 0x0601000C },
    { 0x07010004 },
    { 0x08010004 },
    { 0x00010005 },
    { 0x01010008 },
    { 0x0D010007 },
    { 0x0E01000C },
    { 0x0D010007 },
    { 0x00010005 },
    { 0x01010008 },
    { 0x0F010007 },
    { 0x1001000E },
    { 0x0F010007 },
    { 0x00010006 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010002 },
    { 0x0B010004 },
    { 0x0C010002 },
    { 0x0A01000C },
    { 0x09010006 },
    { 0x00010005 },
    { 0x01E9000C },
};

union AnimationStep* D_800FF874[2] = { D_800FF814, NULL };

void (*D_800FF87C[])(struct MainObj*) = {
    func_8006596C,
    func_80065A54,
    func_80065B04,
};

void (*D_800FF888[3])() = { func_8009216C, func_80065B24, func_80065B30 };

void (*D_800FF894[1])() = { func_80065B6C };
