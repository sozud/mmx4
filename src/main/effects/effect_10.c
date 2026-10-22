// EffectObj, effect_object_update_funcs[10]
// 800B7EE8..800B8064
#include "common.h"
#include "main/55C4.h"
#include "weapon_resources.h"
#ifdef MMX4_SATURN
#include "saturn/game_low.h"
#endif

struct Effect10Trigger {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    u8 sound_id;
    u8 pad;
};

// sound_zone_update
#if defined(MMX4_PC) || defined(MMX4_SATURN)
extern struct Effect10Trigger* sound_zone_lists[2];
u8 player_in_bounds(s16* bounds);

#ifdef MMX4_SATURN
void func_800B7EE8(struct EffectObj* arg0)
{
    struct Effect10Trigger* triggers;
    u8 index;

    if (arg0->state == 0) {
        arg0->state++;
        arg0->ext.unk_effect.unk14 = 0;
        return;
    }

    triggers = sound_zone_lists[(s8)engine_obj.substage];
    for (index = 0; index < 4; index++) {
        struct Effect10Trigger* trigger = &triggers[index];
        u8 bit = 1 << index;
        u8 active = arg0->ext.unk_effect.unk14;

        if (player_in_bounds(&trigger->left)) {
            if (!(active & bit)) {
                if (engine_obj.substage == 0 || active == 0)
                    func_8001540C(SATURN_SOUND_ZONE_CHANNEL, trigger->sound_id, NULL);
                arg0->ext.unk_effect.unk14 = active | bit;
            }
        } else if (active & bit) {
            if (engine_obj.substage != 0) {
                if (active != 3 && active != 6)
                    func_8001540C(6, SATURN_SOUND_ZONE_SLOT, NULL);
            } else if (active == 1 || active == 8) {
                func_8001540C(6, SATURN_SOUND_ZONE_SLOT, NULL);
            }
            arg0->ext.unk_effect.unk14 = active & ~bit;
        }
    }
}
#else
void func_800B7EE8(struct EffectObj* arg0)
{
    struct Effect10Trigger* triggers;
    u8 index;

    if (arg0->state == 0) {
        arg0->state++;
        arg0->ext.unk_effect.unk14 = 0;
        return;
    }

    triggers = sound_zone_lists[(s8)engine_obj.substage];
    for (index = 0; index < 4; index++) {
        struct Effect10Trigger* trigger = &triggers[index];
        u8 bit = 1 << index;
        u8 active = arg0->ext.unk_effect.unk14;

        if (player_in_bounds(&trigger->left)) {
            if (!(active & bit)) {
                if (engine_obj.substage == 0 || active == 0)
                    func_8001540C(5, trigger->sound_id, NULL);
                arg0->ext.unk_effect.unk14 = active | bit;
            }
        } else if (active & bit) {
            if (engine_obj.substage == 0 || (active != 3 && active != 6))
                stop_sound(5, trigger->sound_id);
            arg0->ext.unk_effect.unk14 = active & ~bit;
        }
    }
}
#endif
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_10", func_800B7EE8);
#endif

struct Effect10Trigger sound_zone_list_0[4] = {
    { 0x0000, 0x0700, 0x0000, 0x0200, SATURN_SOUND(0, 0x10), 0 },
    { 0x0670, 0x1500, 0x0000, 0x0600, SATURN_SOUND(2, 0x12), 0 },
    { 0x14A0, 0x1900, 0x0280, 0x0600, SATURN_SOUND(1, 0x11), 0 },
    { 0x1500, 0x1900, 0x0000, 0x03C0, SATURN_SOUND(2, 0x12), 0 },
};

struct Effect10Trigger sound_zone_list_1[4] = {
    { 0x0520, 0x05F0, 0x0130, 0x0220, SATURN_SOUND(1, 0x11), 0 },
    { 0x0200, 0x05F0, 0x01E0, 0x0320, SATURN_SOUND(1, 0x11), 0 },
    { 0x0200, 0x03B0, 0x02E0, 0x03F0, SATURN_SOUND(1, 0x11), 0 },
    { 0x0700, 0x0930, 0x0280, 0x0600, SATURN_SOUND(1, 0x11), 0 },
};

struct Effect10Trigger* sound_zone_lists[2] = {
    sound_zone_list_0,
    sound_zone_list_1,
};

extern u16 sound_zone_data[65];

extern u16 sound_zone_padding;
