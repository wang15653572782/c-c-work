#ifdef  HAVE_CONFIG_H
#include  <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#define MAPSIZE 100
struct map  //存储资源表结构
{
    int m_addr;//空闲区域首址 
    int m_size;//空闲区域长度 
};
struct map map[MAPSIZE];  //存储资源表
//BF存储分配函数
int BF_malloc(struct map *mp,int size)  
{
    register int a,s;//register申请变量是储存在CPU中央寄存器中的，用以提高读写速度 
    register struct map *bp,*bpp;
    for(bp = mp; bp->m_size; bp++)
    {
       if (bp->m_size >= size)
        {
            a = bp->m_addr;
            s = bp->m_size;
            for(bpp = bp; bpp->m_size; bpp++)//寻找满足申请要求且长度最小的空闲区域 
            {   //最佳适应
                if(bpp->m_size >= size && bpp->m_size < s)
                {
                    a = bpp->m_addr;
                    s = bpp->m_size;
                    bp = bpp;
                }
            }
            bp->m_addr += size;//更新首址 
            if ((bp->m_size -= size) == 0)//这段空闲空间恰好为size 
                do
                {
                    bp++;
                    (bp-1)->m_addr = bp->m_addr;// 更新为下一个空闲区域的指针 
                }
                while((bp-1)->m_size = bp->m_size);//末尾截至 
            return(a);
        }
    }
    return(-1);
}
//WF存储分配函数
int WF_malloc(struct map *mp,int size) 
{
    register int a,s;
    register struct map *bp,*bpp;
    for(bp = mp; bp->m_size; bp++)
    {
        if (bp->m_size >= size)
        {
            a = bp->m_addr;
            s = bp->m_size;
            for(bpp = bp; bpp->m_size; bpp++) //满足申请要求且长度最大的空闲区域 
            {   //最坏适应
                if(bpp->m_size > s) 
                {
                    a = bpp->m_addr;
                    s = bpp->m_size;
                    bp = bpp;
                }
            }
            bp->m_addr += size;//更新首址 
            if ((bp->m_size -=size) == 0)//这段空闲空间恰好为size 
                do
                {
                    bp++;
                    (bp-1)->m_addr = bp->m_addr;// 更新为下一个空闲区域的指针 
                }
                while((bp-1)->m_size = bp->m_size);//末尾截至 
            return(a);
        }
    }
    return(-1);
}
//存储释放函数
void mfree(struct map *mp,int aa,int size) 
{
    register struct map *bp;
    register int t;
    register int a;
    a = aa;
    for(bp = mp; bp->m_addr<=a && bp->m_size != 0; bp++);//找到合适的地址 
    if(bp>mp && (bp-1)->m_addr+(bp-1)->m_size==a)
    {  //与前合并
         (bp-1)->m_size += size;
         if (a+size == bp->m_addr)
         {   //前后合并
              (bp-1)->m_size += bp->m_size;
              while (bp->m_size)//更新后面所有的首址和长度 
              {
                  bp++;
                  (bp-1)->m_addr = bp->m_addr;
                  (bp-1)->m_size = bp->m_size;
              }
         }
    }
else
    {
         if (a+size == bp->m_addr && bp->m_size)
         {   //与后合并
              bp->m_addr -= size;
              bp->m_size += size;
         }
         else if (size)
              do
              {   //无合并
                   t = bp->m_addr;
                   bp->m_addr = a;
                   a = t;
                   t = bp->m_size;
                   bp->m_size = size;
                   bp++;
              }
              while (size = t);//判断是末尾 
    }
}
void init()//初始化 
{
    struct map *bp;
    int addr,size;
    int i=0;
    bp=map;
    printf("Please input starting addr and total size:");
    scanf("%d,%d",&addr,&size);
    bp->m_addr=addr;
    bp->m_size=size;
    (++bp)->m_size=0;  //表尾
}
void show_map()//显示存储资源表
{
     int i=0;
     system("clear");  //清屏
     struct map *bp;
     bp=map;
     printf("\nCurrent memory map...\n");
     printf("Address\t\tSize\n");
     while(bp->m_size!=0)
     {
         printf("<%d\t\t%d>\n",bp->m_addr,bp->m_size);
	    bp++;
     }
     printf("\n");
}
main()
{
    int a,s;
    char c;
    int i;
    init();
    printf("please input, b for BF, w for WF:");
    scanf("%c",&c);
    getchar();
    do
    {
        show_map(); //显示存储资源表
        printf("Please input,1 for request,2 for release,0 for exit:");
        scanf("%d",&i);
        switch(i)
        {
            case 1:
                printf("Please input size:");
                scanf("%d", &s);
                if(c==’b’)  //BF
                    a=BF_malloc(map,s);
                else  //WF
                    a=WF_malloc(map,s);
                if(a==-1)
                    printf("request can't be satisfied\n");
                else
                    printf("alloc memory at address:%d,size:%d\n",a,s);
                break;
            case 2:
                printf("Please input addr and size:");
                scanf("%d,%d",&a,&s);
                mfree(map,a,s);
                break;
            case 0:
                exit(0);
        }
    }
    while(1);
}
