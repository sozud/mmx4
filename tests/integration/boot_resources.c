#include "test_runtime.h"
#include "main/55C4.h"
#include "main/323C.h"

void ready_text_init(struct MiscObj*);
void func_8001DE54(struct GameInfo*);
extern const u32* ready_text_animations[];
extern u16 D_8013B940[16];
extern s16 D_800F2204[36];
extern union TitleScratch D_80169498;

static u32 archive[0x100], archive_expected[0x100];
static u16 palette[0x200], palette_expected[0x200];
static struct MiscObj expected_misc[64];

static u32 test_ready_archive(u32 row)
{
    static const s16 x[] = { 160, 160, 96, 208, 256 };
    static const s16 y[] = { 120, 120, 112, 192, 192 };
    static const u16 clut[] = { 0x7801, 0x7801, 0x7847, 0x7845, 0x7845 };
    static const u8 priority[] = { 17, 18, 16, 16, 16 };
    struct MiscObj obj, expected;
    struct EngineObj engine_expected;
    u16 saved[16];
    u32 i, character = row % 2, part = row / 2, animation = part < 2 ? 0 : part - 1;
    memset(archive, 0x35, sizeof(archive));
    archive[0x10 / 4] = 0x300;
    archive[0x24 / 4] = 0x80;
    memcpy(archive_expected, archive, sizeof(archive));
    TEST_SPRITE_FRAMES = (u8*)archive;
    TEST_PALETTE = (u8*)palette;
    for (i = 0; i < COUNT(palette); i++)
        palette[i] = 0x8000 + i;
    memcpy(palette_expected, palette, sizeof(palette));
    for (i = 0; i < 16; i++)
        D_8013B940[i] = saved[i] = 0x1230 + i;
    memset(&obj, 0x25, sizeof(obj));
    memset(&engine_obj, 0x27, sizeof(engine_obj));
    engine_obj.cur_character = character;
    engine_expected = engine_obj;
    obj.active = 0x41;
    obj.id = 18;
    obj.state = 0;
    obj.unk2 = part;
    expected = obj;
    expected.unk3C = (u8*)archive + (character == CHARACTER_X ? 0x80 : 0x300);
    expected.unk40 = 0x1E00;
    expected.animation_table = (u32**)ready_text_animations;
    expected.state = 1;
    expected.bg_offset = -1;
    expected.unk42 = clut[part];
    expected.x_pos.i.hi = x[part];
    expected.y_pos.i.hi = y[part];
    expected.unk16 = priority[part];
    expected.unk15 = 0;
    expected.x_vel.val = expected.y_vel.val = 0;
    expected.unk28 = expected.unk2C = 0;
    expected.ext.ready_text.unk54 = 0;
    expected.ext.ready_text.stay_up_timer = 0;
    expected.ext.ready_text.palette_pos = 0;
    expected.ext.ready_text.unk58 = 0;
    expected.ext.ready_text.palette_cycle_done = 0;
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (u32*)ready_text_animations[animation];
    expected.animation_step.packed = *ready_text_animations[animation];
    if (part == 1)
        for (i = 0; i < 16; i++) {
            saved[i] = palette[0x100 + i];
            palette_expected[0x100 + i] = i ? 0x8000 : 0;
        }
    need_palette_load = 0x20;
    ready_text_init(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_expected));
    c_test_same_words(archive, archive_expected, sizeof(archive));
    c_test_same_words(palette, palette_expected, sizeof(palette));
    c_test_same_words(D_8013B940, saved, sizeof(saved));
    assert(need_palette_load == (part == 1 ? 0x21 : 0x20));
    assert(TEST_SPRITE_FRAMES == (u8*)archive && TEST_PALETTE == (u8*)palette);
    return 1;
}

static u32 test_title_coordinates(u32 row)
{
    struct GameInfo info, expected;
    struct MiscObj owner;
    struct BackgroundObj backgrounds[3];
    union TitleScratch scratch;
    s16 coordinates[36];
    u32 i, ready = row % 2;
    memset(&info, 0x25, sizeof(info));
    memset(&owner, 0, sizeof(owner));
    memset(background_objects, 0x27, sizeof(background_objects));
    memset(misc_objects, 0x35, sizeof(misc_objects));
    memset(&D_80169498, row < 2 ? 0 : 0xA5, sizeof(D_80169498));
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    memcpy(expected_misc, misc_objects, sizeof(expected_misc));
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    memcpy(coordinates, D_800F2204, sizeof(coordinates));
    scratch = D_80169498;
    owner.state = ready ? 2 : 1;
    D_80139690 = OBJECT_HEADER(&owner);
    info.mode = 4;
    expected = info;
    backgrounds[1].x_pos.i.hi = 0x400;
    backgrounds[1].unk4C = 1;
    if (ready) {
        for (i = 0; i < 36; i++)
            scratch.sector[i] = (s32)coordinates[i] * 65536;
        scratch.title.settled = 1;
        backgrounds[0].unk3 = 1;
        expected.mode = 5;
    }
    func_8001DE54(&info);
    c_test_same_words(&info, &expected, sizeof(expected));
    c_test_same_words(&D_80169498, &scratch, sizeof(scratch));
    c_test_same_words(background_objects, backgrounds, sizeof(backgrounds));
    assert(c_test_word_difference((const u32*)misc_objects,
               (const u32*)expected_misc, sizeof(expected_misc) / 4)
        == 0);
    c_test_same_words(D_800F2204, coordinates, sizeof(coordinates));
    assert(D_80139690 == OBJECT_HEADER(&owner));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "ready_archive_relative_offsets", 0, 0, 10, test_ready_archive },
    { "title_signed_coordinates", 0, 0, 4, test_title_coordinates },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 10 + 4;
