#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) return 0;

    int cap = 16;
    int *keys = malloc(cap * sizeof *keys);
    int *cnts = malloc(cap * sizeof *cnts);
    if (!keys || !cnts) return 0;

    int unique = 0;
    for (int i = 0; i < n; ++i) {
        int v;
        if (scanf("%d", &v) != 1) return 0;

        int found = 0;
        for (int j = 0; j < unique; ++j) {
            if (keys[j] == v) { cnts[j]++; found = 1; break; }
        }
        if (!found) {
            if (unique == cap) {
                cap *= 2;
                int *k2 = realloc(keys, cap * sizeof *k2);
                int *c2 = realloc(cnts, cap * sizeof *c2);
                if (!k2 || !c2) return 0;
                keys = k2;
                cnts = c2;
            }
            keys[unique] = v;
            cnts[unique] = 1;
            unique++;
        }
    }

    for (int i = 0; i < unique; ++i) {
        if (i) printf(" ");
        printf("%d:%d", keys[i], cnts[i]);
    }
    printf("\n");

    free(keys);
    free(cnts);
    return 0;
}