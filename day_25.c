#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static int append_node(Node **head, Node **tail, int v) {
    Node *n = malloc(sizeof(Node));
    if (!n) return 0;
    n->val = v;
    n->next = NULL;
    if (!*head) *head = *tail = n;
    else {
        (*tail)->next = n;
        *tail = n;
    }
    return 1;
}

static void free_list(Node *head) {
    Node *cur = head;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) break;
        if (!append_node(&head, &tail, x)) {
            free_list(head);
            return 0;
        }
    }

    int key;
    if (scanf("%d", &key) != 1) {
        free_list(head);
        return 0;
    }

    int count = 0;
    Node *cur = head;
    while (cur) {
        if (cur->val == key) ++count;
        cur = cur->next;
    }

    printf("%d\n", count);
    free_list(head);
    return 0;
}