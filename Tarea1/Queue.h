#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template <class T>
class Queue{
    private:
        Node<T>* front;
        Node<T>* back;
        int count;
    public:
        Queue();
        void push(T data);
        void pop();
        T getFront();
        T getBack();
        bool isEmpty();
        int size();
        ~Queue();
};

template <class T>
Queue<T>::Queue(){
    front = nullptr;
    back = nullptr;
    count = 0;
}

template<class T>
void Queue<T>::push(T data){
    Node<T>* newNode = new Node<T>(data,nullptr);
    if(!isEmpty()){
        back->next = newNode;
        back = newNode;
    } else{
        front = back = newNode;
    }
    count++;
}

template<class T>
void Queue<T>::pop(){
    if(!isEmpty()){
        Node<T>* temp = front;
        front = front->next;
        delete temp;
        count--;
    } else{
        throw out_of_range("error, queue is empty");
    }
}

template<class T>
T Queue<T>::getFront(){
    if(!isEmpty()){
        return front->data;
    }
    else{
        throw out_of_range("error, queue is empty");
    }
}

template<class T>
T Queue<T>::getBack(){
    if(!isEmpty()){
        return back->data;
    }
    else{
        throw out_of_range("error, queue is empty");
    }
}

template<class T>
bool Queue<T>::isEmpty(){
    return front == nullptr;
}

template<class T>
int Queue<T>::size(){
    return count;
}

template<class T>
Queue<T>::~Queue(){
    while(!isEmpty()){
        pop();
    }
}