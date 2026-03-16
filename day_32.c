#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int cap = n > 0 ? n : 1;
    int *stk = malloc(sizeof(int) * cap);
    if (!stk) return 0;
    int top = 0;

    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) { free(stk); return 0; }
        stk[top++] = x;
    }

    int m;
    if (scanf("%d", &m) != 1) {
        /* if pops not provided, just print current stack */
        m = 0;
    }

    for (int i = 0; i < m && top > 0; ++i) --top;

    if (top == 0) {
        printf("\n");
    } else {
        for (int i = top - 1; i >= 0; --i) {
            printf("%d", stk[i]);
            if (i > 0) printf(" ");
        }
        printf("\n");
    }

    free(stk);
    return 0;
}