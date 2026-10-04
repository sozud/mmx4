// EffectObj, effect_object_update_funcs[38]
// 800BD654..800BDE68
#include "common.h"

void cyberspace_trial_spawn_rank_warp(struct EffectObj* self);

void cyberspace_trial_update(struct EffectObj* self)
{
    cyberspace_trial_state_funcs[self->state](self);
}

void cyberspace_trial_init(struct EffectObj* self)
{
    if (0 == engine_obj.substage) {
        self->unk2 = (u8)engine_obj.checkpoint;
        cyberspace_trial_delete_unused_items();
    } else if (engine_obj.checkpoint == 0) {
        self->unk2 = 6;
    } else {
        self->state = 6;
        return;
    }

    self->unk5 = 0;
    self->unk6 = 0;
    self->state++;
    self->ext.effect_38.timer = 0;
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/effects/effect_38_cyberspace_trial", cyberspace_trial_wait_start);
#else
void cyberspace_trial_wait_start(struct EffectObj* self)
{
    s8 subtype;

    subtype = self->unk2;
    if (g_Player.x_pos.i.hi >= cyberspace_trial_trigger_x[subtype].start_x) {
        if (!(subtype % 2) && engine_obj.substage == 0) {
            cyberspace_trial_spawn_guide(self);
            engine_obj.unk10 = 1;
            engine_obj.unk12 = 1;
            engine_obj.unk11 = 1;
            engine_obj.unk13 = 1;
        }
        self->state++;
    }
}
#endif

void cyberspace_trial_wait_goal(struct EffectObj* self)
{
    s8 subtype;

    cyberspace_trial_delete_unused_items();
    subtype = self->unk2;
    if (g_Player.x_pos.i.hi >= cyberspace_trial_trigger_x[subtype].goal_x && (subtype != 6 || g_Player.y_pos.i.hi < 0x400)) {
        player_start_script_action(0x14, 0x40);
        cyberspace_trial_clear_objects(self);
        if ((engine_obj.checkpoint % 2) || engine_obj.substage != 0) {
            self->ext.effect_38.active = 1;
            self->ext.effect_38.timer = 0xA;
            self->state += 2;
        } else {
            self->ext.effect_38.timer = 0x14;
            self->state++;
        }
    }
}

void cyberspace_trial_delay(struct EffectObj* self)
{
    self->ext.effect_38.timer--;
    if (self->ext.effect_38.timer == 0) {
        self->ext.effect_38.timer = 0x64;
        self->state++;
    }
}

void cyberspace_trial_wait_rank(struct EffectObj* self)
{
    if (--self->ext.effect_38.timer == 0 && self->ext.effect_38.active != 0) {
        player_start_script_action(0x15, 0x40);
        cyberspace_trial_spawn_rank_warp(self);
        self->ext.effect_38.timer = 0x64;
        self->state++;
    }
}

void cyberspace_trial_advance(struct EffectObj* self)
{
    u8 timer;

    if (self->ext.effect_38.timer == 0x50) {
        cyberspace_trial_spawn_warps(self);
    }

    timer = self->ext.effect_38.timer - 1;
    self->ext.effect_38.timer = timer;
    if (timer != 0) {
        return;
    }

    switch (self->ext.effect_38.variant) {
    case 0:
        engine_obj.checkpoint++;
        break;
    case 1:
        engine_obj.checkpoint += 2;
        break;
    case 2:
        break;
    default:
        engine_obj.checkpoint += 2;
        break;
    }

    if (engine_obj.checkpoint <= 5) {
        engine_obj.unkF = -0x40;
    } else {
        engine_obj.unkF = 0x40;
    }
    self->state++;
}

void cyberspace_trial_despawn(struct EffectObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cyberspace_trial_spawn_guide(struct EffectObj* self)
{
    struct MiscObj* obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x22;
        obj->ext.pointer.unk50 = self;
        obj->unk2 = 0;
    }
}

void cyberspace_trial_spawn_warps(void* arg0)
{
    s8 var_s0;
    struct MiscObj* temp_v0;

    var_s0 = 0;
    do {
        temp_v0 = find_free_misc_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 0x41;
            temp_v0->id = 0x21;
            temp_v0->ext.pointer.unk50 = arg0;
            temp_v0->unk2 = var_s0;
        }
        var_s0 += 1;
    } while (var_s0 < 2U);
}

void cyberspace_trial_spawn_rank_warp(struct EffectObj* self)
{
    struct MiscObj* misc;
    u8 subtype;

    if (self->ext.effect_38.active == 0 || (self->unk2 % 2) != 0 || engine_obj.substage != 0) {
        return;
    }
    misc = find_free_misc_obj();
    if (misc == NULL) {
        return;
    }
    misc->active = 0x41;
    misc->id = 0x21;
    misc->ext.misc_7.position = self;
    subtype = self->ext.effect_38.variant;
    switch (subtype) {
    case 0:
        misc->unk2 = 2;
        break;
    case 1:
        misc->unk2 = 3;
        break;
    case 2:
        misc->unk2 = 4;
        break;
    default:
        return;
    }
}

void cyberspace_trial_delete_unused_items(void)
{
    switch (engine_obj.checkpoint) {
    case 1:
        if (engine_obj.cur_character == 0) {
            delete_items(2, 4);
            delete_items(2, 0xF);
            delete_items(0x1A, 0);
        } else {
            delete_items(2, 0xC);
            delete_items(2, 0xF);
        }
        break;
    case 3:
        if (engine_obj.cur_character == 0) {
            delete_items(2, 4);
            delete_items(2, 0xC);
            delete_items(0x1A, 0);
        } else {
            delete_items(2, 4);
            delete_items(2, 0xF);
        }
        break;
    case 5:
        if (engine_obj.cur_character == 0) {
            delete_items(2, 4);
            delete_items(2, 0xC);
            delete_items(2, 0xF);
        } else {
            delete_items(2, 4);
            delete_items(2, 0xC);
        }
        break;
    }
}

void cyberspace_trial_clear_objects(struct EffectObj* self)
{
    u32 i;
    s32 count;
    s8 fill = 0;
    s8* ptr;

    for (i = 0; i < 0x30; i++) {
        ptr = (s8*)&main_objects[i];
        count = sizeof(main_objects[i]) - 1;
        do {
            *ptr++ = fill;
        } while (count-- != 0);
    }

    for (i = 0; i < 0x20; i++) {
        ptr = (s8*)&shot_objects[i];
        count = sizeof(shot_objects[i]) - 1;
        do {
            *ptr++ = fill;
        } while (count-- != 0);
    }

    for (i = 0; i < 0x40; i++) {
        if ((misc_objects[i].id != 0x21 && misc_objects[i].id != 0x22)) {
            ptr = (s8*)&misc_objects[i];
            count = sizeof(misc_objects[i]) - 1;
            do {
                *ptr++ = fill;
            } while (count-- != 0);
        }
    }
}

void delete_items(s32 arg0, s32 arg1)
{
    s8 clear_value = 0;
    u32 i = 0;
    s32 count;
    u8* ptr;

    arg0 &= 0xFF;
    arg1 &= 0xFF;
    for (; i < 0x20; i++) {
        if (item_objects[i].id == arg0 && item_objects[i].unk2 == arg1) {
            ptr = (u8*)&item_objects[i];
            count = sizeof(struct ItemObj) - 1;
            do {
                *ptr++ = clear_value;
            } while (count-- != 0);
        }
    }
}

struct CyberspaceTrialBounds cyberspace_trial_trigger_x[7] = {
    { 0x0190, 0x0700 },
    { 0, 0x0300 },
    { 0x0190, 0x0800 },
    { 0, 0x0300 },
    { 0x0170, 0x0C00 },
    { 0, 0x0300 },
    { 0, 0x0F78 },
};

void (*cyberspace_trial_state_funcs[])(struct EffectObj*) = {
    cyberspace_trial_init,
    cyberspace_trial_wait_start,
    cyberspace_trial_wait_goal,
    cyberspace_trial_delay,
    cyberspace_trial_wait_rank,
    cyberspace_trial_advance,
    cyberspace_trial_despawn,
};
