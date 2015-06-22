#ifndef MONITOR_HPP
#define MONITOR_HPP
#define DEBUG 1

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
  
  void signal();
  
  void wait(unique_lock<mutex>&);
  
public:
  
  Monitor(): quantosEsperam(0){};

  void devolveGarfo(int);

  void requisitaGarfo(int);
};
#endif
