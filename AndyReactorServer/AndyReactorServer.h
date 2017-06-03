#pragma once

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Application.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;

class AndyReactorServer : public ServerApplication
{
public:
	AndyReactorServer(void);
	~AndyReactorServer(void);

protected:
	void initialize(Application& self);
	void uninitialize();
	int main(const std::vector<std::string>& args);
};

