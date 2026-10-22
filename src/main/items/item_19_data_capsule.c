// ItemObj, item_object_update_funcs[19]
// 800C470C..800C4CE4
#include "common.h"
#include "main/items/item_19_data_capsule.h"
#include "main/55C4.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/mains/main_41_data_hopper.h"
#endif

// data_capsule_state_funcs
extern void (*data_capsule_state_funcs[])(struct ItemObj*);

void data_capsule_idle(struct ItemObj*);

// data_capsule_attached_funcs
extern void (*data_capsule_attached_funcs[])(struct ItemObj*);
void data_capsule_attached_init(struct ItemObj*);
void data_capsule_attached_follow(struct ItemObj*);
void data_capsule_idle(struct ItemObj*);

struct Item19SpawnPosition {
    u16 x;
    u16 y;
};

struct Item19SpawnPosition data_capsule_positions[4] = {
    { 0x07B0, 0x022C },
    { 0x07B0, 0x03A0 },
    { 0x07B0, 0x0458 },
    { 0x07B0, 0x05D8 },
};

u8 data_capsule_box_0[4] = { 0, 0xFE, 0x29, 8 };
u8 data_capsule_box_1[4] = { 0, 4, 0x29, 0x0B };
u8 data_capsule_box_2[4] = { 0, 4, 0x29, 0x0B };

void (*data_capsule_state_funcs[])(struct ItemObj*) = {
    func_800C4778,
    func_800C49BC,
    data_capsule_idle,
};

void (*data_capsule_attached_funcs[])(struct ItemObj*) = {
    data_capsule_attached_init,
    data_capsule_attached_follow,
    data_capsule_idle,
};

void data_capsule_update(struct ItemObj* arg0)
{
    if (arg0->unk2 >= 0) {
        data_capsule_state_funcs[arg0->state](arg0);
    } else {
        data_capsule_attached_funcs[arg0->state](arg0);
    }
}

// data_capsule_init
#ifdef MMX4_PC
void func_800C4778(struct ItemObj* self);
void func_800C49BC(struct ItemObj* self);
void collide_with_players(struct PlayerObj*);
extern ret_u8 func_8002938C(s32);
#endif

#ifdef MMX4_PC
void func_800C4778(struct ItemObj* self)
{
    if (self->unk2 < 4) {
        s32 index;
        self->state = 1;
        self->on_screen = 1;
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk7 = 0;
        self->active |= 0x40;
        self->unk18 = self->x_pos;
        self->unk1C = self->y_pos;
        index = (u8)func_8002938C(0x29);
        self->animation_table = (const u8* const*)data_hopper_animations;
        self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        self->unk40 = D_801406A8[index] >> 7;
        self->unk42 = ((index * 4 + 0x18) & 0xF) | ((((index + 6) / 4 + 0x1E0) << 6) & 0xFFFF);
        self->unk54 = NULL;
        self->unk50 = NULL;
        self->unk68 = (struct Unk_unk68*)(self->unk2 == 0 ? data_capsule_box_0 : self->unk2 == 1 ? data_capsule_box_1
                                                                                                 : data_capsule_box_2);
        self->unk76 = -1;
        self->unk75 = 1;
        self->unk16 = 6;
        self->unk67 = 0;
        self->x_vel.val = 0;
        self->y_vel.val = 0;
        self->unk28 = 0;
        self->unk2C = 0;
        self->unk7C.timer16 = 0xA;
        ((u16*)&self->unk7C)[1] = 0;
        self->unk7 = engine_obj.character_state.fields.active;
        set_animation(self, self->unk2 + 0xF);
    } else {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk7 = 0;
        self->on_screen = 0;
        for (s32 i = 0; i < 2; i++) {
            struct ItemObj* child = find_free_item_obj();
            if (child != NULL) {
                struct Item19SpawnPosition* pos = &data_capsule_positions[(self->unk2 - 4) * 2 + i];
                child->active = 1;
                child->id = 0x13;
                child->unk2 = i;
                child->x_pos.u.hi = pos->x;
                child->y_pos.u.hi = pos->y;
            }
        }
        despawn_object_permanently(OBJECT_HEADER(self));
    }
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_19_data_capsule", func_800C4778);
#endif

// data_capsule_main
#ifdef MMX4_PC
void func_800C49BC(struct ItemObj* self)
{
    u16* second_timer = (u16*)&self->unk7C;
    struct MainObj* spawned;
    s32 index;
    s16 right_edge;

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (engine_obj.character_state.fields.active != self->unk7)
        self->unk7C.timer16 = 0x1E;

    if (self->unk2 == 0) {
        if (self->unk7C.timer16 != 0) {
            self->unk7C.timer16--;
        } else if (self->animation_step.fields.relative_step != 0) {
            animate_object(ANIMATED_OBJECT(self));
        } else {
            right_edge = (s16)(background_objects[(u8)self->bg_offset].y_pos.u.hi + 0xF0);
            if (self->y_pos.i.hi < right_edge) {
                self->unk7C.timer16 = 0x1E;
                spawned = find_free_main_obj();
                if (spawned != NULL) {
                    spawned->active = 0x41;
                    spawned->id = 0x29;
                    spawned->unk2 = 1;
                    index = (u8)func_8002938C(0x29);
                    spawned->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
                    spawned->unk40 = D_801406A8[index] >> 7;
                    spawned->unk42 = ((index * 4 + 0x18) & 0xF) | (((index + 6) / 4 + 0x1E0) << 6);
                    spawned->x_pos = self->x_pos;
                    spawned->y_pos.val = self->y_pos.val + 0x280000;
                    spawned->unk15 = 0;
                    set_animation(self, self->unk2 + 0xF);
                    if (self->on_screen)
                        func_8001540C(2, 0xEA, spawned);
                }
            }
        }
    } else if (second_timer[1] != 0) {
        if (self->animation_step.fields.relative_step != 0) {
            animate_object(ANIMATED_OBJECT(self));
        } else {
            second_timer[1] = 0;
            set_animation(self, self->unk2 + 0xF);
        }
    }
    self->unk7 = engine_obj.character_state.fields.active;
    collide_with_players(self);
    is_on_screen(BASE_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_19_data_capsule", func_800C49BC);
#endif

void data_capsule_idle(struct ItemObj* arg0)
{
}

void data_capsule_attached_init(struct ItemObj* arg0)
{
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->on_screen = 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk54 = 0;
    arg0->unk50 = 0;
    arg0->unk68 = NULL;
    arg0->unk67 = 0;
    arg0->unk76 = 0;
    arg0->unk75 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 4;
    set_animation(arg0, 1);
}

void data_capsule_attached_follow(struct ItemObj* arg0)
{
    struct MainObj* owner;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    owner = arg0->ext.owner;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    if (owner->unk5 == 5) {
        animate_object(ANIMATED_OBJECT(arg0));
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}
