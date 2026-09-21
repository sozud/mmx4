// MainObj, main_object_update_funcs[74]
// 8008D460..8008FB38
#include "common.h"

void func_8008D460(struct MainObj* arg0)
{
    D_8013B8B8[0] = 0;
    arg0->ext.main_74.unk94 = 0;
    arg0->ext.main_74.unk96 = 0;
    background_objects[0].unk26 = 0x410;
    background_objects[0].unk24 = 0x480;
    background_objects[0].unk2A = 0x200;
    background_objects[0].unk28 = 0x200;
    func_80036AE4(0x14, 0x40);
    arg0->ext.main_74.timer = 0x64;
    arg0->unk5++;
    func_80016FB4(3);
}

void func_8008D4E8(struct MainObj* arg0)
{
    if (--arg0->ext.main_74.timer == 0) {
        func_80013AD8(
#ifdef VERSION_JP
            0x80,
#else
            0x81,
#endif
            4, D_80141F30[2]);
        arg0->unk5++;
    }
}

void func_8008D548(struct MainObj* arg0)
{
    if ((D_801406AC == 2) && (D_8013BD40 == 0)) {
        D_80171EA8 = 1;
        arg0->unk5++;
    }
}

void func_8008D590(struct MainObj* arg0)
{
    func_8001653C();
    arg0->unk5++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008D5C8);

#ifdef VERSION_JP
extern void* D_8013B994_jp;
#define MAIN_74_COLLISION_BOUNDS D_8013B994_jp
#else
extern void* D_8013B8B4;
#define MAIN_74_COLLISION_BOUNDS D_8013B8B4
#endif

void func_8008D764(struct MainObj* arg0, s32 arg1)
{
    switch (arg1 & 0xFF) {
    case 0:
        D_8013B8B0 = 0;
        MAIN_74_COLLISION_BOUNDS = 0;
        arg0->unk50 = 0;
        break;
    case 1:
        D_8013B8B0 = &D_80105368;
        MAIN_74_COLLISION_BOUNDS = &D_8010536C;
        arg0->unk5C = arg0->ext.main_74.unk92;
        arg0->unk5D = arg0->ext.main_74.unk92;
        arg0->unk50 = &D_8010535C;
        break;
    case 2:
        D_8013B8B0 = 0;
        MAIN_74_COLLISION_BOUNDS = &D_80105370;
        arg0->unk5C = arg0->ext.main_74.unk93;
        arg0->unk5D = arg0->ext.main_74.unk93;
        arg0->unk50 = &D_80105360;
        break;
    }

    arg0->ext.main_74.unk91 = arg1;
}

void func_8008D830(struct MainObj* arg0)
{
    D_801058B0[arg0->unk5](arg0);
}

void func_8008D86C(struct MainObj* arg0)
{
}

void func_8008D874(struct MainObj* arg0)
{
    arg0->x_pos.i.hi = 0x567;
    arg0->y_pos.i.hi = 0x287;
    arg0->unk6++;
    func_80015D60(arg0, 0x18);
    func_8001540C(2, 9, arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008D8DC(struct MainObj* arg0)
{
    u16 sound_id;

    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6++;
        sound_id = 0x2D;
        if (engine_obj.cur_character == 0) {
            sound_id = 0x32;
        }
        func_8002217C(sound_id, 0xFF, 0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008D95C(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_8008D764(arg0, 1);
        arg0->unk7E = 3;
        arg0->unk6++;
        func_800921E8(0xC);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008D9C8(struct MainObj* arg0)
{
    s16 temp_v0;

    if (arg0->unk5C < 0x30) {
        if (func_8009227C() == 0) {
            temp_v0 = arg0->unk7E - 1;
            arg0->unk7E = temp_v0;
            if (temp_v0 == 0) {
                func_8001540C(0, 0xE, 0);
                arg0->unk7E = 3;
            }
            arg0->unk5C++;
        }
    } else {
        func_80015D60(arg0, 0);
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        *D_8013B8A0 = 0xA;
        D_8013B8B0 = &D_80105368;
        MAIN_74_COLLISION_BOUNDS = &D_8010536C;
        func_80036B18();
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008DAAC(struct MainObj* arg0)
{
    D_801058C4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008DAE8);

void func_8008DC5C(struct MainObj* arg0)
{
    func_8008D3B8(arg0, 5);
    arg0->unk7C = 5;
    arg0->unk6++;
}

void func_8008DC9C(struct MainObj* arg0)
{
    if (g_Player.y_pos.i.hi < 0x250) {
        arg0->ext.main_74.animation_index = 3;
    } else if (g_Player.y_pos.i.hi < 0x270) {
        arg0->ext.main_74.animation_index = 2;
    } else if (g_Player.y_pos.i.hi < 0x290) {
        arg0->ext.main_74.animation_index = 1;
    } else {
        arg0->ext.main_74.animation_index = 0;
    }
    func_80015D60(arg0,
        D_801058D4[arg0->ext.main_74.animation_index * 2]);
    arg0->unk6++;
}

void func_8008DD38(struct PlayerObj* player)
{
    struct QuadObj* quad;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(player));
    if (player->animation_step.fields.relative_step < 0) {
        player->unk6 += 1;
        func_8001540C(2, 5, player);

        quad = find_free_quad_obj();
        if (quad != 0) {
            quad->active = 1;
            quad->id = 0x10;
            quad->unk2 = player->unk90;
            quad->unk5C = player;
        }
        D_8013B8A8 = OBJECT_HEADER(quad);

        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 1;
            shot->id = 0x39;
            shot->unk2 = player->unk90;
            shot->unk7C = WEAPON_OBJECT(player);
        }
    }
}

void func_8008DDE8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (D_8013B8A8->active == 0) {
        func_80015930(2, 5);
        arg0->unk6++;
        func_80015D60(arg0,
            D_801058D4[arg0->ext.main_74.animation_index * 2 + 1]);
    }
}

void func_8008DE5C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        if (--arg0->unk7C == 0) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
        } else {
            arg0->unk6 = 1;
        }
    }
}

void func_8008DEC4(struct MainObj* arg0)
{
    D_801058DC[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008DF1C(struct MainObj* arg0)
{
    arg0->ext.main_74.animation_index = 1;
    func_80015D60(arg0, 0x1D);
    func_8008D3B8(arg0, 3);
    func_8001540C(2, 6, arg0);
    func_8001540C(2, 1, arg0);
    arg0->unk6++;
}

void func_8008DF8C(struct MainObj* arg0)
{
    struct MiscObj* miscObj;
    struct ShotObj* shotObj;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step < 0) {
        miscObj = find_free_misc_obj();
        if (miscObj != NULL) {
            miscObj->active = 0x41;
            miscObj->id = 0x37;
            miscObj->unk2 = arg0->ext.main_74.animation_index;
            miscObj->ext.misc_55.owner = arg0;
        }
        shotObj = find_free_shot_obj();
        if (shotObj != NULL) {
            shotObj->active = 1;
            shotObj->id = 0x39;
            shotObj->unk2 = arg0->ext.main_74.animation_index + 4;
            shotObj->unk7C = WEAPON_OBJECT(arg0);
        }
        arg0->unk6++;
        D_8013B8A8 = OBJECT_HEADER(miscObj);
    }
}

void func_8008E040(struct MainObj* arg0)
{
    struct QuadObj* quad;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (D_8013B8A8->active == 0) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 0x10;
            quad->unk2 = arg0->ext.main_74.animation_index + 0x10;
            quad->unk5C = PLAYER_OBJECT(arg0);
        }
        D_8013B8A8 = OBJECT_HEADER(quad);
        arg0->unk6++;
    }
}

void func_8008E0CC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (D_8013B8A8->active == 0) {
        func_80015930(2, 1);
        if (arg0->ext.main_74.animation_index != 0) {
            func_80015D60(arg0, 0x22);
        } else {
            func_80015D60(arg0, 0x24);
        }
        arg0->unk6++;
    }
}

void func_8008E14C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8008E18C(struct MainObj* arg0)
{
    D_801058F0[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008E1E4(struct MainObj* arg0)
{
    arg0->ext.main_74.unk8C = 3;
    arg0->unk6++;
    func_80015D60(arg0, 0x19);
    func_8001540C(2, 9, arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008E244(struct MainObj* self)
{
    s32 count;
    u32 i;

    count = 0;
    for (i = 0; i < COUNT(self->ext.main_74.children); i++) {
        if (self->ext.main_74.children[i]->unk5 == 3) {
            count++;
        }
    }
    if ((self->animation_step.fields.relative_step == 0) && (count == 3)) {
        self->unk5 = 2;
        self->unk6 = 0;
        func_8008D764(self, 0);
        D_8013B8A0[0] = 0x1E;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
        return;
    }
    self->x_pos.i.hi = 0;
    self->y_pos.i.hi = 0;
}

void func_8008E318(struct MainObj* arg0)
{
    D_80105904[arg0->unk6](arg0);
}

void func_8008E354(struct MainObj* arg0)
{
    arg0->unk60 = 9;
    arg0->x_pos.i.hi = 0x567;
    arg0->y_pos.i.hi = 0x287;
    func_8008D764(arg0, 1);
    arg0->unk6++;
    func_80015D60(arg0, 0x18);
    func_8001540C(2, 9, arg0);
}

void func_8008E3C0(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        D_8013B8A0[0] = 0x1E;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008E404(struct MainObj* arg0)
{
    D_8010590C[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008E45C(struct MainObj* arg0)
{
    arg0->ext.main_74.unk8C = 3;
    arg0->unk6++;
    func_80015D60(arg0, 0x1B);
    func_8001540C(2, 9, arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008E4BC(struct MainObj* arg0)
{
    u32 i;
    s32 count = 0;
    for (i = 0; i < COUNT(arg0->ext.main_74.children); i++) {
        if (arg0->ext.main_74.children[i]->unk5 == 3) {
            count++;
        }
    }
    if ((arg0->animation_step.fields.relative_step == 0) && (count == 3)) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        func_8008D764(arg0, 0);
        D_8013B8A0[0] = 0x1E;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step != 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }
    arg0->x_pos.i.hi = 0;
    arg0->y_pos.i.hi = 0;
}

void func_8008E590(struct MainObj* arg0)
{
    D_80105914[arg0->unk6](arg0);
}

void func_8008E5CC(struct MainObj* arg0)
{
    arg0->unk60 = 9;
    arg0->x_pos.i.hi = 0x450;
    arg0->y_pos.i.hi = 0x2B8;
    func_8008D764(arg0, 2);
    arg0->unk6++;
    func_80015D60(arg0, 0x1A);
    func_8001540C(2, 9, arg0);
}

void func_8008E638(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        D_8013B8A0[0] = 0xA;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8008E67C(struct MainObj* arg0)
{
    D_8010591C[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008E6D4(struct MainObj* arg0)
{
    func_8008D3B8(arg0, 7);
    func_80015D60(arg0, 2);
    arg0->unk7C = 0x3C;
    arg0->unk62 = 3;
    arg0->unk50 = (const u8*)&D_80105364;
    arg0->unk60 = 0;
    arg0->unk6++;
    func_8001540C(2, 0xB, arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008E748);

void func_8008E8C8(struct MainObj* arg0)
{
    struct ShotObj* current;
    s32 found;
    s16 timer;

    timer = arg0->unk7C;
    if (timer != 0) {
        arg0->unk7C = timer - 1;
        return;
    }

    found = 0;
    for (current = shot_objects; current < &shot_objects[0x20]; current++) {
        if (current->id == 0x38) {
            s32 active = current->active;
            if ((active & 1) == 1) {
                found = 1;
            }
        }
    }

    if (!found) {
        func_80015930(2, 0xB);
        g_Player.unkBA = 0;
        arg0->unk62 = 2;
        arg0->unk60 = 9;
        arg0->unk50 = &D_80105360;
        arg0->unk6++;
    }
}

void func_8008E99C(struct MainObj* arg0)
{
    arg0->unk60 = 9;
    arg0->unk62 = 0;
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}

void func_8008E9B8(struct MainObj* arg0)
{
    D_80105924[arg0->unk6](arg0);
    if (arg0->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
    } else {
        D_8013B8B0 = NULL;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008EA3C(struct MainObj* arg0)
{
    func_80015D60(arg0, 3);
    arg0->unk7C = 0x1E;
    arg0->unk50 = (const u8*)&D_80105360;
    arg0->unk6++;
}

void func_8008EA88(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 4);
        arg0->unk7C = 0xF1;
    }
}

void func_8008EAE4(struct MainObj* arg0)
{
    s16 timer;
    struct ShotObj* shot;

    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 7;
        arg0->unk6 = 0;
        return;
    }
    if ((timer % 10) == 0) {
        func_8001540C(2, 0, arg0);
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x38;
            shot->unk2 = 1;
            shot->x_pos.i.hi = (u16)arg0->x_pos.i.hi + 0x10;
            shot->y_pos.i.hi = (u16)arg0->y_pos.i.hi + 0x10;
            shot->unk7C = WEAPON_OBJECT(arg0);
        }
    }
}

void func_8008EBC0(struct MainObj* arg0)
{
    D_80105934[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
    if (arg0->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
    } else {
        D_8013B8B0 = NULL;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008EC48);

void func_8008ED18(struct MainObj* arg0)
{
    struct MiscObj* miscObj;

    arg0->unk7C--;
    if (arg0->unk7C == 0) {
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    }
    if ((arg0->unk7C % 10) == 0) {
        func_8001540C(2, 0xA, arg0);
        miscObj = find_free_misc_obj();
        if (miscObj != 0) {
            miscObj->active = 0x41;
            miscObj->id = 0x37;
            miscObj->unk2 = 2;
            miscObj->ext.misc_55.owner = arg0;
        }
    }
}

void func_8008EDE8(struct MainObj* arg0)
{
    struct MiscObj* misc;

    g_Player.x_pos.i.hi += 3;
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x5A;
        arg0->unk6++;
    }
    if (arg0->unk7C % 10 == 0) {
        func_8001540C(2, 10, arg0);
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x41;
            misc->id = 0x37;
            misc->unk2 = 2;
            misc->ext.misc_7.position = arg0;
        }
    }
}

void func_8008EED4(struct MainObj* arg0)
{
    g_Player.x_pos.i.hi += 4;
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x5A;
        arg0->unk6++;
    }

    if (arg0->unk7C % 10 == 0) {
        func_8001540C(2, 0xA, arg0);
    }
}

void func_8008EF94(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C - 1;

    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 7;
        arg0->unk6 = 0;
        return;
    }
    if ((timer % 10) == 0) {
        func_8001540C(2, 10, arg0);
    }
}

void func_8008F01C(struct MainObj* arg0)
{
    D_80105940[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
    if (arg0->animation_step.fields.event != 0) {
        D_8013B8B0 = &D_80105374;
        return;
    }
    D_8013B8B0 = NULL;
}

void func_8008F0A4(struct MainObj* arg0)
{
    u8 choice = (u32)(get_random() & 0xFF) % 3;
    switch (choice) {
    case 0:
        func_8008D3B8(arg0, 1);
        break;
    case 1:
        func_8008D3B8(arg0, 2);
        break;
    default:
        func_8008D3B8(arg0, 0);
        break;
    }
    arg0->unk6++;
}

void func_8008F134(struct MainObj* arg0)
{
    if (D_8013B8AC->active == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        D_8013B8A0[0] = 0x1E;
    }
}

void func_8008F16C(struct MainObj* arg0)
{
    D_80105954[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F1A8);

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F3F4);

void func_8008F4BC(struct MainObj* arg0)
{
    s16 timer;
    s8 value;
    s8 delay;

    timer = arg0->unk7E - 1;
    arg0->unk7E = timer;
    if (timer == 0) {
        arg0->unk7C = 0x12C;
        arg0->unk42 ^= 0x8000;
        value = arg0->unk61 - 5;
        arg0->unk61 = value;
        if (value >= 0x1A) {
            arg0->unk61 = 0;
        }
        delay = arg0->unk61;
        if (arg0->unk61 < 5) {
            delay = 5;
        }
        arg0->unk7E = delay;
        arg0->ext.main_74.unk97 = 4;
        arg0->unk5 = 2;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008F578);

void func_8008F6FC(struct MainObj* arg0)
{
    struct EffectObj* effect;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 4;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x2B;
            effect->unk2 = 1;
        }
    }
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008F76C(struct MainObj* arg0)
{
    u16 sound_id;

    if (g_Player.unkC0 != -1) {
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }
    func_8008D764(arg0, 0);
    sound_id = 0x25;
    if (engine_obj.cur_character == 0) {
        sound_id = 0x2C;
    }
    func_8002217C(sound_id, 7, 0);
    arg0->unk5 = 5;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008F7F0(struct MainObj* arg0)
{
    struct EffectObj* effect;

    if (abc_object.unkC == 0) {
        arg0->unk5 = 6;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = -0x7F;
            effect->id = 0x1A;
            effect->x_pos.i.hi = arg0->x_pos.i.hi;
            D_8013B8A8 = OBJECT_HEADER(effect);
            effect->y_pos.i.hi = arg0->y_pos.i.hi;
        }
        func_80015D60(arg0, 0);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8008F884(struct MainObj* arg0)
{
    if (D_8013B8A8->active == 0) {
        func_80036B18();
        engine_obj.character_state.fields.active = 1;
        background_objects[0].unk26 = 0x450;
        background_objects[0].unk24 = 0x480;
        g_Player.unk7A = 0;
        func_800DABE4(8U, 0, 0);
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    if (D_8013B8A8->unk7 == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x40);
    }
}

void func_8008F938(struct MainObj* arg0)
{
    D_80105994[arg0->unk5](arg0);
}

void func_8008F974(struct MainObj* arg0)
{
#define MAIN_74_BOSS_ACTIVE engine_obj.enable_boss

    arg0->on_screen = 0;
    D_801059B0[arg0->state](arg0);
    if (arg0->ext.main_74.unk91 == 0) {
        MAIN_74_BOSS_ACTIVE = 0;
        return;
    }
    MAIN_74_BOSS_ACTIVE = 1;
    if (arg0->ext.main_74.unk91 == 1) {
        arg0->ext.main_74.unk92 = arg0->unk5C;
        return;
    }
    arg0->ext.main_74.unk93 = arg0->unk5C;
}

u8 func_8008FA0C(struct ObjectHeader* arg0, s16 arg1, s16 arg2)
{
    s16 temp_v1;
    s16 temp_a0;

    temp_v1 = arg0->x_pos.i.hi;
    if ((temp_v1 - arg1 >= 0) ? (temp_v1 - arg1 < 3) : (arg1 - temp_v1 < 3)) {
        temp_a0 = arg0->y_pos.i.hi;
        if ((temp_a0 - arg2 >= 0) ? (temp_a0 - arg2 < 3) : (arg2 - temp_a0 < 3)) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_74", func_8008FA88);
