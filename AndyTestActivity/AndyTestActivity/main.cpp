#include "Poco/Activity.h"
#include "Poco/Thread.h"
#include <iostream>

using Poco::Thread;
class ActivityObject
{
public:
	ActivityObject(): _activity(this, &ActivityObject::runActivity)
	{}

	void start()
	{
		_activity.start();
	}

	void stop()
	{
		_activity.stop(); // request stop
		_activity.wait(); // wait until activity actually stops
	}

protected:
	void runActivity()
	{
		while (!_activity.isStopped())
		{
			std::cout << "Activity running." << std::endl;
			Thread::sleep(200);
		}
	}
private:
	Poco::Activity<ActivityObject> _activity;
};

int main(int argc, char** argv)
{
	ActivityObject example;
	example.start();
	Thread::sleep(2000);
	example.stop();

	return 0;
}