#include <stdio.h>
#include <string.h>

int main(void) {
    char s[100001];
    if (!fgets(s, sizeof s, stdin)) return 0;
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[--n] = '\0';
    size_t i = 0, j = n == 0 ? 0 : n - 1;
    while (i < j) {
        if (s[i] != s[j]) {
            printf("NO\n");
            return 0;
        }
        ++i;
        --j;
    }
    printf("YES\n");
    return 0;
}