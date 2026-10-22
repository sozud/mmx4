// MainObj, main_object_update_funcs[62]
// 8007B90C..8007BFF4
#include "common.h"
#include "main/mains/main_62_flame_jet.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/misc/misc_02_rubble.h"
#endif

extern struct Unk_unk68 flame_jet_hurt_box_7;

// flame_jet_setup_funcs
extern void (*flame_jet_setup_funcs[])(struct BarObj*);

// flame_jet_step_funcs
extern void (*flame_jet_step_funcs[])(struct MainObj*);
void flame_jet_idle(struct MainObj* arg0);

void flame_jet_erupt(struct MainObj* arg0);
void flame_jet_pause(struct MainObj* arg0);

// flame_jet_extinguished_funcs
extern void (*flame_jet_extinguished_funcs[])(struct BarObj*);

void flame_jet_extinguished_idle(void);

// flame_jet_state_funcs
extern void (*flame_jet_state_funcs[])(struct MainObj*);
void flame_jet_setup(struct BarObj* arg0);

void flame_jet_extinguished(struct BarObj* arg0);

// flame_jet_init
#ifdef MMX4_PC
static struct VisualObj* main_62_spawn_arm(struct MainObj* arg0, s8 side);
void func_8007B90C(struct MainObj* arg0);
u8 func_8007BABC(struct MainObj* arg0);
void func_8007BE40(struct MainObj* arg0);
s32 func_8002BD58(struct MainObj*, struct MainObj*, s16*, s16*);
extern u8 flame_jet_intervals[8];
extern struct Unk_unk68 flame_jet_debris[2];
extern struct Unk_unk68 flame_jet_extinguish_debris[2];
extern union AnimationStep* flame_jet_animations[9];
extern struct Unk_unk68 D_80107C78[];
extern s16 flame_jet_smoke_offsets[20];
static struct VisualObj* main_62_spawn_arm(struct MainObj* arg0, s8 side)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 0x19;
    visual->unk2 = side;
    visual->x_pos.val = arg0->x_pos.val + (arg0->unk15 != 0 ? -0x690000 : 0x690000);
    visual->unk50 = (struct PlayerObj*)arg0;
    visual->y_pos.val = arg0->y_pos.val - 0x80000;
    return visual;
}
#endif

#ifdef MMX4_PC
void func_8007B90C(struct MainObj* arg0)
{
    struct VisualObj* visual = NULL;

    arg0->active |= 4;
    arg0->unk15 = (arg0->unk2 & 1) ? 0x40 : 0;
    arg0->unk7C = flame_jet_intervals[arg0->unk2];
    if (arg0->unk2 < 4) {
        main_62_spawn_arm(arg0, 1);
        visual = main_62_spawn_arm(arg0, 0);
        spawn_debris_offset(6, (u8*)flame_jet_debris, (struct MiscObj*)arg0,
            arg0->unk15 != 0 ? -0x690000 : 0x690000, 0);
    }
    arg0->ext.main_62.unk80 = visual;
    arg0->ext.main_62.unk86 = 0;
    arg0->animation_table = (const u8* const*)flame_jet_animations;
    arg0->unk16 = 2;
    arg0->collision_data = D_80107C78;
    arg0->hp = 0x7F;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->unk62 = 0;
    arg0->contact_damage = 4;
    arg0->air_state = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk5++;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_62_flame_jet", func_8007B90C);
#endif

// flame_jet_is_vent_blocked
#ifdef MMX4_PC
u8 func_8007BABC(struct MainObj* arg0)
{
    struct WeaponObj* weapon;

    arg0->hurt_box = &flame_jet_vent_box;
    for (weapon = weapon_objects; weapon < weapon_objects + COUNT(weapon_objects); weapon++) {
        if (!weapon->active)
            continue;
        if (!func_8002BD58((struct MainObj*)weapon, arg0,
                &((s16*)&weapon->unk80)[0], &((s16*)&weapon->unk80)[1]))
            continue;
        if (weapon->id == 2 || weapon->id == 0xB || weapon->id == 0x21)
            return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_62_flame_jet", func_8007BABC);
#endif

void flame_jet_wait_sync(struct MainObj* self)
{
    if (func_8007BABC(self) == 0) {
#ifdef MMX4_PC
        if ((self->unk2 >= 4) || (self->ext.main_62.unk80->animation_step.fields.event != 0)) {
#else
        if ((self->ext.main_62.unk80->animation_step.fields.event != 0) || (self->unk2 > 3)) {
#endif
            set_animation(self, 2);
            self->unk5 = 2;
            self->state++;
        }
    }
}

void flame_jet_setup(struct BarObj* self)
{
    flame_jet_setup_funcs[self->unk5](self);
}

void flame_jet_idle(struct MainObj* self)
{
}

void flame_jet_erupt(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5++;
        self->unk7E = (u16)self->unk7C;
    }
    if (self->animation_step.fields.frame_index != 0) {
        update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
        self->ext.main_62.unk86 = (u8)self->on_screen;
    }
}

void flame_jet_pause(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7E;
    if (timer == 0) {
        if (func_8007BABC(self) == 0) {
            self->unk5--;
            set_animation(self, 2);
            if (self->ext.main_62.unk86 != 0) {
                func_8001540C(2, 0xA2, self);
            }
        }
    } else {
        self->unk7E = timer - 1;
    }
}

void flame_jet_main(struct MainObj* self)
{
    s32 result;

    flame_jet_step_funcs[self->unk5](self);
    if ((self->animation_step.fields.frame_index > 2) && (self->animation_step.fields.frame_index < 12)) {
        self->hurt_box = flame_jet_hurt_boxes[self->animation_step.fields.frame_index - 3];
        self->attack_box = flame_jet_attack_boxes[self->animation_step.fields.frame_index - 3];
    } else {
        self->hurt_box = NULL;
        self->attack_box = NULL;
    }
    result = func_8002DD04(self);
    if ((result == 3) || (result == 0xC) || (result == 0x22)) {
        self->unk5 = 0;
        self->unk7E = 0x14;
        self->state++;
        self->unk42 = (self->unk42 & 0x7FFF) + 2;
    } else {
        func_8002D9BC(self);
    }
}

// flame_jet_extinguish
#ifdef MMX4_PC
void func_8007BE40(struct MainObj* arg0)
{
    s32 index;
    s32 x_offset;

    if (--arg0->unk7E != 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
        arg0->ext.main_62.unk86 = arg0->on_screen;
        return;
    }
    arg0->unk5++;
    index = arg0->animation_step.fields.frame_index - 3;
    x_offset = flame_jet_smoke_offsets[index * 2];
    if (arg0->unk15 != 0)
        x_offset = -x_offset;
    spawn_debris_offset(8, (u8*)flame_jet_extinguish_debris, (struct MiscObj*)arg0, (s32)((u32)x_offset << 16),
        (s32)((u32)flame_jet_smoke_offsets[index * 2 + 1] << 16));
    arg0->state = 1;
    arg0->unk5 = 3;
    arg0->unk7E = 0xC8;
    arg0->hp = 0x7F;
    arg0->unk42 -= 2;
    set_animation(arg0, 2);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_62_flame_jet", func_8007BE40);
#endif

void flame_jet_extinguished_idle(void)
{
}

void flame_jet_extinguished(struct BarObj* self)
{
    flame_jet_extinguished_funcs[self->unk5](self);
}

void flame_jet_update(struct MainObj* self)
{
    self->on_screen = 0;
    flame_jet_state_funcs[self->state](self);
}

struct Unk_unk68 flame_jet_attack_box_0 = { 88, -26, 14, 18 };

struct Unk_unk68 flame_jet_attack_box_1 = { 71, -44, 14, 24 };

struct Unk_unk68 flame_jet_attack_box_2 = { 53, -61, 20, 22 };

struct Unk_unk68 flame_jet_attack_box_3 = { 22, -72, 38, 14 };

struct Unk_unk68 flame_jet_attack_box_4 = { -21, -74, 68, 15 };

struct Unk_unk68 flame_jet_attack_box_5 = { -44, -64, 23, 16 };

struct Unk_unk68 flame_jet_attack_box_6 = { -99, -32, 23, 25 };

struct Unk_unk68 flame_jet_attack_box_7 = { -101, -18, 37, 8 };

struct Unk_unk68 flame_jet_attack_box_8 = { -91, -18, 20, 8 };

struct Unk_unk68 flame_jet_hurt_box_0 = { 83, -32, 25, 25 };

struct Unk_unk68 flame_jet_hurt_box_1 = { 66, -48, 37, 47 };

struct Unk_unk68 flame_jet_hurt_box_2 = { 49, -64, 65, 50 };

struct Unk_unk68 flame_jet_hurt_box_3 = { 11, -83, 89, 63 };

struct Unk_unk68 flame_jet_hurt_box_4 = { -28, -88, 125, 44 };

struct Unk_unk68 flame_jet_hurt_box_5 = { -65, -93, -126, 62 };

struct Unk_unk68 flame_jet_hurt_box_6 = { -114, -53, 63, 51 };

struct Unk_unk68 flame_jet_hurt_box_7 = { -117, -35, 80, 32 };

struct Unk_unk68 flame_jet_hurt_box_8 = { -107, -30, 59, 26 };

struct Unk_unk68 flame_jet_vent_box = { 72, -35, 49, 38 };

struct Unk_unk68* flame_jet_hurt_boxes[9] = {
    &flame_jet_hurt_box_0,
    &flame_jet_hurt_box_1,
    &flame_jet_hurt_box_2,
    &flame_jet_hurt_box_3,
    &flame_jet_hurt_box_4,
    &flame_jet_hurt_box_5,
    &flame_jet_hurt_box_6,
    &flame_jet_hurt_box_7,
    &flame_jet_hurt_box_8,
};

struct Unk_unk68* flame_jet_attack_boxes[9] = {
    &flame_jet_attack_box_0,
    &flame_jet_attack_box_1,
    &flame_jet_attack_box_2,
    &flame_jet_attack_box_3,
    &flame_jet_attack_box_4,
    &flame_jet_attack_box_5,
    &flame_jet_attack_box_6,
    &flame_jet_attack_box_7,
    &flame_jet_attack_box_8,
};

union AnimationStep flame_jet_anim_0[] = {
    { 0x00010002 },
    { 0x01010101 },
    { 0x01000102 },
};

union AnimationStep flame_jet_anim_1[] = {
    { 0x02000006 },
};

union AnimationStep flame_jet_anim_2[] = {
    { 0x00010007 },
    { 0x03010007 },
    { 0x04010007 },
    { 0x05010007 },
    { 0x06010007 },
    { 0x07010007 },
    { 0x08010007 },
    { 0x09010007 },
    { 0x0A010007 },
    { 0x0B010007 },
    { 0x0C010007 },
    { 0x13010007 },
    { 0x14010006 },
    { 0x14000001 },
};

union AnimationStep flame_jet_anim_3[] = {
    { 0x0D000001 },
};

union AnimationStep flame_jet_anim_4[] = {
    { 0x0E000001 },
};

union AnimationStep flame_jet_anim_5[] = {
    { 0x0F000001 },
};

union AnimationStep flame_jet_anim_6[] = {
    { 0x10000001 },
};

union AnimationStep flame_jet_anim_7[] = {
    { 0x11000001 },
};

union AnimationStep flame_jet_anim_8[] = {
    { 0x12000001 },
};

union AnimationStep* flame_jet_animations[9] = {
    flame_jet_anim_0,
    flame_jet_anim_1,
    flame_jet_anim_2,
    flame_jet_anim_3,
    flame_jet_anim_4,
    flame_jet_anim_5,
    flame_jet_anim_6,
    flame_jet_anim_7,
    flame_jet_anim_8,
};

struct Unk_unk68 flame_jet_debris[2] = {
    { 3, 4, 3, 4 },
    { 3, 4, 0, 0 },
};

struct Unk_unk68 flame_jet_extinguish_debris[2] = {
    { 5, 6, 7, 8 },
    { 5, 6, 7, 8 },
};

u8 flame_jet_intervals[8] = { 0x14, 0x14, 0x28, 0x28, 0x14, 0x14, 0x28, 0x28 };

void (*flame_jet_setup_funcs[2])() = {
    func_8007B90C,
    flame_jet_wait_sync,
};

void (*flame_jet_step_funcs[4])() = {
    enemy_hit_reaction,
    flame_jet_idle,
    flame_jet_erupt,
    flame_jet_pause,
};

s16 flame_jet_smoke_offsets[20] = {
    (s16)0x005F,
    (s16)0xFFEF,
    (s16)0x0051,
    (s16)0xFFE4,
    (s16)0x0051,
    (s16)0xFFE4,
    (s16)0x0042,
    (s16)0xFFD1,
    (s16)0x0023,
    (s16)0xFFBF,
    (s16)0xFFFC,
    (s16)0xFFBE,
    (s16)0xFFDB,
    (s16)0xFFC8,
    (s16)0xFFA6,
    (s16)0xFFED,
    (s16)0xFFAD,
    (s16)0xFFF3,
    (s16)0xFFAD,
    (s16)0xFFF3,
};

void (*flame_jet_extinguished_funcs[2])() = {
    func_8007BE40,
    flame_jet_extinguished_idle,
};

void (*flame_jet_state_funcs[3])() = {
    flame_jet_setup,
    flame_jet_main,
    flame_jet_extinguished,
};
