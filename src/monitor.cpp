#include "monitor.hpp"

void Monitor::signal()
{
  cv.notify_one();
}

void Monitor::wait(unique_lock<mutex> &lck)
{
  cv.wait(lck);
}
