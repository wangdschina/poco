#include "Poco\Thread.h"
#include "Poco\Condition.h"
#include "Poco\Mutex.h"

using Poco::Thread;
using Poco::Condition;
using Poco::FastMutex;

void Fun(void* lpVoid);

const int THREAD_NUM = 10;
int g_num = 0;

Condition cond;
FastMutex mt;

int main()
{
	Thread td[THREAD_NUM];
	for (int i = 0; i != THREAD_NUM; ++i)
	{
		td[i].start(Fun, &i);
		Sleep(50);
	}
	cond.broadcast();
	for (auto& it : td)
	{
		it.join();
	}
	printf("pause");

	return 0;
}

void Fun( void* lpVoid )
{
	int i = *(int*)lpVoid;

	Poco::ScopedLock<FastMutex> lock(mt);
	cond.wait(mt);

	//Sleep(50);

	g_num++;
	printf("线程编号为%d  全局资源值为%d\n", i, g_num);
}