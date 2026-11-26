#include "test_runtime.h"

void abort(void)
{
    c_test_fail(1);
}
