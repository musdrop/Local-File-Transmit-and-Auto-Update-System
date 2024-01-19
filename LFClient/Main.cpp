#include "Menu.h"
int main()
{
	Logger::instance.Initialize(true, false);
	ClientCtrl clientCtrl;
	Menu menu(&clientCtrl);
	menu.Start();
	return 0;
}