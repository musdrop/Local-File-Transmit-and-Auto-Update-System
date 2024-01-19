#include "Menu.h"

Menu::Menu(ClientCtrl* clientCtrl)
{
	this->clientCtrl = clientCtrl;
	//加载菜单表
	//登录菜单
	vector<string> menu1;
	menu1.push_back("1.登录文件源");
	menu1.push_back("2.登录访问端");
	menu1.push_back("3.退出程序");
	menus.push_back(menu1);
	//文件源菜单
	vector<string> menu2;
	menus.push_back(menu2);
	//访问端菜单
	vector<string> menu3;
	menus.push_back(menu3);
	curm = &(menus[0]);
	menuNum = 0;
}

Menu::~Menu()
{
}

void Menu::Start()
{
	ShowMenu();
	while (true)
	{
		ControlMenu();
	}
}

void Menu::ShowMenu()
{
	for (int i = 0; i < curm->size(); i++)
	{
		cout << (*curm)[i];
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
		Login(FileVisitor);
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
		if (optionsNum == curm->size() - 1)
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
			optionsNum = curm->size() - 1;
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
	system("cls");
	cout << "请输入用户id：";
	char input;
	int num = 0;
	while (true)
	{
		input = _getch();
		// 如果是数字键，则输出数字
		if (isdigit(input))
		{
			if (input == '0' && num == 0)
			{
				continue;
			}
			if (num > 0)
			{
				num *= 10;
			}
			num += (input - '0');
			cout << input;
		}
		//回车键
		else if (input == 13)
		{
			//登录中
			if (num > 0)
			{
				Logining(num, idt);
				num = 0;
			}
		}
		//回退键
		else if (input == 8)
		{
			if (num > 0)
			{
				num /= 10;
				cout << "\b \b";
			}
		}
		//Esc键
		else if (input == 27) {
			break;
		}
	}
}

void Menu::Logining(int id, Identity idt)
{
	vector<string> accessibleFiles;
	cout << endl << "登录中..." << endl;
	int	logcode = clientCtrl->Login(id, idt, accessibleFiles);
	//失败类型
	if (logcode == -2)
	{
		cout << "登录访问端失败，已有访问端" << endl;
	}
	if (logcode == -1)
	{
		cout << "登录文件源失败，已有文件源" << endl;
	}
	if (logcode == 0)
	{
		cout << "登录失败" << endl;
	}
	//失败重试
	if (logcode <= 0)
	{
		cout << "任意键继续...";
		_getch();
		system("cls");
		cout << "请输入用户id：";
		return;
	}
	//登录成功
	if (logcode == 1)
	{

		clientCtrl->RunSource();
		cout << "登录文件源成功" << endl;
		Sleep(1000);
	}
	if (logcode == 2)
	{
		clientCtrl->RunVisitor();
		cout << "登录访问端成功" << endl;
		Sleep(1000);
	}
}

