// VisualObj, visual_object_update_funcs[28]
// 800B3E7C..800B41CC
#include "common.h"

void func_800B3E7C(struct VisualObj* arg0)
{
    D_8010A6A0[arg0->state](arg0);
}

void func_800B3EB8(struct VisualObj* obj)
{
    u16 flags;
    u8 player_direction;
    s8 type;
    s8 mode;
    struct MainObj* owner = MAIN_OBJECT(obj->unk50);

    flags = obj->unk42;
    player_direction = owner->unk15;
    obj->unk42 = flags & 0x7FFF;
    obj->on_screen = 1;
    obj->unk15 = player_direction;
    type = obj->unk2;

    switch (type) {
    case 0:
        func_80015D60(obj, 0xA);
        obj->unk54 = 9;
        break;
    case 1:
        func_80015D60(obj, 0x1A);
        mode = obj->unk5C.fields.mode;
        switch (mode) {
        case 0:
            obj->unk54 = 0x20;
        case 1:
        case 2:
            obj->unk54 = 0x28;
            break;
        }
        break;
    case 2:
        func_80015D60(obj, 0x19);
        owner->ext.main_60.storm_active = 2;
        break;
    case 3:
        func_80015D60(obj, 0xE);
        break;
    }

    obj->unk5C.value = 0;
    obj->state++;
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_28", func_800B3FD4);

void func_800B41AC(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010A6A0[])(struct VisualObj*) = {
    func_800B3EB8,
    func_800B3FD4,
    func_800B41AC,
};
