#include "math.h"
#include "sched.h"
#include "pthread.h"
#include "stdlib.h"
#include "semaphore.h" 
#include "stdio.h"
#include <unistd.h>
typedef struct{  //ʵʱ��������
    char task_id;//������ 
    int call_num;  //����������
    int ci;  // Ci����ʱ�� 
    int ti;  //Ti �������� 
    int ci_left;//ʣ��� 
    int ti_left; 
    int flag;  //�����Ƿ��Ծ��0��2��
    int arg;  //����
    pthread_t th;  //�����Ӧ�߳�
}task;
void proc(int* args);
void* idle();
int select_proc();//����ʵ�ֵ����㷨,��ѡ������ִ��proc()����û�п�ִ������ʱִ��idle()
int task_num = 0;
int idle_num = 0;
int alg;  //��ѡ�㷨��1 �� EDF��2 �� RMS
int curr_proc=-1;//��ǰ������� 
int demo_time = 100;  //��ʾʱ��
task* tasks;
pthread_mutex_t proc_wait[100];//�ٽ���������ʵ�ֻ����� 
pthread_mutex_t main_wait, idle_wait;
float sum=0;//����ci/ti�ܺ� 
pthread_t idle_proc;//�ź��� 
int main(int argc,char** argv)//������mian()��ʼ��������ݣ�����ʵʱ���񲢶�������е��� 
{   
    pthread_mutex_init(&main_wait,NULL);//��ʼ�� 
    pthread_mutex_lock(&main_wait);  //�´�ִ��lock�ȴ��������� 
    pthread_mutex_init(&idle_wait,NULL);//��ʼ��
    pthread_mutex_lock(&idle_wait);  //�´�ִ��lock�ȴ�
    printf("Please input number of real time tasks:\n");
    scanf("%d",&task_num);
    tasks = (task*)malloc(task_num*sizeof(task));
    int i;
for(i=0;i<task_num;i++)
{
        pthread_mutex_init(&proc_wait[i],NULL);//�ź�����ʼ�� 
        pthread_mutex_lock(&proc_wait[i]);//���� 
    }
for(i=0;i<task_num;i++)
{
        printf("Please input task id, followed by Ci and Ti:\n");
    getchar();
        scanf("%c,%d,%d,",&tasks[i].task_id,&tasks[i].ci,&tasks[i].ti);
        tasks[i].ci_left=tasks[i].ci;
        tasks[i].ti_left=tasks[i].ti;
        tasks[i].flag=2;//�����Ծ 
        tasks[i].arg=i; 
        tasks[i].call_num=1; //ִ�д���Ϊ1 
        sum=sum+(float)tasks[i].ci/(float)tasks[i].ti; 
    }
    printf("Please input algorithm, 1 for EDF, 2 for RMS:");
    getchar();
    scanf("%d",&alg);
    printf("Please input demo time:");
    scanf("%d",&demo_time);
    double r=1;  //EDF�㷨
    if(alg==2)
    {  //RMS�㷨
        r=((double)task_num)*(exp(log(2)/(double)task_num)-1);
        printf("r is %lf\n",r);
    }
    if(sum>r)
    {  //���ɵ���
        printf("(sum=%lf > r=%lf) ,not schedulable!\n",sum,r);
        exit(2);
    }

    pthread_create(&idle_proc,NULL,(void*)idle,NULL); //�����й��߳�
    for(i=0;i<task_num;i++)  //����ʵʱ�����߳�
        pthread_create(&tasks[i].th,NULL,(void*)proc,&tasks[i].arg);
    for(i=0;i<demo_time;i++)
    {
         int j; 
         if((curr_proc=select_proc(alg))!=-1)
         {  //�������㷨ѡ�߳�
             pthread_mutex_unlock(&proc_wait[curr_proc]);  //����
             pthread_mutex_lock(&main_wait);  //���̵߳ȴ�
          }
          else
          {   //�޿���������ѡ���й��߳�
              pthread_mutex_unlock(&idle_wait);  
              pthread_mutex_lock(&main_wait);
          }
         for(j=0;j<task_num;j++)
          {  //Ti--��Ϊ0ʱ��ʼ��һ����
              if(--tasks[j].ti_left==0)
              {//��ʼ��һ���� 
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
        pthread_mutex_lock(&proc_wait[*args]);  //�������ȴ�������
        if(idle_num!=0)
{
            printf("idle(%d)",idle_num);
idle_num=0;
        }
        printf("%c%d",tasks[*args].task_id,tasks[*args].call_num);
        tasks[*args].ci_left--;  //ִ��һ��ʱ�䵥λ
        if(tasks[*args].ci_left==0)//����ִ���� 
        {
            printf("(%d)",tasks[*args].ci);
            tasks[*args].flag=0;//����Ծ 
            tasks[*args].call_num++;//������������һ 
        }
        pthread_mutex_unlock(&main_wait); //�������������߳�
    }
};
void* idle()
{
     while(1)
      {
        pthread_mutex_lock(&idle_wait);  //�������ȴ�������
        printf("->");  //�պ�һ��ʱ�䵥λ
        idle_num++;
        pthread_mutex_unlock(&main_wait);  //���������������߳�
    }
};
int select_proc(int alg)//����ʵ�ֵ����㷨
{
    int j;
    int temp1,temp2;
    temp1=10000;
    temp2=-1;
    //RMS�㷨      �������          ��Ծ 
    if((alg==2)&&(curr_proc!=-1)&&(tasks[curr_proc].flag!=0))
        return curr_proc; 

      for(j=0;j<task_num;j++)
      {
        if(tasks[j].flag==2)//���ڻ�Ծ״̬ 
          {
            switch(alg)
              {
                case 1:    //EDF�㷨
                     if(temp1>tasks[j].ti_left)//ʣ�����ʱ�� 
                        {
                           temp1=tasks[j].ti_left;// ���� 
                            temp2=j;//��ǰ��������к� 
                    }
                case 2:    //RMS�㷨
                   if(temp1>tasks[j].ti)
                          {
                        temp1=tasks[j].ti;//���� 
                        temp2=j;
                    }
               }
             }
         }
            return temp2;
}
