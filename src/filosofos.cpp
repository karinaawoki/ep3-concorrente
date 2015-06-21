#define SHARED 1
#define DEBUG 1
#include<thread>
#include<atomic>

#include "monitor.hpp"

using namespace std;

void *filosofoUniforme(vector<Monitor>&,int);
void *filosofoPesado(vector<Monitor>&,int);
void read(char *file_name);

vector<int> quantidade_comeu;
vector<int> peso;
vector<thread> threads;

int N;
atomic<int> R;

vector<Monitor> garfo;

//Monitor *garfo;

int main(int argc, char *argv[])
{
  
  read(argv[1]);
  R = atoi(argv[2]);
  vector<int> thread_args;
  
  /* Inicializando vetores / semáforo / barreira */
  //thread_args.resize(N);
  //threads.resize(N);
  peso.resize(N);
  quantidade_comeu.resize(N);
  //garfo = (Monitor*)malloc(N*sizeof(Monitor));
    
  for(int i = 0; i < N; i++) garfo.emplace_back();

    /* Cria threads - filósofos */
  for(int i = 0; i < N; i++)
    {
      threads.push_back(thread(filosofoUniforme,garfos,i));
    }
  for(int i = 0; i < N; i++) threads[i].join();

  return 0;
}



void *filosofoUniforme(vector<Monitor>& garfo,int num)
{

  while(R>0)
    {    
      printf("oiee\n");
      /* Último filósofo - diferente dos outros */
      if(num == N-1)
        {
	  garfo[0].requisitaGarfo();
	  garfo[num].requisitaGarfo();
	  //filósofo comendo
	  garfo[0].devolveGarfo();
	  garfo[num].devolveGarfo();
	  
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
	  garfo[num].requisitaGarfo();
	  garfo[num+1].requisitaGarfo();
	  //filósofo comendo
	  garfo[num].devolveGarfo();
	  garfo[num+1].devolveGarfo();
            if(DEBUG) printf(" método2\n");
            garfo[num].requisitaGarfo();
            garfo[num+1].requisitaGarfo();
            //filósofo comendo
            garfo[num].devolveGarfo();
            garfo[num+1].devolveGarfo();
        }

      R--;

    }
  return 0;
}

void *filosofoPesado(vector<Monitor>& garfo,int num)
{
    
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

      R--;
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
