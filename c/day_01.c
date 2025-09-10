#include <stdio.h>
#include <string.h>
#include "aoc_utils.h"
#include "aoc_common.h"
#include "aoc_testing.h"

// sample input given by the aoc official page
static const char SAMPLE_INPUT[] =
"1721\n"
"979\n"
"366\n"
"299\n"
"675\n"
"1456\n"
;

// utility used to fullfil a LinkedList from the input of day 1 (impl on the
// end of the file).
void fullfil_ll_with_input(LinkedList *ll, char *input);

// part 1 of the day 1 challenge
usize day_01_part_01(char *input) {
    LinkedList *vals = linked_list_new(INT);
    BTreeSet *set = b_tree_set_new(INT);
    if (!vals || !set) {
        perror("LinkedList/BTreeSet alloc failed!\n");
        exit(1);
    }
    fullfil_ll_with_input(vals, input);
    int v, diff;
    for (LinkedListNode *temp = vals -> head; temp; temp = temp -> next) {
        v = temp -> value.i;
        diff = 2020 - v;
        if (b_tree_set_contains_int(set, diff)) {
            linked_list_destroy(vals);
            b_tree_set_destroy(set);
            return v * diff;
        }
        b_tree_set_push_int(set, v);
    }
    linked_list_destroy(vals);
    b_tree_set_destroy(set);
    return 0;
}

// part 2 of the day 1 challenge
usize day_01_part_02(char *input) {
    LinkedList *vals = linked_list_new(INT);
    BTreeSet *set = b_tree_set_new(INT);
    if (!vals || !set) {
        perror("LinkedList/BTreeSet alloc failed!\n");
        exit(1);
    }
    fullfil_ll_with_input(vals, input);
    LinkedList *aux;
    int a_val, b_val, v;
    for (LinkedListNode *n = vals -> head; n; n = n -> next) {
        v = n -> value.i;
        aux = linked_list_from_b_tree_set(set);
        for (LinkedListNode *a = aux -> head; a; a = a -> next) {
            for (LinkedListNode *b = aux -> head; b; b = b -> next) {
                a_val = a -> value.i;
                b_val = b -> value.i;
                if (a_val + b_val == 2020 - v) {
                    linked_list_destroy(aux);
                    linked_list_destroy(vals);
                    b_tree_set_destroy(set);
                    return a_val * b_val * v;
                }
            }
        }
        linked_list_destroy(aux);
        b_tree_set_push_int(set, v);
    }
    linked_list_destroy(vals);
    b_tree_set_destroy(set);
    return 0;
}

void fullfil_ll_with_input(LinkedList *ll, char *input) {
    int curnum = 0;
    for (usize i = 0; i < strlen(input); i++) {
        if (input[i] == '\n') {
            linked_list_push_int(ll, curnum);
            curnum = 0;
            continue;
        }
        curnum *= 10;
        curnum += input[i] - '0';
    }
}

int day_01_test_01() {
    return assert_eq(day_01_part_01((char *) SAMPLE_INPUT), 514579, NULL);
}

int day_01_test_02() {
    return assert_eq(day_01_part_02((char *) SAMPLE_INPUT), 241861950, NULL);
}

int day_01_tests() {
    int accum = 1;
    accum &= run_test(day_01_test_01, "day_01", "test1");
    accum &= run_test(day_01_test_02, "day_01", "test2");
    return accum;
}
