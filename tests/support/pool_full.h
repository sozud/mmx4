#ifndef MMX4_TESTS_POOL_FULL_H
#define MMX4_TESTS_POOL_FULL_H

static u32 pf_steps[1];
static u32* pf_table[0x20];
static u8 pf_variants[1], pf_title_end[2] = { 0xFF, 0 }, pf_title_skip[3] = { 0, 0xFF, 0 };
static struct MainObj pf_self, pf_expected;
static struct ItemObj pf_item, pf_item_expected;
static struct MiscObj pf_misc, pf_misc_expected;
static struct ShotObj pf_shot, pf_shot_expected;
static struct EffectObj pf_effect, pf_effect_expected;
static struct PlayerObj pf_player_saved, pf_player_expected;
static struct EngineObj pf_engine_saved, pf_engine_expected;
static struct BackgroundObj pf_backgrounds_saved[3], pf_backgrounds_expected[3];
static struct MainBssState pf_bss_saved;
static struct {
    void* base;
    u32 count, size;
    u32 heads[0x40];
} pf_pools[5];
static u16 pf_random_saved;
static s8 pf_bank_saved;

static void pf_same(const void* actual, const void* wanted, u32 size)
{
    u32 i, difference = 0;
    for (i = 0; i < size / 4; i++)
        difference |= ((const u32*)actual)[i] ^ ((const u32*)wanted)[i];
    assert(difference == 0);
}

static struct ObjectHeader* pf_slot(u32 pool, u32 index)
{
    return (struct ObjectHeader*)((u8*)pf_pools[pool].base + index * pf_pools[pool].size);
}

static void pf_fill(u32 pool, void* base, u32 count, u32 size)
{
    u32 i;
    pf_pools[pool].base = base;
    pf_pools[pool].count = count;
    pf_pools[pool].size = size;
    for (i = 0; i < count; i++) {
        pf_pools[pool].heads[i] = *(u32*)pf_slot(pool, i);
        pf_slot(pool, i)->active = 1;
    }
}

static void pf_check_pools(void)
{
    struct ObjectHeader full;
    u32 pool, i, difference = 0;
    for (pool = 0; pool < COUNT(pf_pools); pool++) {
        for (i = 0; i < pf_pools[pool].count; i++) {
            *(u32*)&full = pf_pools[pool].heads[i];
            full.active = 1;
            difference |= *(u32*)pf_slot(pool, i) ^ *(u32*)&full;
            *(u32*)pf_slot(pool, i) = pf_pools[pool].heads[i];
        }
    }
    assert(difference == 0);
}

static void pf_prepare(void)
{
    union AnimationStep step;
    u32 i;
    pf_player_saved = g_Player;
    pf_engine_saved = engine_obj;
    pf_bss_saved = main_bss_state;
    memcpy(pf_backgrounds_saved, background_objects, sizeof(pf_backgrounds_saved));
    pf_random_saved = cur_random;
    pf_bank_saved = D_8013E198[2];
    pf_fill(0, shot_objects, 0x20, sizeof(shot_objects[0]));
    pf_fill(1, visual_objects, 0x20, sizeof(visual_objects[0]));
    pf_fill(2, effect_objects, 0x20, sizeof(effect_objects[0]));
    pf_fill(3, item_objects, 0x20, sizeof(item_objects[0]));
    pf_fill(4, misc_objects, 0x40, sizeof(misc_objects[0]));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(pf_backgrounds_saved));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    g_Player.capsule_state = 1;
    g_Player.input.buttons.held = 1;
    cur_random = 1;
    D_8013E198[2] = -1;
    step.packed = 0;
    step.fields.duration = 5;
    step.fields.relative_step = 1;
    step.fields.frame_index = 4;
    pf_steps[0] = step.packed;
    for (i = 0; i < COUNT(pf_table); i++)
        pf_table[i] = &pf_steps[0];
    memset(&pf_self, 0, sizeof(pf_self));
    pf_self.active = 0x41;
    pf_self.id = 0x31;
    pf_self.unk2 = 9;
    pf_self.x_pos.val = 0x00805678;
    pf_self.y_pos.val = 0x00601234;
    pf_self.unk40 = 0x400;
    pf_self.unk42 = 0x1234;
    pf_self.unk7C = 5;
    pf_self.unk7E = 5;
    pf_self.animation_table = pf_table;
    pf_self.animation_cursor = &pf_steps[0];
    pf_self.animation_step.packed = pf_steps[0];
    memset(&pf_item, 0, sizeof(pf_item));
    pf_item.active = 0x41;
    pf_item.id = 0x10;
    pf_item.x_pos.val = 0x00405678;
    pf_item.y_pos.val = 0x00301234;
    memset(&pf_misc, 0, sizeof(pf_misc));
    pf_misc.active = 0x41;
    pf_misc.id = 0x1C;
    pf_misc.x_pos.val = 0x00505678;
    pf_misc.y_pos.val = 0x00401234;
    pf_misc.animation_table = pf_table;
    pf_misc.animation_cursor = &pf_steps[0];
    pf_misc.animation_step.packed = pf_steps[0];
    memset(&pf_shot, 0, sizeof(pf_shot));
    pf_shot.active = 0x41;
    pf_shot.id = 0x26;
    pf_shot.unk84.value = 3;
    memset(&pf_effect, 0, sizeof(pf_effect));
    pf_effect.active = 1;
    pf_effect.id = 0x24;
}

static void pf_snapshot(void)
{
    pf_expected = pf_self;
    pf_item_expected = pf_item;
    pf_misc_expected = pf_misc;
    pf_shot_expected = pf_shot;
    pf_effect_expected = pf_effect;
    pf_player_expected = g_Player;
    pf_engine_expected = engine_obj;
    memcpy(pf_backgrounds_expected, background_objects, sizeof(pf_backgrounds_expected));
}

static void pf_event(s8 value, s8 relative_step)
{
    pf_self.animation_step.fields.event = value;
    pf_self.animation_step.fields.relative_step = relative_step;
}

static void pf_animated(void)
{
    pf_expected.animation_step.fields.duration--;
}

static void pf_animation(u32 index)
{
    pf_expected.animation_cursor = pf_table[index];
    pf_expected.unk17 = index;
    pf_expected.previous_animation_index = 0xFF;
    pf_expected.animation_step.packed = *pf_table[index];
}

static void pf_script(u8 action, u8 facing)
{
    pf_player_expected.script_state = 1;
    pf_player_expected.script_action = action;
    pf_player_expected.script_facing = facing;
    pf_player_expected.spike_immune = 1;
    pf_engine_expected.gameplay_locked = 1;
}

static u32 pf_finish(u32 extra)
{
    u32 observed;
    pf_check_pools();
    pf_same(&pf_self, &pf_expected, sizeof(pf_self));
    pf_same(&pf_item, &pf_item_expected, sizeof(pf_item));
    pf_same(&pf_misc, &pf_misc_expected, sizeof(pf_misc));
    pf_same(&pf_shot, &pf_shot_expected, sizeof(pf_shot));
    pf_same(&pf_effect, &pf_effect_expected, sizeof(pf_effect));
    pf_same(&g_Player, &pf_player_expected, sizeof(g_Player));
    pf_same(&engine_obj, &pf_engine_expected, sizeof(engine_obj));
    pf_same(background_objects, pf_backgrounds_expected, sizeof(pf_backgrounds_expected));
    assert(cur_random == 1);
    observed = ((u8)pf_self.unk5 | ((u8)pf_self.unk6 << 8) | ((u32)(u16)pf_self.unk7C << 16)) ^ extra;
    g_Player = pf_player_saved;
    engine_obj = pf_engine_saved;
    main_bss_state = pf_bss_saved;
    memcpy(background_objects, pf_backgrounds_saved, sizeof(pf_backgrounds_saved));
    cur_random = pf_random_saved;
    D_8013E198[2] = pf_bank_saved;
    return observed;
}

#endif
