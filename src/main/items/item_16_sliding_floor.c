// ItemObj, item_object_update_funcs[16]
// 800C3FEC..800C413C
#include "common.h"
#include "main/items/item_16_sliding_floor.h"
#include "main/1E1BC.h"
#include "main/object_motion.h"
#include "main/objects.h"

extern struct Unk_unk68 sliding_floor_terrain_box;

// sliding_floor_state_funcs
extern void (*sliding_floor_state_funcs[])(struct ItemObj*);
void sliding_floor_init(struct ItemObj*);
void sliding_floor_slide(struct ItemObj*);
#include "weapon_resources.h"

void sliding_floor_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    sliding_floor_state_funcs[arg0->state](arg0);
    collide_with_players(PLAYER_OBJECT(arg0));
    if (!(arg0->unk7C.train_boss->unk83 & 1)) {
        if ((g_Player.wall_climbable != 0) || (arg0->unk76 != 0)) {
            *arg0->ext.train_layer_parameter = 1;
        }
    }
    update_on_screen(BASE_OBJECT(arg0), 0x200, 0x100);
}

void sliding_floor_init(struct ItemObj* arg0)
{
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->unk68 = &sliding_floor_terrain_box;
    arg0->unk54 = 0;
    arg0->x_vel.val = FIXED(1);
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk75 = 1;
    arg0->unk76 = 0;
    arg0->state = 1;
    arg0->unk5 = 0;
}

void sliding_floor_slide(struct ItemObj* arg0)
{
    if (arg0->unk5 == 0) {
        if (arg0->x_pos.i.hi > 0x1AA0) {
            arg0->unk5 = 1;
            return;
        }
        move_object(MOVING_OBJECT(arg0));
    }
}

struct Unk_unk68 sliding_floor_terrain_box = { 0x27, 0x3C, 0x38, 0x1F };

void (*sliding_floor_state_funcs[])(struct ItemObj*) = {
    sliding_floor_init,
    sliding_floor_slide,
};
