#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int sum = 1,a;
	for(int i = 2; i * i <= n; i++)
		if(n % i == 0) {
			a = 1;
			while(n % i == 0) a *= i,n /= i;
			sum *= (a * i - 1) / (i - 1);//�ȱ��������
		}

	if(n > 1) sum *= (1 + n);
	cout << sum << endl;
	return 0; 
}

