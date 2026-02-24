#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int r, c;
    if (scanf("%d %d", &r, &c) != 2) return 0;
    if (r <= 0 || c <= 0) return 0;

    int *a = malloc(r * c * sizeof *a);
    if (!a) return 0;

    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            scanf("%d", &a[i * c + j]);

    int top = 0, bottom = r - 1, left = 0, right = c - 1;
    int total = r * c, printed = 0;

    while (top <= bottom && left <= right) {
        // left -> right (top row)
        for (int j = left; j <= right && printed < total; ++j) {
            if (printed++) printf(" ");
            printf("%d", a[top * c + j]);
        }
        top++;

        // top -> bottom (right column)
        for (int i = top; i <= bottom && printed < total; ++i) {
            if (printed++) printf(" ");
            printf("%d", a[i * c + right]);
        }
        right--;

        // right -> left (bottom row)
        if (top <= bottom) {
            for (int j = right; j >= left && printed < total; --j) {
                if (printed++) printf(" ");
                printf("%d", a[bottom * c + j]);
            }
            bottom--;
        }

        // bottom -> top (left column)
        if (left <= right) {
            for (int i = bottom; i >= top && printed < total; --i) {
                if (printed++) printf(" ");
                printf("%d", a[i * c + left]);
            }
            left++;
        }
    }

    printf("\n");
    free(a);
    return 0;
}