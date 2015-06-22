#include "monitor.hpp"

void Monitor::signal(condition_variable &cv)
{
  cv.notify_one();
}

void Monitor::wait(unique_lock<mutex> &lck,condition_variable &cv)
{
  cv.wait(lck);
}

void Monitor::devolveGarfo(int apaga,int proc)
{ 
  if(DEBUG) printf("devolveGarfo - entra g:%d p:%d\n", apaga,proc);
  signal(cond);
  quantosEsperam--;
  if(DEBUG) printf("devolveGarfo - saída g:%d p:%d\n", apaga,proc);
}

void Monitor::requisitaGarfo(int apaga,int proc)
{
  
  if(DEBUG) printf("requisitaGarfo - entra g:%d p:%d\n", apaga,proc);
  if(quantosEsperam > 0)
    {
      printf("  1\n");
      unique_lock<mutex> lck(m);
      printf("  2\n");
      wait(lck,cond);
      printf("  3\n");
    }
  quantosEsperam++;
  if(DEBUG) printf("requisitaGarfo - saída g:%d p:%d\n", apaga,proc);
}
