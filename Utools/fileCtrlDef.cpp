#include "FileCtrl.h"
#define FS  FileSignal
namespace jeff
{
	//TransmitSignal
	void TransmitSignal::SetContent(int pos, int width, char* data)
	{
		char* self = (char*)this;
		for (int i = pos; i < pos + width; i++)
		{
			self[i] = data[i - pos];
		}
	}
	void TransmitSignal::GetContent(int pos, int width, char* data)
	{
		char* self = (char*)this;
		for (int i = pos; i < pos + width; i++)
		{
			data[i - pos] = self[i];
		}
	}
	//FileSignal
	FileSignal::FileSignal()
		:inf(0), fileByteSize(0), segmentSize(0), fileInfor(NULL)
	{}
	FileSignal::FileSignal(string newfileName)
		:fileName(newfileName), inf(0), fileByteSize(0), segmentSize(0), fileInfor(NULL)
	{}
	FileSignal::FileSignal(FileSignal& Obj)
		:fileName(Obj.fileName), inf(Obj.inf)
		, fileByteSize(Obj.fileByteSize)
		, segmentSize(Obj.segmentSize)
		, fileInfor(Obj.fileInfor)
	{}
	void FileSignal::operator[](unsigned char signal)
	{
		this->inf = signal;
	}
	void FileSignal::Message(char newInf)
	{
		DL("向消息缓冲区写入控制信息");
		this->inf = newInf;
	}
	char FileSignal::GetSignal()
	{
		return inf;
	}
	string FileSignal::GetFileName()
	{
		return fileName;
	}
	void FileSignal::operator>>(char** transmitCache)
	{
		DL("将文件载入发送缓冲区");
		*transmitCache = fileInfor;
		DL(fileInfor);
	}
	void  FileSignal::operator>>(TransmitSignal& transmitCache)
	{
		DL("将文件指令信息载入发送缓冲区");
		strcpy_s(transmitCache.fileName, 60, fileName.c_str());
		transmitCache.signal = inf;
		transmitCache.fileByteSize = fileByteSize;
		transmitCache.segmentSize = segmentSize;
	}
	FileSignal::~FileSignal()
	{
		if (this->fileInfor)
			delete[]fileInfor;
	}
}