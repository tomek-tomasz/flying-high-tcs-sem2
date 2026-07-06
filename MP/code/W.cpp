//
// Created by tomek on 6/2/26.
//



/*

drzewo przedzialowe?

w wierzcholku trzymam jakas wartosc jego
podrdrzewa reprezentujaca ten przedzial

jak chce zmienic wartosc gdzies to zmieniam i potem
od nowa licze funkcje na przodkach i ich dzieciach

dostaje przedzial i mam polizyczc wartosc z przedzialu
no to znajduje delikwentow brzegowych
i zaczynam od lewego liscia
ide do lca zaznaczajac prawe wiszace wierzcholki tzn
jesli przyszedlem od lewego dziecka to zaznaczam prawe

no i analogicznie dla praweo delikwenta

mozna to rekurencja zrobic
zaczynam od roota

patrze na dzieci ewaluowanego wierzcholka
jesli ktores dziecko jest rozlaczne z przedzialem to je
ignoruje i sie wywoluje tylko na tym drugim ktore nie jest
jesli w caloscie zawieram sie w przedziale to zaznaczam i koncze
jesli w czesci to dziele sie na pol i lece dalej



tworze vector w ktorym elementy to zdarzenia typu
poczatek przedzialu poziomego, koniec przedzialu poziomego
pionowy odcinek
sotuje je po wspolrzednych ale najwazniejszy jest poczatek odcinka
potem jest pionowy odcinek
a na koncu koniec odcinka

tworze drzewo przedzialowe w ktorym liscmi sa wspolrzedne y-kowe
jesli napotykam w vectorze posortowanym
na poczatek odcinka to dodaje 1 do jego wspolrzednej
y-kowey w drzewie
jesli na pionowy odcinek to pytam sie
drzewa przedzialowego o przedzial na wspolrzednych y-kowych
jego
jesli na koncowy odcinek to odejmuje 1 od jego wspolrzednej
y-kowej w drzewie



jak tworze drzewo przedzialowe o k wierzcholkach?
znajduje pierwsze takie l ze k <= 2^l
potem tworze tablice dlugosci 2m albo 2m-1
i zapamietuje gdzie zaczynaja sie liscie
i ja zeruje
teraz gdy chce dodawac na i-ty lisc no to mam

to samo tez musze policzyc dla poziomych odcinkow
analogicznie




*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
    int x, type, y1, y2, id;

    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type < other.type;
    }
};

const int M = 131072;
int tree[2 * M];

void add(int pos, int val) {
    pos += M;
    while (pos > 0) {
        tree[pos] += val;
        pos /= 2;
    }
}

int query(int left, int right) {
    left += M;
    right += M;
    int sum = 0;
    if (left <= right) {
        if (left == right) return tree[left];
        sum += tree[left] + tree[right];
        while (left / 2 != right / 2) {
            if (left % 2 == 0) sum += tree[left + 1];
            if (right % 2 == 1) sum += tree[right - 1];
            left /= 2;
            right /= 2;
        }
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    if (cin >> z) {
        while (z--) {
            int n, K;
            cin >> n >> K;

            vector<Event> events1, events2;
            vector<int> ans(n, 0);

            for (int i = 0; i < n; ++i) {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;

                if (x1 > x2) swap(x1, x2);
                if (y1 > y2) swap(y1, y2);

                if (x1 == x2) {
                    events1.push_back({x1, 2, y1, y2, i});
                    events2.push_back({y1, 1, x1, x1, i});
                    events2.push_back({y2, 3, x1, x1, i});
                } else {
                    events1.push_back({x1, 1, y1, y1, i});
                    events1.push_back({x2, 3, y1, y1, i});
                    events2.push_back({y1, 2, x1, x2, i});
                }
            }

            sort(events1.begin(), events1.end());
            for (const auto& ev : events1) {
                if (ev.type == 1) add(ev.y1, 1);
                else if (ev.type == 2) ans[ev.id] += query(ev.y1, ev.y2);
                else if (ev.type == 3) add(ev.y1, -1);
            }

            sort(events2.begin(), events2.end());
            for (const auto& ev : events2) {
                if (ev.type == 1) add(ev.y1, 1);
                else if (ev.type == 2) ans[ev.id] += query(ev.y1, ev.y2);
                else if (ev.type == 3) add(ev.y1, -1);
            }

            for (int i = 0; i < n; ++i) {
                cout << ans[i] << "\n";
            }
        }
    }
    return 0;
}