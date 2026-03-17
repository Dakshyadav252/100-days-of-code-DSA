#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    if (N <= 0) {
        printf("\n");
        return 0;
    }

    int *queue = malloc(sizeof(int) * N);
    if (!queue) return 0;
    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &queue[i]) != 1) { free(queue); return 0; }
    }

    /* use an array as stack to reverse the queue */
    int *stack = malloc(sizeof(int) * N);
    if (!stack) { free(queue); return 0; }
    int top = 0;
    for (int i = 0; i < N; ++i) stack[top++] = queue[i];

    /* pop and print */
    for (int i = top - 1; i >= 0; --i) {
        printf("%d", stack[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");

    free(queue);
    free(stack);
    return 0;
}