#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "ClientCtrl.h"
class Menu
{
public:
	//监听文件列表请求的回应
	int gotListCode = 0;//0为还未收到响应，1为收到可访问文件列表，2为可访问列表为空，3为无文件源，-1为其他错误
	//监听文件请求的回应
	int gotFileCode = 0;//0为还未收到响应，1为收到文件，2为未找到文件，3为无文件源，4为未连接到服务器，-1为其他错误
	FileList flist;//文件源文件列表
private:
	vector<string> accessibleFiles;//可访问文件列表
	bool isLoggedIn = false;//是否登录
	Identity curIdt = None;//当前登录身份
	int	id = 0;//登录id

	//菜单部分
	int optionsNum = 0;// 选项编号
	vector<string> mainMenu;
	vector<string> visitorMenu;
	vector<string> sourceMenu;
	vector<string>* curm = NULL;


	ClientCtrl* clientCtrl;//对客户端控制模块的引用
public:
	Menu(ClientCtrl* cliclientCtrl);
	~Menu();
	void Start();//程序入口
	//调用,处理fist
	void AddtoList(string name);
	void ClearList();
private:
	void StartSource();//文件源入口，控制和功能实现均集成在入口中
	void StartVisitor();//访问端入口

	void ControlMainMenu();// 主菜单箭头移动和选项控制
	void ControlVisitorMenu(bool& isExit);//访问端菜单控制

	void ShowMenu();// 打印菜单和对应选项后箭头
	int Judgement(); // 判断箭头移动方向

	//登录
	void Login(Identity idt);
	void Logining(int id, Identity idt);

	//访问端功能实现
	//请求文件
	void FileRequest();
	//更新列表
	void UpdataList();
};