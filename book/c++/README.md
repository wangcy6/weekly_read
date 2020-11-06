


# c++ model
- c++不能保证类型downcast？如何兼容c语言？

- 默认copy构造操作是否最够有效？ 在虚继承上表现不好，其他都ok
This cast is done at compile time. It will only perform the cast if the types are related. If the types are not related, you will get a compiler error

10.125.168.112  ---  124.250.73.72
10.125.168.66   ---  124.250.73.84
10.125.168.68   ---  124.250.73.85
ifdown eth1
ifdown em3 


in 每秒CPU的中断次数，包括时间中断

cs 每秒上下文切换次数，例如我们调用系统函数，就要进行上下文切换，线程的切换，也要进程上下文切换，这个值要越小越好，太大了，
要考虑调低线程或者进程的数目,例如在apache和nginx这种web服务器中，我们一般做性能测试时会进行几千并发甚至几万并发的测试，选择web服务器的进程可以由进程或者线程的峰值一直下调，压测，直到cs到一个比较小的值，这个进程和线程数就是比较合适的值了。系统调用也是，每次调用系统函数，我们的代码就会进入内核空间，导致上下文切换，
这个是很耗资源，也要尽量避免频繁调用系统函数。
上下文切换次数过多表示你的CPU大部分浪费在上下文切换，导致CPU干正经事的时间少了
，CPU没有充分利用，是不可取的。