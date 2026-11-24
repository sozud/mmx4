#include "common.h"
#include "main/2824.h"
#include "main/3D88.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/memcard.h"
#include "main/102FC.h"
#include "main/323C.h"
#include "main/game_info.h"
#include "main/menu.h"
#include "main/objects.h"
#ifdef MMX4_SATURN
#include "saturn/menu.h"
#endif

extern u32 D_800EE458;

#ifndef MMX4_SATURN
extern RECT D_800EE450;
#endif

void func_8001293C(void);

void func_8001213C(void);
void func_800122E0(struct DrawInfo* arg0);

#ifdef MMX4_PC
extern void func_80012944(void);
#endif

void func_800128EC(s32);
void func_80012910(s32);
void func_80012934(s32);

void InitMemcards(void);
void clear_vram_rect_ptrs(void);
void func_80012454(void);
void func_80012560(void);
void func_80012600(void);
void func_80013588(void);
void func_80014780(void);
void func_80014DC4(void);
void func_800168D8(void);
s32 func_800169D8(void);
void load_palette(void);
void load_vram_rect_ptrs(void);
#ifndef MMX4_PC
void __main(void);
#endif

#ifdef MMX4_PC
#include "../pc/oracle.h"

void mmx4_pc_finish_cd_load(void);
#endif

void func_80012328(void);

#ifdef VERSION_DEMO
extern u8 D_8013A858_demo;
extern u16 D_801F8100;
extern u16 D_801F8180;
extern u16 D_801F8200;
extern u16 D_801F8280;
void func_8002A160_demo(u8 arg0);
#endif

// entrypoint
#ifndef MMX4_SATURN
void func_80012024(void)
{
#ifndef MMX4_PC
    __main();
#endif
    func_8001213C();
    while (1) {
#ifdef MMX4_PC
        VSync(D_8013BD44 == 0 ? 1 : 0);
        mmx4_pc_finish_cd_load();
#else
        VSync(0);
#endif
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
        main_bss_state.frame_counter++;
#ifdef VERSION_DEMO
        if (D_8013A858_demo != 0 && D_801F8100 == 0 && D_801F8180 == 0 && D_801F8200 == 0 && D_801F8280 == 0) {
            func_8002A160_demo(D_8013A858_demo - 1);
        }
#endif
        func_80012600();
        func_80014780();
        DrawSync(0);
        load_vram_rect_ptrs();
        load_palette();
        DrawSync(0);
        func_80012454();
#ifdef MMX4_PC
        mmx4_pc_complete_scheduled_cd_load(0);
        mmx4_pc_frame_end();
#endif
    }
}
#endif

#ifndef MMX4_SATURN
#ifdef VERSION_DEMO
void func_800BD6C0_demo(s32 arg0);
extern s16 D_800FBCBC_demo;
#endif

void func_8001213C(void)
{
#ifdef VERSION_EU
    SetVideoMode(1);
#endif
    ResetCallback();
    StopCallback();
    ResetGraph(0);
    InitGeom();
    SetGeomOffset(0xA0, 0x78);
    SetGeomScreen(0x200);
#ifdef VERSION_DEMO
    func_800BD6C0_demo(0);
#else
    InitPAD(pad_port1_packet, 0x22, &D_8012F46C, 0x22);
    StartPAD();
    InitCARD(1);
    StartCARD();
    _bu_init();
    InitMemcards();
#endif
    func_80014DC4();
    func_80013588();
#ifndef VERSION_DEMO
    ChangeClearPAD(0);
#endif
    ClearImage(&D_800EE450, 0U, 0U, 0U);
#ifndef VERSION_DEMO
    DrawSync(0);
#endif
    SetDefDrawEnv(&draw_infos[0].drawenv, 0, 0, 0x140, 0xF0);
    SetDefDispEnv(&draw_infos[0].dispenv, 0, 0xF0, 0x140, 0xF0);
    SetDefDrawEnv(&draw_infos[1].drawenv, 0, 0xF0, 0x140, 0xF0);
    SetDefDispEnv(&draw_infos[1].dispenv, 0, 0, 0x140, 0xF0);
    func_800122E0(&draw_infos[0]);
    func_800122E0(&draw_infos[1]);
    func_80012560();
#ifdef VERSION_DEMO
    cur_random = 0xD37;
    D_800FBCBC_demo = 0x78;
    SP_DRAW_BUFFER = 0;
    cur_draw_info = &draw_infos[0];
    D_8013BD44 = 0;
    D_80141BD2 = 0x2A30;
    D_8013A858_demo = 0;
#else
    SP_DRAW_BUFFER = 0;
    cur_draw_info = &draw_infos[0];
    cur_random = 0xD37;
    D_8013BD44 = 0;
    D_80141BD2 = 0x78;
#endif
    func_80012740(0, &func_8001D064);
}
#endif

#ifndef MMX4_SATURN
void func_800122E0(struct DrawInfo* arg0)
{
    ClearOTagR(&arg0->ordering_table.start, 0xC);
    arg0->drawenv.dtd = 0;
    arg0->drawenv.isbg = 1;
#ifdef VERSION_EU
    arg0->dispenv.screen.y = 0x1C;
#endif
    arg0->drawenv.r0 = 0;
    arg0->drawenv.g0 = 0;
    arg0->drawenv.b0 = 0;
#ifdef VERSION_EU
    arg0->dispenv.screen.x = 0;
    arg0->dispenv.screen.h = 0xF0;
    arg0->dispenv.screen.w = 0;
#endif
}
#endif

#if !defined(MMX4_SATURN) && !defined(MMX4_PC)
extern u8 pad_port1_packet[0x22];
extern struct ControllerButtons D_80166D50;

#ifdef VERSION_DEMO
u32 func_800BD710_demo(s32 arg0);

void func_80012328(void)
{
    u32 pads;
    u16 buttons;

    pads = func_800BD710_demo(0);
    buttons = pads;
    controller_input.previous = controller_input.held;
    controller_input.held = buttons;
    controller_input.pressed = buttons & (buttons ^ controller_input.previous);
    buttons = pads >> 16;
    D_80166D50.previous = D_80166D50.current;
    D_80166D50.current = buttons;
    D_80166D50.pressed = buttons & (buttons ^ D_80166D50.previous);
}
#else
void func_80012328(void)
{
    s32 raw;
    s32 raw2;
    u16 buttons;

    if (pad_port1_packet[0] == 0xFF) {
        buttons = 0;
#ifdef VERSION_EU
        D_80166D68 = 1;
#endif
    } else {
#ifdef VERSION_EU
        D_80166D68 = 0;
#endif
        if (pad_port1_packet[1] != 0x41) {
            buttons = 0;
        } else {
            raw = ~pad_port1_packet[3] & ~(pad_port1_packet[2] << 8);
            buttons = raw;
            if ((raw & 0xA000) == 0xA000) {
                buttons = raw & 0x5FFF;
            }
            if ((buttons & 0x5000) == 0x5000) {
                buttons &= 0xAFFF;
            }
        }
    }
    controller_input.previous = controller_input.held;
    controller_input.held = buttons;
    controller_input.pressed = buttons & (buttons ^ controller_input.previous);
    if (D_8012F46C[0] == 0xFF || D_8012F46C[1] != 0x41) {
        buttons = 0;
    } else {
        raw2 = ~D_8012F46C[3] & ~(D_8012F46C[2] << 8);
        buttons = raw2;
        if ((raw2 & 0xA000) == 0xA000) {
            buttons = raw2 & 0x5FFF;
        }
        if ((buttons & 0x5000) == 0x5000) {
            buttons &= 0xAFFF;
        }
    }
    D_80166D50.previous = D_80166D50.current;
    D_80166D50.current = buttons;
    D_80166D50.pressed = buttons & (buttons ^ D_80166D50.previous);
}
#endif
#endif

#ifndef MMX4_SATURN
#ifdef VERSION_DEMO
void func_80012454(void)
{
    if ((D_8013BD44 != 0) && (main_bss_state.transition.active == 0)) {
        if ((controller_input.held & (PADstart | PADselect)) == (PADstart | PADselect)) {
            if (--D_800FBCBC_demo == 0) {
                D_8013A858_demo = 1;
            }
        } else {
            D_800FBCBC_demo = 0x78;
        }
        if (controller_input.held == 0) {
            if (controller_input.previous == 0 && --D_80141BD2 == 0) {
                D_8013A858_demo = 1;
            }
        } else {
            D_80141BD2 = 0x2A30;
        }
    }
}
#else
void func_80012454(void)
{
    if ((D_8013BD44 != 0) && (main_bss_state.transition.active == 0)) {
        if ((controller_input.held & (PADstart | PADselect)) == (PADstart | PADselect)) {
            if (--D_80141BD2 == 0) {
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
#endif
#endif

#ifdef VERSION_DEMO
extern char* D_800C4EC8_demo[2];
void func_800BD738_demo(void); // PadStop
void func_800C47CC_demo(void); // _96_remove
void func_800C47BC_demo(char* file, u32 stack, u32 stack_size); // LoadExec

void func_8002A160_demo(u8 exec)
{
    func_8001D134();
    func_80015178();
    DrawSync(0);
    StopRCnt(RCntCNT0);
    StopRCnt(RCntCNT1);
    StopRCnt(RCntCNT2);
    StopRCnt(RCntCNT3);
    ResetGraph(3);
    func_800BD738_demo();
    StopCallback();
    func_800C47CC_demo();
    func_800C47BC_demo(D_800C4EC8_demo[exec], 0x801FFF00, 0);
}
#endif

extern void (*D_800EE45C[9])();

#ifndef MMX4_SATURN
void func_80012560(void)
{
#ifdef MMX4_PC
    mmx4_pc_threads_init();
#elif defined(MMX4_GAMECUBE)
    s32 i;

    memset(GAME_THREADS, 0, 4 * sizeof(struct GameThread));
    for (i = 0; i < 4; i++) {
        GAME_THREADS[i].state = 0;
        GAME_THREADS[i].pad48[0x70 - 0x48] = 0;
    }
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

#ifdef VERSION_EU
    var_a1 = 0;
    var_t0 = 0x40000404;
    var_a3 = 0x801FEC00;
    var_a2 = 0xC0;
    do {
        GAME_THREADS[var_a1].state = 0;
        temp_v0 = ptr[0x10 / 4];
        GAME_THREADS[var_a1].stack = var_a3;
        var_a3 += 0x400;
        GAME_THREADS[var_a1].unkC = temp_v0 + var_a2;
        var_a2 += 0xC0;
        ((s32*)GAME_THREADS[var_a1].unkC)[0x94 / 4] = var_t0;
        GAME_THREADS[var_a1].pad48[0x70 - 0x48] = 0;
        var_a1++;
    } while (var_a1 < 4);
#else
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
#endif

    dst = (s32*)0x801F8000;
    var_a1 = 0;
    src = &D_800EE45C;
    for (; var_a1 < 9; var_a1++) {
        *dst++ = *src++;
    }
#endif
}
#endif

#ifndef MMX4_SATURN
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
    CUR_GAME_THREAD = GAME_THREADS;
    do {
        switch (CUR_GAME_THREAD->state) {
        case 1:
            if (--CUR_GAME_THREAD->timer == 0) {
            case 2:
            case 4:
            case 0x7F:
                CUR_GAME_THREAD->state = 0x7F;
                ChangeTh(CUR_GAME_THREAD->handle);
                if (D_800EE458 != 0) {
                    D_800EE458 = 0;
                    EnterCriticalSection();
                    CloseTh(CUR_GAME_THREAD->handle);
                    CUR_GAME_THREAD->handle = OpenTh((long (*)())D_8012F490,
                        CUR_GAME_THREAD->stack, CUR_GAME_THREAD->global_pointer);
                    ExitCriticalSection();
                }
            }
            break;
        }
        CUR_GAME_THREAD++;
    } while (CUR_GAME_THREAD < &GAME_THREADS[4]);
#endif
}
#endif

#ifndef MMX4_SATURN
void func_80012740(s32 arg0, void* arg1)
{
#ifdef MMX4_PC
    mmx4_pc_thread_create(arg0, (void (*)(void))arg1);
#else
    struct GameThread* thread;

    EnterCriticalSection();
    thread = &GAME_THREADS[arg0];
    thread->handle = OpenTh((long (*)())arg1, thread->stack, thread->global_pointer);
    ExitCriticalSection();
    thread->state = 2;
#endif
}
#endif

#ifdef MMX4_GAMECUBE
void func_800127C8(s32 arg0)
{
}
#elif !defined(MMX4_SATURN)
void func_800127C8(s32 arg0)
{
#ifdef MMX4_PC
    struct GameThread* thread = D_801F8300;
#else
    struct GameThread* thread = CUR_GAME_THREAD;
#endif

    thread->timer = arg0;
    thread->state = 1;
#ifdef MMX4_PC
    mmx4_pc_thread_yield();
#else
    ChangeTh(0xFF000000);
#endif
}
#endif

#ifndef MMX4_SATURN
void func_800127FC()
{
#ifdef MMX4_PC
    D_801F8300->state = 0;
    mmx4_pc_thread_close();
#else
    CUR_GAME_THREAD->state = 0;
    EnterCriticalSection();
    CloseTh(CUR_GAME_THREAD->handle);
    ExitCriticalSection();
#ifndef MMX4_BIG_ENDIAN
    ChangeTh(0xFF000000);
#endif
#endif
}
#endif

#ifndef MMX4_SATURN
void func_80012854(s32 arg0)
{
#ifdef MMX4_PC
    mmx4_pc_thread_slot(arg0)->state = 0;
#else
    if (GAME_THREADS[arg0].state != 0) {
        GAME_THREADS[arg0].state = 0;
        EnterCriticalSection();
        CloseTh(GAME_THREADS[arg0].handle);
        ExitCriticalSection();
    }
#endif
}
#endif

#ifndef MMX4_SATURN
void func_800128B8(void (*arg0)(void))
{
#ifdef MMX4_PC
    mmx4_pc_thread_replace(arg0);
#else
    D_800EE458 = 1;
    D_8012F490 = arg0;
#ifndef MMX4_BIG_ENDIAN
    ChangeTh(0xFF000000);
#endif
#endif
}
#endif

#ifndef MMX4_SATURN
void func_800128EC(s32 arg0)
{
#ifdef MMX4_PC
    u16* temp_a0 = &mmx4_pc_thread_slot(arg0)->state;
#elif defined(MMX4_WIN32)
    u8* temp_a0 = win32_main_ram + 0x1F8100 + (arg0 << 7);
#else
    u16* temp_a0 = &GAME_THREADS[arg0].state;
#endif
    *temp_a0 |= 0x40;
}
#endif

#ifndef MMX4_SATURN
void func_80012910(s32 arg0)
{
#ifdef MMX4_PC
    u16* temp_a0 = &mmx4_pc_thread_slot(arg0)->state;
#else
    u16* temp_a0 = &GAME_THREADS[arg0].state;
#endif
    *temp_a0 &= ~0x40;
}
#endif

#ifndef MMX4_SATURN
void func_80012934(s32 arg0)
{
}
#endif

#ifndef MMX4_SATURN
void func_8001293C(void)
{
}
#endif

#ifndef MMX4_SATURN
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
#endif

#ifndef MMX4_SATURN
void func_800129A4(s8 arg0)
{
    if (main_bss_state.transition.active == 0) {
        main_bss_state.transition.active = 1;
        main_bss_state.transition.fade_amount = arg0;
        func_80012740(2, func_80012A3C);
    }
}
#endif

#ifndef MMX4_SATURN
void func_800129F0(s32 amount)
{
    if (main_bss_state.transition.active == 0) {
        main_bss_state.transition.active = -1;
        main_bss_state.transition.fade_amount = amount;
        func_80012740(2, func_80012A3C);
    }
}
#endif

#ifdef VERSION_DEMO
char D_800EE40C[36] = "CAPCOM May  8 1997 14:16:53 CAPCOM";
#elif defined(VERSION_JP)
char D_800EE40C[36] = "CAPCOM Jun 20 1997 12:14:39 CAPCOM";
#elif defined(VERSION_EU)
char D_800EE40C[36] = "CAPCOM Aug  3 1998 09:30:21 CAPCOM";
#elif defined(MMX4_WIN32)
char D_800EE40C[36] = "CAPCOM May 12 1998 19:28:57 CAPCOM";
#else
char D_800EE40C[36] = "CAPCOM Aug 19 1997 19:54:17 CAPCOM";
#endif

#ifdef MMX4_SATURN
u16 D_800EE430[16] = {
    SATURN_PAD_RIGHT,
    SATURN_PAD_LEFT,
    SATURN_PAD_UP,
    SATURN_PAD_DOWN,
    SATURN_PAD_A,
    SATURN_PAD_X,
    SATURN_PAD_Y,
    SATURN_PAD_B,
    SATURN_PAD_C,
    SATURN_PAD_R,
    SATURN_PAD_L,
};
#else
u16 D_800EE430[16] = {
    0x2000,
    0x8000,
    0x1000,
    0x4000,
    0x0080,
    0x0010,
#ifndef VERSION_DEMO
    0x0002,
#endif
    0x0040,
    0x0020,
    0x0008,
    0x0004,
    0,
    0,
    0,
    0,
    0,
};
#endif

#ifndef MMX4_SATURN
RECT D_800EE450 = { 0, 0, 1024, 512 };
#endif
#ifdef MMX4_WIN32
u8 pc_2824_data[24] = { 0x48, 0x00, 0x69, 0x00, 0x00, 0xB0, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x02, 0x48, 0x00, 0x69, 0x00, 0x00, 0xB0, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x02 };
#endif

#ifdef VERSION_DEMO
char* D_800C4EC8_demo[] = { "cdrom:\\MENU.EXE;1", "cdrom:\\D8.EXE;1" };

const u16 rodata_2824_pad = 0;
#endif

u32 D_800EE458 = 0;

#ifndef MMX4_SATURN
void (*D_800EE45C[9])() = {
    func_80012740,
    func_800127C8,
    func_800127FC,
    func_80012854,
    func_800128B8,
    func_800128EC,
    func_80012910,
    func_80012934,
    func_8001293C,
};
#endif
