#pragma once
#include "Utools/Net.h"
#include "Utools/FileCtrl.h"
using namespace Net;
using namespace jeff;
using namespace std;
int main()
{
	//初始化DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{

		return 1;
	}
	Logger::instance.Initialize(true);

	Socket server;
	server.Bind("127.0.0.1", 7070);
	server.Listen(1024);
	while (true)
	{

		cout << "正在等待客户端连接" << endl;
		Socket conn = server.Accept();
		cout << "客户端已连接" << endl;
		TransmitSignal get;
		while (true)
		{
			int c = conn.Recv((char*)&get, sizeof(get));
			if (c <= 0)
			{
				break;
			}
			TransmitSignal ts;
			int kind;
			int id;
			get.GetContent(1, 4, (char*)&id);
			if (get.signal == sourceloginRequest)
			{
				cout << "登录id:" << id << endl;
				ts.signal = loginSuccess;
				kind = 1;
				ts.SetContent(1, 1, (char*)&kind);
				conn.Send((const char*)&ts, sizeof(ts));
				cout << "文件源登录请求，已回应";
			}
			else if (get.signal == visitorloginRequest)
			{
				cout << "登录id:" << id << endl;
				ts.signal = loginSuccess;
				kind = 2;
				ts.SetContent(1, 1, (char*)&kind);
				conn.Send((const char*)&ts, sizeof(ts));
				cout << "访问端登录请求，已回应";
				//回应文件列表请求
				//ts.signal = fileSourceNotExist;
				ts.signal = listIsEmpty;
				conn.Send((const char*)&ts, sizeof(ts));
			}
			else
			{
				conn.Close();
				cout << "未知连接,已中断处理";
				continue;
			}
		}
		cout << "断开连接" << endl;
	}
	system("pause");
}