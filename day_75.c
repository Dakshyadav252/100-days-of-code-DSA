#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct { long long sum; int idx; } Pair;

static int cmp_pair(const void *a, const void *b) {
    const Pair *A = a, *B = b;
    if (A->sum < B->sum) return -1;
    if (A->sum > B->sum) return 1;
    if (A->idx < B->idx) return -1;
    if (A->idx > B->idx) return 1;
    return 0;
}

int main(void) {
    int cap = 16, n = 0;
    int *arr = malloc(sizeof(int) * cap);
    if (!arr) return 1;

    int x;
    while (scanf("%d", &x) == 1) {
        if (n == cap) {
            cap *= 2;
            int *tmp = realloc(arr, sizeof(int) * cap);
            if (!tmp) { free(arr); return 1; }
            arr = tmp;
        }
        arr[n++] = x;
    }

    if (n == 0) {
        printf("0\n");
        free(arr);
        return 0;
    }

    Pair *pairs = malloc(sizeof(Pair) * (n + 1));
    if (!pairs) { free(arr); return 1; }

    long long s = 0;
    pairs[0].sum = 0;
    pairs[0].idx = 0;
    for (int i = 0; i < n; ++i) {
        s += arr[i];
        pairs[i + 1].sum = s;
        pairs[i + 1].idx = i + 1;
    }

    qsort(pairs, n + 1, sizeof(Pair), cmp_pair);

    int best = 0;
    int i = 0;
    while (i < n + 1) {
        int j = i + 1;
        while (j < n + 1 && pairs[j].sum == pairs[i].sum) ++j;
        int min_idx = pairs[i].idx;
        int max_idx = pairs[j - 1].idx;
        if (max_idx - min_idx > best) best = max_idx - min_idx;
        i = j;
    }

    printf("%d\n", best);

    free(arr);
    free(pairs);