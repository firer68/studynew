#ifndef LIST_H
#define LIST_H

#define NAME_LEN 32

/* 学生数据类型：姓名 + 分数 */
typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

/* 链表节点 */
typedef struct Node {
    Student data;
    struct Node *next;
} Node;

/*
 * 创建空链表。
 * 返回值：空链表头指针（NULL）。
 */
Node *list_create(void);

/*
 * 头插法插入一个学生。
 * 参数：head —— 链表头指针的地址；stu —— 待插入的学生数据。
 * 返回值：成功 0，失败（内存不足/参数非法）-1。
 */
int list_insert_head(Node **head, const Student *stu);

/*
 * 尾插法插入一个学生。
 * 参数：head —— 链表头指针的地址；stu —— 待插入的学生数据。
 * 返回值：成功 0，失败 -1。
 */
int list_insert_tail(Node **head, const Student *stu);

/*
 * 按姓名删除所有匹配节点（支持重复值）。
 * 参数：head —— 链表头指针的地址；name —— 目标姓名。
 * 返回值：删除的节点个数；参数非法返回 -1。
 */
int list_delete_by_name(Node **head, const char *name);

/*
 * 按姓名查找第一个匹配节点。
 * 参数：head —— 链表头；name —— 目标姓名。
 * 返回值：找到返回节点指针，未找到返回 NULL。
 */
Node *list_find_by_name(Node *head, const char *name);

/*
 * 遍历打印整条链表。
 * 参数：head —— 链表头（只读）。
 * 返回值：无。
 */
void list_print(const Node *head);

/*
 * 释放整张链表，并把 *head 置为 NULL，避免野指针。
 * 参数：head —— 链表头指针的地址；传 NULL 时什么都不做。
 * 返回值：无。
 */
void list_free(Node **head);

/*
 * 返回链表节点数。
 * 参数：head —— 链表头（只读）。
 * 返回值：节点数量；head 为 NULL 时返回 0。
 */
int list_length(const Node *head);

#endif