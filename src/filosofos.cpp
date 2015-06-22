#define SHARED 1
#include<thread>
#include<atomic>
#include<functional>
#include<chrono>
#include<random>
#include<ctime>

#include "monitor.hpp"

using namespace std;

void *filosofoUniforme(vector<Monitor>&,int);
void read(char *file_name);
void distribuiComida();
void pensa();

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
      clock_t begin = clock();
      printf("Filósofo-%d pegou os dois garfos :D   tempo:%LF seg\n", num, (long double)begin/CLOCKS_PER_SEC);
      //filósofo comendo
      if(DEBUG) printf("come %d\n", num);
      garfo[0].devolveGarfo(0, num);
      garfo[num].devolveGarfo(num, num);
      clock_t end = clock();
      printf("Filósofo-%d terminou de comer    :D   tempo:%LF seg\n", num, (long double)end/CLOCKS_PER_SEC);
    }
        
    // Demais filósofos
    else
    {
      if(DEBUG) printf(" método2\n");
      garfo[num].requisitaGarfo(num, num);
      garfo[num+1].requisitaGarfo(num+1, num);
      clock_t begin = clock();
      printf("Filósofo-%d pegou os dois garfos :D   tempo:%LF seg\n", num, (long double)begin/CLOCKS_PER_SEC);
      //filósofo comendo
      if(DEBUG) printf("come %d\n", num);
      garfo[num].devolveGarfo(num, num);
      garfo[num+1].devolveGarfo(num+1, num);
      clock_t end = clock();
      printf("Filósofo-%d terminou de comer    :D   tempo:%LF seg\n", num, (long double)end/CLOCKS_PER_SEC);
    }
    if(DEBUG) printf("pensa %d\n", num);
    pensa();
    
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

void pensa(){
  std::mt19937_64 eng;
  std::uniform_int_distribution<> dist(10, 20);
  auto time = std::chrono::milliseconds{dist(eng)};
  std::this_thread::sleep_for(time);
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
