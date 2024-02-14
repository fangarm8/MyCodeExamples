#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdlib.h>

using namespace std;

template <class T>
struct node {
    T info;
    node* next;

    node() {
        info = -1;
        next = nullptr;
    }
    node(T s, node* p) {
        info = s;
        next = p;
    }
    node(const node& n) {
        info = n.info;
        next = n.next;
    }
    ~node() {}
};

template <class T>
class Stack {
    node<T>* head;
public:
    Stack() {
        head = nullptr;
    }
    Stack(const Stack<T>& l) {
        Stack<T> l2;
        node<T>* temp = l.head;
        while (temp != nullptr) {
            l2.push(temp -> info);
            temp = temp -> next;
        }
        while (l2.head != nullptr) {
            push(l2.pop());
        }
    }
    
    void push(T s) {
        node<T>* p = new node<T>(s, head);        //вызов конструктора node(string s,node*p)
        head = p;
    }
    void print() {
        node<T>* p = head;
        while (p != nullptr) {
            cout << p -> info << " ";
            p = p -> next;
        }
    }
    T pop() {
        if (head != nullptr) {
            T s = head -> info;
            node<T>* p = head;
            head = p -> next;
            delete p;
            return s;
        } 
        else {
            cout << "The queue is empty";
            return NULL;
        }
    }
    node<T>* gethead() {
        return head;
    }
};

template <class T>
class Queue {
    node<T>* head;
    node<T>* tail;
public:
    Queue() {
        head = nullptr;
        tail = nullptr;
    }
    node<T>* gethead() {
        return head;
    }
    void print() {
        node<T>* p = head;
        while (p != nullptr) {
            cout << p -> info << " ";
            p = p -> next;
        }
    }
    void push_back(T x) {
        node<T>* temp = new node<T>(x, nullptr);
        if (tail != nullptr)
            tail -> next = temp;
        else {
            head = temp;
        }
        tail = temp;
    }
    T pop() {
        if (head != nullptr) {
            T s = head -> info;
            node<T>* p = head;
            head = p -> next;
            delete p;
            return s;
        } 
        else {
            cout << "The queue is empty";
            return NULL;
        }
    }
    T pop_read() {
        if (head == nullptr)
            return 0;
        else
            return head -> info;
    }
    T back_read() {
        if (tail == nullptr)
            return 0;
        else
            return tail->info;
    };
};

void solution() {
    ifstream in("graph.txt");
    int v, h;
    in >> v >> h; in.ignore();
    Stack<int>* graphList = new Stack<int>[v];
    for (int i = 0; i < h; i++) {
        int j, tempV;
        in >> j >> tempV;
        graphList[j - 1].push(tempV);
        graphList[tempV - 1].push(j);
        in.ignore();
    }
    for (int i = 0; i < v; i++) {
        cout << i + 1 << ": "; 
        graphList[i].print(); 
        cout << endl;
    }
    cout << "_____________________\n";
    
    int* mark = new int[v + 1];
    int* count = new int[v + 1];
    for (int i = 0; i < v + 1; i++) {
        mark[i] = 0;
        count[i] = 0;
    }

    Queue<int> graph;
    int v_copy = v;
    cout << "Choose the point from 1 to " << v_copy << ": ";
    do { 
        cin >> v; 
    } while(v > v_copy && v < 1);
    mark[v] = 1;
    graph.push_back(v);
    node<int>* grP = graph.gethead();
    int c = 0;
    while(grP != nullptr) {
        node<int>* p = graphList[grP->info - 1].gethead();
        while (p != nullptr) {
            if (mark[p->info] == 0) {
                graph.push_back(p->info);
                count[c]++;
                mark[p->info] = 1;
                p = p->next;
            }
            else {
                p = p->next;
            }
        }
        grP = grP->next;
        c++; 
    }
    graph.pop();
    int steps = 1;
    for (int i = 0; i < v_copy + 1; i++) {
        int v_temp;
        for (int j = 0; j < count[i]; j++) {
            v_temp = graph.pop();
            cout << "Steps from " << v << " to " << v_temp << " is " << steps << endl;
        }
        if (count[i] != 0)
            steps++;

    }
    for (int i = 0; i < v_copy; i++) {
        if (mark[i+1] == 0)
            cout << "Steps from " << v << " to " << i+1 << " is infinite" << endl;
    }
    cout << endl;
}

int main() {
    solution();
    return 0;
}
