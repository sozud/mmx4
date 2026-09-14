// MainObj, main_object_update_funcs[60]
// 8007501C..8007872C
#include "common.h"

extern void* D_80101B4C[];
extern u8 D_80101B58[];

void func_8007501C(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80101B64[arg0->state](arg0);
}

void func_80075064(struct MainObj* arg0)
{
    D_80101B70[arg0->unk5](arg0);
}

void func_800750A0(struct MainObj* arg0)
{
    if (engine_obj.stage == 7) {
        if (g_Player.x_pos.i.hi >= 0x9E1) {
            return;
        }
        func_80036AE4(0x14, 0);
    } else {
        if (g_Player.y_pos.i.hi < 0x6B0) {
            return;
        }
        func_80036AE4(0x14, 0x40);
    }
    arg0->unk5++;
}

void func_80075128(struct MainObj* arg0)
{
    struct EffectObj* effect = find_free_effect_obj();

    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        arg0->ext.main_60.effect = effect;
    }
    arg0->unk5++;
}

void func_8007517C(struct MainObj* arg0)
{
    if (arg0->ext.main_60.effect->active == 0) {
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800751AC);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075320);

void func_80075630(struct MainObj* arg0)
{
    D_80101BB4[arg0->unk5](arg0);
}

void func_8007566C(struct MainObj* arg0)
{
    func_80015930(2, 0xBC);
    g_Player.unkBA = 0;
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk5++;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 0xB);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075700);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800757F4);

void func_800758FC(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_60.saved_unk5;
}

void func_80075908(struct MainObj* arg0)
{
    D_80101BC0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075944);

void func_800759EC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    CollisionRelated(PLAYER_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 9);
        arg0->unk7C = 0x49;
        arg0->unk6++;
    }
}

void func_80075A54(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 0xBB, arg0);
        func_80028BAC(0x18, 8, 1);
        func_80077D48(ANIMATED_OBJECT(arg0));
        arg0->unk7C = 0x2F;
        arg0->unk6++;
    }
}

void func_80075AD0(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        if (engine_obj.stage == 7) {
            func_8002217C(0xF, 0xFF, ENGINE_UNK2E);
            ENGINE_UNK2E = 1;
        }
        arg0->unk6++;
    }
}

void func_80075B54(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (abc_object.unkC == 0) {
        engine_obj.boss_ptr = arg0;
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        arg0->unk7C = 3;
        arg0->unk6++;
        func_800921E8(6);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075BC4);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075C6C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075D38);

void func_80075DDC(struct MainObj* arg0)
{
    D_80101BE0[arg0->unk6](arg0);
}

void func_80075E18(struct MainObj* arg0)
{
    s32 x_pos;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    x_pos = arg0->x_pos.val;
    arg0->unk15 = (g_Player.x_pos.val >= x_pos) << 6;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80075E78);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007601C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800760C4);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800761A0);

void func_8007624C(struct MainObj* arg0)
{
    D_80101BF4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076288);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076364);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007651C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007662C);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800766FC);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_8007681C);

void func_800768CC(struct MainObj* arg0)
{
    D_80101C0C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076908);

void func_800769FC(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_60.unk94 == 1) {
        arg0->collision_data = (const u16*)D_801060F0;
    } else {
        arg0->collision_data = (const u16*)D_80107B78;
    }
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80076A74(struct MainObj* arg0)
{
    D_80101C14[arg0->unk6](arg0);
}

void func_80076AB0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 3);
    arg0->unk15 = (arg0->x_pos.val <= g_Player.x_pos.val) << 6;
    arg0->unk7C = 0x1F;
    arg0->unk6++;
}

void func_80076B14(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_80077ED0(arg0);
        func_8001540C(2, 0xB6, arg0);
        arg0->unk7C = 0x1C;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076B84);

void func_80076C1C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_80076C70(struct MainObj* arg0)
{
    D_80101C24[arg0->unk6](arg0);
}

void func_80076CAC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 3);
    arg0->unk7C = 0x1C;
    arg0->collision_data = (const u16*)D_80107B78;
    arg0->ext.main_60.unk8D = 0;
    arg0->unk15 = (arg0->ext.main_60.unk8B < 2) << 6;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80076D14);

void func_80076DB0(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_80015D60(arg0, 6);
        arg0->collision_data = (const u16*)D_80107B78;
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    }
}

void func_80076E1C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_8001540C(2, 0xB6, arg0);
        arg0->ext.main_60.unk8E = 1;
        arg0->unk7C = 0x78;
        arg0->unk6++;
    }
}

void func_80076E88(struct MainObj* arg0)
{
    s32 direction;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_60.unk88 == 0) {
        arg0->ext.main_60.unk8E = 0;
        func_80015D60(arg0, 1);
        direction = (arg0->x_pos.val >= g_Player.x_pos.val) << 6;
        arg0->unk15 = direction;
        if (direction == 0) {
            arg0->unk20 = FIXED(-2);
        } else {
            arg0->unk20 = FIXED(2);
        }
        arg0->unk24 = FIXED(3);
        arg0->unk6++;
    }
}

void func_80076F14(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        func_8007856C(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_80076F74(struct MainObj* arg0)
{
    D_80101C3C[arg0->unk6](arg0);
}

void func_80076FB0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (!(arg0->ext.main_60.unk8B & 1)) {
        func_80015D60(arg0, 4);
    } else {
        func_80015D60(arg0, 5);
    }
    arg0->unk7C = 0x63;
    arg0->unk15 = ((arg0->ext.main_60.unk8B >> 1) == 0) << 6;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077028);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800770F0);

void func_800771AC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        func_8007856C(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8007720C(struct MainObj* arg0)
{
    func_80078180(arg0);
    D_80101C4C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077258);

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077318);

void func_80077444(struct MainObj* arg0)
{
    func_800780D4(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0xBE, arg0);
    arg0->unk7C = 0x3C;
    arg0->unk6++;
}

void func_80077490(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 0xBC, arg0);
        arg0->ext.main_60.unk8F = 1;
        arg0->ext.main_60.unk90 = 0x10;
        arg0->unk7C = 0x5A;
        arg0->unk6++;
    }
}

void func_80077504(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        if (--arg0->ext.main_60.unk90 == 0) {
            arg0->unk7C = 0x3C;
            arg0->unk6++;
        } else {
            arg0->unk7C = 0x14;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077580);

void func_80077614(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->ext.main_60.unk90++;
        if (arg0->ext.main_60.unk90 >= 0x10) {
            arg0->unk7C = 0x3C;
            arg0->unk6++;
            return;
        }
        arg0->unk7C = 0x14;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077694);

void func_80077738(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        func_8007856C(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_80077798(struct MainObj* arg0)
{
    D_80101C70[arg0->unk6](arg0);
}

void func_800777D4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    arg0->unk7C = 0x5A;
    arg0->unk6++;
}

void func_8007781C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80077868(struct MainObj* arg0)
{
    D_80101C78[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_800778A4);

void func_80077954(struct MainObj* arg0)
{
    s32 x_vel;
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_80015D60(arg0, 1);
        x_vel = FIXED(2);
        arg0->collision_data = (const u16*)D_80107B78;
        if (arg0->unk15 == 0) {
            x_vel = FIXED(-2);
        }
        arg0->unk20 = x_vel;
        arg0->unk24 = FIXED(3);
        arg0->unk6++;
    }
}

void func_800779D4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if ((func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) && (arg0->ext.main_60.unk88 == 0)) {
        func_8007856C(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_80077A44(struct MainObj* arg0)
{
    D_80101C84[arg0->unk6](arg0);
}

void func_80077A80(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    if (!(arg0->ext.main_60.unk8B & 1)) {
        arg0->unk24 = FIXED(-3);
        arg0->unk6++;
    } else {
        arg0->unk7C = 0xA;
        arg0->unk6 += 2;
    }
    if (arg0->ext.main_60.unk8B < 2) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

void func_80077B0C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    CollisionRelated(PLAYER_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 9);
        arg0->unk7C = 0x1E;
        arg0->unk6++;
    }
}

void func_80077B74(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 3);
        arg0->unk7C = 0x1E;
        arg0->unk6++;
    }
}

void func_80077BD0(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk7C = 0xA;
        func_8001540C(2, 0xB4, arg0);
        func_80078314(arg0);
        arg0->unk6++;
    }
}

void func_80077C40(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x5F;
        arg0->unk6++;
    }
}

void func_80077C74(struct MainObj* arg0)
{
    s32 x_vel;
    s16 timer;

    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer != 0) {
        return;
    }
    func_80015D60(arg0, 1);
    x_vel = FIXED(2);
    if (arg0->unk15 == 0) {
        x_vel = FIXED(-2);
    }
    arg0->unk20 = x_vel;
    arg0->unk24 = FIXED(3);
    arg0->unk6++;
}

void func_80077CE8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        func_8007856C(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_80077D48(struct AnimatedObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 0;
        obj->unk50 = (struct PlayerObj*)arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_80101A6C;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077DF0);

void func_80077ED0(struct MainObj* arg0)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x25;
        shot->unk2 = 0;
        shot->unk7C = WEAPON_OBJECT(arg0);
        shot->unk42 = arg0->unk42;
        shot->animation_table = D_80101A6C;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk40 = arg0->unk40;
        shot->bg_offset = arg0->bg_offset;
        shot->unk16 = 5;
        shot->unk15 = arg0->unk15;
    }
}

void func_80077F60(struct MainObj* arg0, s8 arg1)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x25;
        shot->unk2 = arg1;
        shot->unk7C = (struct WeaponObj*)arg0;
        shot->unk42 = arg0->unk42;
        shot->animation_table = D_80101A6C;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk40 = arg0->unk40;
        shot->bg_offset = arg0->bg_offset;
        shot->unk16 = 5;
        shot->unk15 = arg0->unk15;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80077FFC);

void func_800780D4(struct AnimatedObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 2;
        obj->unk50 = PLAYER_OBJECT(arg0);
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_80101A6C;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80078180);

void func_8007826C(struct PlayerObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 3;
        obj->unk50 = arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_80101A6C;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_60", func_80078314);

void func_8007856C(struct MainObj* arg0)
{
    s32 player_x = g_Player.x_pos.val;

    if (arg0->x_pos.val < player_x) {
        if (func_8002B780() & 1) {
            arg0->ext.main_60.unk8B = 0;
        } else {
            arg0->ext.main_60.unk8B = 1;
        }
    } else {
        if (func_8002B780() & 1) {
            arg0->ext.main_60.unk8B = 2;
        } else {
            arg0->ext.main_60.unk8B = 3;
        }
    }
}

void func_800785E4(struct MainObj* arg0)
{
    u32 idx;
    u8** table;
    u8* weights;
    u8* base;
    u8 i;
    u32 rnd;
    u32 gr;

    idx = arg0->unk5C - 1;
    if ((s32)idx < 0)
        idx = arg0->unk5C + 0xE;
    idx >>= 4;
    idx &= 0xFF;
    table = ((u8**)D_80101B4C)[idx];
    gr = get_random();
    i = 0;
    base = D_80101B58;
    weights = base + idx * 3;
    rnd = gr & 0xF;
    while (i < 3) {
        if (rnd < weights[i]) {
            arg0->ext.main_60.unk84 = table[i];
            return;
        }
        i++;
    }
}

void func_800786AC(void)
{
    u8 clear_value;
    u32 i;
    s32 j;
    u8* dst;

    clear_value = 0;
    for (i = 0; i < 0x20; i++) {
        if ((shot_objects[i].id == 0x25) || ((shot_objects[i].unk2 != 0) && (shot_objects[i].unk2 < 5))) {
            dst = (u8*)&shot_objects[i];
            j = 0x9B;
            do {
                *dst++ = clear_value;
            } while (j-- != 0);
        }
    }
}
