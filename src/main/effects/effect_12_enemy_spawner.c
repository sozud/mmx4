// EffectObj, effect_object_update_funcs[12]
// 800B806C..800B84DC
#include "common.h"

u8 enemy_spawner_child_ids[8] = { 12, 25, 12, 12, 12, 12, 12, 12 };
u8 enemy_spawner_child_subtypes[8] = { 2, 1, 2, 2, 2, 2, 2, 2 };

void enemy_spawner_update(struct EffectObj* self)
{
    enemy_spawner_state_funcs[self->state](self);
}

void enemy_spawner_init(struct EffectObj* self)
{
    self->ext.effect_12.timer = 0x60;
    self->ext.effect_12.children[0] = NULL;
    self->ext.effect_12.children[1] = NULL;
    self->ext.effect_12.children[2] = NULL;
    self->ext.effect_12.children[3] = NULL;
    self->ext.effect_12.cooldown = 0;
    self->ext.effect_12.spawned = 0;
    self->ext.effect_12.child_count = (u8)self->unk2 >> 4;
    self->ext.effect_12.child_id = enemy_spawner_child_ids[(u8)self->unk2 & 0xF];
    self->ext.effect_12.child_subtype = enemy_spawner_child_subtypes[(u8)self->unk2 & 0xF];
    self->state = 1;
    self->unk5 = 0;
}

// enemy_spawner_spawn
INCLUDE_ASM("main/nonmatchings/effects/effect_12_enemy_spawner", func_800B8114);

void enemy_spawner_despawn(struct EffectObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

// enemy_spawner_count_children
INCLUDE_ASM("main/nonmatchings/effects/effect_12_enemy_spawner", func_800B8490);

void (*enemy_spawner_state_funcs[])(struct EffectObj*) = {
    enemy_spawner_init,
    func_800B8114,
    enemy_spawner_despawn,
};
