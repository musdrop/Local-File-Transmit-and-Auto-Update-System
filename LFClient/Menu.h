#pragma once
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
enum Identity
{
	FileSource,
	FileVisitor
};
class Menu
{
private:
	int optionsNum = 0;// 选项编号
public:
	void ShowMenu();// 打印菜单和对应选项后箭头
	int Judgement(); // 判断箭头移动方向或进入选项
	void Enteroption(int optionsNum); // 根据当前选项码进入对应功能模块
	void ControlMenu();// 主菜单箭头移动和选项控制
	//功能实现
	void Login(Identity idt);

};

