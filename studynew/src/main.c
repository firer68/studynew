#include "list.h"
#include "io.h"
#include <stdio.h>
#include <string.h>

/* 插入模式 */
#define INSERT_HEAD 0
#define INSERT_TAIL 1

/* ========== 原自动测试部分（保持不变） ========== */

static int add_student(Node **head, int mode, const char *name, int score) {
    Student stu;
    strncpy(stu.name, name, NAME_LEN - 1);
    stu.name[NAME_LEN - 1] = '\0';
    stu.score = score;
    if (mode == INSERT_HEAD) {
        return list_insert_head(head, &stu);
    }
    return list_insert_tail(head, &stu);
}

static void test_basic(void) {
    io_print_title("Test 1: basic insert/find/print/length");
    Node *head = list_create();
    add_student(&head, INSERT_HEAD, "Alice", 90);
    add_student(&head, INSERT_TAIL, "Bob",   85);
    add_student(&head, INSERT_TAIL, "Carol", 78);
    list_print(head);
    io_print_result("length", 3, list_length(head));
    Node *f = list_find_by_name(head, "Bob");
    printf("find Bob   : %s\n", f ? "found" : "not found");
    f = list_find_by_name(head, "Nobody");
    printf("find Nobody: %s\n", f ? "found" : "not found");
    list_free(&head);
}

static void test_delete_empty(void) {
    io_print_title("Test 2: delete from empty list");
    Node *head = list_create();
    int removed = list_delete_by_name(&head, "Alice");
    io_print_result("deleted count", 0, removed);
    io_print_result("length", 0, list_length(head));
    list_print(head);
    list_free(&head);
}

static void test_delete_single(void) {
    io_print_title("Test 3: delete the only node");
    Node *head = list_create();
    add_student(&head, INSERT_HEAD, "Alice", 90);
    int removed = list_delete_by_name(&head, "Alice");
    io_print_result("deleted count", 1, removed);
    io_print_result("head is NULL", 1, head == NULL ? 1 : 0);
    list_free(&head);
}

static void test_delete_not_exist(void) {
    io_print_title("Test 4: delete nonexistent value");
    Node *head = list_create();
    add_student(&head, INSERT_TAIL, "Alice", 90);
    add_student(&head, INSERT_TAIL, "Bob",   85);
    int removed = list_delete_by_name(&head, "Zoe");
    io_print_result("deleted count", 0, removed);
    io_print_result("length", 2, list_length(head));
    list_print(head);
    list_free(&head);
}

static void test_delete_duplicates(void) {
    io_print_title("Test 5: delete duplicate values");
    Node *head = list_create();
    add_student(&head, INSERT_TAIL, "Alice", 90);
    add_student(&head, INSERT_TAIL, "Bob",   85);
    add_student(&head, INSERT_TAIL, "Alice", 70);
    add_student(&head, INSERT_TAIL, "Alice", 60);
    int removed = list_delete_by_name(&head, "Alice");
    io_print_result("deleted count", 3, removed);
    io_print_result("length after delete", 1, list_length(head));
    list_print(head);
    list_free(&head);
}

static void test_free_null(void) {
    io_print_title("Test 6: free then pointer is NULL");
    Node *head = list_create();
    add_student(&head, INSERT_TAIL, "Alice", 90);
    list_free(&head);
    io_print_result("head == NULL after free", 1, head == NULL ? 1 : 0);
    list_free(&head);
    io_print_result("double free safe", 1, head == NULL ? 1 : 0);
}

/* 依次运行全部自动测试 */
static void run_all_tests(void) {
    test_basic();
    test_delete_empty();
    test_delete_single();
    test_delete_not_exist();
    test_delete_duplicates();
    test_free_null();
}

/* ========== 交互菜单部分 ========== */

static void print_menu(void) {
    printf("\n========== 学生链表管理 ==========\n");
    printf(" 1. 头插学生\n");
    printf(" 2. 尾插学生\n");
    printf(" 3. 按姓名删除\n");
    printf(" 4. 按姓名查找\n");
    printf(" 5. 打印链表\n");
    printf(" 6. 显示链表长度\n");
    printf(" 7. 清空链表(整表释放)\n");
    printf(" 8. 运行自动测试\n");
    printf(" 0. 退出\n");
    printf("==================================\n");
    printf("请选择: ");
}

static void do_insert(Node **head, int mode) {
    Student stu;
    if (io_read_student(&stu) != 0) {
        printf("输入无效，已取消\n");
        return;
    }
    int rc = (mode == INSERT_HEAD)
             ? list_insert_head(head, &stu)
             : list_insert_tail(head, &stu);
    if (rc == 0) {
        printf("插入成功: %s (%d 分)\n", stu.name, stu.score);
    } else {
        printf("插入失败（内存不足）\n");
    }
}

static void do_delete(Node **head) {
    char name[NAME_LEN];
    printf("请输入要删除的姓名: ");
    if (io_read_line(name, sizeof(name)) != 0 || name[0] == '\0') {
        printf("输入无效\n");
        return;
    }
    int n = list_delete_by_name(head, name);
    if (n < 0) {
        printf("参数错误\n");
    } else if (n == 0) {
        printf("未找到 %s\n", name);
    } else {
        printf("删除了 %d 个 %s\n", n, name);
    }
}

static void do_find(Node *head) {
    char name[NAME_LEN];
    printf("请输入要查找的姓名: ");
    if (io_read_line(name, sizeof(name)) != 0 || name[0] == '\0') {
        printf("输入无效\n");
        return;
    }
    Node *p = list_find_by_name(head, name);
    if (p != NULL) {
        printf("找到: %s, %d 分\n", p->data.name, p->data.score);
    } else {
        printf("未找到 %s\n", name);
    }
}

/* 处理一次菜单选择；返回 0 表示继续，返回 1 表示退出 */
static int handle_choice(Node **head, int choice) {
    switch (choice) {
        case 1: do_insert(head, INSERT_HEAD); break;
        case 2: do_insert(head, INSERT_TAIL); break;
        case 3: do_delete(head);             break;
        case 4: do_find(*head);              break;
        case 5: list_print(*head);           break;
        case 6: printf("链表长度: %d\n", list_length(*head)); break;
        case 7:
            list_free(head);
            printf("链表已清空\n");
            break;
        case 8: run_all_tests();             break;
        case 0: return 1;
        default: printf("无效选项，请重新输入\n"); break;
    }
    return 0;
}

static void run_menu(void) {
    Node *head = list_create();
    int running = 1;
    while (running) {
        print_menu();
        int choice = -1;
        if (io_read_int("", &choice) != 0) {
            printf("请输入数字\n");
            continue;
        }
        running = !handle_choice(&head, choice);
    }
    list_free(&head);   /* 退出前保证释放 */
    printf("已退出，链表已释放\n");
}

int main(void) {
    run_menu();
    return 0;
}