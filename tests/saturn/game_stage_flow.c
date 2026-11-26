// saturn-capability: disc
// saturn-step-budget: 400000000
#include "test_runtime.h"
#include "support/saturn_disc.h"
#include "support/test_pad.h"
#include "saturn/menu.h"

void func_8002044C(struct EngineObj* arg0);
void func_80020390(struct EngineObj* arg0);
void func_8001D1F0(struct GameInfo* arg0);
void func_8001FEC0(void);
void func_80020060(struct EngineObj* arg0);
s32 GFS_NameToId(const char* name);
extern s32 saturn_cd_file_id;
extern u8 saturn_movie_active;
extern u8 saturn_sprite_list_counts[20];

#define run_game_thread test_disc_run_thread

static u32 loaded(const char* name)
{
    return saturn_cd_file_id == GFS_NameToId(name);
}

static const struct {
    u8 fading, character, armor;
    const char* archive;
} characters[] = {
    { 1, 0, 0, NULL },
    { 0, 1, 0, "PL01.ARC" },
    { 0, 0, 1, "PL02.ARC" },
    { 0, 0, 0, "PL00.ARC" },
};
static void character_thread(void) { func_8002044C(&engine_obj); }
static u32 character_archive_body(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 10;
    engine_obj.unk1 = 1;
    engine_obj.stage = 11;
    engine_obj.cur_character = characters[row].character;
    engine_obj.unk37 = characters[row].armor;
    main_bss_state.transition.active = characters[row].fading;
    saturn_cd_file_id = -1;
    run_game_thread(character_thread, 0);
    if (characters[row].fading) {
        assert(engine_obj.state == 10 && engine_obj.unk1 == 1 && engine_obj.substage == 0 && saturn_cd_file_id == -1);
        return 0;
    }
    assert(engine_obj.state == 4 && engine_obj.unk1 == 0 && engine_obj.substage == 1);
    assert(loaded(characters[row].archive));
    return 1;
}
static u32 character_archive(u32 row) { return test_disc_on_fixture_stack(character_archive_body, row); }

static const u8 movie_stages[] = { 11, 12 };
static void movie_thread(void) { func_80020390(&engine_obj); }
static u32 fortress_movie(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 10;
    engine_obj.stage = movie_stages[row];
    engine_obj.cur_character = 0;
    saturn_movie_active = 1;
    run_game_thread(movie_thread, 0);
    assert(engine_obj.state == 10 && engine_obj.unk1 == 1);
    assert(saturn_movie_active == 1);
    assert(main_bss_state.transition.active == TEST_FADE_OUT_ACTIVE);
    return engine_obj.stage;
}

static void opening_thread(void) { func_8001D1F0(&game_info); }
static u32 title_opening(u32 row)
{
    test_disc_startup();
    memset(&game_info, 0, sizeof(game_info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    game_info.mode = 1;
    main_bss_state.transition.active = row == 0;
    saturn_cd_file_id = -1;
    run_game_thread(opening_thread, 0);
    if (row == 0)
        assert(game_info.mode == 1 && game_info.unk0 == 0 && saturn_cd_file_id == -1);
    else
        assert(game_info.mode == 0 && game_info.unk0 == 1 && loaded("ASCII.ARC"));
    return game_info.mode;
}

static const struct {
    u8 stage, substage, checkpoint, rush, character, music;
} musics[] = {
    { 12, 1, 0, 0, 1, 0 },
    { 12, 1, 0, 0, 0, 1 },
    { 12, 1, 0, 1, 1, 1 },
    { 12, 0, 5, 0, 1, 0 },
    { 12, 0, 10, 0, 1, 1 },
    { 9, 0, 0, 0, 0, 0 },
};
static void music_thread(void) { func_8001FEC0(); }
static u32 stage_music(u32 row)
{
    char* name = saturn_stream_track_info.name;
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.stage = musics[row].stage;
    engine_obj.substage = musics[row].substage;
    engine_obj.checkpoint = musics[row].checkpoint;
    engine_obj.character_state.bytes[8] = musics[row].rush;
    engine_obj.cur_character = musics[row].character;
    name[2] = name[3] = '?';
    run_game_thread(music_thread, 0);
    if (musics[row].music)
        assert(name[0] == 'S' && name[1] == 'T' && name[2] == '0' && name[3] == 'C');
    else
        assert(name[2] == '?' && name[3] == '?');
    return musics[row].music;
}

static void outcome_thread(void) { func_80020060(&engine_obj); }
static u32 outcome_music(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.state = 6;
    engine_obj.unk1 = 1;
    engine_obj.unkF = -1;
    engine_obj.stage = row == 2 ? 12 : 3;
    engine_obj.checkpoint = 3;
    main_bss_state.transition.active = row == 0;
    saturn_sprite_list_counts[0] = 7;
    saturn_music_thread_active = 1;
    run_game_thread(outcome_thread, 0);
    if (row == 0) {
        assert(engine_obj.state == 6 && engine_obj.unk1 == 1 && saturn_sprite_list_counts[0] == 0);
        assert(saturn_music_thread_active == 1);
    } else {
        assert(engine_obj.state == 5 && engine_obj.unk1 == 0 && engine_obj.unk42 == (row == 1));
        assert(saturn_music_thread_active == (row == 1));
    }
    return engine_obj.state;
}

void func_8001F198(struct EngineObj* arg0);
void func_8001F2BC(struct EngineObj* arg0);
extern s32 saturn_weapon_get_palettes[];
extern s32 D_801396B8;
extern struct MiscObj *D_801396C0, *D_801396C4;
static u16 weapon_palette[0x800];
static void weapon_enter_thread(void) { func_8001F198(&engine_obj); }
static void weapon_screen_thread(void) { func_8001F2BC(&engine_obj); }
static u32 weapon_get_body(u32 row)
{
    u32 zero = row & 1, screen = row >> 1, i;
    const u32* palette = (const u32*)((u8*)weapon_palette + 0xAE0);
    char* name = saturn_stream_track_info.name;
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(weapon_palette, 0x5A, sizeof(weapon_palette));
    TEST_PALETTE = (u8*)weapon_palette;
    engine_obj.cur_character = zero;
    engine_obj.stage = 3;
    run_game_thread(weapon_enter_thread, 1);
    assert(engine_obj.stage == 15 && engine_obj.character_state.bytes[0] == 3 && engine_obj.unk2 == 1);
    for (i = 0; i < 0x30; i++)
        assert(palette[i] == (zero ? 0x5A5A5A5Au : (u32)saturn_weapon_get_palettes[2 * 0x30 + i]));
    if (!screen)
        return zero;
    name[2] = name[3] = '?';
    engine_obj.unk1 = 1;
    run_game_thread(weapon_screen_thread, 1);
    assert(engine_obj.unk1 == 2 && engine_obj.unk2 == 0);
    assert(name[2] == '1' && name[3] == 'B');
    assert(D_801396B8 == (zero ? (s32)0xFFF00000 : 0x100000));
    assert(D_801396C0 != NULL && D_801396C0->id == 0x2D && D_801396C0->unk2 == (zero ? 9 : 0));
    assert(D_801396C4 != NULL && D_801396C4->id == 0x2D && D_801396C4->unk2 == (zero ? 12 : 3));
    return 2 + zero;
}
static u32 weapon_get(u32 row) { return test_disc_on_fixture_stack(weapon_get_body, row); }

void func_8001F9DC(struct EngineObj* arg0);
static void weapon_sound_thread(void) { func_8001F9DC(&engine_obj); }
static u32 weapon_sound_body(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.unk2 = 4;
    engine_obj.cur_character = row == 2;
    main_bss_state.transition.active = row == 0;
    saturn_cd_file_id = -1;
    run_game_thread(weapon_sound_thread, 0);
    if (row == 0) {
        assert(engine_obj.unk2 == 4 && saturn_cd_file_id == -1);
        return 0;
    }
    assert(engine_obj.unk2 == 5 && loaded(row == 2 ? "SEPL01.ARC" : "SEPL00.ARC"));
    return row;
}
static u32 weapon_sound(u32 row) { return test_disc_on_fixture_stack(weapon_sound_body, row); }

void stage_music_load(struct EffectObj* self);
extern char stage_music_archive_name[];
static struct EffectObj music_effect;
static void music_load_thread(void) { stage_music_load(&music_effect); }
static u32 music_load_body(u32 row)
{
    test_disc_startup();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&music_effect, 0, sizeof(music_effect));
    music_effect.unk5 = 1;
    engine_obj.stage = row ? 11 : 3;
    engine_obj.substage = !row;
    D_80171EA8 = 0;
    saturn_cd_file_id = -1;
    run_game_thread(music_load_thread, 1);
    assert(music_effect.unk5 == 2 && D_80171EA8 == 1);
    assert(stage_music_archive_name[2] == (row ? 'B' : '3') && stage_music_archive_name[4] == (row ? '0' : '1'));
    assert(loaded(stage_music_archive_name));
    return row;
}
static u32 music_load(u32 row) { return test_disc_on_fixture_stack(music_load_body, row); }

void func_8001E6BC(struct GameInfo* arg0);
static void menu_open_thread(void) { func_8001E6BC(&game_info); }
static u32 menu_open(u32 row)
{
    (void)row;
    test_disc_startup();
    memset(&game_info, 0, sizeof(game_info));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    game_info.unk0 = 3;
    game_info.mode = 20;
    run_game_thread(menu_open_thread, 0);
    assert(game_info.unk0 == 4 && game_info.mode == 0 && game_info.unkD == 1);
    return game_info.unk0;
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_character_archive", 0, 0, COUNT(characters), character_archive },
    { "saturn_fortress_movie", 0, 0, COUNT(movie_stages), fortress_movie },
    { "saturn_title_opening", 0, 0, 2, title_opening },
    { "saturn_stage_music", 0, 0, COUNT(musics), stage_music },
    { "saturn_outcome_music", 0, 0, 3, outcome_music },
    { "saturn_weapon_get", 0, 0, 4, weapon_get },
    { "saturn_weapon_sound", 0, 0, 3, weapon_sound },
    { "saturn_stage_music_load", 0, 0, 2, music_load },
    { "saturn_title_menu_open", 0, 0, 1, menu_open },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(characters) + COUNT(movie_stages) + 2 + COUNT(musics) + 3 + 4 + 3 + 2 + 1;
