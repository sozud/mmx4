// MainObj, main_object_update_funcs[50]
// 8006970C..80069A94
#include "common.h"
#include "main/mains/main_50_train_crate.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/1E1BC.h"
#include "main/CB184.h"
#include "main/collision_bounds.h"
#endif

void train_crate_explode(struct MainObj*);
void train_crate_despawn(struct MainObj* arg0);

// train_crate_step_funcs
void train_crate_idle(struct MainObj* arg0);

extern void (*train_crate_state_funcs[])(struct MainObj*);

void train_crate_update(struct MainObj* self)
{
    train_crate_state_funcs[self->state](self);
}

// train_crate_init
#ifdef MMX4_PC
void func_80069748(struct MainObj* arg0);
void func_800698D8(struct MainObj* arg0);
extern struct Unk_unk68 D_80108504[];
extern u8 train_crate_hurt_box[4];
extern u8 D_800FFBDC[6];
extern u8 train_crate_debris[6];
extern void (*train_crate_step_funcs[2])();
extern ret_u8 func_8002938C(s32);
#endif

#ifdef MMX4_PC
void func_80069748(struct MainObj* arg0)
{
    s32 resource;

    arg0->on_screen = 0;
    arg0->contact_damage = 0;
    arg0->invincibility_timer = 0;
    resource = func_8002938C(0x28);
    arg0->unk40 = D_801406A8[resource] >> 7;
    arg0->unk42 = CLUT_FROM_ID(0x28);
    resource = func_8002938C(0x28);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk16 = 6;
    arg0->hurt_box = train_crate_hurt_box;
    arg0->animation_table = (const u8* const*)train_crate_animations;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->attack_box = NULL;
    arg0->terrain_box = NULL;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->ext.main_50.unk84 = (u8)arg0->unk2 >> 4;
    arg0->unk2 &= 0xF;
    arg0->collision_data = arg0->ext.main_50.unk84 == 8 ? D_80108584 : D_80108504;
    arg0->hp = 3;
    arg0->unk15 = 0;
    arg0->state = 1;
    arg0->unk5 = 1;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_50_train_crate", func_80069748);
#endif

// train_crate_main
#ifdef MMX4_PC
void func_800698D8(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    train_crate_step_funcs[arg0->unk5](arg0);
    if (func_8002DD04(arg0) >= 0) {
        if (func_8002B160(BASE_OBJECT(arg0)) != 0)
            despawn_object(OBJECT_HEADER(arg0));
        return;
    }
    arg0->ext.main_50.timer = 0;
    spawn_debris(6, arg0->ext.main_50.unk84 == 8 ? train_crate_debris : D_800FFBDC, arg0);
    if (engine_obj.stage == 8) {
        apply_tile_effect(arg0->unk2 + 8, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi - 0x40);
    } else {
        apply_tile_effect(arg0->unk2, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi - 0x30);
        if (arg0->ext.main_50.unk84 != 0)
            apply_tile_effect(arg0->ext.main_50.unk84, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi);
    }
    arg0->ext.main_50.unk84 = 0;
    arg0->state = 2;
    arg0->unk5 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_50_train_crate", func_800698D8);
#endif

void train_crate_explode(struct MainObj* self)
{
    if (++self->ext.main_50.timer != 0x30) {
        if (!(main_bss_state.frame_counter & 7)) {
            func_800AF878(BASE_OBJECT(self), 1, 0x18, 0x18);
        }
    } else {
        self->state = 3;
    }
}

void train_crate_despawn(struct MainObj* self)
{
    despawn_object_permanently(self);
}

void train_crate_idle(struct MainObj* self)
{
}

u8 train_crate_hurt_box[4] = { 0xE0, 0xE0, 0x40, 0x50 };

u8 D_800FFBDC[6] = { 0, 1, 2, 1, 0, 2 };

u8 train_crate_debris[6] = { 7, 8, 9, 7, 9, 8 };

union AnimationStep train_crate_anim_0[1] = { { 0x00000101 } };

union AnimationStep train_crate_anim_1[1] = { { 0x01000001 } };

union AnimationStep train_crate_anim_2[1] = { { 0x02000001 } };

union AnimationStep train_crate_anim_3[1] = { { 0x03000001 } };

union AnimationStep train_crate_anim_4[1] = { { 0x04000001 } };

union AnimationStep train_crate_anim_5[1] = { { 0x05000001 } };

union AnimationStep train_crate_anim_6[1] = { { 0x06000001 } };

union AnimationStep train_crate_anim_7[1] = { { 0x07000001 } };

union AnimationStep train_crate_anim_8[1] = { { 0x08000001 } };

union AnimationStep train_crate_anim_9[1] = { { 0x09000001 } };

union AnimationStep* train_crate_animations[10] = {
    train_crate_anim_0,
    train_crate_anim_1,
    train_crate_anim_2,
    train_crate_anim_3,
    train_crate_anim_4,
    train_crate_anim_5,
    train_crate_anim_6,
    train_crate_anim_7,
    train_crate_anim_8,
    train_crate_anim_9,
};

void (*train_crate_state_funcs[])(struct MainObj*) = {
    func_80069748,
    func_800698D8,
    train_crate_explode,
    train_crate_despawn,
};

void (*train_crate_step_funcs[2])() = {
    enemy_hit_reaction,
    train_crate_idle,
};

#ifdef MMX4_WIN32
u8 D_800FFB5C[4] = { 0, 0, 13, 21 };
#endif
