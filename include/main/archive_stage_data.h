#ifndef MAIN_ARCHIVE_STAGE_DATA_H
#define MAIN_ARCHIVE_STAGE_DATA_H

struct ArchivePathData {
    s8 stage_archive_indices[12];
#ifndef MMX4_WIN32
#ifdef VERSION_JP
    char paths[162][64];
#elif defined(VERSION_EU)
    char paths[165][64];
#else
    char paths[163][64];
#endif
#endif
};

extern struct ArchivePathData D_800EE54C;

#endif
