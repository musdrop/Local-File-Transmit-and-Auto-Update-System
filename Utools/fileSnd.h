#ifndef FILESND_H
#define FILESND_H
#include"FileCtrl.h"
namespace jeff
{
	class FileList
	{
		vector<pair<string, string>> allChosenDir;
		void Kick(string fileName);
		void TryOpen(string fileName);
	public:
		int TotalSize();
		void AddNewDir(string newDir);
		void RemoveDir(string existDir);
		string FindDir(string fileName);
	};

	class FileSnd:public FileSignal
	{
	public:
		FileSnd(string fileName);
	};
}
#endif