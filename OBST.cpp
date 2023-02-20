#include <iostream> 
 using namespace std; 
  
 #define MAXNUM 100
 #define MAX 65536 
 //p��Ϊ����ؼ���k1��k5���������ʣ�k1<k2<k3<k4<k5 
 double p[MAXNUM] = {0.00,0.05,0.2,0.1,0.05}; 
 double q[MAXNUM] = {0.2,0.1,0.2,0.05,0.05}; 
 void optimal_bst(double e[][MAXNUM],int root[][MAXNUM],double w[][MAXNUM],int n) 
 { 
         int i =0,j=0; 
         //�������Һ���Ϊ���������ʼ�� 
         for(i = 1;i<=n+1;i++) 
         { 
                e[i][i-1] = q[i-1]; 
                 w[i][i-1] = q[i-1]; 
         } 
         int l = 0; 
         //����˳�����£����ݼ���ʽ��e[i,j] = e[i,r-1]+e[r+1,j 
//             ���ȼ���ڵ����Ϊ1�����Ŷ������Ĵ���e[1,1],e[2,2]���� 
//             ���ż���ڵ����Ϊ1�����Ŷ������Ĵ���e[1,2],e[2,3]���� 
//             ���� 
//             �����������Ϊn�����Ŷ������Ĵ���e[1,n]������֮ǰ����Ľ��ٽ�����Ŷ������Ľ���� 
         for(l = 1;l<=n;l++) 
         { 
                 for(i = 1;i<=n-l+1;i++) 
                 { 
                         j = i+l-1; 
                         e[i][j] = MAX; 
                         w[i][j] = w[i][j-1] + p[j]+q[j]; 
                         for(int r = i;r<=j;r++)  
                       { 
                                 double t = 0; 
                                t = e[i][r-1]+e[r+1][j] + w[i][j]; 
                                 if(t<e[i][j]) 
                                 { 
                                         e[i][j]= t; 
                                         root[i][j] = t; 
                                 } 
                         } 
  
                 } 
         } 
  
 } 
 int main() 
{ 
      double e[MAXNUM][MAXNUM]; 
         int root[MAXNUM][MAXNUM]; 
         double w[MAXNUM][MAXNUM];   
         optimal_bst(e,root,w,4); 
  
         for(int i =0;i<=5;i++) 
         { 
                 for(int j = 0;j<=4;j++) 
                 { 
                 cout << w[i][j] << "  "; 
                 cout << root[i][j] << "  "; 
                         cout << e[i][j] << "  "; 
                         cout<<endl;
                 } 
                 cout << endl; 
         } 
 }  
