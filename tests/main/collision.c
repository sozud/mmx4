#include "test_runtime.h"
#include "main/1CF60.h"
s32 func_8002BD58(struct MainObj*, struct MainObj*, s16*, s16*);

static u32 overlap_left(u8 facing)
{
    struct MainObj first, second;
    struct Unk_unk68 first_box = { 0, 0, 4, 4 };
    struct Unk_unk68 second_box = { 0, 0, 4, 4 };
    s16 x = -100, y = 100;
    s32 hit;
    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    first.attack_box = &first_box;
    second.hurt_box = &second_box;
    first.unk15 = second.unk15 = facing;
    first.x_pos.i.hi = first.y_pos.i.hi = 10;
    second.x_pos.i.hi = second.y_pos.i.hi = 8;
    hit = func_8002BD58(&first, &second, &x, &y);
    assert(hit == 1);
    assert(first.attack_box == &first_box && second.hurt_box == &second_box);
    assert(first.x_pos.i.hi == 10 && first.y_pos.i.hi == 10);
    assert(second.x_pos.i.hi == 8 && second.y_pos.i.hi == 8);
    return (u16)x | ((u32)(u16)y << 16);
}
static u32 normal_left(void)
{
    return overlap_left(0);
}
static u32 mirrored_left(void)
{
    return overlap_left(PLAYER_FACING_RIGHT);
}
static const CTestCase collision_output_edges_cases[] = {
    normal_left,
    mirrored_left,
};
static const u32 collision_output_edges_cases_expected[] = { 0xB000Bu, 0xB0009u };

#ifdef MMX4_PC
struct func_8002C36C_case {
    u32 slot;
    u32 expected[8];
};
static const struct func_8002C36C_case func_8002C36C_cases[] = {
    { 1, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 255, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_8002C36C(u32 row)
{
    const struct func_8002C36C_case* c = &func_8002C36C_cases[row];
    u32 observed_values[8];
    struct PlayerObj obj;
    struct PlayerObj argument_obj_1;
    struct Unk_unk68 child_0;
    struct Unk_unk68 child_1;
    s32 slot;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    slot = c->slot;
    obj.unk68 = NULL;
    argument_obj_1.unk68 = NULL;
    func_8002C36C(&obj, &argument_obj_1, slot);
    observed_values[0] = (u32)argument_obj_1.unk71;
    observed_values[1] = (u32)argument_obj_1.wall_climbable;
    observed_values[2] = (u32)obj.unk72;
    observed_values[3] = (u32)obj.unk73;
    observed_values[4] = (u32)OBJ_UNK74(obj);
    observed_values[5] = (u32)obj.unk76;
    observed_values[6] = (u32)obj.unk77;
    observed_values[7] = (u32)OBJ_UNK78(obj);
    return c_test_observe(0, row, observed_values, c->expected, 8);
}
#endif

static const u8 slope_heights[12][16] = {
    { 15, 15, 15, 15, 14, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 12 },
    { 11, 11, 11, 11, 10, 10, 10, 10, 9, 9, 9, 9, 8, 8, 8, 8 },
    { 7, 7, 7, 7, 6, 6, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4 },
    { 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 },
    { 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7 },
    { 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11 },
    { 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15 },
    { 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8 },
    { 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0 },
    { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7 },
    { 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15 },
};
static u32 slope_contact(u32 row)
{
    static const u8 samples[3] = { 0, 7, 15 };
    static u8 tilemap[4] = { 1, 1, 1, 1 };
    static u16 tiles[2][16][16];
    static u32 attributes[2] = { 0, C_TEST_PSX_WORD(9) };
    struct {
        u32 before;
        struct PlayerObj value;
        u32 after;
    } got, want;
    struct PlayerObj* obj = &got.value;
    struct PlayerObj* expected = &want.value;
    struct PlayerObj player_before = g_Player, entity_before = g_Entity;
    struct EngineObj engine_before = engine_obj;
    struct MainBssState main_before = main_bss_state;
    u32 type = row % 64, x = type % 16, air = (row / 64) % 2;
    u32 i, j, effective = type == 16 ? 9 : type, shape = effective & 15;
    s16 y = 64 + samples[row % 3], correction = 0;
    s32 result = 0;
    u8 flag = 0x20, touched = 0x40;
    s16 displacement = 1234;
    memset(&got, 0xA5, sizeof(got));
    got.before = 0x12345678;
    got.after = 0x87654321;
    obj->bg_offset = 0;
    obj->air_state = air;
    obj->y_pos.val = 200 * 65536 + 0xFEDC;
    obj->unk6C = 11;
    obj->unk6E = 5;
    obj->unk70 = 0x23;
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++)
            tiles[1][i][j] = 1;
    SP_BG_TILEMAP = tilemap;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 2;
    layout_size = 4;
    D_8013B7D8 = touched;
    D_8013B7DC = flag;
    D_8013B804 = displacement;
    want = got;
    if (type == 16) {
        expected->y_pos.i.hi -= 16;
        expected->unk6C = x;
        expected->unk6E = y & 15;
    }
    if (effective <= 28 && effective != 0 && shape >= 1 && shape <= 12) {
        touched = 1;
        correction = slope_heights[shape - 1][x] - (y & 15);
        if (!air || type == 16 || correction <= 0) {
            result = -1;
            expected->unk70 = 8;
            expected->y_pos.i.lo = 0;
            expected->y_pos.i.hi += correction;
        }
    } else if (effective == 33 || effective == 34 || effective == 56 || effective == 57
        || effective == 58 || effective == 60 || effective == 62 || effective == 63) {
        result = -1;
        flag |= 8;
        displacement = -expected->unk6E;
    }
    assert(func_8002CF98(obj, type, x, y) == result);
    c_test_same_words(&got, &want, sizeof(want));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&g_Entity, &entity_before, sizeof(g_Entity));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    assert(D_8013B7D8 == touched && D_8013B7DC == flag && D_8013B804 == displacement);
    for (i = 0; i < 4; i++)
        assert(tilemap[i] == 1);
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++)
            assert(tiles[0][i][j] == 0 && tiles[1][i][j] == 1);
    assert(attributes[0] == 0 && attributes[1] == C_TEST_PSX_WORD(9));
    return 1;
}

s32 func_8002BD58(struct MainObj*, struct MainObj*, s16*, s16*);

static struct MainObj first, second;

static u32 sweep(u32 row)
{
    static const u8 boxes[2][4] = { { 2, 1, 8, 6 }, { 0xFD, 0xFE, 5, 11 } };
    struct Unk_unk68 attack, hurt;
    u32 hash = 0, hits = 0;
    s32 dx, dy, b;
    s16 x, y;

    c_test_zero_words((u32*)&first, sizeof(first) / 4);
    c_test_zero_words((u32*)&second, sizeof(second) / 4);
    first.attack_box = &attack;
    second.hurt_box = &hurt;
    first.unk15 = row & 1 ? PLAYER_FACING_RIGHT : 0;
    second.unk15 = row & 2 ? PLAYER_FACING_RIGHT : 0;
    for (b = 0; b < 2; b++) {
        attack.unk0 = boxes[b][0];
        attack.unk1 = boxes[b][1];
        attack.unk2 = boxes[b][2];
        attack.unk3 = boxes[b][3];
        hurt.unk0 = boxes[1 - b][0];
        hurt.unk1 = boxes[1 - b][1];
        hurt.unk2 = boxes[1 - b][2];
        hurt.unk3 = boxes[1 - b][3];
        for (dx = -14; dx <= 14; dx += 2) {
            for (dy = -14; dy <= 14; dy += 4) {
                first.x_pos.i.hi = 100;
                first.y_pos.i.hi = 50;
                second.x_pos.i.hi = 100 + dx;
                second.y_pos.i.hi = 50 + dy;
                x = y = 0x7777;
                if (func_8002BD58(&first, &second, &x, &y)) {
                    hits++;
                    hash += 1;
                }
                hash = hash * 31 + (u16)x;
                hash = hash * 31 + (u16)y;
            }
        }
    }
    assert(hits != 0 && first.x_pos.i.hi == 100 && second.hurt_box == &hurt);
    return hash;
}

static u32 neither(void) { return sweep(0); }
static u32 attacker(void) { return sweep(1); }
static u32 target(void) { return sweep(2); }
static u32 both(void) { return sweep(3); }
static const CTestCase sweep_cases[] = { neither, attacker, target, both };
static const u32 sweep_expected[] = { 3092694172u, 3951215244u, 4272335052u, 1024630340u };

static u32 facing_right_attacker_misses_left_facing_target(void)
{
    struct Unk_unk68 attack = { 0, 0, 4, 4 }, hurt = { 0, 0, 4, 4 };
    c_test_zero_words((u32*)&first, sizeof(first) / 4);
    c_test_zero_words((u32*)&second, sizeof(second) / 4);
    first.attack_box = &attack;
    second.hurt_box = &hurt;
    first.unk15 = PLAYER_FACING_RIGHT;
    first.x_pos.i.hi = 10;
    second.x_pos.i.hi = 12;
    first.y_pos.i.hi = second.y_pos.i.hi = 40;
    assert(func_8002BB80(&first, &second) == 0);
    second.unk15 = PLAYER_FACING_RIGHT;
    assert(func_8002BB80(&first, &second) == 1);
    return 1;
}

static u32 second_object_without_bounds(void)
{
    struct Unk_unk68 bounds = { 0, 0, 8, 8 };
    struct CollisionObj a, b;
    c_test_zero_words((u32*)&a, sizeof(a) / 4);
    c_test_zero_words((u32*)&b, sizeof(b) / 4);
    a.collision_bounds = &bounds;
    assert(func_8002C160(&a, &b) == 0);
    b.collision_bounds = &bounds;
    assert(func_8002C160(&a, &b) == 1);
    return 1;
}

static const CTestCase bounds_cases[] = {
    facing_right_attacker_misses_left_facing_target,
    second_object_without_bounds,
};
static const u32 bounds_expected[] = { 1, 1 };

static const u32 slot_contact_expected[4][8] = {
#ifdef VERSION_SATURN_PROTO
    { 0x77, 0x02, 0x77, 0x66, 0x01, 0x66, 0x12, 0x5A },
    { 0x77, 0x00, 0x77, 0x66, 0x00, 0x66, 0x10, 0x11 },
    { 0x77, 0x02, 0x77, 0x66, 0x01, 0x66, 0x12, 0x5A },
    { 0x77, 0x00, 0x77, 0x66, 0x00, 0x66, 0x10, 0x11 },
#else
    { 0x77, 0x77, 0x02, 0x66, 0x66, 0x01, 0x12, 0x5A },
    { 0x77, 0x77, 0x00, 0x66, 0x66, 0x00, 0x10, 0x11 },
    { 0x77, 0x77, 0x77, 0x66, 0x66, 0x66, 0x12, 0x5A },
    { 0x77, 0x77, 0x77, 0x66, 0x66, 0x66, 0x10, 0x11 },
#endif
};
static u32 slot_contact(u32 row)
{
    struct Unk_unk68 box0 = { 0, 0, 4, 4 }, box1 = { 0, 0, 4, 4 };
    struct PlayerObj self, other;
    u32 observed[8];
    memset(&self, 0, sizeof(self));
    memset(&other, 0, sizeof(other));
    self.unk68 = &box0;
    other.unk68 = &box1;
    self.unk72 = self.unk73 = 0x77;
    self.unk76 = self.unk77 = 0x66;
#ifndef VERSION_SATURN_PROTO
    self.unk74 = 0x77;
    self.unk78 = 0x66;
#endif
    self.unk75 = 0x5A;
    other.wall_climbable = 0x11;
    other.unk71 = 0x10;
    self.x_pos.i.hi = 100;
    self.y_pos.i.hi = 50;
    other.x_pos.i.hi = 108;
    other.y_pos.i.hi = row & 1 ? 58 : 52;
    func_8002C36C(&self, &other, row < 2 ? 2 : 3);
    observed[0] = (u8)self.unk72;
    observed[1] = (u8)self.unk73;
#ifdef VERSION_SATURN_PROTO
    observed[2] = 0x77;
    observed[5] = 0x66;
#else
    observed[2] = (u8)self.unk74;
    observed[5] = (u8)self.unk78;
#endif
    observed[3] = (u8)self.unk76;
    observed[4] = (u8)self.unk77;
    observed[6] = (u8)other.unk71;
    observed[7] = (u8)other.wall_climbable;
    return c_test_observe(1, row, observed, slot_contact_expected[row], 8);
}

#ifdef MMX4_PC
static u32 slot2_without_bounds(u32 row)
{
    struct PlayerObj self, other;
    memset(&self, 0, sizeof(self));
    memset(&other, 0, sizeof(other));
    self.unk72 = self.unk73 = self.unk74 = 0x77;
    self.unk76 = self.unk77 = self.unk78 = 0x66;
    func_8002C36C(&self, &other, 2);
    assert(self.unk74 == 0 && self.unk78 == 0);
    assert(self.unk72 == 0x77 && self.unk73 == 0x77 && self.unk76 == 0x66 && self.unk77 == 0x66);
    return 1;
}
#define SLOT2_NULL_CASES 1
#else
#define slot2_without_bounds NULL
#define SLOT2_NULL_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "slope_contact", 0, 0, 128, slope_contact },
    { "collision_output_edges", collision_output_edges_cases, collision_output_edges_cases_expected, COUNT(collision_output_edges_cases), 0 },
#ifdef MMX4_PC
    { "func_8002C36C", 0, 0, 2, test_func_8002C36C },
#endif
    { "attack_hurt_facing_sweep", sweep_cases, sweep_expected, 4, NULL },
    { "bounds_checks", bounds_cases, bounds_expected, COUNT(bounds_cases), NULL },
    { "slot_contact", 0, 0, 4, slot_contact },
    { "slot2_without_bounds", 0, 0, SLOT2_NULL_CASES, slot2_without_bounds },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 128 + COUNT(collision_output_edges_cases) + 4 + COUNT(bounds_cases) + 4 + SLOT2_NULL_CASES
#ifdef MMX4_PC
    + 2
#endif
    ;
