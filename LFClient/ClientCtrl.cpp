#include "Menu.h"


ClientCtrl::ClientCtrl()
{
}

ClientCtrl::~ClientCtrl()
{
	delete commandSocket;
	delete commandsListen;
	delete commandsHandle;
}

/*
-2：登录访问端失败，已有访问端
-1：登录文件源失败，已有文件源
0：登录失败
1：登录文件源成功
2：登录访问端成功
*/
int ClientCtrl::Login(int id, Identity idt)
{
	//尝试建立指令通道
	commandSocket = new Socket();
	if (!commandSocket->Connect(ServerIp, ServerPort))
	{
		return 0;
	}
	//创建登录请求，提交登录类型与id
	SendLoginRequest(id, idt);
	//建立指令监听线程
	isRunning = true;
	commandsListen = new thread(&ClientCtrl::CommandsListen, this);
	DL("已建立指令监听线程");
	//建立指令处理线程
	commandsHandle = new thread(&ClientCtrl::CommandsHandle, this);
	DL("已建立指令处理线程");
	//等待...
	logInCode = 0;
	DL("等待登录码更新中");
	while (!logInCode) {}
	//拿到登录响应
	DL("成功获取登录码");
	//登录成功
	if (logInCode == 1)//文件源
	{
		isLoggedIn = true;
		return 1;
	}
	else if (logInCode == 2)//访问端
	{
		isLoggedIn = true;
		return 2;
	}
	//登录失败则根据失败信息直接返回失败码
	else if (logInCode == 3)//已有文件源
	{
		return -1;
	}
	else if (logInCode == 4)//已有访问端
	{
		return -2;
	}
	else if (logInCode == 5)//错误
	{
		return 0;
	}
}

void ClientCtrl::ExitLogin()
{
	isRunning = false;
	isLoggedIn = false;
	isLast = false;
	lastSegmentSize = 0;
	logInCode = 0;

	commandSocket->Close();
	commandSocket = NULL;

	commandsListen = NULL;
	commandsHandle = NULL;
}

void ClientCtrl::UpdataListRequest()
{
	TransmitSignal ts;
	ts.signal = updataListRequest;
	SendCommand(ts);
}

void ClientCtrl::SendFileRequest(string filename)
{
	TransmitSignal ts;
	ts.signal = fileRequest;
	for (int i = 0; i < filename.size(); i++)
	{
		ts.fileName[i] = filename[i];
	}
	SendCommand(ts);
}

void ClientCtrl::SendLoginRequest(int id, Identity idt)
{
	//创建消息
	TransmitSignal ts;
	//写入登录类型
	if (idt == FileVisitor)
	{
		ts.signal = visitorloginRequest;
	}
	else
	{
		ts.signal = sourceloginRequest;
	}
	//写入登录id
	ts.SetContent(1, 4, (char*)&id);
	//发送
	SendCommand(ts);
}

void ClientCtrl::SendCommand(TransmitSignal ts)
{
	commandSocket->Send((const char*)&ts, sizeof(ts));
}

void ClientCtrl::CommandsListen()
{
	int i = 1;
	while (isRunning)
	{
		DL("正在等待第" + to_string(i) + "条指令");
		TransmitSignal ts;
		int recvCode = commandSocket->Recv((char*)&ts, sizeof(ts));
		if (recvCode <= 0)
		{
			isLoggedIn = false;
			//断开连接
			isRunning = false;
			DL("指令连接已断开");
			break;
		}
		DL("成功接受第" + to_string(i) + "条指令");
		commandsQue.push(ts);
		i++;
	}
}

void ClientCtrl::CommandsHandle()
{
	int i = 1;
	while (isRunning)
	{
		if (!commandsQue.empty())
		{
			DL("正在处理第" + to_string(i) + "条指令");
			i++;
			TransmitSignal ts = commandsQue.front();
			commandsQue.pop();
			//共有消息
			if (ts.signal == loginSuccess)
			{
				DL("收到登录成功响应");
				char kind;
				ts.GetContent(1, 1, &kind);
				if (kind == 1)
				{
					logInCode = 1;
				}
				else if (kind == 2)
				{
					logInCode = 2;
				}
			}
			else if (ts.signal == loginFail)
			{
				char reason;
				ts.GetContent(1, 1, &reason);
				if (reason == 3)
				{
					logInCode = 3;
				}
				else if (reason == 4)
				{
					logInCode = 4;
				}
				else if (reason == 5)
				{
					logInCode = 5;
				}
			}
			//文件访问端会收到的消息
			else if (ts.signal == fileNotExist)
			{
				clientMenu->gotFileCode = 2;
			}
			else if (ts.signal == sendLongMessageRequest)
			{
				int port;
				char messagekind;
				ts.GetContent(1, 1, &messagekind);
				port = ts.fileByteSize;
				//执行长信息接受线程
				thread longMessageRecv(&ClientCtrl::LongMessageRecv, this, port, ts.segmentSize, messagekind);
			}
			else if (ts.signal == sendFileRequest)
			{
				int port;
				port = ts.fileByteSize;
				FileRcv fr(ts);
				//执行文件接受线程
				thread fileRecv(&ClientCtrl::FileRecv, this, port, ref(fr));
			}
			else if (ts.signal == sendWholeFile)
			{
				lastSegmentSize = ts.segmentSize;
				totalSize = ts.fileByteSize;
				isLast = true;
			}
			else if (ts.signal == fileSourceNotExist)
			{
				clientMenu->gotListCode = 3;
				clientMenu->gotFileCode = 3;
			}
			else if (ts.signal == listIsEmpty)
			{
				clientMenu->gotListCode = 2;
			}
			//文件源会收到的消息
			else if (ts.signal == readyRecieve)
			{
				int port = ts.fileByteSize;
				if (isFile)
				{
					//执行文件发送线程
					thread fileSend(&ClientCtrl::FileSend, this, port, waitforSendfileDir);
				}
				else
				{
					//执行长消息发送线程
					thread longMessageSend(&ClientCtrl::LongMessageSend, this, port, waitforSendkind);
				}
			}
			else if (ts.signal == fileRequest)
			{
				string filename = ts.fileName;
				waitforSendfileDir = clientMenu->flist.FindDir(filename);
				if (waitforSendfileDir == "not found" && clientMenu->flist.TryOpen(waitforSendfileDir))
				{
					FileReply(false);
					continue;
				}
				FileReply(true, filename);
				isFile = true;
			}
			else if (ts.signal == updataListRequest)
			{
				TransmitSignal rets;
				//列表为空
				if (clientMenu->flist.TotalSize() <= 0)
				{
					rets.signal = listIsEmpty;
					SendCommand(rets);
					continue;
				}
				//列表不为空准备发长消息
				rets.signal = sendLongMessageRequest;
				rets.segmentSize = FListMesSegSize;
				waitforSendkind = 0;//类型为文件列表
				rets.SetContent(1, 1, (char*)&waitforSendkind);
				SendCommand(rets);
				isFile = false;
			}
			else
			{
				DL("无效指令");
			}
		}
	}
}

void ClientCtrl::FileReply(bool isFound, string filename)
{
	TransmitSignal ts;
	if (isFound)
	{
		ts.signal = sendFileRequest;
		for (int i = 0; i < filename.size(); i++)
		{
			ts.fileName[i] = filename[i];
		}
	}
	else
	{
		ts.signal = fileNotExist;
	}
	SendCommand(ts);

}

void ClientCtrl::ToFileNameInList(char* buff, int length)
{
	if (buff[0] == '\0')
	{
		return;
	}
	for (int i = 0; i < length; i += 63)
	{
		string name = buff + i;
		if (name == "")
		{
			break;
		}
		clientMenu->AddtoList(name);
	}
}

void ClientCtrl::LongMessageRecv(int port, unsigned int segmentSize, char kind)
{
	Socket* fileSocket = new Socket();
	//默认是文件列表
	if (kind == 0)
	{
		//连接服务器文件端口
		if (!fileSocket->Connect(ServerIp, port))
		{
			//连接失败
			clientMenu->gotListCode = -1;
			return;
		}
		//回复我准备好了
		isLast = false;
		TransmitSignal ts;
		ts.signal = readyRecieve;
		SendCommand(ts);
		//清空文件列表
		clientMenu->ClearList();
		//开始接受
		char* namesbuff = new char[segmentSize] {};
		char* tempbuff = new char[segmentSize] {};
		while (!isLast)
		{
			int recCode = fileSocket->Recv(tempbuff, segmentSize);
			if (recCode <= 0)
			{
				break;
			}
			ToFileNameInList(namesbuff, segmentSize);
			for (int i = 0; i < segmentSize; i++)
			{
				namesbuff[i] = tempbuff[i];
			}
		}
		while (!isLast) {}
		ToFileNameInList(namesbuff, lastSegmentSize);
		clientMenu->gotListCode = 1;
	}
}

void ClientCtrl::FileRecv(int port, FileRcv& fr)
{
	//连接服务器文件端口
	Socket* fileSocket = new Socket();
	if (!fileSocket->Connect(ServerIp, port))
	{
		//连接失败
		clientMenu->gotFileCode = -1;
		return;
	}
	//回复我准备好了
	isLast = false;
	TransmitSignal ts;
	ts.signal = readyRecieve;
	SendCommand(ts);
	//开始接受
	char* filebuff = new char[fr.segmentSize] {};
	char* tempbuff = new char[fr.segmentSize] {};
	int recCode = fileSocket->Recv(filebuff, fr.segmentSize);
	while (!isLast && recCode > 0)
	{
		recCode = fileSocket->Recv(tempbuff, fr.segmentSize);
		if (recCode <= 0)
		{
			break;
		}
		fr.Receive(filebuff, fr.segmentSize);
		for (int i = 0; i < fr.segmentSize; i++)
		{
			filebuff[i] = tempbuff[i];
		}
	}
	while (!isLast) {}
	fr.Receive(filebuff, lastSegmentSize);
	fr.End(lastSegmentSize);
	clientMenu->gotFileCode = 1;
}

void ClientCtrl::FileSend(int port, string fileDir)
{
	FileSnd fs(fileDir);
	fs.SetSegmentSize(SEGMENT);
	Socket* fileSocket = new Socket();
	if (!fileSocket->Connect(ServerIp, port))
	{
		return;
	}
	char* buff;
	while (fs.Prepare())
	{
		fs >> &buff;
		fileSocket->Send(buff, fs.segmentSize);
	}
	//最后一个包
	fs >> &buff;
	fileSocket->Send(buff, fs.segmentSize);
	//最后包指令
	TransmitSignal ts;
	ts.signal = sendWholeFile;
	ts.segmentSize = fs.lastsegmentSize;
	ts.fileByteSize = fs.fileByteSize;
	SendCommand(ts);
}

void ClientCtrl::LongMessageSend(int port, char kind)
{
	Socket* fileSocket = new Socket();
	if (!fileSocket->Connect(ServerIp, port))
	{
		return;
	}
	if (kind == 0)
	{
		int bufferindex = 0;
		auto fl = clientMenu->flist.GetNamesList();//获取文件名列表
		char* sendbuffer = new char[FListMesSegSize] {'\0'};//发送缓冲区
		for (int i = 0; i < fl.size(); i++)
		{
			for (int j = 0; j < fl[i].size(); j++)
			{
				sendbuffer[bufferindex + j] = fl[i][j];
			}
			bufferindex += 63;
			if (bufferindex >= FListMesSegSize)
			{
				fileSocket->Send(sendbuffer, FListMesSegSize);
				bufferindex = 0;
			}
		}
		//发送最后一个包
		fileSocket->Send(sendbuffer, FListMesSegSize);
		//发送结束指令
		TransmitSignal ts;
		ts.signal = sendWholeFile;
		ts.segmentSize = bufferindex;
		ts.fileByteSize = fl.size() * 63;
		SendCommand(ts);
	}
	fileSocket->Close();
}


