#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "ClientCtrl.h"
using namespace std;
class Menu
{
private:
	int optionsNum = 0;// 选项编号
	vector<vector<string>> menus;//菜单表
	vector<string>* curm;//当前选中表
	int menuNum = 0;//菜单编号
	ClientCtrl* clientCtrl;//对客户端控制模块的引用
public:
	Menu(ClientCtrl* cliclientCtrl);
	~Menu();
	void Start();//程序入口
	void ShowMenu();// 打印菜单和对应选项后箭头
	int Judgement(); // 判断箭头移动方向或进入选项
	void Enteroption(int optionsNum); // 根据当前选项码进入对应功能模块
	void ControlMenu();// 主菜单箭头移动和选项控制
	//功能菜单实现
	void Login(Identity idt);
	void Logining(int id,Identity idt);

};

