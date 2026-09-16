#include "common.h"

#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static FILE* render_log;
static FILE* render_source_log;
static long last_logged_frame = -1;

static int pointer_is_ordering_tag(const P_TAG* pointer)
{
    const OT_TYPE* begin = &cur_draw_info->ordering_table.start;
    const OT_TYPE* end = begin + 12;

    return (uintptr_t)pointer >= (uintptr_t)begin && (uintptr_t)pointer < (uintptr_t)end;
}

static void open_render_log(void)
{
    const char* directory = getenv("MMX4_ORACLE_DUMP_DIR");
    char path[4096];

    if (render_log != NULL || directory == NULL || *directory == '\0')
        return;
    if (mkdir(directory, 0777) != 0 && errno != EEXIST) {
        perror(directory);
        exit(EXIT_FAILURE);
    }
    snprintf(path, sizeof(path), "%s/render.tsv", directory);
    render_log = fopen(path, "w");
    snprintf(path, sizeof(path), "%s/render_sources.tsv", directory);
    render_source_log = fopen(path, "w");
    if (render_log == NULL || render_source_log == NULL) {
        perror(directory);
        exit(EXIT_FAILURE);
    }
}

static u32 packet_word(const P_TAG* primitive, unsigned index, u8 code)
{
    const u8* payload = (const u8*)primitive + offsetof(P_TAG, r0);
    u32 word;

    if (code >= 0x20 && code < 0x80) {
        memcpy(&word, payload + index * sizeof(word), sizeof(word));
    } else {
        u_long wide_word;

        memcpy(&wide_word, payload + index * sizeof(wide_word),
            sizeof(wide_word));
        word = (u32)wide_word;
    }
    return word;
}

void mmx4_pc_render_log_dump(void)
{
    const char* first_text;
    const char* last_text;
    unsigned long first = 0;
    unsigned long last = ~0UL;
    long frame = mmx4_pc_replay_frame();
    u32 game;
    u32 engine;
    int bucket;

    open_render_log();
    if (render_log == NULL || frame < 0 || frame == last_logged_frame)
        return;
    last_logged_frame = frame;
    first_text = getenv("MMX4_ORACLE_DUMP_FIRST");
    last_text = getenv("MMX4_ORACLE_DUMP_LAST");
    if (first_text != NULL)
        first = strtoul(first_text, NULL, 0);
    if (last_text != NULL)
        last = strtoul(last_text, NULL, 0);
    if ((unsigned long)frame < first || (unsigned long)frame > last)
        return;

    memcpy(&game, &game_info, sizeof(game));
    memcpy(&engine, &engine_obj, sizeof(engine));
    for (bucket = 11; bucket >= 0; bucket--) {
        OT_TYPE* ordering_tag = &cur_draw_info->ordering_table.start + bucket;
        P_TAG* primitive = (P_TAG*)getaddr(ordering_tag);
        unsigned order;

        for (order = 0; primitive != (P_TAG*)0xFFFFFF && order < 4096;
             order++) {
            unsigned len;
            unsigned byte_index;
            u8 code;

            if (primitive == NULL || pointer_is_ordering_tag(primitive))
                break;
            len = getlen(primitive);
            code = len != 0 ? getcode(primitive) : 0;
            if (len > 16)
                break;
            fprintf(render_log, "%ld\t%08x\t%08x\t%d\t%u\t%u\t%02x\t",
                frame, game, engine, bucket, order, len, code);
            for (byte_index = 0; byte_index < len * 4; byte_index++) {
                u32 word = packet_word(primitive, byte_index / 4, code);
                u8 byte = word >> ((byte_index & 3) * 8);

                if ((code & 0xFC) == 0x38 && (byte_index == 11 || byte_index == 19 || byte_index == 27))
                    byte = 0;
                if ((code & 1) && code < 0x80 && byte_index < 3)
                    byte = 0;
                fprintf(render_log, "%02x", byte);
            }
            fputc('\n', render_log);
            fprintf(render_source_log, "%ld\t%d\t%u\t%p\t%02x\n",
                frame, bucket, order, (void*)primitive, code);
            primitive = (P_TAG*)getaddr(primitive);
        }
    }
    fflush(render_log);
    fflush(render_source_log);
}
