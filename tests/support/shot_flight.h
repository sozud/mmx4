#ifndef MMX4_TESTS_SHOT_FLIGHT_H
#define MMX4_TESTS_SHOT_FLIGHT_H

static struct WeaponObj shot_flight_owner;
#define sf state_room.shot
#define SHOT_FLIGHT(st, step, setup)                                                                                      \
    (state_reset(step, 0, 0), memset(weapon_objects, 0, sizeof(weapon_objects)),                                          \
        memset(&shot_flight_owner, 0, sizeof(shot_flight_owner)), shot_flight_owner.animation_table = (void*)state_table, \
        shot_flight_owner.x_pos.i.hi = 0x90, shot_flight_owner.y_pos.i.hi = 0x70, shot_flight_owner.unk42 = 0x8123,       \
        sf.active = 1, sf.state = st, sf.unk7C = &shot_flight_owner, sf.x_pos.i.hi = 0x80, sf.y_pos.i.hi = 0x60,          \
        g_Player.x_pos.i.hi = 0x400, g_Player.y_pos.i.hi = 0x60, SPIKE_IMMUNE_SET(g_Player, 1), setup)
#define SHOT_PLAYER_HERE(box)                                                     \
    (sf.unk50.data = box, g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x60, \
        ((struct MainObj*)&g_Player)->hurt_box = &state_hit_box, g_Player.hp = 0x10, SPIKE_IMMUNE_SET(g_Player, 0))
#define SHOT_DESTROYED() (((struct MainObj*)&sf)->hp = 1, state_hit((struct MainObj*)&sf, 0, 0, 1))
#define SHOT_OFF_SCREEN() (sf.x_pos.i.hi = 0x200)

#endif
