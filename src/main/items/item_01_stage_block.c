// ItemObj, item_object_update_funcs[1]
// 800BEBB4..800BF730
#include "common.h"
#include "main/items/item_01_stage_block.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/misc/misc_02_rubble.h"
#include "main/objects.h"
#include "main/stage_objects.h"

extern u8 stage_block_debris[16];

// stage_block_state_funcs
extern void (*stage_block_state_funcs[])(struct ItemObj*);

void stage_block_main(struct ItemObj*);
void stage_block_destroyed(struct ItemObj*);
void stage_block_despawn(struct ItemObj*);

// stage_block_step_funcs
extern void (*stage_block_step_funcs[])(struct ItemObj*);
void stage_block_wait_trigger(struct ItemObj*);

void stage_block_stop(struct ItemObj*);
#include "weapon_resources.h"

void stage_block_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    stage_block_state_funcs[arg0->state](arg0);
}

// stage_block_init
struct Item01DebrisPosition {
    s16 x;
    s16 y;
};

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800BEBFC(struct ItemObj* arg0);
void func_800BEFCC(struct ItemObj* arg0);
void func_800BF1FC(struct ItemObj* arg0);
void func_800BF638(struct BaseObj* arg0, s8 arg1, s16 arg2, s16 arg3);
extern u8 drop_item_table[24][6];
extern struct Unk_unk68 D_80108504[];
extern u8 stage_block_boxes[60];
extern struct Item01DebrisPosition stage_block_spawn_positions[6];
extern ret_u8 func_8002938C(s32);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800BEBFC(struct ItemObj* arg0)
{
    u8 index = (u8)arg0->unk2;
    const struct Item01StageEntry* entry = &stage_block_entries[index];

    arg0->active = 1;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_pos.i.hi = entry->x;
    arg0->y_pos.i.hi = entry->y;
    arg0->animation_step.fields.frame_index = entry->flags_and_palette & 0x3F;
    arg0->y_vel.val = index == 9 ? 0x40000 : 0;
    arg0->unk2C = entry->velocity;
    arg0->unk40 = SATURN_ALT(0x1500, OBJECT_STAGE_TEXTURE(8));
    if (index == 8 || index == 9)
        arg0->unk42 = OBJECT_CLUT(0x7941);
    else if (index == 13)
        arg0->unk42 = OBJECT_CLUT(0x79C4);
    else
        arg0->unk42 = OBJECT_CLUT(0x7983);
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->unk68 = (struct Unk_unk68*)&stage_block_bounds[index];
    arg0->unk5C = 0x10;
    arg0->unk61 = 0;
    arg0->unk75 = 1;
    arg0->unk54 = &stage_block_boxes[index * 4];
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 8);
    if (index == 1)
        arg0->unk66 = 1;
    arg0->unk58 = (const u8*)D_80108504;
    arg0->tail_ext.unk1.unk84.previous_value = 0;
    arg0->tail_ext.unk1.unk88 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_01_stage_block", func_800BEBFC);
#endif

void stage_block_main(struct ItemObj* arg0)
{
    s32 collision;
    s8 index;

    if (arg0->unk2 == 13) {
        arg0->unk76 = -1;
    }
    stage_block_step_funcs[arg0->unk5](arg0);
    update_on_screen(BASE_OBJECT(arg0), stage_block_bounds[arg0->unk2].width, stage_block_bounds[arg0->unk2].height);
    collide_with_players(PLAYER_OBJECT(arg0));
    index = arg0->unk2;
    if (!((u8)stage_block_entries[index].flags_and_palette & 0x80) && (index != 12 || arg0->unk5 == 3)) {
        collision = func_8002DD04(MAIN_OBJECT(arg0));
        if (collision < 0) {
            if (arg0->unk2 == 12) {
                apply_tile_effect((u8)stage_block_entries[12].sound_id, 0, 0);
            }
            arg0->on_screen = 0;
            arg0->unk7C.timer = 60;
            arg0->state++;
            spawn_rubble(15, stage_block_debris, arg0, 0);
            return;
        }
        if (collision > 0) {
            arg0->unk42 |= 0x8000;
        } else {
            arg0->unk42 &= 0x7FFF;
        }
    }
}

void stage_block_wait_trigger(struct ItemObj* self)
{
    s8 index;

    index = self->unk2;
    if (g_Player.x_pos.i.hi < stage_block_entries[index].left) {
        return;
    }
    if (index == 9) {
        func_8001540C(5, 1, NULL);
    }
    if (self->unk2 == 0xD) {
        func_8001540C(5, 0, NULL);
    }
    start_screen_shake_x(0x18, 3, 1);
    self->ext.timer = 1;
    self->unk5 = (u8)self->unk5 + 1;
    if (self->unk2 == 0xD) {
        func_800B10E4(0x21, 0xE10, 0x1E0, 0xF10, 0x1F0, 6);
        func_800B10E4(0x22, 0xE10, 0x1E0, 0xF10, 0x1F0, 6);
    }
}

// stage_block_fall
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/items/item_01_stage_block", func_800BEFCC);
#else
void func_800BEFCC(struct ItemObj* arg0)
{

    if (--arg0->ext.timer == 0) {
        switch (arg0->unk2) {
        case 8:
            func_800B10E4(0x21, 0xA40, 0x1D0, 0xB80, 0x1F0, 1);
            func_800B10E4(0x22, 0xA40, 0x1D0, 0xB80, 0x1F0, 1);
            break;
        case 9:
            func_800B10E4(0x21, 0xB80, 0x1D0, 0xC40, 0x1F0, 1);
            func_800B10E4(0x22, 0xB80, 0x1D0, 0xC40, 0x1F0, 1);
            break;
        }
        arg0->ext.timer = 4;
    }

    if ((arg0->unk2 == 5 || arg0->unk2 == 8) && arg0->tail_ext.unk1.unk84.previous_value == 0) {
        if (arg0->unk2 == 5 && arg0->tail_ext.unk1.unk88 == 0 && arg0->y_pos.i.hi >= 0x1C0) {
            func_8001540C(5, 0, NULL);
            start_screen_shake_y(0x20, 4, 1);
            arg0->tail_ext.unk1.unk88++;
        }
        if (arg0->y_pos.i.hi >= stage_block_entries[arg0->unk2].trigger_x && !((u8)stage_block_entries[arg0->unk2].flags_and_palette & 0x40)) {
            apply_tile_effect((u8)stage_block_entries[arg0->unk2].sound_id, 0, 0);
            arg0->tail_ext.unk1.unk84.previous_value++;
        }
    }

    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 != 9) {
        if (arg0->y_pos.i.hi >= stage_block_entries[arg0->unk2].right) {
            arg0->y_pos.i.hi = stage_block_entries[arg0->unk2].right;
            arg0->ext.timer = 0;
            arg0->unk5++;
        }
    } else if (arg0->y_pos.i.hi <= stage_block_entries[arg0->unk2].right) {
        arg0->y_pos.i.hi = stage_block_entries[arg0->unk2].right;
        arg0->ext.timer = 0;
        arg0->unk5++;
    }
}
#endif

// stage_block_land
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800BF1FC(struct ItemObj* arg0)
{
    u8 kind = (u8)arg0->unk2;
    const struct Item01StageEntry* entry = &stage_block_entries[kind];
    int first;
    int last;
    int index;

    if (arg0->y_pos.i.hi == entry->trigger_x && !(entry->flags_and_palette & 0x40)) {
        apply_tile_effect((u8)entry->sound_id, 0, 0);
        if (kind != 3 && kind != 4)
            arg0->state = 3;
    }
    if (kind != 13 && kind != 5 && kind != 1 && kind != 11) {
        func_8001540C(5, 0, NULL);
        start_screen_shake_y(0x20, 4, 1);
    }
    arg0->unk5++;

    if ((kind >= 2 && kind <= 7) || kind == 11 || kind == 13) {
        func_800B0CA0(0x21, 2, (struct MainObj*)arg0, 0x18, 6);
        func_800B0CA0(0x22, 2, (struct MainObj*)arg0, 0x18, 6);
    }

    if (kind == 1) {
        first = 0;
        last = 1;
    } else if (kind == 10) {
        first = 1;
        last = 4;
    } else if (kind == 11) {
        first = 4;
        last = 6;
    } else {
        return;
    }

    for (index = first; index < last; index++) {
        struct MainObj* obj = find_free_main_obj();
        s32 resource;

        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 7;
        obj->unk2 = index == 3 ? 3 : 2;
        obj->x_pos.i.hi = stage_block_spawn_positions[index].x;
        obj->y_pos.i.hi = stage_block_spawn_positions[index].y;
        resource = func_8002938C(7);
        obj->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE((u8)resource));
        resource = func_8002938C(7);
        obj->unk42 = VISUAL_STAGE_PALETTE((u8)resource);
        resource = func_8002938C(7);
        obj->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES,
            (u8)resource);
    }
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_01_stage_block", func_800BF1FC);
#endif

void stage_block_stop(struct ItemObj* self)
{
    if ((self->unk2 == 5) || (self->unk2 == 0xD)) {
        self->state = 3;
    }
}

extern u32 stage_block_explosion_sounds[4];

void stage_block_destroyed(struct ItemObj* arg0)
{
    if (--arg0->unk7C.timer != 0) {
        if ((WEAPON_FRAME_COUNTER & 7) == 0) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0x1F, 0x1F);
        }
        if ((WEAPON_FRAME_COUNTER & 0xF) == 0) {
            func_8001540C(0, stage_block_explosion_sounds[get_random() & 3], arg0);
        }
    } else {
        arg0->unk5 = 0;
        arg0->state++;
    }
}

void stage_block_despawn(struct ItemObj* arg0)
{
    despawn_object_permanently(OBJECT_HEADER(arg0));
}

void drop_item(struct BaseObj* arg0, s8 arg1)
{
    func_800BF638(arg0, arg1, arg0->x_pos.i.hi, arg0->y_pos.i.hi);
}

// drop_item_at
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800BF638(struct BaseObj* arg0, s8 arg1, s16 arg2, s16 arg3)
{
    const u8* weights = &drop_item_table[0][0];
    s32 offset = (s8)arg1 * 6;
#ifdef MMX4_SATURN
    s32 roll;
#else
    s32 roll = get_random() & 0xFF;
#endif
    struct ItemObj* item;
    s32 index;
    s32 counter;

    if (engine_obj.stage == 5) {
        return;
    }
#ifdef MMX4_SATURN
    roll = get_random() & 0xFF;
#endif

    counter = 0xFF;
    do {
        counter++;
        index = counter & 0xFF;
        roll = (roll & 0xFF) - weights[index + (offset & 0xFF)];
    } while ((u32)(roll & 0xFFFF) < 0x100);

    if (index == 0) {
        return;
    }
    item = find_free_item_obj();
    if (item == NULL) {
        return;
    }
    item->active = 0x21;
    item->id = 2;
    item->unk2 = counter - 1;
    item->x_pos.i.hi = arg2;
    item->y_pos.i.hi = arg3;
    item->backref = NULL;
    item->unk7C.value = 0;
    item->bg_offset = arg0->bg_offset;
}
#else
INCLUDE_ASM("main/nonmatchings/items/item_01_stage_block", func_800BF638);
#endif

struct Item01StageEntry stage_block_entries[15] = {
    { 0x0240, 0x00E0, 0x0200, 0x0100, 0x0100, 0x0040, 0x0C00, 0x0000 },
    { 0x02F0, 0x00D8, 0x0250, 0x0130, 0x0130, 0x0081, 0x2C00, 0x0021 },
    { 0x0390, 0x00E0, 0x02F0, 0x01B0, 0x01B0, 0x0082, 0x1F00, 0x0000 },
    { 0x0430, 0x0140, 0x046B, 0x0197, 0x0197, 0x0003, 0x3D00, 0x0001 },
    { 0x04D0, 0x0140, 0x046B, 0x0197, 0x0197, 0x0003, 0x3D00, 0x0002 },
    { 0x0870, 0x0120, 0x07D0, 0x0230, 0x01C0, 0x0003, 0x2C00, 0x0003 },
    { 0x0930, 0x00E0, 0x08A0, 0x01B0, 0x01B0, 0x0085, 0x1C00, 0x0004 },
    { 0x09E0, 0x00E0, 0x0930, 0x01A0, 0x01A0, 0x0086, 0x1C00, 0x0005 },
    { 0x0AE0, 0x01A8, 0x0A90, 0x0228, 0x0208, 0x0087, 0x0800, 0x0006 },
    { 0x0BE0, 0x0228, 0x0BA0, 0x0198, 0x0198, 0x0088, 0x0D00, 0x0007 },
    { 0x0CA0, 0x0090, 0x0BE0, 0x0148, 0x0148, 0x0089, 0x2C00, 0x0008 },
    { 0x0DB0, 0x00B0, 0x0CE0, 0x0170, 0x0170, 0x008A, 0x1C00, 0x0009 },
    { 0x0DB0, 0x00A8, 0x0CE0, 0x0168, 0x0168, 0x004F, 0x1C00, 0x000A },
    { 0x0EA0, 0x01E0, 0x0EA0, 0x03D0, 0x03D0, 0x00D0, 0x5000, 0x0000 },
    { 0x02F0, 0x0130, 0x0250, 0x0188, 0x0188, 0x0053, 0x2C00, 0x0000 },
};

struct Item01SpriteBounds stage_block_bounds[15] = {
    { 0x00, 0x00, 0x40, 0x20 },
    { 0x00, 0xF8, 0x30, 0x48 },
    { 0x00, 0x08, 0x30, 0x40 },
    { 0x00, 0x08, 0x30, 0x30 },
    { 0x00, 0x08, 0x30, 0x30 },
    { 0x00, 0x00, 0x30, 0x40 },
    { 0x00, 0x08, 0x30, 0x28 },
    { 0x00, 0x08, 0x40, 0x38 },
    { 0x00, 0x10, 0x80, 0x58 },
    { 0x00, 0x10, 0x40, 0x68 },
    { 0x00, 0x00, 0x40, 0x48 },
    { 0x00, 0x00, 0x50, 0x70 },
    { 0x00, 0x00, 0x50, 0x28 },
    { 0x00, 0x08, 0x70, 0x18 },
    { 0x00, 0x00, 0x30, 0x38 },
};

u8 stage_block_boxes[60] = {
    0xC0,
    0xE0,
    0x80,
    0x40,
    0xD0,
    0xA8,
    0x60,
    0xB0,
    0xD0,
    0xB8,
    0x60,
    0x90,
    0xD0,
    0xC8,
    0x60,
    0x70,
    0xD0,
    0xC8,
    0x60,
    0x70,
    0xD0,
    0xC0,
    0x60,
    0x80,
    0xD0,
    0xD0,
    0x60,
    0x60,
    0xC0,
    0xC0,
    0x70,
    0x80,
    0x80,
    0xA8,
    0xFF,
    0xB0,
    0xC0,
    0x98,
    0x80,
    0xD0,
    0xC0,
    0xB8,
    0x80,
    0x90,
    0xB0,
    0xD0,
    0xA0,
    0x60,
    0xB0,
    0xD8,
    0xA0,
    0x50,
    0xB0,
    0xD8,
    0xA0,
    0x50,
    0xD0,
    0xD8,
    0x60,
    0x50,
};

u8 stage_block_debris[16] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x00,
};

struct Item01DebrisPosition stage_block_spawn_positions[6] = {
    { 0x02BF, 0x014C },
    { 0x0C5F, 0x0127 },
    { 0x0C5F, 0x017B },
    { 0x0CE0, 0x017B },
    { 0x0D5F, 0x0127 },
    { 0x0D5F, 0x01A7 },
};

void (*stage_block_state_funcs[])(struct ItemObj*) = {
    func_800BEBFC,
    stage_block_main,
    stage_block_destroyed,
    stage_block_despawn,
};

void (*stage_block_step_funcs[4])(struct ItemObj*) = {
    stage_block_wait_trigger,
    func_800BEFCC,
    func_800BF1FC,
    stage_block_stop,
};

u32 stage_block_explosion_sounds[4] = { 0, 1, 2, 3 };
