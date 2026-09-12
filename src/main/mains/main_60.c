// MainObj, main_object_update_funcs[60]
// 8007501C..8007872C
#include "common.h"

extern void* D_80101B4C[];
extern u8 D_80101B58[];

void func_8007501C(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80101B64[arg0->state](arg0);
}

void func_80075064(struct MainObj* arg0)
{
    D_80101B70[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800750A0);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075128);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007517C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800751AC);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075320);

void func_80075630(struct MainObj* arg0)
{
    D_80101BB4[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007566C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075700);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800757F4);

void func_800758FC(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_60.saved_unk5;
}

void func_80075908(struct MainObj* arg0)
{
    D_80101BC0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075944);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800759EC);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075A54);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075AD0);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075B54);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075BC4);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075C6C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075D38);

void func_80075DDC(struct MainObj* arg0)
{
    D_80101BE0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075E18);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075E78);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007601C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800760C4);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800761A0);

void func_8007624C(struct MainObj* arg0)
{
    D_80101BF4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076288);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076364);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007651C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007662C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800766FC);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007681C);

void func_800768CC(struct MainObj* arg0)
{
    D_80101C0C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076908);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800769FC);

void func_80076A74(struct MainObj* arg0)
{
    D_80101C14[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076AB0);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076B14);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076B84);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076C1C);

void func_80076C70(struct MainObj* arg0)
{
    D_80101C24[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076CAC);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076D14);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076DB0);

void func_80076E1C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_8001540C(2, 0xB6, arg0);
        arg0->ext.main_60.unk8E = 1;
        arg0->unk7C = 0x78;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076E88);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076F14);

void func_80076F74(struct MainObj* arg0)
{
    D_80101C3C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076FB0);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077028);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800770F0);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800771AC);

void func_8007720C(struct MainObj* arg0)
{
    func_80078180(arg0);
    D_80101C4C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077258);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077318);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077444);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077490);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077504);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077580);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077614);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077694);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077738);

void func_80077798(struct MainObj* arg0)
{
    D_80101C70[arg0->unk6](arg0);
}

void func_800777D4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    arg0->unk7C = 0x5A;
    arg0->unk6++;
}

void func_8007781C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80077868(struct MainObj* arg0)
{
    D_80101C78[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800778A4);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077954);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800779D4);

void func_80077A44(struct MainObj* arg0)
{
    D_80101C84[arg0->unk6](arg0);
}

void func_80077A80(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    if (!(arg0->ext.main_60.unk8B & 1)) {
        arg0->unk24 = FIXED(-3);
        arg0->unk6++;
    } else {
        arg0->unk7C = 0xA;
        arg0->unk6 += 2;
    }
    if (arg0->ext.main_60.unk8B < 2) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077B0C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077B74);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077BD0);

void func_80077C40(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x5F;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077C74);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077CE8);

void func_80077D48(struct VisualObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 0;
        obj->unk50 = (struct PlayerObj*)arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_80101A6C;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077DF0);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077ED0);

void func_80077F60(struct MainObj* arg0, s8 arg1)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x25;
        shot->unk2 = arg1;
        shot->unk7C = (struct WeaponObj*)arg0;
        shot->unk42 = arg0->unk42;
        shot->animation_table = D_80101A6C;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk40 = arg0->unk40;
        shot->bg_offset = arg0->bg_offset;
        shot->unk16 = 5;
        shot->unk15 = arg0->unk15;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077FFC);

void func_800780D4(struct VisualObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 2;
        obj->unk50 = (struct PlayerObj*)arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_80101A6C;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80078180);

void func_8007826C(struct PlayerObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 3;
        obj->unk50 = arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_80101A6C;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80078314);

void func_8007856C(struct MainObj* arg0)
{
    s32 player_x = g_Player.x_pos.val;

    if (arg0->x_pos.val < player_x) {
        if (func_8002B780() & 1) {
            arg0->ext.main_60.unk8B = 0;
        } else {
            arg0->ext.main_60.unk8B = 1;
        }
    } else {
        if (func_8002B780() & 1) {
            arg0->ext.main_60.unk8B = 2;
        } else {
            arg0->ext.main_60.unk8B = 3;
        }
    }
}

void func_800785E4(struct MainObj* arg0)
{
    u32 idx;
    u8** table;
    u8* weights;
    u8* base;
    u8 i;
    u32 rnd;
    u32 gr;

    idx = arg0->unk5C - 1;
    if ((s32)idx < 0)
        idx = arg0->unk5C + 0xE;
    idx >>= 4;
    idx &= 0xFF;
    table = ((u8**)D_80101B4C)[idx];
    gr = get_random();
    i = 0;
    base = D_80101B58;
    weights = base + idx * 3;
    rnd = gr & 0xF;
    while (i < 3) {
        if (rnd < weights[i]) {
            arg0->ext.main_60.unk84 = table[i];
            return;
        }
        i++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800786AC);
