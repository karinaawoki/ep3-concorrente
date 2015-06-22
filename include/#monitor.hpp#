#ifndef MONITOR_HPP
#define MONITOR_HPP
#define DEBUG 0

#include <condition_variable>
#include <thread>
#include <vector>
#include <mutex>
#include <string.h>

using namespace std;

class Monitor
{  
    int quantosEsperam;
    condition_variable cv;
    mutex m;

    void signal()
    {
      cv.notify_one();
    };

    void wait(unique_lock<mutex>&lck)
    {
      cv.wait(lck);
    };
    
  public:

  Monitor(): quantosEsperam(0){};

    void devolveGarfo(int garfo, int proc)
    {
      if(DEBUG) printf("devolveGarfo - entra g:%d p:%d\n", garfo, proc);
      unique_lock<mutex> lck(m);
      signal();
      quantosEsperam--;
      if(DEBUG) printf("devolveGarfo - saída g:%d p:%d\n", garfo, proc);
    };

    void requisitaGarfo(int garfo, int proc)
    {
      unique_lock<mutex> lck(m);

      if(DEBUG) printf("requisitaGarfo - entra g:%d p:%d\n", garfo, proc);
      if(quantosEsperam > 0)
      {
        wait(lck);
      }
      quantosEsperam++;
      if(DEBUG) printf("requisitaGarfo - saída g:%d p:%d\n", garfo, proc);
    };
};
#endif
