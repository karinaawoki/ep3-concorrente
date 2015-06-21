#include "monitor.hpp"

using namespace std;

	void Monitor: signal(std:: condition_variable cv)
	{
		sem_wait(&m);
		cv.notify_one();
		sem_post(&m);
	}

	void Monitor: wait(std:: condition_variable cv)
	{
		sem_wait(&m);
		cv.wait();
		sem_post(&m);
	}



	void Monitor: devolveGarfo()
	{
		signal(cv);
	}

	void Monitor: requisitaGarfo()
	{
		wait(cv);
	}