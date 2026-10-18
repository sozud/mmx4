#include "test_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

struct CTestSuite {
    const char* name;
    const struct CTestGroup* groups;
    const u32* group_count;
};
extern const struct CTestSuite c_test_suites[];
extern const u32 c_test_suite_count;

static int selected(const char* name, int argc, char** argv)
{
    int i;
    if (argc < 2)
        return 1;
    for (i = 1; i < argc; i++)
        if (strcmp(argv[i], name) == 0)
            return 1;
    return 0;
}

enum { CASE_FAIL,
    CASE_PASS,
    CASE_SKIP };

static int run_case(const struct CTestGroup* group, u32 index, u32* value)
{
    int fds[2], status;
    pid_t pid;
    if (pipe(fds) != 0)
        return CASE_FAIL;
    fflush(stdout);
    pid = fork();
    if (pid == 0) {
        u32 result;
        close(fds[0]);
        result = c_test_group_run(group, index);
        fflush(stdout);
        if (write(fds[1], &result, sizeof(result)) != sizeof(result))
            _exit(2);
        exit(0);
    }
    close(fds[1]);
    status = read(fds[0], value, sizeof(*value)) == sizeof(*value);
    close(fds[0]);
    if (pid < 0)
        return CASE_FAIL;
    {
        int wait_status;
        if (waitpid(pid, &wait_status, 0) != pid)
            return CASE_FAIL;
        if (WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == 77)
            return CASE_SKIP;
        return status && WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == 0 ? CASE_PASS : CASE_FAIL;
    }
}

static void case_name(const struct CTestGroup* group, u32 index, char* name, u32 size)
{
    snprintf(name, size, "%s#%u", group->name, index);
}

int main(int argc, char** argv)
{
    u32 s, g, i, number, passes = 0, failures = 0, skips = 0;
    char name[256];
    int describe = argc >= 2 && strcmp(argv[1], "--describe") == 0;
    if (describe) {
        argc--;
        argv++;
    }
    for (s = 0; s < c_test_suite_count; s++) {
        const struct CTestSuite* suite = &c_test_suites[s];
        if (!selected(suite->name, argc, argv))
            continue;
        number = 0;
        for (g = 0; g < *suite->group_count; g++) {
            const struct CTestGroup* group = &suite->groups[g];
            for (i = 0; i < group->count; i++, number++) {
                u32 value = 0;
                case_name(group, i, name, sizeof(name));
                if (describe) {
                    printf("%s\t%u\t%s\n", suite->name, number, name);
                    continue;
                }
                printf("CASE\t%s\t%u\t%s\n", suite->name, number, group->name);
                switch (run_case(group, i, &value)) {
                case CASE_PASS:
                    printf("PASS\t%s\t%u\t%s\t%u\n", suite->name, number, name, value);
                    passes++;
                    break;
                case CASE_SKIP:
                    printf("SKIP\t%s\t%u\t%s\n", suite->name, number, name);
                    skips++;
                    break;
                default:
                    printf("FAIL\t%s\t%u\t%s\n", suite->name, number, name);
                    failures++;
                    break;
                }
            }
        }
    }
    if (!describe)
        printf("%u passed, %u failed, %u skipped\n", passes, failures, skips);
    return failures != 0;
}
