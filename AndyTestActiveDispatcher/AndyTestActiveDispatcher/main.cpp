#include "Poco/ActiveDispatcher.h"
#include "Poco/ActiveMethod.h"
#include "Poco/ActiveResult.h"

using Poco::ActiveDispatcher;
using Poco::ActiveMethod;
using Poco::ActiveResult;
using Poco::ActiveStarter;

class ActiveObject: public ActiveDispatcher
{
public:
	ActiveObject() : exampleActiveMethod(this, &ActiveObject::exampleActiveMethodImpl)
	{
	}

	ActiveMethod<int, std::pair<int, int>, ActiveObject, ActiveStarter<ActiveDispatcher>> exampleActiveMethod;

protected:
	int exampleActiveMethodImpl(const std::pair<int, int>& args)
	{
		return args.first + args.second;
	}
};


int main()
{
	ActiveObject myActiveObject;
	ActiveResult<int> result = myActiveObject.exampleActiveMethod(std::make_pair(1, 2));
	result.wait();
	std::cout << result.data() << std::endl;

	return 0;
}