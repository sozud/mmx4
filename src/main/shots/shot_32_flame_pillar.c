// ShotObj, shot_object_update_funcs[32]
// 800A0170..800A03B8
#include "common.h"
#include "main/shots/shot_32_flame_pillar.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/objects.h"

// flame_pillar_state_funcs
extern void (*flame_pillar_state_funcs[])(struct ShotObj*);

void flame_pillar_active(struct ShotObj*);
void flame_pillar_despawn(struct ShotObj*);

u8 flame_pillar_short_box[4] = { 0xF8, 0xCC, 0x0F, 0x23 };
u8 flame_pillar_tall_box[4] = { 0xF8, 0xCC, 0x0F, 0x65 };

// flame_pillar_init
#ifdef MMX4_PC
void func_800A0170(struct ShotObj* arg0);
extern union AnimationStep* ice_block_animations[9];
extern ret_u8 func_8002938C(s32);
#endif

#ifdef MMX4_PC
void func_800A0170(struct ShotObj* arg0)
{
    struct WeaponObj* owner;
    s32 resource;

    arg0->state++;
    arg0->unk60 = 6;
    arg0->unk15 = 0;
    arg0->unk16 = 1;
    arg0->unk68 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk61 = 0;
    arg0->unk5C = 1;
    arg0->animation_table = (u32**)ice_block_animations;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk42 = CLUT_FROM_ID(0x14);
    resource = func_8002938C(0x14);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x14);
    owner = arg0->unk7C;
    arg0->unk16 = 1;
    arg0->unk54 = NULL;
    arg0->unk68 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->x_pos.val = owner->x_pos.val + (arg0->unk2 != 0 ? 0x300000 : 0x100000);
    arg0->unk50.data = flame_pillar_tall_box;
    arg0->y_pos.val = owner->y_pos.val + 0x80000;
    set_animation(arg0, 8);
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_32_flame_pillar", func_800A0170);
#endif

void flame_pillar_active(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    if (self->animation_step.fields.relative_step < 0) {
        self->state++;
    }
}

void flame_pillar_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void flame_pillar_update(struct ShotObj* self)
{
    flame_pillar_state_funcs[self->state](self);
}

void (*flame_pillar_state_funcs[])(struct ShotObj*) = {
    func_800A0170,
    flame_pillar_active,
    flame_pillar_despawn,
};
