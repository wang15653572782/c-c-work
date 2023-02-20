#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int ww[300];
int min(int n,int m)
{
 if(n>m) return m;
 else return n;
}
int max(int d[], int n)
{
 int max=0;
 for(int i=0;i<n;i++){
 	if(d[i]>max){
 		max=d[i];
	 }
 }
 return max;
}
void Sort(int w[],int d[],int s,int e){
	for(int i=s+1;i<=e;i++){
		int tp,td,j,tw;
		tp=w[i];
		td=d[i];
		tw=ww[i];
		j=i-1;
		while(j>=s&&tp>w[j]){
			w[j+1]=w[j];
			d[j+1]=d[j];
			ww[j+1]=ww[j];
			j--;
		}
		w[j+1]=tp;
		d[j+1]=td;
		ww[j+1]=tw;
	}
}
void unions(int pp[],int i,int m){
	int t;
	t=pp[i]+pp[m];
	if(pp[i]>pp[m]){
		pp[i]=m;
		pp[m]=t;
	}
	else{
		pp[m]=i;
		pp[i]=t;
	}
}
int find(int pp[],int i){
	int m,k,t;
	m=i;
	while(pp[m]>0){
		m=pp[m];
	}
	k=i;
	while(k!=m){
		t=pp[k];
		pp[k]=m;
		k=t;
	}
	return m;
}
int main(){
	int n,p[300],d[300],f[300],J[300],b,w[300],q[300];
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i]>>w[i];
		ww[i]=i;
	}
	Sort(w,d,1,n);
	b=min(n,max(d,n));
	//printf("%d\n",b);
	for(int i=0;i<=b;i++){
		f[i]=i;
		p[i]=-1;
	}
	for(int i=1;i<=b;i++){
		 q[i]=-1;
	}
	int k=0,jj,l;
	for(int i=1;i<=n;i++){
		jj=find(p,min(n,d[i]));
		if(f[jj]!=0){
			k=k+1;
			J[k]=i;
			q[f[jj]]=i;
			l=find(p,f[jj]-1);
		    unions(p,l,jj);
		    f[jj]=f[l];
		}
	}
	int money=0;
	for(int i=1;i<=k;i++){
		money=money+w[J[i]];
	}
	printf("%d\n",money);
//	for(int i=1;i<=k;i++){
//		printf("%d %d\\",w[J[i]],d[J[i]]);
//	}
//	printf("\n");
	int flag=0;
	for(int i=1;i<=b;i++){
		if(q[i]!=-1){
			if(flag==0){
				printf("%d",ww[q[i]]);
				flag=1;
			}
		else{
			printf(" %d",ww[q[i]]);
		}
	}
}
}
