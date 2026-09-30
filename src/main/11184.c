// 80020984..80021158
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

void func_800204A4(void);

void func_800204AC(struct EngineObj* arg0);

void func_800204CC(s8* arg0, s32 arg1);

void func_80020580(struct EngineObj* arg0);

void func_80020638(struct EngineObj* arg0);

void func_800206D0(struct EngineObj* arg0);

void func_80020808(struct EngineObj* arg0);

void func_8002088C(struct EngineObj* arg0);

extern void (*D_800F2438[7])(struct EngineObj*);

extern void (*D_800F2454[5])(struct EngineObj*);

u8 D_800F2468[20] = {
    0x59,
    0x10,
    0x80,
    0x2D,
    0x40,
    0x80,
    0x5B,
    0x70,
    0x00,
    0x5C,
    0x90,
    0x01,
    0x72,
    0xD0,
    0x80,
    0xFF,
    0x00,
    0x80,
    0x00,
    0x00,
};

u8 D_800F247C[20] = {
    0x59,
    0x10,
    0x80,
    0x5A,
    0x40,
    0x80,
    0x51,
    0x70,
    0x00,
    0x52,
    0x90,
    0x01,
    0x72,
    0xD0,
    0x80,
    0xFF,
    0x00,
    0x80,
    0x00,
    0x00,
};

u8 D_800F2490[8] = { 0x70, 0x00, 0x90, 0x01, 0xFF, 0, 0, 0 };

void (*D_800F2498[])(struct EngineObj*) = {
    func_80020ED4,
    func_80020F24,
    func_800210B8,
};

void func_80020984(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_800204CC(D_80141BDC + 3, arg0->unk8);
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->unk1++;
        }
    }
}

void func_80020A08(struct EngineObj* arg0)
{
    s8 var_v0;

    if (D_80141BDC[0] == 0) {
        if (D_80141BDF[0] == 0) {
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
        } else {
            func_8001DC30();
            func_800127FC();
        }
    }
}

void func_80020AC8(struct EngineObj* arg0)
{
    D_800F2438[arg0->unk1](arg0);
    update_misc_objects();
    func_80016124();
    init_objects();
}

void func_80020B1C(struct EngineObj* arg0)
{
    func_8001D134();
    D_80141BDF[0] = 0;
    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    func_8001E980(0);
    func_8001C3E8();
    func_800129A4(8);
    arg0->unk8 = func_8001E850(&D_800F2300, 1);
    arg0->unk1++;
}

void func_80020B8C(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_800204CC(D_80141BDC + 3, arg0->unk8);
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            if ((u8)D_80141BDC[3] != 0) {
                func_800129F0(8);
            }
            arg0->unk1++;
        }
    }
}

void func_80020C24(struct EngineObj* arg0)
{
    s8 temp_v1;

    if (D_80141BDC[0] == 0) {
        switch (D_80141BDF[0]) {
        case 0:
            temp_v1 = arg0->state;
            arg0->state = 0xC;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            arg0->unk4 = temp_v1;
            return;
        case 1:
            arg0->state = 3;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            return;
        case 2:
        default:
            func_8001DC30();
            func_800127FC();
            break;
        }
    }
}

void func_80020CB8(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_800204CC(D_80141BDC + 3, arg0->unk8); // why not D_80141BDF?
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->unk1++;
        }
    }
}

void func_80020D3C(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (D_80141BDF[0] == 0) {
            arg0->state = 3;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        } else {
            func_8001DC30();
            func_800127FC();
        }
    }
}

void func_80020D98(struct EngineObj* arg0)
{
    D_800F2454[arg0->unk1](arg0);
    update_misc_objects();
    func_80016124();
    init_objects();
}

void func_80020DEC(u8* arg0, s16 arg1)
{
    struct UnkObj* obj;

    while (arg0[0] != 0xFF) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 1;
            obj->unk2 = arg0[0];
            obj->y_pos.i.hi = arg0[1];
            obj->unk7 = arg0[2];
        }
        arg0 += 3;
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = 0;
        obj->unk2 = -1;
        obj->link.data = D_800F2490;
        obj->x_pos.i.hi = arg1;
    }
}

void func_80020ED4(struct EngineObj* arg0)
{
    arg0->unk7 = 1;
    arg0->character_state.fields.menu_state = 0;
    func_80029DBC();
    D_80141BDF[0] = 0;
    func_80020DEC(&D_800F2468, 0x40);
    func_8001E980(0);
    func_800129A4(8);
}

void func_80020F24(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->character_state.fields.menu_state == 0) {
            func_800204CC(D_80141BDC + 3, 1);
            if (controller_state & PAD_CONFIRM) {
                func_8001540C(0, 0x22, 0);
                if ((u8)D_80141BDC[3] == 0) {
                    func_800129F0(8);
                    arg0->unk7 = 2;
                } else {
                    arg0->character_state.fields.menu_state = 1;
                    func_80029DBC();
#ifdef VERSION_JP
                    D_80141BDC[3] = 1;
#else
                    D_80141BDC[3] = 0;
#endif
                    func_80020DEC(&D_800F247C, 0x78);
                }
            }
        } else {
            func_800204CC(D_80141BDC + 3, 1);
            if (controller_state & PAD_CONFIRM) {
                func_8001540C(0, 0x22, 0);
                arg0->character_state.fields.menu_state = 0;
                if ((u8)D_80141BDC[3] ==
#ifdef VERSION_JP
                    0
#else
                    1
#endif
                ) {
                    arg0->unk7 = 0;
                    if (engine_obj.stage != 0 && engine_obj.unk5F >= 3) {
                        func_8001C3E8();
                    }
                    SetDispMask(0);
                    func_8001D134();
                    func_80015284();
                    reset_game_engine();
                    func_8001DC30();
                    func_800127FC();
                } else {
                    func_80029DBC();
                    D_80141BDC[3] = 0;
                    func_80020DEC(&D_800F2468, 0x40);
                    arg0->unk7 = 1;
                }
            }
        }
    }
}

void func_800210B8(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unk6++;
        func_80029DBC();
        arg0->unk7 = 0;
        arg0->character_state.fields.menu_state = 0;
    }
}

void func_80021104(struct EngineObj* arg0)
{
    D_800F2498[arg0->unk7](arg0);
    update_unk_objects();
    func_80016124();
    func_80025CDC();
}
