#pragma once
#ifndef FILERCV_H
#define FILERCV_H
#include"FileCtrl.h"
namespace jeff
{
	class FileRcv :public FileSignal
	{
		ofstream file;
	public:
		FileRcv(TransmitSignal);
		void Receive(char* fileInfor, int segmentLen = -1);
		bool End(int lastSize);
		~FileRcv();
	};
}
#endif