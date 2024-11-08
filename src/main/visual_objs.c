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

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AEF18);

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

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF084);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF15C);

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

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF388);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF488);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF504);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AF58C);

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

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800AFC4C);

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

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1524);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B158C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B16B0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1758);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B17AC);

void func_800B17CC(struct VisualObj* arg0)
{
    D_8010A4E0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1808);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1864);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B199C);

void func_800B19BC(struct VisualObj* arg0)
{
    D_8010A4EC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B19F8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1A48);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1AD8);

void func_800B1AF8(struct VisualObj* arg0)
{
    D_8010A520[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1B34);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1B74);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1C3C);

void func_800B1C5C(struct VisualObj* arg0)
{
    D_8010A52C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1C98);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1D4C);

void func_800B1D6C(struct VisualObj* arg0)
{
    D_8010A538[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1DA8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1DE4);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1E84);

void func_800B1EA4(struct VisualObj* arg0)
{
    D_8010A544[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1EE0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B1F78);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2070);

void func_800B2090(struct VisualObj* arg0)
{
    D_8010A570[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B20CC);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2200);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B22B4);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B23DC);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2444);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2544);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2698);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2880);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B28CC);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2A3C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2C8C);

void func_800B2D48(struct VisualObj* arg0)
{
    D_8010A5B0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2D84);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2DD0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2E98);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B2F60);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3000);

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

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B30B0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3100);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B320C);

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

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3358);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B3444);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B34EC);

void func_800B3508(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    D_8010A5E4[arg0->base.unk2](arg0);
    is_on_screen(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B355C);

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

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4598);

void func_800B4610(struct VisualObj* arg0)
{
    D_8010A6C8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B464C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B46C8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B46E8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4754);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4790);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4808);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4858);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4894);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B490C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4960);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B499C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4A18);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4A6C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4B0C);

void func_800B4B64(struct VisualObj* arg0)
{
    D_8010A704[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4CC8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4D00);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4E14);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B4E34);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B518C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B51E0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B522C);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B5280);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B52D8);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B5348);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B5448);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B54B0);

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B54EC);

void func_800B5534(struct VisualObj* arg0)
{
    D_8010A784[arg0->base.state](arg0);
}

void func_800B5570(struct VisualObj* arg0)
{
    D_8010A790[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visual_objs", func_800B55AC);

void func_800B56D4(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}
