// WeaponObj, weapon_object_update_funcs[2]
// 80093CBC..800941D4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80093CBC);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80093D78);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80093EB4);

void func_80093FC4(struct WeaponObj* arg0)
{
    if (arg0->animation_step.fields.event & 0x40) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(0, 0x1A, arg0);
    }
    if (arg0->animation_step.fields.event & 0x80) {
        arg0->unk68 = D_8010884C;
        arg0->animation_step.fields.event = 0;
        arg0->unk67 = 0;
        arg0->unk5 = 1;
    }
}

void func_8009403C(struct WeaponObj* arg0)
{
    if (!(arg0->unk70 & 8)) {
        arg0->unk67 = -1;
        arg0->unk2C = 0x4200;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        arg0->unk5 = 2;
    }
}

void func_80094078(struct WeaponObj* arg0)
{
    u32 i;

    if (arg0->unk70 & 8) {
        func_8001540C(0, 0x1A, arg0);
        arg0->unk67 = 0;
        i = 0;
        do {
            func_8009416C(arg0);
            i++;
        } while (i < 4);
        func_80028B68(8, 6, 1);
        arg0->unk5 = 1;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_80094104(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    g_Player.unk98--;
    g_Player.unk99--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80094154(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
}

void func_8009416C(struct WeaponObj* arg0)
{
    struct MiscObj* temp_v0;

    temp_v0 = find_free_misc_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 1;
        temp_v0->id = 0x25;
        temp_v0->unk2 = 0;
        temp_v0->bg_offset = arg0->bg_offset;
        temp_v0->x_pos.val = arg0->x_pos.val;
        temp_v0->y_pos.val = arg0->y_pos.val;
    }
}
