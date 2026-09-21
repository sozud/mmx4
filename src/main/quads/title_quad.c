// QuadObj, quad_object_update_funcs[11]
// 800D6F94..800D7734
#include "common.h"

// white quad that turns into "MEGAMAN" on title screen

// TitleUpdate2 state 0
extern s16 D_8010FCCC[][8];
extern u16 D_8010FD94[];
#ifdef VERSION_JP
extern s16 D_8010FE78_jp[];
extern u16 D_8010FD7C[];
#else
extern s16 D_8010FD7C[][2];
#endif

void func_800D6F94(struct QuadObj* arg0)
{
    struct QuadObj* entity = arg0;
    u16* ptr;
#ifndef VERSION_JP
    u16 temp;
#endif

    entity->bg_offset = -1;
    entity->ext.title_quad.unk42 = 1; // 0x42
    entity->x_pos.i.hi = 0;
    entity->y_pos.i.hi = 0;
    entity->active |= 0x80;

    ptr = D_8010FCCC[entity->unk2];
    entity->unk14.i.hi = *ptr++;
    entity->unk18.i.hi = *ptr++;
    entity->unk1C.i.hi = *ptr++;
    entity->unk20.i.hi = *ptr++;
    entity->unk24.i.hi = *ptr++;
    entity->unk28.i.hi = *ptr++;
    entity->unk2C.i.hi = *ptr++;
    entity->unk30.i.hi = *ptr;

#ifdef VERSION_JP
    switch (entity->unk2) {
    case 0:
    case 1:
    case 9: {
        u16 color = D_8010FD7C[11];

        entity->unk36 = 0x11;
        entity->ext.title_quad.unk38 = 0x3C;
        entity->state = 1;
        entity->unk34 = color;
        quad_is_on_screen(entity);
        break;
    }

    case 2:
    case 3:
    case 4: {
        u16 color = D_8010FD94[0];

        entity->unk36 = 0x10;
        entity->state = 3;
        entity->unk34 = color;
        entity->unk1C = entity->unk14;
        entity->unk20 = entity->unk18;
        entity->unk24 = entity->unk2C;
        entity->unk28 = entity->unk30;
        entity->ext.title_quad.unk38 = D_8010FE78_jp[entity->unk2];
        entity->ext.title_quad.unk43 = 0;
        break;
    }

    case 5: {
        u16 color = D_8010FD7C[11];

        entity->unk36 = 0x12;
        entity->state = 4;
        entity->unk2 = 4;
        entity->ext.title_quad.unk43 = 0;
        entity->unk34 = color;
        break;
    }
    }
#else
    temp = D_8010FD94[0];
    entity->unk36 = 0x10;
    entity->state = 3;
    entity->ext.title_quad.unk38 = 0x14;
    entity->ext.title_quad.unk43 = 0; // 0x43
    entity->unk34 = temp;
#endif
}

// TitleUpdate2 state 1
#ifndef VERSION_JP
void func_800D7058(struct QuadObj* self)
{
    s32 velocity;

    if (game_info.unkA != 1) {
        quad_is_on_screen(self);
        return;
    }

    if (self->unk2 == 0) {
        self->unk28.val += FIXED(-8);
        self->unk30.val += FIXED(-8);
        if (self->unk28.i.hi < self->unk20.i.hi) {
            self->state = 2;
            return;
        }
    } else {
        velocity = FIXED(8);
        self->unk20.val += velocity;
        self->unk18.val += velocity;
        if (self->unk20.i.hi > self->unk28.i.hi) {
            self->state = 2;
            return;
        }
    }
    quad_is_on_screen(self);
}
#endif

// TitleUpdate2 state 3
#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/quads/title_quad", func_800D7154_jp);
#else
void func_800D7100(struct QuadObj* arg0)
{
    // seems to be a timer before the white Quad appears
    if (arg0->ext.title_quad.unk38 != 0) {
        arg0->ext.title_quad.unk38--;
        return;
    }
    arg0->ext.title_quad.unk38 = 3;
    quad_is_on_screen(arg0);
    arg0->state = 4;
}
#endif

// TitleUpdate2 state 4
#ifndef VERSION_JP
void TitleSetWhiteQuadSpeed(struct QuadObj* arg0)
{
    if (game_info.unkA == 2) {
        arg0->ext.title_quad.unk38 = 0x2C; // sets animation speed of white quad that transforms into "MEGAMAN"
        arg0->state = 5;
    }
    quad_is_on_screen(arg0);
}
#endif

// TitleUpdate2 state 5
#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/quads/title_quad", func_800D71FC_jp);
INCLUDE_ASM("main/nonmatchings/quads/title_quad", func_800D7250_jp);
INCLUDE_ASM("main/nonmatchings/quads/title_quad", func_800D7340_jp);
#else
void func_800D7194(struct QuadObj* arg0)
{
    f32* xy_ptr;
    s32 x_diff;
    s32 y_diff;
    s32 pos;
    s16* ptr;
    u16* palette;
    u16* var_v0;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v1;

    xy_ptr = &arg0->unk14;
    pos = 0;
    do {
        ptr = &D_8010FD7C[pos][0];
        x_diff = xy_ptr[0].val - FIXED(ptr[0]);
        y_diff = xy_ptr[1].val - FIXED(ptr[1]);
        temp_v0 = func_8002B810(x_diff, y_diff);
        if ((((arg0->ext.title_quad.unk3E[pos] ^ temp_v0) & 0x10) || (arg0->ext.title_quad.unk3A[pos] != 0)) && (arg0->ext.title_quad.unk42 == 0)) {
            xy_ptr[0].val = FIXED(ptr[0]);
            xy_ptr[1].val = FIXED(ptr[1]);
            arg0->ext.title_quad.unk3A[pos] = 1;
        } else {
            xy_ptr[0].val -= x_diff / arg0->ext.title_quad.unk38;
            xy_ptr[1].val -= y_diff / arg0->ext.title_quad.unk38;
            arg0->ext.title_quad.unk3A[pos] = 0;
            if (pos == 3) {
                arg0->ext.title_quad.unk42 = 0;
            }
        }
        xy_ptr += 2;
        arg0->ext.title_quad.unk3E[pos] = temp_v0;
        pos++;
    } while (pos < 4);

    if ((arg0->ext.title_quad.unk38 % 3) == 0) {
        palette = D_8010FD94;
        temp_v1 = arg0->ext.title_quad.unk43;
        temp_v0_2 = temp_v1 + 1;
        arg0->ext.title_quad.unk43 = temp_v0_2;
        if (temp_v0_2 < 0xE) {
            temp_v0_2 = temp_v1 + 2;
            arg0->ext.title_quad.unk43 = temp_v0_2;
            var_v0 = &palette[temp_v0_2];
        } else {
            var_v0 = &palette[14];
        }
        arg0->unk34 = *var_v0;
    }

    arg0->ext.title_quad.unk38--;
    if (arg0->ext.title_quad.unk38 == 0) {
        arg0->state = 2;
        ptr = D_8010FD7C[0];
        arg0->unk14.i.hi = *(u16*)ptr++;
        arg0->unk18.i.hi = *(u16*)ptr++;
        arg0->unk1C.i.hi = *(u16*)ptr++;
        arg0->unk20.i.hi = *(u16*)ptr++;
        arg0->unk24.i.hi = *(u16*)ptr++;
        arg0->unk28.i.hi = *(u16*)ptr++;
        arg0->unk2C.i.hi = *(u16*)ptr++;
        arg0->unk30.i.hi = *(u16*)ptr;
        arg0->unk2 = 4;
        arg0->ext.title_quad.unk38 = 3;
    }
    quad_is_on_screen(arg0);
}
#endif

// TitleUpdate2 state 6
INCLUDE_ASM("main/nonmatchings/quads/title_quad", func_800D7468);

// TitleUpdate2 state 2
void func_800D76D8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

// title screen doesn't appear if nopped out
void TitleUpdate2(struct QuadObj* arg0)
{
    g_TitleUpdate2Funcs[arg0->state](arg0);
}

#ifdef VERSION_JP
extern void func_800D7154_jp();
extern void func_800D71FC_jp();
extern void func_800D7250_jp();
extern void func_800D7340_jp();

s16 D_8010FCCC[3][8] = {
    { 0, 0, 319, 0, 319, 120, 0, 120 },
    { 80, 192, 319, 121, 319, 240, 80, 240 },
    { 330, 120, 80, 191, 81, 192, 331, 121 },
};

s16 D_8010FE0C_jp[2][8] = {
    { 80, 191, 0, 120, 4, 121, 84, 192 },
    { 0, 120, 330, 120, 331, 121, 1, 121 },
};

s16 D_8010FE2C_jp[7][2] = {
    { 0, 120 },
    { 330, 120 },
    { 80, 192 },
    { 80, 192 },
    { 6, 122 },
    { 316, 122 },
    { 81, 188 },
};

s16 D_8010FE48_jp[3][8] = {
    { 81, 188, 80, 104, 19, 59, 230, 59 },
    { 230, 59, 80, 102, 24, 61, 217, 61 },
    { 217, 61, 80, 191, 0, 119, 0, 240 },
};

s16 D_8010FE78_jp[6] = { 80, 240, 0, 20, 40, 0 };

u16 D_8010FD94[4] = { 0x83E0, 0x8BC2, 0x93C4, 0x9BC6 };
u16 D_8010FD7C[26] = {
    0xA3C8,
    0xAFCB,
    0xB7CD,
    0xBFCF,
    0xC7D1,
    0xCFD3,
    0xDBD6,
    0xE3D8,
    0xEBDA,
    0xF3DC,
    0xFFFF,
    0x8421,
    0x8422,
    0x8424,
    0x8426,
    0x8428,
    0x842A,
    0x842C,
    0x842E,
    0x8430,
    0x8432,
    0x8433,
    0x8435,
    0x8437,
    0x8439,
    0x845F,
};

void (*g_TitleUpdate2Funcs[])(struct QuadObj*) = {
    func_800D6F94,
    func_800D7154_jp,
    func_800D76D8,
    func_800D71FC_jp,
    func_800D7250_jp,
    func_800D7340_jp,
    func_800D7468,
};
#else
s16 D_8010FCCC[11][8] = {
    { 0, 0, 319, 0, 319, 120, 0, 120 },
    { 80, 192, 319, 121, 319, 240, 80, 240 },
    { 330, 120, 80, 191, 81, 192, 331, 121 },
    { 80, 191, 0, 120, 4, 121, 84, 192 },
    { 0, 120, 330, 120, 331, 121, 1, 121 },
    { 0, 120, 330, 120, 80, 192, 80, 192 },
    { 6, 122, 316, 122, 81, 188, 81, 188 },
    { 80, 104, 19, 59, 230, 59, 230, 59 },
    { 80, 102, 24, 61, 217, 61, 217, 61 },
    { 80, 191, 0, 119, 0, 240, 80, 240 },
    { 319, 0, 319, 239, 0, 239, 0, 0 },
};

s16 D_8010FD7C[6][2] = {
    { 23, 72 },
    { 216, 65 },
    { 216, 67 },
    { 23, 74 },
    { 0, 20 },
    { 40, 0 },
};

u16 D_8010FD94[30] = {
    0x8421,
    0x8C63,
    0x94A5,
    0xA108,
    0xAD6B,
    0xB5AD,
    0xC210,
    0xC631,
    0xCE73,
    0xDAD6,
    0xDEF7,
    0xE739,
    0xEF7B,
    0xF7BD,
    0x7FFF,
    0x8421,
    0x8422,
    0x8424,
    0x8426,
    0x8428,
    0x842A,
    0x842C,
    0x842E,
    0x8430,
    0x8432,
    0x8433,
    0x8435,
    0x8437,
    0x8439,
    0x845F,
};

void TitleSetWhiteQuadSpeed(struct QuadObj*);

void (*g_TitleUpdate2Funcs[])(struct QuadObj*) = {
    func_800D6F94,
    func_800D7058,
    func_800D76D8,
    func_800D7100,
    TitleSetWhiteQuadSpeed,
    func_800D7194,
    func_800D7468,
};
#endif
