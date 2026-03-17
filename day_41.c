#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static int enqueue(Node **head, Node **tail, int v) {
    Node *n = malloc(sizeof(*n));
    if (!n) return 0;
    n->val = v;
    n->next = NULL;
    if (!*tail) *head = *tail = n;
    else {
        (*tail)->next = n;
        *tail = n;
    }
    return 1;
}

static int dequeue(Node **head, Node **tail, int *out) {
    if (!*head) return 0;
    Node *n = *head;
    *out = n->val;
    *head = n->next;
    if (!*head) *tail = NULL;
    free(n);
    return 1;
}

static void free_list(Node *head) {
    while (head) {
        Node *t = head;
        head = head->next;
        free(t);
    }
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < N; ++i) {
        char cmd[32];
        if (scanf("%31s", cmd) != 1) break;
        if (strcmp(cmd, "enqueue") == 0) {
            int x;
            if (scanf("%d", &x) != 1) break;
            if (!enqueue(&head, &tail, x)) { free_list(head); return 0; }
        } else if (strcmp(cmd, "dequeue") == 0) {
            int v;
            if (dequeue(&head, &tail, &v)) printf("%d\n", v);
            else printf("-1\n");
        } else {
            /* unknown command: skip rest of line */
            char tmp[256];
            fgets(tmp, sizeof(tmp), stdin);
        }
    }

    free_list(head);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static int enqueue(Node **head, Node **tail, int v) {
    Node *n = malloc(sizeof(*n));
    if (!n) return 0;
    n->val = v;
    n->next = NULL;
    if (!*tail) *head = *tail = n;
    else {
        (*tail)->next = n;
        *tail = n;
    }
    return 1;
}

static int dequeue(Node **head, Node **tail, int *out) {
    if (!*head) return 0;
    Node *n = *head;
    *out = n->val;
    *head = n->next;
    if (!*head) *tail = NULL;
    free(n);
    return 1;
}

static void free_list(Node *head) {
    while (head) {
        Node *t = head;
        head = head->next;
        free(t);
    }
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < N; ++i) {
        char cmd[32];
        if (scanf("%31s", cmd) != 1) break;
        if (strcmp(cmd, "enqueue") == 0) {
            int x;
            if (scanf("%d", &x) != 1) break;
            if (!enqueue(&head, &tail, x)) { free_list(head); return 0; }
        } else if (strcmp(cmd, "dequeue") == 0) {
            int v;
            if (dequeue(&head, &tail, &v)) printf("%d\n", v);
            else printf("-1\n");
            } else {
            /* unknown command: skip rest of line */
            char tmp[256];
            fgets(tmp, sizeof(tmp), stdin);
        }
    }

    free_list(head);
    return 0;
}