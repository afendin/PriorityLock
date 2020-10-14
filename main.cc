#include <stdlib.h>
#include <stdio.h>
#include "PriorityLock.h"
#include "3rdparty/thread.h"

using namespace std;

#define NTHREADS 300

int k_number = 77;
PriorityLock pLock;

void guessNumber(int);

int main()
{
    thread_t workers[NTHREADS];

    // Hold the lock until all threads are created.
    // This makes it easy to assure that PriorityLock is working right.
    pLock.enter(0);
    for (int i = 0; i < NTHREADS; ++i) {
        int priority = random() % 100;
        thread_create(&workers[i], guessNumber, priority);
    }
    pLock.exit();

    for (int i = 0; i < NTHREADS; ++i) {
        thread_join(workers[i]);
    }

    return 0;
}

// Simple function to test PriorityLock.
// Threads allowed to guess the number according to their priority
void guessNumber(int threadPriority)
{
    int number = 0;

    pLock.enter(threadPriority);
    while (number != k_number) {
        number = random() % 100;
    }
    printf("Thread with priority %d guessed the number!\n", threadPriority);
    pLock.exit();
}