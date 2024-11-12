#include "common.h"

// white quad that turns into "MEGAMAN" on title screen

// TitleUpdate2 state 0
extern s16 D_8010FCCC[1][8];
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
INCLUDE_ASM("asm/us/main/nonmatchings/title_quad", func_800D7058);

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
INCLUDE_ASM("asm/us/main/nonmatchings/title_quad", func_800D7194);

// TitleUpdate2 state 6
INCLUDE_ASM("asm/us/main/nonmatchings/title_quad", func_800D7468);

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
