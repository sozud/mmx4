// 800204A4..80020984
#include "common.h"

void func_80016F0C();

void func_8001F118(void);

struct MiscObj* func_8001F150(struct EngineObj* arg0, u8 arg1);

void func_8001F398(struct EngineObj* arg0);

void func_8001F3D4(struct MainObj* obj);

void func_8001F5D8(struct EngineObj* arg0);

void func_8001F798(struct EngineObj* arg0);

void func_8001F850(struct EngineObj* arg0);

void func_8001F8DC(void);

s32 func_8001F8FC(struct GameInfo* arg0);

void func_8001F93C(struct EngineObj* arg0);

void func_8001F968(struct EngineObj* arg0);

void func_8001F9A0(struct EngineObj* arg0);

void func_8001F9DC(struct EngineObj* arg0);

void func_8001FAC0(struct EngineObj* arg0);

void func_8001FAFC(struct EngineObj* arg0);

void func_8001FB50(void);

void engine_state_0(struct EngineObj* arg0);

void engine_state_2(struct EngineObj* arg0);

void engine_state_4(struct EngineObj* arg0);

void func_8001FC20(struct EngineObj* arg0);

s32 func_8001FD7C(struct EngineObj* arg0);

void func_8001FDBC(void);

extern void func_800164D8(void);

void func_8001FEC0(void);

// in a stage
void engine_state_6(struct EngineObj* arg0);

// D_800F241C state 0
void func_8001FF8C(struct EngineObj* arg0);

// D_800F241C state 1
void func_80020060(struct EngineObj* arg0);

// D_800F241C state 2
void func_80020368(struct EngineObj* arg0);

void func_80020390(struct EngineObj* arg0);

void func_8002044C(struct EngineObj* arg0);

void func_80020464(struct EngineObj* arg0);

void func_800204A4(void)
{
}

void func_800204AC(struct EngineObj* arg0)
{
    func_800193D8(arg0);
}

void func_800204CC(s8* arg0, s32 arg1)
{
    if (controller_input.pressed & 0x1000) {
        func_8001540C(0, 0xC, 0);
        if (*arg0 == 0) {
            *arg0 = arg1;
        } else {
            *arg0 = *arg0 - 1;
        }
    }
    if (controller_input.pressed & 0x4000) {
        func_8001540C(0, 0xC, 0);
        if (*arg0 == arg1) {
            *arg0 = 0;
            return;
        }
        *arg0 = *arg0 + 1;
    }
}

void func_80020580(struct EngineObj* arg0)
{
    s8 next_state;

    func_8001D134();
    main_bss_state.transition.selection = 0;
    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    func_8001E980(0);
    if (arg0->stage != 0) {
        func_8001C3E8();
    }
    arg0->unk4 = 0x78;
    func_800129A4(8);
    if (arg0->stage == 0) {
        arg0->unk8 = func_8001E850(D_800F231C, 1);
        next_state = arg0->unk1 + 5;
    } else {
        arg0->unk8 = func_8001E850(D_800F2328, 1);
        next_state = arg0->unk1 + 1;
    }
    arg0->unk1 = next_state;
}

void func_80020638(struct EngineObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        func_800204CC((s8*)&main_bss_state.transition.selection, arg0->unk8);
        if (controller_input.pressed & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            if ((s8)main_bss_state.transition.selection != 2U) {
                func_800129F0(8);
            }
            arg0->unk1++;
        }
    }
}

void func_800206D0(struct EngineObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        switch (main_bss_state.transition.selection) {
        case 0:
            if (D_80171EA8 != 0) {
                func_800127C8(1);
                func_80013014();
                D_80171EA8 = 0;
            }
            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->checkpoint = 0;
            arg0->unk1E = 0;
            arg0->state = 5;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        case 1:
            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->state = 3;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        case 2:
            arg0->unk4 = arg0->state;
            arg0->state = 0xC;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        default:
            func_8001DC30();
            func_800127FC();
            break;
        }
    }
}

void func_80020808(struct EngineObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        func_800204CC((s8*)&main_bss_state.transition.selection, arg0->unk8);
        if (controller_input.pressed & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->unk1++;
        }
    }
}

void func_8002088C(struct EngineObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        switch (main_bss_state.transition.selection) {
        case 0:
            if (D_80171EA8 != 0) {
                func_800127C8(1);
                func_80013014();
                D_80171EA8 = 0;
            }

            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->checkpoint = 0;
            arg0->unk1E = 0;
            arg0->state = 5;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        case 1:
            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->state = 3;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        case 2:
        default:
            func_8001DC30();
            func_800127FC();
            break;
        }
    }
}
