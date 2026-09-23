// MainObj, main_object_update_funcs[57]
// 80072194..800743FC
#include "common.h"

extern void* D_80100EB0[];
extern u8 D_80100EBC[];

void func_800742AC(struct MainObj* arg0);

void func_80072194(struct MainObj* arg0)
{
    D_80101414[arg0->state](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
    if (!(g_Player.unk5C & 0x7F)) {
        func_80074368(0x38);
    }
}

void func_80072204(struct MainObj* arg0)
{
    D_80101420[arg0->unk5](arg0);
}

void func_80072240(struct MainObj* arg0)
{
    struct EffectObj* effect = find_free_effect_obj();

    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        arg0->ext.main_57.effect = effect;
        func_80036AE4(0x14, 0x40);
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800722A0);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072418);

void func_800725DC(struct MainObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800725EC(struct BarObj* arg0)
{
    D_80101458[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072628);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800726CC);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800727C0);

void func_800728C8(struct MainObj* arg0)
{
    D_80101464[arg0->unk6](arg0);
}

void func_80072904(struct MainObj* arg0)
{
    s32 x_vel = FIXED(-0.75);

    arg0->unk6++;
    if (arg0->unk15 != 0) {
        x_vel = FIXED(0.75);
    }
    arg0->unk20 = x_vel;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    engine_obj.enable_boss = 1;
    func_80015D60(arg0, 0x26);
}

void func_80072960(struct MainObj* arg0)
{
    s16 temp_a0;
    s32 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_80028BAC(0x18, 2, 1);
        func_8001540C(2, 0x91, arg0);
    }

    temp_a0 = arg0->x_pos.i.hi;
    temp_v0 = temp_a0 - g_Player.x_pos.i.hi;
    if (temp_v0 >= 0) {
        if (temp_v0 < 0xC1) {
            goto update;
        }
        return;
    }

    if (g_Player.x_pos.i.hi - temp_a0 < 0xC1) {
    update:
        arg0->unk20 = 0;
        func_80015D60(arg0, 1);
        arg0->unk6++;
    }
}

void func_80072A14(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 0x4);
        arg0->unk7C = 0x50;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072A84);

void func_80072BCC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (abc_object.unkC == 0) {
        arg0->unk7E = 3;
        arg0->unk6++;
        func_800921E8(1);
    }
}

void func_80072C20(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (func_8009227C() != 0) {
        return;
    }
    if (--arg0->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        arg0->unk7E = 3;
    }
    if (++arg0->unk5C == 0x30) {
        func_800742AC(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk7E = 0;
        func_80036B18();
    }
}

void func_80072CC4(struct MainObj* arg0)
{
    D_8010147C[arg0->unk6](arg0);
    func_8007427C(arg0);
}

void func_80072D14(struct MainObj* self)
{
    u8 value;

    if (*self->ext.main_57.script == 0xFF) {
        func_800742AC(self);
    }

    value = *self->ext.main_57.script;
    if ((value & 0xFF) == 3) {
        func_80015D60(self, 0x1A);
        self->unk7C = 0x1E;
        self->unk6++;
    } else {
        self->unk5 = value;
        self->unk6 = 0;
    }

    self->ext.main_57.script++;
}

void func_80072DB0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C <= 0) {
        arg0->unk6 = 0;
    }
}

void func_80072DF8(struct MainObj* arg0)
{
    D_80101484[arg0->unk6](arg0);
}

void func_80072E34(struct MainObj* arg0)
{
    s32 var_v1;

    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk6 = (u8)arg0->unk6 + 1;
    if (arg0->ext.main_57.unk92 != 0) {
        func_80015D60(arg0, 0x17);
        var_v1 = -0x18000;
        if (arg0->unk15 != 0) {
            var_v1 = 0x18000;
        }
        arg0->unk54 = (u8*)&D_80101340;
        arg0->unk20 = var_v1;
        arg0->unk50 = (u8*)&D_80101348;
        func_8001540C(2, 0x93, arg0);
        arg0->unk6 = 3;
        return;
    }
    arg0->unk54 = (u8*)&D_8010133C;
    arg0->unk50 = (u8*)&D_80101344;
    func_80015D60(arg0, 1);
}

void func_80072EF8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, arg0);
    }
    if (arg0->animation_step.fields.event == 2) {
        func_80015D60(arg0, 2);
        arg0->unk6++;
    }
}

void func_80072F68(struct MainObj* self)
{
    s32 value;

    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        value = FIXED(-3);
        if (self->unk15 != 0) {
            value = FIXED(3);
        }
        self->unk54 = (const u8*)&D_80101340;
        self->unk20 = value;
        self->unk50 = (const u8*)&D_80101348;
        func_8001540C(2, 0x93, self);
        self->unk6++;
    }
}

void func_80072FF0(struct MainObj* arg0)
{
    s32 mask;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    mask = 2;
    if (arg0->unk15 != 0) {
        mask = 1;
    }
    if (mask & arg0->unk70) {
        func_80074368(0x39);
        func_80028B68(0x1E, 4, 1);
        func_8001540C(2, 0x90, arg0);
        arg0->unk7C = 0x28;
        arg0->unk6++;
    }
}

void func_80073084(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C <= 0) {
        arg0->unk54 = (const u8*)&D_8010133C;
        arg0->unk50 = (const u8*)&D_80101344;
        func_80074368(0x38);
        func_80015D60(arg0, 3);
        arg0->unk6++;
    }
}

void func_80073100(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        if (arg0->ext.main_57.unk92 == 0) {
            func_80015D60(arg0, 0);
        }
        func_8007427C(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80073164(struct MainObj* arg0)
{
    D_8010149C[arg0->unk6](arg0);
}

void func_800731A0(struct MainObj* arg0)
{
    s32 x_vel = FIXED(-3);

    if (arg0->unk15 != 0) {
        x_vel = FIXED(3);
    }
    arg0->unk24 = FIXED(6.5);
    arg0->unk2C = FIXED(0.2578125);
    arg0->unk54 = (const u8*)&D_8010133C;
    arg0->unk20 = x_vel;
    arg0->unk28 = 0;
    arg0->unk50 = (const u8*)&D_80101344;
    func_80015D60(arg0, 1);
    arg0->ext.main_57.unk90 = 0;
    arg0->unk6++;
}

void func_80073228(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 2);
        arg0->unk6++;
    }
}

void func_80073294(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk54 = (const u8*)&D_80101340;
        arg0->unk50 = (const u8*)&D_80101348;
        if (arg0->unk70 & 8) {
            arg0->ext.main_57.unk90 = 1;
            arg0->unk67 = 1;
        }
        arg0->unk6++;
    }
}

void func_8007330C(struct MainObj* arg0)
{
    s32 side_mask;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk67 == 1 && arg0->unk24 < 0) {
        arg0->unk67 = -1;
    }
    if (arg0->unk67 == -1 && (arg0->unk70 & 8)) {
        func_8001540C(2, 0x90, arg0);
        func_8001540C(2, 0x93, arg0);
        func_80028BAC(0x18, 3, 1);
        arg0->unk67 = 0;
    }
    if (arg0->unk67 == 0) {
        side_mask = 2;
        if (arg0->unk15 != 0) {
            side_mask = 1;
        }
        if (side_mask & arg0->unk70) {
            func_80074368(0x39);
            func_8001540C(2, 0x90, arg0);
            func_80028B68(0x1E, 4, 1);
            arg0->unk7C = 0x28;
            arg0->unk6++;
        }
    }
}

void func_8007342C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C <= 0) {
        arg0->unk54 = (const u8*)&D_8010133C;
        arg0->unk50 = (const u8*)&D_80101344;
        func_80074368(0x38);
        func_80015D60(arg0, 3);
        arg0->unk6++;
    }
}

void func_800734A8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 0);
        func_8007427C(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->ext.main_57.unk90 = 0;
    }
}

void func_80073500(struct MainObj* arg0)
{
    D_801014B4[arg0->unk6](arg0);
}

void func_8007353C(struct MainObj* arg0)
{
    s32 x_vel = FIXED(-0.75);

    arg0->unk6++;
    if (arg0->unk15 != 0) {
        x_vel = FIXED(0.75);
    }
    arg0->unk20 = x_vel;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    func_80015D60(arg0, 6);
    arg0->unk54 = (const u8*)&D_8010133C;
    arg0->unk50 = (const u8*)&D_80101344;
    arg0->unk7C = 0x80;
}

void func_800735BC(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_8001540C(2, 0x92, arg0);
        func_80028BAC(0x18, 3, 1);
    }
    if (arg0->animation_step.fields.event != 2) {
        func_8002B718(MOVING_OBJECT(arg0));
    }
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer <= 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80073650(struct MainObj* arg0)
{
    D_801014BC[arg0->unk6](arg0);
}

void func_8007368C(struct MainObj* arg0)
{
    func_80015D60(arg0, 7);
    arg0->unk54 = (const u8*)&D_8010133C;
    arg0->unk50 = (const u8*)&D_80101344;
    arg0->unk6++;
}

void func_800736DC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->ext.main_57.unk90 = 0;
        if (arg0->unk5C >= 0x18) {
            arg0->ext.main_57.unk91 = 4;
        } else {
            arg0->ext.main_57.unk91 = 8;
        }
        arg0->unk7C = 0;
        arg0->unk6++;
    }
}

void func_80073748(struct MainObj* arg0)
{
    u8 i;
    struct ShotObj* shot;

    i = 0;
    do {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x23;
            shot->unk2 = i + arg0->unk7C;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk7 = arg0->ext.main_57.unk91;
            arg0->ext.main_57.shot = shot;
        }
        i++;
    } while (i < 2);

    arg0->unk7E = 0x20;
    arg0->unk7C += 2;
    arg0->unk6++;
}

void func_800737FC(struct MainObj* arg0)
{
    if (arg0->unk7E != 0) {
        arg0->unk7E--;
        return;
    }
    if (arg0->unk7C == arg0->ext.main_57.unk91) {
        func_80015D60(arg0, 1);
        arg0->unk7C = 0;
        arg0->unk6++;
    } else {
        arg0->unk6--;
    }
}

void func_80073878(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, arg0);
    }
    if (arg0->animation_step.fields.event == 2) {
        func_80015D60(arg0, 0x1A);
        arg0->unk7C = 0x40;
        arg0->unk6++;
    }
}

void func_800738EC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80073938(struct MainObj* arg0)
{
    D_801014D4[arg0->unk6](arg0);
}

void func_80073974(struct MainObj* arg0)
{
    func_80015D60(arg0, 4);
    arg0->unk54 = (const u8*)&D_8010133C;
    arg0->unk50 = (const u8*)&D_80101344;
    arg0->unk7C = 0x80;
    arg0->unk7E = 0x18;
    arg0->unk6++;
}

void func_800739D4(struct MainObj* arg0)
{
    struct VisualObj* vobj;
    struct ShotObj* sobj;

    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (--arg0->unk7E == 0) {
        func_8001540C(2, 0x94, arg0);
        arg0->unk7E = 0x18;
    }

    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x30;
        arg0->unk6++;
    }

    if (arg0->animation_step.fields.event == 2) {
        vobj = find_free_visual_obj();
        if (vobj != NULL) {
            vobj->active = 0x41;
            vobj->id = 0x18;
            vobj->unk2 = 0x10;
            vobj->unk15 = arg0->unk15;
            vobj->unk50 = arg0;
            vobj->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 ? 0x15 : -0x15);
            vobj->y_pos.i.hi = arg0->y_pos.i.hi;
        }
    }

    if (arg0->unk7C == 0x40) {
        sobj = find_free_shot_obj();
        if (sobj != NULL) {
            sobj->active = 0x41;
            sobj->id = 0x23;
            sobj->unk2 = 0x10;
            sobj->unk7C = arg0;
            arg0->ext.main_57.shot = sobj;
        }
    }
}

void func_80073B00(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 1);
        arg0->unk6++;
    }
}

void func_80073B58(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        arg0->ext.main_57.shot->unk8C.word = arg0->animation_step.fields.event;
        func_800C813C(0xA, D_801013BC, arg0->ext.main_57.shot);
    }
    if (arg0->animation_step.fields.event == 2) {
        func_80015D60(arg0, 0);
        arg0->unk7C = 0x20;
        arg0->unk6++;
    }
}

void func_80073BDC(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80073C08(struct MainObj* arg0)
{
    D_801014E8[arg0->unk6](arg0);
}

void func_80073C44(struct MainObj* arg0)
{
    func_80015D60(arg0, 0x16);
    arg0->unk54 = (const u8*)&D_8010133C;
    arg0->unk50 = (const u8*)&D_80101344;
    arg0->unk7C = 0x100;
    arg0->unk7E = 0x18;
    arg0->unk6++;
}

void func_80073CA4(struct MainObj* arg0)
{
    struct VisualObj* vobj;
    struct ShotObj* sobj;

    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (--arg0->unk7E == 0) {
        func_8001540C(2, 0x94, arg0);
        arg0->unk7E = 0x18;
    }

    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 0x16);
        arg0->unk7C = 0x80;
        arg0->unk6++;
    }

    if (arg0->animation_step.fields.event == 2) {
        vobj = find_free_visual_obj();
        if (vobj != NULL) {
            vobj->active = 0x41;
            vobj->id = 0x18;
            vobj->unk2 = 0x30;
            vobj->unk15 = arg0->unk15;
            vobj->unk50 = arg0;
            vobj->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 ? 0x15 : -0x15);
            vobj->y_pos.i.hi = arg0->y_pos.i.hi;
        }
    }

    if (arg0->unk7C == 0x40) {
        sobj = find_free_shot_obj();
        if (sobj != NULL) {
            sobj->active = 0x41;
            sobj->id = 0x23;
            sobj->unk2 = 0x20;
            sobj->unk7C = arg0;
            arg0->ext.main_57.shot = sobj;
        }
    }
}

void func_80073DDC(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x60;
        arg0->unk6++;
    }
}

void func_80073E10(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80073E3C(struct MainObj* arg0)
{
}

void func_80073E44(struct MainObj* arg0)
{
    D_801014FC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073E80);

void func_80073F90(struct MainObj* arg0)
{
    struct VisualObj* temp_v0;

    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 < 0) {
        arg0->unk67 = -1;
    }
    if ((arg0->unk67 == -1) && (arg0->unk70 & 8)) {
        func_80015D60(arg0, 0x14);
        if (arg0->ext.main_57.unk92 == 0) {
            temp_v0 = find_free_visual_obj();
            if (temp_v0 != 0) {
                temp_v0->active = 0x41;
                temp_v0->id = 0x18;
                temp_v0->unk2 = 0x50;
                temp_v0->unk15 = arg0->unk15;
                temp_v0->unk50 = PLAYER_OBJECT(arg0);
                arg0->ext.main_57.unk92 = 1;
            }
        }
        arg0->unk67 = 0;
        func_80028BAC(0x10, 3, 1);
        arg0->unk6++;
    }
}

void func_80074068(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->unk70 & 3) {
        func_80028B68(0x10, 3, 1);
        arg0->unk7C = 0x20;
        arg0->unk6++;
    }
}

void func_800740CC(struct MainObj* arg0)
{
    if (--arg0->unk7C != 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }
    if (arg0->unk5C >= 0x18) {
        arg0->ext.main_57.script = D_80100E78;
    } else {
        arg0->ext.main_57.script = D_80100E7C;
    }
    arg0->unk5 = 3;
    arg0->unk6 = 0;
    arg0->ext.main_57.unk93 = 0;
    arg0->ext.main_57.unk94 = 1;
}

void func_80074158(struct MainObj* arg0)
{
    D_8010150C[arg0->unk6](arg0);
}

void func_80074194(struct MainObj* arg0)
{
    struct VisualObj* visual;

    arg0->collision_data = (const u16*)D_801060F0;
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0x18;
        visual->unk2 = 0x20;
        visual->unk15 = arg0->unk15;
        visual->unk50 = PLAYER_OBJECT(arg0);
        visual->x_pos.u.hi = arg0->x_pos.u.hi;
        visual->y_pos.u.hi = arg0->y_pos.u.hi;
        func_80015D60(arg0, 0x19);
        arg0->unk6++;
    }
}

void func_80074220(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->collision_data = (const u16*)D_80107A78;
        arg0->ext.main_57.unk94 = 0;
        arg0->ext.main_57.unk92 = 0;
        arg0->ext.main_57.unk95 = 0;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_8007427C(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

void func_800742AC(struct MainObj* arg0)
{
    u32 byte_offset;
    u8** choices;
    u8 i;
    u32 rnd;
    u32 gr;

    byte_offset = arg0->unk5C - 1;
    if ((s32)byte_offset < 0) {
        byte_offset = arg0->unk5C + 0xE;
    }
    byte_offset = (byte_offset >> 2);
    byte_offset &= 0x3FC;
    choices = D_80100EB0[byte_offset / sizeof(*D_80100EB0)];
    gr = get_random();
    i = 0;
    byte_offset += (u32)D_80100EBC;
    rnd = gr & 0xF;
    while (i < 4) {
        if (rnd < ((u8*)byte_offset)[i]) {
            arg0->ext.main_57.script = choices[i];
            return;
        }
        i++;
    }
}

void func_80074368(s32 arg0)
{
    u16* list;
    u32* attrs;

    list = D_801013C8;
    if (engine_obj.stage == 0xC) {
        list = D_801013EC;
    }
    while (*list != 0) {
        attrs = SP_BG_TILE_ATTRS;
        attrs[*list] &= ~0xFF;
        attrs[*list] |= arg0;
        list++;
    }
}
