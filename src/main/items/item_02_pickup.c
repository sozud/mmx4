// ItemObj, item_object_update_funcs[2]
// 800BF730..800C0404
#include "common.h"
#include "main/items/item_02_pickup.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"

// pickup_state_funcs
extern void (*pickup_state_funcs[])(struct ItemObj*);

void pickup_main(struct ItemObj*);
void pickup_collected(struct ItemObj*);
void pickup_despawn(struct ItemObj*);

struct Item02AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item02AnimationStep pickup_anim_1[17] = {
    { 0x03, 0x00, 0x01, 0x00 },
    { 0x02, 0x00, 0x01, 0x01 },
    { 0x01, 0x00, 0x01, 0x02 },
    { 0x01, 0x00, 0x01, 0x03 },
    { 0x03, 0x00, 0x01, 0x00 },
    { 0x02, 0x00, 0x01, 0x01 },
    { 0x01, 0x00, 0x01, 0x02 },
    { 0x01, 0x00, 0x01, 0x03 },
    { 0x04, 0x00, 0x01, 0x02 },
    { 0x03, 0x00, 0x01, 0x04 },
    { 0x03, 0x00, 0x01, 0x05 },
    { 0x05, 0x00, 0x01, 0x01 },
    { 0x02, 0x00, 0x01, 0x06 },
    { 0x06, 0x00, 0x01, 0x07 },
    { 0x07, 0x00, 0x01, 0x08 },
    { 0x08, 0x00, 0x01, 0x09 },
    { 0x07, 0x00, 0xFD, 0x08 },
};

struct Item02AnimationStep pickup_anim_3[20] = {
    { 0x06, 0x00, 0x01, 0x0A },
    { 0x06, 0x00, 0x01, 0x0B },
    { 0x06, 0x00, 0x01, 0x0C },
    { 0x06, 0x00, 0x01, 0x0D },
    { 0x06, 0x00, 0x01, 0x0E },
    { 0x07, 0x00, 0x01, 0x0F },
    { 0x08, 0x00, 0x01, 0x0A },
    { 0x09, 0x00, 0x01, 0x0F },
    { 0x03, 0x00, 0x01, 0x10 },
    { 0x03, 0x00, 0x01, 0x11 },
    { 0x03, 0x00, 0x01, 0x12 },
    { 0x03, 0x00, 0x01, 0x13 },
    { 0x03, 0x00, 0x01, 0x14 },
    { 0x03, 0x00, 0x01, 0x15 },
    { 0x03, 0x00, 0x01, 0x16 },
    { 0x03, 0x00, 0x01, 0x17 },
    { 0x03, 0x00, 0x01, 0x18 },
    { 0x03, 0x00, 0x01, 0x19 },
    { 0x03, 0x00, 0x01, 0x1A },
    { 0x03, 0x00, 0xF5, 0x0F },
};

struct Item02AnimationStep pickup_anim_0[9] = {
    { 0x06, 0x00, 0x01, 0x1B },
    { 0x05, 0x00, 0x01, 0x1C },
    { 0x05, 0x00, 0x01, 0x1B },
    { 0x05, 0x00, 0x01, 0x1C },
    { 0x05, 0x00, 0x01, 0x1D },
    { 0x07, 0x00, 0x01, 0x1E },
    { 0x07, 0x00, 0x01, 0x21 },
    { 0x07, 0x00, 0x01, 0x20 },
    { 0x07, 0x00, 0xFD, 0x21 },
};

struct Item02AnimationStep pickup_anim_2[14] = {
    { 0x08, 0x00, 0x01, 0x22 },
    { 0x07, 0x00, 0x01, 0x23 },
    { 0x06, 0x00, 0x01, 0x24 },
    { 0x05, 0x00, 0x01, 0x25 },
    { 0x04, 0x00, 0x01, 0x26 },
    { 0x05, 0x00, 0x01, 0x25 },
    { 0x06, 0x00, 0x01, 0x26 },
    { 0x07, 0x00, 0x01, 0x27 },
    { 0x07, 0x00, 0x01, 0x28 },
    { 0x07, 0x00, 0x01, 0x29 },
    { 0x07, 0x00, 0x01, 0x2A },
    { 0x07, 0x00, 0x01, 0x2B },
    { 0x07, 0x00, 0x01, 0x2C },
    { 0x07, 0x00, 0xFB, 0x27 },
};

struct Item02AnimationStep pickup_anim_6[15] = {
    { 0x04, 0x00, 0x01, 0x2E },
    { 0x04, 0x00, 0x01, 0x2F },
    { 0x04, 0x00, 0x01, 0x30 },
    { 0x04, 0x00, 0x01, 0x31 },
    { 0x04, 0x00, 0x01, 0x32 },
    { 0x04, 0x00, 0x01, 0x33 },
    { 0x04, 0x00, 0x01, 0x34 },
    { 0x04, 0x00, 0x01, 0x35 },
    { 0x04, 0x00, 0x01, 0x36 },
    { 0x04, 0x00, 0x01, 0x37 },
    { 0x04, 0x00, 0x01, 0x38 },
    { 0x04, 0x00, 0x01, 0x39 },
    { 0x04, 0x00, 0x01, 0x3A },
    { 0x04, 0x00, 0x01, 0x3B },
    { 0x04, 0x00, 0xF2, 0x3C },
};

struct Item02AnimationStep pickup_anim_5[12] = {
    { 0x06, 0x00, 0x01, 0x3D },
    { 0x06, 0x00, 0x01, 0x3E },
    { 0x06, 0x00, 0x01, 0x3F },
    { 0x06, 0x00, 0x01, 0x40 },
    { 0x06, 0x00, 0x01, 0x41 },
    { 0x06, 0x00, 0x01, 0x42 },
    { 0x06, 0x00, 0x01, 0x43 },
    { 0x06, 0x00, 0x01, 0x44 },
    { 0x06, 0x00, 0x01, 0x45 },
    { 0x06, 0x00, 0x01, 0x46 },
    { 0x06, 0x00, 0x01, 0x47 },
    { 0x06, 0x00, 0xF5, 0x48 },
};

struct Item02AnimationStep pickup_anim_7[16] = {
    { 0x06, 0x00, 0x01, 0x49 },
    { 0x06, 0x00, 0x01, 0x4A },
    { 0x06, 0x00, 0x01, 0x4B },
    { 0x06, 0x00, 0x01, 0x4C },
    { 0x06, 0x00, 0x01, 0x4D },
    { 0x06, 0x00, 0x01, 0x4E },
    { 0x06, 0x00, 0x01, 0x4F },
    { 0x06, 0x00, 0x01, 0x50 },
    { 0x06, 0x00, 0x01, 0x51 },
    { 0x06, 0x00, 0x01, 0x52 },
    { 0x06, 0x00, 0x01, 0x53 },
    { 0x06, 0x00, 0x01, 0x54 },
    { 0x06, 0x00, 0x01, 0x55 },
    { 0x06, 0x00, 0x01, 0x56 },
    { 0x06, 0x00, 0x01, 0x57 },
    { 0x06, 0x00, 0xF1, 0x58 },
};

struct Item02AnimationStep pickup_anim_4[18] = {
    { 0x06, 0x00, 0x01, 0x60 },
    { 0x05, 0x00, 0x01, 0x61 },
    { 0x04, 0x00, 0x01, 0x62 },
    { 0x06, 0x00, 0x01, 0x59 },
    { 0x05, 0x00, 0x01, 0x5A },
    { 0x04, 0x00, 0x01, 0x5B },
    { 0x06, 0x00, 0x01, 0x5C },
    { 0x05, 0x00, 0x01, 0x5D },
    { 0x04, 0x00, 0x01, 0x5E },
    { 0x06, 0x00, 0x01, 0x5F },
    { 0x05, 0x00, 0x01, 0x5E },
    { 0x04, 0x00, 0x01, 0x5D },
    { 0x04, 0x00, 0x01, 0x5C },
    { 0x03, 0x00, 0x01, 0x5B },
    { 0x03, 0x00, 0x01, 0x5A },
    { 0x04, 0x00, 0x01, 0x59 },
    { 0x04, 0x00, 0x01, 0x62 },
    { 0x05, 0x00, 0xEF, 0x61 },
};

struct Item02AnimationStep pickup_anim_8[33] = {
    { 0x03, 0x00, 0x01, 0x63 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x06, 0x00, 0x01, 0x66 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x03, 0x00, 0x01, 0x63 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x06, 0x00, 0x01, 0x66 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x03, 0x00, 0x01, 0x63 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x06, 0x00, 0x01, 0x66 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x03, 0x00, 0x01, 0x63 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x06, 0x00, 0x01, 0x66 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x03, 0x00, 0x01, 0x63 },
    { 0x04, 0x00, 0x01, 0x64 },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x02, 0x00, 0x01, 0x67 },
    { 0x01, 0x00, 0x01, 0x68 },
    { 0x01, 0x00, 0x01, 0x69 },
    { 0x02, 0x00, 0x01, 0x6A },
    { 0x05, 0x00, 0x01, 0x65 },
    { 0x04, 0x00, 0xE0, 0x64 },
};

struct Item02AnimationStep pickup_anim_9[33] = {
    { 0x03, 0x00, 0x01, 0x6B },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x06, 0x00, 0x01, 0x72 },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x03, 0x00, 0x01, 0x6B },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x06, 0x00, 0x01, 0x72 },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x03, 0x00, 0x01, 0x6B },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x06, 0x00, 0x01, 0x72 },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x03, 0x00, 0x01, 0x6B },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x06, 0x00, 0x01, 0x72 },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x03, 0x00, 0x01, 0x6B },
    { 0x04, 0x00, 0x01, 0x6C },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x02, 0x00, 0x01, 0x6E },
    { 0x01, 0x00, 0x01, 0x6F },
    { 0x01, 0x00, 0x01, 0x70 },
    { 0x02, 0x00, 0x01, 0x71 },
    { 0x05, 0x00, 0x01, 0x6D },
    { 0x04, 0x00, 0xE0, 0x6C },
};

struct Item02AnimationStep pickup_anim_10[4] = {
    { 0x05, 0x00, 0x01, 0x73 },
    { 0x05, 0x00, 0x01, 0x74 },
    { 0x05, 0x00, 0x01, 0x75 },
    { 0x05, 0x00, 0xFD, 0x76 },
};

struct Item02AnimationStep* pickup_animations[11] = {
    pickup_anim_0,
    pickup_anim_1,
    pickup_anim_2,
    pickup_anim_3,
    pickup_anim_4,
    pickup_anim_5,
    pickup_anim_6,
    pickup_anim_7,
    pickup_anim_8,
    pickup_anim_9,
    pickup_anim_10,
};

s8 pickup_hit_box_0[4] = { -1, -4, 6, 4 };
s8 pickup_hit_box_1[4] = { -2, -2, 12, 7 };
s8 pickup_hit_box_2[4] = { -1, -2, 6, 5 };
s8 pickup_hit_box_3[4] = { -1, -1, 9, 8 };
s8 pickup_hit_box_4[4] = { 0, 0, 13, 13 };
s8 pickup_hit_box_5[4] = { 0, 0, 10, 16 };
s8 pickup_hit_box_6[4] = { 1, 0, 10, 10 };
s8 pickup_hit_box_7[4] = { 0, 0, 10, 10 };
s8 pickup_hit_box_8[4] = { 0, 0, 13, 13 };
s8 pickup_hit_box_9[4] = { 0, 0, 13, 13 };
s8 pickup_hit_box_10[4] = { 0, 0, 12, 11 };

s8* pickup_hit_boxes[11] = {
    pickup_hit_box_0,
    pickup_hit_box_1,
    pickup_hit_box_2,
    pickup_hit_box_3,
    pickup_hit_box_4,
    pickup_hit_box_5,
    pickup_hit_box_6,
    pickup_hit_box_7,
    pickup_hit_box_8,
    pickup_hit_box_9,
    pickup_hit_box_10,
};

u8 drop_item_table[24][6] = {
    { 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00 },
    { 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00 },
    { 0x01, 0x00, 0xFF, 0x00, 0x00, 0x00 },
    { 0x01, 0x00, 0x00, 0xFF, 0x00, 0x00 },
    { 0x01, 0x00, 0x00, 0x00, 0xFF, 0x00 },
    { 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF },
    { 0x40, 0xA0, 0x20, 0x00, 0x00, 0x00 },
    { 0xC0, 0x30, 0x10, 0x00, 0x00, 0x00 },
    { 0xC0, 0x20, 0x20, 0x00, 0x00, 0x00 },
    { 0xC0, 0x10, 0x30, 0x00, 0x00, 0x00 },
    { 0x40, 0x20, 0xA0, 0x00, 0x00, 0x00 },
    { 0xA0, 0x00, 0x00, 0x40, 0x20, 0x00 },
    { 0xC0, 0x00, 0x00, 0x30, 0x10, 0x00 },
    { 0x80, 0x00, 0x00, 0x40, 0x40, 0x00 },
    { 0xC0, 0x00, 0x00, 0x10, 0x30, 0x00 },
    { 0x80, 0x00, 0x00, 0x30, 0x50, 0x00 },
    { 0x80, 0x38, 0x24, 0x18, 0x08, 0x04 },
    { 0xC0, 0x1C, 0x0A, 0x06, 0x10, 0x04 },
    { 0xC0, 0x1E, 0x07, 0x10, 0x0A, 0x01 },
    { 0x80, 0x08, 0x34, 0x28, 0x18, 0x04 },
    { 0x80, 0x28, 0x38, 0x18, 0x08, 0x00 },
    { 0xC0, 0x0A, 0x20, 0x06, 0x10, 0x00 },
    { 0xC0, 0x10, 0x0A, 0x20, 0x06, 0x00 },
    { 0x80, 0x18, 0x28, 0x38, 0x08, 0x00 },
};

void pickup_update(struct ItemObj* arg0)
{
    pickup_state_funcs[arg0->state](arg0);
}

// pickup_init
#ifdef MMX4_PC
void func_800C00BC(struct ItemObj* arg0);
void func_800BF76C(struct ItemObj* arg0);
void func_800BFCC0(struct ItemObj* arg0, u8 arg1);
void func_800BFBD0(struct ItemObj* arg0);
s32 func_8002C160(struct CollisionObj*, struct CollisionObj*);
#endif

#ifdef MMX4_PC
void func_800BF76C(struct ItemObj* arg0)
{
    u16 flags;
    u8 kind;
    s32 blocked;

    arg0->active = 0x21;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk15 = 0;
    arg0->animation_table = (const u8* const*)pickup_animations;
    arg0->unk42 = 0x7807;
    arg0->unk16 = 6;
    arg0->unk40 = 0;
    arg0->bg_offset = 0;
    arg0->unk2 = (u8)arg0->unk2 & 0x7F;
    arg0->active |= 0x20;
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 3);
    if (arg0->unk2 == 4) {
        arg0->unk42 = 0x780B;
    }

    kind = (u8)arg0->unk2;
    if ((u32)(kind - 7) < 8) {
        arg0->unk7C.value = 7;
    } else if ((u32)(kind - 0xF) < 2) {
        arg0->unk7C.value = 8;
    } else if ((s8)kind == 0x11) {
        arg0->unk7C.value = 9;
    } else if ((s8)kind == 0x12) {
        arg0->unk7C.value = 0xA;
        arg0->unk42 = 0x780B;
    } else {
        arg0->unk7C.value = kind;
    }

    kind = arg0->unk7C.value;
    arg0->unk68 = (struct Unk_unk68*)pickup_hit_boxes[kind];
    arg0->ext.item_2.unk82 = 0xF0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    if (arg0->backref == NULL) {
        arg0->y_vel.val = FIXED(8);
        arg0->unk2C = 0x8000;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    } else {
        arg0->y_vel.val = 0;
        arg0->unk2C = 0x8000;
        arg0->unk67 = 0;
    }

    blocked = 0;
    flags = engine_obj.collected_upgrades;
    switch (kind) {
    case 7:
        if ((flags & 0xFF) == 0xFF
            || (((s32)flags >> (arg0->unk2 - 7)) & 1) != 0) {
            blocked = 1;
        }
        break;
    case 8:
        if ((flags & 0x3000) == 0x3000
            || (flags & (0x1000 << (arg0->unk2 - 0xF))) != 0) {
            blocked = 1;
        }
        break;
    case 9:
        if ((flags & 0x4000)
            || (flags & (0x4000 << (arg0->unk2 - 0x11))) != 0) {
            blocked = 1;
        }
        break;
    case 0xA:
        if ((flags & 0x8000)
            || (flags & (0x8000 << (arg0->unk2 - 0x12))) != 0) {
            blocked = 1;
        }
        break;
    }

    if (blocked) {
        arg0->state = 3;
        return;
    }
    ((u8*)&arg0->unk7C)[1] = 0;
    set_animation(arg0, kind);
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_02_pickup", func_800BF76C);
#endif

void pickup_main(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->unk67 != 0) {
        move_with_gravity((struct AnimatedObj*)arg0);
        CollisionRelated((struct PlayerObj*)arg0);
        if (arg0->unk70 & 8) {
            if (arg0->unk6 == 0) {
                arg0->unk6 = 1;
                if (arg0->y_vel.val >= 0) {
                    arg0->y_vel.val = arg0->y_vel.val >> 1;
                } else {
                    arg0->y_vel.val = -arg0->y_vel.val >> 1;
                }
                arg0->unk2C = 0x8000;
            } else {
                arg0->unk6 = 0;
                arg0->unk67 = 0;
            }
        }
    } else {
        CollisionRelated((struct PlayerObj*)arg0);
        if (!(arg0->unk70 & 8)) {
            arg0->unk6 = 0;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0x8000;
            arg0->unk67 = 1;
        }
        animate_object(arg0);
    }
    if (arg0->backref == NULL) {
        if (--arg0->ext.item_2.unk82 == 0) {
            arg0->state = 3;
            return;
        }
    }
    func_800C00BC(arg0);
    if (func_8002B160(arg0) != 0) {
        if (arg0->backref != NULL) {
            despawn_object(OBJECT_HEADER(arg0));
        } else {
            arg0->state = 3;
            arg0->unk5 = 0;
        }
    } else {
        arg0->on_screen = 0;
        if ((arg0->ext.item_2.unk82 >= 0x3C) || !(BLINK_CLOCK(main_bss_state.frame_counter) & 1)) {
            is_on_screen((struct BaseObj*)arg0);
        }
    }
}

extern void func_800BFBD0(struct ItemObj* arg0);

void pickup_collected(struct ItemObj* arg0)
{
    arg0->on_screen = 0;
    func_800BFBD0(arg0);
}

void pickup_despawn(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

// pickup_refill
#ifdef MMX4_PC
void func_800BFBD0(struct ItemObj* arg0)
{
    u8 health;
    u8 status;

    if (arg0->unk6 == 0) {
        arg0->ext.item_2.unk81--;
        if (arg0->ext.item_2.unk81 != 0) {
            return;
        }

        arg0->ext.item_2.unk81 = 2;
        health = g_Player.hp;
        status = HP_DAMAGE_FLAG(health);
        if (HP_VALUE(health) >= engine_obj.max_hp) {
            arg0->unk6 = 1;
            g_Player.hp = (u8)engine_obj.max_hp | status;
        } else {
            g_Player.hp = (health + 1) | status;
        }
        func_8001540C(0, 0xD, NULL);

        arg0->ext.item_2.unk80--;
        if (arg0->ext.item_2.unk80 == 0) {
            arg0->unk6 = 1;
        }
    } else {
        set_objects_frozen(0);
        arg0->state = 3;
        arg0->unk5 = 0;
        arg0->active &= 0xF7;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_02_pickup", func_800BFBD0);
#endif

// pickup_collect_weapon_energy
#ifdef MMX4_PC
void func_800BFCC0(struct ItemObj* arg0, u8 arg1)
{
    struct PlayerObj* player = &g_Player;
    s32 charge_step;
    s32 engine_step;
    u32 index;
    u32 selected;
    u8 buttons;
    u8 value;
    s8 current;
    s8 next;

    (void)arg0;
    if (arg1 == 2) {
        charge_step = 4;
        engine_step = 1;
    } else if (arg1 == 3) {
        charge_step = 0x10;
        engine_step = 2;
    } else if (arg1 == 6) {
        charge_step = 0x30;
        engine_step = 4;
    } else {
        charge_step = 0;
        engine_step = 0;
    }

    if (engine_obj.cur_character == 0 && g_Player.weapon == 0) {
        index = 1;
        selected = 0;
        buttons = (u8)g_Player.boss_flags;
        do {
            if (((buttons >> (index - 1)) & 1) != 0) {
                if (player->weapon_energy[index] < player->weapon_energy[selected]) {
                    selected = index;
                }
            }
            index++;
        } while (index < 9);

        if (selected != 0) {
            value = (u8)g_Player.weapon_energy[0] + charge_step;
            g_Player.weapon_energy[0] = value;
            if ((s8)value >= 0x31) {
                g_Player.weapon_energy[0] = 0x30;
            }
        }
        value = (u8)player->weapon_energy[selected] + charge_step;
        player->weapon_energy[selected] = value;
        if ((s8)value >= 0x31) {
            player->weapon_energy[selected] = 0x30;
        }
    } else {
        u8 mask = engine_obj.cur_character == 0
            ? (u8)((u8)g_Player.boss_flags >> (g_Player.weapon - 1))
            : (u8)g_Player.boss_flags;

        if ((mask & 1) != 0) {
            current = player->weapon_energy[g_Player.weapon];
            if (current < 0x30) {
                next = current + charge_step;
                player->weapon_energy[g_Player.weapon] = next;
                if (next >= 0x31) {
                    player->weapon_energy[g_Player.weapon] = 0x30;
                }
                func_8001540C(0, 0x16, 0);
            } else {
                player->weapon_energy[g_Player.weapon] = 0x30;
            }
        }
    }

    if ((engine_obj.collected_upgrades & 0x4000) != 0) {
        value = (u8)engine_obj.sub_tanks[2] + engine_step;
        engine_obj.sub_tanks[2] = value;
        if ((s8)value >= 0x21) {
            engine_obj.sub_tanks[2] = 0x20;
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_02_pickup", func_800BFCC0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/items/item_02_pickup", pickup_collect_health);
#else
void pickup_collect_health(struct ItemObj* arg0, s8 arg1, s32 arg2)
{
    u8 player_status;
    s8 value;
    player_status = HP_DAMAGE_FLAG(g_Player.hp);
    if (HP_VALUE(g_Player.hp) < engine_obj.max_hp) {
        set_objects_frozen(1);
        arg0->active |= 8;
        arg0->ext.item_2.unk80 = arg1;
        arg0->ext.item_2.unk81 = 2;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    } else {
        arg0->state = 3;
    }

    if (HP_VALUE(g_Player.hp) >= engine_obj.max_hp) {
        EASY_HP_SET(engine_obj.max_hp * 2 - 1);
        g_Player.hp = engine_obj.max_hp | player_status;
    }

    g_Player.weapon_energy[0] += arg1;
    if ((s8)g_Player.weapon_energy[0] > 0x30) {
        g_Player.weapon_energy[0] = 0x30;
    }

    for (arg1 = 0; arg1 < 2; arg1++) {
        if (engine_obj.collected_upgrades & (0x1000 << arg1)) {
            value = TANK_VALUE(engine_obj.sub_tanks[arg1]);
            if (value < 0x20) {
                value += arg2;
                if (value >= 0x20) {
                    value = 0x20;
                    func_8001540C(0, 0x18, 0);
                } else {
                    func_8001540C(0, 0x17, 0);
                }
                value |= 0x80;
                engine_obj.sub_tanks[arg1] = value;
                return;
            }
        }
    }
}
#endif
// pickup_check_collect
#ifdef MMX4_PC
void func_800C00BC(struct ItemObj* arg0)
{
    struct CollisionObj* player;
    u16 flag;
    s32 shift;

    if (g_Player.ride_state == 0) {
        player = (struct CollisionObj*)&g_Player;
        if (!HP_VALUE(g_Player.hp)) {
            return;
        }
    } else {
        player = (struct CollisionObj*)&qux_object;
        if (!(HP_VALUE(qux_object.hp))) {
            return;
        }
    }
    if (!func_8002C160((struct CollisionObj*)arg0, player)) {
        return;
    }

    arg0->unk5 = 0;
    switch (arg0->unk7C.value) {
    case 0:
        pickup_collect_health(arg0, 4, 1);
        break;
    case 1:
        pickup_collect_health(arg0, 0x10, 2);
        break;
    case 2:
    case 3:
    case 6:
        func_800BFCC0(arg0, arg0->unk7C.value);
        arg0->state = 3;
        break;
    case 4:
        engine_obj.player_lives++;
        if (engine_obj.player_lives >= 10) {
            engine_obj.player_lives = 9;
        } else {
            func_8001540C(0, 0x15, 0);
        }
        arg0->state = 3;
        break;
    case 5:
        pickup_collect_health(arg0, engine_obj.max_hp, 4);
        break;
    case 7:
        flag = engine_obj.collected_upgrades;
        if ((flag & 0xFF) == 0xFF) {
            arg0->state = 3;
            break;
        }
        shift = arg0->unk2 - 7;
        if (flag & (1 << shift)) {
            arg0->state = 3;
            break;
        }
        engine_obj.collected_upgrades = flag | (1 << shift);
        engine_obj.max_hp += 2;
        func_8001540C(0, 0x15, 0);
        arg0->state = 3;
        break;
    case 8:
        flag = engine_obj.collected_upgrades;
        if ((flag & 0x3000) == 0x3000) {
            break;
        }
        shift = arg0->unk2 - 15;
        if (flag & (0x1000 << shift)) {
            break;
        }
        engine_obj.collected_upgrades = flag | (0x1000 << shift);
        arg0->state = 3;
        engine_obj.sub_tanks[arg0->unk2 == 15 ? 0 : 1] = -0x80;
        func_8001540C(0, 0x15, 0);
        break;
    case 9:
        flag = engine_obj.collected_upgrades;
        if ((flag & 0x4000) || (flag & (0x4000 << (arg0->unk2 - 17)))) {
            break;
        }
        engine_obj.collected_upgrades = flag | (0x4000 << (arg0->unk2 - 17));
        arg0->state = 3;
        func_8001540C(0, 0x15, 0);
        engine_obj.sub_tanks[2] = 0;
        break;
    case 10:
        flag = engine_obj.collected_upgrades;
        if ((flag & 0x8000) || (flag & (0x8000 << (arg0->unk2 - 18)))) {
            break;
        }
        engine_obj.collected_upgrades = flag | (0x8000 << (arg0->unk2 - 18));
        arg0->state = 3;
        func_8001540C(0, 0x15, 0);
        break;
    default:
        arg0->state = 3;
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_02_pickup", func_800C00BC);
#endif

void set_objects_frozen(s8 arg0)
{
    engine_obj.unk10 = arg0;
    engine_obj.unk11 = arg0;
    engine_obj.unk12 = arg0;
    engine_obj.unk13 = arg0;
    engine_obj.unk14 = arg0;
    engine_obj.unk15 = arg0;
    engine_obj.unk16 = arg0;
    engine_obj.unk17 = arg0;
}

void (*pickup_state_funcs[])(struct ItemObj*) = {
    func_800BF76C,
    pickup_main,
    pickup_collected,
    pickup_despawn,
};
