#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include<algorithm>
using namespace std;
int new_x, new_y;
int flag= 1;//判断我方棋子的走向，1-向下走，0-向左走，2-走到头了
const int SIZE = 11;
int board[SIZE][SIZE] = { 0 };//本方1，对方-1，空白0
//假设我方为红
int dx = 1, dy = 2;// 我前一步下的地方
int turn(int x,int y) {//判断当前棋局下我方的走向
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
}//双重循环检查假设敌方是阻拦我

		}
	int xi = dx, yi = dy;
	if (flag_turn == 1) {//向下走
		if (xi + 1 == 9 && yi + 1 == 10) {//特殊点
			if (board[10][9] == 0) {
				new_x = 10; new_y = 9; return;
			}
			if (board[10][10] == 0) {
				new_x = 10; new_y = 10; return;
			}
		}
		if (board[xi+1][yi+1] == 0) {//没被敌方占领
			new_x = xi + 1; new_y = yi + 1; return;
		}
		if (board[xi + 1][yi + 1] == -1) {//被敌方占领了，向左转
			new_x = xi + 2; new_y = yi - 1; flag_turn = 0; return;
		}
	}
	if (flag_turn == 0) {//向左走
		if (board[xi + 2][yi - 1] == 0) {//没被敌方占领
			new_x = xi + 2; new_y = yi -1; return;
		}
		if (board[xi + 2][yi - 1] == -1) {//被敌方占领了，向下转
			new_x = xi + 2; new_y = yi - 1; flag_turn = 1; return;
		}
	}
	if (flag_turn==2) {//到最左头了	
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
	//恢复目前的棋盘信息
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y; if (x != -1) board[x][y] = -1;	//对方
		cin >> x >> y; if (x != -1) board[x][y] = 1;	//我方
		if (i == n - 2) {
			dx = x; dy = y;//我方前一步下的棋子
		}
	}
	cin >> x >> y;  if (x != -1) board[x][y] = -1;	//对方
	else {
		dx = x; dy = y;//我方前一步下的棋子
		board[1][2] = 1;
		cout << 1 << ' ' << 2 << endl;
		return 0;
	}
	//此时board[][]里存储的就是当前棋盘的所有棋子信息,x和y存的是对方最近一步下的棋

	/************************************************************************************/
	/***********在下面填充你的代码，决策结果（本方将落子的位置）存入new_x和new_y中****************/
	//下面仅为随机策略的示例代码，可删除
	//int avail_x[SIZE * SIZE], avail_y[SIZE * SIZE]; //合法位置表
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
	flag = turn(dx, dy);//判断走向
	FindBest(flag);
	/***********在上方填充你的代码，决策结果（本方将落子的位置）存入new_x和new_y中****************/
	/************************************************************************************/

	// 向平台输出决策结果
	cout << new_x << ' ' << new_y << endl;
	return 0;
}
