// ItemObj, item_object_update_funcs[25]
// 800C42EC..800C4544
#include "common.h"

void breakable_boulder_update(struct ItemObj* arg0)
{
    if (arg0->state == 0) {
        arg0->state++;
        arg0->unk58 = (const u8*)D_80106270;
        arg0->unk54 = breakable_boulder_hit_box;
        arg0->animation_table = (const u8* const*)D_8010DF48;
        arg0->bg_offset = g_Player.bg_offset;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x99)];
        arg0->unk40 = D_801406A8[func_8002938C(0x99)] >> 7;
        arg0->unk42 = SOME_COORDINATE_CONVERSION(func_8002938C(0x99));
        arg0->unk16 = 7;
        arg0->unk15 = 0;
    } else if (func_8002DD04(MAIN_OBJECT(arg0)) != 0) {
        apply_tile_effect(0x26, 0x430, 0x170);
        get_random();
        spawn_debris_offset(5, breakable_boulder_debris[0], (struct MiscObj*)arg0, FIXED(48), FIXED(32));
        spawn_debris_offset(5, breakable_boulder_debris[1], (struct MiscObj*)arg0, FIXED(-32), FIXED(16));
        spawn_debris_offset(5, breakable_boulder_debris[2], (struct MiscObj*)arg0, 0, 0);
        spawn_debris_offset(5, breakable_boulder_debris[3], (struct MiscObj*)arg0, FIXED(24), FIXED(-16));
        spawn_debris_offset(5, breakable_boulder_debris[0], (struct MiscObj*)arg0, FIXED(-24), FIXED(-32));
        spawn_debris_offset(5, breakable_boulder_debris[1], (struct MiscObj*)arg0, FIXED(16), FIXED(-24));
        spawn_debris_offset(5, breakable_boulder_debris[2], (struct MiscObj*)arg0, FIXED(-16), FIXED(24));
        despawn_object_permanently(OBJECT_HEADER(arg0));
    } else if (func_8002B1E8(BASE_OBJECT(arg0), 0x70, 0x50) == 1) {
        despawn_object(OBJECT_HEADER(arg0));
    }
}

u8 breakable_boulder_hit_box[4] = { 0xE0, 0xD0, 0x40, 0x60 };

u8 breakable_boulder_debris_data[4][8] = {
    { 0x0A, 0x0E, 0x11, 0x13, 0x0C, 0, 0, 0 },
    { 9, 0x0B, 0x10, 0x12, 0x0D, 0, 0, 0 },
    { 0x0F, 0x11, 0x0A, 0x13, 0x0B, 0, 0, 0 },
    { 0x0D, 0x10, 0x0C, 0x12, 0x0B, 0, 0, 0 },
};

u8* breakable_boulder_debris[4] = {
    breakable_boulder_debris_data[0],
    breakable_boulder_debris_data[1],
    breakable_boulder_debris_data[2],
    breakable_boulder_debris_data[3],
};
