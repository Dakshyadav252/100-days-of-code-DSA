#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int *arr = malloc(sizeof(int) * (N > 0 ? N : 1));
    if (!arr) return 0;
    int sz = 0;

    for (int i = 0; i < N; ++i) {
        char cmd[16];
        if (scanf("%15s", cmd) != 1) break;
        if (strcmp(cmd, "insert") == 0) {
            int x;
            if (scanf("%d", &x) != 1) break;
            /* insert x into sorted array (ascending) */
            int pos = 0;
            while (pos < sz && arr[pos] < x) ++pos;
            if (pos < sz) memmove(&arr[pos+1], &arr[pos], sizeof(int) * (sz - pos));
            arr[pos] = x;
            ++sz;
        } else if (strcmp(cmd, "delete") == 0) {
            if (sz == 0) {
                printf("-1\n");
            } else {
                printf("%d\n", arr[0]);
                if (sz > 1) memmove(&arr[0], &arr[1], sizeof(int) * (sz - 1));
                --sz;
            }
        } else if (strcmp(cmd, "peek") == 0) {
            if (sz == 0) printf("-1\n");
            else printf("%d\n", arr[0]);
        } else {
            /* unknown command - ignore rest of line */
            char tmp[256];
            fgets(tmp, sizeof(tmp), stdin);
        }
    }

    free(arr);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int *arr = malloc(sizeof(int) * (N > 0 ? N : 1));
    if (!arr) return 0;
    int sz = 0;

    for (int i = 0; i < N; ++i) {
        char cmd[16];
        if (scanf("%15s", cmd) != 1) break;
        if (strcmp(cmd, "insert") == 0) {
            int x;
            if (scanf("%d", &x) != 1) break;
            /* insert x into sorted array (ascending) */
            int pos = 0;
            while (pos < sz && arr[pos] < x) ++pos;
            if (pos < sz) memmove(&arr[pos+1], &arr[pos], sizeof(int) * (sz - pos));
            arr[pos] = x;
            ++sz;
        } else if (strcmp(cmd, "delete") == 0) {
            if (sz == 0) {
                printf("-1\n");
            } else {
                printf("%d\n", arr[0]);
                if (sz > 1) memmove(&arr[0], &arr[1], sizeof(int) * (sz - 1));
                --sz;
            }
        } else if (strcmp(cmd, "peek") == 0) {
            if (sz == 0) printf("-1\n");
            else printf("%d\n", arr[0]);
        } else {
            /* unknown command - ignore rest of line */
            char tmp[256];
            fgets(tmp, sizeof(tmp), stdin);
        }
    }

    free(arr);
    return 0;