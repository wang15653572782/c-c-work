#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;
struct BSTnode {
	struct BSTnode* left;
	struct BSTnode* right;
	int key;

};
//BSTnode* search(BSTnode* t, int k) {
//	if (t == NULL || t->key == k)return t;
//	if (k < t->key)return search(t->left, k);
//	else return search(t->right, k);
//}//查找算法递归实现
//BSTnode* seach2(BSTnode* t, int k) {
//	BSTnode* p = t;
//	while (p != NULL) {
//		if (k < p->key)p = p->left;
//		else if (k > p->key)p = p->right;
//		else return p;
//	}
//	return NULL;
//}//查找算法迭代实现
void insert(BSTnode*& p, int k) {
	if (p == NULL) {
		p= new BSTnode();
		p->key = k;
	}
	else if (k < p->key)insert(p->left, k);
	else if (k > p->key)insert(p->right, k);

}//插入算法
void deletek(BSTnode*& p, int k) {
	if (p == NULL)return;
	if (k < p->key)deletek(p->left, k);
	else if (k > p->key)deletek(p->right, k);
	//	
	else if (p->left == NULL || p->right == NULL) {
		//		if (p->left != NULL)p = p->left;
		//		if (p->right != NULL)p = p->right;	
		//		else p = NULL;
		BSTnode* tmp = p;

		p = (p->left != NULL) ? p->left : p->right;
		delete tmp;
		//	printf("%d",p->key);
	}
	else if (p->right->left == NULL) {
		BSTnode* sp;
		sp = p->right;
		sp->left = p->left;
		delete p; p = sp;
	}
	else {
		BSTnode* s = p->right;
		BSTnode* r = p->right;
		while (s->left != NULL) {
			r = s; s = s->left;
		}
		r->left = s->right;
		s->left = p->left; s->right = p->right;
		delete p; p = s;
	}
}
void PreOrder(BSTnode* p) {
	if (p == NULL)return;
	printf("%d ", p->key);
	PreOrder(p->left);
	PreOrder(p->right);
}
void InOrder(BSTnode* p) {
	if (p == NULL)return;
	InOrder(p->left);
	printf("%d ", p->key);
	InOrder(p->right);
}
int main() {
	BSTnode* t;
	t = NULL;
	int T;
	cin >> T;
	char sip[10]; int k;

	for (int i = 0; i < T; ++i) {
		scanf("%s", sip);
		scanf("%d", &k);
		if (strcmp(sip, "Insert") == 0)insert(t, k);
		else deletek(t, k);
	}
	//	printf("%d",t->left->left->left->key);
	InOrder(t);
	cout << endl;
	cout << endl;
	PreOrder(t);
	return 0;
}

