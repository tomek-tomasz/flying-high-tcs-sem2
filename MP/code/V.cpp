//
// Created by tomek on 5/26/26.
//




/*
podczas kazdej sesji chce miec minium oraz maximum
z tego co sie pojawilo dotychczas no i zysk to roznica

kopiec min max?

min max w czasie stalym
dodawanie i usuwanie w czasie O(log n)


kopiec jest przechowywany w tablicy chyba w porzadku

kopierc wyglada tak
root ma dwoje dzieci
lewe dziecko jest minimum calego drzewa
prawe jest maksimum
potem ich dzieci analogicznie minimum i maksimum
poddrzewa roota


usuwam min - usuwam cos z konca tablicy i
zamieniam z minimum
a potem poprawiam minimum
patrze na dwoch kandydatow
to dzieci ktore sa min

usuwam max - usuwam cos z konca i zamieniam z max

max to chlopcy min to dziewczynki

jak jestem chlopcem to lece




ale jak bede przechowywal wszystkie dane to mi sie nie zmieszcza w pamieci
zatem chce przechowywac tylko n minimow i n maximow


poki nie mam 2n elementow to moge trzymac to w kopcu min max jednym
potem jak juz sie pojawi wystarczajaco duzo to rozdzielam
to na dwa kopce wyciagajac maxy

dwa kopce min max


Min kopiec min max
<
Max kopiec min max


mam element jesli on jest mniejszy niz max w Min to wyrzucam ten max
i wrzucam nowy element
jesli jest wiekszy niz min w Max to wyrzucam ten min i wrzucam
nowy element
wpp ignoruje element



long longa uzyj bo ci inta nie starczy
*/


#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

class MinMaxHeap {
    int A[20005];
    int heap_size;

    bool isMinLevel(int i) {
        int temp = i + 1;
        int level = 0;
        while (temp > 1) {
            temp >>= 1;
            level++;
        }
        return (level & 1) == 0;
    }

    void pushUpMin(int i) {
        if (i > 2) {
            int grandparent = (i - 3) / 4;
            if (A[i] < A[grandparent]) {
                swap(A[i], A[grandparent]);
                pushUpMin(grandparent);
            }
        }
    }

    void pushUpMax(int i) {
        if (i > 2) {
            int grandparent = (i - 3) / 4;
            if (A[i] > A[grandparent]) {
                swap(A[i], A[grandparent]);
                pushUpMax(grandparent);
            }
        }
    }

    void pushUp(int i) {
        if (i != 0) {
            int parent = (i - 1) / 2;
            if (isMinLevel(i)) {
                if (A[i] > A[parent]) {
                    swap(A[i], A[parent]);
                    pushUpMax(parent);
                } else {
                    pushUpMin(i);
                }
            } else {
                if (A[i] < A[parent]) {
                    swap(A[i], A[parent]);
                    pushUpMin(parent);
                } else {
                    pushUpMax(i);
                }
            }
        }
    }

    void pushDownMin(int i) {
        int m = i;
        bool isGrandchild = false;

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap_size && A[left] < A[m]) { m = left; isGrandchild = false; }
        if (right < heap_size && A[right] < A[m]) { m = right; isGrandchild = false; }

        for (int j = 1; j <= 2; ++j) {
            int child = 2 * i + j;
            if (child < heap_size) {
                int cLeft = 2 * child + 1;
                int cRight = 2 * child + 2;
                if (cLeft < heap_size && A[cLeft] < A[m]) { m = cLeft; isGrandchild = true; }
                if (cRight < heap_size && A[cRight] < A[m]) { m = cRight; isGrandchild = true; }
            }
        }

        if (m != i) {
            swap(A[i], A[m]);
            if (isGrandchild) {
                int parent = (m - 1) / 2;
                if (A[m] > A[parent]) {
                    swap(A[m], A[parent]);
                }
                pushDownMin(m);
            }
        }
    }

    void pushDownMax(int i) {
        int m = i;
        bool isGrandchild = false;

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap_size && A[left] > A[m]) { m = left; isGrandchild = false; }
        if (right < heap_size && A[right] > A[m]) { m = right; isGrandchild = false; }

        for (int j = 1; j <= 2; ++j) {
            int child = 2 * i + j;
            if (child < heap_size) {
                int cLeft = 2 * child + 1;
                int cRight = 2 * child + 2;
                if (cLeft < heap_size && A[cLeft] > A[m]) { m = cLeft; isGrandchild = true; }
                if (cRight < heap_size && A[cRight] > A[m]) { m = cRight; isGrandchild = true; }
            }
        }

        if (m != i) {
            swap(A[i], A[m]);
            if (isGrandchild) {
                int parent = (m - 1) / 2;
                if (A[m] < A[parent]) {
                    swap(A[m], A[parent]);
                }
                pushDownMax(m);
            }
        }
    }

    void pushDown(int i) {
        if (isMinLevel(i)) {
            pushDownMin(i);
        } else {
            pushDownMax(i);
        }
    }

public:
    MinMaxHeap() : heap_size(0) {}

    void insert(int val) {
        A[heap_size] = val;
        pushUp(heap_size);
        heap_size++;
    }

    int extractMin() {
        if (heap_size == 0) return -1;
        int minVal = A[0];
        A[0] = A[heap_size - 1];
        heap_size--;
        if (heap_size > 0) {
            pushDown(0);
        }
        return minVal;
    }

    int extractMax() {
        if (heap_size == 0) return -1;
        if (heap_size == 1) {
            int maxVal = A[0];
            heap_size--;
            return maxVal;
        }
        int maxIdx = 1;
        if (heap_size > 2 && A[2] > A[1]) {
            maxIdx = 2;
        }
        int maxVal = A[maxIdx];
        A[maxIdx] = A[heap_size - 1];
        heap_size--;
        if (maxIdx < heap_size) {
            pushDown(maxIdx);
        }
        return maxVal;
    }

    int getMin() const {
        if (heap_size == 0) return -1;
        return A[0];
    }

    int getMax() const {
        if (heap_size == 0) return -1;
        if (heap_size == 1) return A[0];
        if (heap_size == 2) return A[1];
        return max(A[1], A[2]);
    }

    int size() const {
        return heap_size;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;

            MinMaxHeap H;
            MinMaxHeap H_min;
            MinMaxHeap H_max;
            bool split_done = false;
            long long profit = 0;

            for (int i = 0; i < n; ++i) {
                int k;
                cin >> k;
                int req = n - i;

                for (int j = 0; j < k; ++j) {
                    int val;
                    cin >> val;

                    if (!split_done) {
                        H.insert(val);
                        if (H.size() == 2 * req) {
                            for (int m = 0; m < req; ++m) {
                                H_max.insert(H.extractMax());
                            }
                            int remaining = H.size();
                            for (int m = 0; m < remaining; ++m) {
                                H_min.insert(H.extractMin());
                            }
                            split_done = true;
                        }
                    } else {
                        if (val < H_min.getMax()) {
                            H_min.extractMax();
                            H_min.insert(val);
                        } else if (val > H_max.getMin()) {
                            H_max.extractMin();
                            H_max.insert(val);
                        }
                    }
                }

                if (!split_done) {
                    profit += (H.extractMax() - H.extractMin());
                } else {
                    profit += (H_max.extractMax() - H_min.extractMin());
                }
            }
            cout << profit << "\n";
        }
    }
    return 0;
}