// saturn-capability: vblank
// saturn-step-budget: 2000000000
#include "test_runtime.h"
#include "support/saturn_disc.h"
#include "support/test_pad.h"

void func_80020390(struct EngineObj* arg0);
void func_8001D1F0(struct GameInfo* arg0);
void func_80023624(struct EngineObj* arg0);
void func_8002EF14(struct EngineObj* arg0);
s32 GFS_NameToId(const char* name);
extern s32 saturn_cd_file_id;
extern u8 saturn_movie_active;
extern u8 saturn_movie_top;
extern u16 saturn_movie_height;

#define MOVIE_BITMAP ((volatile u32*)0x25E00000)
#define MOVIE_INGAME_BITMAP_WORDS (176 * 0x500 / 4)
#define MOVIE_INGAME_TOP (8 + 24)

static u32 movie_shown;
static s32 movie_file;

static void skip_once_shown(u32 pass)
{
    u32 i;
    if (saturn_movie_active && movie_file < 0)
        movie_file = saturn_cd_file_id;
    if (saturn_movie_active && !movie_shown) {
        for (i = 0; i < MOVIE_INGAME_BITMAP_WORDS; i += 64) {
            if (MOVIE_BITMAP[i] != 0) {
                movie_shown = 1;
                break;
            }
        }
    }
    TEST_PAD_HELD = movie_shown ? TEST_PAD_START : 0;
}

static void play(void (*fn)(void), u32 drain)
{
    movie_shown = 0;
    movie_file = -1;
    TEST_PAD_HELD = 0;
    saturn_cd_file_id = -1;
    test_vblank_run_thread(fn, skip_once_shown, drain);
    TEST_PAD_HELD = 0;
}

static u32 played(const char* name)
{
    assert(movie_shown);
    assert(movie_file == GFS_NameToId(name));
    assert(saturn_movie_height == 176 && saturn_movie_top == MOVIE_INGAME_TOP);
    assert(saturn_movie_active == 0);
    return movie_file;
}

static const u8 fortress_stages[] = { 11, 12 };
static void fortress_thread(void) { func_80020390(&engine_obj); }
static u32 fortress_movie_body(u32 row)
{
    test_vblank_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 10;
    engine_obj.stage = fortress_stages[row];
    engine_obj.cur_character = 1;
    play(fortress_thread, 0);
    assert(engine_obj.state == 10 && engine_obj.unk1 == 1);
    assert(main_bss_state.transition.active == TEST_FADE_OUT_ACTIVE);
    return played(row == 0 ? "Z3.CPK" : "Z4.CPK");
}
static u32 fortress_movie(u32 row) { return test_disc_on_fixture_stack(fortress_movie_body, row); }

static void opening_thread(void) { func_8001D1F0(&game_info); }
static u32 opening_movie_body(u32 row)
{
    test_vblank_startup();
    memset(&game_info, 0, sizeof(game_info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    play(opening_thread, 0);
    assert(game_info.mode == 1 && game_info.unk0 == 0);
    assert(main_bss_state.transition.active == TEST_FADE_OUT_ACTIVE);
    return played("OP.CPK");
}
static u32 opening_movie(u32 row) { return test_disc_on_fixture_stack(opening_movie_body, row); }

static void ending_thread(void) { func_80023624(&engine_obj); }
static u32 ending_movie_body(u32 row)
{
    test_vblank_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.cur_character = row;
    engine_obj.unk1F = engine_obj.enable_boss = 1;
    play(ending_thread, 0);
    assert(engine_obj.unk1 == 1 && engine_obj.unk1F == 0 && engine_obj.enable_boss == 0);
    assert(main_bss_state.transition.active == TEST_FADE_OUT_ACTIVE);
    return played(row == 0 ? "X4.CPK" : "Z5.CPK");
}
static u32 ending_movie(u32 row) { return test_disc_on_fixture_stack(ending_movie_body, row); }

static const char* route_movies[] = { "X1.CPK", "Z1.CPK", "X2.CPK", "X3.CPK", "Z2.CPK" };
static const struct {
    u8 route, character, armor, next;
    const char* archive;
} routes[] = {
    { 0, 1, 0, 10, NULL },
    { 1, 1, 0, 5, NULL },
    { 2, 1, 0, 6, NULL },
    { 2, 0, 1, 1, NULL },
    { 3, 1, 0, 0, "PL01.ARC" },
    { 4, 0, 1, 0, "PL02.ARC" },
    { 3, 0, 0, 0, "PL00.ARC" },
};
static void route_thread(void) { func_8002EF14(&engine_obj); }
static u32 route_movie_body(u32 row)
{
    test_vblank_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 3;
    engine_obj.unk1 = 8;
    engine_obj.unk2 = 2;
    engine_obj.stage = 13;
    engine_obj.unk5F = 3;
    engine_obj.unkE = routes[row].route;
    engine_obj.cur_character = routes[row].character;
    engine_obj.unk37 = routes[row].armor;
    play(route_thread, routes[row].route <= 2);
    assert(engine_obj.unkE == routes[row].next && engine_obj.unk2 == 0);
    if (routes[row].route <= 2) {
        assert(engine_obj.unk1 == 1 && engine_obj.stage == 13 && engine_obj.unk5F == 3);
    } else {
        assert(engine_obj.unk1 == 7);
        assert(saturn_cd_file_id == GFS_NameToId(routes[row].archive));
        if (routes[row].route == 3) {
            assert(engine_obj.stage == 11 && engine_obj.substage == 0 && engine_obj.unk5F == 9);
            assert(main_bss_state.transition.active == TEST_FADE_OUT_ACTIVE);
        } else {
            assert(engine_obj.stage == 9 && engine_obj.unk5F == 4 && main_bss_state.transition.active == 0);
        }
    }
    return played(route_movies[routes[row].route]);
}
static u32 route_movie(u32 row) { return test_disc_on_fixture_stack(route_movie_body, row); }

const struct CTestGroup c_test_groups[] = {
    { "saturn_fortress_movie_zero", 0, 0, COUNT(fortress_stages), fortress_movie },
    { "saturn_opening_movie", 0, 0, 1, opening_movie },
    { "saturn_ending_movie", 0, 0, 2, ending_movie },
    { "saturn_route_movie", 0, 0, COUNT(routes), route_movie },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(fortress_stages) + 1 + 2 + COUNT(routes);
