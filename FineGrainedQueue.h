//Напишите реализацию метода insertIntoMiddle(int value, int pos) для списка мелкогранулярной блокировкой. 
//Часть кода уже написана — сама структура списка взята из юнита про мелкогранулярную блокировку и приведена ниже.
//Функция должна вставить узел с переданным значением value в позицию pos. Чтобы не переусложнять реализацию, предполагается следующее:
// * очередь не пустая,
// * вставляется элемент в середину или конец списка, то есть вставку в начало списка не нужно рассматривать,
// * если pos больше длины списка, то нужно вставить элемент в конец списка.

#pragma once
#include <mutex>
#include <iostream>
#include <thread>

struct Node
{
    int _value;
    Node* _next;
    std::mutex* _node_mutex;
    Node(int value, Node* ptr = nullptr) : _value(value), _next(ptr) { _node_mutex = new std::mutex; }
    ~Node() { delete _node_mutex; }
};

class FineGrainedQueue
{
public:
    Node* _head;
    std::mutex* _queue_mutex;
    FineGrainedQueue(Node* node) : _head(node) { _queue_mutex = new std::mutex; };
    ~FineGrainedQueue() { delete _queue_mutex; }
    void insertIntoMiddle(int value, int pos) {
        //очередь не пустая
        //вставляется элемент в середину или конец списка, то есть вставку в начало списка не нужно рассматривать
        //соответственно начинаем со второй позиции i=0; ++i;
        Node* cur, * prev;
        int i = 1;

        _queue_mutex->lock();
        prev = _head; 
        cur = prev->_next;
        prev->_node_mutex->lock();
        if (cur) {// проверили и только потом залочили
            cur->_node_mutex->lock();
        }
        _queue_mutex->unlock();
        
        while (true) {
            //если pos больше длины списка, то нужно вставить элемент в конец списка.
            if (i >= pos || cur == nullptr) {
                //insert
                prev->_next = new Node{ value, cur };                
                if (cur) {// проверили и только потом залочили
                    cur->_node_mutex->unlock();
                }
                prev->_node_mutex->unlock();
                break;
            }
            ++i;
            Node* old_prev = prev;
            prev = cur;
            cur = cur->_next;          
            if (cur) {// проверили и только потом залочили
                cur->_node_mutex->lock();
            }
            old_prev->_node_mutex->unlock();
        }
    }

    void _cout() {
        std::unique_lock<std::mutex> guard(*(_queue_mutex));
        Node* cur = _head;
        while (cur != nullptr) {
            std::cout << cur->_value << "\n";
            cur = cur->_next;
        }
    }
};
