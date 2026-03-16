#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int prec(char op) {
    if (op == '^') return 4;
    if (op == '*' || op == '/') return 3;
    if (op == '+' || op == '-') return 2;
    return 0;
}

static int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int main(void) {
    char buf[1024];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    /* remove trailing newline */
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';

    char stack[1024];
    int top = -1;
    char out[1024];
    int oi = 0;

    for (size_t i = 0; buf[i]; ++i) {
        char c = buf[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            out[oi++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') out[oi++] = stack[top--];
            if (top >= 0 && stack[top] == '(') --top; /* pop '(' */
        } else if (is_operator(c)) {
            if (c == '^') {
                /* right-associative: pop while precedence(top) > prec(c) */
                while (top >= 0 && is_operator(stack[top]) && prec(stack[top]) > prec(c))
                    out[oi++] = stack[top--];
            } else {
                /* left-associative: pop while precedence(top) >= prec(c) */
                while (top >= 0 && is_operator(stack[top]) && prec(stack[top]) >= prec(c))
                    out[oi++] = stack[top--];
            }
            stack[++top] = c;
        }
        /* other characters ignored */
    }

    while (top >= 0) {
        if (stack[top] != '(' && stack[top] != ')') out[oi++] = stack[top];
        --top;
    }

    out[oi] = '\0';
    printf("%s\n", out);
    return 0;
}