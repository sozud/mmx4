// MiscObj, misc_object_update_funcs[3]
// 800C85D0..800C8774
#include "common.h"

void func_800C8610(struct MiscObj* arg0);
void func_800C8708(struct MiscObj* arg0);

void func_800C85D0(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800C8610(arg0);
    } else {
        func_800C8708(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_03", func_800C8610);

void func_800C8708(struct MiscObj* arg0)
{
    u8 temp_v0;

    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        func_8002B694((struct AnimatedObj*)arg0);
        func_80015DC8(arg0);
        temp_v0 = arg0->on_screen ^ 1;
        arg0->on_screen = temp_v0;
        if (temp_v0 != 0) {
            is_on_screen(BASE_OBJECT(arg0));
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

s32 D_8010DB48[8] = { -0x30000, -0x20000, 0x18000, 0x28000, -0x38000, -0x28000, 0x20000, 0x30000 };
s32 D_8010DB68[8] = { 0x38000, 0x48000, 0x60000, 0x30000, 0x40000, 0x50000, 0x58000, 0x28000 };
