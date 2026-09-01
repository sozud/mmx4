#include <stdio.h>

#include "oracle_capture.h"

int main(void)
{
    int oracle_result = mmx4_oracle_capture_placeholder();

    if (oracle_result != MMX4_ORACLE_NOT_REQUESTED) {
        return oracle_result;
    }

    puts("MMX4 native source build succeeded");
    return 0;
}
