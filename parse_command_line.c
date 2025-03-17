#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "print_help.h"

#define MAX_LINE_LENGTH 1024

// 解析命令行参数
int parse_command_line(int argc, char *argv[], int *verbose_mode, char *target) {
    // 遍历命令行参数
    for (int i = 1; i < argc; i++) {
        // 如果参数是--help，打印帮助信息并返回0
        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }
        // 如果参数是-v或--verbose，启用详细模式
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            *verbose_mode = 1;
        }
        // 否则认为是目标参数
        else {
            // 如果目标参数已经存在，报错并返回-1
            if (*target != '\0') {
                fprintf(stderr, "Error: Multiple targets specified\n");
                return -1;
            }
            // 将目标参数保存到target变量中
            strcpy(target, argv[i]);
        }
    }
    // 如果没有错误，返回1
    return 1;
}