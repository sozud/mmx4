#include "common.h"
#include "func_tables.h"

void (*D_800FEF80[5])() = {
    func_8009216C,
    func_80062E70,
    func_80062E90,
    func_80062F60,
    func_800630AC,
};

union AnimationStep D_800FEF94[] = {
    { 0x00010007 },
    { 0x00FF0001 },
};

union AnimationStep D_800FEF9C[] = {
    { 0x01010002 },
    { 0x02010005 },
    { 0x03010011 },
    { 0x04010006 },
    { 0x05010008 },
    { 0x06010006 },
    { 0x07010008 },
    { 0x06010006 },
    { 0x05010007 },
    { 0x08010007 },
    { 0x09010008 },
    { 0x08010008 },
    { 0x0501010A },
    { 0x0601000A },
    { 0x07010008 },
    { 0x0A01002B },
    { 0x0B010002 },
    { 0x0C010020 },
    { 0x0C000001 },
};

union AnimationStep D_800FEFE8[] = {
    { 0x05010102 },
    { 0x0D010002 },
    { 0x0F010003 },
    { 0x0D010002 },
    { 0x05010102 },
    { 0x0E010003 },
    { 0x0EFA0001 },
};

union AnimationStep D_800FF004[] = {
    { 0x05010105 },
    { 0x0D010005 },
    { 0x0F010007 },
    { 0x0D010105 },
    { 0x05010005 },
    { 0x0E010007 },
    { 0x0EFA0001 },
};

union AnimationStep D_800FF020[] = {
    { 0x05010005 },
    { 0x10010008 },
    { 0x01010004 },
    { 0x02010004 },
    { 0x11010205 },
    { 0x12010005 },
    { 0x1301000F },
    { 0x14010102 },
    { 0x15010028 },
    { 0x15000001 },
};

union AnimationStep D_800FF048[] = {
    { 0x05010003 },
    { 0x10010004 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x11010203 },
    { 0x12010003 },
    { 0x13010008 },
    { 0x14010102 },
    { 0x15010018 },
    { 0x12010003 },
    { 0x13010008 },
    { 0x14010102 },
    { 0x15010018 },
    { 0x15000001 },
};

union AnimationStep D_800FF080[] = {
    { 0x05010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x11010105 },
    { 0x02010003 },
    { 0x01010003 },
    { 0x0001003C },
    { 0x00000001 },
};

union AnimationStep D_800FF0B8[] = {
    { 0x0501000D },
    { 0x16010103 },
    { 0x17010005 },
    { 0x18010008 },
    { 0x17010004 },
    { 0x16010013 },
    { 0x16000001 },
};

union AnimationStep D_800FF0D4[] = {
    { 0x16010005 },
    { 0x19010105 },
    { 0x1A010005 },
    { 0x1B010005 },
    { 0x1C010105 },
    { 0x1D010005 },
    { 0x1E010005 },
    { 0x1F010105 },
    { 0x1F000001 },
};

union AnimationStep D_800FF0F8[] = {
    { 0x20010005 },
    { 0x21010105 },
    { 0x22010005 },
    { 0x23010005 },
    { 0x24010105 },
    { 0x25010005 },
    { 0x26010005 },
    { 0x27010105 },
    { 0x27000001 },
};

union AnimationStep D_800FF11C[] = {
    { 0x16010005 },
    { 0x1F010105 },
    { 0x1E010005 },
    { 0x1D010005 },
    { 0x1C010105 },
    { 0x1B010005 },
    { 0x1A010005 },
    { 0x19010105 },
    { 0x19000001 },
};

union AnimationStep D_800FF140[] = {
    { 0x20010005 },
    { 0x27010105 },
    { 0x26010005 },
    { 0x25010005 },
    { 0x24010105 },
    { 0x23010005 },
    { 0x22010005 },
    { 0x21010105 },
    { 0x21000001 },
};

union AnimationStep D_800FF164[] = {
    { 0x16010003 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2A010003 },
    { 0x2B010203 },
    { 0x2C010003 },
    { 0x2D01000A },
    { 0x2E010102 },
    { 0x2F010040 },
    { 0x2F000001 },
};

union AnimationStep D_800FF18C[] = {
    { 0x16010003 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2A010003 },
    { 0x2B010203 },
    { 0x2C010003 },
    { 0x2D01000A },
    { 0x2E010102 },
    { 0x2F010040 },
    { 0x2C010003 },
    { 0x2D01000A },
    { 0x2E010102 },
    { 0x2F010016 },
    { 0x2F000001 },
};

union AnimationStep D_800FF1C4[] = {
    { 0x1601000A },
    { 0x30010001 },
    { 0x31010001 },
    { 0x30010001 },
    { 0x32010001 },
    { 0x30010001 },
    { 0x31010001 },
    { 0x30010001 },
    { 0x32010001 },
    { 0x30010001 },
    { 0x31010001 },
    { 0x30010001 },
    { 0x32010001 },
    { 0x2D010002 },
    { 0x2C010002 },
    { 0x2B010002 },
    { 0x2A010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x37010002 },
    { 0x36010002 },
    { 0x37010020 },
    { 0x37010101 },
    { 0x36010002 },
    { 0x37010028 },
    { 0x37000001 },
};

union AnimationStep D_800FF230[] = {
    { 0x35010002 },
    { 0x34010002 },
    { 0x38010002 },
    { 0x16010020 },
    { 0x16000001 },
};

union AnimationStep D_800FF244[] = {
    { 0x05010003 },
    { 0x39010003 },
    { 0x3A010003 },
    { 0x3B010003 },
    { 0x3B000001 },
};

union AnimationStep D_800FF258[] = {
    { 0x3C010003 },
    { 0x3DFF0003 },
};

union AnimationStep D_800FF260[] = {
    { 0x3E010102 },
    { 0x3F010002 },
    { 0x40010003 },
    { 0x41010003 },
    { 0x3B010005 },
    { 0x3C010004 },
    { 0x3E010103 },
    { 0x3A010004 },
    { 0x3B010004 },
    { 0x42010014 },
    { 0x43010006 },
    { 0x44010003 },
    { 0x45010003 },
    { 0x4601000A },
    { 0x45010003 },
    { 0x44010003 },
    { 0x43010003 },
    { 0x47010003 },
    { 0x48010003 },
    { 0x49010003 },
    { 0x4A010003 },
    { 0x4B010006 },
    { 0x4A01001E },
    { 0x4A000001 },
};

union AnimationStep D_800FF2C0[] = {
    { 0x4B010004 },
    { 0x4C010004 },
    { 0x4D010004 },
    { 0x4F010003 },
    { 0x4E010103 },
    { 0x4F010003 },
    { 0x50010003 },
    { 0x4F010003 },
    { 0x4E01001F },
    { 0x4E000001 },
};

union AnimationStep D_800FF2E8[] = {
    { 0x51010001 },
    { 0x52010001 },
    { 0x53010001 },
    { 0x54FD0001 },
};

union AnimationStep D_800FF2F8[] = {
    { 0x55010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x5E010001 },
    { 0x5F010001 },
    { 0x60010001 },
    { 0x61010001 },
    { 0x62010001 },
    { 0x63010001 },
    { 0x63000001 },
};

union AnimationStep D_800FF338[] = {
    { 0x64010001 },
    { 0x65010001 },
    { 0x66FE0001 },
};

union AnimationStep D_800FF344[] = {
    { 0x66010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x66010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x66010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x67010001 },
    { 0x68010001 },
    { 0x68000001 },
};

union AnimationStep D_800FF384[] = {
    { 0x69010002 },
    { 0x6A010002 },
    { 0x69010002 },
    { 0x6A010002 },
    { 0x69010001 },
    { 0x6A010001 },
    { 0x69010001 },
    { 0x6AF90001 },
};

union AnimationStep D_800FF3A4[] = {
    { 0x6B010001 },
    { 0x6C010001 },
    { 0x6D010001 },
    { 0x6EFD0001 },
};

union AnimationStep D_800FF3B4[] = {
    { 0x6F010001 },
    { 0x70010001 },
    { 0x71010001 },
    { 0x70010001 },
    { 0x72010001 },
    { 0x70010001 },
    { 0x70FA0001 },
};

union AnimationStep D_800FF3D0[] = {
    { 0x73010001 },
    { 0x76010001 },
    { 0x74010001 },
    { 0x76010001 },
    { 0x75010001 },
    { 0x76010001 },
    { 0x76FA0001 },
};

union AnimationStep D_800FF3EC[] = {
    { 0x77010005 },
    { 0x78010005 },
    { 0x79010005 },
    { 0x7A010005 },
    { 0x7B010106 },
    { 0x7C010005 },
    { 0x7D010004 },
    { 0x7E010004 },
    { 0x7F010004 },
    { 0x80010004 },
    { 0x81010006 },
    { 0x82010106 },
    { 0x83010006 },
    { 0x84F30006 },
};

union AnimationStep D_800FF424[] = {
    { 0x77010108 },
    { 0x78010004 },
    { 0x79010004 },
    { 0x7A010004 },
    { 0x7B010108 },
    { 0x7A010004 },
    { 0x79010004 },
    { 0x78F90004 },
};

union AnimationStep D_800FF444[] = {
    { 0x85010008 },
    { 0x86010004 },
    { 0x87010004 },
    { 0x88010004 },
    { 0x89010008 },
    { 0x8A010004 },
    { 0x8B010004 },
    { 0x8C010004 },
    { 0x8CF80001 },
};

union AnimationStep D_800FF468[] = {
    { 0x8D010004 },
    { 0x8E010002 },
    { 0x8F010008 },
    { 0x8E010004 },
    { 0x8D010004 },
    { 0x8D000001 },
};

union AnimationStep D_800FF480[] = {
    { 0x8D010004 },
    { 0x90010002 },
    { 0x91010008 },
    { 0x92010004 },
    { 0x93010004 },
    { 0x90010004 },
    { 0x8DFA0004 },
};

union AnimationStep D_800FF49C[] = {
    { 0x94010004 },
    { 0x95010002 },
    { 0x96010008 },
    { 0x97010004 },
    { 0x98010004 },
    { 0x95010004 },
    { 0x94FA0004 },
};

union AnimationStep D_800FF4B8[] = {
    { 0x01010002 },
    { 0x02010005 },
    { 0x03010011 },
    { 0x04010006 },
    { 0x05010008 },
    { 0x06010006 },
    { 0x07010008 },
    { 0x06010006 },
    { 0x06000001 },
};

union AnimationStep D_800FF4DC[] = {
    { 0x05010007 },
    { 0x08010007 },
    { 0x09010008 },
    { 0x08010008 },
    { 0x0501000A },
    { 0x0601000A },
    { 0x07010008 },
    { 0x06010008 },
    { 0x06000001 },
};

union AnimationStep D_800FF500[] = {
    { 0x3C000001 },
};

union AnimationStep* web_spider_animations[40] = {
    D_800FEF94,
    D_800FEF9C,
    D_800FF004,
    D_800FF020,
    D_800FF080,
    D_800FF0B8,
    D_800FF0D4,
    D_800FF0F8,
    D_800FF11C,
    D_800FF140,
    D_800FF164,
    D_800FF1C4,
    D_800FF230,
    D_800FF244,
    D_800FF258,
    D_800FF260,
    D_800FF2C0,
    D_800FF2E8,
    D_800FF2F8,
    D_800FF338,
    D_800FF344,
    D_800FF384,
    D_800FF3A4,
    D_800FF3B4,
    D_800FF3D0,
    D_800FF3EC,
    D_800FF424,
    D_800FF444,
    D_800FF468,
    D_800FF480,
    D_800FF49C,
    D_800FEFE8,
    D_800FF4B8,
    D_800FF4DC,
    D_800FF500,
    D_800FF500,
    D_800FF500,
    D_800FF500,
    D_800FF048,
    D_800FF18C,
};

u8 D_800FF5A4[4] = { 13, 14, 15, 16 };

struct Unk_unk68 D_800FF5A8 = { -21, -21, 40, 34 };

struct Unk_unk68 D_800FF5AC = { -23, -30, 44, 57 };

struct Unk_unk68 D_800FF5B0 = { 0, 0, 24, 19 };

struct Unk_unk68 D_800FF5B4 = { -5, -8, 11, 15 };

struct Unk_unk68 D_800FF5B8 = { -10, -8, 18, 15 };

struct Unk_unk68 D_800FF5BC = { 0, 0, 8, 8 };

RECT D_800FF5C0[4] = {
    { 112, 56, 160, 0 },
    { 208, 56, 160, 104 },
    { 112, 152, 160, 192 },
    { 208, 152, 160, 104 },
};

RECT D_800FF5E0[4] = {
    { 112, 56, 64, 104 },
    { 112, 152, 160, 104 },
    { 208, 56, 256, 104 },
    { 208, 152, 160, 104 },
};

RECT D_800FF600[4] = {
    { 112, 152, 64, 104 },
    { 112, 152, 160, 104 },
    { 208, 135, 256, 104 },
    { 208, 152, 160, 104 },
};

RECT D_800FF620[4] = {
    { 208, 56, 160, 16 },
    { 112, 56, 160, 104 },
    { 208, 152, 160, 192 },
    { 112, 152, 160, 104 },
};

RECT D_800FF640[4] = {
    { 208, 56, 256, 104 },
    { 208, 152, 160, 104 },
    { 112, 56, 64, 104 },
    { 112, 152, 160, 104 },
};

RECT D_800FF660[4] = {
    { 208, 152, 256, 104 },
    { 208, 152, 160, 104 },
    { 112, 152, 64, 104 },
    { 112, 152, 160, 104 },
};

u8 D_800FF680[8] = { 8, 9, 6, 7, 7, 6, 9, 8 };

u8 D_800FF688[8] = { 8, 7, 6, 9, 9, 6, 7, 8 };

u8 D_800FF690[8] = { 7, 8, 6, 9, 6, 9, 7, 8 };

u8 D_800FF698[8] = { 6, 9, 8, 7, 9, 6, 7, 8 };

u8 D_800FF6A0[8] = { 9, 6, 7, 9, 8, 7, 6, 8 };

u8 D_800FF6A8[8] = { 6, 9, 7, 9, 7, 8, 6, 8 };

RECT* web_spider_swing_paths[6] = {
    D_800FF5C0,
    D_800FF5E0,
    D_800FF600,
    D_800FF620,
    D_800FF640,
    D_800FF660,
};

const u8* web_spider_swing_animations[6] = {
    D_800FF680,
    D_800FF688,
    D_800FF690,
    D_800FF698,
    D_800FF6A0,
    D_800FF6A8,
};

u16 web_spider_arena_x = 0x0000;

u16 web_spider_arena_y = 0x0000;

void (*web_spider_state_funcs[3])(struct MainObj*) = {
    web_spider_intro,
    func_8006398C,
    web_spider_death,
};

void (*spiderling_state_funcs[3])() = {
    func_80065574,
    spiderling_run,
    spiderling_despawn,
};

void (*web_spider_intro_funcs[10])(struct MainObj*) = {
    web_spider_intro_warning,
    func_80063334,
    func_8006346C,
    web_spider_intro_spawn_thread,
    web_spider_intro_wait,
    web_spider_intro_descend,
    web_spider_intro_pose,
    web_spider_intro_start_health_bar,
    web_spider_intro_fill_health,
    web_spider_intro_climb,
};

u8 D_800FF724[16] = { 0x07, 0x05, 0x06, 0x04, 0x02, 0x03, 0x01, 0x00, 0x01, 0x00, 0x03, 0x02, 0x05, 0x04, 0x07, 0x06 };

void (*web_spider_step_funcs[7])() = {
    func_8009216C,
    web_spider_fall,
    web_spider_drop,
    web_spider_shoot,
    web_spider_swing,
    web_spider_attack,
    web_spider_big_web,
};

void (*web_spider_drop_funcs[3])() = {
    func_80063B20,
    func_80063DD8,
    func_80063DD8,
};

void (*web_spider_shoot_funcs[3])() = {
    web_spider_shoot_start,
    web_spider_shoot_fire,
    web_spider_shoot_fire,
};

void (*web_spider_swing_funcs[3])(struct MainObj*) = {
    web_spider_swing_start,
    func_80064154,
    web_spider_swing_wait,
};

u8 web_spider_swing_sets[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03 };

void (*web_spider_big_web_funcs[3])() = {
    func_800646EC,
    web_spider_big_web_spin,
    web_spider_big_web_center,
};

void (*web_spider_fall_funcs[5])(struct MainObj*) = {
    web_spider_fall_start,
    web_spider_fall_slow,
    web_spider_fall_land,
    web_spider_fall_crash,
    web_spider_fall_rethread,
};

u8 web_spider_move_timers[4] = { 0x10, 0x14, 0x18, 0x20 };

u8 web_spider_attack_cooldowns[4] = { 0x5A, 0x50, 0x44, 0x32 };

void (*web_spider_death_funcs[3])(struct MainObj*) = {
    web_spider_death_start,
    web_spider_death_explode,
    web_spider_death_finish,
};

struct FixedPointPosition spiderling_velocities[8] = {
    { (s32)0x00010000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0x00028000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0xFFFD8000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0xFFFF0000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
};

void (*spiderling_step_funcs[5])(struct MainObj*) = {
    func_8009216C,
    func_8009216C,
    spiderling_fall,
    spiderling_crawl,
    spiderling_leave,
};

struct Unk_unk68 D_800FF80C = { -11, -10, 21, 23 };

struct Unk_unk68 D_800FF810 = { -11, -10, 20, 42 };

union AnimationStep D_800FF814[] = {
    { 0x05010007 },
    { 0x0601000C },
    { 0x07010004 },
    { 0x08010004 },
    { 0x00010005 },
    { 0x01010008 },
    { 0x0D010007 },
    { 0x0E01000C },
    { 0x0D010007 },
    { 0x00010005 },
    { 0x01010008 },
    { 0x0F010007 },
    { 0x1001000E },
    { 0x0F010007 },
    { 0x00010006 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010002 },
    { 0x0B010004 },
    { 0x0C010002 },
    { 0x0A01000C },
    { 0x09010006 },
    { 0x00010005 },
    { 0x01E9000C },
};

union AnimationStep* D_800FF874[2] = { D_800FF814, NULL };
