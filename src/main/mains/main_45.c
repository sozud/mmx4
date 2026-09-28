// MainObj, main_object_update_funcs[45]
// 80065B8C..80066A48
#include "common.h"
#include "func_tables.h"

void func_80065B8C(struct MainObj* arg0)
{
    D_800FF964[arg0->state](arg0);
}

void func_80065BC8(struct MainObj* self)
{
    self->active |= 4;
    self->unk60 = 2;
    self->on_screen = 0;
    self->unk5C = 0;
    self->unk61 = 1;
    self->collision_data = D_80107678;
    self->bg_offset = g_Player.bg_offset;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk67 = 0;
    self->unk75 = 1;
    self->unk76 = 0;
    self->unk54 = NULL;
    self->unk50 = NULL;
    self->unk15 = 0;
    self->ext.main_45.attack_flags = 0;
    self->ext.main_45.unk81 = 0;
    self->ext.main_45.unk82 = 0;
    self->ext.main_45.unk83 = 0;
    self->animation_table = (const u8* const*)D_800FF918;
    self->unk16 = 4;
    self->unk68 = (struct Unk_unk68*)D_800FF898;
    self->ext.main_45.unk84 = 0x320;
    self->ext.main_45.projectile_command = 0x80;
    self->ext.main_45.unk89 = 0;
    self->ext.main_45.unk86 = D_800FF89C[0];
    self->ext.main_45.unk87 = 0;
    func_80015D60(self, 0);
    self->state = 1;
    self->unk5 = 0;
    self->unk6 = 0;
}

void func_80065CD4(struct MainObj* self)
{
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->ext.main_45.unk8A = self->x_pos.i.hi;
    func_8006630C(self);
    D_800FF978[self->unk5](self);
    func_80066478(self);
    if ((self->ext.main_45.attack_flags & 7) == 7) {
        func_800AF808(BASE_OBJECT(self));
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        *self->ext.main_45.layer_bg_offset = 0;
        self->unk7C = 0x78;
        self->unk7E = 1;
        self->state = 2;
        if (g_Player.unk5 == 2) {
            player_start_script_action(0x14, 0x40);
            self->unk6 = 1;
        } else {
            self->unk6 = 0;
        }
    }
    func_8002B318(BASE_OBJECT(self), 0x100, 0x100);
}

void func_80065DCC(struct MainObj* arg0)
{
    s16 timer;

    func_80066970();
    timer = (u16)arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        if (func_8002BAD0(1, -0x20, 0x80) == 0x1C) {
            arg0->state = 3;
            arg0->unk5 = 0;
        } else {
            arg0->unk7C = 1;
        }
    }
    if ((arg0->unk6 == 0) && ((arg0->x_pos.i.hi + 0x69 >= g_Player.x_pos.i.hi) || (g_Player.x_pos.i.hi >= 0x1B36))) {
        player_start_script_action(0x14, 0x40);
        arg0->unk6 = 1;
    }
    func_8002E184(PLAYER_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x100, 0x100);
}

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_80065EA4);

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_800661AC);

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_8006630C);

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_80066478);

void func_80066580(struct MainObj* arg0)
{
    D_800FF980[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_800665BC);

void func_80066804(struct MainObj* arg0)
{
    if (arg0->x_pos.i.hi >= 0x19A1) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 2;
        engine_obj.boss_ptr = arg0;
        arg0->unk6 = 2;
    }
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80066858(struct MainObj* arg0)
{
    if (arg0->x_pos.i.hi >= 0x1AA1) {
        arg0->unk7E = 3;
        arg0->unk6 = 3;
    } else {
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

void func_8006689C(struct MainObj* arg0)
{
    s16 timer;

    if (arg0->unk5C < 0x30) {
        timer = (u16)arg0->unk7E - 1;
        arg0->unk7E = timer;
        if (timer == 0) {
            func_8001540C(0, 0xE, NULL);
            arg0->unk7E = 3;
        }
        arg0->unk5C = (u8)arg0->unk5C + 1;
        return;
    }
    arg0->ext.main_45.projectile_command = 0xFF;
    arg0->unk5 = 1;
    arg0->unk6 = 0;
    player_end_script_action();
}

void func_8006692C(struct MainObj* arg0)
{
    D_800FF990[arg0->unk6](arg0);
}

void func_80066968(void)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_45", func_80066970);

s8 D_800FF898[4] = { -56, 12, 39, 86 };

u8 D_800FF89C[20] = {
    0,
    1,
    2,
    1,
    2,
    0,
    3,
    3,
    2,
    1,
    0,
    1,
    0,
    2,
    4,
    3,
    3,
    0xFF,
    0,
    0,
};

u8 D_800FF8B0[8] = { 0x11, 0x22, 0x44, 0x08, 0, 0, 0, 0 };

union AnimationStep D_800FF8B8[] = { { 0x00000101 } };

union AnimationStep D_800FF8BC[] = { { 0x01000101 } };

union AnimationStep D_800FF8C0[] = { { 0x02000101 } };

union AnimationStep D_800FF8C4[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06FD0101 },
};

union AnimationStep D_800FF8D4[] = {
    { 0x03010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x06FD0101 },
};

union AnimationStep D_800FF8E4[] = { { 0x07000101 } };

union AnimationStep D_800FF8E8[] = { { 0x0A000101 } };

union AnimationStep D_800FF8EC[] = { { 0x0B000101 } };

union AnimationStep D_800FF8F0[] = { { 0x0C000101 } };

union AnimationStep D_800FF8F4[] = { { 0x0D000101 } };

union AnimationStep D_800FF8F8[] = { { 0x0E000101 } };

union AnimationStep D_800FF8FC[] = { { 0x0F000101 } };

union AnimationStep D_800FF900[] = { { 0x10000101 } };

union AnimationStep D_800FF904[] = { { 0x11000101 } };

union AnimationStep D_800FF908[] = { { 0x12000101 } };

union AnimationStep D_800FF90C[] = { { 0x13000101 } };

union AnimationStep D_800FF910[] = { { 0x14000101 } };

union AnimationStep D_800FF914[] = { { 0x15000101 } };

union AnimationStep* D_800FF918[19] = {
    D_800FF8B8,
    D_800FF8BC,
    D_800FF8C0,
    D_800FF8C4,
    D_800FF8D4,
    D_800FF8E4,
    D_800FF8E8,
    D_800FF8EC,
    D_800FF8F0,
    D_800FF8F4,
    D_800FF8F8,
    D_800FF8FC,
    D_800FF900,
    D_800FF904,
    D_800FF908,
    D_800FF90C,
    D_800FF910,
    D_800FF914,
    NULL,
};

void (*D_800FF964[])(struct MainObj*) = {
    func_80065BC8,
    func_80065CD4,
    func_80065DCC,
    func_80065EA4,
    func_800661AC,
};

void (*D_800FF978[2])(struct MainObj*) = { func_80066580, func_8006692C };

void (*D_800FF980[4])(struct MainObj*) = {
    func_800665BC,
    func_80066804,
    func_80066858,
    func_8006689C,
};

void (*D_800FF990[1])(struct MainObj*) = { func_80066968 };
