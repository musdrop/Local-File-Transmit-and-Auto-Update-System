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
	struct TransimtSignal
	{
		char signal=0;
		char fileName[60] = {'\0'};
		unsigned int fileByteSize=0;
		unsigned int segmentSize=0;
	};
	///
	/// fileName会将string转换为toCstr，这样可以节省string内的一些无必要指针的空间
	///
	enum class InfSignal
	{
		request = 1,
		confirm = 2, 
		fileNotExist=4
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
		FileSignal(FileSignal& Obj);
		void operator>>(char** transmitCache);
		void operator>>(TransimtSignal& transmitCache);
		~FileSignal();
	};
}
#endif