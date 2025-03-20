#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"




Rule rules[MAX_TARGETS]; // 存储规则数组
    int rule_count = 0; // 规则数量
    char current_target[MAX_LINE_LENGTH]; // 存储当前目标名称
    char line[MAX_LINE_LENGTH]; // 用于存储每行的内容
    int line_number = 0; // 记录行号
   
    Node nodes[MAX_NODES];
    int node_count = 0;


int main(int argc, char *argv[]) {
    int verbose_mode = 0; // 是否启用详细模式
    char target[256] = ""; // 目标参数
    

    // 解析命令行参数
    int result = parse_command_line(argc, argv, &verbose_mode, target);

    // 根据解析结果处理
    if (result == 0) {
        // 如果返回0，说明打印了帮助信息，程序正常退出
        return 0;
    } else if (result == -1||result==-2) {
        // 如果返回-1或者-2，说明参数解析有误，程序退出并返回错误码
        return 1;
    } else {
        // 如果返回1，说明参数解析正常完成
        // 在这里可以继续处理其他任务，如读取Makefile等
        printf("Verbose mode: %d\n", verbose_mode);
        printf("Target: %s\n", target);

    }
    //预处理并解析Makefile文件
    preprocess_and_parse_makefile("./Makefile", verbose_mode);

    // 遍历所有解析的规则
    for (int i = 0; i < rule_count; i++) {
        printf("Target: %s\n", rules[i].target);
        printf("Dependencies:\n");
        for (int j = 0; j < rules[i].dependency_count; j++) {
            printf("  %s\n", rules[i].dependencies[j]);
        }
        printf("Commands:\n");
        for (int j = 0; j < rules[i].command_count; j++) {
            printf("  %s\n", rules[i].commands[j]);
        }
    }


    // 添加节点和依赖关系
    add_targets_and_dependencies();

    // 打印依赖图
    printf("依赖图:\n");
    print_dependency_graph();

    // 拓扑排序
    printf("拓扑排序:\n ");
    topological_sort();
    
    //时间戳检查
    printf("\n时间戳检查:\n ");
    const char *dependencies[MAX_NODES];
    int dep_count = 0;
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].name, target) == 0) {
            for (int j = 0; j < nodes[i].dep_count; j++) {
                dependencies[dep_count++] = nodes[i].dependencies[j];
            }
            break;
        }
    }

    if (need_rebuild(target, dependencies, dep_count)) {
        printf("Need to rebuild %s\n", target);
    }
    return 0;
}