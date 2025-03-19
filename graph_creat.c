#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

// 添加目标和依赖文件名到节点
void add_targets_and_dependencies() {
    for (int i = 0; i < rule_count; i++) {
        // 检查目标是否已经存在，不存在则添加
        for (int j = 0; j < node_count; j++) {
            if (strcmp(nodes[j].name, rules[i].target) == 0) {
                break;
            }
            //如果没有找到目标节点，则添加
            if (j == node_count - 1) {
                add_node(rules[i].target);
            }
        }
        add_node(rules[i].target);
        for (int j = 0; j < rules[i].dependency_count; j++) {
            add_dependency(rules[i].target, rules[i].dependencies[j]);
           
            // 检查依赖是否已经存在，不存在则添加
            for(int k=0;k<node_count;k++){
                if(strcmp(nodes[k].name,rules[i].dependencies[j])==0){
                    break;
                }
                ////如果没有找到目标节点，则添加
                if(k==node_count-1){
                    add_node(rules[i].dependencies[j]);
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