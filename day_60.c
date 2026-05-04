#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    if (N <= 0) { printf("YES\n"); return 0; }

    int *a = malloc(sizeof(int) * N);
    if (!a) return 0;
    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &a[i]) != 1) { free(a); return 0; }
    }

    /* If -1 is used to denote NULL in level-order, ensure completeness:
       once a -1 appears, no later non--1 should appear. */
    int seen_null = 0;
    for (int i = 0; i < N; ++i) {
        if (a[i] == -1) seen_null = 1;
        else if (seen_null) {
            printf("NO\n");
            free(a);
            return 0;
        }
    }

    /* Check min-heap property: parent <= children for existing nodes */
    for (int i = 0; i < N; ++i) {
        if (a[i] == -1) continue;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < N && a[l] != -1 && a[i] > a[l]) { printf("NO\n"); free(a); return 0; }
        if (r < N && a[r] != -1 && a[i] > a[r]) { printf("NO\n"); free(a); return 0; }
    }

    printf("YES\n");
    free(a);
    return 0;
}