#include "common.h"

void func_800AEAC0(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1;
    if (g_Player.unkDE == 0) {
        var_a1 = &g_Player;
    } else {
        var_a1 = &g_Entity;
    }
    D_8010A1A0[arg0->base.state](arg0, var_a1);
}

void func_800AEB1C(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->base.on_screen = 1;
    arg0->unk38 = 0;
    arg0->unk3C = (void*)(*(s8**)0x1F80001C + (*(s32**)0x1F80001C)[1]);
    arg0->unk30 = &D_8011BF40;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7804;
    arg0->base.unk16 = 1;
    func_800AEC9C(arg0, arg1);
    func_80015D60(arg0, 3);
    arg0->base.state++;
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800AEBA8(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    s32 var_a0 = 0;

    func_80015DC8(arg0);
    if ((*(s32*)&arg1->base.state & 0xFFFF00) == 0xB00) {
        var_a0 = 1;
    }
    if (arg1->base.unk5 == 0x34) {
        var_a0 = 1;
    }
    if (var_a0 != 0) {
        func_800AEC9C(arg0, arg1);
    } else {
        func_80015D60(arg0, 4);
        arg0->base.state++;
    }
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800AEC48(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    func_80015DC8(arg0);
    if (arg0->unk46 < 0) {
        ZeroObjectState(arg0);
        return;
    }
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800AEC9C(struct Unk* arg0, struct Unk* arg1)
{
    arg0->base.unk15 = arg1->base.unk15;
    if (arg0->base.unk15 == 0) {
        arg0->base.x_pos.i.hi = arg1->base.x_pos.i.hi + D_8010A1AC[arg1->base.unk2 * 2];
    } else {
        arg0->base.x_pos.i.hi = arg1->base.x_pos.i.hi - D_8010A1AC[arg1->base.unk2 * 2];
    }
    arg0->base.y_pos.i.hi = arg1->base.y_pos.i.hi + D_8010A1AE[arg1->base.unk2 * 2];
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AED18);

void func_800AEE5C(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->base.unk15 = arg1->base.unk15;
    if (arg0->base.unk15 == 0) {
        arg0->base.x_pos.i.hi = arg1->base.x_pos.i.hi + D_8010A1B4[arg1->base.unk2 * 2];
    } else {
        arg0->base.x_pos.i.hi = arg1->base.x_pos.i.hi - D_8010A1B4[arg1->base.unk2 * 2];
    }
    arg0->base.y_pos.i.hi = arg1->base.y_pos.i.hi + D_8010A1B6[arg1->base.unk2 * 2];
}

void func_800AEED8(struct VisualObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800AEF18(arg0);
    } else {
        func_800AF02C(arg0);
    }
}

void func_800AEF18(struct VisualObj* arg0)
{
    s32 temp_s0;
    s32 var_a1;

    arg0->base.on_screen = 1;
    if (arg0->base.unk2 == 9) {
        var_a1 = 0;
    }
    if (arg0->base.unk2 == 0x12) {
        var_a1 = 1;
    }
    if (arg0->base.unk2 == 0x14) {
        var_a1 = 2;
    }
    temp_s0 = var_a1 * 3;
    arg0->unk3C = *(u8**)0x1F80001C + *(D_8010A1BC[temp_s0] + *(u32**)0x1F80001C);
    arg0->unk30 = &D_8011BF40;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7802;
    arg0->base.unk16 = 0;
    arg0->base.unk15 = g_Player.base.unk15;
    arg0->unk5C = 0;
    func_800AF1AC(arg0);
    arg0->base.x_pos.i.lo = 0;
    arg0->base.y_pos.i.lo = 0;
    func_80015D60(arg0, D_8010A1BD[temp_s0]);
    func_8001540C(1, D_8010A1BE[temp_s0], arg0);
    arg0->base.state++;
    func_8002B318(arg0, 0x40, 0x20);
}

void func_800AF02C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    func_800AF1AC(arg0);
    if (arg0->base.unk5 == 0) {
        func_800AF084(arg0);
    } else {
        func_800AF15C(arg0);
    }
}

void func_800AF084(struct VisualObj* arg0)
{
    struct WeaponObj* temp_v0;

    if (arg0->unk45 != 0) {
        temp_v0 = find_free_weapon_obj();
        if (temp_v0 != NULL) {
            temp_v0->base.active = 0x21;
            temp_v0->base.id = arg0->base.unk2;
            temp_v0->base.unk2 = 0;
            temp_v0->base.x_pos.val = arg0->base.x_pos.val;
            temp_v0->base.y_pos.val = arg0->base.y_pos.val;
            temp_v0->base.unk15 = arg0->base.unk15;
            temp_v0->unk3C = arg0->unk3C;
            temp_v0->unk30 = arg0->unk30;
            temp_v0->unk40 = arg0->unk40;
            temp_v0->unk42 = arg0->unk42;
            temp_v0->base.unk16 = arg0->base.unk16;
        }
        arg0->base.unk5++;
    }
    func_8002B318(arg0, 0x40, 0x20);
}

void func_800AF15C(struct VisualObj* arg0)
{
    if (arg0->unk46 == 0 || arg0->unk5C != 0) {
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
        if (entity->base.unk15 != arg0->base.unk15) {
            arg0->unk5C = 1;
        }
        if (arg0->unk5C == 0) {
            func_80092E2C(arg0, entity, arg0->base.unk2);
        }
    }
}

void func_800AF22C(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1 = &g_Entity;
    if (!(arg0->base.unk2 & 2)) {
        var_a1 = &g_Player;
    }
    if (arg0->base.state == 0) {
        func_800AF28C(arg0, var_a1);
    } else {
        func_800AF388(arg0, var_a1);
    }
}

void func_800AF28C(struct VisualObj* arg0, struct VisualObj* arg1)
{
    arg0->base.bg_offset = arg1->base.bg_offset;
    arg0->base.unk16 = 1;
    arg0->unk30 = &D_8011BF40;
    arg0->unk3C = *((u8)func_8002938C(0x84) + *(s32**)0x1F800020) + *(s8**)0x1F800020;
    arg0->unk40 = D_801406A8[(u8)func_8002938C(0x84)] >> 7;
    arg0->unk42 = (((u8)func_8002938C(0x84) * 4) + 24) % 16 | ((((u8)func_8002938C(0x84) + 6) / 4) + 480) * 64;
    arg0->base.state++;
}

void func_800AF388(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (arg1->unk5C == 0 || arg1->base.state == 3) {
        ZeroObjectState(arg0);
        return;
    }
    arg0->base.unk15 = arg1->base.unk15;
    if (arg0->base.unk2 & 1) {
        arg0->base.x_pos.val = arg1->base.x_pos.val + FIXED(8);
    } else {
        arg0->base.x_pos.val = arg1->base.x_pos.val + FIXED(-8);
    }
    arg0->base.y_pos.val = arg1->base.y_pos.val;
    D_8010A1C8[arg0->base.unk5](arg0, arg1);
    if (arg1->base.active == 0) {
        arg0->base.on_screen = 0;
    }
    if (func_8002D900(arg1) != 0x24) {
        arg0->base.on_screen = 0;
    }
    if (arg0->base.on_screen != 0) {
        is_on_screen(arg0);
    }
}

void func_800AF488(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF610(arg1) != 0) {
        func_80015D60(arg0, 0x13);
        arg0->base.on_screen = 1;
        arg0->base.unk5 = 1;
    } else if (func_800AF658(arg1) != 0) {
        func_80015D60(arg0, 0x14);
        arg0->base.on_screen = 1;
        arg0->base.unk5 = 2;
    }
}

void func_800AF504(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF610(arg1) != 0) {
        func_80015DC8(arg0);
        arg0->base.on_screen = 1;
        return;
    }
    if (func_800AF658(arg1) != 0) {
        func_80015D60(arg0, 0x14);
        arg0->base.on_screen = 1;
        arg0->base.unk5 = 2;
        return;
    }
    arg0->base.on_screen = 0;
    arg0->base.unk5 = 0;
}

void func_800AF58C(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF658(arg1) != 0) {
        func_80015DC8(arg0);
        arg0->base.on_screen = 1;
        return;
    }
    if (func_800AF610(arg1) != 0) {
        func_80015D60(arg0, 0x13);
        arg0->base.on_screen = 1;
        arg0->base.unk5 = 1;
        return;
    }
    arg0->base.on_screen = 0;
    arg0->base.unk5 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF610);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF658);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF6A0);

void func_800AF808(struct Unk* arg0)
{
    func_800AF828(arg0, 0);
}

void func_800AF828(struct Unk* arg0, s8 arg1)
{
    func_800AFAB4(arg1, arg0->base.x_pos.i.hi, arg0->base.y_pos.i.hi, (get_random() & 1) ^ 1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF878);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF95C);

struct Unk* func_800AFAB4(s8 arg0, s16 x, s16 y, u8 arg3)
{
    struct VisualObj* temp_v0 = find_free_visual_obj();
    if (temp_v0 != NULL) {
        temp_v0->base.active = 0x21;
        temp_v0->base.id = 4;
        temp_v0->base.unk2 = arg0;
        temp_v0->base.state = 0;
        temp_v0->base.unk5 = 0;
        temp_v0->base.unk6 = 0;
        temp_v0->unk5C = arg3;
        temp_v0->base.x_pos.i.hi = x;
        temp_v0->base.x_pos.i.lo = 0;
        temp_v0->base.y_pos.i.hi = y;
        temp_v0->base.y_pos.i.lo = 0;
        temp_v0->base.unk15 = 0;
        temp_v0->base.bg_offset = 0;
        temp_v0->base.unk16 = 1;
    }
    return temp_v0;
}

void func_800AFB50(struct VisualObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800AFB90(arg0);
    } else {
        func_800AFC4C(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFB90);

void func_800AFC4C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 < 0) {
        ZeroObjectState(arg0);
    } else {
        is_on_screen(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFC9C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFD20);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFDA8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFE20);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFEA4);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFF08);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFF28);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFF78);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B0320);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B054C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B0600);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B06AC);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B0804);

void func_800B0890(struct VisualObj* arg0)
{
    D_8010A430[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B08CC);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B0B48);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B0C78);

void func_800B0C98(struct VisualObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B0CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B10E4);

void func_800B1354(struct VisualObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800B1394(arg0);
    } else {
        func_800B1450(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1394);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1450);

void func_800B14E8(struct VisualObj* arg0)
{
    D_8010A4CC[arg0->base.state](arg0);
}

void func_800B1524(struct VisualObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        arg0->base.unk15 = 0;
    } else {
        arg0->base.unk15 = 0x40;
    }
    func_80015D60(arg0, 5);
    arg0->base.state++;
    func_8002B318(arg0, 0xA0, 0xA0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B158C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B16B0);

void func_800B1758(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 < 0) {
        arg0->base.state++;
    }
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800B17AC(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B17CC(struct VisualObj* arg0)
{
    D_8010A4E0[arg0->base.state](arg0);
}

void func_800B1808(struct VisualObj* arg0)
{
    arg0->base.unk15 = arg0->unk50->base.unk15;
    func_80015D60(arg0, arg0->base.unk2);
    arg0->base.on_screen = 1;
    arg0->base.state++;
    func_8002B318(arg0, 0x50, 0x50);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1864);

void func_800B199C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B19BC(struct VisualObj* arg0)
{
    D_8010A4EC[arg0->base.state](arg0);
}

void func_800B19F8(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    arg0->base.unk16 = D_8010A504[arg0->base.unk2];
    func_80015D60(arg0, D_8010A4F8[arg0->base.unk2]);
}

void func_800B1A48(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0 = arg0->unk50;
    if (temp_a0->base.state != 2) {
        if (arg0->unk46 >= 0) {
            arg0->base.x_pos.i.hi = temp_a0->base.x_pos.i.hi;
            arg0->base.y_pos.i.hi = temp_a0->base.y_pos.i.hi;
            func_80015DC8(arg0);
        } else {
            arg0->base.state = 2;
        }
        func_8002B318(arg0, 0x10, 0x10);
    } else {
        arg0->base.state = 2;
    }
}

void func_800B1AD8(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B1AF8(struct VisualObj* arg0)
{
    D_8010A520[arg0->base.state](arg0);
}

void func_800B1B34(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    arg0->unk54 = 0xFF;
    arg0->unk56 = 0xFF;
    arg0->base.unk16 = 6;
    func_80015D60(arg0, 0x15);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1B74);

void func_800B1C3C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B1C5C(struct VisualObj* arg0)
{
    D_8010A52C[arg0->base.state](arg0);
}

void func_800B1C98(struct VisualObj* arg0)
{
    arg0->base.unk15 = arg0->unk50->base.unk15;
    func_80015D60(arg0, arg0->base.unk2);
    arg0->base.on_screen = 1;
    arg0->base.state++;
    func_8002B318(arg0, 0x50, 0x50);
}

void func_800B1CF4(struct VisualObj* arg0)
{
    struct PlayerObj* temp_s1 = arg0->unk50;
    func_80015DC8(arg0);
    arg0->base.x_pos.i.hi = temp_s1->base.x_pos.i.hi;
    arg0->base.y_pos.i.hi = temp_s1->base.y_pos.i.hi;
    func_8002B318(arg0, 0x30, 0x30);
}

void func_800B1D4C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B1D6C(struct VisualObj* arg0)
{
    D_8010A538[arg0->base.state](arg0);
}

void func_800B1DA8(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    arg0->unk54 = 3;
    arg0->base.unk16 = 2;
    func_80015D60(arg0, 0x19);
}

void func_800B1DE4(struct VisualObj* arg0)
{
    struct BaseObj* temp_s1 = arg0->unk50;

    arg0->base.x_pos.i.hi = temp_s1->x_pos.i.hi;
    arg0->base.y_pos.i.hi = temp_s1->y_pos.i.hi;
    if (arg0->unk46 < 0) {
        arg0->unk54--;
    }
    func_80015DC8(arg0);
    if (temp_s1->state == 2) {
        arg0->base.state = 2;
    } else {
        if (arg0->unk54 == 0) {
            arg0->base.state = 2;
        }
        func_8002B318(arg0, 0x10, 0x10);
    }
}

void func_800B1E84(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B1EA4(struct VisualObj* arg0)
{
    D_8010A544[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1EE0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1F78);

void func_800B2070(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B2090(struct VisualObj* arg0)
{
    D_8010A570[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B20CC);

void func_800B2200(struct VisualObj* arg0)
{
    struct PlayerObj* temp_s0;

    if (arg0->base.unk2 == 0) {
        temp_s0 = arg0->unk50;
        arg0->base.x_pos.val = temp_s0->base.x_pos.val;
        arg0->base.y_pos.val = temp_s0->base.y_pos.val;
        func_80015DC8();
        if (temp_s0->unk8A == 0) {
            ZeroObjectState(arg0);
        } else {
            func_8002B318(arg0, 0x10, 0x10);
        }
    } else {
        D_8010A57C[arg0->base.unk5](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B22B4);

void func_800B23DC(struct VisualObj* arg0)
{
    if (arg0->unk50->base.state >= 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        arg0->base.unk6 = 0;
    } else {
        func_80015DC8(arg0);
    }
    func_8002B318(arg0, 0x10, 0x10);
}

void func_800B2444(struct VisualObj* arg0)
{
    switch (arg0->base.unk5) {
    case 0:
        arg0->unk24 = -0x8000;
        arg0->unk54 = 0x78;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->base.unk5 = 1;
        func_80015DC8(arg0);
        func_8002B318(arg0, 0x10, 0x10);
        break;
    case 1:
        if (--arg0->unk54 == 0) {
            arg0->base.unk5 = 2;
        }
        if (!(arg0->unk54 & 7)) {
            func_800AF878(arg0, 0, 0xF, 0xF);
        }
        func_8002B694(arg0);
        func_80015DC8(arg0);
        func_8002B318(arg0, 0x10, 0x10);
        break;
    case 2:
        ZeroObjectState(arg0);
        break;
    }
}

void func_800B2544(struct VisualObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s32 var_a0;

    var_a0 = engine_obj.unkF != 0;
    if (player->unk93 != 6) {
        var_a0 = 1;
    }
    if (player->unk5C == 0) {
        var_a0 = 1;
    }
    if (var_a0 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->base.state == 0) {
        arg0->base.on_screen = 1;
        arg0->base.bg_offset = player->base.bg_offset;
        arg0->unk38 = *(u8**)0x1F800014 + (*(u32**)0x1F800014)[0x1C / 4];
        arg0->unk3C = *(u8**)0x1F80001C + (*(u32**)0x1F80001C)[0x3C / 4];
        arg0->unk30 = &D_8011C0E4;
        arg0->unk40 = 0x520;
        arg0->unk42 = 0x7801;
        arg0->base.unk16 = 0x12;
        arg0->unk49 = 0;
        func_80015D60(arg0, 0);
        arg0->base.state++;
        decompress_player_gfx(arg0, 0x140, 0x20);
    } else {
        func_80015DC8(arg0);
    }
    arg0->base.x_pos.val = player->base.x_pos.val;
    arg0->base.y_pos.val = player->base.y_pos.val;
    arg0->base.unk15 = player->base.unk15;
    func_8002B318(arg0, 0x68, 0x48);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2698);

void func_800B2880(struct VisualObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        decompress_player_gfx(arg0, 0x140, 0x20);
    }
    func_8002B318(arg0, 0x18, 0x30);
}

void func_800B28CC(struct VisualObj* arg0)
{
    struct VisualObj* temp_s1;

    temp_s1 = arg0->unk50;
    if ((temp_s1 == 0) || (temp_s1->base.active == 0)) {
        ZeroObjectState(arg0);
        return;
    }

    if (arg0->base.state == 0) {
        arg0->base.on_screen = 1;
        arg0->unk38 = temp_s1->unk38;
        arg0->unk3C = temp_s1->unk3C;
        arg0->unk30 = temp_s1->unk30;
        arg0->unk40 = D_8010A588[arg0->base.unk2];
        arg0->unk42 = temp_s1->unk42;
        arg0->base.unk16 = D_8010A590[arg0->base.unk2];
        arg0->base.unk15 = temp_s1->base.unk15;
        arg0->unk49 = 1;
        func_80015D60(arg0, D_8010A594[arg0->base.unk2]);
        arg0->base.state++;
    } else {
        func_80015DC8(arg0);
    }

    arg0->base.x_pos.val = temp_s1->base.x_pos.val;
    arg0->base.y_pos.val = temp_s1->base.y_pos.val;

    if (D_8010A598[arg0->base.unk2] != 0) {
        decompress_player_gfx(arg0, 0x140, D_8010A598[arg0->base.unk2]);
    }

    func_8002B318(arg0, D_8010A5A0[arg0->base.unk2 * 2], D_8010A5A2[arg0->base.unk2 * 2]);
}

void func_800B2A3C(struct VisualObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        arg0->unk38 = *(u8**)0x1F800014 + (*(u32**)0x1F800014)[0x18 / 4];
    } else {
        arg0->unk38 = *(u8**)0x1F800014 + (*(u32**)0x1F800014)[0x24 / 4];
    }

    arg0->unk40 = 0x520;
    arg0->unk48 = -1;
    arg0->unk47 = 0;

    decompress_player_gfx(arg0, 0x140, 0x20);
    ZeroObjectState(arg0);
}

void func_800B2AD0(struct VisualObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s8 var_s1;
    u8 temp_v1_2;

    if (arg0->base.state == 0) {
        arg0->base.on_screen = 1;
        arg0->base.unk2 = -1;
        arg0->unk3C = *(u8**)0x1F80001C + (*(u32**)0x1F80001C)[0x30 / 4];
        arg0->unk30 = &D_8011BF40;
        arg0->unk42 = 0x7802;
        arg0->unk40 = 0;
        arg0->base.unk16 = 3;
        arg0->unk5C = 0;
        arg0->base.state++;
    }
    temp_v1_2 = player->cur_anim;
    var_s1 = -((((temp_v1_2 + 0x1B) & 0xFF) < 2U) ^ 1);
    if (((temp_v1_2 + 0x23) & 0xFF) < 2U) {
        var_s1 = 1;
    }
    if (((temp_v1_2 + 0x21) & 0xFF) < 2U) {
        var_s1 = 2;
    }
    if (((temp_v1_2 + 0x1F) & 0xFF) < 2U) {
        var_s1 = 3;
    }

    if (((temp_v1_2 + 0x1D) & 0xFF) < 2U) {
        var_s1 = 4;
    }

    if (var_s1 == -1) {
        ZeroObjectState(arg0);
        return;
    }
    if (var_s1 != arg0->base.unk2) {
        func_80015D60(arg0, var_s1 + 0x20);
        arg0->base.unk2 = var_s1;
    } else {
        func_80015DC8(arg0, var_s1);
    }

    arg0->base.unk15 = player->base.unk15;
    arg0->base.x_pos.val = player->base.x_pos.val;
    arg0->base.y_pos.val = player->base.y_pos.val;
    if (arg0->unk5C == 0) {
        arg0->unk5C = 8;
        func_8001540C(0, 0x1F, arg0);
    } else {
        arg0->unk5C--;
    }
    func_8002B318(arg0, 0x28, 0x28);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2C8C);

void func_800B2D48(struct VisualObj* arg0)
{
    D_8010A5B0[arg0->base.state](arg0);
}

void func_800B2D84(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    arg0->base.unk16 = 4;
    if (arg0->base.unk2 == 0) {
        func_80015D60(arg0, 0x11);
    } else {
        arg0->unk54 = 0;
        func_80015D60(arg0, 0x15);
    }
}

void func_800B2DD0(struct VisualObj* arg0)
{
    struct PlayerObj* temp_v1;
    struct BaseObj* temp_a0;

    func_80015DC8(arg0);
    if (arg0->base.unk2 == 0) {
        temp_v1 = arg0->unk50;
        temp_a0 = temp_v1->unk7C;
        arg0->base.x_pos.val = temp_a0->x_pos.val;
        arg0->base.y_pos.val = temp_a0->y_pos.val;
        if (temp_v1->base.unk2 != 0) {
            is_on_screen(arg0);
        } else {
            ZeroObjectState(arg0);
        }
    } else {
        temp_a0 = arg0->unk50;
        if (arg0->unk46 >= 0 && temp_a0->state == 1 && (temp_a0->unk5 == 3 || temp_a0->unk5 == 5)) {
            is_on_screen(arg0);
        } else {
            ZeroObjectState(arg0);
        }
    }
}

void func_800B2E98(struct VisualObj* arg0)
{
    struct VisualObj* temp_v1 = arg0->unk50;
    arg0->unk40 = temp_v1->unk40;
    arg0->unk42 = temp_v1->unk42 & ~0x8000;
    arg0->unk30 = temp_v1->unk30;
    arg0->unk3C = temp_v1->unk3C;
    arg0->base.unk15 = temp_v1->base.unk15;
    arg0->base.bg_offset = temp_v1->base.bg_offset;
    arg0->base.x_pos.val = temp_v1->base.x_pos.val;
    arg0->base.y_pos.val = temp_v1->base.y_pos.val;
    arg0->base.unk16 = 6;
    arg0->base.unk2 = D_8010A5B8[temp_v1->unk47];
    func_80015D60(arg0, arg0->base.unk2);
    arg0->base.state++;
}

void func_800B2F60(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0;

    temp_a0 = arg0->unk50;
    if (temp_a0->base.state == 0 || temp_a0->base.state == 2) {
        arg0->base.state = 2;
    } else {
        if (arg0->base.unk2 != D_8010A5B8[temp_a0->cur_anim]) {
            arg0->base.unk2 = D_8010A5B8[temp_a0->cur_anim];
            func_80015D60(arg0, arg0->base.unk2);
        } else {
            func_80015DC8(arg0);
        }
        func_8002B318(arg0, 0x90, 0x90);
    }
}

void func_800B3000(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B3020(struct VisualObj* arg0)
{
    struct BaseObj* temp_v1 = arg0->unk50;

    arg0->base.x_pos.val = temp_v1->x_pos.val;
    arg0->base.y_pos.val = temp_v1->y_pos.val;
    D_8010A5C8[arg0->base.state](arg0);
}

void func_800B3074(struct VisualObj* arg0)
{
    D_8010A5D4[arg0->base.state](arg0);
}

void func_800B30B0(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    arg0->base.on_screen = 1;
    if (arg0->base.unk2 != 0x10) {
        arg0->base.unk15 = 0;
        func_800B3100(arg0);
    } else {
        arg0->base.unk16 = 2;
        func_80015D60(arg0, 0x25);
    }
}

void func_800B3100(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0;

    if (arg0->base.unk2 != 0x10) {
        if (arg0->base.unk2 < 7) {
            if (arg0->base.unk2 == 0) {
                func_80015D60(arg0, 0x21);
            } else {
                func_80015D60(arg0, ((arg0->base.unk2 - 1) >> 1) + 0x21);
            }
            arg0->base.unk2++;
            is_on_screen(arg0);
        } else {
            arg0->base.on_screen = 0;
            arg0->base.state = 2;
        }
    } else {
        temp_a0 = arg0->unk50;
        if (((u8)temp_a0->unk94[0] == 2) && (temp_a0->base.active != 0) && (temp_a0->unk97 & 0x40)) {
            arg0->base.unk15 = temp_a0->base.unk15;
            arg0->base.x_pos.i.hi = temp_a0->base.x_pos.i.hi;
            arg0->base.y_pos.i.hi = temp_a0->base.y_pos.i.hi;
            func_80015DC8(arg0);
            is_on_screen(arg0);
            return;
        }
        arg0->base.on_screen = 0;
        ZeroObjectState(arg0);
    }
}

void func_800B320C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B322C(struct VisualObj* arg0)
{
    arg0->base.state = 1;
    switch (arg0->base.unk2) {
    case 0:
        arg0->unk5C = 0;
        arg0->base.x_pos.i.hi -= arg0->base.unk15 ? -0x33 : 0x33;
        arg0->base.y_pos.i.hi -= 4;
        func_80015D60(arg0, 0x13);
        break;
    case 1:
        func_80015D60(arg0, 0x1E);
        break;
    case 2:
        // see func_800AF28C & func_8003D4C8 for a similar pattern
        arg0->unk42 = (((func_8002938C(0x84) * 4 + 0x18) % 16) | ((((func_8002938C(0x84) + 6) / 4) + 0x1E0) << 6));
        func_80015D60(arg0, 0x2B);
        break;
    }
    arg0->unk42 &= ~0x8000;
}

void func_800B3358(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    switch (arg0->base.unk5) {
    case 0:
        if (arg0->unk46 == 0) {
            arg0->base.unk5++;
            func_80015D60(arg0, 0x14);
        }
        break;
    case 1:
        if ((u8)entity->unk88 != 0) {
            arg0->base.unk5++;
            func_80015D60(arg0, 0x15);
        }
        break;
    case 2:
        if (arg0->unk46 == 0) {
            arg0->base.state = 2;
        }
        break;
    }
    if (entity->base.state >= 2) {
        arg0->base.state = 2;
    }
}

void func_800B3444(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    switch (arg0->base.unk5) {
    case 0:
        if (arg0->unk46 == 0) {
            arg0->base.unk5++;
            func_80015D60(arg0, 0x20);
        }
        break;
    case 1:
        if (arg0->unk46 == 0) {
            arg0->base.state = 2;
        }
        break;
    }

    if (entity->base.state == 2) {
        arg0->base.state = 2;
    }
    func_8002B718(arg0);
}

void func_800B34EC(struct VisualObj* arg0)
{
    if (arg0->unk46 == 0) {
        arg0->base.state = 2;
    }
}

void func_800B3508(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    D_8010A5E4[arg0->base.unk2](arg0);
    is_on_screen(arg0);
}

void func_800B355C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B357C(struct VisualObj* arg0)
{
    D_8010A5F0[arg0->base.state](arg0);
}

void func_800B35B8(struct VisualObj* arg0)
{
    D_8010A64C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B35F4);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B36F0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B372C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3768);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B37F8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3848);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3884);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B392C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B397C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B39B8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3A60);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3AB0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3B58);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3B94);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3C34);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3C90);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3E20);

void func_800B3E40(struct VisualObj* arg0)
{
    D_8010A694[arg0->base.state](arg0);
}

void func_800B3E7C(struct VisualObj* arg0)
{
    D_8010A6A0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3FD4);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B41AC);

void func_800B41CC(struct VisualObj* arg0)
{
    D_8010A6AC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4208);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4274);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4450);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4480);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4558);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4578);

void func_800B4598(struct VisualObj* arg0)
{
    if (arg0->unk50->base.state != 1) {
        ZeroObjectState(arg0);
    } else {
        D_8010A6B8[arg0->base.unk5](arg0);
        is_on_screen(arg0);
    }
}

void func_800B4610(struct VisualObj* arg0)
{
    D_8010A6C8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B464C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B46C8);

void func_800B46E8(struct VisualObj* arg0)
{
    D_8010A6D4[arg0->base.unk5](arg0);
    if (arg0->unk50->base.state == 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        arg0->base.unk6 = 0;
    }
}

void func_800B4754(struct VisualObj* arg0)
{
    D_8010A6E4[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4790);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4808);

void func_800B4858(struct VisualObj* arg0)
{
    D_8010A6EC[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4894);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B490C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4960);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B499C);

void func_800B4A18(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    is_on_screen(arg0);
    if (--arg0->unk54 == 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    }
}

void func_800B4A6C(struct VisualObj* arg0)
{
    D_8010A6FC[arg0->base.unk6](arg0);
}

void func_800B4AA8(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    arg0->base.unk16 = 4;
    arg0->base.x_pos.val = entity->base.x_pos.val;
    arg0->base.y_pos.val = entity->base.y_pos.val + FIXED(32);
    func_80015D60(arg0, 0x15);
    arg0->unk54 = 0x20;
    arg0->base.unk6++;
}

void func_800B4B0C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    if (--arg0->unk54 == 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    } else {
        is_on_screen(arg0);
    }
}

void func_800B4B64(struct VisualObj* arg0)
{
    D_8010A704[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4BA0);

void func_800B4CC8(struct VisualObj* arg0)
{
    if (arg0->unk56 == 0) {
        arg0->base.state++;
    } else {
        arg0->unk56--;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4D00);

void func_800B4E14(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4E34);

void func_800B518C(struct VisualObj* arg0)
{
    if (arg0->unk50->base.state >= 3) {
        arg0->base.state = 2;
    }
    func_80015DC8(arg0);
    is_on_screen(arg0);
}

void func_800B51E0(struct VisualObj* arg0)
{
    if (--arg0->unk54 == 0) {
        arg0->unk54 = 30;
        arg0->base.unk5++;
    }
    is_on_screen(arg0);
}

void func_800B522C(struct VisualObj* arg0)
{
    arg0->base.on_screen = 0;
    if (--arg0->unk54 == 0) {
        arg0->base.state = 2;
    }
    if (arg0->unk54 & 1) {
        is_on_screen(arg0);
    }
}

void func_800B5280(struct VisualObj* arg0)
{
    D_8010A760[arg0->base.unk5](arg0);
    func_80015DC8(arg0);
    func_8002B718(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B52D8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B5348);

void func_800B5448(struct VisualObj* arg0)
{
    struct PlayerObj* temp_s0 = arg0->unk50;
    func_80015DC8(arg0);
    arg0->base.x_pos.val = temp_s0->base.x_pos.val;
    arg0->base.y_pos.val = temp_s0->base.y_pos.val;
    is_on_screen(arg0);
    if (temp_s0->unk91 == 0) {
        arg0->base.state = 2;
    }
}

void func_800B54B0(struct VisualObj* arg0)
{
    D_8010A768[arg0->base.unk2](arg0);
}

void func_800B54EC(struct VisualObj* arg0)
{
    if (arg0->base.unk2 == 1) {
        arg0->unk50->unk8C--;
    }
    ZeroObjectState(arg0);
}

void func_800B5534(struct VisualObj* arg0)
{
    D_8010A784[arg0->base.state](arg0);
}

void func_800B5570(struct VisualObj* arg0)
{
    D_8010A790[arg0->base.state](arg0);
}

void func_800B55AC(struct VisualObj* arg0)
{
    if (arg0->unk50->base.state >= 2) {
        arg0->base.on_screen = 0;
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->base.unk2 == 0) {
        if (--arg0->unk5E == 0) {
            arg0->base.state = 1;
        } else {
            if (arg0->unk5C == 0) {
                arg0->base.x_pos.i.hi = arg0->base.x_pos.i.hi + 0x20;
            } else {
                arg0->base.x_pos.i.hi = arg0->base.x_pos.i.hi - 0x20;
            }
            arg0->base.y_pos.i.hi += 1;
            arg0->unk5C ^= 0x20;
            func_80015DC8(arg0);
        }
    } else {
        if (--arg0->unk5C == 0) {
            arg0->base.state = 1;
        }
        arg0->base.x_pos.val = arg0->unk50->base.x_pos.val;
        arg0->base.y_pos.val = arg0->unk50->base.y_pos.val;
        func_80015DC8(arg0);
    }
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800B56D4(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}
