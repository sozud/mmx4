
// mostly shot objs but some other stuff

#include "common.h"

void func_800994A0(struct ShotObj* arg0)
{
    D_80108C74[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800994DC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099784);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009982C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800998D4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800999D0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099A28);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099A8C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099B0C);

void func_80099B30(struct ShotObj* arg0)
{
    D_80108CAC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099C68);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099CF0);

void func_80099D10(struct ShotObj* arg0)
{
}

void func_80099D18(struct ShotObj* arg0)
{
    D_80108CC4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099D54);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099E34);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099F28);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_80099F48);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A10C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A264);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A338);

void func_8009A358(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    CollisionRelated(arg0);
    D_80108CE4[arg0->base.state](arg0);
}

void func_8009A3B4(struct ShotObj* arg0)
{
    if (arg0->unk7C->base.unk15 == 0) {
        arg0->base.x_pos.val = arg0->unk7C->base.x_pos.val + FIXED(-75);
    } else {
        arg0->base.x_pos.val = arg0->unk7C->base.x_pos.val + FIXED(75);
    }
    arg0->base.y_pos.val = arg0->unk7C->base.y_pos.val + FIXED(2);
    arg0->unk42 = arg0->unk7C->unk42;
    arg0->base.on_screen = 0;
    D_80108CF8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A448);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A4F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A598);

void func_8009A5B8(struct ShotObj* arg0)
{
    D_80108D28[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A6B4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A7D8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A7F8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A87C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A964);

void func_8009A984(struct ShotObj* arg0)
{
    if (arg0->unk84 == 0) {
        CollisionRelated(arg0);
    }
    D_80108D5C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009A9E4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009AC40);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009AD08);

void func_8009AD28(struct ShotObj* arg0)
{
}

void func_8009AD30(struct ShotObj* arg0)
{
    D_80108D74[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009AD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009ADF8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009AEBC);

void func_8009AEDC(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009AEE4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009AF98);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B020);

void func_8009B040(struct ShotObj* arg0)
{
    D_80108D88[arg0->base.state](arg0);
}

void func_8009B07C(struct ShotObj* arg0)
{
    D_80108DA8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B0B8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B12C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B1C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B1E8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B3C8);

void func_8009B3E8(struct ShotObj* arg0)
{
    D_80108E48[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B424);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B594);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B654);

void func_8009B674(struct ShotObj* arg)
{
}

void func_8009B67C(struct ShotObj* arg0)
{
    D_80108E5C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B6B8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B734);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B7D8);

void func_8009B7F8(struct ShotObj* arg0)
{
    D_80108E9C[arg0->base.state](arg0);
    if (arg0->base.state >= 3) {
        CollisionRelated(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B85C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009B9B0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BA4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BA6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BC14);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BD08);

void func_8009BD28(struct ShotObj* arg0)
{
    D_80108EBC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BD64);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BE14);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BEF4);

void func_8009BF14(struct ShotObj* arg0)
{
    D_80108ECC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BF50);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009BFE0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C0D0);

void func_8009C0F0(struct ShotObj* arg0)
{
    D_80108EDC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C12C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C238);

void func_8009C258(struct ShotObj* arg)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C260);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C298);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C344);

void func_8009C364(struct ShotObj* arg0)
{
    D_80108F54[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C3A0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C45C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C588);

void func_8009C5F0(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_80108F6C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C638);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C784);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C860);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C96C);

void func_8009C9C8(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C9D0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009C9F0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CAA0);

void func_8009CAC0(struct ShotObj* arg0)
{
    D_80108F90[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CAFC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CBA0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CC44);

void func_8009CC64(struct ShotObj* arg0)
{
    D_80108FAC[arg0->base.state](arg0);
    CollisionRelated(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CCB4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CD80);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CDE0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CF18);

void func_8009CF38(struct ShotObj* arg0)
{
    D_80108FCC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009CF74);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D048);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D1D8);

void func_8009D1F8(struct ShotObj* arg0)
{
}

void func_8009D200(struct ShotObj* arg0)
{
    D_80108FF4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D23C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D560);

void func_8009D580(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D588);

void func_8009D74C(struct ShotObj* arg0)
{
    D_80109008[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D788);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D85C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009D8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DA08);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DA28);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DA7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DB1C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DCF4);

void func_8009DD40(struct ShotObj* arg0)
{
    D_801090AC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DD7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DE04);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DF40);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DF60);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009DFA0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E098);

void func_8009E0B8(struct ShotObj* arg0)
{
    D_8010910C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E0F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E188);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E34C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E490);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E608);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E690);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E718);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E7EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E8E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009E9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009EAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009EAF0);

void func_8009EB6C(struct ShotObj* arg0)
{
    D_80109160[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009EBA8);

void func_8009ED70(struct Unk* arg0)
{
    func_80015DC8(arg0);
    func_8002B694(arg0);
    func_8002D9BC(arg0);

    if (func_8002BB80(arg0, &g_Player) != 0) {
        if (arg0->base.unk2 & 0x40) {
        label:
            func_800AF808(arg0);
        }
    } else if (!(arg0->base.unk2 & 0x40) || (CollisionRelated(arg0), arg0->unk70 == 0)) {
        if (func_8002B160(arg0) == 0) {
            is_on_screen(arg0);
            return;
        }
    } else {
        goto label; // unfortunately seems to be necessary for a match
    }

    arg0->base.state++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009EE40);

void func_8009EE60(void)
{
}

void func_8009EE68(struct ShotObj* arg0)
{
    if (arg0->unk84 == 0) {
        CollisionRelated(arg0);
    }
    D_8010918C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009EEC8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F160);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F218);

void func_8009F238(struct ShotObj* arg0)
{
}

void func_8009F240(struct ShotObj* arg0)
{
    D_801091B4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F27C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F44C);

void func_8009F46C(struct ShotObj* arg0)
{
    struct BaseObj* unk7C = arg0->unk7C;
    arg0->base.x_pos.val = unk7C->x_pos.val;
    arg0->base.y_pos.val = unk7C->y_pos.val;
    D_801091C4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F4C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F594);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F618);

void func_8009F638(struct ShotObj* arg0)
{
    D_801091F0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F674);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F89C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F94C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009F9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009FB38);

void func_8009FB58(struct ShotObj* arg0)
{
}

void func_8009FB60(struct ShotObj* arg0)
{
    D_8010922C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009FB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009FD00);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009FE38);

void func_8009FE58(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009FE60);

void func_8009FF10(struct ShotObj* arg0)
{
    D_80109248[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_8009FF4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A00C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A0150);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A0170);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A02FC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A035C);

void func_800A037C(struct ShotObj* arg0)
{
    D_8010925C[arg0->base.state](arg0);
}

void func_800A03B8(struct ShotObj* arg0)
{
    D_801094EC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A03F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A068C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A0A18);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A0A38);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A0C4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A0FC8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A0FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A12EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A16DC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A16FC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A18A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A18F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A19A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A1B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A1BEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A1C90);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A1CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A1E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A1F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2098);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A220C);

void func_800A2278(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_8010958C[arg0->base.state](arg0);
    CollisionRelated(arg0);
}

void func_800A22D4(struct ShotObj* arg0)
{
    D_801096F4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2310);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A23B4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A23C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A23E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A241C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A24F0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A25EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2748);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A27F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2870);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2928);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A29C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2A58);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2AA0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2C70);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2D54);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2E6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2EB4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A2F2C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3010);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3078);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3170);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A31CC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A325C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A32B8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A33A0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A348C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3520);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3658);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A366C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3758);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A382C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A38B0);

void func_800A3924(struct ShotObj* arg0)
{
    D_8010978C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3960);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3C50);

void func_800A3C70(struct ShotObj* arg0)
{
}

void func_800A3C78(struct ShotObj* arg0)
{
    D_801097CC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3CB4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A3FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4230);

void func_800A4284(struct ShotObj* arg0)
{
}

void func_800A428C(struct ShotObj* arg0)
{
    D_801097E4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A42C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4518);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A46D4);

void func_800A46F4(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A46FC);

void func_800A47C4(struct ShotObj* arg0)
{
    D_8010984C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4800);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4968);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4A50);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4ADC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4D00);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4D20);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4E48);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4F04);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4F24);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A4FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5070);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A50EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5144);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5194);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5318);

void func_800A5348(struct ShotObj* arg0)
{
    D_801098B8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5384);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5404);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5460);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5500);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5540);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A56C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A56E4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5A04);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5C90);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5D20);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5D78);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5DEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5E60);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A5F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6028);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6094);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A60D0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A61CC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6238);

void func_800A6258(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6260);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A62D0);

void func_800A62F0(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s0 = arg0->unk7C;
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    CollisionRelated(arg0);
    if (temp_s0->base.state == 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        arg0->base.unk6 = 0;
    }
    D_80109950[arg0->base.state](arg0);
}

void func_800A6374(struct ShotObj* arg0)
{
    D_80109998[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A63B0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6510);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6600);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A666C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6794);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A67FC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6860);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6940);

void func_800A6960(struct ShotObj* arg0)
{
    D_801099C0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A699C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6C00);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6DCC);

void func_800A6DEC(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A6DF4);

void func_800A6FCC(struct ShotObj* arg0)
{
    D_801099E8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7008);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7104);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7208);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7240);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7318);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A73A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A73C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7458);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A74E4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7504);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7570);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7600);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A766C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A77D8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7820);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7878);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7928);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A79A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A79E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7A54);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7A90);

void func_800A7AF0(struct ShotObj* arg0)
{
    D_80109A78[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7B2C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7BC8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7C50);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7CE8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7E10);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7E40);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7E98);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7F44);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A7FF8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8074);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A80D4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8164);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A81E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A826C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A829C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A82EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A833C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A836C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A83C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A84D4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A858C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8628);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8A58);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8B88);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8C88);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8D1C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8D68);

void func_800A8DB8(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8E50);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A8FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9054);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A90C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A916C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A91D8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9210);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A92C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9334);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A93FC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A94A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A94D4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9544);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9654);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A96F8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A97C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9818);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A98AC);

void func_800A9928(struct ShotObj* arg0)
{
    D_80109B7C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9964);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9AEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9C24);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9CBC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9D98);

void func_800A9DB8(struct ShotObj* arg0)
{
    D_80109BC4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9DF4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9EC0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9F30);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800A9FD0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA000);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA030);

void func_800AA10C(struct ShotObj* arg0)
{
    D_80109BE0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA148);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA20C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA2FC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA3A0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA488);

void func_800AA5A4(struct ShotObj* arg0)
{
    D_80109BF8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA68C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA730);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA85C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA954);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AA994);

void func_800AAA98(struct ShotObj* arg0)
{
    D_80109C20[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AAAD4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AAB74);

void func_800AAC5C(struct ShotObj* arg0)
{
    D_80109C2C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AAC98);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AAD44);

void func_800AAD64(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AAD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AAE94);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AAFF8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB050);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB128);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB170);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB224);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB32C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB384);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB3A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB4C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB518);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB564);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB66C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB6C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB710);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB768);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB814);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB868);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB8EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB98C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AB9C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ABB50);

void func_800ABB70(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s1 = arg0->unk7C;
    if (temp_s1->unk94 == 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi - 20, -1);
    }
    if (temp_s1->unk94 == 1) {
        arg0->unk8C = 0;
        arg0->base.state = 1;
        arg0->base.unk5 = 3;
        arg0->base.unk6 = 0;
        arg0->base.unk7 = 1;
        arg0->unk50 = 0;
        temp_s1->unk8C = 0;
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi - 20, -1);
        arg0->base.x_pos.i.hi = 0;
        arg0->base.y_pos.i.hi = 0;
        arg0->unk5C = 0x30;
        return;
    }
    arg0->base.on_screen = 0;
    D_80109D84[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ABE08);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC114);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC180);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC204);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC31C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC364);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC3BC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC440);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC4A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC4F8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC550);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC5BC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC610);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC66C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC6A8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC6E8);

void func_800AC708(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC710);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC7CC);

void func_800AC7EC(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    }
    arg0->base.on_screen = 0;
    D_80109DF8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC848);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AC8C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ACCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ACD04);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ACD84);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ACDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ACE90);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ACF60);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD00C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD080);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD12C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD1B0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD224);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD338);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD404);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD440);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD47C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD4DC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD538);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD630);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD66C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD6DC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD820);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD868);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD92C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AD9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADA0C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADA64);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADAD8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADBE0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADCE8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADD40);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADDB4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADE04);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADE54);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADED4);

void func_800ADEF4(struct ShotObj* arg0)
{
    D_80109EE8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800ADF30);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE1BC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE2AC);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE2FC);

void func_800AE31C(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE324);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE3D4);

void func_800AE3F4(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    }
    arg0->base.on_screen = 0;
    D_80109F44[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE450);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE4F0);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE594);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE63C);

void func_800AE65C(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->base.state = 3;
    }
    D_8010A064[arg0->base.state](arg0);
}

void func_800AE6B4(struct BazObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    arg0->base.x_pos.val = g_Player.base.x_pos.val;
    arg0->base.y_pos.val = g_Player.base.y_pos.val;

    if (arg0->base.state == 0) {
        func_800AE714(arg0, ptr);

    } else {
        func_800AE790(arg0, ptr);
    }
}

void func_800AE714(struct BazObj* arg0, struct PlayerObj* arg1)
{
    s32 var_v1 = arg0->base.unk2 == 0 ? 2 : 1;

    if (arg1->unk9B[0] == var_v1 || arg1->unk9B[1] == var_v1) {
        arg0->base.on_screen = 1;
        func_80015D60(arg0, arg0->base.unk2 + 8);
        arg0->base.state++;
    }
}

void func_800AE790(struct BazObj* arg0, struct PlayerObj* arg1)
{
    if ((arg1->unk9B[0] == 0) && (arg1->unk9B[1] == 0)) {
        arg0->base.on_screen = 0;
        arg0->base.state = 0;
    } else {
        func_80015DC8(arg0);
    }
}

void func_800AE7DC(struct UnkObj* arg0)
{
    struct PlayerObj* player = &g_Player;

    arg0->unk47 = player->cur_anim;
    arg0->unk15 = player->base.unk15;
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;

    if (arg0->unk4 == 0) {
        func_800AE848(arg0, player);
    } else {
        func_800AE88C(arg0, player);
    }
}

void func_800AE848(struct UnkObj* arg0, struct PlayerObj* player)
{
    if (player->unk8C != 0) {
        if (player->unk8C > 0) {
            arg0->unk3 = 1;
            func_800AEA58();
            return;
        }
        player->unk8C = 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE88C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE8E4);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE95C);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AE9D8);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AEA58);

INCLUDE_ASM("asm/us/main/nonmatchings/shot_objs", func_800AEAA0);
