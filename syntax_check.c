#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void syntax_check(const char *line, int line_number) {
    // 检查是否为空行
    if (strlen(line) == 0) {
        return;
    }

    // 检查是否为命令行（以Tab开头）
    if (line[0] == '\t') {
        return;
    }

    // 检查是否为目标行（包含冒号分隔符）
    char *colon_pos = strchr(line, ':');
    if (colon_pos != NULL) {
        return;
    }

    // 如果既不是命令行也不是目标行，则报错
    fprintf(stderr, "Line %d: Missing colon in taget definition\n", line_number);
}
