// QuadObj, quad_object_update_funcs[9]
// 800D67DC..800D6AD8
#include "common.h"
#include "main/quads/quad_09_aiming_laser_beam.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/sprite_animations.h"
#endif

void aiming_laser_beam_init(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2);
void aiming_laser_beam_main(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2);

void func_800D69A8(struct QuadObj* arg0, struct PlayerObj* player, struct PlayerObj* target);

void aiming_laser_beam_update(struct QuadObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    struct PlayerObj* temp_a2 = arg0->unk5C;
    s32 var_a3 = 0;
    if (g_Player.input_locked != 0) {
        var_a3 = 1;
    }
    if (g_Player.capsule_state != 0) {
        var_a3 = 1;
    }
    if (g_Player.weapon != 6) {
        var_a3 = 1;
    }
    if (g_Player.hp == 0) {
        var_a3 = 1;
    }
    if (g_Player.actions_reset != 0) {
        var_a3 = 1;
    }
    if (arg0->unk5C->active == 0) {
        var_a3 = 1;
    }
    if (arg0->unk5C->hp == 0) {
        var_a3 = 1;
    }
    if (var_a3 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->state == 0) {
        aiming_laser_beam_init(arg0, ptr, temp_a2);
        return;
    }
    aiming_laser_beam_main(arg0, ptr, temp_a2);
}

void aiming_laser_beam_init(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    struct QuadUnkExt3* ext = &arg0->ext.unk_ext3;
    arg0->active = -0x7D;
    arg0->on_screen = 1;
    arg0->bg_offset = arg1->bg_offset;
    arg0->unk34 = arg0->unk2 + 0xD;
    arg0->unk36 = 1;
    ext->unk38 = 0x3C;
    func_800D69A8(arg0, arg1, arg2);
    arg0->state++;
}

void aiming_laser_beam_main(struct QuadObj* arg0, struct PlayerObj* arg1, struct PlayerObj* arg2)
{
    struct QuadUnkExt3* ext = &arg0->ext.unk_ext3;
    if (ext->unk38 == 0) {
        ZeroObjectState(arg0);
        return;
    }
    if (FLICKER_ENABLED && (BLINK_CLOCK(ext->unk38) & 2)) {
        arg0->on_screen ^= 1;
    }
    ext->unk38 -= 1;
    func_800D69A8(arg0, arg1, arg2);
}

// aiming_laser_beam_place
#ifdef MMX4_PC
void func_800D69A8(struct QuadObj* arg0, struct PlayerObj* player, struct PlayerObj* target)
{
    const s8* offsets = (const s8*)&D_8011B230 + player->animation_step.fields.frame_index * 2;
    s32 dx = target->x_pos.val - player->x_pos.val;
    s32 dy = target->y_pos.val - player->y_pos.val;
    s16 x;
    s16 y;
    s16 near_x;
    s16 far_x;
    s16 near_y;
    s16 far_y;

    if (player->unk15 == 0)
        x = player->x_pos.i.hi + offsets[0] + 3;
    else
        x = player->x_pos.i.hi - offsets[0] - 3;
    near_x = target->x_pos.i.hi - (x + 6);
    far_x = target->x_pos.i.hi - (x - 6);
    arg0->x_pos.i.hi = x;
    arg0->vertices[0].x.val = 0;
    arg0->vertices[0].y.val = 0;
    y = player->y_pos.i.hi + offsets[1];
    arg0->y_pos.i.hi = y;
    near_y = target->y_pos.i.hi - (y + 6);
    far_y = target->y_pos.i.hi - (y - 6);
    if (dx < 0) {
        arg0->vertices[1].x.i.hi = far_x;
        arg0->vertices[2].x.i.hi = near_x;
        arg0->vertices[3].x.i.hi = near_x;
    } else {
        arg0->vertices[1].x.i.hi = near_x;
        arg0->vertices[2].x.i.hi = far_x;
        arg0->vertices[3].x.i.hi = far_x;
    }
    if (dy < 0) {
        arg0->vertices[1].y.i.hi = near_y;
        arg0->vertices[2].y.i.hi = near_y;
        arg0->vertices[3].y.i.hi = far_y;
    } else {
        arg0->vertices[1].y.i.hi = far_y;
        arg0->vertices[2].y.i.hi = far_y;
        arg0->vertices[3].y.i.hi = near_y;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/quads/quad_09_aiming_laser_beam", func_800D69A8);
#endif
