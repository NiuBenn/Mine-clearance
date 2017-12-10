#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void welcome()//初始化 欢迎界面
{
	printf("                                 \n");
	printf("        欢迎试玩扫雷游戏         \n");
	printf("      测试版 * 版本号 1.1.0      \n");
	printf("      制作人：  Edision Niu      \n");
	printf("*******游戏中如遇BUG请反馈*******\n");
	printf("                                 \n");
	printf("游戏已加载完毕，请按任意键继续......\n");
	getchar();
	system("cls");//清屏
}

void menu()//主菜单
{
	printf("********************************\n");
	printf("** 0.退出游戏 **** 1.开始游戏 **\n");
	printf("********************************\n");
}
void game()
{
	char Mineboard[ROWS][COLS] = { 0 };//用来存放雷的数组
	char Showboard[ROWS][COLS] = { 0 };//用来展示给玩家的
	printf("游戏开始：\n");
	InitBoard(Mineboard, ROWS,COLS,'0');
	InitBoard(Showboard, ROWS, COLS, '*');
	SetMine(Mineboard, ROW, COL, EASY_COUNT);//布置地雷
	ClearMine(Mineboard, Showboard, ROW, COL);//扫雷
}

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)//数组初始化
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void PrintBoard(char board[ROWS][COLS], int row, int col)//打印棋盘
{
	int i = 0;
	int j = 0;
	printf("  1   2   3   4   5   6   7   8   9  \n");
	printf("-------------------------------------\n");
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			printf("| %c ", board[i][j]);
		}
		printf("| %d\n",i);
		printf("|---|---|---|---|---|---|---|---|---|\n");
	}
}

void SetMine(char board[ROWS][COLS], int row, int col,int count)//布置雷（炸弹）
{
	int x = 0;
	int y = 0;
	while(count>0)
	{
	flag1:
		x = (rand() % 9) + 1;
		y = (rand() % 9) + 1;
		if (board[x][y] != '0')//判断当前区域是否已经布置过雷了
			goto flag1;//如果布置过了回到flag1处重新布置
		board[x][y] = '1';
		count--;
	}
}

void ClearMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)//扫雷
{
	int x = 0;
	int y = 0;
	int tmp = 0;//利用tmp来实现开局第一次踩??炸死
	while((Get(show))>10)//当剩余未知区域大于10执行循环进行扫雷
	{
		system("cls"); 
		printf("\n");
		PrintBoard(show, ROW, COL);
	flag:
		printf("请输入你要排雷的位置:");
		scanf("%d%d", &x, &y);//输入要扫的区域坐标
		if (x < 1 || x>9 || y < 1 || y>9)//对坐标进行判断
		{
			printf("您输入的位置不合法，请重新输入：\n");
			goto flag;//如果不合法重新输入
		}
		if (mine[x][y] == '1')
		{
			if (tmp == 0)
			{
				SetMine(mine, ROW, COL, 1);
				mine[x][y] = '0';
			}
			else
			{
				show[x][y] = '@';
				system("cls");
				PrintBoard(show, ROW, COL);
				printf("炸死了！游戏结束！\n");
				return 0;
			}
		}
		if (mine[x][y] == '0')
		{
			if (show[x][y] == '*')
			{
				if (GetMineCount(mine, x, y) == 0)
				{

					show[x][y] = ' ';
					spread(mine, show, x, y);
				}
				else
				{
					show[x][y] = '0' + GetMineCount(mine, x, y);//字符'0'加数字n等于字符'n',因为GetMineCount返回值为int所以加字符0
				}
			}
			else
			{
				printf("该位置已经扫过雷了，请重新输入：");//如果该坐标的值不为* 即该位置已经扫过雷了
				goto flag;//回到前面flag处再重新输入坐标
			}
		}
		tmp = 1;//进行过一次扫雷之后tmp的值赋为1
	}
	printf("扫雷成功！\n");//当跳出while循环时，即扫雷成功
}

int GetMineCount(char board[ROWS][COLS], int x, int y)//获取当前区域周围雷的个数
{
	int count = 0;
	count = (board[x - 1][y - 1] + board[x - 1][y] + board[x - 1][y + 1] + board[x][y + 1] + board[x + 1][y + 1] + board[x + 1][y] + board[x + 1][y - 1] + board[x][y - 1]) - 8 * '0';
	return count;
}

int Get(char board[ROWS][COLS])//获取未知区域的个数
{
	int i = 0;
	int j = 0;
	int count = 0;
	for (i = 1; i <= ROW; i++)
	{
		for (j = 1; j <= COL; j++)
		{
			if (board[i][j] == '*')
				count++;
		}
	}
	return count;
}

void spread(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y) //对周围无雷区域的展开
{

	int i = -1;
	int j = -1;
	for (i = -1; i <= 1; i++) //边界
	{
		for (j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0) // 避免排到自己注意此处的逻辑关系
			{
				if (x + i >= 1 && x + i <= ROW && y + j >= 1 && y + j <= COL) //x y坐标是否合法
				{
					if (show[x + i][y + j] == '*'&&mine[x + i][y + j] != '1')
					{

						int count = GetMineCount(mine, x + i, y + j);
						if (count != 0)
						{
							show[x + i][y + j] = count + '0';
						}
						else
						{
							show[x + i][y + j] = ' ';
							spread(mine, show, x + i, y + j);
						}

					}

				}
			}
		}
	}
}
