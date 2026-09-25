#include "common.h"

extern u16 D_800F44E8[8];
extern u16 D_800F44F8[8];
extern u8 D_800F4528[0x1C];
extern u8 D_800F4544[0x1C];

// might also be inlined inside reset_objects
void func_80029DBC(void)
{
    u16 a1;
    u16 var_v1;
    u8* a0;
    u8 fill = 0;

    for (a1 = 0; a1 < COUNT(unk_objects); a1++) {
        a0 = (u8*)&unk_objects[a1];
        var_v1 = sizeof(unk_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }
}

void func_80029E1C(struct GameInfo* arg0)
{
    struct UnkObj* obj;
    u8* var_s1;

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->unk2 = 0x5E;
        obj->id = 0;
        obj->y_pos.i.hi = 0x10;
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = 0;
        obj->unk2 = -1;
        if (D_80141BE0 != 0) {
            obj->link.data = D_800F4568;
        } else {
            obj->link.data = D_800F457C;
        }
#ifdef VERSION_JP
        obj->x_pos.i.hi = 0x20;
#else
        obj->x_pos.i.hi = 0x38;
#endif
    }

    if (D_80141BE0 != 0) {
        var_s1 = D_800F4508;
    } else {
        var_s1 = D_800F4560[engine_obj.cur_character];
    }
    while (var_s1[0] != 0xFF) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0;
            obj->unk2 = var_s1[0];
            obj->y_pos.i.hi = var_s1[1];
            obj->unk7 = var_s1[2];
        }
        if (var_s1[2] == 7) {
            break;
        }
        var_s1 += 3;
    }

    var_s1 = D_800F457C;
    if (D_80141BE0 != 0) {
        var_s1 = D_800F4568;
    }
    if (var_s1[1] != 7) {
        do {
            obj = find_free_unk_obj();
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 0;
                obj->unk2 = var_s1[1];
                obj->y_pos.i.hi = var_s1[0];
            }
            var_s1 += 2;
        } while (var_s1[1] != 7);
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->unk2 = -2;
        obj->id = 0;
        obj->x_pos.i.hi = 0x20;
    }

    if (D_80141BE0 == 0) {
        func_8001E980(0);
    }
    D_80141BDF[0] = 0;
    func_800129A4(8);
    D_8013B7D0++;
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002A098);

void func_8002A394(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (D_80141BE0 != 0) {
            arg0->unk0 = 8;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        } else {
            (*(s8*)&arg0->unk6)++;
        }
        func_80029DBC();
        if (D_80141BE0 != 0) {
            func_8001E980(1);
        }
        D_8013B7D0 = 0;
    }
}

void func_8002A41C(struct GameInfo* arg0)
{
    func_8002B460(); // no-op
    D_800F4590[D_8013B7D0](arg0);
    update_unk_objects();
    func_80016124();
    func_80025CDC();
}

void func_8002A484(void)
{
    u32 mask;
    u32 color;
    u16 copy_color;
    u16* dst;
    u16* src;
    u32 component;
    u32 blue;
    u32 green;
    u32 color_index;
    u32 red;
    u32 palette_index;

    if ((((g_FilterAmountB | (g_FilterAmountR | g_FilterAmountG)) != 0) || (need_palette_load & 4)) && ((lastFilterAmountR != g_FilterAmountR) || (lastFilterAmountG != g_FilterAmountG) || (lastFilterAmountB != g_FilterAmountB) || (need_palette_load != 0))) {
        src = dst = SP_PALETTE;
        dst = D_80141F70;
        for (palette_index = 0; palette_index < 128; palette_index++, mask <<= 1) {
            if (!(palette_index & 0x1F)) {
                mask = D_8013E188[palette_index >> 5];
            }
            color_index = 0;
            if ((s32)mask < 0) {
                do {
                    color = *src;
                    src++;
                    if (color != 0) {
                        if (g_FilterModeR != 0) {
                            red = 0;
                            if ((color & 0x1F) >= g_FilterAmountR) {
                                red = (color & 0x1F) - g_FilterAmountR;
                            }
                        } else {
                            component = (color & 0x1F) + g_FilterAmountR;
                            red = 0x1F;
                            if (component < 0x20U) {
                                red = component;
                            }
                        }
                        if (g_FilterModeG != 0) {
                            green = 0;
                            if ((color & 0x3E0) >= g_FilterAmountG) {
                                green = (color & 0x3E0) - g_FilterAmountG;
                            }
                        } else {
                            component = (color & 0x3E0) + g_FilterAmountG;
                            green = 0x3E0;
                            if (component < 0x3E1U) {
                                green = component;
                            }
                        }
                        if (g_FilterModeB != 0) {
                            blue = 0;
                            if ((color & 0x7C00) >= g_FilterAmountB) {
                                blue = (color & 0x7C00) - g_FilterAmountB;
                            }
                        } else {
                            component = (color & 0x7C00) + g_FilterAmountB;
                            blue = 0x7C00;
                            if (component < 0x7C01U) {
                                blue = component;
                            }
                        }
                        *dst = red | green | blue | (color & 0x8000);
                    }
                    color_index += 1;
                    dst++;
                } while (color_index < 0x10U);
            } else {
                do {
                    copy_color = *src;
                    src++;
                    color_index += 1;
                    *dst = copy_color;
                    dst++;
                } while (color_index < 0x10U);
            }
        }
        need_palette_load = 2;
        lastFilterAmountR = g_FilterAmountR;
        lastFilterAmountG = g_FilterAmountG;
        lastFilterAmountB = g_FilterAmountB;
    }
}

u16 D_800F44E8[8] = { 0x10, 0x80, 0x100, 0x40, 0x20, 0x200, 0x400, 0xFFFF };

u16 D_800F44F8[8] = { 0x80, 0x10, 0x40, 0x20, 4, 1, 8, 2 };

u8 D_800F4508[0x20] = {
    0x5F,
    0x28,
    0x00,
    0x60,
    0x38,
    0x00,
    0x61,
    0x48,
    0x01,
    0x62,
    0x58,
    0x02,
    0x63,
    0x68,
    0x03,
    0x64,
    0x78,
    0x04,
    0x65,
    0x88,
    0x04,
    0x66,
    0x98,
    0x05,
    0x67,
    0xA8,
    0x06,
    0x70,
    0xB8,
    0x07,
    0xFF,
    0x00,
};

u8 D_800F4528[0x1C] = {
    0x5F,
    0x30,
    0x00,
    0x61,
    0x40,
    0x01,
    0x62,
    0x50,
    0x02,
    0x63,
    0x60,
    0x03,
    0x64,
    0x70,
    0x04,
    0x66,
    0x80,
    0x05,
    0x67,
    0x90,
    0x06,
    0x70,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};

u8 D_800F4544[0x1C] = {
    0x60,
    0x30,
    0x00,
    0x61,
    0x40,
    0x01,
    0x62,
    0x50,
    0x02,
    0x63,
    0x60,
    0x03,
    0x65,
    0x70,
    0x04,
    0x66,
    0x80,
    0x05,
    0x67,
    0x90,
    0x06,
    0x70,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};

u8* D_800F4560[2] = { D_800F4528, D_800F4544 };

u8 D_800F4568[0x14] = {
    0x30,
    0x00,
    0x48,
    0x01,
    0x58,
    0x02,
    0x68,
    0x03,
    0x80,
    0x04,
    0x98,
    0x05,
    0xA8,
    0x06,
    0xB8,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};

u8 D_800F457C[0x14] = {
    0x30,
    0x00,
    0x40,
    0x01,
    0x50,
    0x02,
    0x60,
    0x03,
    0x70,
    0x04,
    0x80,
    0x05,
    0x90,
    0x06,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};

void (*D_800F4590[])(struct GameInfo* arg0) = {
    func_80029E1C,
    func_8002A098,
    func_8002A394,
};
