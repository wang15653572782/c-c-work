#include<iostream>
#include<algorithm>
using namespace std;
const int Lmax = 201;
int FIND(int* parent, int i)
{//查找含有元素i的树根，使用压缩规则去压缩由i到根j的所有结点
	int j, k, t;
	j = i;
	while (parent[j] > 0) j = parent[j];//找根
	k = i;
	while (k != j) {//压缩由i到根j的结点
		t = parent[k];
		parent[k] = j;
		k = t;
	}
	return j;
}

void UNION(int* parent, int i, int j)
{//使用加权规则合并根为i和j的两个集合
	int x;
	x = parent[i] + parent[j];
	if (parent[i] > parent[j]) {//i的结点少
		parent[i] = j;
		parent[j] = x;
	}
	else {//j的结点少
		parent[j] = i;
		parent[i] = x;
	}
}
int k = 0;
void FJS(int  D[], int n, int b, int J[],int Q[]) {
	int F[Lmax], P[Lmax];
	for (int i = 0; i <= b; ++i) {
		F[i] = i; P[i] = -1;
	}
	
	for (int i = 1; i <= n; ++i) {
		int j = FIND(P,min(n, D[i]));
		if (F[j] != 0) {
			k++; J[k] = i;
			Q[F[j]] = i;
			int l = FIND(P,F[j] - 1); UNION(P,l, j);
			F[j] = F[l];
		}
	}
}
void SORT(int P[], int D[], int s, int e)//按效益大到小排序
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
int Sear(int copy[],int a,int n){
	for(int i=1;i<=n;++i){
		if(copy[i]==a)return i;
	}
	return 0;
}
int main() {
	int n;
	cin >> n;
	int P[Lmax], D[Lmax],J[Lmax],Q[Lmax],copy[Lmax];
	for (int i = 1; i <= n; ++i) {
		cin >> D[i] >> P[i];
		copy[i]=P[i];
	}
	SORT(P, D, 1, n);
	int m = 0;
	for (int i = 1; i <= n; ++i) {
		if (D[i] > m)m = D[i];
	}
	int b = min(n, m);
	for (int i = 1; i <= b; i++)
		Q[i] = -1;
	 FJS(D, n, b, J, Q);
	 int sum = 0;
	 for (int i = 1; i <= b; i++)
	 {
		 if (Q[i] != -1) {
			 sum += P[Q[i]];
		 }
	 }
	 cout << sum << endl;
	 for (int i = 1; i <= n; ++i) {
	 	
	if (Q[i] != -1)cout <<Sear(copy,P[Q[i]],n)<< " ";
	 }
	 return 0;
 }
