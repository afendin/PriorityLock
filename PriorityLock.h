#include <list>
using namespace std;

#include "3rdparty/Lock.h"
#include "3rdparty/CV.h"

struct PriorityCV
{
    int priority = 0;
    CV cv;
};

class PriorityLock
{
public:
    PriorityLock();

    void enter(int priority);
    void exit();
private:
    bool m_acquired; //if priority lock is acquired by some thread
    Lock m_lock;

    list<PriorityCV*> m_CVList; // list of waiting threads
};