#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1005;
int a[N],num[N][N],dp[N][N];
int main()
{
    int m;
    char a[51];
    while(~scanf("%d",&m))
    {
        cin>>a+1;
        int n=strlen(a+1);
        //预处理,计算i到j数字串组成的数字
        for(int i = 1;i <= n;i++)
        {
            num[i][i] = a[i]-'0';//只有一个数字
            for(int j = i+1;j <= n;j++)
            {
                num[i][j] = num[i][j-1]*10 + a[j]-'0';
            }
        }
 
        memset(dp,0x3f,sizeof(dp));
        for(int i = 1;i <= n;i++)
            dp[0][i] = num[1][i];//无加号时
        for(int i = 1;i <= m;i++)
            for(int j = i;j <= n;j++)
                for(int k = i;k <= j;k++)
                    dp[i][j] = min(dp[i][j],dp[i-1][k] + num[k+1][j]);
        cout<< dp[m][n] <<endl;
    }
    return 0;
}
