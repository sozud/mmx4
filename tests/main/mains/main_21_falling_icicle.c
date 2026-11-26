#include "test_runtime.h"
#include "main/mains/main_21_falling_icicle.h"
#include "support/state_cases.h"
void falling_icicle_shatter(struct MainObj*);
void falling_icicle_wait(struct MainObj*);
void falling_icicle_release(struct MainObj*);

#define FI(step, t80, t82) (state_reset(step, 0, 0), so.state = 1, so.ext.main_21.timer_80 = t80, so.ext.main_21.timer_82 = t82)
#define FIX() (state_extra = (u16)so.ext.main_21.timer_80 | (u32)(u16)so.ext.main_21.timer_82 << 16)
static void fi_shatter_end(void)
{
    FI(0, 0, 0), so.state = 2, so.animation_step.fields.event = 1, falling_icicle_shatter(&so), state_extra = so.state;
}
static void fi_shatter(void) { FI(0, 0, 0), so.state = 2, falling_icicle_shatter(&so), state_extra = so.state; }
static void fi_wait_first(void) { FI(2, 3, 2), falling_icicle_wait(&so), FIX(); }
static void fi_wait_second(void) { FI(2, 0, 2), falling_icicle_wait(&so), FIX(); }
static void fi_wait_done(void) { FI(2, 0, 0), falling_icicle_wait(&so), FIX(); }
static void fi_release(void) { FI(3, 0, 0), so.animation_step.fields.event = 1, falling_icicle_release(&so); }
static void fi_release_wait(void) { FI(3, 0, 0), falling_icicle_release(&so); }

static void (*const falling_icicle_states_cases[])(void) = {
    fi_shatter_end,
    fi_shatter,
    fi_wait_first,
    fi_wait_second,
    fi_wait_done,
    fi_release,
    fi_release_wait,
};
static const u32 falling_icicle_states_expected[] = {
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x3u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x2u,
    0x0u,
    0x2u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x20002u,
    0x0u,
    0x2u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x10000u,
    0x0u,
    0x3u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x4u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x500000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x3u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
};
static u32 test_falling_icicle_states(u32 row)
{
    return state_run(falling_icicle_states_cases[row], row, &falling_icicle_states_expected[row * 10]);
}

void falling_icicle_init(struct MainObj*);
void func_80054D8C(struct MainObj*);
static u32 icicle_main(u32 row)
{
    u32 i, debris = 0;
    state_reset(0, 0, 0);
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.bg_offset = -1;
    g_Player.x_pos.i.hi = row == 2 ? 0x80 : 0x200;
    g_Player.y_pos.i.hi = row == 2 ? 0x60 : 0x200;
    MAIN_OBJECT(&g_Player)->hurt_box = (const u8*)&state_hit_box;
    so.active = 0x41;
    so.id = 21;
    so.x_pos.i.hi = row == 1 ? 0x1000 : 0x80;
    so.y_pos.i.hi = 0x60;
    falling_icicle_init(&so);
    if (row == 3)
        so.collision_flags = 8;
    if (row == 4)
        state_hit(&so, 1, 0, 3);
    func_80054D8C(&so);
    assert(so.unk5 == 2 && so.ext.main_21.timer_80 == 0x1D);
    assert(so.state == (row == 0 ? 1 : row == 1 ? 3
                                                : 2));
    assert(so.unk17 == (row >= 2 ? 4 : 0));
    for (i = 0; i < COUNT(misc_objects); i++)
        debris += misc_objects[i].active == 0x41 && misc_objects[i].id == 3;
    assert(debris == (row >= 2 ? 3 : 0));
    return so.state;
}

const struct CTestGroup c_test_groups[] = {
    { "falling_icicle_states", 0, 0, COUNT(falling_icicle_states_cases), test_falling_icicle_states },
    { "icicle_main", 0, 0, 5, icicle_main },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(falling_icicle_states_cases) + 5;
