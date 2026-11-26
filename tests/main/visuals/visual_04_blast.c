#include "test_runtime.h"
#include "main/visuals/visual_04_blast.h"

void func_800AF95C(struct ObjectHeader* arg0, s32 type, s32 x_range, s32 y_range, s32 divisor);
extern u8 D_8013B8E4;

static const struct {
    u16 seed;
    u8 divisor, toggle;
    u32 expected[3];
} box_cases[] = {
    { 0x1234, 0, 1, { 0x03010421u, 0x01F6026Au, 0x39EC0002u } },
    { 0x5678, 7, 0, { 0x02010421u, 0x005C027Bu, 0x1A1C0001u } },
};
static u32 box(u32 row)
{
    struct MainObj obj;
    struct VisualObj* blast = &visual_objects[0];
    u32 observed[3];
    memset(&obj, 0, sizeof(obj));
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    obj.x_pos.i.hi = 0x200;
    obj.y_pos.i.hi = 0x100;
    cur_random = box_cases[row].seed;
    D_8013B8E4 = box_cases[row].toggle;
    func_800AF95C(OBJECT_HEADER(&obj), 1, 0xFF, 0xFF, box_cases[row].divisor);
    assert(blast->unk16 == VISUAL_SATURN_LAYER(1) && visual_objects[1].active == 0);
    observed[0] = (u8)blast->active | (u32)(u8)blast->id << 8 | (u32)(u8)blast->unk2 << 16 | (u32)(u8)blast->unk5C.value << 24;
    observed[1] = (u16)blast->x_pos.i.hi | (u32)(u16)blast->y_pos.i.hi << 16;
    observed[2] = D_8013B8E4 | (u32)cur_random << 16;
    return c_test_observe(0, row, observed, box_cases[row].expected, 3);
}

#include "support/state_cases.h"
#include "support/sound_probe.h"
#ifdef MMX4_SATURN
#define BLAST_PALETTE 6
#else
#define BLAST_PALETTE (6 | 0x1E0 << 6)
#endif
extern u8* blast_animations[1];
static s32 blast_archive[4] = { 0x10, 0x14, 0x18, 0x1C };
#define sv state_room.visual
#define BLAST(st, setup) (state_reset(0, 0, 0), TEST_SPRITE_FRAMES = (u8*)blast_archive, sound_probe_begin_group(0), sv.active = 0x41, sv.state = st, sv.unk2 = 2, sv.x_pos.i.hi = 0x80, sv.y_pos.i.hi = 0x60, sv.unk5C.value = 0xFF, setup, blast_update(&sv), state_extra = (u16)sv.unk42 | (u32)(sv.unk3C == (u8*)blast_archive + 0x18) << 16)
static void bl_start(void)
{
    BLAST(0, 0);
    assert(sv.animation_table == (u32**)blast_animations && sv.unk17 == 0 && sv.unk42 == BLAST_PALETTE);
    SOUND_CHECK(sound_probe_id() == -1);
}
static void bl_start_sound(void)
{
    BLAST(0, sv.unk5C.value = 0x12);
    SOUND_CHECK(sound_probe_id() == 0x12);
}
static void bl_burning(void) { BLAST(1, sv.animation_step.fields.relative_step = 1); }
static void bl_burnt(void) { BLAST(1, sv.animation_step.fields.relative_step = -1); }

static void (*const bl_cases[])(void) = {
    bl_start,
    bl_start_sound,
    bl_burning,
    bl_burnt,
};
static const u32 bl_expected[] = {
    0x1u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x10000u | BLAST_PALETTE,
    0x10000u | BLAST_PALETTE,
    0u,
    0x1u,
    0xFF000241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x10000u | BLAST_PALETTE,
    0x10000u | BLAST_PALETTE,
    0u,
    0x1u,
    0x241u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
    0u,
    0u,
    0x800000u,
    0x600000u,
    0u,
    0u,
    0u,
    0x40000u,
    0u,
    0u,
};
static u32 test_bl(u32 row)
{
    return object_run(bl_cases[row], row, &bl_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "blast_steps", 0, 0, COUNT(bl_cases), test_bl },
    { "explosion_in_box_offsets_and_variants", NULL, NULL, COUNT(box_cases), box },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(box_cases) + COUNT(bl_cases);
