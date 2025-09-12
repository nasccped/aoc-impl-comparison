#include <stdio.h>
#include <string.h>
#include "aoc_utils.h"
#include "aoc_common.h"
#include "aoc_testing.h"

// sample input given by the aoc official page
static const char SAMPLE_INPUT[] =
"..##.......\n"
"#...#...#..\n"
".#....#..#.\n"
"..#.#...#.#\n"
".#...##..#.\n"
"..#.##.....\n"
".#.#.#....#\n"
".#........#\n"
"#.##...#...\n"
"#...##....#\n"
".#..#...#.#\n"
;

usize DAY_03_ROW_LENGTH = 0;

LinkedList *gen_linked_list_for_day_03(char *input) {
    LinkedList *ll = linked_list_new(STRING);
    if (!ll) {
        perror("Linked list alloc failed\n");
        exit(1);
    }
    char buf[40];
    usize bufind = 0;
    char *str = NULL;
    for (usize i = 0; i < strlen(input); i++) {
        if (input[i] == '\n') {
            buf[bufind] = '\0';
            str = (char *) malloc(strlen(buf) + 1);
            if (!str) {
                perror("String alloc failed\n");
                exit(1);
            }
            strcpy(str, buf);
            linked_list_push_str(ll, str);
            str = NULL;
            bufind = 0;
            continue;
        }
        buf[bufind++] = input[i];
    }
    return ll;
}

usize input_traversal(LinkedList *ll, usize x_incr, usize y_incr) {
    usize accum = 0;
    LinkedListNode *n = ll -> head;
    usize x = x_incr;
    while (n) {
        for (usize y = 0; y < y_incr; y++) {
            n = n -> next;
            if (!n) break;
        }
        if (!n) break;
        char cel = n -> value.s[x];
        if (cel == '#') accum++;
        x = (x + x_incr) % DAY_03_ROW_LENGTH;
    }
    return accum;
}

// part 1 of the day 3 challenge
usize day_03_part_01(char *input) {
    for (usize i = 0; input[i] != '\n'; i++) DAY_03_ROW_LENGTH = i;
    DAY_03_ROW_LENGTH++;
    LinkedList *rows = gen_linked_list_for_day_03(input);
    usize result = input_traversal(rows, 3, 1);
    linked_list_destroy(rows);
    return result;
}

// part 2 of the day 3 challenge
usize day_03_part_02(char *input) {
    for (usize i = 0; input[i] != '\n'; i++) DAY_03_ROW_LENGTH = i;
    DAY_03_ROW_LENGTH++;
    LinkedList *rows = gen_linked_list_for_day_03(input);
    usize result = 0;
    usize traversal_count;
    usize traversals[][2] = {
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2},
    };
    for (int i = 0; i < 5; i++) {
        traversal_count = input_traversal(rows,
                                          traversals[i][0],
                                          traversals[i][1]);
        if (traversal_count && !result) result++;
        result *= traversal_count ? traversal_count : 1;
    }
    linked_list_destroy(rows);
    return result;
}

int day_03_test_01() {
    return assert_eq(day_03_part_01((char *) SAMPLE_INPUT), 7, NULL);
}

int day_03_test_02() {
    return assert_eq(day_03_part_02((char *) SAMPLE_INPUT), 336, NULL);
}

int day_03_tests() {
    int accum = 1;
    accum &= run_test(day_03_test_01, "day_03", "test1");
    accum &= run_test(day_03_test_02, "day_03", "test2");
    return accum;
}
