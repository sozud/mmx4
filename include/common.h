#ifdef VERSION_JP
#define ASM_ROOT "asm/jp/"
#else
#define ASM_ROOT "asm/us/"
#endif

#if defined(MMX4_PC) || defined(SKIP_ASM) || defined(PERMUTER)
#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)
#else
#define INCLUDE_ASM(FOLDER, NAME)                   \
    __asm__(".pushsection .text\n"                  \
            "\t.align\t2\n"                         \
            "\t.globl\t" #NAME "\n"                 \
            "\t.ent\t" #NAME "\n" #NAME ":\n"       \
            ".include \"" ASM_ROOT FOLDER "/" #NAME ".s\"\n" \
            "\t.set reorder\n"                      \
            "\t.set at\n"                           \
            "\t.end\t" #NAME "\n"                   \
            ".popsection");

#define INCLUDE_RODATA(FOLDER, NAME)                \
    __asm__(".pushsection .rodata\n"                \
            ".include \"" ASM_ROOT FOLDER "/" #NAME ".s\"\n" \
            ".popsection");

__asm__(".include \"macro.inc\"\n");
#endif

#define NULL ((void*)0)
#define FIXED(x) ((s32)((x)*0x10000))
#define COUNT(x) (sizeof(x) / sizeof(x[0]))
#define MMX4_STATIC_ASSERT(name, condition) typedef char static_assert_##name[(condition) ? 1 : -1]
#ifdef MMX4_PC
#define MMX4_OFFSET_OF(type, member) __builtin_offsetof(type, member)
#else
#define MMX4_OFFSET_OF(type, member) ((u32)&(((type*)0)->member))
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
#else
#define PAD_CONFIRM PADRdown
#define PAD_CANCEL PADRright
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
typedef char SoundArchive_header_must_be_8_bytes[sizeof(struct SoundArchive) == 8 ? 1 : -1];

struct CdImageOrigin {
    u16 x, y;
};
struct HudSpriteOrigin {
    s16 x, y;
    u16 clut;
};
struct StageObjectMarginData {
    u16 margins[5];
    u16 alignment_padding;
};
struct MainFlags {
    s32 unk0;
};
struct MainBssState {
    struct MainFlags flags;
    s8 transition[4];
    u8 character_mode;
    u8 alignment_padding[3];
};
struct FadeState {
    s16 unk0, unk2;
    u16 unk4, alignment_padding;
};
struct ArchiveSelectionData {
    u8 prefix[8];
    u8 archive_ids[124];
};
union CdSectorBuffer {
    u8 sectors[16][0x800];
    u32 words[0x2000];
};
struct MissionSelectData {
    u8 stage_order[12];
    u8 route_a[8];
    u8 route_b[8];
    u16 route_a_positions[4];
    u16 route_b_positions[3];
    u16 briefing_sound_ids[11];
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
    u32 has_next;
};
struct ArchivePathData {
    s8 stage_archive_indices[12];
#ifdef VERSION_JP
    char paths[162][64];
#else
    char paths[163][64];
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
    u8 unk90[18];                 /* 0x90 */
    u8 unkA2[18];                 /* 0xA2 */
    u8 settled;                   /* 0xB4 */
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

extern struct MissionSelectData D_800F474C;
extern union PlayerChargeData D_800F8BE0;

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

typedef s8 PlayerChargeState;
enum {
    PLAYER_CHARGE_NONE,
    PLAYER_CHARGE_PARTIAL,
    PLAYER_CHARGE_FULL,
};

MMX4_STATIC_ASSERT(animation_step_size, sizeof(union AnimationStep) == sizeof(u32));

#define OBJECT_HEADER_FIELDS \
    s8 active;                \
    s8 id;                    \
    s8 unk2;                  \
    s8 on_screen;             \
    s8 state;                 \
    s8 unk5;                  \
    s8 unk6;                  \
    s8 unk7;                  \
    f32 x_pos;                \
    f32 y_pos;                \
    void* backref;

#define BASE_OBJ_TAIL_FIELDS \
    s8 bg_offset;             \
    u8 unk15;                 \
    u8 unk16;                 \
    u8 unk17;

#define BASE_OBJ_FIELDS \
    OBJECT_HEADER_FIELDS \
    BASE_OBJ_TAIL_FIELDS

#define MOVING_OBJ_FIELDS \
    BASE_OBJ_FIELDS        \
    s32 unk18;             \
    s32 unk1C;             \
    f32 x_vel;             \
    f32 y_vel;

#define ANIMATED_OBJ_FIELDS                   \
    MOVING_OBJ_FIELDS                         \
    s32 unk28;                                \
    s32 unk2C;                                \
    u32** animation_table;                    \
    u32* animation_cursor;                    \
    void* unk38;                              \
    void* unk3C;                              \
    u16 unk40;                                \
    u16 unk42;                                \
    union AnimationStep animation_step;       \
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
    u8 pad0[8];
    f32 x_pos;
    f32 y_pos;
    u8 pad10[0x58];
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

struct Main0Ext {
    u8 unk80;
    u8 index;
    u8 flags[3];
    u8 unk85;
};

struct Main3Ext {
    u32 unk80;
    s32 unk84;
    u32 unk88;
    u32 unk8C;
    u32 saved_unk5;
};

struct Main5Ext {
    u8 pad80[0xC];
    u16 saved_unk5;
};

struct MainSavedState80Ext {
    u32 saved_unk5;
};

struct Main58Ext { u32 saved_unk5, unk84, unk88; };
struct Main10Ext {
    u32 unk80;
    s32 unk84;
    s32 unk88;
    u32 unk8C;
    u32 unk90;
    u32 saved_unk5;
};

struct MainSavedState8CExt {
    u8 pad80[0xC];
    u32 saved_unk5;
};

struct MainSavedState90Ext {
    u8 pad80[0x10];
    u32 saved_unk5;
};

struct Main17Ext {
    u32 unk80;
    u8 pad84[0xC];
    u32 saved_unk5;
};

struct Main37Ext {
    u32 unk80;
    u32 unk84;
    u32 unk88;
    u32 unk8C;
    u8 pad90[4];
    u32 saved_unk5;
};

struct MainSavedState94Ext {
    u8 pad80[0x14];
    u32 saved_unk5;
};

struct Main52Ext {
    u8 unk80;
    u8 pad81[0x13];
    u32 saved_unk5;
};

struct Main13Ext {
    u32 unk80;
    u32 unk84;
    u32 unk88;
    u32 saved_unk5;
};

struct Main11Ext {
    u8 pad80[7];
    u8 saved_unk5;
};

struct Main12Ext {
    u8 pad80[2];
    u8 saved_unk5;
};

struct Main22Ext {
    u32 saved_unk5;
    u32 unk84;
    u8 pad88[0xC];
    u32 unk94;
};

struct Main24Ext {
    u32 unk80;
    u8 pad84[0x10];
    u32 saved_unk5;
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
    u32 unk84;
    u8 pad88[0xC];
    u32 saved_unk5;
};

struct Main48Ext {
    u8 pad80[4];
    u8 saved_unk5;
};

struct Main73Ext {
    u8 pad80[9];
    s8 unk89;
    u8 pad8A[2];
    u8 effect_state;
    u8 object_id;
    u8 unk8E;
};

struct Main73PartsExt {
    struct MainObj* parts[3];
    u8 effect_state;
    u8 object_id;
    u8 unk8E;
};

struct Main18Ext {
    u8 pad80;
    u8 unk81;
    u8 unk82;
    u8 pad83;
    u8 unk84;
    s8 unk85;
    u8 pad86;
    u8 unk87;
    u8 unk88;
    u8 pad89[0xE];
    u8 saved_unk5;
};

struct Main19Ext {
    u8 pad80;
    u8 animation_index;
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

struct Main36Ext {
    u8 pad80[8];
    u8 saved_unk5;
};

struct Main43Ext {
    u8 pad80[0xC];
    u16 animation_index;
    u16 animation_length;
    u16 unk90;
    u8 unk92;
    u8 pad93;
    u8 unk94;
    u8 pad95;
    u8 animation_id;
    s8 animation_set;
};

struct Main56Ext {
    u8 pad80[0xB];
    u8 flags;
};

struct Main57Ext {
    u8 pad80[8];
    struct Unk_unk68* unk88;
    u8 pad8C[0x93 - 0x8C];
    u8 unk93;
    u8 unk94;
};

struct Main487Ext {
    u8 pad80[0xA];
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
    u32 unk80;
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
};

struct Main72Ext {
    u8 pad80[4];
    s16 unk84;
};

struct Main60Ext {
    u8 pad80[0xA];
    u8 saved_unk5;
    u8 unk8B;
};

struct Main64Ext {
    u8 pad80[4];
    u16 unk84;
    u16 unk86;
    u8 unk88;
    u8 pad89[2];
    u8 unk8B;
    u8 pad8C[5];
    u8 unk91;
};

struct Main74Ext {
    u8 pad80[0x17];
    u8 unk97;
};

struct Main75Ext {
    struct EffectObj* unk80;
    u8 pad84[0xA];
    u8 saved_unk5;
};

struct Main8Ext {
    u32 unk80;
    u32 unk84;
    u8 unk88;
    u8 unk89;
    u8 pad8A;
    u8 unk8B;
    u8 unk8C;
};

struct Main27Ext {
    u8 unk80;
    u8 pad81[0x13];
    u32 saved_unk5;
};

struct Main41Ext {
    u8 unk80;
    u8 pad81;
    u8 unk82;
    u8 unk83;
    u8 unk84;
};

struct Main66Ext {
    u8 pad80[6];
    u8 unk86;
    u8 unk87;
};

struct Main70Ext {
    u16 unk80;
    u16 unk82;
    u8 pad84;
    u8 unk85;
    u8 unk86;
    u8 unk87;
    u8 pad88[0xC];
    u32 saved_unk5;
};

union MainObjExt {
    u32 raw[7];
    struct Main0Ext main_0;
    struct Main3Ext main_3;
    struct Main5Ext main_5;
    struct Main8Ext main_8;
    struct MainSavedState94Ext main_6;
    struct MainSavedState94Ext main_7;
    struct Main10Ext main_10;
    struct Main11Ext main_11;
    struct Main12Ext main_12;
    struct Main13Ext main_13;
    struct MainSavedState90Ext main_14;
    struct Main17Ext main_17;
    struct Main18Ext main_18;
    struct Main19Ext main_19;
    struct Main21Ext main_21;
    struct Main22Ext main_22;
    struct Main24Ext main_24;
    struct Main25Ext main_25;
    struct Main27Ext main_27;
    struct MainSavedState94Ext main_32;
    struct MainSavedState94Ext main_33;
    struct Main35Ext main_35;
    struct Main36Ext main_36;
    struct Main41Ext main_41;
    struct Main43Ext main_43;
    struct Main487Ext main_487;
    struct Main37Ext main_37;
    struct MainSavedState80Ext main_38;
    struct MainSavedState94Ext main_44;
    struct Main48Ext main_48;
    struct Main49Ext main_49;
    struct MainSavedState94Ext main_51;
    struct Main52Ext main_52;
    struct Main56Ext main_56;
    struct Main57Ext main_57;
    struct Main58Ext main_58;
    struct Main60Ext main_60;
    struct Main64Ext main_64;
    struct Main66Ext main_66;
    struct MainSavedState94Ext main_67;
    struct Main70Ext main_70;
    struct Main53Ext main_53;
    struct Main62Ext main_62;
    struct Main71Ext main_71;
    struct Main72Ext main_72;
    struct Main73Ext main_73;
    struct Main73PartsExt main_73_parts;
    struct Main74Ext main_74;
    struct Main75Ext main_75;
};

#ifndef MMX4_PC
MMX4_STATIC_ASSERT(main_obj_ext_size, sizeof(union MainObjExt) == 0x1C);
#endif

#define MAIN_OBJ_TAIL_FIELDS                        \
    s32 unk20;                                  \
    s32 unk24;                                  \
    s32 unk28;                                  \
    s32 unk2C;                                  \
    const u8* const* animation_table;            \
    const u8* animation_cursor;                  \
    s16 animation_speed;                         \
    u8 pad3A[2];                                 \
    const u8* sprite_frames;                     \
    u16 unk40;                                   \
    u16 unk42;                                   \
    union AnimationStep animation_step;          \
    u8 previous_animation_index;                 \
    s8 pad49[7];                                 \
    const u8* unk50;                             \
    const u8* unk54;                             \
    const u16* collision_data;                   \
    s8 unk5C;                                    \
    s8 unk5D;                                    \
    s8 unk5E;                                    \
    s8 unk5F;                                    \
    s8 unk60;                                    \
    s8 unk61;                                    \
    s8 unk62;                                    \
    s8 unk63;                                    \
    s8 unk64;                                    \
    s8 unk65;                                    \
    s8 unk66;                                    \
    s8 unk67;                                    \
    struct Unk_unk68* unk68;                     \
    s16 unk6C;                                   \
    s16 unk6E;                                   \
    u8 unk70;                                    \
    s8 : 8;                                      \
    s8 unk72;                                    \
    s8 unk73;                                    \
    s8 unk74;                                    \
    s8 unk75;                                    \
    s8 unk76;                                    \
    s8 unk77;                                    \
    s8 unk78;                                    \
    s8 unk79;                                    \
    s8 unk7A;                                    \
    u8 unk7B;                                    \
    s16 unk7C;                                   \
    s16 unk7E;                                   \
    union MainObjExt ext;

struct MainObj {
    BASE_OBJ_FIELDS
    f32 unk18;
    f32 unk1C;
    MAIN_OBJ_TAIL_FIELDS
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
    s8 unk3E;
    s8 unk3F;
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
    s8 unk4A;
    s8 pad4B[0x50 - 0x4B];
    void* unk50;
    const u32* unk54;
    void* unk58;
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
    s8 unk71;
    u8 unk72;
    u8 unk73;
    u8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 unk79;
    s8 unk7A;
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
    u16 unk82;
    s8 unk84;
    s8 unk85;
    s8 unk86;
    s8 unk87;
    union PlayerUnk88 unk88;
    union PlayerUnk8A unk8A;
    s8 unk8C;
    u8 unk8D;
    s8 unk8E;
    s8 unk8F;
    s8 unk90;
    u8 unk91;
    u8 unk92;
    s8 unk93;
    s8 unk94[2];
    s8 unk96;
    s8 unk97;
    s8 unk98;
    s8 unk99;
    s8 unk9A;
    PlayerChargeState charge_state[2];
    u8 unk9D;
    u8 unk9E;
    s8 unk9F;
    s8 unkA0;
    s8 unkA1;
    s8 unkA2;
    s8 : 8;
    s8 unkA4;
    s8 unkA5;
    s8 unkA6;
    s8 unkA7;
    s8 charge_levels[0x10];
    u8 unkB8;
    s8 unkB9;
    s8 unkBA;
    s8 unkBB;
    s8 unkBC;
    s8 unkBD;
    s8 unkBE;
    s8 unkBF;
    s8 unkC0;
    s8 unkC1;
    s8 unkC2;
    s8 unkC3;
    s8 unkC4;
    s8 unkC5;
    s8 unkC6;
    s8 unkC7;
    struct MainObj* weapon_06_slots[3];
    s8 unkD4;
    u8 unkD5;
    u8 unkD6;
    s8 unkD7;
    s8 : 8;
    s8 unkD9;
    u16 unkDA;
    s8 padDC[0xDE - 0xDC];
    s8 unkDE;
    s8 unkDF;
    s8 unkE0;
    s8 unkE1;
    u8 unkE2;
    s8 : 8;
}; // size 0xE4

MMX4_STATIC_ASSERT(player_unk68_offset,
    MMX4_OFFSET_OF(struct PlayerObj, unk68) == MMX4_OFFSET_OF(struct MainObj, unk68));
MMX4_STATIC_ASSERT(player_unk6C_offset,
    MMX4_OFFSET_OF(struct PlayerObj, unk6C) == MMX4_OFFSET_OF(struct MainObj, unk6C));
MMX4_STATIC_ASSERT(player_unk6E_offset,
    MMX4_OFFSET_OF(struct PlayerObj, unk6E) == MMX4_OFFSET_OF(struct MainObj, unk6E));
MMX4_STATIC_ASSERT(player_unk70_offset,
    MMX4_OFFSET_OF(struct PlayerObj, unk70) == MMX4_OFFSET_OF(struct MainObj, unk70));
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

struct VisualObj {
    ANIMATED_OBJ_FIELDS
    u8 unk49;
    s8 pad4A[0x50 - 0x4A];
    struct PlayerObj* unk50; // 0x50, guessed
    s16 unk54;
    s16 unk56;
    s32 : 32;
    s8 unk5C;
    s8 : 8;
    s16 unk5E;
    u8 pa58[0x70 - 0x60];
}; // size 0x70

union ShotUnk8C {
    s32 word;
    u16 half;
    s8 byte;
    struct ObjectHeader* object;
};

union ShotUnk58 {
    const u8* data;
    const u16* collision_data;
    struct Unk_unk68* collision_bounds;
};

struct Shot24Ext {
    u8 owner_state;
    u8 owner_notified;
    s16 timer;
};

struct ShotObj {
    ANIMATED_OBJ_FIELDS
    s8 pad49[0x50 - 0x49];
    union {
        const u8* data;
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
        u16 halves[2];
        u8 bytes[4];
        struct Shot24Ext shot_24;
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
    MMX4_OFFSET_OF(struct ShotObj, unk54) == MMX4_OFFSET_OF(struct MainObj, unk54));
MMX4_STATIC_ASSERT(shot_unk58_offset,
    MMX4_OFFSET_OF(struct ShotObj, unk58) == MMX4_OFFSET_OF(struct MainObj, collision_data));
MMX4_STATIC_ASSERT(shot_unk68_offset,
    MMX4_OFFSET_OF(struct ShotObj, unk68) == MMX4_OFFSET_OF(struct MainObj, unk68));

struct Weapon7Ext {
    u16 timer;
};

struct Weapon10Ext {
    u8 timer;
    u8 pad8D[0x90 - 0x8D];
    u8 unk90;
};

struct Weapon14Ext {
    u8 unk8C;
    s8 unk8D;
};

struct Weapon16Ext {
    u16 timer;
    u8 pad8E[0x91 - 0x8E];
    u8 unk91;
};

struct Weapon20Ext {
    u8 pad8C[0x8E - 0x8C];
    s8 unk8E;
};

union WeaponUnk84 {
    s32 word;
    u8 byte;
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

union WeaponObjExt {
    u8 raw[0x94 - 0x8C];
    struct Weapon7Ext weapon_7;
    struct Weapon10Ext weapon_10;
    struct Weapon14Ext weapon_14;
    struct Weapon16Ext weapon_16;
    struct Weapon20Ext weapon_20;
    struct Weapon29Ext weapon_29;
    struct Shot46Ext shot_46;
};

MMX4_STATIC_ASSERT(weapon_obj_ext_size, sizeof(union WeaponObjExt) == 0x8);

struct WeaponObj {
    BASE_OBJ_FIELDS
    s32 unk18;
    s32 unk1C;
    f32 x_vel;
    f32 y_vel;
    s32 unk28;
    s32 unk2C;
    u32** animation_table;
    u32* animation_cursor;
    void* unk38;
    void* unk3C;
    u16 unk40;
    u16 unk42;
    union AnimationStep animation_step;
    u8 previous_animation_index;
    s8 pad49[0x50 - 0x49];
    const u8* unk50;
    s32 unk54;
    s8 pad58[0x61 - 0x58];
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
    struct PlayerObj* owner;
    union WeaponUnk80 unk80;
    union WeaponUnk84 unk84;
    s8 pad88[0x8C - 0x88];
    union WeaponObjExt ext;
    u8 unk94;
    s8 pad95[0x98 - 0x95];
    s8 unk98;
    s8 pad99[0x9C - 0x99];
}; // size 0x9C

#ifndef MMX4_PC
MMX4_STATIC_ASSERT(psx_weapon_owner_offset,
    MMX4_OFFSET_OF(struct WeaponObj, owner) == 0x7C);
MMX4_STATIC_ASSERT(psx_weapon_ext_offset,
    MMX4_OFFSET_OF(struct WeaponObj, ext) == 0x8C);
#endif

struct UnkObj {
    ANIMATED_OBJ_FIELDS
    s8 pad49[0x4B - 0x49];
    s8 unk4B;
    s8 pad4C[0x50 - 0x4C];
    u8* unk50;
    u8 unk54;
    u8 pad55[0x60 - 0x55];
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

union ItemExt {
    struct Item2Ext item_2;
    struct Item4Ext item_4;
    struct Item12Ext item_12;
    struct MainObj* owner;
};

union ItemUnk84 {
    u16 timer;
    u32 previous_value;
};

union ItemUnk7C {
    u8 value;
    s32 item_4_timer;
    struct MiscObj* misc;
    void* object;
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
    s32 unk50;
    s32 unk54;
    s8 pad58[0x5C - 0x58];
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
    union ItemUnk84 unk84;
    s32 unk88;
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
    f32* position;
};

struct Misc2Ext {
    u8 pad50[4];
    struct MainObj* owner;
    u8 unk58;
};

struct Misc11Ext { u8 pad50[4], active; };

struct Misc51Ext {
    struct MainObj* source;
    u8 unk54;
};

struct Misc45Ext {
    u8 pad50[0x5A - 0x50];
    s16 target_x;
    u8 direction;
};
struct Misc24Ext { struct MainObj* main; s16 timer; u16 child_active; struct MiscObj* child; };

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

struct Misc34Related {
    u8 pad0[0x16], active, variant;
};

struct Misc34Ext {
    struct Misc34Related* related;
    u8 timer;
    u8 pad55;
    u8 variant;
    u8 pad57[2];
    u8 enabled;
};

struct Misc39Ext {
    void* related;
    u16 timer;
};

struct Misc55Ext {
    struct WeaponObj* owner;
};

struct Misc53Ext {
    u8 pad50[4];
    struct EffectObj* effect;
    u16 timer;
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
    struct Misc7Ext misc_7;
    struct Misc11Ext misc_11;
    struct Misc45Ext misc_45;
    struct Misc51Ext misc_51;
    struct Misc24Ext misc_24;
    struct Misc53Ext misc_53;
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
    s8 pad7[0x14 - 7];
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
    BASE_OBJ_FIELDS
    s8 pad18[0x30 - 0x18];
    u32** animation_table;
    s32 pad34;
    s32 unk38;
    void* unk3C;
    u16 unk40;
    u16 unk42;
    s8 pad44[0x50 - 0x44];
}; // size 0x50

union RideArmorUnk98 {
    s16 packed;
    struct {
        u8 low;
        u8 high;
    } bytes;
};

struct RideArmorObj {
    BASE_OBJ_FIELDS
    s32 unk18;
    s32 unk1C;
    f32 x_vel;
    s8 pad24[0x46 - 0x24];
    s8 unk46;
    s8 pad47[0x5C - 0x47];
    s8 unk5C;
    s8 pad5D[0x70 - 0x5D];
    u8 unk70;
    s8 pad71[0x7D - 0x71];
    u8 unk7D;
    u8 unk7E;
    s8 pad7F;
    u8 unk80;
    s8 pad81;
    u8 unk82;
    s8 pad83[0x88 - 0x83];
    u16 collision_flags;
    s16 unk8A;
    s16 unk8C;
    s8 pad8E[0x97 - 0x8E];
    s8 unk97;
    union RideArmorUnk98 unk98;
    s8 pad9A[0xB0 - 0x9A];
}; // size 0xB0

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
    u8 data[0x200];
};

struct OrderingTableBuffer {
    u8 data[0x100];
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
extern struct Unk16 D_80141BD8;
extern struct BackgroundObj background_objects[3];
extern u8 D_800FF7A4[];
extern u8 D_800FF7A8[4];
extern const u8* D_800FF6C8[];
extern u8 D_80104CDC[];
extern u8 D_80104CE0[];
extern struct Item04Data D_8010C8B4;
extern u8 D_8010C904[];
extern s32 D_8010C918[4];
extern struct BgDrawRelated D_8015D9D0[];
extern struct MainPrimitiveBuffer temp1[];
extern struct SecondaryPrimitiveBuffer temp2[];
extern struct BackgroundPrimitiveBuffer temp3[];
extern struct OrderingTableBuffer temp4[];
extern struct AuxiliaryPrimitiveBuffer temp5[];
#ifdef MMX4_PC
extern TILE D_80169D78[2];
extern struct FadeState D_8016DEA0;
#else
extern struct SecondaryPrimitiveBuffer D_80169D78[];
extern struct BackgroundPrimitiveBuffer D_8016DEA0;
#endif
extern DR_TPAGE D_8012F498[2];
extern TILE D_8013B7B0[2];
extern POLY_FT4 D_80139F20[2];
extern POLY_F4 D_80139F70[2];
extern DR_TPAGE D_80139FA0[2];
extern POLY_F4 D_80139FB0[2][128];
extern DR_TPAGE D_80171EB0[2][6][8];
extern u8 D_80141BE8[0x300];
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

struct QuadUnkExt2 {
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

struct QuadUnkExt3 {
    u8 unk38;
};

struct Quad5Ext {
    s32* data;
    u16 unk3C;
    s16 unk3E;
    u16 index;
};

struct Quad10Ext {
    s32 unk38;
    u8 pad3C[0x44 - 0x3C];
    u8 unk44;
};

struct QuadUnkExt4 {
    s32 : 32;
    u16 unk3C;
};

union QuadExt {
    struct ReadyLineExt ready_line;
    struct SearchLightMotion search_light;
    struct QuadUnkExt unk_ext;
    struct QuadUnkExt2 unk_ext2;
    struct Quad4Ext quad_4;
    struct Quad5Ext quad_5;
    struct Quad10Ext quad_10;
    struct Quad2Ext quad_2;
    struct QuadUnkExt3 unk_ext3;
    struct QuadUnkExt4 unk_ext4;
    u32 unk38;
};

struct SearchLightRuntime {
    s32 x_accumulator;
    s32 y_accumulator;
    u16 pause_timer;
    s16 extent;
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
    struct ReadyLineRuntime ready_line;
};

union QuadLink {
    struct EffectObj* owner;
    u16 direction;
};

struct QuadObj {
    OBJECT_HEADER_FIELDS
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
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
    s32 boss_ptr; // 0x20
    s8 enable_boss; // 0x24
    s8 unk25;
    union EngineCharacterState character_state; // 0x26
    s8 unk36;
    s8 unk37;
    void* unk38;
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

#define ENGINE_STAGE_ID (*(u16*)&engine_obj.stage)
#define ENGINE_CHECKPOINT (*(u8*)&engine_obj.checkpoint)
#define ENGINE_UNK2E (engine_obj.character_state.bytes[8])

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
    s32 unk18;
};

struct Effect4Ext {
    u16 timer;
    s16 unk16;
};

struct Effect22Ext {
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17;
    u16 unk18;
};

struct Effect24Ext {
    struct EffectObj* spawned_effect;
    u16 timer;
    u8 unk1A;
    u8 unk1B;
};

struct Effect38Ext {
    u8 pad14;
    u8 timer;
    u8 unk16;
    u8 unk17;
};

struct Effect8Ext {
    u8 pad14[2];
    u8 unk16;
    u8 pad17;
    u16 unk18;
};

struct Effect9Ext {
    u16 transition_timer;
    u16 movement_timer;
    s16 direction;
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

struct Effect5Ext {
    u32 unk14;
    u32 unk18;
    u8 unk1C;
    u8 pad1D;
    u8 unk1E;
};

struct Effect14Ext {
    u16 unk14;
    u8 unk16;
};
struct Effect17Ext { u8 pad14[4], timer; };
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
};

struct Effect32Ext {
    u8 unk14, unk15, unk16, pad17;
    union Effect32Palette palette;
    union Effect32PaletteSource palette_source;
};
struct Effect36Ext { u8 pad14[4]; struct Unk_unk68* collision_bounds; };
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
    struct Effect9Ext effect_9;
    u16 effect_26_timer;
    struct Effect4Ext effect_4;
    struct UnkEffectExt unk_effect;
    struct Effect5Ext effect_5;
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
    struct Effect32Ext effect_23;
    struct Effect32Ext effect_32;
    struct Effect36Ext effect_36;
    struct Effect38Ext effect_38;
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

#define ASSERT_OBJECT_HEADER(type, first_tail_member)                                        \
    MMX4_STATIC_ASSERT(type##_backref_offset,                                                 \
        MMX4_OFFSET_OF(struct type, backref) == MMX4_OFFSET_OF(struct ObjectHeader, backref)); \
    MMX4_STATIC_ASSERT(type##_header_size,                                                    \
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
ASSERT_OBJECT_HEADER(QuadObj, unk14);
ASSERT_OBJECT_HEADER(EffectObj, ext);

#undef ASSERT_OBJECT_HEADER

#define ASSERT_MOVING_OBJECT(type)                                                   \
    MMX4_STATIC_ASSERT(type##_x_vel_offset,                                          \
        MMX4_OFFSET_OF(struct type, x_vel) == MMX4_OFFSET_OF(struct MovingObj, x_vel)); \
    MMX4_STATIC_ASSERT(type##_y_vel_offset,                                          \
        MMX4_OFFSET_OF(struct type, y_vel) == MMX4_OFFSET_OF(struct MovingObj, y_vel))

ASSERT_MOVING_OBJECT(PlayerObj);
ASSERT_MOVING_OBJECT(VisualObj);
ASSERT_MOVING_OBJECT(MiscObj);
ASSERT_MOVING_OBJECT(WeaponObj);

#undef ASSERT_MOVING_OBJECT

#define ASSERT_ANIMATED_OBJECT(type)                                                   \
    MMX4_STATIC_ASSERT(type##_animation_table_offset,                                  \
        MMX4_OFFSET_OF(struct type, animation_table) ==                                \
            MMX4_OFFSET_OF(struct AnimatedObj, animation_table));                      \
    MMX4_STATIC_ASSERT(type##_animation_cursor_offset,                                 \
        MMX4_OFFSET_OF(struct type, animation_cursor) ==                               \
            MMX4_OFFSET_OF(struct AnimatedObj, animation_cursor));                     \
    MMX4_STATIC_ASSERT(type##_animation_step_offset,                                   \
        MMX4_OFFSET_OF(struct type, animation_step) ==                                 \
            MMX4_OFFSET_OF(struct AnimatedObj, animation_step));                       \
    MMX4_STATIC_ASSERT(type##_previous_animation_index_offset,                         \
        MMX4_OFFSET_OF(struct type, previous_animation_index) ==                       \
            MMX4_OFFSET_OF(struct AnimatedObj, previous_animation_index))

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
extern u8 D_800F8B30[];
extern u8 D_800F8B34[][4];
extern struct Unk_unk68 D_80100E78;
extern struct Unk_unk68 D_80100E7C;
extern u16 D_801013C8[18];
extern u16 D_801013EC[20];
extern struct Unk_unk68 D_800F8BC4;
extern struct Unk_unk68 D_800F8BC8;
extern s8 D_800F8BF8[];
extern s8 D_800F8C10[];
extern s8 D_800F8C28[];
struct PlayerModeTiming {
    u8 first;
    u8 second;
};
extern struct PlayerModeTiming D_800F8C4C[];
extern s8 D_800F8CCC[];
extern s8 D_800F8CE4[];
extern s8 D_800F8CFC[];
extern s8 D_800F8D14[];
extern u8 D_800F8D44[];
extern struct VisualAttachmentOffset D_8010A1AC[2];
extern struct VisualAttachmentOffset D_8010A1B4[2];
extern struct VisualAttachmentInit D_8010A1BC[4];
extern u8 D_80108C44[4];
extern u8 D_80108C48[4];
extern u8 D_80108C4C[4];
extern u8 D_80108C50[4];
extern u8 D_80108C58[4];
extern u8 D_8010A1D4[];
struct Visual03Bounds {
    s32 x;
    s32 y;
};
extern struct Visual03Bounds D_8010A1E4[];

extern u16 D_80108768[48];

struct PlayerFrameOffset {
    s8 x;
    s8 y;
};
union PlayerFrameOffsetData {
    struct PlayerFrameOffset offsets[256];
    s8 components[512];
};
extern union PlayerFrameOffsetData D_8011B230;
extern u32* D_8010A4C0[3];
extern u8 D_8010A4F8[];
extern u8 D_8010A504[];
extern u16 D_8010A588[];
extern u8 D_8010A590[4];
extern u8 D_8010A594[4];
extern s16 D_8010A598[4];
extern struct VisualBounds D_8010A5A0[4];
extern u8 D_8010A5B8[];
extern u16** D_8010AE0C[26];
extern u32* D_8010E4EC[];
extern u32* D_8010E514[];
extern u32* D_8010E538[];
extern u32* D_8010E55C[];
extern u32* D_8010ECD4[];
extern s8 D_8010FE38[];
extern u8 D_8010FED4[];
extern s16 D_8010FF00[4];
extern s32* D_8010FAB4[8];
extern u8 D_801193F0[];
extern u32 D_801194F0[];
extern u8 D_8011A030[];
extern u8 D_8011A130[];
extern u32 D_8011A230[];
extern u8 D_8011AF60[];
extern u32* D_8011BF40[54];
extern u32* D_8011C094[7];
extern u32* D_8011C0E4[3];
extern union AnimationStep* D_800FE890[21];
extern void* D_80101624[12];
extern void* D_80101A6C[30];
#ifdef MMX4_PC
extern struct MainBssState main_bss_state;
#define D_80141BD8 (main_bss_state.flags)
#define D_80141BDC (main_bss_state.transition)
#define D_80141BDE (&main_bss_state.transition[2])
#define D_80141BDF ((u8*)&main_bss_state.transition[3])
#define D_80141BE0 (main_bss_state.character_mode)
#else
extern s8 D_80141BDC[];
extern s8 D_80141BDE[];
extern u8 D_80141BDF[];
extern u8 D_80141BE0;
#endif
extern struct Unk5 D_800F0E18[];
extern s32 D_80137CC0;
extern s8 D_801419B3;
extern s8 D_80141A07;
extern s8 D_80141A5B;
extern struct DrawInfo* cur_draw_info;
extern struct EngineObj engine_obj;
extern u8 layout_width;
extern u16 layout_size;
extern void (*engine_update_funcs[])(struct EngineObj*);
extern u8 D_80171EA8;
struct MemcardPath {
    char path[6];
};
extern const struct MemcardPath D_800100C0;
extern u8 D_800F2180[];
extern u8 D_800F21A0[];
extern s16 D_800F21DC[];
extern u8 D_800F21F8[];
extern u8 D_800F22D0[];
extern u8 D_800F22E0[];
extern u8 D_800F2300[];
extern u8 D_800F2310[12];
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
extern s32 D_800FA108[2];
extern s32 D_800FA110[2];
extern u8 D_800FAEF0[8];
extern u8 D_800FAEF8[4];
extern struct Unk_unk68 D_800FAEFC;
extern u8 D_80105FC8[13][3];
extern struct Unk_unk68 D_80103F00;
extern struct Unk_unk68 D_80103F04;
extern struct Unk_unk68 D_80107E84[];
extern struct Unk_unk68 D_8010884C[];
extern struct Unk_unk68 D_80105374;
extern u16 D_80106070[64];
extern struct Unk_unk68 D_801060F0[32];
extern struct Unk_unk68 D_801061F0[32];
extern u8 D_80109028[4];
extern u8 D_8010902C[32][4];
extern u8 D_801090C4[4];
extern u16 D_801090E8[3][2];
extern u8 D_80109104[8];
extern struct Unk_unk68 D_80109894;
extern u8 D_80109BA8[2][4];
extern u8 D_80108BA4[];
extern struct EffectObj* D_8013B8A8;
extern struct Unk_unk68* D_8013B8B0;
extern struct ShotObj* D_8013B8C0;
extern struct ShotObj* D_8013B8C4;
extern struct Unk_unk68 D_8010D0FC;
extern struct FixedMatrix2 D_800F2ADC[16];
extern s32 D_800EE458;
extern void (*D_8012F490)(void);
extern s8 D_80173C6C[4];
extern s8 D_80137DFC;
extern u8 D_80137DD4;
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
extern u16 D_80166C08;
extern u16 D_80166C0A;
extern s8 D_800F8BE9[];
extern u8 D_800FB0EC[8];
extern void (*D_800FB104[])();
#ifdef MMX4_PC
#define D_8010B465 (((u8*)D_8010B464)[1])
#else
extern u8 D_8010B465;
#endif
extern u8 x_ready_text_flags[];
extern u8 x_ready_text_flags_1[];
#define D_800F2CA4 ((const u32* const**)(x_ready_text_flags_1 + 0x0C))
extern u8* const* D_800F2DD8[];
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
extern void (*D_8010B4C4[])();
extern void (*D_8010BEC8[])();
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
extern u16 D_801419BE[];
extern void (*g_MegamanInBriefingRoomUpdateFuncs[2])();
extern void (*g_TitleUpdateFuncs[])();
extern void (*D_8010EB84[4])();
extern void (*g_SelectACharacterUpdateFuncs[3])();
extern struct MainObj main_objects[0x30]; // D_8013BED0
extern void (*g_SearchLightUpdateFuncs[3])(struct QuadObj*);
extern void (*D_8010FC84[])();
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
extern s8 D_8013B810;
extern u8 D_8013B814;
extern u8 D_8013B8A0[];
extern struct AbcObj abc_object;
extern struct BarObj bar_object;
extern struct BazObj baz_objects[2];
extern struct VisualObj visual_objects[0x20];
extern struct ShotObj shot_objects[0x20];
extern struct WeaponObj weapon_objects[0x10];
extern struct UnkObj unk_objects[0x14];
extern struct UnkObj foo_objects[3];
extern struct EffectObj effect_objects[0x20];
extern struct ItemObj item_objects[0x20];
extern struct MiscObj misc_objects[0x40];
extern const u8* D_800FB0BC[12];
extern struct LayerObj layer_objects[4];
extern struct RideArmorObj qux_object;
extern struct GameInfo game_info;
extern void (*D_800F485C[1])();
extern void (*ReadyTextUpdateFuncs[3])();
extern u8* D_80137DC4;
extern s32 D_80137DD0;
extern u32* D_801406A8;
extern struct SearchLightInit D_8010F600[6];
extern s32 D_8010F66C[3];
extern struct SearchLightColorLookup D_8010F684;
extern struct SearchLightIntensityLookup D_8010F68C;
extern u32* D_8010EAC8[7];
extern u32* D_8010EAE4[6];
extern u32* D_8010EAFC[10];
extern u8 D_8010EB24[16];
extern u8 D_8010EB34[16];
extern u8 D_8010EB44[16];
extern struct CharacterSelectPosition D_8010EB54[9];
extern struct CharacterSelectPosition D_8010EB78[3];
extern u8 D_801406AC;
extern s32 D_80142F70;
extern u8* D_8015D9C8;
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
extern u8 D_800F1D90;
extern CdlATV D_80139644;
extern u8 D_80171EA9;
extern s32 D_80166BB4;
#ifdef MMX4_PC
extern u8 D_80166D68[0x22];
#else
extern u8 D_80166D68;
#endif
extern u8 D_8012F46C[0x22];
extern u16 D_800EE430[];
extern RECT D_800EE450;
extern u16 cur_random;
extern s32 D_8013BD44;
extern s16 D_80141BD2;
extern s8 D_80139528;
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
extern u8* D_80173C80;
extern u8 D_80173C84;
extern void (*D_8010EBB4[16])();
extern void (*D_8010EB98[])();
extern void (*D_8010EBA0[])();
extern u8 need_palette_load;
extern void (*D_8010EBA8[])();
extern u8 D_801721B8;
extern s8 D_801721F7;
extern void (*D_8010FC90[])();
extern struct Unk14* D_8010B1F8[];
extern s32 D_8010B23C[][4];
extern s32 D_8013E188[4];
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
extern u16 controller_state;
extern s8 D_801419FC;
extern u8 D_800F4508[0x20];
extern u8* D_800F4560[];
extern u8 D_800F4568[0x14];
extern u8 D_800F457C[0x14];
extern u8* D_800F4834[10];
extern u16 D_800F312C[];
extern void (*D_800F3134[])(struct BackgroundObj* arg0);
extern struct Prim D_800EE504[];
extern struct RectPtrPair vram_rect_ptrs[];
extern struct RectPtrPair* vram_rect_ptr;
extern u8 D_800F30D4[16][2];
struct XaSequenceParams {
    u8 sequence, volume;
};
struct XaSequenceData {
    struct XaSequenceParams stage[16][2][2];
    struct XaSequenceParams alternate[16];
};
extern struct XaSequenceData D_800F1A0C;
extern u8* D_80141F00;
extern u8* D_80141F50[];
extern u8* cur_draw_info_dispenv_screen_w;
extern u8* cur_draw_info_drawenv;

void func_8001293C(void);
void TeleportRelatedObjectUpdate(struct EffectObj*);
void func_8009ED70(struct ShotObj*);
s32 func_8002DD04(struct MainObj*);
extern union CdSectorBuffer D_8012F4B4;
extern RECT D_80137CFC;
extern s32 D_80137D08[];
extern s32 D_800F99C4[][2];
extern struct FixedPointPosition D_800F99D4[];
extern struct FixedPointPosition D_800F99E4[];
extern u32* D_8010DBC0[];
extern u8 D_8010DBF8[];
extern u8 D_8010A074[9][16];
extern u8 D_8010A104[9][16];
extern u8 D_80102984[32];
extern u8 D_801029A4[32];
extern u8 D_80109E10[];
extern s16 D_800FFAD8[];

#include "func_tables.h"

s32 func_80034E2C();
s32 func_80034F7C();
s16 func_8002BAA4(void);
void func_80036470(s32 arg0);
void func_800129F0(s32);
void func_800127C8(s32);
void func_80012A3C();
s32 func_8001540C(s32, s32, void*);
s32 func_80015A10(s32, struct MainObj*);
void func_8001B644(u8*);
void func_8001C008(s32, s32);
s32 func_800350A4(struct PlayerObj*, s32);
void func_8003516C(struct PlayerObj*, s32, s32);
s32 func_8002D180(struct PlayerObj*, s16, s16, s32);
s32 func_8002B780(void);
s32 func_8002938C();
void func_8002B318(struct BaseObj*, s32, s32);
void func_800127C8(s32);
void func_800127FC(void);
void func_800129A4(s8);
void func_80013530(void);
typedef unsigned long CdLoadAddress;
void func_80013AD8(s32, u8, CdLoadAddress);
void func_80013890(u32, u8*);
void func_800261B4(s32, u32, u8*);
void func_80028FEC(s16, s16, s16, s16, u8);
void func_80028B68(s8, s8, s8);
void func_800292D0(struct StageObjectRecord*);
struct ObjectHeader* MakeObject(u8);
s32 func_8002B7DC(struct ObjectHeader*, struct ObjectHeader*);
void func_80094F74(void);
void func_80015284(void);
void func_8001C3E8(void);
void reset_game_engine(void);
void func_8001DC30(void);
s32 func_80015D60(void*, s32);
void func_80015D90(struct AnimatedObj*, s32, s32);
void func_80015DC8(struct AnimatedObj*);
s32 func_80033694(struct PlayerObj*);
void func_80034538(struct PlayerObj*);
void func_80034668(struct PlayerObj*);
void func_80034754(struct PlayerObj*);
void func_8003484C(struct PlayerObj*);
void func_8003490C(struct PlayerObj*);
void func_80034968(struct PlayerObj*);
void func_80034D64(struct PlayerObj*);
void func_80036A94(struct PlayerObj*);
void func_80036E98(struct PlayerObj*);
void func_80025188(s32, u8);
void func_80025588(s16, s16, s16, s16, s32);
void func_80027AAC(struct BackgroundObj*);
void func_80027AFC(struct BackgroundObj*);
void func_80027B70(struct Unk9*);
void func_80027BE4(struct BackgroundObj*);
void func_80027E90(struct BackgroundObj*);
void func_80027EBC(struct BackgroundObj*);
void func_80027F50(void);
void func_80027F7C(void);
void func_80028310(struct BackgroundObj*);
void func_80028338(struct BackgroundObj*);
void func_80028364(struct BackgroundObj*);
void func_800283D0(struct BackgroundObj*);
void func_800283F8(void);
void func_80028424(void);
s32 func_80039C34(struct Unk12*);
s32 func_80039E5C(struct Unk12*);
s32 func_80039F28(struct Unk12*);
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
void func_800B6D1C(s32, s8, s8);
void func_800B6EB4(s16, s16, s16, s16, s32);
s8 func_800B6FF4(s32, s8);
void ZeroObjectState(struct ObjectHeader* arg0);
void init_objects();
void func_80026648();
s16 func_8002BAD0(s16, s16, s16);
u8 func_800D8E94(struct LayerObj*);
u8 func_800D9B08(struct LayerObj*);
void func_800DA984();
s32 func_800E5FF4(s32, s32, u8*);
void func_800AE6B4(struct BazObj*);
struct VisualObj* func_800AFAB4(s8, s16, s16, u8);
void func_80027FA8();
void func_8002F048();
void quad_is_on_screen(struct QuadObj*);
void func_80015930(u8, u8);
void func_80016F0C();
void func_80023D30();
void func_8002AB20();
void func_8001D230();
void func_8001FB50();
void func_8002217C(u16, u8, u8);
void func_80022730(struct AbcObj*);
void func_8002B718(struct MovingObj*);
s32 func_8002B7B0(struct ObjectHeader*, s32, s32);
void func_8002B93C(struct MovingObj*, s32);
void func_8002B9F0(s32 *arg0, s32 *arg1, u8 arg2);
void func_80028A48(struct BackgroundObj *arg0);
void func_80028BAC(s8, s8, s8);
void func_800DABE4(u8, s32, s32);
s32 func_8002B160(struct BaseObj*);
s32 func_8002B1E8(struct BaseObj*, s32, s32);
s32 func_8002D9BC(void*);
void func_800BF60C(struct BaseObj*, s8);
void func_800C813C(s32, void*, void*);
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
void func_80018000(s32);
void func_8002B0C8(struct ObjectHeader* arg0);
void func_8002B108(struct ObjectHeader* arg0);
void func_8002B560(s8, s8);
void func_8002B694(struct AnimatedObj* arg0);
void func_80036034(struct PlayerObj*);
s32 func_80038D38(struct PlayerObj*);
s32 func_80038D88(struct PlayerObj*);
void func_80038E44(struct PlayerObj*, s32);
void func_800921E8(s32);
void func_800AF95C(struct ObjectHeader*, s32, s32, s32, s32);

enum SelectedPlayer {
    CHARACTER_X,
    CHARACTER_ZERO
};

#ifdef MMX4_PC
#include "game_prototypes.h"
#endif

#ifdef MMX4_PC
#include "pc_build.h"
#endif
