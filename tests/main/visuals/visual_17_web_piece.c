#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/visuals/visual_17_web_piece.h"
#include "main/55C4.h"
#include "main/mains/main_43_web_spider.h"

void func_800B20CC(struct VisualObj*);
void web_piece_main(struct VisualObj*);
void func_800B22B4(struct VisualObj*);
void web_piece_hang(struct VisualObj*);
void web_piece_fall(struct VisualObj*);
extern s16 web_piece_positions_a[4][2], web_piece_positions_b[4][2];
u8 angle_from_delta(s32, s32);

static u32 web_rows(u32 index)
{
    static const u8 scenarios[] = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12 };
    u32 row = scenarios[index];
    struct VisualObj obj;
    struct MainObj owner;
    struct QuadObj quad;
    const s16* target;
    u8 heading;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&quad, 0, sizeof(quad));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    memset(visual_objects, 0, sizeof(visual_objects));
    engine_obj.stage = 5;
    owner.active = 0x41;
    owner.state = 1;
    owner.x_pos.i.hi = 0x12C0;
    owner.y_pos.i.hi = 0x500;
    obj.active = 0x41;
    obj.id = 17;
    obj.state = 1;
    obj.unk50 = PLAYER_OBJECT(&owner);
    obj.x_pos.i.hi = 0x12C0;
    obj.y_pos.i.hi = 0x500;
    obj.animation_table = (u32**)web_spider_animations;
    set_animation(&obj, 0x17);
    obj.animation_step.fields.duration = 2;
    background_objects[0].x_pos.i.hi = 0x1200;
    background_objects[0].y_pos.i.hi = 0x480;
    switch (row) {
    case 0:
    case 1:
        obj.state = 0;
        obj.unk2 = row == 0 ? 0 : 2;
        func_800B20CC(&obj);
        assert(obj.state == 1 && obj.on_screen == 1 && obj.unk17 == (row == 0 ? 0x18 : 0x17));
        assert(obj.unk16 == (row == 0 ? VISUAL_SATURN_LAYER(3) : VISUAL_SATURN_LAYER(5)));
        if (row == 1) {
            assert(obj.x_vel.val > 0 && obj.y_vel.val < 0 && obj.unk5C.owner == (struct PlayerObj*)&g_QuadObjects[0]);
            assert(g_QuadObjects[0].active == (s8)0x81 && g_QuadObjects[0].id == 5);
        }
        break;
    case 2:
    case 3:
        owner.ext.main_43.flash_timer = row == 3 ? 5 : 0;
        owner.x_pos.i.hi = 0x1280;
        web_piece_main(&obj);
        assert(obj.active == (row == 2 ? 0 : 0x41) && (row == 2 || obj.x_pos.i.hi == 0x1280));
        assert(row == 2 || obj.on_screen == 1);
        break;
    case 4:
    case 5:
    case 6:
        engine_obj.stage = row == 6 ? 0xC : 5;
        obj.unk2 = 2;
        obj.y_vel.val = -0x10000;
        obj.unk5C.owner = (struct PlayerObj*)&quad;
        if (row == 6) {
            obj.x_pos.i.hi = 0x10C0;
            obj.y_pos.i.hi = 0x600;
        }
        target = row == 6 ? web_piece_positions_b[1] : web_piece_positions_a[1];
        heading = angle_from_delta(obj.x_pos.val - (target[0] << 16), obj.y_pos.val - (target[1] << 16));
        obj.unk54 = row == 4 ? heading ^ 0x10 : heading;
        web_piece_main(&obj);
        if (row == 4) {
            assert(obj.unk5 == 1 && obj.x_pos.i.hi == web_piece_positions_a[1][0] && obj.y_pos.i.hi == web_piece_positions_a[1][1]);
            assert(quad.state == 2 && obj.y_vel.val == 0);
        } else {
            assert(obj.unk5 == 0 && quad.state == 0 && obj.y_pos.i.hi == (row == 6 ? 0x601 : 0x501));
        }
        assert(quad.x_pos.val == obj.x_pos.val && quad.y_pos.val == obj.y_pos.val);
        break;
    case 7:
    case 8:
        obj.unk2 = 2;
        obj.unk5 = 1;
        owner.state = row == 7 ? 2 : 1;
        web_piece_main(&obj);
        assert(obj.state == (row == 7 ? 2 : 1) && obj.animation_step.fields.duration == (row == 7 ? 2 : 1));
        break;
    default:
        obj.state = 2;
        obj.unk5 = row == 9 ? 0 : row == 12 ? 2 : 1;
        obj.unk54 = row == 10 ? 1 : 5;
        obj.y_vel.val = -0x8000;
        web_piece_fall(&obj);
        if (row == 12) {
            assert(obj.active == 0);
            break;
        }
        assert(obj.unk5 == (row == 10 ? 2 : 1) && obj.unk54 == (row == 9 ? 0x78 : row == 10 ? 0 : 4));
        for (i = 0; i < COUNT(visual_objects) && visual_objects[i].active == 0; i++)
            ;
        assert((i < COUNT(visual_objects)) == (row == 10));
        break;
    }
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "web_rows", 0, 0, 12, web_rows },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12;
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
