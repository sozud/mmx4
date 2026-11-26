#include "test_runtime.h"
#include "main/misc/misc_18_ready_text.h"
#include "weapon_resources.h"

#ifdef MMX4_SATURN
#define READY_TEXT_SHADOW_PALETTE 0x10
#define READY_TEXT_LEAVE_PALETTE 0x01
#else
#define READY_TEXT_SHADOW_PALETTE 0x7840
#define READY_TEXT_LEAVE_PALETTE 0x7801
#endif

void ready_text_appear(struct MiscObj*);
void ready_text_bounce(struct MiscObj*);
void ready_text_leave(struct MiscObj*);
void ready_text_blink(struct MiscObj*);
extern u16 D_8013B940[16];
extern u8 ready_text_palette_cycle[];
static u16 bank[0x50][16];
static u16 palette[0x200];

static u32 ready_steps(u32 row)
{
    static const u8 appear_unk2[] = { 1, 0, 0, 0, 0, 1, 0 }, appear_unk54[] = { 0, 0, 2, 0, 0, 0, 0 };
    static const u8 appear_pos[] = { 0, 0, 0, 3, 13, 0, 0 };
    struct MiscObj obj;
    struct EffectObj owner;
    u32 i, j;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&engine_obj, 0, sizeof(engine_obj));
    for (i = 0; i < 0x50; i++)
        for (j = 0; j < 16; j++)
            bank[i][j] = i << 8 | j;
    for (i = 0; i < 0x200; i++)
        palette[i] = 0xEEEE;
    for (i = 0; i < 16; i++)
        D_8013B940[i] = 0x4000 + i;
    TEST_PALETTE = (u8*)palette;
    TEST_PALETTE_BANK = (u8*)bank;
    need_palette_load = 0;
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.x_pos.i.hi = 160;
    obj.y_pos.i.hi = 120;
    obj.ext.ready_text.owner = &owner;
    if (row <= 6) {
        owner.ext.unk_effect.unk16 = row <= 1;
        obj.unk2 = appear_unk2[row];
        obj.ext.ready_text.unk54 = appear_unk54[row];
        obj.ext.ready_text.palette_pos = appear_pos[row];
        obj.ext.ready_text.palette_cycle_done = row == 6;
        ready_text_appear(&obj);
        if (row <= 1) {
            assert(obj.unk5 == 1 && obj.ext.ready_text.unk54 == 8 && palette[16] == 0x3900 && need_palette_load == 1);
            assert(obj.x_vel.val == (row == 0 ? 0x4000 : -0x4000) && obj.y_vel.val == (row == 0 ? -0x8000 : 0x8000));
            assert(row == 1 || obj.unk42 == READY_TEXT_SHADOW_PALETTE);
        } else if (row == 2 || row >= 5) {
            assert(obj.unk5 == 0 && obj.ext.ready_text.unk54 == (row == 2 ? 1 : 0) && palette[16] == 0xEEEE);
        } else {
            assert(palette[16] == (0x39 + ready_text_palette_cycle[appear_pos[row]]) << 8 && palette[31] == palette[16] + 15);
            assert(obj.ext.ready_text.palette_pos == (row == 3 ? 4 : 0));
            assert(obj.ext.ready_text.palette_cycle_done == (row == 4));
        }
        return 1;
    }
    if (row <= 12) {
        obj.unk5 = 1;
        obj.unk2 = row == 9 || row == 11;
        obj.unk6 = row >= 11;
        obj.ext.ready_text.stay_up_timer = row == 7 ? 2 : 0;
        obj.ext.ready_text.unk54 = row == 8 ? 2 : 1;
        obj.y_vel.val = 0x8000;
        ready_text_bounce(&obj);
        if (row == 7) {
            assert(obj.ext.ready_text.stay_up_timer == 1 && obj.ext.ready_text.unk54 == 1);
        } else if (row == 8) {
            assert(obj.ext.ready_text.unk54 == 1 && obj.y_pos.val == (120 << 16) - 0x8000);
        } else if (row <= 10) {
            assert(obj.unk6 == 1 && obj.ext.ready_text.unk54 == 8 && obj.ext.ready_text.stay_up_timer == 30);
            assert(obj.x_vel.val == (row == 9 ? -0x4000 : 0x4000) && obj.y_vel.val == (row == 9 ? 0x8000 : -0x8000));
        } else {
            assert(obj.unk5 == 2 && obj.unk6 == 0 && obj.unk42 == READY_TEXT_LEAVE_PALETTE && engine_obj.unk1E == 1);
            assert(obj.x_vel.val == (row == 11 ? -0x100000 : 0x100000) && obj.y_vel.val == 0);
            assert(palette[0x100] == (row == 11 ? 0x4000 : 0xEEEE) && palette[0x10F] == (row == 11 ? 0x400F : 0xEEEE));
            assert(need_palette_load == (row == 11));
        }
        return 1;
    }
    if (row <= 16) {
        obj.unk5 = 2;
        obj.on_screen = row == 13;
        obj.x_vel.val = 0x100000;
        engine_obj.stage = row == 16 ? 2 : 5;
        engine_obj.checkpoint = row == 15;
        engine_obj.gameplay_locked = 1;
        ready_text_leave(&obj);
        assert(obj.state == (row == 13 ? 1 : 2) && obj.x_pos.i.hi == (row == 13 ? 176 : 160));
        assert(engine_obj.gameplay_locked == (row == 14 ? 0 : 1));
        return 1;
    }
    WEAPON_FRAME_COUNTER = row == 17 ? 0x10 : 0x0F;
    obj.on_screen = 1;
    ready_text_blink(&obj);
    assert(obj.on_screen == (row == 17));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "ready_steps", 0, 0, 19, ready_steps },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 19;
