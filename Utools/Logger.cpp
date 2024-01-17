#include "Logger.h"
Logger Logger::instance;//实例
Logger::Logger()
{

}

Logger::~Logger()
{
	Debug_Log("---程序停止运行---");
	logfile.close();
}

void Logger::Initialize(bool isRestart, string filename)
{
	if (isRestart)
	{
		//重新记录日志文件
		logfile.open(filename);
	}
	else
	{
		//追加到日志文件末尾
		logfile.open(filename, std::ios::app);
	}
	if (!logfile)
	{
		//日志文件加载失败
		exit(1);
	}
	Debug_Log("---程序开始运行---");
}

void Logger::Debug_Log(string log_info)
{
	// 获取当前时间
	auto now = std::chrono::system_clock::now();
	time_t now_c = std::chrono::system_clock::to_time_t(now);
	//输出日志信息
	logfile << ctime(&now_c) << "|DEBUG:" << log_info << std::endl;
	cout << ctime(&now_c) << "|DEBUG:" << log_info << std::endl;
}

void Logger::Error_Log(string log_info)
{
	// 获取当前时间
	auto now = std::chrono::system_clock::now();
	time_t now_c = std::chrono::system_clock::to_time_t(now);
	//输出日志信息
	logfile << ctime(&now_c) << "|ERROR:" << log_info << std::endl;
	cout << ctime(&now_c) << "|ERROR:" << log_info << std::endl;
}
