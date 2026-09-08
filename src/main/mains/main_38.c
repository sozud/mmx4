// MainObj, main_object_update_funcs[38]
// 80060A88..80061590
#include "common.h"

void func_80060A88(struct MainObj* arg0)
{
    D_800FE8EC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060AC4);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060BC4);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060D3C);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060DC8);

void func_80060E08(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_38.saved_unk5;
}

void func_80060E14(struct MainObj* arg0)
{
    D_800FE918[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060E50);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060E94);

void func_80060F5C(struct MainObj* arg0)
{
    D_800FE920[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060F98);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060FF8);

void func_8006104C(struct MainObj* arg0)
{
    D_800FE928[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061088);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_800610F0);

void func_8006114C(struct MainObj* arg0)
{
    D_800FE930[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061188);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_800611E0);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061240);

void func_8006128C(struct MainObj* arg0)
{
    D_800FE93C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_800612C8);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061310);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_8006135C);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061424);

extern u32* D_800FE890[];

void func_800614E8(struct VisualObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 0;
        obj->unk50 = (struct PlayerObj*)arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_800FE890;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}
