#ifndef OBJ_H
#define OBJ_H

#define OBJECT_HEADER_FIELDS \
    s8 active;               \
    s8 id;                   \
    s8 unk2;                 \
    s8 on_screen;            \
    s8 state;                \
    s8 unk5;                 \
    s8 unk6;                 \
    s8 unk7;                 \
    f32 x_pos;               \
    f32 y_pos;               \
    void* backref;

#define BASE_OBJ_TAIL_FIELDS \
    s8 bg_offset;            \
    u8 unk15;                \
    u8 unk16;                \
    u8 unk17;

#define BASE_OBJ_FIELDS  \
    OBJECT_HEADER_FIELDS \
    BASE_OBJ_TAIL_FIELDS

#define MOVING_OBJ_FIELDS \
    BASE_OBJ_FIELDS       \
    f32 unk18;            \
    f32 unk1C;            \
    f32 x_vel;            \
    f32 y_vel;

#define ANIMATED_OBJ_FIELDS             \
    MOVING_OBJ_FIELDS                   \
    s32 unk28;                          \
    s32 unk2C;                          \
    u32** animation_table;              \
    u32* animation_cursor;              \
    void* unk38;                        \
    void* unk3C;                        \
    u16 unk40;                          \
    u16 unk42;                          \
    union AnimationStep animation_step; \
    u8 previous_animation_index;

struct ObjectHeader {
    OBJECT_HEADER_FIELDS
};

struct BaseObj {
    BASE_OBJ_FIELDS
};

struct MovingObj {
    MOVING_OBJ_FIELDS
};

struct AnimatedObj {
    ANIMATED_OBJ_FIELDS
};

struct GraphicsObj {
    ANIMATED_OBJ_FIELDS
    s8 unk49;
};

struct CollisionObj {
    ANIMATED_OBJ_FIELDS
    s8 pad49[0x50 - 0x49];
    const u8* unk50;
    const u8* unk54;
    const u8* unk58;
    s8 unk5C;
    s8 pad5D[0x68 - 0x5D];
    struct Unk_unk68* collision_bounds;
    s16 unk6C;
    s16 unk6E;
};

#ifdef MMX4_PC
MMX4_STATIC_ASSERT(pc_object_header_size, sizeof(struct ObjectHeader) == 0x18);
MMX4_STATIC_ASSERT(pc_base_object_size, sizeof(struct BaseObj) == 0x20);
#else
MMX4_STATIC_ASSERT(psx_object_header_size, sizeof(struct ObjectHeader) == 0x14);
MMX4_STATIC_ASSERT(psx_base_object_size, sizeof(struct BaseObj) == 0x18);
#endif

#define OBJECT_HEADER(object) ((struct ObjectHeader*)(object))
#define BASE_OBJECT(object) ((struct BaseObj*)(object))
#define MOVING_OBJECT(object) ((struct MovingObj*)(object))
#define ANIMATED_OBJECT(object) ((struct AnimatedObj*)(object))
#define GRAPHICS_OBJECT(object) ((struct GraphicsObj*)(object))
#define PLAYER_OBJECT(object) ((struct PlayerObj*)(object))
#define MAIN_OBJECT(object) ((struct MainObj*)(object))
#define UNK_OBJECT(object) ((struct UnkObj*)(object))
#define SHOT_OBJECT(object) ((struct ShotObj*)(object))
#define WEAPON_OBJECT(object) ((struct WeaponObj*)(object))
#define VISUAL_OBJECT(object) ((struct VisualObj*)(object))
#define EFFECT_OBJECT(object) ((struct EffectObj*)(object))
#define MISC_OBJECT(object) ((struct MiscObj*)(object))
#define COLLISION_OBJECT(object) ((struct CollisionObj*)(object))

struct Main0Ext {
    u8 background_relative;
    u8 index;
    u8 flags[3];
    u8 exit_mode;
    u8 damage_flash_timer;
};

struct Main3Ext {
    u32 alerted;
    s32 roll_timer;
    u32 player_ahead;
    u32 turn_timer;
    u32 saved_step;
};

struct Main5Ext {
    u8 unk80;
    u8 unk81;
    u8 pad82[5];
    u8 lifetime;
    u8 spawn_timer;
    u8 pad89[2];
    u8 unk8B;
    u16 saved_unk5;
    u16 part_index;
    u16 target_x;
    u16 target_y;
    struct MainObj* owner;
};

struct Main6Ext {
    u32 armor_broken;
    u32 ground_probe_distance;
    u32 armor_health;
    u32 core_health;
    u32 hitbox_toggle;
    u32 saved_step;
};

struct MainSavedState80Ext {
    u32 saved_unk5;
};

struct Main58Ext {
    u32 saved_unk5, unk84, unk88, unk8C, unk90, unk94;
};
struct Main10Ext {
    u32 timer;
    s32 turn_delay;
    s32 struggle;
    u32 hold_state;
    u32 can_grab;
    u32 saved_unk5;
};

struct MainSavedState8CExt {
    u8 pad80[0xC];
    u32 saved_unk5;
};

struct Main14Ext {
    u32 unk80;
    u32 unk84;
    s32 visual_variant;
    u32 unk8C;
    u32 saved_unk5;
    u32 unk94;
};

struct Main16Ext {
    u32 unk80;
    s32 unk84;
    s32 unk88;
    u32 unk8C;
    u32 unk90;
    u32 shot_09_active;
    u32 unk98;
};

struct Main17Ext {
    u32 unk80;
    u32 unk84;
    u32 unk88;
    u32 unk8C;
    u32 unk90;
    u32 saved_unk5;
};

union Main37Unk80 {
    u32 word;
    u8 saved_direction;
};

struct Main37Ext {
    union Main37Unk80 unk80;
    f32 unk84;
    f32 unk88;
    f32 unk8C;
    u8 pad90[4];
    u32 saved_unk5;
};

struct Main31Ext {
    u8 pad80[3];
    u8 unk83;
    u8 unk84;
};

struct Main32Ext {
    u32 unk80;
    u32 unk84;
    s32 unk88;
    u32 unk8C;
    u32 unk90;
    u32 saved_unk5;
};

struct Main33Ext {
    u8 unk80;
    u8 variant;
    s16 target_x;
    u8 unk84;
    u8 intro_active;
    u8 intro_laps;
    u8 unk87;
    s16 unk88;
    u8 pad8A[4];
    u16 unk8E;
    u8 flash_timer;
    u8 unk91;
    u8 pad92[2];
    u32 saved_unk5;
};

struct Main34Ext {
    s8 unk80;
    u8 pad81;
    u8 unk82;
};

struct Main38Ext {
    u32 saved_unk5;
    s32 unk84;
    u32 unk88;
    u32 unk8C;
    u32 unk90;
    u32 unk94;
};

struct Main39Ext {
    union {
        struct {
            u16 unk80;
            s16 unk82;
        } h;
        u32 w;
    } unk80;
    union {
        struct {
            s16 unk84;
            u16 unk86;
        } h;
        u32 w;
    } unk84;
    u8 unk88;
    u8 pad89[3];
    s32 unk8C;
    s32 unk90;
    u8 unk94;
};

struct Main40Ext {
    u8 unk80;
    u8 unk81;
    u16 timer;
    u16 trigger_time;
};

struct MainSavedState94Ext {
    u32 unk80;
    u32 unk84;
    u32 unk88;
    u32 unk8C;
    u32 unk90;
    u32 saved_unk5;
};

struct Main51Ext {
    u32 unk80;
    u32 unk84;
    u8 pad88[8];
    u32 unk90;
    u32 saved_unk5;
};

struct Main7Ext {
    u32 unk80;
    u32 unk84;
    s32 saved_x_velocity;
    s32 saved_y_velocity;
    u32 unk90;
    u32 saved_unk5;
};

struct Main52Ext {
    u8 unk80;
    u8 pad81[3];
    u8 unk84;
    u8 pad85[3];
    u8 unk88;
    u8 pad89[3];
    u8 unk8C;
    u8 pad8D[7];
    u32 saved_unk5;
};

struct Main13Ext {
    u32 unk80;
    u32 unk84;
    u32 unk88;
    u32 saved_unk5;
};

struct Main11Ext {
    u8 unk80;
    u8 pad81[3];
    u8 angle;
    u8 unk85;
    s8 unk86;
    u8 saved_unk5;
};

struct Main12Ext {
    u8 unk80;
    u8 unk81;
    u8 saved_unk5;
    u8 pad83[3];
    u16 unk86;
    u16 unk88;
    u16 unk8A;
    u16 unk8C;
};

struct Main22Ext {
    u32 saved_unk5;
    u32 unk84;
    u32 destroyed;
    u32 unk8C;
    u32 unk90;
    u32 parts_mask;
};

struct Main26Ext {
    s8 last_health;
    s8 stage;
};

struct Main23Ext {
    u8 unk80;
    u8 unk81;
    u8 unk82;
};

struct Main24Ext {
    u32 unk80;
    u8 pad84[0x10];
    u32 saved_unk5;
};

struct Main47Ext {
    struct Main45Ext* train_boss;
    s8* boss_hp;
    u32 unk88;
    u32 unk8C;
    u32 unk90;
    u32 unk94;
};

struct Main76Ext {
    s32 saved_x_velocity;
    u8 pad84[0x98 - 0x84];
    s8 bounce_step;
};

struct Main25Ext {
    u32 unk80;
    u32 unk84;
    u32 unk88;
    u8 pad8C[8];
    u32 saved_unk5;
};

struct Main35Ext {
    u32 unk80;
    u32 sound_timer;
    u8 pad88[0xC];
    u32 saved_unk5;
};

struct Main45LayerSignals {
    u8 unk16;
    u8 collision_state;
    u8 projectile_state[3];
};

struct Main45Ext {
    u8 attack_flags;
    s8 unk81;
    u8 unk82;
    u8 unk83;
    s16 unk84;
    u8 unk86;
    u8 unk87;
    u8 projectile_command;
    u8 unk89;
    s16 unk8A;
    u8* layer_bg_offset;
    u8* layer_parameter;
    struct Main45LayerSignals* layer_signals;
};

struct Main48Ext {
    s8 unk80;
    u8 unk81;
    s8 unk82;
    s8 unk83;
    u8 saved_unk5;
    u8 collision_result;
    u8 unk86;
    u8 unk87;
    u8 unk88;
};

union Main73EffectData {
    struct {
        u8 state;
        u8 object_id;
        u8 unk8E;
        u8 pad8F;
    } bytes;
    struct {
        u16 x;
        u16 y;
    } position;
};

struct Main73Ext {
    union {
        struct EffectObj* effect;
        s8* script;
    } unk80;
    u8* cycle_script;
    u8 cycle_step;
    u8 shot_count;
    u8 unk8A;
    u8 blink_delay;
    union Main73EffectData effect;
};

struct Main73PartsExt {
    struct MainObj* parts[3];
    u8 effect_state;
    u8 object_id;
    u8 unk8E;
};

struct Main18RuntimeFields {
    u8 unk80;
    u8 unk81;
    u8 unk82;
    u8 unk83;
    u8 unk84;
    s8 unk85;
    u8 unk86;
    u8 unk87;
};

union Main18StateData {
    struct Main18RuntimeFields runtime;
    struct FixedPointPosition saved_position;
};

struct Main18Ext {
    union Main18StateData state;
    u8 unk88;
    u8 shed_timer;
    u16 ice_pieces;
    u32 unk8C;
    u32 unk90;
    u8 pad94[3];
    u8 saved_unk5;
};

struct Main19Ext {
    u8 unk80;
    u8 animation_index;
    u8 unk82;
    u8 unk83;
    u16 unk84;
    u16 unk86;
    u16 unk88;
    u16 unk8A;
    u8 unk8C;
};

struct Main21Ext {
    s16 timer_80;
    s16 timer_82;
    u8 saved_unk5;
};

struct Main49Ext {
    u8 unk80;
    u8 index;
    u8 unk82;
    u8 unk83;
    u8 pad84;
    u8 unk85;
    u8 unk86;
};

struct Main50Ext {
    u8 pad80[2];
    u16 timer;
    u8 unk84;
};

struct Main54Ext {
    u8 flash_timer;
    u8 powered_up;
    u8 was_hit;
    u8 pad83;
    u8 grab;
    u8 active;
    u8 claw_hitbox;
    u8 afterimage_timer;
    u8 crash_timer;
    u8 pattern_set;
    u8 power_hits;
    u8 pad8B;
    struct EffectObj* effect;
    u8* pattern;
    u8 unk94;
    u8 fight_started;
    u8 high_jump;
};

struct Main55Ext {
    u32 distance;
    u8 unk84;
    u8 unk85;
    u8 unk86;
    u8 unk87;
    u8 unk88;
};

struct Main36Ext {
    u8 unk80[4];
    struct MiscObj* unk84;
    u8 saved_unk5;
    u8 unk89;
    u16 unk8A;
    u8 unk8C;
    u8 unk8D;
};

struct Main43Ext {
    struct ShotObj* shot;
    struct EffectObj* effect;
    u16 big_web_done;
    u16 flash_timer;
    u16 animation_index;
    u16 animation_length;
    u16 attack_cooldown;
    u8 attack_count;
    u8 move_direction;
    u8 unk94;
    s8 hurt_collision;
    s8 animation_id;
    s8 animation_set;
};

struct Main46Ext {
    struct Main45Ext* owner;
    u8 pad84[0x95 - 0x84];
    u8 unk95;
};

union Main56Unk89 {
    u8 value;
    s8 signed_value;
};

union Main56Unk80 {
    struct EffectObj* effect;
    struct VisualObj* visual;
};

struct Main56Ext {
    union Main56Unk80 object;
    u8* pattern;
    u8 vortex_result;
    union Main56Unk89 unk89;
    u8 flash_timer;
    u8 flags;
};

struct Main57Ext {
    struct EffectObj* effect;
    struct ShotObj* shot;
    u8* script;
    RECT* rect;
    u8 leap_grounded;
    u8 shard_count;
    u8 tusks_broken;
    u8 flashing;
    u8 flash_timer;
    u8 staggered;
};

struct Main487Ext {
#ifdef MMX4_PC
    u8 pad80[0x12];
#else
    u8 pad80[0xA];
#endif
    u8 unk8A;
};

struct Main53Ext {
    u8 unk80;
    u8 unk81;
    u8 unk82;
    u8 unk83;
    u8 unk84;
    u8 unk85;
};

struct Main62Ext {
    struct VisualObj* unk80;
    u8 pad84[2];
    u8 unk86;
};

struct Main71Ext {
    u8 pad80[4];
    s16 unk84;
    u8 unk86;
    u8 unk87;
    u8 unk88;
    u8 unk89;
    u8 unk8A;
    u8 unk8B;
    u8 unk8C;
    u8 unk8D;
    s8 unk8E;
};

struct Main72Ext {
    u8 pad80[4];
    s16 unk84;
    u8 unk86;
    u8 lifetime;
    u8 spawn_timer;
};

struct Main60Ext {
    struct EffectObj* effect;
    u8* pattern;
    u16 feather_mask;
    u8 saved_unk5;
    u8 corner;
    u8 pad8C;
    u8 shot_count;
    u8 feathers_holding;
    u8 storm_active;
    u8 storm_timer;
    u8 unk91;
    u8 patrol_delay;
    u8 flash_timer;
    u8 flash_mode;
};

union Main61Data {
    s8* script;
    struct EffectObj* effect;
};

struct Main61Ext {
    union Main61Data data;
    u8 flash_timer;
    u8 split;
    u8 blink_timer;
    u8 combo_count;
    u8 stunned;
    u8 split_hits;
    u8 merge;
    u8 active;
    u8 speed_level;
    u8 hit_lock;
    u8 split_done;
    u8 pad8F[0x94 - 0x8F];
    struct MainObj* partner;
};

struct Main65Ext {
    struct MainObj* object;
    struct MainObj* smoke;
    s16 jump_start_y;
    u8 flash_timer;
    u8 leap_frames;
    u8 leap_to_right;
    u8 attack;
    u8 attack_repeat;
};

struct Main64Ext {
    void* object;
    u16 target_x;
    u16 target_y;
    u8 skip_attack;
    u8 next_step;
    u8 unk8A;
    u8 shot_count;
    s16 arena_x;
    s16 arena_y;
    u8 hit_count;
    u8 force_laser;
    u8 flash_timer;
    u8 saved_health;
};

struct Main74Ext {
    struct MainObj* children[3];
    u8 unk8C;
    u8 effect_state;
    u8 unk8E;
    u8 timer;
    u8 animation_index;
    u8 target;
    u8 upper_health;
    u8 lower_health;
    u8 death_kind;
    u8 pad95;
    u8 pattern_index;
    u8 unk97;
};

struct ShotObj;

struct Main75Ext {
    union {
        struct EffectObj* effect;
        struct ShotObj* shot;
        struct MainObj* child;
    } object;
    const u8* script;
    struct ShotObj* thruster;
    s16 background_unk1E;
    u8 saved_unk5;
    u8 hit_timer;
    u8 hit_active;
    u8 random_index;
    u8 orbs_ready;
    u8 bob_timer;
    s8 bob_step;
    u8 blink_delay;
};

struct Main8Ext {
    const void* unk80;
    const void* unk84;
    u8 unk88;
    u8 queued_sound;
    u8 unk8A;
    u8 unk8B;
    u8 unk8C;
};

struct Main9Ext {
    const u8* animation_1;
    const u8* animation_2;
    u8 animation_timer;
    u8 pad89[4];
    u8 object_id;
    u8 pad8E[2];
    struct EffectObj* effect;
};

struct Main27Ext {
    u8 unk80;
    u8 collision_direction;
    u8 unk82;
    u8 pad83;
    s32 unk84;
    u8 unk88;
    u8 unk89;
    u8 unk8A;
    u8 unk8B;
    s32 unk8C;
    u8 unk90;
    u8 unk91;
    u8 unk92;
    u8 pad93;
    u32 saved_unk5;
};

struct Main28Ext {
    struct MainObj* context;
    u8 unk84;
    u8 unk85;
    u16 unk86;
    u16 unk88;
    u16 index;
};

struct MemcardSaveSlot {
    u8 character;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u16 unk6;
    u16 unk8[16];
    u8 unk28;
    u8 unk29;
};
typedef char MemcardSaveSlot_must_be_0x2A_bytes[sizeof(struct MemcardSaveSlot) == 0x2A ? 1 : -1];

struct Main29Record {
    s8 unk0;
    s8 unk1;
    u8 pad2[2];
    s8 unk4;
};

struct Main29ControllerExt {
    u8 unk80;
    u8 unk81;
};

struct Main29Ext {
    struct MainObj* source;
    union {
        struct MainObj* children[4];
        struct {
            struct MainObj* children[2];
            struct Main29Record* target;
            struct Main29Record* record;
        } controller;
    } slots;
    u16 unk94;
    u16 unk96;
};

struct Main41Ext {
    u8 unk80;
    u8 unk81;
    u8 unk82;
    u8 unk83;
    u8 unk84;
};

struct Main42Ext {
    u8 background_relative;
    u8 pad81[3];
    struct MiscObj* unk84;
};

struct Main68Ext {
    struct MainObj* scythe;
    struct VisualObj* visual;
    struct EffectObj* effect;
    u8 count;
    u8 shot_type;
    u8 active_shots;
    u8 next_attack;
    u8 blink_delay;
    u8 flash_timer;
    s8 bob_step;
};

union Main69State {
    u32 word;
    struct {
        u8 variant;
        u8 unk8D;
        u8 unk8E;
        s8 wave_delay;
    } bytes;
};

struct Main69Ext {
    struct EffectObj* effect;
    struct VisualObj* linked_object;
    u8* script;
    union Main69State state;
    u32 unk90;
    u32 unk94;
};

struct Main67Ext {
    s32 vertical_speed;
    s32 delay;
    u8 direction;
    u8 unk89;
    u8 unk8A;
    u8 pad8B[2];
    u8 unk8D;
    u8 pad8E[6];
    u32 saved_unk5;
};

struct Main66Ext {
    struct EffectObj* effect;
    u8 drone_count;
    u8 hover_timer;
    u8 crystal_released;
    u8 release_countdown;
    u8 flash_timer;
    u8 trail_write;
    u8 trail_read;
    u8 trail_target;
    u8 active;
    u8 blink_timer;
    u8 pad8E[6];
    struct MainObj* partner;
};

struct Main70Ext {
    s16 alarm_timer;
    s16 flash_timer;
    u8 unk84;
    u8 unk85;
    u8 alarm_color;
    u8 alarm_flashing;
    u8 pad88[0xC];
    u32 saved_unk5;
};

struct Main20Ext {
    s8 unk80;
    s8 unk81;
};

union MainObjExt {
    u32 raw[7];
    struct Main0Ext main_0;
    struct Main3Ext main_3;
    struct Main5Ext main_5;
    struct Main8Ext main_8;
    struct Main9Ext main_9;
    struct Main6Ext main_6;
    struct Main7Ext main_7;
    struct Main10Ext main_10;
    struct Main11Ext main_11;
    struct Main12Ext main_12;
    struct Main13Ext main_13;
    struct Main14Ext main_14;
    struct Main16Ext main_16;
    struct Main17Ext main_17;
    struct Main18Ext main_18;
    struct Main19Ext main_19;
    struct Main20Ext main_20;
    struct Main21Ext main_21;
    struct Main22Ext main_22;
    struct Main23Ext main_23;
    struct Main26Ext main_26;
    struct Main24Ext main_24;
    struct Main25Ext main_25;
    struct Main47Ext main_47;
    struct Main27Ext main_27;
    struct Main28Ext main_28;
    struct Main29Ext main_29;
    struct Main29ControllerExt main_29_controller;
    struct Main31Ext main_31;
    struct Main32Ext main_32;
    struct Main33Ext main_33;
    struct Main34Ext main_34;
    struct Main35Ext main_35;
    struct Main36Ext main_36;
    struct Main41Ext main_41;
    struct Main42Ext main_42;
    struct Main43Ext main_43;
    struct Main487Ext main_487;
    struct Main37Ext main_37;
    struct Main38Ext main_38;
    struct Main39Ext main_39;
    struct Main40Ext main_40;
    struct MainSavedState94Ext main_44;
    struct Main45Ext main_45;
    struct Main48Ext main_48;
    struct Main46Ext main_46;
    struct Main49Ext main_49;
    struct Main50Ext main_50;
    struct Main51Ext main_51;
    struct Main52Ext main_52;
    struct Main54Ext main_54;
    struct Main55Ext main_55;
    struct Main56Ext main_56;
    struct Main57Ext main_57;
    struct Main58Ext main_58;
    struct Main60Ext main_60;
    struct Main61Ext main_61;
    struct Main64Ext main_64;
    struct Main65Ext main_65;
    struct Main66Ext main_66;
    struct Main67Ext main_67;
    struct Main68Ext main_68;
    struct Main69Ext main_69;
    struct Main70Ext main_70;
    struct Main53Ext main_53;
    struct Main62Ext main_62;
    struct Main71Ext main_71;
    struct Main72Ext main_72;
    struct Main73Ext main_73;
    struct Main73PartsExt main_73_parts;
    struct Main74Ext main_74;
    struct Main75Ext main_75;
    struct Main76Ext main_76;
};

#ifndef MMX4_PC
MMX4_STATIC_ASSERT(main_obj_ext_size, sizeof(union MainObjExt) == 0x1C);
#endif

#define MAIN_OBJ_TAIL_FIELDS            \
    s32 x_speed;                        \
    s32 y_speed;                        \
    s32 x_accel;                        \
    s32 gravity;                        \
    const u8* const* animation_table;   \
    const u8* animation_cursor;         \
    s16 animation_speed;                \
    u8 pad3A[2];                        \
    const u8* sprite_frames;            \
    u16 unk40;                          \
    u16 unk42;                          \
    union AnimationStep animation_step; \
    u8 previous_animation_index;        \
    s8 pad49[2];                        \
    s8 unk4B;                           \
    s8 pad4C[4];                        \
    const void* attack_box;             \
    const void* hurt_box;               \
    const void* collision_data;         \
    s8 hp;                              \
    s8 unk5D;                           \
    s8 unk5E;                           \
    s8 drain_hold_timer;                \
    s8 contact_damage;                  \
    s8 invincibility_timer;             \
    s8 unk62;                           \
    s8 unk63;                           \
    s8 unk64;                           \
    s8 unk65;                           \
    s8 unk66;                           \
    s8 air_state;                       \
    struct Unk_unk68* terrain_box;      \
    s16 unk6C;                          \
    s16 unk6E;                          \
    u8 collision_flags;                 \
    s8:                                 \
    8;                                  \
    s8 unk72;                           \
    s8 unk73;                           \
    s8 unk74;                           \
    s8 unk75;                           \
    s8 unk76;                           \
    s8 unk77;                           \
    s8 unk78;                           \
    s8 unk79;                           \
    s8 unk7A;                           \
    u8 unk7B;                           \
    s16 unk7C;                          \
    s16 unk7E;                          \
    union MainObjExt ext;

struct MainObj {
    BASE_OBJ_FIELDS
    f32 unk18;
    f32 unk1C;
    MAIN_OBJ_TAIL_FIELDS
};

union BackgroundUnk3E {
    u16 half;
    s8 bytes[2];
};

struct BackgroundObj {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    s8 unk3;
    s8 unk4;
    u8 pad4[3];
    f32 x_pos;
    f32 y_pos;
    u8 pad10[4];
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    u16 unk34;
    s8 unk36;
    s8 unk37;
    u8 pad38[2];
    s8 unk3A;
    s8 unk3B;
    s8 unk3C;
    s8 unk3D;
    union BackgroundUnk3E unk3E;
    u16 unk40;
    u16 unk42;
    s8 unk44;
    s8 unk45;
    s8 unk46;
    s8 unk47;
    s8 unk48;
    s8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    s8 min_y;
    s8 max_y;
    s8 unk51;
    s8 pad52[2];
}; // size 0x54

union PlayerUnk88 {
    u16 value;
    struct {
        s8 timer;
        u8 collision_flags;
    } bytes;
    struct {
        u8 timer;
        u8 collision_flags;
    } unsigned_bytes;
};

// similar to Unk
struct PlayerObj {
    ANIMATED_OBJ_FIELDS
    s8 unk49;
    s8 wall_climbable;
    s8 pad4B[0x50 - 0x4B];
    void* unk50;
    struct Unk_unk68* unk54;
    void* unk58;
    s8 hp;
    s8 hud_hp;
    s8 spawn_hp;
    s8 drain_hold_timer;
    s8 unk60;
    s8 invincibility_timer;
    s8 unk62;
    s8 hurt_type;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 air_state;
    struct Unk_unk68* unk68;
    s16 unk6C;
    s16 unk6E;
    u8 unk70;
    s8 unk71;
    u8 unk72;
    u8 unk73;
    u8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 touching_spikes;
    s8 spike_immune;
    union {
        u32 history;
        struct {
            u16 held;
            u16 previous;
        } buttons;
        struct {
            u8 held_low;
            u8 held_high;
            u8 previous_low;
            u8 previous_high;
        } bytes;
    } input;
    u16 pressed_input;
    u16 double_tap_direction;
    s8 dash_momentum;
    s8 dash_timer;
    s8 air_action;
    s8 double_tap_dash;
    union PlayerUnk88 unk88;
    union PlayerUnk8A unk8A;
    s8 afterimage;
    u8 unk8D;
    s8 attacking;
    s8 shot_fired;
    s8 attack_ended;
    u8 attack_pose_timer;
    u8 shot_cooldown;
    s8 weapon;
    s8 shot_types[2];
    s8 shot_type;
    s8 last_shot_type;
    s8 shot_count;
    s8 special_shot_count;
    s8 shot_cycle;
    PlayerChargeState charge_state[2];
    u8 charge_timer;
    u8 special_charge_timer;
    s8 flash_delay;
    s8 flash_phase;
    s8 flash_palette;
    s8 shot_palette_timer;
    s8 : 8;
    s8 hurt_phase;
    s8 hit_facing;
    s8 stock_charge;
    s8 armor_parts;
    s8 weapon_energy[0x10];
    u8 arm_type;
    s8 boss_flags;
    s8 stun_timer;
    s8 combo;
    s8 update_delay;
    s8 update_delay_request;
    s8 beam_in_delay;
    s8 actions_reset;
    s8 script_state;
    s8 script_action;
    s8 script_facing;
    s8 input_locked;
    s8 capsule_state;
    s8 ride_state;
    s8 unkC6;
    s8 death_timer;
    struct MainObj* weapon_06_slots[3];
    s8 ride_animation;
    u8 hover_timer;
    u8 hover_bob;
    s8 voice_timer;
    s8 : 8;
    s8 is_clone;
    u16 clone_timer;
    union PlayerUnkDC clone_offset;
    s8 controlling_clone;
    s8 unkDF;
    s8 nova_strike_active;
    s8 nova_strike_timer;
    u8 item_step;
    s8 : 8;
}; // size 0xE4

MMX4_STATIC_ASSERT(player_unk68_offset,
    MMX4_OFFSET_OF(struct PlayerObj, unk68) == MMX4_OFFSET_OF(struct MainObj, terrain_box));
MMX4_STATIC_ASSERT(player_unk6C_offset,
    MMX4_OFFSET_OF(struct PlayerObj, unk6C) == MMX4_OFFSET_OF(struct MainObj, unk6C));
MMX4_STATIC_ASSERT(player_unk6E_offset,
    MMX4_OFFSET_OF(struct PlayerObj, unk6E) == MMX4_OFFSET_OF(struct MainObj, unk6E));
MMX4_STATIC_ASSERT(player_unk70_offset,
    MMX4_OFFSET_OF(struct PlayerObj, unk70) == MMX4_OFFSET_OF(struct MainObj, collision_flags));
MMX4_STATIC_ASSERT(player_held_input_offset,
    MMX4_OFFSET_OF(struct PlayerObj, input.buttons.held) == MMX4_OFFSET_OF(struct PlayerObj, input));
MMX4_STATIC_ASSERT(player_previous_input_offset,
    MMX4_OFFSET_OF(struct PlayerObj, input.buttons.previous) == MMX4_OFFSET_OF(struct PlayerObj, input) + sizeof(u16));
MMX4_STATIC_ASSERT(player_pressed_input_offset,
    MMX4_OFFSET_OF(struct PlayerObj, pressed_input) == MMX4_OFFSET_OF(struct PlayerObj, input) + sizeof(((struct PlayerObj*)0)->input));
#ifndef MMX4_PC
MMX4_STATIC_ASSERT(psx_player_input_offset,
    MMX4_OFFSET_OF(struct PlayerObj, input) == 0x7C);
#endif

struct Unk_unk68 {
    s8 unk0;
    s8 unk1;
    u8 unk2;
    u8 unk3;
};

union VisualUnk5C {
    s8 value;
    struct PlayerObj* owner;
    struct {
        s8 pad5C;
        s8 mode;
        s16 unk5E;
    } fields;
};

struct VisualObj {
    ANIMATED_OBJ_FIELDS
    u8 unk49;
    s8 pad4A[0x50 - 0x4A];
    struct PlayerObj* unk50; // 0x50, guessed
    s16 unk54;
    s16 unk56;
    s16 unk58;
    s16 unk5A;
    union VisualUnk5C unk5C;
    u8 pa58[0x70 - 0x60];
}; // size 0x70

struct Shot29Ext {
    u8 timer;
    u8 unk8D;
};

union ShotUnk8C {
    s32 word;
    struct ShotObj* shot;
    u16 half;
    s16 halves[2];
    s8 byte;
    u8 bytes[4];
    struct Shot29Ext shot_29;
    struct ObjectHeader* object;
};

union ShotUnk58 {
    const u8* data;
    const u16* collision_data;
    const union AnimationStep* animation_steps;
    struct Unk_unk68* collision_bounds;
};

struct Shot24Ext {
    u8 owner_state;
    u8 owner_notified;
    s16 timer;
};

struct Shot24Owner {
    OBJECT_HEADER_FIELDS
    u8* collision_states;
};

#ifndef MMX4_PC
MMX4_STATIC_ASSERT(shot_24_owner_collision_states_offset,
    MMX4_OFFSET_OF(struct Shot24Owner, collision_states) == 0x14);
#endif

struct Shot55Unk84 {
    s16 x;
    s16 y;
};

struct ShotObj {
    ANIMATED_OBJ_FIELDS
    s8 pad49[0x50 - 0x49];
    union {
        const u8* data;
        s16* frames;
        struct PlayerObj* player;
    } unk50;
    const u8* unk54;
    union ShotUnk58 unk58;
    s8 unk5C;
    s8 pad5D[0x60 - 0x5D];
    s8 unk60;
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    struct Unk_unk68* unk68;
    s8 pad6C[0x70 - 0x6C];
    u8 unk70;
    s8 pad71;
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 : 8;
    s8 unk7A;
    s8 : 8;
    struct WeaponObj* unk7C;
    s32 : 32;
    union {
        s32 value;
        u32* collision_state;
        struct EffectObj* effect;
        u16 halves[2];
        u8 bytes[4];
        struct Shot24Ext shot_24;
        struct Shot55Unk84 shot_55;
    } unk84;
    s16 timer;
    s16 unk8A;
    union ShotUnk8C unk8C;
    f32_halves unk90;
    s8 unk94;
    u8 unk95;
    s8 unk96;
    s8 pad97;
    s8 unk98;
    s8 unk99;
    s8 unk9A;
    s8 pad9B;
}; // size 0x9C

MMX4_STATIC_ASSERT(shot_unk54_offset,
    MMX4_OFFSET_OF(struct ShotObj, unk54) == MMX4_OFFSET_OF(struct MainObj, hurt_box));
MMX4_STATIC_ASSERT(shot_unk58_offset,
    MMX4_OFFSET_OF(struct ShotObj, unk58) == MMX4_OFFSET_OF(struct MainObj, collision_data));
MMX4_STATIC_ASSERT(shot_unk68_offset,
    MMX4_OFFSET_OF(struct ShotObj, unk68) == MMX4_OFFSET_OF(struct MainObj, terrain_box));

struct Weapon1Ext {
    u8 lifetime;
    u8 timer;
    u8 pad8E[0x90 - 0x8E];
    u8 unk90;
};

struct Weapon2Ext {
    u8 lifetime;
    u8 timer;
};

struct Weapon7Ext {
    u16 timer;
    u8 pad8E[2];
    u8 unk90;
    u8 unk91;
};

struct Weapon3Ext {
    u16 offset;
    u16 lifetime;
    s8 unk90;
    s8 unk91;
};

struct Weapon6Ext {
    u8 direction;
    u8 adjusted_direction;
    u8 lifetime;
    u8 timer;
};

struct Weapon8Ext {
    u8 timer;
};

struct Weapon17Ext {
    u8 pad8C;
    u8 timer;
};

struct Weapon10Ext {
    u8 timer;
    u8 pad8D[0x8F - 0x8D];
    u8 unk8F;
    u8 unk90;
};

struct Weapon14Ext {
    u8 unk8C;
    s8 unk8D;
};

struct Weapon13Ext {
    u8 timer;
};

struct Weapon16Ext {
    u16 timer;
    u16 delay;
    u8 pad90;
    u8 unk91;
};

struct Weapon20Ext {
    u8 lifetime;
    u8 timer;
    s8 unk8E;
};

union WeaponUnk84 {
    s32 word;
    u8 byte;
    u8 bytes[4];
    u16 halves[2];
};

struct Weapon15Ext {
    u8 unk8C;
    u8 unk8D;
    u8 unk8E;
    u8 unk8F;
};

union WeaponUnk88 {
    u16 half;
    u8 bytes[2];
};

union WeaponUnk80 {
    s32 word;
    u8 bytes[4];
};

struct Weapon29Ext {
    u8 pad8C[4];
    s32 unk90;
};

struct Shot46Ext {
    u8 unk8C;
    u8 pad8D;
    u8 unk8E;
    u8 unk8F;
};

struct Shot55Ext {
    u8 pad8C[0x90 - 0x8C];
    u8 unk90;
    u8 pad91;
    u8 unk92;
};

struct Weapon60Ext {
    struct MainObj* target;
    u8 direction;
};

union WeaponObjExt {
    u8 raw[0x94 - 0x8C];
    RECT* rect;
    struct MainObj* target;
    struct Weapon1Ext weapon_1;
    struct Weapon2Ext weapon_2;
    struct Weapon6Ext weapon_6;
    struct Weapon3Ext weapon_3;
    struct Weapon7Ext weapon_7;
    struct Weapon8Ext weapon_8;
    struct Weapon10Ext weapon_10;
    struct Weapon14Ext weapon_14;
    struct Weapon13Ext weapon_13;
    struct Weapon15Ext weapon_15;
    struct Weapon16Ext weapon_16;
    struct Weapon60Ext weapon_60;
    struct Weapon17Ext weapon_17;
    struct Weapon20Ext weapon_20;
    struct Weapon29Ext weapon_29;
    struct Shot46Ext shot_46;
    struct Shot55Ext shot_55;
};

#ifndef MMX4_PC
MMX4_STATIC_ASSERT(weapon_obj_ext_size, sizeof(union WeaponObjExt) == 0x8);
#endif

struct WeaponObj {
    BASE_OBJ_FIELDS
    f32 unk18;
    f32 unk1C;
    f32 x_vel;
    f32 y_vel;
    f32 unk28;
    s32 unk2C;
    u32** animation_table;
    u32* animation_cursor;
    void* unk38;
    void* unk3C;
    u16 unk40;
    u16 unk42;
    union AnimationStep animation_step;
    u8 previous_animation_index;
    s8 unk49;
    s8 pad4A[0x50 - 0x4A];
    const void* unk50;
    const void* unk54;
    const void* unk58;
    s8 unk5C;
    s8 pad5D[3];
    s8 unk60;
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    struct Unk_unk68* unk68;
    s8 pad6C[4];
    u8 unk70;
    s8 unk71;
    u8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 : 8;
    s8 unk7A;
    s8 pad7B;
    struct PlayerObj* owner;
    union WeaponUnk80 unk80;
    union WeaponUnk84 unk84;
    union WeaponUnk88 unk88;
    s16 unk8A;
    union WeaponObjExt ext;
    u8 unk94;
    u8 unk95;
    s8 pad96[0x98 - 0x96];
    s8 unk98;
    s8 pad99[0x9C - 0x99];
}; // size 0x9C

MMX4_STATIC_ASSERT(weapon_unk54_offset,
    MMX4_OFFSET_OF(struct WeaponObj, unk54) == MMX4_OFFSET_OF(struct MainObj, hurt_box));
MMX4_STATIC_ASSERT(weapon_unk54_width,
    sizeof(((struct WeaponObj*)0)->unk54) == sizeof(((struct MainObj*)0)->hurt_box));

#ifndef MMX4_PC
MMX4_STATIC_ASSERT(psx_weapon_owner_offset,
    MMX4_OFFSET_OF(struct WeaponObj, owner) == 0x7C);
MMX4_STATIC_ASSERT(psx_weapon_ext_offset,
    MMX4_OFFSET_OF(struct WeaponObj, ext) == 0x8C);
#endif

union UnkObjLink {
    u8* data;
    struct UnkObj* previous;
    struct PlayerObj* player;
};

struct PlayerAfterimageExt {
    s16 position_timer;
    s16 blink_timer;
    s16 palette_offset;
    u8 pad5A[6];
};

struct Unk0Ext {
    u8 selection_index;
};

union UnkObjExt {
    u8 raw[0xC];
    s8 timer;
    struct Unk0Ext unk_0;
    struct PlayerAfterimageExt afterimage;
};

struct UnkObj {
    ANIMATED_OBJ_FIELDS
    s8 pad49[0x4B - 0x49];
    s8 unk4B;
    s8 pad4C[0x50 - 0x4C];
    union UnkObjLink link;
    union UnkObjExt ext;
}; // size 0x60

struct Item2Ext {
    s8 unk80;
    s8 unk81;
    u16 unk82;
};

struct Item4Ext {
    s32 timer;
};

struct Item12Ext {
    s32 x_offset;
};

struct Item23Ext {
    s16 unk80;
    s16 timer;
};

struct Item22Ext {
    s32 collision_side;
};

union ItemExt {
    u32 packed;
    s32 timer;
    struct Item2Ext item_2;
    struct Item12Ext item_12;
    struct Item22Ext item_22;
    struct Item23Ext item_23;
    struct MainObj* owner;
    u8* train_layer_parameter;
};

union ItemUnk84 {
    u16 timer;
    u32 previous_value;
    u8 bytes[4];
};

struct Item19Unk7C {
    u16 timer;
    u16 open_requested;
};

union ItemUnk7C {
    u8 value;
    u16 timer16;
    s32 timer;
    struct MainObj* owner;
    struct Main45Ext* train_boss;
    struct MiscObj* misc;
    void* object;
    struct Unk_unk68* bounds;
    s32 item_26_value;
    struct Item19Unk7C item_19;
    struct {
        u16 x;
        u16 y;
    } saved_pos;
};

struct ItemTailExtUnk {
    union ItemUnk84 unk84;
    s32 unk88;
};

struct ItemTailExtUnk2 {
    u8 timer;
    u8 previous_value;
    u8 value;
};

union ItemTailExt {
    struct ItemTailExtUnk unk1;
    struct ItemTailExtUnk2 unk2;
};

struct ItemObj {
    BASE_OBJ_FIELDS
    f32 unk18;
    f32 unk1C;
    f32 x_vel;
    f32 y_vel;
    s32 unk28;
    s32 unk2C;
    const u8* const* animation_table;
    const u8* animation_cursor;
    s16 animation_speed;
    u8 pad3A[2];
    const u8* sprite_frames;
    u16 unk40;
    u16 unk42;
    union AnimationStep animation_step;
    u8 previous_animation_index;
    s8 pad49[0x50 - 0x49];
    const u8* unk50;
    const u8* unk54;
    const u8* unk58;
    s8 unk5C;
    s8 pad5D[0x61 - 0x5D];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    struct Unk_unk68* unk68;
    s8 pad6C[0x70 - 0x6C];
    u8 unk70;
    s8 : 8;
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 : 8;
    s8 unk7A;
    s8 pad7B;
    union ItemUnk7C unk7C;
    union ItemExt ext;
    union ItemTailExt tail_ext;
}; // size 0x8C

union LayerPrivateState {
    f32 value;
    s8 signed_byte;
    u8 misc_20_active;
    u8 bytes[2];
};

struct LayerObj {
    BASE_OBJ_FIELDS
    f32 unk18;
    union LayerPrivateState private_state;
    s8 unk20[0x24 - 0x20];
    u8 unk24;
    u8 unk25;
    s8 pad26[0x30 - 0x26];
}; // size 0x30

struct MiscUnk50_2 {
    s8 unk0;
    s8 pad_[4];
    f32 x_pos;
    f32 y_pos;
    s32 unk8;
    s32 unkC;
    u8 unk16;
};

struct ReadyTextExt {
    struct EffectObj* owner;
    u16 unk54;
    u16 stay_up_timer; // 0x56
    u16 palette_pos;
    u16 unk58;
    u16 palette_cycle_done; // 0x5C
};

struct MiscPointerExt {
    void* unk50;
};

struct Misc7Ext {
    void* position;
};

struct Misc32Ext {
    struct MainObj* owner;
    s8 animation;
    u8 timer;
};

struct Misc5Ext {
    struct MainObj* owner;
    s8 animation;
};

struct Misc8Ext {
    u8 pad50[4];
    u8 alternate;
    u8 timer;
};

struct Misc2Ext {
    u8 pad50[4];
    struct MainObj* owner;
    u8 unk58;
};

struct Misc9Ext {
    u8 pad50[4];
    struct ItemObj* owner;
    u8 unk58;
};

struct Misc11Ext {
    u8 pad50[4];
    s8 active;
};

struct Misc42Ext {
    u8 pad50[4];
    s8 unk54;
    s8 unk55;
    s8 unk56;
    s8 unk57;
    s8 unk58;
};

struct Misc15Ext {
    u8 pad50[4];
    u16 unk54;
};

struct Misc16Ext {
    u8 pad50[4];
    u16 timer;
};

struct Misc51Ext {
    struct MainObj* source;
    u8 unk54;
};

struct Misc49Ext {
    void* owner;
    u16 timer;
};

struct Misc45Ext {
    u8 pad50[4];
    struct MainObj* owner;
    s16 unk58;
    s16 target_x;
    u8 direction;
};

struct Misc08EffectTriplet {
    u8 first;
    u8 second;
    u8 third;
};

struct Misc24Ext {
    struct MainObj* main;
    s16 timer;
    u16 child_active;
    struct MiscObj* child;
};

struct TitleLogoExt {
    struct MiscObj* unk50;
    u8 palette_shift_speed; // 0x54
    u8 palette_shift_value; // 0x55
    s8 unk56;
    u8 unk57;
    s32* palette1;
    s32* palette2;
};

struct SelectACharacterExt {
    s8 pad50[4];
    s8 unk54;
    u8 blast_timer; // 0x55
    s8 unk56;
    u8 cur_character_selected;
};

struct Misc4Ext {
    struct MainObj* owner;
};

struct Misc6Ext {
    u8 pad50[4];
    union {
        s32 packed;
        struct {
            s16 x;
            s16 y;
        } position;
    } saved_position;
    u8 timer;
};

struct Misc20Ext {
    struct LayerObj* owner;
};

struct Misc31Ext {
    u8 pad50[4];
    u8 animation;
    u8 timer;
};

struct Misc33Ext {
    s8* completion_flag;
    u16 timer;
};

struct Misc34Ext {
    struct EffectObj* related;
    u8 timer;
    u8 unk55;
    u8 variant;
    u8 unk57;
    u8 unk58;
    u8 enabled;
    u16 unk5A;
    u8 unk5C;
    u8 unk5D;
};

struct Misc39Ext {
    void* related;
    s16 timer;
};

struct Misc55Ext {
    struct MainObj* owner;
};

struct Misc52Ext {
    struct MiscObj* parent;
    u8 pad54;
    u8 timer;
    u8 unk56;
    s8 unk57;
};

struct Misc22Ext {
    struct MainObj* owner;
    u8 pad54[2];
    u8 timer;
};

struct Misc26Ext {
    struct MainObj* owner;
    u8 timer;
};

struct Misc30Ext {
    struct MainObj* owner;
    s8 unk54;
    u8 pad55;
    s16 unk56;
};

struct Misc53Ext {
    u8 pad50[4];
    struct EffectObj* effect;
    s16 timer;
    u8 movement_timer;
    u8 pad5B;
    s8 x_step;
};

struct UnkExt {
    struct MiscUnk50_2* unk50;
    s8 unk54;
    s8 unk55;
    union {
        s8 byte;
        u16 sht;
    } unk56;
    s8 unk58;
};

union MiscExt {
    struct Misc2Ext misc_2;
    struct Misc9Ext misc_9;
    struct Misc5Ext misc_5;
    struct Misc32Ext misc_32;
    struct Misc7Ext misc_7;
    struct Misc8Ext misc_8;
    struct Misc11Ext misc_11;
    struct Misc15Ext misc_15;
    struct Misc16Ext misc_16;
    struct Misc42Ext misc_42;
    struct Misc45Ext misc_45;
    struct Misc51Ext misc_51;
    struct Misc49Ext misc_49;
    struct Misc24Ext misc_24;
    struct ReadyTextExt ready_text;
    struct MiscPointerExt pointer;
    struct TitleLogoExt title_logo;
    struct SelectACharacterExt sel_char;
    struct Misc4Ext misc_4;
    struct Misc6Ext misc_6;
    struct Misc20Ext misc_20;
    struct Misc31Ext misc_31;
    struct Misc33Ext misc_33;
    struct Misc34Ext misc_34;
    struct Misc39Ext misc_39;
    struct Misc52Ext misc_52;
    struct Misc22Ext misc_22;
    struct Misc30Ext misc_30;
    struct Misc26Ext misc_26;
    struct Misc53Ext misc_53;
    struct Misc55Ext misc_55;
    struct UnkExt unk;
    struct {
        u32 pad;
        s8 bytes[10];
    } tail;
};

struct MiscObj {
    ANIMATED_OBJ_FIELDS
    s8 pad49[4];
    union MiscExt ext;
}; // size 0x60

struct BarObj {
    s8 : 8;
    s8 : 8;
    s8 unk2;
    s8 : 8;
    s8 state;
    s8 unk5;
    s8 unk6;
    s8 pad7;
    s32 x_pos;
    s8 padC[8];
    s8 unk14;
    s8 : 8;
    union {
        u8 items[16];
        struct {
            u8 player[2];
            u8 weapons[8];
            u8 unk20;
            u8 unk21;
            u8 unk22;
            u8 unk23;
            u8 unk24;
            u8 unk25;
        } fields;
    } options;
    s8 pad26[0x28 - 0x26];
    s32 unk28;
    s32 unk2C;
    s32 unk30;
}; // size 0x34

struct BazObj {
    ANIMATED_OBJ_FIELDS
    s8 pad49[0x50 - 0x49];
}; // size 0x50

union RideArmorUnkA0 {
    struct {
        s16 x;
        s16 y;
    } saved_accel;
    struct EffectObj* chaser_effect;
};

union RideArmorUnk98 {
    s16 packed;
    struct {
        u8 low;
        u8 high;
    } bytes;
};

union RideArmorUnk80 {
    u32 packed;
    struct {
        u8 unk80;
        u8 unk81;
        u8 unk82;
        u8 unk83;
    } bytes;
};

union RideArmorUnk94 {
    u32 value;
    u16 halves[2];
    struct {
        u8 pad94[3];
        s8 unk97;
    } bytes;
};

union RideArmorUnk90 {
    u32 value;
    s8 byte;
    struct {
        u8 pad90[3];
        u8 action_state;
    } bytes;
};

union RideArmorInputState {
    u16 value;
    struct {
        u8 buttons;
        u8 cooldown;
    } bytes;
};

union RideArmorTapState {
    u16 value;
    struct {
        u8 active;
        u8 timer;
    } bytes;
};

struct RideArmorObj {
    ANIMATED_OBJ_FIELDS
    s8 unk49;
    s8 unk4A;
    s8 pad4B[0x50 - 0x4B];
    void* unk50;
    const void* unk54;
    const void* unk58;
    s8 hp;
    s8 unk5D;
    s8 unk5E;
    s8 unk5F;
    s8 unk60;
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    struct Unk_unk68* unk68;
    s16 unk6C;
    s16 unk6E;
    u8 unk70;
    u8 unk71;
    u8 unk72;
    u8 unk73;
    u8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 unk79;
    s8 unk7A;
    s8 pad7B;
    u8 unk7C;
    u8 unk7D;
    u8 unk7E;
    u8 spawned_parts;
    union RideArmorUnk80 unk80;
    u8 unk84;
    u8 unk85;
    u8 unk86;
    s8 unk87;
    u16 collision_flags;
    s16 unk8A;
    union RideArmorInputState unk8C;
    union RideArmorTapState unk8E;
    union RideArmorUnk90 unk90;
    union RideArmorUnk94 unk94;
    union RideArmorUnk98 unk98;
    s16 pad9A;
    s16 saved_x_vel;
    s16 saved_y_vel;
    union RideArmorUnkA0 unkA0;
    s16 launch_speed;
    u16 unkA6;
    s8 input_flags;
    s8 padA9[0xB0 - 0xA9];
}; // size 0xB0

#define ASSERT_RIDE_ARMOR_FIELD(ride_field, player_field) \
    MMX4_STATIC_ASSERT(ride_armor_##ride_field,           \
        MMX4_OFFSET_OF(struct RideArmorObj, ride_field) == MMX4_OFFSET_OF(struct PlayerObj, player_field))
ASSERT_RIDE_ARMOR_FIELD(unk49, unk49);
ASSERT_RIDE_ARMOR_FIELD(unk50, unk50);
ASSERT_RIDE_ARMOR_FIELD(hp, hp);
ASSERT_RIDE_ARMOR_FIELD(unk68, unk68);
ASSERT_RIDE_ARMOR_FIELD(unk70, unk70);
ASSERT_RIDE_ARMOR_FIELD(unk7A, spike_immune);
ASSERT_RIDE_ARMOR_FIELD(unk7C, input);
ASSERT_RIDE_ARMOR_FIELD(unk80, pressed_input);
ASSERT_RIDE_ARMOR_FIELD(collision_flags, unk88);
ASSERT_RIDE_ARMOR_FIELD(unk8A, unk8A);
ASSERT_RIDE_ARMOR_FIELD(unk8E, attacking);
#undef ASSERT_RIDE_ARMOR_FIELD
#ifndef MMX4_PC
MMX4_STATIC_ASSERT(psx_ride_armor_size, sizeof(struct RideArmorObj) == 0xB0);
#endif

// D_8013BC28
struct AbcObj {
    u16* unk0;
    u16 unk4;
    s16 unk6;
    s16 unk8;
    u16 unkA;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 : 16;
}; // size 0x14

struct Func80022730Config {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
};

struct Unk2 {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 pad2[1];
    s16 unk4;
    u8 pad5[6];
    u8 unkC;
    u8 unkD;
};

struct Unk3 {
    u8 pad[0xc0];
    s8 unkC0;
};

struct Unk10 {
    u8 pad[0x2A];
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 pad2[8];
}; /* size 0x35 */

struct Unk11 {
    u8 unk00;
    u8 unk01;
    s8 unk02;
    u8 padding03[3];
    u8 unk06;
    u8 padding07[13];
    u8 unk14;
    u8 padding15[11];
    u32 unk20;
    s32 unk24;
    u32 unk28;
    u8 padding2C[59];
    s8 unk67;
    u8 padding68[33];
    u8 unk89;
};

struct Unk12 {
    u8 pad0[2];
    s8 unk2;
    u8 pad3[0xc0];
    s8 unkC3;
};

struct Unk15 {
    u8 pad[5];
    u8 unk5;
    u8 pad10[0x79];
    u16 unk80;
    u16 unk82;
    u8 pad82[3];
    u8 unk87;
    s8 unk88;
    u8 pad5[0x3a];
    s8 unkC3;
};

struct Unk16 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 unk18[0x70 - 0x18];
    s32 unk70;
    u8 unk74[0x9C - 0x74];
    u32 unk9C;
};

#ifndef MMX4_SATURN
struct BgDrawRelated {
    SPRT_16 sprites[0x400];
};

struct MainPrimitiveBuffer {
    POLY_FT4 data[0x400];
};

struct SecondaryPrimitiveBuffer {
    P_TAG data[0x400];
};

struct BackgroundPrimitiveBuffer {
    SPRT_16 data[32];
};

struct OrderingTableBuffer {
    DR_TPAGE data[32];
};

struct AuxiliaryPrimitiveBuffer {
    POLY_F4 data[5];
};
#endif

struct StageSpriteSlot {
    s32 tag;
    s8 r;
    s8 g;
    s16 b_and_code;
    s16 x;
    s16 y;
    s16 u;
    s16 v;
};

struct StageSpritePrimitive {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u16 u0, v0;
    u16 clut;
    s16 w, h;
};

struct GameThread {
    u16 state;
    s16 timer;
    u32 unk4;
    u32 handle;
    u32 unkC;
    u32 stack;
    u32 unk14[12];
    u32 global_pointer;
    u8 pad48[0x80 - 0x48];
};

extern struct PlayerObj g_Player;
extern struct PlayerObj g_Entity;
#ifdef MMX4_WIN32
extern u8 flicker_enabled;
#define FLICKER_ENABLED flicker_enabled
#else
#define FLICKER_ENABLED 1
#endif
#ifdef MMX4_WIN32
extern struct Unk16 blink_timer;
#define BLINK_TIMER blink_timer
#endif
#ifdef MMX4_WIN32
extern u8 easy_mode;
extern s16 easy_hp;
#define EASY_MODE easy_mode
#define EASY_HP_SET(v) (easy_hp = (v))
#define EASY_HP_ADD(v) (easy_hp += (v))
#else
extern s16 easy_hp;
#define EASY_MODE 0
#define EASY_HP_SET(v)
#define EASY_HP_ADD(v)
#endif
#ifdef MMX4_WIN32
#define SHAKE_ENABLED FLICKER_ENABLED
#define BLINK_CLOCK(timer) BLINK_TIMER.unk0
#else
#define SHAKE_ENABLED 1
#define BLINK_CLOCK(timer) (timer)
#endif
extern struct BackgroundObj background_objects[3];
extern u8 jet_stingray_bubble_index;

#ifndef MMX4_SATURN
extern struct BgDrawRelated D_8015D9D0[];
extern struct MainPrimitiveBuffer temp1[];
extern struct SecondaryPrimitiveBuffer temp2[];
extern struct BackgroundPrimitiveBuffer temp3[];
extern struct OrderingTableBuffer temp4[];
extern struct AuxiliaryPrimitiveBuffer temp5[];
extern TILE D_80169D78[2];
#endif
extern struct FadeState D_8016DEA0;
#ifndef MMX4_SATURN
extern DR_TPAGE D_8012F498[2];
extern TILE D_8013B7B0[2];
extern POLY_FT4 D_80139F20[2];
extern POLY_F4 D_80139F70[2];
extern DR_TPAGE D_80139FA0[2];
extern POLY_F4 D_80139FB0[2][128];
extern DR_TPAGE D_80171EB0[2][6][8];
#endif
extern u8 D_80141BE8[];
extern u16 D_801441C8[3][32][32];

#ifndef MMX4_PC
typedef u32 OT_TYPE;
#endif

#ifndef MMX4_SATURN
extern P_TAG* D_8013BC40[2][4][8];
extern P_TAG* D_8013E1E8[2][4][8];

struct DrawOrderingTable {
    OT_TYPE start;
    OT_TYPE unk1;
    OT_TYPE fade;
    OT_TYPE unk3;
    OT_TYPE mid;
    OT_TYPE unk5[5];
    OT_TYPE ui;
    OT_TYPE end;
};

struct DrawInfo {
    DISPENV dispenv;
    DRAWENV drawenv; // 0x14
    struct DrawOrderingTable ordering_table;
#ifdef MMX4_PC
    P_CODE ordering_table_tail;
#endif
};

extern struct DrawInfo draw_infos[2];
#endif

typedef union {
    s32* ptr;
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } two;
    struct {
        u16 lo;
        u16 hi;
    } utwo;
    struct {
        s8 a;
        s8 b;
        s8 c;
        s8 d;
    } one;
} Multi;

struct ReadyLineExt {
    f32 x_vel;
    f32 y_vel;
    f32 x_accel;
    f32 y_accel;
};

struct SearchLightMotion {
    s32 velocity;
    s32 acceleration;
    s32 vertical_velocity;
    s32 vertical_acceleration;
};

struct QuadUnkExt {
    u16 unk38;
};

struct TitleQuadExt {
    u16 unk38;
    u8 unk3A[4];
    u8 unk3E[4];
    u8 unk42;
    u8 unk43;
};

struct Quad4Ext {
    u8 unk38;
    u8 unk39;
    u8 timer;
};
union QuadScale {
    u16 value;
    struct {
        u8 fraction;
        u8 integer;
    } bytes;
};

struct Quad2Ext {
    const s32* vertices;
    union QuadScale x_scale;
    union QuadScale y_scale;
    u8 direction[2];
};

extern u8 D_8013B960;

struct QuadUnkExt3 {
    u8 unk38;
};

struct Quad5Ext {
    s32* data;
    u16 scale;
    s16 update_timer;
    u16 index;
};

struct Quad10Ext {
    s32 counter;
    s32 x_step;
    s32 y_step;
    u8 progress;
#ifdef MMX4_PC
    u8 history[16];
#else
    u8 history[3];
#endif
};

struct QuadUnkExt4 {
    s32 : 32;
    u16 unk3C;
};

struct Quad1Ext {
    u8 settled[4];
    u8 region[4];
    u16 steps;
    u8 unk42;
    u8 delay;
};

union QuadExt {
    struct Quad1Ext quad_1;
    struct ReadyLineExt ready_line;
    struct SearchLightMotion search_light;
    struct QuadUnkExt unk_ext;
    struct TitleQuadExt title_quad;
    struct Quad4Ext quad_4;
    struct Quad5Ext quad_5;
    struct Quad2Ext quad_2;
    struct QuadUnkExt3 unk_ext3;
    struct QuadUnkExt4 unk_ext4;
    struct Quad10Ext quad_10;
    u32 unk38;
};

struct SearchLightRuntime {
    s32 x_accumulator;
    s32 y_accumulator;
    u16 pause_timer;
    s16 extent;
    s32 base_speed;
};

struct Quad06Runtime {
    s32 x_accumulator;
    s32 y_accumulator;
    s32 acceleration;
    s32 base_speed;
};

struct ReadyLineRuntime {
    u8 directions[4];
    u8 crossed[4];
    u16 interpolation_frames;
    s16 delay;
    u8 converging;
    u8 initialized;
    u8 alignment[2];
};

union QuadRuntime {
    struct {
        u8 unk48;
        s8 pad_[3];
        s8 unk4C;
        s8 unk4D;
        s8 unk4E;
        s8 unk4F;
        u16 unk50;
        s16 unk52;
        s8 unk54;
        s8 unk55;
        u8 pad56[2];
    } legacy;
    struct SearchLightRuntime search_light;
    struct Quad06Runtime quad_06;
    struct ReadyLineRuntime ready_line;
};

union QuadLink {
    struct EffectObj* owner;
    u16 direction;
    s32 y_accel;
};

struct QuadVertex {
    f32 x;
    f32 y;
};

struct QuadObj {
    OBJECT_HEADER_FIELDS
    struct QuadVertex vertices[4];
    u16 unk34;
    s8 unk36;
    s8 bg_offset;
    union QuadExt ext;
    union QuadRuntime runtime;
    union QuadLink link;
    struct PlayerObj* unk5C; // might be something else
}; // size 0x60

#ifdef MMX4_WIN32
#pragma pack(push, 1)
#endif
union EngineCharacterState {
    s8 bytes[0x10];
    struct {
        s8 active;
        s8 flags;
        s8 selected_characters;
        s8 previous_character;
        s8 secret_code_phase;
        s8 secret_code_index;
#ifdef MMX4_SHC
        u8 menu_state_bytes[4];
#else
        s32 menu_state;
#endif
        u8 reserved[6];
    }
#if !defined(MMX4_WIN32) && !defined(MMX4_SHC)
    __attribute((packed))
#endif
    fields;
};

#ifdef MMX4_WIN32
#pragma pack(pop)
#endif

// D_801721C0
struct EngineObj {
    s8 state;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s16 unk4;
    s8 unk6;
    s8 unk7;
    s16 unk8;
    s16 unkA;
    s8 stage; // 0xc
    s8 substage; // 0xd
    s8 unkE;
    s8 unkF;
    s8 unk10;
    s8 unk11;
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
    s8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
    s8 gameplay_locked;
    s8 checkpoint; // 0x1d
    s8 unk1E;
    s8 unk1F;
    struct MainObj* boss_ptr; // 0x20
    s8 enable_boss; // 0x24
    s8 unk25;
    union EngineCharacterState character_state; // 0x26
    union {
        s8 value;
        u8 timer;
    } unk36;
    s8 unk37;
    struct PlayerObj* controlled_player;
    struct BaseObj* unk3C;
    u8 unk40;
    s8 unk41;
    u8 unk42;
    s8 cur_character; // 0x43
    s8 player_lives;
    u8 checkpoint_hp;
    s8 max_hp;
    s8 armor_parts;
    s8 arm_type;
    s8 player_initial_data[0x10]; // 0x49
    s8 palette_flags; // 0x59
    u16 collected_upgrades;
    s8 sub_tanks[3];
    u8 unk5F;
    u8 unk60;
    u8 pad61[3];
}; // size 0x64

#define engine_flags engine_obj.character_state.fields.flags

struct Unk66 {
    u8 pad[0x34];
    u32* unk34;
    u8 pad2[12];
    union {
        struct {
            s8 unk44;
            s8 : 8;
            s8 unk46;
        } j;
        s32 unk44;
    } i;
};

struct Unk20 {
    u8 unk0;
    u8 unk1;
};

struct Unk21 {
    u8 pad[4];
    u8 unk4;
    u8 unk5;
    u8 pad2[0xe];
    u8 unk14;
    u8 unk15;
    u8 unk16;
};

struct GameInfo {
    s8 unk0;
    s8 mode;
    s8 unk2;
    s8 unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s8 unkC;
    s8 unkD;
    s8 unkE;
    s8 unkF;
}; // size 0x10

struct Unk80139690 {
    u8 pad;
    s8 unk1;
};

struct Unk14 {
    u16 unk0;
    s8 unk2;
    u8 unk3;
};

struct UnkEffectExt {
    u8 unk14;
    u8 unk15;
    u8 unk16;
    s8 : 8;
    void* unk18;
};

struct Effect26Ext {
    u16 timer;
    u8 quad_timer;
};

struct Effect4Ext {
    u16 timer;
    s16 unk16;
};

struct Effect22Ext {
    u8 unk14;
    u8 unk15;
    s8 unk16;
    s8 unk17;
    s16 unk18;
};

struct Effect24Ext {
    struct EffectObj* spawned_effect;
    u16 timer;
    u8 unk1A;
    u8 unk1B;
};

struct Effect12Ext {
    struct MainObj* children[4];
    u16 cooldown;
    u16 timer;
    u8 spawned;
    u8 child_count;
    u8 child_subtype;
    u8 child_id;
};

struct Effect16Ext {
    u8 pad14[4];
    u16 saved_background_2A;
    u16 saved_background_28;
};

struct Effect38Ext {
    u8 pad14;
    u8 timer;
    u8 active;
    u8 variant;
};

struct Effect28Ext {
    u8 pad14[4];
    u8 timer;
    u8 filter_timer;
    u8 unk1A;
    u8 unk1B;
    u8 palette_index;
    u8 finished;
};

struct Effect37Ext {
    u8 pad14[4];
    u8 timer;
    u8 unk19;
    u8 unk1A;
    u8 pad1B;
    u8 action;
    u8 finished;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
};

struct Effect34Ext {
    u8 unk14;
    u8 pad15;
    u16 timer;
};

struct Effect8Ext {
    u8 pad14[2];
    s8 unk16;
    s8 unk17;
    s16 unk18;
};

struct Effect9Ext {
    s16 transition_timer;
    u16 movement_timer;
    s16 direction;
    u16 target_x;
    u8* movement_table;
    u8 timer;
    s8 frame;
    u8 pad22[2];
    s32 velocity;
};

struct Effect42Ext {
    union {
        struct MainObj* main;
        struct PlayerObj* player;
    } owner;
    u8 timer;
};

struct Effect43Ext {
    u16 unk14;
    u16 unk16;
};

struct Effect21SpawnRecord {
    u16 x;
    u16 y;
    u8 object_id;
    u8 flags;
};

struct Effect21Ext {
    struct Effect21SpawnRecord* cursor;
    u32 spawned;
    u8 timer;
    u8 index;
    u8 phase;
    u8 inside;
    u8 was_inside;
};

struct Effect5Ext {
    s32 unk14;
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
};

struct Effect14Ext {
    u16 unk14;
    u8 unk16;
};
struct Effect17Ext {
    struct AnimatedObj* source;
    u8 timer;
    u8 phase;
};
union Effect32Palette {
    s32 packed;
    struct {
        u8 timer;
        u8 unk1;
        s8 step;
        u8 id;
    } fields;
};

union Effect32PaletteSource {
    u8* bytes;
    s32* words;
    struct Effect28AnimationStep* animation;
};

struct Effect32Ext {
    u8 unk14;
    s8 unk15;
    u8 unk16, pad17;
    union Effect32Palette palette;
    union Effect32PaletteSource palette_source;
};

struct Effect33Ext {
    u8 timer;
    u8 period;
    u8 proximity;
    u8 variant;
    u8 burst;
    u8 cooldown;
};

struct EffectPaletteExt {
    u8 unk14, unk15, unk16, pad17;
    union Effect32Palette palette;
    union Effect32PaletteSource palette_source;
};

struct Effect23Ext {
    u32 unk14;
    union Effect32Palette palette;
    union Effect32PaletteSource palette_source;
};

struct Effect41Ext {
    u32 unk14;
    union Effect32Palette palette;
    union Effect32PaletteSource palette_source;
};

struct Effect36Ext {
    u8 pad14[4];
    struct EffectObj* spawned_effect;
    u32 timer;
};

struct Effect28AnimationStep {
    u8 timer;
    u8 unused;
    s8 frame_step;
    u8 frame;
};
struct ScalingX {
    struct Unk14* unk14;
    s8 unk18;
};

struct PaletteAnimationExt {
    s32* source;
    s32* destination;
    s8* cursor;
    s8 palette_count;
    s8 timer;
    u8 padding[14];
};

union EffectExt {
    struct Effect12Ext effect_12;
    struct Effect16Ext effect_16;
    struct Effect9Ext effect_9;
    struct Effect26Ext effect_26;
    struct Effect4Ext effect_4;
    struct UnkEffectExt unk_effect;
    struct Effect5Ext effect_5;
    struct Effect21Ext effect_21;
    struct Effect8Ext effect_8;
    struct Effect14Ext effect_14;
    struct Effect17Ext effect_17;
    struct UnkEffectExt effect_15;
    struct UnkEffectExt effect_19;
    struct UnkEffectExt effect_20;
    struct Effect22Ext effect_22;
    struct Effect24Ext effect_24;
    struct UnkEffectExt effect_25;
    struct UnkEffectExt effect_27;
    struct Effect23Ext effect_23;
    struct Effect28Ext effect_28;
    struct EffectPaletteExt effect_29;
    struct Effect32Ext effect_32;
    struct Effect33Ext effect_33;
    struct Effect34Ext effect_34;
    struct Effect36Ext effect_36;
    struct Effect37Ext effect_37;
    struct Effect38Ext effect_38;
    struct EffectPaletteExt effect_39;
    struct EffectPaletteExt effect_40;
    struct Effect41Ext effect_41;
    struct Effect42Ext effect_42;
    struct Effect43Ext effect_43;
    struct ScalingX scaling_x;
    struct PaletteAnimationExt palette_animation;
};

struct EffectObj {
    OBJECT_HEADER_FIELDS
    union EffectExt ext;
}; // size 0x30

#ifdef MMX4_PC
MMX4_STATIC_ASSERT(pc_effect_object_size, sizeof(struct EffectObj) == 0x40);
#else
MMX4_STATIC_ASSERT(psx_effect_object_size, sizeof(struct EffectObj) == 0x30);
#endif

#define ASSERT_OBJECT_HEADER(type, first_tail_member)                                          \
    MMX4_STATIC_ASSERT(type##_backref_offset,                                                  \
        MMX4_OFFSET_OF(struct type, backref) == MMX4_OFFSET_OF(struct ObjectHeader, backref)); \
    MMX4_STATIC_ASSERT(type##_header_size,                                                     \
        MMX4_OFFSET_OF(struct type, first_tail_member) == sizeof(struct ObjectHeader))

ASSERT_OBJECT_HEADER(BaseObj, bg_offset);
ASSERT_OBJECT_HEADER(PlayerObj, bg_offset);
ASSERT_OBJECT_HEADER(VisualObj, bg_offset);
ASSERT_OBJECT_HEADER(ShotObj, bg_offset);
ASSERT_OBJECT_HEADER(WeaponObj, bg_offset);
ASSERT_OBJECT_HEADER(UnkObj, bg_offset);
ASSERT_OBJECT_HEADER(ItemObj, bg_offset);
ASSERT_OBJECT_HEADER(LayerObj, bg_offset);
ASSERT_OBJECT_HEADER(MiscObj, bg_offset);
ASSERT_OBJECT_HEADER(BazObj, bg_offset);
ASSERT_OBJECT_HEADER(RideArmorObj, bg_offset);
ASSERT_OBJECT_HEADER(MainObj, bg_offset);
ASSERT_OBJECT_HEADER(QuadObj, vertices);
ASSERT_OBJECT_HEADER(EffectObj, ext);

#undef ASSERT_OBJECT_HEADER

#define ASSERT_MOVING_OBJECT(type)                                                      \
    MMX4_STATIC_ASSERT(type##_x_vel_offset,                                             \
        MMX4_OFFSET_OF(struct type, x_vel) == MMX4_OFFSET_OF(struct MovingObj, x_vel)); \
    MMX4_STATIC_ASSERT(type##_y_vel_offset,                                             \
        MMX4_OFFSET_OF(struct type, y_vel) == MMX4_OFFSET_OF(struct MovingObj, y_vel))

ASSERT_MOVING_OBJECT(PlayerObj);
ASSERT_MOVING_OBJECT(VisualObj);
ASSERT_MOVING_OBJECT(MiscObj);
ASSERT_MOVING_OBJECT(WeaponObj);

#undef ASSERT_MOVING_OBJECT

#define ASSERT_ANIMATED_OBJECT(type)                                                                            \
    MMX4_STATIC_ASSERT(type##_animation_table_offset,                                                           \
        MMX4_OFFSET_OF(struct type, animation_table) == MMX4_OFFSET_OF(struct AnimatedObj, animation_table));   \
    MMX4_STATIC_ASSERT(type##_animation_cursor_offset,                                                          \
        MMX4_OFFSET_OF(struct type, animation_cursor) == MMX4_OFFSET_OF(struct AnimatedObj, animation_cursor)); \
    MMX4_STATIC_ASSERT(type##_animation_step_offset,                                                            \
        MMX4_OFFSET_OF(struct type, animation_step) == MMX4_OFFSET_OF(struct AnimatedObj, animation_step));     \
    MMX4_STATIC_ASSERT(type##_previous_animation_index_offset,                                                  \
        MMX4_OFFSET_OF(struct type, previous_animation_index) == MMX4_OFFSET_OF(struct AnimatedObj, previous_animation_index))

ASSERT_ANIMATED_OBJECT(PlayerObj);
ASSERT_ANIMATED_OBJECT(MainObj);
ASSERT_ANIMATED_OBJECT(VisualObj);
ASSERT_ANIMATED_OBJECT(ShotObj);
ASSERT_ANIMATED_OBJECT(UnkObj);
ASSERT_ANIMATED_OBJECT(MiscObj);
ASSERT_ANIMATED_OBJECT(WeaponObj);

#undef ASSERT_ANIMATED_OBJECT

#endif
