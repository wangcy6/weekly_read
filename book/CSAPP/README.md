https://github.com/Talk-Go-CSAPP-05/Discusion

https://talkgo.org/t/topic/

https://github.com/mofaph/csapp

https://pccito.ugr.es/ec/practicas/2a/

![image.png](https://i.loli.net/2020/09/21/yzXcpZ4VYNOrjg8.png)



### 第三周

### 总结



### 记录

- ```shell
  gcc -Og -o prog main.c mstore.c
  objdump -d prog 
  objdump -d mstore.o
  如果既想显示源代码，又想显示汇编代码，可以使用“layout split”命令
  p $rbp
  ```

### 阅读资料

- https://xz.aliyun.com/t/2554
- https://www.youtube.com/playlist?list=PLmBgoRqEQCWy58EIwLSWwMPfkwLOLRM5R
- https://www.bilibili.com/video/BV1a54y1k7YE?from=search&seid=11557456987003497790

- https://imhuwq.com/2019/01/31/%E4%BB%8E%E6%B1%87%E7%BC%96%E7%9A%84%E8%A7%92%E5%BA%A6%E7%90%86%E8%A7%A3%E7%A8%8B%E5%BA%8F%EF%BC%88%E4%B8%80%EF%BC%89%E2%80%94%E2%80%94%20%E6%93%8D%E4%BD%9C%E6%95%B0%E6%8D%AE%E7%9A%84%E6%8C%87%E4%BB%A4%E6%B5%81/ 【10%】
- https://bbs.pediy.com/thread-257246.htm 【10%】

## 第二周打卡：



汇编指令回顾，下面都是具体例子，先了解，在验证（目前没有验证）

1. call c++ 普通函数调用 call 地址，虚函数 call ptr[i] 是个偏移量。可见代码编译时候不确定对应地址
2. lock volatile 解决缓存内存可可见性， 不解决
3. gcc golang 设置cflag开启内联，print 遍历查看 x 十六进制内容。 写demo打印函数堆栈调用和整数数值。
4. 二进制操作一定看懂 &  ^操作。




## 第一周打卡：

关于 一个程序是如何执行的，具体来说在单核下 执行2个字如何 理解的。

（1） shell 执行fork +exec命令运行一个程序。因此可见程序运行需要一个地址空间，包括只读段，堆栈这些虚拟空间. 这个时候经常进程创建成功。这只是静态部分，如果单任务情况下已经满足了。

（2） 进程执行具体是通过线程调用（默认一个线程）完成的。
场景：在执行过程需要IO操作 鼠标键盘,，网络 信号等任务时候。需要操作系统中断机制 完成协同工作。
例如。通过信号让一个阻塞在慢系统调用的线程从睡眠状态到运行状态。

（3）即使在单核情况下，除去中断外，系统调用也会引起cpu上下文切换。
vmstat 查看 in数量小于cs的印证了，上下文切换触发原因多种。

（4） 有什么办法减少上下文切换？
a ：无锁编程 ，一般锁会触发中断，这里说的锁也是高级抽象。
b： 协程：线程的上下文切换在内核自动完成的。这里用协程代替线程
c：原子操作 。
d：减少线程数量。

因此可见，一个程序运行，这里抽象为进程这个概念。这个概念隐含很多东西，不仅是独占那么简单。需要更加复杂机制。

所在小组
   第五组
组内昵称
     王传义
你的心得体会



# 03_Java高并发编程详解-多线程与架构设计



## 线程安全场景

- 读写锁