#define MAX_LINE_LENGTH 1024 // 定义每行的最大长度
#define MAX_TARGETS 100 // 定义最大规则数量
#define MAX_DEPENDENCIES 100 // 定义最大依赖数量
#define MAX_COMMANDS 100 // 定义最大命令数量
#define MAX_NODES 100 // 定义最大节点数量

int parse_command_line(int argc, char *argv[], int *verbose_mode, char *target);
void preprocess_and_parse_makefile(const char *filename, int verbose_mode);
void print_help();
void syntax_check(const char *line, int line_number,int *in_rule);
void add_node(const char *name);
void add_node2(const char *name);
void add_dependency(const char *from, const char *to);
void add_targets_and_dependencies();
void topological_sort();
void print_dependency_graph();
time_t get_file_mtime(const char *filename);
int need_rebuild(const char *target, const char *dependencies[], int dep_count);




typedef struct {
    char target[MAX_LINE_LENGTH]; // 目标名称
    char dependencies[MAX_DEPENDENCIES][MAX_LINE_LENGTH]; // 存储依赖数组
    int dependency_count; // 依赖数量
    char commands[MAX_COMMANDS][MAX_LINE_LENGTH]; // 存储命令数组
    int command_count; // 命令数量
} Rule;

// 定义节点结构体Node
typedef struct {
    char name[100]; // 节点名称
    int in_degree; // 入度
    char dependencies[10][100]; // 存储依赖数组
    int dep_count; // 依赖数量
} Node;
