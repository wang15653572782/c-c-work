#include<iostream>
#include<algorithm>
using namespace std;
#define Lmax 200
int W[Lmax] = { 0 }; int X[Lmax] = { 0 };
int n, M;
int flag = 0; int flag1 = 0;
void Sort(int* W, int* copy, int n) {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < n; ++j) {
			if (W[j] > W[j + 1]) {
				int temp1, temp2;
				temp1 = W[j];
				temp2 = copy[j];
				W[j] = W[j + 1];
				copy[j] = copy[j + 1];
				W[j + 1] = temp1;
				copy[j + 1] = temp2;
			}
		}
}
struct save {
	int len;
	int a[Lmax];
	bool operator<(const save& c) {
		if (len < c.len)return true;
		if (len == c.len) {
			for (int i = 0; i < len; ++i) {
				if (a[i]!=c.a[i])return a[i]<c.a[i];
			}
		}
	}
};
save B[Lmax]; int o = 0;
void prit(int* X, int* copy, int k, int n) {
	int flag[Lmax] = { 0 }; int z = 0;
	int Tmp[Lmax]={0};
	for (int i = 1; i <= k; ++i) {

	if(X[i]==1)flag[z++]=copy[i];
	}
	sort(flag, flag + z);
	B[o].len = z;
	for (int i = 0; i < z; ++i)B[o].a[i] = flag[i];
	o++;
}
void OUT() {
	sort(B, B + o );
	for (int i = 0; i < o ; ++i) {
		for (int j = 0; j < B[i].len - 1; ++j) {
			cout << B[i].a[j] << " ";
		}
		cout << B[i].a[B[i].len - 1] << "\n";
	}
}
void sumofsub(int s, int k, int r, int* copy) {
	int j;
	X[k] = 1;
	if (s + W[k] == M) {
		flag = 1;
		prit(X, copy, k, n);
	}
	else { if (s + W[k] + W[k + 1] <= M)sumofsub(s + W[k], k + 1, r - W[k], copy); }
	if ((s + r - W[k] >= M) && (s + W[k + 1] <= M)) {
		X[k] = 0; sumofsub(s, k + 1, r - W[k], copy);
	}
}

int main() {
	int r = 0;
	cin >> n >> M;
	int copy[Lmax];

	for (int i = 1; i <= n; ++i) {
		cin >> W[i]; r += W[i]; copy[i] = i;
	}
	Sort(W, copy, n);
	//for (int i = 1; i <= n; ++i)cout << W[i]<<" "<<copy[i]<<" ";

	sumofsub(0, 1, r, copy);

	if (flag == 0)cout << "no solution!" << endl;
	else {
		OUT();
	}
	return 0;
}
