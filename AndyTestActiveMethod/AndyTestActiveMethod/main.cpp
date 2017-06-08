#include "Poco/ActiveMethod.h"
#include "Poco/ActiveResult.h"

using Poco::ActiveMethod;
using Poco::ActiveResult;

class ActiveObject
{
public:
	ActiveObject() : exampleActiveMethod(this, &ActiveObject::exampleActiveMethodImpl)
	{
	}

	ActiveMethod<int, std::pair<int, int>, ActiveObject> exampleActiveMethod;

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