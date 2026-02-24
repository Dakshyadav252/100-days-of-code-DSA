#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) break;
        Node *node = malloc(sizeof(Node));
        if (!node) return 0;
        node->val = x;
        node->next = NULL;
        if (!head) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }

    Node *cur = head;
    while (cur) {
        printf("%d", cur->val);
        if (cur->next) printf(" ");
        cur = cur->next;
    }
    printf("\n");

    // free list
    cur = head;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }

    return 0;
}