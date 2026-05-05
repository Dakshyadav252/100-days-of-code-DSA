#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *strdup_local(const char *s) {
    size_t n = strlen(s) + 1;
    char *t = malloc(n);
    if (t) memcpy(t, s, n);
    return t;
}

static int cmpstr(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 1;
    if (n <= 0) return 0;

    char **names = malloc(sizeof(char*) * n);
    if (!names) return 1;

    char buf[1001];
    for (int i = 0; i < n; ++i) {
        if (scanf("%1000s", buf) != 1) return 1;
        names[i] = strdup_local(buf);
        if (!names[i]) return 1;
    }

    qsort(names, n, sizeof(char*), cmpstr);

    char *best = names[0];
    int bestcnt = 1;
    char *cur = names[0];
    int curcnt = 1;

    for (int i = 1; i < n; ++i) {
        if (strcmp(names[i], cur) == 0) {
            ++curcnt;
        } else {
            if (curcnt > bestcnt || (curcnt == bestcnt && strcmp(cur, best) < 0)) {
                bestcnt = curcnt;
                best = cur;
            }
            cur = names[i];
            curcnt = 1;
        }
    }
    /* handle last group */
    if (curcnt > bestcnt || (curcnt == bestcnt && strcmp(cur, best) < 0)) {
        bestcnt = curcnt;
        best = cur;
    }

    printf("%s %d\n", best, bestcnt);

    for (int i = 0; i < n; ++i) free(names[i]);
    free(names);
    return 0;
}