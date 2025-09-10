#include "aoc_utils.h"
#include <string.h>
#include <stdio.h>

/* Creates a new LinkedList from a given type variant. */
LinkedList *linked_list_new(GenericVariant type) {
    LinkedList *p = (LinkedList *) malloc(sizeof(LinkedList));
    if (!p) return NULL;
    p -> type = type;
    p -> head = NULL;
    return p;
}

/* Pushes a new int node in an existing LinkedList.
 * It can fail if the LinkedList pointer is null or if it's
 * a non INT variant LinkedList. */
LinkedListNode *linked_list_push_int(LinkedList *ll, int value) {
    if (!ll) {
        perror("Linked list is NULL!\n");
        exit(1);
    }
    if (ll -> type != INT) {
        perror("Pushing an int to a non int linked list");
        exit(1);
    }
    LinkedListNode *p = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    if (!p) return NULL;
    p -> value.i = value;
    p -> next = NULL;
    if (!(ll -> head)) {
        ll -> head = p;
        return p;
    }
    LinkedListNode *temp;
    for (temp = ll -> head; temp -> next; temp = temp -> next);
    temp -> next = p;
    return p;
}

/* Deallocate a LinkedList pointer and it's nodes. */
void linked_list_destroy(LinkedList *ll) {
    if (!ll) return;
    LinkedListNode *temp = ll -> head, *aux;
    while (temp) {
        aux = temp -> next;
        switch (ll -> type) {
            case STRING:
                free(temp -> value.s);
                break;
            default:
                break;
        }
        free(temp);
        temp = aux;
    }
    free(ll);
}

/* Creates a new BTreeSet from a given type. */
BTreeSet *b_tree_set_new(GenericVariant type) {
    BTreeSet *p = (BTreeSet *) malloc(sizeof(BTreeSet));
    if (!p) return NULL;
    p -> type = type;
    p -> root = NULL;
    return p;
}

/* Pushes a new int element to an existing BTreeSet.
 * It can fail if the BTreeSet is a non-int Generic variant. */
void b_tree_set_push_int(BTreeSet *bts, int value) {
    if (!bts) {
        perror("BTreeSet pointer is null!\n");
        exit(1);
    }
    if (bts -> type != INT) {
        perror("Pushing an int value to a non int BTreeSet\n");
        exit(1);
    }
    BTreeSetNode *p = (BTreeSetNode *) malloc(sizeof(BTreeSetNode));
    if (!p) {
        perror("BTreeNode allocate failed");
        exit(1);
    }
    p -> value.i = value;
    p -> left = NULL;
    p -> right = NULL;
    if (!(bts -> root)) {
        bts -> root = p;
        return;
    }
    BTreeSetNode *temp = bts -> root;
    while (1) {
        if (b_tree_set_node_compare(temp, p, INT) < 0) {
            if (temp -> right) temp = temp -> right;
            else {
                temp -> right = p;
                break;
            }
        } else if (b_tree_set_node_compare(temp, p, INT) > 0) {
            if (temp -> left) temp = temp -> left;
            else {
                temp -> left = p;
                break;
            }
        } else break;
    }
}

/* Checks if the given BTreeSet pointer contains the given int element. */
int b_tree_set_contains_int(BTreeSet *bts, int value) {
    if (!bts) {
        perror("BTreeSet is NULL\n");
        exit(1);
    }
    if (bts -> type != INT) {
        perror("Searching for int in a non int BTreeSet\n");
        exit(1);
    }
    BTreeSetNode *node = bts -> root;
    while (node) {
        if (node -> value.i < value) node = node -> right;
        else if (node -> value.i > value) node = node -> left;
        else return 1;
    }
    return 0;
}

/* Compare two different BTreeSet nodes inner value by a given type.
 * Can fail if any of the pointers is null.
 *
 * The returned value will be:
 * - X when X < 0 => if left pointer is less than right pointer
 * - X when X > 0 => if left pointer is greater than right pointer
 * - X when X < 0 => if both are equals
 *
 * Math difference is used to get the value (strcmp function used when our
 * set is String type). */
int b_tree_set_node_compare(BTreeSetNode *left,
                            BTreeSetNode *right,
                            GenericVariant type) {
    if (!left || !right) {
        perror("BTreeSet comparing failed (pointers are null)!\n");
        exit(1);
    }
    switch (type) {
        case INT: return left -> value.i - right -> value.i;
        case DOUBLE: return left -> value.d - right -> value.d;
        case CHAR: return left -> value.c - right -> value.c;
        default: return strcmp(left -> value.s, right -> value.s);
    }
}

/* Deallocate mem used to store a BTreeSet. An assistant function is used to
 * clear the tree nodes (with recursion). */
void b_tree_set_destroy(BTreeSet *bts) {
    if (!bts) return;
    b_tree_set_destroy_by_recursion(bts -> root, bts -> type);
    free(bts);
}

/* Deallocate mem of all BTreeSet nodes recursively. */
void b_tree_set_destroy_by_recursion(BTreeSetNode *node, GenericVariant type) {
    if (!node) return;
    b_tree_set_destroy_by_recursion(node -> left, type);
    b_tree_set_destroy_by_recursion(node -> right, type);
    switch (type) {
        case STRING:
            free(node -> value.s);
            break;
        default:
    }
    free(node);
}

/* Create a new LinkedList from BTreeSet pointer.
 * It'll fail if the pointer is null
 * The LinkedList type+items will be set to the same as the BTreeSet
 * reference.
 *
 * This function also needs an assistant function to push items (using
 * recursion). */
LinkedList *linked_list_from_b_tree_set(BTreeSet *bts) {
    if (!bts) {
        perror("BTreeSet is null\n");
        exit(1);
    }
    LinkedList *p = linked_list_new(INT);
    if (!p) {
        perror("LinkedList alloc failed\n");
        exit(1);
    }
    fullfil_ll_from_b_tree_set(p, bts -> root, bts -> type);
    return p;
}

/* Function mentioned above. */
void fullfil_ll_from_b_tree_set(LinkedList *ll, BTreeSetNode *node, GenericVariant type) {
    if (!ll) {
        perror("LinkedList is NULL\n");
        exit(1);
    }
    if (!node) return;
    if (ll -> type != type) {
        perror("Non suitable type pushing\n");
        exit(1);
    }
    // push left, current node, then, right to preserve Set ordering.
    fullfil_ll_from_b_tree_set(ll, node -> left, type);
    switch (type) {
        case INT:
            linked_list_push_int(ll, node -> value.i);
            break;
        default:
            perror("Non implemented code (push: double/char/string func is missing)\n");
            exit(1);
            break;
    }
    fullfil_ll_from_b_tree_set(ll, node -> right, type);
}
