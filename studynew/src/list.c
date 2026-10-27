#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *list_create(void) {
    return NULL;
}

int list_insert_head(Node **head, const Student *stu) {
    if (head == NULL || stu == NULL) {
        return -1;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return -1;
    }
    node->data = *stu;
    node->next = *head;
    *head = node;
    return 0;
}

int list_insert_tail(Node **head, const Student *stu) {
    if (head == NULL || stu == NULL) {
        return -1;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return -1;
    }
    node->data = *stu;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
        return 0;
    }
    Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    return 0;
}

int list_delete_by_name(Node **head, const char *name) {
    if (head == NULL || name == NULL) {
        return -1;
    }
    int count = 0;
    /* 用二级指针遍历，可统一处理"删除头节点"和"删除中间节点" */
    Node **pp = head;
    while (*pp != NULL) {
        if (strcmp((*pp)->data.name, name) == 0) {
            Node *victim = *pp;
            *pp = victim->next;
            free(victim);
            count++;
        } else {
            pp = &(*pp)->next;
        }
    }
    return count;
}

Node *list_find_by_name(Node *head, const char *name) {
    if (name == NULL) {
        return NULL;
    }
    Node *cur = head;
    while (cur != NULL) {
        if (strcmp(cur->data.name, name) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void list_print(const Node *head) {
    if (head == NULL) {
        printf("[empty list]\n");
        return;
    }
    const Node *cur = head;
    int idx = 1;
    while (cur != NULL) {
        printf("%d: name=%s, score=%d\n", idx++, cur->data.name, cur->data.score);
        cur = cur->next;
    }
}

void list_free(Node **head) {
    if (head == NULL) {
        return;
    }
    Node *cur = *head;
    while (cur != NULL) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL; /* 置空，防止野指针 / 二次释放 */
}

int list_length(const Node *head) {
    int n = 0;
    const Node *cur = head;
    while (cur != NULL) {
        n++;
        cur = cur->next;
    }
    return n;
}