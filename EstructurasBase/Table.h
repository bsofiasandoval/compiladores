#pragma once
#include <map>
#include <iostream>
using namespace std;

template<class K, class V>
class Table{
    private:
        map<K, V> table;
    public:
        void insert(K key, V value);
        void remove(K key);
        V get(K key);
        bool contains(K key);
        bool isEmpty();
        int size();
};

template<class K,class V>
void Table<K, V>::insert(K key, V value){
    table[key] = value;
}

template<class K,class V>
void Table<K, V>::remove(K key){
    if(contains(key)){
        table.erase(key);
    } else{
        throw out_of_range("error, key not found");
    }
}

template<class K,class V>
V Table<K, V>::get(K key){
    if(contains(key)){
        return table.at(key);
    } else{
        throw out_of_range("error, key not found");
    }
}

template<class K,class V>
bool Table<K, V>::contains(K key){
    return table.find(key) != table.end();
}

template<class K,class V>
bool Table<K, V>::isEmpty(){
    return table.empty();
}

template<class K,class V>
int Table<K, V>::size(){
    return table.size();
}

