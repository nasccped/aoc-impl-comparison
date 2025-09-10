#ifndef AOC_TESTING_H
#define AOC_TESTING_H

/* Define usefull testing tooles (such as Python/Rust). */

#include "aoc_utils.h"

int assert_eq(usize value1, usize value2, const char *message);
int run_test(int (*func)(void), const char *mod_name, const char *func_name);

#endif
