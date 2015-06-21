#include <condition_variable>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef class monitor
{
	std::condition_variable cv;

public:

	void signal(std::condition_variable cv);

	void wait(std::condition_variable cv);



	void devolveGarfo();

	void requisitaGarfo();
}Monitor;