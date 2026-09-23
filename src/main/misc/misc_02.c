// MiscObj, misc_object_update_funcs[2]
// 800C7EDC..800C85D0
#include "common.h"

void func_800C7EDC(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800C7F1C(arg0);
    } else {
        func_800C80D8(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C7F1C);

void func_800C80D8(struct MiscObj* arg0)
{
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        func_8002B694(ANIMATED_OBJECT(arg0));
        arg0->on_screen ^= 1;
        if (arg0->on_screen != 0) {
            is_on_screen(BASE_OBJECT(arg0));
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_800C813C(s32 arg0, void* arg1, void* arg2)
{
    s32 var_s1;
    u8 temp_v0_2;
    u8* var_s3;
    struct MainObj* var_s2;
    struct MiscObj* temp_v0;

    var_s3 = arg1;
    var_s1 = arg0;
    var_s2 = arg2;
    if (var_s1 & 0xFF) {
        do {
            temp_v0 = find_free_misc_obj();
            if (temp_v0 != NULL) {
                temp_v0->active = 0x41;
                temp_v0->id = 3;
                temp_v0->unk2 = 0;
                temp_v0->unk15 = get_random() & 0x40;
                temp_v0->state = 0;
                temp_v0->unk5 = 0;
                temp_v0->unk6 = 0;
                temp_v0->x_pos.val = var_s2->x_pos.val + ((get_random() & 3) << 16);
                temp_v0->y_pos.val = var_s2->y_pos.val + ((get_random() & 3) << 16);
                temp_v0_2 = *var_s3;
                var_s3 += 1;
                temp_v0->ext.misc_2.owner = var_s2;
                temp_v0->ext.misc_2.unk58 = temp_v0_2;
            }
            var_s1 -= 1;
        } while (var_s1 & 0xFF);
    }
}

void func_800C8214(s32 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 var_s1;
    u8* var_s3;
    s16 var_s4;
    struct MainObj* var_s2;
    struct MiscObj* temp_v0;
    struct MiscObj* obj;
    u8 temp_v1;

    var_s3 = arg1;
    var_s1 = arg0;
    var_s4 = arg3;
    var_s2 = arg2;
    if (var_s1 & 0xFF) {
        do {
            temp_v0 = find_free_misc_obj();
            if (temp_v0 != NULL) {
                obj = temp_v0;
                obj->active = 0x41;
                obj->id = 3;
                obj->unk2 = 1;
                obj->unk15 = get_random() & 0x40;
                obj->state = 0;
                obj->unk5 = 0;
                obj->unk6 = 0;
                obj->x_pos.val = var_s2->x_pos.val + (get_random() & 3) + arg4;
                obj->y_pos.val = var_s2->y_pos.val + (get_random() & 3) + arg5;
                temp_v1 = *var_s3;
                obj->ext.misc_2.owner = var_s2;
                obj->unk42 = var_s4;
                obj->ext.misc_2.unk58 = temp_v1;
                obj->unk3C = ANIMATED_OBJECT(obj->ext.misc_2.owner)->unk3C;
                obj->animation_table = ANIMATED_OBJECT(obj->ext.misc_2.owner)->animation_table;
                var_s3 += 1;
                obj->unk40 = obj->ext.misc_2.owner->unk40;
            }
            var_s1 -= 1;
        } while (var_s1 & 0xFF);
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C833C);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C842C);

s32 D_8010DAC8[8] = { -0x30000, -0x20000, 0x18000, 0x28000, -0x38000, -0x28000, 0x20000, 0x30000 };
s32 D_8010DAE8[8] = { 0x38000, 0x48000, 0x60000, 0x30000, 0x40000, 0x50000, 0x58000, 0x28000 };
