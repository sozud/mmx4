// VisualObj, visual_object_update_funcs[2]
// 800AEED8..800AF22C
#include "common.h"

void func_800AEED8(struct VisualObj* arg0)
{
    if (arg0->state == 0) {
        func_800AEF18(arg0);
    } else {
        func_800AF02C(arg0);
    }
}

void func_800AEF18(struct VisualObj* arg0)
{
    s32 temp_s0;
    s32 var_a1;

    arg0->on_screen = 1;
    if (arg0->unk2 == 9) {
        var_a1 = 0;
    }
    if (arg0->unk2 == 0x12) {
        var_a1 = 1;
    }
    if (arg0->unk2 == 0x14) {
        var_a1 = 2;
    }
    temp_s0 = var_a1;
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + ((u32*)SP_SPRITE_FRAMES)[D_8010A1BC[temp_s0].archive_slot];
    arg0->animation_table = &D_8011BF40;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7802;
    arg0->unk16 = 0;
    arg0->unk15 = g_Player.unk15;
    arg0->unk5C = 0;
    func_800AF1AC(arg0);
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    func_80015D60(arg0, D_8010A1BC[temp_s0].animation);
    func_8001540C(1, D_8010A1BC[temp_s0].sound, arg0);
    arg0->state++;
    func_8002B318(arg0, 0x40, 0x20);
}

void func_800AF02C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    func_800AF1AC(arg0);
    if (arg0->unk5 == 0) {
        func_800AF084(arg0);
    } else {
        func_800AF15C(arg0);
    }
}

void func_800AF084(struct VisualObj* arg0)
{
    struct WeaponObj* temp_v0;

    if (arg0->animation_step.fields.event != 0) {
        temp_v0 = find_free_weapon_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 0x21;
            temp_v0->id = arg0->unk2;
            temp_v0->unk2 = 0;
            temp_v0->x_pos.val = arg0->x_pos.val;
            temp_v0->y_pos.val = arg0->y_pos.val;
            temp_v0->unk15 = arg0->unk15;
            temp_v0->unk3C = arg0->unk3C;
            temp_v0->animation_table = arg0->animation_table;
            temp_v0->unk40 = arg0->unk40;
            temp_v0->unk42 = arg0->unk42;
            temp_v0->unk16 = arg0->unk16;
        }
        arg0->unk5++;
    }
    func_8002B318(arg0, 0x40, 0x20);
}

void func_800AF15C(struct VisualObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0 || arg0->unk5C != 0) {
        ZeroObjectState(arg0);
    } else {
        func_8002B318(arg0, 0x40, 0x20);
    }
}

void func_800AF1AC(struct VisualObj* arg0)
{
    struct PlayerObj* entity = &g_Player;

    if (arg0->unk5C == 0) {
        if (entity->unk8E == 0) {
            arg0->unk5C = 1;
        }
        if (entity->unk15 != arg0->unk15) {
            arg0->unk5C = 1;
        }
        if (arg0->unk5C == 0) {
            func_80092E2C(arg0, entity, arg0->unk2);
        }
    }
}
