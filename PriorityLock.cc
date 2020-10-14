#include "PriorityLock.h"

PriorityLock::PriorityLock()
{
    m_acquired = false;
}

void PriorityLock::enter(int priority)
{
    //every thread creates a Condition Variable object for itself
    PriorityCV *pcv = new PriorityCV;
    pcv->priority = priority;

    m_lock.acquire();
    //and adds itself to the list of waiting threads
    m_CVList.push_back(pcv);

    //if priority lock is already acquired, current thread waits for it
    while (m_acquired == true) {
        pcv->cv.wait(&m_lock);
    }

    //then thread acquires lock for itself, removes itself from waiting list
    // and deletes its Condition Variable object
    m_acquired = true;
    m_CVList.remove(pcv);
    delete pcv;
    m_lock.release();
}

void PriorityLock::exit()
{
    m_lock.acquire();
    //release the priority lock
    m_acquired = false;


    //if list of waiting threads is not empty find thread
    // with highest priority number and wake it up by calling
    // signal() method on its Condition Variable object
    if (m_CVList.size() > 0) {
        list<PriorityCV*>::iterator it = m_CVList.begin();
        list<PriorityCV*>::iterator maxPriorityCV = it;
        int maxPriorityNumber = (*it)->priority;

        for (; it != m_CVList.end(); ++it) {
            if ((*it)->priority > maxPriorityNumber){
                maxPriorityCV = it;
                maxPriorityNumber = (*it)->priority;
            }
        }
        (*maxPriorityCV)->cv.signal();
    }
    m_lock.release();
}