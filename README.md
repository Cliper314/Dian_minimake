# 学习笔记
## 基础命令的学习
	```
	code . #打开VS code
	
	gcc main.c -o hello #用main生成名叫hello的可执行文件
		编译后是否需要再次执行该命令？
		需要
	
	./hello #执行hello文件
	
	rm -f hello  #删除hello文件
		ps:加上.\表示执行当前目录
	
	cd minimake  #定位到minimake目录

---
## git
	### 1.配置git
		`git config --global user.name "Your Name"
		git config --global user.email "your_email@example.com"
	
	### 2.创建与克隆仓库
		创建仓库
			mkdir my_project
			cd my_project
			git init
		克隆仓库
			git clone https://github.com/user/repo.git
	
	### 3.基本操作


`

## make工具
	### 基础规则
		```
		app: main.c utils.c #目标:依赖
			gcc -o app main.c utils.c # tab 命令
	```
	### 语法
		```
		POHNY: all clean #声明
		@echo...#就不会打印这个命令
		$(CFLAGS) #可以直接指代CFLAGS所表示的所有变量 
		$< #代表目标文件的 第一个依赖项。
	```

---
## 阶段1 阶段2
	### 1.argc与argv（不需要定义）
	
		argc表示命令行参数的数量（包括程序名称本身），是int类型
		
		argv表示参数的内容，是一个**字符串数组**
	
	### 2.-v的实现
	
	### 3.fopen()与fgets()
	
		FILE *fopen(const char *filename, const char *mode)
		打开一个文件，并返回一个指向该文件的文件指针
		！！！注意如果用"w"该文件存在，则清空，不存在则创建
		
		char *fgets(char *str, int n, FILE *stream)
		从文件中读取一行内容，并将其存储到指定的缓冲区中。它会读取直到换行符或缓冲区满(即读取数量不能超过n)为止。返回str，即读取的内容
	
	### 5.stderr,perror,fprintf…
	
	### 6.Wrong1 全局变量定义
		必须定义在所有函数的外部
		全局变量可以在定义时初始化，也可以不初始化。如果未初始化，全局变量会被自动初始化为零（对于基本数据类型）或空指针（对于指针类型）。
		如果需要在多个文件中使用同一个全局变量，需要在定义文件中定义它，在其他文件中使用   extern   关键字声明它。
	
	### 7.const
	
	### 8.结构体
		一个文件中定义的结构体不需要在其他文件中再次定义。如果在一个文件（如  header.h  ）中定义了一个结构体，那么在其他文件中可以通过包含该头文件来使用这个结构体，而无需再次定义。

---

## 阶段3
	### 1.结点
		参考数据结构
	
	### 2.Kahn算法
		1. 找出所有入度为 0 的节点，这些节点没有依赖，可以作为拓扑排序的起点。
		2. 从图中移除这些节点，并更新它们的邻接节点的入度。
		3. 重复上述过程，直到所有节点都被处理完毕。

	### 3#include <sys/stat.h>与#include <time.h>
		1.stat()
			int stat(const char *pathname, struct stat *buf);
			pathname 指向文件路径的字符串，表示要获取状态信息的文件或目录的路径
		2.struct stat
		    dev_t     st_dev;     // 文件的设备ID
			ino_t     st_ino;     // 文件的inode号
		    mode_t    st_mode;    // 文件的类型和权限
		    nlink_t   st_nlink;   // 硬链接数
		    uid_t     st_uid;     // 文件所有者的用户ID
		    gid_t     st_gid;     // 文件所有者的组ID
		    dev_t     st_rdev;    // 设备类型（如果是特殊文件）
		    off_t     st_size;    // 文件大小（以字节为单位）
		    blksize_t st_blksize; // 文件系统I/O的块大小
		    blkcnt_t  st_blocks;  // 分配的块数
		    time_t    st_atime;   // 最后访问时间
		    time_t    st_mtime;   // 最后修改时间
		    time_t    st_ctime;   // 最后状态改变时间
		3.time_t
			通常用于存储从某个特定时刻（通常是1970年1月1日00:00:00 UTC，即“Unix时间戳”）开始的秒数。  time_t   类型的变量可以用于表示时间点，方便进行时间计算和转换。
			
			 time_t   是一个算术类型，通常是一个长整型（  long   或   long long  ）
			 
			 可以使用   time()   函数获取当前时间，并将其存储为   time_t   类型：time_t now = time(NULL);  // 获取当前时间
---
## 阶段4
	### 1.system()
		int system(const char *command);
		用于在程序中执行系统命令,允许通过C程序调用操作系统的shell来执行外部命令，就像在命令行中直接输入命令一样。

	### 2.fork()
		pid_t fork(void);
		
