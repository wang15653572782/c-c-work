#include <iostream>
#include <cmath>
using namespace std;
#define N 8
int queenPos[100];
//���������õĻʺ�λ�á������Ͻ���(0,0)
void NQueen(int k);
int a[100];
int z=1;
int main()
{
NQueen(0); //�ӵ�0�п�ʼ�ڻʺ�
	//cout<<a[2]<<endl;
	int n;
	cin >>n ;
	while(n--){
		int b;
		cin>>b;
		cout<<a[b]<<endl;
	}
	
	
	return 0;
}
void NQueen(int k) {
	int i;
	if (k == N) {//N���ʺ��Ѿ��ں�
	int t=0;
		for (i = 0; i < 8; i++){
			t=t*10+queenPos[i]+1;
		}
	//	cout<<t<<endl;
		a[z++]=t;	
		
		return;
	}
	for (i = 0; i < N; i++) {//���Ե�k���ʺ��λ��
		int j;
		for (j = 0; j < k; j++) {
			//���Ѿ��ںõģ���ʺ��λ�ñȽϣ����Ƿ��ͻ
			if (queenPos[j] == i || abs(queenPos[j] - i) == abs(k - j))
				break;
		}
if (j == k) {//��ǰѡ��λ��i����ͻ
	queenPos[k] = i;//����k���ʺ����λ��i
	NQueen(k + 1);
	}
	

	}
}
