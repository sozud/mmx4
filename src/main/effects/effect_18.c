// EffectObj, effect_object_update_funcs[18]
// 800B9690..800B9940
#include "common.h"

void func_800B9690(struct EffectObj* arg0)
{
    D_8010B7A8[arg0->state](arg0);
}

void func_800B96CC(struct EffectObj* arg0)
{
    arg0->state++;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_18", func_800B96E0);

void func_800B97B0(struct EffectObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800B97D0(void)
{
    u32 i;
    struct MainObj* p1;
    struct MiscObj* p2;
    struct WeaponObj* p3;
    struct ShotObj* p4;
    struct VisualObj* p5;

    p1 = main_objects;
    for (i = 0; i < COUNT(main_objects); p1++, i++) {
        if (p1->active != 0) {
            p1->y_pos.val = 0x8000000 - p1->y_pos.val;
        }
    }
    p2 = misc_objects;
    for (i = 0; i < COUNT(misc_objects); p2++, i++) {
        if (p2->active != 0) {
            p2->y_pos.val = 0x8000000 - p2->y_pos.val;
        }
    }
    p3 = weapon_objects;
    for (i = 0; i < COUNT(weapon_objects); p3++, i++) {
        if (p3->active != 0) {
            p3->y_pos.val = 0x8000000 - p3->y_pos.val;
        }
    }
    p4 = shot_objects;
    for (i = 0; i < COUNT(shot_objects); p4++, i++) {
        if (p4->active != 0) {
            p4->y_pos.val = 0x8000000 - p4->y_pos.val;
        }
    }
    p5 = visual_objects;
    for (i = 0; i < COUNT(visual_objects); p5++, i++) {
        if (p5->active != 0) {
            p5->y_pos.val = 0x8000000 - p5->y_pos.val;
        }
    }
}

void (*D_8010B7A8[])(struct EffectObj*) = {
    func_800B96CC,
    func_800B96E0,
    func_800B97B0,
};
