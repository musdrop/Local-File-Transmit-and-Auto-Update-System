#include"FileCtrl.h"
#include <vector>
#define FP filePackage::
#define FT fileType::
using namespace std;
namespace jeff
{
	FP filePackage()
		:suffix(FT none), byteSize(0), fileInfor(NULL)
	{}
	FP filePackage(filePackage& Obj)
		: suffix(Obj.suffix), fileName(Obj.fileName), byteSize(Obj.byteSize), fileInfor(Obj.fileInfor)
	{}
	FP filePackage(string givenFileName)
	{
		Construct(givenFileName);
	}
	void FP fileNotExist()
	{
		fileName.clear();
		suffix = fileType::none;
		byteSize = 0;
		if (fileInfor)
			delete[] fileInfor;
	}
	void FP makeSuffix(string givenSuffix)
	{
		if (givenSuffix == "txt")
			suffix = fileType::txt;
		else if (givenSuffix == "pdf")
			suffix = fileType::pdf;
		else if (givenSuffix == "docx" || givenSuffix == "doc")
			suffix = fileType::word;
		else if (givenSuffix == "pptx" || givenSuffix == "ppt" || givenSuffix == "ppsx")
			suffix = fileType::ppt;
		else if (givenSuffix == "xlsx" || givenSuffix == "xls")
			suffix = fileType::excel;
		else if (givenSuffix == "zip")
			suffix = fileType::zip;
	}
	void FP splitFileName(string givenFileName)
	{
		int offset = givenFileName.find('.');
		if (offset >= 1)
		{
			fileName = givenFileName.substr(0, offset);
			makeSuffix(givenFileName.substr(offset + 1, givenFileName.size() - 1));
		}
	}
	void FP Construct(string givenFileName)
	{
		if (this->byteSize == 0)
		{
			struct stat fileInforCache;
			// �ṩ�ļ����ַ���������ļ����Խṹ��
			stat(givenFileName.c_str(), &fileInforCache);
			this->byteSize = fileInforCache.st_size;
		}
		vector<char> tempFileInfor;
		char tempCharInfor;
		if (this->fileName.size() == 0)
		{
			splitFileName(givenFileName);
		}
		fstream file(givenFileName, ios::in);
		for (int n = 0; n < (int)suffix; ++n)
		{
			file >> tempCharInfor;
			tempFileInfor.push_back(tempCharInfor);
			if (file.eof())
			{
				file.close();
				break;
			}
		}
		if (tempFileInfor.size() > 0)
		{
			this->fileInfor = new char[byteSize];
			for (int n = 0; n < (int)suffix; ++n)
				fileInfor[n] = tempFileInfor[n];
		}
		else
			fileNotExist();
	}
	FP ~filePackage()
	{
		if (fileInfor != NULL)
			delete[] fileInfor;
	}
}