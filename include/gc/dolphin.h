#ifndef GC_DOLPHIN_H
#define GC_DOLPHIN_H

typedef struct {
    unsigned long dummy[3];
} GXTlutObj;

typedef enum {
    GX_TL_IA8,
    GX_TL_RGB565,
    GX_TL_RGB5A3
} GXTlutFmt;

typedef struct DVDFileInfo DVDFileInfo;
typedef void (*DVDCallback)(long result, DVDFileInfo* fileInfo);

struct DVDFileInfo {
    unsigned char cb[0x30];
    unsigned long startAddr;
    unsigned long length;
    DVDCallback callback;
};

#define OSRoundUp32B(x) (((unsigned long)(x) + 31) & ~31)

void OSReport(const char* msg, ...);
void OSPanic(const char* file, int line, const char* msg, ...);
int DVDOpen(const char* fileName, DVDFileInfo* fileInfo);
int DVDClose(DVDFileInfo* fileInfo);
int DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, long length, long offset, DVDCallback callback, long prio);
void DCFlushRangeNoSync(void* addr, unsigned long nbytes);
void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt, unsigned short n_entries);
void GXSetScissor(unsigned long left, unsigned long top, unsigned long wd, unsigned long ht);

#endif
