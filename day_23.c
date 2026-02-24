#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static Node *append_node(Node **head, Node **tail, int v) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->val = v;
    n->next = NULL;
    if (!*head) *head = *tail = n;
    else {
        (*tail)->next = n;
        *tail = n;
    }
    return n;
}

static Node *merge_lists(Node *a, Node *b) {
    Node dummy;
    Node *t = &dummy;
    dummy.next = NULL;
    while (a && b) {
        if (a->val <= b->val) {
            t->next = a;
            a = a->next;
        } else {
            t->next = b;
            b = b->next;
        }
        t = t->next;
        t->next = NULL;
    }
    t->next = a ? a : b;
    return dummy.next;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Node *h1 = NULL, *t1 = NULL;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) break;
        if (!append_node(&h1, &t1, x)) return 0;
    }

    int m;
    if (scanf("%d", &m) != 1) {
        // if second list size not provided, print first list and exit
        Node *cur = h1;
        while (cur) {
            printf("%d", cur->val);
            if (cur->next) printf(" ");
            cur = cur->next;
        }
        printf("\n");
        // free
        cur = h1;
        while (cur) { Node *tmp = cur; cur = cur->next; free(tmp); }
        return 0;
    }

    Node *h2 = NULL, *t2 = NULL;
    for (int i = 0; i < m; ++i) {
        int x;
        if (scanf("%d", &x) != 1) break;
        if (!append_node(&h2, &t2, x)) return 0;
    }

    Node *merged = merge_lists(h1, h2);

    Node *cur = merged;
    while (cur) {
        printf("%d", cur->val);
        if (cur->next) printf(" ");
        cur = cur->next;
    }
    printf("\n");

    // free merged list
    cur = merged;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }

    return 0;
}