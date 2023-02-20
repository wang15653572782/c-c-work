#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;
struct BSTnode {
	struct BSTnode* left;
	struct BSTnode* right;
	struct BSTnode* parent;
	int key;
	char color;
};
void LL(BSTnode*& A) {
	BSTnode* B = A->left;
	A->left = B->right;
	B->right = A;
	A = B;
}
void RR(BSTnode*& A) {
	BSTnode* B = A->right;
	A->right = B->left;
	B->left = A;
	A = B;
}
void LR(BSTnode*& A) {
	RR(A->left);
	LL(A);
}
void RL(BSTnode*& A) {
	LL(A->right);
	RR(A);
}

void insert(BSTnode*& xi, int k) {

	if (xi== NULL) {
		xi = new BSTnode();
		xi->color = 'B';
		xi->key = k;
		cout << k;
		return;
	}
	cout << xi->key;
	if (xi != NULL) {
		BSTnode* x = xi;
		BSTnode* p = x;
		BSTnode* g =NULL;
		BSTnode* u = NULL;
		while (x != NULL) {
			p = x;
			if (k < x->key) {
				x = x->left;

			}
			else if (k > x->key) {
				x = x->right;
			}
			else return;
		}
		x = new BSTnode();
		x->color = 'R';
		x->key = k;//cout<<xi->key;
		if (k < p->key) {p->left = x;x->parent = p; }
		else {p->right = x; x->parent = p; }
		if (p->color == 'B'||p==NULL) return;
		while (p->color == 'R'&&p) {
			g = p->parent;
			u = (p == g->left) ? g->right : g->left;
			if (x == p->left && p == g->left &&u&& u->color == 'B') {
				LL(g); g->color = 'B'; g->left->color = 'R'; g->right->color = 'R';
			}
			else if (p == g->right && x == p->right &&u&& u->color == 'B') {
				RR(g); g->color = 'B'; g->left->color = 'R'; g->right->color = 'R';
			}
			else if (p == g->left && x == p->right &&u&& u->color == 'B') {
				LR(g); g->color = 'B'; g->left->color = 'R'; g->right->color = 'R';
			}
			else if (p == g->right && x == p->left &&u&& u->color == 'B') {
				RL(g); g->color = 'B'; g->left->color = 'R'; g->right->color = 'R';
			}
			else if (u->color == 'R') {
				p->color = 'B'; u->color = 'B';
				if (g == xi)g->color = 'B';
				else {
					g->color = 'R';
					x = g; p = x->parent;
				}
			}

		}
	}
}
void deletek(BSTnode*& p, int k) {
	
}
void PreOrder(BSTnode* p) {
	if (p == NULL)return;
	printf("%d %c ", p->key,p->color);
	PreOrder(p->left);
	PreOrder(p->right);
}
void InOrder(BSTnode* p) {
	if (p == NULL)return;
	InOrder(p->left);
	printf("%d %c ", p->key, p->color);
	InOrder(p->right);
}

int main() {
	BSTnode* t=NULL;
	
	//freopen("in.txt", "r", stdin);
	int T;
	cin >> T;
	char sip[10]; int k;
	//printf("%d", t->key);
	for (int i = 0; i < T; ++i) {
		scanf("%s", sip);
		scanf("%d", &k);
		if (sip[0] == 'I') { insert(t, k);  }
		//else deletek(t, k);
	
	}
		if(t==NULL)cout<<"123";
		else cout<<t->color;
	/*InOrder(t);
	cout << endl;
	cout << endl;
	PreOrder(t);*/
	return 0;
}

