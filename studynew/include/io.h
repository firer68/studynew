#ifndef IO_H
#define IO_H

#include "list.h"

/*
 * 打印一个带边框的测试标题。
 * 参数：title —— 标题字符串；为 NULL 时打印空标题。
 * 返回值：无。
 */
void io_print_title(const char *title);

/*
 * 打印一条测试断言结果（PASS / FAIL）。
 * 参数：name —— 测试名；expected —— 期望值；actual —— 实际值。
 * 返回值：无。
 */
void io_print_result(const char *name, int expected, int actual);

/*
 * 从 stdin 读一行，去掉末尾换行；超长部分丢弃。
 * 参数：buf —— 缓冲区；size —— 缓冲区大小。
 * 返回值：成功 0，EOF/参数非法 -1。
 */
int io_read_line(char *buf, int size);

/*
 * 从 stdin 读一个整数（带提示语）。
 * 参数：prompt —— 提示字符串，可为 NULL；value —— 输出参数。
 * 返回值：成功 0，输入非数字/EOF -1。
 */
int io_read_int(const char *prompt, int *value);

/*
 * 从 stdin 读一个学生的姓名和分数。
 * 参数：stu —— 输出参数，读入的学生数据。
 * 返回值：成功 0，输入无效/EOF -1。
 */
int io_read_student(Student *stu);

#endif