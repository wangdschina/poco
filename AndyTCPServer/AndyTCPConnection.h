#pragma once

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string>

using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;

class AndyTCPConnection : public TCPServerConnection
{
public:
	AndyTCPConnection(const StreamSocket& s, const std::string& arg1, int arg2, double arg3);

	void run();

private:
	std::string m_arg1;
	int			m_arg2;
	double		m_arg3;
};

