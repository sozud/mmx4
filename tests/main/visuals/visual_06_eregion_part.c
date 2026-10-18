#include "test_runtime.h"
#include "main/visuals/visual_06_eregion_part.h"
#include "support/state_cases.h"
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
static const u32 eregion_slash_owner_events_cases_expected[] = { 0x1022041u, 0x30700u, 0x80700u, 0x80700u, 0x1032041u, 0x1070741u, 0x10C0741u };

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
static const u32 eregion_visual_default_owner_cases_expected[] = { 0x2FF41u, 0x40000000u, 0x20641u, 0x40000000u, 0x27F41u, 0x40000000u, 0x20241u };

static struct MainObj part_owner;
#define sv state_room.visual
#define PART(kind, st, setup) (state_reset(0, 0, 0), memset(&part_owner, 0, sizeof(part_owner)), part_owner.active = 1, part_owner.unk17 = 2, part_owner.x_pos.i.hi = 0x80, part_owner.y_pos.i.hi = 0x60, part_owner.unk42 = 0x8001, sv.active = 1, sv.unk2 = kind, sv.state = st, sv.unk50 = (struct PlayerObj*)&part_owner, setup, func_800AFF78(&sv), state_extra = sv.unk54 | sv.unk16 << 8 | part_owner.ext.main_8.queued_sound << 16)
static void ep_body_orphan(void)
{
    PART(1, 2, part_owner.state = 2);
}
static void ep_body_left(void) { PART(1, 2, part_owner.state = 1); }
static void ep_body_right(void) { PART(1, 2, (part_owner.state = 1, part_owner.unk15 = 0x40)); }
static void ep_mouth_gone(void) { PART(5, 2, part_owner.active = 0); }
static void ep_mouth_open(void) { PART(5, 2, 0); }
static void ep_mouth_hold(void) { PART(5, 2, sv.unk17 = 3); }
static void ep_mouth_busy(void) { PART(5, 2, part_owner.unk7 = 1); }
static void ep_mouth_hidden(void) { PART(5, 2, part_owner.unk7 = -1); }
static void ep_legs_gone(void) { PART(3, 3, part_owner.active = 0); }
static void ep_legs_hidden(void) { PART(3, 3, part_owner.unk7 = -1); }
static void ep_legs_busy(void) { PART(3, 3, part_owner.unk7 = 1); }
static void ep_legs_step(void) { PART(3, 3, 0); }
static void ep_legs_walk(void) { PART(3, 3, sv.unk17 = 2); }
static void ep_legs_stomp(void) { PART(4, 3, (part_owner.animation_step.fields.frame_index = 0x18, sv.animation_step.fields.event = 1)); }
static void ep_legs_stomp_b(void) { PART(4, 3, (part_owner.animation_step.fields.frame_index = 0x1B, sv.unk17 = 3, sv.animation_step.fields.event = 1, sv.unk54 = 1)); }
static void ep_legs_stomp_c(void) { PART(4, 3, part_owner.animation_step.fields.frame_index = 0x1C); }
static void ep_legs_stomp_d(void) { PART(4, 3, part_owner.animation_step.fields.frame_index = 0x1D); }
static void ep_legs_plain(void) { PART(4, 3, part_owner.animation_step.fields.frame_index = 2); }
static void ep_mirror_gone(void) { PART(5, 4, part_owner.active = 0); }
static void ep_mirror_sync(void) { PART(5, 4, part_owner.animation_step.fields.frame_index = 3); }
static void ep_mirror_hidden(void) { PART(5, 4, part_owner.unk7 = -1); }

static void (*const eregion_part_states_cases[])(void) = {
    ep_body_orphan,
    ep_body_left,
    ep_body_right,
    ep_mouth_gone,
    ep_mouth_open,
    ep_mouth_hold,
    ep_mouth_busy,
    ep_mouth_hidden,
    ep_legs_gone,
    ep_legs_hidden,
    ep_legs_busy,
    ep_legs_step,
    ep_legs_walk,
    ep_legs_stomp,
    ep_legs_stomp_b,
    ep_legs_stomp_c,
    ep_legs_stomp_d,
    ep_legs_plain,
    ep_mirror_gone,
    ep_mirror_sync,
    ep_mirror_hidden,
};
static const u32 eregion_part_states_expected[] = { 0u, 0u, 0x350000u, 0x620000u, 0u, 0u, 0u, 0x58001u, 0u, 0u, 2u, 0xFF000101u, 0x350000u, 0x620000u, 0u, 0u, 0u, 0x58001u, 0u, 0u, 2u, 0xFF400101u, 0xCB0000u, 0x620000u, 0u, 0u, 0u, 0x58001u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 2u, 0xFF000501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 2u, 0x501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0u, 2u, 0x501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 2u, 0x501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 0u, 0u, 0x7A0000u, 0x120000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 3u, 0x301u, 0x7A0000u, 0x120000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 3u, 0x301u, 0x7A0000u, 0x120000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 3u, 0xFF000301u, 0x7A0000u, 0x120000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 3u, 0x301u, 0x7A0000u, 0x120000u, 0u, 0u, 0u, 0x48000u, 0u, 0u, 3u, 0xFF000401u, 0xB60000u, 0x330000u, 0u, 0u, 0u, 0x58000u, 0x700u, 0u, 3u, 0x401u, 0xB70000u, 0x330000u, 0u, 0u, 0u, 0x48000u, 0x1A0700u, 0u, 3u, 0xFF000401u, 0xD50000u, 0x2D0000u, 0u, 0u, 0u, 0x58000u, 0x700u, 0u, 3u, 0xFF000401u, 0xD70000u, 0x2C0000u, 0u, 0u, 0u, 0x58000u, 0x700u, 0u, 3u, 0xFF000401u, 0xC90000u, 0x200000u, 0u, 0u, 0u, 0x58000u, 0x500u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 4u, 0xFF000501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 4u, 0x501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0u };

static u32 test_eregion_part_states(u32 row)
{
    return object_run(eregion_part_states_cases[row], row, &eregion_part_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "eregion_part_states", 0, 0, COUNT(eregion_part_states_cases), test_eregion_part_states },
    { "eregion_slash_owner_events", NULL, eregion_slash_owner_events_cases_expected, COUNT(eregion_slash_owner_events_cases_expected), slash_case },
    { "eregion_visual_default_owner", NULL, eregion_visual_default_owner_cases_expected, COUNT(eregion_visual_default_owner_cases_expected), owner_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(eregion_part_states_cases) + COUNT(eregion_slash_owner_events_cases_expected) + COUNT(eregion_visual_default_owner_cases_expected);
