// ShotObj, shot_object_update_funcs[35]
// 800A22D4..800A3924
#include "common.h"

void func_800A22D4(struct ShotObj* arg0)
{
    D_801096F4[arg0->state](arg0);
}

void func_800A2310(struct ShotObj* arg0)
{
    struct WeaponObj* temp_v1;

    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk67 = 0;
    arg0->state = (u8)arg0->state + 1 + ((s8)arg0->unk2 >> 4);
    arg0->unk2 = (u8)arg0->unk2 & 0xF;
    if (arg0->state < 4) {
        temp_v1 = arg0->unk7C;
        arg0->unk3C = temp_v1->unk3C;
        arg0->unk40 = temp_v1->unk40;
        arg0->unk42 = temp_v1->unk42 & 0x7FFF;
        arg0->bg_offset = (s8)(u8)temp_v1->bg_offset;
        arg0->animation_table = temp_v1->animation_table;
        arg0->unk15 = temp_v1->unk15;
    }
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

void func_800A23B4(struct ShotObj* arg0)
{
    arg0->state = 7;
}

void func_800A23C0(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A23E0(struct ShotObj* arg0)
{
    D_80109714[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A241C);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A24F0);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A25EC);

void func_800A2748(struct ShotObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    if ((u8)arg0->unk2 & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
    if (background_objects[0].y_pos.i.hi - 0x30 >= arg0->y_pos.i.hi) {
        arg0->unk54 = (const u8*)&D_801096B8;
        arg0->unk50.data = (const u8*)&D_801096BC;
        func_80015D60(ANIMATED_OBJECT(arg0), 0xA);
        arg0->y_vel.val = FIXED(-0.5);
        arg0->unk2C = FIXED(0.09375);
        arg0->timer = 0xF0;
        arg0->unk16 = 2;
        arg0->unk6++;
    }
}

void func_800A27F4(struct ShotObj* arg0)
{
    s16 timer;
    struct WeaponObj* weapon;
    u8 next_state;
    s8 index;
    u16* table;
    u16 background_x;
    u16 offset;

    weapon = arg0->unk7C;
    if (weapon->unk6 != 5) {
        timer = (u16)arg0->timer - 1;
        arg0->timer = timer;
        if (timer != 0) {
            return;
        }
    }

    next_state = arg0->unk6 + 1;
    index = arg0->unk2;
    table = *(u16**)&weapon->ext;
    background_x = background_objects[0].unk1E;
    offset = table[index];

    arg0->timer = 15;
    arg0->unk6 = next_state;
    arg0->x_pos.i.hi = background_x + (offset + 0x10);
}

void func_800A2870(struct ShotObj* arg0)
{
    s16 temp_v0;

    func_8002B694(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    temp_v0 = arg0->timer;
    if (temp_v0 != 0) {
        arg0->timer = temp_v0 - 1;
        return;
    }
    CollisionRelated(PLAYER_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(ANIMATED_OBJECT(arg0), 0xB);
        func_800C813C(4, D_801096DC, arg0);
        func_8001540C(2, 0x9A, arg0);
        func_80028BAC(0x10, 3, 1);
        arg0->timer = 0x100;
        arg0->unk6++;
    }
}

void func_800A2928(struct ShotObj* arg0)
{
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (func_8002BB80(MAIN_OBJECT(arg0), MAIN_OBJECT(arg0->unk7C)) != 0) {
        func_8001540C(2, 0x98, arg0);
        func_800C813C(4, D_801096DC, arg0);
        arg0->state = 6;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    temp_v0 = (u16)arg0->timer - 1;
    arg0->timer = temp_v0;
    if (temp_v0 == 0) {
        arg0->timer = 0x32;
        arg0->unk6++;
    }
}

void func_800A29C8(struct ShotObj* arg0)
{
    s16 timer;

    timer = arg0->timer - 1;
    arg0->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x98, arg0);
        func_800C813C(4, D_801096DC, arg0);
        arg0->state = 6;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    } else {
        arg0->on_screen ^= 1;
        if (arg0->on_screen != 0) {
            is_on_screen(BASE_OBJECT(arg0));
        }
    }
}

void func_800A2A58(struct ShotObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109734[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2AA0);

void func_800A2B8C(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;
    s32 collision_result;
    u16 flags;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010973C[arg0->unk6](arg0);
    func_8002D9BC(arg0);
    collision_result = func_8002DD04(MAIN_OBJECT(arg0));
    weapon = arg0->unk7C;
    if ((collision_result < 0) || (weapon->unk5 != 8)) {
        func_8001540C(2, 0x97, arg0);
        func_800C813C(4, D_801096DC, arg0);
        arg0->state = 6;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    if (collision_result > 0) {
        flags = arg0->unk42 | 0x8000;
    } else {
        flags = arg0->unk42 & 0x7FFF;
    }
    arg0->unk42 = flags;
}

void func_800A2C70(struct ShotObj* arg0)
{
    s16 timer;
    s8 on_screen;

    timer = arg0->timer - 1;
    arg0->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x96, arg0);
        arg0->unk6++;
        return;
    }

    on_screen = arg0->on_screen ^ 1;
    arg0->on_screen = on_screen;
    if (on_screen != 0) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_800A2CEC(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk54 = (const u8*)&D_801096C0;
        arg0->unk50.data = (const u8*)&D_801096C4;
        arg0->unk8C.word = 0;
        arg0->unk6++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2D54);

void func_800A2E6C(struct ShotObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109748[arg0->unk5](arg0);
}

void func_800A2EB4(struct ShotObj* arg0)
{
    arg0->unk68 = &D_801096B0;
    arg0->unk54 = (const u8*)&D_801096C8;
    arg0->unk50.data = (const u8*)&D_801096CC;
    arg0->unk5C = 3;
    arg0->unk60 = 6;
    arg0->unk16 = 4;
    func_80015D60(arg0, 0x20);
    arg0->unk5++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A2F2C);

void func_800A3010(struct ShotObj* arg0)
{
    func_8002B93C(MOVING_OBJECT(arg0), arg0->unk2 + 0xC);
    arg0->x_vel.val *= 4;
    if (arg0->unk15 == 0x40) {
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->y_vel.val *= 4;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A3078);

void func_800A3170(struct ShotObj* arg0)
{
    s16 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    temp_v0 = arg0->timer - 1;
    arg0->timer = temp_v0;
    if (temp_v0 == 0) {
        arg0->timer = 0x32;
        arg0->unk6++;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800A31CC(struct ShotObj* arg0)
{
    s16 timer;

    timer = arg0->timer - 1;
    arg0->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x98, arg0);
        func_800C813C(4, D_801096DC, arg0);
        arg0->state = 6;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    } else {
        arg0->on_screen ^= 1;
        if (arg0->on_screen != 0) {
            is_on_screen(BASE_OBJECT(arg0));
        }
    }
}

void func_800A325C(struct ShotObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109760[arg0->unk5](arg0);
    func_8002D9BC(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A32B8);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A33A0);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A348C);

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A3520);

void func_800A3658(struct ShotObj* arg0)
{
    arg0->state = 6;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_35", func_800A366C);

void func_800A3758(struct ShotObj* object)
{
    struct ShotObj* arg0;
    s8 index;

    arg0 = (struct ShotObj*)object;
    index = arg0->unk2;
    if (index < 3) {
        arg0->x_vel.val = D_801096D0[index];
    } else {
        arg0->x_vel.val = -(((s32*)((u8*)&D_801096A8 + 0x1C))[index]);
    }
    arg0->y_vel.val = FIXED(6.5);
    arg0->unk2C = FIXED(0.2578125);
    arg0->unk5C = 5;
    arg0->unk60 = 6;
    arg0->unk68 = (struct Unk_unk68*)((u8*)&D_801096A8 + 4);
    arg0->unk54 = (const u8*)&D_801096B8;
    arg0->unk50.data = (const u8*)&D_801096BC;
    arg0->unk28 = 0;
    arg0->unk16 = 2;
    func_80015D60(arg0, 0xA);
    arg0->unk5++;
}

void func_800A382C(struct ShotObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8002B694(ANIMATED_OBJECT(arg0));
    CollisionRelated(PLAYER_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0x98, arg0);
        func_800C813C(5, D_801096DC, arg0);
        arg0->state = 6;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void func_800A38B0(struct ShotObj* arg0)
{
    RECT** table;
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    if (arg0->unk7 == 4) {
        table = D_80109698;
    } else {
        table = D_8010969C;
    }
    weapon->ext.rect = table[get_random() & 7];
}

RECT D_80109598[8] = {
    { 0x30, 0x90, 0xF0, 0x150 },
    { 0x30, 0x70, 0xB0, 0xF0 },
    { 0x70, 0xD0, 0x130, 0x190 },
    { 0x70, 0x90, 0xB0, 0xD0 },
    { 0xB0, 0x110, 0x170, 0x1B0 },
    { 0x110, 0x150, 0x190, 0x1B0 },
    { 0xD0, 0x110, 0x150, 0x190 },
    { 0x130, 0x150, 0x170, 0x190 },
};

RECT D_801095D8[8][2] = {
    { { 0x30, 0x70, 0xB0, 0xF0 }, { 0x130, 0x170, 0x190, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xB0 }, { 0xF0, 0x130, 0x170, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xD0 }, { 0xF0, 0x110, 0x170, 0x190 } },
    { { 0x30, 0x50, 0xB0, 0xD0 }, { 0xF0, 0x150, 0x170, 0x190 } },
    { { 0x30, 0x50, 0x70, 0x90 }, { 0x150, 0x170, 0x190, 0x1B0 } },
    { { 0x50, 0x70, 0x90, 0xF0 }, { 0x110, 0x170, 0x190, 0x1B0 } },
    { { 0x30, 0x50, 0x70, 0xD0 }, { 0xF0, 0x150, 0x170, 0x190 } },
    { { 0x50, 0x70, 0xB0, 0xD0 }, { 0x110, 0x130, 0x170, 0x190 } },
};

RECT* D_80109658[8] = {
    &D_80109598[0],
    &D_80109598[1],
    &D_80109598[2],
    &D_80109598[3],
    &D_80109598[4],
    &D_80109598[5],
    &D_80109598[6],
    &D_80109598[7],
};

RECT* D_80109678[8] = {
    D_801095D8[0],
    D_801095D8[1],
    D_801095D8[2],
    D_801095D8[3],
    D_801095D8[4],
    D_801095D8[5],
    D_801095D8[6],
    D_801095D8[7],
};

RECT** D_80109698 = D_80109658;
RECT** D_8010969C = D_80109678;

s16 D_801096A0[2][2] = {
    { -19, -31 },
    { 36, -31 },
};

struct Unk_unk68 D_801096A8 = { -39, 21, 27, 30 };
struct Unk_unk68 D_801096AC = { 0, 10, 9, 3 };
struct Unk_unk68 D_801096B0 = { 0, 0, 6, 6 };
struct Unk_unk68 D_801096B4 = { 0, -4, 10, 7 };
struct Unk_unk68 D_801096B8 = { -12, -32, 23, 63 };
struct Unk_unk68 D_801096BC = { -4, -20, 9, 30 };
struct Unk_unk68 D_801096C0 = { -37, -56, 73, 118 };
struct Unk_unk68 D_801096C4 = { -28, -48, 55, 88 };
struct Unk_unk68 D_801096C8 = { -13, -12, 23, 23 };
struct Unk_unk68 D_801096CC = { -5, -8, 9, 15 };

s32 D_801096D0[3] = { 0x30000, 0x20000, 0x10000 };

u8 D_801096DC[12] = { 12, 13, 14, 15, 13, 15, 12, 14, 13, 15, 0, 0 };

u8 D_801096E8[12] = { 12, 13, 35, 15, 35, 15, 36, 14, 36, 15, 0, 0 };

void (*D_801096F4[])(struct ShotObj*) = {
    func_800A2310,
    func_800A23E0,
    func_800A2A58,
    func_800A325C,
    func_800A366C,
    func_800A2E6C,
    func_800A23B4,
    func_800A23C0,
};

void (*D_80109714[])(struct ShotObj*) = {
    func_800A241C,
    func_800A24F0,
};

void (*D_8010971C[])(struct ShotObj*) = {
    func_800A25EC,
    func_800A2748,
    func_800A27F4,
    func_800A2870,
    func_800A2928,
    func_800A29C8,
};

void (*D_80109734[])(struct ShotObj*) = {
    func_800A2AA0,
    func_800A2B8C,
};

void (*D_8010973C[])(struct ShotObj*) = {
    func_800A2C70,
    func_800A2CEC,
    func_800A2D54,
};

void (*D_80109748[])(struct ShotObj*) = {
    func_800A2EB4,
    func_800A2F2C,
};

void (*D_80109750[])(struct ShotObj*) = {
    func_800A3010,
    func_800A3078,
    func_800A3170,
    func_800A31CC,
};

void (*D_80109760[])(struct ShotObj*) = {
    func_800A32B8,
    func_800A33A0,
};

void (*D_80109768[])(struct ShotObj*) = {
    func_800A348C,
    func_800A3520,
    func_800A3658,
};

void (*D_80109774[])(struct ShotObj*) = {
    func_800A3758,
    func_800A382C,
};

s16 D_8010977C[4][2] = {
    { -0x1280, 0x2AFF },
    { -0x1280, 0x2AFF },
    { -0xA80, 0x19FF },
    { -0xA80, 0x19FF },
};
