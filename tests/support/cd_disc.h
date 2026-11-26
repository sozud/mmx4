#ifndef MMX4_TESTS_CD_DISC_H
#define MMX4_TESTS_CD_DISC_H
#include <psyz/cd.h>
#include <psyz/disc.h>

#define CD_DISC_SECTORS 48
#define CD_DISC_REGIONS 4
static u8 cd_disc_data[CD_DISC_SECTORS][0x800];
static struct {
    s32 first;
    u32 row, count;
} cd_disc_regions[CD_DISC_REGIONS];
static u32 cd_disc_region_count;
static s32 cd_disc_wrong_header, cd_disc_wrong_header2, cd_disc_unreadable;
static u32 cd_disc_reads[CD_DISC_SECTORS];

static u8 cd_disc_bcd(s32 value) { return (u8)(value / 10 << 4 | value % 10); }

static int cd_disc_sector(int sector, unsigned char* out)
{
    s32 index = -1, position = sector + 150;
    u32 i;
    for (i = 0; i < cd_disc_region_count; i++)
        if (sector >= cd_disc_regions[i].first && sector < cd_disc_regions[i].first + (s32)cd_disc_regions[i].count)
            index = cd_disc_regions[i].row + (sector - cd_disc_regions[i].first);
    if (index < 0)
        return -1;
    if (sector == cd_disc_unreadable) {
        cd_disc_unreadable = -1;
        return -1;
    }
    if (sector == cd_disc_wrong_header2) {
        cd_disc_wrong_header2 = -1;
        position++;
    } else if (sector == cd_disc_wrong_header) {
        cd_disc_wrong_header = -1;
        position++;
    }
    cd_disc_reads[index]++;
    memset(out, 0, PSYZ_DISC_SECTOR_SIZE);
    memset(out + 1, 0xFF, 10);
    out[12] = cd_disc_bcd(position / 75 / 60);
    out[13] = cd_disc_bcd(position / 75 % 60);
    out[14] = cd_disc_bcd(position % 75);
    out[15] = 2;
    memcpy(out + 24, cd_disc_data[index], 0x800);
    return 0;
}

static u8 cd_disc_byte(u32 index, u32 offset) { return (u8)(index * 29 + offset * 7 + (offset >> 8) * 3 + 1); }

static void cd_disc_insert(s32 first)
{
    u32 i, j;
    cd_disc_regions[0].first = first;
    cd_disc_regions[0].row = 0;
    cd_disc_regions[0].count = CD_DISC_SECTORS;
    cd_disc_region_count = 1;
    cd_disc_wrong_header = cd_disc_wrong_header2 = cd_disc_unreadable = -1;
    for (i = 0; i < CD_DISC_SECTORS; i++) {
        cd_disc_reads[i] = 0;
        for (j = 0; j < 0x800; j++)
            cd_disc_data[i][j] = cd_disc_byte(i, j);
    }
    Psyz_CdSetSectorOverlay(cd_disc_sector);
}

#define CD_DISC_NOWHERE (-0x10000)
static void cd_disc_place(s32 first, u32 row, u32 count)
{
    cd_disc_regions[cd_disc_region_count].first = first;
    cd_disc_regions[cd_disc_region_count].row = row;
    cd_disc_regions[cd_disc_region_count].count = count;
    cd_disc_region_count++;
}

static void cd_disc_eject(void)
{
    CdReadyCallback(NULL);
    CdControlB(CdlPause, NULL, NULL);
    Psyz_CdSetSectorOverlay(NULL);
}

static void cd_disc_put_word(u32 index, u32 word, u32 value)
{
    u8* p = &cd_disc_data[index][word * 4];
    p[0] = value;
    p[1] = value >> 8;
    p[2] = value >> 16;
    p[3] = value >> 24;
}

static void cd_disc_archive(u32 row, u32 command, u32 size)
{
    memset(cd_disc_data[row], 0, 0x800);
    cd_disc_put_word(row, 0, 1);
    cd_disc_put_word(row, 2, command);
    cd_disc_put_word(row, 3, size);
}
#endif
