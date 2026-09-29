// MainObj, main_object_update_funcs[44]
// 80065930..80065B8C
#include "common.h"
#include "func_tables.h"

void anchored_mine_update(struct MainObj* self)
{
    anchored_mine_state_funcs[self->state](self);
}

void anchored_mine_init(struct MainObj* obj)
{
    obj->active = 0x41;
    obj->hp = 1;
    obj->contact_damage = 3;
    obj->invincibility_timer = 0;
    obj->bg_offset = g_Player.bg_offset;
    obj->collision_data = D_801060F0;
    obj->animation_table = (const u8* const*)anchored_mine_animations;
    obj->unk16 = 6;
    obj->hurt_box = &anchored_mine_hurt_box;
    // memset 0
    obj->x_speed = 0;
    obj->y_speed = 0;
    obj->x_accel = 0;
    obj->gravity = 0;
    obj->air_state = 0;
    obj->terrain_box = NULL;
    obj->attack_box = &anchored_mine_attack_box;
    obj->unk18.val = obj->x_pos.val;
    obj->unk1C.val = obj->y_pos.val;
    set_animation(obj, 0);
    obj->ext.main_44.unk80 = 0;
    obj->ext.main_44.unk84 = 0;
    obj->ext.main_44.unk88 = 0;
    obj->ext.main_44.unk8C = 0;
    obj->ext.main_44.unk90 = 0;
    obj->ext.main_44.saved_unk5 = 0;
    obj->unk5 = 2;
    obj->unk6 = 0;
    obj->state++;
}

extern void (*anchored_mine_step_funcs[])(struct MainObj*);

void anchored_mine_main(struct MainObj* self)
{
    s8 temp_v0;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    anchored_mine_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    func_8002DD04(self);
    temp_v0 = self->unk5;
    if (temp_v0 != 0) {
        self->ext.main_44.saved_unk5 = temp_v0;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = (u8)self->state + 1;
}

void anchored_mine_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void anchored_mine_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_44.saved_unk5;
}

void anchored_mine_idle(struct MainObj* self)
{
    anchored_mine_idle_funcs[self->unk6](self);
}

void anchored_mine_animate(struct MainObj* self)
{
    animate_object(self);
}

struct Unk_unk68 anchored_mine_hurt_box = { -11, -10, 21, 23 };

struct Unk_unk68 anchored_mine_attack_box = { -11, -10, 20, 42 };

union AnimationStep anchored_mine_anim_0[] = {
    { 0x05010007 },
    { 0x0601000C },
    { 0x07010004 },
    { 0x08010004 },
    { 0x00010005 },
    { 0x01010008 },
    { 0x0D010007 },
    { 0x0E01000C },
    { 0x0D010007 },
    { 0x00010005 },
    { 0x01010008 },
    { 0x0F010007 },
    { 0x1001000E },
    { 0x0F010007 },
    { 0x00010006 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010002 },
    { 0x0B010004 },
    { 0x0C010002 },
    { 0x0A01000C },
    { 0x09010006 },
    { 0x00010005 },
    { 0x01E9000C },
};

union AnimationStep* anchored_mine_animations[2] = { anchored_mine_anim_0, NULL };

void (*anchored_mine_state_funcs[])(struct MainObj*) = {
    anchored_mine_init,
    anchored_mine_main,
    anchored_mine_despawn,
};

void (*anchored_mine_step_funcs[3])() = { enemy_hit_reaction, anchored_mine_resume_step, anchored_mine_idle };

void (*anchored_mine_idle_funcs[1])() = { anchored_mine_animate };
