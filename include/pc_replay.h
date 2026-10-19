#ifndef MMX4_PC_REPLAY_H
#define MMX4_PC_REPLAY_H

struct SerializedEngineObj {
    s8 state, unk1, unk2, unk3;
    s16 unk4;
    s8 unk6, unk7;
    s16 unk8, unkA;
    s8 stage, substage, unkE, unkF;
    s8 unk10, unk11, unk12, unk13;
    s8 unk14, unk15, unk16, unk17;
    s8 unk18, unk19, unk1A, unk1B;
    s8 gameplay_locked, checkpoint, unk1E, unk1F;
    u32 boss_ptr;
    s8 enable_boss, unk25;
    union EngineCharacterState character_state;
    s8 unk36, unk37;
    u32 unk38, unk3C;
    u8 unk40;
    s8 unk41;
    u8 unk42;
    s8 cur_character, player_lives;
    u8 checkpoint_hp;
    s8 max_hp, armor_parts, arm_type;
    s8 player_initial_data[0x10];
    s8 palette_flags;
    u16 collected_upgrades;
    s8 sub_tanks[3];
    u8 unk5F, unk60;
    u8 pad61[3];
};

_Static_assert(sizeof(struct SerializedEngineObj) == 0x64,
    "replay engine state must use the PSX layout");

struct ReplayData {
    u32 frame;
    s32 flags;
    u16 random;
    u16 padA;
    struct SerializedEngineObj initial_engine;
    struct SerializedEngineObj saved_engine;
    u16 inputs[0xE10];
};

void save_replay_engine(struct SerializedEngineObj* target);

#endif
