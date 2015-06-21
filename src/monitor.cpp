#include "monitor.hpp"

void Monitor::signal()
{
  cv.notify_one();
}

void Monitor::wait(unique_lock<mutex> &lck)
{
  cv.wait(lck);
}

void Monitor::devolveGarfo()
{
  unique_lock<mutex> lck(m);
  this->signal();
}

void Monitor::requisitaGarfo()
{
  unique_lock<mutex> lck(m);
  this->wait(lck);
}
