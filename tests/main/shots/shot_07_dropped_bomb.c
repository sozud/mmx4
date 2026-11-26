#include "test_runtime.h"

#include "support/state_cases.h"
#include "support/shot_flight.h"
#include "main/shots/shot_07_dropped_bomb.h"

void dropped_bomb_idle(struct ShotObj*);
extern u8 dropped_bomb_hit_box[4];
#define BOMB(st, setup) (SHOT_FLIGHT(st, 0, setup), dropped_bomb_update(&sf))
static void bomb_init(void) { BOMB(0, 0); }
static void bomb_destroyed(void) { BOMB(1, SHOT_DESTROYED()); }
static void bomb_lands(void)
{
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    BOMB(1, (state_terrain(0x38), sf.unk68 = (struct Unk_unk68*)dropped_bomb_hit_box, SP_CUR_MAIN_OBJ = (struct MainObj*)&sf));
    SP_CUR_MAIN_OBJ = current;
}
static void bomb_falls(void) { BOMB(1, 0); }
static void bomb_off_screen(void) { BOMB(1, SHOT_OFF_SCREEN()); }
static void bomb_despawn(void) { BOMB(2, 0); }
static void bomb_idle(void) { SHOT_FLIGHT(3, 0, 0), dropped_bomb_idle(&sf); }
static void (*const bomb_cases[])(void) = {
    bomb_init,
    bomb_destroyed,
    bomb_lands,
    bomb_falls,
    bomb_off_screen,
    bomb_despawn,
    bomb_idle,
};
static const u32 bomb_expected[] = {
    0x1u, 0xFF000001u, 0x800000u, 0x600000u, 0x0u, 0xFFFF0000u, 0x300000u, 0x50000u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x48000u, 0x0u, 0x2100u,
    0x2u, 0x1u, 0x7B0000u, 0x7C0000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x2100u,
    0x1u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x2u, 0x1u, 0x2000000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x40000u, 0x0u, 0x0u,
    0x0u, 0x0u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x3u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_bomb(u32 row)
{
    return object_run(bomb_cases[row], row, &bomb_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "dropped_bomb_states", 0, 0, COUNT(bomb_cases), test_bomb },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(bomb_cases);
