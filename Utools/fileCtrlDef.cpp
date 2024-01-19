#include"FileCtrl.h"
#define FS  FileSignal
namespace jeff
{
	FileSignal::FileSignal()
		:inf(0), fileByteSize(0), segmentSize(0), fileInfor(NULL)
	{}
	FileSignal::FileSignal(FileSignal& Obj)
		:fileName(Obj.fileName), inf(Obj.inf)
		, fileByteSize(Obj.fileByteSize)
		, segmentSize(Obj.segmentSize)
		, fileInfor(Obj.fileInfor)
	{}
	void FileSignal::operator>>(char** transmitCache)
	{
		DL("将文件载入缓冲区");
		*transmitCache = fileInfor;
	}
	void  FileSignal::operator>>(TransimtSignal& transmitCache)
	{
		DL("将文件指令信息载入缓冲区");
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