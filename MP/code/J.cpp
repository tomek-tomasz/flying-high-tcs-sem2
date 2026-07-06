//
// Created by tomek on 4/14/26.
//


/*
jak zrobic tablice hashujaca?
co to jest?
to tablica ktora daje jakiemus abstrakcyjnemu obiektowi
liczbe mod N gdzie N to jest rozmiar tablicy hashujacej
robie to poprzez funkcje hashujace
pamietaj hashe w typie unsinged ? (cokolwiek to znaczy)


insert chce miec rozmiar tablicy
mniej wiecej dwa razy wiekszy od ilosci
elementow przechowywanych


przy wstawianiu mam tablice
funkcja hashujaca daje mi jakies miejsce w tablicy
jesli jest puste to wstawiam element
jesli jest zajete to skacze inna funkcja hashujaca ktora
sie nie zeruje oraz ktorej wartosci sa wzglednie pierwsze z N
zatem N to bedzie liczba pierwsza



musze tez deletowac
jak deletuje to mam problem
bo gdy ja szukam elementu w tablicy
to ja przechodze przez elementy dajace te sama liczbe przy hashowaniu
dopoki nie bedzie puste
no i jesli mi ktos usunie element
to mam problem

zatem jak usuwam element to wstawiam flage inna niz pole puste
np "-"
ona dziala dla find tak jakby to pole bylo zajete
a dla insert dziala jakby bylo puste

rehashowanie
wtedy gdy jest za duzo elementow = 1/2 N
wtedy gdy jest za duzo kreseczek = 1/4 N
*/


#include<iostream>
using namespace std;

struct car {
    char number[8]{};
    int penalty = -1;
};


unsigned long long p = 37;
unsigned long long P[8];

unsigned long long q = 41;
unsigned long long Q[8];

int car_counter=0, deleted_counter=0;

int k = 0;
int Size[17] = {53
,97
,193
,389
,769
,1543
,3079
,6151
,12289
,24593
,49157
,98317
,196613
,393241
,786433
,1572869
,3145739
};



unsigned int polynomial_hash(int N, const char key[8], const unsigned long long powers[8]) {
    unsigned int result = 0;
    for (int i=0; i<8; i++) result += key[i]*powers[7-i] % N;
    return result % N;
}


void insert(car* T, const car &to_add) {
    int N = Size[k];
    unsigned int hash = polynomial_hash(N, to_add.number, P);
    unsigned int hash_q = polynomial_hash(N, to_add.number, Q);
    if (hash_q == 0) hash_q = 1;

    int first_deleted = -1;

    while (true) {
        if (T[hash].penalty == -1) {
            if (first_deleted != -1) {
                T[first_deleted] = to_add;
                deleted_counter--;
            } else {
                T[hash] = to_add;
            }
            car_counter++;
            return;
        }

        if (T[hash].penalty == -2) {
            if (first_deleted == -1) first_deleted = hash;
        } else {
            bool flag = true;
            for (int i = 0; i < 8; ++i) {
                if (T[hash].number[i] != to_add.number[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                T[hash].penalty += to_add.penalty;
                return;
            }
        }

        hash += hash_q;
        hash %= N;
    }
}

int find(car* T, char number[8]) {
    int N = Size[k];
    unsigned int hash = polynomial_hash(N, number, P);
    unsigned int hash_q = polynomial_hash(N, number, Q);
    if (hash_q == 0) hash_q = 1;

    while (true) {
        if (T[hash].penalty == -1) return -1;

        if (T[hash].penalty >= 0) {
            bool flag = true;
            for (int i = 0; i < 8; ++i) {
                if (T[hash].number[i] != number[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) return T[hash].penalty;
        }

        hash += hash_q;
        hash %= N;
    }
}

int remove(car* T, char number[8]) {
    int N = Size[k];
    unsigned int hash = polynomial_hash(N, number, P);
    unsigned int hash_q = polynomial_hash(N, number, Q);
    if (hash_q == 0) hash_q = 1;

    while (true) {
        if (T[hash].penalty == -1) return -1;

        if (T[hash].penalty >= 0) {
            bool flag = true;
            for (int i = 0; i < 8; ++i) {
                if (T[hash].number[i] != number[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                int result = T[hash].penalty;
                T[hash].penalty = -2;
                deleted_counter++;
                car_counter--;
                return result;
            }
        }

        hash += hash_q;
        hash %= N;
    }
}

void rehash(car* &T) {
    deleted_counter = 0;
    car_counter = 0;
    int N = Size[k];
    k++;
    auto new_T = new car[Size[k]]{};
    for (int i=0; i<N; i++) {
        if (T[i].penalty < 0) continue;
        insert(new_T, T[i]);
    }
    delete[] T;
    T = new_T;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    P[0]=1;
    Q[0]=1;
    for (int i=1; i<8 ; i++) {
        P[i] = p*P[i-1];
        Q[i] = q*Q[i-1];
    }
    string instruction;
    car current_car{};
    int z, n;
    cin>>z;
    while(z--) {
        car_counter=0;
        deleted_counter=0;
        k=0;
        auto T = new car[Size[k]]{};
        cin>>n;
        for (int i=0; i<n; i++) {
            cin>>instruction;
            for (char & c : current_car.number) cin>>c;
            switch (instruction[0]) {
                case 'I' : {
                    cin>>current_car.penalty;
                    insert(T, current_car);
                    break;
                }
                case 'F' : {
                    int result = find(T, current_car.number);
                    if (result == -1) result = 0;
                    cout<<result<<'\n';
                    break;
                }
                case 'D' : {
                    int result = remove(T, current_car.number);
                    if (result == -1) cout<<"ERROR\n";
                    else {
                        for (char j : current_car.number) {
                            cout<<j;
                        }
                        cout<<' '<<result<<'\n';
                    }
                    break;
                }
                default: ;
            }
            if (car_counter > Size[k]/2 || deleted_counter > Size[k]/4) rehash(T);
        }
        delete[] T;
    }

}










