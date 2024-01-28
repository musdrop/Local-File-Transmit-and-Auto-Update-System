#include "Menu.h"

Menu::Menu(ClientCtrl* clientCtrl)
{
	//菜单与控制部分互相绑定
	this->clientCtrl = clientCtrl;
	clientCtrl->clientMenu = this;
	//加载菜单
	//登录菜单
	mainMenu.push_back("1.登录文件源");
	mainMenu.push_back("2.登录访问端");
	mainMenu.push_back("3.退出程序");
	//访问端菜单
	visitorMenu.push_back("1.访问文件");
	visitorMenu.push_back("2.更新列表");
	visitorMenu.push_back("3.退出登录");
	//文件源菜单
	sourceMenu.push_back("1.订阅文件");
	sourceMenu.push_back("2.移除订阅");
	sourceMenu.push_back("3.退出登录");
	curm = &mainMenu;
}

Menu::~Menu()
{
}

void Menu::Start()
{
	ShowMenu();
	while (true)
	{
		ControlMainMenu();
	}
}

void Menu::StartSource()
{
	system("cls");
	curm = &sourceMenu;

	cout << "当前无订阅文件..." << endl;
	ShowMenu();
	while (true)
	{
		bool isExit = false;
		switch (Judgement())
		{
		case 1:
			if (optionsNum == mainMenu.size() - 1)
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
				optionsNum = mainMenu.size() - 1;
			}
			else
			{
				optionsNum--;
			}
			break;
		case 0:
			if (optionsNum == 0)
			{
				//订阅文件
				cout << "请输入文件路径：";
				string a;
				getline(cin, a);
				if (a == "")
				{
					break;
				}
				if (flist.AddNewDir(a))
				{
					cout << "订阅文件成功" << endl;
				}
				else
				{
					cout << "订阅文件失败" << endl;
				}
				Sleep(1000);
			}
			else if (optionsNum == 1)
			{
				//删除文件
				cout << "请输入文件名：";
				string a;
				getline(cin, a);
				if (a == "")
				{
					break;
				}
				flist.RemoveDir(flist[a]);
				cout << "已移除" << endl;
				Sleep(1000);
			}
			else if (optionsNum == 2)
			{
				//客户端退出登录
				clientCtrl->ExitLogin();
				isExit = true;
			}
			break;
		case 2:
			break;
		default:
			break;
		}
		if (isExit)
		{
			curm = &mainMenu;
			break;
		}
		system("cls");
		if (flist.TotalSize() > 0)
		{
			cout << "已订阅的文件如下：" << endl;
		}
		else
		{
			cout << "当前无订阅文件..." << endl;
		}
		flist.PrintFileNames();
		ShowMenu();
	}
}

void Menu::StartVisitor()
{
	while (true)
	{
		system("cls");
		cout << "正在尝试获取可访问文件列表..." << endl;
		//等待
		while (!gotListCode) {}
		if (gotListCode == 3)
		{
			cout << "无文件源" << endl;
		}
		else if (gotListCode == 2)
		{
			cout << "暂无可访问的文件" << endl;
		}
		//重试
		if (gotListCode == -1 || gotListCode > 1)
		{
			gotListCode = 0;
			cout << "回车可再次尝试获取可访问文件列表...";
			char input;
			while (true)
			{
				input = _getch();
				if (input == 13 || input == 27)
				{
					break;
				}
			}
			if (input == 13)
			{
				clientCtrl->UpdataListRequest();
				continue;
			}
			else if (input == 27)
			{
				clientCtrl->ExitLogin();
				break;
			}
		}
		//成功获得列表
		if (gotListCode == 1)
		{
			gotListCode = 0;
			curm = &visitorMenu;
			system("cls");
			cout << "可访问的文件有：" << endl;
			for (int i = 0; i < accessibleFiles.size(); i++)
			{
				cout << accessibleFiles[i] << endl;
			}
			ShowMenu();
			while (true)
			{
				bool isExit = false;
				ControlVisitorMenu(isExit);
				if (isExit)
				{
					curm = &mainMenu;
					break;
				}
			}
		}
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

void Menu::ControlMainMenu()
{
	switch (Judgement())
	{
	case 1:
		if (optionsNum == mainMenu.size() - 1)
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
			optionsNum = mainMenu.size() - 1;
		}
		else
		{
			optionsNum--;
		}
		break;
	case 0:
		if (optionsNum == 0)
		{
			Login(FileSource);
		}
		else if (optionsNum == 1)
		{
			Login(FileVisitor);
		}
		else if (optionsNum == 2)
		{
			exit(0);
		}
		break;
	case 2:
		return;
	default:
		break;
	}
	system("cls");
	ShowMenu();
}

void Menu::ControlVisitorMenu(bool& isExit)
{
	switch (Judgement())
	{
	case 1:
		if (optionsNum == visitorMenu.size() - 1)
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
			optionsNum = visitorMenu.size() - 1;
		}
		else
		{
			optionsNum--;
		}
		break;
	case 0:
		//执行选项函数
		if (optionsNum == 0)
		{
			FileRequest();
		}
		else if (optionsNum == 1)
		{
			UpdataList();
		}
		else if (optionsNum == 2)
		{
			//客户端退出登录
			clientCtrl->ExitLogin();
			isExit = true;
		}
		break;
	case 2:
		return;
	default:
		break;
	}
	system("cls");
	cout << "可访问的文件有：" << endl;
	for (int i = 0; i < accessibleFiles.size(); i++)
	{
		cout << accessibleFiles[i] << endl;
	}
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
				if (isLoggedIn)
				{
					break;
				}
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
	cout << endl << "登录中..." << endl;
	int	logcode = clientCtrl->Login(id, idt);
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
	isLoggedIn = true;
	this->id = id;
	optionsNum = 0;
	if (logcode == 1)
	{
		curIdt = FileSource;
		cout << "登录文件源成功" << endl;
		Sleep(1000);
		StartSource();
	}
	if (logcode == 2)
	{
		curIdt = FileVisitor;
		cout << "登录访问端成功" << endl;
		Sleep(1000);
		StartVisitor();
	}
}

void Menu::FileRequest()
{
	while (true)
	{
		system("cls");
		cout << "可访问的文件有：" << endl;
		for (int i = 0; i < accessibleFiles.size(); i++)
		{
			cout << accessibleFiles[i] << endl;
		}
		cout << "请输入文件名(无输入时回车返回菜单)：";
		string input;
		getline(cin, input);
		if (input == "")
		{
			break;
		}
		auto it = find(accessibleFiles.begin(), accessibleFiles.end(), input);
		if (it == accessibleFiles.end())
		{
			cout << "该文件不在可访问列表中" << endl
				<< "按任意键继续...";
			_getch();
			continue;
		}
		gotFileCode = 0;
		clientCtrl->SendFileRequest(input);
		cout << "正在获取文件..." << endl;
		//等待文件
		while (!gotFileCode) {}
		if (gotFileCode == 3)
		{
			cout << "无文件源" << endl;
		}
		else if (gotFileCode == 2)
		{
			cout << "未找到该文件" << endl;
		}
		if (gotFileCode == -1 || gotFileCode > 1)
		{
			cout << "按任意键继续...";
			_getch();
			break;
		}
		if (gotFileCode == 1)
		{
			cout << "成功获取文件" << input << endl;
			cout << "按任意键继续...";
			_getch();
			break;
		}
	}
}

void Menu::UpdataList()
{
	gotListCode = 0;
	clientCtrl->UpdataListRequest();
	while (true)
	{
		system("cls");
		cout << "正在尝试获取可访问文件列表..." << endl;
		//等待
		while (!gotListCode) {}
		if (gotListCode == 3)
		{
			cout << "无文件源" << endl;
		}
		else if (gotListCode == 2)
		{
			cout << "暂无可访问的文件" << endl;
		}
		//重试
		if (gotListCode == -1 || gotListCode > 1)
		{
			gotListCode = 0;
			cout << "回车可再次尝试获取可访问文件列表...";
			char input;
			while (true)
			{
				input = _getch();
				if (input == 13 || input == 27)
				{
					break;
				}
			}
			if (input == 13)
			{
				clientCtrl->UpdataListRequest();
				continue;
			}
			else if (input == 27)
			{
				clientCtrl->ExitLogin();
				break;
			}
		}
		//成功获得列表
		if (gotListCode == 1)
		{
			cout << "成功更新列表" << endl;
			Sleep(1000);
			break;
		}
	}
}

void Menu::AddtoList(string name)
{
	accessibleFiles.push_back(name);
}

void Menu::ClearList()
{
	accessibleFiles.clear();
}