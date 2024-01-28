#include "Net.h"

Net::Address::Address(string ip, int port)
{
	//构建sockaddr
	std::memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
	sockaddr.sin_port = htons(port);
	//保存地址信息
	this->ip = ip;
	this->port = port;
}

Net::Address::~Address()
{

}

Net::Socket::Socket()
{
	sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == INVALID_SOCKET)
	{
		EL(to_string(sockfd) + "-创建套接字失败！失败信息：" + string(strerror(errno)));
	}
	else
	{
		DL(to_string(sockfd) + "-创建套接字成功！");
	}
}

Net::Socket::Socket(SOCKET s)
{
	sockfd = s;

}


Net::Socket::~Socket()
{
	Close();
}

void Net::Socket::Bind(string ip, int port)
{
	Address addr(ip, port);
	if (::bind(sockfd, (const sockaddr*)&addr.sockaddr, sizeof(sockaddr_in)) < 0)
	{
		EL(to_string(sockfd) + "-套接字绑定地址端口失败！失败信息：" + string(strerror(errno)));
		return;
	}
	else
	{
		DL(to_string(sockfd) + "-套接字绑定地址端口成功：ip：" + ip + "端口：" + to_string(port));
	}
}

void Net::Socket::Bind(Address addr)
{
	if (::bind(sockfd, (const sockaddr*)&addr.sockaddr, sizeof(sockaddr_in)) < 0)
	{
		EL(to_string(sockfd) + "-套接字绑定地址端口失败！失败信息：" + string(strerror(errno)));
		return;
	}
	else
	{
		DL(to_string(sockfd) + "-套接字绑定地址端口成功：ip：" + addr.ip + "端口：" + to_string(addr.port));
	}
}

void Net::Socket::Listen(int backlog)
{
	if (::listen(sockfd, backlog) < 0)
	{
		EL(to_string(sockfd) + "-套接字监听结果异常！异常信息：" + string(strerror(errno)));
		return;
	}
	else
	{
		DL(to_string(sockfd) + "-套接字监听中...");
	}
}

Net::Socket Net::Socket::Accept()
{
	sockaddr_in connaddr;
	int socklen = sizeof(sockaddr_in);
	SOCKET connfd = ::accept(sockfd, (sockaddr*)&connaddr, &socklen);
	//创建连接套接字
	Socket connsk(connfd);
	if (connfd < 0)
	{
		EL(to_string(sockfd) + "-套接字接受连接失败！失败信息：" + string(strerror(errno)));
	}
	else
	{
		string ip = inet_ntoa(connaddr.sin_addr);
		int port = ntohs(connaddr.sin_port);
		DL(to_string(sockfd) + "-接受一个连接，来自：ip：" + ip + "端口：" + to_string(port));
		//连接套接字载入连接对象的地址
		connsk.connectedAddr = new Address(ip, port);
	}
	//返回连接套接字
	return connsk;
}


bool Net::Socket::Connect(string ip, int port)
{
	Address addr(ip, port);
	int connectCode = ::connect(sockfd, (struct sockaddr*)&addr.sockaddr, sizeof(sockaddr_in));
	if (connectCode < 0)
	{
		EL(to_string(sockfd) + "-套接字连接失败！失败信息：" + string(strerror(errno)));
		return false;
	}
	else
	{
		DL(to_string(sockfd) + "-套接字连接成功！连接到：ip：" + ip + "端口：" + to_string(port));
		connectedAddr = new Address(ip, port);
		return true;
	}
}

void Net::Socket::Connect(Address addr)
{
	if (::connect(sockfd, (struct sockaddr*)&addr.sockaddr, sizeof(sockaddr)) < 0)
	{
		EL(to_string(sockfd) + "-套接字连接失败！失败信息：" + string(strerror(errno)));
		return;
	}
	else
	{
		DL(to_string(sockfd) + "-套接字连接成功！连接到：ip：" + addr.ip + "端口：" + to_string(addr.port));
		connectedAddr = new Address(addr.ip, addr.port);
	}
}

void Net::Socket::Send(const char* data, int size)
{
	::send(sockfd, data, size, 0);
	DL(to_string(sockfd) + "-成功发送" + to_string(size) + "字节数据");
}

int Net::Socket::Recv(char* data, int size)
{
	int rsn = ::recv(sockfd, data, size, 0);
	if (rsn == 0)
	{
		DL(to_string(sockfd) + "-连接被对方关闭");
	}
	else if (rsn == -1)
	{
		EL(to_string(sockfd) + "-连接出现错误，错误信息：" + string(strerror(errno)));
	}
	else
	{
		DL(to_string(sockfd) + "-成功接受" + to_string(rsn) + "字节数据");
	}
	return rsn;
}

void Net::Socket::Close()
{
	::closesocket(sockfd);
	DL(to_string(sockfd) + "-关闭套接字");
}
