#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/player_gfx_archive.h"
#include "main/visuals/visual_26_weapon_overlay.h"

static struct VisualObj overlay_owner;
#define ov state_room.visual
#define OVERLAY(st, kind, setup) (state_reset(0, 0, 0), GFX_QUEUE_RESET(), memset(&overlay_owner, 0, sizeof(overlay_owner)), overlay_owner.active = 1, overlay_owner.animation_table = (void*)state_table, overlay_owner.unk15 = PLAYER_FACING_RIGHT, overlay_owner.x_pos.i.hi = 0x90, overlay_owner.y_pos.i.hi = 0x70, ov.active = 1, ov.state = st, ov.unk2 = kind, ov.unk50 = &overlay_owner, setup, weapon_overlay_update(&ov), state_extra = ov.unk17 | (u32)ov.unk16 << 8 | GFX_QUEUED() << 16, ov.unk50 = NULL)
static void overlay_no_owner(void) { OVERLAY(1, 1, ov.unk50 = NULL); }
static void overlay_owner_gone(void) { OVERLAY(1, 1, overlay_owner.active = 0); }
static void overlay_init(void) { OVERLAY(0, 1, 0); }
static void overlay_decodes(void) { OVERLAY(1, 0, (gfx_archive_fill(), ov.unk38 = (u8*)gfx_archive.bank, ov.animation_step.fields.frame_index = 7, ov.previous_animation_index = 0xFF)); }
static void (*const overlay_cases[])(void) = {
    overlay_no_owner,
    overlay_owner_gone,
    overlay_init,
    overlay_decodes,
};
static const u32 overlay_expected[] = {
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x1u, 0xFF400101u, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x201u, 0x0u,
    0x1u, 0x1u | GFX_DECODED_FRAME(7) << 24, 0x900000u, 0x700000u, 0x0u, 0x0u, 0x0u, 0x40000u, GFX_ONE_UPLOAD, 0x0u,
};
static u32 test_overlay(u32 row)
{
    return object_run(overlay_cases[row], row, &overlay_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "weapon_overlay_states", 0, 0, COUNT(overlay_cases), test_overlay },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(overlay_cases);
