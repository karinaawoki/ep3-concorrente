#define SHARED 1
#include<thread>
#include<atomic>
#include<functional>

#include "monitor.hpp"

using namespace std;

void *filosofoUniforme(vector<Monitor>&,int);
void read(char *file_name);
void distribuiComida();

vector<int> quantidade_comeu;
vector<int> peso;
vector<thread> threads;
vector<int> comida_por_filosofo;

int N;
atomic<int> R;

int main(int argc, char *argv[])
{
  read(argv[1]);


  R = atoi(argv[2]);
  vector<int> thread_args;

  /* Modo uniforme */
  if(argv[3][0]=='U' || argv[3][0]=='u')
  {
    for (int i = 0; i < N; i++)  peso[i] = 1;
  }
  
  /* Inicializando vetores / semáforo */
  quantidade_comeu.resize(N);
  comida_por_filosofo.resize(N);
  vector<Monitor> garfos(N);
  
  distribuiComida();

  /* Cria threads - filósofos */
  for(int i = 0; i < N; i++)
  {
    threads.emplace_back(filosofoUniforme,ref(garfos),i);
  }
  
  for(int i = 0; i < N; i++) threads[i].join();

  /* Quantidade comida */
  printf("\n\n\n");
  for (int i = 0; i < N; ++i)
  {
    printf("Filósofo-%d comeu %d Refeições!\n", i, quantidade_comeu[i]);
  }

  return 0;
}



void *filosofoUniforme(vector<Monitor>& garfo,int num)
{
  while(quantidade_comeu[num] < comida_por_filosofo[num])
  {          
    if(DEBUG) printf("entrou na thread %d\n", num);

    /* Último filósofo - diferente dos outros */
    if(num == N-1)
    {
      if(DEBUG) printf(" método1\n");
      garfo[0].requisitaGarfo(0, num);
      garfo[num].requisitaGarfo(num, num);
      //filósofo comendo
      if(DEBUG) printf("come %d\n", num);
      garfo[0].devolveGarfo(0, num);
      garfo[num].devolveGarfo(num, num);
    }
        
    // Demais filósofos
    else
    {
      if(DEBUG) printf(" método2\n");
      garfo[num].requisitaGarfo(num, num);
      garfo[num+1].requisitaGarfo(num+1, num);
      //filósofo comendo
      if(DEBUG) printf("come %d\n", num);
      garfo[num].devolveGarfo(num, num);
      garfo[num+1].devolveGarfo(num+1, num);
    }
    if(DEBUG) printf("pensa %d\n", num);
    
    quantidade_comeu[num] ++;
  }
  R--;
  return 0;
}


void distribuiComida()
{
  int somaPesos = 0;
  for (int i = 0; i < N; i++)
    somaPesos += peso[i];

  int k = R/somaPesos;
  for (int i = 0; i < N; i++)
    comida_por_filosofo[i] = k*peso[i];

  int resto = R%somaPesos;
  for (int i = 0; i < N && resto>0; i++)
  {
    if(resto >= peso[i])
    {
      comida_por_filosofo[i] += peso[i];
      resto-=peso[i];
    }
    else
    {
      comida_por_filosofo[i] += resto;
      resto = 0;
    }
  }
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
