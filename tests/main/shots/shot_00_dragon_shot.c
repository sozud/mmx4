#include "test_runtime.h"
#include "main/shots/shot_00_dragon_shot.h"
extern union AnimationStep* D_800F9934[16];
extern u8 dragon_shot_flame_box[4], dragon_shot_pulse_hit_box[4], dragon_shot_bomb_box[4];
extern u8 dragon_shot_box_0[4], dragon_shot_box_1[4], dragon_shot_box_2[4];
extern u8 dragon_shot_box_3[4], dragon_shot_box_4[4], dragon_shot_box_5[4];

static const s8 kinds[10] = { 0, 1, 2, 2, 3, 3, 4, 4, -1, 5 };
static const u8 frame_bytes[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
static u32 dragon_case(u32 mode)
{
    struct ShotObj obj, expected;
    struct MainObj owner, expected_owner;
    struct BackgroundObj expected_backgrounds[3];
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 i, actual, animation = 0;
    s32 kind = kinds[mode];
    background_objects[0].x_pos.val = 50 * 65536 + 0x4567;
    background_objects[0].y_pos.val = 60 * 65536 + 0x6789;
    memcpy(expected_backgrounds, background_objects, sizeof(expected_backgrounds));
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&obj.unk84, 0xA5, sizeof(obj) - MMX4_OFFSET_OF(struct ShotObj, unk84));
    owner.active = 0x41;
    owner.id = 0;
    owner.state = 1;
    owner.unk15 = mode == 3 || mode == 5 ? 0x40 : 0;
    owner.unk40 = 0x1234;
    owner.unk42 = 0x9234;
    owner.unk7E = mode == 7 ? -1 : 0;
    owner.bg_offset = 0;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 120 * 65536 + 0x2345;
    owner.animation_table = (const u8* const*)D_800F9934;
    owner.sprite_frames = frame_bytes;
    owner.hurt_box = dragon_shot_box_1;
    obj.active = 0x41;
    obj.id = 0;
    obj.unk2 = kind;
    obj.state = 6;
    obj.unk5 = 9;
    obj.unk17 = 0;
    obj.previous_animation_index = 9;
    obj.unk16 = 22;
    obj.animation_table = owner.animation_table;
    obj.animation_cursor = (const u8*)D_800F9934[0];
    obj.animation_step = *D_800F9934[0];
    obj.x_pos.val = 77 * 65536 + 0xABCD;
    obj.y_pos.val = 88 * 65536 + 0x9876;
    obj.x_vel.val = 1234;
    obj.y_vel.val = 5678;
    obj.unk28 = 123;
    obj.unk2C = 456;
    obj.unk50.data = dragon_shot_box_1;
    obj.unk54 = dragon_shot_box_1;
    obj.unk68 = (struct Unk_unk68*)dragon_shot_box_2;
    obj.unk5C = 23;
    obj.unk60 = 4;
    obj.unk7C = (struct WeaponObj*)&owner;
    expected = obj;
    expected_owner = owner;
    expected.unk40 = owner.unk40;
    expected.unk42 = owner.unk42;
    expected.unk3C = (void*)owner.sprite_frames;
    expected.unk15 = owner.unk15;
    expected.unk68 = NULL;
    expected.unk54 = NULL;
    expected.unk5C = 0;
    if (kind >= 0 && kind <= 4) {
        expected.x_pos = owner.x_pos;
        expected.y_pos = owner.y_pos;
        expected.unk60 = 5;
        expected.unk16 = kind == 4 ? 6 : 1;
        if (kind <= 1) {
            expected.bg_offset = owner.bg_offset;
            expected.state = kind + 1;
            animation = kind == 0 ? 2 : 4;
            expected.unk50.data = kind == 0 ? dragon_shot_flame_box : dragon_shot_pulse_hit_box;
            expected_owner.hurt_box = kind == 0 ? dragon_shot_box_3 : dragon_shot_box_4;
        } else if (kind <= 3) {
            expected.state = 3;
            animation = 10;
            expected.bg_offset = 0;
            expected.unk42 = 0x1234;
            expected.unk68 = (struct Unk_unk68*)dragon_shot_box_2;
            expected.x_pos.val += background_objects[0].x_pos.val + (owner.unk15 ? -40 * 65536 : 40 * 65536);
            expected.y_pos.val += background_objects[0].y_pos.val;
            expected.x_vel.val = kind == 2 ? (owner.unk15 ? -0x38000 : 0x38000) : (owner.unk15 ? -0x28000 : 0x28000);
            expected.y_vel.val = 0x18000;
            expected.unk28 = 0;
            expected.unk2C = 0x1000;
            expected.unk50.data = dragon_shot_bomb_box;
        } else {
            expected.state = 5;
            expected.bg_offset = 0;
            animation = mode == 7 ? 14 : 12;
            expected.unk50.data = mode == 7 ? dragon_shot_box_0 : dragon_shot_box_1;
            if (mode == 7)
                expected_owner.hurt_box = dragon_shot_box_5;
        }
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)D_800F9934[animation];
        expected.animation_step = *D_800F9934[animation];
    }
    expected.on_screen = 1;
    func_800994DC(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&expected_owner)[i]);
    for (i = 0; i < sizeof(expected_backgrounds) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)expected_backgrounds)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    actual = (u8)obj.state | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.x_pos.i.hi << 16);
    return actual;
}
#define CASE(m)                                             \
    static u32 dragon_shot_owner_animation_dragon_##m(void) \
    {                                                       \
        return dragon_case(m);                              \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
CASE(8)
CASE(9)
#define ENTRY(m) dragon_shot_owner_animation_dragon_##m,
static const CTestCase dragon_shot_owner_animation_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) ENTRY(8) ENTRY(9) };
static const u32 dragon_shot_owner_animation_cases_expected[] = { 0x640201u, 0x640402u, 0xBE0A03u, 0x6E0A03u, 0xBE0A03u, 0x6E0A03u, 0x640C05u, 0x640E05u, 0x4D0006u, 0x4D0006u };
#undef CASE
#undef ENTRY

static const u32 func_800994DC_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_800994DC(u32 row)
{
    u32 observed_values[14];
    struct ShotObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0_present = 255;
    obj.unk2 = -1;
    background_objects[0].x_pos.val = -30396368;
    background_objects[0].y_pos.val = 0;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    func_800994DC(&obj);
    observed_values[0] = (u32)obj.bg_offset;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk15;
    observed_values[3] = (u32)obj.unk16;
    observed_values[4] = (u32)obj.unk28;
    observed_values[5] = (u32)obj.unk2C;
    observed_values[6] = (u32)obj.unk40;
    observed_values[7] = (u32)obj.unk42;
    observed_values[8] = (u32)obj.unk5C;
    observed_values[9] = (u32)obj.unk60;
    observed_values[10] = (u32)obj.x_pos.val;
    observed_values[11] = (u32)obj.x_vel.val;
    observed_values[12] = (u32)obj.y_pos.val;
    observed_values[13] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, func_800994DC_expected, 14);
}

const struct CTestGroup c_test_groups[] = {
    { "dragon_shot_owner_animation", dragon_shot_owner_animation_cases, dragon_shot_owner_animation_cases_expected, COUNT(dragon_shot_owner_animation_cases), 0 },
    { "func_800994DC", 0, 0, 1, test_func_800994DC },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dragon_shot_owner_animation_cases) + 1;
