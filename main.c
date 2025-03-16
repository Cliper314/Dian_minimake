#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 打印帮助信息
void print_help() {
    printf("Usage: minimake [options] [target]\n");
    printf("Options:\n");
    printf("  --help     Display this help message\n");
    printf("  -v, --verbose  Enable verbose mode\n");
}

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

int main(int argc, char *argv[]) {
    int verbose_mode = 0; // 是否启用详细模式
    char target[256] = ""; // 目标参数

    // 解析命令行参数
    int result = parse_command_line(argc, argv, &verbose_mode, target);

    // 根据解析结果处理
    if (result == 0) {
        // 如果返回0，说明打印了帮助信息，程序正常退出
        return 0;
    } else if (result == -1) {
        // 如果返回-1，说明参数解析有误，程序退出并返回错误码
        return 1;
    } else {
        // 如果返回1，说明参数解析正常完成
        // 在这里可以继续处理其他任务，如读取Makefile等
        printf("Verbose mode: %d\n", verbose_mode);
        printf("Target: %s\n", target);
        return 0;
    }
}