#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
int main()
{
	int input = 0;
	welcome();//欢迎界面
	system("color f0");
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择：");
		scanf("%d", &input);
		system("cls");
		switch (input)
		{
		case 1:
			game();//进入游戏
			break;
		case 0:
			printf("退出游戏！\n");
			break;
		default:
			printf("输入错误！\n");
			break;
		}
	} while (input);
	system("pause");
	return 0;
}