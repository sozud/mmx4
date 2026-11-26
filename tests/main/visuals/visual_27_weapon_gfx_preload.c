#include "test_runtime.h"
#include "main/visuals/visual_27_weapon_gfx_preload.h"
#include "support/player_gfx_archive.h"

static struct {
    u32 root[16];
    u32 bank[2];
    u16 stream[24];
} preload_archive;
static u32 preload(u32 row)
{
    struct VisualObj obj;
    u32 bank = (u32)((u8*)preload_archive.bank - (u8*)&preload_archive);
    gfx_archive_fill();
    memset(&preload_archive, 0, sizeof(preload_archive));
    memcpy(preload_archive.stream, gfx_archive.stream, sizeof(preload_archive.stream));
    preload_archive.root[6] = bank;
    preload_archive.root[9] = bank + 4;
    preload_archive.bank[0] = 1 << 20 | (u32)((u8*)preload_archive.stream - (u8*)&preload_archive.bank[0]);
    preload_archive.bank[1] = 1 << 20 | (u32)((u8*)preload_archive.stream - (u8*)&preload_archive.bank[1]);
    TEST_PLAYER_GFX = (u8*)&preload_archive;
    GFX_QUEUE_RESET();
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 27;
    obj.unk2 = row;
    weapon_gfx_preload_update(&obj);
    assert(obj.active == 0 && obj.previous_animation_index == GFX_DECODED_FRAME(0));
    return (u32)((u8*)obj.unk38 - (u8*)preload_archive.bank) | GFX_QUEUED() << 8;
}
static const u32 preload_expected[] = { GFX_ONE_UPLOAD >> 8, 4u | GFX_ONE_UPLOAD >> 8 };

const struct CTestGroup c_test_groups[] = {
    { "weapon_gfx_preload_entries", NULL, preload_expected, COUNT(preload_expected), preload },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(preload_expected);
