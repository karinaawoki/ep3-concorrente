CC=g++
CFLAGS=  -Wall -pedantic -ansi -pthread -lgmpxx -lgmp -g -std=c++11
RM=rm -f

ep: filosofos.o monitor.o 
	$(CC) $(CFLAGS) $^ -o $@

filosofos.o: src/filosofos.cpp
	$(CC) $(CFLAGS) -c $^

monitor.o: src/monitor.hpp src/monitor.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *.gch *~ src/*.o src/*~ 
