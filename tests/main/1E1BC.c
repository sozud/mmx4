#include "test_runtime.h"
#include "main/1E1BC.h"
static struct Unk_unk68 bounds = { 0, 0, 10, 10 };
static const s8 offsets[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
static const u8 contact_flags[] = { 1, 2, 8, 4 };
static u32 contact(u32 row)
{
    struct PlayerObj obj, expected, player_before, entity_expected;
    struct RideArmorObj armor_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 side = row % 4, gap = row / 4 % 3, preference = row / 12 % 3, alive = row < 36, movement = (side + gap) % 3;
    s32 distance = 19 + gap, dx = offsets[side][0] * distance, dy = offsets[side][1] * distance, drift = (s32)movement - 1, x = dx, y = dy, penetration_x = 0, penetration_y = 0;
    u8 flags = 0, previous = alive && gap == 1 ? contact_flags[side] : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    memset(&qux_object, 0, sizeof(qux_object));
    obj.active = 0x41;
    obj.unk68 = &bounds;
    obj.unk66 = (s32)preference - 1;
    obj.unk75 = 1;
    obj.unk73 = previous;
    obj.unk77 = (previous & 0xB) != 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk18.val = obj.x_pos.val - drift * 65536;
    obj.unk1C = obj.y_pos;
    g_Player.active = 0x21;
    g_Player.hp = 30;
    g_Player.unk68 = &bounds;
    g_Player.x_pos.i.hi = 1024;
    g_Player.y_pos.i.hi = 1024;
    g_Entity.active = alive ? 0x41 : 0;
    g_Entity.unk68 = &bounds;
    g_Entity.unk71 = 0x10;
    g_Entity.x_pos.val = (160 + dx) * 65536 + 0xAAAA;
    g_Entity.y_pos.val = (120 + dy) * 65536 + 0xBBBB;
    g_Entity.unk18.val = g_Entity.x_pos.val - drift * 65536;
    g_Entity.unk1C = g_Entity.y_pos;
    expected = obj;
    player_before = g_Player;
    entity_expected = g_Entity;
    armor_before = qux_object;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    if (alive) {
        if (gap == 0) {
            penetration_x = dx < 0 ? -20 - dx : 20 - dx;
            penetration_y = dy < 0 ? -20 - dy : 20 - dy;
            if (preference == 2 || (preference == 1 && (penetration_x < 0 ? -penetration_x : penetration_x) < (penetration_y < 0 ? -penetration_y : penetration_y)))
                x += penetration_x;
            else
                y += penetration_y;
            entity_expected.unk6C = penetration_x;
            entity_expected.unk6E = penetration_y;
        }
#ifndef VERSION_DEMO
        if ((previous & 0xB) && drift && !((drift > 0 ? 2 : 1) & previous))
            x += drift;
#endif
        if ((y == 20 || y == -20) && x > -20 && x < 20)
            flags |= y > 0 ? 4 : 8;
        if ((x == 20 || x == -20) && y > -20 && y < 20) {
            flags |= x > 0 ? 2 : 1;
            entity_expected.wall_climbable = 1;
        }
        entity_expected.x_pos.i.hi = 160 + x;
        entity_expected.y_pos.i.hi = 120 + y;
        entity_expected.unk71 |= flags;
        expected.unk73 = flags;
        expected.unk77 = (flags & 0xB) != 0;
    }
    collide_with_players(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&g_Entity, &entity_expected, sizeof(g_Entity));
    c_test_same_words(&qux_object, &armor_before, sizeof(qux_object));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 10 && bounds.unk3 == 10);
    return 1;
}
#ifndef VERSION_SATURN_PROTO
static u32 armor_carry(u32 row)
{
    struct PlayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    memset(&qux_object, 0, sizeof(qux_object));
    obj.active = 0x41;
    obj.unk68 = &bounds;
    obj.unk78 = row;
    obj.x_pos.i.hi = 160;
    obj.unk18.i.hi = 158;
    obj.y_pos.i.hi = obj.unk1C.i.hi = 120;
    g_Player.unk68 = &bounds;
    g_Player.x_pos.i.hi = g_Player.y_pos.i.hi = 1024;
    qux_object.active = 1;
    qux_object.unk68 = &bounds;
    qux_object.x_pos.i.hi = qux_object.unk18.i.hi = 400;
    qux_object.y_pos.i.hi = qux_object.unk1C.i.hi = 120;
    collide_with_players(&obj);
    assert(qux_object.x_pos.i.hi == (row ? 402 : 400) && qux_object.y_pos.i.hi == 120);
    assert(obj.unk74 == 0 && obj.unk78 == 0 && g_Player.x_pos.i.hi == 1024);
    return qux_object.x_pos.i.hi;
}
#endif

static struct Unk_unk68 shot_box = { 0, 0, 8, 8 };
static u32 shot_hits(u32 row)
{
    struct ShotObj shot;
    u32 riding = row < 4, hit;
    memset(&shot, 0, sizeof(shot));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&qux_object, 0, sizeof(qux_object));
    SPIKE_IMMUNE_SET(g_Player, 0);
    ((struct MainObj*)&shot)->attack_box = &shot_box;
    shot.x_pos.i.hi = row == 1 ? 300 : row == 3 ? 105 : 95;
    shot.y_pos.i.hi = 50;
    shot.unk60 = row == 3 ? 30 : row >= 4 ? 2 : 3;
    shot.unk62 = row >= 4 ? 5 : 0;
    g_Player.ride_state = riding ? -1 : 0;
    ((struct MainObj*)&g_Player)->hurt_box = &shot_box;
    g_Player.x_pos.i.hi = 100;
    g_Player.y_pos.i.hi = 50;
    g_Player.hp = 20;
    g_Player.unk2 = row == 5;
    g_Player.armor_parts = row == 4 ? 2 : 0;
    g_Player.boss_flags = row == 5 ? 0x20 : 0;
    g_Player.weapon_energy[0] = row == 4 ? 0x30 : 0x10;
    ((struct MainObj*)&qux_object)->hurt_box = &shot_box;
    qux_object.x_pos.i.hi = 100;
    qux_object.y_pos.i.hi = 50;
    qux_object.hp = 20;
    qux_object.unk85 = row == 0;
    hit = func_8002D9BC(&shot);
    assert(hit == (row >= 2));
    if (riding) {
        assert((u8)qux_object.hp == (row < 2 ? 20 : row == 2 ? (17 | 0x80) : 0x80));
        assert(qux_object.unk63 == (row < 2 ? 0 : row == 2 ? 1 : 2) && qux_object.unk84 == (row == 3 ? PLAYER_FACING_RIGHT : 0));
        assert(g_Player.hp == 20);
    } else {
        assert((u8)g_Player.hp == ((row == 4 ? 19 : 18) | 0x80) && g_Player.hurt_type == 5);
        assert(g_Player.weapon_energy[0] == (row == 4 ? 0x30 : 0x16) && g_Player.hit_facing == 0);
    }
    return hit;
}

extern u16 D_80106070[64];
static u8 hit_table[128];
static u32 hit_frames[4];
static u32 weapon_hits(u32 row)
{
    struct MainObj* object = &main_objects[0];
    struct WeaponObj* weapon = &weapon_objects[0];
    s32 result;
    memset(main_objects, 0, sizeof(main_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(hit_table, 0, sizeof(hit_table));
    memset(hit_frames, 0, sizeof(hit_frames));
    TEST_SPRITE_FRAMES = (u8*)hit_frames;
    object->unk7A = row == 0;
    object->unk65 = 5;
    object->collision_data = row == 1 || row == 2 ? (void*)D_80106070 : (void*)hit_table;
    object->hurt_box = &shot_box;
    object->hp = 10;
    object->unk5 = object->unk6 = 3;
    object->x_pos.i.hi = weapon->x_pos.i.hi = 100;
    object->y_pos.i.hi = weapon->y_pos.i.hi = 50;
    g_Player.unk2 = row == 2;
    weapon->active = 1;
    weapon->id = row == 4 ? 0x3D : row == 5 ? 0x3E : 5;
    ((struct MainObj*)weapon)->attack_box = &shot_box;
    hit_table[5 * 2] = 2;
    hit_table[0x3D * 2] = 1;
    hit_table[0x3D * 2 + 1] = 1;
    hit_table[0x3E * 2] = hit_table[0x3E * 2 + 1] = 1;
    result = func_8002DD04(object);
    assert(result == (row >= 4 ? weapon->id + 1 : 0));
    assert(object->unk65 == (row == 1 || row == 2 ? 5 : 0));
    assert(object->hp == (row >= 4 ? 9 : 10) && g_Player.update_delay_request == (row >= 4));
    assert(object->unk63 == (row == 3 ? 2 : row >= 4 ? 1 : 0));
    assert(object->unk5 == (row >= 4 ? 0 : 3) && visual_objects[0].active == (row >= 4 ? 0x21 : 0));
    return result;
}

const struct CTestGroup c_test_groups[] = {
    { "entity_overlap_touch_separation_resolution_and_carried_motion", NULL, NULL, 37, contact },
#ifndef VERSION_SATURN_PROTO
    { "armor_carry", NULL, NULL, 2, armor_carry },
#endif
    { "shot_hits", NULL, NULL, 6, shot_hits },
    { "weapon_hits", NULL, NULL, 6, weapon_hits },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 37 + 6 + 6
#ifndef VERSION_SATURN_PROTO
    + 2
#endif
    ;
