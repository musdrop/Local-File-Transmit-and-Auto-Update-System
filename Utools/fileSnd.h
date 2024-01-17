#ifndef FILESND_H
#define FILESND_H
#include"FileCtrl.h"
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