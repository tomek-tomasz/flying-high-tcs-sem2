/*
min na stosie przechowuje pary - kogo dodalem i kto w danym momencie jest minimum

drugi sposob - przechowuje dwa stosy - jeden przechowujacy dane a drugi przechowujacy minima,
jesli minima sa sciagane ze stosu z danymi to sciagam tez je do stosu z minimami
uwaga - jesli minimum sie powtarza to dwa razy dodaje je na stos z minimami.
*/


#include<iostream>
using namespace std;

template<class c>
class myPair {
public:
    c first;
    c second;
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


/*
min w kolejce
tworze druga kolejke w ktorej moge usuwac z obu stron i dodawac tylko z jednej
przechowuje tam elementy ktore moga byc minimami, to znaczy ta kolejka jest zawsze niemalejaca
jesli przyjdzie mi liczba ktora jest mniejsza od konca to usuwam do momentu kiedy bedzie niemalejaca
zrzucajac minimum z kolejki z danymi zrzucam ja z kolejki z minimami.

mozemy tez zaimplemetowac kolejke dwoma stosami z minimum
kiedy enqueue do kolejki do daje na pierwzy stos i jesli chce dequeue to jesli drugi stos jest pusty
przerzucam wszystkie elementy pierwszego stosu do niego, a jesli jest niepusty to usuwam jeden element z drugiego stosu
W ten sposob biorac minimum z obu minimow mamy kolejke z minimum
*/


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


template<class c, class o>
void solveStack(stackMin<c,o> & S, int n) {
    string instruction;
    for (int i=0; i<n; i++) {
        cin>>instruction;
        switch (instruction[0]) {

            case 'p': {
                if (instruction[1] == 'o') {
                    if (S.empty()) cout<<"ERROR"<<'\n';
                    else {
                        cout<<S.top()<<'\n';
                        S.pop();
                    }

                }
                else {
                    c x;
                    cin>>x;
                    S.push(x);
                }
                break;
            }
            case 't': {
                if (S.empty()) cout<<"EMPTY\n";
                else cout<<S.top()<<'\n';
                break;
            }
            case 'm': {
                if (S.empty()) cout<<"EMPTY\n";
                else cout<<S.min()<<'\n';
                break;
            }
            case 'c': {
                S.clear();
                break;
            }
            case 'e': {
                if (S.empty()) cout<<"YES\n";
                else cout<<"NO\n";
                break;
            }
        }
     }
}


template<class c, class o>
void solveQueue(queueMin<c,o> & S, int n) {
    string instruction;
    for (int i=0; i<n; i++) {
        cin>>instruction;
        switch (instruction[0]) {
            case 'e': {
                if (instruction[1] == 'm') {
                    if (S.empty()) cout<<"YES\n";
                    else cout<<"NO\n";
                }
                else {
                    c x;
                    cin>>x;
                    S.enqueue(x);
                }
                break;
            }
            case 'f': {
                if (S.empty()) cout<<"EMPTY\n";
                else cout<<S.front()<<'\n';
                break;
            }
            case 'd': {
                if (S.empty()) cout<<"ERROR\n";
                else {
                    cout<<S.front()<<'\n';
                    S.dequeue();
                }
                break;

            }
            case 'c': {
                S.clear();
                break;
            }
            case 'm': {
                if (S.empty()) cout<<"EMPTY\n";
                else cout<<S.min()<<'\n';
                break;
            }
        }
    }
}

