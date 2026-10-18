// MainObj, main_object_update_funcs[59]
// 80074E84..8007501C
#include "common.h"
#include "main/mains/main_59_timed_explosion.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/misc/misc_23_explosion_puff.h"
#include "main/objects.h"

// timed_explosion_state_funcs
extern void (*timed_explosion_state_funcs[])(struct MainObj*);
void timed_explosion_wait(struct MainObj*);

void timed_explosion_despawn(struct MainObj* arg0);

// storm_owl_grab_funcs
extern struct Unk_unk68 timed_explosion_attack_box;

void timed_explosion_wait(struct MainObj* self)
{
    s32* sprite_archive;

    if (--self->unk7C == 0) {
        sprite_archive = SP_SPRITE_FRAMES;
        *(s32*)&self->animation_speed = 0;
        self->sprite_frames = (u8*)sprite_archive + sprite_archive[2];
        self->animation_table = (const u8* const*)explosion_animations;
        self->unk40 = 0;
        self->unk42 = 0x788F;
        self->hurt_box = 0;
        self->attack_box = &timed_explosion_attack_box;
        set_animation(self, 2);

        if (get_random() & 1) {
            func_8001540C(0, 0, self);
        } else {
            func_8001540C(0, 1, self);
        }
        self->state++;
        update_on_screen(BASE_OBJECT(self), 0x18, 0x18);
    }
}

void timed_explosion_explode(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x18, 0x18);
    if ((self->animation_step.fields.relative_step < 0) || (func_8002B1E8(BASE_OBJECT(self), 0x18, 0x18) != 0)) {
        self->state++;
    }
}

void timed_explosion_despawn(struct MainObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void timed_explosion_update(struct MainObj* self)
{
    timed_explosion_state_funcs[self->state](self);
}

struct Unk_unk68 timed_explosion_attack_box = { -16, -16, 31, 29 };

void (*timed_explosion_state_funcs[3])() = {
    timed_explosion_wait,
    timed_explosion_explode,
    timed_explosion_despawn,
};
