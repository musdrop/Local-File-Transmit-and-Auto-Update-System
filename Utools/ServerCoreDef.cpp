#include"ServerCore.h"
namespace jeff
{
	Connection::Connection()
		:id(0),fileSnd_fileRcv(make_pair(0,0)),newSndMsg_newRcvMsg(make_pair(false,false))
	{}
	Connection::Connection(int existId)
		:id(existId), fileSnd_fileRcv(make_pair(0, 0)), newSndMsg_newRcvMsg(make_pair(false, false))
	{}
	void Connection::WriteSnd(char newSignal)
	{
		this->fileSnd_fileRcv.first = newSignal;
		this->newSndMsg_newRcvMsg.first = true;
	}
	void Connection::WriteRcv(char newSignal)
	{
		this->fileSnd_fileRcv.second = newSignal;
		this->newSndMsg_newRcvMsg.second = true;
	}
	char Connection::GetSnd()
	{
		this->newSndMsg_newRcvMsg.first = false;
		return this->fileSnd_fileRcv.first;
	}
	char Connection::GetRcv()
	{
		this->newSndMsg_newRcvMsg.second = false;
		return this->fileSnd_fileRcv.second;
	}
	int Connection::GetId()
	{
		return this->id;
	}
	bool Connection::IsNewMessage(bool isSnd)
	{
		if (isSnd)
			return newSndMsg_newRcvMsg.first;
		else
			return newSndMsg_newRcvMsg.second;
	}
	bool  Connection::operator==(Connection& Obj)
	{
		return Obj.id == id
			&& newSndMsg_newRcvMsg == Obj.newSndMsg_newRcvMsg
			&& fileSnd_fileRcv == Obj.fileSnd_fileRcv;
	}

	Connection* Core::New(int id)
	{
		Connection newConnect(id);
		return &pool.append_Node(newConnect)->get_Data();
	}
	void Core::Delete(Connection* existEle)
	{
		pool.delete_node(pool.find_Node(*existEle));
	}
	Connection* Core::Find(int id)
	{
		for (int n = 0; n < pool.size_Chain(); ++n)
		{
			if (pool[n].get_Data().GetId() == id)
				return &pool[n].get_Data();
		}
		return NULL;
	}
}