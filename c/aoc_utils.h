#ifndef AOC_UTILS_H
#define AOC_UTILS_H

/* Advent of code common utilities (functions, type alias, structs, ...) */

#include <stdlib.h>

typedef long long unsigned int usize;

typedef enum _GenericVariantEnum {
    INT, DOUBLE, CHAR, STRING
} GenericVariant;

typedef struct _BTreeSetNodeStruct {
    union {
        int i;
        double d;
        char c;
        char *s;
    } value;
    struct _BTreeSetNodeStruct *left;
    struct _BTreeSetNodeStruct *right;
} BTreeSetNode;

typedef struct _BTreeSetStruct {
    GenericVariant type;
    BTreeSetNode *root;
} BTreeSet;

typedef struct _LinkedListNodeStruct {
    union {
        int i;
        double d;
        char c;
        char *s;
    } value;
    struct _LinkedListNodeStruct *next;
} LinkedListNode;

typedef struct _LinkedListStruct {
    GenericVariant type;
    LinkedListNode *head;
} LinkedList;

BTreeSet *b_tree_set_new(GenericVariant);
BTreeSet *b_tree_set_from_linked_list(LinkedList *);
int b_tree_set_contains_int(BTreeSet *, int);
void b_tree_set_push_int(BTreeSet *, int);
int b_tree_set_node_compare(BTreeSetNode *, BTreeSetNode *, GenericVariant);
void b_tree_set_destroy(BTreeSet *);

int char_is_num(char c);

void linked_list_destroy(LinkedList *);
LinkedList *linked_list_from_b_tree_set(BTreeSet *);
LinkedList *linked_list_new(GenericVariant);
LinkedListNode *linked_list_push_int(LinkedList *, int );
LinkedListNode *linked_list_push_str(LinkedList *, char *);

#endif
