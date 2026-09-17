// MainObj, main_object_update_funcs[32]
// 8005C824..8005D1F4
#include "common.h"

void func_8005C824(struct MainObj* arg0)
{
    D_800FDD2C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005C860);

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005C960);

void func_8005CADC(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005CAFC(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_32.saved_unk5;
}

void func_8005CB08(struct MainObj* arg0)
{
    func_8005D118(arg0);
    D_800FDD5C[arg0->unk6](arg0);
}

void func_8005CB54(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk7C = 0xC8;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CB90);

void func_8005CC6C(struct MainObj* arg0)
{
    D_800FDD64[arg0->unk6](arg0);
}

void func_8005CCA8(struct MainObj* arg0)
{
    func_80015D60(arg0, 1);
    arg0->ext.main_32.unk80 = 5;
    arg0->unk20 = 0;
    arg0->unk54 = (const u8*)&D_800FDC80;
    arg0->unk50 = (const u8*)&D_800FDC80;
    arg0->unk6++;
}

void func_8005CCFC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.raw[0] == 0) {
        arg0->ext.raw[2] = 1;
        func_8005D148(arg0);
        arg0->ext.raw[0] = 13;
        arg0->unk6++;
    }
}

void func_8005CD5C(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->ext.main_32.unk80 == 0) {
        func_80015D60(arg0, 3);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}

void func_8005CDB0(struct MainObj* arg0)
{
    D_800FDD6C[arg0->unk6](arg0);
}

void func_8005CDEC(struct MainObj* arg0)
{
    s32* velocity;
    s32 selected;
    u8 step;

    func_80015D60(arg0, 3);
    velocity = D_800FDC90;
    if (arg0->unk15 & 0x40) {
        velocity++;
    }
    selected = *velocity;
    step = arg0->unk6;
    arg0->unk24 = FIXED(0.3125);
    arg0->unk20 = selected;
    arg0->unk6 = step + 1;
}

void func_8005CE50(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8005CE80(struct MainObj* arg0)
{
    D_800FDD74[arg0->unk6](arg0);
}

void func_8005CEBC(struct MainObj* arg0)
{
    s32* velocity;
    s32 selected;

    func_80015D60(arg0, 3);
    velocity = D_800FDC90;
    if (arg0->unk15 & 0x40) {
        velocity++;
    }
    selected = *velocity;
    arg0->unk50 = (const u8*)&D_800FDC80;
    arg0->unk24 = 0;
    arg0->ext.main_32.unk88 = 1;
    arg0->unk20 = selected;
    arg0->unk6++;
}

void func_8005CF30(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8005CF60(struct MainObj* arg0)
{
    D_800FDD7C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CF9C);

void func_8005D0A0(struct MainObj* arg0)
{
    s32 unused[1];
    s16 timer = arg0->unk7C;
    if (timer == 0) {
        arg0->unk6++;
    } else {
        arg0->unk7C = timer - 1;
    }
}

void func_8005D0D8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->unk24 += 0x100;
}

void func_8005D118(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

void func_8005D148(struct MainObj* arg0)
{
    struct ShotObj* temp_v0;

    temp_v0 = find_free_shot_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = 7;
        temp_v0->unk2 = 0;
        temp_v0->unk40 = arg0->unk40;
        temp_v0->unk42 = arg0->unk42;
        temp_v0->animation_table = (u32**)arg0->animation_table;
        temp_v0->unk3C = (u8*)arg0->sprite_frames;
        temp_v0->bg_offset = arg0->bg_offset;
        temp_v0->unk15 = arg0->unk15;
        temp_v0->x_pos.val = arg0->x_pos.val;
        temp_v0->y_pos.val = arg0->y_pos.val;
        temp_v0->unk7C = WEAPON_OBJECT(arg0);
        temp_v0->unk16 = 6;
    }
}
