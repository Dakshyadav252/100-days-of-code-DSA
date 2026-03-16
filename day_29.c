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

    int k;
    if (scanf("%d", &k) != 1) {
        /* no k provided: print original list */
        Node *cur = head;
        while (cur) {
            printf("%d", cur->val);
            if (cur->next) printf(" ");
            cur = cur->next;
        }
        printf("\n");
        free_list(head);
        return 0;
    }

    if (!head) {
        printf("\n");
        return 0;
    }

    if (n == 0) {
        printf("\n");
        return 0;
    }

    k %= n;
    if (k < 0) k = (k + n) % n;
    if (k == 0) {
        /* no rotation */
        Node *cur = head;
        while (cur) {
            printf("%d", cur->val);
            if (cur->next) printf(" ");
            cur = cur->next;
        }
        printf("\n");
        free_list(head);
        return 0;
    }

    /* make circular */
    tail->next = head;

    /* new tail is at position n - k - 1 (0-indexed) from head */
    int steps = n - k;
    Node *new_tail = head;
    for (int i = 1; i < steps; ++i) new_tail = new_tail->next;

    Node *new_head = new_tail->next;
    new_tail->next = NULL; /* break circularity */

    /* print rotated list */
    Node *cur = new_head;
    while (cur) {
        printf("%d", cur->val);
        if (cur->next) printf(" ");
        cur = cur->next;
    }
    printf("\n");

    free_list(new_head);
    return 0;
}