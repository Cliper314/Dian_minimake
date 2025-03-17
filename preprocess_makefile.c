#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "syntax_check.h"

#define MAX_LINE_LENGTH 1024 // 定义每行的最大长度

// 预处理Makefile文件
void preprocess_makefile(const char *filename, int verbose_mode) {
    FILE *file = fopen(filename, "r"); // 打开Makefile文件
    if (file == NULL) {
        perror("Error opening Makefile");
        return;
    }

    char line[MAX_LINE_LENGTH]; // 用于存储每行的内容
    int line_number = 0; // 记录行号

    // 打开文件以写入清理后的内容（如果启用详细模式）
    FILE *output_file = NULL;
    if (verbose_mode) {
        output_file = fopen("Minimake_cleaned.mk", "w");
        if (output_file == NULL) {
            perror("Error creating Minimake_cleaned.mk");
            fclose(file);
            return;
        }
    }

    // 逐行读取Makefile文件
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        line_number++;

        // 去除行尾的换行符
        line[strcspn(line, "\n")] = 0;

        // 过滤空行（仅包含空白字符的行）
        int is_empty = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isspace(line[i])) {
                is_empty = 0;
                break;
            }
        }
        if (is_empty) {
            continue;
        }

        // 去除行尾空格
        int end = strlen(line) - 1;
        while (end >= 0 && isspace(line[end])) {
            line[end] = '\0';
            end--;
        }

        // 去除注释（#及其后面的内容）
        int comment_pos = strcspn(line, "#");
        if (comment_pos < strlen(line)) {
            line[comment_pos] = '\0';
        }

        // 去除注释后的行如果变成空行，则跳过
        is_empty = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isspace(line[i])) {
                is_empty = 0;
                break;
            }
        }
        if (is_empty) {
            continue;
        }

        // 调用语法检查函数完成静态语法检查
        syntax_check(line,line_number);

        // 如果启用详细模式，将清理后的行写入输出文件
        if (verbose_mode) {
            fprintf(output_file, "%s\n", line);
        }

        // 打印处理后的行（调试用,最后记得删）
        printf("Line %d: %s\n", line_number, line);
    }

    // 关闭文件
    fclose(file);
    if (verbose_mode) {
        fclose(output_file);
    }
}