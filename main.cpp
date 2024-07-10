#include "FineGrainedQueue.h"
#include <thread>

int main()
{
    FineGrainedQueue queue(new Node(10, nullptr));

    std::thread t1([&queue]() { queue.insertIntoMiddle(20, 15); });
    std::thread t2([&queue]() { queue.insertIntoMiddle(30, 15); });
    std::thread t3([&queue]() { queue.insertIntoMiddle(40, 15); });
    std::thread t4([&queue]() { queue.insertIntoMiddle(50, 15); });
    std::thread t5([&queue]() { queue.insertIntoMiddle(60, 15); });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join(); 
    
    queue._cout();

    return 0;
}
