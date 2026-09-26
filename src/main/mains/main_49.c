// MainObj, main_object_update_funcs[49]
// 800684F8..8006970C
#include "common.h"

extern u8 D_800FFB64[];
extern s16 main49_activation_distances[4];

void func_800684F8(struct MainObj* arg0)
{
    D_800FFB78[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068548);

void func_800688B8(struct MainObj* arg0)
{
    u8 temp_v1;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(5, D_800FFB68, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0x12);
        goto block_12;
    }
    temp_v1 = SP_CUR_MAIN_OBJ->ext.main_49.unk85;
    if (temp_v1 != 2 && temp_v1 < 6U) {
        func_80068F88(arg0);
    }
    func_80068D6C(arg0);
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0) {
        func_80069000(arg0);
    }
    D_800FFB88[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0) {
        if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
            is_on_screen(BASE_OBJECT(arg0));
        } else {
            arg0->state = 2;
        }
    } else if (func_8002B1E8(BASE_OBJECT(arg0), 0x70, 0) != 0) {
        arg0->state = 2;
    } else {
        is_on_screen(BASE_OBJECT(arg0));
    }
    return;
block_12:
    arg0->state = 2;
}

void func_80068A10(struct MainObj* arg0)
{
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0 || arg0->unk2 == 9) {
        func_8002B0C8(OBJECT_HEADER(arg0));
    } else {
        func_8002B108(OBJECT_HEADER(arg0));
    }
}

void func_80068A68(struct MainObj* arg0)
{
    s8 temp_a2;
    s16 threshold;
    u8 temp_v0;
    u8* temp_v1;

    if (arg0->unk6 == 0) {
        temp_a2 = arg0->unk2;
        threshold = main49_activation_distances[temp_a2 - 6];
        if ((g_Player.x_pos.i.hi - arg0->x_pos.i.hi) >= threshold) {
            temp_v1 = (u8*)SP_CUR_MAIN_OBJ;
            temp_v1[0x81] = (u8)((temp_a2 - 6) * 0x10);
            arg0->unk6 = (u8)arg0->unk6 + 1;
        }
    } else {
        temp_v1 = (u8*)SP_CUR_MAIN_OBJ;
        temp_v0 = temp_v1[0x81];
        if (temp_v0 == 0) {
            arg0->state = 1;
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->unk7A = 0;
            if (g_Player.x_pos.val < arg0->x_pos.val) {
                arg0->unk15 = 0;
                return;
            }
            arg0->unk15 = 0x40;
            return;
        }
        temp_v1[0x81] = temp_v0 - 1;
    }
}

void func_80068B3C(struct MainObj* arg0)
{
}

void func_80068B44(struct MainObj* arg0)
{
    D_800FFBA8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068B80);

void func_80068C2C(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));

    if (self->unk15 != 0) {
        if (self->unk70 & 1) {
            self->unk15 = 0;
            self->unk20 = -self->unk20;
        }
    } else if (self->unk70 & 2) {
        self->unk15 = 0x40;
        self->unk20 = -self->unk20;
    }
}

void func_80068CB0(struct MainObj* arg0)
{
    D_800FFBB0[arg0->unk6](arg0);
}

extern u32 D_801076F8[];
extern u8 D_800FFB60[];

void func_80068CEC(struct MainObj* arg0)
{
    arg0->collision_data = (const u16*)D_801076F8;
    arg0->unk54 = D_800FFB60;
    arg0->unk50 = D_800FFB64;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk6++;
    func_80015D60(arg0, 8);
}

void func_80068D4C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068D6C);

void func_80068F88(struct MainObj* arg0)
{
    u8 timer;

    if (arg0->unk5 == 2) {
        timer = SP_CUR_MAIN_OBJ->ext.main_49.index + 1;
        SP_CUR_MAIN_OBJ->ext.main_49.index = timer;
        if ((timer & 0xFF) == 0x5A) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            SP_CUR_MAIN_OBJ->ext.main_49.index = 0;
            arg0->unk24 = 0;
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            func_80015D60(arg0, 7);
        }
    }
}

void func_80069000(struct MainObj* arg0)
{
    s16 distance;
    s32 y_distance;
    struct MainObj* self;
    struct MainObj* current;

    if ((arg0->unk67 == 0) && (arg0->unk5 != 6)) {
        self = SP_CUR_MAIN_OBJ;
        if (self->ext.main_49.unk83 != 0) {
            self->ext.main_49.unk83--;
            return;
        }

        if ((arg0->x_pos.i.hi - g_Player.x_pos.i.hi) >= 0) {
            distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        } else {
            distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
        }

        if (distance < 0x81) {
            if (arg0->x_pos.i.hi > g_Player.x_pos.i.hi) {
                arg0->unk15 = 0;
            } else {
                arg0->unk15 = 0x40;
            }

            current = SP_CUR_MAIN_OBJ;
            if ((current->ext.main_49.unk85 == 1) || ((current->ext.main_49.unk85 == 2) && (arg0->unk2 != 0))) {
                current->ext.main_49.unk82 = 0x40;
            } else {
                y_distance = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
                if (y_distance >= 0x21) {
                    SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x80;
                } else if (y_distance < -0x10) {
                    SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x82;
                } else {
                    SP_CUR_MAIN_OBJ->ext.main_49.unk82 = 0x81;
                }
            }

            func_80015D60(arg0, 0xA);
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
    }
}

void func_8006917C(struct MainObj* arg0)
{
    D_800FFBB8[arg0->unk6](arg0);
}

void func_800691B8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        if (SP_CUR_MAIN_OBJ->ext.main_49.unk80 == 4) {
            func_80015D60(arg0, 0x17);
        } else {
            func_80015D60(arg0, 0x18);
        }
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk6++;
    }
}

void func_80069248(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        if (SP_CUR_MAIN_OBJ->ext.main_49.unk85 == 2) {
            arg0->unk5 = 7;
        } else {
            arg0->unk5 = 2;
        }
        arg0->unk6 = 0;
        arg0->unk67 = 0;
    }
}

void func_800692AC(struct MainObj* arg0)
{
    D_800FFBC0[arg0->unk6](arg0);
}

void func_800692E8(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk6++;
    }
}

void func_80069330(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 < 0) {
        SP_CUR_MAIN_OBJ->ext.main_49.unk80 = 4;
        func_80015D60(arg0, 9);
        arg0->unk5 = 3;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = -1;
    }
}

void func_800693AC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (++SP_CUR_MAIN_OBJ->ext.main_49.index == 0x3C) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_80069414(struct MainObj* arg0)
{
    D_800FFBC8[arg0->unk6](arg0);
}

void func_80069450(struct MainObj* arg0)
{
    u8 flags;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        flags = SP_CUR_MAIN_OBJ->ext.main_49.unk82;
        if (flags & 0x80) {
            switch (flags & 3) {
            case 0:
                func_80015D60(arg0, 0xD);
                break;
            case 1:
                func_80015D60(arg0, 0xC);
                break;
            case 2:
                func_80015D60(arg0, 0xE);
                break;
            }
        } else {
            func_80015D60(arg0, 0x1A);
        }
        arg0->unk6++;
    }
}

void func_8006951C(struct MainObj* arg0)
{
    s8 event;
    struct ShotObj* shot;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    event = arg0->animation_step.fields.event;
    if (event != 0) {
        if (event == 3) {
            func_8001540C(2, 0x66, arg0);
        }
        arg0->unk6++;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x19;
            shot->unk2 = SP_CUR_MAIN_OBJ->ext.main_49.unk82;
            shot->x_pos.val = arg0->x_pos.val;
            shot->y_pos.val = arg0->y_pos.val;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42 & 0x7FFF;
            shot->bg_offset = arg0->bg_offset;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk15 = arg0->unk15;
        }
    }
}

void func_80069610(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 11);
        arg0->unk6++;
    }
}

void func_80069660(struct MainObj* arg0)
{
    struct MainObj* main;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        if (SP_CUR_MAIN_OBJ->ext.main_49.unk85 == 2) {
            arg0->unk5 = 7;
        } else {
            arg0->unk5 = 5;
        }
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = 0;
        SP_CUR_MAIN_OBJ->ext.main_49.index = 0;
        main = SP_CUR_MAIN_OBJ;
        if (main->ext.main_49.unk85 == 2) {
            main->ext.main_49.unk83 = 0x5A;
        } else {
            main->ext.main_49.unk83 = 0xB4;
        }
        func_80015D60(arg0, 7);
    }
}
