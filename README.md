# 学习笔记
## 基础命令的学习
1.文件和目录操作
	
	查看当前目录内容：ls
		ls
		列出当前目录中的文件和目录。
		•   -l  ：以长格式显示文件和目录的详细信息。
		•   -a  ：显示所有文件，包括隐藏文件（以   .   开头的文件）。
	
	切换目录：cd
		cd <directory>
		切换到指定的目录。
		•   cd ..  ：切换到上一级目录。
		•   cd ~  ：切换到当前用户的主目录。
		•   cd -  ：切换到上一次所在的目录。
	
	创建目录：mkdir
		mkdir <directory>
		创建一个新的目录。
		•   -p  ：递归创建目录，即使父目录不存在也会自动创建。
			例如：mkdir -p new_directory/sub_directory
	
	创建文件：touch
		touch <file>
		创建一个空文件，如果文件已存在，则更新其访问和修改时间。
	
	删除文件：rm
		rm <file>
		删除指定的文件。
		•   -r  ：递归删除目录及其内容。
		•   -f  ：强制删除，不提示确认。
			例如：rm -rf new_directory
	
	删除目录：rmdir
		rmdir <directory>
		删除空目录
	
	查看文件内容：cat
		cat <file>
		输出文件内容到终端。
	
	查看文件内容（分页）：less
		less <file>
		分页显示文件内容，适合查看大文件。
	
	查看文件内容（头部或尾部）：head和tail
		head <file>
		tail <file>
		•   head  ：显示文件的前几行。
		•   tail  ：显示文件的后几行。
		-n  ：指定显示的行数。
			例如：head -n 5 file1.txt
	
2.系统信息和管理
```
	查看当前路径：  pwd 
		pwd
		显示当前工作目录的绝对路径。
	
	查看系统信息：  uname  
		uname
		显示系统信息。
		-a  ：显示所有系统信息。
			例如：uname -a
	
	查看进程信息：  ps  
		ps
		显示当前用户的进程信息。
		aux  ：显示所有用户的进程信息。
	
	查看文件系统信息：  lsblk  
		lsblk
		• 显示所有块设备的信息。
```
	
3.文本处理
```
	查找文件：  find
		find <directory> -name <pattern>
		在指定目录中查找符合特定模式的文件。
		•   -type  ：指定文件类型（如   f   表示文件，  d   表示目录）。
		•   -mtime  ：查找修改时间符合特定条件的文件。
	
	查找文本内容：  grep  
		grep <pattern> <file>
		在文件中查找符合特定模式的文本内容。
		•   -i  ：忽略大小写。
		•   -r  ：递归查找。
		•   -n  ：显示匹配行的行号。
	
	替换文本内容：  sed  
		sed 's/<old>/<new>/' <file>
		在文件中替换文本内容。
		-i  ：直接修改文件内容。不加的话不会修改文件中内容而只是打印出修改内容。
```
	


---
## git
	### 1.配置git
		git config --global user.name "Your Name"
		git config --global user.email "your_email@example.com"
	
	### 2.创建与克隆仓库
		创建仓库
			mkdir my_project
			cd my_project
			git init
		克隆仓库
			git clone https://github.com/user/repo.git
	
	### 3.基本操作
		1.添加文件到仓库
			echo "Hello, World!" > hello.txt
			git add hello.txt
			
			•   echo "Hello, World!" > hello.txt  ：创建一个名为   hello.txt   的文件，并写入内容。
			•   git add hello.txt  ：将   hello.txt   文件添加到暂存区。
		
		2.提交更改
			git commit -m "Add hello.txt file"
		
		3.查看状态
			git status
			显示当前仓库的状态，包括哪些文件被修改、哪些文件未被跟踪等。
		
		4.查看提交历史
			git log
			显示提交历史，包括提交的哈希值、作者、日期和提交信息。
		
		5.分支操作
			1.创建分支
				git branch feature-branch
				创建一个名为   feature-branch   的新分支。
			2.切换分支
				git checkout feature-branch
				切换到   feature-branch   分支。
			3.合并分支
				git checkout main
				切换回主分支。
				git merge feature-branch
				将   feature-branch   分支的更改合并到主分支。
		
		6.远程仓库操作
			1.添加远程仓库
				git remote add origin https://github.com/username/repository.git
				添加一个名为   origin   的远程仓库。
			2.推送更改到远程仓库
				git push -u origin main
				将本地的   main   分支推送到远程仓库   origin  ，并设置上游分支。
			3.拉取远程仓库的更改
				git pull origin main
				从远程仓库   origin   拉取   main   分支的更改，并合并到当前分支。
	


---

## make工具
	### 基础规则
		```
		app: main.c utils.c #目标:依赖
			gcc -o app main.c utils.c # Tab 命令
	
	### 语法
		```
		POHNY: all clean #伪目标
		@echo...#就不会打印这个命令
		$(CFLAGS) #可以直接指代CFLAGS所表示的所有变量 
		$< #代表目标文件的 第一个依赖项。
	
	### 使用make命令
		make -f custom_makefile
		使用   -f   选项指定
	

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
	
	### 4.字符串函数
		1.strcpy
			char *strcpy(char *dest, const char *src);
			
			它将一个字符串的内容复制到另一个字符串中，直到遇到源字符串的终止符   \0  
			
			参数说明
				•   dest  ：目标字符串的起始地址。这是拷贝的目标位置，必须有足够的空间来存储源字符串的内容。
				•   src  ：源字符串的起始地址。这是要拷贝的字符串，必须以终止符   \0   结尾。
			
			返回目标字符串的起始地址，即   dest   的值
		
		2.strcmp
			int strcmp(const char *str1, const char *str2);
			
			
			按照字典顺序比较两个以空字符（  \0  ）结尾的字节字符串，并返回一个整数值，表示两个字符串的大小关系
			
			返回一个整数值，表示两个字符串的比较结果：
				• 返回值 < 0：表示   str1   小于   str2  。
				• 返回值 == 0：表示   str1   等于   str2  。
				• 返回值 > 0：表示   str1   大于   str2  。
		
		3.strcspn
			size_t strcspn(const char *s1, const char *s2);
			
			计算一个字符串中不包含指定字符集合的第一个子串的长度。
			
			参数说明
				•   s1  ：要检查的源字符串。
				•   s2  ：包含要排除的字符的字符串。  s2   中的字符将被视为“排除字符集”。
			
			返回一个   size_t   （无符号整数类型）类型的值，表示从   s1   的开头开始，直到遇到   s2   中的任意一个字符为止的子串长度。
		
		4.strtok
			char *strtok(char *str, const char *delim);
			
			通过指定分隔符来分割字符串
			
			参数说明
				•   str  ：
					• 第一次调用时，  str   是要分割的原始字符串。
					• 从第二次调用开始，  str   应该是   NULL  ，表示继续分割上次调用后剩余的字符串。
				•   delim  ：包含分隔符的字符串。  delim   中的每个字符都被视为一个分隔符。
			
		 如果成功分割出一个子字符串，  strtok   返回指向该子字符串的指针。
		
		5.strchr
			char *strchr(const char *str, int c);
			
			在字符串中查找指定字符的第一次出现位置。
			
			参数说明
				•   str  ：要查找的目标字符串。
				•   c  ：要查找的字符。注意，这里的   c   是一个   int   类型，但实际上是一个字符值。在调用时，通常传递字符的 ASCII 值。
			
			如果找到指定字符   c  ，  strchr   返回指向该字符第一次出现位置的指针
	
	### 5.stderr,perror,fprintf
		1.stderr
		 是一个全局文件指针,stderr   是一个全局文件指针
		 类型：  FILE *  
		
		2.perror
			void perror(const char *s);
		 perror   会将字符串   s   输出到   stderr  ，后面跟着一个冒号和一个空格，然后是当前错误码（  errno  ）的描述信息。
		
		3.fprintf
			int fprintf(FILE *stream, const char *format, ...);
			参数：
				•   stream  ：目标文件流，可以是   stdout  、  stderr   或其他打开的文件流。
				•   format  ：格式化字符串，用于指定输出的格式。
				•   ...  ：可变参数列表，根据   format   中的格式说明符提供相应的值。
	
	### 6.Wrong1 全局变量定义
		必须定义在所有函数的外部
		全局变量可以在定义时初始化，也可以不初始化。如果未初始化，全局变量会被自动初始化为零（对于基本数据类型）或空指针（对于指针类型）。
		如果需要在多个文件中使用同一个全局变量，需要在定义文件中定义它，在其他文件中使用   extern   关键字声明它。
	
	### 7.const
	
	### 8.结构体
		一个文件中定义的结构体不需要在其他文件中再次定义。如果在一个文件（如  header.h  ）中定义了一个结构体，那么在其他文件中可以通过包含该头文件来使用这个结构体，而无需再次定义。
		
		结构体变量 访问方式：使用点运算符（  .  ）。
		指向结构体的指针 访问方式：使用箭头运算符（  ->  ）。

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
		
		创建一个与当前进程（父进程）几乎完全相同的子进程。子进程是父进程的副本，子进程和父进程是两个独立的进程
		
		返回值：
			• 在子进程中返回 0。
			• 在父进程中返回子进程的 PID。
			• 如果创建子进程失败，则返回 -1，并设置相应的错误码（  errno  ）。

	### 3.execvp()
		int execvp(const char *file, char *const argv[]);
		
		在当前进程中加载并执行一个新的程序。
		
		参数说明
			•   file  ：指定要执行的程序的文件名。 ，因此不需要提供完整的路径。
			•   argv  ：是一个字符串数组，用于传递命令行参数给新程序。第一个参数通常是程序的名称（类似于命令行中的程序名），后续参数是传递给程序的参数列表。最后一个参数必须是   NULL  ，表示参数列表的结束。
		
		返回值
			• 如果   execvp()   成功执行，当前进程会被新程序替换，  execvp()   不会返回。
			• 如果   execvp()   执行失败，它会返回   -1  ，并设置相应的错误码（  errno  ）。

	### 4.waitpid()
		pid_t waitpid(pid_t pid, int *status, int options);
		
		用于等待一个子进程结束并获取其状态信息。
		
		参数说明
			•   pid  ：指定要等待的子进程的 PID。根据   pid   的值，  waitpid()   的行为会有所不同：
				•   > 0  ：等待指定 PID 的子进程。
				•   == 0  ：等待与调用进程在同一进程组中的任意子进程。
				•   < -1  ：等待进程组 ID 等于   pid   的绝对值的任意子进程。
				•   == -1  ：等待任意子进程（与   wait()   的行为类似）。
			
			•   status  ：一个指向   int   类型的指针，用于存储子进程的退出状态信息。如果不需要获取状态信息，可以将其设置为   NULL  。
			
			•   options  ：用于控制   waitpid()   的行为，可以是以下值的组合（通过位或操作）：
				•   WNOHANG  ：非阻塞模式。如果指定的子进程尚未结束，则   waitpid()   立即返回，不会阻塞调用进程。
				•   WUNTRACED  ：如果子进程被信号暂停（如收到   SIGTSTP  ），则返回子进程的状态信息。
				•   WCONTINUED  （仅在某些系统中支持）：如果子进程从暂停状态恢复运行，则返回子进程的状态信息。
		
		返回值
			 • 如果成功等待到子进程结束，  waitpid()   返回子进程的 PID。
			 • 如果没有找到匹配的子进程，返回 0。
			 • 如果发生错误，返回   -1  ，并设置相应的错误码（  errno  ）。

	### 5.WIFEXITED和WEXITSTATUS
		它们通常在父进程调用 wait() 或 waitpid() 获取子进程的退出状态后使用
		status 是 wait() 或 waitpid() 返回的状态值。
		1.WIFEXITED(status)
			这个宏用于检查子进程是否正常退出（即子进程调用了 exit() 函数或返回到主函数结束）。
			如果子进程正常退出，返回非零值；否则返回0。
		2.WEXITSTATUS(status)
			这个宏用于获取子进程的退出状态码。只有在 WIFEXITED(status) 返回真时，才能使用这个宏。
			返回子进程的退出状态码。这个状态码是由子进程传递给 exit() 函数的值，或者子进程主函数的返回值。

	### 6.Unix进程模型
		1.进程的基本概念
			程序在执行过程中的一个实例
		
		2.进程的创建：  fork() 
		
		3.进程的执行：  exec   系列函数
		
		4.进程的终止：  exit()   和   _exit() 
			void exit(int status);
			void _exit(int status);
		
		5.等待子进程结束：  wait()   和   waitpid()  
			pid_t wait(int *status);
			pid_t waitpid(pid_t pid, int *status, int options);
			
			区别：参数   pid   可以指定等待的子进程，  options   可以设置等待选项（如非阻塞模式）
		
		6.进程间通信（IPC）
			 Unix 系统中多个进程之间交换数据或同步运行状态的机制
		
		7，僵尸进程
			当一个子进程结束时，它的父进程可能还没有读取子进程的状态信息。此时，子进程的进程表项不会被释放，这个子进程就变成了僵尸进程（Zombie Process）。僵尸进程无法被操作系统回收，会占用系统资源。
			为了避免僵尸进程，父进程应该在子进程结束时及时调用   wait()   或   waitpid()   获取子进程的状态信息。
	