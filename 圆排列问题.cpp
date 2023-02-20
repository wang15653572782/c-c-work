#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
#define MAX 9999999999
double Xo[15];
int R[15];
int Copy[15];
int a[15];
double minL=MAX;
int flag[15]={0};
double getXo(int k){//第k个圆的圆心 
	double temp=0;
	for(int i=0;i<k;++i){
		double x=Xo[i]+sqrt((R[k]+R[i])*(R[k]+R[i])-(R[k]-R[i])*(R[k]-R[i]));
		if(x>temp)temp=x;
	}
	return temp;
}


void getL(int n){
	double l=MAX,r=-MAX;
	for(int i=0;i<n;++i){
		if(Xo[i]-R[i]<l)l=Xo[i]-R[i];
		if(Xo[i]+R[i]>r)r=Xo[i]+R[i];
	}
	if(r-l<minL){
		minL=r-l;
		for(int i=0;i<n;++i){
            a[i]=R[i];
        }
	}
}

void traceback(int k,int n){
	if(k==n)getL(n);
	else{
		for(int i=k;i<n;++i){
			swap(R[k],R[i]);
		
			double x=getXo(k);
			if(x+R[k]+R[0]<minL){
				Xo[k]=x;
				traceback(k+1,n);
			}
			swap(R[k],R[i]);
		
		}
	}
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>R[i];Copy[i]=R[i];
	}
//
int order[15];
int z=0;
	traceback(0,n);
	printf("%.2lf\n",minL);
	//for(int i=0;i<n;++i)cout<<Copy[i];
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)
		if(flag[j]==0&&Copy[j]==a[i]){
			flag[j]=1;order[z++]=j+1;break;
		}
	}
	for(int i=0;i<n;++i)cout<<order[i]<<" ";
	return 0;
}
