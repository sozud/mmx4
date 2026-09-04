// QuadObj, quad_object_update_funcs[12]
// 800D7734..800D7A4C
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_12", func_800D7734);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_12", func_800D784C);

void func_800D7960(struct QuadObj* arg0)
{
    struct MiscObj* misc;
    if (--(arg0->ext.unk_ext.unk38) == 0) {
        if (arg0->unk2 == 0) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->base.active = 1;
                misc->base.id = 0x13;
                misc->base.unk2 = 0xB;
            }
        }
        arg0->state++;
    }
    quad_is_on_screen(arg0);
}

void func_800D79F0(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D7A10(struct QuadObj* arg0)
{
    D_8010FE10[arg0->state](arg0);
}

void (*D_8010FE10[])(struct QuadObj*) = {
    func_800D7734,
    func_800D784C,
    func_800D7960,
    func_800D79F0,
};
