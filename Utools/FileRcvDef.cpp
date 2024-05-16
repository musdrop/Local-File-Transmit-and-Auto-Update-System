#include"FileRcv.h"

namespace jeff {
	FileRcv::FileRcv(TransmitSignal inforReceived) {
		inf = inforReceived.signal;
		string fileName = inforReceived.fileName;
		this->fileName = fileName;
		this->segmentSize = inforReceived.segmentSize;
		file.open(fileName, ios::binary);
	}

	void FileRcv::Receive(char* fileInfor, int segmentLen) {
		if (segmentLen == -1) {
			segmentLen = segmentSize;
		}
		this->fileByteSize += segmentLen;
		file.write(fileInfor, segmentLen);
		DL("接收到文件并进行写入");
	}

	bool FileRcv::End(int lastSize) {
		if (this->fileByteSize == lastSize) {
			DL("文件接受成功");
			file.close();
			return true;
		}
		else {
			DL("文件存在传输丢失，文件传输失败，请求重传");
			this->inf = InfSignal::resendFileRequest;
			file.close();
			return false;
		}
	}

	FileRcv::~FileRcv() {
		file.close();
	}
}
