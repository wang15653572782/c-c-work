#include<iostream>
#include<algorithm>
using namespace std;
int time(int a[], int s, int e) {
	if (s == e)return 0;
	if (e - s == 1) {
		if (a[s] > a[e])return 1;
		else return 0;
	}
	else {
int m = s + (e - s) / 2;
	int coun = 0;
	sort(a + s, a + m+1, greater<int>());
	sort(a + m+1, a + e+1, greater<int>());
	int i = s, j = m + 1;
	while (i <= m&& j <= e) {
		while (a[i] <= a[j])j++;
				coun=coun+e-j+1;			
		i++;
	}
	return coun;
	}
	
}
int count(int a[], int s, int e) {
	if (s < e) {
		int m = s + (e - s) / 2;
		if (e - s == 1) {
			if (a[s] > a[e])return 1;
			else return 0;
		}

		return count(a, s, m) + count(a, m + 1, e);
	}
	else return 0;
	
}
int main() {
	int n;
	int a[100];
	cin >> n;
	for (int i = 0; i < n; i++)cin >> a[i];
	cout << time(a,0,n-1) << endl;
	return 0; 
}
