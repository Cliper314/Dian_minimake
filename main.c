#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse_command_line.h"
#include "preprocess_makefile.h"

#define MAX_LINE_LENGTH 1024


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
    //预处理Makefile文件
    preprocess_makefile("./Makefile", verbose_mode);
}