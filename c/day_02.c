#include <stdio.h>
#include <string.h>
#include "aoc_utils.h"
#include "aoc_common.h"
#include "aoc_testing.h"

// sample input given by the aoc official page
static const char SAMPLE_INPUT[] =
"1-3 a: abcde\n"
"1-3 b: cdefg\n"
"2-9 c: ccccccccc1721\n"
;

typedef enum {
    INCREMENT_MIN,
    INCREMENT_MAX,
    READ_CHAR,
    READ_ROW
} RowAction;

LinkedList *build_day_02_linked_list(char *input) {
    LinkedList *ll = linked_list_new(STRING);
    if (!ll) {
        perror("Failed to allocate linkedlist\n");
        exit(1);
    }
    char buff[50];
    int bufind = 0;
    char *str = NULL;
    for (usize i = 0; i < strlen(input); i++) {
        if (input[i] == '\n') {
            buff[bufind] = '\0';
            str = (char *) malloc(strlen(buff) + 1);
            strcpy(str, buff);
            bufind = 0;
            linked_list_push_str(ll, str);
            continue;
        }
        buff[bufind++] = input[i];
    }
    return ll;
}

// part 1 of the day 1 challenge
usize day_02_part_01(char *input) {
    LinkedList *rows = build_day_02_linked_list(input);
    int min, max, char_count;
    char c;
    RowAction ra;
    usize accum = 0;
    char *str;

    for (LinkedListNode *n = rows -> head; n; n = n -> next) {
        str = n -> value.s;
        ra = INCREMENT_MIN;
        char_count = 0;
        min = 0;
        max = 0;
        for (usize i = 0; i < strlen(str); i++) switch (str[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (ra == INCREMENT_MIN) {
                    min *= 10;
                    min += str[i] - '0';
                } else {
                    max *= 10;
                    max += str[i] - '0';
                }
                break;
            case '-':
                ra = INCREMENT_MAX;
                break;
            case ' ':
                if (ra == INCREMENT_MAX) ra = READ_CHAR;
                else ra = READ_ROW;
                break;
            case ':':
                break;
            default:
                if (ra == READ_CHAR) c = str[i];
                else if (str[i] == c) char_count++;
                break;
        }
        accum += char_count >= min && char_count <= max;
    }
    linked_list_destroy(rows);
    return accum;
}

// part 2 of the day 1 challenge
usize day_02_part_02(char *input) {
    LinkedList *rows = build_day_02_linked_list(input);
    int min, max;
    char c;
    RowAction ra;
    usize accum = 0;
    char *str;
    int str_ind, bye_switch;
    char char_at_pos_1, char_at_pos_2;

    for (LinkedListNode *n = rows -> head; n; n = n -> next) {
        str = n -> value.s;
        ra = INCREMENT_MIN;
        min = 0;
        max = 0;
        str_ind = 1;
        bye_switch = 0;
        char_at_pos_1 = '\0';
        char_at_pos_2 = '\0';
        for (usize i = 0; i < strlen(str); i++) switch (str[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (ra == INCREMENT_MIN) {
                    min *= 10;
                    min += str[i] - '0';
                } else {
                    max *= 10;
                    max += str[i] - '0';
                }
                break;
            case '-':
                ra = INCREMENT_MAX;
                break;
            case ' ':
                if (ra == INCREMENT_MAX) ra = READ_CHAR;
                else ra = READ_ROW;
                break;
            case ':':
                break;
            default:
                if (bye_switch) break;
                else if (ra == READ_CHAR) {
                    c = str[i];
                    break;
                }
                else if (str_ind > max) bye_switch++;
                else if (str_ind == min) char_at_pos_1 = str[i];
                else if (str_ind == max) char_at_pos_2 = str[i];
                str_ind++;
                break;
        }
        accum += (char_at_pos_1 == c) != (char_at_pos_2 == c);
    }
    linked_list_destroy(rows);
    return accum;
}

int day_02_test_01() {
    return assert_eq(day_02_part_01((char *) SAMPLE_INPUT), 2, NULL);
}

int day_02_test_02() {
    return assert_eq(day_02_part_02((char *) SAMPLE_INPUT), 1, NULL);
}

int day_02_tests() {
    int accum = 1;
    accum &= run_test(day_02_test_01, "day_02", "test1");
    accum &= run_test(day_02_test_02, "day_02", "test2");
    return accum;
}
