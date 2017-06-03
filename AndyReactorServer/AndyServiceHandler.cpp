#include "AndyServiceHandler.h"

#include "Poco/Util/Application.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/NObserver.h"

using Poco::Util::Application;
using Poco::DateTimeFormat;
using Poco::Net::ServerSocket;
using Poco::Net::TCPServer;
using Poco::NObserver;


AndyServiceHandler::AndyServiceHandler( StreamSocket& socket, SocketReactor& reactor ) : 
	m_socket(socket), 
	m_reactor(reactor), 
	m_pBuffer(new char[BUFFER_SIZE])
{
	Application& app = Application::instance();
	app.logger().information("Connection from" + socket.peerAddress().toString());
	m_reactor.addEventHandler(m_socket,	NObserver<AndyServiceHandler, ReadableNotification>(*this, &AndyServiceHandler::onReadable));
	m_reactor.addEventHandler(m_socket,	NObserver<AndyServiceHandler, ShutdownNotification>(*this, &AndyServiceHandler::onShutdown));
}

AndyServiceHandler::~AndyServiceHandler(void)
{
	Application& app = Application::instance();
	app.logger().information("Disconnecting " + m_socket.peerAddress().toString());
	m_reactor.removeEventHandler(m_socket, NObserver<AndyServiceHandler, ReadableNotification>(*this, &AndyServiceHandler::onReadable));
	m_reactor.removeEventHandler(m_socket, NObserver<AndyServiceHandler, ShutdownNotification>(*this, &AndyServiceHandler::onShutdown));
	delete [] m_pBuffer;
}

void AndyServiceHandler::onReadable( const AutoPtr<ReadableNotification>& pNf )
{
	if (m_socket.available())
	{
		// Receive data from StreamSocket
		int n = m_socket.receiveBytes(m_pBuffer, BUFFER_SIZE);

		// Send data back the client 
		m_socket.sendBytes(m_pBuffer, n);
	}
	else
	{
		delete this;
	}
}

// When ShutdownNotification is detected, this method will be invoked.
void AndyServiceHandler::onShutdown( const AutoPtr<ShutdownNotification>& pNf )
{
	delete this;
}
