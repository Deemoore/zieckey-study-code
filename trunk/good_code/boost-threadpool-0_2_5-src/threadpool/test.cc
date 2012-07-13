#include <iostream>
#include "boost/threadpool.hpp"

using namespace std;
using boost::threadpool::pool;

// Some example tasks
void first_task()
{
    cout << "first task is running\n" ;
}

void second_task()
{
    cout << "second task is running\n" ;
}

void task_with_parameter(int value)
{
    cout << "task_with_parameter(" << value << ")\n";
}

int main(int argc,char *argv[])
{
    // Create fifo thread pool container with two threads.
    pool tp(22);

    for (int i = 0; i < 1000; ++i)
    {
        // Add some tasks to the pool.
        tp.schedule(&first_task);
        tp.schedule(&second_task); 
        tp.schedule(boost::bind(task_with_parameter, 4));
    }

    // Wait until all tasks are finished.
    tp.wait();

    // Now all tasks are finished!    
    return(0);
}
