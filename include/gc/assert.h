#ifndef GC_ASSERT_H
#define GC_ASSERT_H

void __msl_assertion_failed(const char* condition, const char* filename, const char* funcname, int lineno);

#define assert(condition) \
    ((condition) ? ((void)0) : __msl_assertion_failed(#condition, __FILE__, __func__, __LINE__))

#endif
