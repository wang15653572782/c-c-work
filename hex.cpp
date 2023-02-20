#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include<algorithm>
using namespace std;
int new_x, new_y;
int flag= 1;//�ж��ҷ����ӵ�����1-�����ߣ�0-�����ߣ�2-�ߵ�ͷ��
const int SIZE = 11;
int board[SIZE][SIZE] = { 0 };//����1���Է�-1���հ�0
//�����ҷ�Ϊ��
int dx = 1, dy = 2;// ��ǰһ���µĵط�
int turn(int x,int y) {//�жϵ�ǰ������ҷ�������
	int i = x, j = y;
	if (i == 1 && j == 2)return 1;
	if (i == 10)return 2;
	for (int z = 0; z <= 10; ++z) {
		if (board[10][z] == 1)return 2;
	}
	if (board[i - 1][j - 1] == 1&&i+1<=10&&j+1<=10&&board[i+1][j+1]==0)return 1;
	if (board[i - 1][j - 1] == 1 && i + 1 <= 10 && j + 1 <= 10 && board[i + 1][j + 1] == -1)return 0;
	if (board[i - 2][j + 1] == 1&& i + 2 <= 10 && board[i+2][j-1]==0)return 0;
	if (board[i - 2][j + 1] == 1 &&i+2<=10&& board[i + 2][j - 1] == -1)return 1;
}
void FindBest(int flag_turn) {
if (board[0][2] == -1 && board[0][3] == 0) {
				new_x = 0; new_y = 3; return;
			}
			if (board[0][2] == 0 && board[0][3] == -1) {
				new_x = 0; new_y = 2; return;
			}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] && flag_turn == 2) {

			}
if (board[i][j] == 1&&flag_turn==1) {
				if (board[i - 1][j] == -1&&board[i][j-1]==0) {
					new_x = i; new_y = j - 1; return;
				}
				if (board[i - 1][j] == 0 && board[i][j - 1] == -1) {
					new_x = i-1; new_y = j; return;
				}
			}
if (board[i][j] == 1 && flag_turn==0) {
	if (board[i - 1][j] == -1 && board[i-1][j + 1] == 0) {
		new_x = i-1; new_y = j +1; return;
	}
	if (board[i - 1][j] == 0 && board[i-1][j +1] == -1) {
		new_x = i - 1; new_y = j; return;
	}
}//˫��ѭ��������з���������

		}
	int xi = dx, yi = dy;
	if (flag_turn == 1) {//������
		if (xi + 1 == 9 && yi + 1 == 10) {//�����
			if (board[10][9] == 0) {
				new_x = 10; new_y = 9; return;
			}
			if (board[10][10] == 0) {
				new_x = 10; new_y = 10; return;
			}
		}
		if (board[xi+1][yi+1] == 0) {//û���з�ռ��
			new_x = xi + 1; new_y = yi + 1; return;
		}
		if (board[xi + 1][yi + 1] == -1) {//���з�ռ���ˣ�����ת
			new_x = xi + 2; new_y = yi - 1; flag_turn = 0; return;
		}
	}
	if (flag_turn == 0) {//������
		if (board[xi + 2][yi - 1] == 0) {//û���з�ռ��
			new_x = xi + 2; new_y = yi -1; return;
		}
		if (board[xi + 2][yi - 1] == -1) {//���з�ռ���ˣ�����ת
			new_x = xi + 2; new_y = yi - 1; flag_turn = 1; return;
		}
	}
	if (flag_turn==2) {//������ͷ��	
			if (board[xi - 1][yi] == -1 && board[xi][yi - 1] == 0) {
				new_x = xi; new_y = yi - 1; return;
			}
			if (board[xi - 1][yi] == 0 && board[xi][yi - 1] == -1) {
				new_x = xi - 1; new_y = yi; return;
			}
			if (board[xi - 1][yi] == 0 && board[xi][yi - 1] == 0) {
				new_x = xi - 1; new_y = yi; return;
			}
		
	}
			
}
int main()
{
	int x, y, n;
	//�ָ�Ŀǰ��������Ϣ
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y; if (x != -1) board[x][y] = -1;	//�Է�
		cin >> x >> y; if (x != -1) board[x][y] = 1;	//�ҷ�
		if (i == n - 2) {
			dx = x; dy = y;//�ҷ�ǰһ���µ�����
		}
	}
	cin >> x >> y;  if (x != -1) board[x][y] = -1;	//�Է�
	else {
		dx = x; dy = y;//�ҷ�ǰһ���µ�����
		board[1][2] = 1;
		cout << 1 << ' ' << 2 << endl;
		return 0;
	}
	//��ʱboard[][]��洢�ľ��ǵ�ǰ���̵�����������Ϣ,x��y����ǶԷ����һ���µ���

	/************************************************************************************/
	/***********�����������Ĵ��룬���߽�������������ӵ�λ�ã�����new_x��new_y��****************/
	//�����Ϊ������Ե�ʾ�����룬��ɾ��
	//int avail_x[SIZE * SIZE], avail_y[SIZE * SIZE]; //�Ϸ�λ�ñ�
	//int cnt = 0;
	//for (int i = 0; i < SIZE; i++)
	//	for (int j = 0; j < SIZE; j++)
	//		if (board[i][j] == 0) {
	//			avail_x[cnt] = i;
	//			avail_y[cnt] = j;
	//			cnt++;
	//		}
	//srand(time(0));
	//int rand_pos = rand() % cnt;
	//int new_x = avail_x[rand_pos];
	//int new_y = avail_y[rand_pos];
	flag = turn(dx, dy);//�ж�����
	FindBest(flag);
	/***********���Ϸ������Ĵ��룬���߽�������������ӵ�λ�ã�����new_x��new_y��****************/
	/************************************************************************************/

	// ��ƽ̨������߽��
	cout << new_x << ' ' << new_y << endl;
	return 0;
}
