// ShotObj, shot_object_update_funcs[16]
// 8009C364..8009C5F0
#include "common.h"
#include "main/shots/shot_16_linked_spark.h"
#include "main/55C4.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/1E1BC.h"
#endif

// linked_spark_state_funcs
extern void (*linked_spark_state_funcs[])(struct ShotObj*);

void linked_spark_update(struct ShotObj* self)
{
    linked_spark_state_funcs[self->state](self);
}

void linked_spark_init(struct ShotObj* rawArg0)
{
    struct ShotObj* arg0 = rawArg0;
    s32 value;

    value = 1;
    arg0->state = value;
    arg0->on_screen = value;
    arg0->unk5C = value;
    value = arg0->unk2;
    arg0->unk16 = 6;
    arg0->unk68 = 0;
    arg0->unk54 = 0;
    arg0->unk50.data = 0;
    arg0->unk60 = 4;

    switch (value) {
    case 0:
        arg0->unk84.value = 6;
        arg0->unk15 = 0;
        break;
    case 1:
        arg0->unk84.value = 6;
        arg0->unk15 = 0x40;
        break;
    case 2:
        arg0->unk84.value = 9;
        break;
    case 3:
        arg0->unk84.value = 0xC;
        break;
    }

    set_animation(arg0, arg0->unk84.value);
}

// linked_spark_main
#ifdef MMX4_PC
void func_8009C45C(struct ShotObj* self);
extern u8 turret_laser_full_beam_box[4];
extern u8* turret_laser_beam_boxes[12];
#endif

#ifdef MMX4_PC
// src/main/shots/shot_16_linked_spark.c

void func_8009C45C(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;

    if (self->unk5 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            set_animation(self, self->unk84.value + 1);
            self->unk5 = 1;
            if (owner->active != 0 && owner->id == 0x1D && owner->state == 1 && owner->unk2 >= 0)
                owner->unk5 = 4;
        } else {
            s8 index = self->animation_step.fields.event;
            self->unk50.data = index > 0 && index <= 12 ? turret_laser_beam_boxes[index - 1]
                                                        : turret_laser_full_beam_box;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    self->x_pos = owner->x_pos;
    self->y_pos = owner->y_pos;
    func_8002D9BC(self);
    func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player));
    if (self->unk2 < 2)
        update_on_screen(BASE_OBJECT(self), 0x68, 0x10);
    else
        update_on_screen(BASE_OBJECT(self), 0x10, 0x68);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_16_linked_spark", func_8009C45C);
#endif

void linked_spark_despawn(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    if ((weapon->active != 0) && (weapon->id == 0x1D) && (weapon->unk2 >= 0)) {
        weapon->ext.weapon_29.unk90 = 0;
        weapon->unk80.bytes[1] &= 0xFE;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*linked_spark_state_funcs[])(struct ShotObj*) = {
    linked_spark_init,
    func_8009C45C,
    linked_spark_despawn,
};
