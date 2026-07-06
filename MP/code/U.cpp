//
// Created by tomek on 5/26/26.
//




/*
odwracam czas
sortuje po deadlinach i biore
ostatnia grupe ktora ma najpozniejszy deadline
dodaje te grupe do kopca minimum
licze czas pomiedzy deadlinem ktory dodalem
i poprzednim deadlinem
i robie
wyjmij dziecko z kopca minimum
jesli ono sie zdazy wyhustac w tym czasie to go usuwam
a jesli ono sie nie zdazy yhustac to husta sie tyle ile moze
i zmieniam jego wartosc o tyle ile hustal sie



struktura dziecko ma deadline i ile sie chce hustac

sort bedzie po deadline'ach
a kopiec ma sort po tym ile sie tam chce hustac

mozna przeladowac operator porownywania w jeden
sposob a w drugim uzyc sort(mozna lambde!)
(dziecko d1, dziecko d2) -> {return d1.deadline <= d2.deadline} chyba?




kopiec to drzewo zrownowazone co trzyma minimum w roocie
jesli chodzi o usuwanie minimum to
*/


#include <iostream>
#include <algorithm>

using namespace std;

struct Child {
    int d;
    int t;
};


int constexpr max_children = 1000000;
Child children[max_children];
int heap_data[max_children];
int heap_sz = 0;

void heap_push(int val) {
    heap_data[heap_sz] = val;
    int i = heap_sz;
    heap_sz++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap_data[i] < heap_data[p]) {
            int tmp = heap_data[i];
            heap_data[i] = heap_data[p];
            heap_data[p] = tmp;
            i = p;
        } else {
            break;
        }
    }
}

int heap_pop() {
    int res = heap_data[0];
    heap_data[0] = heap_data[--heap_sz];
    int i = 0;
    while (true) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;
        if (l < heap_sz && heap_data[l] < heap_data[smallest]) smallest = l;
        if (r < heap_sz && heap_data[r] < heap_data[smallest]) smallest = r;
        if (smallest != i) {
            int tmp = heap_data[i];
            heap_data[i] = heap_data[smallest];
            heap_data[smallest] = tmp;
            i = smallest;
        } else {
            break;
        }
    }
    return res;
}

bool compareChildren(const Child& a, const Child& b) {
    return a.d > b.d;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    if (cin >> z) {
        while (z--) {
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                cin >> children[i].d >> children[i].t;
            }
            sort(children, children + n, compareChildren);

            heap_sz = 0;
            int ans = 0;
            int current_time = children[0].d;
            int idx = 0;

            while (current_time > 0) {
                while (idx < n && children[idx].d >= current_time) {
                    heap_push(children[idx].t);
                    idx++;
                }

                int next_time = 0;
                if (idx < n) {
                    next_time = children[idx].d;
                }

                if (heap_sz == 0) {
                    current_time = next_time;
                    continue;
                }

                int available_time = current_time - next_time;
                while (available_time > 0 && heap_sz > 0) {
                    int needed = heap_pop();
                    if (needed <= available_time) {
                        available_time -= needed;
                        ans++;
                    } else {
                        heap_push(needed - available_time);
                        available_time = 0;
                    }
                }
                current_time = next_time;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}