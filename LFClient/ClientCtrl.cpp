#include "ClientCtrl.h"


ClientCtrl::ClientCtrl()
{
	isRunning = false;
	isLoggedIn = false;
	commandSocket = NULL;
	fileSocket = NULL;
	commandsListen = NULL;
}

ClientCtrl::~ClientCtrl()
{
	delete commandSocket;
	delete fileSocket;
	delete commandsListen;
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
	//创建登录请求，提交登录类型与id
	SendLoginRequest(id, idt);
	//建立指令监听线程
	isRunning = true;
	commandsListen = new thread(&ClientCtrl::CommandsListen, this);
	//等待...
	while (commandsQue.empty()) {}
	//拿到登录响应
	TransmitSignal ts = commandsQue.front();
	commandsQue.pop();
	char kind;//登录类型或失败原因
	ts.GetContent(1, 1, &kind);//提取登录类型或失败原因
	//登录成功
	if (ts.signal == loginSuccess)
	{
		if (kind == 0)//文件源
		{
			return 1;
		}
		else if (kind == 1)//访问端
		{
			return 2;
		}
	}
	//登录失败则根据失败信息直接返回失败码
	else
	{
		if (kind == 0)//已有文件源
		{
			return -1;
		}
		else if (kind == 1)//已有访问端
		{
			return -2;
		}
		else//其他
		{
			return 0;
		}
	}
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

void ClientCtrl::SendLoginRequest(int id, Identity idt)
{
	//创建消息
	TransmitSignal ts;
	//写入登录类型
	if (idt == FileVisitor)
	{
		ts.signal = visitorloginRequest;
	}
	else
	{
		ts.signal = sourceloginRequest;
	}
	//写入登录id
	ts.SetContent(1, 4, (char*)&id);
	//发送
	commandSocket->Send((const char*)&ts, sizeof(ts));
}

void ClientCtrl::CommandsListen()
{
	while (isRunning)
	{
		TransmitSignal ts;
		int recvCode = commandSocket->Recv((char*)&ts, sizeof(ts));
		if (recvCode <= 0)
		{
			break;
		}
		commandsQue.push(ts);
	}
}

