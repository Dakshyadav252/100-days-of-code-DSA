#include <stdio.h>
#include <stdlib.h>

static int cmp_ll(const void *a, const void *b) {
    long long va = *(const long long *)a;
    long long vb = *(const long long *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) { printf("0\n"); return 0; }

    long long *pref = malloc((size_t)(n + 1) * sizeof *pref);
    if (!pref) return 0;

    pref[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int v;
        if (scanf("%d", &v) != 1) { free(pref); return 0; }
        pref[i] = pref[i - 1] + v;
    }

    qsort(pref, (size_t)(n + 1), sizeof *pref, cmp_ll);

    long long result = 0;
    int i = 0;
    while (i <= n) {
        int j = i + 1;
        while (j <= n && pref[j] == pref[i]) ++j;
        long long k = j - i;
        result += k * (k - 1) / 2;
        i = j;
    }

    printf("%lld\n", result);