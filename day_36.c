#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) {
        /* consume possible remaining input and print empty line */
        int dummy;
        if (scanf("%d", &dummy) != 1) { /* ignore */ }
        printf("\n");
        return 0;
    }

    int *arr = malloc(sizeof(int) * n);
    if (!arr) return 0;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 0;
        }
    }

    int m;
    if (scanf("%d", &m) != 1) {
        /* no m provided: print current queue front->rear */
        for (int i = 0; i < n; ++i) {
            if (i) printf(" ");
            printf("%d", arr[i]);
        }
        printf("\n");
        free(arr);
        return 0;
    }

    /* treat m as number of rotations (dequeue then enqueue) */
    if (n > 0) {
        m %= n;
        if (m < 0) m = (m % n + n) % n;
    } else {
        m = 0;
    }

    /* print starting from index m (rotated left by m) */
    for (int i = 0; i < n; ++i) {
        int idx = (m + i) % n;
        if (i) printf(" ");
        printf("%d", arr[idx]);
    }
    printf("\n");

    free(arr);