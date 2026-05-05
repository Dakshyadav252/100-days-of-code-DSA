#include <stdio.h>
#include <string.h>

int main(void) {
    static char s[1000005];
    if (scanf("%1000000s", s) != 1) return 1;

    int cnt[26] = {0};
    for (int i = 0; s[i]; ++i) {
        int idx = s[i] - 'a';
        if (++cnt[idx] == 2) {
            putchar(s[i]);
            putchar('\n');
            return 0;
        }
    }

    printf("-1\n");
    return 0;