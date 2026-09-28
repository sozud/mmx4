// MainObj, main_object_update_funcs[36]
// 8005F510..8005FDBC
#include "common.h"
#include "func_tables.h"

void func_8005F510(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FE4A8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005F558);

extern void (*D_800FE4B4[])(struct MainObj*);

void func_8005F758(struct MainObj* arg0)
{
    D_800FE4B4[arg0->unk5](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if ((SP_CUR_MAIN_OBJ->ext.main_36.unk8D == 0) && (g_Player.unkBA == 0) && (func_8002D9BC(arg0) != 0) && (g_Player.unkBA != 0)) {
        SP_CUR_MAIN_OBJ->ext.main_36.unk8D = 1;
    }

    SP_CUR_MAIN_OBJ->ext.main_36.saved_unk5 = arg0->unk5;
    func_8005FCD8(arg0);

    if (func_8002B160(BASE_OBJECT(arg0)) == 1) {
        arg0->state = 2;
    }
}

void func_8005F844(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005F864(struct MainObj* arg0)
{
    arg0->unk5 = SP_CUR_MAIN_OBJ->ext.main_36.saved_unk5;
}

void func_8005F87C(struct MainObj* arg0)
{
    struct MiscObj* misc;

    if (SP_CUR_MAIN_OBJ->ext.main_36.unk8D != 0 && g_Player.unkBA != 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            SP_CUR_MAIN_OBJ->ext.main_36.unk8C = 1;
            misc->active = 0x41;
            misc->id = 0xB;
            misc->unk16 = 1;
            misc->unk15 = arg0->unk15;
            misc->unk40 = arg0->unk40;
            misc->unk42 = arg0->unk42;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->animation_table = (u32**)D_800FE48C;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->bg_offset = g_Player.bg_offset;
            misc->ext.misc_11.active = 0;
            SP_CUR_MAIN_OBJ->ext.main_36.unk84 = misc;
            func_80015D60(misc, 0);
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            func_80015D60(arg0, 0);
        }
    }
    func_8002B718(MOVING_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8005F9A4(struct MainObj* arg0)
{
    D_800FE4C4[arg0->unk6](arg0);
    is_on_screen((struct BaseObj*)arg0);
}

void func_8005F9F4(struct MainObj* arg0)
{
    s32 distance;

    SP_CUR_MAIN_OBJ->ext.main_36.unk89 = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    func_8002B93C(MOVING_OBJECT(arg0), SP_CUR_MAIN_OBJ->ext.main_36.unk89);
    SP_CUR_MAIN_OBJ->ext.main_36.unk84->x_vel.val = arg0->unk20;
    SP_CUR_MAIN_OBJ->ext.main_36.unk84->y_vel.val = arg0->unk24;
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(SP_CUR_MAIN_OBJ->ext.main_36.unk84));
    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance >= 0 ? distance < 2 : arg0->x_pos.i.hi - g_Player.x_pos.i.hi < 2) {
        distance = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
        if (distance >= 0 ? distance < 2 : arg0->y_pos.i.hi - g_Player.y_pos.i.hi < 2) {
            func_80015D60(arg0, 3);
            func_80015D60(SP_CUR_MAIN_OBJ->ext.main_36.unk84, 3);
            arg0->unk6++;
        }
    }
}

void func_8005FB38(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        if (SP_CUR_MAIN_OBJ->ext.main_36.unk8C != 0) {
            func_80015D60(arg0, 4);
            func_80015D60(SP_CUR_MAIN_OBJ->ext.main_36.unk84, 5);
        }
        arg0->unk6++;
    }
}

void func_8005FBBC(struct MainObj* self)
{
    struct MainObj* current;
    u16 timer;

    current = SP_CUR_MAIN_OBJ;
    timer = current->ext.main_36.unk8A - 1;
    current->ext.main_36.unk8A = timer;
    if (timer == 0) {
        self->unk62 = 0;
        self->unk50 = NULL;
        self->unk54 = NULL;
        g_Player.unkBA = 0;
        self->unk6++;
        current = SP_CUR_MAIN_OBJ;
        if (current->ext.main_36.unk8C != 0) {
            current->ext.main_36.unk84->ext.misc_11.active = 1;
        }
        func_80015D60(self, 6);
        return;
    }
    if (current->ext.main_36.unk8C != 0 && timer == 0x40) {
        func_80036470(4);
    }
    if ((SP_CUR_MAIN_OBJ->ext.main_36.unk8A & 7) == 0) {
        func_8001540C(2, 0xED, self);
    }
}

void func_8005FCAC(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->state++;
    }
}

void func_8005FCD8(struct MainObj* arg0)
{
    s32 result;

    result = func_8002DD04(arg0);
    if (result == 0) {
        return;
    }
    if (result < 0) {
        func_80015D60(arg0, 3);
        arg0->unk5 = 3;
        arg0->unk6 = 1;
        arg0->unk50 = NULL;
        arg0->unk54 = NULL;
        SP_CUR_MAIN_OBJ->ext.main_36.unk8A = 1;
        return;
    }

    arg0->unk5C = 0x10;
    if (arg0->unk5 == 3) {
        return;
    }

    if (g_Player.x_pos.i.hi <= arg0->x_pos.i.hi) {
        arg0->unk20 += FIXED(0.28125);
        if (arg0->unk20 == FIXED(0.28125)) {
            func_80015D60(arg0, 1);
        }
    } else {
        arg0->unk20 -= FIXED(0.28125);
        if (arg0->unk20 == FIXED(-0.28125)) {
            func_80015D60(arg0, 2);
        }
    }
}

struct Unk_unk68 D_800FE2E8 = { -14, -14, 28, 28 };

union AnimationStep D_800FE2EC[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010002 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07F90002 },
};

union AnimationStep D_800FE30C[] = {
    { 0x00010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1AED0002 },
};

union AnimationStep D_800FE35C[] = {
    { 0x00010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x15010002 },
    { 0x14010002 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x11010002 },
    { 0x10010002 },
    { 0x0F010002 },
    { 0x0E010002 },
    { 0x0D010002 },
    { 0x0C010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x08ED0002 },
};

union AnimationStep D_800FE3AC[] = {
    { 0x00010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F000102 },
};

union AnimationStep D_800FE3C4[] = {
    { 0x20010002 },
    { 0x24010002 },
    { 0x23010002 },
    { 0x25010002 },
    { 0x21010002 },
    { 0x26010002 },
    { 0x22010002 },
    { 0x27F90002 },
};

union AnimationStep D_800FE3E4[] = {
    { 0x28010002 },
    { 0x3D010002 },
    { 0x24010002 },
    { 0x3D010002 },
    { 0x28010002 },
    { 0x3D010002 },
    { 0x25010002 },
    { 0x3D010002 },
    { 0x38010002 },
    { 0x3D010002 },
    { 0x36010002 },
    { 0x3D010002 },
    { 0x38010002 },
    { 0x3D010002 },
    { 0x37010002 },
    { 0x3DF10002 },
};

union AnimationStep D_800FE424[] = {
    { 0x1F010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1C010002 },
    { 0x1B010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B010002 },
    { 0x2C010002 },
    { 0x2D010002 },
    { 0x2E010002 },
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3C010002 },
    { 0x3D000102 },
};

union AnimationStep* D_800FE48C[7] = {
    D_800FE2EC,
    D_800FE30C,
    D_800FE35C,
    D_800FE3AC,
    D_800FE3C4,
    D_800FE3E4,
    D_800FE424,
};

void (*D_800FE4A8[3])() = {
    func_8005F558,
    func_8005F758,
    func_8005F844,
};

void (*D_800FE4B4[4])() = {
    func_8009216C,
    func_8005F864,
    func_8005F87C,
    func_8005F9A4,
};

void (*D_800FE4C4[4])() = {
    func_8005F9F4,
    func_8005FB38,
    func_8005FBBC,
    func_8005FCAC,
};
