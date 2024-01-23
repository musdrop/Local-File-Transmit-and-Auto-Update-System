#pragma once
#include "Utools\\Net.h"
#include "Utools\\fileSnd.h"
#include <Utools\\fileRcv.h>
#include <vector>
#include <queue>
#include <thread>
#include "Menu.h"
using namespace Net;
using namespace jeff;
//服务器ip端口
#define ServerIp "0"
#define ServerPort 0
//登录身份
enum Identity
{
	None,
	FileSource,
	FileVisitor
};
//客户端控制
class ClientCtrl
{
public:
	Menu* clientMenu;
private:
	bool isLoggedIn = false;//是否登录
	bool isRunning = false;//客户端到服务器的连接是否运行中

	bool isLast = false;//是否为最后一个包
	int lastSegmentSize = 0;


	int logInCode = 0;//0为未接受到响应,1为登录文件源成功，2为登录访问端成功，3为已有文件源，4为已有访问端，5为其他失败

	queue<TransmitSignal> commandsQue;//指令队列
	thread* commandsListen = NULL;//指令监听线程
	thread* commandsHandle = NULL;//指令处理线程

	Socket* commandSocket = NULL;//指令通道Socket
	Socket* fileSocket = NULL;//文件通道Socket
public:
	ClientCtrl();
	~ClientCtrl();
	int Login(int id, Identity idt);//登录
	void RunSource();//文件源启动运行
	void RunVisitor();//访问端启动运行
	void ExitVistor();

	void UpdataListRequest();//发送更新列表请求
	void SendFileRequest(string filename);//发送文件请求
	void SendLoginRequest(int id, Identity idt);//发送登录请求
	void CommandsListen();//指令监听线程
	void CommandsHandle();//指令处理线程

	void ToFileNameInList(char* buff, int length);
	void LongMessageRecv(int port, unsigned int segmentSize, char kind);//长消息接受线程
	void FileRecv(int port, FileRcv& fr);//文件接受线程
};

