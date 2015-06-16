


typedef class monitor
{
	condition_variable cv;

	void signal(condition_variable cv)
	{
		sem_wait(&m);
		cv.notify_one();
		sem_post(&m);
	}

	void wait(condition_variable cv)
	{
		sem_wait(&m);
		cv.wait();
		sem_post(&m);
	}



	void devolveGarfo()
	{
		signal(cv);
	}

	void requisitaGarfo()
	{
		wait(cv);
	}
}Monitor;