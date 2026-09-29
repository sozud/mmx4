// ItemObj, item_object_update_funcs[2]
// 800BF730..800C0404
#include "common.h"

void pickup_update(struct ItemObj* arg0)
{
    pickup_state_funcs[arg0->state](arg0);
}

// pickup_init
INCLUDE_ASM("main/nonmatchings/items/item_02", func_800BF76C);

void pickup_main(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->unk67 != 0) {
        move_with_gravity((struct AnimatedObj*)arg0);
        CollisionRelated((struct PlayerObj*)arg0);
        if (arg0->unk70 & 8) {
            if (arg0->unk6 == 0) {
                arg0->unk6 = 1;
                if (arg0->y_vel.val >= 0) {
                    arg0->y_vel.val = arg0->y_vel.val >> 1;
                } else {
                    arg0->y_vel.val = -arg0->y_vel.val >> 1;
                }
                arg0->unk2C = 0x8000;
            } else {
                arg0->unk6 = 0;
                arg0->unk67 = 0;
            }
        }
    } else {
        CollisionRelated((struct PlayerObj*)arg0);
        if (!(arg0->unk70 & 8)) {
            arg0->unk2C = 0x8000;
            arg0->unk6 = 0;
            arg0->y_vel.val = 0;
            arg0->unk67 = 1;
        }
        animate_object(arg0);
    }
    if (arg0->backref == NULL) {
        if (--arg0->ext.item_2.unk82 == 0) {
            arg0->state = 3;
            return;
        }
    }
    func_800C00BC(arg0);
    if (func_8002B160(arg0) != 0) {
        if (arg0->backref != NULL) {
            despawn_object(OBJECT_HEADER(arg0));
        } else {
            arg0->state = 3;
            arg0->unk5 = 0;
        }
    } else {
        arg0->on_screen = 0;
        if ((arg0->ext.item_2.unk82 >= 0x3C) || !(D_80141BD8.unk0 & 1)) {
            is_on_screen((struct BaseObj*)arg0);
        }
    }
}

extern void func_800BFBD0(struct ItemObj* arg0);

void pickup_collected(struct ItemObj* arg0)
{
    arg0->on_screen = 0;
    func_800BFBD0(arg0);
}

void pickup_despawn(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

// pickup_refill
INCLUDE_ASM("main/nonmatchings/items/item_02", func_800BFBD0);

// pickup_collect_weapon_energy
INCLUDE_ASM("main/nonmatchings/items/item_02", func_800BFCC0);

void pickup_collect_health(struct ItemObj* arg0, s8 arg1, s32 arg2)
{
    s32 player_status;
    u8 player_health;
    u8 charge;
    s8 value;

    player_health = g_Player.hp;
    player_status = player_health & 0x80;
    if ((player_health & 0x7F) < engine_obj.unk46) {
        set_objects_frozen(1);
        arg0->ext.item_2.unk80 = arg1;
        arg0->ext.item_2.unk81 = 2;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->active |= 8;
    } else {
        arg0->state = 3;
    }

    player_health = g_Player.hp;
    if ((player_health & 0x7F) >= engine_obj.unk46) {
        g_Player.hp = engine_obj.unk46 | player_status;
    }

    charge = g_Player.weapon_energy[0] + arg1;
    g_Player.weapon_energy[0] = charge;
    if ((s8)charge >= 0x31) {
        g_Player.weapon_energy[0] = 0x30;
    }

    for (arg1 = 0; arg1 < 2; arg1++) {
        if (engine_obj.unk5A & (0x1000 << arg1)) {
            value = engine_obj.unk5C[arg1] & 0x7F;
            if (value < 0x20) {
                value += arg2;
                if (value >= 0x20) {
                    value = 0x20;
                    func_8001540C(0, 0x18, 0);
                } else {
                    func_8001540C(0, 0x17, 0);
                }
                value |= 0x80;
                engine_obj.unk5C[arg1] = value;
                return;
            }
        }
    }
}
// pickup_check_collect
INCLUDE_ASM("main/nonmatchings/items/item_02", func_800C00BC);

void set_objects_frozen(s8 arg0)
{
    engine_obj.unk10 = arg0;
    engine_obj.unk11 = arg0;
    engine_obj.unk12 = arg0;
    engine_obj.unk13 = arg0;
    engine_obj.unk14 = arg0;
    engine_obj.unk15 = arg0;
    engine_obj.unk16 = arg0;
    engine_obj.unk17 = arg0;
}

void (*pickup_state_funcs[])(struct ItemObj*) = {
    func_800BF76C,
    pickup_main,
    pickup_collected,
    pickup_despawn,
};
