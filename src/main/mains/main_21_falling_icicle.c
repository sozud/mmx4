// MainObj, main_object_update_funcs[21]
// 80054C50..80054FE8
#include "common.h"
#include "func_tables.h"

void falling_icicle_update(struct MainObj* self)
{
    falling_icicle_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
    animate_object(self);
}

void falling_icicle_init(struct MainObj* arg0)
{
    struct MainObj* self;

    self = arg0;
    self->contact_damage = 1;
    self->invincibility_timer = 0;
    self->bg_offset = g_Player.bg_offset;
    self->animation_table = (const u8* const*)falling_icicle_animations;
    self->unk16 = 6;
    self->hurt_box = &falling_icicle_body_box;
    self->attack_box = &falling_icicle_body_box;
    self->terrain_box = &falling_icicle_terrain_box;
    self->collision_data = D_80108504;
    self->ext.main_21.timer_80 = 0x1E;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->unk15 = 0;
    self->hp = 3;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->ext.main_21.timer_82 = self->unk2 * 0x14;
    set_animation(arg0, 0);
    self->state = 1;
    self->unk5 = 2;
}

// falling_icicle_main
INCLUDE_ASM("main/nonmatchings/mains/main_21_falling_icicle", func_80054D8C);

void falling_icicle_shatter(struct MainObj* self)
{
    if (self->animation_step.fields.event == 1) {
        self->state = 3;
    }
}

void falling_icicle_despawn(struct MainObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void falling_icicle_wait(struct MainObj* self)
{
    if (self->ext.main_21.timer_80 == 0) {
        if (self->ext.main_21.timer_82 == 0) {
            self->unk5 = 3;
            set_animation(self, 0);
            return;
        }
        self->ext.main_21.timer_82--;
        return;
    }
    self->ext.main_21.timer_80--;
}

void falling_icicle_release(struct MainObj* self)
{
    if (self->animation_step.fields.event == 1) {
        self->gravity = 0x5000;
        self->unk5 = 4;
    }
}

void falling_icicle_fall(struct MainObj* self)
{
    move_with_gravity((struct AnimatedObj*)self);
}

void falling_icicle_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_21.saved_unk5;
}

union AnimationStep falling_icicle_anim_0[] = {
    { 0x01010003 },
    { 0x02010005 },
    { 0x03010003 },
    { 0x00000150 },
};

union AnimationStep falling_icicle_anim_1[] = {
    { 0x04000001 },
};

union AnimationStep falling_icicle_anim_2[] = {
    { 0x05000001 },
};

union AnimationStep falling_icicle_anim_3[] = {
    { 0x06000001 },
};

union AnimationStep falling_icicle_anim_4[] = {
    { 0x07010006 },
    { 0x08010006 },
    { 0x09000106 },
};

union AnimationStep* falling_icicle_animations[5] = {
    falling_icicle_anim_0,
    falling_icicle_anim_1,
    falling_icicle_anim_2,
    falling_icicle_anim_3,
    falling_icicle_anim_4,
};

u8 falling_icicle_debris[4] = { 1, 2, 3, 0 };

struct Unk_unk68 falling_icicle_body_box = { -8, -16, 16, 32 };

struct Unk_unk68 falling_icicle_terrain_box = { 0, 0, 8, 16 };

void (*falling_icicle_state_funcs[4])(struct MainObj*) = {
    falling_icicle_init,
    func_80054D8C,
    falling_icicle_shatter,
    falling_icicle_despawn,
};

void (*falling_icicle_step_funcs[5])() = {
    enemy_hit_reaction,
    falling_icicle_resume_step,
    falling_icicle_wait,
    falling_icicle_release,
    falling_icicle_fall,
};
