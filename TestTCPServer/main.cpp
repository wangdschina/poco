#include <iostream>

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

using Poco::Net::StreamSocket;
using Poco::Net::SocketAddress;

const int BUFFER_SIZE = 1024;

int main(int argc, char** argv)
{
	SocketAddress address("127.0.0.1", 12346);
	StreamSocket socket(address);
	char buffer[BUFFER_SIZE];
	while (true)
	{
		if (socket.available())
		{
			int len = socket.receiveBytes(buffer, BUFFER_SIZE);
			buffer[len] = '\0';
			std::cout << "" << buffer;
		}
	}
	return 0;
}