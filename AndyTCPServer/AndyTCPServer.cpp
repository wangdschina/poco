#include "AndyTCPServer.h"
#include "AndyTCPConnectionFactory.h"

#include "Poco/DateTimeFormat.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"

using Poco::DateTimeFormat;
using Poco::Net::ServerSocket;
using Poco::Net::TCPServer;

void AndyTCPServer::initialize( Application& self )
{
	ServerApplication::loadConfiguration();
	ServerApplication::initialize(self);
}

void AndyTCPServer::uninitialize()
{
	ServerApplication::uninitialize();
}

int AndyTCPServer::main( const std::vector<std::string>& args )
{
	unsigned short port = (unsigned short) config().getInt("AndyTCPServer.port", 12346);
	std::string format(config().getString("AndyTCPServer.format", DateTimeFormat::ISO8601_FORMAT));

	// 1. Bind a ServerSocket with an address
	ServerSocket serverSocket(port);

	// 2. Pass the ServerSocket to a TCPServer
	TCPServer server(new AndyTCPConnectionFactory(format, 0, 0.0), serverSocket);

	// 3. Start the TCPServer
	server.start();

	// 4. Wait for termination
	waitForTerminationRequest();

	// 5. Stop the TCPServer
	server.stop();

	return Application::EXIT_OK;
}
