#ifndef AndyTCPServer_h__
#define AndyTCPServer_h__

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Application.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;


class AndyTCPServer : public ServerApplication
{
public:

	AndyTCPServer(void)
	{
	}

	~AndyTCPServer(void)
	{
	}

protected:
	void initialize(Application& self);
	void uninitialize();
	int main(const std::vector<std::string>& args);
};


#endif // AndyTCPServer_h__

