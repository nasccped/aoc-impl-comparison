#include <stdio.h>
#include "aoc_testing.h"

/*
 * Implementation of size_t (usize) value assertion, message is optional.
 * This function will return boolean as int:
 * if succeed -> 1
 * else -> 0
 */
int assert_eq(usize value1, usize value2, const char *message) {
    if (value1 != value2) {
        if (message) printf(message, value1, value2);
        else printf("Assert Panic: left value is `%lld` but right value is `%lld`.",
                    value1,
                    value2);
        return 0;
    }
    return 1;
}

/*
 * Does almost the same as the function above, but with pretty printing in
 * terminal.
 *
 * It receives a function pointer that returns int (bool) and don't receives
 * arguments (function above is expected).
 *
 * The mod name refers to the module (day 1, day 2, ...). The func_name refers
 * to the part of the challenge (1, 2).
 */
int run_test(int (*func)(void), const char *mod_name, const char *func_name) {
    // if any of these are NULL
    if (!func || !mod_name || !func_name) {
        perror("Mod and Func name (also Func pointer) must always be NOT-NULL.\n");
        perror("Aborting...\n");
        exit(1);
    }
    printf("Running \033[33m%s\033[0m::\033[33m%s\033[0m: ", mod_name, func_name);
    int result = func();
    if (result) printf("\033[92mok\033[0m\n");
    else printf("\n test \033[91mfailed\033[0m\n");
    return result;
}
