#ifndef UNIT_H
#define UNIT_H

typedef void (*unit_test_t)(void);

#define TEST(name)                                                      \
    void unit__##name(void);                                            \
    static void unit__##name##_init(void) __attribute__((constructor)); \
    static void unit__##name##_init(void)                               \
    {                                                                   \
        unit_test_add(""#name, unit__##name);                                \
    }                                                                   \
    void unit__##name(void)

void unit_test_fail(const char *fmt,...);
void unit_test_add(const char *name, unit_test_t test);
int  unit_tests_run(void);

#endif /* UNIT_H */

#ifdef UNIT_H_IMPLEMENTATION

#ifndef UNIT_H_SIZE
#define UNIT_H_SIZE 128
#endif /* UNIT_H_REALLOC */

#ifndef UNIT_H_REALLOC
#define UNIT_H_REALLOC realloc
#endif /* UNIT_H_REALLOC */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct unit__test {
    unit_test_t func;
    const char *name;
};

static size_t unit__size = 0, unit__ntests = 0;
static struct unit__test *unit__tests = 0;

void
unit_test_add(const char *name, unit_test_t func)
{
    if (unit__ntests + 1 >= unit__size) {
        unit__size += UNIT_H_SIZE;
        unit__tests = (struct unit__test *)UNIT_H_REALLOC(unit__tests, unit__size);
        if (!unit__tests)
            unit_test_fail("realloc failed:");
    }

    unit__tests[unit__ntests].name = name;
    unit__tests[unit__ntests].func = func;
    unit__ntests++;
}

void
unit_test_fail(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
        fputc(' ', stderr);
        perror(NULL);
    } else {
        fputc('\n', stderr);
    }

    exit(EXIT_FAILURE);
}

#ifndef UNIT_H_RUN_TEST
#define UNIT_H_RUN_TEST unit_test_run
#include <unistd.h>
#include <sys/wait.h>

int
unit_test_run(const struct unit__test *t)
{
    int status;

    switch (fork()) {
    case -1:
        unit_test_fail("Failed to fork process:");
        return -1;
    case 0:
        t->func();
        exit(EXIT_SUCCESS);
        return 0; /* UNREACHABLE */
    default:
        wait(&status);
        return WEXITSTATUS(status);
    }
}
#endif /* linux */

int
unit_tests_run(void)
{
    int i, passed = 0;

    for (i = 0; i < unit__ntests; i++) {
        printf("Test [%d/%ld] %s...\n", i + 1, unit__ntests, unit__tests[i].name);
        passed += UNIT_H_RUN_TEST(&unit__tests[i]) == 0;
    }

    printf("%d of %ld tests passed.\n", passed, unit__ntests);
    return passed != unit__ntests;
}

#endif /* UNIT_H_IMPLEMENTATION */
