#pragma once
#ifndef USER_H
#define USER_H
namespace jeff
{
	class User
	{
	private:
		const char userName[20] = { '\0' };
		const char password[20] = { '\0' };
		int id;
	public:
		User();

	};
}
#endif