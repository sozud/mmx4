#include "common.h"
#include "main/55C4.h"
#include <stdint.h>

struct SaturnStageBootConfig {
    uint32_t magic;
    uint8_t stage, substage, character, enabled;
    uint8_t checkpoint, loadout, story, reserved;
};

const volatile struct SaturnStageBootConfig saturn_stage_boot_config = {
    0x53544742, SATURN_STAGE_BOOT_STAGE, SATURN_STAGE_BOOT_SUBSTAGE,
    SATURN_STAGE_BOOT_CHARACTER, 1, SATURN_STAGE_BOOT_CHECKPOINT,
    SATURN_STAGE_BOOT_LOADOUT, SATURN_STAGE_BOOT_STORY, 0
};
volatile uint32_t saturn_stage_boot_applied;
volatile uint32_t saturn_stage_boot_checkpoint_applied;

typedef char stage_offset_checked[__builtin_offsetof(struct EngineObj, stage) == 0xC ? 1 : -1];
typedef char substage_offset_checked[__builtin_offsetof(struct EngineObj, substage) == 0xD ? 1 : -1];
typedef char character_offset_checked[__builtin_offsetof(struct EngineObj, cur_character) == 0x43 ? 1 : -1];
typedef char config_size_checked[sizeof(struct SaturnStageBootConfig) == 12 ? 1 : -1];

void saturn_stage_boot_apply(struct EngineObj* engine)
{
    if (saturn_stage_boot_applied || engine->state != 4 || engine->stage != 0 || engine->substage != 0 || game_info.unk0 != 6 || game_info.mode != 2)
        return;
    uint8_t stage = saturn_stage_boot_config.stage;
    uint8_t substage = saturn_stage_boot_config.substage;
    uint8_t character = saturn_stage_boot_config.character;
    if (saturn_stage_boot_config.magic != 0x53544742 || !saturn_stage_boot_config.enabled || stage > 12 || substage > 1 || character > 1 || engine->cur_character != character)
        return;
    engine->stage = stage;
    engine->substage = substage;
    engine->unk5F = saturn_stage_boot_config.story;
    if (saturn_stage_boot_config.loadout == 1 || saturn_stage_boot_config.loadout == 2) {
        engine->player_lives = 4;
        engine->checkpoint_hp = 0x30;
        engine->max_hp = 0x30;
        engine->palette_flags = 0xFF;
        if (saturn_stage_boot_config.loadout == 2 && stage >= 1 && stage <= 8) {
            u8 mask = 1;
            while (--stage != 0)
                mask <<= 1;
            engine->palette_flags &= (u8)~mask;
        }
        engine->collected_upgrades = 0xF0FF;
        engine->sub_tanks[0] = 0xA0;
        engine->sub_tanks[1] = 0xA0;
        engine->sub_tanks[2] = 0x20;
        if (character == CHARACTER_X) {
            engine->armor_parts = 0x0F;
            engine->arm_type = 2;
        }
    }
    saturn_stage_boot_applied = 1;
    __asm__ volatile(".global _saturn_stage_boot_committed\n_saturn_stage_boot_committed:"
                     :
                     :
                     : "memory");
}

void saturn_stage_boot_checkpoint(struct EngineObj* engine)
{
    if (saturn_stage_boot_applied && !saturn_stage_boot_checkpoint_applied) {
        engine->checkpoint = saturn_stage_boot_config.checkpoint;
        saturn_stage_boot_checkpoint_applied = 1;
    }
}
