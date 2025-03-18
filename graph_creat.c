#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NODES 100 // 定义最大节点数量

// 定义节点结构体Node
typedef struct {
    char name[100]; // 节点名称
    int in_degree; // 入度
    char dependencies[10][100]; // 存储依赖数组
    int dep_count; // 依赖数量
} Node;

Node nodes[MAX_NODES];
int node_count = 0;

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
            for (int j = 0; j < node_count; j++) {
                if (strcmp(nodes[j].name, to) == 0) {
                    nodes[j].in_degree++;
                    strcpy(nodes[i].dependencies[nodes[i].dep_count], to);
                    nodes[i].dep_count++;
                    return;
                }
            }
        }
    }
}

// 拓扑排序
void topological_sort() {
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // 将入度为0的节点加入队列(入度为 0 的节点表示没有未完成的依赖，可以立即处理。)
    for (int i = 0; i < node_count; i++) {
        if (nodes[i].in_degree == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        printf("%s ", nodes[u].name);

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
}