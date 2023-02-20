#include<stdio.h>
#include<stdlib.h>
#include<cstring> 
#include<iostream>
using namespace std;
 typedef struct node {
	struct node* next[20] = {NULL};
	int times = 0;
	char word[20] = "";
}Tnode, * Tnodeptr;
int dist(char* S, char* P) {
	int m = strlen(S);
	int n = strlen(P);
	char s[17], p[17];
	for (int i = 1; i < m + 1; ++i)s[i] = S[i - 1];
	for (int i = 1; i < n + 1; ++i)p[i] = P[i - 1];
	int Dist[20][20] = { 0 };
	for (int i = 0; i <= m; ++i)Dist[i][0] = i; 	
	for (int j = 0; j <= n; ++j)Dist[0][j] = j;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j) {
			if (s[i] == p[j])Dist[i][j] = Dist[i - 1][j - 1];
			else {
				int a = min(Dist[i - 1][j - 1], Dist[i][j - 1]);
				int b = min(a, Dist[i - 1][j]);
				Dist[i][j] = b + 1;
			}
		}
	return Dist[m][n];
}
void insert(Tnodeptr root, char *word, int times) {
	Tnodeptr tmp = root;
	int d=dist(tmp->word,word);
while(tmp->next[d]!=NULL){
	tmp=tmp->next[d];
	d=dist(tmp->word,word);
}
tmp->next[d]=new Tnode;
tmp->next[d]->times=times;
strcpy(tmp->next[d]->word,word);
	return;	
}
int flag=0;
Tnodeptr ros= new Tnode;
Tnodeptr R[1000];
int is=0;
void search(Tnodeptr root,char *wd,int k){
	if(root!=NULL){
		Tnodeptr tmp=root;
		int d=dist(tmp->word,wd);
		if(d<=k&&d!=0){
			R[is]=new Tnode;
			R[is]=tmp;
			is++;
		}
	int x=d-k;int y=d+k;
	for(int i=x;i<=y;++i){
	if(!flag&&i>=0&&i<=16)search(tmp->next[i],wd,k);
	}
	}
}
void find(int i){
	int max=R[0]->times;
	char ch[20];
	strcpy(ch,R[0]->word);
	for(int j=1;j<i;++j){
		if(R[j]->times>max){strcpy(ch,R[j]->word);max=R[j]->times;
		}
		if(R[j]->times==max&&strcmp(R[j]->word,ch)<0)strcpy(ch,R[j]->word);
	}
	printf("%s\n",ch);
	return;
}
void findk(Tnodeptr root,char *word,int k){
	Tnodeptr tmp=root;
while(tmp!=NULL){
	int d=dist(tmp->word,word);
	tmp=tmp->next[d];
	if(d==0){
		flag=1;break;
	}
	
}
if(flag==1){
printf("%s\n",tmp->word);return;
}
search(root,word,k);
if(is==0)printf("No similar word in dictionary\n");
if(is>0)find(is);
}

int main() {
	 Tnodeptr ro = new Tnode;
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; ++i) {
			int times;char x[16];
		
		scanf("%d", &times);
		scanf("%s", x);
		if(i==0){
			ro->times=times;
	strcpy(ro->word,x);
		}else{
			insert(ro, x, times);
		}	
	}
	for (int i = 0; i < m; ++i) {
		char y[20];
		scanf("%s", y);	
			findk(ro,y,k);
			flag=0;is=0;
	}
	return 0;
}
