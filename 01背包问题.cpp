#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

#define INT_MAX 1 << 30
#define MAX 100
typedef long long ll;
int n,m;
int v[3500];
int d[3500];
int dp[20000];
int f[3000][3000];

int main()
{
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for (int i = 1; i <=n; i += 1)
    {
        scanf("%d%d",&v[i],&d[i]);
    }
    for (int i = 1; i <=n; i++)
    {
        for (int j = m; j >= v[i]; j--)
        {
            dp[j] = max(dp[j],dp[j-v[i]]+d[i]);
        }
    }
    /*for (int i = 1; i <=m; i++)
    {//������ʵ�������յı仯�������Ҫ�����̵Ŀ��Կ��±�ע������Ǹ���ά����Ĵ�ӡ���̡�
        cout<<dp[i]<<' ';
    }*/

    printf("%d\n",dp[m]);
    /*memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < v[i]; j++)
            f[i][j] = f[i - 1][j];
        for(int j = v[i]; j <= m; j++)
        {
            if (f[i - 1][j] < f[i - 1][j - v[i]] + d[i])
                f[i][j] = f[i - 1][j - v[i]] + d[i];
            else
                f[i][j] = f[i - 1][j];
        }

    }
    for(int i=1; i<=n; i++)
    {//���������ı仯����
        for(int j=1; j<=m; j++)
        {
            cout<<f[i][j]<<' ';
        }
        cout<<endl;
    }
    cout << f[n][m] << "\n";*/
    return 0;
}


