// MainObj, main_object_update_funcs[43]
// 800631C8..80065930
#include "common.h"

void func_800643B0(struct MainObj* arg0);
void func_8006458C(struct MainObj* arg0);

void func_800631C8(struct MainObj* arg0)
{
    if (arg0->unk2 == 0) {
        D_800FF6E4[arg0->state](arg0);
    } else {
        D_800FF6F0[arg0->state](arg0);
    }
}

void func_80063234(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FF6FC[arg0->unk5](arg0);
    if (arg0->unk5 >= 2) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_800632A4(struct MainObj* arg0)
{
    struct EffectObj* effect;

    if (g_Player.unkC4 == 0) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            arg0->ext.main_43.effect = effect;
        }
        func_80036AE4(0x14, 0x40);
        D_800FF6E0 = background_objects[0].unk26;
        D_800FF6E2 = background_objects[0].unk2A;
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063334);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006346C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063600);

void func_8006364C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 5;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = FIXED(-8);
        arg0->unk2C = 0;
        func_80015D60(arg0, 0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800636A0);

void func_800637A8(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk5 = 7;
        if (engine_obj.stage == 1) {
            ((void (*)(u16, u8, s8))func_8002217C)(8, 0xFF, ENGINE_UNK2E);
            ENGINE_UNK2E = 1;
        }
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063814);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063854);

void func_80063914(struct MainObj* arg0)
{
    if (arg0->on_screen == 0) {
        arg0->state = 1;
        arg0->unk5 = 2;
        arg0->unk61 = 0;
        return;
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0x70, arg0);
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006398C);

void func_80063AE4(struct MainObj* arg0)
{
    D_800FF750[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063B20);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063DD8);

void func_80063F80(struct MainObj* arg0)
{
    D_800FF75C[arg0->unk6](arg0);
}

void func_80063FBC(struct MainObj* arg0)
{
    arg0->unk6 = 1;
    func_80015D60(arg0, 3);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063FE4);

void func_800640B4(struct MainObj* arg0)
{
    D_800FF768[arg0->unk6](arg0);
}

void func_800640F0(struct MainObj* arg0)
{
    arg0->unk6 = 1;
    arg0->ext.main_43.unk93 = 0;
    arg0->ext.main_43.animation_set = D_800FF774[get_random() & 0xF];
    func_80065268(arg0);
    arg0->ext.main_43.animation_index = 0;
    arg0->ext.main_43.animation_length = 7;
    func_800652C8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064154);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064338);

void func_80064360(struct MainObj* arg0)
{
    if ((arg0->ext.main_43.unk94 == 0) && (arg0->ext.main_43.unk92 != 0)) {
        func_8006458C(arg0);
    } else {
        func_800643B0(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800643B0);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006458C);

void func_800646B0(struct MainObj* arg0)
{
    D_800FF784[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800646EC);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800648D0);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800649C0);

void func_80064AE8(struct MainObj* arg0)
{
    D_800FF790[arg0->unk6](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

void func_80064B38(struct MainObj* arg0)
{
    arg0->unk6 = 1;
    arg0->unk24 = FIXED(4);
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = FIXED(0.25);
    func_80015D60(arg0, 0xD);
    arg0->unk68 = &D_800FF5B0;
    arg0->collision_data = (const u16*)D_801060F0;
    arg0->ext.main_43.unk95 = 1;
}

void func_80064BA8(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6 = 2;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.5);
        func_80015D60(arg0, 0xE);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_80064C0C(struct MainObj* arg0)
{
    if (arg0->unk70 & 8) {
        arg0->unk6 = 3;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        func_80015D60(arg0, 0xF);
        arg0->unk68 = NULL;
        func_8001540C(2, 0x74, arg0);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_80064C84(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6 = 4;
        func_80015D60(arg0, 0x10);
    } else if (arg0->animation_step.fields.event != 0) {
        arg0->unk5C -= 4;
        arg0->animation_step.fields.event = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064CF4);

void func_80064DC8(struct MainObj* arg0)
{
    if (arg0->ext.main_43.unk88 == 0 && arg0->state < 2 && arg0->unk5 == 2 && (*(u32*)&arg0->state & 0xFFFF0000) == 0x02010000 && arg0->unk5C < 0x18) {
        arg0->unk5 = 6;
        arg0->ext.main_43.unk88 = 1;
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->ext.main_43.unk95 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064E58);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064F24);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064FD8);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065088);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065168);

void func_80065268(struct MainObj* arg0)
{
    arg0->unk7C = D_800FF7A4[(arg0->unk5C & 0x7F) >> 3];
}

void func_8006528C(struct MainObj* arg0)
{
    if (arg0->ext.main_43.unk90 == 0) {
        arg0->ext.main_43.unk90 = D_800FF7A8[(arg0->unk5C & 0x7F) >> 3];
    }
}

void func_800652C8(struct MainObj* arg0)
{
    u8 animation_id;
    animation_id = D_800FF6C8[arg0->ext.main_43.animation_set]
                             [arg0->ext.main_43.animation_index];
    arg0->ext.main_43.animation_id = animation_id;
    func_80015D60(arg0, animation_id);
}

void func_8006530C(struct MainObj* arg0)
{
    arg0->unk5 = 1;
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->ext.main_43.unk8A = 0x19;
    arg0->unk42 &= 0x7FFF;
    func_80036AE4(0x14, g_Player.unk15);
    func_80015D60(arg0, 0x22);
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006537C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065458);

void func_80065538(struct MainObj* arg0)
{
    D_800FF7AC[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065574);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006565C);

void func_80065704(struct MainObj* arg0)
{
    if (arg0->unk70 & 3) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
    }
    if (arg0->unk70 & 8) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        func_80015D60(arg0, 0x1C);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065794);

void func_80065898(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk24 = FIXED(1.5);
        arg0->unk6 = 1;
        func_80015D60(arg0, 0x1E);
        return;
    }
    if (arg0->on_screen == 0) {
        arg0->state = 2;
    }
    func_80015DC8(arg0);
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_80065910(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
