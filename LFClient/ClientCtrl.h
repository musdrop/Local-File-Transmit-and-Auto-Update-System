#pragma once
#include "Utools\\Net.h"
#include "Utools\\fileSnd.h"
#include <vector>
#include <queue>
#include <thread>
using namespace Net;
using namespace jeff;
//服务器ip端口
#define ServerIp "0"
#define ServerPort 0
//登录身份
enum Identity
{
	FileSource,
	FileVisitor
};
//客户端控制
class ClientCtrl
{
private:
	bool isLoggedIn;//是否登录
	bool isRunning;//客户端到服务器的连接是否运行中
	queue<TransmitSignal> commandsQue;//指令队列
	thread* commandsListen;//指令监听线程
	Socket* commandSocket;//指令通道Socket
	Socket* fileSocket;//文件通道Socket
public:
	ClientCtrl();
	~ClientCtrl();
	int Login(int id, Identity idt, vector<string>& accessibleFies);//登录
	void RunSource();//文件源启动运行
	void RunVisitor();//访问端启动运行

	void SendLoginRequest(int id, Identity idt);
	void CommandsListen();
};

