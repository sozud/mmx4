#ifdef VERSION_JP
#define ASM_ROOT "asm/jp/"
#elif defined(VERSION_EU)
#define ASM_ROOT "asm/eu/"
#else
#define ASM_ROOT "asm/us/"
#endif

#if defined(MMX4_PC) || defined(SKIP_ASM) || defined(PERMUTER)
#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)
#else
#define INCLUDE_ASM(FOLDER, NAME)                            \
    __asm__(".pushsection .text\n"                           \
            "\t.align\t2\n"                                  \
            "\t.globl\t" #NAME "\n"                          \
            "\t.ent\t" #NAME "\n" #NAME ":\n"                \
            ".include \"" ASM_ROOT FOLDER "/" #NAME ".s\"\n" \
            "\t.set reorder\n"                               \
            "\t.set at\n"                                    \
            "\t.end\t" #NAME "\n"                            \
            ".popsection");

#define INCLUDE_RODATA(FOLDER, NAME)                         \
    __asm__(".pushsection .rodata\n"                         \
            ".include \"" ASM_ROOT FOLDER "/" #NAME ".s\"\n" \
            ".popsection");

__asm__(".include \"macro.inc\"\n");
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define NULL ((void*)0)
#define FIXED(x) ((s32)((x)*0x10000))
#define COUNT(x) (sizeof(x) / sizeof(x[0]))
#define SOME_COORDINATE_CONVERSION(v) ((((v)*4) + 24) % 16 | (((((v)*4) + 24) / 16) + 480) << 6)
#define WITHIN_BOUNDS(lo, v, hi) ((lo) < (v) && (v) < (hi))
#define POS_BOUNDS_CHECK_FAIL_RET0(a, b) \
    if (a - b >= 0) {                    \
        if (a - b <= 0x2FFFF) {          \
        } else {                         \
            return 0;                    \
        }                                \
    } else {                             \
        if (b - a > 0x2FFFF)             \
            return 0;                    \
    }

#define ABS(A, B) (((A) - (B) < 0) ? (B) - (A) : (A) - (B))

#define ON_SCREEN_X(X, W) ((u16)((X) + (W)) < (u16)((W) + ((W) + SCREEN_WIDTH)))
#define ON_SCREEN_Y(Y, H) ((u16)((Y) + (H)) < (u16)((H) + ((H) + SCREEN_HEIGHT)))

#define MMX4_STATIC_ASSERT(name, condition) typedef char static_assert_##name[(condition) ? 1 : -1]
#ifdef MMX4_PC
#define MMX4_OFFSET_OF(type, member) __builtin_offsetof(type, member)
#else
#define MMX4_OFFSET_OF(type, member) ((u32) & (((type*)0)->member))
#endif

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef u16 Palette[16];

#ifdef MMX4_WIN32
typedef u8 ret_u8;
typedef s8 ret_s8;
typedef u8 arg_u8;
typedef u16 arg_u16;
#else
typedef s32 ret_u8;
typedef s32 ret_s8;
typedef s32 arg_u8;
typedef s32 arg_u16;
#endif

#ifdef MMX4_PC
#include <psyz.h>
#include <libgte.h>
#include <libgpu.h>
#define SsVabTransCompleted PsyzSsVabTransCompleted
#include <libsnd.h>
#undef SsVabTransCompleted
#include <libetc.h>
#include <kernel.h>
#include <libapi.h>
#include <libcd.h>
#include <libpress.h>
#else
#include "psy-q-4.0/SYS/TYPES.H"
#include "psy-q-4.0/LIBGTE.H"
#include "psy-q-4.0/LIBGPU.H"
#include "psy-q-4.0/LIBSND.H"
#include "psy-q-4.0/LIBETC.H"
#include "psy-q-4.0/KERNEL.H"
#include "psy-q-4.0/LIBCD.H"
#include "psy-q-4.0/LIBPRESS.H"
#endif

#include "scratchpad.h"
#include "archive_memory.h"

#ifdef VERSION_JP
#define PAD_CONFIRM PADRright
#define PAD_CANCEL PADRdown
#define PAD_SELECTION_ALT PADRdown
#define PAD_SELECTION_BUTTONS (PADRright | PADRdown)
#elif defined(MMX4_WIN32)
#define PAD_CONFIRM (PADRleft | PADstart)
#define PAD_CANCEL PADRright
#define PAD_SELECTION_ALT PADRdown
#define PAD_SELECTION_BUTTONS (PADstart | PADRleft | PADRdown)
#else
#define PAD_CONFIRM PADRdown
#define PAD_CANCEL PADRright
#define PAD_SELECTION_ALT PADRup
#define PAD_SELECTION_BUTTONS (PADRup | PADRdown)
#endif

union MainPaletteData {
    u8 raw[0x200];
    struct {
        u8 preceding_palettes[0xA0];
        u16 dialogue_palette[0x20];
        u8 trailing_palettes[0x120];
    };
};

struct DialogueGlyph {
    u8 frame;
    u8 character;
    u8 x;
    u8 y;
};

struct DialogueGlyphData {
    u16 count;
    u16 active;
    struct DialogueGlyph glyphs[60];
};

union PlayerChargeData {
    struct {
        s8 animation_indices[6];
        s8 initial_thresholds[3];
        s8 linked_thresholds[15];
    } charge;
    struct {
        s8 health_divisors[18];
        s8 alignment_padding[6];
    } hud;
};

struct SoundArchive {
    u32 vab_offset : 24;
    u32 vab_id : 8;
    u32 unk4;
    u8 sound_entries[0];
};
struct SoundTransfer {
    s32 remaining;
    s32 offset;
};

typedef char SoundArchive_header_must_be_8_bytes[sizeof(struct SoundArchive) == 8 ? 1 : -1];

struct CdImageOrigin {
    u16 x, y;
};
union CdCommand {
    u32 word;
    struct {
        u8 arg; // 0x0
        u8 op; // 0x1
        u16 handler; // 0x2
    } f;
};
extern union CdCommand D_80137CD4;
struct HudSpriteOrigin {
    s16 x, y;
    u16 clut;
};
struct StageObjectMarginData {
    u16 margins[5];
    u16 alignment_padding;
};
struct TransitionState {
    s8 active;
    s8 fade_amount;
    s8 suspended;
    u8 selection;
};
struct MainBssState {
    s32 frame_counter;
    struct TransitionState transition;
    u8 character_mode;
    u8 alignment_padding[3];
};
extern struct MainBssState main_bss_state;

struct ControllerInput {
    u16 held;
    u16 previous;
    u16 pressed;
};
extern struct ControllerInput controller_input;

struct MemcardMenuState {
    u8* buffer;
    u8 card_status[2];
    u8 port;
    u8 selection;
    u8 result;
    u8 operation;
    u8 timer;
    u8 padding;
    struct MemcardSaveSlot* slot;
};
extern struct MemcardMenuState memcard_menu;

struct FadeState {
    s16 unk0, unk2;
    u16 unk4, alignment_padding;
};
struct ArchiveSelectionData {
    u8 prefix[8];
#ifdef MMX4_WIN32
    u8 archive_ids[128];
#else
    u8 archive_ids[124];
#endif
};
union CdSectorBuffer {
    u8 sectors[16][0x800];
    u32 words[0x2000];
};
struct TitleObjectInit {
    s16 x, y;
    s8 sprite, flags;
};
struct SearchLightInit {
    s16 vertices[8];
    u16 extent;
};
struct SearchLightColorLookup {
    u16 values[3];
    u16 alignment;
};
struct SearchLightIntensityLookup {
    u8 values[3];
    u8 alignment;
};
struct SearchLightSpawner {
    u8 active, type, reserved, background_index;
    s16 x, y;
};
struct CharacterSelectPosition {
    s16 x, y;
};
struct TileEffectRecord {
    u8 layer;
    u8 pad1[3];
    u8 packed_count;
    u8 pad5;
    s16 x, y;
    u16 padA;
    u16* tiles;
    u8 has_next;
};
struct ArchivePathData {
    s8 stage_archive_indices[12];
#ifndef MMX4_WIN32
#ifdef VERSION_JP
    char paths[162][64];
#elif defined(VERSION_EU)
    char paths[165][64];
#else
    char paths[163][64];
#endif
#endif
};
struct VisualAttachmentOffset {
    s16 x, y;
};
struct VisualAttachmentInit {
    u8 archive_slot, animation, sound;
};
struct VisualSpawnOffset {
    s8 x, y;
};
struct VisualBounds {
    s16 x, y;
};
struct CdCompletionSlot {
    u8 pending, callback;
    u16 pad2;
    u32 callback_arg;
    u16 transfer_pending, padA;
};
typedef char CdCompletionSlot_must_be_12_bytes[sizeof(struct CdCompletionSlot) == 12 ? 1 : -1];
struct BackgroundCameraModePair {
    u8 primary, secondary;
};
struct PlayerGaugePosition {
    s16 x;
    u16 bottom;
};
typedef union {
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } i;
    struct {
        u16 lo;
        u16 hi;
    } u;
    u8 bytes[4];
} f32;
struct TitlePointState {
    f32 coordinates[36];
    u8 unk90[18]; /* 0x90 */
    u8 unkA2[18]; /* 0xA2 */
    u8 settled; /* 0xB4 */
};
union TitleScratch {
    s32 sector[0x200];
    struct TitlePointState title;
};
union SepBundle {
    s32 offsets[0x1000];
    u8 raw[0x4000];
};
struct BackgroundLayoutConfig {
    u8 object_ids[4];
    u8 layer_ids[3][2];
};
struct BackgroundLayoutConfigData {
    struct BackgroundLayoutConfig records[33];
    u8 alignment_padding[2];
};
struct Checkpoint {
    s16 x, y;
    s16 bg0_x, bg0_y, bg1_x, bg1_y, bg2_x, bg2_y;
    s16 bg0_right, bg0_bottom, bg0_left, bg0_top;
    s16 facing;
    s16 bg1_off_x, bg1_off_y, bg2_off_x, bg2_off_y;
    s16 player_unkBE;
#ifdef MMX4_WIN32
    s16 pc_unk24[2];
#endif
};
struct StageObjectRecord {
    u8 flags, id, subtype, object_type;
    s16 x, y;
};

struct FixedPointPosition {
    s32 x;
    s32 y;
};

struct FixedMatrix2 {
    s16 m00, m01;
    s16 m10, m11;
};

struct BootTransitionDataRegion {
    u8 preceding_record_tail[3];
    u8 stage_map[9];
} __attribute__((packed));

#ifdef MMX4_WIN32
extern u8 mission_stage_order[16];
#else
extern u8 mission_stage_order[12];
#endif
extern u8 mission_palette_order[8];
extern u8 mission_route_b[8];
extern RECT mission_route_a_positions;
extern RECT mission_route_b_positions;
extern u16 briefing_voice_ids[10];
extern union PlayerChargeData player_weapon_energy;

union AnimationStep {
    u32 packed;
    struct {
        s8 duration;
        s8 event;
        s8 relative_step;
        u8 frame_index;
    } fields;
};

union PlayerUnk8A {
    u16 packed;
    struct {
        u8 low;
        s8 high;
    } bytes;
};

union PlayerUnkDC {
    s16 value;
    u16 unsigned_value;
};

typedef s8 PlayerChargeState;
enum {
    PLAYER_CHARGE_NONE,
    PLAYER_CHARGE_PARTIAL,
    PLAYER_CHARGE_FULL,
};

enum PlayerState {
    PLAYER_STATE_INIT,
    PLAYER_STATE_NORMAL,
    PLAYER_STATE_DEATH,
    PLAYER_STATE_INACTIVE,
};

enum PlayerAction {
    PLAYER_BEAM_IN,
    PLAYER_BEAM_OUT,
    PLAYER_IDLE,
    PLAYER_WALK_START,
    PLAYER_WALK,
    PLAYER_SETTLE,
    PLAYER_JUMP,
    PLAYER_FALL,
    PLAYER_LAND,
    PLAYER_WALL_CLING,
    PLAYER_WALL_JUMP,
    PLAYER_WALL_SLIDE,
    PLAYER_DASH,
    PLAYER_AIR_DASH,
    PLAYER_LADDER_TRANSITION,
    PLAYER_LADDER_UP,
    PLAYER_LADDER_DOWN,
    PLAYER_HURT,
    PLAYER_RIDE,
    PLAYER_CAPSULE,
    PLAYER_SCRIPT_WAIT,
    PLAYER_SCRIPT_WALK,
    PLAYER_SCRIPT_VANISH,
    PLAYER_SCRIPT_JUMP,
    PLAYER_SCRIPT_VICTORY,
    PLAYER_STAGE_CLEAR,
    PLAYER_LADDER_SHOOT = 0x20,
    PLAYER_HOVER,
    PLAYER_NOVA_STRIKE,
    PLAYER_SOUL_BODY,
    PLAYER_SOUL_BODY_CLONE,
    PLAYER_SOUL_BODY_VANISH,
    PLAYER_WEAPON_POSE,
    PLAYER_RISING_FIRE,
    PLAYER_RISING_FIRE_CHARGED,
    PLAYER_ZERO_SABER = 0x30,
    PLAYER_ZERO_JUMP_SLASH,
    PLAYER_ZERO_FALL_SLASH,
    PLAYER_ZERO_LADDER_SLASH,
    PLAYER_ZERO_WALL_SLASH,
    PLAYER_ZERO_RAIJINGEKI,
    PLAYER_ZERO_HYOURETSUZAN,
    PLAYER_ZERO_SPIN_JUMP_SLASH,
    PLAYER_ZERO_SPIN_FALL_SLASH,
    PLAYER_ZERO_RYUENJIN,
    PLAYER_ZERO_RAKUHOUHA,
    PLAYER_ZERO_SHIPPUUGA,
};

enum PlayerInput {
    PLAYER_INPUT_RIGHT = 0x1,
    PLAYER_INPUT_LEFT = 0x2,
    PLAYER_INPUT_UP = 0x4,
    PLAYER_INPUT_DOWN = 0x8,
    PLAYER_INPUT_SHOOT = 0x10,
    PLAYER_INPUT_SPECIAL = 0x20,
    PLAYER_INPUT_GIGA = 0x40,
    PLAYER_INPUT_JUMP = 0x80,
    PLAYER_INPUT_DASH = 0x100,
    PLAYER_INPUT_NEXT_WEAPON = 0x200,
    PLAYER_INPUT_PREVIOUS_WEAPON = 0x400,
};

enum PlayerCollision {
    PLAYER_COLLIDE_RIGHT = 0x1,
    PLAYER_COLLIDE_LEFT = 0x2,
    PLAYER_COLLIDE_CEILING = 0x4,
    PLAYER_COLLIDE_GROUND = 0x8,
};

MMX4_STATIC_ASSERT(animation_step_size, sizeof(union AnimationStep) == sizeof(u32));

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
    u8 pad81[6];
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
    u32 saved_unk5, unk84, unk88;
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
    u8 pad81[6];
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
    u8 pad88[4];
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
    struct BaseObj* unk80;
    u32 unk84;
    u32 unk88;
    u32 unk8C;
    u32 unk90;
    u32 unk94;
};

struct Main76Ext {
    s32 saved_x_velocity;
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
    u8 unk81;
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
    u8 pad8A;
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
    u8 pad80[5];
    u8 unk85;
    u8 unk86;
    u8 unk87;
    u8 unk88;
};

struct Main36Ext {
    u8 pad80[4];
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
    u8 pad89;
    u8 unk8A;
    u8 pad8B[2];
    u8 unk8D;
    u8 unk8E;
};

struct Main72Ext {
    u8 pad80[4];
    s16 unk84;
    u8 pad86;
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

struct Main28InitData {
    u8 unk84;
    u8 unk15;
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

struct MenuRuntimeData {
    struct MemcardSaveSlot save;
#ifdef MMX4_WIN32
    u8 pad2A[6];
#else
    u8 pad2A[2];
#endif
    u8 button_lookup[24];
    u16 low_button_masks[8];
    u16 high_button_masks[3];
    u16 sign_bit_mask;
};

struct Main29Record {
    s8 unk0;
    s8 unk1;
    u8 pad2[2];
    s8 unk4;
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
    u8 pad81;
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
    u8 pad84;
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
    s8 unk5F;                           \
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
    s8 pad51[3];
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
    const u32* unk54;
    void* unk58;
    s8 hp;
    s8 hud_hp;
    s8 unk5E;
    s8 unk5F;
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
    f32 unk90;
    s8 pad94;
    u8 unk95;
    s8 pad96[0x98 - 0x96];
    s8 unk98;
    s8 unk99;
    s8 pad9A[0x9C - 0x9A];
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

struct Weapon60SpawnOffset {
    s16 x;
    s16 y;
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
    s8 pad8A[0x8C - 0x8A];
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

struct Item04Data {
    u16 unk0;
    u16 unk2[6];
    u8 object_ids[50];
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
};

struct Item01StageEntry {
    u16 x;
    u16 y;
    u16 left;
    u16 right;
    u16 trigger_x;
    u16 flags_and_palette;
    u16 velocity;
    u16 sound_id;
};

extern struct Item01StageEntry stage_block_entries[15];

struct Item01SpriteBounds {
    u8 x_offset;
    u8 y_offset;
    u8 width;
    u8 height;
};

extern struct Item01SpriteBounds stage_block_bounds[15];
extern u8 stage_block_debris[16];

union ItemUnk84 {
    u16 timer;
    u32 previous_value;
    u8 bytes[4];
};

union ItemUnk7C {
    u8 value;
    u16 timer16;
    s32 timer;
    struct MainObj* owner;
    struct MiscObj* misc;
    void* object;
    struct Unk_unk68* bounds;
    s32 item_26_value;
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
};

struct LayerObj {
    BASE_OBJ_FIELDS
    f32 unk18;
    union LayerPrivateState private_state;
    s8 pad20[0x24 - 0x20];
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

struct Misc08EffectTripletTable {
    struct Misc08EffectTriplet entries[26];
    u8 padding[2];
};

struct Misc08EffectDescriptor {
    u8 effect_id;
    u8 variant;
};

extern struct Misc08EffectTripletTable crumbling_tile_second_effects;
extern u8 crumbling_tile_debris_0[];
extern u8 crumbling_tile_debris_1[];
extern u8 crumbling_tile_debris_2[];
extern u8 crumbling_tile_debris_3[];
extern u8 crumbling_tile_debris_4[];
extern u8 crumbling_tile_debris_5[];
extern u8 crumbling_tile_debris_6[];
extern u8 crumbling_tile_debris_7[];
extern u8 crumbling_tile_debris_8[];
extern u8 crumbling_tile_debris_9[];
extern u8 crumbling_tile_debris_10[];
extern struct Misc08EffectDescriptor crumbling_tile_first_effects[];
extern u8 D_80104A3C[];
extern void (*sigma_cloak_teleport_funcs[])(struct MainObj*);
void func_80012E18(u8* arg0, u8* arg1);
void spawn_owner_debris(s32 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4, s32 arg5);
void spawn_debris_offset(u8 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4);
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
    u8 pad50[4], animation;
};

struct Misc33Ext {
    s8* completion_flag;
    u16 timer;
};

struct Misc34Ext {
    struct EffectObj* related;
    u8 timer;
    u8 pad55;
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
    u8 pad50[5];
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
};

union MiscExt {
    struct Misc2Ext misc_2;
    struct Misc9Ext misc_9;
    struct Misc5Ext misc_5;
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
    u8 unk16[8]; // size unconfirmed
    s16 : 16;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    s8 : 8;
    s8 : 8;
    u8 unk25;
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
    s8 unk5C;
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
    s8 pad87;
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
ASSERT_RIDE_ARMOR_FIELD(unk5C, hp);
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

struct Unk5 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct Unk9 {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[3];
    u32 unk8;
    u32 unkC;
    u8 padd[1];
    u32 unk14;
    u32 unk18;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    u8 pad33[19];
    s8 unk47;
    s8 unk48;
    s8 unk49;
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
    u16 timer;
    u32 unk4;
    u32 handle;
    u32 unkC;
    u32 stack;
    u32 unk14[12];
    u32 global_pointer;
    u8 pad48[0x80 - 0x48];
};

struct Prim {
    u16 x;
    u16 y;
    s8 uv;
    u8 w;
    u8 h;
    s8 clut;
}; // size 0x8

extern struct PlayerObj g_Player;
extern struct PlayerObj g_Entity;
extern const u32* D_80119DF0[144];
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
extern u8 web_spider_move_timers[];
extern u8 web_spider_attack_cooldowns[4];
extern const u8* web_spider_swing_animations[];
extern s8 breakable_terrain_effect_offsets[];
extern struct Unk_unk68 D_800FF5B0;
extern u16 web_spider_arena_x;
extern u16 web_spider_arena_y;
extern struct Unk_unk68 D_801075F4[];

struct MovingBlockMotion {
    s32 x_velocity;
    s32 y_velocity;
    u16 range;
    u8 vertical;
};
extern struct MovingBlockMotion moving_block_motion[1];

struct Effect1314ItemSpawn {
    u8 reserved;
    u8 id;
    s16 x;
    s16 y;
};
extern struct Effect1314ItemSpawn edge_spawner_items[19];
extern struct Unk_unk68 D_80108584[];
extern u8 rising_platform_debris[2][4];
extern u8 web_spider_swing_sets[];
extern u8 train_boss_turret_hurt_box[];
extern u8 train_boss_turret_attack_box[];
extern struct Unk_unk68 D_80106670[];
extern u8 ride_armor_pilot_hurt_box[];
extern union AnimationStep D_801001F8[];
extern union AnimationStep D_801001FC[];
extern union AnimationStep* spike_crawler_animations[5];
extern void* general_scripts[2];
extern u8 general_script_weights[4];
extern s8 spike_crawler_terrain_box[4];
extern s8 spike_crawler_attack_box[4];
extern s8 spike_crawler_hurt_box[4];
extern struct Unk_unk68 D_80108484[];
extern struct Unk_unk68 D_80100200;
extern struct Unk_unk68 D_80100204;
extern struct Unk_unk68 D_80100210;
extern struct Unk_unk68 D_80100214;
extern struct Unk_unk68 jet_stingray_swim_attack_box;
extern struct Unk_unk68 jet_stingray_swim_hurt_box;
extern u8 ride_armor_pilot_attack_box[];
extern struct Unk_unk68 ride_armor_pilot_punch_box;
extern struct Item04Data destructible_core_data;
extern u8 destructible_core_debris[];
extern s32 destructible_core_explosion_sounds[4];
extern u8 hover_sentry_debris[];
extern struct Unk_unk68 wave_rider_body_hurt_box;
extern struct Unk_unk68 wave_rider_rider_hurt_box[2];
extern u8 wave_rider_debris[8];
extern u8 wave_rider_rider_debris[8];
extern struct Unk_unk68 D_8010024C;
extern u8 D_801005B0[4];
extern u8 shell_crawler_debris[4];
extern u8 bomb_bat_debris[4];
extern u16 D_800FDDA0[14];
extern u8 D_800FDF40[12];
extern struct Unk_unk68* bomb_bat_hurt_boxes[2];
extern u8 train_cannon_debris[8];
extern u8 mushroom_shot_spore_hit_box[4];
extern u8 mushroom_shot_spore_offsets[8];
extern s32 mushroom_shot_spore_x_speeds[4];
extern s32 mushroom_shot_spore_x_accels[4];
extern s16 hatch_blast_tile_x[4];
extern u8 hatch_blast_debris[8];
extern u8 hatch_blast_break_debris[16];
extern struct Unk_unk68 D_80106270[32];
extern u8 breakable_boulder_hit_box[4];
extern u8* breakable_boulder_debris[4];
extern union AnimationStep* D_8010DF48[57];
extern s32 rubble_x_offsets[8];
extern s32 rubble_y_offsets[8];
extern struct BgDrawRelated D_8015D9D0[];
extern struct MainPrimitiveBuffer temp1[];
extern struct SecondaryPrimitiveBuffer temp2[];
extern struct BackgroundPrimitiveBuffer temp3[];
extern struct OrderingTableBuffer temp4[];
extern struct AuxiliaryPrimitiveBuffer temp5[];
extern TILE D_80169D78[2];
extern struct FadeState D_8016DEA0;
extern DR_TPAGE D_8012F498[2];
extern TILE D_8013B7B0[2];
extern POLY_FT4 D_80139F20[2];
extern POLY_F4 D_80139F70[2];
extern DR_TPAGE D_80139FA0[2];
extern POLY_F4 D_80139FB0[2][128];
extern DR_TPAGE D_80171EB0[2][6][8];
extern u8 D_80141BE8[];
extern u16 D_801441C8[3][32][32];

#ifndef MMX4_PC
typedef u32 OT_TYPE;
#endif

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

struct QuadMotionData {
    u16 vertex[4];
    s8 speed[4];
};

extern struct QuadMotionData boss_warning_quad_motions[22];
extern u8 D_8013B960[0x10];

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
    u8 history[3];
};

struct PlayerUnk8CFields {
    s8 unk8C;
    u8 unk8D;
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

union EngineCharacterState {
    s8 bytes[0x10];
    struct {
        s8 active;
        s8 flags;
        s8 selected_characters;
        s8 previous_character;
        s8 secret_code_phase;
        s8 secret_code_index;
        s32 menu_state;
        u8 reserved[6];
    } __attribute__((packed)) fields;
};

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
    s8 unk1C;
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
    s8 unk44;
    u8 unk45;
    s8 unk46;
    s8 unk47;
    s8 unk48;
    s8 player_initial_data[0x10]; // 0x49
    s8 palette_flags; // 0x59
    u16 unk5A;
    s8 unk5C[3];
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

struct Effect16Coordinate {
    u16 primary;
    u16 secondary;
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
    u8 pad1A;
    u8 unk1B;
    u8 palette_index;
    u8 finished;
};

struct Effect37Ext {
    u8 pad14[4];
    u8 timer;
    u8 unk19;
    u8 pad1A[2];
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

extern struct Effect21SpawnRecord* crumble_sequencer_sequences[20];

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

struct Unk22 {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    u8 pad[0x28];
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

struct Unk23 {
    s8 pad[0xc];
    s8 unkC;
    s8 unkD;
    s8 pad2[0xf];
    s8 unk1D;
};

struct Unk24 {
    s8 pad[2];
    s8 unk2;
    s8 pad2[0x3d];
    s8 unk40;
};

struct OffsetInfo {
    u16 x_offset;
    u8 pad2[2];
    u16 y_offset;
    u8 pad[77];
};

struct RectPtrPair {
    RECT rect;
    u_long* ptr;
};

extern struct QuadObj g_QuadObjects[0x20];
extern struct ArchivePathData D_800EE54C;
extern u8 player_leap_fall_animations[];
extern u8 player_jump_voices[][4];
extern u8 frost_walrus_script_recover_high[4];
extern u8 frost_walrus_script_recover_low[4];
extern u16 frost_walrus_floor_tiles[18];
extern u16 frost_walrus_floor_tiles_rush[20];
extern s16 frost_walrus_burst_offsets[20][2];
extern u8 frost_walrus_burst_subtypes[20];
extern void* jet_stingray_animations[45];
extern void* cyber_peacock_animations[38];
extern struct Unk_unk68 player_x_collision_bounds;
extern struct Unk_unk68 player_zero_collision_bounds;
extern struct Unk_unk68 D_800F9124;
extern s8 player_shot_has_pose[];
extern s8 player_shot_is_special_weapon[];
extern s8 player_shot_is_charged_special[];
struct PlayerShotTiming {
    u8 pose_time;
    u8 cooldown;
};
extern struct PlayerShotTiming player_shot_timings[];
extern s8 player_shot_limits[];
extern s8 player_shot_waits_for_specials[];
extern s8 player_shot_counts_as_shot[];
extern s8 player_shot_counts_as_special[];
extern u8 player_ladder_shoot_animations[];
extern struct VisualAttachmentOffset wall_slide_dust_offsets[2];
extern struct VisualAttachmentOffset dash_dust_offsets[2];
extern struct VisualAttachmentInit charge_muzzle_flash_types[4];
extern u8 dragon_shot_flame_box[4];
extern u8 dragon_shot_flame_hit_box[4];
extern u8 dragon_shot_pulse_hit_box[4];
extern u8 dragon_shot_pulse_box[4];
extern u8 dragon_shot_burn_box[4];
extern u8 small_effect_animations[];
struct Visual03Bounds {
    s32 x;
    s32 y;
};
extern struct Visual03Bounds small_effect_bounds[];

extern u16 buster_muzzle_offsets[48];

struct PlayerFrameOffset {
    s8 x;
    s8 y;
};
union PlayerFrameOffsetData {
    struct PlayerFrameOffset offsets[256];
    s8 components[512];
};
extern union PlayerFrameOffsetData D_8011B230;
extern u32* explosion_animations[3];
extern u8 ride_dust_animations[];
extern u8 ride_dust_layers[];
extern u16 weapon_overlay_palettes[];
extern u8 weapon_overlay_layers[4];
extern u8 weapon_overlay_animations[4];
extern s16 weapon_overlay_gfx_rows[4];
extern struct VisualBounds weapon_overlay_bounds[4];
extern u8 wave_rider_jet_animations[];
extern u16** camera_trigger_stage_scripts[26];
extern u32* briefing_x_partner_animations[];
extern u32* briefing_x_animations[];
extern u32* briefing_zero_animations[];
extern u32* briefing_zero_partner_animations[];
extern u32* option_toggle_animations[];
extern s8 sigma_beam_sweep_speeds[];
extern u8 sigma_laser_flash_colors[];
extern s16 train_scroll_lock_positions[4];
extern s32* web_piece_quad_frame_table[8];
extern u8 D_801193F0[];
extern u32 D_801194F0[];
extern u8 D_8011A030[];
extern u8 D_8011A130[];
extern u32 D_8011A230[];
extern u8 D_8011AF60[];
extern const u32* D_8011AFF0[];
extern u32* D_8011BF40[];
extern u32* D_8011C070[9];
extern u32* D_8011C094[7];
extern u32* D_8011C0E4[3];
extern union AnimationStep* train_cannon_animations[21];
extern union AnimationStep* train_crate_animations[10];
extern union AnimationStep* latcher_animations[7];
extern union AnimationStep* intro_messenger_animations[3];
extern union AnimationStep* web_spider_animations[40];
extern struct Unk_unk68 web_spider_attack_box;
extern struct Unk_unk68 web_spider_hurt_box;
extern void* beam_drone_animations[12];
extern void* storm_owl_animations[30];
extern void* gunship_animations[29];
extern struct Unk5 D_800F0E18[];
extern struct Unk_unk68 jet_stingray_land_attack_box;
extern struct Unk_unk68 jet_stingray_land_hurt_box;
extern struct Unk_unk68 jet_stingray_terrain_box;
extern struct Unk_unk68 D_801072F4[];
extern union AnimationStep* spike_sled_animations[23];
extern struct Unk_unk68 D_800FDD88;
extern struct Unk_unk68 D_800FDD8C;
extern u8 ride_armor_missile_hit_box[4];
extern struct Weapon60SpawnOffset ride_armor_missile_offsets[3];
extern s32 D_80137CC0;
extern s8 D_80141A07;
extern s8 D_80141A5B;
extern struct DrawInfo* cur_draw_info;
extern struct EngineObj engine_obj;
extern s8 D_801307F8;
extern struct EffectObj* boss_warning_tiles[22];
extern u8* tile_flicker_scripts[2];
extern struct Effect28AnimationStep* tile_anim_scripts[3];
extern s16 rock_drop_sequence_delays[10];
extern u8 rock_drop_sequence_subtypes[12];
extern s16 rock_drop_sequence_x_positions[10];
extern u8* tile_strip_anim_scripts[2];
extern u8* tile_loop_anim_scripts[2];
extern u8* tile_blink_anim_scripts[1];
extern u8 layout_width;
extern u16 layout_size;
extern void (*engine_update_funcs[])(struct EngineObj*);
extern u8 D_80171EA8;
struct MemcardPath {
    char path[6];
};

extern const struct MemcardPath D_800100C0;

struct MemcardFileList {
    char names[15][22];
    u8 count; // 0x14A
    s8 pad14B;
    s32 total_size; // 0x14C
    s32 sizes[15]; // 0x150
};

extern u8 D_80173AE0[0x14A];
extern u8 D_80173C2A;
extern s32 D_80173C2C;
#define D_80173AE0_LIST ((struct MemcardFileList*)D_80173AE0)

extern u8 D_800F2180[];
extern u8 D_800F21A0[];
extern s16 D_800F21DC[];
extern u8 D_800F21F8[];
extern u8 D_800F22D0[];
extern u8 D_800F22E0[];
extern u8 D_800F22F0[16];
extern u8 D_800F2300[];
extern u8 D_800F2310[12];
extern u8 D_800F231C[12];
extern u8 D_800F2328[16];
struct GameInfoAuxData {
    u8 scripts[3][16];
    u32 lookup[8];
};
extern struct GameInfoAuxData D_800F2338;
extern RECT D_800F2388;
extern RECT D_800F2428;
extern RECT D_800F2430;
extern u8 D_800F2468[];
#ifdef VERSION_JP
extern u8 D_800F2474_jp[4];
#endif
extern u8 D_800F247C[];
extern u8 D_800F2490[];
extern struct BackgroundCameraModePair D_800F32D4[16][2];
extern u16 D_80106770[64];
extern struct Unk_unk68 D_801068F0[33];
extern s32 robot_bee_approach_speeds[2];
extern s32 robot_bee_charge_speeds[2];
extern s32 robot_bee_sting_speeds[2];
extern s32 ice_bird_fly_speeds[2];
extern s32 robot_bee_lunge_speeds[2];
extern u8 ambush_gunner_emerge_particles[8];
extern u32 D_800FA72C;
extern u32 D_800FA730;
extern u8 dragonfly_body_boxes[8];
extern u8 dragonfly_grab_box[4];
extern struct Unk_unk68 heavy_mech_hurt_box;
extern struct Unk_unk68 heavy_mech_attack_box;
extern struct Unk_unk68 heavy_mech_terrain_box;
extern union AnimationStep* heavy_mech_animations[18];
extern struct Unk_unk68 trident_mech_hurt_box;
extern struct Unk_unk68 trident_mech_attack_box;
extern struct Unk_unk68 trident_mech_charge_attack_box;
extern struct Unk_unk68 shell_crawler_body_box;
extern struct Unk_unk68 shell_crawler_shell_box;
extern struct Unk_unk68 D_800FBEF4;
extern struct Unk_unk68 D_800FBEF8;
extern u8 D_800FC340[4];
extern struct Unk_unk68 D_800FBEFC;
extern struct Unk_unk68 snowman_bomb_hurt_box;
extern struct Unk_unk68 snowman_bomb_attack_box;
extern struct Unk_unk68 snowman_bomb_terrain_box;
extern union AnimationStep* snowman_bomb_animations[];
extern struct Unk_unk68 snowman_bomb_blast_hurt_box;
extern struct Unk_unk68 snowman_bomb_blast_attack_box;
extern struct Unk_unk68 snowman_bomb_blast_terrain_box;
extern u8 snowman_bomb_debris[4];
extern s32 D_800F9070[2];
extern s32 D_800F9078[2];
extern s32 D_800F9080[2];
extern s32 D_800F9088[2];
extern s32 D_800F9090[2];
extern s32 D_800F9098[2];
extern u16 D_800FBEDC[12];
extern struct Unk_unk68 D_800FBF00;
extern struct Unk_unk68 D_800FBF04;
extern struct Unk_unk68 D_800FBF0C;
extern struct Unk_unk68 D_800FBF10;
extern struct Unk_unk68 ice_block_crumble_attack_box;
extern struct Unk_unk68* surface_hopper_launch_hurt_boxes[4];
extern struct Unk_unk68* surface_hopper_launch_attack_boxes[4];
extern struct Unk_unk68* surface_hopper_launch_terrain_boxes[4];
extern s16 surface_hopper_launch_x_speeds[8];
extern s16 surface_hopper_launch_y_speeds[8];
extern u8 surface_hopper_launch_facings[8];
extern u8 surface_hopper_launch_animations[8];
extern u8 slope_skier_debris[];
extern u8 regen_turret_debris[];
extern void (*regen_turret_rebuild_funcs[])(struct MainObj*);
extern struct Unk_unk68 thorn_trap_open_hurt_box[];
extern struct Unk_unk68 bomb_bat_body_box;
extern s32 bomb_bat_fly_speeds[2];
extern struct Unk_unk68 highway_trooper_terrain_box;
extern u16 highway_trooper_stop_x[];
extern void (*highway_trooper_step_funcs[])(struct MainObj*);
extern struct Unk_unk68 wheel_charger_open_hurt_box;
extern struct Unk_unk68 wheel_charger_open_attack_box;
extern union AnimationStep* data_hopper_animations[19];
extern struct Unk_unk68 data_hopper_terrain_box;
extern struct Unk_unk68 data_hopper_attack_box;
extern struct Unk_unk68 D_80103F08;
extern struct Unk_unk68 D_80103F0C;
extern s8 player_hover_bob[16];
extern struct Unk_unk68 ground_hunter_crawl_box[];
extern struct Unk_unk68 ground_hunter_rise_box[];
extern u8 ice_wall_debris[];
extern void (*ice_wall_break_funcs[])(struct BaseObj*);
extern void (*pod_spawner_step_funcs[])(struct MainObj*);
extern struct Unk_unk68 ice_bird_body_box;
extern union AnimationStep* ice_bird_animations[];
extern struct Unk_unk68 D_80106974[];
extern union AnimationStep* falling_icicle_animations[];
extern struct Unk_unk68 falling_icicle_body_box;
extern struct Unk_unk68 falling_icicle_terrain_box;
extern struct Unk_unk68* surface_hopper_attach_terrain_boxes[2];
extern u8 jet_drone_debris[];
extern union AnimationStep* spawner_pod_animations[];
extern struct Main28InitData spawner_pod_init_data[];
extern struct Unk_unk68 D_80106AF4[];
extern struct Unk_unk68 D_80107074[];
extern struct Unk_unk68 D_80108504[];
extern struct Unk_unk68 frost_tower_charged_part_box[];
extern struct Unk_unk68 soul_body_hit_box[];
extern struct Unk_unk68 ice_bird_charge_box;
extern struct Unk_unk68 D_80106B74[];
extern struct Unk_unk68 dragonfly_terrain_box;
extern u8 boss_voice_tracks[13][3];
extern union AnimationStep D_80105FF0[32];
extern struct Unk_unk68 D_80103EE4;
extern struct Unk_unk68 D_80103EF0;
extern struct Unk_unk68 D_80103EF4;
extern struct Unk_unk68 D_80103EE8;
extern struct Unk_unk68 D_80103F00;
extern struct Unk_unk68 D_80103F04;
extern struct Unk_unk68 D_80104504;
extern struct Unk_unk68 D_80104508;
extern struct Unk_unk68 D_8010450C;
extern struct Unk_unk68 D_80104510;
extern struct Unk_unk68 D_80108084[];
extern struct Unk_unk68 D_80108104[];
extern struct Unk_unk68 D_801049AC;
extern void* unused_ride_armor_animations[];
extern struct Unk_unk68 unused_ride_armor_hit_box;
extern struct Unk_unk68 unused_ride_armor_terrain_box;
extern struct Unk_unk68 D_80108184[];
extern u8 sigma_scythe_plant_next[4];
extern u8 sigma_cloak_pattern[4];
extern struct Unk_unk68 gunship_debris[];
extern struct Unk_unk68 D_801074F4[];
extern struct Unk_unk68 D_80107778[];
extern struct Unk_unk68 D_80107E84[];
extern struct Unk_unk68 D_80107F04[];
extern struct Unk_unk68 frost_tower_terrain_box[];
extern struct Unk_unk68 D_80105374;
extern struct Unk_unk68 D_801044FC;
extern struct Unk_unk68 D_80104500;
extern struct Unk_unk68 D_80105360;
extern struct Unk_unk68 D_80105364;
extern struct Unk_unk68 D_8010535C;
extern struct Unk_unk68 D_80105368;
extern struct Unk_unk68 D_8010536C;
extern struct Unk_unk68 D_80105370;
extern u8 sigma_final_laser_animations[8];
extern u16 D_80106070[64];
extern struct Unk_unk68 D_801060F0[32];
extern struct Unk_unk68 D_80107DFC[];
extern struct Unk_unk68 D_801079F8[];
extern struct Unk_unk68 D_80107A78[];
extern struct Unk_unk68 D_80107B78[];
extern struct Unk_unk68 frost_walrus_breath_debris[3];
extern s32 split_mushroom_walk_speeds[3];
extern struct Unk_unk68 split_mushroom_terrain_box;
extern struct Unk_unk68 storm_owl_attack_box;
extern struct Unk_unk68 storm_owl_slam_terrain_box;
extern struct Unk_unk68 cyber_peacock_hit_box;
extern struct Unk_unk68 cyber_peacock_rising_kick_attack_box;
extern struct Unk_unk68 cyber_peacock_rising_kick_hurt_box;
extern struct Unk_unk68 cyber_peacock_slash_attack_box;
extern struct Unk_unk68 cyber_peacock_slash_hurt_box;
extern struct Unk_unk68 cyber_peacock_slash_swing_attack_box;
extern struct Unk_unk68 cyber_peacock_slash_swing_hurt_box;
extern struct Unk_unk68 nova_strike_hit_box[];
extern struct Unk_unk68 magma_dragoon_terrain_box;
extern struct Unk_unk68 magma_dragoon_hurt_box;
extern struct Unk_unk68 magma_dragoon_crouch_hurt_box;
extern struct Unk_unk68 magma_dragoon_attack_box;
extern struct Unk_unk68 magma_dragoon_leap_attack_box;
extern struct Unk_unk68 magma_dragoon_punch_attack_box;
extern struct Unk_unk68 frost_walrus_hurt_box;
extern struct Unk_unk68 frost_walrus_charge_hurt_box;
extern struct Unk_unk68 frost_walrus_attack_box;
extern struct Unk_unk68 frost_walrus_charge_attack_box;
extern u16 D_80106470[];
extern struct Unk_unk68 spike_marl_walk_attack_box;
extern struct Unk_unk68 spike_marl_walk_hurt_box;
extern struct Unk_unk68 spike_marl_curl_attack_box;
extern struct Unk_unk68 spike_marl_curl_hurt_box;
extern struct Unk_unk68 D_801061F0[32];
extern struct Unk_unk68 D_801069F4[];
extern struct Unk_unk68 lightning_web_charged_part_box[];
extern struct Unk_unk68 D_80108004[];
extern struct Unk_unk68 jet_stingray_debris[2];
extern struct Unk_unk68 double_attack_box;
extern struct Unk_unk68 double_hurt_box;
extern struct Unk_unk68 D_801049B0[2];
extern u8 surface_hopper_appear_animations[4];
extern s8 train_boss_terrain_box[4];
extern u8 train_boss_attack_timers[20];
extern union AnimationStep* train_boss_animations[];
extern struct Unk_unk68 D_80107678[];
extern struct Unk_unk68 jet_stingray_dash_attack_box;
extern struct Unk_unk68 jet_stingray_dash_hurt_box;
extern struct Unk_unk68 flame_jet_hurt_box_7;
extern struct Unk_unk68 flame_jet_vent_box;
extern struct Unk_unk68* flame_jet_hurt_boxes[9];
extern struct Unk_unk68* flame_jet_attack_boxes[9];
extern struct Unk_unk68 magma_dragoon_fire_volley_debris;
extern struct Unk_unk68 double_dive_attack_box;
extern struct Unk_unk68 double_dive_hurt_box;
extern u8 ride_armor_punch_hit_boxes[][4];
extern u8 ride_armor_punch_animations[8];
extern u8 ride_armor_punch_steps[8];
extern u8 crusher_wall_terrain_box[4];
extern u16 crusher_wall_x_positions[4];
extern u8 wheel_charger_debris[8];
extern u8 rocket_spiker_exhaust_variants[12];
extern struct Unk_unk68 train_cannon_hurt_box;
extern struct Unk_unk68 train_cannon_attack_box;
extern struct Unk_unk68 train_cannon_terrain_box;
extern struct Unk_unk68 anchored_mine_hurt_box;
extern struct Unk_unk68 anchored_mine_attack_box;
extern struct Unk_unk68 D_800FFC54;
extern struct Unk_unk68 D_800FFC58;
extern struct Unk_unk68 D_800FFC5C;
extern union AnimationStep* anchored_mine_animations[2];
extern u8** slash_beast_patterns[3];
extern u8 slash_beast_pattern_weights[12];
extern union AnimationStep* fortress_cannon_animations[14];
extern u8 web_thread_hit_box[4];
extern u8 web_thread_collision[32][4];
extern u8 train_boss_bullet_hit_box[4];
extern u8 train_boss_arm_attack_box[4];
extern u8 train_boss_arm_hurt_boxes[2][4];
extern u16 train_boss_arm_debris_positions[3][2];
extern u8 train_boss_arm_debris[8];
extern struct Unk_unk68 hatch_blast_terrain_box;
extern u8 double_ball_box_5[2][4];
extern u8 tile_anim_trigger_offsets[4][2];
extern s16 tile_loop_anim_offsets[2][2];
extern u16 palette_pulse_palette[16];
extern u8 breakable_wall_debris[8];
extern s16 gate_core_exit_x[2];
extern s16 bg_zone_controller_zone_bounds[4];
extern u8 ride_chaser_ram_hit_box[];
extern struct Unk_unk68 lemon_hit_box[];
extern struct Unk_unk68 stock_shot_hit_box[];
extern struct Unk_unk68 lightning_web_charged_shot_box[];
extern struct Unk_unk68 lightning_web_shot_box[];
extern struct Unk_unk68 lightning_web_charged_net_box[];
extern struct Unk_unk68 lightning_web_net_box[];
extern struct Unk_unk68 lightning_web_terrain_box[];
extern struct Unk_unk68 aiming_laser_marker_box[];
extern struct Unk_unk68 twin_slasher_hit_boxes[];
extern struct Unk_unk68 zero_saber_hit_boxes[];
extern u8 frost_sparkle_animations[];
extern u32* D_8011C018[22];
extern s16 train_boss_arm_offsets[3][2];
extern s16 drone_beam_boxes[4][2];
extern s16 train_boss_arm_reach[4];
extern u8 train_boss_arm_extended_clear_masks[4];
extern u8 double_ball_box_2[4];
extern u8 double_ball_box_3[4];
extern u8 double_ball_box_4[2][4];
extern u8 train_boss_arm_extended_bits[4];
extern u8 train_boss_arm_active_clear_masks[4];
extern struct Unk_unk68 walrus_ice_shard_terrain_box;
extern struct Unk_unk68 walrus_ice_ball_hurt_box;
extern u8 trap_floor_terrain_box[4];
extern u8 teleporter_terrain_box[4];
extern struct Unk_unk68 gunship_hurt_box;
extern struct Unk_unk68 gunship_terrain_box;
struct Misc25Velocity {
    s8 x;
    s8 y;
};
extern struct Misc25Velocity sentry_flash_offsets[8];
void func_8007C090(struct WeaponObj* weapon);
extern s16 sigma_laser_sweep_offsets[14][2];
extern s16 sigma_laser_end_offsets[8][2];
extern struct Unk_unk68 walrus_ice_ball_attack_box;

extern struct Unk_unk68 walrus_ice_ball_attack_box;
extern struct Unk_unk68 walrus_ice_shard_hurt_box;
extern struct Unk_unk68 walrus_ice_shard_attack_box;
extern u8 walrus_ice_debris[12];
extern RECT** walrus_ice_drop_patterns_a;
extern RECT** walrus_ice_drop_patterns_b;
extern u8 hatch_blast_hit_box[4];
extern u8 peacock_missile_explosion_box[4];
extern u8 iris_drone_explode_box[4];
extern u8 iris_laser_box[4];
extern u8 iris_pillar_box[4];
extern u8 sigma_spike_box[4];
extern struct ObjectHeader* D_8013B8A8;
extern u16 D_8013B858[0x10];
extern s16 D_8013B878[0x10];
extern struct Unk_unk68* D_8013B8B0;
extern u8 D_8013B8B8[8];
extern struct ShotObj* general_fists[2];
extern u8 rising_slab_crush_boxes[4][16];
extern u8 rising_slab_terrain_boxes[4][16];
extern struct Unk_unk68 sliding_floor_terrain_box;
extern struct Unk_unk68 light_capsule_platform_box;
extern struct FixedMatrix2 D_800F2ADC[16];
extern s32 D_800EE458;
extern void (*D_8012F490)(void);
extern s8 D_80173C6C[4];
extern u8 D_80137DFC;
extern u8 D_80137DFD;
extern struct SoundTransfer D_80137E00;
extern u8 D_80137DDC;
extern s32 D_8013BD44;
extern u8 D_8013BD40;
extern s16 D_80141BD2;
extern struct BackgroundLayoutConfigData D_800F3188;
extern const u8* s_StageMainIds[13][2];
extern struct StageObjectRecord* D_800F4430[13][2];
extern struct StageObjectRecord* D_800F43C8[13][2];
extern u8* D_8010FFDC[][2];
extern u8 layout_height;
extern u8 dragonfly_debris[8];
extern u8 player_death_orb_directions[4][8];
extern u8 spawner_pod_debris[];
extern void (*dragonfly_step_funcs[])();
#ifdef MMX4_PC
#define D_8010B465 (((u8*)search_light_spawners)[1])
#else
extern u8 D_8010B465;
#endif
extern u8 x_ready_text_flags[];
extern u8* const* D_800F2DD8[];
extern const u8* D_800F2DD0[];
extern u16 D_800F2F40[16];
extern const u32* const* D_800F2EE8[];
extern const u32* const* D_800F2F00[];
extern s16 D_800F2FDC[2];
extern struct MiscObj* D_801397BC;
extern struct MiscObj* D_801397C0;
extern struct MiscObj* D_801397C4;
extern struct MiscObj* D_801397C8;
extern struct MiscObj* D_801397CC;
extern struct MiscObj* D_801397D0;
extern struct MiscObj* D_801397D4;
extern u8 D_801397D8;
extern struct Func80022730Config* D_801397DC;
extern s16 D_801397E0;
extern u16 D_801397E4[0x20];
extern u8 D_80139824;
extern u8 D_80139828;
#ifdef MMX4_PC
extern char D_80137E0C[SS_SEQ_TABSIZ * 3 * 10];
#else
extern char D_80137E0C[0x1428];
#endif
extern s8 D_80139234[24];
extern u8 D_8013924C[4];
extern void* D_8013DC10;
extern void* D_8013DC14;
extern void* D_8013DC18;
extern void* D_8013DC1C;
extern void* D_8013DC20;
extern void* D_8013DC24;
extern void* D_8013DC28;
extern void* D_8013DC2C;
extern void* D_8013DC30;
extern void* D_8013DC34;
extern void* D_8013DC38;
extern void* D_8013DC3C;
extern void* D_8013DC40;
extern void* D_8013DC44;
extern void* D_8013DC48;
extern void* D_8013DC4C;
extern void* D_8013DC54;
extern void* D_8013DC58;
extern void* D_8013DC5C;
extern void* D_8013DC60;
extern void* D_8013DC64;
extern void* D_8013DC68;
extern void* D_8013DC6C;
extern void* D_8013DC70;
extern void* D_8013DC74;
extern void* D_8013DC78;
extern void* D_8013DC7C;
extern void* D_8013DC80;
extern void* D_8013DC84;
extern void* D_8013DC88;
extern void* D_8013DC8C;
extern void* D_8013DC90;
extern void* D_8013DC94;
extern void* D_8013DC98;
extern void* D_8013DC9C;
extern void* D_8013DCA0;
extern s8 D_8013E198[6];
extern s8 D_8013E1C4;
extern s8 D_8013E1C8[4];
extern s32 D_801395E4;
extern s32 D_801395E8;
extern volatile s32 D_80139634;
extern struct ObjectHeader* D_80139690;
extern void (*D_800F43A8[1])(s32);
extern void (*g_TitleScalingXUpdateFuncs[])();
extern void (*search_light_maker_state_funcs[])();
extern void (*teleport_intro_state_funcs[])();
extern s8 D_801F6018;
extern s8 D_801F6019;
extern s8 D_801F604F;
extern s32 D_80139514;
extern u8 D_80139554[];
extern s8 D_80139568;
extern s16 D_8013955C;
extern u8 D_80173C84;
extern s32 D_80175EE8[];
#ifdef MMX4_PC
#define D_8016DEA2 (D_8016DEA0.unk2)
#define D_8016DEA4 (D_8016DEA0.unk4)
#else
extern s16 D_8016DEA2;
extern s16 D_8016DEA4;
#endif
extern struct GameThread* D_801F8300;
extern void (*g_MegamanInBriefingRoomUpdateFuncs[2])();
extern void (*g_TitleUpdateFuncs[])();
extern void (*select_char_portrait_funcs[4])();
extern void (*g_SelectACharacterUpdateFuncs[3])();
extern struct MainObj main_objects[0x30]; // D_8013BED0
extern void (*g_SearchLightUpdateFuncs[3])(struct QuadObj*);
extern void (*ready_line_state_funcs[])();
extern void (*g_TitleUpdate2Funcs[])();
extern u8 D_8013B7D0;
extern u8 D_8013B7D8;
extern u8 D_8013B7DC;
extern s16 D_8013B7E0;
extern s16 D_8013B7E4;
extern s16 D_8013B7E8;
extern s16 D_8013B7EC;
extern s16 D_8013B7F0;
extern s16 D_8013B7F4;
extern s16 D_8013B7F8;
extern s16 D_8013B7FC;
extern s16 D_8013B800;
extern s16 D_8013B804;
extern struct MiscObj* D_8013B808;
extern u8* D_8013B80C;
extern s16 magma_dragoon_arena_center[2];
extern s16 magma_dragoon_arena_floor[2];
extern s16 magma_dragoon_arena_ceiling[4];
extern s8 D_8013B810;
extern u8 D_8013B814;
extern u8 D_8013B8A0[];
extern struct EffectObj* sigma_sequencer;
extern struct AbcObj abc_object;
extern struct BarObj bar_object;
extern struct BazObj baz_objects[2];
extern struct VisualObj visual_objects[0x20];
extern struct ShotObj shot_objects[0x20];
extern struct WeaponObj weapon_objects[0x10];
#ifdef MMX4_WIN32
#define UNK_OBJECT_COUNT 30
#else
#define UNK_OBJECT_COUNT 0x14
#endif
extern struct UnkObj unk_objects[UNK_OBJECT_COUNT];
extern struct UnkObj foo_objects[3];
extern struct EffectObj effect_objects[0x20];
extern struct ItemObj item_objects[0x20];
extern struct MiscObj misc_objects[0x40];
extern const u8* dragonfly_animations[12];
extern struct LayerObj layer_objects[4];
extern struct RideArmorObj qux_object;
extern struct GameInfo game_info;
extern void (*D_800F485C[1])();
extern void (*ReadyTextUpdateFuncs[3])();
extern u8* D_80137DC4;
extern s32 D_80137DD0;
extern u32* D_801406A8;
extern struct SearchLightInit search_light_shapes[6];
extern s32 search_light_speeds[3];
extern struct SearchLightColorLookup search_light_colors;
extern struct SearchLightIntensityLookup search_light_blend_modes;
extern u32* select_char_x_animations[7];
extern u32* select_char_zero_animations[6];
extern u32* select_char_menu_animations[10];
extern u8 select_char_initial_animations[16];
extern u8 select_char_palettes[16];
extern u8 select_char_priorities[16];
extern struct CharacterSelectPosition select_char_positions[9];
extern struct CharacterSelectPosition select_char_text_positions[3];
extern u8 D_801406AC;
extern u8* D_8015D9C8;
extern u8 D_800EE47E[];
extern u32 D_80141F38;
extern union AnimationStep D_800F8DC8[];
extern struct Unk_unk68 armored_walker_terrain_box;
extern struct Unk_unk68 armored_walker_hit_box;
extern union AnimationStep* armored_walker_animations[];
extern struct Unk_unk68 D_80106370[];
extern struct Unk_unk68 thorn_trap_attack_box[];
extern struct Unk_unk68 thorn_trap_strike_boxes[];
extern struct Unk_unk68 D_800FD9F8[];
extern struct Unk_unk68 D_800FD9FC[];
extern struct Unk_unk68 D_800FDA00[];
extern struct Unk_unk68 D_800FDA04[];
extern struct Unk_unk68 D_800FDA08[];
extern struct Unk_unk68 D_80100220;
extern struct Unk_unk68 D_80100224;
extern struct Unk_unk68 D_80100208;
extern struct Unk_unk68 D_8010020C;
extern struct Unk_unk68 D_801059D8;
extern struct Unk_unk68 D_801059DC;
extern u8 D_801374B4;
extern u8 D_801374B8;
extern s8 D_80137CE4;
extern u8 D_80137CF0;
extern u8 D_80137CF4;
extern u8 D_8013BD40;
#ifdef MMX4_PC
extern struct BootTransitionDataRegion g_BootTransitionDataRegion;
#define D_800F1C0F (g_BootTransitionDataRegion.stage_map)
#else
extern u8 D_800F1C0F[];
#endif
extern u32 D_800F1D8C;
extern struct MenuRuntimeData D_800F1D90;
extern CdlATV D_80139644;
extern u8 D_80171EA9;
extern u8 D_80166D68;
extern u8 D_8012F46C[0x22];
extern u16 D_800EE430[];
extern RECT D_800EE450;
extern u16 cur_random;
extern s32 D_8013BD44;
extern s16 D_80141BD2;
extern u8 D_80139528;
extern CdlATV D_80139520;
extern s32 D_80137CD8;
extern RECT D_800F1658;
extern u16 D_80141F70[0x800];
extern u16 lastFilterAmountR, lastFilterAmountG, lastFilterAmountB;
extern u8 D_80139524;
extern s8 D_8013952C;
extern s32 D_80139530;
extern s32 D_80139564;
extern s8 D_8013956C;
extern s32 D_801419AC;
extern s8 D_80141BD0;
extern s32 D_80141BD4;
extern s8 D_80141F4A;
extern u8 D_801441B0;
extern u16* D_801441B4;
extern u8 D_801441B8;
extern u8* D_80137CC4;
extern s32 D_80137CCC;
extern u8 D_80137CE8;
extern s32 D_80137CEC;
extern CdlLOC D_80137CF8;
extern DISPENV old_dispenv[2];
extern s8 D_80166C20;
extern s8 D_80166C21;
extern s8 D_80166CC0;
extern s8 D_80166CC1;
extern s32 D_80137CBC;
extern s32 D_80137CEC;
extern s32 D_80139670;
extern s32 D_80139674;
extern s32 D_80139678;
extern s32 D_8013967C;
extern s32 D_80139680;
extern s32 D_80139684;
extern s32 D_80139688;
extern u8 D_800F1E90[];
extern u8 D_800F1EAC[];
extern u8 armored_walker_debris[8];
extern u8* D_80173C80;
extern u8 D_80173C84;
extern void (*select_char_subtype_funcs[16])();
extern void (*select_char_scroll_text_funcs[])();
extern void (*select_char_selector_funcs[])();
extern u8 need_palette_load;
extern void (*select_char_character_funcs[])();
extern s8 D_801721F7;
extern void (*ready_line_type_funcs[])();
extern struct Unk14* color_filter_scripts[];
extern s32 color_filter_masks[][4];
extern s32 D_8013E188[4];
extern struct Unk_unk68 unused_ride_armor_debris[2];
extern void (*unused_ride_armor_step_funcs[])(struct MainObj*);
// extern s32 D_8013E18C;
// extern s32 D_8013E190;
// extern s32 D_8013E194;
extern s8 D_801754A0;
// 0 is color add mode, 1 is color subtract mode
extern u8 g_FilterModeR;
extern u8 g_FilterModeG;
extern u8 g_FilterModeB;
// how much to add or subtract to each channel
extern u16 g_FilterAmountR;
extern u16 g_FilterAmountB;
extern u16 g_FilterAmountG;
extern u8 D_800F4508[];
extern u8* D_800F4560[];
extern u8 D_800F4568[];
extern u8 D_800F457C[];
extern u8* D_800F4834[10];
extern u16 D_800F312C[];
extern void (*D_800F3134[])(struct BackgroundObj* arg0);
extern struct Prim D_800EE504[];
extern struct RectPtrPair vram_rect_ptrs[];
extern struct RectPtrPair* vram_rect_ptr;
extern u8 D_800F30D4[16][2];
enum XaArchive {
#ifdef VERSION_JP
    XA_ARCHIVE_BGM1 = 0x94,
#else
    XA_ARCHIVE_BGM1 = 0x95,
#endif
    XA_ARCHIVE_BGM2,
    XA_ARCHIVE_BGM3,
    XA_ARCHIVE_BGM4,
    XA_ARCHIVE_BGM5,
    XA_ARCHIVE_BOSS_INTRO,
    XA_ARCHIVE_VOICE1,
    XA_ARCHIVE_VOICE2,
    XA_ARCHIVE_VOICE3,
    XA_ARCHIVE_VOICE4,
    XA_ARCHIVE_VOICE5,
};

enum XaTrack {
    MUSIC_STAFF_ROLL = 0x00,
    MUSIC_SIGMA_FINAL_BATTLE = 0x01,
    MUSIC_SIGMA_BATTLE = 0x02,
    MUSIC_STAGE_JUNGLE = 0x03,
    MUSIC_STAGE_FINAL_WEAPON = 0x04,
    MUSIC_STAGE_MILITARY_TRAIN = 0x05,
    MUSIC_STAGE_BIO_LABORATORY = 0x06,
    MUSIC_BOSS_BATTLE = 0x07,
    MUSIC_BRIEFING = 0x08,
    MUSIC_STAGE_SNOW_BASE_2 = 0x09,
    MUSIC_STAGE_CYBER_SPACE = 0x0A,
    MUSIC_REPLIFORCE_BATTLE = 0x0B,
    MUSIC_STAGE_AIR_FORCE = 0x0C,
    MUSIC_IRIS_BATTLE = 0x0D,
    MUSIC_STAGE_SNOW_BASE = 0x0E,
    MUSIC_DOUBLE_BATTLE = 0x0F,
    MUSIC_STAGE_INTRO_X = 0x10,
    MUSIC_STAGE_VOLCANO = 0x11,
    MUSIC_STAGE_MARINE_BASE = 0x12,
    MUSIC_STAGE_INTRO_ZERO = 0x13,
    MUSIC_STAGE_SPACE_PORT = 0x14,
    MUSIC_INTRO_BOSS_BATTLE = 0x15,
    MUSIC_BRIEFING_LATE = 0x16,
    MUSIC_WEAPON_GET = 0x17,
    MUSIC_DIALOGUE_1 = 0x18,
    MUSIC_DIALOGUE_2 = 0x19,
    MUSIC_DIALOGUE_3 = 0x1A,
    MUSIC_LIGHT_CAPSULE = 0x1B,
    MUSIC_CHARACTER_SELECT = 0x1C,
    MUSIC_TITLE = 0x20,
    MUSIC_STAGE_CLEAR_ZERO = 0x21,
    MUSIC_STAGE_CLEAR_X = 0x22,
    VOICE_IRIS_3 = 0x28,
    VOICE_CYBER_PEACOCK_1 = 0x29,
    VOICE_MAGMA_DRAGOON_1 = 0x2A,
    VOICE_MAGMA_DRAGOON_2 = 0x2B,
    VOICE_IRIS_2 = 0x2C,
    VOICE_SLASH_BEAST_3 = 0x2D,
    VOICE_COLONEL_1 = 0x2E,
    VOICE_IRIS_1 = 0x2F,
    VOICE_MAGMA_DRAGOON_3 = 0x30,
    VOICE_COLONEL_2 = 0x31,
    VOICE_GENERAL_3 = 0x32,
    VOICE_CYBER_PEACOCK_2 = 0x33,
    VOICE_JET_STINGRAY_1 = 0x34,
    VOICE_SPLIT_MUSHROOM_1 = 0x35,
    VOICE_SPLIT_MUSHROOM_3 = 0x36,
    VOICE_SPLIT_MUSHROOM_2 = 0x37,
    VOICE_SLASH_BEAST_2 = 0x38,
    VOICE_CYBER_PEACOCK_3 = 0x39,
    VOICE_JET_STINGRAY_2 = 0x3A,
    VOICE_COLONEL_3 = 0x3B,
    VOICE_FROST_WALRUS_2 = 0x3C,
    VOICE_JET_STINGRAY_3 = 0x3D,
    VOICE_UNUSED_1 = 0x3E,
    VOICE_WEB_SPIDER_2 = 0x3F,
    VOICE_SIGMA_3 = 0x40,
    VOICE_SLASH_BEAST_1 = 0x41,
    VOICE_GENERAL_1 = 0x42,
    VOICE_GENERAL_2 = 0x43,
    VOICE_STORM_OWL_2 = 0x44,
    VOICE_FROST_WALRUS_1 = 0x45,
    VOICE_FROST_WALRUS_3 = 0x46,
    VOICE_UNUSED_2 = 0x47,
    VOICE_SIGMA_1 = 0x48,
    VOICE_DOUBLE_3 = 0x49,
    VOICE_SIGMA_2 = 0x4A,
    VOICE_STORM_OWL_1 = 0x4B,
    VOICE_DOUBLE_2 = 0x4C,
    VOICE_DOUBLE_1 = 0x4D,
    VOICE_STORM_OWL_3 = 0x4E,
    VOICE_WEB_SPIDER_1 = 0x4F,
    MUSIC_BOSS_INTRO_WEB_SPIDER = 0x50,
    MUSIC_BOSS_INTRO_FROST_WALRUS = 0x51,
    MUSIC_BOSS_INTRO_SPLIT_MUSHROOM = 0x52,
    MUSIC_BOSS_INTRO_MAGMA_DRAGOON = 0x53,
    MUSIC_BOSS_INTRO_JET_STINGRAY = 0x54,
    MUSIC_BOSS_INTRO_CYBER_PEACOCK = 0x55,
    MUSIC_BOSS_INTRO_STORM_OWL = 0x56,
    MUSIC_BOSS_INTRO_SLASH_BEAST = 0x57,
};

struct XaSequenceParams {
    u8 sequence, volume;
};
extern struct XaSequenceParams stage_music[16][2][2];
extern u8 alternate_stage_music[32];
extern u8* D_80141F00;
extern u8* D_80141EE8[];
extern u8* D_80141F50[];
extern u8* cur_draw_info_dispenv_screen_w;
extern u8* cur_draw_info_drawenv;

void func_8001293C(void);
void TeleportRelatedObjectUpdate(struct EffectObj*);
void grenade_fly(struct ShotObj*);
ret_s8 func_8002DD04(struct MainObj*);
void hover_sentry_check_player_near(struct MainObj*);
u8 func_8003CF24(struct RideArmorObj*);
void func_8003D338(struct AnimatedObj*);
void func_8003D39C(struct MainObj*);
void snowman_bomb_check_fall(struct MainObj*);
void proximity_door_check_player(struct EffectObj*);
void proximity_door_start_script(struct EffectObj*, s32);
void func_800C63BC(struct ItemObj*);
void light_capsule_main(struct ItemObj*);
void ride_armor_pilot_spawn_dust(struct VisualObj*, u8);
void cyberspace_trial_delete_unused_items(void);
extern union CdSectorBuffer D_8012F4B4;
extern RECT D_80137CFC;
extern s32 D_80137D08[];
extern s32 background_dragon_perch_points[][2];
extern struct FixedPointPosition background_dragon_route_starts[];
extern struct FixedPointPosition background_dragon_staging_offsets[];
extern u32* dragon_rubble_animations[];
extern u8 dragon_rubble_debris[];
extern u8 x_water_wake_modes[9][16];
extern u8 zero_water_wake_modes[9][16];
extern u8 cyber_peacock_attacks[32];
extern u8 cyber_peacock_attacks_low_health[32];
extern u8 general_shot_prop_debris[];
extern s16 sentry_drone_activation_distances[];

#include "func_tables.h"

s32 func_80034E2C();
void player_start_stage_clear(struct PlayerObj*);
s16 func_8002BAA4(void);
void player_damage(s8);
void func_800129F0(s32);
void func_800127C8(s32);
void func_80012A3C();
s32 func_8001540C(s32, arg_u8, void*);
s32 is_sound_finished(s32, struct MainObj*);
void func_8001B644(u8*);
s32 func_8001CB24(u8* buffer, s32 device_num, s32 size);
void func_8001CC5C(s32 device_num, struct MemcardFileList* list, const char* pattern);
s32 func_8001CD70(s32 arg0);
int func_8001CDE4(int arg0);
s32 func_8001CE84(s32 device_num);
void func_8001B718(s16, u8, u8);
void func_8001B7C0(s16 x, s16 y, u8 arg2);
void func_8001C210(void);
void func_8001C30C(struct MemcardSaveSlot*);
void func_8001C008(s32, s32);
s32 player_set_animation(struct PlayerObj*, s32);
void player_enter_beam_out(struct PlayerObj*);
void player_enter_stand(struct PlayerObj*);
void player_script_walk_to_mark(struct PlayerObj*);
void player_set_collision_bounds(struct PlayerObj*);
void robot_bee_check_dive(struct MainObj* arg0);
void func_8004D6FC(struct MainObj* arg0);
void trident_mech_check_fall(struct MainObj*);
extern u8 robot_bee_debris[];
extern u8 ambush_gunner_debris[];
extern u8 ice_bird_debris[];
extern char train_boss_turret_debris[8];
extern struct Unk_unk68 trident_mech_stunned_hurt_box;
extern u8 trident_mech_debris[12];
extern u16 player_stage_3_entry_y[2][4];
extern u16 player_stage_6_entry_y[6];
extern u16 player_stage_12_entry_y[20];
struct PlayerDashEffectOffset {
    u16 x, y;
};
extern struct PlayerDashEffectOffset player_dash_spark_offsets[2];
extern u16 player_dash_splash_offsets[2];
void player_set_idle_animation(struct PlayerObj*);
void func_800CEFC0(struct MiscObj*);
void cyberspace_guide_update_blink(struct MiscObj*);
void player_set_animation_frame(struct PlayerObj*, s32, s32);
void player_enter_ladder_grab(struct PlayerObj*);
void player_enter_ladder_climb_on_top(struct PlayerObj*);
void player_clear_dash_and_attack(struct PlayerObj*);
void player_play_voice(struct PlayerObj*, u8);
struct WeaponObj* player_spawn_weapon(s8, s8, s8, struct PlayerObj*);
void func_80037484(struct PlayerObj*, s32);
void player_set_shoot_animation(struct PlayerObj*);
s32 func_8002D180(struct PlayerObj*, s16, s16, s32);
ret_u8 get_random_nonzero(void);
ret_u8 func_8002938C();
void update_on_screen(struct BaseObj*, s32, s32);
void func_800127C8(s32);
void func_800127FC(void);
void func_800129A4(s8);
void func_80013530(void);
typedef unsigned long CdLoadAddress;
extern u32 D_80141F30[8];
void func_80013AD8(s32, u8, CdLoadAddress);
void func_80013890(u32, u8*);
void func_800261B4(s32);
void func_80028FEC(s16, s16, s16, s16, u8);
struct Item03StageEntry {
    u16 x;
    u16 y;
    u16 velocity;
    u16 right;
    u16 trigger_x;
    u16 object_id;
    s16 width;
    s16 height;
};
extern struct Item03StageEntry falling_pillar_entries[22];
void start_screen_shake_x(s8, s8, s8);
void func_800292D0(struct StageObjectRecord*);
struct ObjectHeader* MakeObject(u8);
ret_u8 angle_to_object(struct ObjectHeader*, struct ObjectHeader*);
void soul_body_clone_update(void);
void func_80015284(void);
void func_8001C3E8(void);
void reset_game_engine(void);
void func_8001DC30(void);
s32 set_animation(void*, s32);
void set_animation_frame(struct AnimatedObj*, s32, s32);
void animate_object(struct AnimatedObj*);
void ice_bird_spawn_ice_shards(struct AnimatedObj*);
void ice_bird_face_player(struct AnimatedObj*);
void frost_tower_hide(struct WeaponObj*);
void func_8001653C(void);
s32 player_check_dash_input(struct PlayerObj*);
s32 func_80033FF0(struct PlayerObj*);
void player_enter_jump(struct PlayerObj*);
void player_enter_land(struct PlayerObj*);
void player_enter_dash(struct PlayerObj*);
void player_enter_dash_end(struct PlayerObj*);
void player_enter_air_dash(struct PlayerObj*);
void player_enter_fall_shooting(struct PlayerObj*);
void player_enter_wall_cling(struct PlayerObj*);
void player_enter_ladder_up(struct PlayerObj*);
void player_spawn_wall_slide_dust(struct PlayerObj*);
void player_spawn_dash_spark(struct PlayerObj*);
void player_spawn_dash_splash(struct PlayerObj*);
void player_reset_weapon(struct PlayerObj*);
s32 player_zero_check_ladder_slash(struct PlayerObj*);
s32 player_zero_check_shippuuga(struct PlayerObj*);
void func_80025188(s32, u8);
void func_800253F0(struct MainObj*, s32);
void func_80025588(s16, s16, s16, s16, s32);
void func_80027AAC(struct BackgroundObj*);
void func_80027AFC(struct BackgroundObj*);
void func_80027B70(struct Unk9*);
void func_80027BE4(struct BackgroundObj*);
void func_80027E90(struct BackgroundObj*);
void func_80027EBC(struct BackgroundObj*);
void func_80027F50(struct BackgroundObj*);
void func_80027F7C(struct BackgroundObj*);
void func_80028310(struct BackgroundObj*);
void func_80028338(struct BackgroundObj*);
void func_80028364(struct BackgroundObj*);
void func_800283D0(struct BackgroundObj*);
void func_800283F8(struct BackgroundObj*);
void func_80028424(struct BackgroundObj*);
s32 player_zero_check_raijingeki(struct PlayerObj*);
s32 player_zero_check_ryuenjin(struct PlayerObj*);
s32 func_80039F28(struct PlayerObj*);
void func_80012EB8();
void func_8001D064();
void func_8001D134();
void func_8001DAF8();
void reset_objects();
void func_80013014();
void func_80023D68();
void func_8002A484();
void func_80023D68();
void func_8002A484();
void search_light_maker_spawn_edges(s32, s8, s8);
void search_light_maker_spawn_in_rect(s16, s16, s16, s16, s32);
s8 search_light_maker_scroll_dirs(s32, s8);
void ZeroObjectState(struct ObjectHeader* arg0);
void init_objects();
void func_80026648();
s16 get_layout_screen(s16, s16, s16);
u8 train_scroll_player_at_lock(struct LayerObj*);
u8 train_tunnel_player_at_lock(struct LayerObj*);
void refresh_visible_tile_effect(s32 arg0, s32 arg1, s32 arg2);
s32 func_800E5FF4(s32, s32, u8*);
void func_800AE6B4(struct BazObj*);
struct VisualObj* spawn_explosion_at(s8, s16, s16, u8);
void func_80027FA8();
void func_8002F048();
void quad_is_on_screen(struct QuadObj*);
s32 search_light_is_visible(struct QuadObj*);
void stop_sound(u8, u8);
void func_80016F0C();
void func_80023D30();
void func_8002AB20();
void func_8001D230();
void func_8001FB50();
void func_8002217C(u16, u8, u8);
void func_80022730(struct AbcObj*);
void move_object(struct MovingObj*);
ret_u8 angle_to_point(struct ObjectHeader*, s32, s32);
void set_velocity_from_angle(struct MovingObj*, arg_u8);
void func_8002B9F0(s32* arg0, s32* arg1, u8 arg2);
void update_screen_shake_x(struct BackgroundObj* arg0);
void start_screen_shake_y(s8, s8, s8);
void apply_tile_effect(u8, s32, s32);
s32 func_8002B160(struct BaseObj*);
s32 func_8002B1E8(struct BaseObj*, s32, s32);
ret_u8 func_8002D9BC(void*);
void drop_item(struct BaseObj*, s8);
void func_800BF638(struct BaseObj* arg0, s8 arg1, s16 arg2, s16 arg3);
void spawn_rubble(arg_u8, u8*, void*, s32);
void ice_bird_spawn_charge_ring(struct MainObj*, s8);
void spawn_debris(arg_u8, void*, void*);
extern u8 D_800F9118[8];
struct MenuTextureData {
    u32 texture[96];
#ifdef MMX4_WIN32
    char product_codes[4][16];
    char sc[4];
    char title[12];
#endif
    s16 bounds[8];
};
extern u8 D_800F1FC0[32];
extern struct MenuTextureData D_800F1FE0;
struct ShotObj* web_spider_spawn_thread(struct MainObj*, s32);
void ice_core_face_player(struct AnimatedObj*);
void drone_pod_random_explosion(struct MainObj*);
void drone_pod_alarm_flash(struct MainObj*);
void bomb_bat_drop_bomb(struct MainObj*);
void storm_owl_spawn_storm_charge(struct AnimatedObj*);
void magma_dragoon_spawn_flames(struct AnimatedObj*, u32);
s32 update_boss_music_delay(void);
void vent_spawn_mixed_puffs(struct MiscObj*, u8);
void vent_spawn_puffs(struct MiscObj*, u8);
void is_on_screen(struct BaseObj*);
s32 func_8002CF98(struct PlayerObj*, u8, s16, s16);
s32 func_8002D32C(struct PlayerObj*, s16, s32);
s32 func_8002D5E4(struct PlayerObj*, s16);
u8 func_8002D724(struct PlayerObj*, s16, s16);
u8 func_8002D7E4(struct PlayerObj*, s16, s16);
u8 func_8002D900(struct PlayerObj*);
u8 func_8002D994(struct PlayerObj*);
void func_800E5D78(s32);
s32 func_800E5D90(s32, s32, s32);
void func_80016334(void);
#ifdef MMX4_PC
void func_80016124(void);
#endif
void func_8001663C(u8, u8);
void func_800175AC(u8);
s32 func_800E5ACC(void);
void func_800E6138(s8*);
void func_8001213C(void);
void func_800122E0(struct DrawInfo* arg0);
extern void func_80013A20(void);
extern void func_80013E68(u8 status, u8* result);
void func_80013650(void);
s8 func_800136B0();
void func_800137F0();
void MyCdReadyCallback(u8 status, u8* result);
void func_80018000(arg_u8);
void despawn_object(struct ObjectHeader* arg0);
void despawn_object_permanently(struct ObjectHeader* arg0);
void func_8002B560(s8, s8);
void move_with_gravity(struct AnimatedObj* arg0);
#ifdef MMX4_PC
void func_8002C36C(struct PlayerObj*, struct PlayerObj*, s32);
s32 func_8002D490(struct PlayerObj*);
void func_8002E294(struct PlayerObj*, struct PlayerObj*);
void func_8002E380(struct MovingObj*, struct MovingObj*, u8);
#endif
void slope_skier_read_slope(struct MainObj*);
void caterkiller_face_player(struct MainObj*);
void func_800583B0(struct MainObj*, s16, s16, s32);
void func_800AF878(struct BaseObj*, s32, s32, s32);
void func_800C842C(s32, u8*, void*, s32, void*);
void delete_items(s32, s32);
void wheel_charger_face_player(struct MainObj*);
void train_cannon_fire_blast(struct PlayerObj*);
void train_cannon_fire_volley(struct MainObj*);
void train_cannon_spawn_charge_glow(struct VisualObj*);
void func_800681C4(struct MainObj*);
void func_80068340(struct MainObj*);
void func_8006AE80(struct MainObj*);
void slash_beast_face_player(struct MainObj*);
void breakable_terrain_spawn_rubble(struct MainObj*);
void web_spider_set_move_timer(struct MainObj*);
void web_spider_set_swing_animation(struct MainObj*);
void func_800204CC(s8*, s32);
void func_80097670(struct WeaponObj*);
void double_cyclone_charged_fly(struct WeaponObj*);
void twin_slasher_hide(struct WeaponObj*);
void aiming_laser_charged_aim(struct WeaponObj*, struct PlayerObj*);
void player_clear_dash(struct PlayerObj*);
s32 player_hover_check_end(struct PlayerObj*);
s32 player_hover_steer(struct PlayerObj*);
s32 player_check_shoot_ladder(struct PlayerObj*);
void func_8003C624(struct RideArmorObj*);
void func_8003D8A8(struct RideArmorObj*, s32, s32);
s32 func_8003DCD8(struct RideArmorObj*);
s32 func_8003D7E4(struct RideArmorObj*, u8, s32);
s32 player_zero_shippuuga_cancel(struct PlayerObj*);
void func_8003D254(struct VisualObj*);
void func_8003D6EC(struct AnimatedObj*, s32);
void player_hover_set_direction(struct PlayerObj*, s32);
void play_boss_voice(s32);
void func_800AF95C(struct ObjectHeader*, s32, s32, s32, s32);
void func_800B0CA0(s32, arg_u8, struct MainObj*, s32, s32);
struct VisualObj* jet_stingray_spawn_splash(struct MainObj*);
u8 jet_stingray_check_surface(struct PlayerObj*, s32, s32);
void fortress_collapse_spawn_random_explosion(struct EffectObj*);

enum SelectedPlayer {
    CHARACTER_X,
    CHARACTER_ZERO
};

extern struct ArchiveSelectionData D_800EE480;
extern s32 loaded_vab_address;
extern s32 saved_vab_address;
extern s32 movie_slice_offset;
extern u8 cd_fade_requested;
extern u8 pad_port1_packet[0x22];

#ifdef VERSION_EU
void func_800182E8(s32);
#else
void func_800182E8(void);
#endif

void func_800E9040(void);

#ifdef MMX4_PC
long SpuSetTransferMode(long);
void StCdInterrupt(void);
void func_80012328(void);
void func_80012F44(void);
void func_80014A90(s32, s32);
void func_80014C70(void);
void func_80017100(void);
void func_800179BC(void);
void func_80017E84(void);
void func_80017F2C(void);
void func_8001A9EC(struct EngineObj*);
void func_800200D4(struct EngineObj*);
void func_80021F34(void);
void func_80024260(void);
void func_80024334(struct VisualObj*);
void func_80024920(struct QuadObj*);
void func_80024B9C(struct QuadObj*);
void func_8002588C(struct PlayerObj*, s32, s32);
void func_800262B8(u8);
void func_80026AA0(s32);
void func_80027344(s32, s32, s32);
void func_800275DC(s32, s32, s32);
void func_80028690(struct BackgroundObj*);
void func_80028E24(void);
void func_8002B3C0(struct BaseObj*);
s32 func_8002BB80(struct MainObj*, struct MainObj*);
s32 func_8002C160(struct CollisionObj*, struct CollisionObj*);
void func_8002C26C(struct CollisionObj*, struct CollisionObj*);
void func_8002C2EC(struct CollisionObj*, struct CollisionObj*);
s32 player_check_walk(struct PlayerObj*);
s32 player_check_air_move(struct PlayerObj*);
s32 player_check_wall(struct PlayerObj*);
s32 player_check_wall_jump(struct PlayerObj*);
s32 player_is_pushing_wall(struct PlayerObj*);
void func_80033D54(struct PlayerObj*);
s32 player_check_ladder_air(struct PlayerObj*);
void player_enter_walk_start(struct PlayerObj*);
void player_enter_land_or_fall(struct PlayerObj*);
void player_enter_wall_slide(struct PlayerObj*);
void func_80034B64(struct PlayerObj*);
void player_check_low_hp_alarm(struct PlayerObj*);
void func_80036F50(struct PlayerObj*);
s32 player_check_shoot_air(struct PlayerObj*);
s32 player_check_hover(struct PlayerObj*);
s32 player_has_weapon_energy(struct PlayerObj*);
s32 player_zero_check_jump_slash(struct PlayerObj*);
s32 player_zero_check_wall_slash(struct PlayerObj*);
s32 player_zero_check_hyouretsuzan(struct PlayerObj*);
s32 player_zero_check_double_jump(struct PlayerObj*);
void trident_mech_face_player(struct AnimatedObj*);
void snowman_bomb_face_player(struct AnimatedObj*);
void jump_shooter_face_player(struct AnimatedObj*);
void func_8006B2A4(struct MainObj*);
void func_8006B398(struct MainObj*);
void func_8006E920(struct MainObj*, s32);
void colonel_face_center(struct BaseObj*);
void func_800889DC(struct MainObj*);
void buster_shot_place_at_muzzle(struct VisualObj*, struct PlayerObj*, arg_u8);
void lightning_web_draw(struct WeaponObj*);
void iris_drone_move(struct ShotObj*);
void func_800AFB90(struct VisualObj*);
void floor_trap_explode(struct EffectObj*);
void armored_walker_check_fall(struct MainObj*);
void armored_walker_check_behind(struct MainObj*);
void armored_walker_check_wall(struct MainObj*);
void palette_pulse_init(struct EffectObj*);
void func_800BD080(struct EffectObj*);
void cyberspace_trial_spawn_rank_warp(struct EffectObj*);
void func_800D9B48(struct LayerObj*);
void func_800DCF40(void);
void func_800E0CEC(void);
void func_800E0D0C(void);
void post_boss_cutscene_spawn_afterimages(struct UnkObj*);

#include "game_prototypes.h"
#endif

#ifdef MMX4_PC
#include "pc_build.h"
#endif
