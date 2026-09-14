// MainObj, main_object_update_funcs[55]
// 8006EB40..8006FD50
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006EB40);

void func_8006ECC4(struct MainObj* arg0)
{
    s32 distance;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    distance = arg0->x_pos.val - background_objects[arg0->bg_offset].x_pos.val;
    if (distance > FIXED(48) && distance < FIXED(272)) {
        arg0->unk5 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006ED44);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006EF28);

void func_8006F0A0(struct MainObj* arg0)
{
    D_801007F8[arg0->unk2](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F0DC);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F244);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F304);

void func_8006F41C(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 0);
        if (arg0->unk2 == 1) {
            arg0->unk24 = FIXED(-2);
            arg0->unk6++;
        } else {
            arg0->unk5 = 1;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8006F494(struct MainObj* arg0)
{
    s32 y_diff;

    y_diff = g_Player.y_pos.val - arg0->y_pos.val;
    if (y_diff >= 0) {
        if (y_diff <= 0xFFFFF) {
            goto set_state;
        }
    } else if (arg0->y_pos.val - g_Player.y_pos.val <= 0xFFFFF) {
    set_state:
        arg0->unk5 = 1;
        arg0->unk6 = 0;
    }
    func_80015DC8(arg0);
}

void func_8006F504(struct MainObj* arg0)
{
    D_80100800[arg0->unk6](arg0);
    arg0->unk20 = background_objects[arg0->bg_offset].unk47 << 0x10;
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8006F584(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7++;
        func_80015D60(arg0, 4);
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk7 = 0;
        arg0->unk7C = 0;
        arg0->ext.main_55.unk85 = 0;
        arg0->ext.main_55.unk86 = 0;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F5F4);

void func_8006F7B4(struct MainObj* arg0)
{
    D_80100810[arg0->unk6](arg0);
    arg0->unk20 = background_objects[arg0->bg_offset].unk47 << 0x10;
    func_80015DC8(arg0);
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8006F83C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F86C);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006FA24);

void func_8006FABC(struct MainObj* arg0)
{
    engine_obj.enable_boss = 0;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_8006FAE4(struct MainObj* arg0)
{
    D_80100838[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006FB20);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006FBFC);

s32 func_8006FCB8(struct PlayerObj* arg0, s32 arg1, s32 arg2)
{
    s16 temp_a1;
    s16 temp_a2;
    s32 temp_v0;
    u8 tile;
    s32 temp_v1;
    s32 var_v0;

    temp_a1 = arg0->x_pos.u.hi + arg1;
    temp_a2 = arg0->y_pos.u.hi + arg2;
    temp_v0 = ((s32(*)(struct PlayerObj*, s16, s16))func_8002D724)(
        arg0, temp_a1, temp_a2);
    tile = temp_v0;
    var_v0 = 1;
    if ((u32)((temp_v0 - 0x10) & 0xFF) >= 9U) {
        temp_v1 = tile;
        if (temp_v1 == 0x38) {
            return (arg0->y_pos.i.hi >= 0x121) * 2;
        }
        var_v0 = -(temp_v1 == 0x24) & 3;
        return var_v0;
    }
    return var_v0;
}
