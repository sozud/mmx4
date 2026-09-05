#include "common.h"

// entrypoint
void func_80012024(void)
{
    func_800DAE84();
    func_8001213C();
    while (1) {
        VSync(0);
        PutDispEnv(&cur_draw_info->dispenv);
        PutDrawEnv(&cur_draw_info->drawenv);
        DrawOTag(&cur_draw_info->ordering_table.end);
        SP_DRAW_BUFFER ^= 1;
        cur_draw_info = &draw_infos[SP_DRAW_BUFFER];
        ClearOTagR(&cur_draw_info->ordering_table.start, 0xC);
        func_800168D8();
        func_800169D8();
        func_80012328();
        clear_vram_rect_ptrs();
        D_80141BD8.unk0++;
        func_80012600();
        func_80014780();
        DrawSync(0);
        load_vram_rect_ptrs();
        load_palette();
        DrawSync(0);
        func_80012454();
    }
}

void func_8001213C(void)
{
    ResetCallback();
    StopCallback();
    ResetGraph(0);
    func_800E9040();
    SetGeomOffset(0xA0, 0x78);
    SetGeomScreen(0x200);
    InitPAD(&D_80166D68, 0x22, &D_8012F46C, 0x22);
    StartPAD();
    InitCARD(1);
    StartCARD();
    _bu_init();
    InitMemcards();
    func_80014DC4();
    func_80013588();
    ChangeClearPAD(0);
    ClearImage(&D_800EE450, 0U, 0U, 0U);
    DrawSync(0);
    SetDefDrawEnv(&draw_infos[0].drawenv, 0, 0, 0x140, 0xF0);
    SetDefDispEnv(&draw_infos[0].dispenv, 0, 0xF0, 0x140, 0xF0);
    SetDefDrawEnv(&draw_infos[1].drawenv, 0, 0xF0, 0x140, 0xF0);
    SetDefDispEnv(&draw_infos[1].dispenv, 0, 0, 0x140, 0xF0);
    func_800122E0(&draw_infos[0]);
    func_800122E0(&draw_infos[1]);
    func_80012560();
    cur_random = 0xD37; // seed RNG
    SP_DRAW_BUFFER = 0;
    cur_draw_info = &draw_infos[0];
    D_8013BD44 = 0;
    D_80141BD2 = 0x78;
    func_80012740(0, &func_8001D064);
}

void func_800122E0(struct DrawInfo* arg0)
{
    ClearOTagR(&arg0->ordering_table.start, 0xC);
    arg0->drawenv.dtd = 0;
    arg0->drawenv.isbg = 1;
    arg0->drawenv.r0 = 0;
    arg0->drawenv.g0 = 0;
    arg0->drawenv.b0 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/2824", func_80012328);

void func_80012454(void)
{
    u16 temp_v0;

    if ((D_8013BD44 != 0) && (D_80141BDC[0] == 0)) {
        if ((D_80166C08 & 0x900) == 0x900) {
            temp_v0 = D_80141BD2 - 1;
            D_80141BD2 = temp_v0;
            if ((temp_v0 << 0x10) == 0) {
                if ((engine_obj.stage != 0) && (engine_obj.unk5F >= 3U)) {
                    func_8001C3E8();
                }
                SetDispMask(0);
                func_80012854(0);
                func_80012854(1);
                func_80012854(2);
                func_80012854(3);
                D_80141BD2 = 0x78;
                func_8001D134();
                func_80015284();
                reset_game_engine();
                func_8001DC30();
            }
        } else {
            D_80141BD2 = 0x78;
        }
    }
}

extern void (*D_800EE45C[9])();

void func_80012560(void)
{
#ifdef MMX4_PC
    mmx4_pc_threads_init();
#else
    s32* ptr = (s32*)0x100;
    s16* var_a0;
    s32 temp_v0;
    s32 var_t0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32* dst;
    s32* src;
    volatile s32* var_v1;

    var_a1 = 0;
    var_t0 = 0x40000404;
    var_v1 = (volatile s32*)0x801F8170;
    var_a3 = 0x801FEC00;
    var_a2 = 0xC0;
    var_a0 = (s16*)0x801F8100;
    do {
        *var_a0 = 0;
        temp_v0 = ptr[0x10 / 4];
        var_v1[-0x60 / 4] = var_a3;
        var_a3 += 0x400;
        var_a0 += 0x40;
        var_a1 += 1;
        var_v1[-0x64 / 4] = temp_v0 + var_a2;
        var_a2 += 0xC0;
        ((s32*)var_v1[-0x64 / 4])[0x94 / 4] = var_t0;
        *(volatile u8*)var_v1 = 0;
        var_v1 += 0x20;
    } while (var_a1 < 4);

    dst = (s32*)0x801F8000;
    var_a1 = 0;
    src = &D_800EE45C;
    for (; var_a1 < 9; var_a1++) {
        *dst++ = *src++;
    }
#endif
}

void func_80012600(void)
{
#ifdef MMX4_PC
    s32 slot;

    for (slot = 0; slot < 4; slot++) {
        struct GameThread* thread = mmx4_pc_thread_slot(slot);
        D_801F8300 = thread;
        if (thread->state == 1 && --thread->timer == 0)
            thread->state = 2;
        if (thread->state == 2 || thread->state == 4 || thread->state == 0x7f)
            mmx4_pc_thread_run(slot);
    }
#else
    u16 temp_v0_2;
    u16 temp_v1;
    void* temp_v0;
    struct GameThread* temp_v0_3;
    struct GameThread* temp_v0_4;

    D_801F8300 = (void*)0x801F8100;
    do {
        temp_v1 = ((struct GameThread*)D_801F8300)->state;
        switch (temp_v1) {
        case 0x1:
            temp_v0_2 = ((struct GameThread*)D_801F8300)->timer - 1;
            ((struct GameThread*)D_801F8300)->timer = temp_v0_2;
            if ((temp_v0_2 << 0x10) == 0) {
            case 0x2:
            case 0x4:
            case 0x7F:
                temp_v0_3 = *(struct GameThread**)0x801F8300;
                temp_v0_3->state = 0x7F;
                ChangeTh(temp_v0_3->handle);
                if (D_800EE458 != 0) {
                    D_800EE458 = 0;
                    EnterCriticalSection();
                    CloseTh((*(struct GameThread**)0x801F8300)->handle);
                    temp_v0_4 = *(struct GameThread**)0x801F8300;
                    (*(struct GameThread**)0x801F8300)->handle = OpenTh(
                        (long (*)())D_8012F490, temp_v0_4->stack,
                        temp_v0_4->global_pointer);
                    ExitCriticalSection();
                }
            }
            break;
        }
        temp_v0 = *(void**)0x801F8300 + 0x80;
        *(void**)0x801F8300 = temp_v0;
    } while ((u32)temp_v0 <= 0x801F82FFU);
#endif
}

void func_80012740(s32 arg0, void* arg1)
{
#ifdef MMX4_PC
    mmx4_pc_thread_create(arg0, (void (*)(void))arg1);
#else
    s32 temp_s0;
    u16* ptr;

    EnterCriticalSection();
    temp_s0 = arg0 << 7;
    ptr = (u16*)(0x801f8100 + temp_s0);
    *(s32*)(0x801f8108 + temp_s0) = OpenTh((long (*)())arg1, *(s32*)(0x801f8110 + temp_s0),
        *(s32*)(0x801f8144 + temp_s0));
    ExitCriticalSection();
    *ptr = 2;
#endif
}

void func_800127C8(s32 arg0)
{
    D_801F8300->timer = arg0;
    D_801F8300->state = 1;
#ifdef MMX4_PC
    mmx4_pc_thread_yield();
#else
    ChangeTh(0xFF000000);
#endif
}

void func_800127FC()
{
#ifdef MMX4_PC
    D_801F8300->state = 0;
    mmx4_pc_thread_close();
#else
    (*(s16**)0x801F8300)[0] = 0;
    EnterCriticalSection();
    CloseTh((*(s32**)0x801F8300)[2]);
    ExitCriticalSection();
    ChangeTh(0xFF000000);
#endif
}

void func_80012854(s32 arg0)
{
#ifdef MMX4_PC
    mmx4_pc_thread_slot(arg0)->state = 0;
#else
    s32 temp_s0;
    u16* temp_v1;

    temp_s0 = arg0 << 7;
    temp_v1 = temp_s0 + 0x801F8100;
    if (*temp_v1 != 0) {
        *temp_v1 = 0;
        EnterCriticalSection();
        CloseTh(*(u32*)(temp_s0 + 0x801F8108));
        ExitCriticalSection();
    }
#endif
}

void func_800128B8(void (*arg0)(void))
{
#ifdef MMX4_PC
    mmx4_pc_thread_replace(arg0);
#else
    D_8012F490 = arg0;
    D_800EE458 = 1;
    ChangeTh(0xFF000000);
#endif
}

void func_800128EC(s32 arg0)
{
#ifdef MMX4_PC
    u16* temp_a0 = &mmx4_pc_thread_slot(arg0)->state;
#else
    u16* temp_a0 = (arg0 << 7) + 0x801F8100;
#endif
    *temp_a0 |= 0x40;
}

void func_80012910(s32 arg0)
{
#ifdef MMX4_PC
    u16* temp_a0 = &mmx4_pc_thread_slot(arg0)->state;
#else
    u16* temp_a0 = (arg0 << 7) + 0x801F8100;
#endif
    *temp_a0 &= ~0x40;
}

void func_80012934(s32 arg0)
{
}

void func_8001293C(void)
{
}

void func_80012944(void)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        (i + *(s16**)0x801F8300)[48] = 0;
    }

    for (i = 0; i < 16; i++) {
        (i + *(u8**)0x801F8300)[0x71] = 0;
    }
}

void func_800129A4(s8 arg0)
{
    if (D_80141BDC[0] == 0) {
        D_80141BDC[0] = 1;
        D_80141BDC[1] = arg0;
        func_80012740(2, func_80012A3C);
    }
}

void func_800129F0(s32 arg0)
{
    if (D_80141BDC[0] == 0) {
        D_80141BDC[0] = -1;
        D_80141BDC[1] = arg0;
        func_80012740(2, func_80012A3C);
    }
}
