#ifndef FILESND_H
#define FILESND_H
#include"FileCtrl.h"
namespace jeff
{
	class FileList
	{
	private:
		vector<pair<string, string>> allChosenDir;//fileName+fileDir
		//根据文件名移除
		void Kick(string fileName);
	public:
		//预打开
		bool TryOpen(string fileDir, bool notNewFile = true);
		//获取文件列表长度
		int TotalSize();
		//新增文件
		bool AddNewDir(string newDir);
		//删除文件
		void RemoveDir(string existDir);
		//根据文件名查找文件路径
		string FindDir(string fileName);
		string operator[](string);
		//获取名单列表
		vector<string> GetNamesList();
		void Save();
		void PrintFileNames();
	};

	class FileSnd :public FileSignal
	{
		ifstream file;
	public:
		int lastsegmentSize;
		FileSnd(string);
		void SetSegmentSize(int size);
		bool Prepare();
		void Close();
		~FileSnd();
	};
}
#endif