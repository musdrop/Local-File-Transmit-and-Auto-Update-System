#pragma once
#include "Utools\\Net.h"
#include <vector>
using namespace Net;
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
	Socket* commandSocket;
	Socket* fileSocket;
public:
	ClientCtrl();
	~ClientCtrl();
	int Login(int id, Identity idt, vector<string>& accessibleFies);//登录
	void RunSource();//文件源启动运行
	void RunVisitor();//访问端启动运行
};

