#include "test_runtime.h"
#include "main/shots/shot_30_cannon_shot.h"

#ifndef VERSION_DEMO
static const u32 cannon_shot_spawn_flash_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_cannon_shot_spawn_flash(u32 row)
{
    u32 observed_values[10];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    FILL_ACTIVE(visual_objects, 32, 255 ? 1 : 0);
    cannon_shot_spawn_flash(&obj);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].bg_offset;
    observed_values[2] = (u32)visual_objects[0].id;
    observed_values[3] = (u32)visual_objects[0].unk15;
    observed_values[4] = (u32)visual_objects[0].unk16;
    observed_values[5] = (u32)visual_objects[0].unk2;
    observed_values[6] = (u32)visual_objects[0].unk40;
    observed_values[7] = (u32)visual_objects[0].unk42;
    observed_values[8] = (u32)visual_objects[0].x_pos.val;
    observed_values[9] = (u32)visual_objects[0].y_pos.val;
    return c_test_observe(0, row, observed_values, cannon_shot_spawn_flash_expected, 10);
}
#endif

#include "support/state_cases.h"
void func_8009FD00(struct ShotObj*);
static struct WeaponObj cs_owner;
#define cs state_room.shot
#define CS(st, kind, face) (state_reset(0, 0, 0), memset(&cs_owner, 0, sizeof(cs_owner)), memset(weapon_objects, 0, sizeof(weapon_objects)), cs_owner.x_pos.i.hi = 0x100, cs_owner.y_pos.i.hi = 0x80, cs.active = 1, cs.state = st, cs.unk2 = kind, cs.unk15 = face, cs.unk42 = 0x8123, cs.unk7C = &cs_owner, cs.x_pos.i.hi = 0x80, cs.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x400, g_Player.y_pos.i.hi = 0x60, SPIKE_IMMUNE_SET(g_Player, 1))
#define CSX() (state_extra = cs.unk84.value | (u32)cs.unk8C.word << 8 | (u32)cs.unk17 << 16)
static void cs_init_0_left(void)
{
    CS(0, 0, 0), cannon_shot_update(&cs), CSX();
}
static void cs_init_0_right(void) { CS(0, 0, PLAYER_FACING_RIGHT), cannon_shot_update(&cs), CSX(); }
static void cs_init_1_left(void) { CS(0, 1, 0), cannon_shot_update(&cs), CSX(); }
static void cs_init_1_right(void) { CS(0, 1, PLAYER_FACING_RIGHT), cannon_shot_update(&cs), CSX(); }
static void cs_init_2_left(void) { CS(0, 2, 0), cannon_shot_update(&cs), CSX(); }
static void cs_init_2_right(void) { CS(0, 2, PLAYER_FACING_RIGHT), cannon_shot_update(&cs), CSX(); }
#define FLY(face, timer, anim, setup) (CS(1, 0, face), cs.unk84.value = timer, cs.unk17 = anim, setup, func_8009FD00(&cs), CSX())
static void cs_destroyed_fast(void)
{
    FLY(0, 5, 3, (cs.x_vel.val = -0x40000, cs.unk28 = 0x100, ((struct MainObj*)&cs)->hp = 1, state_hit((struct MainObj*)&cs, 0, 0, 1)));
}
static void cs_fires_right(void) { FLY(PLAYER_FACING_RIGHT, 1, 3, 0); }
static void cs_fires_left(void) { FLY(0, 1, 3, 0); }
static void cs_grounded_off_screen(void) { FLY(0, 1, 4, cs.x_pos.i.hi = 0x200); }
static void cs_waits(void) { FLY(0, 5, 3, 0); }
static void cs_despawn(void) { CS(2, 0, 0), cannon_shot_update(&cs), CSX(); }
static void cs_idle(void) { CS(3, 0, 0), cannon_shot_update(&cs), CSX(); }
static void (*const cs_cases[])(void) = {
    cs_init_0_left,
    cs_init_0_right,
    cs_init_1_left,
    cs_init_1_right,
    cs_init_2_left,
    cs_init_2_right,
    cs_destroyed_fast,
    cs_fires_right,
    cs_fires_left,
    cs_grounded_off_screen,
    cs_waits,
    cs_despawn,
    cs_idle,
};
#define CS_FLASH DEMO_ALT(0x4100u, 0x0u)
#define CS_MARK DEMO_ALT(0x100u, 0x0u)
static const u32 cs_expected[] = {
    0x1u,
    0xFF000001u,
    0xE00000u,
    0x780000u,
    0x0u,
    0x0u,
    0x0u,
    0x50123u,
    0x30010u,
    CS_FLASH,
    0x1u,
    0xFF400001u,
    0x1200000u,
    0x780000u,
    0x0u,
    0x0u,
    0x0u,
    0x50123u,
    0x30010u,
    CS_FLASH,
    0x1u,
    0xFF000101u,
    0xE30000u,
    0x8E0000u,
    0x0u,
    0x0u,
    0x0u,
    0x50123u,
    0x30010u,
    CS_FLASH,
    0x1u,
    0xFF400101u,
    0x11D0000u,
    0x8E0000u,
    0x0u,
    0x0u,
    0x0u,
    0x50123u,
    0x30010u,
    CS_FLASH,
    0x1u,
    0xFF000201u,
    0xF40000u,
    0x920000u,
    0x0u,
    0x0u,
    0x0u,
    0x50123u,
    0x30010u,
    CS_FLASH,
    0x1u,
    0xFF400201u,
    0x10C0000u,
    0x920000u,
    0x0u,
    0x0u,
    0x0u,
    0x50123u,
    0x30010u,
    CS_FLASH,
    0x2u,
    0x1u,
    0x7C0000u,
    0x600000u,
    0xFFFBFF00u,
    0x0u,
    0x0u,
    0x48123u,
    0x30005u | CS_MARK,
    0x2100u,
    0x1u,
    0xFF400001u,
    0x900000u,
    0x600000u,
    0x22000u,
    0x0u,
    0x600u,
    0x58123u,
    0x40000u,
    0x0u,
    0x1u,
    0xFF000001u,
    0x700000u,
    0x600000u,
    0xFFFDE000u,
    0x0u,
    0x600u,
    0x58123u,
    0x40000u,
    0x0u,
    0x2u,
    0x1u,
    0x2000000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x48123u,
    0x40000u | CS_MARK,
    0x0u,
    0x1u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x48123u,
    0x30004u,
    0x0u,
    0x0u,
    0x0u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x58123u,
    0x0u,
    0x0u,
    0x3u,
    0x1u,
    0x800000u,
    0x600000u,
    0x0u,
    0x0u,
    0x0u,
    0x58123u,
    0x0u,
    0x0u,
};
static u32 test_cs(u32 row)
{
    return object_run(cs_cases[row], row, &cs_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
#ifndef VERSION_DEMO
    { "cannon_shot_spawn_flash", 0, 0, 1, test_cannon_shot_spawn_flash },
#endif
    { "cannon_shot_states", 0, 0, COUNT(cs_cases), test_cs },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(cs_cases)
#ifndef VERSION_DEMO
    + 1
#endif
    ;
