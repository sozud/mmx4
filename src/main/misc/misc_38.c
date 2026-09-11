// MiscObj, misc_object_update_funcs[38]
// 800CF4B8..800CF790
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_38", func_800CF4B8);

void func_800CF5F0(struct MiscObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state++;
    }
}

void func_800CF640(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_38", func_800CF660);

INCLUDE_ASM("main/nonmatchings/misc/misc_38", func_800CF708);

void func_800CF754(struct MiscObj* arg0)
{
    D_8010EF0C[arg0->state](arg0);
}

void (*D_8010EF0C[5])(struct MiscObj*) = {
    func_800CF4B8,
    func_800CF5F0,
    func_800CF640,
    func_800CF660,
    func_800CF708,
};
