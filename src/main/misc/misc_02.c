// MiscObj, misc_object_update_funcs[2]
// 800C7EDC..800C85D0
#include "common.h"

void func_800C7EDC(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800C7F1C();
    } else {
        func_800C80D8();
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C7F1C);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C80D8);

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

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C8214);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C833C);

INCLUDE_ASM("main/nonmatchings/misc/misc_02", func_800C842C);
