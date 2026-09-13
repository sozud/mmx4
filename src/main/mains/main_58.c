// MainObj, main_object_update_funcs[58]
// 800743FC..80074E84
#include "common.h"

void func_800743FC(struct MainObj* arg0)
{
    D_80101658[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074438);

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_800745E8);

void func_800747EC(struct MainObj* arg0)
{
    arg0->ext.main_58.unk88 = 2;
    if (arg0->unk2 == 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8007482C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_58.saved_unk5;
}

void func_80074838(struct MainObj* arg0)
{
    D_8010167C[arg0->unk6](arg0);
}

void func_80074874(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_800748B8);

void func_8007491C(struct MainObj* arg0)
{
    D_80101684[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074958);

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_800749B8);

void func_80074A0C(struct MainObj* arg0)
{
    D_8010168C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074A48);

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074AA8);

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074B10);

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074B68);

void func_80074BD8(struct MainObj* arg0)
{
    D_8010169C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074C14);

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074CB8);

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074D10);

void func_80074DDC(struct VisualObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 0;
        obj->unk50 = (struct PlayerObj*)arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_80101624;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}
