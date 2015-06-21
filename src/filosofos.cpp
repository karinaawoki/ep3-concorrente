#define SHARED 1
#define DEBUG 1

#include "monitor.hpp"

using namespace std;

void *filosofoUniforme(void *i);
void *filosofoPesado(void *i);
void read(char *file_name);

vector<int> quantidade_comeu;
vector<int> peso;
vector<pthread_t> threads;

pthread_barrier_t barreira; 
pthread_barrier_t barreira2; 

int N;
int R;

mutex mutex_r;
//vector<Monitor> garfo;

Monitor *garfo;

int main(int argc, char *argv[])
{
    read(argv[1]);
    R = atoi(argv[2]);
    vector<int> thread_args;
    printf("%d\n", N);

    /* Inicializando vetores / semáforo / barreira */
    thread_args.resize(N);
    threads.resize(N);
    quantidade_comeu.resize(N);
    pthread_barrier_init(&barreira, NULL, N);
    pthread_barrier_init(&barreira2, NULL, N);
    garfo = (Monitor*)malloc(N*sizeof(Monitor));

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
        if(DEBUG) printf("entrou na thread \n");
        /* Último filósofo - diferente dos outros */
        if(num == N-1)
        {
            if(DEBUG) printf(" método1\n");
            garfo[0].requisitaGarfo();
            printf("lalalala\n");
            garfo[num].requisitaGarfo();
            //filósofo comendo
            garfo[0].devolveGarfo();
            garfo[num].devolveGarfo();
        }
        
        // Demais filósofos
        else
        {
            if(DEBUG) printf(" método2\n");
            garfo[num].requisitaGarfo();
            garfo[num+1].requisitaGarfo();
            //filósofo comendo
            garfo[num].devolveGarfo();
            garfo[num+1].devolveGarfo();
        }

        mutex_r.lock();
            R--;
        mutex_r.unlock();

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

        mutex_r.lock();
        R--;
        mutex_r.unlock();

        pthread_barrier_wait(&barreira);
        pthread_barrier_wait(&barreira2);
    }
    return NULL;
}





void read(char *file_name)
{
    char line[1000];
    FILE *file;
    int lineCount = 0;
    file = fopen(file_name , "r");

    while((fgets(line, sizeof(line), file)) != NULL)
    {
        if (lineCount == 0)
        { /* First line contains number of vertex */
            N = atoi(line);
            peso.resize(N);
            lineCount = 1;  
        }

        else
        {
            char space[2] = " ";
            peso[0] = atoi(strtok(line, space));
            for(int i = 1; i<N; i++)
            {
                peso[i] = atoi(strtok(NULL, space));
            }
            break;
        }
    }
    fclose(file);
}