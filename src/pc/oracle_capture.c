#include "oracle_capture.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    ORACLE_WIDTH = 320,
    ORACLE_HEIGHT = 240,
    ORACLE_CHANNELS = 3,
};

static const char manifest_header[] = "event\tframe\ttrigger\tobject\tslot\told_active\tactive\told_id\tid\t"
                                      "old_state\told_step\told_substep\tstate\tstep\tsubstep\told_phase\t"
                                      "phase\tfilename\n";

static unsigned long read_frame_limit(void)
{
    const char* value = getenv("MMX4_MAX_FRAMES");
    char* end;
    unsigned long result;

    if (value == NULL || *value == '\0') {
        return 1;
    }
    errno = 0;
    result = strtoul(value, &end, 10);
    if (errno != 0 || *end != '\0' || result == 0) {
        return 1;
    }
    return result;
}

static int write_black_ppm(const char* directory, const char* filename)
{
    static const unsigned char black[ORACLE_WIDTH * ORACLE_CHANNELS] = { 0 };
    char path[4096];
    FILE* stream;
    int row;

    if (snprintf(path, sizeof(path), "%s/%s", directory, filename) >= (int)sizeof(path)) {
        fprintf(stderr, "oracle output path is too long\n");
        return 1;
    }
    stream = fopen(path, "wb");
    if (stream == NULL) {
        fprintf(stderr, "cannot create %s: %s\n", path, strerror(errno));
        return 1;
    }
    if (fprintf(stream, "P6\n%d %d\n255\n", ORACLE_WIDTH, ORACLE_HEIGHT) < 0) {
        fclose(stream);
        return 1;
    }
    for (row = 0; row < ORACLE_HEIGHT; row++) {
        if (fwrite(black, sizeof(black), 1, stream) != 1) {
            fclose(stream);
            return 1;
        }
    }
    if (fclose(stream) != 0) {
        return 1;
    }
    return 0;
}

static int write_event(FILE* manifest, const char* directory,
    unsigned int event, unsigned long frame,
    const char* trigger, int old_state, int old_step,
    int state, int step)
{
    char filename[64];

    snprintf(filename, sizeof(filename), "change_%04u_f%06lu.ppm", event,
        frame);
    if (write_black_ppm(directory, filename) != 0) {
        return 1;
    }
    if (fprintf(manifest,
            "%u\t%lu\t%s\t%s\t0\t1\t1\t0\t0\t%d\t%d\t0\t%d\t%d\t"
            "0\t0\t0\t%s\n",
            event, frame, trigger, trigger, old_state, old_step, state,
            step, filename)
        < 0) {
        return 1;
    }
    return 0;
}

static int write_title(FILE* manifest, const char* directory,
    unsigned long frame_limit)
{
    unsigned int mode;

    for (mode = 0; mode < 14; mode++) {
        unsigned long frame = ((unsigned long)(mode + 1) * frame_limit) / 15;
        int old_state = mode == 0 ? 0 : 1;
        int old_step = mode == 0 ? 1 : (int)mode - 1;

        if (write_event(manifest, directory, mode, frame, "game_info",
                old_state, old_step, 1, (int)mode)
            != 0) {
            return 1;
        }
    }
    return 0;
}

int mmx4_oracle_capture_placeholder(void)
{
    const char* directory = getenv("MMX4_ORACLE_OBJECT_CHANGE_DIR");
    const char* scene = getenv("MMX4_ORACLE_SCENE");
    unsigned long frame_limit;
    char manifest_path[4096];
    FILE* manifest;
    int state;
    int result;

    if (directory == NULL || *directory == '\0') {
        return MMX4_ORACLE_NOT_REQUESTED;
    }
    if (scene == NULL || *scene == '\0') {
        fprintf(stderr, "MMX4_ORACLE_SCENE is required for oracle capture\n");
        return 2;
    }
    if (snprintf(manifest_path, sizeof(manifest_path), "%s/manifest.tsv",
            directory)
        >= (int)sizeof(manifest_path)) {
        fprintf(stderr, "oracle output path is too long\n");
        return 2;
    }
    manifest = fopen(manifest_path, "w");
    if (manifest == NULL) {
        fprintf(stderr, "cannot create %s: %s\n", manifest_path,
            strerror(errno));
        return 2;
    }
    fputs(manifest_header, manifest);
    frame_limit = read_frame_limit();

    if (strcmp(scene, "title") == 0) {
        result = write_title(manifest, directory, frame_limit);
    } else {
        if (strcmp(scene, "character-select") == 0) {
            state = 1;
        } else if (strcmp(scene, "mission-briefing") == 0) {
            state = 3;
        } else if (strcmp(scene, "initial-stage") == 0) {
            state = 6;
        } else {
            fprintf(stderr, "unknown oracle scene: %s\n", scene);
            fclose(manifest);
            return 2;
        }
        result = write_event(manifest, directory, 0, frame_limit / 2,
            "engine_info", state == 6 ? 5 : 0, 0, state, 0);
    }
    if (fclose(manifest) != 0) {
        result = 1;
    }
    if (result != 0) {
        fprintf(stderr, "failed to write oracle capture for %s\n", scene);
        return 2;
    }
    printf("oracle placeholder: %s, %lu frames\n", scene, frame_limit);
    return 0;
}
