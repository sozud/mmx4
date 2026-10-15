#include "test_runtime.h"
extern union AnimationStep* D_800FAD68[26];

static u32 slash_case(u32 mode)
{
    struct MainObj owner, owner_expected;
    struct VisualObj obj, expected;
    struct PlayerObj player_expected;
    struct BackgroundObj background_before[3];
    u32 i, word = mode == 0 || mode == 4 ? 10 : mode == 1 ? 6
                                                          : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memcpy(background_before, background_objects, sizeof(background_before));
    owner.active = 0x41;
    owner.id = 8;
    owner.state = mode == 2 ? 2 : 1;
    owner.unk5 = mode == 3 ? 4 : 5;
    owner.ext.main_8.queued_sound = 7;
    owner.x_pos.val = 100 * 65536 + 0xBEEF;
    owner.y_pos.val = 200 * 65536 + 0xCAFE;
    obj.active = 0x41;
    obj.id = 6;
    obj.state = 1;
    obj.unk2 = mode == 5 ? 2 : 1;
    obj.unk5 = 3;
    obj.unk6 = 4;
    obj.unk7 = 5;
    obj.bg_offset = -1;
    obj.unk50 = PLAYER_OBJECT(&owner);
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (u32**)D_800FAD68;
    obj.animation_cursor = (u32*)&D_800FAD68[18][word];
    obj.animation_step = D_800FAD68[18][word];
    obj.unk17 = 18;
    obj.previous_animation_index = 7;
    if (mode == 6)
        obj.animation_step.fields.duration = 1;
    g_Player.update_delay = mode == 4 || mode == 5 ? 1 : 0;
    player_expected = g_Player;
    expected = obj;
    owner_expected = owner;
    if (mode == 0 || mode == 4)
        owner_expected.ext.main_8.queued_sound = 0x20;
    if (mode >= 1 && mode <= 3)
        memset(&expected, 0, 8);
    else {
        expected.on_screen = 1;
        if (mode != 4) {
            if (mode == 6) {
                expected.animation_cursor++;
                expected.animation_step = D_800FAD68[18][1];
            } else
                expected.animation_step.fields.duration--;
        }
    }
    eregion_part_slash(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_expected)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    assert(D_800FAD68[18][0].packed == 0x0C010008 && D_800FAD68[18][6].packed == 0x20010103 && D_800FAD68[18][10].packed == 0x20010203);
    return (u8)obj.active | ((u32)(u8)owner.ext.main_8.queued_sound << 8) | ((u32)obj.animation_step.fields.duration << 16) | ((u32)(u8)obj.on_screen << 24);
}
#define CASE(m)                                           \
    static u32 eregion_slash_owner_events_slash_##m(void) \
    {                                                     \
        return slash_case(m);                             \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
#define ENTRY(m) eregion_slash_owner_events_slash_##m,
static const CTestCase eregion_slash_owner_events_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) };
static const u32 eregion_slash_owner_events_cases_expected[] = { 0x1022041u, 0x30700u, 0x80700u, 0x80700u, 0x1032041u, 0x1070741u, 0x10C0741u };
#undef CASE
#undef ENTRY

static const s8 subtypes[7] = { -1, -1, 6, 6, 127, 127, 2 };
static u32 owner_case(u32 mode)
{
    struct MainObj owner, eregion_visual_default_owner_owner_before;
    struct VisualObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&owner, 0, sizeof(owner));
    memset(&obj, 0, sizeof(obj));
    owner.active = 0x41;
    owner.id = 8;
    owner.state = mode & 1 ? 2 : 1;
    owner.unk7 = -1;
    owner.unk15 = mode & 1 ? 0x40 : 0;
    owner.x_pos.val = 300 * 65536 + 0x1234;
    owner.y_pos.val = 100 * 65536 + 0x5678;
    owner.unk42 = 0x9234;
    obj.active = 0x41;
    obj.id = 6;
    obj.unk2 = subtypes[mode];
    obj.state = 2;
    obj.on_screen = 3;
    obj.unk5 = 4;
    obj.unk6 = 5;
    obj.unk7 = 6;
    obj.x_pos.val = 50 * 65536 + 0xBEEF;
    obj.y_pos.val = 60 * 65536 + 0xCAFE;
    obj.unk42 = 0x7777;
    obj.unk15 = 0x40;
    obj.unk50 = (struct PlayerObj*)&owner;
    obj.unk54 = 123;
    obj.unk56 = 321;
    obj.unk17 = 9;
    obj.animation_step.packed = 0x12345678;
    eregion_visual_default_owner_owner_before = owner;
    expected = obj;
    expected.x_pos = owner.x_pos;
    expected.y_pos = owner.y_pos;
    expected.on_screen = 0;
    expected.unk15 = owner.unk15;
    if (mode & 1)
        memset(&expected, 0, 8);
    func_800AFF78(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&eregion_visual_default_owner_owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return obj.active | ((u32)(u8)obj.unk2 << 8) | ((u32)(u8)obj.state << 16) | ((u32)obj.unk15 << 24);
}
#define CASE(m)                                             \
    static u32 eregion_visual_default_owner_owner_##m(void) \
    {                                                       \
        return owner_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
#define ENTRY(m) eregion_visual_default_owner_owner_##m,
static const CTestCase eregion_visual_default_owner_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) };
static const u32 eregion_visual_default_owner_cases_expected[] = { 0x2FF41u, 0x40000000u, 0x20641u, 0x40000000u, 0x27F41u, 0x40000000u, 0x20241u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "eregion_slash_owner_events", eregion_slash_owner_events_cases, eregion_slash_owner_events_cases_expected, COUNT(eregion_slash_owner_events_cases), 0 },
    { "eregion_visual_default_owner", eregion_visual_default_owner_cases, eregion_visual_default_owner_cases_expected, COUNT(eregion_visual_default_owner_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(eregion_slash_owner_events_cases) + COUNT(eregion_visual_default_owner_cases);
