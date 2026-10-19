#include "test_runtime.h"

#include "support/state_cases.h"

#include "support/player_cases.h"
#include "main/player_special.h"
#include "main/weapons/weapon_24_zero_saber.h"
#define sw state_room.weapon
#define SABER(animation) (player_reset(PLAYER_ZERO_SABER, 1, animation), memset(&state_room, 0, sizeof(state_room)), effect_objects[0].active = shot_objects[0].active = 0, pl.hp = 0x10)
static void zs_aura_reset(void)
{
    SABER(0x66);
    state_room.visual.active = 1;
    pl.hp = 0;
    func_80098338(&state_room.visual);
}
static void zs_aura_locked(void)
{
    SABER(0x66);
    state_room.visual.active = 1;
    pl.input_locked = 1;
    func_80098338(&state_room.visual);
}
static void zs_aura_cancelled(void)
{
    SABER(0x66);
    state_room.visual.active = 1;
    pl.actions_reset = 1;
    func_80098338(&state_room.visual);
}
static void zs_aura_other(void)
{
    SABER(0x58);
    state_room.visual.active = 1;
    func_80098338(&state_room.visual);
}
static void zs_aura_start(void)
{
    SABER(0x66);
    func_80098338(&state_room.visual);
}
static void zs_aura_follow(void)
{
    SABER(0x66);
    state_room.visual.state = 1;
    state_room.visual.animation_step.fields.relative_step = 1;
    func_80098338(&state_room.visual);
}
static void zs_aura_end(void)
{
    SABER(0x66);
    state_room.visual.state = 1;
    state_room.visual.active = 1;
    func_80098338(&state_room.visual);
}
static void zs_flame_left(void)
{
    SABER(0x65);
    cur_random = 1;
    func_80098474(&state_room.misc);
}
static void zs_flame_right(void)
{
    SABER(0x65);
    pl.unk15 = 0x40;
    cur_random = 2;
    func_80098474(&state_room.misc);
}
static void zs_flame_burn(void)
{
    SABER(0x65);
    state_room.misc.state = 1;
    state_room.misc.animation_step.fields.relative_step = 1;
    func_80098474(&state_room.misc);
}
static void zs_flame_out(void)
{
    SABER(0x65);
    state_room.misc.state = 1;
    state_room.misc.active = 1;
    func_80098474(&state_room.misc);
}
static void zs_blade(u8 id, u8 kind, u8 event)
{
    SABER(0x58);
    pl.animation_step.fields.event = event;
    sw.id = id;
    sw.unk2 = kind;
    sw.unk84.word = pl.unk17;
    zero_saber_update(&sw);
    state_extra = need_palette_load;
}
static void zs_blade_first(void) { zs_blade(0x18, 0, 0); }
static void zs_blade_fall(void) { zs_blade(0x1C, 0, 3); }
static void zs_blade_spin(void) { zs_blade(0x20, 1, 0); }
static void zs_blade_spin_plain(void) { zs_blade(0x20, 0, 0); }
static void zs_blade_wave(void) { zs_blade(0x21, 0, 0); }
static void zs_blade_charged(void)
{
    SABER(0x58);
    pl.boss_flags = 0x40;
    sw.id = 0x1B;
    sw.unk84.word = pl.unk17;
    zero_saber_update(&sw);
}
static void zs_blade_follow(void)
{
    SABER(0x58);
    sw.state = 1;
    sw.unk84.word = pl.unk17;
    sw.animation_step.fields.relative_step = 1;
    zero_saber_update(&sw);
}
static void zs_blade_end(void)
{
    SABER(0x58);
    sw.state = 1;
    sw.active = 1;
    sw.unk84.word = pl.unk17;
    zero_saber_update(&sw);
}
static void zs_blade_switched(void)
{
    SABER(0x58);
    sw.active = 1;
    sw.unk84.word = 0x59;
    zero_saber_update(&sw);
}
static void zs_blade_dead(void)
{
    SABER(0x58);
    sw.active = 1;
    sw.unk84.word = pl.unk17;
    pl.hp = 0;
    zero_saber_update(&sw);
}

static void (*const zero_saber_states_cases[])(void) = {
    zs_aura_reset,
    zs_aura_locked,
    zs_aura_cancelled,
    zs_aura_other,
    zs_aura_start,
    zs_aura_follow,
    zs_aura_end,
    zs_flame_left,
    zs_flame_right,
    zs_flame_burn,
    zs_flame_out,
    zs_blade_first,
    zs_blade_fall,
    zs_blade_spin,
    zs_blade_spin_plain,
    zs_blade_wave,
    zs_blade_charged,
    zs_blade_follow,
    zs_blade_end,
    zs_blade_switched,
    zs_blade_dead,
};
static const u32 zero_saber_states_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0xFF000000u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x37801u, 0u, 0u, 1u, 0u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF0000u, 0u, 0u, 1u, 0xFF000000u, 0x440000u, 0xC80000u, 0u, 0u, 0u, 0x17804u, 0u, 0u, 1u, 0xFF400000u, 0x780000u, 0xBA0000u, 0u, 0u, 0u, 0x17804u, 0u, 0u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF0000u, 0u, 0u, 1u, 0xFF000000u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x17801u, 1u, 0u, 1u, 0xFF000000u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x17801u, 1u, 0u, 1u, 0xFF000100u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x27801u, 1u, 0u, 1u, 0xFF000000u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x27801u, 1u, 0u, 1u, 0xFF000021u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x27801u, 1u, 0u, 1u, 0xFF000000u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0x17801u, 0u, 0u, 1u, 0u, 0x640000u, 0xC80000u, 0u, 0u, 0u, 0xFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_zero_saber_states(u32 row)
{
    return object_run(zero_saber_states_cases[row], row, &zero_saber_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "zero_saber_states", 0, 0, COUNT(zero_saber_states_cases), test_zero_saber_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(zero_saber_states_cases);
