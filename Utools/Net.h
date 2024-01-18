#pragma once
#pragma warning(disable : 4996) // 禁用不安全的函数警告
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include "Logger.h"
using namespace std;
//日志操作宏定义
#define EL Logger::instance.Error_Log
#define DL Logger::instance.Debug_Log
//链接ws2库
#pragma comment(lib,"ws2_32.lib")
//Net命名空间
namespace Net
{
	//地址类
	class Address
	{
	public:
		Address(string ip, int port);
		~Address();

	public:
		string ip;//ip地址
		int port;//端口号
		sockaddr_in sockaddr;
	};

	//基础套接字实现
	class Socket
	{
	public:
		Socket();
		Socket(SOCKET s);
		~Socket();

		void Bind(string ip, int port);//绑定ip和端口
		void Bind(Address addr);
		void Listen(int flag);//监听
		Socket Accept();//接受连接请求，返回连接对应客户端的套接字，阻塞
		void Connect(string ip, int port);//连接服务器
		void Connect(Address addr);
		void Send(const char* data, int size);//发送信息
		int Recv(char* data, int size);//接受信息，阻塞
		void Close();//关闭套接字

	protected:
		SOCKET sockfd;//套接字标识符
	};
}
