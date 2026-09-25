// ItemObj, item_object_update_funcs[25]
// 800C42EC..800C4544
#include "common.h"

void func_800C42EC(struct ItemObj* arg0)
{
    if (arg0->state == 0) {
        arg0->state++;
        arg0->unk58 = (const u8*)D_80106270;
        arg0->unk54 = D_8010D198;
        arg0->animation_table = (const u8* const*)D_8010DF48;
        arg0->bg_offset = g_Player.bg_offset;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x99)];
        arg0->unk40 = D_801406A8[func_8002938C(0x99)] >> 7;
        arg0->unk42 = SOME_COORDINATE_CONVERSION(func_8002938C(0x99));
        arg0->unk16 = 7;
        arg0->unk15 = 0;
    } else if (func_8002DD04(MAIN_OBJECT(arg0)) != 0) {
        func_800DABE4(0x26, 0x430, 0x170);
        get_random();
        func_800C833C(5, D_8010D1BC[0], (struct MiscObj*)arg0, FIXED(48), FIXED(32));
        func_800C833C(5, D_8010D1BC[1], (struct MiscObj*)arg0, FIXED(-32), FIXED(16));
        func_800C833C(5, D_8010D1BC[2], (struct MiscObj*)arg0, 0, 0);
        func_800C833C(5, D_8010D1BC[3], (struct MiscObj*)arg0, FIXED(24), FIXED(-16));
        func_800C833C(5, D_8010D1BC[0], (struct MiscObj*)arg0, FIXED(-24), FIXED(-32));
        func_800C833C(5, D_8010D1BC[1], (struct MiscObj*)arg0, FIXED(16), FIXED(-24));
        func_800C833C(5, D_8010D1BC[2], (struct MiscObj*)arg0, FIXED(-16), FIXED(24));
        func_8002B108(OBJECT_HEADER(arg0));
    } else if (func_8002B1E8(BASE_OBJECT(arg0), 0x70, 0x50) == 1) {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}
