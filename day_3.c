#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) {
        printf("Not Found\nComparisons = 0\n");
        return 0;
    }

    int *a = malloc(n * sizeof *a);
    if (!a) return 0;

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1) { free(a); return 0; }
    }

    int k;
    if (scanf("%d", &k) != 1) { free(a); return 0; }

    int comparisons = 0;
    int found = -1;
    for (int i = 0; i < n; ++i) {
        ++comparisons;
        if (a[i] == k) { found = i; break; }
    }

    if (found != -1)
        printf("Found at index %d\n", found);
    else
        printf("Not Found\n");

    printf("Comparisons = %d\n", comparisons);

    free(a);
    return 0;
}