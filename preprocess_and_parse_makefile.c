#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "syntax_check.h"

#define MAX_LINE_LENGTH 1024 // 定义每行的最大长度
#define MAX_TARGETS 100 // 定义最大规则数量
#define MAX_DEPENDENCIES 100 // 定义最大依赖数量
#define MAX_COMMANDS 100 // 定义最大命令数量

// 定义规则结构体Rule
typedef struct {
    char target[MAX_LINE_LENGTH]; // 目标名称
    char dependencies[MAX_DEPENDENCIES][MAX_LINE_LENGTH]; // 存储依赖数组
    int dependency_count; // 依赖数量
    char commands[MAX_COMMANDS][MAX_LINE_LENGTH]; // 存储命令数组
    int command_count; // 命令数量
} Rule;

// 定义规则数组
Rule rules[MAX_TARGETS]; // 存储规则数组
int rule_count = 0; // 规则数量
char current_target[MAX_LINE_LENGTH]; // 存储当前目标名称
char line[MAX_LINE_LENGTH]; // 用于存储每行的内容
int line_number = 0; // 记录行号
int in_rule = 0; // 标记是否在规则定义中




// 预处理Makefile文件
void preprocess_and_parse_makefile(const char *filename, int verbose_mode) {
    
    FILE *file = fopen(filename, "r"); // 打开Makefile文件
    if (file == NULL) {
        perror("Error opening Makefile");
        return;
    }

    
    // 打开文件以写入清理后的内容（如果启用详细模式）
    FILE *output_file = NULL; // 输出文件指针
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
        syntax_check(line,line_number,&in_rule);
        
        // 处理规则定义
        if (in_rule) {

            // 检查当前行是否是命令行（以制表符 '\t' 开头）
            if (line[0] == '\t') {
                char command[MAX_LINE_LENGTH];
                strcpy(command, line + 1);
                if (rules[rule_count - 1].command_count < MAX_COMMANDS) {
                    strcpy(rules[rule_count - 1].commands[rules[rule_count - 1].command_count], command);
                    rules[rule_count - 1].command_count++;
                }
            } else {
                // 如果当前行不是命令行，将 in_rule 设为 0
                in_rule = 0;
            }
        } else {
            // 检查当前行是否是规则定义行（以冒号 ':' 结尾）
            char *colon_pos = strchr(line, ':');
            if (colon_pos != NULL) {
                *colon_pos = '\0';
                strcpy(current_target, line);

                // 检查是否有重复的目标定义
                for (int i = 0; i < rule_count; i++) {
                    if (strcmp(rules[i].target, current_target) == 0) {
                        fprintf(stderr, "Line %d: Duplicate target definition '%s'\n", line_number, current_target);
                    }
                }

                // 将当前目标复制到新的规则结构中
                strcpy(rules[rule_count].target, current_target);
                rules[rule_count].dependency_count = 0;
                rules[rule_count].command_count = 0;

                 // 使用 strtok 函数提取目标行中的依赖项
                char *token = strtok(colon_pos + 1, " ");
                while (token != NULL) {
                    if (rules[rule_count].dependency_count < MAX_DEPENDENCIES) {
                        strcpy(rules[rule_count].dependencies[rules[rule_count].dependency_count], token);
                        rules[rule_count].dependency_count++;
                    }
                    token = strtok(NULL, " \t");

                rule_count++;
                in_rule = 1;
            }
        }


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