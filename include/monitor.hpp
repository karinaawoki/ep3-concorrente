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
  condition_variable cond;
  mutex m;

  void signal(condition_variable&);

  void wait(unique_lock<mutex>&,condition_variable&);
    
  public:

  Monitor():quantosEsperam(0){};

  void devolveGarfo(int,int);

  void requisitaGarfo(int,int);
};
#endif
