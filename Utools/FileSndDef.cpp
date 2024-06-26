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
		EL("从文件列表中删除" + fileName);
	}
	bool FileList::TryOpen(string fileDir, bool notNewFile)
	{
		ifstream file(fileDir);
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
			if (notNewFile)
				RemoveDir(fileDir);
			return false;
		}
	}
	int FileList::TotalSize()
	{
		return this->allChosenDir.size();
	}
	bool FileList::AddNewDir(string newDir)
	{
		DL("正在处理文件路径");
		pair<string, string>tempPair;
		if (TryOpen(newDir, false))
		{
			tempPair.second = newDir;
			DL("文件路径写入成功");
			int pos = newDir.find_last_of('\\') + 1;
			DL("正在解析文件名称");
			if (pos > 0)
			{
				tempPair.first = newDir.substr(pos, newDir.size() - 1);
				DL("文件名称写入成功");
				this->allChosenDir.push_back(tempPair);
				return true;
			}
			else
			{
				EL("文件名称解析失败，进行二次解析");
				pos = newDir.find_last_of('/') + 1;
				if (pos > 0)
				{
					tempPair.first = newDir.substr(pos, newDir.size() - 1);
					DL("文件名称写入成功");
					this->allChosenDir.push_back(tempPair);
					return true;
				}
				else
				{
					EL("文件名称解析失败");
					return false;
				}
			}
		}
		else
		{
			EL("文件路径无效或文件不存在");
			return false;
		}
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

	vector<string> FileList::GetNamesList()
	{
		vector<string> nl;
		for (int i = 0; i < allChosenDir.size(); i++)
		{
			nl.push_back(allChosenDir[i].first);
		}
		return nl;
	}

	void FileList::PrintFileNames()
	{
		for (int i = 0; i < allChosenDir.size(); i++)
		{
			cout << allChosenDir[i].first << endl;
		}
	}


	FileSnd::FileSnd(string fileDir)
	{
		file.open(fileDir, ios::binary);
		if (!file.good())
		{
			file.close();
			EL("文件不存在或文件路径无效");
		}
	}
	void FileSnd::SetSegmentSize(int size)
	{
		segmentSize = size;
	}
	bool FileSnd::Prepare()
	{
		DL("正在准备文件发送");
		if (fileInfor)
			delete[] fileInfor;
		DL("新建文件发送缓冲区");
		fileInfor = new char[SEGMENT];
		//一次读入一个包
		file.read(fileInfor, SEGMENT);
		//获取最近一次读写操作的实际读取字节数
		int n = file.gcount();
		this->fileByteSize += n;
		if (n < segmentSize)
		{
			lastsegmentSize = n;
			return false;
		}
		else
		{
			return true;
		}
	}
	void FileSnd::Close()
	{
		file.close();
	}
	FileSnd::~FileSnd()
	{
		file.close();
	}
}