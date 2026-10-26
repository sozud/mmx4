// VisualObj, visual_object_update_funcs[16]
// 800B1EA4..800B2090
#include "common.h"
#include "main/visuals/visual_16_enemy_charge_glow.h"
#include "main/55C4.h"
#include "main/objects.h"

// enemy_charge_glow_state_funcs
extern void (*enemy_charge_glow_state_funcs[])(struct VisualObj*);
void enemy_charge_glow_init(struct VisualObj*);

void enemy_charge_glow_despawn(struct VisualObj*);
#include "weapon_resources.h"

void enemy_charge_glow_update(struct VisualObj* arg0)
{
    enemy_charge_glow_state_funcs[arg0->state](arg0);
}

void enemy_charge_glow_init(struct VisualObj* arg0)
{
    struct PlayerObj* owner;

    if (arg0->unk2 == 0) {
        owner = arg0->unk50;
        arg0->unk15 = owner->unk15;
        if (owner->id == 0x26) {
            set_animation(arg0, 0x14);
        } else {
            set_animation(arg0, 8);
        }
    } else {
        arg0->unk15 = arg0->unk50->unk15;
        set_animation(arg0, 0xD);
    }
    arg0->on_screen = 1;
    arg0->state = 1;
    arg0->unk42 &= 0x7FFF;
}

// enemy_charge_glow_main

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B1F78(struct VisualObj* arg0);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/visuals/visual_16_enemy_charge_glow", func_800B1F78);
#else
void func_800B1F78(struct VisualObj* arg0)
{
    struct MainObj* owner;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 == 0) {
        do {
            owner = (struct MainObj*)arg0->unk50;
            if (owner->ext.main_38.unk88 == 1 && owner->id == 0x26)
                set_animation(arg0, 0x13);
            if (owner->ext.main_38.unk88 == 2 || owner->unk5 != 3)
                arg0->state = 2;
        } while (0);
        update_on_screen(BASE_OBJECT(arg0), 0x50, 0x50);
        return;
    }
    shot = (struct ShotObj*)arg0->unk50;
    if (shot->active == 0 || shot->unk8C.word != 0)
        arg0->state = 2;
    arg0->x_pos.i.hi = shot->x_pos.i.hi;
    arg0->y_pos.i.hi = shot->y_pos.i.hi;
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
}
#endif

void enemy_charge_glow_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*enemy_charge_glow_state_funcs[])(struct VisualObj*) = {
    enemy_charge_glow_init,
    func_800B1F78,
    enemy_charge_glow_despawn,
};
