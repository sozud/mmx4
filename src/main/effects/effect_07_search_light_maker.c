// EffectObj, effect_object_update_funcs[7]
// 800B6B18..800B7078
#include "common.h"

extern struct SearchLightSpawner search_light_spawners[];

// search lights don't appear in level if nopped out
// effect_obj 0x07
void search_light_maker_update(struct EffectObj* self)
{
    // asm(".rept 13 ; nop ; .endr");
    search_light_maker_state_funcs[self->state](self);
}

// search_light_maker_state_funcs state 0
void search_light_maker_init(struct EffectObj* self)
{
    s32 var_v0;
    struct SearchLightSpawner* var_v1;
    struct BackgroundObj* background_object;

    self->state = 1;

    var_v1 = &search_light_spawners;
    for (var_v0 = 11; var_v0 >= 0; var_v0--) {
        var_v1->active = 0;
        var_v1 += 1;
    }

    background_object = background_objects;
    search_light_maker_spawn_in_rect((background_object->x_pos.i.hi - 48), (background_object->x_pos.i.hi + 368), (background_object->y_pos.i.hi - 48), (background_object->y_pos.i.hi + 288), self);
    background_object++;
    search_light_maker_spawn_in_rect((background_object->x_pos.i.hi - 48), (background_object->x_pos.i.hi + 368), (background_object->y_pos.i.hi - 48), (background_object->y_pos.i.hi + 288), self);
    background_object++;
    search_light_maker_spawn_in_rect((background_object->x_pos.i.hi - 48), (background_object->x_pos.i.hi + 368), (background_object->y_pos.i.hi - 48), (background_object->y_pos.i.hi + 288), self);
}

// search_light_maker_state_funcs state 1
void search_light_maker_main(struct EffectObj* self)
{
    search_light_maker_spawn_scrolled(self);
}

// search_light_maker_state_funcs state 2
void search_light_maker_idle(struct EffectObj* self)
{
}

void search_light_maker_spawn_scrolled(struct EffectObj* self)
{
    search_light_maker_spawn_edges(self, 0, search_light_maker_scroll_dirs(self, 0));
    search_light_maker_spawn_edges(self, 1, search_light_maker_scroll_dirs(self, 1));
    search_light_maker_spawn_edges(self, 2, search_light_maker_scroll_dirs(self, 2));
}

void search_light_maker_spawn_edges(s32 arg0, s8 arg1, s8 arg2)
{
    s8 temp;
    u16 a1, a3;
    struct BackgroundObj* temp_s0;

    temp_s0 = &background_objects[arg1];
    if (arg2 != 0) {
        if (arg2 & 1) {
            a1 = temp_s0->x_pos.i.hi;
            a3 = temp_s0->y_pos.i.hi;
            search_light_maker_spawn_in_rect(a1 + 0x130, a1 + 0x190, a3 - 0x50, a3 + 0x140, arg0);
        }
        temp = arg2 & 2;
        if (temp != 0) {
            a1 = temp_s0->x_pos.i.hi;
            a3 = temp_s0->y_pos.i.hi;
            search_light_maker_spawn_in_rect(a1 - 0x50, a1 - 0x10, a3 - 0x50, a3 + 0x140, arg0);
        }
        temp = arg2 & 4;
        if (temp != 0) {
            a1 = temp_s0->x_pos.i.hi;
            a3 = temp_s0->y_pos.i.hi;
            search_light_maker_spawn_in_rect(a1 - 0x50, a1 + 0x190, a3 + 0x100, a3 + 0x140, arg0);
        }
        temp = arg2 & 8;
        if (temp != 0) {
            a1 = temp_s0->x_pos.i.hi;
            a3 = temp_s0->y_pos.i.hi;
            search_light_maker_spawn_in_rect(a1 - 0x50, a1 + 0x190, a3 - 0x50, a3 - 0x10, arg0);
        }
    }
}

struct Initializer {
    u8 active;
    u8 type;
    u8 unk2;
    u8 unk3;
    s16 value1;
    s16 value2;
};

void search_light_maker_spawn_in_rect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4)
{
    struct Initializer* current = (struct Initializer*)search_light_spawners;
    struct QuadObj* result;

    if (current->type != 0xFF) {
        do {
            if (current->active == 0 && current->value1 > arg0 && current->value1 < arg1 && current->value2 > arg2 && current->value2 < arg3) {
                result = find_free_quad_obj();
                if (result != NULL) {
                    result->active = 1;
                    result->id = 0;
                    result->unk2 = current->type;
                    result->bg_offset = current->unk3;
                    result->x_pos.i.hi = current->value1;
                    result->y_pos.i.hi = current->value2;
                    result->backref = (struct SearchLightSpawner*)current;
                    current->active = 1;
                }
            }
            current++;
        } while (current->type != 0xFF);
    }
}

s8 search_light_maker_scroll_dirs(s32 arg0, s8 arg1)
{
    struct BackgroundObj* ptr = &background_objects[arg1];
    s8 result = 0;

    if (ptr->unk14.i.hi != ptr->x_pos.i.hi) {
        if (ptr->unk14.i.hi < ptr->x_pos.i.hi) {
            result = 1;
        } else {
            result = 2;
        }
    }

    if (ptr->unk18.i.hi != ptr->y_pos.i.hi) {
        if (ptr->unk18.i.hi < ptr->y_pos.i.hi) {
            result |= 4;
        } else {
            result |= 8;
        }
    }

    return result;
}

struct SearchLightSpawner search_light_spawners[12] = {
    { 0, 0, 0, 0, 1072, 512 },
    { 0, 0, 0, 0, 2457, 512 },
    { 0, 2, 0, 2, 0, 512 },
    { 0, 3, 0, 2, 245, 512 },
    { 0, 2, 0, 2, 738, 512 },
    { 0, 2, 0, 2, 1093, 512 },
    { 0, 3, 0, 2, 1712, 512 },
    { 0, 4, 0, 2, 128, 336 },
    { 0, 4, 0, 2, 736, 336 },
    { 0, 5, 0, 2, 1136, 336 },
    { 0, 4, 0, 2, 1696, 336 },
    { 0, 0xff, 0, 0, 0, 0 },
};

void (*search_light_maker_state_funcs[])(struct EffectObj*) = {
    search_light_maker_init,
    search_light_maker_main,
    search_light_maker_idle,
};
