#pragma once
#pragma warning(disable : 4996) // 禁用不安全的函数警告
#include <fstream>
#include <chrono>
#include <iostream>
#include <string>
using namespace std;
class Logger
{
public:
	static Logger instance;//实例
private:
	ofstream logfile;//日志文件流对象
	bool isConsoleOn;
public:
	Logger();
	~Logger();
	//运行程序时在主函数入口出执行(建议执行：Logger::instance.Initialize(true);）
	void Initialize(bool isRestart, bool isConsoleOn = true, string filename = "LogMessage.txt");//日志初始化
	void Debug_Log(string log_info);
	void Error_Log(string log_info);
};

