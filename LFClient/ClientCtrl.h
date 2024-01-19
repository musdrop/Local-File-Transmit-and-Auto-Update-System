#pragma once
#include "Utools\\Net.h"
#include <vector>
enum Identity
{
	FileSource,
	FileVisitor
};
class ClientCtrl
{
private:

public:
	ClientCtrl();
	~ClientCtrl();
	int Login(int id, Identity idt, vector<string>& accessibleFies);//登录
	void RunSource();//文件源启动运行
	void RunVisitor();//访问端启动运行
};

