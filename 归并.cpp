#include<stdio.h>
void merge(int a[],int first,int mid,int last,int temp[]) {     //��������ϲ����� 
 	int i=first,n=mid,j=mid+1,m=last,k=0;
 	while(i<=n&&j<=m){
 		if(a[i]<=a[j])
 			temp[k++]=a[i++];
		 else 
		 	temp[k++]=a[j++];
	 }
	 while(i<=n) {
	 	temp[k++]=a[i++];
	 }
	 while(j<=m){
	 	temp[k++]=a[j++];
	 }
	 for(i=0;i<last-first+1;i++) {
	 a[first+i]=temp[i];
     }
 }
  
 void mergesort(int a[],int first,int last,int temp[]){          //��������ϲ����� 
    int mid=(first+last)/2;
	if(first<last){
		mergesort(a,first,mid,temp); //���
		mergesort(a,mid+1,last,temp); //�ұ�
		merge(a,first,mid,last,temp); //ǰ�����õ����������������飬����������� 
	}   
 }
 
 
 int main(){
 	int a[1000],temp[1000],n;
 	scanf("%d",&n);
 	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	mergesort(a,0,n-1,temp) ;
	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	return 0;
 }
