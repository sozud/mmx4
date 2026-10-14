#include "common.h"
#include "memcard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define CARD_SIZE 0x20000
#define BLOCK_SIZE 0x2000
#define FRAME_SIZE 0x80
static struct {
    u8 data[CARD_SIZE];
    int present;
    int acknowledged;
    const char* fault;
    char path[4096];
} cards[2];
static int initialized;

static void blank_card(u8* data)
{
    int i;
    memset(data, 0, CARD_SIZE);
    data[0] = 'M';
    data[1] = 'C';
    data[0x7F] = 0x0E;
    for (i = 0x80; i < 0x800; i += FRAME_SIZE) {
        data[i] = data[i + 0x7F] = 0xA0;
        data[i + 8] = data[i + 9] = 0xFF;
    }
    for (i = 0x800; i < 0x1200; i += FRAME_SIZE) {
        memset(data + i, 0xFF, 4);
        data[i + 8] = data[i + 9] = 0xFF;
    }
}

static void flush_card(int port)
{
    FILE* file = fopen(cards[port].path, "wb");
    if (file == NULL || fwrite(cards[port].data, CARD_SIZE, 1, file) != 1 || fclose(file)) {
        fprintf(stderr, "MMX4 PC: unable to save memory card %s\n", cards[port].path);
        exit(1);
    }
}

static void init_cards(void)
{
    const char* dir = getenv("MMX4_MEMCARD_DIR");
    int port;
    if (initialized)
        return;
    initialized = 1;
    if (!dir) {
        dir = "memcards";
        mkdir(dir, 0755);
    }
    for (port = 0; port < 2; port++) {
        char key[40];
        FILE* file;
        snprintf(cards[port].path, sizeof(cards[port].path), "%s/card%d.mcr", dir, port);
        snprintf(key, sizeof(key), "MMX4_MEMCARD_FAULT_%d", port);
        cards[port].fault = getenv(key);
        file = fopen(cards[port].path, "rb");
        if (file) {
            if (fread(cards[port].data, CARD_SIZE, 1, file) != 1 || fgetc(file) != EOF) {
                fprintf(stderr, "MMX4 PC: invalid memory card %s\n", cards[port].path);
                exit(1);
            }
            fclose(file);
            cards[port].present = 1;
        } else if (!getenv("MMX4_MEMCARD_DIR")) {
            blank_card(cards[port].data);
            cards[port].present = 1;
            flush_card(port);
        }
    }
}

int mmx4_pc_card_info(int port)
{
    static const u8 bios_zero_page[FRAME_SIZE] = {
        [0] = 3,
        [4] = 0x80,
        [5] = 0x0C,
        [6] = 0x5A,
        [7] = 0x27,
        [8] = 8,
        [10] = 0x40,
        [11] = 3,
        [0x60] = 2,
        [0x68] = 0xFF,
    };
    init_cards();
    if (port < 0 || port > 1 || !cards[port].present)
        return 1;
    if (!cards[port].acknowledged) {
        int read_fault = cards[port].fault && !strcmp(cards[port].fault, "read");
        const u8* source = !read_fault && !memcmp(cards[port].data, "MC", 2) ? cards[port].data : bios_zero_page;
        cards[port].acknowledged = 1;
        if (!cards[port].fault || strcmp(cards[port].fault, "write")) {
            memcpy(cards[port].data + 0x1F80, source, FRAME_SIZE);
            flush_card(port);
        }
    }
    return 0;
}

int mmx4_pc_card_load(int port)
{
    if (mmx4_pc_card_info(port))
        return 1;
    if (cards[port].fault && !strcmp(cards[port].fault, "read"))
        return 3;
    return memcmp(cards[port].data, "MC", 2) ? 2 : 0;
}

int mmx4_pc_card_format(int port)
{
    if (mmx4_pc_card_info(port))
        return 1;
    if (cards[port].fault && !strcmp(cards[port].fault, "write"))
        return 1;
    {
        u8 system_area[FRAME_SIZE];
        memcpy(system_area, cards[port].data + 0x1F80, FRAME_SIZE);
        blank_card(cards[port].data);
        memcpy(cards[port].data + 0x1F80, system_area, FRAME_SIZE);
    }
    flush_card(port);
    return 0;
}

void mmx4_pc_card_list(int port, struct MemcardFileList* list, const char* pattern)
{
    int block;
    list->count = 0;
    list->total_size = 0;
    if (mmx4_pc_card_load(port))
        return;
    for (block = 1; block < 16; block++) {
        const u8* frame = cards[port].data + block * FRAME_SIZE;
        if (frame[0] != 0x51)
            continue;
        if (*pattern && strncmp((const char*)frame + 10, pattern, 20))
            continue;
        memcpy(list->names[list->count], frame + 10, 20);
        list->names[list->count][20] = 0;
        list->sizes[list->count] = frame[4] | frame[5] << 8 | frame[6] << 16 | frame[7] << 24;
        list->total_size += list->sizes[list->count++];
    }
}

static int save_block(int port)
{
    int block;
    for (block = 1; block < 16; block++) {
        u8* frame = cards[port].data + block * FRAME_SIZE;
        if (frame[0] == 0x51 && !strcmp((char*)frame + 10, "BASLUS-00561"))
            return block;
    }
    return 0;
}

int mmx4_pc_card_read(int port, void* buffer, int size)
{
    int block;
    if (mmx4_pc_card_load(port))
        return 2;
    block = save_block(port);
    if (!block)
        return 1;
    if (size < 0 || size > BLOCK_SIZE)
        return 2;
    memcpy(buffer, cards[port].data + block * BLOCK_SIZE, size);
    return 0;
}

int mmx4_pc_card_write(int port, const void* buffer, int size)
{
    int block;
    if (mmx4_pc_card_load(port) || (cards[port].fault && !strcmp(cards[port].fault, "write")))
        return 2;
    if (size < 0 || size > BLOCK_SIZE)
        return 2;
    block = save_block(port);
    if (!block) {
        u8* frame;
        int i;
        for (block = 1; block < 16; block++)
            if ((cards[port].data[block * FRAME_SIZE] & 0xF0) == 0xA0)
                break;
        if (block == 16)
            return 1;
        frame = cards[port].data + block * FRAME_SIZE;
        memset(frame, 0, FRAME_SIZE);
        frame[0] = 0x51;
        frame[5] = 0x20;
        frame[8] = frame[9] = 0xFF;
        memcpy(frame + 10, "BASLUS-00561", sizeof("BASLUS-00561") - 1);
        for (i = 0; i < 0x7F; i++)
            frame[0x7F] ^= frame[i];
    }
    memcpy(cards[port].data + block * BLOCK_SIZE, buffer, size);
    flush_card(port);
    return 0;
}
