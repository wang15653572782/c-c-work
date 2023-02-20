#include<stdio.h>
#include<stdlib.h>
#define size 1000
struct Step {
	int x, y;
	int steps;
};
typedef struct {
	int front;
	int rear;
	Step data[size];
}queue;
void push(Step item, queue* p) {
	p->data[p->rear] = item;
	p->rear++;
}
void pop(queue* p) {
	p->front++;
}
int empty(queue* p) {
	if (p->front == p->rear)return 1;
	else return 0;
}
int a[100][100];
int visit[100][100] = { 0 };
int Next[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
int n, m;
void bfs(queue* q, int ai, int b) {
	
	Step nd;
	nd.x = ai, nd.y = b, nd.steps = 0; visit[ai][b] = 1;
	push(nd, q);
	while (!empty(q)) {
		Step s = q->data[q->front];
		//printf("%d %d\n", s.x, s.y);
		//printf("%d\n", s.steps);
		if (a[s.x][s.y]==4) {
			printf("%d\n", s.steps);
			return;
		}
		for (int i = 0; i < 4; i++) {
			int nx = s.x + Next[i][0];
			int ny = s.y + Next[i][1];
			int step = s.steps + 1;
			if ((nx < n && nx >= 0) && (ny <m && ny >= 0) && (visit[nx][ny] == 0) && (a[nx][ny]!=1)) {
				Step p; p.x = nx, p.y = ny, p.steps = step;
				visit[nx][ny] = 1; 
				push(p, q);
			}
		}
		pop(q);
	}
	printf("unreachable\n");
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		queue q;
		q.front = 0;
	q.rear = 0;
	int ai, b;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				scanf("%d",&a[i][j]);
				if (a[i][j] == 3) {
					ai = i, b = j;
				}
			
			}
		bfs(&q, ai, b);
	}
	return 0;
}
