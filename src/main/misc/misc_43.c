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

void func_800D0548(struct MiscObj* arg0)
{
    if (background_objects[g_Player.bg_offset].x_pos.i.hi == 0x12F0) {
        func_80036AE4(0x15, 0);
        arg0->unk5 = 1;
    }
}

void func_800D05B0(struct MiscObj* arg0)
{
    if (g_Player.unkC0 == -1) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 2;
    }
}

void func_800D05F4(struct MiscObj* arg0)
{
    u16 sound_id;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        sound_id = 0x27;
        if (engine_obj.cur_character == 0) {
            sound_id = 0x2E;
        }
        func_8002217C(sound_id, 0xFF, 0);
        arg0->unk5 = 3;
    }
}

void func_800D0658(struct MiscObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 4;
    }
}

void func_800D0698(struct MiscObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_8002B718(MOVING_OBJECT(arg0));
        arg0->unk5 = 5;
    }
}

void func_800D06E0(struct MiscObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->y_pos.i.hi < background_objects[g_Player.bg_offset].y_pos.i.hi - 0x30) {
        arg0->ext.unk.unk54 = 0x3C;
        arg0->unk5 = 6;
    }
}

void func_800D0754(struct MiscObj* arg0)
{
    if (--arg0->ext.unk.unk54 != 0) {
        return;
    }
    func_8002217C(engine_obj.cur_character == 0 ? 0x2F : 0x28, 0, 0);
    arg0->unk5 = 7;
}

void func_800D07C0(struct MiscObj* arg0)
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
