#include "test_runtime.h"
extern union AnimationStep* wall_crawler_animations[25];
extern u8 wall_crawler_shot_hit_boxes[8], wall_crawler_shot_terrain_box[4];
extern s8 wall_crawler_shot_spawn_offsets[16];

static u32 default_case(u32 observation)
{
    struct ShotObj obj, before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 6;
    obj.state = 1;
    obj.unk2 = 0;
    obj.unk15 = 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -65536;
    obj.unk42 = 0x9234;
    obj.unk28 = 0x27;
    obj.unk2C = 0x28;
    obj.unk67 = 0x25;
    obj.unk16 = 0x26;
    obj.animation_table = (u32**)wall_crawler_animations;
    set_animation(&obj, 0);
    before = obj;
    func_8009A9E4(&obj);
    before.unk68 = (struct Unk_unk68*)wall_crawler_shot_terrain_box;
    before.unk54 = wall_crawler_shot_hit_boxes;
    before.unk50.data = wall_crawler_shot_hit_boxes;
    before.on_screen = 1;
    before.unk58.data = (const u8*)D_80105FF0;
    before.state = 2;
    before.unk28 = before.unk2C = 0;
    before.unk5C = 1;
    before.unk67 = before.unk16 = 0;
    before.unk60 = 2;
    before.unk42 = 0x1234;
    before.x_vel.val = 3 * 65536;
    before.y_vel.val = -3 * 65536;
    before.x_pos.i.hi += wall_crawler_shot_spawn_offsets[2];
    before.y_pos.i.hi += wall_crawler_shot_spawn_offsets[3];
    before.unk17 = 11;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)wall_crawler_animations[11];
    before.animation_step = *wall_crawler_animations[11];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    if (observation == 0)
        return (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16);
    return obj.animation_step.packed;
}
#define CASE(n)                  \
    static u32 default_##n(void) \
    {                            \
        return default_case(n);  \
    }
CASE(0)
CASE(1)
#define ENTRY(n) default_##n,
static const CTestCase wall_crawler_shot_default_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 wall_crawler_shot_default_cases_expected[] = { 0xC80071u, 0x10010001u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "wall_crawler_shot_default", wall_crawler_shot_default_cases, wall_crawler_shot_default_cases_expected, COUNT(wall_crawler_shot_default_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wall_crawler_shot_default_cases);
