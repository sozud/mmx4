// WeaponObj, weapon_object_update_funcs[3]
// 80094A78..800951C0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_03", func_80094A78);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_03", func_80094B24);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_03", func_80094C18);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_03", func_80094D40);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_03", func_80094DC0);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_03", func_80094E50);

void func_80094EC8(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.unk98--;
    g_Player.unk99--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void func_80094F14(s32 arg0)
{
    u16* var_a0;
    u16* var_v1;
    u32 var_a1;

    var_a1 = 0;
    var_a0 = SP_PALETTE_BANK[(s16)arg0];
    var_v1 = SP_PALETTES[1];
    do {
        *var_v1++ = *var_a0++;
        var_a1 += 1;
    } while (var_a1 < 0x10U);
    need_palette_load |= 1;
}

void func_80094F74(void)
{
    s32 var_a0;
    struct BackgroundObj* obj;
    struct PlayerObj* entity = &g_Entity;

    obj = &background_objects[g_Player.bg_offset];
    if (entity->active != 0) {
        var_a0 = g_Player.unkC3 != 0;
        if (g_Player.unkC4 != 0) {
            var_a0 = 1;
        }
        if (g_Player.unk93 != 3) {
            var_a0 = 1;
        }
        if (g_Player.unkBF != 0) {
            var_a0 = 1;
        }
        if (g_Player.unk5C == 0) {
            var_a0 = 1;
        }
        if (entity->y_pos.i.hi >= obj->y_pos.i.hi + 328) {
            var_a0 = 1;
        }
        if (var_a0 != 0) {
            entity->active = 0;
            entity->on_screen = 0;
            g_Player.unkDE = 0;
            g_Player.unk7A = 0;
            return;
        }
        engine_obj.unk38 = entity;
        if (entity->unk5 != 0x25) {
            if (--entity->unkDA == 0) {
                func_800350A4(entity, 0x62);
                entity->on_screen = 1;
                entity->unk5 = 0x25;
            }
        }
        entity->unk18 = entity->x_pos.val;
        entity->unk1C = entity->y_pos.val;
        D_800F8980[entity->state](entity);
        if (entity->active != 0) {
            CollisionRelated(entity);
            if (obj->x_pos.i.hi >= entity->x_pos.i.hi) {
                entity->x_pos.i.hi = obj->x_pos.i.hi;
            }
            if (entity->x_pos.i.hi >= (obj->x_pos.i.hi + 320)) {
                entity->x_pos.i.hi = obj->x_pos.i.hi + 320;
            }
            if (obj->y_pos.i.hi >= entity->y_pos.i.hi) {
                entity->y_pos.i.hi = obj->y_pos.i.hi;
            }
            decompress_player_gfx(GRAPHICS_OBJECT(entity), 320, 64);
            if (entity->unkDA != 0 && entity->unkDA < 60) {
                entity->on_screen ^= 1;
            }
        }
    }
}
