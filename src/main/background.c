// BackgroundObj
// 8002771C..80028B68
#include "common.h"

void func_80027E28(struct BackgroundObj* arg0);
void func_80027EE8(struct BackgroundObj* arg0);
void func_800282D0(struct BackgroundObj* arg0);
void func_80028450(struct BackgroundObj* arg0);
void func_80028AD8(struct BackgroundObj* arg0);

void func_8002771C(void)
{
    struct BackgroundObj* obj = background_objects;
    u32 i;
    u8* ptr;

    for (i = 0; i < 3; i++) {
        obj->unk0 = 1;
        obj->unk3 = 1;
        obj->unk44 = 1;
        obj->unk4D = 0;
        obj->min_y = 0;
        obj->unk4E = layout_width - 1;
        obj->max_y = layout_height - 1;
        obj++;
    }

    ptr = (u8*)D_800F3188.records + ((engine_obj.stage * sizeof(struct BackgroundLayoutConfig) * 2) + (engine_obj.substage * sizeof(struct BackgroundLayoutConfig)));
    D_80173C6C[0] = *ptr++;
    D_80173C6C[1] = *ptr++;
    D_80173C6C[2] = *ptr++;
    D_80173C6C[3] = *ptr++;
    background_objects[0].unk4B = *ptr++;
    background_objects[0].unk4A = *ptr++;
    background_objects[1].unk4B = *ptr++;
    background_objects[1].unk4A = *ptr++;
    background_objects[2].unk4B = *ptr++;
    background_objects[2].unk4A = *ptr++;
}

void func_80027850(void)
{
    struct BackgroundObj* bg_obj = &background_objects[0];
    if ((bg_obj->unk44 != 0) && (g_Player.unkBC == 0)) {
        D_800F3134[bg_obj->unk4](bg_obj);
        if (bg_obj->unk34 & 0x10) {
            func_80028A48(bg_obj);
        }
        if (bg_obj->unk34 & 1) {
            func_80028AD8(bg_obj);
        }
        func_80028690(bg_obj);
    }
}

void func_80027908(struct BackgroundObj* arg0)
{
    arg0->unk47 = 2;
    arg0->unk48 = 8;
    arg0->unk2C = 0x60;
    arg0->unk2E = 0xC0;
    arg0->unk30 = 0xA0;
    arg0->unk32 = 0xA0;
    arg0->unk14.val = arg0->x_pos.val;
    arg0->unk18.val = arg0->y_pos.val;
    arg0->unk24 = arg0->unk1C;
    arg0->unk26 = arg0->unk1E;
    arg0->unk28 = arg0->unk20;
    arg0->unk2A = arg0->unk22;
    arg0->unk4++;
}

void func_80027974(struct BackgroundObj* arg0)
{
    s32 temp_a1;
    arg0->unk14.val = arg0->x_pos.val;
    temp_a1 = arg0->y_pos.val;
    arg0->unk18.val = temp_a1;
    arg0->unk49 = -arg0->unk48;
    func_80027A5C(arg0);
    func_80027AAC(arg0);
    func_80027AFC(arg0);
    func_80027B70(arg0);
    func_80027BE4(arg0);
}

void func_800279D8(struct BackgroundObj* arg0)
{
    s32 scroll_x;

    arg0->unk14.val = arg0->x_pos.val;
    arg0->unk18.val = arg0->y_pos.val;
    arg0->unk49 = -(u8)arg0->unk48;
    func_80027AAC(arg0);
    func_80027AFC(arg0);
    func_80027BE4(arg0);
    scroll_x = background_objects[0].x_pos.i.hi;
    if (scroll_x < 0) {
        scroll_x += 3;
    }
    background_objects[0].y_pos.i.hi = (u16)background_objects[0].unk20 - (scroll_x >> 2);
}

void func_80027A5C(struct BackgroundObj* a0)
{
    s16 v0, v1;

    v1 = g_Player.y_pos.i.hi - a0->y_pos.i.hi;
    v0 = v1 - a0->unk2C;

    if (v0 >= 0) {
        v0 = v1 - a0->unk2E;

        if (v0 <= 0) {
            return;
        }
    }

    a0->y_pos.i.hi = v0 + a0->y_pos.i.hi;
}

void func_80027AAC(struct BackgroundObj* a0)
{
    s16 v0, v1;

    v1 = g_Player.x_pos.i.hi - a0->x_pos.i.hi;
    v0 = v1 - a0->unk30;

    if (v0 >= 0) {
        v0 = v1 - a0->unk32;

        if (v0 <= 0) {
            return;
        }
    }

    a0->x_pos.i.hi = v0 + a0->x_pos.i.hi;
}

void func_80027AFC(struct BackgroundObj* arg0)
{
    s16 delta;

    delta = arg0->x_pos.i.hi - arg0->unk14.i.hi;
    if (delta >= 0) {
        if (delta >= arg0->unk48) {
            delta = arg0->unk48;
        }
        arg0->x_pos.i.hi = delta + arg0->unk14.i.hi;
    } else {
        if (delta < arg0->unk49) {
            delta = arg0->unk49;
        }
        arg0->x_pos.i.hi = delta + arg0->unk14.i.hi;
    }
}

void func_80027B70(struct Unk9* arg0)
{
    s16 delta;
    u16 base;
    s8 temp;
    u16 temp2;

    temp2 = *(u16*)((u8*)arg0 + 0xE);
    base = *(u16*)((u8*)arg0 + 0x1A);
    delta = temp2 - base;

    if (delta >= 0) {
        temp = arg0->unk48;
        if (delta >= temp) {
            delta = temp;
        }
    } else {
        temp = arg0->unk49;
        if (delta < temp) {
            delta = temp;
        }
    }

    *(u16*)((u8*)arg0 + 0xE) = delta + base;
}

void func_80027BE4(struct BackgroundObj* arg0)
{
    s16 temp_v1;

    if (arg0->unk1C < arg0->x_pos.i.hi) {
        arg0->x_pos.i.hi = arg0->unk1C;
        if (engine_obj.stage != 5 || g_Player.unkC5 == 0) {
            temp_v1 = arg0->unk1C + 0x140;
            if (g_Player.x_pos.i.hi + 8 >= temp_v1) {
                g_Player.x_pos.i.hi = arg0->unk1C + 0x138;
            }
            goto label;
        }
    } else {
    label:
        if (arg0->unk1E >= arg0->x_pos.i.hi) {
            arg0->x_pos.i.hi = arg0->unk1E;
            if (engine_obj.stage != 5 || g_Player.unkC5 == 0) {
                temp_v1 = arg0->unk1E;
                if (g_Player.x_pos.i.hi - 8 < temp_v1) {
                    g_Player.x_pos.i.hi = temp_v1 + 8;
                }
            }
        }
    }

    if (arg0->unk20 < arg0->y_pos.i.hi) {
        arg0->y_pos.i.hi = arg0->unk20;
        temp_v1 = arg0->unk20 + 0x100;
        if (g_Player.y_pos.i.hi - 8 >= temp_v1) {
            g_Player.unk5C = -0x80;
        }
    } else {
        if (arg0->unk22 >= arg0->y_pos.i.hi) {
            arg0->y_pos.i.hi = arg0->unk22;
        }
    }
}

void func_80027D40(void)
{
    struct BackgroundObj* ptr = &background_objects[1];
    if (ptr->unk44 != 0 && g_Player.unkBC == 0) {
        ptr->unk14.val = ptr->x_pos.val;
        ptr->unk18.val = ptr->y_pos.val;
        D_800F3140[ptr->unk4](ptr);
    }
}

void func_80027DC0(struct BackgroundObj* arg0)
{
    // overlap with D_800F32D5
    arg0->unk4 = D_800F32D4[engine_obj.stage][engine_obj.substage].primary;
}

void func_80027DF0(struct BackgroundObj* arg0)
{
    func_80027E28(arg0);
    func_80027EE8(arg0);
    func_80027FA8(arg0);
}

void func_80027E28(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].y_pos.i.hi;
    v0 = arg0->unk42 + (v0 >> 1);
    arg0->y_pos.i.hi = v0;
}

void func_80027E48(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].y_pos.i.hi;
    v0 = arg0->unk42 + (v0 >> 2);
    arg0->y_pos.i.hi = v0;
}

void func_80027E68(struct BackgroundObj* arg0)
{
    s16 value = background_objects[0].y_pos.i.hi;
    value >>= 1;
    value = value + (value >> 1);
    value = arg0->unk42 + value;
    arg0->y_pos.i.hi = value;
}

void func_80027E90(struct BackgroundObj* arg0)
{
    volatile u16* background = (volatile u16*)&background_objects[0].y_pos.i.hi;
    s16 value = background[0];
    s16 second = background[0];
    value >>= 2;
    value += second;
    value = arg0->unk42 + value;
    arg0->y_pos.i.hi = value;
}

void func_80027EBC(struct BackgroundObj* arg0)
{
    volatile u16* background = (volatile u16*)&background_objects[0].y_pos.i.hi;
    s16 value = background[0];
    s16 second = background[0];
    value >>= 1;
    value += second;
    value = arg0->unk42 + value;
    arg0->y_pos.i.hi = value;
}

void func_80027EE8(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].x_pos.i.hi;
    v0 = arg0->unk40 + (v0 >> 1);
    arg0->x_pos.i.hi = v0;
}

void func_80027F08(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].x_pos.i.hi;
    v0 = arg0->unk40 + (v0 >> 2);
    arg0->x_pos.i.hi = v0;
}

void func_80027F28(struct BackgroundObj* arg0)
{
    s16 value = background_objects[0].x_pos.i.hi;
    value >>= 1;
    value = value + (value >> 1);
    value = arg0->unk40 + value;
    arg0->x_pos.i.hi = value;
}

void func_80027F50(struct BackgroundObj* arg0)
{
    volatile u16* background = (volatile u16*)&background_objects[0].x_pos.i.hi;
    s16 value = background[0];
    s16 second = background[0];
    value >>= 2;
    value += second;
    value = arg0->unk40 + value;
    arg0->x_pos.i.hi = value;
}

void func_80027F7C(struct BackgroundObj* arg0)
{
    volatile u16* background = (volatile u16*)&background_objects[0].x_pos.i.hi;
    s16 value = background[0];
    s16 second = background[0];
    value >>= 1;
    value += second;
    value = arg0->unk40 + value;
    arg0->x_pos.i.hi = value;
}

#define FUNC_NAME func_80027FA8

#include "helpers/bg_is_on_screen.h"

#undef FUNC_NAME

void func_80028070(struct BackgroundObj* arg0)
{
    arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + arg0->unk40;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi + arg0->unk42;
    func_80027FA8(arg0);
}

void func_800280BC(struct BackgroundObj* arg0)
{
    func_80027E48(arg0);
    func_80027F08(arg0);
    func_80027FA8(arg0);
}

void func_800280F4(struct BackgroundObj* arg0)
{
    func_80027EE8(arg0);
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi + arg0->unk42;
    func_80027FA8(arg0);
}

void func_80028138(void)
{
}

void func_80028140(struct BackgroundObj* arg0)
{
    func_80027F28(arg0);
    func_80027E68(arg0);
    func_80027FA8(arg0);
}

void func_80028178(struct BackgroundObj* arg0)
{
    func_80027F50(arg0);
    func_80027E90(arg0);
    func_80027FA8(arg0);
}

void func_800281B0(struct BackgroundObj* arg0)
{
    func_80027F7C(arg0);
    func_80027EBC(arg0);
    func_80027FA8(arg0);
}

void func_800281E8(void)
{
    struct BackgroundObj* ptr = &background_objects[2];
    if (ptr->unk44 != 0 && g_Player.unkBC == 0) {
        ptr->unk14.val = ptr->x_pos.val;
        ptr->unk18.val = ptr->y_pos.val;
        D_800F3164[ptr->unk4](ptr);
    }
}

void func_80028268(struct BackgroundObj* arg0)
{
    arg0->unk4 = D_800F32D4[engine_obj.stage][engine_obj.substage].secondary;
}

void func_80028298(struct BackgroundObj* arg0)
{
    func_800282D0(arg0);
    func_80028390(arg0);
    func_80028450(arg0);
}

void func_800282D0(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].y_pos.i.hi;
    v0 = arg0->unk42 + (v0 >> 1);
    arg0->y_pos.i.hi = v0;
}

void func_800282F0(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].y_pos.i.hi;
    v0 = arg0->unk42 + (v0 >> 2);
    arg0->y_pos.i.hi = v0;
}

void func_80028310(struct BackgroundObj* arg0)
{
    s16 value = background_objects[0].y_pos.i.hi;
    value >>= 1;
    value = value + (value >> 1);
    value = arg0->unk42 + value;
    arg0->y_pos.i.hi = value;
}

void func_80028338(struct BackgroundObj* arg0)
{
    volatile u16* background = (volatile u16*)&background_objects[0].y_pos.i.hi;
    s16 value = background[0];
    s16 second = background[0];
    value >>= 2;
    value += second;
    value = arg0->unk42 + value;
    arg0->y_pos.i.hi = value;
}

void func_80028364(struct BackgroundObj* arg0)
{
    volatile u16* background = (volatile u16*)&background_objects[0].y_pos.i.hi;
    s16 value = background[0];
    s16 second = background[0];
    value >>= 1;
    value += second;
    value = arg0->unk42 + value;
    arg0->y_pos.i.hi = value;
}

void func_80028390(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].x_pos.i.hi;
    v0 = arg0->unk40 + (v0 >> 1);
    arg0->x_pos.i.hi = v0;
}

void func_800283B0(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].x_pos.i.hi;
    v0 = arg0->unk40 + (v0 >> 2);
    arg0->x_pos.i.hi = v0;
}

void func_800283D0(struct BackgroundObj* arg0)
{
    s16 value = background_objects[0].x_pos.i.hi;
    value >>= 1;
    value = value + (value >> 1);
    value = arg0->unk40 + value;
    arg0->x_pos.i.hi = value;
}

void func_800283F8(struct BackgroundObj* arg0)
{
    volatile u16* background = (volatile u16*)&background_objects[0].x_pos.i.hi;
    s16 value = background[0];
    s16 second = background[0];
    value >>= 2;
    value += second;
    value = arg0->unk40 + value;
    arg0->x_pos.i.hi = value;
}

void func_80028424(struct BackgroundObj* arg0)
{
    volatile u16* background = (volatile u16*)&background_objects[0].x_pos.i.hi;
    s16 value = background[0];
    s16 second = background[0];
    value >>= 1;
    value += second;
    value = arg0->unk40 + value;
    arg0->x_pos.i.hi = value;
}

#define FUNC_NAME func_80028450

#include "helpers/bg_is_on_screen.h"

#undef FUNC_NAME

void func_80028518(struct BackgroundObj* arg0)
{
    arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + arg0->unk40;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi + arg0->unk42;
    func_80028450(arg0);
}

void func_80028564(struct BackgroundObj* arg0)
{
    func_800282F0(arg0);
    func_800283B0(arg0);
    func_80028450(arg0);
}

void func_8002859C(struct BackgroundObj* arg0)
{
    func_80028390(arg0);
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi + arg0->unk42;
    func_80028450(arg0);
}

void func_800285E0(struct BackgroundObj* arg0)
{
}

void func_800285E8(struct BackgroundObj* arg0)
{
    func_800283D0(arg0);
    func_80028310(arg0);
    func_80028450(arg0);
}

void func_80028620(struct BackgroundObj* arg0)
{
    func_800283F8(arg0);
    func_80028338(arg0);
    func_80028450(arg0);
}

void func_80028658(struct BackgroundObj* arg0)
{
    func_80028424(arg0);
    func_80028364(arg0);
    func_80028450(arg0);
}

INCLUDE_ASM("main/nonmatchings/background", func_80028690);

void func_80028A48(struct BackgroundObj* arg0)
{
    if (--arg0->unk36 == 0) {
        arg0->unk34 &= ~0x10;
        return;
    }
    if (--arg0->unk3C == 0) {
        arg0->unk3E.bytes[0] ^= 0x80;
        arg0->unk3C = arg0->unk3A;
    }
    if (arg0->unk3E.bytes[0] >= 0) {
        arg0->x_pos.i.hi += arg0->unk45;
    }
}

void func_80028AD8(struct BackgroundObj* arg0)
{
    if (--arg0->unk37 == 0) {
        arg0->unk34 &= 0xFFFE;
        return;
    }
    if (--arg0->unk3D == 0) {
        arg0->unk3E.bytes[1] ^= 0x80;
        arg0->unk3D = arg0->unk3B;
    }
    if (arg0->unk3E.bytes[1] >= 0) {
        arg0->y_pos.i.hi += arg0->unk46;
    }
}

void (*D_800F3134[])(struct BackgroundObj* arg0) = {
    func_80027908,
    func_80027974,
    func_800279D8,
};

void (*D_800F3140[])(struct BackgroundObj*) = {
    func_80027DC0,
    func_80027DF0,
    func_80028070,
    func_800280BC,
    func_800280F4,
    func_800285E0,
    func_800285E8,
    func_80028620,
    func_80028658,
};

void (*D_800F3164[])(struct BackgroundObj*) = {
    func_80028268,
    func_80028298,
    func_80028518,
    func_80028564,
    func_8002859C,
    func_800285E0,
    func_800285E8,
    func_80028620,
    func_80028658,
};

#define BACKGROUND_CONFIG(a, b, c, d, e, f, g, h, i, j) \
    {                                                   \
        { a, b, c, d },                                 \
        {                                               \
            { e, f }, { g, h },                         \
            {                                           \
                i, j                                    \
            }                                           \
        }                                               \
    }

struct BackgroundLayoutConfigData D_800F3188 = {
    {
        BACKGROUND_CONFIG(6, 3, 9, 10, 5, 8, 4, 7, 9, 10),
        BACKGROUND_CONFIG(6, 3, 9, 10, 4, 7, 5, 8, 9, 10),
        BACKGROUND_CONFIG(6, 3, 9, 10, 5, 8, 4, 7, 9, 10),
        BACKGROUND_CONFIG(6, 3, 9, 10, 5, 7, 4, 8, 9, 10),
        BACKGROUND_CONFIG(7, 3, 9, 10, 6, 8, 9, 10, 4, 5),
        BACKGROUND_CONFIG(6, 3, 9, 10, 4, 7, 5, 8, 9, 10),
        BACKGROUND_CONFIG(7, 3, 9, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(6, 3, 8, 10, 4, 7, 5, 9, 5, 10),
        BACKGROUND_CONFIG(7, 3, 9, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(7, 3, 9, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(6, 3, 9, 10, 7, 8, 4, 5, 9, 10),
        BACKGROUND_CONFIG(7, 3, 9, 10, 5, 9, 4, 8, 6, 10),
        BACKGROUND_CONFIG(7, 3, 9, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(6, 3, 9, 10, 4, 7, 5, 8, 9, 10),
        BACKGROUND_CONFIG(7, 3, 8, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(7, 3, 9, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(7, 3, 9, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(7, 3, 7, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(7, 3, 7, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
        BACKGROUND_CONFIG(7, 3, 7, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
        BACKGROUND_CONFIG(7, 3, 7, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(7, 3, 7, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(7, 3, 7, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(7, 3, 6, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(4, 3, 9, 10, 4, 8, 5, 9, 6, 10),
        BACKGROUND_CONFIG(4, 3, 9, 10, 9, 10, 4, 6, 5, 7),
        BACKGROUND_CONFIG(8, 7, 5, 4, 3, 6, 5, 10, 4, 9),
        BACKGROUND_CONFIG(6, 3, 9, 10, 4, 7, 5, 8, 9, 9),
        BACKGROUND_CONFIG(6, 3, 9, 10, 4, 7, 5, 8, 9, 9),
        BACKGROUND_CONFIG(9, 8, 9, 10, 4, 5, 7, 8, 10, 10),
        BACKGROUND_CONFIG(6, 8, 9, 10, 4, 5, 10, 10, 6, 7),
    },
    { 0, 0 },
};

#undef BACKGROUND_CONFIG

struct BackgroundCameraModePair D_800F32D4[16][2] = {
    { { 2, 4 }, { 2, 4 } },
    { { 2, 1 }, { 5, 1 } },
    { { 3, 5 }, { 2, 2 } },
    { { 5, 5 }, { 5, 5 } },
    { { 1, 3 }, { 2, 1 } },
    { { 8, 6 }, { 2, 4 } },
    { { 1, 3 }, { 1, 3 } },
    { { 5, 5 }, { 5, 5 } },
    { { 5, 5 }, { 5, 5 } },
    { { 1, 1 }, { 0, 0 } },
    { { 5, 1 }, { 0, 0 } },
    { { 5, 3 }, { 5, 3 } },
    { { 2, 1 }, { 2, 3 } },
    { { 0, 0 }, { 5, 5 } },
    { { 0, 0 }, { 0, 0 } },
    { { 5, 5 }, { 2, 3 } },
};
