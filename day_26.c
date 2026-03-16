#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int val;
    struct DNode *prev;
    struct DNode *next;
} DNode;

static int append_node(DNode **head, DNode **tail, int v) {
    DNode *n = malloc(sizeof(DNode));
    if (!n) return 0;
    n->val = v;
    n->prev = *tail;
    n->next = NULL;
    if (!*head) *head = *tail = n;
    else {
        (*tail)->next = n;
        *tail = n;
    }
    return 1;
}

static void free_list(DNode *head) {
    DNode *cur = head;
    while (cur) {
        DNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    DNode *head = NULL, *tail = NULL;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) break;
        if (!append_node(&head, &tail, x)) {
            free_list(head);
            return 0;
        }
    }

    DNode *cur = head;
    while (cur) {
        printf("%d", cur->val);
        if (cur->next) printf(" ");
        cur = cur->next;
    }
    printf("\n");

    free_list(head);
    return 0;
}