#define INCLUDE_ASM(FOLDER, NAME)                   \
    __asm__(".pushsection .text\n"                  \
            "\t.align\t2\n"                         \
            "\t.globl\t" #NAME "\n"                 \
            "\t.ent\t" #NAME "\n" #NAME ":\n"       \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            "\t.set reorder\n"                      \
            "\t.set at\n"                           \
            "\t.end\t" #NAME "\n"                   \
            ".popsection");

__asm__(".include \"macro.inc\"\n");

#define NULL ((void*)0)
#define FIXED(x) ((s32)((x)*0x10000))
#define COUNT(x) (sizeof(x) / sizeof(x[0]))

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#include "psy-q-4.0/SYS/TYPES.H"
#include "psy-q-4.0/LIBGTE.H"
#include "psy-q-4.0/LIBGPU.H"
#include "psy-q-4.0/LIBSND.H"
#include "psy-q-4.0/LIBETC.H"
#include "psy-q-4.0/KERNEL.H"
#include "psy-q-4.0/LIBCD.H"
#include "psy-q-4.0/LIBPRESS.H"

#include "scratchpad.h"
#include "archive_memory.h"

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

struct CdImageOrigin { u16 x, y; };
struct HudSpriteOrigin { s16 x, y; u16 clut; };
struct StageObjectMarginData { u16 margins[5]; u16 alignment_padding; };
struct MainFlags { s32 unk0; };
struct MainBssState {
    struct MainFlags flags;
    s8 transition[4];
    u8 character_mode;
    u8 alignment_padding[3];
};
struct FadeState { s16 unk0, unk2; u16 unk4, alignment_padding; };
struct ArchiveSelectionData { u8 prefix[8]; u8 archive_ids[124]; };
union CdSectorBuffer { u8 sectors[16][0x800]; u32 words[0x2000]; };
struct MissionSelectData {
    u8 stage_order[12];
    u8 route_a[8];
    u8 route_b[8];
    u16 route_a_positions[4];
    u16 route_b_positions[3];
    u16 briefing_sound_ids[11];
};
struct TitleObjectInit { s16 x, y; s8 sprite, flags; };
struct SearchLightInit { s16 vertices[8]; u16 extent; };
struct SearchLightColorLookup { u16 values[3]; u16 alignment; };
struct SearchLightIntensityLookup { u8 values[3]; u8 alignment; };
struct SearchLightSpawner {
    u8 active, type, reserved, background_index;
    s16 x, y;
};
struct CharacterSelectPosition { s16 x, y; };
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
struct ArchivePathData { s8 stage_archive_indices[12]; char paths[163][64]; };
struct VisualAttachmentOffset { s16 x, y; };
struct VisualAttachmentInit { u8 archive_slot, animation, sound; };
struct VisualSpawnOffset { s8 x, y; };
struct VisualBounds { s16 x, y; };
struct CdCompletionSlot {
    u8 pending, callback;
    u16 pad2;
    u32 callback_arg;
    u16 transfer_pending, padA;
};
typedef char CdCompletionSlot_must_be_12_bytes[
    sizeof(struct CdCompletionSlot) == 12 ? 1 : -1];
struct BackgroundCameraModePair { u8 primary, secondary; };
struct PlayerGaugePosition { s16 x; u16 bottom; };
struct BackgroundLayoutConfig { u8 object_ids[4]; u8 layer_ids[3][2]; };
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
struct BootTransitionDataRegion {
    u8 preceding_record_tail[3];
    u8 stage_map[9];
} __attribute__((packed));

extern struct MissionSelectData D_800F474C;
extern union PlayerChargeData D_800F8BE0;

typedef union {
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } i;
} f32;

struct BaseObj {
    s8 active;
    s8 id; // 0x01
    s8 unk2;
    s8 on_screen; // 0x03
    s8 state;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    f32 x_pos; // 0x8 and 0xA
    f32 y_pos; // 0xC and 0xE
    s32 unk10;
    s8 bg_offset;
    u8 unk15;
    u8 unk16;
    u8 unk17;
};

struct Unk {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x8];
    s16 animation_speed;
    u8 pad39[5];
    u16 unk40;
    u16 unk42;
    s8 pad43[9];
    s32 unk50;
    s32 unk54;
    s8 pad55[4];
    s8 unk5C;
    s8 unk5D;
    u8 pad2f[3];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    struct Unk_unk68* unk68;
    s16 : 16;
    s16 unk6E;
    u8 unk70;
    s8 : 8;
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 unk79;
    s8 unk7A;
    u8 pad68[0x10];
    u16 unk8C;
    u32 unk90;
    u32 unk94;
    u32 pad98;
}; // size 0x9c

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
    s16 unk34;
    u8 pad32[10];
    u16 unk40;
    u16 unk42;
    s8 unk44;
    u8 pad45[2];
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    s8 unk4D;
    s8 unk4E;
    s8 min_y;
    s8 max_y;
    s8 pad51[3];
}; // size 0x54

// similar to Unk
struct PlayerObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x8];
    s32* unk38;
    s32 unk3C;
    u16 unk40;
    u16 unk42;
    s8 unk44;
    s8 unk45;
    s8 unk46;
    u8 cur_anim; // 0x47
    u8 prev_anim; // 0x48
    s8 unk49;
    s8 unk4A;
    s8 pad4B[0x50 - 0x4B];
    s32 unk50;
    s32 unk54;
    s8 pad55[4];
    s8 unk5C;
    s8 unk5D;
    u8 pad2f[3];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    struct Unk_unk68* unk68;
    s16 : 16;
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
    u32 unk7C;
    u16 unk80;
    u16 unk82;
    s8 unk84;
    s8 : 8;
    s8 unk86;
    s8 unk87;
    s8 unk88;
    u8 unk89;
    u16 unk8A;
    s8 unk8C;
    s8 : 8;
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
    s8 unk9B[2];
    u8 unk9D;
    u8 unk9E;
    s8 unk9F;
    s8 unkA0;
    s8 unkA1;
    s8 unkA2;
    s8 : 8;
    s8 unkA4;
    s8 : 8;
    s8 unkA6;
    s8 unkA7;
    s8 unkA8;
    u8 padA9[0xB8 - 0xA9];
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
    s8 padC6[0xC8 - 0xC6];
    s32 unkC8;
    s32 unkCC;
    s32 unkD0;
    s8 unkD4;
    s8 padD5[0xD7 - 0xD5];
    s8 unkD7;
    s8 : 8;
    s8 unkD9;
    u16 unkDA;
    s8 padDC[0xDE - 0xDC];
    s8 unkDE;
    s8 : 8;
    s8 unkE0;
    s8 unkE1;
    s8 padE2[0xE4 - 0xE2];
}; // size 0xE4

struct Unk_unk68 {
    s8 unk0;
    s8 unk1;
    u8 unk2;
    u8 unk3;
};

struct VisualObj {
    struct BaseObj base;
    s8 pad18[0x20 - 0x18];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    void* unk30;
    s32 : 32;
    s32 unk38;
    void* unk3C;
    u16 unk40;
    u16 unk42;
    s8 unk44;
    s8 unk45;
    s8 unk46;
    u8 unk47;
    u8 unk48;
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

struct ShotObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s8 pad20[0x42 - 0x20];
    u16 unk42;
    s8 pad44[0x50 - 0x44];
    s32 unk50;
    s32 unk54;
    s32 : 32;
    s8 unk5C;
    s8 pad5D[0x61 - 0x5D];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 : 8;
    s32 unk68;
    s8 pad6C[0x72 - 0x6C];
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
    struct WeaponObj* unk7C; // might be something else
    s32 : 32;
    s32 unk84;
    s32 : 32;
    s8 unk8C;
    s8 pad8D[0x98 - 0x8D];
    s8 unk98;
    s8 pad99[0x9C - 0x99];
}; // size 0x9C

struct WeaponObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s8 pad20[0x30 - 0x20];
    s32 unk30;
    s8 pad34[0x3C - 0x34];
    void* unk3C;
    u16 unk40;
    u16 unk42;
    s8 pad44[0x50 - 0x44];
    s32 unk50;
    s32 unk54;
    s8 pad58[0x61 - 0x58];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 : 8;
    s32 unk68;
    s8 pad6C[0x72 - 0x6C];
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 : 8;
    s8 unk7A;
    s8 pad7B[0x8C - 0x7B];
    s8 unk8C;
    s8 pad8D[0x94 - 0x8D];
    u8 unk94;
    s8 pad95[0x98 - 0x95];
    s8 unk98;
    s8 pad99[0x9C - 0x99];
}; // size 0x9C

struct UnkObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s8** unk30;
    s32 : 32;
    s16 unk38;
    s16 : 16;
    s32 unk3C;
    u16 unk40;
    u16 unk42;
    s8 pad44[0x47 - 0x44];
    s8 unk47;
    s8 pad48[0x50 - 0x48];
    u8* unk50;
    u8 unk54;
    u8 pad55[0x60 - 0x55];
}; // size 0x60

struct ItemObj {
    struct BaseObj base;
    f32 unk18;
    f32 unk1C;
    s8 pad20[0x50 - 0x20];
    s32 unk50;
    s32 unk54;
    s8 pad58[0x61 - 0x58];
    s8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 : 8;
    s32 unk68;
    s8 pad6C[0x72 - 0x6C];
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    s8 : 8;
    s8 unk7A;
    s8 pad7B[0x8C - 0x7B];
}; // size 0x8C

struct LayerObj {
    struct BaseObj base;
    f32 unk18;
    f32 unk1C;
    s8 pad20[0x30 - 0x20];
}; // size 0x30

struct MiscUnk50_1 {
    u8 pad[0x16];
    u8 unk16;
};

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
    struct MiscUnk50_1* unk50;
    u16 unk54;
    u16 stay_up_timer; // 0x56
    u16 palette_pos;
    u16 unk58;
    u16 palette_cycle_done; // 0x5C
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
    struct ReadyTextExt ready_text;
    struct TitleLogoExt title_logo;
    struct SelectACharacterExt sel_char;
    struct UnkExt unk;
};

struct MiscObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    f32 x_vel; // 0x20
    f32 y_vel;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad30[0x4];
    s32 unk38;
    void* unk3C;
    u16 unk40;
    u16 unk42;
    s8 unk44;
    s8 unk45;
    s8 unk46;
    s8 unk47;
    s8 pad47[5];
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
    struct BaseObj base;
    s8 pad18[0x50 - 0x18];
}; // size 0x50

struct QuxObj {
    struct BaseObj base;
    s32 unk18;
    s32 unk1C;
    s8 pad20[0x5C - 0x20];
    s8 unk5C;
    s8 pad5D[0x8A - 0x5D];
    s16 unk8A;
    s16 unk8C;
    s8 pad8E[0x97 - 0x8E];
    s8 unk97;
    s8 pad98[0xB0 - 0x98];
}; // size 0xB0

// D_8013BC28
struct AbcObj {
    s8 pad0[4];
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

struct Unk6 {
    u8 pad0[5];
    u8 unk5;
    u8 pad5[4];
    s16 unkA;
    s16 padc;
    s16 unkE;
    u8 pad6[0x19];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x3];
    u16 unk40;
    u16 unk42;
    u8 pad2f[0x37];
    s8 unk67;
};
struct Unk7 {
    u8 pad[0x80];
    u16 unk80;
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
    u8 pad[0x4000];
};

struct MainPrimitiveBuffer {
    u8 data[0xA000];
};

struct SecondaryPrimitiveBuffer {
    u8 data[0x2000];
};

struct BackgroundPrimitiveBuffer {
    u8 data[0x200];
};

struct OrderingTableBuffer {
    u8 data[0x100];
};

struct AuxiliaryPrimitiveBuffer {
    u8 data[0x78];
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
extern struct Unk16 D_80141BD8;
extern struct BackgroundObj background_objects[];
extern struct BgDrawRelated D_8015D9D0[];
extern struct MainPrimitiveBuffer temp1[];
extern struct SecondaryPrimitiveBuffer temp2[];
extern struct BackgroundPrimitiveBuffer temp3[];
extern struct OrderingTableBuffer temp4[];
extern struct AuxiliaryPrimitiveBuffer temp5[];
extern struct StageSpriteSlot D_8013B7B0[2];
extern struct OrderingTableBuffer D_8012F498[];
extern struct SecondaryPrimitiveBuffer D_80169D78[];
extern struct BackgroundPrimitiveBuffer D_8016DEA0;

struct DrawInfo {
    DISPENV dispenv;
    DRAWENV drawenv; // 0x14
    u32 unk70;
    u8 pad70[12];
    u32 unk80;
    u8 pad80[24];
    u32 unk9C;
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

struct QuadUnkExt {
    u16 unk38;
};

struct QuadUnkExt2 {
    u16 unk38;
    s16 : 16;
    s16 unk3C;
    s16 : 16;
    s16 : 16;
    u8 unk42;
    u8 unk43;
};

struct QuadUnkExt3 {
    u8 unk38;
};

struct QuadUnkExt4 {
    s32 : 32;
    u16 unk3C;
};

union QuadExt {
    struct ReadyLineExt ready_line;
    struct QuadUnkExt unk_ext;
    struct QuadUnkExt2 unk_ext2;
    struct QuadUnkExt3 unk_ext3;
    struct QuadUnkExt4 unk_ext4;
    u32 unk38;
};

struct QuadObj {
    s8 active;
    s8 id; // 0x01
    s8 unk2;
    s8 on_screen;
    s8 state;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    f32 x_pos;
    f32 y_pos;
    s8 pad10[4];
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
    struct BaseObj* unk58; // might be something else
    struct PlayerObj* unk5C; // might be something else
}; // size 0x60

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
    s8 unk26[0x2C - 0x26];
    s32 unk2C;
    s8 pad30[0x36 - 0x30];
    s8 pad36;
    s8 unk37;
    void* unk38;
    struct BaseObj* unk3C;
    u8 unk40;
    s8 unk41;
    u8 unk42;
    s8 cur_character; // 0x43
    s8 unk44;
    u8 pad45;
    s8 unk46;
    s8 unk47;
    s8 unk48;
    s8 pad49[0x5A - 0x49];
    u16 unk5A;
    s8 pad5C[0x5F - 0x5C];
    u8 unk5F;
    s32 : 32;
}; // size 0x64

#define ENGINE_STAGE_ID (*(u16*)&engine_obj.stage)
#define ENGINE_CHECKPOINT (*(u8*)&engine_obj.checkpoint)
#define ENGINE_UNK2E (((s8*)&engine_obj.unk2C)[2])

extern u8 engine_obj_27;
#define engine_flags engine_obj_27

struct Unk18 {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s8 unk4;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    s8 unk8;
    s8 unk9[4];
    u8* unk10;
};

struct Unk19 {
    u8 pad[0x7];
    s32 unk8;
    s32 unkC;
    u8 pad6[0x7];
    s8 unk17;
    s8 pad2[0x6];
    s32 unk20;
    s32 unk24;
    u8 pad345[5];
    u32* unk30;
    u32* unk34;
    s8 pad3[0xc];
    u32 unk44;
    u8 unk48;
};

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

struct MainObj {
    struct BaseObj base;
    f32 unk18;
    f32 unk1C;
    s8 pad20[0x9C - 0x20];
};

struct Unk14 {
    u16 unk0;
    s8 unk2;
    u8 unk3;
};

struct UnkEffectExt {
    u8 unk14;
    s8 unk15;
    s8 unk16;
    s8 : 8;
    s32 unk18;
};
struct EffectExt2 {
    struct Unk14* unk14;
    Multi unk18;
    u8 pad18[4];
    s8 unk20;
    s8 pad20[12];
};

struct ScalingX {
    struct Unk14* unk14;
    s8 unk18;
};

struct EffectUnk3 {
    s32* unk14;
    s32 pad;
    s8* unk1C;
    u8 pad20;
    s8 unk21;
};

union EffectExt {
    struct UnkEffectExt unk_effect;
    struct EffectExt2 unk_effect2;
    struct ScalingX scaling_x;
    struct EffectUnk3 unk3;
};

struct EffectObj {
    s8 active;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s8 state;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    f32 x_pos; // 0x8 and 0xA
    f32 y_pos; // 0xC and 0xE
    s32 unk10;
    union EffectExt ext;
}; // size 0x30

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
extern struct Unk_unk68 D_800F8BC4;
extern struct Unk_unk68 D_800F8BC8;
extern s8 D_800F8BF8[];
extern s8 D_800F8C10[];
extern s8 D_800F8C28[];
extern u8 D_800F8C4C[];
extern u8 D_800F8C4D[];
extern s8 D_800F8CCC[];
extern s8 D_800F8CE4[];
extern s8 D_800F8CFC[];
extern s8 D_800F8D14[];
extern struct VisualAttachmentOffset D_8010A1AC[2];
extern struct VisualAttachmentOffset D_8010A1B4[2];
extern struct VisualAttachmentInit D_8010A1BC[4];
extern const u32* D_8010A4C0[3];
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
extern s8* D_8010ECD4[];
extern s8 D_8010FE38[];
extern u8 D_8010FED4[];
extern u8 D_801193F0[];
extern u32 D_801194F0[];
extern u8 D_8011A030[];
extern u8 D_8011A130[];
extern u32 D_8011A230[];
extern u8 D_8011AF60[];
extern u32* D_8011BF40[54];
extern u32* D_8011C0E4[3];
extern s8 D_80141BDC[];
extern s8 D_80141BDE[];
extern u8 D_80141BDF[];
extern u8 D_80141BE0;
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
extern u8 D_800F2180[];
extern u8 D_800F21A0[];
extern s16 D_800F21DC[];
extern u8 D_800F21F8[];
extern u8 D_800F22D0[];
extern u8 D_800F22E0[];
extern u8 D_800F2300[16];
extern u8 D_800F2328[16];
extern RECT D_800F2428;
extern RECT D_800F2430;
extern u8 D_800F2468[];
extern u8 D_800F247C[];
extern u8 D_800F2490[];
extern struct BackgroundCameraModePair D_800F32D4[16][2];
extern s32 D_800EE458;
extern s32 D_8012F490;
extern s8 D_80173C6C;
extern s8 D_80173C6D;
extern s8 D_80173C6E;
extern s8 D_80173C6F;
extern s8 D_80137DFC;
extern u8 D_80137DD4;
extern u8 D_80137DDC;
extern s32 D_8013BD44;
extern u8 D_8013BD40;
extern s16 D_80141BD2;
extern struct BackgroundLayoutConfigData D_800F3188;
extern struct StageObjectRecord* D_800F4430[13][2];
extern struct StageObjectRecord* D_800F43C8[13][2];
extern u8* D_8010FFDC[][2];
extern u8 layout_height;
extern u16 D_80166C08;
extern u16 D_80166C0A;
extern s8 D_800F8BE9[];
extern u8 D_800FB0EC[8];
extern void (*D_800FB104[])();
extern u8 D_8010B465;
extern u8 x_ready_text_flags[];
#define D_800F2CA4 ((const u32* const**)(x_ready_text_flags + 0x10))
extern struct MiscUnk50_1* const* D_800F2DD8[];
extern const u32* const* D_800F2EE8[];
extern const u32* const* D_800F2F00[];
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
extern void* D_80137E0C;
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
extern struct BaseObj* D_80139690;
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
extern s16 D_8016DEA2;
extern s16 D_8016DEA4;
extern struct GameThread* D_801F8300;
extern u16 D_801419BE[];
extern void (*g_MegamanInBriefingRoomUpdateFuncs[2])();
extern void (*g_TitleUpdateFuncs[])();
extern void (*D_8010EB84[4])();
extern void (*g_SelectACharacterUpdateFuncs[3])();
extern struct Unk main_objects[0x30]; // D_8013BED0
extern void (*g_SearchLightUpdateFuncs[3])();
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
extern s16 D_8013B804;
extern struct MiscObj* D_8013B808;
extern u8* D_8013B80C;
extern s8 D_8013B810;
extern u8 D_8013B814;
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
extern struct LayerObj layer_objects[4];
extern struct QuxObj qux_object;
extern struct GameInfo game_info;
extern void (*D_800F485C[1])();
extern void (*ReadyTextUpdateFuncs[3])();
extern s32 D_80137DC4;
extern s32 D_80137DD0;
extern u32* D_801406A8;
extern u8 D_801406AC;
extern s32 D_80142F70;
extern s32 D_8015D9C8;
extern u8 D_801374B4;
extern s8 D_801374B8;
extern s8 D_80137CE4;
extern s8 D_80137CF0;
extern s8 D_80137CF4;
extern u8 D_8013BD40;
extern u8 D_800F1C0F[];
extern u32 D_800F1D8C;
extern u8 D_800F1D90;
extern CdlATV D_80139644;
extern s8 D_80139645;
extern s8 D_80139646;
extern s8 D_80139647;
extern u8 D_80171EA9;
extern s32 D_80166BB4;
extern u8 D_80166D68;
extern s32 D_8012F46C;
extern u16 D_800EE430[];
extern RECT D_800EE450;
extern u16 cur_random;
extern s32 D_8013BD44;
extern s16 D_80141BD2;
extern s8 D_80139528;
extern CdlATV D_80139520;
extern s32 D_80137CD8;
extern RECT D_800F1658;
extern u32 D_80141F70;
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
extern s32 D_80137CC4;
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
extern s32 D_80173C80;
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
extern s8 g_FilterModeR;
extern s8 g_FilterModeG;
extern s8 g_FilterModeB;
// how much to add or subtract to each channel
extern u16 g_FilterAmountR;
extern s16 g_FilterAmountB;
extern s16 g_FilterAmountG;
extern u16 controller_state;
extern s8 D_801419FC;
extern u8 D_800F4508[0x20];
extern u8* D_800F4560[];
extern u8 D_800F4568[0x14];
extern u8 D_800F457C[0x14];
extern u8* D_800F4834[10];
extern void (*D_800F3134[])(struct BackgroundObj* arg0);
extern struct Prim D_800EE504[];
extern struct RectPtrPair vram_rect_ptrs[];
extern struct RectPtrPair* vram_rect_ptr;
extern u8 D_800F30D4[16][2];
struct XaSequenceParams { u8 sequence, volume; };
struct XaSequenceData {
    struct XaSequenceParams stage[16][2][2];
    struct XaSequenceParams alternate[16];
};
extern struct XaSequenceData D_800F1A0C;
extern u8* D_80141F00;
extern u8* cur_draw_info_dispenv_screen_w;
extern u8* cur_draw_info_drawenv;

void func_8001293C(void);
void TeleportRelatedObjectUpdate(struct EffectObj*);
void func_8009ED70(struct Unk*);
extern s32* D_8012F4B4[];
extern RECT D_80137CFC;
extern s32 D_80137D08[];

#include "func_tables.h"

s32 func_80034E2C();
s32 func_80034F7C();
void func_800129F0(s32);
void func_800127C8(s32);
void func_80012A3C();
s32 func_8001540C(s32, s32, struct Unk6*);
s32 func_800350A4(struct PlayerObj*, s32);
void func_8002B318(struct BaseObj*, s32, s32);
void func_800127C8(s32);
void func_800127FC(void);
void func_800129A4(s8);
void func_80013530(void);
void func_80013AD8(u8, u8, s32);
void func_800261B4(s32, u32, u8*);
void func_80028FEC(s16, s16, s16, s16, u8);
void func_800292D0(s32);
void func_80094F74(void);
void func_80015284(void);
void func_8001C3E8(void);
void reset_game_engine(void);
void func_8001DC30(void);
s32 func_80015D60(struct Unk19*, s32);
void func_80015DC8();
s32 func_80033694();
void func_80034538(struct Unk7*);
void func_80034754(struct Unk7*);
void func_80025188(s32, u8);
void func_80025588(s16, s16, s16, s16, s32);
void func_80027AAC(struct BackgroundObj*);
void func_80027AFC(struct Unk9*);
void func_80027B70(struct Unk9*);
void func_80027BE4(struct BackgroundObj*);
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
void ZeroObjectState(struct Unk18* arg0);
void init_objects();
void func_80026648();
s16 func_8002BAD0(s16, s16, s16);
u8 func_800D8E94(struct LayerObj*);
u8 func_800D9B08(struct LayerObj*);
void func_800DA984(u8);
s32 func_800E5FF4(s32, s32, u8*);
void func_800AE6B4(struct BazObj*);
struct Unk* func_800AFAB4(s8, s16, s16, u8);
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
void func_8002B718();
void is_on_screen(struct BaseObj*);
s32 func_8002CF98(struct Unk*, u8, s16, s16);
s32 func_8002D32C(struct PlayerObj*, s16, s32);
s32 func_8002D5E4(struct PlayerObj*, s16);
u8 func_8002D724(struct PlayerObj*, s16, s16);
s32 func_8002D7E4(struct Unk*, s16, s16);
u8 func_8002D900(struct PlayerObj*);
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
extern void func_80013E68(void);
void func_80013650(void);
s8 func_800136B0();
void func_800137F0();
void MyCdReadyCallback(void);
void func_80018000(s32);

enum SelectedPlayer {
    CHARACTER_X,
    CHARACTER_ZERO
};
