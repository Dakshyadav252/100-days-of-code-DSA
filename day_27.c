#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static Node *new_node(int v) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->val = v;
    n->next = NULL;
    return n;
}

static void free_list(Node *head) {
    Node *cur = head;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

static int list_len(Node *h) {
    int c = 0;
    for (; h; h = h->next) ++c;
    return c;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int *a = malloc(sizeof(int) * n);
    if (!a) return 0;
    for (int i = 0; i < n; ++i) if (scanf("%d", &a[i]) != 1) { free(a); return 0; }

    int m;
    if (scanf("%d", &m) != 1) { free(a); return 0; }
    int *b = malloc(sizeof(int) * m);
    if (!b) { free(a); return 0; }
    for (int i = 0; i < m; ++i) if (scanf("%d", &b[i]) != 1) { free(a); free(b); return 0; }

    /* find common suffix length */
    int i = n - 1, j = m - 1;
    while (i >= 0 && j >= 0 && a[i] == b[j]) { --i; --j; }
    int common_start_a = i + 1; /* index in a where shared suffix begins, if common_len > 0 */
    int common_start_b = j + 1;

    /* build first list and keep pointers */
    Node **pa = malloc(sizeof(Node*) * n);
    if (!pa) { free(a); free(b); return 0; }
    Node *head1 = NULL, *tail1 = NULL;
    for (int k = 0; k < n; ++k) {
        pa[k] = new_node(a[k]);
        if (!pa[k]) {
            /* cleanup allocated so far */
            for (int t = 0; t < k; ++t) free(pa[t]);
            free(pa); free(a); free(b);
            return 0;
        }
        if (!head1) head1 = tail1 = pa[k];
        else { tail1->next = pa[k]; tail1 = pa[k]; }
    }

    /* build second list; reuse nodes for common suffix to simulate intersection */
    Node *head2 = NULL, *tail2 = NULL;
    if (common_start_b == 0 && common_start_a < n) {
        /* entire second list is the shared suffix */
        head2 = pa[common_start_a];
    } else {
        /* create unique prefix nodes for second list */
        for (int k = 0; k < common_start_b; ++k) {
            Node *nn = new_node(b[k]);
            if (!nn) {
                /* free second list prefix built so far */
                Node *t = head2;
                while (t) { Node *tmp = t; t = t->next; free(tmp); }
                free(pa); free(a); free(b);
                free_list(head1);
                return 0;
            }
            if (!head2) head2 = tail2 = nn;
            else { tail2->next = nn; tail2 = nn; }
        }
        if (common_start_a < n) {
            /* link the shared suffix from first list */
            if (!head2) head2 = pa[common_start_a];
            else tail2->next = pa[common_start_a];
        }
    }

    /* find intersection using lengths */
    int len1 = list_len(head1);
    int len2 = list_len(head2);
    Node *p = head1, *q = head2;
    if (len1 > len2) {
        int d = len1 - len2;
        while (d--) p = p->next;
    } else if (len2 > len1) {
        int d = len2 - len1;
        while (d--) q = q->next;
    }
    while (p && q && p != q) { p = p->next; q = q->next; }

    if (p && q) printf("%d\n", p->val);
    else printf("No Intersection\n");

    /* free memory without double-free: free unique nodes of list2 (if any), then free entire list1 */
    if (common_start_a < n) {
        /* there is a shared suffix */
        Node *cur = head2;
        while (cur && cur != pa[common_start_a]) {
            Node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        /* now free list1 (which includes the shared suffix) */
        free_list(head1);
    } else {
        /* no shared suffix: free both lists independently */
        free_list(head2);
        free_list(head1);
    }

    free(pa); free(a); free(b);
    return 0;
}