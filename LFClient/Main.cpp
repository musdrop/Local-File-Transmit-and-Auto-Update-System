#include "Menu.h"
int main()
{
	Logger::instance.Initialize(true, false, "ClientLog.txt");
	ClientCtrl clientCtrl;
	Menu menu(&clientCtrl);
	menu.Start();
	return 0;
}