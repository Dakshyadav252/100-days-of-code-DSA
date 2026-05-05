#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int m;
    if (scanf("%d", &m) != 1) return 1;
    int q;
    if (scanf("%d", &q) != 1) return 1;

    long long *table = malloc(sizeof(long long) * m);
    int *state = calloc(m, sizeof(int)); // 0 = empty, 1 = occupied

    char op[16];
    long long key;

    for (int t = 0; t < q; ++t) {
        if (scanf("%s %lld", op, &key) != 2) return 1;
        int h = (int)((key % m + m) % m);

        if (strcmp(op, "INSERT") == 0) {
            int found = 0;
            for (int i = 0; i < m; ++i) {
                int idx = (h + (int)((long long)i * i % m)) % m;
                if (state[idx] == 1 && table[idx] == key) { found = 1; break; }
                if (state[idx] == 0) {
                    table[idx] = key;
                    state[idx] = 1;
                    break;
                }
            }
            (void)found; // no output required for INSERT
        } else if (strcmp(op, "SEARCH") == 0) {
            int found = 0;
            for (int i = 0; i < m; ++i) {
                int idx = (h + (int)((long long)i * i % m)) % m;
                if (state[idx] == 0) break; // empty slot -> not present
                if (state[idx] == 1 && table[idx] == key) { found = 1; break; }
            }
            if (found) printf("FOUND\n"); else printf("NOT FOUND\n");
        } else {
            // unknown operation
            return 1;
        }
    }

    free(table);
    free(state);
    return 0;
}
