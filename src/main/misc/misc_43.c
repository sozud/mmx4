// MiscObj, misc_object_update_funcs[43]
// 800D0374..800D07EC
#include "common.h"

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D03A8_jp);
#endif

void func_800D0374(struct MiscObj* arg0)
{
    D_8010F014[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D03B0);

INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D04D0);

void func_800D0528(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D0548);

INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D05B0);

INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D05F4);

INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D0658);

void func_800D0698(struct MiscObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_8002B718(MOVING_OBJECT(arg0));
        arg0->unk5 = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D06E0);

INCLUDE_ASM("main/nonmatchings/misc/misc_43", func_800D0754);

void func_800D07C0(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->state = 2;
        engine_obj.unkF = 1;
    }
}

union AnimationStep D_8010EFD8[1] = { { .packed = 0x00000101 } };

union AnimationStep D_8010EFDC[4] = {
    { .packed = 0x00010002 },
    { .packed = 0x02010002 },
    { .packed = 0x01010001 },
    { .packed = 0x01000101 },
};

union AnimationStep D_8010EFEC[7] = {
    { .packed = 0x02010002 },
    { .packed = 0x0001000A },
    { .packed = 0x02010002 },
    { .packed = 0x03010006 },
    { .packed = 0x00010002 },
    { .packed = 0x04010001 },
    { .packed = 0x04000101 },
};

union AnimationStep* D_8010F008[3] = {
    D_8010EFD8,
    D_8010EFDC,
    D_8010EFEC,
};

void (*D_8010F014[3])(struct MiscObj*) = {
    func_800D03B0,
    func_800D04D0,
    func_800D0528,
};

void (*D_8010F020[8])(struct MiscObj*) = {
    func_800D0548,
    func_800D05B0,
    func_800D05F4,
    func_800D0658,
    func_800D0698,
    func_800D06E0,
    func_800D0754,
    func_800D07C0,
};
