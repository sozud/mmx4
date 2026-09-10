// MiscObj, misc_object_update_funcs[4]
// 800C8774..800C8FA8
#include "common.h"

void func_800C8774(struct MiscObj* arg0)
{
    D_8010DC18[arg0->state](arg0);
}

void func_800C87B0(struct MiscObj* arg0)
{
    s16 owner_count;
    s32 adjusted_x;
    s32 random_y;
    s32 random_x;
    s32 resource_index;
    s32 clut_x;
    s32* menu_frame_offsets;
    s32 adjusted_y;
    struct MainObj* owner;

    owner = arg0->ext.misc_4.owner;
    arg0->animation_table = D_8010DBC0;
    random_x = func_8002938C(0x85);
    random_y = func_8002938C(0x85);
    clut_x = random_x * 4 + 0x18;
    adjusted_x = clut_x;
    if (clut_x < 0) {
        adjusted_x = clut_x + 0xF;
    }
    adjusted_y = random_y + 6;
    clut_x -= (adjusted_x >> 4) * 0x10;
    if (adjusted_y < 0) {
        adjusted_y = random_y + 9;
    }
    arg0->unk42 = clut_x | (((adjusted_y >> 2) + 0x1E0) << 6);
    resource_index = func_8002938C(0x85, adjusted_y, random_y);
    arg0->unk40 = D_801406A8[resource_index] >> 7;

    resource_index = func_8002938C(0x85);
    menu_frame_offsets = SP_MENU_FRAMES;
    resource_index = menu_frame_offsets[resource_index];
    arg0->bg_offset = 0;
    arg0->unk3C = (u8*)menu_frame_offsets + resource_index;
    arg0->unk15 = get_random() & 0x40;
    arg0->unk16 = 7;
    arg0->x_vel.val = 0;
    func_800C813C(8, D_8010DBF8, arg0);
    func_800AF828(arg0, 2);
    func_8001540C(5, 1, arg0);
    func_80028BAC(0x14, 4, 2);

    arg0->animation_step.fields.frame_index = arg0->unk2;
    arg0->state++;
    owner_count = owner->unk7C;
    if (owner_count >= 0x15) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    owner->unk7C = owner_count + 1;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C8938(struct MiscObj* arg0)
{
    struct MainObj* temp_s1;

    temp_s1 = arg0->ext.misc_4.owner;
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }

    temp_s1->unk7C--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_04", func_800C899C);

INCLUDE_ASM("main/nonmatchings/misc/misc_04", func_800C8B74);

INCLUDE_ASM("main/nonmatchings/misc/misc_04", func_800C8BDC);

INCLUDE_ASM("main/nonmatchings/misc/misc_04", func_800C8E90);
