#ifndef AOC_UTILS_H
#define AOC_UTILS_H

/* Advent of code common utilities (functions, type alias, structs, ...) */

#include <stdlib.h>

// size_t alias to usize
typedef long long unsigned int usize;

/* generics */
typedef enum _GenericVariantEnum {
    INT, DOUBLE, CHAR, STRING
} GenericVariant;

int char_is_num(char c);

/* Linked List content */
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

/* Linked List functions controller */
// Constructor
LinkedList *linked_list_new(GenericVariant type);
// Push int element
LinkedListNode *linked_list_push_int(LinkedList *ll, int value);
// Push char pointer element
LinkedListNode *linked_list_push_str(LinkedList *ll, char *value);
// Dealocate Linked List mem
void linked_list_destroy(LinkedList *ll);

/* Binary Tree Set */
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
/* Binary Tree Set (node) */
typedef struct _BTreeSetStruct {
    GenericVariant type;
    BTreeSetNode *root;
} BTreeSet;

/* Binary Tree Set functions controller */
// Constructor
BTreeSet *b_tree_set_new(GenericVariant type);
// Constructs from a Linked List
BTreeSet *b_tree_set_from_linked_list(LinkedList *ll);
int b_tree_set_contains_int(BTreeSet *bst, int value);
// Push a new int element to the set
void b_tree_set_push_int(BTreeSet *bts, int value);
// Push the int element through value checking in set node

// Compare two nodes
int b_tree_set_node_compare(BTreeSetNode *left,
                            BTreeSetNode *right,
                            GenericVariant type);
// Free BTreeSet mem
void b_tree_set_destroy(BTreeSet *ll);
// Free BTreeSet nodes mem
void b_tree_set_destroy_by_recursion(BTreeSetNode *node, GenericVariant type);

// Relationship functions through LinkedList and BTreeSet
void fullfil_ll_from_b_tree_set(LinkedList *ll,
                                BTreeSetNode *node,
                                GenericVariant type);
LinkedList *linked_list_from_b_tree_set(BTreeSet *bts);

#endif
