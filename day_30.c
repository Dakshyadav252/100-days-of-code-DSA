#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coeff;
    int exp;
    struct Term *next;
} Term;

static Term *new_term(int c, int e) {
    Term *t = malloc(sizeof(*t));
    if (!t) return NULL;
    t->coeff = c;
    t->exp = e;
    t->next = NULL;
    return t;
}

/* insert in descending exponent order; combine like exponents */
static int insert_term(Term **head, int c, int e) {
    if (c == 0) return 1;
    Term *prev = NULL, *cur = *head;
    while (cur && cur->exp > e) {
        prev = cur;
        cur = cur->next;
    }
    if (cur && cur->exp == e) {
        cur->coeff += c;
        if (cur->coeff == 0) {
            /* remove node */
            if (prev) prev->next = cur->next;
            else *head = cur->next;
            free(cur);
        }
        return 1;
    }
    Term *t = new_term(c, e);
    if (!t) return 0;
    if (!prev) {
        t->next = *head;
        *head = t;
    } else {
        t->next = prev->next;
        prev->next = t;
    }
    return 1;
}

static void free_list(Term *h) {
    while (h) {
        Term *tmp = h;
        h = h->next;
        free(tmp);
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Term *head = NULL;
    for (int i = 0; i < n; ++i) {
        int c, e;
        if (scanf("%d %d", &c, &e) != 1) break;
        if (!insert_term(&head, c, e)) {
            free_list(head);
            return 0;
        }
    }

    if (!head) {
        printf("0\n");
        return 0;
    }

    Term *cur = head;
    int first = 1;
    while (cur) {
        int c = cur->coeff;
        int e = cur->exp;
        if (c == 0) { cur = cur->next; continue; }

        if (!first) {
            if (c < 0) printf(" - ");
            else printf(" + ");
        } else {
            if (c < 0) printf("-");
            first = 0;
        }

        int ac = c < 0 ? -c : c;
        if (e == 0) {
            printf("%d", ac);
        } else if (e == 1) {
            printf("%dx", ac);
        } else {
            printf("%dx^%d", ac, e);
        }

        cur = cur->next;
    }
    printf("\n");

    free_list(head);
    return 0;
}