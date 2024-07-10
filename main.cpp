#include "FineGrainedQueue.h"

int main()
{
    FineGrainedQueue queue(new Node{11, new Node(22, nullptr) } );
    
    queue.insertIntoMiddle(33, 2);
    queue.insertIntoMiddle(89, 2);
    queue.insertIntoMiddle(4, 89);
    queue.insertIntoMiddle(1655, 2);
    queue.insertIntoMiddle(99, 2);

    return 0;
}
