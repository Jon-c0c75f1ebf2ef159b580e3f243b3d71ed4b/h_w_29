//Напишите реализацию метода insertIntoMiddle(int value, int pos) для списка мелкогранулярной блокировкой. 
//Часть кода уже написана — сама структура списка взята из юнита про мелкогранулярную блокировку и приведена ниже.
//Функция должна вставить узел с переданным значением value в позицию pos. Чтобы не переусложнять реализацию, предполагается следующее:
// * очередь не пустая,
// * вставляется элемент в середину или конец списка, то есть вставку в начало списка не нужно рассматривать,
// * если pos больше длины списка, то нужно вставить элемент в конец списка.

#pragma once
#include <mutex>
//#include <shared_mutex>
//#include <condition_variable>

struct Node
{
  int _value;
  Node* _next;
  std::mutex* _node_mutex;
  Node(int value, Node* ptr) : _value(value), _next(ptr) {}
};

class FineGrainedQueue
{
public:
  Node* _head;
  std::mutex* _queue_mutex;
  FineGrainedQueue(Node* node) : _head(node) {_queue_mutex = new std::mutex;};
  ~FineGrainedQueue() {        delete _queue_mutex;    }
  void insertIntoMiddle(int value, int pos) {

        Node* insertNode = new Node{value, nullptr};
        Node* cur = _head;
        Node* tmp = nullptr;
        int i = 0;
      
        {
            //очередь не пустая
            //вставляется элемент в середину или конец списка, то есть вставку в начало списка не нужно рассматривать
            tmp = cur;
            cur = cur->_next;
            i++;
        }
      
        while(true) {
          
            //если pos больше длины списка, то нужно вставить элемент в конец списка.
            if (i == pos || cur == nullptr) {
                //insert
                insertNode->_next = cur;
                tmp->_next = insertNode;
                break;
            }
            
            ++i;
            cur = cur->_next;
        }
        
        
    }
};



