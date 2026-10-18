#include "test_runtime.h"
#include "main/mains/main_75_general.h"
#include "main/195B4.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
extern union AnimationStep* final_cutscene_animations[1];
extern void* general_animations[46];
extern struct Unk_unk68 D_801059BC, D_801059C4[5];
void general_rise(struct MainObj*);
u8 general_at_position(struct ObjectHeader*, s16, s16);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static s32 menu_frames[32];
static u32 page_metadata[2] = { 0x400, 0x480 };
static u32 ending_case(u32 mode)
{
    struct MainObj obj, expected;
    struct EffectObj effect, effect_before;
    struct BackgroundObj backgrounds_expected[3];
    struct EngineObj engine_expected;
    struct PlayerObj player_before = g_Player;
    u32 i, index = mode == 4 ? 6 : 8;
    memset(&obj, 0, sizeof(obj));
    memset(&effect, 0, sizeof(effect));
    for (i = 0; i < 16; i++) {
        menu_frames[i] = 64 + i * 4;
        menu_frames[i + 16] = i + 1;
    }
    engine_obj.stage = mode == 4 ? 12 : 11;
    engine_obj.substage = 1;
    background_objects[0].x_pos.val = 40 * 65536 + 0xBEEF;
    background_objects[0].y_pos.val = 50 * 65536 + 0xCAFE;
    background_objects[0].unk24 = 1;
    background_objects[0].unk26 = 2;
    background_objects[0].unk28 = 3;
    background_objects[0].unk2A = 4;
    effect.active = mode ? 1 : 0;
    effect.id = 26;
    effect.state = 2;
    effect.unk7 = mode >= 3 ? 1 : 0;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 8;
    obj.unk6 = 4;
    obj.on_screen = 1;
    obj.ext.main_75.object.effect = &effect;
    obj.unk7E = mode == 2 ? 0 : 1;
    obj.unk42 = 0x2345;
    obj.unk15 = 0x40;
    obj.unk17 = 3;
    obj.previous_animation_index = 9;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    D_801406A8 = page_metadata;
    TEST_MENU_FRAMES = (u8*)menu_frames;
    expected = obj;
    effect_before = effect;
    engine_expected = engine_obj;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    expected.on_screen = 0;
    if (mode == 1)
        expected.unk7E = 0;
    if (mode == 2) {
        expected.unk7E = 5;
        expected.unk42 ^= 0x8000;
    }
    if (mode >= 3) {
        assert(s_StageMainIds[(u8)engine_obj.stage][1][index] == 0xA3 && (u8)func_8002938C(0xA3) == index);
        expected.unk5 = 9;
        expected.unk40 = 0xB9;
        expected.unk42 = mode == 4 ? 0x78C0 : 0x78C8;
        expected.sprite_frames = (u8*)&menu_frames[16 + index];
        expected.animation_table = (const u8* const*)final_cutscene_animations;
        ANIMATED_OBJECT(&expected)->animation_cursor = (u32*)final_cutscene_animations[0];
        expected.animation_step = final_cutscene_animations[0][0];
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        expected.x_pos.u.hi = 264;
        expected.y_pos.u.hi = 154;
        expected.unk15 = 0;
        backgrounds_expected[0].unk24 = backgrounds_expected[0].unk26 = 40;
        backgrounds_expected[0].unk28 = backgrounds_expected[0].unk2A = 50;
    }
    func_800915C4(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(effect) / 4; i++)
        assert(((u32*)&effect)[i] == ((u32*)&effect_before)[i]);
    for (i = 0; i < sizeof(backgrounds_expected) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 16; i++) {
        assert(menu_frames[i] == 64 + i * 4);
        assert(menu_frames[i + 16] == i + 1);
    }
    assert(D_801406A8 == page_metadata && page_metadata[0] == 0x400 && page_metadata[1] == 0x480 && SP_MENU_FRAMES == menu_frames);
    i = obj.unk42 | ((u32)(u8)obj.unk7E << 16) | ((u32)(u8)obj.unk5 << 24);
    return i;
}
#define CASE(m)                                               \
    static u32 general_ending_effect_context_ending_##m(void) \
    {                                                         \
        return ending_case(m);                                \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) general_ending_effect_context_ending_##m,
static const CTestCase general_ending_effect_context_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 general_ending_effect_context_cases_expected[] = { 0x8012345u, 0x8002345u, 0x805A345u, 0x90178C8u, 0x90178C0u };
#undef CASE
#undef ENTRY

static u32 far_player(u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 i, actual, original_step;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 2;
    obj.unk7 = 3;
    obj.unk7C = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    g_Player.x_pos.i.hi = 109;
    g_Player.y_pos.i.hi = 200;
    obj.collision_flags = 2;
    obj.animation_table = (u32**)general_animations;
    obj.animation_cursor = general_animations[1];
    obj.animation_step.packed = *(u32*)general_animations[1];
    before = obj;
    player_before = g_Player;
    original_step = *(u32*)general_animations[1];
    func_800905D4(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.unk7 = obj.unk7;
    before.unk15 = obj.unk15;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    assert(*(u32*)general_animations[1] == original_step);
    actual = observation == 0 ? (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8)
            | ((u32)(u8)obj.unk7 << 16) | ((u32)(u8)obj.unk15 << 24)
                              : obj.animation_step.packed;
    return actual;
}
static u32 far_state(void)
{
    return far_player(0);
}
static u32 far_animation(void)
{
    return far_player(1);
}
static const CTestCase general_far_player_cases[] = { far_state, far_animation };
static const u32 general_far_player_cases_expected[] = { 0x40000002u, 0x10001u };

static u32 graphics_header[4] = { 0x1800, 0x12345678, 0x87654321, 0x55555555 };
static u32 intro_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj linked, linked_before, pool_expected[32];
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    u32 i, free_count = mode < 2 ? 0 : mode == 2 ? 1
                                                 : 2;
    memset(&obj, 0, sizeof(obj));
    memset(&linked, 0, sizeof(linked));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = i < 32 - free_count ? 1 : 0;
        shot_objects[i].id = 39;
        shot_objects[i].unk2 = 9;
        shot_objects[i].state = 40;
        shot_objects[i].unk5 = 3;
        shot_objects[i].unk6 = 4;
        shot_objects[i].unk7 = 5;
        shot_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        shot_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        shot_objects[i].unk42 = 0x7777;
        shot_objects[i].bg_offset = 2;
    }
    linked.active = mode == 0 ? 1 : 0;
    linked.id = 55;
    linked.state = 2;
    memset(&obj.ext.main_75, 0xA5, sizeof(obj.ext.main_75));
    obj.ext.main_75.object.shot = mode == 1 || mode == 3 ? NULL : &linked;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 9;
    obj.hp = 127;
    obj.contact_damage = 7;
    obj.invincibility_timer = 3;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_speed = 12345;
    obj.y_speed = -12345;
    obj.x_accel = 123;
    obj.gravity = -321;
    obj.air_state = 7;
    obj.bg_offset = -1;
    obj.unk42 = 0x1234;
    obj.terrain_box = &D_801059BC;
    g_Player.x_pos.val = (mode == 4 ? 3700 : 3736) * 65536 + 0x1234;
    g_Player.bg_offset = 1;
    g_Player.script_state = 1;
    g_Player.spike_immune = 1;
    g_Player.script_action = 0x14;
    g_Player.script_facing = 0x40;
    engine_obj.gameplay_locked = 1;
    D_801406A8 = graphics_header;
    expected = obj;
    linked_before = linked;
    player_expected = g_Player;
    engine_expected = engine_obj;
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    if (mode != 0) {
        expected.hp = 0;
        expected.contact_damage = 9;
        expected.invincibility_timer = 0;
        expected.x_pos.i.hi = 0xE98;
        expected.y_pos.i.hi = 0x27B;
        expected.unk5 = 2;
        expected.unk18.val = expected.x_pos.val;
        expected.unk1C.val = expected.y_pos.val;
        expected.unk40 = 0xE0;
        expected.unk16 = 5;
        expected.x_speed = expected.y_speed = expected.x_accel = expected.gravity = 0;
        expected.air_state = 0;
        expected.terrain_box = NULL;
        expected.collision_data = D_80107B78;
        expected.hurt_box = D_801059C4;
        expected.attack_box = &D_801059BC;
        expected.bg_offset = 1;
        expected.unk15 = mode == 4 ? 0 : 0x40;
        expected.animation_table = (const u8* const*)general_animations;
        expected.animation_cursor = general_animations[0];
        expected.animation_step = *(union AnimationStep*)general_animations[0];
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        assert(expected.animation_step.packed == 1);
        memset(&expected.ext.main_75, 0, sizeof(expected.ext.main_75));
        if (free_count) {
            u32 first = 32 - free_count;
            pool_expected[first].active = 0x41;
            pool_expected[first].id = 55;
            pool_expected[first].unk2 = 1;
            pool_expected[first].unk7C = (struct WeaponObj*)&obj;
            expected.ext.main_75.object.shot = &shot_objects[first];
        }
        if (free_count == 2) {
            pool_expected[31].active = 0x41;
            pool_expected[31].id = 55;
            pool_expected[31].unk2 = 0;
            pool_expected[31].unk7C = (struct WeaponObj*)&obj;
            expected.ext.main_75.thruster = &shot_objects[31];
        }
        player_expected.script_state = 0;
        player_expected.spike_immune = 0;
        engine_expected.gameplay_locked = 0;
    }
    func_8008FBCC(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(linked) / 4; i++)
        assert(((u32*)&linked)[i] == ((u32*)&linked_before)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    assert(D_801406A8 == graphics_header && graphics_header[0] == 0x1800);
    assert(graphics_header[1] == 0x12345678 && graphics_header[2] == 0x87654321 && graphics_header[3] == 0x55555555);
    i = (u8)obj.unk5 | ((u32)obj.unk15 << 8) | ((u32)(u8)obj.hp << 16);
    return i;
}
#define CASE(m)                                            \
    static u32 general_intro_two_shot_pool_intro_##m(void) \
    {                                                      \
        return intro_case(m);                              \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) general_intro_two_shot_pool_intro_##m,
static const CTestCase general_intro_two_shot_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 general_intro_two_shot_pool_cases_expected[] = { 0x7F0001u, 0x4002u, 0x4002u, 0x4002u, 0x2u, 0x4002u };
#undef CASE
#undef ENTRY

static u32 punch_case(u32 right, u32 observation)
{
    struct MainObj obj, before;
    struct ShotObj thruster, thruster_before, pool_before[32];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&thruster, 0, sizeof(thruster));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    shot_objects[17].active = shot_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk7C = 0x7777;
    obj.unk15 = right ? 0x40 : 0;
    obj.ext.main_75.thruster = &thruster;
    thruster.active = 0x41;
    thruster.id = 55;
    thruster.unk84.shot_55.x = 0x27;
    thruster.unk84.shot_55.y = 0x28;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation_frame(&obj, 11, 2);
    before = obj;
    thruster_before = thruster;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    general_punch_launch(&obj);
    before.animation_step.fields.duration = 1;
    before.animation_step.fields.event = 0;
    pool_before[17].active = pool_before[31].active = 0x41;
    pool_before[17].id = pool_before[31].id = 55;
    pool_before[17].unk2 = 2;
    pool_before[31].unk2 = 3;
    pool_before[17].unk7C = pool_before[31].unk7C = WEAPON_OBJECT(&obj);
    pool_before[17].unk8C.shot = &shot_objects[31];
    pool_before[31].unk8C.shot = &shot_objects[17];
    thruster_before.unk84.shot_55.x = right ? -0x20 : 0x20;
    thruster_before.unk84.shot_55.y = -4;
    assert(general_fists[0] == &shot_objects[17] && general_fists[1] == &shot_objects[31]);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(thruster) / 4; i++)
        assert(((u32*)&thruster)[i] == ((u32*)&thruster_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    return observation == 0 ? (u16)thruster.unk84.shot_55.x | ((u32)(u16)thruster.unk84.shot_55.y << 16) : obj.animation_step.packed;
}
#define CASE(m, n)                                              \
    static u32 general_punch_linked_fists_punch_##m##_##n(void) \
    {                                                           \
        return punch_case(m, n);                                \
    }
CASE(0, 0)
CASE(0, 1)
CASE(1, 0)
CASE(1, 1)
#define ENTRY(m, n) general_punch_linked_fists_punch_##m##_##n,
static const CTestCase general_punch_linked_fists_cases[]
    = { ENTRY(0, 0) ENTRY(0, 1) ENTRY(1, 0) ENTRY(1, 1) };
static const u32 general_punch_linked_fists_cases_expected[] = { 0xFFFC0020u, 0x1E010001u, 0xFFFCFFE0u, 0x1E010001u };
#undef general_fists
#undef CASE
#undef ENTRY

static u32 rise_case(u32 observation)
{
    struct MainObj obj, before;
    struct ShotObj thruster, thruster_before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&thruster, 0, sizeof(thruster));
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk7 = 0;
    obj.unk7C = 0x7777;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -32768;
    obj.gravity = 0x1000;
    obj.ext.main_75.thruster = &thruster;
    thruster.active = 0x41;
    thruster.id = 55;
    thruster.unk84.shot_55.x = 0x27;
    thruster.unk84.shot_55.y = 0x28;
    obj.animation_table = (const u8* const*)general_animations;
    thruster.animation_table = (u32**)general_animations;
    set_animation(&obj, 0);
    set_animation(&thruster, 0);
    before = obj;
    thruster_before = thruster;
    general_rise(&obj);
    before.unk7 = 1;
    before.unk17 = 8;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)general_animations[8];
    before.animation_step = *(union AnimationStep*)general_animations[8];
    before.y_speed = 32768;
    before.unk7C = 60;
    before.terrain_box = &D_801059D8;
    thruster_before.unk17 = 5;
    thruster_before.previous_animation_index = 0xFF;
    thruster_before.animation_cursor = general_animations[5];
    thruster_before.animation_step = *(union AnimationStep*)general_animations[5];
    thruster_before.unk84.shot_55.x = 24;
    thruster_before.unk84.shot_55.y = 4;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(thruster) / 4; i++)
        assert(((u32*)&thruster)[i] == ((u32*)&thruster_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return observation ? thruster.animation_step.packed : (u8)obj.unk7 | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.unk7C << 16);
}
#define CASE(n)                                            \
    static u32 general_rise_animation_start_rise_##n(void) \
    {                                                      \
        return rise_case(n);                               \
    }
CASE(0)
CASE(1)
#define ENTRY(n) general_rise_animation_start_rise_##n,
static const CTestCase general_rise_animation_start_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 general_rise_animation_start_cases_expected[] = { 0x3C0801u, 0xF010001u };
#undef CASE
#undef ENTRY

static u8 sound_entries[12];
static u32 impact_case(u32 mode)
{
    struct MainObj obj, before;
    struct ShotObj thruster, thruster_before, pool_before[32];
    struct BackgroundObj backgrounds_before[3];
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 i, impact = mode != 0;
    memset(&obj, 0, sizeof(obj));
    memset(&thruster, 0, sizeof(thruster));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(sound_entries, 0, sizeof(sound_entries));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    if (mode == 2)
        shot_objects[31].active = 0;
    D_80141F50[2] = sound_entries;
    D_8013E198[2] = -1;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.collision_flags = impact ? 8 : 0;
    obj.ext.main_75.thruster = &thruster;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -2 * 65536;
    thruster.active = 0x41;
    thruster.id = 55;
    thruster.timer = 7;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, 0);
    before = obj;
    thruster_before = thruster;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    general_slam_fall(&obj);
    before.x_pos.val += 65536;
    before.y_pos.val += 2 * 65536;
    if (impact) {
        before.unk6++;
        before.unk17 = 10;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)general_animations[10];
        before.animation_step = *(union AnimationStep*)general_animations[10];
        thruster_before.timer = 0;
        backgrounds_before[0].unk36 = 20;
        backgrounds_before[0].unk45 = 4;
        backgrounds_before[0].unk3E.bytes[0] = 4;
        backgrounds_before[0].unk3C = 2;
        backgrounds_before[0].unk3A = 2;
        backgrounds_before[0].unk34 |= 0x10;
    }
    if (mode == 2) {
        pool_before[31].active = 0x41;
        pool_before[31].id = 0x37;
        pool_before[31].unk2 = 6;
        pool_before[31].unk7C = WEAPON_OBJECT(&obj);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(thruster) / 4; i++)
        assert(((u32*)&thruster)[i] == ((u32*)&thruster_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(sound_entries); i++)
        assert(sound_entries[i] == 0);
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)(u8)thruster.timer << 8) | ((u32)shot_objects[31].active << 16);
}
#define CASE(m)                                          \
    static u32 general_slam_impact_pool_impact_##m(void) \
    {                                                    \
        return impact_case(m);                           \
    }
CASE(0)
CASE(1)
CASE(2)
#define ENTRY(m) general_slam_impact_pool_impact_##m,
static const CTestCase general_slam_impact_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) };
static const u32 general_slam_impact_pool_cases_expected[] = { 0x10702u, 0x10003u, 0x410003u };
#undef CASE
#undef ENTRY

static u32 general_slam_right_launch_slam_case(void)
{
    struct MainObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk6 = 3;
    obj.unk7C = 1;
    obj.unk15 = 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = 2 * 65536;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, 0);
    before = obj;
    general_slam_ascend(&obj);
    before.x_pos.val += 65536;
    before.y_pos.val -= 2 * 65536;
    before.x_speed = 2 * 65536;
    before.y_speed = 0;
    before.unk7C = 0;
    before.unk6 = 4;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    actual = (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16);
    return actual;
}
static const CTestCase general_slam_right_launch_cases[] = { general_slam_right_launch_slam_case };
static const u32 general_slam_right_launch_cases_expected[] = { 0xC60065u };

static u32 general_slam_thruster_transitions_slam_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj thruster, expected_thruster;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 i, facing = mode & 1, rise = mode >= 2 && mode < 4;
    memset(&obj, 0, sizeof(obj));
    memset(&thruster, 0, sizeof(thruster));
    D_8013E198[2] = -1;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk6 = 2;
    obj.unk7 = mode >= 4;
    obj.unk7C = rise ? 0 : 1;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_speed = 3 * 65536;
    obj.y_speed = 7 * 65536;
    obj.ext.main_75.thruster = &thruster;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, rise ? 10 : mode >= 4 ? 9
                                              : 0);
    if (rise || mode >= 4) {
        obj.animation_cursor += (rise ? 22 : 3) * sizeof(union AnimationStep);
        obj.animation_step = *(const union AnimationStep*)obj.animation_cursor;
        assert(rise ? obj.animation_step.packed == 0x09000001 : obj.animation_step.packed == 0x19000102);
    }
    thruster.active = 0x41;
    thruster.id = 55;
    thruster.timer = 7;
    thruster.animation_table = (const u8* const*)general_animations;
    set_animation(&thruster, 0);
    expected = obj;
    expected_thruster = thruster;
    if (mode >= 4) {
        expected.animation_step.fields.duration = 1;
        expected.x_speed = 0;
        expected.y_speed = -5 * 65536;
        expected.unk6 = 3;
        expected.unk7 = 0;
    } else {
        u32 anim = rise ? 8 : 9, thruster_anim = rise ? 5 : 6;
        expected.unk17 = anim;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = general_animations[anim];
        expected.animation_step = *(union AnimationStep*)general_animations[anim];
        expected_thruster.unk17 = thruster_anim;
        expected_thruster.previous_animation_index = 0xFF;
        expected_thruster.animation_cursor = general_animations[thruster_anim];
        expected_thruster.animation_step = *(union AnimationStep*)general_animations[thruster_anim];
        expected_thruster.unk84.halves[0] = facing ? -24 : 24;
        expected_thruster.unk84.halves[1] = rise ? 4 : -16;
        if (rise) {
            expected.unk6 = 3;
            expected.unk7C = 15;
            expected.x_speed = 0;
            expected.y_speed = 5 * 65536;
            expected.terrain_box = &D_801059D8;
            expected_thruster.timer = 1;
        } else {
            expected.unk7 = 1;
            expected.unk7C = 0;
            expected.terrain_box = &D_801059DC;
        }
    }
    if (rise)
        general_slam_rise(&obj);
    else
        general_slam_windup(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(thruster) / 4; i++)
        assert(((u32*)&thruster)[i] == ((u32*)&expected_thruster)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)(u8)obj.unk7 << 8) | ((u32)obj.unk17 << 16) | ((u32)thruster.unk17 << 24);
}
#define CASE(m)                                                 \
    static u32 general_slam_thruster_transitions_slam_##m(void) \
    {                                                           \
        return general_slam_thruster_transitions_slam_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) general_slam_thruster_transitions_slam_##m,
static const CTestCase general_slam_thruster_transitions_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 general_slam_thruster_transitions_cases_expected[] = { 0x6090102u, 0x6090102u, 0x5080003u, 0x5080003u, 0x90003u, 0x90003u };
#undef CASE
#undef ENTRY

struct func_800905D4_case {
    u32 obj_y_pos_hi, g_Player_y_pos_hi, obj_x_pos_hi, g_Player_x_pos_hi, collision_flags, unk15;
    u32 expected[7];
};
static const struct func_800905D4_case func_800905D4_cases[] = {
    { -32626, -32512, 0, 0, 0, 0, { 0u, 6u, 0u, 0u, 0x1Eu, 0u, 0u } },
    { 0, 0, 0, 0, 3, 255, { 0xBFu, 2u, 0u, 0u, 0u, 0u, 0u } },
    { -32626, -32512, -28673, -28671, 0, 0, { 0u, 6u, 0u, 0u, 0x1Eu, 0u, 0u } },
    { -32626, -32512, 7, -16377, 3, 255, { 0xBFu, 2u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800905D4(u32 row)
{
    const struct func_800905D4_case* c = &func_800905D4_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    g_Player.y_pos.i.hi = c->g_Player_y_pos_hi;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.collision_flags = c->collision_flags;
    obj.unk15 = c->unk15;
    func_800905D4(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

static const u32 general_at_position_expected[] = { 0u };
static u32 test_general_at_position(u32 row)
{
    u32 observed_values[1];
    struct ObjectHeader obj;
    u8 return_value;
    s16 arg1;
    s16 arg2;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.i.hi = 4;
    arg1 = -32767;
    arg2 = 0;
    return_value = general_at_position(&obj, arg1, arg2);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, general_at_position_expected, 1);
}

struct general_rise_case {
    u32 unk7C;
    u32 expected[7];
};
static const struct general_rise_case general_rise_cases[] = {
    { 0, { 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u } },
    { 1, { 0u, 0u, 2u, 0u, 0u, 0u, 0u } },
};
static u32 test_general_rise(u32 row)
{
    const struct general_rise_case* c = &general_rise_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    struct ShotObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_801059D8, 0, sizeof(D_801059D8));
    obj.unk7 = -1;
    child_0_present = 0;
    obj.unk7C = c->unk7C;
    obj.ext.main_75.thruster = child_0_present ? &child_0 : NULL;
    general_rise(&obj);
    observed_values[0] = (u32)child_0.unk84.shot_55.x;
    observed_values[1] = (u32)child_0.unk84.shot_55.y;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7;
    observed_values[5] = (u32)obj.unk7C;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

static const u32 general_slam_ascend_expected[] = { 1u, 0u, 0xFFFE0000u, 0u };
static u32 test_general_slam_ascend(u32 row)
{
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7C = 1;
    general_slam_ascend(&obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.unk7C;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, general_slam_ascend_expected, 4);
}

struct general_slam_leave_case {
    u32 collision_flags, unk15;
    u32 expected[5];
};
static const struct general_slam_leave_case general_slam_leave_cases[] = {
    { 2, 255, { 0xFFu, 0u, 0u, 0u, 0u } },
    { 1, 0, { 0u, 0u, 0u, 0u, 0u } },
    { 3, 0, { 0x40u, 2u, 0u, 0u, 0u } },
};
static u32 test_general_slam_leave(u32 row)
{
    const struct general_slam_leave_case* c = &general_slam_leave_cases[row];
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.collision_flags = c->collision_flags;
    obj.unk15 = c->unk15;
    general_slam_leave(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.x_speed;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}

struct general_slam_rise_case {
    u32 unk7C, relative_step;
    u32 expected[7];
};
static const struct general_slam_rise_case general_slam_rise_cases[] = {
    { 255, 0, { 0u, 0u, 0u, 0u, 0xFEu, 0u, 0u } },
    { 0, -1, { 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_general_slam_rise(u32 row)
{
    const struct general_slam_rise_case* c = &general_slam_rise_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    struct ShotObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_801059D8, 0, sizeof(D_801059D8));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = c->unk7C;
    obj.animation_step.fields.relative_step = c->relative_step;
    child_0_present = 0;
    obj.ext.main_75.thruster = child_0_present ? &child_0 : NULL;
    general_slam_rise(&obj);
    observed_values[0] = (u32)child_0.timer;
    observed_values[1] = (u32)child_0.unk84.halves[0];
    observed_values[2] = (u32)child_0.unk84.halves[1];
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

struct general_slam_windup_case {
    u32 event;
    u32 expected[7];
};
static const struct general_slam_windup_case general_slam_windup_cases[] = {
    { 0, { 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u } },
    { -1, { 0u, 0u, 1u, 0u, 0u, 0u, 0xFFFB0000u } },
};
static u32 test_general_slam_windup(u32 row)
{
    const struct general_slam_windup_case* c = &general_slam_windup_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    struct ShotObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_801059DC, 0, sizeof(D_801059DC));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7 = -1;
    child_0_present = 0;
    obj.animation_step.fields.event = c->event;
    obj.ext.main_75.thruster = child_0_present ? &child_0 : NULL;
    general_slam_windup(&obj);
    observed_values[0] = (u32)child_0.unk84.shot_55.x;
    observed_values[1] = (u32)child_0.unk84.shot_55.y;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

#include "support/pool_full.h"
static u32 pool_full_general_death_blink(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    general_death_blink(&pf_self);
    pf_expected.unk5++;
    pf_expected.on_screen = 0;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_general_punch_rings(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_snapshot();
    general_punch_rings(&pf_self);
    pf_animated();
    pf_expected.unk7C = 0x3C;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_general_death_blink,
    pool_full_general_punch_rings,
};

static const u32 pool_full_cases_expected[] = { 0x1u, 0x3C0000u };
const struct CTestGroup c_test_groups[] = {
    { "general_ending_effect_context", general_ending_effect_context_cases, general_ending_effect_context_cases_expected, COUNT(general_ending_effect_context_cases), 0 },
    { "general_far_player", general_far_player_cases, general_far_player_cases_expected, COUNT(general_far_player_cases), 0 },
    { "general_intro_two_shot_pool", general_intro_two_shot_pool_cases, general_intro_two_shot_pool_cases_expected, COUNT(general_intro_two_shot_pool_cases), 0 },
    { "general_punch_linked_fists", general_punch_linked_fists_cases, general_punch_linked_fists_cases_expected, COUNT(general_punch_linked_fists_cases), 0 },
    { "general_rise_animation_start", general_rise_animation_start_cases, general_rise_animation_start_cases_expected, COUNT(general_rise_animation_start_cases), 0 },
    { "general_slam_impact_pool", general_slam_impact_pool_cases, general_slam_impact_pool_cases_expected, COUNT(general_slam_impact_pool_cases), 0 },
    { "general_slam_right_launch", general_slam_right_launch_cases, general_slam_right_launch_cases_expected, COUNT(general_slam_right_launch_cases), 0 },
    { "general_slam_thruster_transitions", general_slam_thruster_transitions_cases, general_slam_thruster_transitions_cases_expected, COUNT(general_slam_thruster_transitions_cases), 0 },
    { "func_800905D4", 0, 0, 4, test_func_800905D4 },
    { "general_at_position", 0, 0, 1, test_general_at_position },
    { "general_rise", 0, 0, 2, test_general_rise },
    { "general_slam_ascend", 0, 0, 1, test_general_slam_ascend },
    { "general_slam_leave", 0, 0, 3, test_general_slam_leave },
    { "general_slam_rise", 0, 0, 2, test_general_slam_rise },
    { "general_slam_windup", 0, 0, 2, test_general_slam_windup },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(general_ending_effect_context_cases) + COUNT(general_far_player_cases) + COUNT(general_intro_two_shot_pool_cases) + COUNT(general_punch_linked_fists_cases) + COUNT(general_rise_animation_start_cases) + COUNT(general_slam_impact_pool_cases) + COUNT(general_slam_right_launch_cases) + COUNT(general_slam_thruster_transitions_cases) + 4 + 1 + 2 + 1 + 3 + 2 + 2 + COUNT(pool_full_cases);
