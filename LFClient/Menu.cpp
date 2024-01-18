#include "Menu.h"

void Menu::ShowMenu()
{
	string m[4] =
	{
		"1.登录文件源",
		"2.登录访问端",
		"3.退出程序",
		"" };
	for (int i = 0; m[i] != ""; i++)
	{
		cout << m[i];
		if (optionsNum == i)
		{
			cout << "<--";
		}
		cout << endl;
	}
}

int Menu::Judgement()
{
	int a = _getch();
	if (a == 115)
	{
		return 1;
	}
	else if (a == 119)
	{
		return -1;
	}
	else if (a == 13)
	{
		return 0;
	}
	return 2;
}

void Menu::Enteroption(int optionsNum)
{
	switch (optionsNum)
	{
	case 0:
		Login(FileSource);
		break;
	case 1:
		Login(FileSource);
		break;
	case 2:
		exit(0);
		break;
	default:
		break;
	}
}
void Menu::ControlMenu()
{
	switch (Judgement())
	{
	case 1:
		if (optionsNum == 2)
		{
			optionsNum = 0;
		}
		else
		{
			optionsNum++;
		}
		break;

	case -1:
		if (optionsNum == 0)
		{
			optionsNum = 2;
		}
		else
		{
			optionsNum--;
		}
		break;
	case 0:
		Enteroption(optionsNum);
		break; // 跳转到选项进入模块
	case 2:
		return;
	default:
		break;
	}
	system("cls");
	ShowMenu();
}

void Menu::Login(Identity idt)
{
	cout << ""
}

