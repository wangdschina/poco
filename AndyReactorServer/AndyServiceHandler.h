#pragma once

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/AutoPtr.h"
#include "Poco/Net/SocketNotification.h"

using Poco::Net::StreamSocket;
using Poco::Net::SocketReactor;
using Poco::AutoPtr;
using Poco::Net::ReadableNotification;
using Poco::Net::ShutdownNotification;

class AndyServiceHandler
{
public:
	AndyServiceHandler(StreamSocket& socket, SocketReactor& reactor);
	~AndyServiceHandler(void);

	void onReadable(const AutoPtr<ReadableNotification>& pNf);
	void onShutdown(const AutoPtr<ShutdownNotification>& pNf);

private:
	enum 
	{
		BUFFER_SIZE = 1024
	};
	StreamSocket	m_socket;
	SocketReactor&	m_reactor;
	char*			m_pBuffer;
};

