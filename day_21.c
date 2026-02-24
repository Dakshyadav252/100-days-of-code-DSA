#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) { printf("\n"); return 0; }

    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; ++i) {
        int v;
        if (scanf("%d", &v) != 1) {
            while (head) { Node *t = head->next; free(head); head = t; }
            return 0;
        }
        Node *node = malloc(sizeof *node);
        if (!node) {
            while (head) { Node *t = head->next; free(head); head = t; }
            return 0;
        }
        node->val = v;
        node->next = NULL;
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
    }

    int first = 1;
    for (Node *cur = head; cur != NULL; cur = cur->next) {
        if (!first) printf(" ");
        printf("%d", cur->val);
        first = 0;
    }
    printf("\n");

    while (head) { Node *t = head->next; free(head); head = t; }
    return 0;
}