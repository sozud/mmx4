// MainObj, main_object_update_funcs[70]
// 80088BA0..80089AA4
#include "common.h"

extern u8 D_80104A3C[];

void func_80088BA0(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_801049E4[arg0->state](arg0);
}

void func_80088BE8(struct MainObj* arg0)
{
    D_801049F0[arg0->unk5](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088C40);

void func_80088D30(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi >= 0x8E9) {
        func_80036AE4(0x14, 0x40);
        func_80015D60(arg0, 2);
        arg0->unk5++;
    }
}

void func_80088D8C(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 0);
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = arg0;
        arg0->unk7C = 3;
        arg0->unk5++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80088E04(struct MainObj* self)
{
    s16 timer;
    u8 count;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_8001540C(0, 0xE, NULL);
        self->unk7C = 3;
    }
    count = self->unk5C + 1;
    self->unk5C = count;
    if ((s8)count == 0x30) {
        func_80036B18();
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk7C = 0xA;
        self->state++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088EA4);

void func_80088F78(struct MainObj* arg0)
{
    D_80104A10[arg0->unk5](arg0);
    if ((arg0->unk5 < 3) && (arg0->state != 0)) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
    }
}

void func_80088FF0(struct MainObj* self)
{
    u8 i;

    for (i = 0; i < 4U; i++) {
        D_8013E188[i] = -1;
    }
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    self->ext.main_70.unk86 = 0;
    self->ext.main_70.unk80 = 0x28;
    self->ext.main_70.unk82 = 4;
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = NULL;
    self->unk7C = 0x28;
    self->unk7E = 5;
    self->unk42 &= ~0x8000;
    engine_obj.character_state.bytes[0] = 1;
    self->unk5++;
}

void func_800890B0(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0xA0;
        arg0->unk5++;
        return;
    }
    if (--arg0->unk7E == 0) {
        func_800AF878(BASE_OBJECT(arg0), 1, 0x10, 0x10);
        arg0->unk7E = 5;
    }
}

void func_80089138(struct MainObj* self)
{
    s16 countdown;
    u16 timer;

    if ((D_80141BD8.unk0 & 3) == 0) {
        func_80089798(self);
    }

    countdown = self->unk7E;
    if (countdown == 0) {
        func_80089910(self);
    } else {
        self->unk7E = countdown - 1;
    }

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 0x10) == 0) {
        self->unk5 = (u8)self->unk5 + 1;
    }
}

void func_800891C8(struct MainObj* arg0)
{
    func_800C813C(4, &D_801049AC, arg0);
    background_objects[0].unk1C = 0xA00;
    background_objects[0].unk24 = 0xA00;
    func_800DABE4(0, 0x9E0, 0x350);
    engine_obj.character_state.bytes[0] = 0;
    arg0->unk7C = 0x5A;
    arg0->on_screen = 0;
    arg0->unk7E = 5;
    arg0->unk5++;
}

void func_8008924C(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk5++;
        return;
    }
    if ((D_80141BD8.unk0 & 7) == 0) {
        self->y_pos.i.hi = (get_random() & 0x7F) + 0x360;
        func_800C813C(5, &D_801049B0, self);
    }
    timer = self->unk7E - 1;
    self->unk7E = timer;
    if (timer == 0) {
        func_800AF878(BASE_OBJECT(self), 1, 0x20, 0x20);
        self->unk7E = 5;
    }
}

void func_80089314(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80089334(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_70.saved_unk5;
}

void func_80089340(struct MainObj* arg0)
{
    D_80104A28[arg0->unk6](arg0);
}

void func_8008937C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 1);
        arg0->unk7C = 0x18;
        arg0->unk6++;
    }
}

void func_800893DC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->collision_data = (const u16*)D_80108104;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80089438(struct MainObj* arg0)
{
    D_80104A30[arg0->unk6](arg0);
}

void func_80089474(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 2);
    arg0->unk7C = 0x27;
    arg0->unk6++;
}

void func_800894BC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 0xD);
        func_80089588(arg0);
        arg0->unk7C = 0x18;
        arg0->unk6++;
    }
}

void func_80089524(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7C = 0x5A;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089588);

void func_80089798(struct MainObj* arg0)
{
    s16 x = background_objects[0].x_pos.i.hi;
    s16 y = background_objects[0].y_pos.i.hi;
    arg0->ext.main_70.unk85 = func_8002B780() % 4;
    switch (arg0->ext.main_70.unk85) {
    case 0:
        break;
    case 1:
        x += 0xA0;
        break;
    case 3:
        x += 0xA0;
        // Fall through.
    case 2:
        y += 0x78;
        break;
    }
    x += func_8002B780() % 0xA0;
    y += func_8002B780() % 0x78;
    func_800AFAB4(0, x, y, 0xFF);
    if ((D_80141BD8.unk0 & 3) == 0) {
        func_8001540C(0, D_80104A3C[(get_random() & 3) * 4], NULL);
    }
}

void func_80089910(struct MainObj* arg0)
{
    s16 timer;

    if (arg0->ext.main_70.unk87 != 0) {
        D_80104A4C[arg0->ext.main_70.unk86](arg0);
    } else {
        timer = arg0->ext.main_70.unk80 - 1;
        arg0->ext.main_70.unk80 = timer;
        if (timer == 0) {
            arg0->ext.main_70.unk87 = 1;
        }
    }
}

void func_80089984(struct MainObj* arg0)
{
    if (--arg0->ext.main_70.unk82 == 0) {
        arg0->ext.main_70.unk80 = 0x5A;
        need_palette_load |= 1;
        arg0->ext.main_70.unk82 = 4;
        arg0->ext.main_70.unk86 ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->ext.main_70.unk87 = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
    }
}

void func_80089A10(struct MainObj* arg0)
{
    s16 timer;

    timer = arg0->ext.main_70.unk82 - 1;
    arg0->ext.main_70.unk82 = timer;
    if (timer == 0) {
        arg0->ext.main_70.unk80 = 0x28;
        need_palette_load |= 1;
        arg0->ext.main_70.unk82 = 4;
        arg0->ext.main_70.unk86 ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->ext.main_70.unk87 = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}
