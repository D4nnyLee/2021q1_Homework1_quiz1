#include <stdbool.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

node_t *list_make_node_t(node_t *list, int value);

void list_free(node_t **list);

void quicksort(node_t **list);
