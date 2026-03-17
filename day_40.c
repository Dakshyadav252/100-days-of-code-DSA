#include <stdio.h>
#include <stdlib.h>

static void swap_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

static void sift_down(int a[], int n, int i) {
    while (1) {
        int l = 2 * i + 1;
        int r = l + 1;
        int largest = i;
        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;
        if (largest == i) break;
        swap_int(&a[i], &a[largest]);
        i = largest;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) {
        printf("\n");
        return 0;
    }

    int *a = malloc(sizeof(int) * n);
    if (!a) return 0;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1) { free(a); return 0; }
    }

    /* build max-heap */
    for (int i = n / 2 - 1; i >= 0; --i) sift_down(a, n, i);

    /* extract max repeatedly to sort ascending */
    for (int end = n - 1; end > 0; --end) {
        swap_int(&a[0], &a[end]);
        sift_down(a, end, 0);
    }

    for (int i = 0; i < n; ++i) {
        if (i) printf(" ");
        printf("%d", a[i]);
    }
    printf("\n");

    free(a);
    return 0;
}