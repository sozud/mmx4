#include "common.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <psyz/video.h>

int mmx4_pc_write_state_screenshot(unsigned long transition,
    unsigned long frame_number, u32 game_state, u32 engine_state)
{
    const char* directory = getenv("MMX4_ORACLE_SCREENSHOT_DIR");
    char filename[96];
    char manifest_path[1024];
    char path[1024];
    unsigned char* pixels;
    int width;
    int height;
    FILE* image;
    FILE* manifest;
    size_t i;
    size_t count;
    size_t visible = 0;

    if (directory == NULL || *directory == '\0')
        return 1;
    if (mkdir(directory, 0777) != 0 && errno != EEXIST)
        return 0;
    pixels = Psyz_VideoAllocCapturedFrame(&width, &height);
    if (pixels == NULL || width <= 0 || height <= 0) {
        free(pixels);
        return 0;
    }
    count = (size_t)width * height;
    for (i = 0; i < count; i++) {
        unsigned value = pixels[i * 3] + pixels[i * 3 + 1] + pixels[i * 3 + 2];
        if (value > 24)
            visible++;
    }
    if (visible < count / 100) {
        free(pixels);
        return 0;
    }
    snprintf(filename, sizeof(filename),
        "transition_%04lu_f%06lu_g%08x_e%08x.ppm", transition,
        frame_number, game_state, engine_state);
    snprintf(path, sizeof(path), "%s/%s", directory, filename);
    image = fopen(path, "wb");
    if (image == NULL) {
        free(pixels);
        return 0;
    }
    fprintf(image, "P6\n%d %d\n255\n", width, height);
    fwrite(pixels, 3, count, image);
    fclose(image);
    free(pixels);
    snprintf(manifest_path, sizeof(manifest_path), "%s/manifest.tsv", directory);
    manifest = fopen(manifest_path, "a");
    if (manifest == NULL)
        return 0;
    fprintf(manifest, "%lu\t%lu\t%08x\t%08x\t%s\n", transition,
        frame_number, game_state, engine_state, filename);
    fclose(manifest);
    return 1;
}

void mmx4_pc_write_replay_frame(long frame)
{
    const char* directory = getenv("MMX4_ORACLE_FRAME_DIR");
    const char* value;
    unsigned long first = 0;
    unsigned long last = ~0UL;
    unsigned long interval = 1;
    char path[1024];
    unsigned char* pixels;
    int width;
    int height;
    FILE* image;

    if (directory == NULL || *directory == '\0' || frame < 0)
        return;
    value = getenv("MMX4_ORACLE_FRAME_FIRST");
    if (value != NULL)
        first = strtoul(value, NULL, 0);
    value = getenv("MMX4_ORACLE_FRAME_LAST");
    if (value != NULL)
        last = strtoul(value, NULL, 0);
    value = getenv("MMX4_ORACLE_FRAME_INTERVAL");
    if (value != NULL)
        interval = strtoul(value, NULL, 0);
    if ((unsigned long)frame < first || (unsigned long)frame > last ||
        interval == 0 || ((unsigned long)frame - first) % interval != 0)
        return;
    if (mkdir(directory, 0777) != 0 && errno != EEXIST)
        return;
    pixels = Psyz_VideoAllocCapturedFrame(&width, &height);
    if (pixels == NULL || width <= 0 || height <= 0) {
        free(pixels);
        return;
    }
    snprintf(path, sizeof(path), "%s/frame_%06ld.ppm", directory, frame);
    image = fopen(path, "wb");
    if (image != NULL) {
        fprintf(image, "P6\n%d %d\n255\n", width, height);
        fwrite(pixels, 3, (size_t)width * height, image);
        fclose(image);
    }
    free(pixels);
}
