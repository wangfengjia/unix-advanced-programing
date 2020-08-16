# unix环境高级编程索引目录
### 第一章-UNIX基础知识
1. unix体系结构
2. 登录
3. 文件和目录
4. 输入和输出
5. 程序和进程
6. 出错处理
7. 用户标识
8. 信号
9. 时间值
10. 系统调用和库函数

### 第二章-UNIX标准及实现
1. UNIX标准化
2. UNIX系统实现
3. 标准和实现的关系
4. 限制
5. 选项
6. 功能测试宏
7. 基本系统数据类型
8. 标准之间的冲突

###第三章-文件I/O
1. 文件描述符
2. 函数open和openat
3. 函数create
4. 函数close
5. 函数lseek
6. 函数read
7. 函数write
8. I/O的效率
9. 文件共享
10. 原子操作
11. 函数dup和dup2
12. 函数sync,fsync和fdatasync
13. 函数fcntl
14. 函数ioctl
15. /dev/fd

### 第四章-文件和目录
1. 函数stat,fstat,fstatat和lstat
2. 文件类型
3. 设置用户ID和设置组ID
4. 文件访问权限
5. 新文件和目录的所有权
6. 函数access和faccessat
7. 函数unmask
8. 函数chmod,fchmod和fchmodat
9. 粘着位
10. 函数chown,fchown,fchownat和lchown
11. 文件长度
12. 文件截断
13. 文件系统
14. 函数link,linkat,unlink,unlinkat和remove
15. 函数rename和renameat
16. 符号链接
17. 创建和读取读好链接
18. 文件的时间
19. 函数futimens,utimensat和utimes(更改文件数据的最后访问和最后修改时间)
20. 函数mkdir,mkdirat和rmdir
21. 读目录
22. 函数chdir,fchdir和getcwd(更改进程的当前工作目录)
23. 设备特殊文件
24. 文件访问权限位

###第五章-标准I/O库(由ISO C标准说明)
1. 流和FILE对象
2. 标准输入,标准输出,标准错误
3. 缓冲
4. 打开流
5. 读和写流
6. 每次一行I/O
7. 标准I/O的效率
8. 二进制I/O
9. 定位流
10. 格式化I/O
11. 实现细节
12. 临时文件
13. 内存流
14. 标准I/O的替代软件

###第六章-系统数据文件和信息
1. 口令文件
2. 阴影口令
3. 组文件
4. 附属组ID
5. 实现区别
6. 其他的数据文件
7. 登录账户记录
8. 系统标识
9. 时间和日期例程

###第七章-进程环境
1. main函数
2. 进程终止
3. 命令行参数
4. 环境表
5. C程序的存储空间布局
6. 共享库
7. 存储空间(堆上的)分配
8. 环境变量
9. 函数setjmp和longjmp
10. 函数getrlimit和setrlimit

##第八章-进程控制