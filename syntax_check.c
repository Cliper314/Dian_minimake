#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void syntax_check(const char *line, int line_number,int *in_rule2) {
     // 检查是否为目标行（包含冒号分隔符）
     char *colon_pos = strchr(line, ':');
     if (colon_pos != NULL) {
         *in_rule2 = 1;//标记已经进入规则
         return;
     }

    // 检查是否为空行
    else if (strlen(line) == 0) {
        return;
    }

    // 检查是否为命令行（以Tab开头）
    else if (line[0] == '\t') {
        if (!*in_rule2) {
            fprintf(stderr, "Line %d: Command found before rule\n", line_number);
        }//如果没有进入规则，报错
        return;
    }

   // 如果既不是命令行也不是目标行，则报错
   
    fprintf(stderr, "Line %d: Missing colon in taget definition\n", line_number);
    *in_rule2 = 0;//重置标记为没有进入规则
   
}
