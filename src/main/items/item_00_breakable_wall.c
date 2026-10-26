// ItemObj, item_object_update_funcs[0]
// 800BE9A0..800BEBB4
#include "common.h"
#include "main/items/item_00_breakable_wall.h"
#include "main/1E1BC.h"
#include "main/CB184.h"
#include "main/objects.h"

extern u8 breakable_wall_debris[8];

// breakable_wall_state_funcs
extern void (*breakable_wall_state_funcs[])(struct ItemObj*);

void breakable_wall_main(struct ItemObj*);
void breakable_wall_despawn(struct ItemObj*);
#include "weapon_resources.h"

void breakable_wall_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    breakable_wall_state_funcs[arg0->state](arg0);
}

// breakable_wall_init

extern union AnimationStep* falling_rock_d_animations[];
extern u8 breakable_wall_hit_box[4];
extern struct Unk_unk68 D_80108684[];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800BE9E8(struct ItemObj* self);
extern union AnimationStep* falling_rock_d_animations[];
extern ret_u8 func_8002938C(s32);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/items/item_00_breakable_wall", func_800BE9E8);
#else
void func_800BE9E8(struct ItemObj* self)
{
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->on_screen = 0;
    self->unk5C = 1;
    self->unk61 = 0;
    self->animation_table = (const u8* const*)falling_rock_d_animations;
    self->unk42 = OBJECT_STAGE_CLUT(0x9A);
    self->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x9A));
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x9A));
    self->unk54 = breakable_wall_hit_box;
    self->unk50 = NULL;
    self->unk68 = NULL;
    self->unk58 = (const u8*)D_80108684;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->state = 1;
}
#endif

void breakable_wall_main(struct ItemObj* arg0)
{
    u8 var_a0;

    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        spawn_debris(7, breakable_wall_debris, arg0);
        var_a0 = 7;
        if (arg0->unk2 == 0) {
            var_a0 = 2;
        }
        apply_tile_effect(var_a0, (s16)(arg0->x_pos.u.hi - 0x20),
            (s16)(arg0->y_pos.u.hi - 0x18));
        arg0->state = 2;
    }
}

void breakable_wall_despawn(struct ItemObj* arg0)
{
    despawn_object_permanently(OBJECT_HEADER(arg0));
}

void (*breakable_wall_state_funcs[])(struct ItemObj*) = {
    func_800BE9E8,
    breakable_wall_main,
    breakable_wall_despawn,
};

u8 breakable_wall_hit_box[4] = { 0xE0, 0xE8, 0x40, 0x30 };
u8 breakable_wall_debris[8] = { 0, 1, 2, 3, 4, 5, 6, 0 };
