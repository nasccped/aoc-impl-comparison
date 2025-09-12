#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc_testing.h"
#include "aoc_common.h"

static char
i01[] =
#include "../inputs/day-01.c.txt"
,
i02[] =
#include "../inputs/day-02.c.txt"
,
i03[] =
#include "../inputs/day-03.c.txt"
;

int tests();

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("No action for this amount of args (%d)\n", argc);
        printf("Aborting...\n");
        return 1;
    }
    // skip if no args (goto main body)
    else if (argc < 2);
    else if (!strcmp(argv[1], "test")) return tests();
    else {
        printf("Non valid arg: %s\n", argv[1]);
        return 1;
    }
    printf("Result for day 2 input (part 1): %lld\n", day_02_part_01(i02));
    return 0;
}

int tests() {
    int result = 1;
    result &= day_01_tests();
    result &= day_02_tests();
    result &= day_03_tests();
    return !result;
}
