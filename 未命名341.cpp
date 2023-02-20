#define _GNU_SOURCE   
#include "sched.h"
#include<sys/types.h>
#include<sys/syscall.h>
#include<unistd.h>
#include <pthread.h>
#include "stdio.h"
#include "stdlib.h"
#include "semaphore.h"
#include "sys/wait.h"
#include "string.h"
int producer(void * args);
int consumer(void *args);
pthread_mutex_t mutex;//临界区变量 
sem_t product;// 信号量 ，生产者生产产品的数量 
sem_t warehouse;// 信号量，还可以生产的数量 
char buffer[8][4];//产品 
int bp=0;//栈顶指针 
int main(int argc,char** argv)
{
  pthread_mutex_init(&mutex,NULL);//初始化 
   sem_init(&product,0,0);//生产者生产量为零 
    sem_init(&warehouse,0,8);//还可生产8 
   int clone_flag,arg,retval;
    char *stack;//定义一个栈 
   clone_flag=CLONE_VM|CLONE_SIGHAND|CLONE_FS|   CLONE_FILES;//flag参数各位掩码的组合 
    //共享父进程的虚拟内存 //共享对信号的处置设置//共享与文件系统相关的信息// 共享文件描述符
    int i;
     for(i=0;i<2;i++)
     {  //创建四个线程
        arg = i;
        stack =(char*)malloc(4096); //申请栈空间 
        retval=clone((void*)producer,&(stack[4095]),clone_flag,(void*)&arg);//创建生产者进程 
      stack =(char*)malloc(4096); //申请栈空间 
        retval=clone((void*)consumer,&(stack[4095]),clone_flag,(void*)&arg);//创建消费者进程 
   
usleep(1);//更精准 
 }  
    exit(1);
}
int producer(void* args)
{
    int id = *((int*)args);//当前的id号 
    int i;
    for(i=0;i<10;i++)
    {
            sleep(i+1);  //表现线程速度差别
        sem_wait(&warehouse);// (等待信号量非零时）信号量减一 
        pthread_mutex_lock(&mutex);// 互斥锁上锁 
        if(id==0)
            strcpy(buffer[bp],"aaa\0");
        else
            strcpy(buffer[bp],"bbb\0");
        bp++;
        printf("producer%d produce %s in %d\n",id,buffer[bp-1],bp-1);
        pthread_mutex_unlock(&mutex);//互斥锁解锁 
        sem_post(&product);//给信号量加一 
    }
    printf("producer%d is over!\n",id);
}
int consumer(void *args)
{
    int id = *((int*)args);//当前的id号 
    int i;
    for(i=0;i<10;i++)
    {
        sleep(10-i);  //表现线程速度差别
        sem_wait(&product);// (等待信号量非零时）信号量减一
        pthread_mutex_lock(&mutex);// 互斥锁上锁 
        bp--;
        printf("consumer%d get %s in%d\n",id,buffer[bp],bp);
        strcpy(buffer[bp],"zzz\0");
        pthread_mutex_unlock(&mutex);//互斥锁解锁 
        sem_post(&warehouse);//给信号量加一 
    }
    printf("consumer%d is over!\n",id);
}

