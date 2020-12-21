#define _GNU_SOURCE
#include <linux/futex.h>    //for FUTEX_WAIT FUTEX_WAKE
#include <sys/time.h>       //for struct timespec
#include <sys/syscall.h>    //for SYS_futex
#include <unistd.h>         //for syscall
#include <sys/mman.h>       //for mmap
#include <stdint.h>         //for uint32_t
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define error_handle(msg) do{perror(msg); exit(EXIT_FAILURE);} while(0)

int futex(int* uaddr, int futex_op, int val, const struct timespec *timeout,
            int *uaddr2, int val3) 
{
    return syscall(SYS_futex, uaddr, futex_op, val, timeout, uaddr2, val3);
}

void futex_wait(int *futexp)
{
    while(1) {
        //通过一个循环来避免多个线程占用同一个futex的情况
        if(__sync_bool_compare_and_swap(futexp, 1, 0)){
            break;
        }

        int s = futex(futexp, FUTEX_WAIT, 0, NULL, NULL, 0);
        //判断被唤醒后,再占有futex，此时futexp是否会被futex改为0
        printf("futexp = %d\n", *futexp);
        if(s == -1) {
            error_handle("futex: ");
        } 
    }
}

void futex_post(int* futexp) 
{
    if(__sync_bool_compare_and_swap(futexp, 0, 1)) {
        //这里有一个情况是，将futex值加1后，还没进行下一步唤醒，有新线程过来
        //则新线程会获得futex的所有权
        int s = futex(futexp, FUTEX_WAKE, 1, NULL , NULL, 0);
        if(s == -1) {
            error_handle("futex FUTEX_WAKE:");
        }
    }
}

int main(int argc, char *argv[])
{
    int *futexes = (int *)mmap(NULL, sizeof(uint32_t) * 2, PROT_READ | PROT_WRITE,
            MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if(futexes == MAP_FAILED) {
        error_handle("mmap:");
    }
    int *futex1 = &futexes[0];
    int *futex2 = &futexes[1];
    *futex1 = 1;    //child 先走
    *futex2 = 0;    //parent 默认阻塞
    int rt = fork();
    if(rt == -1) {
        error_handle("fork");
    }

    if(rt == 0) {   //child
        for(int i = 0; i < 3; ++i) {
            futex_wait(futex1);
            printf("child %d\n", i);
            futex_post(futex2);
        }
    } else {
        for(int i = 0; i < 3; ++i) {
            futex_wait(futex2);
            printf("parent %d\n", i);
            futex_post(futex1);
        }
    }
    return 0;
}