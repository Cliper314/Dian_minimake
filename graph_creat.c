#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include "head.h"


extern Rule rules[MAX_TARGETS]; // 存储规则数组
extern int rule_count; // 规则数量


extern Node nodes[MAX_NODES];
extern int node_count;

// 添加节点
void add_node(const char *name) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].name, name) == 0) {
            return;
        }
    }
    strcpy(nodes[node_count].name, name);
    nodes[node_count].in_degree = 0;
    nodes[node_count].dep_count = 0;
    node_count++;
}


// 添加依赖关系
void add_dependency(const char *from, const char *to) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].name, from) == 0) {
            strcpy(nodes[i].dependencies[nodes[i].dep_count], to);
            nodes[i].dep_count++;
            for (int j = 0; j < node_count; j++) {
                if (strcmp(nodes[j].name, to) == 0) {
                    nodes[j].in_degree++;
                    return;
                }
            }
        }
    }
}

// 添加目标和依赖文件名到节点
void add_targets_and_dependencies() {
    for (int i = 0; i < rule_count; i++) {
        // 检查目标是否已经存在，不存在则添加
        int target_exists = 0;
        for (int j = 0; j < node_count; j++) {
            if (strcmp(nodes[j].name, rules[i].target) == 0) {
                target_exists = 1;
                break;
            }
        }
        if (!target_exists) {
            add_node(rules[i].target);
        }

        for (int j = 0; j < rules[i].dependency_count; j++) {
            add_dependency(rules[i].target, rules[i].dependencies[j]);

            // 检查依赖是否已经存在，不存在则添加
            int dep_exists = 0;
            for (int k = 0; k < node_count; k++) {
                if (strcmp(nodes[k].name, rules[i].dependencies[j]) == 0) {
                    dep_exists = 1;
                    break;
                }
            }
            if (!dep_exists) {
                add_node(rules[i].dependencies[j]);
            }
        }
    }
}

// 拓扑排序
void topological_sort() {
    int queue[MAX_NODES];
    int stack[MAX_NODES];
    int front = 0, rear = 0, top = -1;

    // 将入度为0的节点加入队列(入度为 0 的节点表示没有未完成的依赖，可以立即处理。)
    for (int i = 0; i < node_count; i++) {
        if (nodes[i].in_degree == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        stack[++top] = u; // 将节点添加到栈中
        for (int i = 0; i < nodes[u].dep_count; i++) {
            for (int j = 0; j < node_count; j++) {
                if (strcmp(nodes[j].name, nodes[u].dependencies[i]) == 0) {
                    nodes[j].in_degree--;
                    if (nodes[j].in_degree == 0) {
                        queue[rear++] = j;
                    }
                    break;
                }
            }
        }
    }

    // 从栈中弹出节点进行输出，确保先输出依赖项后输出目标项
    while (top >= 0) {
        int u = stack[top--];
        printf("%s ", nodes[u].name);
    }
}

// 打印依赖图
void print_dependency_graph() {
    for (int i = 0; i < node_count; i++) {
        printf("%s:", nodes[i].name);
        for (int j = 0; j < nodes[i].dep_count; j++) {
            printf(" %s", nodes[i].dependencies[j]);
        }
        printf("\n");
    }
}

// 获取文件的修改时间
time_t get_file_mtime(const char *filename) {
    struct stat buffer;
    if (stat(filename, &buffer) == 0) {
        return buffer.st_mtime;
    }
    return -1;
}

// 判断是否需要重新构建返回1则需要
int need_rebuild(const char *target, const char *dependencies[], int dep_count) {
    if (get_file_mtime(target) == -1) {
        printf("Target file %s does not exist.\n", target);
        return 1;
    }

    time_t target_mtime = get_file_mtime(target);
    //printf("Target file %s modification time: %ld\n", target, target_mtime);

    for (int i = 0; i < dep_count; i++) {
        const char *dep = dependencies[i];
        time_t dep_mtime = get_file_mtime(dep);

        if (dep_mtime == -1) {
            printf("Dependency file %s does not exist.\n", dep);
            return 1;
        }

        //printf("Dependency file %s modification time: %ld\n", dep, dep_mtime);

        if (dep_mtime > target_mtime) {
            printf("Dependency file %s is newer than target file %s.\n", dep, target);
            return 1;
        }
    }

    return 0;
}