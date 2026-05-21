#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template<class T>
class Stack{
    private:
        Node<T>* top;
        int count;
    public:
        Stack();
        void push(T data);
        void pop();
        T getTop();
        bool isEmpty();
        int size();
        ~Stack();
};

template<class T>
Stack<T>::Stack(){
    top = nullptr;
    count = 0;
}

template<class T>
void Stack<T>::push(T data){
    Node<T>* newNode = new Node<T>(data, nullptr);
    newNode->next = top;
    top = newNode;
    count++;
}

template<class T>
void Stack<T>::pop(){
    if(!isEmpty()){
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        count--;
    } else{
        throw out_of_range("error, stack is empty");
    }
}

template<class T>
T Stack<T>::getTop(){
    if(!isEmpty()){
        return top->data;
    } else{
        throw out_of_range("error, stack is empty");
    }
}

template<class T>
bool Stack<T>::isEmpty(){
    return top == nullptr;
}

template<class T>
int Stack<T>::size(){
    return count;
}


template<class T>
Stack<T>::~Stack(){
    while(!isEmpty()){
        pop();
    }
}
