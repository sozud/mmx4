// MiscObj, misc_object_update_funcs[38]
// 800CF4B8..800CF790
#include "common.h"
#include "main/misc/misc_38_dragoon_flame.h"
#include "main/55C4.h"
#include "main/objects.h"

// dragoon_flame_state_funcs
extern void (*dragoon_flame_state_funcs[])(struct MiscObj*);

void dragoon_flame_burn(struct MiscObj*);
void dragoon_flame_despawn(struct MiscObj*);

void dragoon_flame_attached(struct MiscObj*);
#include "weapon_resources.h"

// dragoon_flame_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CF4B8(struct MiscObj* arg0);
void func_800CF660(struct MiscObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CF4B8(struct MiscObj* arg0)
{
    struct MainObj* source = arg0->ext.misc_7.position;

    arg0->x_pos.val = source->x_pos.val;
    arg0->y_pos.val = source->y_pos.val;
    arg0->unk40 = source->unk40;
    arg0->unk42 = source->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)source->animation_table;
    arg0->unk3C = (void*)source->sprite_frames;
    arg0->unk15 = 0;
    arg0->bg_offset = source->bg_offset;
    switch ((u8)arg0->unk2) {
    case 2:
        set_animation(arg0, 0x18);
        arg0->unk16 = VISUAL_SATURN_LAYER(7);
        arg0->state = 1;
        break;
    case 3:
        set_animation(arg0, 0x17);
        arg0->unk16 = VISUAL_SATURN_LAYER(4);
        arg0->state = 1;
        break;
    case 4:
        set_animation(arg0, 0xE);
        arg0->unk16 = VISUAL_SATURN_LAYER(4);
        arg0->state = 4;
        break;
    case 5:
        set_animation(arg0, 0x15);
        arg0->unk16 = VISUAL_SATURN_LAYER(4);
        arg0->state = 4;
        break;
    default:
        set_animation(arg0, 0x19);
        arg0->unk16 = VISUAL_SATURN_LAYER(4);
        arg0->state = 3;
        break;
    }
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_38_dragoon_flame", func_800CF4B8);
#endif

void dragoon_flame_burn(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->state++;
    }
}

void dragoon_flame_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

// dragoon_flame_attach_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CF660(struct MiscObj* arg0)
{
    struct MainObj* source = arg0->ext.misc_7.position;

    arg0->x_pos.val = source->x_pos.val;
    arg0->y_pos.val = source->y_pos.val;
    animate_object(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (source->air_state == 0) {
        set_animation(arg0, 0x1A);
        arg0->state -= 2;
    } else if (arg0->animation_step.fields.relative_step < 0 && arg0->unk2 != 0) {
        arg0->state--;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_38_dragoon_flame", func_800CF660);
#endif

void dragoon_flame_attached(struct MiscObj* self)
{
    struct ObjectHeader* target = self->ext.pointer.unk50;
    self->x_pos.val = target->x_pos.val;
    self->y_pos.val = target->y_pos.val;
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void dragoon_flame_update(struct MiscObj* self)
{
    dragoon_flame_state_funcs[self->state](self);
}

void (*dragoon_flame_state_funcs[5])(struct MiscObj*) = {
    func_800CF4B8,
    dragoon_flame_burn,
    dragoon_flame_despawn,
    func_800CF660,
    dragoon_flame_attached,
};
