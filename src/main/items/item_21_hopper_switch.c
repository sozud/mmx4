// ItemObj, item_object_update_funcs[21]
// 800C52CC..800C5544
#include "common.h"
#include "main/items/item_21_hopper_switch.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/collision.h"
#include "main/objects.h"
#include "main/mains/main_41_data_hopper.h"

// hopper_switch_state_funcs
extern void (*hopper_switch_state_funcs[])(struct ItemObj*);

void hopper_switch_main(struct ItemObj*);
void hopper_switch_despawn(struct ItemObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/mains/main_41_data_hopper.h"
#endif

// hopper_switch_init

extern u8 hopper_switch_box[4];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C52CC(struct ItemObj* self);
extern ret_u8 func_8002938C(s32);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/items/item_21_hopper_switch", func_800C52CC);
#else
void func_800C52CC(struct ItemObj* self)
{
    u8 index;

    self->active |= 0x41;
    self->on_screen = 0;
    index = func_8002938C(0x29);
    self->animation_table = (const u8* const*)data_hopper_animations;
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    self->unk40 = OBJECT_STAGE_TEXTURE(index);
    self->unk42 = OBJECT_CLUT(CLUT_FROM_XY(index, index));
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->unk68 = (struct Unk_unk68*)hopper_switch_box;
    self->state = 1;
}
#endif

s32 hopper_switch_hopper_touching(struct ItemObj* arg0)
{
    struct MainObj* object;

    for (object = main_objects; object < main_objects + COUNT(main_objects); object++) {
        if (object->active == 0 || object->id != 0x29) {
            continue;
        }
        if (func_8002C160(COLLISION_OBJECT(arg0), COLLISION_OBJECT(object)) == 0) {
            continue;
        }
        return 1;
    }
    return 0;
}

void hopper_switch_main(struct ItemObj* arg0)
{
    if (arg0->unk5 == 0) {
        if (hopper_switch_hopper_touching(arg0) == 0) {
            return;
        }
        apply_tile_effect(arg0->unk2, 0, 0);
        arg0->unk5 = 1;
        set_animation(arg0, 0xE);
    } else {
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->on_screen = 0;
            arg0->state = 2;
            return;
        }
        animate_object(ANIMATED_OBJECT(arg0));
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void hopper_switch_despawn(struct ItemObj* arg0)
{
    despawn_object_permanently(OBJECT_HEADER(arg0));
}

void hopper_switch_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    hopper_switch_state_funcs[arg0->state](arg0);
}

u8 hopper_switch_box[4] = { 0, 0, 8, 0x0E };

void (*hopper_switch_state_funcs[])(struct ItemObj*) = {
    func_800C52CC,
    hopper_switch_main,
    hopper_switch_despawn,
};
