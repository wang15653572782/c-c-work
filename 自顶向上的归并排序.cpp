#include<iostream>
using namespace std;

void Merge(int a[],int s,int m,int e){
	int pb=0;
	int tmp[100]; 
	int p1=s,p2=m+1;
	while(p1<=m&&p2<=e){
		if(a[p1]<a[p2])tmp[pb++]=a[p1++];
		else tmp[pb++]=a[p2++];
	}
	while(p1<=m)tmp[pb++]=a[p1++];
	while(p2<=e)tmp[pb++]=a[p2++];
	for(int i=0;i<e-s+1;++i)a[s+i]=tmp[i];
}
void MergeSort(int a[],int s,int e){
	for(int i=1;i<e+1;i*=2)
	for(int j=0;j<e+1;j+=2*i){
		Merge(a,j,j+i-1,min(j+2*i-1,e));
	}
}
int main(){
	int a[10]={1,34,45,576,876,5,67,43,23,43};
	MergeSort(a,0,9);
	for(int i=0;i<10;++i)
	printf("%d ",a[i]);
	return 0;
}
