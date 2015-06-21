#define SHARED 1
#define _XOPEN_SOURCE 600

#include "monitor.hpp"


using namespace std;

void *filosofoUniforme(void *i);
void *filosofoPesado(void *i);


vector<int> quantidade_comeu;
vector<int> peso;
vector<pthread_t> threads;

pthread_barrier_t barreira; 
pthread_barrier_t barreira2; 

int N;
int R;

sem_t m, mutex_r;
vector<Monitor> garfo;





int main(int argc, char *argv[])
{
	N = 3;
	R = atoi(argv[2]);
	vector<int> thread_args;

	/* Inicializando vetores / semáforo / barreira */
	thread_args.resize(N);
	threads.resize(N);
	peso.resize(N);
	quantidade_comeu.resize(N);
	garfo.resize(N);
	sem_init(&m, SHARED, 1);
	sem_init(&mutex_r, SHARED, 1);
	pthread_barrier_init(&barreira, NULL, N);
	pthread_barrier_init(&barreira2, NULL, N);



	/* Cria threads - filósofos */
	for(int i = 0; i < N; i++)
	{
		thread_args[i] = i;
      	if(pthread_create(&threads[i], NULL, filosofoUniforme,(void*)&thread_args[i]))
        	abort();
    }
    for(int i = 0; i < N; i++) pthread_join(threads[i], NULL);

	return 0;
}



void *filosofoUniforme(void *i)
{
	int num = *((int *) i);
	
	while(R>0)
	{	
		/* Último filósofo - diferente dos outros */
		if(num == N-1)
		{
			garfo[0].requisitaGarfo();
			garfo[num].requisitaGarfo();
			//filósofo comendo
			garfo[0].devolveGarfo();
			garfo[num].devolveGarfo();
		}
		
		// Demais filósofos
		else
		{
			garfo[num].requisitaGarfo();
			garfo[num+1].requisitaGarfo();
			//filósofo comendo
			garfo[num].devolveGarfo();
			garfo[num+1].devolveGarfo();
		}

		sem_wait(&mutex_r);
			R--;
		sem_post(&mutex_r);

		pthread_barrier_wait(&barreira);
		pthread_barrier_wait(&barreira2);
	}

	return 0;
}

void *filosofoPesado(void *i)
{
	int num = *((int *) i);
	
	while(R>0)
	{	
		/* Último filósofo - diferente dos outros */
		if(num == N-1)
		{

		}
		
		// Demais filósofos
		else
		{

		}

		sem_wait(&mutex_r);
			R--;
		sem_post(&mutex_r);

		pthread_barrier_wait(&barreira);
		pthread_barrier_wait(&barreira2);
	}

	return NULL;
}