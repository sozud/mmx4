#ifndef MMX4_COMMON_H
#define MMX4_COMMON_H

#ifdef VERSION_JP
#define ASM_ROOT "asm/jp/"
#elif defined(VERSION_EU)
#define ASM_ROOT "asm/eu/"
#else
#define ASM_ROOT "asm/us/"
#endif

#if defined(MMX4_SHC)
#define INCLUDE_ASM(FOLDER, NAME) extern int shc_unported_asm_##NAME
#define INCLUDE_RODATA(FOLDER, NAME) extern int shc_unported_rodata_##NAME
#elif defined(MMX4_PC) || defined(SKIP_ASM) || defined(PERMUTER)
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
#define CLUT_FROM_XY(x, y) ((((x)*4 + 0x18) % 16) | ((((y) + 6) / 4 + 0x1E0) << 6))
#define CLUT_FROM_ID(id) CLUT_FROM_XY(func_8002938C(id), func_8002938C(id))
// Player and ride-armor HP and Sub Tanks store a 7-bit quantity with bit 7
// latched on the frame it is damaged or drained.
#define HP_VALUE(v) ((v) & 0x7F)
#define HP_DAMAGE_FLAG(v) ((v) & 0x80)
#define TANK_VALUE(v) HP_VALUE(v)
#define TANK_DRAINED(v) HP_DAMAGE_FLAG(v)
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

#if defined(MMX4_SHC_LAYOUT_CHECKS)
#define MMX4_STATIC_ASSERT(name, condition) int shc_layout_check_##name(void) { return (condition); } extern int shc_layout_decl_##name
#elif defined(MMX4_SHC)
#define MMX4_STATIC_ASSERT(name, condition) extern int shc_layout_check_##name(void)
#elif defined(MMX4_WIN32)
#define MMX4_STATIC_ASSERT(name, condition)
#else
#define MMX4_STATIC_ASSERT(name, condition) typedef char static_assert_##name[(condition) ? 1 : -1]
#endif
#if defined(MMX4_SATURN) && !defined(assert)
#define assert(condition) ((void)0)
#endif
#ifdef MMX4_PC
#define MMX4_OFFSET_OF(type, member) __builtin_offsetof(type, member)
#else
#define MMX4_OFFSET_OF(type, member) ((u32) & (((type*)0)->member))
#endif

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
#ifdef MMX4_SHC
typedef struct ShcUnsupportedSigned64 s64;
#elif defined(MMX4_WIN32)
typedef signed __int64 s64;
#else
typedef signed long long s64;
#endif
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#ifdef MMX4_SHC
typedef struct ShcUnsupportedUnsigned64 u64;
#elif defined(MMX4_WIN32)
typedef unsigned __int64 u64;
#else
typedef unsigned long long u64;
#endif

struct PlayerHurtVelocity {
    s32 x_vel;
    s32 x_accel;
    s32 y_vel;
    s32 gravity;
};

#ifdef MMX4_SATURN
#define PLAYER_FACING_RIGHT 0x10
#define PLAYER_FACING_SHIFT 4
#else
#define PLAYER_FACING_RIGHT 0x40
#define PLAYER_FACING_SHIFT 6
#endif

#ifdef MMX4_SHC
void* memcpy(void*, const void*, unsigned int);
void* memset(void*, int, unsigned int);
#define __builtin_memcpy memcpy
#define __builtin_memset memset
#endif

typedef u16 Palette[16];

#ifdef MMX4_WIN32
typedef u8 ret_u8;
typedef s8 ret_s8;
typedef u8 arg_u8;
typedef u16 arg_u16;
typedef s16 arg_s16;
#else
typedef s32 ret_u8;
typedef s32 ret_s8;
typedef s32 arg_u8;
typedef s32 arg_u16;
typedef s32 arg_s16;
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
#elif !defined(MMX4_SATURN)
#include "psy-q-4.0/SYS/TYPES.H"
#ifdef MMX4_WIN32
#define _INC_TYPES
#define near near_
#define far far_
#endif
#include "psy-q-4.0/LIBGTE.H"
#include "psy-q-4.0/LIBGPU.H"
#include "psy-q-4.0/LIBSND.H"
#include "psy-q-4.0/LIBETC.H"
#include "psy-q-4.0/KERNEL.H"
#include "psy-q-4.0/LIBCD.H"
#include "psy-q-4.0/LIBPRESS.H"
#endif

#ifdef MMX4_SATURN
typedef struct {
    s16 x, y;
    s16 w, h;
} RECT;
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

/* EU writes the tpage mode inline; US/JP query GetGraphType(). */
#ifdef VERSION_EU
#define BG_DRAW_TPAGE(p, tpage) \
    (setlen(p, 1), ((u_long*)(p))[sizeof(OT_TYPE) / sizeof(u_long)] = 0xE1000000 | (tpage))
#else
#define BG_DRAW_TPAGE(p, tpage) \
    (setlen(p, 1), ((u_long*)(p))[sizeof(OT_TYPE) / sizeof(u_long)] = 0xE1000000 | ((GetGraphType() == 1 || GetGraphType() == 2) ? (tpage) : ((tpage)&0x9FF)))
#endif

struct DialogueGlyph {
    u8 frame;
    u8 character;
    u8 x;
    u8 y;
};

struct SoundArchive {
    u32 vab_offset : 24;
    u32 vab_id : 8;
    u32 unk4;
#ifndef MMX4_SHC
    u8 sound_entries[0];
#endif
};
struct SoundTransfer {
    s32 remaining;
    s32 offset;
};

typedef char SoundArchive_header_must_be_8_bytes[sizeof(struct SoundArchive) == 8 ? 1 : -1];

union CdCommand {
    u32 word;
    struct {
        u8 arg; // 0x0
        u8 op; // 0x1
        u16 handler; // 0x2
    } f;
};
extern union CdCommand D_80137CD4;
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
union CdSectorBuffer {
    u8 sectors[16][0x800];
    u32 words[0x2000];
};
struct CdCompletionSlot {
    u8 pending, callback;
    u16 pad2;
    u32 callback_arg;
    u16 transfer_pending, padA;
};
typedef char CdCompletionSlot_must_be_12_bytes[sizeof(struct CdCompletionSlot) == 12 ? 1 : -1];
typedef union {
    s32 val;
    struct {
#ifdef MMX4_SATURN
        s16 hi;
        s16 lo;
#else
        s16 lo;
        s16 hi;
#endif
    } i;
    struct {
#ifdef MMX4_SATURN
        u16 hi;
        u16 lo;
#else
        u16 lo;
        u16 hi;
#endif
    } u;
    u8 bytes[4];
} f32;

#ifdef MMX4_SATURN
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
} f32_halves;
#else
typedef f32 f32_halves;
#endif
struct TitlePointState {
    f32 coordinates[36];
    u8 unk90[18]; /* 0x90 */
    u8 unkA2[18]; /* 0xA2 */
    u8 settled; /* 0xB4 */
};
struct StageObjectRecord {
    u8 flags, id, subtype, object_type;
    s16 x, y;
};

struct FixedPointPosition {
    s32 x;
    s32 y;
};

struct BootTransitionDataRegion {
    u8 preceding_record_tail[3];
    u8 stage_map[9];
};

#ifdef MMX4_WIN32
extern u8 mission_stage_order[16];
#else
extern u8 mission_stage_order[12];
#endif

union AnimationStep {
    struct {
        s8 duration;
        s8 event;
        s8 relative_step;
        u8 frame_index;
    } fields;
    u32 packed;
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

MMX4_STATIC_ASSERT(animation_step_size, sizeof(union AnimationStep) == sizeof(u32));

#include "obj.h"

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

#ifndef MMX4_SATURN
struct RectPtrPair {
    RECT rect;
    u_long* ptr;
};
#endif

extern struct QuadObj g_QuadObjects[0x20];

struct PlayerFrameOffset {
    s8 x;
    s8 y;
};
extern s32 D_80137CC0;
extern s8 D_80141A07;
extern s8 D_80141A5B;
extern struct DrawInfo* cur_draw_info;
extern struct EngineObj engine_obj;
extern struct EffectObj* boss_warning_tiles[22];
extern u8 layout_width;
extern u16 layout_size;
extern u8 D_80171EA8;

struct MemcardFileList {
    char names[15][22];
    u8 count; // 0x14A
    s8 pad14B;
    s32 total_size; // 0x14C
    s32 sizes[15]; // 0x150
};

extern struct MemcardFileList memcard_files;

#ifdef VERSION_JP
extern u8 D_800F2474_jp[4];
#endif

extern struct ObjectHeader* D_8013B8A8;
extern u16 D_8013B858[0x10];
extern s16 D_8013B878[0x10];
extern struct Unk_unk68* D_8013B8B0;
extern u8 D_8013B8B8;
extern struct ShotObj* general_fists[2];
extern void (*D_8012F490)(void);
extern s8 D_80173C6C[4];
extern u8 D_80137DFC;
extern u8 D_80137DFD;
extern struct SoundTransfer D_80137E00;
extern u8 D_80137DDC;
extern s32 D_8013BD44;
extern u8 D_8013BD40;
extern s16 D_80141BD2;
extern u8 layout_height;
#ifdef MMX4_PC
#define D_8010B465 (((u8*)search_light_spawners)[1])
#else
extern u8 D_8010B465;
#endif
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
extern s32 D_80139514;
extern u8 D_80139554[];
extern s8 D_80139568;
extern s16 D_8013955C;
#ifdef MMX4_SATURN
extern u16 D_80173C84;
#else
extern u8 D_80173C84;
#endif
extern s32 D_80175EE8[];
#ifdef MMX4_PC
#define D_8016DEA2 (D_8016DEA0.unk2)
#define D_8016DEA4 (D_8016DEA0.unk4)
#else
extern s16 D_8016DEA2;
extern s16 D_8016DEA4;
#endif
#ifdef MMX4_WIN32
#define D_801F8300 (*(struct GameThread**)(win32_main_ram + 0x1F8300))
#define GAME_THREADS ((struct GameThread*)(win32_main_ram + 0x1F8100))
#define CUR_GAME_THREAD (*(struct GameThread**)(win32_main_ram + 0x1F8300))
#else
extern struct GameThread* D_801F8300;
#define GAME_THREADS ((struct GameThread*)0x801F8100)
#define CUR_GAME_THREAD (*(struct GameThread**)0x801F8300)
#endif
extern struct MainObj main_objects[0x30]; // D_8013BED0
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
extern s16 magma_dragoon_arena_left;
extern s16 magma_dragoon_arena_right;
extern s16 magma_dragoon_arena_center;
extern s16 magma_dragoon_arena_floor;
extern s16 magma_dragoon_arena_ceiling;
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
extern struct LayerObj layer_objects[4];
extern struct RideArmorObj qux_object;
extern struct GameInfo game_info;
extern void (*D_800F485C[1])();
extern u8* D_80137DC4;
extern s32 D_80137DD0;
extern u32* D_801406A8;
extern u8 D_801406AC;
extern u8* D_8015D9C8;
extern u8 D_800EE47E[];
extern u8 D_801374B4;
extern u8 D_801374B8;
extern s8 D_80137CE4;
extern u8 D_80137CF0;
extern u8 D_80137CF4;
extern u8 D_8013BD40;
#if defined(MMX4_PC) || defined(MMX4_SATURN)
extern struct BootTransitionDataRegion g_BootTransitionDataRegion;
#define D_800F1C0F (g_BootTransitionDataRegion.stage_map)
#else
extern u8 D_800F1C0F[];
#endif
#ifndef MMX4_SATURN
extern CdlATV D_80139644;
#endif
extern u8 D_80171EA9;
extern u8 D_80166D68;
extern u8 D_8012F46C[0x22];
extern u16 cur_random;
extern s32 D_8013BD44;
extern s16 D_80141BD2;
extern u8 D_80139528;
#ifndef MMX4_SATURN
extern CdlATV D_80139520;
#endif
extern s32 D_80137CD8;
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
extern u8 D_801441B0;
extern u16* D_801441B4;
extern u8 D_801441B8;
extern u8* D_80137CC4;
extern s32 D_80137CCC;
extern u8 D_80137CE8;
extern s32 D_80137CEC;
#ifndef MMX4_SATURN
extern CdlLOC D_80137CF8;
extern DISPENV old_dispenv[2];
#endif
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
extern u8* D_80173C80;
extern u8 need_palette_load;
extern s8 D_801721F7;
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
#ifndef MMX4_SATURN
extern struct RectPtrPair vram_rect_ptrs[];
extern struct RectPtrPair* vram_rect_ptr;
#endif

extern u8* D_80141F00;
extern u8* D_80141EE8[];
extern u8* D_80141F50[];
extern u8* cur_draw_info_dispenv_screen_w;
extern u8* cur_draw_info_drawenv;

extern union CdSectorBuffer D_8012F4B4;
#ifndef MMX4_SATURN
extern RECT D_80137CFC;
#endif
extern s32 D_80137D08[];

void enemy_hit_reaction(struct MainObj*);

void func_800B5960(struct EffectObj* arg0);

void func_800BB9B8(struct EffectObj* arg0);

void func_800C9EAC(struct MiscObj* arg0);

void func_800CB00C(struct MiscObj* arg0);
void func_800CB848(struct MiscObj* arg0);

void func_800CD750(struct MiscObj* arg0);
void func_800CDC84(struct MiscObj* arg0);

void func_800D76F8(struct QuadObj* arg0);

void func_80029420(struct EngineObj* arg0);
void func_8002951C(struct EngineObj* arg0);
void func_8002979C(struct EngineObj* arg0);
void func_800297D8(struct EngineObj* arg0);
void func_800298B4(struct EngineObj* arg0);
void func_80029928(struct EngineObj* arg0);
void func_80029978(struct EngineObj* arg0);

s32 update_boss_music_delay(void);

// D_8010B34C
extern void (*D_8010B34C[])(struct EffectObj*);

// D_8010FDD0
extern void (*D_8010FDD0[])(struct QuadObj*);

void func_800D7154(struct QuadObj* arg0);

ret_u8 func_8002938C(s32);
extern u32 D_80141F30[8];
s32 func_800E5FF4(s32, s32, u8*);
void quad_is_on_screen(struct QuadObj*);
void drop_item(struct BaseObj*, s8);
void spawn_debris(arg_u8, void*, void*);
s32 update_boss_music_delay(void);
void func_800E5D78(s32);
s32 func_800E5D90(s32, s32, s32);
#ifdef MMX4_PC
void func_80016124(void);
#endif
s32 func_800E5ACC(void);
void func_800E6138(s8*);
extern void func_80013A20(void);
#ifdef MMX4_PC
void func_8002C36C(struct PlayerObj*, struct PlayerObj*, s32);
s32 func_8002D490(struct PlayerObj*);
void func_8002E294(struct PlayerObj*, struct PlayerObj*);
void func_8002E380(struct MovingObj*, struct MovingObj*, u8);
#endif
void func_800AF878(struct BaseObj*, s32, s32, s32);
void play_boss_voice(s32);

extern s32 loaded_vab_address;
extern s32 saved_vab_address;
extern s32 movie_slice_offset;
extern u8 cd_fade_requested;

#ifdef VERSION_EU
void func_800182E8(s32);
#else
void func_800182E8(void);
#endif

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
void func_800E0D0C(void);
void post_boss_cutscene_spawn_afterimages(struct UnkObj*);

#endif

#ifdef MMX4_SATURN
#include "saturn/game_prototypes.h"
#endif

#ifdef MMX4_PC
#include "pc_build.h"
#endif

#ifdef MMX4_WIN32
extern u32 D_800F44C4;
extern u32 D_800F44D8;
#elif defined(MMX4_SATURN)
extern u16 D_800F44C4[9];
extern u16 D_800F44D8[7];
#else
extern u16 D_800F44C4[9]; // secret code sequence
extern u16 D_800F44D8[8]; // secret code sequence
#endif

#ifdef MMX4_WIN32
u8 angle_from_delta(s32 arg0, s32 arg1);
u8 func_8001E850(u8* arg0, u8 arg1);
u8 get_random();
#endif
#ifdef MMX4_WIN32
void player_start_script_action(s8 action, s8 facing);
#endif
void spawn_explosion(struct BaseObj* arg0);

#endif
