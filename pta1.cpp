#include<stdio.h>
#include<stdlib.h>
#define size 606
#define max 999999999 
int edge[size][size];
int prim(int n) {
	int lowcost[size];
	int U[size];
	int sum = 0;
	int v,min;
	for (int i = 0; i < n; i++) {
		lowcost[i] = edge[0][i]; U[i] = 1;
	}
	U[0] = -1;
	for (int i = 1; i <= n-1; i++) {
		v = 0; min = max;
		for (int j = 0; j <n; j++) {
			if (U[j] != -1 && lowcost[j] < min) {
				v = j; min = lowcost[j];
			}			
		}
        if (v == 0) {		
			return -1;
		}
		sum += min;
	 lowcost[v] = 0; U[v] = -1;
	 for (int j = 0; j < n; j++) {
     if (U[j] != -1 && edge[v][j] < lowcost[j]) {
				lowcost[j] = edge[v][j]; U[j] = v;
			}
		}			
	}
	return sum;
}
int main() {
for (int i = 0; i <size; i++)
			for (int j = 0; j < size; j++) {			
					edge[i][j] = max;			
			}
	int e, n;
	int cost = 0;
	scanf("%d%d", &n, &e);
	for(int i=0;i<n;++i){
		int z;
	scanf("%d",&z);
	edge[i][n]=z;
	edge[n][i]=z;
	}
		
		for (int i = 0; i < e; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			edge[a][b] = c;
			edge[b][a] = c;
		}	
		cost = prim(n+1);
		printf("%d",cost);
	return 0;
}
