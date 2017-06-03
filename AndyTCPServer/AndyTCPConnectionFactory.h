#pragma once

#include "AndyTCPConnection.h"

#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string>

using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;

class AndyTCPConnectionFactory : public TCPServerConnectionFactory
{
public:
	AndyTCPConnectionFactory(const std::string arg1, int arg2, double arg3) : 
		m_arg1(arg1), 
		m_arg2(arg2), 
		m_arg3(arg3)
	{

	}

	TCPServerConnection* createConnection(const StreamSocket& socket)
	{
		return new AndyTCPConnection(socket, m_arg1, m_arg2, m_arg3);
	}

private:
	std::string m_arg1;
	int			m_arg2;
	double		m_arg3;
};

