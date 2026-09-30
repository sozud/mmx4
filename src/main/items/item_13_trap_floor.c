// ItemObj, item_object_update_funcs[13]
// 800C351C..800C3880
#include "common.h"

struct Item13AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item13AnimationStep trap_floor_anim_0[1] = {
    { 8, 0, 0, 0 },
};

struct Item13AnimationStep trap_floor_anim_1[7] = {
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 0x21, 1, 0, 7 },
};

struct Item13AnimationStep* trap_floor_animations[2] = {
    trap_floor_anim_0,
    trap_floor_anim_1,
};

void trap_floor_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    trap_floor_state_funcs[arg0->state](arg0);
    is_on_screen(arg0);
}

// trap_floor_init
void func_800C3578(struct ItemObj* arg0)
{
    s32 resource;
    s32 row;

    arg0->active = 0x49;
    arg0->unk16 = 7;
    arg0->unk40 = D_801406A8[func_8002938C(0x81)] >> 7;
    resource = func_8002938C(0x81);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    resource = func_8002938C(0x81);
    row = func_8002938C(0x81);
    arg0->unk42 = SOME_COORDINATE_CONVERSION_XY(resource, row);
    arg0->animation_table = (const u8* const*)trap_floor_animations;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk67 = arg0->unk15 = 0;
    arg0->unk68 = (struct Unk_unk68*)trap_floor_terrain_box;
    arg0->unk75 = 1;
    arg0->state = 1;
    arg0->unk5 = 0;
    set_animation(ANIMATED_OBJECT(arg0), 0);
}

void trap_floor_main(struct ItemObj* arg0)
{
    struct EngineObj* engine = &engine_obj;
    struct PlayerObj* player = &g_Player;

    if (arg0->unk5 == 0) {
        trap_floor_wait_stand(arg0, engine, player);
        return;
    }
    trap_floor_open(arg0, engine, player);
}

#ifdef MMX4_PC
#define ITEM13_PLAYER_EXTENT(bounds) \
    ((bounds) != NULL ? (bounds)->unk3 + (bounds)->unk1 : 0)
#else
#define ITEM13_PLAYER_EXTENT(bounds) ((bounds)->unk3 + (bounds)->unk1)
#endif

void trap_floor_wait_stand(struct ItemObj* self, struct EngineObj* engine,
    struct PlayerObj* player)
{
    s16 y_diff;
    struct Unk_unk68* player_bounds;
    struct Unk_unk68* item_bounds;

    y_diff = (u16)self->y_pos.i.hi - (u16)player->y_pos.i.hi;
    if (y_diff >= 0) {
        item_bounds = self->unk68;
        player_bounds = player->unk68;
        if (y_diff >= ITEM13_PLAYER_EXTENT(player_bounds) + (item_bounds->unk3 - item_bounds->unk1)) {
            if (engine->unk10 == 0) {
                engine->unk10 = 1;
                engine->unk11 = 1;
                engine->unk12 = 1;
                engine->unk13 = 1;
                engine->unk14 = 1;
            }
            set_animation(self, 1);
            func_8001540C(5, 2, self);
            if (self->unk2 != 0) {
                background_objects[0].unk28 = 0x100;
            }
            self->unk5++;
        }
    }
}

void trap_floor_open(struct ItemObj* arg0, struct EngineObj* arg1,
    struct PlayerObj* arg2)
{
    if (arg0->animation_step.fields.event == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
    } else {
        if (arg1->unk10 != 0) {
            arg1->unk10 = 0;
            arg1->unk11 = 0;
            arg1->unk12 = 0;
            arg1->unk13 = 0;
            arg1->unk14 = 0;
        }
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void trap_floor_opened(struct ItemObj* arg0)
{
    u8 type;

    collide_with_players(PLAYER_OBJECT(arg0));

    type = 7;
    if (engine_obj.substage != 0) {
        type = 0x10;
    }

    apply_tile_effect(type, (s16)(arg0->x_pos.u.hi - 0x10),
        arg0->y_pos.i.hi);
}

void (*trap_floor_state_funcs[])(struct ItemObj*) = {
    func_800C3578,
    trap_floor_main,
    trap_floor_opened,
};

u8 trap_floor_terrain_box[4] = { 0, 8, 0x20, 0x10 };
