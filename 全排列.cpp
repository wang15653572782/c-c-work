#include<stdio.h>
int num[15],book[15],n;
void print(){
	int i;
	for(i=1;i<=n;i++){
		if(i==n)printf("%d\n",num[i]);
		else printf("%d ",num[i]);
	}
}
void search(int step){
	int i;
	if(step>n)
		print();
	for(i=1;i<=n;i++)
		if(book[i]==0){
			book[i]=1;//���ʹ��ı��Ϊ1 
			num[step]=i;//��num�����¼ÿ�η��ʹ����� 
			search(step+1);//�������ṹ������������� 
			book[i]=0;//���� 
		}
}
int main(){
	while(1){
		scanf("%d",&n);
		if(n==0)break;
	int step=1;
	search(step);
	} 
	
	return 0;
}
