#include<iostream>
using namespace std;
template<class c>
class myPair {
public:
    c first;
    c second;
    bool operator ==(myPair a) {
        return first == a.first && second == a.second;
    }
};


template<class c, class o>
class stackMin{
private:
        c* content;
        c* minima;
        o cmp = o();
        int capacity;
        int size;
        int minima_size;
public:
    stackMin(int a = 4){
        content = new c[a];
        minima = new c[a];
        capacity = a;
        size = 0;
        minima_size = 0;
    }

    void push(c x){
        if (capacity==size) {
            int new_capacity;
            if (size == 0 ) new_capacity = 1;
            else new_capacity = 2*capacity;
            c* new_content = new c[new_capacity];
            c* new_minima = new c[new_capacity];
            for(int i=0; i<size; i++) new_content[i] = content[i];
            for(int i=0; i<size; i++) new_minima[i] = minima[i];
            delete[] content;
            delete[] minima;
            content=new_content;
            minima=new_minima;
            capacity=new_capacity;
        }
        if (size == 0) {
            minima[0] = x;
            minima_size++;
        }else if (cmp(x,minima[minima_size-1]) || minima[minima_size-1]==x) {
            minima[minima_size] = x;
            minima_size++;
        }
        content[size] = x;
        size++;
    }

    bool pop(){
        if(size==0) return false;
        if (content[size-1] == minima[minima_size-1]) minima_size--;
        size--;
        return true;
    }

    c top(){
        return content[size-1];
    }

    bool empty() {
        if(size==0) return true;
        return false;
    }

    c min() {
        return minima[minima_size-1];
    }

    void clear(){
        size = 0;
        minima_size = 0;
    }
    ~stackMin(){
        delete[] content;
        delete[] minima;
    }
};


template<class c, class o>
class queueMin{
private:
    stackMin<c, o>* left_stack;
    stackMin<c, o>* right_stack;
    o cmp = o();
public:
    queueMin(int a = 4) {
        left_stack = new stackMin<c, o>(a);
        right_stack = new stackMin<c, o>(a);
    }
    void enqueue(c x) {
        left_stack->push(x);
    }
    bool dequeue() {
        if (right_stack->empty()) {
            if (left_stack->empty()) return false;
            while (!left_stack->empty()) {
                right_stack->push(left_stack->top());
                left_stack->pop();
            }
        }
        return right_stack->pop();
    }
    c front() {
        if (right_stack->empty()) {
            while (!left_stack->empty()) {
                right_stack->push(left_stack->top());
                left_stack->pop();
            }
        }
        return right_stack->top();
    }
    c min() {
        if (left_stack->empty()) return right_stack->min();
        if (right_stack->empty()) return left_stack->min();
        if (cmp(left_stack->min(),right_stack->min())) return left_stack->min();
        return right_stack->min();
    }
    bool empty() {
        return left_stack->empty() && right_stack->empty();
    }
    void clear() {
        left_stack->clear();
        right_stack->clear();
    }
    ~queueMin() {
        delete left_stack;
        delete right_stack;
    }
};

/*
w pasach o dlugosci k+1 minimalizujemy sumy najlzejszego i drugiego najlzejszego dziecka.
robie kolejke i szukam minimow przed jakims kolega
to idzie tak
dla kazdego elementu sprawdzam najlzejsze legalne dziecko za nim za pomoca kolejki
w ten sposob przejde na pewno kiedys przez najlzejsza legalna pare i ja zwracam.
*/


class cmp_weights {
public:
    bool operator()(const myPair<int> &a, const myPair<int> &b) {
        return a.second<b.second || (a.second == b.second && a.first< b.first);
    }
};



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string a1,a2;
    int z,n,k;
    cin>>z;
    while(z--){
        cin>>n>>k;
        myPair<int> kids[n];

        for(int i=0; i<n; i++) {
            kids[i].first = i;
            cin>>kids[i].second;
        }
        auto queue = queueMin<myPair<int>, cmp_weights>(k+2);

        int l=0,r=1,min_weight=kids[l].second+kids[r].second;
        queue.enqueue(kids[l]);
        queue.enqueue(kids[r]);
        for (int i=2; i<n; i++) {
            if (i>k) queue.dequeue();
            auto min_i = queue.min();
            if (min_weight>min_i.second+kids[i].second) {
                min_weight = min_i.second + kids[i].second;
                l = min_i.first;
                r = i;
            }
            queue.enqueue(kids[i]);

        }
        cout<<min_weight<<' '<<l<<' '<<r<<'\n';


    }
}