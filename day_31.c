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
        int op;
        if (scanf("%d", &op) != 1) break;
        if (op == 1) {
            int val;
            if (scanf("%d", &val) != 1) break;
            if (top == cap) {
                printf("Stack Overflow\n");
            } else {
                stk[top++] = val;
            }
        } else if (op == 2) {
            if (top == 0) {
                printf("Stack Underflow\n");
            } else {
                printf("%d\n", stk[--top]);
            }
        } else if (op == 3) {
            if (top == 0) {
                printf("\n");
            } else {
                for (int j = top - 1; j >= 0; --j) {
                    printf("%d", stk[j]);
                    if (j > 0) printf(" ");
                }
                printf("\n");
            }
        }
    }

    free(stk);
    return 0;
}