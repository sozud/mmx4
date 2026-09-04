// QuadObj, quad_object_update_funcs[11]
// 800D6F94..800D7734
#include "common.h"

// white quad that turns into "MEGAMAN" on title screen

// TitleUpdate2 state 0
extern s16 D_8010FCCC[][8];
extern u16 D_8010FD94[];

void func_800D6F94(struct QuadObj* entity)
{
    u16* ptr;
    u16 temp;

    entity->bg_offset = -1;
    entity->ext.unk_ext2.unk42 = 1; // 0x42
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

    temp = D_8010FD94[0];
    entity->unk36 = 0x10;
    entity->state = 3;
    entity->ext.unk_ext2.unk38 = 0x14;
    entity->ext.unk_ext2.unk43 = 0; // 0x43
    entity->unk34 = temp;
}

// TitleUpdate2 state 1
INCLUDE_ASM("asm/us/main/nonmatchings/quads/title_quad", func_800D7058);

// TitleUpdate2 state 3
void func_800D7100(struct QuadObj* arg0)
{
    // seems to be a timer before the white Quad appears
    if (arg0->ext.unk_ext2.unk38 != 0) {
        arg0->ext.unk_ext2.unk38--;
        return;
    }
    arg0->ext.unk_ext2.unk38 = 3;
    quad_is_on_screen(arg0);
    arg0->state = 4;
}

// TitleUpdate2 state 4
void TitleSetWhiteQuadSpeed(struct QuadObj* arg0)
{
    if (game_info.unkA == 2) {
        arg0->ext.unk_ext2.unk38 = 0x2C; // sets animation speed of white quad that transforms into "MEGAMAN"
        arg0->state = 5;
    }
    quad_is_on_screen(arg0);
}

// TitleUpdate2 state 5
INCLUDE_ASM("asm/us/main/nonmatchings/quads/title_quad", func_800D7194);

// TitleUpdate2 state 6
INCLUDE_ASM("asm/us/main/nonmatchings/quads/title_quad", func_800D7468);

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

s16 D_8010FD7C[12] = {
    23,
    72,
    216,
    65,
    216,
    67,
    23,
    74,
    0,
    20,
    40,
    0,
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
