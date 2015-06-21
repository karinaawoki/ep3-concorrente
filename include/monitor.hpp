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

  	Monitor()
  	{
  		quantosEsperam = 0;
		};

    void devolveGarfo(int apaga)
    {
    	if(DEBUG) printf("devolveGarfo - entra %d\n", apaga);
			this->quantosEsperam--;
		  unique_lock<mutex> lck(m);
		  this->signal();
    	if(DEBUG) printf("devolveGarfo - saída %d\n", apaga);
		};

    void requisitaGarfo(int apaga)
    {
    	if(DEBUG) printf("requisitaGarfo - entra %d\n", apaga);
			while(quantosEsperam > 0)
			{
				printf("  1\n");
		    unique_lock<mutex> lck(m);
				printf("  2\n");
		    this->wait(lck);
				printf("  3\n");
			}
			quantosEsperam++;
    	if(DEBUG) printf("requisitaGarfo - saída %d\n", apaga);
		};
};
#endif
