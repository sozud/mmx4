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
        if ((previous & 0xB) && drift && !((drift > 0 ? 2 : 1) & previous))
            x += drift;
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
const struct CTestGroup c_test_groups[] = { { "entity_overlap_touch_separation_resolution_and_carried_motion", NULL, NULL, 37, contact } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 37;
