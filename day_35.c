#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int cap = n > 0 ? n : 1;
    int *queue = malloc(sizeof(int) * cap);
    if (!queue) return 0;

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &queue[i]) != 1) {
            free(queue);
            return 0;
        }
    }

    if (n == 0) {
        printf("\n");
        free(queue);
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        printf("%d", queue[i]);
        if (i + 1 < n) printf(" ");
    }
    printf("\n");

    free(queue);
    return 0;
}