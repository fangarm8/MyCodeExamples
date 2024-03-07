#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Exeption {};

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
    ~Stack() {
        delete head;
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
            throw(Exeption());
        }
    }
    T pop_read(unsigned int n) {
        node<T>* p = head;
        for (unsigned int i = 0; i < n; i++) {
            if (p != nullptr) {
                p = p->next;
            }
            else {
                throw(Exeption());
            }
        }
        T s = p->info;
        return s;
    }
    unsigned int size() {
        node<T>* p = head;
        unsigned int size(0);
        while(p != nullptr) {
            p = p->next;
            size++;
        }
        return size;
    }
};

class point {
public:
    double x;
    double y;
    point() {
        x = 0; y = 0;
    }
    point(double a, double b) {
        x = a; y = b;
    }
    point(const point& b) {
        x = b.x;
        y = b.y;
    }
    point operator= (const point& b) {
        this->x = b.x;
        this->y = b.y;
        return *this;
    }
    point operator+ (const point& b) {
        double x_new = this->x + b.x;
        double y_new = this->y + b.y;
        point ans(x_new, y_new);
        return ans;
    }
    point operator- (const point& b) {
        double x_new = this->x - b.x;
        double y_new = this->y - b.y;
        point ans(x_new, y_new);
        return ans;
    }
    double operator^ (const point& b) {
        return ((this->x*b.y) - (b.x*this->y));
    }
    friend istream& operator>> (istream& in, point& p) {
        double x_in, y_in;
        in >> x_in >> y_in;
        p.x = x_in; p.y = y_in;
        return in;
    }
    friend ostream& operator<< (ostream& out, point& p) {
        out << p.x << ", " << p.y;
        return out;
    }
};

Stack<point> graham(vector<point>& points) {
    Stack<point> ans;
    if (!points.empty()) {
        point p0 = points[0];
        for (int i = 1; i < (int) points.size(); i++) {
            if(points[i].y < p0.y || (points[i].y == p0.y && points[i].x < p0.x)) {
                p0 = points[i];
            }
        }
        sort(points.begin(), points.end(), [&](point p1, point p2){
            return ((p0 - p1)^(p0 - p2)) >= 0;
        });
        for (int i = 0; i < (int) points.size(); i++) {
            while (ans.size() >= 2) {
                try {
                    point new_vector = points[i] - ans.pop_read(0);
                    point last_vector = ans.pop_read(0) - ans.pop_read(1);
                    if ((new_vector ^ last_vector) > 0) {
                        ans.pop();
                    } else {
                        break;
                    }
                }
                catch(Exeption) {
                    cout << "Something went wrong";
                }
            }
            ans.push(points[i]);
        }
    } else {
        cout << "There aren't any points!";
    }
    return ans;
}

int main() {
    vector<point> points; int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        point p;
        cin >> p;
        points.push_back(p);
    }
    Stack<point> Gr = graham(points);
    cout << "_______" << endl;
    Gr.print();
    return 0;
}
