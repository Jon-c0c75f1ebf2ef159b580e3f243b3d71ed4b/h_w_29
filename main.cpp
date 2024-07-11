#include "FineGrainedQueue.h"
#include <thread>

int main()
{
    FineGrainedQueue queue(new Node{ 10, new Node(20, nullptr) });

    std::thread t1([&queue]() { queue.insertIntoMiddle(30, 2); });
    std::thread t2([&queue]() { queue.insertIntoMiddle(40, 4); });
    std::thread t3([&queue]() { queue.insertIntoMiddle(50, 11); });
    std::thread t4([&queue]() { queue.insertIntoMiddle(60, 25); });
    std::thread t5([&queue]() { queue.insertIntoMiddle(70, 3); });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    queue._cout();

    return 0;
}
