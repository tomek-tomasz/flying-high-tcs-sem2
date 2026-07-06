/*
zeby odwrocic liste potrzebuje glowy i ogona
zeby polaczyc dwa pociagi usuwam tail i lacze wiesz te dwa 

moj pomysl to jest ze znacznikuje node jesli trzeba zmienic kierunek poruszania sie po liscie
z lewej na prawo lub z prawej na lewo

ale to jest lepsze:
mozna tez sprawdzac czy nastepny wraca do poprzedniego i isc innym niz ten ktory powraca do node'a w ktorym sie zmienia.
zrob sobie funkcje ktora decyduje w ktora strone jest next.

zrob tablice wskaznikow:
Node* t[2]

dwa node'y po kolei a, b
kierunek 0 lub kierunek 1
if(b -> t[0] == a) return 0;
return 1

to jest nasza decyzja b->[b->t[0]==a] lubie to!
*/


#include <iostream>
using namespace std;

template<class T>
class node {
public:
    T content;
    node* t[2];
    node(T& name) {
        content = name;
    }
    node() {}
    node<T>* next(node<T>* prev) {
        return t[t[0]==prev];
    }
    node<T>* prev(node<T>* next) {
        return t[t[0]==next];
    }
    void link_next(node<T>* next, node<T>* new_next) {
        t[t[1]==next] = new_next;
    }
    void link_prev(node<T>* prev, node<T>* new_prev) {
        t[t[1]==prev] = new_prev;
    }
};

template<class T>
class doubleList {
private:
    string list_name;
    node<T>* head;
    node<T>* tail;
public:
    doubleList(const string& train_name) {
        list_name = train_name;
        head = new node<T>;
        tail = new node<T>;
        head->t[0] = nullptr;
        head->t[1] = tail;
        tail->t[0] = head;
        tail->t[1] = nullptr;
    }

    doubleList(const string& train_name, T name) {
        list_name = train_name;
        auto first_person = new node(name);
        head = new node<T>;
        tail = new node<T>;
        head->t[0] = nullptr;
        head->t[1] = first_person;
        first_person->t[0] = head;
        first_person->t[1] = tail;
        tail->t[0] = first_person;
        tail->t[1] = nullptr;
    }

    void addFirst(T& name) {
        auto new_person = new node(name);
        node<T>* pom = head->t[1];
        pom->link_prev(head, new_person);
        new_person->t[0] = head;
        new_person->t[1] = pom;
        head->t[1] = new_person;
    }

    void addFirst(node<T>* n) {
        node<T>* pom = head->t[1];
        pom->link_prev(head, n);
        n->t[0] = head;
        n->t[1] = pom;
        head->t[1] = n;
    }

    void addLast(T& name) {
        auto new_person = new node(name);
        node<T>* pom = tail->t[0];
        pom->link_next(tail, new_person);
        new_person->t[0] = pom;
        new_person->t[1] = tail;
        tail->t[0] = new_person;
    }

    void addLast(node<T>* n) {
        node<T>* pom = tail->t[0];
        pom->link_next(tail, n);
        n->t[0] = pom;
        n->t[1] = tail;
        tail->t[0] = n;
    }

    node<T>* detachFront() {
        if (empty()) return nullptr;
        node<T>* to_detach = head->t[1];
        to_detach->next(head)->link_prev(to_detach, head);
        head->t[1] = to_detach->next(head);
        return to_detach;
    }

    node<T>* detachLast() {
        if (empty()) return nullptr;
        node<T>* to_detach = tail->t[0];
        to_detach->prev(tail)->link_next(to_detach, tail);
        tail->t[0] = to_detach->prev(tail);
        return to_detach;
    }

    void reverse() {
        if (empty()) return;
        node<T>* first = head->t[1];
        node<T>* last = tail->t[0];
        first->link_prev(head,tail);
        last->link_next(tail,head);
        head->t[1] = last;
        tail->t[0] = first;
    }

    void unionn(doubleList<T>& L) {
        if (L.empty()) return;
        node<T>*  old_last = tail->t[0];
        tail->t[0] = L.tail->t[0];
        tail->t[0]->link_next(L.tail, tail);
        old_last->link_next(tail, L.head->t[1]);
        L.head->t[1]->link_prev(L.head, old_last);
        L.head->t[1] = L.tail;
        L.tail->t[0] = L.head;
    }

    void clean() {
        if (empty()) return;
        node<T>* previous = head;
        node<T>* current = head->t[1];
        node<T>* next = current->next(previous);
        while (next != tail) {
            previous = current;
            current = next;
            next = current->next(previous);
            delete previous;
        }
        if (current != head && current != tail && current != nullptr) delete current;
        if (next != head && next != tail && next != nullptr ) delete next;
        head->t[1] = tail;
        tail->t[0] = head;
    }
    void print() {
        cout<<'\"'<<list_name<<"\":\n";
        if (empty()) {
            cout<<'\n';
            return;
        }
        node<string>* previous = head;
        node<string>* current = head->t[1];
        node<string>* next = current->next(previous);
        while (next != nullptr) {
            previous = current;
            current = next;
            next = current->next(previous);
            cout<<previous->content;
            if (next!=nullptr) cout<<"<-";
        }
        cout<<'\n';
    }
    bool empty() {
        return head->t[1]==tail;
    }
    string getname() {
        return list_name;
    }

    ~doubleList() {
        clean();
        delete head;
        delete tail;
    }
};




int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z,n;
    cin>>z;
    while(z--){
        cin>>n;
        doubleList<string>* trains[20];
        for (auto & train : trains) train=nullptr;
        while (n--) {
            string instruction;
            cin>>instruction;
            switch (instruction[0]) {
                case 'N': {//NEW
                    string Train, Person;
                    cin>>Train>>Person;
                    auto* new_train = new doubleList<string>(Train, Person);
                    for (auto & train : trains) {
                        if (train==nullptr) {
                            train = new_train;
                            break;
                        }
                    }
                    break;
                }
                case 'B': {//BACK
                    string Train, Person;
                    cin>>Train>>Person;
                    for (auto & train : trains) {
                        if (train != nullptr && train->getname() == Train) {
                            train->addLast(Person);
                            break;
                        }
                    }

                    break;
                }
                case 'F': {//FRONT
                    string Train, Person;
                    cin>>Train>>Person;
                    for (auto & train : trains) {
                        if (train != nullptr && train->getname() == Train) {
                            train->addFirst(Person);
                            break;
                        }
                    }
                    break;
                }
                case 'P': {//PRINT
                    string Train;
                    cin>>Train;
                    for (auto & train : trains) {
                        if (train != nullptr && train->getname() == Train) {
                            train->print();
                            break;
                        }
                    }
                    break;
                }
                case 'R': {//REVERSE
                    string Train;
                    cin>>Train;
                    for (auto & train : trains) {
                        if (train != nullptr && train->getname() == Train) {
                            train->reverse();
                            break;
                        }
                    }
                    break;
                }
                case 'U': {//UNION
                    string Train1, Train2;
                    cin>>Train1>>Train2;
                    doubleList<string> *train1=nullptr, *train2=nullptr;
                    for (auto & train : trains) {
                        if (train != nullptr && train->getname() == Train1) {
                            train1=train;
                            if (train1!=nullptr && train2!=nullptr) {
                                break;
                            }
                        }
                        else if (train != nullptr && train->getname() == Train2) {
                            train2=train;
                            train = nullptr;
                            if (train1!=nullptr && train2!=nullptr) {
                                break;
                            }
                        }
                    }
                    train1->unionn(*train2);
                    delete train2;
                    break;
                }
                case 'D': {

                    if (instruction[3]=='F') {//DELFRONT
                        string Train1, Train2;
                        cin>>Train1>>Train2;
                        doubleList<string> *train2=nullptr;
                        node<string> *detached;
                        for (auto & train : trains) {
                            if (train != nullptr && train->getname() == Train2) {
                                train2=train;
                                detached = train2->detachFront();
                                if (train2->empty()) {
                                    delete train2;
                                    train = nullptr;
                                }
                            }
                        }

                        auto* new_train = new doubleList<string>(Train1);
                        new_train->addFirst(detached);
                        for (auto & train : trains) {
                            if (train==nullptr) {
                                train = new_train;
                                break;
                            }
                        }


                    }else {//DELBACK
                        string Train1, Train2;
                        cin>>Train2>>Train1;
                        doubleList<string> *train2=nullptr;
                        node<string> *detached;
                        for (auto & train : trains) {
                            if (train != nullptr && train->getname() == Train2) {
                                train2=train;
                                detached = train2->detachLast();
                                if (train2->empty()) {
                                    delete train2;
                                    train=nullptr;
                                }
                            }
                        }
                        auto* new_train = new doubleList<string>(Train1);
                        new_train->addFirst(detached);
                        for (auto & train : trains) {
                            if (train==nullptr) {
                                train = new_train;
                                break;
                            }
                        }

                    }
                }
                default: ;
            }
        }
        for  (auto & train : trains) {
            if (train!=nullptr) delete train;
        }


    }
}













