#include "common.h"

// uncomment to skip movies
// #define SKIP_MDEC

struct Temp1 {
    u8 pad[0xA000];
};

struct Temp2 {
    u8 pad[0x2000];
};

struct Temp3 {
    u8 pad[0x200];
};

struct Temp4 {
    u8 pad[0x100];
};

struct Temp5 {
    u8 pad[0x78];
};

extern s32 D_80139514;
extern u8 D_80139554;
extern s8 D_80139568;
extern s16 D_8013955C;
extern struct Temp1 D_801499C8[];
extern struct Temp2 D_80169D98[];
extern struct Temp3 D_80139830[];
extern struct Temp4 D_80139C30[];
extern struct Temp5 D_80139E30[];
extern u8 D_80173C84;
extern s32 D_80175EE8[];

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012A3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012D28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012D4C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012D68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012D88);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012E18);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012E2C);

void func_80012E38(void)
{
    func_80013AD8(0x40, 0, 0);
    func_80014C70();
    func_80013890(0x41, 0x801F3000);
    func_80014C70();
}

void func_80012E80()
{
    func_80013AD8(0, 0, 0);
    func_80014C70();
}

void func_80012EB0(void)
{
}

void func_80012EB8(void)
{
    s32 var_a0;

    if (engine_obj.cur_character == CHARACTER_X) { // g_GameVars.unk43
        var_a0 = 0x4E;
        if (engine_obj.unk37 == 0) { // g_GameVars.unk37
            var_a0 = 0x4B;
        }
    } else {
        var_a0 = 0x4D;
    }
    func_80013AD8(var_a0, 0, 0);
    func_80014A90(0, 0);
    func_80013530();
    D_80173C80 = D_8015D9C8;
    D_80166BB4 = D_80142F70;
    func_80015C10();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80012F44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013014);

void func_8001326C(u8 arg0)
{
    DR_MODE* draw_mode;
    u8 temp_a0;
    SPRT* sprt;
    struct Prim* prim;
    s32 tpage;

    if ((arg0 != 0) || !(D_80141BD8.unk0 & 0x10)) {
        sprt = *(SPRT**)0x1F800100;
        draw_mode = *(DR_MODE**)0x1F800104;
        prim = &D_800EE504[arg0];
        tpage = GetTPage(0, 0, 0x380, 0x100);
        SetDrawMode(draw_mode, 0, 0, tpage, 0);
        setSprt(sprt);
        setXY0(sprt, prim->x, prim->y);
        setUV0(sprt, (prim->uv & 0xF) * 0x10, prim->uv & 0xF0);
        temp_a0 = prim->clut;
        setShadeTex(sprt, 1);
        setSemiTrans(sprt, 0);
        // this ought to be setClut but can't figure it out
        sprt->clut = ((temp_a0 & 0xF) | (((temp_a0 >> 4) + 0x1E0) << 6));
        setWH(sprt, prim->w * 0x10, prim->h * 0x10);
        catPrim(draw_mode, sprt);
        addPrims(&cur_draw_info->unk80, draw_mode, sprt);
        *(SPRT**)0x1F800100 = ++sprt;
        *(DR_MODE**)0x1F800104 = ++draw_mode;
    }
}

void func_80013404(u8 arg0)
{
    s32 temp_v1;
    u8 var_s0;
    s8* a0;
    s8* var_v0;
    struct EngineObj* ptr = &engine_obj;
    *(void**)0x1F800100 = &D_801499C8[SP_DRAW_INFO_POS];
    *(void**)0x1F800104 = &D_80169D98[SP_DRAW_INFO_POS];

    func_800160F4();

    for (var_s0 = 0; var_s0 < 3; var_s0++) {
        func_8001326C(var_s0);
    }
    if (arg0) {
        if (ptr->cur_character != CHARACTER_X) {
            func_8001326C(4);
        } else {
            func_8001326C(3);
        }
        func_8001326C(5);

        a0 = &D_800EE54C;
        if (ptr->stage == 0xC) {
            var_v0 = a0 + 0xB;
        } else {
            var_v0 = a0 + ptr->stage;
        }
        D_800EE538 = *var_v0;

        func_8001326C(6);

        if (ptr->stage < 9) {
            if (ptr->substage != 0) {
                func_8001326C(8);
            } else {
                func_8001326C(7);
            }
        }
    }
}

void func_80013530(void)
{
    func_800129F0(0x10);
    if (D_80141BDC[0] != 0) {
        do {
            func_80013404(0);
            func_800127C8(1);
        } while (D_80141BDC[0] != 0);
    }
}

void func_80013588(s32 arg0)
{
    u8 sp10;
    sp10 = 0xA0;
    do {
    } while (CdInit() == 0);
    do {

    } while (CdControl(CdlSetmode, &sp10, 0) == 0);
    VSync(3);
    D_80137CE4 = 0;
    D_801406AC = 0;
    D_8013BD40 = 0;
    D_801374B8 = 0;
    D_801374B4 = 0;
    D_80137CF0 = 0;
    D_80137CF4 = 0;
    func_80016334();
}

s32 func_80013614(s32 arg0, s32* arg1)
{
    struct Unk5* temp_v0;
    temp_v0 = &D_800F0E18[arg0];
    *arg1 = temp_v0->unk4;
    D_80137CC0 = temp_v0->unk8;
    return temp_v0->unk0;
}

void func_80013650(void)
{

    if (D_80137CD8 == 0) {
        CdReadyCallback(&MyCdReadyCallback);
    } else {
        CdReadyCallback(&func_80013E68);
    }
    while (CdControl(CdlReadN, 0, 0) == 0)
        ;
    D_801406AC = 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800136B0);

void func_800137F0(void)
{
    CdReadyCallback(0);
    D_801406AC = 0;
    do {

    } while (CdControl(CdlPause, 0, 0) == 0);
    D_801406AC = 2;
    D_8015D9C8 = D_80137DC4;
    D_80142F70 = D_80137DD0;
}

u8 func_8001385C(void)
{
    u8 sp10;

    do {

    } while (CdControlB(CdlNop, 0, &sp10) == 0);
    return sp10;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013890);

void func_80013968(void)
{
    u8 sp10;

    sp10 = 0xA0;
    D_801406AC = 0;
    D_80137CEC = 0;
    CdIntToPos(D_80137CCC, &D_80137CF8);
    D_80137CCC -= 1;
    do {
    loop_1:
        if (CdReady(1, NULL) != 0) {
            goto loop_1;
        }
        if (CdControl(CdlSetmode, &sp10, NULL) == 0) {
            goto loop_1;
        }
        VSync(3);
    } while (CdControl(CdlSetloc, &D_80137CF8.minute, NULL) == 0);
    func_80013650();
}

void MyCdReadyCallback(void)
{
    if (D_801406AC != 0) {
        D_80137CEC += 1;
        if (CdReady(1, NULL) != 1) {
        pos:
            CdReadyCallback(NULL);
            CdControlB(CdlPause, NULL, NULL);
            D_801406AC = 0x80;
        } else {
            if (func_800136B0() != -1) {
                if (D_80137CBC == 0) {
                    func_800137F0();
                }
            } else {
                goto pos;
            }
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013DA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80013E68);

void func_80014140(void)
{
    if (D_80137CE8 != 0) {
        D_80137CE8 = 0;
        D_80137CC4 = D_80137DC4;
    }
    if (func_800136B0() == -1) {
        CdReadyCallback(0);
        CdControlB(CdlPause, NULL, NULL);
        D_801406AC = 0x80;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800141BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800142BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014514);

s32 func_800147AC();
extern u8 D_8013BD40;

void func_80014780(void)
{
    if (D_8013BD40 != 0) {
        func_800147AC();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800147AC);

void func_800148E4(void)
{
}

void func_800148EC()
{
    u32 temp_a1;

    temp_a1 = D_80137D08[D_801374B4 * 3];
    D_80137CFC.x = temp_a1 >> 0x10;
    D_80137CFC.y = temp_a1;
    D_80137CFC.w = 0x40;
    D_80137CFC.h = 0x10;
    LoadImage(&D_80137CFC, &D_8012F4B4[D_801374B4 << 9]);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014968);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014A90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80014C70);

void func_80014DC4(void)
{
    u8 var_v1;

    D_80137DFC = 0;

    for (var_v1 = 0; var_v1 < 6; var_v1++) {
        D_8013E198[var_v1] = -1;
    }
    for (var_v1 = 0; var_v1 < 4; var_v1++) {
        D_8013E1C8[var_v1] = -1;
    }
    for (var_v1 = 0; var_v1 < 4; var_v1++) {
        D_8013924C[var_v1] = -1;
    }
    for (var_v1 = 0; var_v1 < 24; var_v1++) {
        D_80139234[var_v1] = -1;
    }

    D_8013DC10 = &_SsNoteOn;
    D_8013DC14 = &_SsSetProgramChange;
    D_8013DC1C = &dmy_SsGetMetaEvent;
    D_8013DC18 = &dmy_SsSetPitchBend;
    D_8013DC20 = &_SsSetControlChange;
    D_8013DC24 = &dmy_SsContBankChange;
    D_8013DC2C = &_SsContMainVol;
    D_8013DC30 = &dmy_SsContPanpot;
    D_8013DC34 = &dmy_SsContDamper;
    D_8013DC38 = &dmy_SsContNrpn1;
    D_8013DC3C = &dmy_SsContNrpn2;
    D_8013DC40 = &_SsContRpn1;
    D_8013DC44 = &dmy_SsContRpn2;
    D_8013DC48 = &dmy_SsContExternal;
    D_8013DC4C = &dmy_SsContResetAll;
    D_8013DC28 = &dmy_SsContDataEntry;
    D_8013DC54 = &dmy_SsSetNrpnVabAttr0;
    D_8013DC58 = &dmy_SsSetNrpnVabAttr1;
    D_8013DC5C = &dmy_SsSetNrpnVabAttr2;
    D_8013DC60 = &dmy_SsSetNrpnVabAttr3;
    D_8013DC64 = &dmy_SsSetNrpnVabAttr4;
    D_8013DC68 = &dmy_SsSetNrpnVabAttr5;
    D_8013DC6C = &dmy_SsSetNrpnVabAttr6;
    D_8013DC70 = &dmy_SsSetNrpnVabAttr7;
    D_8013DC74 = &dmy_SsSetNrpnVabAttr8;
    D_8013DC78 = &dmy_SsSetNrpnVabAttr9;
    D_8013DC7C = &dmy_SsSetNrpnVabAttr10;
    D_8013DC80 = &dmy_SsSetNrpnVabAttr11;
    D_8013DC84 = &dmy_SsSetNrpnVabAttr12;
    D_8013DC88 = &dmy_SsSetNrpnVabAttr13;
    D_8013DC8C = &dmy_SsSetNrpnVabAttr14;
    D_8013DC90 = &dmy_SsSetNrpnVabAttr15;
    D_8013DC94 = &dmy_SsSetNrpnVabAttr16;
    D_8013DC98 = &dmy_SsSetNrpnVabAttr17;
    D_8013DC9C = &dmy_SsSetNrpnVabAttr18;
    D_8013DCA0 = &dmy_SsSetNrpnVabAttr19;

    SsInit();
    SsSetTableSize(&D_80137E0C, 3, 0xA);
    SsSetTickMode(1);
    SsUtSetReverbType(2);
    while (SpuClearReverbWorkArea(2) == -1)
        ;
    func_800E0D0C();
    SsUtSetReverbDepth(8, 8);
}

void func_8001512C(void)
{
    SsStart();
    SsSetMVol(0x7F, 0x7F);
    SsSetSerialAttr(0, 0, 0);
    SsSetSerialVol(0, 0x4A, 0x4A);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015284);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800153D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001540C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800154E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800157AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015930);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015A10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015A50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015C10);

void func_80015D60(struct Unk19* arg0, s32 arg1)
{
    arg0->unk34 = arg0->unk30[arg1];
    arg0->unk17 = arg1;
    arg0->unk48 = 0xFF;
    arg0->unk44 = *arg0->unk34;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015D90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80015DC8);

void clear_vram_rect_ptrs(void)
{
    u32 i;
    struct RectPtrPair* ptr;

    ptr = &vram_rect_ptrs[0];
    vram_rect_ptr = ptr;

    for (i = 0; i < 8; i++) {
        ptr->rect.x = 0;
        ptr->rect.y = 0;
        ptr->rect.w = 0;
        ptr->rect.h = 0;
        ptr->ptr = NULL;
        ptr++;
    }
}

void load_vram_rect_ptrs(void)
{
    struct RectPtrPair* cur;
    for (cur = &vram_rect_ptrs[0]; cur < &vram_rect_ptrs[8]; cur++) {
        if (cur->ptr != NULL) {
            LoadImage(&cur->rect, cur->ptr);
        }
    }
    vram_rect_ptr = &vram_rect_ptrs[0];
}

extern s32 player_gfx_buf_0[];
extern s32 player_gfx_buf_1[];

void decompress_player_gfx(struct PlayerObj* arg0, s16 x, s16 y)
{
    u8* src;
    u8* dst;
    s32* new_var;
    struct RectPtrPair* gfx;
    u32 temp_a1;
    s16 size;

    if (arg0->prev_anim == arg0->cur_anim) {
        return;
    }

    src = arg0->unk38;
    new_var = arg0->unk38;
    arg0->prev_anim = arg0->cur_anim;
    temp_a1 = new_var[arg0->cur_anim];
    size = temp_a1 >> 0x14;
    if (arg0->unk49 == 3) {
        dst = player_gfx_buf_0;
    } else {
        dst = &player_gfx_buf_1[arg0->unk49 * 1024];
    }
    decompress_gfx(&src[temp_a1 & 0xFFFFF], dst);

    gfx = vram_rect_ptr;
    do {
        gfx->rect.x = x;
        gfx->rect.y = y;
        gfx->ptr = dst;
        if (size < 16) {
            gfx->rect.w = size * 4;
            gfx->rect.h = 16;
            size = 0;
        } else {
            gfx->rect.w = 64;
            gfx->rect.h = size / 16 * 16; // quantize to a multiple of 16
            y += gfx->rect.h;
            size -= gfx->rect.h;
            dst += 2048;
        }
        gfx++;
    } while (size != 0);

    gfx->ptr = NULL;
    vram_rect_ptr = gfx;
}

void load_palette(void)
{
    if (need_palette_load != 0) {
        if (need_palette_load & 1) {
            LoadImage(&D_800F1658, SP_PALETTE);
        } else if (need_palette_load & 2) {
            LoadImage(&D_800F1658, &D_80141F70); // D_80141F70 is in vram_rect_ptr but can't figure out a match
        }

        need_palette_load = 0;
    }
}

// copy scratchpad to memory location
void func_80016074(void)
{
    u16* var_a0;
    u16* var_a1;
    u32 var_v1;

    var_a1 = &D_80141F70;
    var_a0 = *(u16**)0x1F800028;
    var_v1 = 0;
    do {
        *var_a1++ = *var_a0++;
        var_v1 += 1;
    } while (var_v1 < 0x800U);
}

void func_800160AC(void)
{
    u16* src = D_801441B4;
    u16* dst = *(u16**)0x1F800008;
    s32 count = (*(u32*)0x1F80000C - (u32)dst) >> 1;

    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}

extern s32 D_800F1660;
extern s32 D_800F1860;

void func_800160F4(void)
{
    LoadImage(&D_800F1860, &D_800F1660);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016124);

void func_80016334(void)
{
    func_80016420(0);
    D_80171EA9 = 1;
    D_8013956C = 1;
    D_801419AC = 0;
    D_801441B8 = 0;
    D_80141F4A = 0;
    D_8013952C = 0;
    D_80141BD4 = 0;
    D_80139524 = 0x80;
    D_80139530 = 0;
    D_80141BD0 = 0;
    D_80139564 = 0;
    D_801441B0 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800163BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800163EC);

void func_80016448(u8 arg0);
extern u8 D_80139524;

void func_80016420(s8 arg0)
{
    D_80139524 = arg0;
    func_80016448(arg0);
}

void func_80016448(u8 arg0)
{
    s32 temp_v0;
    D_80139528 = arg0;
    if (D_80171EA9 == 1) {
        D_80139520.val0 = arg0;
        D_80139520.val1 = 0;
        D_80139520.val2 = arg0;
        D_80139520.val3 = 0;
    } else {
        temp_v0 = arg0 >> 1;
        D_80139520.val0 = temp_v0; // volume for CD(L) -> SPU (L)
        D_80139520.val1 = temp_v0; // volume for CD(L) -> SPU (R)
        D_80139520.val2 = temp_v0; // volume for CD(R) -> SPU (L)
        D_80139520.val3 = temp_v0; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139520);
}

void func_800164D8(void)
{
    s8 pad[2];
    s32 a = engine_obj.stage * 8;
    s32 b = engine_obj.substage * 4;
    s32 c = engine_obj.cur_character * 2;
    s32 temp_v0;

    temp_v0 = a + b + c;
    func_8001663C(D_800F1A0C[temp_v0], D_800F1A0C[temp_v0 + 1]);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001653C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001663C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800168D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800169D8);

void func_80016B38(void)
{
    D_80141BD0 = 0;
    D_80141BD4 = 0;
    D_80139564 = 0;
}

void func_80016B58(void)
{
    s32 temp_v0;
    u8* ptr = &D_80139554;

    temp_v0 = CdSync(1, ptr);
    if ((temp_v0 == 2) && !(*ptr & 0x40) && (CdControl(CdlReadS, 0, ptr) != 0)) {
        D_80173C84 = 2;
        D_80139530 = temp_v0;
    }
}

void func_80016BDC(void)
{
    if (D_8013955C & D_801441B8) {
        while (CdControl(CdlPause, 0, &D_80139554) == 5)
            ;
        D_80139530 = 3;
        if (D_80139554 & 0x10) {
            D_8013952C = 1;
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016C5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016D0C);

void func_80016DAC()
{
    s32 var_v0;

    if (CdSync(1, 0) == 2) {
        if (D_801441B0 == 0) {
            var_v0 = CdControl(CdlSeekL, &D_80139514, 0);
        } else {
            var_v0 = CdControlF(CdlSeekL, &D_80139514);
        }
        if (var_v0 != 0) {
            D_80139530 = 1;
        }
        D_80139564 = 2;
    }
}

void func_80016E34()
{
    if (CdSync(1, 0) == 2 && CdControl(CdlSetfilter, &D_80175EE8, 0) != 0) {
        D_80139530 = 5;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016E84);

void func_80016F0C()
{
    s32 temp_s0 = D_80141BD4;
    if (temp_s0 == 2) {
        func_80016420(0);
        if (D_80139564 == temp_s0) {
            if (D_8013955C != 0) {
                while (CdControlB(CdlPause, 0, NULL) == 0)
                    ;
            }
        }
        SsSetSerialAttr(0, 0, 0);
        D_80139564 = 0;
        D_80139568 = 0;
        D_80173C84 = 0;
        D_80139530 = 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80016FB4);

void decompress_gfx(u16* src, u16* dest)
{
    s32 var_a3;
    u32 upper_bits;
    u16 var_t0;
    u16 var_t1;
    u32 var_v1;
    s32 arg2;
start:
    var_t1 = *(src++);

    var_t0 = 0x8000;
    for (var_a3 = 0x10; var_a3 != 0; var_t0 >>= 1, var_a3--) {
        if (!(var_t1 & var_t0)) {
            // v1 assignment probably fake, found by permuter
            *(dest++) = (var_v1 = *(src++));
            continue;
        }
        arg2 = *(src++);
        upper_bits = arg2 & 0xF800;
        if (upper_bits != 0) {
            var_v1 = upper_bits >> 0xB;
            arg2 &= 0x7FF;
        } else {
            var_v1 = *(src++);
        }
        if ((var_v1 | arg2) != 0) {
            if (arg2 == 0) {
                do {
                    *(dest++) = 0;
                    var_v1 -= 1;
                } while (var_v1 != 0);
                continue;
            } else {
                arg2 = dest - arg2;
                do {
                    *(dest++) = *((u16*)arg2);
                    arg2 += 2;
                    var_v1 -= 1;
                } while (var_v1 != 0);
            }
        } else {
            return;
        }
    }

    goto start;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800170B0);

void func_800170E0(void)
{
    need_palette_load |= 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017100);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017268);

void func_80017340(void)
{
    u8 start;
    s8 end;
    u8 var_v0;

    *(void**)0x1F800100 = &D_801499C8[*(s32*)0x1F800000];
    *(void**)0x1F800104 = &D_80169D98[*(s32*)0x1F800000];
    *(void**)0x1F800110 = &D_801499C8[*(s32*)0x1F800000];

    func_80017E84();

    if (engine_obj.cur_character == CHARACTER_X) {
        end = 10;
    } else {
        end = 8;
    }

    if (engine_obj.cur_character == CHARACTER_X) {
        func_800175AC(0x14);
        func_800175AC(0);
        func_800175AC(1);
        if (bar_object.unk16[1] != 0) {
            func_800175AC(0x15);
            func_800175AC(2);
            func_800175AC(3);
        }
    }

    if (engine_obj.cur_character == CHARACTER_X) {
        start = 2;
    } else {
        start = 0;
    }

    while (start < end) {
        if (bar_object.unk16[start] != 0) {
            func_800175AC(start + 0x14);
            func_800175AC(start * 2);
            func_800175AC(start * 2 + 1);
        }
        start++;
    }

    if (bar_object.unk20 != 0) {
        func_800175AC(0x23);
    }
    if (bar_object.unk21 != 0) {
        func_800175AC(0x24);
    }
    if (bar_object.unk22 != 0) {
        func_800175AC(0x25);
    }
    func_800175AC(0x1F);
    if (bar_object.unk25 != 0) {
        func_800175AC(0x26);
    }
    func_800175AC(0x1E);
    func_800175AC(0x20);
    if (engine_obj.stage > 0 && engine_obj.stage < 9) {
        if (engine_obj.cur_character == CHARACTER_X) {
            var_v0 = bar_object.unk16[engine_obj.stage + 1];
        } else {
            var_v0 = bar_object.unk16[D_800F1C0F[engine_obj.stage]];
        }
        if (var_v0 != 0) {
            func_800175AC(0x21);
        }
    }
    func_800175AC(0x22);
    func_800179BC();
    func_80017F2C();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800175AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800179BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017E84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80017F2C);

// general movie playing code
#ifndef SKIP_MDEC
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018000);
#else
void func_80018000(s32 temp)
{
    asm(".rept 184 ; nop ; .endr");
}
#endif

// capcom logo playing code
#ifndef SKIP_MDEC
INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800182E8);
#else
void func_800182E8(void)
{
    asm(".rept 194 ; nop ; .endr");
}
#endif

void Set24BitDisp(s32 w, s32 h)
{
    RECT rect;
    old_dispenv[0] = draw_infos[0].dispenv;
    old_dispenv[1] = draw_infos[1].dispenv;
    ResetGraph(0);
    rect.x = 0;
    rect.y = 0;
    rect.w = 480;
    rect.h = 480;
    VSync(0);
    ClearImage(&rect, 0, 0, 0);
    DrawSync(0);
    SetDispMask(1);
    SetDefDispEnv(&draw_infos[0].dispenv, 0, 0, w, h);
    SetDefDispEnv(&draw_infos[1].dispenv, 0, 240, w, h);
    draw_infos[1].dispenv.isrgb24 = 1;
    draw_infos[0].dispenv.isrgb24 = 1;
    draw_infos[1].dispenv.isinter = 0;
    draw_infos[0].dispenv.isinter = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018788);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018B88);

void func_80018E50(void)
{
    u8 sp10 = 0x80;
    func_800192F8();
    while (CdControlB(CdlPause, 0, NULL) == 0)
        ;
    VSync(0);
    CdDataCallback(0);
    CdReadyCallback(0);
    DecDCToutCallback(0);
    StUnSetRing();
    while (CdReset(0) == 0)
        ;
    VSync(3);
    while (CdControl(CdlSetmode, &sp10, 0) == 0)
        ;
    VSync(3);
}

void func_80018EEC(void)
{
    do {

    } while (D_80139634 != 0);
    D_801395E4 = D_801395E8;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80018F18);

void func_80018FD0(u32 arg0)
{
    D_800F1D8C = arg0;
    if (D_80171EA9 != 0) {
        D_80139644.val0 = arg0;
        D_80139644.val1 = 0;
        D_80139644.val2 = arg0;
        D_80139644.val3 = 0;
    } else {
        D_80139644.val0 = arg0 >> 1; // volume for CD(L) -> SPU (L)
        D_80139644.val1 = arg0 >> 1; // volume for CD(L) -> SPU (R)
        D_80139644.val2 = arg0 >> 1; // volume for CD(R) -> SPU (L)
        D_80139644.val3 = arg0 >> 1; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139644);
}

void func_80019058(s8 arg0)
{
    u32 temp_v0;

    D_80171EA9 = arg0;
    if (arg0 & 0xFF) {
        D_80139644.val1 = 0;
        D_80139644.val3 = 0;
        D_80139644.val0 = D_800F1D8C;
        D_80139644.val2 = D_800F1D8C;
    } else {
        temp_v0 = D_800F1D8C >> 1;
        D_80139644.val0 = temp_v0; // volume for CD(L) -> SPU (L)
        D_80139644.val1 = temp_v0; // volume for CD(L) -> SPU (R)
        D_80139644.val2 = temp_v0; // volume for CD(R) -> SPU (L)
        D_80139644.val3 = temp_v0; // volume for CD(R) -> SPU (R)
    }
    CdMix(&D_80139644);
}

extern s32 D_80139614;

void func_800190F0(s32 arg0)
{
    D_80139614 = arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019100);

extern s32 D_80139610;

void func_80019208(void)
{
    D_80139610 += 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019228);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800192F8);

void func_800193D8(struct EngineObj* arg0)
{
    u8* ptr = &D_80141BDF;
    u8 temp_s1 = *ptr;
    u8 temp_s3 = engine_obj.unk1;
    u8 temp_s4 = engine_obj.unk2;

    D_800F1F64[arg0->unk1](arg0);

    if (*ptr != temp_s1 && engine_obj.unk1 == temp_s3 && engine_obj.unk2 == temp_s4) {
        func_8001540C(0, 12, NULL);
    }
    if (arg0->unk1 != 10) {
        func_80016124();
        update_misc_objects();
        init_objects();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800194C8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001961C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001989C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019B64);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019BF4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019D04);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80019EF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A308);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A498);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A710);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A7D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A860);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A8E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001A9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001AA98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001ABDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001AE8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B10C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B388);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B4E4);

void func_8001B558(void)
{
    s32 temp;
    if (controller_state & (PADstart | PADRup | PADRdown | PADRleft | PADRright)) {
        func_8001540C(0, 0x22, 0);
        reset_objects();
        temp = D_801721B8;
        if (temp < 5) {
            if (temp >= 0) {
                game_info.unk0 = 7;
                game_info.unk2 = 0;
                game_info.unk3 = 0;
                if (D_800F1D90 != 0xFF) {
                    game_info.unk8 = func_8001E850(&D_800F22D0, 0);
                    game_info.mode = 1;
                    D_80141BDF[0] = 1;
                } else {
                    game_info.unk8 = func_8001E850(&D_800F22E0, 0);
                    game_info.mode = 3;
                    D_80141BDF[0] = 0;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B644);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B718);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001B8B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001BCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001BE10);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C008);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C07C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C210);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C30C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C3E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C4B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C5A8);

void InitMemcards(void)
{
    EnterCriticalSection();
    D_80139670 = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_80139674 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80139678 = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    D_8013967C = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_80139680 = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_80139684 = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80139688 = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(D_80139670);
    EnableEvent(D_80139674);
    EnableEvent(D_80139678);
    EnableEvent(D_8013967C);
    EnableEvent(D_80139680);
    EnableEvent(D_80139684);
    EnableEvent(D_80139688);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C854);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C8AC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001C8F4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CB24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CC5C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CD70);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CE84);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CEDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CF74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001CFF4);

void func_8001D064(void)
{
    s32 var_v1;
    s8* var_a0;
    s8 fill;

    SetDispMask(0);
    func_8001D104();
    func_80012E38();
    func_8001512C();
    PlayCapcomLogo();
    fill = 0;
    var_a0 = (s8*)&game_info;
    var_v1 = sizeof(game_info);
    while (var_v1-- != 0) {
        *var_a0++ = fill;
    }
    D_8013BD44 = 1;
    game_info.unk0 = 0;
    game_info.mode = 0;
    game_info.unk2 = 0;
    game_info.unk3 = 0;
    func_800128B8(&func_8001DAF8);
}

void func_8001D104(void)
{
}

void PlayCapcomLogo(void)
{
    func_800182E8(); // nop out to skip capcom logo
    SetDispMask(0);
}

void func_8001D134(void)
{
    func_80023D30();
    func_80016F0C();
    func_80015930(0xFF, 0);
    reset_objects();
    func_8002AB20();
}

void func_8001D178(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 0;
        arg0->mode++;
    }
}

void func_8001D1A4(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 1;
        func_8001D134();
        arg0->mode = 0;
        arg0->unk0++;
    }
}

void func_8001D1F0(struct GameInfo* arg0)
{
    if (arg0->mode == 0) {
        func_8001D230(arg0);
    } else {
        func_8001D284(arg0);
    }
}

void func_8001D230(struct GameInfo* arg0)
{
    arg0->unkD = 1;
    D_80173C80 = 0x80178000;
    func_80018000(1); // nop out to skip opening cinematic
    arg0->mode++;
}

void func_8001D284(struct GameInfo* arg0)
{
    arg0->unk0 = 1;
    arg0->mode = 0;
}

void func_8001D294(struct GameInfo* arg0)
{
    D_800F2170[arg0->mode](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001D2D0);

void func_8001D364(struct GameInfo* arg0)
{
    u32 var_s0;
    struct MiscObj* temp_v0;

    reset_objects();
    func_8002AB20();
    func_800160AC();
    func_80021E74();
    func_8002771C();
    func_80028BF0();
    func_80027850();
    func_80027D40();
    func_800281E8();
    func_80035240();
    func_80028DB4();
    func_80028F58();
    func_80023CE0();
    func_8001FDBC();
    for (var_s0 = 2; var_s0 < 5; var_s0++) {
        temp_v0 = find_free_misc_obj();
        if (temp_v0 != NULL) {
            temp_v0->base.active = 1;
            temp_v0->base.id = 0x12;
            temp_v0->base.unk2 = var_s0;
        }
    }
    func_8001FEC0();
    arg0->unk2 = 0;
    arg0->mode++;
    func_800129A4(8);
    func_80023D68();
}

void func_8001D460(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 0;
    }
    if (--arg0->unk4 == 0 || g_Player.base.active == 0 || g_Player.base.state == 3) {
        func_800129F0(8);
        func_80022074();
        arg0->mode++;
    } else {
        get_random();
        func_80021F34();
    }
    func_80023D68();
}

void func_8001D514(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 1;
        D_80141BDE[0] = 0;
        func_8001D134();
        reset_game_engine();
        arg0->unk0 = 3;
        arg0->mode = 0;
    } else {
        func_80023D68();
    }
}

void func_8001D57C(struct GameInfo* arg0)
{
    D_800F2184[arg0->mode](arg0);
    update_misc_objects();
    init_objects();
}

void func_8001D5C8(struct GameInfo* arg0)
{
    struct MiscObj* temp_v0;

    arg0->unkD = 1;
    func_8001D134();
    func_80012E80();
    func_800160F4();
    temp_v0 = find_free_misc_obj();
    if (temp_v0 != NULL) {
        temp_v0->base.active = 1;
        temp_v0->base.id = 0x15;
    }
    arg0->unk4 = 0x12C;
    func_800129A4(8);
    arg0->mode++;
}

void func_8001D64C(struct GameInfo* arg0)
{
    if (--arg0->unk4 == 0) {
        arg0->mode++;
        func_800129F0(8);
    }
}

void func_8001D698(struct GameInfo* arg0)
{
    arg0->unkD = 1;
    arg0->unk0 = 0;
    arg0->mode = 0;
    arg0->unk2 = 0;
    arg0->unk3 = 0;
    if (++arg0->unkC == 4) {
        arg0->unkC = 0;
    }
}

void func_8001D6DC(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->unkE == 1) {
            arg0->unk0 = 6;
        } else {
            arg0->unk0 = 1;
        }
        return;
    }

    switch (arg0->unkE) {
    case 0:
        break;
    case 1:
        update_misc_objects();
        func_80023D68();
        break;
    case 2:
        func_80023D68();
        break;
    case 3:
        update_misc_objects();
        init_objects();
        break;
    }
}

void func_8001D77C(struct GameInfo* arg0)
{
    D_800F2194[arg0->mode](arg0);
    update_misc_objects();
    func_8002A484();
    func_80023D68();
}

void func_8001D7D0(struct GameInfo* /* D_80173C70 */ arg0)
{
    u8 var_s0;
    struct MiscObj* temp_v0;

    D_80141BDE[0] = 0;
    func_80016F0C();
    func_80015930(0xFF, 0);
    D_8013E1BE = 0;
    D_80141BE6 = 0;
    D_80175EA0 = 0;
    D_8013E188[0] = 0;
    D_8013E188[1] = 0;
    D_8013E188[2] = 0;
    D_8013E188[3] = 0;
    need_palette_load |= 1;
    reset_objects();
    for (var_s0 = 0; var_s0 < 14; var_s0++) {
        temp_v0 = find_free_misc_obj();
        if (temp_v0 != NULL) {
            temp_v0->base.active = 1;
            temp_v0->base.id = 0x13;
            temp_v0->base.unk2 = D_800F21A0[var_s0];
        }
    }
    func_800129A4(8);
    arg0->mode++;
}

void func_8001D8DC(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (controller_state & PADLup) {
            func_8001540C(0, 0xC, 0);
            if (arg0->unk2 == 0) {
                arg0->unk2 = 2;
            } else {
                arg0->unk2--;
            }
        }
        if (controller_state & PADLdown) {
            func_8001540C(0, 0xC, 0);
            if (arg0->unk2 == 2) {
                arg0->unk2 = 0;
            } else {
                arg0->unk2++;
            }
        }
        if (controller_state & (PADRdown | PADstart)) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->mode++;
        }
    }
}

void func_8001D9D0(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        switch (arg0->unk2) {
        case 0:
            engine_obj.state = 0;
            engine_obj.unk1 = 0;
            engine_obj.unk2 = 0;
            engine_obj.unk3 = 0;
            func_80012740(1, &func_8001FB50);
            func_800127FC();
            return;
            break;
        case 1:
            arg0->unk0 = 7;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        default:
        case 2:
            arg0->unk0 = 8;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        }
    }
}

// never called?
void func_8001DA70(void)
{
    func_80012740(1, &func_8001FB50);
    func_800127FC();
}

// never called?
void func_8001DAA0(void)
{
    func_80012740(1, &func_8001FB50);
    func_800127FC();
}

void func_8001DAD0(struct GameInfo* arg0)
{
    func_8001A9EC(&engine_obj);
}

void func_8001DAF8(void)
{
    s32 var_v1;

    game_info.unkD = 1;
    D_80141BDE[0] = 0;
    D_80141BE0 = 1;
    func_8001D134();
    while (1) {
        D_800F21B0[game_info.unk0](&game_info);
        if (game_info.unkD == 0) {
            var_v1 = 0x800;
            if (game_info.unk0 != 1) {
                var_v1 = 0x8F0;
            }
            if (var_v1 & controller_state) {
                func_8001540C(0, 0x22, 0);
                game_info.unkD = 1;
                game_info.unkE = game_info.unk0;
                func_80012854(1);
                if (D_80141BDC[0] == 0) {
                    func_800129F0(8);
                }
                game_info.unk0 = 5;
                game_info.mode = 0;
                game_info.unk2 = 0;
                game_info.unk3 = 0;
            }
        }
        func_800127C8(1);
    }
}

void func_8001DC30(void)
{
    game_info.unk0 = 1;
    game_info.mode = 0;
    game_info.unk2 = 0;
    game_info.unk3 = 0;
    func_80012740(0, &func_8001DAF8);
}

struct QuadObj* func_8001DC7C(s8 arg0, s8 arg1)
{
    struct QuadObj* quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = arg0;
        quad->unk2 = arg1;
        return quad;
    }
    return NULL;
}

void func_8001DCCC(struct GameInfo* arg0)
{
    arg0->unkD = 2;
    arg0->unkA = 0;
    func_8001D134();
    reset_game_engine();
    engine_obj.stage = 0xE;
    engine_obj.substage = 0;
    func_80013014();
    func_800160AC();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 1;
    background_objects[2].unk3 = 0;
    need_palette_load |= 1;
    D_80139690 = func_8001DC7C(0xB, 0xA);
    func_800129A4(8);
    arg0->unk4 = 0;
    arg0->mode++;
}

void func_8001DDB0(struct GameInfo* arg0)
{
    if (arg0->unk4 == 0) {
        func_8001663C(0x20, 0x7F);
        arg0->unk4 = 1;
    }
    if (D_80173C84 == 2) {
        arg0->unkD = 1;
        arg0->unk4 = 0xA;
        arg0->mode++;
    }
}

void func_8001DE20(struct GameInfo* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
        arg0->unkA = 2;
        arg0->mode++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001DE54);

void func_8001DF48(struct GameInfo* arg0)
{
    if (D_80139690->unk1 == 0x13) {
        arg0->unk4 = 0x32;
        arg0->mode++;
    }
}

void func_8001DF7C(struct GameInfo* arg0)
{
    struct EffectObj* obj;

    if (--arg0->unk4 == 0) {
        obj = find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->unk1 = 2;
            obj->unk2 = 0xC;
            D_80139690 = obj;
        }
        arg0->unk4 = 0xA;
        arg0->mode++;
    }
}

void func_8001E000(struct GameInfo* arg0)
{
    if (arg0->unk4 != 0) {
        arg0->unk4--;
        return;
    }
    if (D_80139690->active == 0) {
        D_8013E1BE = 0;
        D_80141BE6 = 0;
        D_80175EA0 = 0;
        D_8013E188[0] = 0;
        D_8013E188[1] = 0;
        D_8013E188[2] = 0;
        D_8013E188[3] = 0;
        need_palette_load |= 1;
        func_8001DC7C(0xC, 0);
        func_8001DC7C(0xC, 1);
        func_8001DC7C(0xC, 2);
        func_8001DC7C(0xC, 3);
        func_8001DC7C(0xC, 4);
        func_8001DC7C(0xC, 5);
        func_8001DC7C(0xC, 6);
        func_8001DC7C(0xC, 7);
        func_8001DC7C(0xC, 8);
        arg0->unk6 = 0x3C;
        background_objects[0].unk3 = 0;
        arg0->unkA = 0;
        arg0->mode++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E130);

void func_8001E3FC(struct GameInfo* arg0)
{
    if (D_80139690->active == 0) {
        arg0->unk4 = 0x10;
        arg0->unk6 = 0;
        arg0->mode++;
        (*(u16**)0x1F800028)[0x306 / 2] = 0x8000;
        need_palette_load |= 1;
    }
}

void func_8001E458(struct GameInfo* arg0)
{
    s16 temp_a1;

    if (--arg0->unk4 == 0) {
        temp_a1 = arg0->unk6;
        if (temp_a1 != 0xE) {
            arg0->unk6++;
            (*(u16**)0x1F800028)[0x106 / 2] = D_800F21DC[temp_a1];
            arg0->unk4 = 6;
            need_palette_load |= 1;
            return;
        }
        arg0->unk4 = 1;
        arg0->mode++;
    }
}

void func_8001E4F0(struct GameInfo* arg0)
{
    if (--arg0->unk4 == 0) {
        reset_objects();
        arg0->unk4 = 1;
        arg0->mode++;
    }
}

void func_8001E54C(struct GameInfo* /* D_80173C70 */ arg0)
{
    u32 var_s0;
    struct BaseObj* obj;

    if (--arg0->unk4 == 0) {
        obj = (struct BaseObj*)find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 2;
            obj->unk2 = 0xD;
        }
        for (var_s0 = 0; var_s0 < 9; var_s0++) {
            obj = (struct BaseObj*)find_free_misc_obj();
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 0x13;
                obj->unk2 = D_800F21F8[var_s0];
            }
        }
        arg0->unk4 = 0x258;
        arg0->mode++;
        background_objects[2].unk3 = 1;
        arg0->unkD = 0;
    }
}

void func_8001E638(struct GameInfo* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
        func_800129F0(8);
        arg0->mode++;
    }
}

void func_8001E690(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->mode++;
    }
}

void func_8001E6BC(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 1;
        func_8001D134();
        arg0->mode = 0;
        arg0->unk0++;
    }
}

void func_8001E708(struct GameInfo* arg0)
{
    D_800F2294[arg0->mode](arg0);
    if (controller_state & PADstart && arg0->unkD == 1) {
        func_80016F0C();
        func_8001540C(0, 0x22, 0);
        arg0->mode = 0xC;
        D_8013E1BE = 0;
        D_80141BE6 = 0;
        D_80175EA0 = 0;
        D_8013E188[0] = 0;
        D_8013E188[1] = 0;
        D_8013E188[2] = 0;
        D_8013E188[3] = 0;
        background_objects[0].unk3 = 0;
        background_objects[1].unk3 = 1;
        background_objects[2].unk3 = 0;
        need_palette_load |= 1;
        reset_objects();
        background_objects[1].x_pos.i.hi = 0x400;
        background_objects[1].unk4C = 1;
        arg0->unk4 = 1;
    }
    update_effect_objects();
    update_misc_objects();
    update_quad_objects();
    func_8002A484();
    func_80023D68();
}

u8 func_8001E850(u8* arg0, u8 arg1)
{
    s8 counter = 0;
    struct MiscObj* misc;

    if (arg0[0] != 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->base.active = 1;
            misc->base.id = 0x20;
            misc->ext.ready_text.unk50 = arg0;
            misc->base.x_pos.i.hi = arg0[0];
            misc->ext.title_logo.palette_shift_value = arg1;
            arg0++;
        }
    } else {
        arg0++;
    }

    while (arg0[0] != 0xFF) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->base.active = 1;
            misc->base.id = 0x1F;
            misc->base.unk2 = arg0[0];
            arg0++;
            misc->base.unk7 = counter++;
            misc->base.y_pos.i.hi = arg0[0] & 0xF0;
            misc->ext.title_logo.palette_shift_value = arg1;
            arg0++;
        }
    }
    return arg0[1];
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E954);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E980);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001E9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EA90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EBA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EC34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EC90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001ED44);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EE08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EF48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001EFF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F0BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F150);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F198);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F2BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F398);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F3D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F488);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F5D8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F634);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F6E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F798);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F850);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F8DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F8FC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F93C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F968);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F9A0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001F9DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FA24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FAC0);

void func_8001FAFC(struct EngineObj* arg0)
{
    func_8002B460();
    D_800F23DC[arg0->unk1](arg0);
    func_8001F118();
}

void func_8001FB50(void)
{
    while (1) {
        engine_update_funcs[engine_obj.state](&engine_obj);
        func_800127C8(1);
    }
}

void engine_state_0(struct EngineObj* arg0)
{
    arg0->unk44 = 2;
    arg0->unk46 = 0x20;
    arg0->state = 1;
}

void engine_state_2(struct EngineObj* arg0)
{
    arg0->state = 3;
}

void engine_state_4(struct EngineObj* arg0)
{
    func_80013014();
    arg0->checkpoint = 0;
    arg0->unk1E = 0;
    D_80171EA8 = 0;
    arg0->state = 5;
}

void func_8001FC20(struct EngineObj* arg0)
{
    struct EngineObj* var_v0;
    u32 var_v1;

    if (func_8001FD7C(arg0) != 0 && D_80171EA8 != engine_obj.checkpoint) {
        func_80012F44();
    }

    for (var_v1 = 0; var_v1 < 8; var_v1++) {
        arg0->unk26[var_v1] = 0;
    }

    D_8013BC34[0] = 0;
    D_8013BC38 = 0;

    reset_objects();
    func_8002AB20();
    func_800160AC();
    func_8002771C();
    func_80028BF0();
    func_80027850();
    func_80027D40();
    func_800281E8();
    func_80035240();
    func_80028DB4();
    func_80028F58();

    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    arg0->unk10 = 0;
    arg0->unk11 = 0;
    arg0->unk12 = 0;
    arg0->unk13 = 0;
    arg0->unk14 = 0;
    arg0->unk15 = 0;
    arg0->unk16 = 0;
    arg0->unk17 = 0;
    arg0->unk18 = 0;
    arg0->unk19 = 0;
    arg0->unk1A = 0;
    arg0->unk1C = 1;
    arg0->unkF = 0;

    func_80023CE0();
    func_8001FDBC();
    if (arg0->unk42 != 0) {
        arg0->unk42 = 0;
    } else {
        func_8001FEC0();
    }
    func_800129A4(8);
    arg0->state++;
}

s32 func_8001FD7C(struct EngineObj* arg0)
{
    if (arg0->stage != 0xC) {
        return 0;
    } else if (arg0->substage != 0) {
        return 0;
    } else if (arg0->checkpoint >= 2) {
        return arg0->checkpoint < 0xA;
    }
    return 0;
}

void func_8001FDBC(void)
{
    struct EngineObj* ptr = &engine_obj;
    struct BaseObj* obj;

    if (engine_obj.stage == 5 && engine_obj.checkpoint == 0) {
        engine_obj.unk1E = 1;
        return;
    }
    if (ptr->stage == 0xC && ptr->substage != 0 && ptr->checkpoint == 0) {
        ptr->unk1E = -2;
        if (engine_obj.cur_character != CHARACTER_X) {
            obj = (struct BaseObj*)find_free_misc_obj();
            if (obj != NULL) {
                obj->active = 0x41;
                obj->id = 0x34;
                obj->unk2 = 1;
            }
        }
    } else if (ptr->unk1E == 0) {
        obj = (struct BaseObj*)find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x1B;
            return;
        }
        ptr->unk1E = 1;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8001FEC0);

// in a stage
void engine_state_6(struct EngineObj* arg0)
{
    D_800F241C[arg0->unk1](arg0);
}

// D_800F241C state 0
void func_8001FF8C(struct EngineObj* arg0)
{
    if (!arg0->unk1C && !D_80141BDC[0] && ((controller_state & PADstart) || D_80166D68 == 0xFF) && !arg0->unk10 && !arg0->unkF) {
        arg0->unk1 = 2;
    } else {
        if (g_Player.base.state == 3) {
            arg0->unk1++;
            func_800129F0(8);
        }
        get_random(); // ???
        func_80021158();
    }
    func_80023D68();
}

// D_800F241C state 1
void func_80020060(struct EngineObj* arg0)
{
    if (D_80141BDC[0] != 0) {
        func_80021158();
        func_80023D68();
    } else {
        func_800200D4(arg0);
        func_80015930(0xFF, 0);
        if (arg0->unk42 == 0) {
            func_80016F0C();
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800200D4);

// D_800F241C state 2
void func_80020368(struct EngineObj* arg0)
{
    func_80035EF0();
    func_8002FCAC();
}

void func_80020390(struct EngineObj* arg0)
{
    MoveImage(&D_800F2428, 0x240, 0);
    DrawSync(0);
    if ((arg0->stage == 0xB) && (arg0->cur_character != CHARACTER_X)) {
        func_80018000(8);
    }
    if ((arg0->stage == 0xC) && (arg0->cur_character != CHARACTER_X)) {
        func_80018000(9);
    }
    MoveImage(&D_800F2430, 0x140, 0xB0);
    DrawSync(0);
    arg0->unk1++;
}

void func_8002044C(struct EngineObj* arg0)
{
    arg0->substage = 1;
    arg0->state = 4;
    arg0->unk1 = 0;
}

void func_80020464(struct EngineObj* arg0)
{
    if (arg0->unk1 == 0) {
        func_80020390(arg0);
    } else {
        func_8002044C(arg0);
    }
}

void func_800204A4(void)
{
}

void func_800204AC(struct EngineObj* arg0)
{
    func_800193D8(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800204CC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020580);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020638);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800206D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020808);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002088C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020984);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020A08);

void func_80020AC8(struct EngineObj* arg0)
{
    D_800F2438[arg0->unk1](arg0);
    update_misc_objects();
    func_80016124();
    init_objects();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020C24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020CB8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020D3C);

void func_80020D98(struct EngineObj* arg0)
{
    D_800F2454[arg0->unk1](arg0);
    update_misc_objects();
    func_80016124();
    init_objects();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020DEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020ED4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80020F24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800210B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021104);

void func_80021158(void)
{
    func_80035EF0();
    func_80021C14();
    func_800311EC();
    update_weapon_objects();
    update_main_objects();
    update_shot_objects();
    update_visual_objects();
    update_effect_objects();
    update_item_objects();
    update_misc_objects();
    update_quad_objects();
    func_80028E24();
    func_80021D20();
    CollisionRelated(&g_Player);
    func_80027850();
    func_80027D40();
    func_800281E8();
    update_layer_objects();
    func_8002A484();
    func_80021D84();
    func_80021CC8();
    decompress_player_gfx(&g_Player, 0x140, 0);
}

void update_main_objects(void)
{
#define current (*(struct Unk**)0x1F80004C)
    if (!g_Player.unkBC) {
        for (current = main_objects; current < &main_objects[COUNT(main_objects)]; current++) {
            if (current->base.active) {
                if (g_Player.unkBC != 0 || (engine_obj.unk12 != 0 && !(current->base.active & 0x8))) {
                    if (current->base.on_screen != 0) {
                        func_8002B3C0(current);
                    }
                } else {
                    main_object_update_funcs[current->base.id](current);
                }
            }
        }
    }
#undef current
}

void update_weapon_objects(void)
{
#define current (*(struct WeaponObj**)0x1F800050)
    if (!g_Player.unkBC) {
        for (current = weapon_objects; current < &weapon_objects[COUNT(weapon_objects)]; current++) {
            if (current->base.active) {
                if (g_Player.unkBC != 0 || (engine_obj.unk11 != 0 && !(current->base.active & 0x8))) {
                    if (current->base.on_screen != 0) {
                        func_8002B3C0(current);
                    }
                } else {
                    weapon_object_update_funcs[current->base.id](current);
                }
            }
        }
    }
#undef current
}

void update_shot_objects(void)
{
#define current (*(struct ShotObj**)0x1F800050)
    if (!g_Player.unkBC) {
        for (current = shot_objects; current < &shot_objects[COUNT(shot_objects)]; current++) {
            if (current->base.active) {
                if (g_Player.unkBC != 0 || (engine_obj.unk13 != 0 && !(current->base.active & 0x8))) {
                    if (current->base.on_screen != 0) {
                        func_8002B3C0(current);
                    }
                } else {
                    shot_object_update_funcs[current->base.id](current);
                }
            }
        }
    }
#undef current
}

void update_visual_objects(void)
{
#define current (*(struct VisualObj**)0x1F800054)
    for (current = visual_objects; current < &visual_objects[COUNT(visual_objects)]; current++) {
        if (engine_obj.unk14 == 0 && current->base.active != 0) {
            visual_object_update_funcs[current->base.id](current);
        } else if (current->base.active != 0) {
            if (current->base.active & 8) {
                visual_object_update_funcs[current->base.id](current);
            } else if (current->base.on_screen != 0) {
                func_8002B3C0(current);
            }
        }
    }
#undef current
}

void update_effect_objects(void)
{
#define current (*(struct EffectObj**)0x1F80005C)
    for (current = effect_objects; current < &effect_objects[COUNT(effect_objects)]; current++) {
        if (engine_obj.unk15 == 0 && current->active) {
            effect_object_update_funcs[current->unk1](current);
        } else if (engine_obj.unk15 && current->active & 8) {
            effect_object_update_funcs[current->unk1](current);
        }
    }
#undef current
}

void update_item_objects(void)
{
#define current (*(struct ItemObj**)0x1F800060)
    if (!g_Player.unkBC) {
        for (current = item_objects; current < &item_objects[COUNT(item_objects)]; current++) {
            if (current->base.active) {
                if (g_Player.unkBC != 0 || (engine_obj.unk16 != 0 && !(current->base.active & 0x8))) {
                    if (current->base.on_screen != 0) {
                        func_8002B3C0(current);
                    }
                } else {
                    item_object_update_funcs[current->base.id](current);
                }
            }
        }
    }
#undef current
}

void update_misc_objects(void)
{
#define current (*(struct MiscObj**)0x1F800064)
    for (current = misc_objects; current < &misc_objects[COUNT(misc_objects)]; current++) {
        if (engine_obj.unk17 == 0 && current->base.active != 0) {
            misc_object_update_funcs[current->base.id](current);
        } else if (current->base.active != 0) {
            if (current->base.active & 8) {
                misc_object_update_funcs[current->base.id](current);
            } else if (current->base.on_screen != 0) {
                func_8002B3C0(current);
            }
        }
    }
#undef current
}

void update_unk_objects(void)
{
#define current (*(struct UnkObj**)0x1F800064)
    for (current = unk_objects; current < &unk_objects[COUNT(unk_objects)]; current++) {
        if (current->active) {
            unk_object_update_funcs[current->id](current);
        }
    }
#undef current
}

void update_quad_objects(void)
{
#define current (*(struct QuadObj**)0x1F800068)
    for (current = g_QuadObjects; current < &g_QuadObjects[COUNT(g_QuadObjects)]; current++) {
        if (engine_obj.unk18 == 0 && current->active != 0) {
            quad_object_update_funcs[current->id](current);
        } else if (current->active != 0) {
            if (current->active & 8) {
                quad_object_update_funcs[current->id](current);
            } else if (current->on_screen != 0) {
                func_8002B458(current); // no-op
            }
        }
    }
#undef current
}

void update_layer_objects(void)
{
#define current (*(struct LayerObj**)0x1F80006C)
    for (current = layer_objects; current < &layer_objects[COUNT(layer_objects)]; current++) {
        if (engine_obj.unk19 == 0 && current->base.active) {
            layer_object_update_funcs[current->base.id](current);
        } else if (engine_obj.unk19 && current->base.active & 8) {
            layer_object_update_funcs[current->base.id](current);
        }
    }
#undef current
}

void func_80021C14(void)
{
    if (engine_obj.unk10 == 0) {
        if (qux_object.base.active != 0) {
            D_800F2AD4[qux_object.base.id](&qux_object);
            return;
        }
    } else if (qux_object.base.active != 0) {
        if (qux_object.base.active & 8) {
            D_800F2AD4[qux_object.base.id](&qux_object);
            return;
        }
        if (qux_object.base.on_screen != 0) {
            func_8002B3C0(&qux_object);
        }
    }
}

void func_80021CC8(void)
{
    struct UnkObj* var_s0;

    for (var_s0 = &foo_objects; var_s0 < &foo_objects[COUNT(foo_objects)]; var_s0++) {
        func_800AE7DC(var_s0);
    }
}

void func_80021D20(void)
{
    if (D_8013BC34[0] != 0) {
        func_80022730(D_8013BC34 - 0xC);
        return;
    }
    if (D_8013BC38 != 0) {
        func_8002217C(D_8013BC38 & 0x7FFF, 0xFF, 0);
    }
}

void func_80021D84(void)
{
    func_800AE6B4(&baz_objects[0]);
    func_800AE6B4(&baz_objects[1]);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021DBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021E74);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80021F34);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80022074);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800220C4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80022138);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002217C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80022730);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002328C);

void func_80023624(struct EngineObj* arg0)
{
    reset_objects();
    func_8002AB20();
    arg0->unk1F = 0;
    arg0->enable_boss = 0;

    if (arg0->cur_character == CHARACTER_X) {
        func_80018000(5);
    } else {
        func_80018000(10);
    }

    arg0->unk1++;
}

void func_80023684(struct EngineObj* arg0)
{
    arg0->unk1++;
}

void func_80023698(struct EngineObj* arg0)
{
    struct MiscObj* obj;
    u8 var_v1;

    for (var_v1 = 0; var_v1 < 16; var_v1++) {
        arg0->unk26[var_v1] = 0;
    }
    arg0->stage = 0xF;
    arg0->substage = 1;

    func_80013014();
    func_800160AC();
    func_80028BF0();
    func_8002771C();

    if (arg0->cur_character != CHARACTER_X) {
        background_objects[1].y_pos.val = FIXED(768);
    }

    func_80023CE0();
    background_objects[0].unk3 = 1;
    background_objects[1].unk3 = 0;
    background_objects[2].unk3 = 1;
    need_palette_load |= 1;

    for (var_v1 = 0; var_v1 < 5; var_v1++) {
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0x38;
            obj->base.unk2 = get_random() & 1;
            obj->ext.title_logo.palette_shift_speed = get_random();
        }
    }

    arg0->unk2 = 0;
    arg0->unk1++;

    func_8001663C(0, 0x7F);
    func_800129A4(8);
}

void func_800237E4(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->unk2 == 0) {
            if (D_80173C84 == 2) {
                arg0->unk2++;
            }
        } else {
            background_objects[0].y_pos.val += FIXED(7.0 / 16);
            if (background_objects[0].y_pos.i.hi == 4304) {
                arg0->unk2 = 0;
                arg0->unk4 = 0x1A4;
                arg0->unk1++;
            }
        }
    }
}

void func_80023870(struct EngineObj* arg0)
{
    struct MiscObj* obj;

    if (--arg0->unk4 == 0) {
        arg0->unk1++;
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0x38;
            obj->base.unk2 = 2;
            obj->ext.title_logo.palette_shift_speed = 0;
        }
        arg0->unk4 = 0xB4;
    }
}

void func_800238F0(struct EngineObj* arg0)
{
    if (arg0->unk4 == 0) {
        background_objects[0].y_pos.val += FIXED(0.5);
        if (background_objects[0].y_pos.i.hi == 4480) {
            arg0->unk1++;
            background_objects[0].unk3 = 0;
            background_objects[1].unk3 = 1;
        }
    } else {
        arg0->unk4--;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023970);

void func_800239E0(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        game_info.unk0 = 3;
        game_info.mode = 0;
        game_info.unk2 = 0;
        game_info.unk3 = 0;
        D_8013E1C4 = 1;
        D_8013BD44 = 0;
        func_80012740(0, &func_8001DAF8);
        func_800127FC();
    }
}

void func_80023A54(struct EngineObj* arg0)
{
    D_800F2FE0[arg0->unk1](arg0);
    func_8002B460();
    update_misc_objects();
    func_80023D68();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023B98);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80023CA4);

void func_80023CE0()
{
    func_80025DA0(0, D_800F30D4[engine_obj.stage * 2][engine_obj.substage]);
    func_80026118();
}

void func_80023D30(void)
{
    D_80173C6C = 3;
    D_80173C6D = 4;
    D_80173C6E = 5;
    D_80173C6F = 6;
}

void func_80023D68(void)
{
    func_80026648();
    init_objects();
}

void func_80023D90(void)
{
    func_80017100();
    func_80017340();
}

// some kind of init?
void init_objects(void)
{
    struct UnkObj* var_s0;
    struct Unk* var_s0_2;
    struct WeaponObj* var_s0_3;
    struct ShotObj* var_s0_4;
    struct VisualObj* var_s0_5;
    struct ItemObj* var_s0_6;
    struct MiscObj* var_s0_7;
    struct UnkObj* var_s0_8;
    struct QuadObj* var_s0_9;
    s32 temp_a0;
    void* temp_v1;
    void* temp_v1_2;
    void* temp_v1_3;
    void* temp_v1_4;
    void* temp_v1_5;
    void* temp_v1_6;
    void* temp_v1_7;
    void* temp_v1_8;
    void* temp_v1_9;
    struct PlayerObj* ptr = &g_Player;
    struct BazObj* ptr2;
    struct PlayerObj* ptr3 = &g_Entity;
    struct QuxObj* ptr4;

    temp_a0 = *(s32*)0x1F800000;
    *(s32*)0x1F800124 = 0;
    *(void**)0x1F800100 = &D_801499C8[temp_a0]; // size 0xA000
    *(void**)0x1F800104 = &D_80169D98[temp_a0]; // size 0x2000
    *(void**)0x1F800108 = &D_80139830[temp_a0]; // size 0x200
    *(void**)0x1F80010C = &D_80139C30[temp_a0]; // size 0x100
    *(void**)0x1F800110 = &D_80139E30[temp_a0]; // size 0x78

    func_80024E70(); // ???
    func_800241E8(); // initialize some memory around D_8013BC40 and D_8013E1E8

    if (g_Player.base.on_screen) {
        func_80024334(ptr);
        if (g_Player.base.unk2 == 0) {
            func_800257BC(ptr);
        }
    }
    if (g_Entity.base.on_screen != 0) {
        func_80024334(ptr3);
    }
    if (ptr->base.unk2 == 0) {
        ptr2 = &baz_objects;
        if (ptr2->base.on_screen != 0) {
            func_80024334(ptr2);
        }
        ptr2 += 1;
        if (ptr2->base.on_screen != 0) {
            func_80024334(ptr2);
        }
    }

    // this one loops backwards for some reason, doesn't seem to be a compiler optimization
    for (var_s0 = &foo_objects[2]; var_s0 >= &foo_objects[0]; var_s0--) {
        if (var_s0->unk3 != 0) {
            func_80024334(var_s0);
        }
    }

    // might be a series of macros or inlines

    for (var_s0_2 = &main_objects[0]; var_s0_2 < &main_objects[COUNT(main_objects)]; var_s0_2++) {
        if (var_s0_2->base.on_screen != 0) {
            func_80024334(var_s0_2);
        }
    }

    for (var_s0_3 = &weapon_objects[0]; var_s0_3 < &weapon_objects[COUNT(weapon_objects)]; var_s0_3++) {
        if (var_s0_3->base.on_screen != 0) {
            func_80024334(var_s0_3);
        }
    }

    for (var_s0_4 = &shot_objects[0]; var_s0_4 < &shot_objects[COUNT(shot_objects)]; var_s0_4++) {
        if (var_s0_4->base.on_screen != 0) {
            func_80024334(var_s0_4);
        }
    }

    for (var_s0_5 = &visual_objects[0]; var_s0_5 < &visual_objects[COUNT(visual_objects)]; var_s0_5++) {
        if (var_s0_5->base.on_screen != 0) {
            func_80024334(var_s0_5);
        }
    }

    for (var_s0_6 = &item_objects[0]; var_s0_6 < &item_objects[COUNT(item_objects)]; var_s0_6++) {
        if (var_s0_6->base.on_screen != 0) {
            func_80024334(var_s0_6);
        }
    }

    for (var_s0_7 = &misc_objects[0]; var_s0_7 < &misc_objects[COUNT(misc_objects)]; var_s0_7++) {
        if (var_s0_7->base.on_screen != 0) {
            func_80024334(var_s0_7);
        }
    }

    for (var_s0_8 = &unk_objects[0]; var_s0_8 < &unk_objects[COUNT(unk_objects)]; var_s0_8++) {
        if (var_s0_8->unk3 != 0) {
            func_80024334(var_s0_8);
        }
    }

    ptr4 = &qux_object;
    if (ptr4->base.on_screen != 0) {
        func_80024334(&qux_object);
    }

    for (var_s0_9 = &g_QuadObjects[0]; var_s0_9 < &g_QuadObjects[COUNT(g_QuadObjects)]; var_s0_9++) {
        if (var_s0_9->on_screen != 0) {
            if (var_s0_9->active & 2) {
                func_80024B9C(var_s0_9);
            } else {
                func_80024920(var_s0_9);
            }
        }
    }

    func_80024260();
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800241E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024260);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024334);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024920);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024B9C);

void func_80024E70(void)
{
    struct PlayerObj* player = &g_Player;
    struct EngineObj* ptr = &engine_obj;

    if (engine_obj.unk1F != 0) {
        func_800253F0(player, 0);
        func_80025188(1, engine_obj.unk44 + 0x3B);
        func_80025188(0, (engine_obj.unk46 - 0x20) / 2 + 0x45);
        if (player->base.unk2 == 0) {
            func_80024F5C(player);
        } else {
            func_8002509C(player);
        }
        if (ptr->enable_boss) {
            func_800253F0(ptr->boss_ptr, 1);
            func_80025188(7, ptr->unk25 + 0x57);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80024F5C);

void func_8002509C(struct PlayerObj* arg0)
{
    s8 temp_s0;
    s8 temp_s1;

    if (arg0->unkB9 & 0x20) {
        temp_s0 = arg0->unkA8;
        func_80025588(0x24, 0x29, 0x4F - temp_s0, 0x4F, 0);
        temp_s1 = temp_s0 / 12;
        func_80025188(3, (temp_s1 / 10) + 0x3B);
        func_80025188(4, (temp_s1 % 10) + 0x3B);
        func_80025188(2, 0x4E);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80025188);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800253F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80025588);

void func_800257BC(struct PlayerObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s16 var_a2;

    if (player->unkA7 & 8) {
        func_8002588C(arg0, 3, 0x7843);
    }
    if (player->unkA7 & 1) {
        func_8002588C(arg0, 0, 0x7843);
    }
    if (player->unkA7 & 4) {
        if (player->unkB8 == 2) {
            var_a2 = 0x7844;
        } else {
            var_a2 = 0x7843;
        }
        func_8002588C(arg0, 2, var_a2);
    }
    if (player->unkA7 & 2) {
        func_8002588C(arg0, 1, 0x7843);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002588C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80025CDC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80025DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026118);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800261B4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800262B8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800264D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800265B4);

void func_80026648(void)
{
    struct BackgroundObj* bg_obj;
    u32 var_s0;
    u32 bg_num;

    var_s0 = 0;
    *(s32*)0x1F80011C = 0;
    do {
        if (background_objects[var_s0].unk4C != 0) {
            func_800262B8(var_s0 & 0xFF);
        }
        var_s0 += 1;
    } while (var_s0 < 3);
    bg_num = 0;
    func_8002728C();
    func_80026720();
    bg_obj = background_objects;
    *(void**)0x1F800108 = &D_8015D9D0[SP_DRAW_INFO_POS];
    do {
        if (bg_obj->unk3 != 0) {
            func_800267D4(bg_num);
            func_80026AA0(bg_num);
            func_80026894(bg_num);
        }
        bg_num += 1;
        bg_obj += 1;
    } while (bg_num < 3);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026720);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800267D4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026894);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026AA0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80026CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800270F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002728C);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027344);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800275DC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002771C);

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

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800279D8);

void func_80027A5C(struct BackgroundObj* a0)
{
    s16 v0, v1;

    v1 = g_Player.base.y_pos.i.hi - a0->y_pos.i.hi;
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

    v1 = g_Player.base.x_pos.i.hi - a0->x_pos.i.hi;
    v0 = v1 - a0->unk30;

    if (v0 >= 0) {
        v0 = v1 - a0->unk32;

        if (v0 <= 0) {
            return;
        }
    }

    a0->x_pos.i.hi = v0 + a0->x_pos.i.hi;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027AFC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027B70);

void func_80027BE4(struct BackgroundObj* arg0)
{
    s16 temp_v1;

    if (arg0->unk1C < arg0->x_pos.i.hi) {
        arg0->x_pos.i.hi = arg0->unk1C;
        if (engine_obj.stage != 5 || g_Player.unkC5 == 0) {
            temp_v1 = arg0->unk1C + 0x140;
            if (g_Player.base.x_pos.i.hi + 8 >= temp_v1) {
                g_Player.base.x_pos.i.hi = arg0->unk1C + 0x138;
            }
            goto label;
        }
    } else {
    label:
        if (arg0->unk1E >= arg0->x_pos.i.hi) {
            arg0->x_pos.i.hi = arg0->unk1E;
            if (engine_obj.stage != 5 || g_Player.unkC5 == 0) {
                temp_v1 = arg0->unk1E;
                if (g_Player.base.x_pos.i.hi - 8 < temp_v1) {
                    g_Player.base.x_pos.i.hi = temp_v1 + 8;
                }
            }
        }
    }

    if (arg0->unk20 < arg0->y_pos.i.hi) {
        arg0->y_pos.i.hi = arg0->unk20;
        temp_v1 = arg0->unk20 + 0x100;
        if (g_Player.base.y_pos.i.hi - 8 >= temp_v1) {
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
    arg0->unk4 = D_800F32D4[engine_obj.substage << 1][engine_obj.stage << 2];
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027E28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027E48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027E68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027E90);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027EBC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027EE8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027F08);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027F28);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027F50);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80027F7C);

#define FUNC_NAME func_80027FA8
#include "helpers/bg_is_on_screen.h"
#undef FUNC_NAME

void func_80028070(struct BackgroundObj* arg0)
{
    arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + arg0->unk40;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi + arg0->unk42;
    func_80027FA8(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800280BC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800280F4);

void func_80028138(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028140);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028178);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800281B0);

void func_800281E8(void)
{
    struct BackgroundObj* ptr = &background_objects[2];
    if (ptr->unk44 != 0 && g_Player.unkBC == 0) {
        ptr->unk14.val = ptr->x_pos.val;
        ptr->unk18.val = ptr->y_pos.val;
        D_800F3164[ptr->unk4](ptr);
    }
}

extern u8 D_800F32D5[1][1];

void func_80028268(struct BackgroundObj* arg0)
{
    arg0->unk4 = D_800F32D5[engine_obj.substage << 1][engine_obj.stage << 2];
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028298);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800282D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800282F0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028310);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028338);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028364);

void func_80028390(struct BackgroundObj* arg0)
{
    s16 v0 = background_objects[0].x_pos.i.hi;
    v0 = arg0->unk40 + (v0 >> 1);
    arg0->x_pos.i.hi = v0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800283B0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800283D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800283F8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028424);

#define FUNC_NAME func_80028450
#include "helpers/bg_is_on_screen.h"
#undef FUNC_NAME

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028518);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028564);

void func_8002859C(struct BackgroundObj* arg0)
{
    func_80028390(arg0);
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi + arg0->unk42;
    func_80028450(arg0);
}

void func_800285E0(struct BackgroundObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800285E8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028620);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028658);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028690);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028A48);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028B68);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028BAC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028BF0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028DB4);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028E24);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028F58);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_80028FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_800292D0);

INCLUDE_ASM("asm/us/main/nonmatchings/323C", func_8002938C);

extern void (*g_MakeObjectFuncs[1])(s32 arg0);

void MakeObject(u8 arg0)
{
    g_MakeObjectFuncs[arg0](arg0 << 2);
}
