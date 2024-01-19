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
		//预打开
		bool TryOpen(string fileName, bool notNewFile = true);
	public:
		//获取文件列表长度
		int TotalSize();
		//新增文件
		void AddNewDir(string newDir);
		//删除文件
		void RemoveDir(string existDir);
		//根据文件名查找文件路径
		string FindDir(string fileName);
	};

	class FileSnd:public FileSignal
	{
	public:
		FileSnd(string fileName);
	};
}
#endif