#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstring> 
using namespace std;
#define LL long long

int xiang();
int bds();

int xiang()//计算表达式
{
    int result;
    char op;
    while(op=cin.peek(),op==' ')//处理空格
        cin.get();

    if(op=='!')//如果有！
    {
        int fh=1;
        while(cin.peek()=='!'||cin.peek()==' ')//处理可能的多个！
        {
            char pt=cin.get();
            if(pt=='!')
                fh=-fh;
        }
        result=bds();//计算项
        if(fh==-1)
            result=!result;


    }
    else
        result=bds();

    int more=1;
    while(more)//是否还有项
    {
        char p;
        while(p=cin.peek(),p==' ')//处理空格
        cin.get();

        if(p=='&'||p=='|')//如果还有项
        {
            p=cin.get();
            int value;

            char p1;
            while(p1=cin.peek(),p1==' ')
            cin.get();


            if(p1=='!')//重复计算项的工作
            {
                int fh=1;
                while(cin.peek()=='!'||cin.peek()==' ')
                {
                    char pt=cin.get();
                    if(pt=='!')
                        fh=-fh;
                }
                value=bds();
                if(fh==-1)
                    value=!value;
            }
            else
                value=bds();

            if(p=='&')//把两个项连接在一起
                result&=value;
            else
                result|=value;
        }
        else//如果没有项more=0跳出循环
            more=0;
    }
    return result;
}

int bds()//计算项
{
    int result;
    char op;
    while(op=cin.peek(),op==' ')//处理空格
        cin.get();

    if(op=='(')//如果有'('表示：项由(表达式)组成
    {
        cin.get();//处理括号(
        result=xiang();//计算项
        cin.get();//处理括号)
    }
    else//项由真值F或V组成
    {
        char p=cin.get();
        if(p=='V')
            result=1;
        else
            result=0;
    }
    return result;
}

int main()
{
    int i=1;
    while(cin.peek()!=EOF)//如果输入流还有字符
    {
        int k=xiang();
        char e=cin.peek();
        while(cin.peek()==' ')//处理每一行输入末尾的空格
        cin.get();

        printf("Expression %d: ",i++);
        if(k==0)
            cout<<"F"<<endl;
        else
            cout<<"V"<<endl;

        cin.get();//处理每一行输入完成的'\n'
    }

    return 0;
}


