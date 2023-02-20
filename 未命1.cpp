#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

void UNION(int* parent, int i, int j)
{
	int x;
	x = parent[i] + parent[j];
	if (parent[i] > parent[j])//i节点少 
	{
		parent[i] = j;
		parent[j] = x;
	}
	if (parent[j] >= parent[i])
	{
		parent[j] = i;
		parent[i] = x;
	}
}

int Find(int i, int* parent)
{
	int j;
	int k, t;
	j = i;//查找包含元素i的树根
	while (parent[j] > 0)
	{
		j = parent[j];
	}
	k = i;
	while (k != j)
	{

		t = parent[k];
		parent[k] = j;
		k = t;
	}
	return j;
}


int FJS(int* Q, int* D, int n, int b, int* J)
{
	int i;
	int F[200];
	int P[200];
	int j, l;
	for (i = 0; i <= b; i++)
	{
		F[i] = i; P[i] = -1;
	}
	int k = 0;
	for (i = 1; i <= n; i++)
	{
		j = Find(min(n, D[i]), P);//D[i]超过n取n
		if (F[j] != 0)
		{
			k++;
			J[k] = i;
			Q[F[j]] = i;
			l = Find(F[j] - 1, P);

			UNION(P, l, j);
			F[j] = F[l];
		}
	}
	return k;
}


void SORT(int D[], int P[], int s, int e)//按效益大到小排序
{
 for (int i = s + 1; i <= e; ++i)
 {
  int tmp = P[i];
  int tmd = D[i];
  int j = i - 1;
  while (j >= s &&tmp > P[j])
  {
   P[j + 1] = P[j];
   D[j + 1] = D[j];
   j--;
  }
  P[j + 1] = tmp;
  D[j + 1] = tmd;
 }
}
int Max(int* D, int n)
{
	int b = 0;
	for (int i = 0; i < n; i++)
	{
		if (D[i] > b)b = D[i];
	}
	return b;
}
int main()
{
	int n;
	cin >> n;
	int D[202], D1[202];
	int P[202], P1[202];
	int J[202];
	for (int i = 1; i <= n; i++)
	{
		cin >> D[i] >> P[i];
		D1[i] = D[i];
		P1[i] = P[i];
	}

	Sort(D,P,1,n);
	int b = min(n, Max(D, n));
	int Q[202];
	for (int q = 1; q <= n; q++)
	{
		Q[q] = -1;
	}
	int num = FJS(Q, D, n, b, J);// 选出来了num个

	int sum = 0;
	for (int i = 1; i <= b; i++)
	{
		if (Q[i] == -1)
			continue;
		else
		{
			sum = sum + P[Q[i]];
		}

	}
	cout << sum << endl;


	//for (int i = 1; i <= b ;i++)
	//{
	//	cout << Q[i];
	//}

	//cout << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (P[Q[i]] == P1[j])
			{
				cout << j << " ";
			}
		}
	}

}

