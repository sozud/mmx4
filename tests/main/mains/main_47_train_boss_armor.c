#include "test_runtime.h"
extern u16 train_boss_armor_smoke_offsets[3][2];

static u32* reflected_word(struct MainObj* obj)
{
#ifdef MMX4_PC
    return &obj->ext.main_47.unk88;
#else
    return (u32*)((u8*)obj + 0x88);
#endif
}
static void bind_owner(struct MainObj* obj, struct Main45Ext* owner, s8* hp)
{
    obj->ext.main_47.train_boss = owner;
    obj->ext.main_47.boss_hp = hp;
}
static struct ArmorInput {
    u8 timer, reflected, weapon, hit, hp, attack;
};
static const struct ArmorInput inputs[] = {
    { 2, 0, 0, 0, 16, 0 },
    { 2, 1, 0, 0, 16, 0 },
    { 0, 0, 0, 0, 16, 0 },
    { 0, 0, 0, 1, 16, 0 },
    { 0, 0, 3, 1, 16, 0 },
    { 0, 0, 0, 1, 1, 0 },
    { 0, 0, 0, 1, 1, 6 },
};
static u32 armor_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct Main45Ext owner, owner_before;
    struct Main45LayerSignals signals, signals_before;
    struct PlayerObj player_before;
    struct WeaponObj weapon_before;
    struct Unk_unk68 attack = { 0, 0, 8, 8 }, hurt = { 0, 0, 8, 8 };
    struct WeaponObj* weapon = &weapon_objects[0];
    s8 boss_hp = 48;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&signals, 0, sizeof(signals));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
    }
    for (i = 0; i < COUNT(visual_objects); i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x35;
    }
    for (i = 0; i < COUNT(D_8013E198); i++)
        D_8013E198[i] = -1;
    cur_random = 0x1234;
    obj.active = 0x41;
    obj.id = 47;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0x27;
    obj.hp = obj.unk5D = inputs[mode].hp;
    obj.unk42 = 0x9234;
    obj.bg_offset = 0;
    obj.x_pos.val = 100 * 65536 + 0x1357;
    obj.y_pos.val = 100 * 65536 + 0x2468;
    obj.hurt_box = &hurt;
    obj.collision_data = D_80107678;
    obj.invincibility_timer = inputs[mode].timer;
    bind_owner(&obj, &owner, &boss_hp);
    *reflected_word(&obj) = 0xA5A52700 | inputs[mode].reflected;
    owner.unk87 = 1;
    owner.attack_flags = inputs[mode].attack;
    owner.layer_signals = &signals;
    signals.unk16 = 0x27;
    signals.collision_state = 0x35;
    weapon->active = inputs[mode].hit;
    weapon->id = inputs[mode].weapon;
    weapon->unk64 = 2;
    weapon->bg_offset = 0;
    weapon->unk50 = &attack;
    weapon->x_pos.val = obj.x_pos.val;
    weapon->y_pos.val = obj.y_pos.val;
    weapon->unk98 = 0x27;
    g_Player.active = 0x41;
    g_Player.hp = 20;
    engine_obj.cur_character = 0;
    before = obj;
    owner_before = owner;
    signals_before = signals;
    player_before = g_Player;
    weapon_before = *weapon;
    func_80066F1C(&obj);
    before.state = obj.state;
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.invincibility_timer = obj.invincibility_timer;
    before.hp = obj.hp;
    before.unk5D = obj.unk5D;
    before.unk42 = obj.unk42;
    before.unk63 = obj.unk63;
    before.unk65 = obj.unk65;
    before.on_screen = obj.on_screen;
    before.unk7C = obj.unk7C;
    before.unk7E = obj.unk7E;
    before.unk18 = obj.unk18;
    before.unk1C = obj.unk1C;
    *reflected_word(&before) = *reflected_word(&obj);
    owner_before.attack_flags = owner.attack_flags;
    signals_before.unk16 = signals.unk16;
    player_before.spike_immune = g_Player.spike_immune;
    player_before.update_delay_request = g_Player.update_delay_request;
    weapon_before.unk80 = weapon->unk80;
    weapon_before.unk98 = weapon->unk98;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(signals); i++)
        assert(((u8*)&signals)[i] == ((u8*)&signals_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(*weapon) / 4; i++)
        assert(((u32*)weapon)[i] == ((u32*)&weapon_before)[i]);
    assert(obj.hurt_box == &hurt && obj.collision_data == D_80107678 && owner.layer_signals == &signals);
    assert(hurt.unk2 == 8 && hurt.unk3 == 8 && attack.unk2 == 8 && attack.unk3 == 8);
    assert(obj.x_pos.val == before.x_pos.val && obj.y_pos.val == before.y_pos.val);
    assert(obj.unk18.val == obj.x_pos.val && obj.unk1C.val == obj.y_pos.val);
    assert(g_Player.update_delay_request == 0);
    for (i = 0; i < COUNT(misc_objects); i++)
        assert(misc_objects[i].active == 1 && misc_objects[i].id == 0x27);
    for (i = 0; i < COUNT(visual_objects); i++)
        assert(visual_objects[i].active == 1 && visual_objects[i].id == 0x35);
    for (i = 1; i < COUNT(weapon_objects); i++)
        assert(weapon_objects[i].active == 0);
    for (i = 0; i < COUNT(D_8013E198); i++)
        assert(D_8013E198[i] == -1);
    switch (observation) {
    case 0:
        actual = (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk6 << 16) | ((u32)(u8)obj.invincibility_timer << 24);
        break;
    case 1:
        actual = (u8)obj.hp | ((u32)(u8)obj.unk5D << 8) | ((u32)(u8)obj.unk63 << 16) | ((u32)(u8)obj.unk65 << 24);
        break;
    case 2:
        actual = obj.unk42 | ((u32)obj.on_screen << 16) | ((u32)owner.attack_flags << 24);
        break;
    case 3:
        actual = (u8)boss_hp | ((u32)signals.unk16 << 8) | ((u32)g_Player.spike_immune << 16) | ((u32)(u8)weapon->unk98 << 24);
        break;
    case 4:
        actual = *reflected_word(&obj);
        break;
    case 5:
        actual = weapon->unk80.word;
        break;
    default:
        actual = (u16)obj.unk7C | ((u32)(u16)obj.unk7E << 16);
        break;
    }
    return actual;
}
#define ARMOR_CASE(m, n)                                 \
    static u32 train_armor_context_armor_##m##_##n(void) \
    {                                                    \
        return armor_case(m, n);                         \
    }
#define ARMOR_MODE(m) ARMOR_CASE(m, 0) ARMOR_CASE(m, 1) ARMOR_CASE(m, 2) ARMOR_CASE(m, 3) ARMOR_CASE(m, 4) ARMOR_CASE(m, 5) ARMOR_CASE(m, 6)
ARMOR_MODE(0)
ARMOR_MODE(1)
ARMOR_MODE(3)
ARMOR_MODE(4)
ARMOR_MODE(5)
ARMOR_MODE(6)
#define ARMOR_ENTRY(m, n) train_armor_context_armor_##m##_##n,
#define ARMOR_ENTRIES(m) ARMOR_ENTRY(m, 0) ARMOR_ENTRY(m, 1) ARMOR_ENTRY(m, 2) ARMOR_ENTRY(m, 3) ARMOR_ENTRY(m, 4) ARMOR_ENTRY(m, 5) ARMOR_ENTRY(m, 6)
static const CTestCase train_armor_context_cases[]
    = { ARMOR_ENTRIES(0) ARMOR_ENTRIES(1) ARMOR_ENTRIES(3) ARMOR_ENTRIES(4) ARMOR_ENTRIES(5) ARMOR_ENTRIES(6) };
static const u32 train_armor_context_cases_expected[] = { 0x1010201u, 0x1010u, 0x19234u, 0x27000130u, 0xA5A52700u, 0x0u, 0x0u, 0x1010201u, 0x1010u, 0x19234u, 0x27002730u, 0xA5A52701u, 0x0u, 0x0u, 0x2010201u, 0x2000E0Eu, 0x19234u, 0x100012Eu, 0xA5A52700u, 0x680068u, 0x0u, 0x2010201u, 0x2FF1010u, 0x11234u, 0x27002730u, 0xA5A52701u, 0x680068u, 0x0u, 0x10202u, 0x2000100u, 0x11009234u, 0x100272Fu, 0xA5A52700u, 0x680068u, 0x100B4u, 0x10203u, 0x2000100u, 0x17009234u, 0x101272Fu, 0xA5A52700u, 0x680068u, 0x0u };
#undef ARMOR_CASE
#undef ARMOR_MODE
#undef ARMOR_ENTRY
#undef ARMOR_ENTRIES

static u32 smoke_case(u32 mode, u32 observation)
{
    struct MainObj obj, before, parent, parent_before;
    struct BaseObj* parent_ptr;
    struct VisualObj pool_before[32];
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&parent, 0, sizeof(parent));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
        visual_objects[i].state = 0x28;
    }
    if (mode == 3)
        visual_objects[17].active = 0;
    obj.active = 0x41;
    obj.id = 47;
    obj.state = 2;
    obj.unk2 = 2;
    obj.unk7C = mode == 0 ? 1 : 2;
    obj.unk7E = mode < 2 ? 2 : 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    parent.x_pos.val = 300 * 65536 + 0x4321;
    parent.active = 0x41;
    parent.id = 45;
    parent_ptr = (struct BaseObj*)&parent;
#ifdef MMX4_PC
    obj.ext.main_47.train_boss = (struct Main45Ext*)parent_ptr;
#else
    assert(sizeof(parent_ptr) == 4 && MMX4_OFFSET_OF(struct MainObj, ext) == 0x80);
    memcpy((u8*)&obj + 0x80, &parent_ptr, sizeof(parent_ptr));
#endif
    before = obj;
    parent_before = parent;
    player_before = g_Player;
    memcpy(pool_before, visual_objects, sizeof(pool_before));
    cur_random = 0xACE1;
    train_boss_armor_smoke(&obj);
    before.unk7C--;
    if (mode == 0)
        before.state = 3;
    else
        before.unk7E = mode == 1 ? 1 : 10;
    if (mode == 3) {
        struct VisualObj* expected = &pool_before[17];
        s16 left = 300 + train_boss_armor_smoke_offsets[2][0] - 6;
        s16 top = 200 + train_boss_armor_smoke_offsets[2][1] - 6;
        assert(visual_objects[17].x_pos.i.hi >= left && visual_objects[17].x_pos.i.hi < left + 12);
        assert(visual_objects[17].y_pos.i.hi >= top && visual_objects[17].y_pos.i.hi < top + 12);
        expected->active = 0x21;
        expected->id = 9;
        expected->unk2 = 0;
        expected->x_pos = visual_objects[17].x_pos;
        expected->y_pos = visual_objects[17].y_pos;
        assert(expected->x_pos.i.lo == 0 && expected->y_pos.i.lo == 0);
        expected->x_vel.val = 0;
        expected->y_vel.val = 65536;
        expected->unk15 = 0;
        expected->unk5C.value = 1;
        expected->state = expected->unk5 = expected->unk6 = 0;
    } else
        assert(cur_random == 0xACE1);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(parent) / 4; i++)
        assert(((u32*)&parent)[i] == ((u32*)&parent_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool_before)[i]);
    if (observation == 0)
        return (u16)obj.unk7C | ((u32)(u8)obj.unk7E << 16) | ((u32)obj.state << 24);
    if (observation == 1)
        return (u16)visual_objects[17].x_pos.i.hi | ((u32)(u16)visual_objects[17].y_pos.i.hi << 16);
    return cur_random;
}
#define CASE(m, n)                                             \
    static u32 train_armor_smoke_context_smoke_##m##_##n(void) \
    {                                                          \
        return smoke_case(m, n);                               \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
#define ENTRY(m, n) train_armor_smoke_context_smoke_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2)
static const CTestCase train_armor_smoke_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) };
static const u32 train_armor_smoke_context_cases_expected[] = { 0x3020000u, 0x0u, 0xACE1u, 0x2010001u, 0x0u, 0xACE1u, 0x20A0001u, 0x0u, 0xACE1u, 0x20A0001u, 0xCE010Fu, 0xBAF3u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

#ifdef MMX4_PC
#define TEST_ARMOR_OWNER_LINK(object) (object).ext.main_47.train_boss
#define TEST_ARMOR_OWNER_ADDRESS ((struct Main45Ext*)&owner)
#define TEST_ARMOR_HP_LINK(object) (object).ext.main_47.boss_hp
#define TEST_ARMOR_HP_ADDRESS (&hp)
#define TEST_ARMOR_WORD88(object) (object).ext.main_47.unk88
#define TEST_ARMOR_WORD8C(object) (object).ext.main_47.unk8C
#define TEST_ARMOR_WORD90(object) (object).ext.main_47.unk90
#define TEST_ARMOR_WORD94(object) (object).ext.main_47.unk94
#else
#define TEST_ARMOR_OWNER_LINK(object) (object).ext.raw[0]
#define TEST_ARMOR_OWNER_ADDRESS ((u32)&owner)
#define TEST_ARMOR_HP_LINK(object) (object).ext.raw[1]
#define TEST_ARMOR_HP_ADDRESS ((u32)&hp)
#define TEST_ARMOR_WORD88(object) (object).ext.raw[2]
#define TEST_ARMOR_WORD8C(object) (object).ext.raw[3]
#define TEST_ARMOR_WORD90(object) (object).ext.raw[4]
#define TEST_ARMOR_WORD94(object) (object).ext.raw[5]
#endif
static const u32 func_80066DE8_expected[] = { 0u, 2u, 0u, 0x10u, 0u, 1u, 0u, 3u, 2u, 0x10u, 0u, 0u, 0x10000u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_80066DE8(u32 row)
{
    u32 observed_values[22];
    struct MainObj obj;
    u8 pool_0_full;
    struct MainObj before;
    struct BaseObj owner;
    struct ShotObj shots_before[32];
    s8 hp;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&owner, 0, sizeof(owner));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    memcpy(shots_before, shot_objects, sizeof(shots_before));
    func_80066DE8(&obj);
    c_test_same_words(shot_objects, shots_before, sizeof(shot_objects));
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.contact_damage;
    observed_values[2] = (u32)obj.gravity;
    observed_values[3] = (u32)obj.hp;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.state;
    observed_values[6] = (u32)obj.unk15;
    observed_values[7] = (u32)obj.unk16;
    observed_values[8] = (u32)obj.unk5;
    observed_values[9] = (u32)obj.unk5D;
    observed_values[10] = (u32)obj.unk6;
    observed_values[11] = (u32)obj.x_accel;
    observed_values[12] = (u32)obj.x_speed;
    observed_values[13] = (u32)obj.y_speed;
    observed_values[14] = (u32)shot_objects[0].active;
    observed_values[15] = (u32)shot_objects[0].bg_offset;
    observed_values[16] = (u32)shot_objects[0].id;
    observed_values[17] = (u32)shot_objects[0].state;
    observed_values[18] = (u32)shot_objects[0].unk15;
    observed_values[19] = (u32)shot_objects[0].unk2;
    observed_values[20] = (u32)shot_objects[0].unk40;
    observed_values[21] = (u32)shot_objects[0].unk42;
    TEST_ARMOR_OWNER_LINK(obj) = TEST_ARMOR_OWNER_ADDRESS;
    hp = 17;
    TEST_ARMOR_HP_LINK(obj) = TEST_ARMOR_HP_ADDRESS;
    TEST_ARMOR_WORD88(obj) = 305419896;
    TEST_ARMOR_WORD8C(obj) = 305419896;
    TEST_ARMOR_WORD90(obj) = 305419896;
    TEST_ARMOR_WORD94(obj) = 305419896;
    before = obj;
    TEST_ARMOR_OWNER_LINK(before) = 0;
    TEST_ARMOR_HP_LINK(before) = 0;
    TEST_ARMOR_WORD88(before) = 0;
    TEST_ARMOR_WORD8C(before) = 0;
    TEST_ARMOR_WORD90(before) = 0;
    TEST_ARMOR_WORD94(before) = 0;
    train_boss_armor_clear(&obj);
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(shot_objects, shots_before, sizeof(shot_objects));
    return c_test_observe(0, row, observed_values, func_80066DE8_expected, 22);
}
#undef TEST_ARMOR_OWNER_LINK
#undef TEST_ARMOR_OWNER_ADDRESS
#undef TEST_ARMOR_HP_LINK
#undef TEST_ARMOR_HP_ADDRESS
#undef TEST_ARMOR_WORD88
#undef TEST_ARMOR_WORD8C
#undef TEST_ARMOR_WORD90
#undef TEST_ARMOR_WORD94

const struct CTestGroup c_test_groups[] = {
    { "train_armor_context", train_armor_context_cases, train_armor_context_cases_expected, COUNT(train_armor_context_cases), 0 },
    { "train_armor_smoke_context", train_armor_smoke_context_cases, train_armor_smoke_context_cases_expected, COUNT(train_armor_smoke_context_cases), 0 },
    { "func_80066DE8", 0, 0, 1, test_func_80066DE8 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_armor_context_cases) + COUNT(train_armor_smoke_context_cases) + 1;
