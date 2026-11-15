#include "test_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <process.h>
#else
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
extern char** environ;
#endif

struct CTestSuite {
    const char* name;
    const struct CTestGroup* groups;
    const u32* group_count;
};
extern const struct CTestSuite c_test_suites[];
extern const u32 c_test_suite_count;

enum RunMode { MODE_FORK,
    MODE_SPAWN };

enum { CASE_FAIL,
    CASE_PASS,
    CASE_SKIP };

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

static const char* program_path;

static int spawn_case(char* const* args)
{
#ifdef _WIN32
    char program[1024];
    snprintf(program, sizeof(program), "\"%s\"", _pgmptr);
    ((const char**)args)[0] = program;
    return (int)_spawnv(_P_WAIT, _pgmptr, (const char* const*)args);
#else
    pid_t pid;
    int status;
    if (posix_spawnp(&pid, program_path, NULL, NULL, args, environ) != 0)
        return -1;
    if (waitpid(pid, &status, 0) != pid || !WIFEXITED(status))
        return -1;
    return WEXITSTATUS(status);
#endif
}

static int run_case_process(u32 suite, u32 group, u32 index, u32* value)
{
    char numbers[3][16], result_path[64];
    char* args[7];
    int code;
    FILE* result;
    int status = 0;
    snprintf(numbers[0], sizeof(numbers[0]), "%u", suite);
    snprintf(numbers[1], sizeof(numbers[1]), "%u", group);
    snprintf(numbers[2], sizeof(numbers[2]), "%u", index);
    snprintf(result_path, sizeof(result_path), "mmx4_tests_case_%d.tmp", (int)getpid());
    args[0] = (char*)program_path;
    args[1] = "--case";
    args[2] = numbers[0];
    args[3] = numbers[1];
    args[4] = numbers[2];
    args[5] = result_path;
    args[6] = NULL;
    remove(result_path);
    fflush(stdout);
    code = spawn_case(args);
    result = fopen(result_path, "rb");
    if (result != NULL) {
        status = fread(value, sizeof(*value), 1, result) == 1;
        fclose(result);
        remove(result_path);
    }
    if (code == 77)
        return CASE_SKIP;
    return status && code == 0 ? CASE_PASS : CASE_FAIL;
}

static int run_child_case(char** argv)
{
    const struct CTestSuite* suite = &c_test_suites[strtoul(argv[2], NULL, 10)];
    const struct CTestGroup* group = &suite->groups[strtoul(argv[3], NULL, 10)];
    u32 result;
    FILE* out;
#ifdef _WIN32
    _set_error_mode(_OUT_TO_STDERR);
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif
    result = c_test_group_run(group, strtoul(argv[4], NULL, 10));
    fflush(stdout);
    out = fopen(argv[5], "wb");
    if (out == NULL || fwrite(&result, sizeof(result), 1, out) != 1)
        return 2;
    fclose(out);
    return 0;
}

#ifndef _WIN32
static int run_case_fork(const struct CTestGroup* group, u32 index, u32* value)
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
#endif

static int run_case(enum RunMode mode, u32 suite, u32 group, u32 index, u32* value)
{
#ifdef _WIN32
    (void)mode;
    return run_case_process(suite, group, index, value);
#else
    if (mode == MODE_SPAWN)
        return run_case_process(suite, group, index, value);
    return run_case_fork(&c_test_suites[suite].groups[group], index, value);
#endif
}

static void case_name(const struct CTestGroup* group, u32 index, char* name, u32 size)
{
    snprintf(name, size, "%s#%u", group->name, index);
}

static enum RunMode default_mode(void)
{
#ifdef _WIN32
    return MODE_SPAWN;
#else
    return MODE_FORK;
#endif
}

static void drop_argument(int* argc, char** argv, int index)
{
    int i;
    for (i = index; i < *argc - 1; i++)
        argv[i] = argv[i + 1];
    (*argc)--;
}

int main(int argc, char** argv)
{
    u32 s, g, i, number, passes = 0, failures = 0, skips = 0;
    char name[256];
    int describe = 0, arg;
    enum RunMode mode = default_mode();
    program_path = argv[0];
    if (argc == 6 && strcmp(argv[1], "--case") == 0)
        return run_child_case(argv);
    for (arg = 1; arg < argc;) {
        if (strcmp(argv[arg], "--describe") == 0)
            describe = 1;
        else if (strcmp(argv[arg], "--spawn") == 0)
            mode = MODE_SPAWN;
#ifndef _WIN32
        else if (strcmp(argv[arg], "--fork") == 0)
            mode = MODE_FORK;
#endif
        else {
            arg++;
            continue;
        }
        drop_argument(&argc, argv, arg);
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
                switch (run_case(mode, s, g, i, &value)) {
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
