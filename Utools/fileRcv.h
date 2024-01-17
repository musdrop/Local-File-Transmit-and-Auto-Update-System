#pragma once
#ifndef FILERCV_H
#define FILERCV_H
#include"fileCtrl.h"
namespace jeff
{
	class fileRcvServer :public filePackage
	{

	};
	class fileRcvClient :public filePackage
	{
		std::string Cache;
	public:
		fileRcvClient(filePackage fileReceived);

	};
}
#endif