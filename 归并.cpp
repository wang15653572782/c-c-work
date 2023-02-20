#include<stdio.h>
void merge(int a[],int first,int mid,int last,int temp[]) {     //有序数组合并排序 
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
  
 void mergesort(int a[],int first,int last,int temp[]){          //任意数组合并排序 
    int mid=(first+last)/2;
	if(first<last){
		mergesort(a,first,mid,temp); //左边
		mergesort(a,mid+1,last,temp); //右边
		merge(a,first,mid,last,temp); //前两步得到左右两个有序数组，将其组合排序 
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
