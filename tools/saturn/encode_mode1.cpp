#include "lec.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc != 2) return 2;
    char* end = nullptr;
    errno = 0;
    unsigned long lba = std::strtoul(argv[1], &end, 10);
    if (errno || !*argv[1] || *end || lba > 449849) return 2;
    unsigned char sector[2352];
    for (;; ++lba) {
        const size_t count = std::fread(sector, 1, sizeof sector, stdin);
        if (count == 0) return std::ferror(stdin) ? 1 : 0;
        if (count != sizeof sector || lba > 449849) return 1;
        lec_encode_mode1_sector(static_cast<unsigned>(lba + 150), sector);
        if (std::fwrite(sector, 1, sizeof sector, stdout) != sizeof sector) return 1;
    }
}
