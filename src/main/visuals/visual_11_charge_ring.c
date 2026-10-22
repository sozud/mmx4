// VisualObj, visual_object_update_funcs[11]
// 800B17CC..800B19BC
#include "common.h"
#include "main/visuals/visual_11_charge_ring.h"
#include "main/55C4.h"
#include "main/objects.h"

// charge_ring_state_funcs
extern void (*charge_ring_state_funcs[])(struct VisualObj*);
void charge_ring_init(struct VisualObj*);

void charge_ring_despawn(struct VisualObj*);
#include "weapon_resources.h"

void charge_ring_update(struct VisualObj* arg0)
{
    charge_ring_state_funcs[arg0->state](arg0);
}

void charge_ring_init(struct VisualObj* arg0)
{
    arg0->unk15 = arg0->unk50->unk15;
    set_animation(arg0, arg0->unk2);
    arg0->on_screen = 1;
    arg0->state++;
    update_on_screen(arg0, 0x50, 0x50);
}

// charge_ring_main

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B1864(struct VisualObj* self);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B1864(struct VisualObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk50;
    s32 variant = parent->ext.main_14.visual_variant;

    if (parent->active != 0)
        parent->id = 0xE;
    else
        self->state++;

    if (variant == 0xFF || parent->state == 2) {
        self->state++;
        return;
    }
    if (variant != self->unk2 && !(variant == 6 && parent->unk5 < 3)) {
        self->unk2 = variant;
        set_animation(self, (s8)variant);
    }
    animate_object(ANIMATED_OBJECT(self));
    self->x_pos.u.hi = parent->x_pos.u.hi;
    self->y_pos.u.hi = parent->y_pos.u.hi;
    if (parent->unk5 == 1)
        self->y_pos.u.hi -= 5;
    else if (parent->unk5 != 0) {
        self->x_pos.u.hi -= 2;
        self->y_pos.u.hi -= 10;
    }
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}
#else
INCLUDE_ASM("main/nonmatchings/visuals/visual_11_charge_ring", func_800B1864);
#endif

void charge_ring_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*charge_ring_state_funcs[])(struct VisualObj*) = {
    charge_ring_init,
    func_800B1864,
    charge_ring_despawn,
};
