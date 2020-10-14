BINARIES := PriorityLock
all: $(BINARIES)

CFLAGS := $(CFLAGS) -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS

THREADLIBS := Lock.o PriorityLock.o thread.o CV.o

clean:
	rm -f *.o $(BINARIES)

PriorityLock: main.cc PriorityLock.o $(THREADLIBS)
	g++ $(CFLAGS) $^ -lpthread -lrt -o $@

kitchen.o: kitchen.cc
	g++ -c $(CFLAGS) $< -o $@

Lock.o: 3rdparty/Lock.cc
	g++ -c $(CFLAGS) $< -o $@

PriorityLock.o: PriorityLock.cc
	g++ -c $(CFLAGS) $< -o $@

thread.o: 3rdparty/thread.c
	gcc -c $(CFLAGS) $< -o $@

CV.o: 3rdparty/CV.cc
	g++ -c $(CFLAGS) $< -o $@
