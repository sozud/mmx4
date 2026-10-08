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
    self->ext.effect_12.children[0] = NULL;
    self->ext.effect_12.children[1] = NULL;
    self->ext.effect_12.children[2] = NULL;
    self->ext.effect_12.children[3] = NULL;
    self->ext.effect_12.cooldown = 0;
    self->ext.effect_12.timer = 0x60;
    self->ext.effect_12.spawned = 0;
    self->ext.effect_12.child_count = (self->unk2 >> 4) & 0xF;
    self->ext.effect_12.child_id = enemy_spawner_child_ids[(u8)self->unk2 & 0xF];
    self->ext.effect_12.child_subtype = enemy_spawner_child_subtypes[(u8)self->unk2 & 0xF];
    self->state = 1;
    self->unk5 = 0;
}

// enemy_spawner_spawn
s32 func_800B8490(struct EffectObj* self);
ret_u8 func_8002938C(arg_u8 id);

void func_800B8114(struct EffectObj* self)
{
    s16 i;
    s16 distance;
    s32 clut;
    struct MainObj* child;
#ifdef VERSION_EU
    struct MainObj** slot;
#endif
    if (func_800B8490(self) == 0) {
        for (i = 0; i < self->ext.effect_12.child_count; i++) {
#ifdef VERSION_EU
            struct Effect12Ext* children = &self->ext.effect_12;
            child = children->children[i];
#else
            child = self->ext.effect_12.children[i];
#endif
            if ((child != 0) && (child->active == 0)) {
#ifdef VERSION_EU
                children->children[i] = 0;
#else
                self->ext.effect_12.children[i] = 0;
#endif
            }
        }

        switch (self->unk5) {
        case 0:
            distance = ABS(self->x_pos.i.hi, g_Player.x_pos.i.hi);
            if (distance < 0x80) {
                self->unk5 = 1;
            }
            break;

        case 1:
            for (i = 0; i < self->ext.effect_12.child_count; i++) {
#ifdef VERSION_EU
                s32 offset = i * sizeof(struct MainObj*);
                struct Effect12Ext* ext = &self->ext.effect_12;
                if (*(slot = (struct MainObj**)((u8*)&ext->children[0] + offset)) == 0) {
#else
                if (self->ext.effect_12.children[i] == 0) {
#endif
                    if (self->ext.effect_12.cooldown == 0) {
                        child = find_free_main_obj();
                        if (child != 0) {
#ifdef VERSION_EU
                            *slot = child;
#else
                            self->ext.effect_12.children[i] = child;
#endif
                            child->active = 0x41;
                            child->id = self->ext.effect_12.child_id;
                            child->unk2 = self->ext.effect_12.child_subtype;
                            child->x_pos.val = self->x_pos.val;
                            child->y_pos.val = self->y_pos.val;
                            self->ext.effect_12.cooldown = 0x20;
                            child->unk40 = (u16)(D_801406A8[func_8002938C((u8)child->id) & 0xFF] >> 7);
                            clut = SOME_COORDINATE_CONVERSION(func_8002938C((u8)child->id) & 0xFF);
                            child->unk42 = clut;
                            child->sprite_frames = (const u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C((u8)child->id) & 0xFF];
                            self->ext.effect_12.spawned++;
                            if (self->ext.effect_12.spawned >= self->ext.effect_12.child_count) {
                                self->unk5 = 2;
                            }
                        }
                    } else {
                        self->ext.effect_12.cooldown--;
                    }
                }
            }

            break;

        case 2:
            i = 0;
            child = 0;
            for (i = 0; i < self->ext.effect_12.child_count; i++) {
#ifdef VERSION_EU
                struct Effect12Ext* children = &self->ext.effect_12;
                child = children->children[i];
#else
                child = self->ext.effect_12.children[i];
#endif
            }
            if (child == 0) {
                self->unk5 = 3;
                self->ext.effect_12.spawned = 0;
                self->ext.effect_12.cooldown = 0;
                self->ext.effect_12.timer = 0x60;
            }
            break;

        case 3:
            if (--self->ext.effect_12.timer != 0) {
                return;
            }
            self->unk5 = 0;
            return;
        }

        return;
    }
    self->state = 2;
    return;
}

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
