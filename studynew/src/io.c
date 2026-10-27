#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void io_print_title(const char *title) {
    if (title == NULL) {
        title = "";
    }
    printf("\n========== %s ==========\n", title);
}

void io_print_result(const char *name, int expected, int actual) {
    const char *status = (expected == actual) ? "PASS" : "FAIL";
    printf("[%s] %s: expected=%d, actual=%d\n",
           status, name ? name : "", expected, actual);
}

int io_read_line(char *buf, int size) {
    if (buf == NULL || size <= 0) {
        return -1;
    }
    if (fgets(buf, size, stdin) == NULL) {
        return -1;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        /* 行太长，清掉剩余字符，避免污染下一次输入 */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            /* discard */
        }
    }
    return 0;
}

int io_read_int(const char *prompt, int *value) {
    if (prompt != NULL) {
        printf("%s", prompt);
    }
    char buf[64];
    if (io_read_line(buf, sizeof(buf)) != 0) {
        return -1;
    }
    char *end = NULL;
    long v = strtol(buf, &end, 10);
    if (end == buf) {          /* 一个数字都没读到 */
        return -1;
    }
    if (value != NULL) {
        *value = (int)v;
    }
    return 0;
}

int io_read_student(Student *stu) {
    if (stu == NULL) {
        return -1;
    }
    char name[NAME_LEN];
    printf("请输入姓名: ");
    if (io_read_line(name, sizeof(name)) != 0) {
        return -1;
    }
    if (name[0] == '\0') {         /* 空姓名拒绝 */
        return -1;
    }
    strncpy(stu->name, name, NAME_LEN - 1);
    stu->name[NAME_LEN - 1] = '\0';

    int score = 0;
    if (io_read_int("请输入分数: ", &score) != 0) {
        return -1;
    }
    stu->score = score;
    return 0;
}