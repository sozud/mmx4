#include "test_runtime.h"
#include "weapon_resources.h"

void func_8006C6AC(struct MainObj* arg0);
void func_8006D3DC(struct MainObj* arg0);
void func_8006E920(struct MainObj* arg0, u32 value);
extern union AnimationStep* slash_beast_animations[];

static struct MainObj beast;
static u8 pattern[2];
static u32 floor_attrs[0x400];

static void place(s32 dx, u8 step, u16 seed)
{
    c_test_zero_words((u32*)&beast, sizeof(beast) / 4);
    beast.active = 1;
    beast.id = 0x54;
    beast.state = 1;
    beast.hp = 0x20;
    beast.x_pos.i.hi = 0x200;
    beast.y_pos.i.hi = 0x100;
    beast.animation_table = (const u8* const*)slash_beast_animations;
    pattern[0] = 0;
    pattern[1] = step;
    beast.ext.main_54.pattern = &pattern[0];
    g_Player.x_pos.val = (0x200 + dx) << 16;
    g_Player.y_pos.i.hi = 0x100;
    cur_random = seed;
}

static void choose_far_hurt(void) { place(0xC0, 0, 0); beast.hp = 8; func_8006C6AC(&beast); }
static void choose_far(void) { place(0xC0, 0, 0); func_8006C6AC(&beast); }
static void choose_step0(void) { place(0x40, 0, 1); func_8006C6AC(&beast); }
static void choose_step0_jump(void) { place(0x40, 0, 0); func_8006C6AC(&beast); }
static void choose_step1_far(void) { place(0x90, 1, 1); func_8006C6AC(&beast); }
static void choose_step1_powered(void) { place(0x40, 1, 1); beast.ext.main_54.powered_up = 1; func_8006C6AC(&beast); }
static void choose_step1_jump(void) { place(0x40, 1, 0); func_8006C6AC(&beast); }
static void choose_step2_near(void) { place(0x40, 2, 1); func_8006C6AC(&beast); }
static void choose_step2_far(void) { place(0x90, 2, 1); func_8006C6AC(&beast); }

static void jump_near(void) { place(0x40, 0, 1); func_8006D3DC(&beast); }
static void jump_wait(void) { place(0x90, 0, 1); func_8006D3DC(&beast); }
static void jump_right(void) { place(0x90, 0, 1); beast.unk15 = PLAYER_FACING_RIGHT; beast.animation_step.fields.event = 1; func_8006D3DC(&beast); }
static void jump_grab_left(void) { place(-0x90, 0, 1); beast.ext.main_54.grab = 1; beast.animation_step.fields.event = 1; func_8006D3DC(&beast); }
static void jump_grab_right(void) { place(0x90, 0, 1); beast.ext.main_54.grab = 1; beast.unk15 = PLAYER_FACING_RIGHT; beast.animation_step.fields.event = 1; func_8006D3DC(&beast); }

static void floor(u8 stage, u8 facing, u32 code)
{
    c_test_zero_words(floor_attrs, COUNT(floor_attrs));
    place(0x40, 0, 1);
    SATURN_TILE_ATTRS = floor_attrs;
    engine_obj.stage = stage;
    beast.unk15 = facing;
    func_8006E920(&beast, TILE_ATTR_VALUE(code));
}
static void floor_solid_fortress(void) { floor(0xC, 0, 0x38); }
static void floor_left(void) { floor(0xB, 0, 0x3E); }
static void floor_left_fortress(void) { floor(0xC, 0, 0x3E); }
static void floor_right_fortress(void) { floor(0xC, PLAYER_FACING_RIGHT, 0x3E); }

static void (*const beast_cases[])(void) = {
    choose_far_hurt, choose_far, choose_step0, choose_step0_jump, choose_step1_far,
    choose_step1_powered, choose_step1_jump, choose_step2_near, choose_step2_far,
    jump_near, jump_wait, jump_right, jump_grab_left, jump_grab_right,
    floor_solid_fortress, floor_left, floor_left_fortress, floor_right_fortress,
};

#define WORDS 5
static const u32 beast_expected[][WORDS] = {
#include "game_slash_beast_expected.inc"
};

static u32 beast_run(u32 row)
{
    u32 observed[WORDS], attrs = 0, i;
    beast_cases[row]();
    for (i = 0; i < COUNT(floor_attrs); i++)
        attrs += (floor_attrs[i] >> 24) * (i + 1);
    observed[0] = (u8)beast.unk5 | (u32)(u8)beast.unk6 << 8 | (u32)beast.unk17 << 16 | (u32)beast.ext.main_54.grab << 24;
    observed[1] = (u16)beast.unk7C | (u32)(u16)beast.unk7E << 16;
    observed[2] = beast.x_speed;
    observed[3] = beast.y_speed ^ (u32)beast.gravity << 8;
    observed[4] = attrs ^ (u32)beast.ext.main_54.high_jump << 24 ^ (u32)(u8)beast.unk15 << 16;
    return c_test_observe(0, row, observed, beast_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_slash_beast", 0, 0, COUNT(beast_cases), beast_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(beast_cases);
