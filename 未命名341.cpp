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
pthread_mutex_t mutex;//�ٽ������� 
sem_t product;// �ź��� ��������������Ʒ������ 
sem_t warehouse;// �ź��������������������� 
char buffer[8][4];//��Ʒ 
int bp=0;//ջ��ָ�� 
int main(int argc,char** argv)
{
  pthread_mutex_init(&mutex,NULL);//��ʼ�� 
   sem_init(&product,0,0);//������������Ϊ�� 
    sem_init(&warehouse,0,8);//��������8 
   int clone_flag,arg,retval;
    char *stack;//����һ��ջ 
   clone_flag=CLONE_VM|CLONE_SIGHAND|CLONE_FS|   CLONE_FILES;//flag������λ�������� 
    //�������̵������ڴ� //������źŵĴ�������//�������ļ�ϵͳ��ص���Ϣ// �����ļ�������
    int i;
     for(i=0;i<2;i++)
     {  //�����ĸ��߳�
        arg = i;
        stack =(char*)malloc(4096); //����ջ�ռ� 
        retval=clone((void*)producer,&(stack[4095]),clone_flag,(void*)&arg);//���������߽��� 
      stack =(char*)malloc(4096); //����ջ�ռ� 
        retval=clone((void*)consumer,&(stack[4095]),clone_flag,(void*)&arg);//���������߽��� 
   
usleep(1);//����׼ 
 }  
    exit(1);
}
int producer(void* args)
{
    int id = *((int*)args);//��ǰ��id�� 
    int i;
    for(i=0;i<10;i++)
    {
            sleep(i+1);  //�����߳��ٶȲ��
        sem_wait(&warehouse);// (�ȴ��ź�������ʱ���ź�����һ 
        pthread_mutex_lock(&mutex);// ���������� 
        if(id==0)
            strcpy(buffer[bp],"aaa\0");
        else
            strcpy(buffer[bp],"bbb\0");
        bp++;
        printf("producer%d produce %s in %d\n",id,buffer[bp-1],bp-1);
        pthread_mutex_unlock(&mutex);//���������� 
        sem_post(&product);//���ź�����һ 
    }
    printf("producer%d is over!\n",id);
}
int consumer(void *args)
{
    int id = *((int*)args);//��ǰ��id�� 
    int i;
    for(i=0;i<10;i++)
    {
        sleep(10-i);  //�����߳��ٶȲ��
        sem_wait(&product);// (�ȴ��ź�������ʱ���ź�����һ
        pthread_mutex_lock(&mutex);// ���������� 
        bp--;
        printf("consumer%d get %s in%d\n",id,buffer[bp],bp);
        strcpy(buffer[bp],"zzz\0");
        pthread_mutex_unlock(&mutex);//���������� 
        sem_post(&warehouse);//���ź�����һ 
    }
    printf("consumer%d is over!\n",id);
}

