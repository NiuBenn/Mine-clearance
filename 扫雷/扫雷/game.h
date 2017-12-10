#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10
#define HARD_COUNT 20

void welcome();//初始化
void menu();//主菜单
void game();//游戏菜单
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);//数组初始化
void PrintBoard(char board[ROWS][COLS], int row, int col);//打印棋盘
void SetMine(char board[ROWS][COLS], int row, int col,int count);//布置雷（炸弹）
void ClearMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);//扫雷
int GetMineCount(char board[ROWS][COLS], int x, int y);//获取当前区域周围雷的个数
int Get(char board[ROWS][COLS]);//获取未知区域的个数
void spread(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);//对周围无雷区域的展开

#endif //__GAME_H__
