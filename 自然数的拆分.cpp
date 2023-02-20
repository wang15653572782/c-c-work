#include<iostream>
using namespace std;
int a[5000];
void split(int t){
	for(int i=1;i<t;++i){
		cout<<a[i]<<"+";
	}
	cout<<a[t]<<endl;
	int j=t,L=a[j];
	for(int i=a[j-1];i<=L/2;++i){
		a[j]=i;a[j+1]=L-i;split(j+1);
	}
} 
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n/2;++i){
		a[1]=i;a[2]=n-i;split(2);
	}
	return 0;
}
