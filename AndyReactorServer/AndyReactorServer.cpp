#include "AndyReactorServer.h"
#include "AndyServiceHandler.h"

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAcceptor.h"

using Poco::Net::ServerSocket;
using Poco::Net::SocketAcceptor;


AndyReactorServer::AndyReactorServer(void)
{
}


AndyReactorServer::~AndyReactorServer(void)
{
}

void AndyReactorServer::initialize( Application& self )
{
	loadConfiguration();
	ServerApplication::initialize(self);
}

void AndyReactorServer::uninitialize()
{
	ServerApplication::uninitialize();
}

int AndyReactorServer::main( const std::vector<std::string>& args )
{
	unsigned short port = (unsigned short) config().getInt("AndyReactor.port", 12346);
	ServerSocket serverSocket(port);
	SocketReactor reactor;
	SocketAcceptor<AndyServiceHandler> acceptor(serverSocket, reactor);

	reactor.run();

	waitForTerminationRequest();
	reactor.stop();

	return Application::EXIT_OK;
}
