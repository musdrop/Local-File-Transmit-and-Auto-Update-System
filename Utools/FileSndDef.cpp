#include "FileSnd.h"
#define FILECLEAR(x) for(int n =0;n<SEGMENT;++n)x[n]=0;
namespace jeff
{
	void FileList::Kick(string fileName)
	{
		for (int n = 0; n < this->allChosenDir.size(); ++n)
		{
			if (allChosenDir[n].first == fileName)
				allChosenDir.erase(allChosenDir.begin() + n);
		}
		EL("从文件列表中删除"+fileName);
	}
	bool FileList::TryOpen(string fileName,bool notNewFile)
	{
		ifstream file(fileName);
		if (file.good())
		{
			file.close();
			DL("文件预打开成功");
			return true;
		}
		else
		{
			file.close();
			EL("文件预打开失败");
			if(notNewFile)
				Kick(fileName);
			return false;
		}
	}
	int FileList::TotalSize()
	{
		return this->allChosenDir.size();
	}
	void FileList::AddNewDir(string newDir)
	{
		DL("正在处理文件路径");
		pair<string, string>tempPair;
		if (TryOpen(newDir,false))
		{
			tempPair.second = newDir;
			DL("文件路径写入成功");
			int pos = newDir.find_last_of('\\')+1;
			DL("正在解析文件名称");
			if (pos > 0)
			{
				tempPair.first = newDir.substr(pos, newDir.size() - 1);
				DL("文件名称写入成功");
				this->allChosenDir.push_back(tempPair);
			}
			else
			{
				EL("文件名称解析失败，进行二次解析");
				pos = newDir.find_last_of('/')+1;
				if (pos > 0)
				{
					tempPair.first = newDir.substr(pos, newDir.size() - 1);
					DL("文件名称写入成功");
					this->allChosenDir.push_back(tempPair);
				}
				else
					EL("文件名称解析失败");
			}
		}
		else
			EL("文件路径无效或文件不存在");
	}
	void FileList::RemoveDir(string existDir)
	{
		for (int n = 0; n < this->allChosenDir.size(); ++n)
		{
			if (allChosenDir[n].second == existDir)
			{
				DL("从列表中移出" + existDir);
				allChosenDir.erase(allChosenDir.begin() + n);
				break;
			}
		}
	}
	string FileList::FindDir(string fileName)
	{
		for (int n = 0; n < allChosenDir.size(); ++n)
		{
			if (allChosenDir[n].first == fileName)
				return allChosenDir[n].second;
		}
		return "not found";
	}
	string FileList::operator[](string fileName)
	{
		return FindDir(fileName);
	}


	FileSnd::FileSnd(string newfileName):FileSignal(newfileName),lastPos(0)
	{
		file.open(newfileName,ios::binary);
		struct stat temp;
		stat(newfileName.c_str(), &temp);
		this->fileByteSize = temp.st_size;
		if (!file.good())
		{
			file.close();
			EL("文件不存在或文件路径无效");
		}
	}
	void FileSnd::Prepare()
	{
		DL("正在准备文件发送");
		if (fileInfor)
			delete[] fileInfor;
		DL("新建文件发送缓冲区");
		fileInfor = new char[SEGMENT];
		int n = 0;
		for(;n<SEGMENT&&!file.eof();++n)
			file >> fileInfor[n];
		if (file.eof())
			lastPos += n,segmentSize = n;
		else
			lastPos += SEGMENT, segmentSize = SEGMENT;
	}
	void FileSnd::Message(char newMessage)
	{
		DL("向消息缓冲区写入控制信息");
		this->inf = newMessage;
	}
	int FileSnd::FileLeft()
	{
		DL("计算文件未发送部分长度");
		return this->fileByteSize - lastPos;
	}
	FileSnd::~FileSnd()
	{
		file.close();
	}
}