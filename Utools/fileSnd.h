#ifndef FILESND_H
#define FILESND_H
#include"fileCtrl.h"
namespace jeff
{
	class fileSndClient :public filePackage
	{
		User Owner;
		char signal;
	public:
		fileTransmit Snd();

	};
}
#endif