#include "test_runtime.h"
#include "main/shots/shot_00_dragon_shot.h"
#include "support/state_cases.h"
void dragon_shot_pulse(struct ShotObj*);
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
static const u32 dragon_shot_owner_animation_cases_expected[] = { 0x640201u, 0x640402u, 0xBE0A03u, 0x6E0A03u, 0xBE0A03u, 0x6E0A03u, 0x640C05u, 0x640E05u, 0x4D0006u, 0x4D0006u };

static struct WeaponObj pulse_owner;
#define ss state_room.shot
#define PULSE(ev, rel) (state_reset(0, 0, 0), memset(&pulse_owner, 0, sizeof(pulse_owner)), pulse_owner.x_pos.i.hi = 0x80, pulse_owner.y_pos.i.hi = 0x60, pulse_owner.unk42 = 0x8004, ss.active = 1, ss.state = 3, ss.unk7C = &pulse_owner, ss.animation_step.fields.event = ev, ss.animation_step.fields.relative_step = rel, dragon_shot_pulse(&ss), state_extra = ss.unk50.data == dragon_shot_pulse_hit_box)
static void dsp_glow(void)
{
    PULSE(0, 1);
}
static void dsp_strike(void) { PULSE(1, 1); }
static void dsp_end(void) { PULSE(0, -1); }

static void (*const dragon_shot_pulse_states_cases[])(void) = {
    dsp_glow,
    dsp_strike,
    dsp_end,
};
static const u32 dragon_shot_pulse_states_expected[] = { 3u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48004u, 0u, 0u, 3u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48004u, 1u, 0u, 4u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48004u, 0u, 0u };

static u32 test_dragon_shot_pulse_states(u32 row)
{
    return object_run(dragon_shot_pulse_states_cases[row], row, &dragon_shot_pulse_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "dragon_shot_pulse_states", 0, 0, COUNT(dragon_shot_pulse_states_cases), test_dragon_shot_pulse_states },
    { "dragon_shot_owner_animation", NULL, dragon_shot_owner_animation_cases_expected, COUNT(dragon_shot_owner_animation_cases_expected), dragon_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dragon_shot_pulse_states_cases) + COUNT(dragon_shot_owner_animation_cases_expected);
