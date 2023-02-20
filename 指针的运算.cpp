#include<iostream>
using namespace std;
int main(){
	char* p1,*p2;
	int *p3,*p4;int n=4;
	p3=(int *)100;
	p4=(int *)200;
	cout<<p4-p3<<endl;
	p1=(char*)p3;
	p2=(char*)p4;
	cout<<p1-p2<<endl;
	cout<<(p4+n)-p3<<endl;
	
}

