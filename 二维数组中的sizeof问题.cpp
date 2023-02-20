#include<stdio.h>
int main(){
	int a[3][3];
	printf("%d %d",sizeof(a)/sizeof(a[0]),sizeof(a[0])/sizeof(int));
}
