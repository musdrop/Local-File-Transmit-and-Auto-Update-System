#pragma once
#ifndef  FILECTRL_H
#define FILECTRL_H
#define DL(x) Logger::instance.Debug_Log(x)
#define EL(x) Logger::instance.Error_Log(x)
#include"User.h"
#include"Logger.h"
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <vector>
//分段字节数宏
#define SEGMENT 1000
namespace jeff
{
	using namespace std;
	//跨平台编译
#if _WIN64 || _WIN32
	//windows32位和64位编译部分
#else
	//linux 编译部分
#endif
	//实际传输的结构体
	class TransmitSignal
	{
	public:
		char signal = 0;
		char fileName[60] = { '\0' };
		unsigned int fileByteSize = 0;
		unsigned int segmentSize = 0;
		void SetContent(int pos, int width, char* data);//字节层面向结构体内写入内容
		void GetContent(int pos, int width, char* data);//字节层面向结构体内提取内容
	};
	///
	/// fileName会将string转换为toCstr，这样可以节省string内的一些无必要指针的空间
	///
	enum InfSignal
	{
		visitorloginRequest,//用于客户端登录时向服务器发起：携带id
		sourceloginRequest,//用于客户端登录时向服务器发起：携带id
		fileRequest,//用于访问端尝试访问文件源文件时发起：携带文件名
		loginSuccess,//响应登录请求，携带成功登录的类型
		loginFail,//响应登录请求：携带失败原因

		sendFileRequest,//用于服务器与客户端之间任意一端打算向另一端发送文件时发起：请求方时服务器时携带监听的端口
		readyRecieve,//用于响应文件发送请求：响应方是服务器时携带文件通道监听的端口
		//客户端要发文件时向服务器请求，拿到携带端口号的响应根据端口号连接服务器建立文件通道
		//客户端要收文件时拿到的请求里携带服务器的端口号，同样以此建立文件通道

		sendWholeFile,//文件发送方发送完时使用：携带文件总字节数，最后一个包的有效字节数
		fileNotExist//用于文件源响应文件访问请求
	};
	class FileSignal
	{
	protected:
		char inf;//控制信息
		string fileName;//文件名称
		unsigned int fileByteSize;//总文件长度
		unsigned int segmentSize;//实际段长度

		char* fileInfor;//文件信息
	public:
		FileSignal();
		FileSignal(string newfileName);
		FileSignal(FileSignal& Obj);
		char GetSignal();
		string GetFileName();
		void operator[](unsigned char signal);//[] 运算符设置控制信息
		void operator>>(char** transmitCache);
		void operator>>(TransmitSignal& transmitCache);
	};
}
#endif