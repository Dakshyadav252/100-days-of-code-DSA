#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static int append_node(Node **head, Node **tail, int v) {
    Node *n = malloc(sizeof(Node));
    if (!n) return 0;
    n->val = v;
    n->next = NULL;
    if (!*head) *head = *tail = n;
    else {
        (*tail)->next = n;
        *tail = n;
    }
    return 1;
}

static void free_list(Node *head) {
    Node *cur = head;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1) break;
        if (!append_node(&head, &tail, x)) {
            free_list(head);
            return 0;
        }
    }

    int key;
    if (scanf("%d", &key) != 1) {
        // no key provided: print original list
        Node *cur = head;
        while (cur) {
            printf("%d", cur->val);
            if (cur->next) printf(" ");
            cur = cur->next;
        }
        printf("\n");
        free_list(head);
        return 0;
    }

    // delete first occurrence of key
    if (head) {
        if (head->val == key) {
            Node *tmp = head;
            head = head->next;
            free(tmp);
        } else {
            Node *prev = head;
            Node *cur = head->next;
            while (cur && cur->val != key) {
                prev = cur;
                cur = cur->next;
            }
            if (cur) {
                prev->next = cur->next;
                free(cur);
            }
        }
    }

    // print resulting list
    Node *cur = head;
    while (cur) {
        printf("%d", cur->val);
        if (cur->next) printf(" ");
        cur = cur->next;
    }
    printf("\n");

    free_list(head);
    return 0;
}