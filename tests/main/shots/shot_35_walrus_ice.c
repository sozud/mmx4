#include "test_runtime.h"
#include "main/shots/shot_10_dragon_spread_shot.h"
#include "main/shots/shot_35_walrus_ice.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
void walrus_ice_lob_fall(struct ShotObj*);
void walrus_ice_ball(struct ShotObj*);
void walrus_ice_chunk(struct ShotObj*);
void walrus_ice_shard(struct ShotObj*);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

#define ICICLE_CASE(name, owner_state, ticks)                                             \
    static u32 name(void)                                                                 \
    {                                                                                     \
        struct ShotObj obj;                                                               \
        struct MainObj owner;                                                             \
        RECT offsets = { 11, 22, 33, 44 };                                                \
        u32 actual;                                                                       \
        memset(&obj, 0, sizeof(obj));                                                     \
        memset(&owner, 0, sizeof(owner));                                                 \
        memset(background_objects, 0, sizeof(background_objects));                        \
        background_objects[0].unk1E = 100;                                                \
        owner.unk6 = owner_state;                                                         \
        owner.ext.main_57.rect = &offsets;                                                \
        obj.unk7C = &owner;                                                               \
        obj.unk2 = 2;                                                                     \
        obj.timer = ticks;                                                                \
        obj.x_pos.i.hi = -10;                                                             \
        walrus_ice_icicle_wait_drop(&obj);                                                \
        assert(obj.unk7C == &owner && owner.ext.main_57.rect == &offsets);                \
        assert(owner.unk6 == owner_state && offsets.w == 33);                             \
        actual = obj.x_pos.u.hi | ((u32)(u8)obj.timer << 16) | ((u32)(u8)obj.unk6 << 24); \
        return actual;                                                                    \
    }
ICICLE_CASE(waiting, 0, 2)
ICICLE_CASE(expired, 0, 1)
ICICLE_CASE(owner_trigger, 5, 2)

static const CTestCase icicle_wait_cases[] = {
    waiting,
    expired,
    owner_trigger,
};
static const u32 icicle_wait_cases_expected[] = { 0x1FFF6u, 0x10F0095u, 0x10F0095u };
#undef ICICLE_CASE

static const u32 walrus_ice_ball_main_expected[] = { 6u, 0x80000000u, 0u, 0u, 0u, 0u };
static u32 test_walrus_ice_ball_main(u32 row)
{
    u32 observed_values[6];
    struct ShotObj obj;
    struct WeaponObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&misc_objects, 0, sizeof(misc_objects));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    obj.x_pos.val = -2147483648;
    obj.y_pos.val = 0;
    obj.unk6 = 0;
    child_0.unk5 = 0;
    obj.unk42 = 0;
    obj.unk7C = &child_0;
    walrus_ice_ball_main(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk18.val;
    observed_values[2] = (u32)obj.unk1C.val;
    observed_values[3] = (u32)obj.unk42;
    observed_values[4] = (u32)obj.unk5;
    observed_values[5] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, walrus_ice_ball_main_expected, 6);
}

#include "support/projectile_damage.h"
DAMAGE_CASE(2)
DAMAGE_CASE(3)
DAMAGE_CASE(4)
DAMAGE_CASE(5)
DAMAGE_CASE(6)
DAMAGE_CASE(7)
DAMAGE_CASE(8)
DAMAGE_CASE(9)
DAMAGE_CASE(10)
static const CTestCase walrus_ice_damage_cases[] = { DAMAGE_ENTRY(2) DAMAGE_ENTRY(3) DAMAGE_ENTRY(4) DAMAGE_ENTRY(5) DAMAGE_ENTRY(6) DAMAGE_ENTRY(7) DAMAGE_ENTRY(8) DAMAGE_ENTRY(9) DAMAGE_ENTRY(10) };

static const u32 walrus_ice_damage_cases_expected[] = { 0x12350A06u, 0x12350006u, 0x92350701u, 0x12350A06u, 0x12350006u, 0x92350701u, 0x12350506u, 0x12350006u, 0x92350201u };
#include "support/state_cases.h"

static struct MainObj walrus_owner;
#define ss state_room.shot
#define ICE(st, step, phase) (state_reset(step, phase, 0), memset(&walrus_owner, 0, sizeof(walrus_owner)), walrus_owner.x_pos.i.hi = 0x100, walrus_owner.y_pos.i.hi = 0x100, ss.state = st, ss.unk7C = (struct WeaponObj*)&walrus_owner, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define ICE_SEEN() (state_extra = (u16)ss.timer | (u32)(u8)ss.on_screen << 16 | (u32)(u8)shot_objects[5].unk2 << 24)
static void wi_chunk_init_left(void)
{
    ICE(3, 0, 0);
    walrus_ice_chunk(&ss);
    ICE_SEEN();
}
static void wi_chunk_init_right(void)
{
    ICE(3, 0, 0);
    ss.unk15 = 0x40;
    walrus_ice_chunk(&ss);
    ICE_SEEN();
}
static void wi_chunk_blink(void)
{
    ICE(3, 1, 0);
    ss.timer = 3;
    walrus_ice_chunk(&ss);
    ICE_SEEN();
}
static void wi_chunk_blink_off(void)
{
    ICE(3, 1, 0);
    ss.timer = 3;
    ss.on_screen = 1;
    walrus_ice_chunk(&ss);
    ICE_SEEN();
}
static void wi_chunk_armed(void)
{
    ICE(3, 1, 0);
    ss.timer = 1;
    walrus_ice_chunk(&ss);
    ICE_SEEN();
}
static void wi_chunk_land(void)
{
    ICE(3, 1, 1);
    ss.unk70 = 8;
    walrus_ice_chunk(&ss);
    ICE_SEEN();
}
static void wi_chunk_fall(void)
{
    ICE(3, 1, 1);
    ss.y_vel.val = -0x10000;
    walrus_ice_chunk(&ss);
}
static void wi_chunk_break(void)
{
    ICE(3, 1, 2);
    walrus_ice_chunk(&ss);
}
static void wi_ball_init_left(void)
{
    ICE(2, 0, 0);
    walrus_ice_ball(&ss);
    ICE_SEEN();
}
static void wi_ball_init_right(void)
{
    ICE(2, 0, 0);
    ss.unk15 = 0x40;
    walrus_ice_ball(&ss);
    ICE_SEEN();
}
static void wi_shard_stuck(void)
{
    ICE(5, 1, 2);
    ss.timer = 2;
    walrus_ice_shard(&ss);
    ICE_SEEN();
}
static void wi_shard_stuck_done(void)
{
    ICE(5, 1, 2);
    ss.timer = 1;
    walrus_ice_shard(&ss);
    ICE_SEEN();
}
static void wi_shard_blink(void)
{
    ICE(5, 1, 3);
    ss.timer = 3;
    walrus_ice_shard(&ss);
    ICE_SEEN();
}
static void wi_shard_blink_off(void)
{
    ICE(5, 1, 3);
    ss.timer = 3;
    ss.on_screen = 1;
    walrus_ice_shard(&ss);
    ICE_SEEN();
}
static void wi_shard_melt(void)
{
    ICE(5, 1, 3);
    ss.timer = 1;
    walrus_ice_shard(&ss);
}
static void wi_shard_wall_left(void)
{
    ICE(5, 1, 1);
    ss.unk70 = 2;
    walrus_ice_shard(&ss);
    ICE_SEEN();
}
static void wi_shard_wall_right(void)
{
    ICE(5, 1, 1);
    ss.unk70 = 1;
    walrus_ice_shard(&ss);
    ICE_SEEN();
}
static void wi_shard_floor(void)
{
    ICE(5, 1, 1);
    ss.unk70 = 8;
    walrus_ice_shard(&ss);
    ICE_SEEN();
}
static void wi_shard_away(void)
{
    ICE(5, 1, 1);
    ss.x_pos.i.hi = 0x1000;
    walrus_ice_shard(&ss);
}
static void wi_shard_owner_gone(void)
{
    ICE(5, 1, 2);
    ss.timer = 2;
    walrus_owner.state = 2;
    walrus_ice_shard(&ss);
}
static void wi_shard_hit(void)
{
    ICE(5, 1, 2);
    ss.timer = 2;
    so.hp = 5;
    state_hit(&so, 0, 0, 1);
    walrus_ice_shard(&ss);
}
static void wi_lob_init_fore(void)
{
    ICE(4, 0, 0);
    ss.unk2 = 1;
    walrus_ice_lob(&ss);
}
static void wi_lob_init_back(void)
{
    ICE(4, 0, 0);
    ss.unk2 = 4;
    walrus_ice_lob(&ss);
}
static void wi_lob_land(void)
{
    ICE(4, 1, 0);
    ss.unk70 = 8;
    walrus_ice_lob(&ss);
}
static void wi_lob_fall(void)
{
    ICE(4, 1, 0);
    ss.y_vel.val = 0x10000;
    walrus_ice_lob(&ss);
}

static void (*const walrus_ice_states_cases[])(void) = {
    wi_chunk_init_left,
    wi_chunk_init_right,
    wi_chunk_blink,
    wi_chunk_blink_off,
    wi_chunk_armed,
    wi_chunk_land,
    wi_chunk_fall,
    wi_chunk_break,
    wi_ball_init_left,
    wi_ball_init_right,
    wi_shard_stuck,
    wi_shard_stuck_done,
    wi_shard_blink,
    wi_shard_blink_off,
    wi_shard_melt,
    wi_shard_wall_left,
    wi_shard_wall_right,
    wi_shard_floor,
    wi_shard_away,
    wi_shard_owner_gone,
    wi_shard_hit,
    wi_lob_init_fore,
    wi_lob_init_back,
    wi_lob_land,
    wi_lob_fall,
};
static const u32 walrus_ice_states_expected[] = { 0x103u, 0xFF000000u, 0x700000u, 0xD00000u, 0u, 0u, 0x480000u, 0x50000u, 0x60u, 0u, 0x103u, 0xFF400000u, 0x1900000u, 0xD00000u, 0u, 0u, 0x480000u, 0x50000u, 0x60u, 0u, 0x103u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x10002u, 0u, 0x103u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0x10103u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20103u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x35010000u, 0x41410000u, 0x10103u, 0u, 0x800000u, 0x610000u, 0u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0u, 6u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x102u, 0xFF000000u, 0xB00000u, 0x1100000u, 0u, 0x38000u, 0u, 0x50000u, 0x60u, 0u, 0x102u, 0xFF400000u, 0x1500000u, 0x1100000u, 0u, 0x38000u, 0u, 0x50000u, 0x60u, 0u, 0x20105u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10001u, 0u, 0x30105u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10032u, 0u, 0x30105u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x10002u, 0u, 0x30105u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 6u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0x41000000u, 0x10105u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10000u, 0u, 0x10105u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10000u, 0u, 0x10105u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x10000u, 0u, 6u, 0u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 6u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0x41000000u, 0x20105u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x2100u, 0x104u, 0xFF000100u, 0x800000u, 0x600000u, 0x20000u, 0x68000u, 0x420000u, 0x50000u, 0u, 0u, 0x104u, 0xFF000400u, 0x800000u, 0x600000u, 0xFFFE0000u, 0x68000u, 0x420000u, 0x50000u, 0u, 0u, 0x104u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x104u, 0u, 0x800000u, 0x5F0000u, 0u, 0x10000u, 0u, 0x50000u, 0u, 0u };

static u32 test_walrus_ice_states(u32 row)
{
    return object_run(walrus_ice_states_cases[row], row, &walrus_ice_states_expected[row * 10]);
}

#define ss state_room.shot
#define LOB(attr) (state_reset(0, 0, 0), state_terrain(attr), ss.active = 1, ss.state = 5, ss.x_pos.i.hi = 0x40, ss.y_pos.i.hi = 0x40, ss.y_vel.val = -0x40000, ss.unk68 = &state_hit_box, walrus_ice_lob_fall(&ss), state_extra = ss.unk70)
static void wi_lob_drop_air(void)
{
    LOB(0);
}
static void wi_lob_drop_land(void) { LOB(0x38); }

static void (*const walrus_ice_lob_cases[])(void) = {
    wi_lob_drop_air,
    wi_lob_drop_land,
};
static const u32 walrus_ice_lob_expected[] = { 5u, 1u, 0x400000u, 0x440000u, 0u, 0xFFFC0000u, 0u, 0x50000u, 0u, 0u, 6u, 1u, 0x400000u, 0x440000u, 0u, 0xFFFC0000u, 0u, 0x50000u, 0xFu, 0x41000000u };

static u32 test_walrus_ice_lob(u32 row)
{
    return object_run(walrus_ice_lob_cases[row], row, &walrus_ice_lob_expected[row * 10]);
}

extern void* frost_walrus_animations[];
static const s16 offsets[] = { -19, 36 };
static struct VisualObj visuals_expected[32];
static u32 form(u32 row)
{
    struct ShotObj obj, expected, *current = SP_CUR_SHOT_OBJ;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 type = row % 3, terminal = row / 3 % 2, face = row / 6 % 2, stopped = row / 12 % 2, capacity = row / 24, i;
    u32 animation = type == 2 ? 9 : 8, frame = terminal ? type == 2 ? 6 : 3 : 0;
    const union AnimationStep* commands = frost_walrus_animations[animation];
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 32; i++)
        visual_objects[i].active = i < capacity ? 0 : 1;
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    owner.active = 0x41;
    owner.id = 57;
    owner.state = 1;
    owner.unk5 = stopped ? 10 : 4;
    owner.unk15 = face ? 0x40 : 0;
    owner.unk42 = 0x9234;
    owner.x_pos.val = 160 * 65536 + 0x1234;
    owner.y_pos.val = 120 * 65536 + 0x5678;
    owner_before = owner;
    obj.active = 0x41;
    obj.id = 35;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0;
    obj.unk2 = type;
    obj.on_screen = 7;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.animation_table = (u32**)frost_walrus_animations;
    set_animation(&obj, animation);
    obj.animation_cursor = (u32*)&commands[frame];
    obj.animation_step = commands[frame];
    assert(obj.animation_step.packed == (terminal ? 0x2C000002 : type == 2 ? 0x33010002
                                                                           : 0x2F010002));
    expected = obj;
    expected.x_pos = owner.x_pos;
    expected.y_pos = owner.y_pos;
    expected.unk42 = owner.unk42;
    expected.animation_step.fields.duration = 1;
    if (stopped) {
        expected.state = 6;
        expected.unk5 = expected.unk6 = 0;
    } else {
        if (type & 1)
            expected.on_screen = 1;
        if (terminal) {
            expected.unk6 = 1;
            if (!(type & 1))
                for (i = 0; i < 2 && i < capacity; i++) {
                    struct VisualObj* child = &visuals_expected[i];
                    child->active = 0x41;
                    child->id = 24;
                    child->unk50 = PLAYER_OBJECT(&owner);
                    child->x_pos.i.hi = 160 + (face ? offsets[i] : -offsets[i]);
                    child->y_pos.i.hi = 89;
                }
        }
    }
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    SP_CUR_SHOT_OBJ = &obj;
    func_800A25EC(&obj);
    assert(SP_CUR_SHOT_OBJ == &obj);
    SP_CUR_SHOT_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals_expected, sizeof(visuals_expected) / 4) == 0);
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(cur_random == 0x1234 && D_8013E198[2] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "walrus_ice_lob", 0, 0, COUNT(walrus_ice_lob_cases), test_walrus_ice_lob },
    { "walrus_ice_states", 0, 0, COUNT(walrus_ice_states_cases), test_walrus_ice_states },
    { "icicle_wait", icicle_wait_cases, icicle_wait_cases_expected, COUNT(icicle_wait_cases), 0 },
    { "walrus_ice_ball_main", 0, 0, 1, test_walrus_ice_ball_main },
    { "walrus_ice_damage", walrus_ice_damage_cases, walrus_ice_damage_cases_expected, COUNT(walrus_ice_damage_cases), 0 },
    { "icicle_form_owner_interrupt_and_zero_one_two_visual_slots", NULL, NULL, 72, form },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(walrus_ice_lob_cases) + COUNT(walrus_ice_states_cases) + COUNT(icicle_wait_cases) + 1 + COUNT(walrus_ice_damage_cases) + 72;
