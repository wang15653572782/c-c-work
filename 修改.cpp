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
bool vaild(int x, int y) {//判断点是否出界
	if (x >= 0 && x <= 10 && y >= 0 && y <= 10)return true;
	else return false;
}
int turn() {//判断当前棋局下我方的走向
	for (int z = 0; z <= 10; ++z) {
		if (board[10][z] == 1)return 2;
	}
	while (dx <= 10 && dy <= 10) {
		while (dx <= 10 && dy <= 10 && board[dx][dy] == 1) {
			dx++; dy++;
		}
		//if (board[dx][dy] == 0)return 1;
		dx--; dy--;
		if (dx + 2 <= 10 && dy + 1 <= 10) {
			if (board[dx + 2][dy - 1] == -1 && board[dx + 1][dy + 1] == 0) return 1;
			if (board[dx + 2][dy - 1] == 0 && board[dx + 1][dy + 1] == 0) return 1;
			if (board[dx + 2][dy - 1] == 0 && board[dx + 1][dy + 1] == -1) return 0;
		}
		if (dx == 9)return 0;
		while (dx <= 10 && dy <= 10 && board[dx][dy] == 1) {
			dx += 2; dy--;
		}
		dx -= 2; dy++;
		if (dx + 2 <= 10 && dy + 1 <= 10) {
			if (board[dx + 1][dy + 1] == 0 && board[dx + 2][dy - 1] == 0)return 0;
			if (board[dx + 1][dy + 1] == -1 && board[dx + 2][dy - 1] == 0)return 0;
			if (board[dx + 1][dy + 1] == 0 && board[dx + 2][dy - 1] == -1)return 1;
		}
	}
	/*if (board[i - 1][j - 1] == 1&&i+1<=10&&j+1<=10&&board[i+1][j+1]==0)return 1;
	if (board[i - 1][j - 1] == 1 && i + 1 <= 10 && j + 1 <= 10 && board[i + 1][j + 1] == -1)return 0;
	if (board[i - 2][j + 1] == 1&& i + 2 <= 10 && board[i+2][j-1]==0)return 0;
	if (board[i - 2][j + 1] == 1 &&i+2<=10&& board[i + 2][j - 1] == -1)return 1;*/
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
			if (board[i][j] == 1 && vaild(i - 1, j - 1) && board[i - 1][j - 1] == 1) {
				if (vaild(i + 1, j + 1) && board[i + 1][j + 1] != 1 && board[i + 2][j - 1] == 1) {
					if (board[i + 1][j - 1] == 1 || board[i + 1][j] == 1)break;
					if (board[i+ 1][j-1] == -1 && board[i + 1][j ] == 0) {
						new_x = i + 1; new_y = j ; return;
					}
					if (board[i + 1][j-1] == 0 && board[i +1][j] == -1) {
						new_x = i +1; new_y = j-1; return;
					}
				}
				if (board[i - 1][j] == -1 && board[i][j - 1] == 0&&board[i-1][j-1]==1) {
					new_x = i; new_y = j - 1; return;
				}
				if (board[i - 1][j] == 0 && board[i][j - 1] == -1&&board[i-1][j-1]==1) {
					new_x = i - 1; new_y = j; return;
				}
				if (board[i + 1][j] == -1 && board[i][j + 1] == 0&&board[i+1][j+1]==1) {
					new_x = i; new_y = j + 1; return;
				}
				if (board[i + 1][j] == 0 && board[i][j + 1] == -1&&board[i+1][j+1]==1) {
					new_x = i + 1; new_y = j; return;
				}
			}
			if (board[i][j] == 1 && vaild(i - 2, j + 1) && board[i - 2][j + 1] == 1) {
				if (vaild(i + 2, j -1) && board[i + 1][j + 1] == 1 && board[i + 2][j - 1] != 1) {
					if (board[i + 1][j] == 1 || board[i][j + 1] == 1)break;
					if (board[i + 1][j] == -1 && board[i][j+1] == 0) {
						new_x = i; new_y = j+1; return;
					}
					if (board[i + 1][j] == 0 && board[i][j+1] == -1) {
						new_x = i + 1; new_y = j; return;
					}
				}
				if (board[i - 1][j] == -1 && board[i - 1][j + 1] == 0&&board[i-2][j+1]==1) {
					new_x = i - 1; new_y = j + 1; return;
				}
				if (board[i - 1][j] == 0 && board[i - 1][j + 1] == -1&&board[i-2][j+1]==1) {
					new_x = i - 1; new_y = j; return;
				}
				if (board[i + 1][j - 1] == -1 && board[i + 1][j] == 0&&board[i+2][j-1]==1) {
					new_x = i + 1; new_y = j; return;
				}
				if (board[i + 1][j - 1] == 0 && board[i + 1][j] == -1&&board[i+2][j-1]==1) {
					new_x = i + 1; new_y = j - 1; return;
				}
			}

			//双重循环检查假设敌方是阻拦我
		}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 1 && flag_turn == 2) {
				if (board[0][2] == 0 && board[0][3] == 0) {
					new_x = 0; new_y = 3; return;
				}
				if (vaild(i - 1, j - 1) && board[i - 1][j - 1] == 1) {
					if (board[i][j - 1] == 0 && board[i - 1][j] == 0) {
						new_x = i; new_y = j - 1; return;
					}

				}
				if (vaild(i - 2, j + 1) && board[i - 2][j + 1] == 1 && board[i - 1][j] == 0) {
					if (board[i - 1][j + 1] == 0) {
						new_x = i - 1; new_y = j + 1; return;
					}
				}
			}
		}
	int xi = dx, yi = dy;
	if (flag_turn == 1) {//向下走
	if(board[3][4]==1&&board[5][3]==0&&board[7][2]==0&&board[9][1]==0){
		new_x=5;new_y=3;return;
	}
	if(board[4][5]==1&&board[6][4]==0&&board[8][3]==0&&board[10][2]==0){
		new_x=6;new_y=4;return;
	}
		if(board[5][6] == 1&&board[7][5]==0&&board[9][4]==0) {
			new_x = 7; new_y = 5; return;
}
		if (board[6][7] == 1 && board[8][6] == 0 && board[10][5] == 0) {
			new_x = 8; new_y = 6; return;
		}
		if (board[7][8] == 1 && board[9][7] == 0) {
			new_x = 9; new_y = 7; return;
		}
		if (xi + 1 == 9 && yi + 1 == 10) {//特殊点
			new_x = 9; new_y = 10; return;
		}
		if (vaild(xi+1,yi+1)&&board[xi+1][yi+1] == 0) {//没被敌方占领
			new_x = xi + 1; new_y = yi + 1; return;
		}
		if (vaild(xi+1,yi+1)&&board[xi + 1][yi + 1] == -1) {//被敌方占领了，向左转
			new_x = xi + 2; new_y = yi - 1; flag_turn = 0; return;
		}
	}
	if (flag_turn == 0) {//向左走
		if (xi == 9) {
			new_x = 10;
			if (board[10][yi] == 0) { new_y = yi; return; }
			if (board[10][yi - 1] == 0 && board[10][yi] != 1) { new_y = yi - 1; return; }
			
		}
		if (yi == 0 && xi < 10) {
			new_x = xi + 1; new_y = yi + 1; return;
		}
		if (vaild(xi+2,yi-1)&&board[xi + 2][yi - 1] == 0) {//没被敌方占领
			if (board[xi + 1][yi - 1] == -1 && board[xi + 1][yi] == -1) {
				new_x = xi + 1; new_y = yi + 1; return;
			}
			else {
				new_x = xi + 2; new_y = yi - 1; return;
			}
		}
		if (vaild(xi + 2, yi - 1) && board[xi + 2][yi - 1] == -1) {//被敌方占领了，向下转
			new_x = xi +1; new_y = yi +1;  return;
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
int x1 = -1, y1 = -1;
int search(int p, int q) {
	if (board[p - 2][q + 1] == 1 && (p - 2) >= 0 && (q + 1) <= 10) {
		if (board[p - 1][q] == -1 && board[p - 1][q + 1] == 0) {
			x1 = p - 1; y1 = q + 1; return 1;
		}
		if (board[p - 1][q] == 0 && board[p - 1][q + 1] == -1) {
			x1 = p - 1; y1 = q; return 1;
		}
	}
	else {
		if (p - 1 < 0 || q + 1 > 10) return 0;
		if (board[p][q + 1] == -1 && board[p - 1][q + 1] == 0) {
			x1 = p - 1; y1 = q + 1; return 1;
		}
		if (board[p][q + 1] == 0 && board[p - 1][q + 1] == -1) {
			x1 = p; y1 = q + 1; return 1;
		}
	}
	return 0;
}
int main()
{
	int  result = 0, X = -1, Y = -1;
	int x, y, n;
	//恢复目前的棋盘信息
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y; if (x != -1) board[x][y] = -1;	//对方
		cin >> x >> y; if (x != -1) board[x][y] = 1;	//我方
		//if (i == n - 2) {
		//	dx = x; dy = y;//我方前一步下的棋子
		//}
	}
	cin >> x >> y;  if (x != -1) board[x][y] = -1;	//对方
	else {
		//dx = x; dy = y;//我方前一步下的棋子
		board[1][2] = 1;
		cout << 1 << ' ' << 2 << endl;
		return 0;
	}
	
	if (board[1][2] == 1) {
flag = turn();//判断走向
	FindBest(flag);
	}
	if (board[1][2] == -1) {

		if (board[10][0] == 0) {
			new_x = 10; new_y = 0;//抢占蓝色优势位
		}
		else {
			for (int i = 10; i >= 0; i--) {
				if (result == 1) {
					break;
				}
				for (int j = 0; j <= 10; j++) {
					if (board[i][j] == 1) {
						if (j > Y) {
							X = i; Y = j;//存离胜利最近的棋子 
						}
						result = search(i, j);//返回查询结果，如果附近四个点有棋子 为1 
						if (result == 1) {//如果有对方棋子挡路 
							new_x = x1;
							new_y = y1;
							break;
						}
					}
				}
			}//遍历棋盘看是否有棋子挡4路 
			if (result == 0) {//没有棋子当陆，准备走对角线； 
				if (Y < 9) {
					if ((X - 1 >= 0 && Y + 2 <= 10) || (X - 2 >= 0 && Y + 1 <= 10)) {
						if (board[X - 1][Y + 2] == 0 && X - 1 >= 0 && Y + 2 <= 10) {
							new_x = X - 1; new_y = Y + 2;
						}
						else if (X - 2 >= 0 && Y + 1 <= 10) {
							new_x = X - 2; new_y = Y + 1;
						}
					}
					else {
						new_x = X + 1; new_y = Y + 1;
					}
				}
				else {
					X = 10; Y = 0;
					while (1) {
						if (Y < 9) {
                             if (board[X - 1][Y + 2] == 1) {
							if (board[X][Y + 1] == 0 && board[X - 1][Y + 1] == 0) {
								new_x = X; new_y = Y + 1;
								break;
							}
							X = X - 1; Y = Y + 2;
						}
						else if (board[X - 2][Y + 1] == 1) {
							if (board[X - 1][Y] == 0 && board[X - 1][Y + 1] == 0) {
								new_x = X - 1;
								new_y = Y;
								break;
							}
							X = X - 2; Y = Y + 1;
						}
						}
						else if (Y == 9) {
							new_x = X;
							new_y = Y + 1;
							break;
						}
						
					}

				}
			}
		}
	}
	/***********在上方填充你的代码，决策结果（本方将落子的位置）存入new_x和new_y中****************/
	/************************************************************************************/

	// 向平台输出决策结果
	cout << new_x << ' ' << new_y << endl;
	return 0;
}
