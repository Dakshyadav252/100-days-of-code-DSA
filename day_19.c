#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n < 2) return 0;

    int *a = malloc(n * sizeof *a);
    if (!a) return 0;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1) { free(a); return 0; }
    }

    qsort(a, n, sizeof *a, cmp_int);

    int l = 0, r = n - 1;
    long long best_sum = (long long)a[l] + a[r];
    int best_l = a[l], best_r = a[r];

    while (l < r) {
        long long sum = (long long)a[l] + a[r];
        if (llabs(sum) < llabs(best_sum)) {
            best_sum = sum;
            best_l = a[l];
            best_r = a[r];
        }
        if (sum < 0) ++l;
        else if (sum > 0) --r;
        else { best_l = a[l]; best_r = a[r]; break; }
    }

    printf("%d %d\n", best_l, best_r);
    free(a);