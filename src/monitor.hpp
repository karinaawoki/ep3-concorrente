#ifndef MONITOR_HPP
#define MONITOR_HPP
#include <condition_variable>
#include <thread>
#include <vector>
#include <mutex>
#include <string.h>

using namespace std;

class Monitor
{
    condition_variable cv;
    mutex m;

    void signal();

    void wait(unique_lock<mutex>&);
    
  public:

    void devolveGarfo();

    void requisitaGarfo();
};
#endif
