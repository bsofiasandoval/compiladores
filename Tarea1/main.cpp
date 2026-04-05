#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "Table.h"
using namespace std;

void testStack(){
    cout << "=== STACK TEST ===" << endl;
    Stack<int> s;

    cout << "empty: " << (s.isEmpty() ? "true" : "false") << endl;

    cout << "pushing 1,2,3 to the stack" << endl;;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "size: " << s.size() << endl;
    cout << "top: " << s.getTop() << endl; 
    s.pop();
    cout << "popped once" << endl;
    cout << "top: " << s.getTop() << endl; 
  
    cout << "popping until empty" << endl;
    s.pop();
    s.pop();

    cout << "empty: " << (s.isEmpty() ? "true" : "false") << endl;

    try {
        s.pop();
    } catch(const out_of_range& e){
        cout << "pop on empty:" << e.what() << endl;
    }
    
    cout << endl;
}

void testQueue(){
    cout << "=== QUEUE TEST ===" << endl;
    Queue<string> q;
    
    cout << "empty: " << (q.isEmpty() ? "true" : "false") << endl;

    cout << "adding first,second, and third to the queue" << endl;
    q.push("first");
    q.push("second");
    q.push("third");

    cout << "size:" << q.size() << endl;
    cout << "front:" << q.getFront() << endl;
    cout << "back:" << q.getBack() << endl;
    
    q.pop();
    cout << "popped once" << endl;
    cout << "front:" << q.getFront() << endl;
    cout << "back:" << q.getBack() << endl;

    cout << "popping until empty" << endl;
    q.pop();
    q.pop();
    cout << "empty: " << (q.isEmpty() ? "true" : "false") << endl;

    try {
        q.pop();
    } catch(const out_of_range& e){
        cout << "pop on empty:" << e.what() << endl;
    }
    
    cout << endl;
}

void testTable(){
    cout << "=== TABLE TEST ===" << endl;
    Table<string, int> t;

    cout << "empty: " << (t.isEmpty() ? "true" : "false") << endl;

    cout << "inserting age:21, year:2026, schoolYear: 4" << endl;
    t.insert("age", 21);
    t.insert("year", 2026);
    t.insert("schoolYear", 4);

    cout << "size: " << t.size() << endl; // 3
    cout << "age: " << t.get("age") << endl; // 21

    cout << "overwrote age with 25" << endl;
    t.insert("age", 15);
    cout << "age:" << t.get("age") << endl;

    cout << "contains age: " << (t.contains("age") ? "true" : "false") << endl; // true
    cout << "contains name: " << (t.contains("name") ? "true" : "false") << endl; // false

    t.remove("age");
    cout << "removed age" << endl;
    cout << "contains age: " << (t.contains("age") ? "true" : "false") << endl; // false
    cout << "size: " << t.size() << endl; // 2

    // get on nonexistent key should throw
    try {
        t.get("age");
    } catch (const out_of_range& e) {
        cout << "get nonexistent key: " << e.what() << endl;
    }

    // remove on nonexistent key should throw
    try {
        t.remove("name");
    } catch (const out_of_range& e) {
        cout << "remove nonexistent key: " << e.what() << endl;
    }

    cout << endl;
    
}

int main(){
    testStack();
    testQueue();
    testTable();
    return 0;
}