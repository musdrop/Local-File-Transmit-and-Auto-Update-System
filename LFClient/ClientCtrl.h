#pragma once
#include "Utools\\Net.h"
#include "Utools\\fileSnd.h"
#include "Utools\\fileRcv.h"
#include <vector>
#include <queue>
#include <thread>
using namespace Net;
using namespace jeff;
//服务器ip端口
#define ServerIp "127.0.0.1"
#define ServerPort 7070
class Menu;
#define FListMesSegSize 630//
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
	Menu* clientMenu = NULL;
private:
	bool isLoggedIn = false;//是否登录
	bool isRunning = false;//客户端到服务器的连接是否运行中

	//等待文件接受结束
	bool isLast = false;//是否为最后一个包
	int lastSegmentSize = 0;
	int totalSize = 0;

	//等待发送
	bool isFile = false;//等待发送的是否为文件
	string waitforSendfileDir = "";//等待发送的文件路径
	char waitforSendkind = 0;//等待发送的长消息类型

	//等待登录响应
	int logInCode = 0;//-1为其他失败,0为未接受到响应,1为登录文件源成功，2为登录访问端成功，3为已有文件源，4为已有访问端

	//指令通信
	queue<TransmitSignal> commandsQue;//指令队列
	thread* commandsListen = NULL;//指令监听线程
	thread* commandsHandle = NULL;//指令处理线程
	Socket* commandSocket = NULL;//指令通道Socket

public:
	ClientCtrl();
	~ClientCtrl();
	int Login(int id, Identity idt);//登录
	void ExitLogin();//退出登录
	//请求区
	void UpdataListRequest();//发送更新列表请求
	void SendFileRequest(string filename);//发送文件请求
private:
	void SendLoginRequest(int id, Identity idt);//发送登录请求
	void SendCommand(TransmitSignal ts);//发送命令
	//回复区
	void FileReply(bool isFound, string filename = "");

	void CommandsListen();//指令监听线程
	void CommandsHandle();//指令处理线程

	void ToFileNameInList(char* buff, int length);//提取文件列表名
	void LongMessageRecv(int port, unsigned int segmentSize, char kind);//长消息接受线程
	void FileRecv(int port, FileRcv& fr);//文件接受线程

	void LongMessageSend(int port, char kind);//长消息发送线程
	void FileSend(int port, string fileDir);//文件发送线程
};