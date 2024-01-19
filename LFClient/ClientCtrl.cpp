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
	//尝试建立指令通道
	commandSocket = new Socket();
	if (!commandSocket->Connect(ServerIp, ServerPort))
	{
		return 0;
	}
	//创建登录请求，提交登录类型与id并等待返回信息
	//登录失败则根据失败信息直接返回失败码

	//登录成功
	// 
	//访问端：继续等待可访问文件的列表
	//获得列表并载入accessibleFies
	// 
	//文件源：
	// 
	//返回成功码
	Sleep(1000);
	return 0;
}

void ClientCtrl::RunSource()
{
}

void ClientCtrl::RunVisitor()
{
}

