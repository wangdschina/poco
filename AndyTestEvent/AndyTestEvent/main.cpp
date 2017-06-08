#include <process.h>

#include "Poco\Event.h"
#include "Poco\Mutex.h"

using Poco::Event;
using Poco::FastMutex;

unsigned int CALLBACK Fun(void* lpVoid);

const int THREAD_NUM = 10;
int g_num = 0;

Event event;
FastMutex mt;

int main()
{
	HANDLE hand[THREAD_NUM];
	for (int i = 0; i != THREAD_NUM; ++i)
	{
		hand[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
		event.wait();
	}
	WaitForMultipleObjects(THREAD_NUM, hand, TRUE, INFINITE);

	for (int i = 0; i != THREAD_NUM; ++i)
		CloseHandle(hand[i]);

	return 0;
}

unsigned int CALLBACK Fun( void* lpVoid )
{
	int i = *(int*)lpVoid;
	event.set();

	Sleep(50);

	Poco::ScopedLock<FastMutex> lock(mt);
	g_num++;
	printf("线程编号为%d  全局资源值为%d\n", i, g_num);

	return 0;
}