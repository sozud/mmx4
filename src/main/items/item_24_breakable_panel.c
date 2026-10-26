// ItemObj, item_object_update_funcs[24]
// 800C6054..800C62DC
#include "common.h"
#include "main/items/item_24_breakable_panel.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/objects.h"

// breakable_panel_state_funcs
extern void (*breakable_panel_state_funcs[])(struct ItemObj*);

void breakable_panel_main(struct ItemObj*);
void breakable_panel_destroyed(struct ItemObj*);
#include "weapon_resources.h"

struct Item24AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item24AnimationStep breakable_panel_anim_steps[7] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
    { 1, 0, 0, 6 },
};

struct Item24AnimationStep* breakable_panel_animations[7] = {
    &breakable_panel_anim_steps[0],
    &breakable_panel_anim_steps[1],
    &breakable_panel_anim_steps[2],
    &breakable_panel_anim_steps[3],
    &breakable_panel_anim_steps[4],
    &breakable_panel_anim_steps[5],
    &breakable_panel_anim_steps[6],
};

u8 breakable_panel_debris[12] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 0, 0 };
u8 breakable_panel_terrain_box[4] = { 0, 0, 0x17, 0x26 };
u8 breakable_panel_hit_box[4] = { 0xEC, 0xDB, 0x27, 0x49 };

void breakable_panel_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    breakable_panel_state_funcs[arg0->state](arg0);
}

// breakable_panel_init

extern struct Unk_unk68 D_80108504[];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C609C(struct ItemObj* self);
extern ret_u8 func_8002938C(s32);
#endif

void func_800C609C(struct ItemObj* self)
{
    struct ItemObj* item;
    u32 index;
    s32 value;
    s32* frames;
    s32 offset;
    s8 bg_offset;

    self->state = 1;
    self->unk5 = 0;
    self->on_screen = 1;
    index = func_8002938C(0x9E);
    item = self;
    value = index * 4;
    item->unk40 = OBJECT_STAGE_TEXTURE(index);
    frames = SP_MENU_FRAMES;
    offset = frames[index];
    value = ((value + 0x18) & 0xF) | (((index + 6) / 4 + 0x1E0) << 6);
    item->unk42 = OBJECT_CLUT(value);
    item->animation_table = (const u8* const*)breakable_panel_animations;
    item->unk5C = 0x20;
    item->unk58 = (const u8*)D_80108504;
    item->unk15 = 0;
    item->unk61 = 0;
    item->unk75 = 1;
    item->sprite_frames = (const u8*)frames + offset;
    bg_offset = g_Player.bg_offset;
    item->unk16 = VISUAL_SATURN_LAYER(5);
    item->unk54 = (const u8*)breakable_panel_hit_box;
    item->unk68 = (struct Unk_unk68*)breakable_panel_terrain_box;
    item->bg_offset = bg_offset;
    set_animation(item, 0);
}

void breakable_panel_main(struct ItemObj* arg0)
{
    s32 collision;

    collision = func_8002DD04(MAIN_OBJECT(arg0));
    if (collision < 0) {
        arg0->on_screen = 0;
        spawn_debris(0xA, breakable_panel_debris, arg0);
        arg0->unk7C.timer = 0x1E;
        arg0->state++;
        return;
    }
    if (collision > 0) {
        arg0->unk42 = arg0->unk42 | 0x8000;
    } else {
        arg0->unk42 = arg0->unk42 & 0x7FFF;
    }
    collide_with_players(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

extern u32 breakable_panel_explosion_types[];

void breakable_panel_destroyed(struct ItemObj* arg0)
{
    if (--arg0->unk7C.timer != 0) {
        if ((WEAPON_FRAME_COUNTER & 7) == 0) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0xF, 0x3F);
        }
        if ((WEAPON_FRAME_COUNTER & 0xF) == 0) {
            ((s32(*)(s32, s32, void*))func_8001540C)(0, breakable_panel_explosion_types[get_random() & 3], arg0);
        }
    } else {
        despawn_object_permanently(OBJECT_HEADER(arg0));
    }
}

void (*breakable_panel_state_funcs[])(struct ItemObj*) = {
    func_800C609C,
    breakable_panel_main,
    breakable_panel_destroyed,
};

u32 breakable_panel_explosion_types[4] = { 0, 1, 2, 3 };
