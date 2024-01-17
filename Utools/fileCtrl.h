#pragma once
#ifndef  FILECTRL_H
#define FILECTRL_H
#include"User.h"
#include <string>
#include <fstream>
#include <sys/stat.h>
size_t getFileSize1(const char* fileName) {

	if (fileName == NULL) {
		return 0;
	}
	struct stat statbuf;
	// 提供文件名字符串，获得文件属性结构体
	stat(fileName, &statbuf);
	// 获取文件大小
	size_t filesize = statbuf.st_size;
	return filesize;
}
namespace jeff
{
	//跨平台编译
#if _WIN64 || _WIN32
	//windows32位和64位编译部分
#else
	//linux 编译部分
#endif
	 //文件分类，枚举量的值可以是单个传输的宽度或者其他的 unsigned int 的值
	enum class fileType
	{
		none=0,

		txt,
		pdf,

		word,
		ppt,
		excel,

		zip
	};
	//实际传输的结构体
	struct fileTransmit
	{
		const char* fileName;
		unsigned int segmentSize;
		unsigned int totalSize;
		char* fileInfor;
	};
	///
	/// fileName会将string转换为toCstr，这样可以节省string内的一些无必要指针的空间
	///


	//文件打包类
	class filePackage
	{
	protected:
		std::string fileName;
		fileType suffix;
		unsigned long long byteSize;
		char* fileInfor;
	private:
		void fileNotExist();
		//将后缀从string转为fileType
		void makeSuffix(std::string);
		//将后缀和文件名称分开
		void splitFileName(std::string);
		//
		//自动调用makeSuffix
		//
	public:
		filePackage();
		filePackage(filePackage&);
		//将文件创建为打包对象
		void Construct(std::string);
		filePackage(std::string);
		~filePackage();
	};
	///
	/// 不负责实现发送打包和接受打包，这由子类fileSend和fileReceive实现
	///
}
#endif