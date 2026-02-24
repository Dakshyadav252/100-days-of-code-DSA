#include <stdio.h>
#include <string.h>

int main(void) {
    char s[100001];
    if (scanf("%100000s", s) != 1) return 0;
    size_t n = strlen(s);
    for (size_t i = 0; i < n; ++i) putchar(s[n - 1 - i]);
    putchar('\n');
}