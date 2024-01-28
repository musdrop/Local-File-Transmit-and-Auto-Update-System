#include "Menu.h"
int main()
{
	//初始化DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{

		return 1;
	}
	Logger::instance.Initialize(true, false, "ClientLog.txt");
	ClientCtrl clientCtrl;
	Menu menu(&clientCtrl);
	menu.Start();
	return 0;
}