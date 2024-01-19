#include "ClientCtrl.h"


ClientCtrl::ClientCtrl()
{
}

ClientCtrl::~ClientCtrl()
{
}

//-2：登录访问端失败，已有访问端
//-1：登录文件源失败，已有文件源
//0：登录失败
//1：登录文件源成功
//2：登录访问端成功
int ClientCtrl::Login(int id, Identity idt, vector<string>& accessibleFies)
{
	return 0;
}

void ClientCtrl::RunSource()
{
}

void ClientCtrl::RunVisitor()
{
}

