#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DNode {
    int val;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct Deque {
    DNode *head;
    DNode *tail;
    int sz;
} Deque;

static Deque *deque_new(void) {
    Deque *d = malloc(sizeof(*d));
    if (!d) return NULL;
    d->head = d->tail = NULL;
    d->sz = 0;
    return d;
}

static DNode *node_new(int v) {
    DNode *n = malloc(sizeof(*n));
    if (!n) return NULL;
    n->val = v;
    n->prev = n->next = NULL;
    return n;
}

static void deque_push_front(Deque *d, int v) {
    DNode *n = node_new(v);
    if (!n) return;
    n->next = d->head;
    if (d->head) d->head->prev = n;
    d->head = n;
    if (!d->tail) d->tail = n;
    d->sz++;
}

static void deque_push_back(Deque *d, int v) {
    DNode *n = node_new(v);
    if (!n) return;
    n->prev = d->tail;
    if (d->tail) d->tail->next = n;
    d->tail = n;
    if (!d->head) d->head = n;
    d->sz++;
}

static int deque_pop_front(Deque *d, int *out) {
    if (!d->head) return 0;
    DNode *n = d->head;
    *out = n->val;
    d->head = n->next;
    if (d->head) d->head->prev = NULL;
    else d->tail = NULL;
    free(n);
    d->sz--;
    return 1;
}

static int deque_pop_back(Deque *d, int *out) {
    if (!d->tail) return 0;
    DNode *n = d->tail;
    *out = n->val;
    d->tail = n->prev;
    if (d->tail) d->tail->next = NULL;
    else d->head = NULL;
    free(n);
    d->sz--;
    return 1;
}

static int deque_front(Deque *d, int *out) {
    if (!d->head) return 0;
    *out = d->head->val;
    return 1;
}

static int deque_back(Deque *d, int *out) {
    if (!d->tail) return 0;
    *out = d->tail->val;
    return 1;
}

static int deque_empty(Deque *d) {
    return d->sz == 0;
}

static int deque_size(Deque *d) {
    return d->sz;
}

static void deque_clear(Deque *d) {
    DNode *cur = d->head;
    while (cur) {
        DNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    d->head = d->tail = NULL;
    d->sz = 0;
}

static void deque_print(Deque *d) {
    DNode *cur = d->head;
    if (!cur) {
        printf("\n");
        return;
    }
    int first = 1;
    while (cur) {
        if (!first) printf(" ");
        first = 0;
        printf("%d", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    Deque *d = deque_new();
    if (!d) return 0;

    for (int i = 0; i < N; ++i) {
        char cmd[32];
        if (scanf("%31s", cmd) != 1) break;

        if (strcmp(cmd, "push_front") == 0) {
            int x; if (scanf("%d", &x) != 1) break;
            deque_push_front(d, x);
        } else if (strcmp(cmd, "push_back") == 0) {
            int x; if (scanf("%d", &x) != 1) break;
            deque_push_back(d, x);
        } else if (strcmp(cmd, "pop_front") == 0) {
            int v;
            if (deque_pop_front(d, &v)) printf("%d\n", v);
            else printf("-1\n");
        } else if (strcmp(cmd, "pop_back") == 0) {
            int v;
            if (deque_pop_back(d, &v)) printf("%d\n", v);
            else printf("-1\n");
        } else if (strcmp(cmd, "front") == 0) {
            int v;
            if (deque_front(d, &v)) printf("%d\n", v);
            else printf("-1\n");
        } else if (strcmp(cmd, "back") == 0) {
            int v;
            if (deque_back(d, &v)) printf("%d\n", v);
            else printf("-1\n");
        } else if (strcmp(cmd, "empty") == 0) {
            printf("%d\n", deque_empty(d));
        } else if (strcmp(cmd, "size") == 0) {
            printf("%d\n", deque_size(d));
        } else if (strcmp(cmd, "clear") == 0) {
            deque_clear(d);
        } else if (strcmp(cmd, "print") == 0) {
            deque_print(d);
        } else {
            /* ignore unknown command line */
            char tmp[256];
            fgets(tmp, sizeof(tmp), stdin);
        }
    }

    deque_clear(d);
    free(d);
    return 0;
}

