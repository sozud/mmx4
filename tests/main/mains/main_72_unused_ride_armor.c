#include "test_runtime.h"
#include "main/mains/main_72_unused_ride_armor.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static struct Fixture {
    struct MainObj obj;
    u32 frames[2];
    const u8* table[10];
};
static void initialize(struct Fixture* fixture, u32 mode)
{
    u32 i;
    memset(fixture, 0, sizeof(*fixture));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(D_80139234, 0, sizeof(D_80139234));
    memset(D_8013924C, 0, sizeof(D_8013924C));
    memset(D_8013E198, 0, sizeof(D_8013E198));
    memset(D_80141EE8, 0, sizeof(D_80141EE8));
    memset(D_80141F50, 0, sizeof(D_80141F50));
    memset(background_objects, 0, sizeof(background_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    fixture->frames[0] = mode == 1 ? 0x04000302 : 0x04010302;
    fixture->frames[1] = 0x06000103;
    if (mode == 2)
        fixture->frames[0] = 0x04010301;
    for (i = 0; i < COUNT(fixture->table); i++)
        fixture->table[i] = (const u8*)fixture->frames;
    fixture->obj.animation_table = fixture->table;
    fixture->obj.animation_cursor = (const u8*)fixture->frames;
    fixture->obj.animation_step.packed = fixture->frames[0];
    fixture->obj.x_pos.i.hi = 50;
    fixture->obj.y_pos.i.hi = 100;
    fixture->obj.ext.main_72.unk84 = 1;
    fixture->obj.collision_flags = 8;
    fixture->obj.previous_animation_index = 9;
    if (mode >= 2)
        fixture->obj.unk6 = 1;
    if (mode >= 3) {
        fixture->obj.ext.main_72.lifetime = mode == 3 ? 1 : 2;
        fixture->obj.ext.main_72.spawn_timer = mode == 4 ? 1 : 2;
    }
    if (mode >= 6 && mode <= 8) {
        fixture->obj.collision_flags = 0;
        fixture->obj.y_pos.i.hi = mode == 6 ? 0 : -100;
        fixture->obj.y_speed = mode == 8 ? -0x60000 : -0x10000;
        fixture->obj.gravity = 0x4200;
    }
    if (mode == 9) {
        fixture->obj.ext.main_72.spawn_timer = 1;
        for (i = 0; i < COUNT(shot_objects); i++)
            shot_objects[i].active = 1;
    }
    if (mode == 10) {
        fixture->obj.collision_flags = 0;
        fixture->obj.y_pos.i.hi = -100;
        fixture->obj.ext.main_72.unk84 = -1;
        fixture->obj.y_speed = -0x10000;
        fixture->obj.gravity = 0x4200;
    }
    g_Player.x_pos.i.hi = 100;
}

#define ANIMATION_CASE(name, function, finished, value)                                          \
    static u32 name(void)                                                                        \
    {                                                                                            \
        struct Fixture fixture;                                                                  \
        u32 actual;                                                                              \
        initialize(&fixture, finished);                                                          \
        function(&fixture.obj);                                                                  \
        assert(fixture.obj.animation_table == fixture.table);                                    \
        assert(fixture.obj.animation_cursor == (const u8*)(fixture.frames + ((finished) == 2))); \
        actual = (u32)(value);                                                                   \
        return actual;                                                                           \
    }
ANIMATION_CASE(jump_state, unused_ride_armor_jump, 0, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(jump_frame, unused_ride_armor_jump, 0, fixture.obj.animation_step.packed)
ANIMATION_CASE(jump_speed, unused_ride_armor_jump, 0, fixture.obj.y_speed)
ANIMATION_CASE(jump_gravity, unused_ride_armor_jump, 0, fixture.obj.gravity)
ANIMATION_CASE(jump_flags, unused_ride_armor_jump, 0, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(jump_timers, unused_ride_armor_jump, 0, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(fall_state, unused_ride_armor_fall, 0, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(fall_frame, unused_ride_armor_fall, 0, fixture.obj.animation_step.packed)
ANIMATION_CASE(fall_speed, unused_ride_armor_fall, 0, fixture.obj.y_speed)
ANIMATION_CASE(fall_gravity, unused_ride_armor_fall, 0, fixture.obj.gravity)
ANIMATION_CASE(fall_flags, unused_ride_armor_fall, 0, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(fall_timers, unused_ride_armor_fall, 0, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(land_state, unused_ride_armor_land, 0, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(land_frame, unused_ride_armor_land, 0, fixture.obj.animation_step.packed)
ANIMATION_CASE(land_speed, unused_ride_armor_land, 0, fixture.obj.y_speed)
ANIMATION_CASE(land_gravity, unused_ride_armor_land, 0, fixture.obj.gravity)
ANIMATION_CASE(land_flags, unused_ride_armor_land, 0, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(land_timers, unused_ride_armor_land, 0, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(land_finished_state, unused_ride_armor_land, 1, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(land_finished_frame, unused_ride_armor_land, 1, fixture.obj.animation_step.packed)
ANIMATION_CASE(land_finished_speed, unused_ride_armor_land, 1, fixture.obj.y_speed)
ANIMATION_CASE(land_finished_gravity, unused_ride_armor_land, 1, fixture.obj.gravity)
ANIMATION_CASE(land_finished_flags, unused_ride_armor_land, 1, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(land_finished_timers, unused_ride_armor_land, 1, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(shoot_state, unused_ride_armor_shoot, 0, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(shoot_frame, unused_ride_armor_shoot, 0, fixture.obj.animation_step.packed)
ANIMATION_CASE(shoot_speed, unused_ride_armor_shoot, 0, fixture.obj.y_speed)
ANIMATION_CASE(shoot_gravity, unused_ride_armor_shoot, 0, fixture.obj.gravity)
ANIMATION_CASE(shoot_flags, unused_ride_armor_shoot, 0, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(shoot_timers, unused_ride_armor_shoot, 0, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(land_advance_state, unused_ride_armor_land, 2, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(land_advance_frame, unused_ride_armor_land, 2, fixture.obj.animation_step.packed)
ANIMATION_CASE(land_advance_speed, unused_ride_armor_land, 2, fixture.obj.y_speed)
ANIMATION_CASE(land_advance_gravity, unused_ride_armor_land, 2, fixture.obj.gravity)
ANIMATION_CASE(land_advance_flags, unused_ride_armor_land, 2, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(land_advance_timers, unused_ride_armor_land, 2, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(shoot_expired_state, unused_ride_armor_shoot, 3, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(shoot_expired_frame, unused_ride_armor_shoot, 3, fixture.obj.animation_step.packed)
ANIMATION_CASE(shoot_expired_speed, unused_ride_armor_shoot, 3, fixture.obj.y_speed)
ANIMATION_CASE(shoot_expired_gravity, unused_ride_armor_shoot, 3, fixture.obj.gravity)
ANIMATION_CASE(shoot_expired_flags, unused_ride_armor_shoot, 3, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(shoot_expired_timers, unused_ride_armor_shoot, 3, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(shoot_spawn_state, unused_ride_armor_shoot, 4, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(shoot_spawn_frame, unused_ride_armor_shoot, 4, fixture.obj.animation_step.packed)
ANIMATION_CASE(shoot_spawn_speed, unused_ride_armor_shoot, 4, fixture.obj.y_speed)
ANIMATION_CASE(shoot_spawn_gravity, unused_ride_armor_shoot, 4, fixture.obj.gravity)
ANIMATION_CASE(shoot_spawn_flags, unused_ride_armor_shoot, 4, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(shoot_spawn_timers, unused_ride_armor_shoot, 4, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(shoot_wait_state, unused_ride_armor_shoot, 5, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(shoot_wait_frame, unused_ride_armor_shoot, 5, fixture.obj.animation_step.packed)
ANIMATION_CASE(shoot_wait_speed, unused_ride_armor_shoot, 5, fixture.obj.y_speed)
ANIMATION_CASE(shoot_wait_gravity, unused_ride_armor_shoot, 5, fixture.obj.gravity)
ANIMATION_CASE(shoot_wait_flags, unused_ride_armor_shoot, 5, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(shoot_wait_timers, unused_ride_armor_shoot, 5, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(shoot_spawn_shot_state, unused_ride_armor_shoot, 4, (u8)shot_objects[0].active | ((u32)(u8)shot_objects[0].id << 8) | ((u32)(u8)shot_objects[0].unk2 << 16))
ANIMATION_CASE(shoot_spawn_shot_position, unused_ride_armor_shoot, 4, shot_objects[0].x_pos.u.hi | ((u32)shot_objects[0].y_pos.u.hi << 16))
ANIMATION_CASE(shoot_spawn_shot_links, unused_ride_armor_shoot, 4, (shot_objects[0].unk7C == &fixture.obj) | ((u32)(shot_objects[0].animation_table == fixture.obj.animation_table) << 1))
ANIMATION_CASE(fall_near_state, unused_ride_armor_fall, 6, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(fall_near_frame, unused_ride_armor_fall, 6, fixture.obj.animation_step.packed)
ANIMATION_CASE(fall_near_speed, unused_ride_armor_fall, 6, fixture.obj.y_speed)
ANIMATION_CASE(fall_near_gravity, unused_ride_armor_fall, 6, fixture.obj.gravity)
ANIMATION_CASE(fall_near_flags, unused_ride_armor_fall, 6, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(fall_near_timers, unused_ride_armor_fall, 6, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(fall_near_x, unused_ride_armor_fall, 6, fixture.obj.x_pos.val)
ANIMATION_CASE(fall_near_y, unused_ride_armor_fall, 6, fixture.obj.y_pos.val)
ANIMATION_CASE(fall_far_state, unused_ride_armor_fall, 7, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(fall_far_frame, unused_ride_armor_fall, 7, fixture.obj.animation_step.packed)
ANIMATION_CASE(fall_far_speed, unused_ride_armor_fall, 7, fixture.obj.y_speed)
ANIMATION_CASE(fall_far_gravity, unused_ride_armor_fall, 7, fixture.obj.gravity)
ANIMATION_CASE(fall_far_flags, unused_ride_armor_fall, 7, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(fall_far_timers, unused_ride_armor_fall, 7, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(fall_far_x, unused_ride_armor_fall, 7, fixture.obj.x_pos.val)
ANIMATION_CASE(fall_far_y, unused_ride_armor_fall, 7, fixture.obj.y_pos.val)
ANIMATION_CASE(fall_capped_state, unused_ride_armor_fall, 8, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(fall_capped_frame, unused_ride_armor_fall, 8, fixture.obj.animation_step.packed)
ANIMATION_CASE(fall_capped_speed, unused_ride_armor_fall, 8, fixture.obj.y_speed)
ANIMATION_CASE(fall_capped_gravity, unused_ride_armor_fall, 8, fixture.obj.gravity)
ANIMATION_CASE(fall_capped_flags, unused_ride_armor_fall, 8, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(fall_capped_timers, unused_ride_armor_fall, 8, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(fall_capped_x, unused_ride_armor_fall, 8, fixture.obj.x_pos.val)
ANIMATION_CASE(fall_capped_y, unused_ride_armor_fall, 8, fixture.obj.y_pos.val)
ANIMATION_CASE(shoot_no_slot_state, unused_ride_armor_shoot, 9, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8))
ANIMATION_CASE(shoot_no_slot_timers, unused_ride_armor_shoot, 9, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(shoot_no_slot_shot_state, unused_ride_armor_shoot, 9, (u8)shot_objects[0].active | ((u32)(u8)shot_objects[0].id << 8))
ANIMATION_CASE(fall_negative_x_x, unused_ride_armor_fall, 10, fixture.obj.x_pos.val)
ANIMATION_CASE(fall_negative_x_x_speed, unused_ride_armor_fall, 10, fixture.obj.x_speed)
ANIMATION_CASE(fall_negative_x_y, unused_ride_armor_fall, 10, fixture.obj.y_pos.val)
ANIMATION_CASE(rapid_initial_state, unused_ride_armor_rapid_fire, 0, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(rapid_initial_frame, unused_ride_armor_rapid_fire, 0, fixture.obj.animation_step.packed)
ANIMATION_CASE(rapid_initial_flags, unused_ride_armor_rapid_fire, 0, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(rapid_initial_timers, unused_ride_armor_rapid_fire, 0, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(rapid_initial_shot_state, unused_ride_armor_rapid_fire, 0, (u8)shot_objects[0].active | ((u32)(u8)shot_objects[0].id << 8) | ((u32)(u8)shot_objects[0].unk2 << 16))
ANIMATION_CASE(rapid_initial_shot_links, unused_ride_armor_rapid_fire, 0, (shot_objects[0].unk7C == &fixture.obj) | ((u32)(shot_objects[0].animation_table == fixture.obj.animation_table) << 1))
ANIMATION_CASE(rapid_expired_state, unused_ride_armor_rapid_fire, 3, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(rapid_expired_frame, unused_ride_armor_rapid_fire, 3, fixture.obj.animation_step.packed)
ANIMATION_CASE(rapid_expired_flags, unused_ride_armor_rapid_fire, 3, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(rapid_expired_timers, unused_ride_armor_rapid_fire, 3, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(rapid_expired_shot_state, unused_ride_armor_rapid_fire, 3, (u8)shot_objects[0].active | ((u32)(u8)shot_objects[0].id << 8) | ((u32)(u8)shot_objects[0].unk2 << 16))
ANIMATION_CASE(rapid_expired_shot_links, unused_ride_armor_rapid_fire, 3, (shot_objects[0].unk7C == &fixture.obj) | ((u32)(shot_objects[0].animation_table == fixture.obj.animation_table) << 1))
ANIMATION_CASE(rapid_pause_state, unused_ride_armor_rapid_fire, 4, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(rapid_pause_frame, unused_ride_armor_rapid_fire, 4, fixture.obj.animation_step.packed)
ANIMATION_CASE(rapid_pause_flags, unused_ride_armor_rapid_fire, 4, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(rapid_pause_timers, unused_ride_armor_rapid_fire, 4, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(rapid_pause_shot_state, unused_ride_armor_rapid_fire, 4, (u8)shot_objects[0].active | ((u32)(u8)shot_objects[0].id << 8) | ((u32)(u8)shot_objects[0].unk2 << 16))
ANIMATION_CASE(rapid_pause_shot_links, unused_ride_armor_rapid_fire, 4, (shot_objects[0].unk7C == &fixture.obj) | ((u32)(shot_objects[0].animation_table == fixture.obj.animation_table) << 1))
ANIMATION_CASE(rapid_spawn_state, unused_ride_armor_rapid_fire, 5, (u8)fixture.obj.unk5 | ((u32)(u8)fixture.obj.unk6 << 8) | ((u32)fixture.obj.unk15 << 16) | ((u32)(u8)fixture.obj.air_state << 24))
ANIMATION_CASE(rapid_spawn_frame, unused_ride_armor_rapid_fire, 5, fixture.obj.animation_step.packed)
ANIMATION_CASE(rapid_spawn_flags, unused_ride_armor_rapid_fire, 5, fixture.obj.collision_flags | ((u32)fixture.obj.unk17 << 8) | ((u32)fixture.obj.previous_animation_index << 16))
ANIMATION_CASE(rapid_spawn_timers, unused_ride_armor_rapid_fire, 5, fixture.obj.ext.main_72.lifetime | ((u32)fixture.obj.ext.main_72.spawn_timer << 8))
ANIMATION_CASE(rapid_spawn_shot_state, unused_ride_armor_rapid_fire, 5, (u8)shot_objects[0].active | ((u32)(u8)shot_objects[0].id << 8) | ((u32)(u8)shot_objects[0].unk2 << 16))
ANIMATION_CASE(rapid_spawn_shot_links, unused_ride_armor_rapid_fire, 5, (shot_objects[0].unk7C == &fixture.obj) | ((u32)(shot_objects[0].animation_table == fixture.obj.animation_table) << 1))

static const CTestCase ride_armor_animation_cases[] = {
    jump_state,
    jump_frame,
    jump_speed,
    jump_gravity,
    jump_flags,
    jump_timers,
    fall_state,
    fall_frame,
    fall_speed,
    fall_gravity,
    fall_flags,
    fall_timers,
    land_state,
    land_frame,
    land_speed,
    land_gravity,
    land_flags,
    land_timers,
    land_finished_state,
    land_finished_frame,
    land_finished_speed,
    land_finished_gravity,
    land_finished_flags,
    land_finished_timers,
    shoot_state,
    shoot_frame,
    shoot_speed,
    shoot_gravity,
    shoot_flags,
    shoot_timers,
    land_advance_state,
    land_advance_frame,
    land_advance_speed,
    land_advance_gravity,
    land_advance_flags,
    land_advance_timers,
    shoot_expired_state,
    shoot_expired_frame,
    shoot_expired_speed,
    shoot_expired_gravity,
    shoot_expired_flags,
    shoot_expired_timers,
    shoot_spawn_state,
    shoot_spawn_frame,
    shoot_spawn_speed,
    shoot_spawn_gravity,
    shoot_spawn_flags,
    shoot_spawn_timers,
    shoot_wait_state,
    shoot_wait_frame,
    shoot_wait_speed,
    shoot_wait_gravity,
    shoot_wait_flags,
    shoot_wait_timers,
    shoot_spawn_shot_state,
    shoot_spawn_shot_position,
    shoot_spawn_shot_links,
    fall_near_state,
    fall_near_frame,
    fall_near_speed,
    fall_near_gravity,
    fall_near_flags,
    fall_near_timers,
    fall_near_x,
    fall_near_y,
    fall_far_state,
    fall_far_frame,
    fall_far_speed,
    fall_far_gravity,
    fall_far_flags,
    fall_far_timers,
    fall_far_x,
    fall_far_y,
    fall_capped_state,
    fall_capped_frame,
    fall_capped_speed,
    fall_capped_gravity,
    fall_capped_flags,
    fall_capped_timers,
    fall_capped_x,
    fall_capped_y,
    shoot_no_slot_state,
    shoot_no_slot_timers,
    shoot_no_slot_shot_state,
    fall_negative_x_x,
    fall_negative_x_x_speed,
    fall_negative_x_y,
    rapid_initial_state,
    rapid_initial_frame,
    rapid_initial_flags,
    rapid_initial_timers,
    rapid_initial_shot_state,
    rapid_initial_shot_links,
    rapid_expired_state,
    rapid_expired_frame,
    rapid_expired_flags,
    rapid_expired_timers,
    rapid_expired_shot_state,
    rapid_expired_shot_links,
    rapid_pause_state,
    rapid_pause_frame,
    rapid_pause_flags,
    rapid_pause_timers,
    rapid_pause_shot_state,
    rapid_pause_shot_links,
    rapid_spawn_state,
    rapid_spawn_frame,
    rapid_spawn_flags,
    rapid_spawn_timers,
    rapid_spawn_shot_state,
    rapid_spawn_shot_links,
};
static const u32 ride_armor_animation_cases_expected[] = { 0x1400100u, 0x4010302u, 0x53E00u, 0x4200u, 0xFF0200u, 0x0u, 0x1000005u, 0x4010302u, 0x0u, 0x4200u, 0xFF0308u, 0x0u, 0x100u, 0x4010301u, 0x0u, 0x0u, 0xFF0408u, 0x0u, 0x7u, 0x4000302u, 0x0u, 0x0u, 0xFF0408u, 0x0u, 0x400100u, 0x4010301u, 0x0u, 0x0u, 0xFF0808u, 0xF3Fu, 0x100u, 0x6000103u, 0x0u, 0x0u, 0x90008u, 0x0u, 0x2u, 0x4010302u, 0x0u, 0x0u, 0x90008u, 0x200u, 0x100u, 0x4010301u, 0x0u, 0x0u, 0x90008u, 0x1001u, 0x100u, 0x4010301u, 0x0u, 0x0u, 0x90008u, 0x101u, 0x2F41u, 0x640032u, 0x3u, 0x2u, 0x4010302u, 0xFFFF0000u, 0x4200u, 0x90000u, 0x202u, 0x320000u, 0x0u, 0x100u, 0x4010302u, 0xFFFEBE00u, 0x4200u, 0x90000u, 0x202u, 0x31FF00u, 0xFF9D0000u, 0x100u, 0x4010302u, 0xFFF9DE00u, 0x4200u, 0x90000u, 0x202u, 0x31FF00u, 0xFFA1E000u, 0x100u, 0x1001u, 0x1u, 0x320100u, 0x100u, 0xFF9D0000u, 0x400100u, 0x4010301u, 0xFF0908u, 0x2F7Fu, 0x12F41u, 0x3u, 0x2u, 0x4010302u, 0x90008u, 0x200u, 0x0u, 0x0u, 0x100u, 0x4010301u, 0x90008u, 0x1u, 0x0u, 0x0u, 0x100u, 0x4010301u, 0x90008u, 0x101u, 0x12F41u, 0x3u };
#undef ANIMATION_CASE

struct unused_ride_armor_fall_case {
    u32 collision_flags;
    u32 expected[6];
};
static const struct unused_ride_armor_fall_case unused_ride_armor_fall_cases[] = {
    { 8, { 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, { 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_unused_ride_armor_fall(u32 row)
{
    const struct unused_ride_armor_fall_case* c = &unused_ride_armor_fall_cases[row];
    u32 observed_values[6];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk6 = -1;
    obj.collision_flags = c->collision_flags;
    unused_ride_armor_fall(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.gravity;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_accel;
    observed_values[4] = (u32)obj.x_speed;
    observed_values[5] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

struct unused_ride_armor_jump_case {
    u32 collision_flags, y_speed, obj_y_pos_hi, g_Player_y_pos_hi;
    u32 expected[7];
};
static const struct unused_ride_armor_jump_case unused_ride_armor_jump_cases[] = {
    { 4, 0, 0, 0, { 0u, 4u, 0u, 0u, 0u, 0u, 0u } },
    { 0, -1, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0xFFFFFFFFu } },
    { 0, 0, -28704, -28528, { 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 0, 0, 0, { 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u } },
};
static u32 test_unused_ride_armor_jump(u32 row)
{
    const struct unused_ride_armor_jump_case* c = &unused_ride_armor_jump_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk6 = -1;
    obj.collision_flags = c->collision_flags;
    obj.y_speed = c->y_speed;
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    g_Player.y_pos.i.hi = c->g_Player_y_pos_hi;
    unused_ride_armor_jump(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.collision_flags;
    observed_values[2] = (u32)obj.gravity;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.x_accel;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

const struct CTestGroup c_test_groups[] = {
    { "ride_armor_animation", ride_armor_animation_cases, ride_armor_animation_cases_expected, COUNT(ride_armor_animation_cases), 0 },
    { "unused_ride_armor_fall", 0, 0, 2, test_unused_ride_armor_fall },
    { "unused_ride_armor_jump", 0, 0, 4, test_unused_ride_armor_jump },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ride_armor_animation_cases) + 2 + 4;
