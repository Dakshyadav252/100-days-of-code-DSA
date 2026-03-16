#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static int push(Node **top, int v) {
    Node *n = malloc(sizeof(*n));
    if (!n) return 0;
    n->val = v;
    n->next = *top;
    *top = n;
    return 1;
}

static int pop(Node **top, int *out) {
    if (!*top) return 0;
    Node *n = *top;
    *out = n->val;
    *top = n->next;
    free(n);
    return 1;
}

static void free_stack(Node *top) {
    while (top) {
        Node *t = top;
        top = top->next;
        free(t);
    }
}

static int is_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int main(void) {
    char buf[8192];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    Node *stk = NULL;
    char *tok = strtok(buf, " \t\r\n");
    while (tok) {
        char *end;
        long v = strtol(tok, &end, 10);
        if (*end == '\0') {
            if (!push(&stk, (int)v)) { free_stack(stk); return 0; }
        } else if (strlen(tok) == 1 && is_op(tok[0])) {
            int b, a;
            if (!pop(&stk, &b) || !pop(&stk, &a)) { free_stack(stk); return 0; }
            int r = 0;
            switch (tok[0]) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/': r = b == 0 ? 0 : a / b; break;
            }
            if (!push(&stk, r)) { free_stack(stk); return 0; }
        }
        /* ignore unknown tokens */
        tok = strtok(NULL, " \t\r\n");
    }

    int result;
    if (!pop(&stk, &result)) {
        free_stack(stk);
        return 0;
    }

    printf("%d\n", result);
    free_stack(stk);
    return 0;
}