#pragma once
#include<vector>
#include<string>
#include"ServerFile.h"
#include"JeffStructures.h"
using namespace std;
namespace jeff
{
	class Connection
	{
		int id;
		//文件发送端和文件接受端
		pair<bool, bool> newSndMsg_newRcvMsg;
		pair<char, char> fileSnd_fileRcv;
	public:
		Connection();
		Connection(int existId);
		void WriteSnd(char newSignal);
		void WriteRcv(char newSignal);
		bool IsNewMessage(bool isSnd);
		int GetId();
		char GetSnd();
		char GetRcv();
		bool operator==(Connection& Obj);
	};
	class Core
	{
		Chain<Connection> pool;
	public:
		//获取一个分配好的连接区
		Connection* New(int id=0);
		//摧毁一个分配好的连接区
		void Delete(Connection*);
		//根据id找到存在的连接区
		Connection* Find(int id);
	};
}

