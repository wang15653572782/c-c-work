#include "math.h"
#include "sched.h"
#include "pthread.h"
#include "stdlib.h"
#include "semaphore.h" 
#include "stdio.h"
#include <unistd.h>
typedef struct{  //实时任务描述
    char task_id;//任务名 
    int call_num;  //任务发生次数
    int ci;  // Ci处理时间 
    int ti;  //Ti 发生周期 
    int ci_left;//剩余的 
    int ti_left; 
    int flag;  //任务是否活跃，0否，2是
    int arg;  //参数
    pthread_t th;  //任务对应线程
}task;
void proc(int* args);
void* idle();
int select_proc();//用于实现调度算法,被选中任务执行proc()，在没有可执行任务时执行idle()
int task_num = 0;
int idle_num = 0;
int alg;  //所选算法，1 是 EDF，2 是 RMS
int curr_proc=-1;//当前任务参数 
int demo_time = 100;  //演示时间
task* tasks;
pthread_mutex_t proc_wait[100];//临界区变量来实现互斥锁 
pthread_mutex_t main_wait, idle_wait;
float sum=0;//保存ci/ti总和 
pthread_t idle_proc;//信号量 
int main(int argc,char** argv)//主函数mian()初始化相关数据，创建实时任务并对任务进行调度 
{   
    pthread_mutex_init(&main_wait,NULL);//初始化 
    pthread_mutex_lock(&main_wait);  //下次执行lock等待，互斥锁 
    pthread_mutex_init(&idle_wait,NULL);//初始化
    pthread_mutex_lock(&idle_wait);  //下次执行lock等待
    printf("Please input number of real time tasks:\n");
    scanf("%d",&task_num);
    tasks = (task*)malloc(task_num*sizeof(task));
    int i;
for(i=0;i<task_num;i++)
{
        pthread_mutex_init(&proc_wait[i],NULL);//信号量初始化 
        pthread_mutex_lock(&proc_wait[i]);//上锁 
    }
for(i=0;i<task_num;i++)
{
        printf("Please input task id, followed by Ci and Ti:\n");
    getchar();
        scanf("%c,%d,%d,",&tasks[i].task_id,&tasks[i].ci,&tasks[i].ti);
        tasks[i].ci_left=tasks[i].ci;
        tasks[i].ti_left=tasks[i].ti;
        tasks[i].flag=2;//任务活跃 
        tasks[i].arg=i; 
        tasks[i].call_num=1; //执行次数为1 
        sum=sum+(float)tasks[i].ci/(float)tasks[i].ti; 
    }
    printf("Please input algorithm, 1 for EDF, 2 for RMS:");
    getchar();
    scanf("%d",&alg);
    printf("Please input demo time:");
    scanf("%d",&demo_time);
    double r=1;  //EDF算法
    if(alg==2)
    {  //RMS算法
        r=((double)task_num)*(exp(log(2)/(double)task_num)-1);
        printf("r is %lf\n",r);
    }
    if(sum>r)
    {  //不可调度
        printf("(sum=%lf > r=%lf) ,not schedulable!\n",sum,r);
        exit(2);
    }

    pthread_create(&idle_proc,NULL,(void*)idle,NULL); //创建闲逛线程
    for(i=0;i<task_num;i++)  //创建实时任务线程
        pthread_create(&tasks[i].th,NULL,(void*)proc,&tasks[i].arg);
    for(i=0;i<demo_time;i++)
    {
         int j; 
         if((curr_proc=select_proc(alg))!=-1)
         {  //按调度算法选线程
             pthread_mutex_unlock(&proc_wait[curr_proc]);  //唤醒
             pthread_mutex_lock(&main_wait);  //主线程等待
          }
          else
          {   //无可运行任务，选择闲逛线程
              pthread_mutex_unlock(&idle_wait);  
              pthread_mutex_lock(&main_wait);
          }
         for(j=0;j<task_num;j++)
          {  //Ti--，为0时开始下一周期
              if(--tasks[j].ti_left==0)
              {//开始下一周期 
                  tasks[j].ti_left=tasks[j].ti;
                  tasks[j].ci_left=tasks[j].ci;
                  pthread_create(&tasks[j].th,NULL,(void*)proc,&tasks[j].arg);
                  tasks[j].flag=2;
              }
         }
    }
    printf("\n");
    sleep(10); 
};

void proc(int* args)
{
    while(tasks[*args].ci_left>0)
    {
        pthread_mutex_lock(&proc_wait[*args]);  //上锁，等待被调度
        if(idle_num!=0)
{
            printf("idle(%d)",idle_num);
idle_num=0;
        }
        printf("%c%d",tasks[*args].task_id,tasks[*args].call_num);
        tasks[*args].ci_left--;  //执行一个时间单位
        if(tasks[*args].ci_left==0)//任务执行完 
        {
            printf("(%d)",tasks[*args].ci);
            tasks[*args].flag=0;//不活跃 
            tasks[*args].call_num++;//任务发生次数加一 
        }
        pthread_mutex_unlock(&main_wait); //解锁，唤醒主线程
    }
};
void* idle()
{
     while(1)
      {
        pthread_mutex_lock(&idle_wait);  //上锁，等待被调度
        printf("->");  //空耗一个时间单位
        idle_num++;
        pthread_mutex_unlock(&main_wait);  //解锁，唤醒主控线程
    }
};
int select_proc(int alg)//用于实现调度算法
{
    int j;
    int temp1,temp2;
    temp1=10000;
    temp2=-1;
    //RMS算法      任务序号          活跃 
    if((alg==2)&&(curr_proc!=-1)&&(tasks[curr_proc].flag!=0))
        return curr_proc; 

      for(j=0;j<task_num;j++)
      {
        if(tasks[j].flag==2)//处于活跃状态 
          {
            switch(alg)
              {
                case 1:    //EDF算法
                     if(temp1>tasks[j].ti_left)//剩余截至时间 
                        {
                           temp1=tasks[j].ti_left;// 更新 
                            temp2=j;//当前任务的序列号 
                    }
                case 2:    //RMS算法
                   if(temp1>tasks[j].ti)
                          {
                        temp1=tasks[j].ti;//更新 
                        temp2=j;
                    }
               }
             }
         }
            return temp2;
}
