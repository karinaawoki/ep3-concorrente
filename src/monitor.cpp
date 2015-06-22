#include "monitor.hpp"

void Monitor::signal()
{
  cv.notify_one();
}

void Monitor::wait(unique_lock<mutex> &lck)
{
  cv.wait(lck);
}

void Monitor::devolveGarfo(int apaga)
{ 
    if(DEBUG) printf("devolveGarfo - entra %d\n", apaga);
    this->signal();
    this->quantosEsperam--;
    if(DEBUG) printf("devolveGarfo - saída %d\n", apaga);
}

void Monitor::requisitaGarfo(int apaga)
{
  
  if(DEBUG) printf("requisitaGarfo - entra %d\n", apaga);
  if(this->quantosEsperam > 0)
    {
      printf("  1\n");
      unique_lock<mutex> lck(m);
      printf("  2\n");
      this->wait(lck);
      printf("  3\n");
    }
  this->quantosEsperam++;
  if(DEBUG) printf("requisitaGarfo - saída %d\n", apaga);
}
=======
