// LayerObj, layer_object_update_funcs[3]
// 800D9C84..800DA05C
#include "common.h"

#ifdef MMX4_PC
#include "main/objects.h"
#include "main/player_common.h"
#endif

// train_boss_trigger_update
#ifdef MMX4_PC
void func_800D9C84(struct LayerObj* self);
extern ret_u8 func_8002938C(s32);
#endif

#ifdef MMX4_PC
// src/main/layers/layer_03.c

void func_800D9C84(struct LayerObj* self)
{
    struct Main45LayerSignals* signals = (struct Main45LayerSignals*)&self->unk16;
    s32 slot;

    if (self->unk2 == 0) {
        struct MainObj* boss;

        if (g_Player.x_pos.i.hi < 0x1B61) {
            return;
        }
        player_start_script_action(0x14, 0);
        boss = find_free_main_obj();
        if (boss != NULL) {
            s32 resource;
            s32 column;
            s32 row;

            boss->active = 0x41;
            boss->id = 0x2D;
            boss->unk2 = 0;
            boss->unk40 = D_801406A8[(u8)func_8002938C(0x2D)] >> 7;
            resource = (u8)func_8002938C(0x2D);
            column = resource * 4 + 0x18;
            row = (u8)func_8002938C(0x2D);
            boss->unk42 = (column % 16) | (((row + 6) / 4 + 0x1E0) << 6);
            resource = (u8)func_8002938C(0x2D);
            boss->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
            boss->x_pos.val = FIXED(0x1960);
            boss->y_pos.val = FIXED(0x180);
            boss->state = 0;
        }
        despawn_object(OBJECT_HEADER(self));
        return;
    }

    for (slot = 0; slot < 5; slot++) {
        struct MainObj* object = &main_objects[slot];
        if (object->id == 0x2E && self->unk17 != 0) {
            object->unk42 |= 0x8000;
            self->unk17--;
        } else if (self->unk16 != 0) {
            object->unk42 |= 0x8000;
        } else {
            object->unk42 &= 0x7FFF;
        }
        object->x_pos.i.hi = (u16)object->x_pos.i.hi + (s8)self->bg_offset;
    }
    for (slot = 0; slot < 5; slot++) {
        struct ShotObj* object = &shot_objects[slot];
        u8* flash = NULL;
        if (object->state >= 3) {

            assert((u8)object->unk2 < COUNT(signals->projectile_state));
            flash = &signals->projectile_state[(u8)object->unk2];
        }
        if (flash != NULL && *flash != 0) {
            object->unk42 |= 0x8000;
            (*flash)--;
        } else if (self->unk16 != 0) {
            object->unk42 |= 0x8000;
        } else {
            object->unk42 &= 0x7FFF;
        }
        object->x_pos.i.hi = (u16)object->x_pos.i.hi + (s8)self->bg_offset;
    }
    for (slot = 0; slot < 2; slot++) {
        struct ItemObj* object = &item_objects[slot];
        if (self->unk16 != 0)
            object->unk42 |= 0x8000;
        else
            object->unk42 &= 0x7FFF;
        object->x_pos.i.hi = (u16)object->x_pos.i.hi + (s8)self->bg_offset;
    }
    if (self->unk15 != 0) {
        g_Player.x_pos.i.hi = (u16)g_Player.x_pos.i.hi + (s8)self->bg_offset;
        for (slot = 0; slot < COUNT(weapon_objects); slot++) {
            struct WeaponObj* object = &weapon_objects[slot];
            object->x_pos.i.hi = (u16)object->x_pos.i.hi + (s8)self->bg_offset;
        }
    }
    self->bg_offset = self->unk15 = self->unk16 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/layers/layer_03", func_800D9C84);
#endif
