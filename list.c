#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static inline void list_add_node_t(node_t **list, node_t *node_t)
{
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right)
{
    while (*left)
        left = &((*left)->next);
    *left = right;
}

node_t *list_make_node_t(node_t *list, int value)
{
    node_t *node = (node_t *) malloc(sizeof(node_t));
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    node->next = list;
    node->value = value;

    return node;
}

void list_free(node_t **list)
{
    node_t *node = *list;
    *list = NULL;

    while (node) {
        node_t *tmp = node;
        node = node->next;
        free(tmp);
    }
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

#define MAX_LEVEL 300

    node_t **beg[MAX_LEVEL], *end[MAX_LEVEL];

    beg[0] = list;
    end[0] = NULL;

    for (int i = 0; i >= 0;) {
        if (*beg[i] == end[i])
            --i;
        else {
            node_t *pivot = *beg[i], *n = pivot->next;
            int val = pivot->value;
            pivot->next = NULL;

            int cnt_left = 0, cnt_right = 0;
            node_t *left = NULL, *right = NULL;
            while (n != end[i]) {
                node_t *tmp = n;
                n = n->next;

                if (tmp->value > val) {
                    ++cnt_right;
                    list_add_node_t(&right, tmp);
                } else {
                    ++cnt_left;
                    list_add_node_t(&left, tmp);
                }
            }

            list_concat(&right, end[i]);
            list_concat(&pivot, right);
            list_concat(&left, pivot);
            *beg[i] = left;

            beg[i + 1] = &pivot->next;
            end[i + 1] = end[i];
            end[i++] = pivot;

            if (cnt_left < cnt_right) {
                node_t **beg_swap = beg[i];
                beg[i] = beg[i - 1];
                beg[i - 1] = beg_swap;

                node_t *end_swap = end[i];
                end[i] = end[i - 1];
                end[i - 1] = end_swap;
            }
        }
    }

#undef MAX_LEVEL
}
